#!/usr/bin/env python3

import numpy as np
# import quaternion
import rospy
import math
from gazebo_msgs.msg import ModelState, ModelStates
from gazebo_msgs.srv import SetModelState
from scipy.spatial.transform import Rotation as R

# Auxiliary main function -- the actual main function
def main():
    rospy.init_node('depth_camera_circular_trajectory_node')

    print('Inside the main function\n')
    #rospy.Subscriber('/gazebo/model_states', ModelStates, modelStateCallback)
    iter = 1
    multiplier = 0.002
    radius = 3
    state_msg = ModelState()
    rate = rospy.Rate(50)

    while not rospy.is_shutdown():
        deg = iter*multiplier
        x = radius*math.cos(deg)
        y = radius*math.sin(deg)
        z = 3
        orientation_matrix = R.from_matrix([[np.cos(deg), -np.sin(deg), 0],
                                        [np.sin(deg), np.cos(deg), 0],
                                        [0, 0, 1]])
        rotate_by_180_y = R.from_matrix([[np.cos(np.pi), 0, np.sin(np.pi)],
                                         [0, 1, 0],
                                         [-np.sin(np.pi), 0, np.cos(np.pi)]])
        rotate_by_180_x = R.from_matrix([[1, 0, 0],
                                          [0, np.cos(np.pi), -np.sin(np.pi)],
                                         [0, np.sin(np.pi), np.cos(np.pi)]])

        orientation_matrix = orientation_matrix*rotate_by_180_y*rotate_by_180_x
        orientation_quaternion = orientation_matrix.as_quat()
        state_msg.pose.orientation.x = orientation_quaternion[0]
        state_msg.pose.orientation.y = orientation_quaternion[1]
        state_msg.pose.orientation.z = orientation_quaternion[2]
        state_msg.pose.orientation.w = orientation_quaternion[3]


        #TODO: Check the model name
        state_msg.model_name = 'depth_camera'
        state_msg.pose.position.x = x
        state_msg.pose.position.y = y
        state_msg.pose.position.z = z
        pub = rospy.Publisher('/gazebo/set_model_state', ModelState, queue_size=10)
        pub.publish(state_msg)
        iter+=1;
        rate.sleep()

    

# main function
if __name__  == '__main__':
    try:
        main()
    except rospy.ROSInterruptException:
        pass


#
