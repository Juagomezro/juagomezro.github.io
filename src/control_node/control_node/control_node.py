import rclpy
from rclpy.node import Node
from rclpy.action import ActionClient
from std_msgs.msg import Int32
from hexapod_interfaces.action import EnviarPaso

class ControlNode(Node):
    def __init__(self):
        super().__init__('control_node')
        self._action_client = ActionClient(self, EnviarPaso, 'gui_action')
        self.estado = 1
        self.e_ori = -0.5  # Simulación inicial
        self.e_pos = 1.0

        self.timer = self.create_timer(2.0, self.enviar_logica)

    def enviar_logica(self):
        if not self._action_client.wait_for_server(timeout_sec=1.0):
            self.get_logger().error("No se encuentra el servidor de acción 'gui_action'")
            return

        if self.estado == 1: 
            self.get_logger().info(f"Estado 1: e_ori={self.e_ori} < 0")
            paso = 2
        elif self.estado == 2:
            self.get_logger().info(f"Estado 2: e_ori={self.e_ori} > 0")
            paso = 3
        elif self.estado == 3:
            self.get_logger().info(f"Estado 3: e_pos={self.e_pos} < 0")
            paso = 4
        else:
            self.get_logger().info("Fin del proceso")
            return

        goal_msg = EnviarPaso.Goal()
        goal_msg.paso = paso

        self._action_client.send_goal_async(goal_msg).add_done_callback(self.goal_callback)
        self.estado += 1

    def goal_callback(self, future):
        goal_handle = future.result()
        if not goal_handle.accepted:
            self.get_logger().error("Objetivo rechazado")
            return
        self.get_logger().info("Objetivo aceptado")

        goal_handle.get_result_async().add_done_callback(self.result_callback)

    def result_callback(self, future):
        result = future.result().result
        self.get_logger().info(f"Resultado recibido: {result.recibido}")


def main(args=None):
    rclpy.init(args=args)
    node = ControlNode()
    rclpy.spin(node)
    rclpy.shutdown()
