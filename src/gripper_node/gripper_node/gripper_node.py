import rclpy
from rclpy.node import Node
from std_srvs.srv import Trigger
from std_msgs.msg import Int32

class GripperNode(Node):
    def __init__(self):
        super().__init__('gripper_node')

        # Estado del gripper: 0 = cerrado, 1 = abierto
        self.estado = 0

        # Servicio Trigger para activar (alternar) el gripper
        self.srv = self.create_service(Trigger, 'activar_gripper', self.callback_trigger)

        # Publicador de estado del gripper
        self.publisher = self.create_publisher(Int32, '/gripper_estado', 10)

        self.get_logger().info('Nodo de gripper listo con servicio y publicación')

    def callback_trigger(self, request, response):
        # Alterna el estado
        if self.estado == 0:
            self.estado = 1
            self.abrir()
        else:
            self.estado = 0
            self.cerrar()

        # Publica el nuevo estado
        estado_msg = Int32()
        estado_msg.data = self.estado
        self.publisher.publish(estado_msg)

        response.success = True
        response.message = f'Gripper {"abierto" if self.estado == 1 else "cerrado"}'
        return response

    def abrir(self):
        self.get_logger().info('>> Abriendo gripper...')

    def cerrar(self):
        self.get_logger().info('>> Cerrando gripper...')

def main(args=None):
    rclpy.init(args=args)
    node = GripperNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()
