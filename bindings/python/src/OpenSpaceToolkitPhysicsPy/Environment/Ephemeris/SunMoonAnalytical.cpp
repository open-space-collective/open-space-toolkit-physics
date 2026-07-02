/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Environment/Ephemeris/SunMoonAnalytical.hpp>

inline void OpenSpaceToolkitPhysicsPy_Environment_Ephemeris_SunMoonAnalytical(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Shared;

    using ostk::physics::environment::Ephemeris;
    using ostk::physics::environment::ephemeris::SunMoonAnalytical;

    class_<SunMoonAnalytical, Shared<SunMoonAnalytical>, Ephemeris> sunMoonAnalyticalClass(
        aModule,
        "SunMoonAnalytical",
        R"doc(
            Low-precision analytical Sun/Moon ephemeris.

            Positions are computed from the analytical series of Montenbruck & Gill,
            approximating the body position with respect to the mean equator and equinox
            of J2000, which is treated as GCRF.

            Accuracy with respect to high-precision (JPL DE) ephemerides, measured over 2020-2026:

            - Sun: < 0.1 deg in direction, < 0.01% in distance
            - Moon: < 0.1 deg in direction, < 0.15% in distance

            This is orders of magnitude faster than a SPICE-based ephemeris,
            and well-suited for applications such as third-body point-mass gravity
            where only an approximate body position is needed.

            Args:
                body (SunMoonAnalytical.Body): The celestial body for this ephemeris.

            Example:
                >>> from ostk.physics.environment.ephemeris import SunMoonAnalytical
                >>> sun_ephemeris = SunMoonAnalytical(SunMoonAnalytical.Body.Sun)

            See Also:
                O. Montenbruck, E. Gill, *Satellite Orbits: Models, Methods and Applications*, Section 3.3.2.
        )doc"
    );

    enum_<SunMoonAnalytical::Body>(sunMoonAnalyticalClass, "Body")

        .value("Sun", SunMoonAnalytical::Body::Sun, "Sun")
        .value("Moon", SunMoonAnalytical::Body::Moon, "Moon");

    sunMoonAnalyticalClass

        .def(
            init<const SunMoonAnalytical::Body&>(),
            arg("body"),
            R"doc(
                Constructor.

                Args:
                    body (SunMoonAnalytical.Body): The celestial body for this ephemeris.
            )doc"
        )

        .def(
            "get_body",
            &SunMoonAnalytical::getBody,
            R"doc(
                Get the celestial body of this ephemeris.

                Returns:
                    SunMoonAnalytical.Body: The celestial body.
            )doc"
        )

        .def_static(
            "string_from_body",
            &SunMoonAnalytical::StringFromBody,
            arg("body"),
            R"doc(
                Convert a celestial body to its string representation.

                Args:
                    body (SunMoonAnalytical.Body): The celestial body.

                Returns:
                    str: String representation of the celestial body.
            )doc"
        )

        ;
}
