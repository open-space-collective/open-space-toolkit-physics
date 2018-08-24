////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           LibraryPhysicsPy/Environment/Object.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Environment/Object.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryPhysicsPy_Environment_Object         ( )
{

    using namespace boost::python ;

    using library::core::types::Shared ;
    using library::core::types::String ;

    using library::physics::time::Instant ;
    using library::physics::env::Object ;

    scope in_Object = class_<Object, boost::noncopyable>("Object", no_init)

        .def(self_ns::str(self_ns::self))

        .def("isDefined", &Object::isDefined)
        
        .def("accessName", &Object::accessName, return_value_policy<reference_existing_object>())
        .def("accessInstant", &Object::accessInstant, return_value_policy<reference_existing_object>())
        // .def("accessFrame", &Object::accessFrame, return_value_policy<reference_existing_object>())
        .def("accessGeometry", &Object::accessGeometry, return_value_policy<reference_existing_object>())
        .def("getPositionIn", &Object::getPositionIn)
        .def("getTransformTo", &Object::getTransformTo)
        .def("getAxesIn", &Object::getAxesIn)
        .def("setInstant", &Object::setInstant)

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////