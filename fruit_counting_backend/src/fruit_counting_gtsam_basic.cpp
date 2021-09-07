#include <ros/ros.h>
#include <fruit_couting_base/vecPoints.h>

#include <gtsam/geometry/Point2.h>

#include <gtsam/inference/Symbol.h>
#include <gtsam/nonlinear/ISAM2.h>
#include <gtsam/nonlinear/NonlinearFactorGraph.h>
#include <gtsam/nonlinear/Values.h>

// In GTSAM, measurement functions are represented as 'factors'. Several common
// factors have been provided with the library for solving robotics/SLAM/Bundle
// Adjustment problems. Here we will use Projection factors to model the
// camera's landmark observations. Also, we will initialize the robot at some
// location using a Prior factor.
#include <gtsam/slam/ProjectionFactor.h>
#include "FruitMap.h"

std::string circles_centres_topic = "/fruits_per_image/camera_pose_circles_centres";
bool initialized = false;

//global params
//TODO(OFN): put these in a separate class. There should not be any isloated variable

//calibration parameters : TODO(OFN): get from yaml file
gtsam::Cal3_S2::shared_ptr K(new gtsam::Cal3_S2(565.5, 565.6, 0.0, 320.5, 240.5));

// Define camera observation noise model
auto pixel_measurement_noise = gtsam::noiseModel::Isotropic::Sigma(2, 1);

//iSAM2 parameters
//might have to tweak these
gtsam::ISAM2Params isam2_params;
gtsam::ISAM2 isam2;

//Factor graph object
gtsam::NonlinearFactorGraph factor_graph;

//values of estimates
gtsam::Values initial_estimates;

FruitMap fruit_map;
//the main callback function where everything happens
void cameraPoseCirclesCentresCallback(const fruit_couting_base::vecPointsConstPtr& msg){
    //no point in going through all that if no fruits were detected in the frame
    if(msg->centres2d.size() == 0) return;
    static int camera_pose_index = -1;
    camera_pose_index++;
    std::vector<Fruit> local_fruits;
    //populate the local_fruits vector with fruits with the correct landmark ids
    fruit_map.dataAssociation(msg, local_fruits );

    //add the Generic Projection Factors for all the circles that the camera sees
    for(auto local_fruit: local_fruits) {
        gtsam::Point2 temp_pixel_measurement(local_fruit.temp_pixel_coordinates_.x(),
                                             local_fruit.temp_pixel_coordinates_.y());
        factor_graph.emplace_shared<gtsam::GenericProjectionFactor<gtsam::Pose3,
                gtsam::Point3,
                gtsam::Cal3_S2>>(
                temp_pixel_measurement,
                pixel_measurement_noise,
                gtsam::Symbol('x', camera_pose_index),
                gtsam::Symbol('l', local_fruit.landmark_id_),
                K);

        //initialize the landmarks that have not been seen before
        if(!local_fruit.has_been_seen_before_){
            initial_estimates.insert<gtsam::Point3>(gtsam::Symbol('l', local_fruit.landmark_id_), local_fruit.global_3d_position_);

            /*//TODO: adding prior on every landmark too. BIG BUG: change or understand
            //Add prior on the first landmark
            static auto landmark_prior = gtsam::noiseModel::Isotropic::Sigma(3, 0.01);
            factor_graph.addPrior(gtsam::Symbol('l', local_fruit.landmark_id_), local_fruit.global_3d_position_, landmark_prior);
             */
        }

    }
    //ERROR: Getting an error probably because the projecton factor needs to have two poses linked to them
    //setting the initial estimates of the camera pose as obtained from the ros message
    gtsam::Pose3 camera_pose(gtsam::Rot3(msg->camera_pose.orientation.w,
                                         msg->camera_pose.orientation.x,
                                         msg->camera_pose.orientation.y,
                                         msg->camera_pose.orientation.z),
                             gtsam::Point3(msg->camera_pose.position.x,
                                           msg->camera_pose.position.y,
                                           msg->camera_pose.position.z));

    //initial estimates for pose
    initial_estimates.insert(gtsam::Symbol('x', camera_pose_index), camera_pose);

    //TODO: I need prior on every pose until I get the VO working
    static auto initial_pose_prior = gtsam::noiseModel::Diagonal::Sigmas(
            (gtsam::Vector(6) << gtsam::Vector3::Constant(0.05), gtsam::Vector3::Constant(0.05)).finished());
    factor_graph.addPrior(gtsam::Symbol('x', camera_pose_index), camera_pose, initial_pose_prior);

    //check if its the first time
    if(!initialized){

        //Add prior on the first pose
        //TODO: not sure why its gotta be static. remove and check


        initialized = true;

    }
    else{
        isam2.update(factor_graph, initial_estimates);
        //pasting the info here coz its important: // Each call to iSAM2 update(*) performs one iteration of the iterative
        //            // nonlinear solver. If accuracy is desired at the expense of time,
        //            // update(*) can be called additional times to perform multiple optimizer
        //            // iterations every step.
        isam2.update();
        gtsam::Values current_estimate = isam2.calculateEstimate();
        //TODO(OFN): add some debug info here if you want
        factor_graph.resize(0);
        initial_estimates.clear();

    }
    std::cout<<"Total fruits: "<<fruit_map.fruit_map_.size()<<std::endl;

}


int main(int argc, char** argv){
    ros::init(argc, argv, "fruit_counting_backend_gtsam_basic");
    ros::NodeHandle nh;

    //initializing the values of global variables here
    isam2_params.relinearizeThreshold = 0.01;
    isam2_params.relinearizeSkip = 1;

    gtsam::ISAM2 tempisam2(isam2_params);
    isam2 = tempisam2;
    //subscribe to the measurements
    ros::Subscriber sub_camera_pose_circles_centres = nh.subscribe<fruit_couting_base::vecPoints>(circles_centres_topic, 10, cameraPoseCirclesCentresCallback);
    ros::spin();

    return 0;
}