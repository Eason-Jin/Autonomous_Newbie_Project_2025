// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from msgs:msg/Kinematics.idl
// generated code does not contain a copyright notice

#ifndef MSGS__MSG__DETAIL__KINEMATICS__STRUCT_HPP_
#define MSGS__MSG__DETAIL__KINEMATICS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'position'
#include "geometry_msgs/msg/detail/point__struct.hpp"
// Member 'velocity'
// Member 'acceleration'
#include "geometry_msgs/msg/detail/vector3__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__msgs__msg__Kinematics __attribute__((deprecated))
#else
# define DEPRECATED__msgs__msg__Kinematics __declspec(deprecated)
#endif

namespace msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Kinematics_
{
  using Type = Kinematics_<ContainerAllocator>;

  explicit Kinematics_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : position(_init),
    velocity(_init),
    acceleration(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->angle = 0.0;
      this->anglular_velocity = 0.0;
    }
  }

  explicit Kinematics_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : position(_alloc, _init),
    velocity(_alloc, _init),
    acceleration(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->angle = 0.0;
      this->anglular_velocity = 0.0;
    }
  }

  // field types and members
  using _position_type =
    geometry_msgs::msg::Point_<ContainerAllocator>;
  _position_type position;
  using _velocity_type =
    geometry_msgs::msg::Vector3_<ContainerAllocator>;
  _velocity_type velocity;
  using _acceleration_type =
    geometry_msgs::msg::Vector3_<ContainerAllocator>;
  _acceleration_type acceleration;
  using _angle_type =
    double;
  _angle_type angle;
  using _anglular_velocity_type =
    double;
  _anglular_velocity_type anglular_velocity;

  // setters for named parameter idiom
  Type & set__position(
    const geometry_msgs::msg::Point_<ContainerAllocator> & _arg)
  {
    this->position = _arg;
    return *this;
  }
  Type & set__velocity(
    const geometry_msgs::msg::Vector3_<ContainerAllocator> & _arg)
  {
    this->velocity = _arg;
    return *this;
  }
  Type & set__acceleration(
    const geometry_msgs::msg::Vector3_<ContainerAllocator> & _arg)
  {
    this->acceleration = _arg;
    return *this;
  }
  Type & set__angle(
    const double & _arg)
  {
    this->angle = _arg;
    return *this;
  }
  Type & set__anglular_velocity(
    const double & _arg)
  {
    this->anglular_velocity = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    msgs::msg::Kinematics_<ContainerAllocator> *;
  using ConstRawPtr =
    const msgs::msg::Kinematics_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<msgs::msg::Kinematics_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<msgs::msg::Kinematics_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      msgs::msg::Kinematics_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<msgs::msg::Kinematics_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      msgs::msg::Kinematics_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<msgs::msg::Kinematics_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<msgs::msg::Kinematics_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<msgs::msg::Kinematics_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__msgs__msg__Kinematics
    std::shared_ptr<msgs::msg::Kinematics_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__msgs__msg__Kinematics
    std::shared_ptr<msgs::msg::Kinematics_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Kinematics_ & other) const
  {
    if (this->position != other.position) {
      return false;
    }
    if (this->velocity != other.velocity) {
      return false;
    }
    if (this->acceleration != other.acceleration) {
      return false;
    }
    if (this->angle != other.angle) {
      return false;
    }
    if (this->anglular_velocity != other.anglular_velocity) {
      return false;
    }
    return true;
  }
  bool operator!=(const Kinematics_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Kinematics_

// alias to use template instance with default allocator
using Kinematics =
  msgs::msg::Kinematics_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace msgs

#endif  // MSGS__MSG__DETAIL__KINEMATICS__STRUCT_HPP_
