#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

class HelloWorldPublisher : public rclcpp::Node
{
public:
  HelloWorldPublisher() : Node("hello_world_publisher")
  {
    publisher_ = this->create_publisher<std_msgs::msg::String>("~/hello_world", 10);

    timer_ = this->create_wall_timer(
      std::chrono::seconds(1),
      std::bind(&HelloWorldPublisher::publish_message, this)
    );
  }

private:
  void publish_message()
  {
    auto message = std_msgs::msg::String();
    message.data = "Hello world";
    RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
    publisher_->publish(message);
  }

  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);

  rclcpp::spin(std::make_shared<HelloWorldPublisher>());

  rclcpp::shutdown();
  return 0;
}

