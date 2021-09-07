;; Auto-generated. Do not edit!


(when (boundp 'fruit_couting_base::vecPoints)
  (if (not (find-package "FRUIT_COUTING_BASE"))
    (make-package "FRUIT_COUTING_BASE"))
  (shadow 'vecPoints (find-package "FRUIT_COUTING_BASE")))
(unless (find-package "FRUIT_COUTING_BASE::VECPOINTS")
  (make-package "FRUIT_COUTING_BASE::VECPOINTS"))

(in-package "ROS")
;;//! \htmlinclude vecPoints.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass fruit_couting_base::vecPoints
  :super ros::object
  :slots (_header _camera_pose _centres3d _centres2d ))

(defmethod fruit_couting_base::vecPoints
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:camera_pose __camera_pose) (instance geometry_msgs::Pose :init))
    ((:centres3d __centres3d) ())
    ((:centres2d __centres2d) ())
    )
   (send-super :init)
   (setq _header __header)
   (setq _camera_pose __camera_pose)
   (setq _centres3d __centres3d)
   (setq _centres2d __centres2d)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:camera_pose
   (&rest __camera_pose)
   (if (keywordp (car __camera_pose))
       (send* _camera_pose __camera_pose)
     (progn
       (if __camera_pose (setq _camera_pose (car __camera_pose)))
       _camera_pose)))
  (:centres3d
   (&rest __centres3d)
   (if (keywordp (car __centres3d))
       (send* _centres3d __centres3d)
     (progn
       (if __centres3d (setq _centres3d (car __centres3d)))
       _centres3d)))
  (:centres2d
   (&rest __centres2d)
   (if (keywordp (car __centres2d))
       (send* _centres2d __centres2d)
     (progn
       (if __centres2d (setq _centres2d (car __centres2d)))
       _centres2d)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; geometry_msgs/Pose _camera_pose
    (send _camera_pose :serialization-length)
    ;; geometry_msgs/Point[] _centres3d
    (apply #'+ (send-all _centres3d :serialization-length)) 4
    ;; geometry_msgs/Point[] _centres2d
    (apply #'+ (send-all _centres2d :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; geometry_msgs/Pose _camera_pose
       (send _camera_pose :serialize s)
     ;; geometry_msgs/Point[] _centres3d
     (write-long (length _centres3d) s)
     (dolist (elem _centres3d)
       (send elem :serialize s)
       )
     ;; geometry_msgs/Point[] _centres2d
     (write-long (length _centres2d) s)
     (dolist (elem _centres2d)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; geometry_msgs/Pose _camera_pose
     (send _camera_pose :deserialize buf ptr-) (incf ptr- (send _camera_pose :serialization-length))
   ;; geometry_msgs/Point[] _centres3d
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _centres3d (let (r) (dotimes (i n) (push (instance geometry_msgs::Point :init) r)) r))
     (dolist (elem- _centres3d)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;; geometry_msgs/Point[] _centres2d
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _centres2d (let (r) (dotimes (i n) (push (instance geometry_msgs::Point :init) r)) r))
     (dolist (elem- _centres2d)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get fruit_couting_base::vecPoints :md5sum-) "53552ab9226ff5fc524d3c626f4ca409")
(setf (get fruit_couting_base::vecPoints :datatype-) "fruit_couting_base/vecPoints")
(setf (get fruit_couting_base::vecPoints :definition-)
      "Header header
geometry_msgs/Pose camera_pose
geometry_msgs/Point[] centres3d
geometry_msgs/Point[] centres2d

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id

================================================================================
MSG: geometry_msgs/Pose
# A representation of pose in free space, composed of position and orientation. 
Point position
Quaternion orientation

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

================================================================================
MSG: geometry_msgs/Quaternion
# This represents an orientation in free space in quaternion form.

float64 x
float64 y
float64 z
float64 w

")



(provide :fruit_couting_base/vecPoints "53552ab9226ff5fc524d3c626f4ca409")


