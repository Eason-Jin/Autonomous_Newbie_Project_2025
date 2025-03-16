// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from msgs:msg/Response.idl
// generated code does not contain a copyright notice

#ifndef MSGS__MSG__DETAIL__RESPONSE__STRUCT_H_
#define MSGS__MSG__DETAIL__RESPONSE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'target'
// Member 'vehicle'
#include "msgs/msg/detail/kinematics__struct.h"
// Member 'lvtl'
// Member 'target_location'
#include "geometry_msgs/msg/detail/point__struct.h"

/// Struct defined in msg/Response in the package msgs.
typedef struct msgs__msg__Response
{
  msgs__msg__Kinematics target;
  msgs__msg__Kinematics vehicle;
  /// last_valid_target_location
  geometry_msgs__msg__Point lvtl;
  geometry_msgs__msg__Point target_location;
} msgs__msg__Response;

// Struct for a sequence of msgs__msg__Response.
typedef struct msgs__msg__Response__Sequence
{
  msgs__msg__Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} msgs__msg__Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MSGS__MSG__DETAIL__RESPONSE__STRUCT_H_
