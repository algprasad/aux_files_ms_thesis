//
// Created by alg on 7/27/21.
//

#ifndef FRUIT_COUNTING_BACKEND_FRUIT_H
#define FRUIT_COUNTING_BACKEND_FRUIT_H

#include <gtsam/geometry/Point3.h>
#include <gtsam/geometry/Point2.h>

/**
 * Characteristics of a single fruit
 * **/
class Fruit {
public:
    int landmark_id_;
    gtsam::Point3 global_3d_position_;
    //temp pixel coordinates are constantly replaced by new values
    gtsam::Point2 temp_pixel_coordinates_;
    //this is useful when we want to check if the fruit is a new one or has been seen before. This would help us decide if we need to initialize it or not
    bool has_been_seen_before_;
    Fruit(): has_been_seen_before_(false){}
    Fruit(gtsam::Point3 global_3d_position, gtsam::Point2 temp_pixel_coordinates): global_3d_position_(global_3d_position),
                                                                                    temp_pixel_coordinates_(temp_pixel_coordinates),
                                                                                    has_been_seen_before_(false){}

};


#endif //FRUIT_COUNTING_BACKEND_FRUIT_H
