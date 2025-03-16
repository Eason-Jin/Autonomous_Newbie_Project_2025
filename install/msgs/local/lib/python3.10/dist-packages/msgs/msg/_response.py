# generated from rosidl_generator_py/resource/_idl.py.em
# with input from msgs:msg/Response.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_Response(type):
    """Metaclass of message 'Response'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('msgs')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'msgs.msg.Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__response
            cls._TYPE_SUPPORT = module.type_support_msg__msg__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__response

            from geometry_msgs.msg import Point
            if Point.__class__._TYPE_SUPPORT is None:
                Point.__class__.__import_type_support__()

            from msgs.msg import Kinematics
            if Kinematics.__class__._TYPE_SUPPORT is None:
                Kinematics.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class Response(metaclass=Metaclass_Response):
    """Message class 'Response'."""

    __slots__ = [
        '_target',
        '_vehicle',
        '_lvtl',
        '_target_location',
    ]

    _fields_and_field_types = {
        'target': 'msgs/Kinematics',
        'vehicle': 'msgs/Kinematics',
        'lvtl': 'geometry_msgs/Point',
        'target_location': 'geometry_msgs/Point',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['msgs', 'msg'], 'Kinematics'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['msgs', 'msg'], 'Kinematics'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Point'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Point'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from msgs.msg import Kinematics
        self.target = kwargs.get('target', Kinematics())
        from msgs.msg import Kinematics
        self.vehicle = kwargs.get('vehicle', Kinematics())
        from geometry_msgs.msg import Point
        self.lvtl = kwargs.get('lvtl', Point())
        from geometry_msgs.msg import Point
        self.target_location = kwargs.get('target_location', Point())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.target != other.target:
            return False
        if self.vehicle != other.vehicle:
            return False
        if self.lvtl != other.lvtl:
            return False
        if self.target_location != other.target_location:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def target(self):
        """Message field 'target'."""
        return self._target

    @target.setter
    def target(self, value):
        if __debug__:
            from msgs.msg import Kinematics
            assert \
                isinstance(value, Kinematics), \
                "The 'target' field must be a sub message of type 'Kinematics'"
        self._target = value

    @builtins.property
    def vehicle(self):
        """Message field 'vehicle'."""
        return self._vehicle

    @vehicle.setter
    def vehicle(self, value):
        if __debug__:
            from msgs.msg import Kinematics
            assert \
                isinstance(value, Kinematics), \
                "The 'vehicle' field must be a sub message of type 'Kinematics'"
        self._vehicle = value

    @builtins.property
    def lvtl(self):
        """Message field 'lvtl'."""
        return self._lvtl

    @lvtl.setter
    def lvtl(self, value):
        if __debug__:
            from geometry_msgs.msg import Point
            assert \
                isinstance(value, Point), \
                "The 'lvtl' field must be a sub message of type 'Point'"
        self._lvtl = value

    @builtins.property
    def target_location(self):
        """Message field 'target_location'."""
        return self._target_location

    @target_location.setter
    def target_location(self, value):
        if __debug__:
            from geometry_msgs.msg import Point
            assert \
                isinstance(value, Point), \
                "The 'target_location' field must be a sub message of type 'Point'"
        self._target_location = value
