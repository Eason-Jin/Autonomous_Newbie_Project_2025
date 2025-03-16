// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from msgs:msg/Response.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "msgs/msg/detail/response__rosidl_typesupport_introspection_c.h"
#include "msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "msgs/msg/detail/response__functions.h"
#include "msgs/msg/detail/response__struct.h"


// Include directives for member types
// Member `target`
// Member `vehicle`
#include "msgs/msg/kinematics.h"
// Member `target`
// Member `vehicle`
#include "msgs/msg/detail/kinematics__rosidl_typesupport_introspection_c.h"
// Member `lvtl`
// Member `target_location`
#include "geometry_msgs/msg/point.h"
// Member `lvtl`
// Member `target_location`
#include "geometry_msgs/msg/detail/point__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void msgs__msg__Response__rosidl_typesupport_introspection_c__Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  msgs__msg__Response__init(message_memory);
}

void msgs__msg__Response__rosidl_typesupport_introspection_c__Response_fini_function(void * message_memory)
{
  msgs__msg__Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember msgs__msg__Response__rosidl_typesupport_introspection_c__Response_message_member_array[4] = {
  {
    "target",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(msgs__msg__Response, target),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "vehicle",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(msgs__msg__Response, vehicle),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "lvtl",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(msgs__msg__Response, lvtl),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "target_location",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(msgs__msg__Response, target_location),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers msgs__msg__Response__rosidl_typesupport_introspection_c__Response_message_members = {
  "msgs__msg",  // message namespace
  "Response",  // message name
  4,  // number of fields
  sizeof(msgs__msg__Response),
  msgs__msg__Response__rosidl_typesupport_introspection_c__Response_message_member_array,  // message members
  msgs__msg__Response__rosidl_typesupport_introspection_c__Response_init_function,  // function to initialize message memory (memory has to be allocated)
  msgs__msg__Response__rosidl_typesupport_introspection_c__Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t msgs__msg__Response__rosidl_typesupport_introspection_c__Response_message_type_support_handle = {
  0,
  &msgs__msg__Response__rosidl_typesupport_introspection_c__Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, msgs, msg, Response)() {
  msgs__msg__Response__rosidl_typesupport_introspection_c__Response_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, msgs, msg, Kinematics)();
  msgs__msg__Response__rosidl_typesupport_introspection_c__Response_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, msgs, msg, Kinematics)();
  msgs__msg__Response__rosidl_typesupport_introspection_c__Response_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Point)();
  msgs__msg__Response__rosidl_typesupport_introspection_c__Response_message_member_array[3].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Point)();
  if (!msgs__msg__Response__rosidl_typesupport_introspection_c__Response_message_type_support_handle.typesupport_identifier) {
    msgs__msg__Response__rosidl_typesupport_introspection_c__Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &msgs__msg__Response__rosidl_typesupport_introspection_c__Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
