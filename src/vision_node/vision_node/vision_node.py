import rclpy
from rclpy.node import Node
from hexapod_interfaces.srv import CapturarImagen

import numpy as np
import cv2
import base64
from math import atan2, degrees
from std_msgs.msg import Float32MultiArray


class VisionNode(Node):
    def __init__(self):
        super().__init__('vision_node')

        # Servicio de captura
        self.cli = self.create_client(CapturarImagen, 'capturar_imagen')
        while not self.cli.wait_for_service(timeout_sec=1.0):
            self.get_logger().info('Esperando servicio capturar_imagen...')
        self.req = CapturarImagen.Request()

        # Publishers
        self.pub_orientacion = self.create_publisher(Float32MultiArray, 'flecha_orientacion', 10)
        self.pub_objetos = self.create_publisher(Float32MultiArray, 'objetos_detectados', 10)

    def run(self):
        self.get_logger().info("Escribe '1' para capturar imagen o '0' para salir.")
        while rclpy.ok():
            cmd = input("Comando (1=capturar, 0=salir): ").strip()
            if cmd == '1':
                self.process_image()
            elif cmd == '0':
                self.get_logger().info("Cerrando nodo vision_node.")
                break
            else:
                print("Comando inválido. Usa '1' o '0'.")

    def process_image(self):
        future = self.cli.call_async(self.req)
        rclpy.spin_until_future_complete(self, future)

        if not future.result():
            self.get_logger().error('No se recibió imagen del servicio.')
            return

        # === Decodificar imagen ===
        img_data = base64.b64decode(future.result().imagen_base64)
        img_array = np.frombuffer(img_data, dtype=np.uint8)
        img = cv2.imdecode(img_array, cv2.IMREAD_COLOR)

        # === Parámetros de calibración espacial ===
        REAL_WIDTH_M, REAL_HEIGHT_M = 2.04, 1.15
        IMG_HEIGHT_PX, IMG_WIDTH_PX = img.shape[:2]
        RESOL_X = IMG_WIDTH_PX / REAL_WIDTH_M
        RESOL_Y = IMG_HEIGHT_PX / REAL_HEIGHT_M
        MIN_AREA_M2 = 0.0008
        AREA_MINIMA = MIN_AREA_M2 * (RESOL_X * RESOL_Y)

        # === Umbrales HSV ===
        GREEN_LO = np.array([40, 80, 80])
        GREEN_HI = np.array([80, 255, 255])
        BLUE_LO  = np.array([90, 50, 30])
        BLUE_HI  = np.array([140, 255, 255])
        YELLOW_LO = np.array([20, 100, 100])
        YELLOW_HI = np.array([35, 255, 255])
        RED_LO1 = np.array([0, 30, 30])
        RED_HI1 = np.array([10, 255, 255])
        RED_LO2 = np.array([170, 30, 30])
        RED_HI2 = np.array([179, 255, 255])
        KERNEL = cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (5,5))

        hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
        bajo, alto = np.array([0, 30, 30]), np.array([179, 255, 255])
        mapa_ocup = cv2.inRange(hsv, bajo, alto)
        vis = img.copy()

        # === Detectar marcador amarillo (cola) ===
        mask_tail = cv2.inRange(hsv, YELLOW_LO, YELLOW_HI)
        mask_tail = cv2.morphologyEx(mask_tail, cv2.MORPH_OPEN, KERNEL, iterations=2)
        mask_tail = cv2.morphologyEx(mask_tail, cv2.MORPH_CLOSE, KERNEL, iterations=2)
        conts_tail, _ = cv2.findContours(mask_tail, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
        if not conts_tail:
            self.get_logger().error("No se detectó el marcador amarillo en la cola")
            return
        c_p = max(conts_tail, key=cv2.contourArea)
        M_p = cv2.moments(c_p)
        tail = np.array([M_p['m10']/M_p['m00'], M_p['m01']/M_p['m00']])

        # === Detectar flecha roja ===
        mask_red1 = cv2.inRange(hsv, RED_LO1, RED_HI1)
        mask_red2 = cv2.inRange(hsv, RED_LO2, RED_HI2)
        mask_red = cv2.bitwise_or(mask_red1, mask_red2)
        mask_red = cv2.morphologyEx(mask_red, cv2.MORPH_OPEN, KERNEL, iterations=2)
        mask_red = cv2.morphologyEx(mask_red, cv2.MORPH_CLOSE, KERNEL, iterations=2)
        conts_r, _ = cv2.findContours(mask_red, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

        flecha = None
        area_max = 0
        for c in conts_r:
            area = cv2.contourArea(c)
            if area > area_max:
                flecha = c
                area_max = area
        if flecha is None or area_max < 500:
            self.get_logger().error("No se detectó el contorno de la flecha roja")
            return

        # === Calcular orientación ===
        pts = flecha.reshape(-1, 2).astype(np.float32)
        dists = np.linalg.norm(pts - tail, axis=1)
        tip = pts[np.argmax(dists)]
        dx = tip[0] - tail[0]
        dy = tail[1] - tip[1]
        angle = (degrees(atan2(dy, dx)) + 360) % 360
        print(f"Orientación de la flecha: {angle:.1f}°")

        # === Publicar orientación ===
        tail_x_m = tail[0] / RESOL_X
        tail_y_m = (IMG_HEIGHT_PX - tail[1]) / RESOL_Y
        msg_flecha = Float32MultiArray()
        msg_flecha.data = [tail_x_m, tail_y_m, angle]
        self.pub_orientacion.publish(msg_flecha)
        self.get_logger().info(f"Publicado en /flecha_orientacion: x={tail_x_m:.2f}, y={tail_y_m:.2f}, ángulo={angle:.1f}°")

        # === Detección de objetos excluyendo la flecha ===
        mask_sin_robot = cv2.bitwise_and(mapa_ocup, cv2.bitwise_not(mask_red))
        binaria = cv2.morphologyEx(mask_sin_robot, cv2.MORPH_OPEN, KERNEL, iterations=1)
        binaria = cv2.morphologyEx(binaria, cv2.MORPH_CLOSE, KERNEL, iterations=1)
        num_lbl, labels, stats, cents = cv2.connectedComponentsWithStats(binaria, connectivity=8)

        msg_objetos = Float32MultiArray()
        for lbl in range(1, num_lbl):
            area_px = stats[lbl, cv2.CC_STAT_AREA]
            if area_px < AREA_MINIMA:
                continue
            cx_px, cy_px = cents[lbl]
            cy_map_px = IMG_HEIGHT_PX - cy_px
            cx_m = cx_px / RESOL_X
            cy_m = cy_map_px / RESOL_Y
            h_val, s_val, v_val = hsv[int(cy_px), int(cx_px)]

            if GREEN_LO[0] <= h_val <= GREEN_HI[0] and GREEN_LO[1] <= s_val <= GREEN_HI[1]:
                color_code = 1
            elif BLUE_LO[0] <= h_val <= BLUE_HI[0] and BLUE_LO[1] <= s_val <= BLUE_HI[1]:
                color_code = 0
            elif YELLOW_LO[0] <= h_val <= YELLOW_HI[0] and YELLOW_LO[1] <= s_val <= YELLOW_HI[1]:
                color_code = 2
            else:
                color_code = 3  # Otro

            msg_objetos.data.extend([cx_m, cy_m, float(color_code)])

        self.pub_objetos.publish(msg_objetos)
        self.get_logger().info(f"Publicado en /objetos_detectados: {len(msg_objetos.data)//3} objetos")



def main(args=None):
    rclpy.init(args=args)
    node = VisionNode()
    try:
        node.run()
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
