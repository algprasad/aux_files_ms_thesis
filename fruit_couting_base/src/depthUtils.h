//
// Created by alg on 7/21/21.
//

#ifndef FRUIT_COUTING_BASE_DEPTHUTILS_H
#define FRUIT_COUTING_BASE_DEPTHUTILS_H
#include <sensor_msgs/PointCloud2.h>
#include <geometry_msgs/Pose.h>

void pixelTo3DPoint(const sensor_msgs::PointCloud2 pCloud, double u, double v, geometry_msgs::Pose& p)
{
// get width and height of 2D point cloud data
    int width = pCloud.width;
    int height = pCloud.height;

// Convert from u (column / width), v (row/height) to position in array
// where X,Y,Z data starts
    int arrayPosition = v*pCloud.row_step + u*pCloud.point_step;

// compute position in array where x,y,z data start
    int arrayPosX = arrayPosition + pCloud.fields[0].offset; // X has an offset of 0
    int arrayPosY = arrayPosition + pCloud.fields[1].offset; // Y has an offset of 4
    int arrayPosZ = arrayPosition + pCloud.fields[2].offset; // Z has an offset of 8

    float X = 0.0;
    float Y = 0.0;
    float Z = 0.0;

    memcpy(&X, &pCloud.data[arrayPosX], sizeof(float));
    memcpy(&Y, &pCloud.data[arrayPosY], sizeof(float));
    memcpy(&Z, &pCloud.data[arrayPosZ], sizeof(float));

    p.position.x = X;
    p.position.y = Y;
    p.position.z = Z;

}
void depthImagePixel2Point(const sensor_msgs::Image depth_image, double u, double v, geometry_msgs::Pose& point){
    //uint16_t z_raw = depth_image.data.at<u, v>

}

#endif //FRUIT_COUTING_BASE_DEPTHUTILS_H
