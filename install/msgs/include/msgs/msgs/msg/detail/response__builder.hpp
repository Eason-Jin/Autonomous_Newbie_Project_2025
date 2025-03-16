// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from msgs:msg/Response.idl
// generated code does not contain a copyright notice

#ifndef MSGS__MSG__DETAIL__RESPONSE__BUILDER_HPP_
#define MSGS__MSG__DETAIL__RESPONSE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "msgs/msg/detail/response__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace msgs
{

namespace msg
{

namespace builder
{

class Init_Response_target_location
{
public:
  explicit Init_Response_target_location(::msgs::msg::Response & msg)
  : msg_(msg)
  {}
  ::msgs::msg::Response target_location(::msgs::msg::Response::_target_location_type arg)
  {
    msg_.target_location = std::move(arg);
    return std::move(msg_);
  }

private:
  ::msgs::msg::Response msg_;
};

class Init_Response_lvtl
{
public:
  explicit Init_Response_lvtl(::msgs::msg::Response & msg)
  : msg_(msg)
  {}
  Init_Response_target_location lvtl(::msgs::msg::Response::_lvtl_type arg)
  {
    msg_.lvtl = std::move(arg);
    return Init_Response_target_location(msg_);
  }

private:
  ::msgs::msg::Response msg_;
};

class Init_Response_vehicle
{
public:
  explicit Init_Response_vehicle(::msgs::msg::Response & msg)
  : msg_(msg)
  {}
  Init_Response_lvtl vehicle(::msgs::msg::Response::_vehicle_type arg)
  {
    msg_.vehicle = std::move(arg);
    return Init_Response_lvtl(msg_);
  }

private:
  ::msgs::msg::Response msg_;
};

class Init_Response_target
{
public:
  Init_Response_target()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Response_vehicle target(::msgs::msg::Response::_target_type arg)
  {
    msg_.target = std::move(arg);
    return Init_Response_vehicle(msg_);
  }

private:
  ::msgs::msg::Response msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::msgs::msg::Response>()
{
  return msgs::msg::builder::Init_Response_target();
}

}  // namespace msgs

#endif  // MSGS__MSG__DETAIL__RESPONSE__BUILDER_HPP_
