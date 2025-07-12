import rclpy
from rclpy.node import Node
from hexapod_interfaces.srv import CapturarImagen

from coppeliasim_zmqremoteapi_client import RemoteAPIClient
import numpy as np
import cv2
import base64

class CameraNode(Node):
    def __init__(self):
        super().__init__('camera_node')
        self.get_logger().info("Nodo de cámara iniciado.")

        # Conexión con CoppeliaSim
        self.client = RemoteAPIClient()
        self.sim = self.client.require('sim')

        # Obtener handle del sensor de visión
        self.vision_sensor_handle = self.sim.getObject('/visionSensor')

        # Crear servicio
        self.srv = self.create_service(CapturarImagen, 'capturar_imagen', self.capturar_imagen_callback)

    def capturar_imagen_callback(self, request, response):
        self.get_logger().info("Solicitud recibida: capturar imagen")

        # Obtener imagen y resolución desde el sensor
        img_char, res_x, res_y = self.sim.getVisionSensorCharImage(self.vision_sensor_handle)

        # Convertir imagen a array NumPy y cambiar formato de color
        img = np.frombuffer(img_char, dtype=np.uint8).reshape((res_y, res_x, 3))
        img = cv2.cvtColor(img, cv2.COLOR_RGB2BGR)

        # Codificar imagen en JPG y luego a base64
        success, buffer = cv2.imencode('.jpg', img)
        if not success:
            self.get_logger().error("Error al codificar la imagen.")
            response.imagen_base64 = ''
            return response

        img_base64 = base64.b64encode(buffer).decode('utf-8')
        response.imagen_base64 = img_base64
        self.get_logger().info("Imagen enviada correctamente.")
        return response


def main(args=None):
    rclpy.init(args=args)
    node = CameraNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
