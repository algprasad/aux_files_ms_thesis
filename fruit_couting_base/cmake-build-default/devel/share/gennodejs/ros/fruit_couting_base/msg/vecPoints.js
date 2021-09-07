// Auto-generated. Do not edit!

// (in-package fruit_couting_base.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let geometry_msgs = _finder('geometry_msgs');
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class vecPoints {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.camera_pose = null;
      this.centres3d = null;
      this.centres2d = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('camera_pose')) {
        this.camera_pose = initObj.camera_pose
      }
      else {
        this.camera_pose = new geometry_msgs.msg.Pose();
      }
      if (initObj.hasOwnProperty('centres3d')) {
        this.centres3d = initObj.centres3d
      }
      else {
        this.centres3d = [];
      }
      if (initObj.hasOwnProperty('centres2d')) {
        this.centres2d = initObj.centres2d
      }
      else {
        this.centres2d = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type vecPoints
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [camera_pose]
    bufferOffset = geometry_msgs.msg.Pose.serialize(obj.camera_pose, buffer, bufferOffset);
    // Serialize message field [centres3d]
    // Serialize the length for message field [centres3d]
    bufferOffset = _serializer.uint32(obj.centres3d.length, buffer, bufferOffset);
    obj.centres3d.forEach((val) => {
      bufferOffset = geometry_msgs.msg.Point.serialize(val, buffer, bufferOffset);
    });
    // Serialize message field [centres2d]
    // Serialize the length for message field [centres2d]
    bufferOffset = _serializer.uint32(obj.centres2d.length, buffer, bufferOffset);
    obj.centres2d.forEach((val) => {
      bufferOffset = geometry_msgs.msg.Point.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type vecPoints
    let len;
    let data = new vecPoints(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [camera_pose]
    data.camera_pose = geometry_msgs.msg.Pose.deserialize(buffer, bufferOffset);
    // Deserialize message field [centres3d]
    // Deserialize array length for message field [centres3d]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.centres3d = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.centres3d[i] = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset)
    }
    // Deserialize message field [centres2d]
    // Deserialize array length for message field [centres2d]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.centres2d = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.centres2d[i] = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    length += 24 * object.centres3d.length;
    length += 24 * object.centres2d.length;
    return length + 64;
  }

  static datatype() {
    // Returns string type for a message object
    return 'fruit_couting_base/vecPoints';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '53552ab9226ff5fc524d3c626f4ca409';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
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
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new vecPoints(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.camera_pose !== undefined) {
      resolved.camera_pose = geometry_msgs.msg.Pose.Resolve(msg.camera_pose)
    }
    else {
      resolved.camera_pose = new geometry_msgs.msg.Pose()
    }

    if (msg.centres3d !== undefined) {
      resolved.centres3d = new Array(msg.centres3d.length);
      for (let i = 0; i < resolved.centres3d.length; ++i) {
        resolved.centres3d[i] = geometry_msgs.msg.Point.Resolve(msg.centres3d[i]);
      }
    }
    else {
      resolved.centres3d = []
    }

    if (msg.centres2d !== undefined) {
      resolved.centres2d = new Array(msg.centres2d.length);
      for (let i = 0; i < resolved.centres2d.length; ++i) {
        resolved.centres2d[i] = geometry_msgs.msg.Point.Resolve(msg.centres2d[i]);
      }
    }
    else {
      resolved.centres2d = []
    }

    return resolved;
    }
};

module.exports = vecPoints;
