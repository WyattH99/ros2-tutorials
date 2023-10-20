#include "rclcpp/rclcpp.hpp"
//#include "example_interfaces/srv/add_two_ints.hpp"
#include "tutorial_interfaces/srv/add_three_ints.hpp"

#include <memory>

void add(const 
	//std::shared_ptr<example_interfaces::srv::AddTwoInts::Request> request, 
	//std::shared_ptr<example_interfaces::srv::AddTwoInts::Response> response)
	std::shared_ptr<tutorial_interfaces::srv::AddThreeInts::Request> request,
	std::shared_ptr<tutorial_interfaces::srv::AddThreeInts::Response>       response)
{
	//response->sum = request->a + request->b;
	response->sum = request->a + request->b + request->c;
	RCLCPP_INFO(
		rclcpp::get_logger("rclcpp"), 
		//"Incoming request\na: %ld" " b: %ld", 
		"Incoming request\na: %ld" " b: %ld" " c: %ld", request->a, 
		request->b, request->c
		);
	RCLCPP_INFO(
		rclcpp::get_logger("rclcpp"), 
		"Sending Response: [%ld]", 
		(long int)response->sum
		);
}

int main(int argc, char **argv)
{
	// Initializes ROS 2 C++ client library
	rclcpp::init(argc, argv);
	
	// Creates a node named "add_two_ints_server"
	//std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("add_two_ints_server");
	std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("add_three_ints_server");

	// Creates a Service named "add_two_ints" for the node
	// And advertises it over the networks with the &add method
	//rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr service = node->create_service<example_interfaces::srv::AddTwoInts>("add_two_ints", &add);
	rclcpp::Service<tutorial_interfaces::srv::AddThreeInts>::SharedPtr service = node->create_service<tutorial_interfaces::srv::AddThreeInts>("add_three_ints",  &add);

	// Prints log message when ready
	//RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to add two ints.");
	RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to add three ints.");

	// Spins up the node then deconstructs when done.
	rclcpp::spin(node);
	rclcpp::shutdown();
}
