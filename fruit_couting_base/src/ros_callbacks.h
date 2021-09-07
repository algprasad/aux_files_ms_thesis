//
// Created by alg on 7/21/21.
//

#ifndef FRUIT_COUTING_BASE_ROS_CALLBACKS_H
#define FRUIT_COUTING_BASE_ROS_CALLBACKS_H

void depthPointsCallback(const sensor_msgs::PointCloud2ConstPtr& msg){
    current_point_cloud = *msg;
    recieved_first_point_cloud = true;
}

#endif //FRUIT_COUTING_BASE_ROS_CALLBACKS_H
