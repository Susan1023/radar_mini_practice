cmake_minimum_required(VERSION 3.16)
project(radar_mini)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(radar_core
    src/geometry.cpp
    src/cluster.cpp
    src/tracker.cpp
    src/fusion.cpp
    src/pipeline.cpp)

target_include_directories(radar_core PUBLIC include)

add_executable(radar_mini main.cpp)
target_link_libraries(radar_mini PRIVATE radar_core)

option(BUILD_ROS_NODE "Build ROS adapter" OFF)

if(BUILD_ROS_NODE)
    find_package(rclcpp REQUIRED)
    find_package(std_msgs REQUIRED)

    add_executable(radar_ros ros_main.cpp)
    target_link_libraries(
        radar_ros PRIVATE radar_core rclcpp::rclcpp std_msgs::std_msgs
    )

endif()