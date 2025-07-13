import rclpy
from rclpy.node import Node
from hexapod_interfaces.srv import ObtenerPoseRobot, ObtenerObjetos, CapturarImagen
from hexapod_interfaces.msg import Objeto

from coppeliasim_zmqremoteapi_client import RemoteAPIClient
import numpy as np
import cv2
import base64
from math import atan2, degrees

class VisionNode(Node):
    def __init__(self):
        super().__init__('vision_node')

        # Conexión con CoppeliaSim
        self.client = RemoteAPIClient()
        self.sim = self.client.require('sim')
        self.vision_sensor_handle = self.sim.getObject('/visionSensor')

        self.ultima_binaria = None  # Para almacenar última imagen binaria

        # Crear servicios
        self.create_service(ObtenerPoseRobot, 'get_orientacion_flecha', self.handle_flecha)
        self.create_service(ObtenerObjetos, 'get_objetos_detectados', self.handle_objetos)
        self.create_service(CapturarImagen, 'get_mapa_binario', self.handle_mapa_binario)
        self.get_logger().info("Servicios listos: get_orientacion_flecha, get_objetos_detectados y get_mapa_binario.")

    def capturar_imagen(self):
        img_char, res_x, res_y = self.sim.getVisionSensorCharImage(self.vision_sensor_handle)
        img = np.frombuffer(img_char, dtype=np.uint8).reshape((res_y, res_x, 3))
        img = cv2.cvtColor(img, cv2.COLOR_RGB2BGR)
        return img

    def handle_flecha(self, request, response):
        try:
            img = self.capturar_imagen()
        except Exception as e:
            self.get_logger().error(f"Error capturando imagen: {e}")
            return response

        REAL_WIDTH_M, REAL_HEIGHT_M = 2.04, 1.15
        IMG_HEIGHT_PX, IMG_WIDTH_PX = img.shape[:2]
        RESOL_X = IMG_WIDTH_PX / REAL_WIDTH_M
        RESOL_Y = IMG_HEIGHT_PX / REAL_HEIGHT_M

        YELLOW_LO = np.array([20, 100, 100])
        YELLOW_HI = np.array([35, 255, 255])
        RED_LO1 = np.array([0, 30, 30])
        RED_HI1 = np.array([10, 255, 255])
        RED_LO2 = np.array([170, 30, 30])
        RED_HI2 = np.array([179, 255, 255])
        KERNEL = cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (5,5))

        hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
        mask_tail = cv2.inRange(hsv, YELLOW_LO, YELLOW_HI)
        mask_tail = cv2.morphologyEx(mask_tail, cv2.MORPH_OPEN, KERNEL, iterations=2)
        mask_tail = cv2.morphologyEx(mask_tail, cv2.MORPH_CLOSE, KERNEL, iterations=2)
        conts_tail, _ = cv2.findContours(mask_tail, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
        if not conts_tail:
            self.get_logger().error("No se detectó el marcador amarillo en la cola")
            return response

        c_p = max(conts_tail, key=cv2.contourArea)
        M_p = cv2.moments(c_p)
        tail = np.array([M_p['m10']/M_p['m00'], M_p['m01']/M_p['m00']])

        mask_red = cv2.bitwise_or(cv2.inRange(hsv, RED_LO1, RED_HI1), cv2.inRange(hsv, RED_LO2, RED_HI2))
        mask_red = cv2.morphologyEx(mask_red, cv2.MORPH_OPEN, KERNEL, iterations=2)
        mask_red = cv2.morphologyEx(mask_red, cv2.MORPH_CLOSE, KERNEL, iterations=2)
        conts_r, _ = cv2.findContours(mask_red, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

        flecha = max(conts_r, key=cv2.contourArea, default=None)
        if flecha is None or cv2.contourArea(flecha) < 500:
            self.get_logger().error("No se detectó el contorno de la flecha roja")
            return response

        pts = flecha.reshape(-1, 2).astype(np.float32)
        dists = np.linalg.norm(pts - tail, axis=1)
        tip = pts[np.argmax(dists)]
        dx = tip[0] - tail[0]
        dy = tail[1] - tip[1]
        angle = (degrees(atan2(dy, dx)) + 360) % 360

        x_m = tail[0] / RESOL_X
        y_m = (IMG_HEIGHT_PX - tail[1]) / RESOL_Y

        response.x = float(x_m)
        response.y = float(y_m)
        response.angle = float(angle)
        self.get_logger().info(f"Flecha -> x: {x_m:.2f}, y: {y_m:.2f}, angulo: {angle:.1f}°")
        return response

    def handle_objetos(self, request, response):
        try:
            img = self.capturar_imagen()
        except Exception as e:
            self.get_logger().error(f"Error capturando imagen: {e}")
            return response

        REAL_WIDTH_M, REAL_HEIGHT_M = 2.04, 1.15
        IMG_HEIGHT_PX, IMG_WIDTH_PX = img.shape[:2]
        RESOL_X = IMG_WIDTH_PX / REAL_WIDTH_M
        RESOL_Y = IMG_HEIGHT_PX / REAL_HEIGHT_M
        MIN_AREA_M2 = 0.0008
        AREA_MINIMA = MIN_AREA_M2 * (RESOL_X * RESOL_Y)

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

        # Mapa binario general
        bajo, alto = np.array([0, 30, 30]), np.array([179, 255, 255])
        mapa_ocup = cv2.inRange(hsv, bajo, alto)

        # Remover flecha y marcador amarillo
        mask_red = cv2.bitwise_or(cv2.inRange(hsv, RED_LO1, RED_HI1), cv2.inRange(hsv, RED_LO2, RED_HI2))
        mask_tail = cv2.inRange(hsv, YELLOW_LO, YELLOW_HI)
        mascara_completa = cv2.bitwise_or(mask_red, mask_tail)

        mask_sin_robot = cv2.bitwise_and(mapa_ocup, cv2.bitwise_not(mascara_completa))
        binaria = cv2.morphologyEx(mask_sin_robot, cv2.MORPH_OPEN, KERNEL)
        binaria = cv2.morphologyEx(binaria, cv2.MORPH_CLOSE, KERNEL)

        self.ultima_binaria = binaria  # Guardar para otro servicio

        num_lbl, _, stats, cents = cv2.connectedComponentsWithStats(binaria, connectivity=8)

        for i in range(1, num_lbl):
            area = stats[i, cv2.CC_STAT_AREA]
            if area < AREA_MINIMA:
                continue
            cx_px, cy_px = cents[i]
            cy_map_px = IMG_HEIGHT_PX - cy_px
            cx_m = cx_px / RESOL_X
            cy_m = cy_map_px / RESOL_Y
            h_val, s_val, _ = hsv[int(cy_px), int(cx_px)]

            if 40 <= h_val <= 80 and s_val >= 80:
                color = 1
            elif 90 <= h_val <= 140:
                color = 0
            elif 20 <= h_val <= 35:
                color = 2
            else:
                color = 3

            obj_msg = Objeto()
            obj_msg.x = float(cx_m)
            obj_msg.y = float(cy_m)
            obj_msg.color = int(color)
            response.objetos.append(obj_msg)

        self.get_logger().info(f"{len(response.objetos)} objetos detectados")
        return response

    def handle_mapa_binario(self, request, response):
        try:
            if self.ultima_binaria is None:
                self.get_logger().warn("Binaria aún no generada, capturando imagen...")
                _ = self.handle_objetos(request, ObtenerObjetos.Response())

            if self.ultima_binaria is None:
                self.get_logger().error("No se pudo generar la imagen binaria.")
                response.imagen_base64 = ''
                return response

            _, buffer = cv2.imencode('.png', self.ultima_binaria)
            response.imagen_base64 = base64.b64encode(buffer).decode('utf-8')
            self.get_logger().info("Imagen binaria enviada correctamente.")
            return response
        except Exception as e:
            self.get_logger().error(f"Error en handle_mapa_binario: {e}")
            response.imagen_base64 = ''
            return response

def main(args=None):
    rclpy.init(args=args)
    node = VisionNode()
    try:
        rclpy.spin(node)
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
