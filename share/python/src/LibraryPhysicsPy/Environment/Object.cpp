////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           LibraryPhysicsPy/Environment/Object.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <LibraryPhysicsPy/Environment/Object/Geometry.cpp>

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
        .def(self_ns::repr(self_ns::self))

        .def("isDefined", &Object::isDefined)
        
        .def("accessName", &Object::accessName, return_value_policy<reference_existing_object>())
        .def("accessInstant", &Object::accessInstant, return_value_policy<reference_existing_object>())
        .def("accessFrame", &Object::accessFrame)
        .def("getPositionIn", &Object::getPositionIn)
        .def("getTransformTo", &Object::getTransformTo)
        .def("getAxesIn", &Object::getAxesIn)
        .def("getGeometryIn", &Object::getGeometryIn)
        .def("setInstant", &Object::setInstant)

    ;

    register_ptr_to_python<Shared<const Object>>() ;

    implicitly_convertible<Shared<Object>, Shared<const Object>>() ;

    LibraryPhysicsPy_Environment_Object_Geometry() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////