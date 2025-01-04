/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Coordinate/Spherical/LLA.hpp>

inline void OpenSpaceToolkitPhysicsPy_Coordinate_Spherical_LLA(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Real;

    using ostk::physics::coordinate::spherical::LLA;
    using ostk::physics::unit::Angle;
    using ostk::physics::unit::Length;

    class_<LLA>(
        aModule,
        "LLA",
        R"doc(
            Geodetic Latitude - Longitude - Altitude (LLA).

            :reference: https://en.wikipedia.org/wiki/Latitude
            :reference: https://en.wikipedia.org/wiki/Longitude
        )doc"
    )

        .def(
            init<const Angle&, const Angle&, const Length&>(),
            arg("latitude"),
            arg("longitude"),
            arg("altitude"),
            R"doc(
                Construct an LLA instance.

                Args:
                    latitude (Angle): Latitude.
                    longitude (Angle): Longitude.
                    altitude (Length): Altitude.
            )doc"
        )

        .def(
            self == self,
            R"doc(
                Equality operator.

                Args:
                    other (LLA): Other LLA.

                Returns:
                    bool: True if equal.
            )doc"
        )
        .def(
            self != self,
            R"doc(
                Inequality operator.

                Args:
                    other (LLA): Other LLA.

                Returns:
                    bool: True if not equal.
            )doc"
        )

        .def("__str__", &(shiftToString<LLA>))
        .def("__repr__", &(shiftToString<LLA>))

        .def(
            "is_defined",
            &LLA::isDefined,
            R"doc(
                Check if defined.

                Returns:
                    bool: True if defined.
            )doc"
        )

        .def(
            "get_latitude",
            &LLA::getLatitude,
            R"doc(
                Get latitude.

                Returns:
                    Angle: Latitude.
            )doc"
        )
        .def(
            "get_longitude",
            &LLA::getLongitude,
            R"doc(
                Get longitude.

                Returns:
                    Angle: Longitude.
            )doc"
        )
        .def(
            "get_altitude",
            &LLA::getAltitude,
            R"doc(
                Get altitude.

                Returns:
                    Length: Altitude.
            )doc"
        )

        .def(
            "on_surface",
            &LLA::onSurface,
            R"doc(
                Get LLA on surface (Altitude is 0.0).

                Returns:
                    LLA: LLA on surface.
            )doc"
        )

        .def(
            "calculate_distance_to",
            &LLA::calculateDistanceTo,
            R"doc(
                Calculate the distance between this LLA coordinate and another LLA coordinate.
                If ellipsoid parameters are not provided, values from the global Environment central celestial are used. 

                Args:
                    lla (LLA): Another LLA coordinate.
                    ellipsoid_equatorial_radius (Length): Equatorial radius of the ellipsoid.
                    ellipsoid_flattening (float): Flattening of the ellipsoid.

                Returns:
                    Length: Distance.
            )doc",
            arg("lla"),
            arg_v("ellipsoid_equatorial_radius", Length::Undefined(), "Length.Undefined()"),
            arg_v("ellipsoid_flattening", Real::Undefined(), "Real.Undefined()")
        )
        .def(
            "calculate_azimuth_to",
            &LLA::calculateAzimuthTo,
            R"doc(
                Calculate the azimuth angles between this LLA coordinate and another LLA coordinate.
                If ellipsoid parameters are not provided, values from the global Environment central celestial are used. 

                Args:
                    lla (LLA): Another LLA coordinate.
                    ellipsoid_equatorial_radius (Length): Equatorial radius of the ellipsoid.
                    ellipsoid_flattening (float): Flattening of the ellipsoid.

                Returns:
                    Angle: Azimuth.

                )doc",
            arg("lla"),
            arg_v("ellipsoid_equatorial_radius", Length::Undefined(), "Length.Undefined()"),
            arg_v("ellipsoid_flattening", Real::Undefined(), "Real.Undefined()")
        )
        .def(
            "calculate_intermediate_to",
            &LLA::calculateIntermediateTo,
            R"doc(
                Calculate a point between this LLA coordinate and another LLA coordinate.
                If ellipsoid parameters are not provided, values from the global Environment central celestial are used. 

                Args:
                    lla (LLA): Another LLA coordinate.
                    ratio (Real): Ratio.
                    ellipsoid_equatorial_radius (Length): Equatorial radius of the ellipsoid.
                    ellipsoid_flattening (float): Flattening of the ellipsoid.

                Returns:
                    LLA: A point between the two LLA coordinates.
            )doc",
            arg("lla"),
            arg("ratio"),
            arg_v("ellipsoid_equatorial_radius", Length::Undefined(), "Length.Undefined()"),
            arg_v("ellipsoid_flattening", Real::Undefined(), "Real.Undefined()")
        )
        .def(
            "calculate_forward",
            &LLA::calculateForward,
            R"doc(
                Propagate this LLA coordinate in provided direction and distance.
                If ellipsoid parameters are not provided, values from the global Environment central celestial are used. 

                Args:
                    azimuth (Angle): Azimuth.
                    distance (Length): Distance.
                    ellipsoid_equatorial_radius (Length): Equatorial radius of the ellipsoid.
                    ellipsoid_flattening (float): Flattening of the ellipsoid.

                Returns:
                    LLA: Propagated LLA coordinate.
            )doc",
            arg("azimuth"),
            arg("distance"),
            arg_v("ellipsoid_equatorial_radius", Length::Undefined(), "Length.Undefined()"),
            arg_v("ellipsoid_flattening", Real::Undefined(), "Real.Undefined()")
        )
        .def(
            "calculate_linspace_to",
            &LLA::calculateLinspaceTo,
            R"doc(
                Generate LLAs between this LLA coordinate and another LLA coordinate at a given interval.
                If ellipsoid parameters are not provided, values from the global Environment central celestial are used. 

                Args:
                    lla (LLA): Another LLA coordinate.
                    number_of_points (Size): Number of points.
                    ellipsoid_equatorial_radius (Length): Equatorial radius of the ellipsoid.
                    ellipsoid_flattening (float): Flattening of the ellipsoid.

                Returns:
                    list[LLA]: List of LLA coordinates.
            )doc",
            arg("lla"),
            arg("number_of_points"),
            arg_v("ellipsoid_equatorial_radius", Length::Undefined(), "Length.Undefined()"),
            arg_v("ellipsoid_flattening", Real::Undefined(), "Real.Undefined()")
        )

        .def(
            "to_vector",
            &LLA::toVector,
            R"doc(
                Convert to vector.

                Returns:
                    np.ndarray: Vector.
            )doc"
        )
        .def(
            "to_cartesian",
            &LLA::toCartesian,
            R"doc(
                Convert to Cartesian.
                If ellipsoid parameters are not provided, values from the global Environment central celestial are used. 

                Args:
                    ellipsoid_equatorial_radius (Length): Equatorial radius of the ellipsoid.
                    ellipsoid_flattening (float): Flattening of the ellipsoid.

                Returns:
                    np.ndarray: Cartesian.
            )doc",
            arg_v("ellipsoid_equatorial_radius", Length::Undefined(), "Length.Undefined()"),
            arg_v("ellipsoid_flattening", Real::Undefined(), "Real.Undefined()")
        )
        .def(
            "to_string",
            &LLA::toString,
            R"doc(
                Convert to string.

                Returns:
                    String: String representation.
            )doc"
        )

        .def_static(
            "undefined",
            &LLA::Undefined,
            R"doc(
                Undefined LLA.

                Returns:
                    LLA: Undefined LLA.
            )doc"
        )
        .def_static(
            "vector",
            &LLA::Vector,
            arg("vector"),
            R"doc(
                Construct LLA from vector.

                Args:
                    vector (np.ndarray): Vector.

                Returns:
                    LLA: LLA.
            )doc"
        )
        .def_static(
            "cartesian",
            &LLA::Cartesian,
            R"doc(
                Construct LLA from Cartesian.
                If ellipsoid parameters are not provided, values from the global Environment central celestial are used. 

                Args:
                    cartesian_coordinates (np.ndarray): Cartesian coordinates.
                    ellipsoid_equatorial_radius (Length): Equatorial radius of the ellipsoid.
                    ellipsoid_flattening (float): Flattening of the ellipsoid.

                Returns:
                    LLA: LLA.
            )doc",
            arg("cartesian_coordinates"),
            arg_v("ellipsoid_equatorial_radius", Length::Undefined(), "Length.Undefined()"),
            arg_v("ellipsoid_flattening", Real::Undefined(), "Real.Undefined()")
        )
        .def_static(
            "distance_between",
            &LLA::DistanceBetween,
            R"doc(
                Calculate the distance between two LLA coordinates.
                If ellipsoid parameters are not provided, values from the global Environment central celestial are used. 

                Args:
                    lla_1 (LLA): First LLA coordinate.
                    lla_2 (LLA): Second LLA coordinate.
                    ellipsoid_equatorial_radius (Length): Equatorial radius of the ellipsoid.
                    ellipsoid_flattening (float): Flattening of the ellipsoid.

                Returns:
                    Length: Distance.
            )doc",
            arg("lla_1"),
            arg("lla_2"),
            arg_v("ellipsoid_equatorial_radius", Length::Undefined(), "Length.Undefined()"),
            arg_v("ellipsoid_flattening", Real::Undefined(), "Real.Undefined()")
        )
        .def_static(
            "azimuth_between",
            &LLA::AzimuthBetween,
            R"doc(
                Calculate the azimuth angles between two LLA coordinates.
                If ellipsoid parameters are not provided, values from the global Environment central celestial are used. 

                Args:
                    lla_1 (LLA): First LLA coordinate.
                    lla_2 (LLA): Second LLA coordinate.
                    ellipsoid_equatorial_radius (Length): Equatorial radius of the ellipsoid.
                    ellipsoid_flattening (float): Flattening of the ellipsoid.

                Returns:
                    Angle: Azimuth.
            )doc",
            arg("lla_1"),
            arg("lla_2"),
            arg_v("ellipsoid_equatorial_radius", Length::Undefined(), "Length.Undefined()"),
            arg_v("ellipsoid_flattening", Real::Undefined(), "Real.Undefined()")
        )
        .def_static(
            "intermediate_between",
            &LLA::IntermediateBetween,
            R"doc(
                Calculate a point between two LLA coordinates.
                If ellipsoid parameters are not provided, values from the global Environment central celestial are used. 

                Args:
                    lla_1 (LLA): First LLA coordinate.
                    lla_2 (LLA): Second LLA coordinate.
                    ratio (Real): Ratio.
                    ellipsoid_equatorial_radius (Length): Equatorial radius of the ellipsoid.
                    ellipsoid_flattening (float): Flattening of the ellipsoid.

                Returns:
                    LLA: A point between the two LLA coordinates.
            )doc",
            arg("lla_1"),
            arg("lla_2"),
            arg("ratio"),
            arg_v("ellipsoid_equatorial_radius", Length::Undefined(), "Length.Undefined()"),
            arg_v("ellipsoid_flattening", Real::Undefined(), "Real.Undefined()")
        )
        .def_static(
            "forward",
            &LLA::Forward,
            R"doc(
                Propagate an LLA coordinate in provided direction and distance.
                If ellipsoid parameters are not provided, values from the global Environment central celestial are used. 

                Args:
                    lla (LLA): LLA coordinate.
                    azimuth (Angle): Azimuth.
                    distance (Length): Distance.
                    ellipsoid_equatorial_radius (Length): Equatorial radius of the ellipsoid.
                    ellipsoid_flattening (float): Flattening of the ellipsoid.

                Returns:
                    LLA: Propagated LLA coordinate.
            )doc",
            arg("lla"),
            arg("azimuth"),
            arg("distance"),
            arg_v("ellipsoid_equatorial_radius", Length::Undefined(), "Length.Undefined()"),
            arg_v("ellipsoid_flattening", Real::Undefined(), "Real.Undefined()")
        )
        .def_static(
            "linspace",
            &LLA::Linspace,
            R"doc(
                Generate LLAs between two LLA coordinates at a given interval.
                If ellipsoid parameters are not provided, values from the global Environment central celestial are used. 

                Args:
                    lla_1 (LLA): First LLA coordinate.
                    lla_2 (LLA): Second LLA coordinate.
                    number_of_points (Size): Number of points.
                    ellipsoid_equatorial_radius (Length): Equatorial radius of the ellipsoid.
                    ellipsoid_flattening (float): Flattening of the ellipsoid.

                Returns:
                    list[LLA]: List of LLA coordinates.
            )doc",
            arg("lla_1"),
            arg("lla_2"),
            arg("number_of_points"),
            arg_v("ellipsoid_equatorial_radius", Length::Undefined(), "Length.Undefined()"),
            arg_v("ellipsoid_flattening", Real::Undefined(), "Real.Undefined()")
        )
        .def_static(
            "from_position",
            &LLA::FromPosition,
            R"doc(
                Construct LLA from position.

                Args:
                    position (Position): Position.
                    celestial (Celestial): Celestial object. Defaults to None, in which case, values from the global Environment central celestial are used. 

                Returns:
                    LLA: LLA.
            )doc",
            arg("position"),
            arg_v("celestial", nullptr, "None")
        )

        ;
}
