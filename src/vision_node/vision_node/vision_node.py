import rclpy
from rclpy.node import Node
from example_interfaces.srv import Trigger

class VisionNode(Node):
    def __init__(self):
        super().__init__('vision_node')

        # Servicios estándar tipo Trigger
        self.create_service(Trigger, 'get_pose', self.get_pose_callback)
        self.create_service(Trigger, 'get_objetivo', self.get_objetivo_callback)

        self.timer = self.create_timer(1.0, self.timer_callback)  # Cada 1s

    def timer_callback(self):
        # Publicación simulada, sin topic
        self.get_logger().info("Simulando procesamiento de visión...")

    def get_pose_callback(self, request, response):
        response.success = True
        response.message = "1.0,3.0,30.0"  # x, y, theta
        self.get_logger().info("Respondido get_pose con datos simulados")
        return response

    def get_objetivo_callback(self, request, response):
        response.success = True
        response.message = "-5.0,-2.0"  # x_obj, y_obj
        self.get_logger().info("Respondido get_objetivo con datos simulados")
        return response

def main(args=None):
    rclpy.init(args=args)
    node = VisionNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()
