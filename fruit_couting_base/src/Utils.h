//
// Created by alg on 7/22/21.
//

#ifndef FRUIT_COUTING_BASE_UTILS_H
#define FRUIT_COUTING_BASE_UTILS_H
#include <sensor_msgs/Image.h>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/core.hpp>
#include <geometry_msgs/TransformStamped.h>
#include <tf2_ros/transform_listener.h>

cv::Mat  getCvMatFromImage(const sensor_msgs::Image sm_image, bool depth_image= false){
    cv::Mat current_rgb_image;
    cv_bridge::CvImagePtr cv_ptr;
    try
    {
        if(depth_image) cv_ptr = cv_bridge::toCvCopy(sm_image, sensor_msgs::image_encodings::TYPE_32FC1);
        else cv_ptr = cv_bridge::toCvCopy(sm_image, sensor_msgs::image_encodings::BGR8);
    }
    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("cv_bridge exception: %s", e.what());
    }
    current_rgb_image = cv_ptr->image;
    return current_rgb_image;
}

geometry_msgs::TransformStamped getCameraTF(){
    geometry_msgs::TransformStamped tf_stamped;
    tf2_ros::Buffer tf2_buffer;
    tf2_ros::TransformListener tf2_listener(tf2_buffer);

    try{
        tf_stamped = tf2_buffer.lookupTransform("camera_link", "world",
                                                    ros::Time(0));
    }
    catch (tf2::TransformException &ex) {
        ROS_WARN("%s",ex.what());
        ros::Duration(1.0).sleep();
    }
    return tf_stamped;


}
#endif //FRUIT_COUTING_BASE_UTILS_H
