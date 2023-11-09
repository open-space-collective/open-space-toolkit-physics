/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth.hpp>
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
    using EarthGravityModel = ostk::physics::environment::gravitational::Earth;
    // using EarthAtmosphericModel = ostk::physics::environment::atmospheric::Earth;
    using ostk::physics::environment::atmospheric::earth::NRLMSISE00;

    class_<NRLMSISE00, Shared<NRLMSISE00>> nrlmsise(aModule, "NRLMSISE00");

    nrlmsise

        .def(
            init<
                const NRLMSISE00::InputDataType&,
                const Real&,
                const Real&,
                const Real&,
                const Shared<const Frame>&,
                const Length&,
                const Real&,
                const Shared<Celestial>&>(),
            arg("input_data_type"),
            arg("f107_constant_value"),
            arg("f107_average_constant_value"),
            arg("kp_constant_value"),
            arg("earth_frame"),
            arg("earth_radius"),
            arg("earth_flattening"),
            arg("sun_celestial")
        )

        .def("is_defined", &NRLMSISE00::isDefined)

        .def("get_input_data_type", &NRLMSISE00::getInputDataType)

        .def("get_density_at", &NRLMSISE00::getDensityAt, arg("lla"), arg("instant"))

        ;

    enum_<NRLMSISE00::InputDataType>(nrlmsise, "InputDataType")

        .value("ConstantFluxAndGeoMag", NRLMSISE00::InputDataType::ConstantFluxAndGeoMag)
        .value("CSSISpaceWeatherFile", NRLMSISE00::InputDataType::CSSISpaceWeatherFile);
}
