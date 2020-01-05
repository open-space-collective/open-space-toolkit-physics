////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           bindings/python/src/OpenSpaceToolkitPhysicsPy/Coordinate/Transform.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Physics/Coordinate/Transform.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitPhysicsPy_Coordinate_Transform       ( )
{

    using namespace boost::python ;

    using ostk::core::types::Real ;

    using ostk::math::obj::Vector3d ;
    using ostk::math::geom::d3::trf::rot::Quaternion ;
    using ostk::math::geom::d3::trf::rot::RotationVector ;

    using ostk::physics::time::Instant ;

    using ostk::physics::coord::Transform ;

    scope in_Transform = class_<Transform>("Transform", init<Instant, Vector3d, Vector3d, Quaternion, Vector3d, Transform::Type>())

        .def(self == self)
        .def(self != self)

        .def(self * self)

        .def(self *= self)

        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))

        .def("is_defined", &Transform::isDefined)
        .def("is_identity", &Transform::isIdentity)

        .def("access_instant", &Transform::accessInstant, return_value_policy<reference_existing_object>())
        .def("access_translation", &Transform::accessTranslation, return_value_policy<reference_existing_object>())
        .def("access_velocity", &Transform::accessVelocity, return_value_policy<reference_existing_object>())
        .def("access_orientation", &Transform::accessOrientation, return_value_policy<reference_existing_object>())
        .def("access_angular_velocity", &Transform::accessAngularVelocity, return_value_policy<reference_existing_object>())
        .def("get_instant", &Transform::getInstant)
        .def("get_translation", &Transform::getTranslation)
        .def("get_velocity", &Transform::getVelocity)
        .def("get_orientation", &Transform::getOrientation)
        .def("get_angular_velocity", &Transform::getAngularVelocity)
        .def("get_inverse", &Transform::getInverse)
        .def("apply_to_position", &Transform::applyToPosition)
        .def("apply_to_velocity", &Transform::applyToVelocity)
        .def("apply_to_vector", &Transform::applyToVector)

        .def("undefined", &Transform::Undefined).staticmethod("undefined")
        .def("identity", &Transform::Identity).staticmethod("identity")
        // .def("translation", &Transform::Translation).staticmethod("translation")
        .def("active", &Transform::Active).staticmethod("active")
        .def("passive", &Transform::Passive).staticmethod("passive")

    ;

    enum_<Transform::Type>("Type")

        .value("Undefined", Transform::Type::Undefined)
        .value("Active", Transform::Type::Active)
        .value("Passive", Transform::Type::Passive)

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
