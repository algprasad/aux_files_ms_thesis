# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "fruit_couting_base: 1 messages, 0 services")

set(MSG_I_FLAGS "-Ifruit_couting_base:/home/alg/fruit_counting/fruit_counting_ws/src/fruit_couting_base/msg;-Istd_msgs:/opt/ros/noetic/share/std_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/noetic/share/geometry_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(fruit_couting_base_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/alg/fruit_counting/fruit_counting_ws/src/fruit_couting_base/msg/vecPoints.msg" NAME_WE)
add_custom_target(_fruit_couting_base_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "fruit_couting_base" "/home/alg/fruit_counting/fruit_counting_ws/src/fruit_couting_base/msg/vecPoints.msg" "std_msgs/Header:geometry_msgs/Quaternion:geometry_msgs/Pose:geometry_msgs/Point"
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(fruit_couting_base
  "/home/alg/fruit_counting/fruit_counting_ws/src/fruit_couting_base/msg/vecPoints.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/fruit_couting_base
)

### Generating Services

### Generating Module File
_generate_module_cpp(fruit_couting_base
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/fruit_couting_base
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(fruit_couting_base_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(fruit_couting_base_generate_messages fruit_couting_base_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/alg/fruit_counting/fruit_counting_ws/src/fruit_couting_base/msg/vecPoints.msg" NAME_WE)
add_dependencies(fruit_couting_base_generate_messages_cpp _fruit_couting_base_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(fruit_couting_base_gencpp)
add_dependencies(fruit_couting_base_gencpp fruit_couting_base_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS fruit_couting_base_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(fruit_couting_base
  "/home/alg/fruit_counting/fruit_counting_ws/src/fruit_couting_base/msg/vecPoints.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/fruit_couting_base
)

### Generating Services

### Generating Module File
_generate_module_eus(fruit_couting_base
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/fruit_couting_base
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(fruit_couting_base_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(fruit_couting_base_generate_messages fruit_couting_base_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/alg/fruit_counting/fruit_counting_ws/src/fruit_couting_base/msg/vecPoints.msg" NAME_WE)
add_dependencies(fruit_couting_base_generate_messages_eus _fruit_couting_base_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(fruit_couting_base_geneus)
add_dependencies(fruit_couting_base_geneus fruit_couting_base_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS fruit_couting_base_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(fruit_couting_base
  "/home/alg/fruit_counting/fruit_counting_ws/src/fruit_couting_base/msg/vecPoints.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/fruit_couting_base
)

### Generating Services

### Generating Module File
_generate_module_lisp(fruit_couting_base
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/fruit_couting_base
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(fruit_couting_base_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(fruit_couting_base_generate_messages fruit_couting_base_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/alg/fruit_counting/fruit_counting_ws/src/fruit_couting_base/msg/vecPoints.msg" NAME_WE)
add_dependencies(fruit_couting_base_generate_messages_lisp _fruit_couting_base_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(fruit_couting_base_genlisp)
add_dependencies(fruit_couting_base_genlisp fruit_couting_base_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS fruit_couting_base_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(fruit_couting_base
  "/home/alg/fruit_counting/fruit_counting_ws/src/fruit_couting_base/msg/vecPoints.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/fruit_couting_base
)

### Generating Services

### Generating Module File
_generate_module_nodejs(fruit_couting_base
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/fruit_couting_base
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(fruit_couting_base_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(fruit_couting_base_generate_messages fruit_couting_base_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/alg/fruit_counting/fruit_counting_ws/src/fruit_couting_base/msg/vecPoints.msg" NAME_WE)
add_dependencies(fruit_couting_base_generate_messages_nodejs _fruit_couting_base_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(fruit_couting_base_gennodejs)
add_dependencies(fruit_couting_base_gennodejs fruit_couting_base_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS fruit_couting_base_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(fruit_couting_base
  "/home/alg/fruit_counting/fruit_counting_ws/src/fruit_couting_base/msg/vecPoints.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/fruit_couting_base
)

### Generating Services

### Generating Module File
_generate_module_py(fruit_couting_base
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/fruit_couting_base
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(fruit_couting_base_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(fruit_couting_base_generate_messages fruit_couting_base_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/alg/fruit_counting/fruit_counting_ws/src/fruit_couting_base/msg/vecPoints.msg" NAME_WE)
add_dependencies(fruit_couting_base_generate_messages_py _fruit_couting_base_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(fruit_couting_base_genpy)
add_dependencies(fruit_couting_base_genpy fruit_couting_base_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS fruit_couting_base_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/fruit_couting_base)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/fruit_couting_base
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(fruit_couting_base_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()
if(TARGET geometry_msgs_generate_messages_cpp)
  add_dependencies(fruit_couting_base_generate_messages_cpp geometry_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/fruit_couting_base)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/fruit_couting_base
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(fruit_couting_base_generate_messages_eus std_msgs_generate_messages_eus)
endif()
if(TARGET geometry_msgs_generate_messages_eus)
  add_dependencies(fruit_couting_base_generate_messages_eus geometry_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/fruit_couting_base)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/fruit_couting_base
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(fruit_couting_base_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()
if(TARGET geometry_msgs_generate_messages_lisp)
  add_dependencies(fruit_couting_base_generate_messages_lisp geometry_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/fruit_couting_base)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/fruit_couting_base
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(fruit_couting_base_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()
if(TARGET geometry_msgs_generate_messages_nodejs)
  add_dependencies(fruit_couting_base_generate_messages_nodejs geometry_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/fruit_couting_base)
  install(CODE "execute_process(COMMAND \"/usr/bin/python3\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/fruit_couting_base\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/fruit_couting_base
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(fruit_couting_base_generate_messages_py std_msgs_generate_messages_py)
endif()
if(TARGET geometry_msgs_generate_messages_py)
  add_dependencies(fruit_couting_base_generate_messages_py geometry_msgs_generate_messages_py)
endif()