//
// Created by alg on 7/21/21.
//
#include <ros/ros.h>
#include <gazebo_msgs/ModelStates.h>
#include <gazebo_msgs/ModelState.h>
#include <geometry_msgs/PoseStamped.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_ros/transform_broadcaster.h>
#include <tf2_ros/static_transform_broadcaster.h>

ros::Publisher pub_camera_pose;
void gazeboModelStatesCallback(const gazebo_msgs::ModelStatesConstPtr msg){
    int camera_index = -1;

    for(int i =0; i< msg->pose.size(); i++ ){
        if(msg->name[i] == "depth_camera") camera_index = i;
    }
    if(camera_index == -1) {
        ROS_INFO("depth camera pose not available!");
        return;
    }
    geometry_msgs::PoseStamped camera_pose_gt;
    camera_pose_gt.header.stamp = ros::Time::now();
    camera_pose_gt.pose.position.x = msg->pose[camera_index].position.x;
    camera_pose_gt.pose.position.y= msg->pose[camera_index].position.y;
    camera_pose_gt.pose.position.z = msg->pose[camera_index].position.z;
    camera_pose_gt.pose.orientation.x = msg->pose[camera_index].orientation.x;
    camera_pose_gt.pose.orientation.y = msg->pose[camera_index].orientation.y;
    camera_pose_gt.pose.orientation.z = msg->pose[camera_index].orientation.z;
    camera_pose_gt.pose.orientation.w = msg->pose[camera_index].orientation.w;
    pub_camera_pose.publish(camera_pose_gt);

    //publish a tf
    static tf2_ros::TransformBroadcaster br;
    //the message type that will be published by the transform broadcaster
    geometry_msgs::TransformStamped transform_stamped;
    transform_stamped.header.stamp = ros::Time::now();
    transform_stamped.header.frame_id="world";
    transform_stamped.child_frame_id="camera_base_link";
    transform_stamped.transform.translation.x = camera_pose_gt.pose.position.x;
    transform_stamped.transform.translation.y = camera_pose_gt.pose.position.y;
    transform_stamped.transform.translation.z = camera_pose_gt.pose.position.z;

    transform_stamped.transform.rotation.x = camera_pose_gt.pose.orientation.x;
    transform_stamped.transform.rotation.y = camera_pose_gt.pose.orientation.y;
    transform_stamped.transform.rotation.z = camera_pose_gt.pose.orientation.z;
    transform_stamped.transform.rotation.w = camera_pose_gt.pose.orientation.w;

    br.sendTransform(transform_stamped);

    //static transform from the camera link to the camera_optical_link
    //HACK: Dont use this anywhere else
    static tf2_ros::StaticTransformBroadcaster static_tf_broadcaster;
    geometry_msgs::TransformStamped static_tf_stamped;
    static_tf_stamped.header.stamp = ros::Time::now();
    static_tf_stamped.header.frame_id = "camera_base_link";
    static_tf_stamped.child_frame_id = "camera_link";
    static_tf_stamped.transform.translation.x = 0;
    static_tf_stamped.transform.translation.y = 0;
    static_tf_stamped.transform.translation.z = 0;

    static_tf_stamped.transform.rotation.x = 0.5;
    static_tf_stamped.transform.rotation.y = -0.5;
    static_tf_stamped.transform.rotation.z = 0.5;
    static_tf_stamped.transform.rotation.w = -0.5;

    static_tf_broadcaster.sendTransform(static_tf_stamped);

}
int main(int argc, char** argv){

    ros::init(argc, argv, "camera_node_publisher_node");
    ros::NodeHandle nh;

    //subscribe to the gazebo_msgs
    ros::Subscriber sub_gazebo_model_states = nh.subscribe("/gazebo/model_states", 10, gazeboModelStatesCallback);
    pub_camera_pose = nh.advertise<geometry_msgs::PoseStamped>("/depth_camera/pose_gt", 10);
    ros::Rate rate(50);
    std::cout<<"Publishing Transform\n";
    while(ros::ok()){

        ros::spinOnce();
        rate.sleep();
    }

    return 0;

}