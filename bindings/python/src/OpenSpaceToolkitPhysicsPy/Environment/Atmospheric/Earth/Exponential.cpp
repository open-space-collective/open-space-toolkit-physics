/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/Exponential.hpp>

inline void OpenSpaceToolkitPhysicsPy_Environment_Atmospheric_Earth_Exponential(nanobind::module_& aModule)
{
    using namespace nanobind;

    using ostk::core::type::Shared;

    using ostk::physics::coordinate::Position;
    using ostk::physics::coordinate::spherical::LLA;
    using ostk::physics::environment::atmospheric::earth::Exponential;
    using ostk::physics::time::Instant;

    class_<Exponential>(
        aModule,
        "Exponential",
        R"doc(
            Exponential atmospheric model.

        )doc"
    )

        .def(init<>())

        .def(
            "is_defined",
            &Exponential::isDefined,
            R"doc(
                Check if the exponential atmospheric model is defined.

                Returns:
                    bool: True if the exponential atmospheric model is defined.
            )doc"
        )

        .def(
            "get_density_at",
            nanobind::overload_cast<const LLA&, const Instant&>(&Exponential::getDensityAt, nanobind::const_),
            arg("lla"),
            arg("instant"),
            R"doc(
                Get the atmospheric density value at a given position and instant.

                Args:
                    lla (LLA): A position, expressed as latitude, longitude, altitude [deg, deg, m].
                    instant (Instant): An Instant.

                Returns:
                    float: Atmospheric density value.
            )doc"
        )

        ;
}
