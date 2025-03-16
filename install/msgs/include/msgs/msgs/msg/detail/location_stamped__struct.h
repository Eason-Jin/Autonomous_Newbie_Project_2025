// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from msgs:msg/LocationStamped.idl
// generated code does not contain a copyright notice

#ifndef MSGS__MSG__DETAIL__LOCATION_STAMPED__STRUCT_H_
#define MSGS__MSG__DETAIL__LOCATION_STAMPED__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'location'
#include "geometry_msgs/msg/detail/point__struct.h"

/// Struct defined in msg/LocationStamped in the package msgs.
typedef struct msgs__msg__LocationStamped
{
  std_msgs__msg__Header header;
  geometry_msgs__msg__Point location;
} msgs__msg__LocationStamped;

// Struct for a sequence of msgs__msg__LocationStamped.
typedef struct msgs__msg__LocationStamped__Sequence
{
  msgs__msg__LocationStamped * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} msgs__msg__LocationStamped__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MSGS__MSG__DETAIL__LOCATION_STAMPED__STRUCT_H_
