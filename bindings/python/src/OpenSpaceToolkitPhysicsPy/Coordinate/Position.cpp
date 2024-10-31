/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Coordinate/Position.hpp>

inline void OpenSpaceToolkitPhysicsPy_Coordinate_Position(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Integer;
    using ostk::core::type::Shared;

    using ostk::mathematics::object::Vector3d;

    using ostk::physics::coordinate::Frame;
    using ostk::physics::coordinate::Position;

    class_<Position>(
        aModule,
        "Position",
        R"doc(
            Position.
        )doc"
    )

        .def(
            init<Vector3d, Position::Unit, Shared<const Frame>&>(),
            arg("coordinates"),
            arg("unit"),
            arg("frame"),
            R"doc(
                Constructs a position.

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
                    other (Position): Other position.

                Returns:
                    bool: True if equal.
            )doc"
        )
        .def(
            self != self,
            R"doc(
                Inequality operator.

                Args:
                    other (Position): Other position.

                Returns:
                    bool: True if not equal.
            )doc"
        )

        .def("__str__", &(shiftToString<Position>))
        .def("__repr__", &(shiftToString<Position>))

        .def(
            "is_defined",
            &Position::isDefined,
            R"doc(
                Check if the Position is defined.

                Returns:
                    bool: True if the Position is defined.
            )doc"
        )
        .def(
            "is_near",
            &Position::isNear,
            arg("position"),
            arg("tolerance"),
            R"doc(
                Check if the Position is near another Position.

                Args:
                    position (Position): Position to compare with.
                    tolerance (Length): Tolerance.

                Returns:
                    bool: True if the Position is near another Position.
            )doc"
        )

        .def(
            "access_frame",
            &Position::accessFrame,
            R"doc(
                Access the frame of reference.

                Returns:
                    Frame: Frame of reference.
            )doc"
        )
        .def(
            "get_coordinates",
            &Position::getCoordinates,
            R"doc(
                Get the coordinates.

                Returns:
                    np.ndarray: Coordinates.
            )doc"
        )
        .def(
            "get_unit",
            &Position::getUnit,
            R"doc(
                Get the unit.

                Returns:
                    Unit: Unit.
            )doc"
        )
        .def(
            "in_unit",
            &Position::inUnit,
            R"doc(
                Get the position in the unit.

                Returns:
                    Position: Position in the unit.
            )doc"
        )
        .def(
            "in_meters",
            &Position::inMeters,
            R"doc(
                Get the position in meters.

                Returns:
                    Position: Position in meters.
            )doc"
        )
        .def(
            "in_frame",
            &Position::inFrame,
            arg("frame"),
            arg("instant"),
            R"doc(
                Get the position in another frame of reference.

                Args:
                    frame (Frame): Frame of reference.
                    instant (Instant): Instant.

                Returns:
                    Position: Position in another frame of reference.
            )doc"
        )
        .def(
            "to_string",
            &Position::toString,
            arg_v("precision", DEFAULT_PRECISION, "Integer.Undefined()"),
            R"doc(
                Create a string representation.

                Args:
                    precision (Integer): Precision.

                Returns:
                    String: String representation.
            )doc"
        )

        .def_static(
            "undefined",
            &Position::Undefined,
            R"doc(
                Get undefined position.

                Returns:
                    Position: Undefined position.
            )doc"
        )
        .def_static(
            "meters",
            &Position::Meters,
            arg("coordinates"),
            arg("frame"),
            R"doc(
                Create a position in meters.

                Args:
                    coordinates (np.ndarray): Coordinates.
                    frame (Frame): Frame of reference.

                Returns:
                    Position: Position in meters.
            )doc"
        )

        ;
}
