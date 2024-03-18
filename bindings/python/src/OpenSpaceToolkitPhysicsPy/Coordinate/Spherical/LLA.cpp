/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Coordinate/Spherical/LLA.hpp>

inline void OpenSpaceToolkitPhysicsPy_Coordinate_Spherical_LLA(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::physics::unit::Length;
    using ostk::physics::unit::Angle;
    using ostk::physics::coordinate::spherical::LLA;

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

        .def(
            "calculate_distance_to",
            &LLA::calculateDistanceTo,
            arg("lla"),
            arg("ellipsoid_equatorial_radius"),
            arg("ellipsoid_flattening")
        )
        .def(
            "calculate_azimuth_to",
            &LLA::calculateAzimuthTo,
            arg("lla"),
            arg("ellipsoid_equatorial_radius"),
            arg("ellipsoid_flattening")
        )
        .def(
            "calculate_intermediate_to",
            &LLA::calculateIntermediateTo,
            arg("lla"),
            arg("ratio"),
            arg("ellipsoid_equatorial_radius"),
            arg("ellipsoid_flattening")
        )
        .def(
            "calculate_forward",
            &LLA::calculateForward,
            arg("azimuth"),
            arg("distance"),
            arg("ellipsoid_equatorial_radius"),
            arg("ellipsoid_flattening")
        )
        .def(
            "calculate_linspace_to",
            &LLA::calculateLinspaceTo,
            arg("lla"),
            arg("number_of_points"),
            arg("ellipsoid_equatorial_radius"),
            arg("ellipsoid_flattening")
        )

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
        .def_static(
            "distance_between",
            &LLA::DistanceBetween,
            arg("lla_1"),
            arg("lla_2"),
            arg("ellipsoid_equatorial_radius"),
            arg("ellipsoid_flattening")
        )
        .def_static(
            "azimuth_between",
            &LLA::AzimuthBetween,
            arg("lla_1"),
            arg("lla_2"),
            arg("ellipsoid_equatorial_radius"),
            arg("ellipsoid_flattening")
        )
        .def_static(
            "intermediate_between",
            &LLA::IntermediateBetween,
            arg("lla_1"),
            arg("lla_2"),
            arg("ratio"),
            arg("ellipsoid_equatorial_radius"),
            arg("ellipsoid_flattening")
        )
        .def_static(
            "forward",
            &LLA::Forward,
            arg("lla"),
            arg("azimuth"),
            arg("distance"),
            arg("ellipsoid_equatorial_radius"),
            arg("ellipsoid_flattening")
        )
        .def_static(
            "linspace",
            &LLA::Linspace,
            arg("lla_1"),
            arg("lla_2"),
            arg("number_of_points"),
            arg("ellipsoid_equatorial_radius"),
            arg("ellipsoid_flattening")
        )

        ;
}
