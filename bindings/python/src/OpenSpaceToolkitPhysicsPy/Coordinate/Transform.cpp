/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Coordinate/Transform.hpp>

inline void OpenSpaceToolkitPhysicsPy_Coordinate_Transform(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Real;

    using ostk::mathematics::object::Vector3d;
    using ostk::mathematics::geometry::d3::transformation::rotation::Quaternion;
    using ostk::mathematics::geometry::d3::transformation::rotation::RotationVector;

    using ostk::physics::time::Instant;

    using ostk::physics::coordinate::Transform;

    class_<Transform> transform_class(
        aModule,
        "Transform",
        R"doc(
            Transform.

            :reference: https://en.wikipedia.org/wiki/Active_and_passive_transformation
            :reference: https://core.ac.uk/download/pdf/77055186.pdf
        )doc"
    );

    transform_class

        .def(
            init<Instant, Vector3d, Vector3d, Quaternion, Vector3d, Transform::Type>(),
            arg("instant"),
            arg("translation"),
            arg("velocity"),
            arg("orientation"),
            arg("angular_velocity"),
            arg("type"),
            R"doc(
                Constructs a transform.

                Args:
                    instant (Instant): Instant.
                    translation (np.ndarray): Translation.
                    velocity (np.ndarray): Velocity.
                    orientation (Quaternion): Orientation.
                    angular_velocity (np.ndarray): Angular velocity.
                    type (Type): Type.
            )doc"
        )

        .def(
            self == self,
            R"doc(
                Equality operator.

                Args:
                    other (Transform): Other transform.

                Returns:
                    bool: True if equal.
            )doc"
        )
        .def(
            self != self,
            R"doc(
                Inequality operator.

                Args:
                    other (Transform): Other transform.

                Returns:
                    bool: True if not equal.
            )doc"
        )

        .def(
            self * self,
            R"doc(
                Multiplication operator.

                Args:
                    other (Transform): Other transform.

                Returns:
                    Transform: Composition.
            )doc"
        )

        .def(
            self *= self,
            R"doc(
                Multiplication assignment operator.

                Args:
                    other (Transform): Other transform.

                Returns:
                    Transform: Composition.
            )doc"
        )

        .def("__str__", &(shiftToString<Transform>))
        .def("__repr__", &(shiftToString<Transform>))

        .def(
            "is_defined",
            &Transform::isDefined,
            R"doc(
                Check if the transform is defined.

                Returns:
                    bool: True if the transform is defined.
            )doc"
        )
        .def(
            "is_identity",
            &Transform::isIdentity,
            R"doc(
                Check if the transform is the identity.

                Returns:
                    bool: True if the transform is the identity.
            )doc"
        )

        .def(
            "access_instant",
            &Transform::accessInstant,
            return_value_policy::reference,
            R"doc(
                Access the instant.

                Returns:
                    Instant: Instant.
            )doc"
        )
        .def(
            "access_translation",
            &Transform::accessTranslation,
            return_value_policy::reference,
            R"doc(
                Access the translation.

                Returns:
                    np.ndarray: Translation.
            )doc"
        )
        .def(
            "access_velocity",
            &Transform::accessVelocity,
            return_value_policy::reference,
            R"doc(
                Access the velocity.

                Returns:
                    np.ndarray: Velocity.
            )doc"
        )
        .def(
            "access_orientation",
            &Transform::accessOrientation,
            return_value_policy::reference,
            R"doc(
                Access the orientation.

                Returns:
                    Quaternion: Orientation.
            )doc"
        )
        .def(
            "access_angular_velocity",
            &Transform::accessAngularVelocity,
            return_value_policy::reference,
            R"doc(
                Access the angular velocity.

                Returns:
                    np.ndarray: Angular velocity.
            )doc"
        )

        .def(
            "get_instant",
            &Transform::getInstant,
            R"doc(
                Get the instant.

                Returns:
                    Instant: Instant.
            )doc"
        )
        .def(
            "get_translation",
            &Transform::getTranslation,
            R"doc(
                Get the translation.

                Returns:
                    np.ndarray: Translation.
            )doc"
        )
        .def(
            "get_velocity",
            &Transform::getVelocity,
            R"doc(
                Get the velocity.

                Returns:
                    np.ndarray: Velocity.
            )doc"
        )
        .def(
            "get_orientation",
            &Transform::getOrientation,
            R"doc(
                Get the orientation.

                Returns:
                    Quaternion: Orientation.
            )doc"
        )
        .def(
            "get_angular_velocity",
            &Transform::getAngularVelocity,
            R"doc(
                Get the angular velocity.

                Returns:
                    np.ndarray: Angular velocity.
            )doc"
        )
        .def(
            "get_inverse",
            &Transform::getInverse,
            R"doc(
                Get the inverse.

                Returns:
                    Transform: Inverse.
            )doc"
        )
        .def(
            "apply_to_position",
            &Transform::applyToPosition,
            arg("position"),
            R"doc(
                Apply the transform to a position.

                Args:
                    position (Position): Position.

                Returns:
                    np.ndarray: Transformed position.
            )doc"
        )
        .def(
            "apply_to_velocity",
            &Transform::applyToVelocity,
            arg("position"),
            arg("velocity"),
            R"doc(
                Apply the transform to a velocity.

                Args:
                    position (Position): Position.
                    velocity (Velocity): Velocity.

                Returns:
                    np.ndarray: Transformed velocity.
            )doc"
        )
        .def(
            "apply_to_vector",
            &Transform::applyToVector,
            arg("vector"),
            R"doc(
                Apply the transform to a vector.

                Args:
                    vector (np.ndarray): Vector.

                Returns:
                    np.ndarray: Transformed vector.
            )doc"
        )

        .def_static(
            "undefined",
            &Transform::Undefined,
            R"doc(
                Get undefined transform.

                Returns:
                    Transform: Undefined transform.
            )doc"
        )
        .def_static(
            "identity",
            &Transform::Identity,
            R"doc(
                Get identity transform.

                Returns:
                    Transform: Identity transform.
            )doc"
        )

        .def_static(
            "active",
            &Transform::Active,
            arg("instant"),
            arg("translation"),
            arg("velocity"),
            arg("orientation"),
            arg("angular_velocity"),
            R"doc(
                Create an active transform.

                Args:
                    instant (Instant): Instant.
                    translation (np.ndarray): Translation.
                    velocity (np.ndarray): Velocity.
                    orientation (Quaternion): Orientation.
                    angular_velocity (np.ndarray): Angular velocity.

                Returns:
                    Transform: Active transform.
            )doc"
        )

        .def_static(
            "passive",
            &Transform::Passive,
            arg("instant"),
            arg("translation"),
            arg("velocity"),
            arg("orientation"),
            arg("angular_velocity"),
            R"doc(
                Create a passive transform.

                Args:
                    instant (Instant): Instant.
                    translation (np.ndarray): Translation.
                    velocity (np.ndarray): Velocity.
                    orientation (Quaternion): Orientation.
                    angular_velocity (np.ndarray): Angular velocity.

                Returns:
                    Transform: Passive transform.
            )doc"
        )

        ;

    enum_<Transform::Type>(
        transform_class,
        "Type",
        R"doc(
            Transform type.
        )doc"
    )

        .value(
            "Undefined",
            Transform::Type::Undefined,
            R"doc(
                Undefined type.
            )doc"
        )
        .value(
            "Active",
            Transform::Type::Active,
            R"doc(
                Active type.
            )doc"
        )
        .value(
            "Passive",
            Transform::Type::Passive,
            R"doc(
                Passive type.
            )doc"
        )

        ;
}
