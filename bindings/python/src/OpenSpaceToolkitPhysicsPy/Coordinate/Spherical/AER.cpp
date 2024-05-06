/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Coordinate/Spherical/AER.hpp>

inline void OpenSpaceToolkitPhysicsPy_Coordinate_Spherical_AER(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::physics::unit::Length;
    using ostk::physics::unit::Angle;
    using ostk::physics::coordinate::Position;
    using ostk::physics::coordinate::spherical::AER;

    class_<AER>(aModule, "AER",
        R"doc(
            Azimuth - Elevation - Range (AER).
        )doc"
    )

        .def(init<const Angle&, const Angle&, const Length&>(), arg("azimuth"), arg("elevation"), arg("range"),
            R"doc(
            Construct an AER instance.

            Args:
                azimuth (Angle): Azimuth.
                elevation (Angle): Elevation.
                range (Length): Range.
            )doc"
        )

        .def(self == self,
            R"doc(
            Equality operator.

            Args:
                other (AER): Other AER.

            Returns:
                bool: True if equal.
            )doc"
        )
        .def(self != self,
            R"doc(
            Inequality operator.

            Args:
                other (AER): Other AER.

            Returns:
                bool: True if not equal.
            )doc"
        )

        .def("__str__", &(shiftToString<AER>))
        .def("__repr__", &(shiftToString<AER>))

        .def("is_defined", &AER::isDefined,
            R"doc(
            Check if defined.

            Returns:
                bool: True if defined.
            )doc"
        )

        .def("get_azimuth", &AER::getAzimuth,
            R"doc(
            Get azimuth.

            Returns:
                Angle: Azimuth.
            )doc"
        )
        .def("get_elevation", &AER::getElevation,
            R"doc(
            Get elevation.

            Returns:
                Angle: Elevation.
            )doc"
        )
        .def("get_range", &AER::getRange,
            R"doc(
            Get range.

            Returns:
                Length: Range.
            )doc"
        )
        .def("to_vector", &AER::toVector,
            R"doc(
            Convert to vector.

            Returns:
                Vector3d: Vector.
            )doc"
        )
        .def("to_string", &AER::toString,
            R"doc(
            Convert to string.

            Returns:
                String: String representation.
            )doc"
        )

        .def_static("undefined", &AER::Undefined,
            R"doc(
            Undefined AER.

            Returns:
                AER: Undefined AER.
            )doc"
        )
        .def_static("vector", &AER::Vector, arg("vector"),
            R"doc(
            Construct AER from vector.

            Args:
                vector (Vector3d): Vector.

            Returns:
                AER: AER.
            )doc"
        )
        .def_static(
            "from_position_to_position",
            &AER::FromPositionToPosition,
            arg("from_position"),
            arg("to_position"),
            arg("is_z_negative") = DEFAULT_IS_Z_NEGATIVE,
            R"doc(
            Construct AER from position to position.

            Args:
                from_position (Position): From position.
                to_position (Position): To position.
                is_z_negative (bool): True if Z is negative.

            Returns:
                AER: AER.
            )doc"
        )

        ;
}
