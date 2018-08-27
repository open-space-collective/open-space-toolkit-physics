////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           LibraryPhysicsPy/Environment/Object/Geometry.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Environment/Object/Geometry.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryPhysicsPy_Environment_Object_Geometry ( )
{

    using namespace boost::python ;

    using library::core::types::Unique ;
    using library::core::types::Shared ;

    using library::physics::coord::Frame ;
    using library::physics::env::object::Geometry ;

    scope in_Geometry = class_<Geometry>("Geometry", init<const Geometry::Object&, const Shared<const Frame>&>())

        .def(init<const Unique<Geometry::Object>&, const Shared<const Frame>&>())

        .def(self == self)
        .def(self != self)

        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))

        .def("isDefined", &Geometry::isDefined)
        .def("intersects", &Geometry::intersects)
        // .def("contains", &Geometry::contains)
        
        .def("accessFrame", &Geometry::accessFrame)
        .def("in", &Geometry::in)
        
        .def("Undefined", &Geometry::Undefined).staticmethod("Undefined")

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////