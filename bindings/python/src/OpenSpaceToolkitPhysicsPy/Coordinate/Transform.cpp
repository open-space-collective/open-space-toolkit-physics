////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           bindings/python/src/OpenSpaceToolkitPhysicsPy/Coordinate/Transform.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Physics/Coordinate/Transform.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitPhysicsPy_Coordinate_Transform (         pybind11::module&          aModule                                     )
{

    using namespace pybind11 ;

    using ostk::core::types::Real ;

    using ostk::math::obj::Vector3d ;
    using ostk::math::geom::d3::trf::rot::Quaternion ;
    using ostk::math::geom::d3::trf::rot::RotationVector ;

    using ostk::physics::time::Instant ;

    using ostk::physics::coord::Transform ;

    class_<Transform> transform_class(aModule, "Transform") ;

    transform_class.def(init<Instant, Vector3d, Vector3d, Quaternion, Vector3d, Transform::Type>())

        .def(self == self)
        .def(self != self)

        .def(self * self)

        .def(self *= self)

        .def("__str__", &(shiftToString<Transform>))
        .def("__repr__", &(shiftToString<Transform>))

        .def("is_defined", &Transform::isDefined)
        .def("is_identity", &Transform::isIdentity)

        // .def("access_instant", &Transform::accessInstant, return_value_policy<reference_existing_object>())
        // .def("access_translation", &Transform::accessTranslation, return_value_policy<reference_existing_object>())
        // .def("access_velocity", &Transform::accessVelocity, return_value_policy<reference_existing_object>())
        // .def("access_orientation", &Transform::accessOrientation, return_value_policy<reference_existing_object>())
        // .def("access_angular_velocity", &Transform::accessAngularVelocity, return_value_policy<reference_existing_object>())
        .def("access_instant", &Transform::accessInstant, return_value_policy::reference)
        .def("access_translation", &Transform::accessTranslation, return_value_policy::reference)
        .def("access_velocity", &Transform::accessVelocity, return_value_policy::reference)
        .def("access_orientation", &Transform::accessOrientation, return_value_policy::reference)
        .def("access_angular_velocity", &Transform::accessAngularVelocity, return_value_policy::reference)
        .def("get_instant", &Transform::getInstant)
        .def("get_translation", &Transform::getTranslation)
        .def("get_velocity", &Transform::getVelocity)
        .def("get_orientation", &Transform::getOrientation)
        .def("get_angular_velocity", &Transform::getAngularVelocity)
        .def("get_inverse", &Transform::getInverse)
        .def("apply_to_position", &Transform::applyToPosition)
        .def("apply_to_velocity", &Transform::applyToVelocity)
        .def("apply_to_vector", &Transform::applyToVector)

        .def_static("undefined", &Transform::Undefined)
        .def_static("identity", &Transform::Identity)
        // .def_static("translation", &Transform::Translation)
        .def_static("active", &Transform::Active)
        .def_static("passive", &Transform::Passive)

    ;

    enum_<Transform::Type>(transform_class, "Type")

        .value("Undefined", Transform::Type::Undefined)
        .value("Active", Transform::Type::Active)
        .value("Passive", Transform::Type::Passive)

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
