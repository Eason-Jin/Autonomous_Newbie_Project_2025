// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from msgs:msg/Response.idl
// generated code does not contain a copyright notice
#include "msgs/msg/detail/response__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `target`
// Member `vehicle`
#include "msgs/msg/detail/kinematics__functions.h"
// Member `lvtl`
// Member `target_location`
#include "geometry_msgs/msg/detail/point__functions.h"

bool
msgs__msg__Response__init(msgs__msg__Response * msg)
{
  if (!msg) {
    return false;
  }
  // target
  if (!msgs__msg__Kinematics__init(&msg->target)) {
    msgs__msg__Response__fini(msg);
    return false;
  }
  // vehicle
  if (!msgs__msg__Kinematics__init(&msg->vehicle)) {
    msgs__msg__Response__fini(msg);
    return false;
  }
  // lvtl
  if (!geometry_msgs__msg__Point__init(&msg->lvtl)) {
    msgs__msg__Response__fini(msg);
    return false;
  }
  // target_location
  if (!geometry_msgs__msg__Point__init(&msg->target_location)) {
    msgs__msg__Response__fini(msg);
    return false;
  }
  return true;
}

void
msgs__msg__Response__fini(msgs__msg__Response * msg)
{
  if (!msg) {
    return;
  }
  // target
  msgs__msg__Kinematics__fini(&msg->target);
  // vehicle
  msgs__msg__Kinematics__fini(&msg->vehicle);
  // lvtl
  geometry_msgs__msg__Point__fini(&msg->lvtl);
  // target_location
  geometry_msgs__msg__Point__fini(&msg->target_location);
}

bool
msgs__msg__Response__are_equal(const msgs__msg__Response * lhs, const msgs__msg__Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // target
  if (!msgs__msg__Kinematics__are_equal(
      &(lhs->target), &(rhs->target)))
  {
    return false;
  }
  // vehicle
  if (!msgs__msg__Kinematics__are_equal(
      &(lhs->vehicle), &(rhs->vehicle)))
  {
    return false;
  }
  // lvtl
  if (!geometry_msgs__msg__Point__are_equal(
      &(lhs->lvtl), &(rhs->lvtl)))
  {
    return false;
  }
  // target_location
  if (!geometry_msgs__msg__Point__are_equal(
      &(lhs->target_location), &(rhs->target_location)))
  {
    return false;
  }
  return true;
}

bool
msgs__msg__Response__copy(
  const msgs__msg__Response * input,
  msgs__msg__Response * output)
{
  if (!input || !output) {
    return false;
  }
  // target
  if (!msgs__msg__Kinematics__copy(
      &(input->target), &(output->target)))
  {
    return false;
  }
  // vehicle
  if (!msgs__msg__Kinematics__copy(
      &(input->vehicle), &(output->vehicle)))
  {
    return false;
  }
  // lvtl
  if (!geometry_msgs__msg__Point__copy(
      &(input->lvtl), &(output->lvtl)))
  {
    return false;
  }
  // target_location
  if (!geometry_msgs__msg__Point__copy(
      &(input->target_location), &(output->target_location)))
  {
    return false;
  }
  return true;
}

msgs__msg__Response *
msgs__msg__Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  msgs__msg__Response * msg = (msgs__msg__Response *)allocator.allocate(sizeof(msgs__msg__Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(msgs__msg__Response));
  bool success = msgs__msg__Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
msgs__msg__Response__destroy(msgs__msg__Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    msgs__msg__Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
msgs__msg__Response__Sequence__init(msgs__msg__Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  msgs__msg__Response * data = NULL;

  if (size) {
    data = (msgs__msg__Response *)allocator.zero_allocate(size, sizeof(msgs__msg__Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = msgs__msg__Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        msgs__msg__Response__fini(&data[i - 1]);
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
msgs__msg__Response__Sequence__fini(msgs__msg__Response__Sequence * array)
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
      msgs__msg__Response__fini(&array->data[i]);
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

msgs__msg__Response__Sequence *
msgs__msg__Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  msgs__msg__Response__Sequence * array = (msgs__msg__Response__Sequence *)allocator.allocate(sizeof(msgs__msg__Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = msgs__msg__Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
msgs__msg__Response__Sequence__destroy(msgs__msg__Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    msgs__msg__Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
msgs__msg__Response__Sequence__are_equal(const msgs__msg__Response__Sequence * lhs, const msgs__msg__Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!msgs__msg__Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
msgs__msg__Response__Sequence__copy(
  const msgs__msg__Response__Sequence * input,
  msgs__msg__Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(msgs__msg__Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    msgs__msg__Response * data =
      (msgs__msg__Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!msgs__msg__Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          msgs__msg__Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!msgs__msg__Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
