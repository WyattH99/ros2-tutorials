# Copyright 2016 Open Source Robotics Foundation, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Dependencies
import rclpy
from rclpy.node import Node

# Need to add these Dependencies to the package.xml
from std_msgs.msg import String


# This class inherits from Node
class MinimalPublisher(Node):
    
    # Constructor
    def __init__(self):
        # Call the Node class Constructor and name it
        super().__init__('minimal_publisher')
        # Declares that the node publishes a String over a topic named topic
        # with a queue size of 10
        self.publisher_ = self.create_publisher(String, 'topic', 10)
        # Create a timer that calles timer_callback every 0.5 secs
        timer_period = 0.5  # seconds
        self.timer = self.create_timer(timer_period, self.timer_callback)
        # Counter
        self.i = 0

    def timer_callback(self):
        # Create the message that will be published
        msg = String()
        msg.data = 'Hello World: %d' % self.i
        # Hand the message to the publish that was created in __init__
        self.publisher_.publish(msg)
        # Log to the console that the message was published
        self.get_logger().info('Publishing: "%s"' % msg.data)
        # Increment the counter
        self.i += 1


def main(args=None):
    # Initialize the ros
    rclpy.init(args=args)
    
    # Create the Publisher
    minimal_publisher = MinimalPublisher()

    # tell ros to spin up the node
    rclpy.spin(minimal_publisher)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    minimal_publisher.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
