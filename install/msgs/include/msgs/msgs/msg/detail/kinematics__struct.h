// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from msgs:msg/Kinematics.idl
// generated code does not contain a copyright notice

#ifndef MSGS__MSG__DETAIL__KINEMATICS__STRUCT_H_
#define MSGS__MSG__DETAIL__KINEMATICS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'position'
#include "geometry_msgs/msg/detail/point__struct.h"
// Member 'velocity'
// Member 'acceleration'
#include "geometry_msgs/msg/detail/vector3__struct.h"

/// Struct defined in msg/Kinematics in the package msgs.
/**
  * relative to starting position of the vehicle (m)
 */
typedef struct msgs__msg__Kinematics
{
  geometry_msgs__msg__Point position;
  /// (m/s)
  geometry_msgs__msg__Vector3 velocity;
  /// (m/s/s)
  geometry_msgs__msg__Vector3 acceleration;
  /// (positive is anti-clockwise, negative is clockwise)
  double angle;
  /// (positive is anti-clockwise, negative is clockwise)
  double anglular_velocity;
} msgs__msg__Kinematics;

// Struct for a sequence of msgs__msg__Kinematics.
typedef struct msgs__msg__Kinematics__Sequence
{
  msgs__msg__Kinematics * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} msgs__msg__Kinematics__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MSGS__MSG__DETAIL__KINEMATICS__STRUCT_H_
