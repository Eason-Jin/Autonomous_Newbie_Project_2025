// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from msgs:msg/Response.idl
// generated code does not contain a copyright notice

#ifndef MSGS__MSG__DETAIL__RESPONSE__STRUCT_HPP_
#define MSGS__MSG__DETAIL__RESPONSE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'target'
// Member 'vehicle'
#include "msgs/msg/detail/kinematics__struct.hpp"
// Member 'lvtl'
// Member 'target_location'
#include "geometry_msgs/msg/detail/point__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__msgs__msg__Response __attribute__((deprecated))
#else
# define DEPRECATED__msgs__msg__Response __declspec(deprecated)
#endif

namespace msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Response_
{
  using Type = Response_<ContainerAllocator>;

  explicit Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : target(_init),
    vehicle(_init),
    lvtl(_init),
    target_location(_init)
  {
    (void)_init;
  }

  explicit Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : target(_alloc, _init),
    vehicle(_alloc, _init),
    lvtl(_alloc, _init),
    target_location(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _target_type =
    msgs::msg::Kinematics_<ContainerAllocator>;
  _target_type target;
  using _vehicle_type =
    msgs::msg::Kinematics_<ContainerAllocator>;
  _vehicle_type vehicle;
  using _lvtl_type =
    geometry_msgs::msg::Point_<ContainerAllocator>;
  _lvtl_type lvtl;
  using _target_location_type =
    geometry_msgs::msg::Point_<ContainerAllocator>;
  _target_location_type target_location;

  // setters for named parameter idiom
  Type & set__target(
    const msgs::msg::Kinematics_<ContainerAllocator> & _arg)
  {
    this->target = _arg;
    return *this;
  }
  Type & set__vehicle(
    const msgs::msg::Kinematics_<ContainerAllocator> & _arg)
  {
    this->vehicle = _arg;
    return *this;
  }
  Type & set__lvtl(
    const geometry_msgs::msg::Point_<ContainerAllocator> & _arg)
  {
    this->lvtl = _arg;
    return *this;
  }
  Type & set__target_location(
    const geometry_msgs::msg::Point_<ContainerAllocator> & _arg)
  {
    this->target_location = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    msgs::msg::Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const msgs::msg::Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<msgs::msg::Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<msgs::msg::Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      msgs::msg::Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<msgs::msg::Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      msgs::msg::Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<msgs::msg::Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<msgs::msg::Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<msgs::msg::Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__msgs__msg__Response
    std::shared_ptr<msgs::msg::Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__msgs__msg__Response
    std::shared_ptr<msgs::msg::Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Response_ & other) const
  {
    if (this->target != other.target) {
      return false;
    }
    if (this->vehicle != other.vehicle) {
      return false;
    }
    if (this->lvtl != other.lvtl) {
      return false;
    }
    if (this->target_location != other.target_location) {
      return false;
    }
    return true;
  }
  bool operator!=(const Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Response_

// alias to use template instance with default allocator
using Response =
  msgs::msg::Response_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace msgs

#endif  // MSGS__MSG__DETAIL__RESPONSE__STRUCT_HPP_
