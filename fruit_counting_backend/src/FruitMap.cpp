//
// Created by alg on 7/27/21.
//

#include "FruitMap.h"

void FruitMap::dataAssociation(fruit_couting_base::vecPointsConstPtr camera_pose_circles_centres,
                               std::vector<Fruit> &local_fruits) {

    //for each fruit in the camera_pose_circles_centres, check against each fruit in the map to see if it was seen before and add values to the vector accordingly
    for(int msg_index = 0; msg_index < camera_pose_circles_centres->centres2d.size(); msg_index++){
        //make the local_fruit object to add to the vector
        //TODO: (Potential source of error): check the pixel values if they are x,y or y,x
        Fruit local_fruit(gtsam::Point3(
                                        camera_pose_circles_centres->centres3d[msg_index].x,
                                        camera_pose_circles_centres->centres3d[msg_index].y,
                                        camera_pose_circles_centres->centres3d[msg_index].z
                          ),
                          gtsam::Point2(
                                  camera_pose_circles_centres->centres2d[msg_index].x,
                                  camera_pose_circles_centres->centres2d[msg_index].y
                                  )
                                  );

        //check against the map
        for(auto fruit_in_map: this->fruit_map_){
            //check Euclidian distance

            double euclidean_distance = euclideanDistance(fruit_in_map.global_3d_position_, local_fruit.global_3d_position_);
            if(euclidean_distance < data_association_distance_threshold){
                //that means it has been detected before
                local_fruit.has_been_seen_before_ = true;
                local_fruit.landmark_id_ = fruit_in_map.landmark_id_;
                //no need to check for any other fruits in the map
                break;
           }

        }
        //since the has_been_seen_before_ has been set to false by default, that boolean will only be changed to true if we found its association
        if(!local_fruit.has_been_seen_before_){
           //assign a landmark ID to the fruit
           local_fruit.landmark_id_ = this->fruit_map_.size();
           //add to map
           fruit_map_.push_back(local_fruit);
        }
        local_fruits.push_back(local_fruit);

    }

}

double FruitMap::euclideanDistance(const gtsam::Point3& matrix, const gtsam::Point3& point) {
    double distance = sqrt(
                            (matrix.x() - point.x())*(matrix.x() - point.x()) +
                               (matrix.y() - point.y())*(matrix.y() - point.y()) +
                               (matrix.z() - point.z())*(matrix.z() - point.z())
                           );


    return distance;
}
