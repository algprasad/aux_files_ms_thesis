//
// Created by alg on 7/27/21.
//

#ifndef FRUIT_COUNTING_BACKEND_FRUITMAP_H
#define FRUIT_COUNTING_BACKEND_FRUITMAP_H

#include <vector>
#include <gtsam/geometry/Point3.h>
#include <fruit_couting_base/vecPoints.h>
#include "Fruit.h"

class FruitMap {
public:
    //Each fruit object has a landmark id
    std::vector<Fruit> fruit_map_;
    double data_association_distance_threshold;

    FruitMap(){
        //setting the data association threshold at 10 cm
        data_association_distance_threshold = 0.1;
    };

    void dataAssociation(fruit_couting_base::vecPointsConstPtr camera_pose_circles_centres, std::vector<Fruit>& local_fruits);
    int getTotalFruits();


    double euclideanDistance(const gtsam::Point3& matrix, const gtsam::Point3 &point);
};


#endif //FRUIT_COUNTING_BACKEND_FRUITMAP_H
