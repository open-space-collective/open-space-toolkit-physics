/// Apache License 2.0

#include <tuple>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/CIRF.hpp>

inline void OpenSpaceToolkitPhysicsPy_Coordinate_Frame_Provider_CIRF(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Real;
    using ostk::core::type::Shared;

    using ostk::physics::coordinate::frame::Provider;
    using ostk::physics::coordinate::frame::provider::CIRF;

    class_<CIRF, Shared<CIRF>, Provider>(
        aModule,
        "CIRF",
        R"doc(
            Celestial Intermediate Reference Frame (CIRF) provider.

            Bias, precession-nutation.
        )doc"
    )

        .def(
            init<>(),
            R"doc(
                Constructor.
            )doc"
        )

        .def(
            "is_defined",
            &CIRF::isDefined,
            R"doc(
                Check if the CIRF provider is defined.

                Returns:
                    bool: True if defined.
            )doc"
        )

        .def(
            "get_transform_at",
            &CIRF::getTransformAt,
            arg("instant"),
            R"doc(
                Get the transform at a given instant.

                Args:
                    instant (Instant): An instant.

                Returns:
                    Transform: The transform from GCRF to CIRF at the given instant.
            )doc"
        )

        .def_static(
            "compute_cip_coordinates",
            [](const Real& aModifiedJulianDate_TT, const bool interpolate) -> std::tuple<double, double, double>
            {
                double x;
                double y;
                double s;

                CIRF::ComputeCIPCoordinates(aModifiedJulianDate_TT, x, y, s, interpolate);

                return {x, y, s};
            },
            arg("modified_julian_date_tt"),
            arg("interpolate"),
            R"doc(
                Compute the IAU 2006/2000A CIP X, Y and CIO locator s at a given instant.

                This is the raw model output (before the observed CIP offsets applied by `get_transform_at`),
                evaluated either directly via the SOFA series or by interpolating a cached grid of the series
                (see `is_xys_interpolation_enabled`).

                Args:
                    modified_julian_date_tt (float): A Modified Julian Date, in the TT scale.
                    interpolate (bool): If True, interpolate a cached grid of the series; otherwise evaluate it directly.

                Returns:
                    tuple[float, float, float]: The CIP X coordinate [rad], the CIP Y coordinate [rad] and the CIO locator s [rad].
            )doc"
        )

        .def_static(
            "is_xys_interpolation_enabled",
            &CIRF::IsXysInterpolationEnabled,
            R"doc(
                Check whether X, Y, s interpolation is enabled.

                Defaults to enabled, unless the environment variable
                OSTK_PHYSICS_COORDINATE_FRAME_PROVIDER_CIRF_XYS_INTERPOLATION is set to "Disabled" or "False".
                Can be overridden at runtime via `set_xys_interpolation_enabled`.

                Returns:
                    bool: True if X, Y, s interpolation is enabled.
            )doc"
        )

        .def_static(
            "set_xys_interpolation_enabled",
            &CIRF::SetXysInterpolationEnabled,
            arg("interpolation_enabled"),
            R"doc(
                Enable or disable X, Y, s interpolation at runtime.

                Overrides the environment-variable default. Primarily intended for testing and benchmarking.

                Args:
                    interpolation_enabled (bool): True to enable interpolation, False to evaluate the series directly.
            )doc"
        )

        ;
}
