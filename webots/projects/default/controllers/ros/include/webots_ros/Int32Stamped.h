/*
 * Copyright 1996-2022 Cyberbotics Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// Generated by gencpp from file webots_ros/Int32Stamped.msg
// DO NOT EDIT!

#ifndef WEBOTS_ROS_MESSAGE_INT32STAMPED_H
#define WEBOTS_ROS_MESSAGE_INT32STAMPED_H

#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>

namespace webots_ros
{
template <class ContainerAllocator>
struct Int32Stamped_
{
  typedef Int32Stamped_<ContainerAllocator> Type;

  Int32Stamped_()
    : header()
    , data(0)  {
    }
  Int32Stamped_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , data(0)  {
    }

   typedef ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef int32_t  _data_type;
  _data_type data;



  typedef boost::shared_ptr< ::webots_ros::Int32Stamped_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::webots_ros::Int32Stamped_<ContainerAllocator> const> ConstPtr;

}; // struct Int32Stamped_

typedef ::webots_ros::Int32Stamped_<std::allocator<void> > Int32Stamped;

typedef boost::shared_ptr< ::webots_ros::Int32Stamped > Int32StampedPtr;
typedef boost::shared_ptr< ::webots_ros::Int32Stamped const> Int32StampedConstPtr;

// constants requiring out of line definition

template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::webots_ros::Int32Stamped_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::webots_ros::Int32Stamped_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace webots_ros

namespace ros
{
namespace message_traits
{

// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'std_msgs': ['/opt/ros/groovy/share/std_msgs/msg'], 'webots_ros': ['/home/simon/my_Webots_Projects/controllers/ros_controller/catkin_ws/src/webots_ros/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']

template <class ContainerAllocator>
struct IsFixedSize< ::webots_ros::Int32Stamped_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::webots_ros::Int32Stamped_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::webots_ros::Int32Stamped_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::webots_ros::Int32Stamped_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::webots_ros::Int32Stamped_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::webots_ros::Int32Stamped_<ContainerAllocator> const>
  : FalseType
  { };

template<class ContainerAllocator>
struct MD5Sum< ::webots_ros::Int32Stamped_<ContainerAllocator> >
{
  static const char* value()
  {
    return "e7344a45486eefa24d2f337265df37ce";
  }

  static const char* value(const ::webots_ros::Int32Stamped_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x0147e4f36cba5cdaULL;
  static const uint64_t static_value2 = 0x7fa39c089e493413ULL;
};

template<class ContainerAllocator>
struct DataType< ::webots_ros::Int32Stamped_<ContainerAllocator> >
{
  static const char* value()
  {
    return "webots_ros/Int32Stamped";
  }

  static const char* value(const ::webots_ros::Int32Stamped_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::webots_ros::Int32Stamped_<ContainerAllocator> >
{
  static const char* value()
  {
    return "Header header\n\
int32 data\n\\n\
\n\
";
  }

  static const char* value(const ::webots_ros::Int32Stamped_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::webots_ros::Int32Stamped_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.data);

    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct Int32Stamped_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::webots_ros::Int32Stamped_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::webots_ros::Int32Stamped_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "data: ";
    Printer<int32_t>::stream(s, indent + "  ", v.data);

  }
};

} // namespace message_operations
} // namespace ros

#endif // WEBOTS_ROS_MESSAGE_INT32STAMPED_H
