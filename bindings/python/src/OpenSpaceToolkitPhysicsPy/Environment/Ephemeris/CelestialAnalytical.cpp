/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Environment/Ephemeris/CelestialAnalytical.hpp>

inline void OpenSpaceToolkitPhysicsPy_Environment_Ephemeris_CelestialAnalytical(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Shared;

    using ostk::physics::environment::Ephemeris;
    using ostk::physics::environment::ephemeris::CelestialAnalytical;
    using ostk::physics::environment::object::Celestial;

    class_<CelestialAnalytical, Shared<CelestialAnalytical>, Ephemeris>(
        aModule,
        "CelestialAnalytical",
        R"doc(
            Low-precision analytical celestial ephemeris.

            Positions are computed from the analytical series of Montenbruck & Gill,
            approximating the body position with respect to the mean equator and equinox
            of J2000, which is treated as GCRF.

            Only the Sun and the Moon are currently supported.

            Accuracy with respect to high-precision (JPL DE) ephemerides, measured over 2020-2026:

            - Sun: < 0.1 deg in direction, < 0.01% in distance
            - Moon: < 0.1 deg in direction, < 0.15% in distance

            This is orders of magnitude faster than a SPICE-based ephemeris,
            and well-suited for applications such as third-body point-mass gravity
            where only an approximate body position is needed.

            Args:
                type (Celestial.Type): The celestial body type for this ephemeris.

            Example:
                >>> from ostk.physics.environment.ephemeris import CelestialAnalytical
                >>> from ostk.physics.environment.object import Celestial
                >>> sun_ephemeris = CelestialAnalytical(Celestial.Type.Sun)

            See Also:
                O. Montenbruck, E. Gill, *Satellite Orbits: Models, Methods and Applications*, Section 3.3.2.
        )doc"
    )

        .def(
            init<const Celestial::Type&>(),
            arg("type"),
            R"doc(
                Constructor.

                Only Celestial.Type.Sun and Celestial.Type.Moon are currently supported.

                Args:
                    type (Celestial.Type): The celestial body type for this ephemeris.
            )doc"
        )

        .def(
            "get_type",
            &CelestialAnalytical::getType,
            R"doc(
                Get the celestial body type of this ephemeris.

                Returns:
                    Celestial.Type: The celestial body type.
            )doc"
        )

        ;
}
