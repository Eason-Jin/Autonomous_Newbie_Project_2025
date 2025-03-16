// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from msgs:msg/LocationStamped.idl
// generated code does not contain a copyright notice

#ifndef MSGS__MSG__DETAIL__LOCATION_STAMPED__BUILDER_HPP_
#define MSGS__MSG__DETAIL__LOCATION_STAMPED__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "msgs/msg/detail/location_stamped__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace msgs
{

namespace msg
{

namespace builder
{

class Init_LocationStamped_location
{
public:
  explicit Init_LocationStamped_location(::msgs::msg::LocationStamped & msg)
  : msg_(msg)
  {}
  ::msgs::msg::LocationStamped location(::msgs::msg::LocationStamped::_location_type arg)
  {
    msg_.location = std::move(arg);
    return std::move(msg_);
  }

private:
  ::msgs::msg::LocationStamped msg_;
};

class Init_LocationStamped_header
{
public:
  Init_LocationStamped_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LocationStamped_location header(::msgs::msg::LocationStamped::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_LocationStamped_location(msg_);
  }

private:
  ::msgs::msg::LocationStamped msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::msgs::msg::LocationStamped>()
{
  return msgs::msg::builder::Init_LocationStamped_header();
}

}  // namespace msgs

#endif  // MSGS__MSG__DETAIL__LOCATION_STAMPED__BUILDER_HPP_
