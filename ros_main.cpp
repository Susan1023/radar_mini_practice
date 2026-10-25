#include <memory>
#include <vector>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
#include "pipeline.h"

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<rclcpp::Node>("radar_mini_ros");
    Tracker tracker(1.0);

    auto subscription= 
        node->create_subscription<std_msgs::msg::Float64MultiArray>("radar_points",10,[&tracker,node](std_msgs::msg::Float64MultiArray::SharedPtr msg)
            {
                std::vector<Point> points;
                
                for(std::size_t i=0; i+1< msg->data.size(); i+= 2){
                    points.push_back({msg->data[i], msg->data[i + 1]});

                }
            processLidarFrame(tracker,points, node->now().seconds());
            tracker.print();

            
            
            }
    );


    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}