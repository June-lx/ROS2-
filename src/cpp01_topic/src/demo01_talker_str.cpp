/*
  需求：以某个频率发送文本“hello world！”，文本后缀编号，每发布一条，编号加1.
  流程：
    1.包含头文件
    2.初始化ROS2客户端
    3.自定义节点类
      3-1.创建消息发布方
      3-2.创建定时器
      3-3.组织并发布消息
    4.调用spin函数，传入自定义类对象指针
    5.释放资源
*/

// 1.包含头文件
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <chrono>

using namespace std::chrono_literals;
// 3.自定义节点类
class TalkerStr : public rclcpp::Node{
  public:
    TalkerStr():Node("talker_node_cpp"){
      RCLCPP_INFO(this->get_logger(),"发布节点创建！");
      // 3-1.创建消息发布方
      /*
        模板：被发布的消息类型
        参数1：话题名称
        参数2：QOS（消息队列长度）
        返回值：发布者对象指针
      */
      publisher_ = this->create_publisher<std_msgs::msg::String>("chatter", 10);
      // 3-2.创建定时器
      /*
        参数1：周期时间
        参数2：回调函数
        返回值：定时器对象指针
      */
      timer_ = this->create_wall_timer(1s, std::bind(&TalkerStr::on_timer, this));
    }
  private:
    void on_timer(){
      // 3-3.组织并发布消息
      auto message = std_msgs::msg::String();
      message.data = std::string("hello world! ") + std::to_string(count_++);
      RCLCPP_INFO(this->get_logger(), "发布方发布的消息：%s", message.data.c_str());
      publisher_->publish(message);
    }
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    size_t count_ = 0;
  };
int main(int argc, char ** argv)
{
  // 2.初始化ROS2客户端
  rclcpp::init(argc, argv);

  // 4.调用spin函数，传入自定义类对象指针
  rclcpp::spin(std::make_shared<TalkerStr>());

  // 5.释放资源
  rclcpp::shutdown();
  return 0;
}
