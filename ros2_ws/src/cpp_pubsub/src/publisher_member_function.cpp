// Copyright 2016 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// Header files
// Standard C++ Headers
#include <chrono>
#include <memory>
//#include <functional>
//#include <string>

// ROS 2 Specific Headers (also dependencies in package.xml and CMakeLists.txt
#include "rclcpp/rclcpp.hpp" // Allows the use of the common pieces of ROS 2
#include "tutorial_interfaces/msg/num.hpp" // Tutorial for interfaces
//#include "std_msgs/msg/string.hpp" // Built-in message types to publish data

// Namespace declared
using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses std::bind() to register a
 * member function as a callback from the timer. */

// MinimalPublisher class declared that inherits from the rclcpp::Node class
class MinimalPublisher : public rclcpp::Node
{
public:
  MinimalPublisher() // Constructor Initializes name and count_
  : Node("minimal_publisher"), count_(0)
  {
    // Creates the publisher String type with the topic name and queue size 
    //publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
    publisher_ = this->create_publisher<tutorial_interfaces::msg::Num>("topic",10);
    // Creates wall timer that executes "timer_callback" method every 500ms
    timer_ = this->create_wall_timer(
      500ms, std::bind(&MinimalPublisher::timer_callback, this));
  }

private:
  // Define timer_callback() used in the constructor
  void timer_callback()
  {
    // Creates the count message, publishes it, and couts a confirmation
    //auto message = std_msgs::msg::String();
    //message.data = "Hello, world! " + std::to_string(count_++);
    //RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
    auto message = tutorial_interfaces::msg::Num();
    message.num = this->count_++;
    RCLCPP_INFO_STREAM(this->get_logger(), "Publishing: '" << message.num << "'");
    publisher_->publish(message);
  }

  // Declaration of the private variables
  rclcpp::TimerBase::SharedPtr timer_;
  //rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  rclcpp::Publisher<tutorial_interfaces::msg::Num>::SharedPtr publisher_;
  size_t count_;
};

int main(int argc, char * argv[])
{
  // Initialize ROS 2
  rclcpp::init(argc, argv);
  // Start processing
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}
