// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from msgs:msg/Kinematics.idl
// generated code does not contain a copyright notice
#include "msgs/msg/detail/kinematics__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `position`
#include "geometry_msgs/msg/detail/point__functions.h"
// Member `velocity`
// Member `acceleration`
#include "geometry_msgs/msg/detail/vector3__functions.h"

bool
msgs__msg__Kinematics__init(msgs__msg__Kinematics * msg)
{
  if (!msg) {
    return false;
  }
  // position
  if (!geometry_msgs__msg__Point__init(&msg->position)) {
    msgs__msg__Kinematics__fini(msg);
    return false;
  }
  // velocity
  if (!geometry_msgs__msg__Vector3__init(&msg->velocity)) {
    msgs__msg__Kinematics__fini(msg);
    return false;
  }
  // acceleration
  if (!geometry_msgs__msg__Vector3__init(&msg->acceleration)) {
    msgs__msg__Kinematics__fini(msg);
    return false;
  }
  // angle
  // anglular_velocity
  return true;
}

void
msgs__msg__Kinematics__fini(msgs__msg__Kinematics * msg)
{
  if (!msg) {
    return;
  }
  // position
  geometry_msgs__msg__Point__fini(&msg->position);
  // velocity
  geometry_msgs__msg__Vector3__fini(&msg->velocity);
  // acceleration
  geometry_msgs__msg__Vector3__fini(&msg->acceleration);
  // angle
  // anglular_velocity
}

bool
msgs__msg__Kinematics__are_equal(const msgs__msg__Kinematics * lhs, const msgs__msg__Kinematics * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // position
  if (!geometry_msgs__msg__Point__are_equal(
      &(lhs->position), &(rhs->position)))
  {
    return false;
  }
  // velocity
  if (!geometry_msgs__msg__Vector3__are_equal(
      &(lhs->velocity), &(rhs->velocity)))
  {
    return false;
  }
  // acceleration
  if (!geometry_msgs__msg__Vector3__are_equal(
      &(lhs->acceleration), &(rhs->acceleration)))
  {
    return false;
  }
  // angle
  if (lhs->angle != rhs->angle) {
    return false;
  }
  // anglular_velocity
  if (lhs->anglular_velocity != rhs->anglular_velocity) {
    return false;
  }
  return true;
}

bool
msgs__msg__Kinematics__copy(
  const msgs__msg__Kinematics * input,
  msgs__msg__Kinematics * output)
{
  if (!input || !output) {
    return false;
  }
  // position
  if (!geometry_msgs__msg__Point__copy(
      &(input->position), &(output->position)))
  {
    return false;
  }
  // velocity
  if (!geometry_msgs__msg__Vector3__copy(
      &(input->velocity), &(output->velocity)))
  {
    return false;
  }
  // acceleration
  if (!geometry_msgs__msg__Vector3__copy(
      &(input->acceleration), &(output->acceleration)))
  {
    return false;
  }
  // angle
  output->angle = input->angle;
  // anglular_velocity
  output->anglular_velocity = input->anglular_velocity;
  return true;
}

msgs__msg__Kinematics *
msgs__msg__Kinematics__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  msgs__msg__Kinematics * msg = (msgs__msg__Kinematics *)allocator.allocate(sizeof(msgs__msg__Kinematics), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(msgs__msg__Kinematics));
  bool success = msgs__msg__Kinematics__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
msgs__msg__Kinematics__destroy(msgs__msg__Kinematics * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    msgs__msg__Kinematics__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
msgs__msg__Kinematics__Sequence__init(msgs__msg__Kinematics__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  msgs__msg__Kinematics * data = NULL;

  if (size) {
    data = (msgs__msg__Kinematics *)allocator.zero_allocate(size, sizeof(msgs__msg__Kinematics), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = msgs__msg__Kinematics__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        msgs__msg__Kinematics__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
msgs__msg__Kinematics__Sequence__fini(msgs__msg__Kinematics__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      msgs__msg__Kinematics__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

msgs__msg__Kinematics__Sequence *
msgs__msg__Kinematics__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  msgs__msg__Kinematics__Sequence * array = (msgs__msg__Kinematics__Sequence *)allocator.allocate(sizeof(msgs__msg__Kinematics__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = msgs__msg__Kinematics__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
msgs__msg__Kinematics__Sequence__destroy(msgs__msg__Kinematics__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    msgs__msg__Kinematics__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
msgs__msg__Kinematics__Sequence__are_equal(const msgs__msg__Kinematics__Sequence * lhs, const msgs__msg__Kinematics__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!msgs__msg__Kinematics__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
msgs__msg__Kinematics__Sequence__copy(
  const msgs__msg__Kinematics__Sequence * input,
  msgs__msg__Kinematics__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(msgs__msg__Kinematics);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    msgs__msg__Kinematics * data =
      (msgs__msg__Kinematics *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!msgs__msg__Kinematics__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          msgs__msg__Kinematics__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!msgs__msg__Kinematics__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
