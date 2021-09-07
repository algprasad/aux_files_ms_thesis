#include <ros/ros.h>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/core/core.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <sensor_msgs/Image.h>
#include <cv_bridge/cv_bridge.h>
#include <iostream>
#include "depthUtils.h"
#include <sensor_msgs/PointCloud2.h>
#include <geometry_msgs/Point.h>
//HACK: currently just using PoseArray to publish all the points
#include <geometry_msgs/PoseArray.h>


cv::Mat current_rgb_image;
cv::Mat current_depth_image;
sensor_msgs::PointCloud2 current_point_cloud;
//publishing the vector of 3D positions of the centres of all circles detected in the circle
ros::Publisher pub_circles_centres;

bool recieved_first_rgb_image = false;
bool recieved_first_point_cloud = false;
std::string rgb_image_topic = "/camera/rgb/image_raw";
std::string depth_image_topic = "/camera/depth/points";
std::string circles_centres_topic = "/fruits_per_image/circles_centres";
std::string depth_image_topic = "/camera/depth/image_raw";
void depthImageCallback(const sensor_msgs::ImageConstPtr msg){
    cv_bridge::CvImagePtr cv_ptr;
    try
    {
        cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::TYPE_32FC1);
    }
    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("cv_bridge exception: %s", e.what());
        return;
    }
    current_depth_image = cv_ptr->image;
}

void rgbImageCallback(const sensor_msgs::ImageConstPtr msg){
    //std::cout<<"inside image callback\n";
    cv_bridge::CvImagePtr cv_ptr;
    try
    {
        cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    }
    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("cv_bridge exception: %s", e.what());
        return;
    }
    current_rgb_image = cv_ptr->image;
    recieved_first_rgb_image = true;

}

void get3DPointsOfCentres(std::vector<cv::Vec3f> circles) {
    geometry_msgs::PoseArray circles_centres;
    for(auto circle: circles){
        geometry_msgs::Pose current_point;
        //std::cout<<"circle centre: "<<circle[0]<<" "<<circle[1]<<std::endl;
        //pixelTo3DPoint(current_point_cloud, circle[0], circle[1], current_point);
        cv::Point3_<float_t> *p = current_depth_image.ptr<cv::Point3_<float_t> >(circle[1], circle[0]);

        std::cout<<"depth: "<<p->z<<" "<<p->x<<" "<<p->y<<"\n";
        circles_centres.poses.push_back(current_point);
    }
    pub_circles_centres.publish(circles_centres);

}

void depthPointsCallback(const sensor_msgs::PointCloud2ConstPtr& msg){
    current_point_cloud = *msg;
    recieved_first_point_cloud = true;
}

void detectCirclesInCurrentRGBImage(){
    cv::Mat gray;
    cv::cvtColor(current_rgb_image, gray, cv::COLOR_BGR2GRAY);
    medianBlur(gray, gray, 5);
    std::vector<cv::Vec3f> circles;
    cv::HoughCircles(gray, circles, cv::HOUGH_GRADIENT, 1,
                     gray.rows/16,  // change this value to detect circles with different distances to each other
                     100, 30, 1, 30 // change the last two parameters
            // (min_radius & max_radius) to detect larger circles
    );

    std::cout<<"number of circles in the image: "<<circles.size()<<std::endl;

    if(recieved_first_point_cloud) get3DPointsOfCentres(circles);

}
//current rgb image
int main(int argc, char** argv){
    ros::init(argc, argv, "fruits_per_image");
    ros::NodeHandle nh;

    //subscribe to the rgb and depth image
    //TODO: Make this into a message_filter so that you are operating on the same rgb image and depth image at the correct camera pose.
    ros::Subscriber sub_rgb_image = nh.subscribe<sensor_msgs::Image>(rgb_image_topic, 10, rgbImageCallback);
    ros::Subscriber sub_depth_image = nh.subscribe<sensor_msgs::Image>(depth_image_topic, 10, depthImageCallback);
    ros::Subscriber sub_depth_points = nh.subscribe<sensor_msgs::PointCloud2>(depth_image_topic, 10, depthPointsCallback);

    pub_circles_centres = nh.advertise<geometry_msgs::PoseArray>(circles_centres_topic, 10);
    ros::Rate rate(20);
    while(ros::ok()){
        std::cout<<"spinning\n";
        //detect circles in the image and determine the centres
        if(recieved_first_rgb_image) detectCirclesInCurrentRGBImage();

        ros::spinOnce();
        rate.sleep();
    }

    return 0;
}