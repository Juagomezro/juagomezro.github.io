import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from vision_node.msg import MapaDatos
from cv_bridge import CvBridge
import numpy as np
import cv2

class VisionNode(Node):
    def __init__(self):
        super().__init__('vision_node')

        # Dirección IP de la cámara (RTSP o MJPEG o HTTP stream)
        self.cam_url = 'http://<IP>:<PUERTO>/video'  # Reemplaza esto con la URL real
        self.cap = cv2.VideoCapture(self.cam_url)

        if not self.cap.isOpened():
            self.get_logger().error("No se pudo abrir la cámara IP")
            return

        self.bridge = CvBridge()

        # Publicadores
        self.data_pub = self.create_publisher(MapaDatos, 'mapa_datos', 10)
        self.img_pub = self.create_publisher(Image, 'imagen_debug', 10)

        self.timer = self.create_timer(1.0, self.timer_callback)  # cada 1s

    def timer_callback(self):
        ret, frame = self.cap.read()

        if not ret:
            self.get_logger().warn("No se pudo leer imagen de la cámara.")
            return

        # Procesamiento de imagen aquí
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

        # Simulamos datos (reemplaza esto con tu lógica real)
        matriz = np.identity(3)
        vector = np.array([1.0, 2.0, 3.0])
        pose = np.array([0.5, 1.0, 0.2])

        # Publicar mensaje personalizado
        msg = MapaDatos()
        msg.matriz = matriz.flatten().tolist()
        msg.vector = vector.tolist()
        msg.pose = pose.tolist()
        self.data_pub.publish(msg)

        # Publicar imagen para debug (opcional)
        img_msg = self.bridge.cv2_to_imgmsg(frame, encoding='bgr8')
        self.img_pub.publish(img_msg)

        self.get_logger().info("Publicado MapaDatos y frame")

def main(args=None):
    rclpy.init(args=args)
    node = VisionNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.cap.release()
        node.destroy_node()
        rclpy.shutdown()
