//
// Created by alg on 7/21/21.
//
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
#include "Utils.h"
#include <sensor_msgs/PointCloud2.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/PointStamped.h>
//HACK: currently just using PoseArray to publish all the points
#include <geometry_msgs/PoseArray.h>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Geometry>

//include message_filters header files
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <gazebo_msgs/ModelStates.h>
#include <tf2_ros/transform_listener.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <tf2/LinearMath/Matrix3x3.h>
#include "fruit_couting_base/vecPoints.h"

//publishing the vector of 3D positions of the centres of all circles detected in the circle
ros::Publisher pub_circles_centres;


std::string rgb_image_topic = "/camera/rgb/image_raw";
std::string depth_image_topic = "/camera/depth/image_raw";
std::string circles_centres_topic = "/fruits_per_image/camera_pose_circles_centres";

void get3DPointsOfCentres(const std::vector<cv::Vec3f>& circles,
                          cv::Mat depth_image,
                          fruit_couting_base::vecPoints & camera_pose_circles_centres,
                          const geometry_msgs::PoseStamped camera_pose) {
    camera_pose_circles_centres.header.frame_id = "world";
    camera_pose_circles_centres.header.stamp = ros::Time::now();

    for(auto circle: circles){
        geometry_msgs::Point current_point;
        //convert pixel to 3D point
        cv::Point3_<float_t> *p = depth_image.ptr<cv::Point3_<float_t> >(circle[1], circle[0]); //note that it has (y,x) thats why circle[1] came first
        double z = p->z;
        Eigen::Matrix3d camera_matrix;
        camera_matrix <<565.6, 0, 320.5,
                        0, 565.6, 240.5,
                        0, 0, 1;
        Eigen::Vector3d uvw;
        uvw << z*circle[0],
                z*circle[1],
                z;
        //points wrt camera optical frame
        Eigen::Vector3d coTp = camera_matrix.inverse() * uvw;
        Eigen::Vector4d coTpoint;
        coTpoint << coTp[0], coTp[1], coTp[2], 1;
        Eigen::Matrix4d cHco, wHc;
        cHco << 0, 0, 1, 0,
                -1, 0, 0, 0,
                0, -1, 0, 0,
                0, 0, 0, 1;
        tf2::Quaternion tf2_quat;
        tf2_quat.setX(camera_pose.pose.orientation.x);
        tf2_quat.setY(camera_pose.pose.orientation.y);
        tf2_quat.setZ(camera_pose.pose.orientation.z);
        tf2_quat.setW(camera_pose.pose.orientation.w);
        tf2::Matrix3x3 rotation_matrix(tf2_quat);
        wHc <<  rotation_matrix[0][0], rotation_matrix[0][1], rotation_matrix[0][2], camera_pose.pose.position.x,
                rotation_matrix[1][0], rotation_matrix[1][1], rotation_matrix[1][2], camera_pose.pose.position.y,
                rotation_matrix[2][0], rotation_matrix[2][1], rotation_matrix[2][2], camera_pose.pose.position.z,
                0, 0, 0, 1;
        Eigen::Vector4d wHpoint= wHc*cHco*coTpoint;
        current_point.x = wHpoint[0];
        current_point.y = wHpoint[1];
        current_point.z = wHpoint[2];

        //add to the geometry_msgs::PoseArray vector
        camera_pose_circles_centres.centres3d.push_back(current_point);
        geometry_msgs::Point centre2d;
        centre2d.x = circle[0];
        centre2d.y = circle[1];
        camera_pose_circles_centres.centres2d.push_back(centre2d);
        camera_pose_circles_centres.camera_pose = camera_pose.pose;

    }

}

void detectCirclesInCurrentRGBImage(const cv::Mat& current_rgb_image, std::vector<cv::Vec3f>& circles){
    cv::Mat gray;
    cv::cvtColor(current_rgb_image, gray, cv::COLOR_BGR2GRAY);
    medianBlur(gray, gray, 5);

    cv::HoughCircles(gray, circles, cv::HOUGH_GRADIENT, 1,
                     gray.rows/16,  // change this value to detect circles with different distances to each other
                     100, 30, 1, 30 // change the last two parameters
            // (min_radius & max_radius) to detect larger circles
    );
    std::cout<<"number of circles in the image: "<<circles.size()<<std::endl;


}
void rgbDepthCameraPoseCallback(const sensor_msgs::ImageConstPtr& rgb_msg,
                                const sensor_msgs::ImageConstPtr& depth_msg,
                                const geometry_msgs::PoseStamped& pose_msg){

    cv::Mat current_rgb_image = getCvMatFromImage(*rgb_msg);
    cv::Mat current_depth_image = getCvMatFromImage(*depth_msg, true);

    //detect circles
    std::vector<cv::Vec3f> circles;
    detectCirclesInCurrentRGBImage(current_rgb_image, circles);

    //get 3D points of the circles
    //geometry_msgs::PoseArray circles_centres;
    fruit_couting_base::vecPoints camera_pose_circles_centres_msg;
    //using tf2 to get transform of camera_optical_frame wrt world

    get3DPointsOfCentres(circles, current_depth_image,  camera_pose_circles_centres_msg, pose_msg);

    //publish the centres
    pub_circles_centres.publish(camera_pose_circles_centres_msg);
    //TODO: may have to check if there is a need to clear this or not. I dont want it to add to the previous camera poses
    //circles_centres.poses.clear();
}

int main(int argc, char** argv){
    ros::init(argc, argv, "fruits_per_image");
    ros::NodeHandle nh;
    message_filters::Subscriber<sensor_msgs::Image> sub_rgb_image(nh, rgb_image_topic, 100);
    message_filters::Subscriber<sensor_msgs::Image> sub_depth_image(nh, depth_image_topic, 100);
    message_filters::Subscriber<geometry_msgs::PoseStamped> sub_camera_pose (nh, "/depth_camera/pose_gt", 100);

    //pub_circles_centres = nh.advertise<geometry_msgs::PoseArray>(circles_centres_topic, 10);
    pub_circles_centres = nh.advertise<fruit_couting_base::vecPoints>(circles_centres_topic, 10);

    typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::Image, sensor_msgs::Image , geometry_msgs::PoseStamped > MySyncPolicy;
    message_filters::Synchronizer<MySyncPolicy> sync2(MySyncPolicy(30), sub_rgb_image, sub_depth_image, sub_camera_pose);
    sync2.registerCallback(&rgbDepthCameraPoseCallback);
    ros::spin();
    return 0;
}
