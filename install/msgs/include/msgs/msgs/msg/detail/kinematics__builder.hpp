// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from msgs:msg/Kinematics.idl
// generated code does not contain a copyright notice

#ifndef MSGS__MSG__DETAIL__KINEMATICS__BUILDER_HPP_
#define MSGS__MSG__DETAIL__KINEMATICS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "msgs/msg/detail/kinematics__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace msgs
{

namespace msg
{

namespace builder
{

class Init_Kinematics_anglular_velocity
{
public:
  explicit Init_Kinematics_anglular_velocity(::msgs::msg::Kinematics & msg)
  : msg_(msg)
  {}
  ::msgs::msg::Kinematics anglular_velocity(::msgs::msg::Kinematics::_anglular_velocity_type arg)
  {
    msg_.anglular_velocity = std::move(arg);
    return std::move(msg_);
  }

private:
  ::msgs::msg::Kinematics msg_;
};

class Init_Kinematics_angle
{
public:
  explicit Init_Kinematics_angle(::msgs::msg::Kinematics & msg)
  : msg_(msg)
  {}
  Init_Kinematics_anglular_velocity angle(::msgs::msg::Kinematics::_angle_type arg)
  {
    msg_.angle = std::move(arg);
    return Init_Kinematics_anglular_velocity(msg_);
  }

private:
  ::msgs::msg::Kinematics msg_;
};

class Init_Kinematics_acceleration
{
public:
  explicit Init_Kinematics_acceleration(::msgs::msg::Kinematics & msg)
  : msg_(msg)
  {}
  Init_Kinematics_angle acceleration(::msgs::msg::Kinematics::_acceleration_type arg)
  {
    msg_.acceleration = std::move(arg);
    return Init_Kinematics_angle(msg_);
  }

private:
  ::msgs::msg::Kinematics msg_;
};

class Init_Kinematics_velocity
{
public:
  explicit Init_Kinematics_velocity(::msgs::msg::Kinematics & msg)
  : msg_(msg)
  {}
  Init_Kinematics_acceleration velocity(::msgs::msg::Kinematics::_velocity_type arg)
  {
    msg_.velocity = std::move(arg);
    return Init_Kinematics_acceleration(msg_);
  }

private:
  ::msgs::msg::Kinematics msg_;
};

class Init_Kinematics_position
{
public:
  Init_Kinematics_position()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Kinematics_velocity position(::msgs::msg::Kinematics::_position_type arg)
  {
    msg_.position = std::move(arg);
    return Init_Kinematics_velocity(msg_);
  }

private:
  ::msgs::msg::Kinematics msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::msgs::msg::Kinematics>()
{
  return msgs::msg::builder::Init_Kinematics_position();
}

}  // namespace msgs

#endif  // MSGS__MSG__DETAIL__KINEMATICS__BUILDER_HPP_
