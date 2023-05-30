/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Coordinate/Spherical/AER.hpp>

inline void OpenSpaceToolkitPhysicsPy_Coordinate_Spherical_AER(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::physics::units::Length;
    using ostk::physics::units::Angle;
    using ostk::physics::coord::Position;
    using ostk::physics::coord::spherical::AER;

    class_<AER>(aModule, "AER")

        .def(init<const Angle&, const Angle&, const Length&>(), arg("azimuth"), arg("elevation"), arg("range"))

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<AER>))
        .def("__repr__", &(shiftToString<AER>))

        .def("is_defined", &AER::isDefined)

        .def("get_azimuth", &AER::getAzimuth)
        .def("get_elevation", &AER::getElevation)
        .def("get_range", &AER::getRange)
        .def("to_vector", &AER::toVector)
        .def("to_string", &AER::toString)

        .def_static("undefined", &AER::Undefined)
        .def_static("vector", &AER::Vector, arg("vector"))
        .def_static(
            "from_position_to_position",
            &AER::FromPositionToPosition,
            arg("from_position"),
            arg("to_position"),
            arg("is_z_negative") = DEFAULT_IS_Z_NEGATIVE
        )

        ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
