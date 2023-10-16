#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"


class NodeSubCpp: public rclcpp::Node{
    public:
    NodeSubCpp() : Node("node_sub_cpp"){
        subscriber_ = this->create_subscription<std_msgs::msg::String>(
            "topic_1",
            10,
            std::bind(
                &NodeSubCpp::callback,
                this,
                std::placeholders::_1
            )
        );
    }

    private:
    void callback(const std_msgs::msg::String::SharedPtr msg){
        RCLCPP_INFO(
            this->get_logger(),
            "received : '%s",
            msg->data.c_str()
        );
    }
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscriber_;
};

int main(int argc, char *argv[]){
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<NodeSubCpp>());
    rclcpp::shutdown();
    return 0;
}