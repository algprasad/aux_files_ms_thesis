cmake_minimum_required(VERSION 3.0.2)
project(fruit_counting_backend)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
set("fruit_couting_base_DIR"  /home/alg/fruit_counting/fruit_counting_ws/devel/share/fruit_couting_base/cmake/)
find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  sensor_msgs
  tf fruit_couting_base
  tf2_ros
)
find_package(GTSAM REQUIRED)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES fruit_counting_backend
#  CATKIN_DEPENDS geometry_msgs roscpp sensor_msgs tf tf2_ros
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(sandbox src/sandbox.cpp)
add_executable(vslam_example  src/visualSLAMExample.cpp)
add_executable(fruit_counting_basic_gtsam src/fruit_counting_gtsam_basic.cpp src/FruitMap.cpp src/FruitMap.h src/Fruit.cpp src/Fruit.h)
target_link_libraries(sandbox PRIVATE ${catkin_LIBRARIES} gtsam)
target_link_libraries(vslam_example PRIVATE ${catkin_LIBRARIES} gtsam)
target_link_libraries(fruit_counting_basic_gtsam PRIVATE ${catkin_LIBRARIES} gtsam)
