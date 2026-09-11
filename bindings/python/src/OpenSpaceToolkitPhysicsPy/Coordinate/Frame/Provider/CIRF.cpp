/// Apache License 2.0

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
            "is_xys_interpolation_enabled",
            &CIRF::IsXysInterpolationEnabled,
            R"doc(
                Check whether X, Y, s interpolation is enabled.

                Defaults to disabled, unless the environment variable
                OSTK_PHYSICS_COORDINATE_FRAME_PROVIDER_CIRF_XYS_INTERPOLATION is set to "Enabled" or "True".
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

                Overrides the environment-variable default for the lifetime of the process.

                Args:
                    interpolation_enabled (bool): True to enable interpolation, False to evaluate the series directly.
            )doc"
        )

        .def_static(
            "clear_xys_cache",
            &CIRF::ClearXysCache,
            R"doc(
                Clear the cached X, Y, s interpolation grid.

                Releases the memory held by the grid nodes computed so far. Subsequent interpolated evaluations
                re-populate the grid on demand, so this only affects memory usage and performance, not results.
            )doc"
        )

        ;
}
