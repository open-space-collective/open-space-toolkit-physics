////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           LibraryPhysicsPy/Coordinate/Axes.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Coordinate/Axes.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryPhysicsPy_Coordinate_Axes            ( )
{

    using namespace boost::python ;

    using library::core::types::Shared ;

    using library::math::obj::Vector3d ;

    using library::physics::coord::Axes ;
    using library::physics::coord::Frame ;

    scope in_Axes = class_<Axes>("Axes", init<const Vector3d&, const Vector3d&, const Vector3d&, const Shared<const Frame>&>())

        .def(self == self)
        .def(self != self)

        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))

        .def("isDefined", &Axes::isDefined)

        .def("x", &Axes::x, return_value_policy<reference_existing_object>())
        .def("y", &Axes::y, return_value_policy<reference_existing_object>())
        .def("z", &Axes::z, return_value_policy<reference_existing_object>())
        
        .def("Undefined", &Axes::Undefined).staticmethod("Undefined")

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////