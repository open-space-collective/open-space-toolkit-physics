/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/Exponential.hpp>

inline void OpenSpaceToolkitPhysicsPy_Environment_Atmospheric_Earth_Exponential(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::types::Shared;

    using ostk::physics::time::Instant;
    using ostk::physics::coord::Position;
    using ostk::physics::coord::spherical::LLA;
    using ostk::physics::environment::atmospheric::earth::Exponential;

    class_<Exponential, Shared<Exponential>>(aModule, "Exponential")

        .def(init<>())

        .def("is_defined", &Exponential::isDefined)

        .def(
            "get_density_at",
            pybind11::overload_cast<const LLA&, const Instant&>(&Exponential::getDensityAt, pybind11::const_),
            arg("lla"),
            arg("instant")
        )

        .def(
            "get_density_at",
            pybind11::overload_cast<const Position&, const Instant&>(&Exponential::getDensityAt, pybind11::const_),
            arg("position"),
            arg("instant")
        )

        ;
}
