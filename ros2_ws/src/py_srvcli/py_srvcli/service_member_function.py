from example_interfaces.srv import AddTwoInts

# Dependencies
import rclpy
from rclpy.node import Node

# Define MinimalService class and inherit from Node class
class MinimalService(Node):
    
    def __init__(self):
        # Initialize the node by calling __init__ of the Parent class (Node)
        super().__init__('minimal_service')
        # Create a service with a type, name, and callback function 
        self.srv = self.create_service(AddTwoInts, 'add_two_ints', self.add_two_ints_callback)
    
    # Update the response.sum and log the confirmation
    def add_two_ints_callback(self, request, response):
        response.sum = request.a + request.b
        self.get_logger().info('Incoming request\na: %d b: %d' % (request.a, request.b))
        return response

def main():
    # Init ros library
    rclpy.init()
    
    # Create a MinimalService instance
    minimal_service = MinimalService()
    
    # Spin up the Node
    rclpy.spin(minimal_service)
    
    rclpy.shutdown()

if __name__ == '__main__':
    main()
