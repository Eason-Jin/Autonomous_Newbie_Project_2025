// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from msgs:msg/Response.idl
// generated code does not contain a copyright notice

#ifndef MSGS__MSG__DETAIL__RESPONSE__TRAITS_HPP_
#define MSGS__MSG__DETAIL__RESPONSE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "msgs/msg/detail/response__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'target'
// Member 'vehicle'
#include "msgs/msg/detail/kinematics__traits.hpp"
// Member 'lvtl'
// Member 'target_location'
#include "geometry_msgs/msg/detail/point__traits.hpp"

namespace msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: target
  {
    out << "target: ";
    to_flow_style_yaml(msg.target, out);
    out << ", ";
  }

  // member: vehicle
  {
    out << "vehicle: ";
    to_flow_style_yaml(msg.vehicle, out);
    out << ", ";
  }

  // member: lvtl
  {
    out << "lvtl: ";
    to_flow_style_yaml(msg.lvtl, out);
    out << ", ";
  }

  // member: target_location
  {
    out << "target_location: ";
    to_flow_style_yaml(msg.target_location, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: target
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "target:\n";
    to_block_style_yaml(msg.target, out, indentation + 2);
  }

  // member: vehicle
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "vehicle:\n";
    to_block_style_yaml(msg.vehicle, out, indentation + 2);
  }

  // member: lvtl
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lvtl:\n";
    to_block_style_yaml(msg.lvtl, out, indentation + 2);
  }

  // member: target_location
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "target_location:\n";
    to_block_style_yaml(msg.target_location, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace msgs

namespace rosidl_generator_traits
{

[[deprecated("use msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const msgs::msg::Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const msgs::msg::Response & msg)
{
  return msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<msgs::msg::Response>()
{
  return "msgs::msg::Response";
}

template<>
inline const char * name<msgs::msg::Response>()
{
  return "msgs/msg/Response";
}

template<>
struct has_fixed_size<msgs::msg::Response>
  : std::integral_constant<bool, has_fixed_size<geometry_msgs::msg::Point>::value && has_fixed_size<msgs::msg::Kinematics>::value> {};

template<>
struct has_bounded_size<msgs::msg::Response>
  : std::integral_constant<bool, has_bounded_size<geometry_msgs::msg::Point>::value && has_bounded_size<msgs::msg::Kinematics>::value> {};

template<>
struct is_message<msgs::msg::Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // MSGS__MSG__DETAIL__RESPONSE__TRAITS_HPP_
