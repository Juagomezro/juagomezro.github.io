import rclpy
from rclpy.node import Node
from rclpy.action import ActionClient
from std_msgs.msg import String
from std_srvs.srv import Trigger, SetBool
from example_interfaces.srv import SetBool as BoolSrv
from std_srvs.srv import Trigger
from std_srvs.srv import SetBool
from std_srvs.srv import SetBool
from example_interfaces.srv import Trigger as TriggerSrv
from hexapod_interfaces.action import EnviarPaso

import numpy as np
from math import cos, sin, atan2, sqrt, radians, degrees

class ControlNode(Node):
    def __init__(self):
        super().__init__('control_node')
        self._action_client = ActionClient(self, EnviarPaso, 'gui_action')

        self.pose = None
        self.objetivo = None

        # Servicios estándar
        self.cli_pose = self.create_client(Trigger, 'get_pose')

        # Nuevo servicio de control que recibe objetivo en string
        self.create_service(String, 'control', self.control_callback)

        self.tolerancia_dist = 1.0
        self.tolerancia_ang = radians(5)
        self.avance_dist = 3.0
        self.giro_angulo = radians(10)

        self.timer = self.create_timer(1.0, self.timer_callback)

    def control_callback(self, request, response):
        try:
            parts = request.data.strip().split('],[')
            pos_str = parts[0].replace('[', '')
            pose_str = parts[1].replace(']', '')

            self.objetivo = np.array([float(x) for x in pos_str.split(',')])
            pose_parts = [float(x) for x in pose_str.split(',')]
            self.pose = (np.array([pose_parts[0], pose_parts[1]]), radians(pose_parts[2]))

            self.get_logger().info(f"Modo recibido: Objetivo={self.objetivo}, Pose={pose_parts}")
            response.success = True
            response.message = "Modo procesado correctamente"
        except Exception as e:
            response.success = False
            response.message = f"Error al procesar modo: {e}"
        return response

    def timer_callback(self):
        if self.pose is None or self.objetivo is None:
            return

        pos_movil, theta_movil = self.pose
        paso = self.calcular_paso(pos_movil, theta_movil, self.objetivo)

        if paso is not None:
            self.enviar_paso(paso)
        else:
            self.get_logger().info("Objetivo alcanzado")

    def calcular_paso(self, pos_movil, theta_movil, punto_objetivo_global):
        R_movil = np.array([
            [cos(theta_movil), -sin(theta_movil)],
            [sin(theta_movil),  cos(theta_movil)]
        ])
        punto_local = R_movil.T @ (punto_objetivo_global - pos_movil)
        distancia = np.linalg.norm(punto_local)
        angulo = atan2(punto_local[1], punto_local[0])

        self.get_logger().info(f"Distancia={distancia:.2f}, Ángulo={degrees(angulo):.2f}°")

        if abs(angulo) > self.tolerancia_ang:
            return 2 if angulo < 0 else 3  # Girar derecha o izquierda
        elif distancia > self.tolerancia_dist:
            return 4  # Avanzar
        else:
            return None  # Objetivo alcanzado

    def enviar_paso(self, paso):
        if not self._action_client.wait_for_server(timeout_sec=1.0):
            self.get_logger().error("No se encuentra el servidor de acción 'gui_action'")
            return

        goal_msg = EnviarPaso.Goal()
        goal_msg.paso = paso

        self.get_logger().info(f"Enviando paso: {paso}")
        send_goal_future = self._action_client.send_goal_async(goal_msg)
        send_goal_future.add_done_callback(self.goal_response_callback)

    def goal_response_callback(self, future):
        goal_handle = future.result()
        if not goal_handle.accepted:
            self.get_logger().warn('Objetivo rechazado')
            return
        self.get_logger().info('Objetivo aceptado')
        goal_handle.get_result_async().add_done_callback(self.result_callback)

    def result_callback(self, future):
        result = future.result().result
        self.get_logger().info(f"Resultado: recibido={result.recibido}")

def main(args=None):
    rclpy.init(args=args)
    node = ControlNode()
    rclpy.spin(node)
    rclpy.shutdown()
