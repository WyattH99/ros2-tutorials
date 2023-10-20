import sys

# Dependencies
from example_interfaces.srv import AddTwoInts
import rclpy
from rclpy.node import Node


# MinimalClientAsync inherits from Node
class MinimalClientAsync(Node):

    def __init__(self):
        # initialize using the Node init and call it minimal_client_async
        super().__init__('minimal_client_async')
        # Create a client with a type and name that is same as the service node
        self.cli = self.create_client(AddTwoInts, 'add_two_ints')
        # Check if the service matching the client is available
        while not self.cli.wait_for_service(timeout_sec=1.0):
            self.get_logger().info('service not available, waiting again...')
        self.req = AddTwoInts.Request()

    def send_request(self, a, b):
        self.req.a = a
        self.req.b = b
        # Check the future to see if there is a response from the service
        self.future = self.cli.call_async(self.req)
        rclpy.spin_until_future_complete(self, self.future)
        return self.future.result()


def main():
    # Initialize Ros library
    rclpy.init()

    # Create a Client node
    minimal_client = MinimalClientAsync()
    # Use sys.argv to get the inputs from the console for the request
    response = minimal_client.send_request(int(sys.argv[1]), int(sys.argv[2]))
    # Logg the response and the request info
    minimal_client.get_logger().info(
            'Result of add_two_ints: for %d + %d = %d' %
            (int(sys.argv[1]), int(sys.argv[2]), response.sum))
    
    # Decontruct the Node
    minimal_client.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
