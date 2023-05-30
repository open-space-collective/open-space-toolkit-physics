/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Coordinate/Spherical/LLA.hpp>

inline void OpenSpaceToolkitPhysicsPy_Coordinate_Spherical_LLA(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::physics::units::Length;
    using ostk::physics::units::Angle;
    using ostk::physics::coord::spherical::LLA;

    class_<LLA>(aModule, "LLA")

        .def(init<const Angle&, const Angle&, const Length&>(), arg("latitude"), arg("longitude"), arg("altitude"))

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<LLA>))
        .def("__repr__", &(shiftToString<LLA>))

        .def("is_defined", &LLA::isDefined)

        .def("get_latitude", &LLA::getLatitude)
        .def("get_longitude", &LLA::getLongitude)
        .def("get_altitude", &LLA::getAltitude)
        .def("to_vector", &LLA::toVector)
        .def("to_cartesian", &LLA::toCartesian, arg("ellipsoid_equatorial_radius"), arg("ellipsoid_flattening"))
        .def("to_string", &LLA::toString)

        .def_static("undefined", &LLA::Undefined)
        .def_static("vector", &LLA::Vector, arg("vector"))
        .def_static(
            "cartesian",
            &LLA::Cartesian,
            arg("cartesian_coordinates"),
            arg("ellipsoid_equatorial_radius"),
            arg("ellipsoid_flattening")
        )

        ;
}
