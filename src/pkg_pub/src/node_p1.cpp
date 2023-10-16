#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class NodePubCpp : public rclcpp::Node
{
public:
    NodePubCpp() : Node("node_pub_cpp"), count_(0)
    {
        publisher_ = this->create_publisher<std_msgs::msg::String>("topic_1", 10);
        timer_ = this->create_wall_timer(
            std::chrono::seconds(1), std::bind(&NodePubCpp::callback, this));
    }

private:
    void callback()
    {
        auto message = std_msgs::msg::String();
        message.data = "Hello, " + std::to_string(count_++);
        RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
        publisher_->publish(message);
    }

    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    size_t count_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<NodePubCpp>());
    rclcpp::shutdown();
    return 0;
}
