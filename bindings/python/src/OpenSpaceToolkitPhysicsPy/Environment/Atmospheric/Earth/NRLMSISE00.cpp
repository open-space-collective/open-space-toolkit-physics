/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/NRLMSISE00.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Objects/Celestial.hpp>

inline void OpenSpaceToolkitPhysicsPy_Environment_Atmospheric_Earth_NRLMSISE00(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::types::Shared;
    using ostk::core::types::Real;

    using ostk::physics::units::Length;
    using ostk::physics::time::Instant;
    using ostk::physics::coord::Frame;
    using ostk::physics::coord::spherical::LLA;
    using ostk::physics::env::obj::Celestial;
    using ostk::physics::environment::atmospheric::earth::NRLMSISE00;

    class_<NRLMSISE00, Shared<NRLMSISE00>>(aModule, "NRLMSISE00")

        .def(
            init<
                const Shared<const Frame>&, 
                const Length&, 
                const Real&, 
                const Shared<Celestial>&
                >(),
            arg("earth_frame"),
            arg("earth_radius"),
            arg("earth_flattening"),
            arg("sun_celestial") = nullptr
            )

        .def("is_defined", &NRLMSISE00::isDefined)

        .def(
            "get_density_at",
            &NRLMSISE00::getDensityAt,
            arg("lla"),
            arg("instant")
        )

        ;
}
