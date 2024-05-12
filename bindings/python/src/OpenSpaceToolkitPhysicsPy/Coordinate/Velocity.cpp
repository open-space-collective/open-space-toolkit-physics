/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Coordinate/Velocity.hpp>

inline void OpenSpaceToolkitPhysicsPy_Coordinate_Velocity(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Integer;
    using ostk::core::type::Shared;

    using ostk::mathematics::object::Vector3d;

    using ostk::physics::coordinate::Velocity;
    using ostk::physics::coordinate::Frame;

    class_<Velocity> velocity(
        aModule,
        "Velocity",
        R"doc(
            Velocity.
        )doc"
    );

    velocity

        .def(
            init<Vector3d, Velocity::Unit, Shared<const Frame>&>(),
            arg("coordinates"),
            arg("unit"),
            arg("frame"),
            R"doc(
                Constructs a velocity.

                Args:
                    coordinates (np.ndarray): Coordinates.
                    unit (Unit): Unit.
                    frame (Frame): Frame of reference.
            )doc"
        )

        .def(
            self == self,
            R"doc(
                Equality operator.

                Args:
                    other (Velocity): Other velocity.

                Returns:
                    bool: True if equal.
            )doc"
        )
        .def(
            self != self,
            R"doc(
                Inequality operator.

                Args:
                    other (Velocity): Other velocity.

                Returns:
                    bool: True if not equal.
            )doc"
        )

        .def("__str__", &(shiftToString<Velocity>))
        .def("__repr__", &(shiftToString<Velocity>))

        .def(
            "is_defined",
            &Velocity::isDefined,
            R"doc(
                Check if the instance is defined.

                Returns:
                    bool: True if the instance is defined.
            )doc"
        )

        .def(
            "access_frame",
            &Velocity::accessFrame,
            R"doc(
                Access the frame of reference.

                Returns:
                    Frame: Frame of reference.
            )doc"
        )

        .def(
            "get_coordinates",
            &Velocity::getCoordinates,
            R"doc(
                Get the coordinates.

                Returns:
                    np.ndarray: Coordinates.
            )doc"
        )
        .def(
            "get_unit",
            &Velocity::getUnit,
            R"doc(
                Get the unit.

                Returns:
                    Unit: Unit.
            )doc"
        )
        .def(
            "in_unit",
            &Velocity::inUnit,
            arg("unit"),
            R"doc(
                Convert to unit.

                Args:
                    unit (Unit): Unit.

                Returns:
                    Velocity: Velocity.
            )doc"
        )
        .def(
            "in_frame",
            &Velocity::inFrame,
            arg("position"),
            arg("frame"),
            arg("instant"),
            R"doc(
                Convert to frame.

                Args:
                    position (Position): Position.
                    frame (Frame): Frame.
                    instant (Instant): Instant.

                Returns:
                    Velocity: Velocity.
            )doc"
        )
        .def(
            "to_string",
            &Velocity::toString,
            arg("precision") = DEFAULT_PRECISION,
            R"doc(
                Convert to string.

                Args:
                    precision (int): Precision.

                Returns:
                    String: String.
            )doc"
        )

        .def_static(
            "undefined",
            &Velocity::Undefined,
            R"doc(
                Get undefined velocity.

                Returns:
                    Velocity: Undefined velocity.
            )doc"
        )
        .def_static(
            "meters_per_second",
            &Velocity::MetersPerSecond,
            arg("coordinates"),
            arg("frame"),
            R"doc(
                Create a velocity in meters per second.

                Args:
                    coordinates (np.ndarray): Coordinates.
                    frame (Frame): Frame of reference.

                Returns:
                    Velocity: Velocity in meters per second.
            )doc"
        )
        .def_static(
            "string_from_unit",
            &Velocity::StringFromUnit,
            arg("unit"),
            R"doc(
                Create a string from unit.

                Args:
                    unit (Unit): Unit.

                Returns:
                    String: String.
            )doc"
        )

        ;

    enum_<Velocity::Unit>(
        velocity,
        "Unit",
        R"doc(
            Velocity unit.
        )doc"
    )

        .value(
            "Undefined",
            Velocity::Unit::Undefined,
            R"doc(
                Undefined.
            )doc"
        )
        .value(
            "MeterPerSecond",
            Velocity::Unit::MeterPerSecond,
            R"doc(
                Meter per second.
            )doc"
        )

        ;
}
