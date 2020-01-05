////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           bindings/python/src/OpenSpaceToolkitPhysicsPy/Environment/Object.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkitPhysicsPy/Environment/Object/Geometry.cpp>

#include <OpenSpaceToolkit/Physics/Environment/Object.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitPhysicsPy_Environment_Object         ( )
{

    using namespace boost::python ;

    using ostk::core::types::Shared ;
    using ostk::core::types::String ;

    using ostk::physics::time::Instant ;
    using ostk::physics::env::Object ;

    scope in_Object = class_<Object, boost::noncopyable>("Object", no_init)

        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))

        .def("isDefined", &Object::isDefined)

        .def("accessName", &Object::accessName, return_value_policy<reference_existing_object>())
        .def("accessInstant", &Object::accessInstant, return_value_policy<reference_existing_object>())
        .def("accessFrame", &Object::accessFrame)
        .def("getName", &Object::getName)
        .def("getInstant", &Object::getInstant)
        .def("getGeometry", &Object::getGeometry)
        .def("getPositionIn", &Object::getPositionIn)
        .def("getTransformTo", &Object::getTransformTo)
        .def("getAxesIn", &Object::getAxesIn)
        .def("getGeometryIn", &Object::getGeometryIn)
        .def("setInstant", &Object::setInstant)

    ;

    register_ptr_to_python<Shared<const Object>>() ;

    implicitly_convertible<Shared<Object>, Shared<const Object>>() ;

    OpenSpaceToolkitPhysicsPy_Environment_Object_Geometry() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////