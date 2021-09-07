cmake_minimum_required(VERSION 3.0.2)
project(fruit_couting_base)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(OpenCV REQUIRED)
find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
    sensor_msgs cv_bridge
  roscpp
  rospy
  sensor_msgs
  std_msgs
  tf2 tf2_ros
        message_generation
        tf2_geometry_msgs
)

# Generate messages in the 'msg' folder
add_message_files(
        FILES
        vecPoints.msg
        #   Message2.msg
)

## Generate added messages and services with any dependencies listed here
generate_messages(
        DEPENDENCIES
        std_msgs
        geometry_msgs
)


catkin_package(
        #  INCLUDE_DIRS include
        #  LIBRARIES my_pkg
        CATKIN_DEPENDS geometry_msgs roscpp std_msgs message_runtime
        #  DEPENDS system_lib
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

#add_executable(fruits_per_image src/fruit_per_image_node.cpp src/depthUtils.h src/depthUtils.h src/ros_callbacks.h )
add_executable(fruits_per_image_message_filters src/fruits_per_image_node_with_message_filters.cpp )
add_executable(camera_pose_publisher_node src/camera_pose_publisher_node.cpp src/Utils.h)

#target_link_libraries(fruits_per_image ${catkin_LIBRARIES} ${OpenCV_LIBS})
target_link_libraries(fruits_per_image_message_filters ${catkin_LIBRARIES} ${OpenCV_LIBS})
target_link_libraries(camera_pose_publisher_node ${catkin_LIBRARIES} ${OpenCV_LIBS})
