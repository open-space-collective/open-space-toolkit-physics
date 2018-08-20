////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           LibraryPhysicsPy/Coordinate/Transform.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Coordinate/Transform.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryPhysicsPy_Coordinate_Transform       ( )
{

    using namespace boost::python ;

    using library::core::types::Real ;

    using library::math::obj::Vector3d ;
    using library::math::geom::trf::rot::Quaternion ;
    using library::math::geom::trf::rot::RotationVector ;

    using library::physics::time::Instant ;

    using library::physics::coord::Transform ;

    scope in_Transform = class_<Transform>("Transform", init<Instant, Vector3d, Vector3d, Quaternion, Vector3d, Transform::Type>())

        .def(self == self)
        .def(self != self)

        .def(self * self)

        .def(self *= self)

        .def(self_ns::str(self_ns::self))

        .def("isDefined", &Transform::isDefined)

        .def("accessInstant", &Transform::accessInstant, return_value_policy<reference_existing_object>())
        .def("accessTranslation", &Transform::accessTranslation, return_value_policy<reference_existing_object>())
        .def("accessVelocity", &Transform::accessVelocity, return_value_policy<reference_existing_object>())
        .def("accessOrientation", &Transform::accessOrientation, return_value_policy<reference_existing_object>())
        .def("accessAngularVelocity", &Transform::accessAngularVelocity, return_value_policy<reference_existing_object>())
        .def("getInstant", &Transform::getInstant)
        .def("getTranslation", &Transform::getTranslation)
        .def("getVelocity", &Transform::getVelocity)
        .def("getOrientation", &Transform::getOrientation)
        .def("getAngularVelocity", &Transform::getAngularVelocity)
        .def("getInverse", &Transform::getInverse)
        .def("applyToPosition", &Transform::applyToPosition)
        .def("applyToVelocity", &Transform::applyToVelocity)
        .def("applyToVector", &Transform::applyToVector)
        
        .def("Undefined", &Transform::Undefined).staticmethod("Undefined")
        .def("Identity", &Transform::Identity).staticmethod("Identity")
        // .def("Translation", &Transform::Translation).staticmethod("Translation")
        .def("Active", &Transform::Active).staticmethod("Active")
        .def("Passive", &Transform::Passive).staticmethod("Passive")

    ;

    enum_<Transform::Type>("Type")

        .value("Undefined", Transform::Type::Undefined)
        .value("Active", Transform::Type::Active)
        .value("Passive", Transform::Type::Passive)

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////