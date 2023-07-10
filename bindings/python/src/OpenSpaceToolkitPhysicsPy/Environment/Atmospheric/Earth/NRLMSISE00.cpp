/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/NRLMSISE00.hpp>

inline void OpenSpaceToolkitPhysicsPy_Environment_Atmospheric_Earth_NRLMSISE00(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::types::Shared;

    using ostk::physics::time::Instant;
    using ostk::physics::coord::Position;
    using ostk::physics::coord::spherical::LLA;
    using ostk::physics::environment::atmospheric::earth::NRLMSISE00;

    class_<NRLMSISE00, Shared<NRLMSISE00>>(aModule, "NRLMSISE00")

        .def(init<>())

        .def("is_defined", &NRLMSISE00::isDefined)

        .def(
            "get_density_at",
            pybind11::overload_cast<const LLA&, const Instant&, const Position&>(
                &NRLMSISE00::getDensityAt, pybind11::const_
            ),
            arg("lla"),
            arg("instant"),
            arg("sun_position") = Position::Undefined()
        )

        .def(
            "get_density_at",
            pybind11::overload_cast<const Position&, const Instant&, const Position&>(
                &NRLMSISE00::getDensityAt, pybind11::const_
            ),
            arg("position"),
            arg("instant"),
            arg("sun_position")
        )

        .def(
            "get_density_at",
            pybind11::overload_cast<const Position&, const Instant&>(&NRLMSISE00::getDensityAt, pybind11::const_),
            arg("position"),
            arg("instant")
        )

        ;
}
