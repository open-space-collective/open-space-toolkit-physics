/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/NRLMSISE00.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Object/Celestial.hpp>

inline void OpenSpaceToolkitPhysicsPy_Environment_Atmospheric_Earth_NRLMSISE00(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Shared;
    using ostk::core::type::Real;

    using ostk::physics::unit::Length;
    using ostk::physics::time::Instant;
    using ostk::physics::coordinate::Frame;
    using ostk::physics::coordinate::spherical::LLA;
    using ostk::physics::environment::object::Celestial;
    using EarthGravityModel = ostk::physics::environment::gravitational::Earth;
    using EarthAtmosphericModel = ostk::physics::environment::atmospheric::Earth;
    using ostk::physics::environment::atmospheric::earth::NRLMSISE00;

    class_<NRLMSISE00, Shared<NRLMSISE00>> nrlmsise(aModule, "NRLMSISE00");

    enum_<NRLMSISE00::InputDataType>(nrlmsise, "InputDataType")

        .value("ConstantFluxAndGeoMag", NRLMSISE00::InputDataType::ConstantFluxAndGeoMag)
        .value("CSSISpaceWeatherFile", NRLMSISE00::InputDataType::CSSISpaceWeatherFile);

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
            arg("input_data_type") = NRLMSISE00::InputDataType::CSSISpaceWeatherFile,
            arg("f107_constant_value") = EarthAtmosphericModel::defaultF107ConstantValue,
            arg("f107_average_constant_value") = EarthAtmosphericModel::defaultF107AConstantValue,
            arg("kp_constant_value") = EarthAtmosphericModel::defaultKpConstantValue,
            arg_v("earth_frame", Frame::ITRF(), "Frame.ITRF()"),
            arg_v("earth_radius", EarthGravityModel::WGS84.equatorialRadius_, "WGS84.equatorialRadius_"),
            arg_v("earth_flattening", EarthGravityModel::WGS84.flattening_, "WGS84.flattening_"),
            arg("sun_celestial") = nullptr
        )

        .def("is_defined", &NRLMSISE00::isDefined)

        .def("get_input_data_type", &NRLMSISE00::getInputDataType)

        .def("get_density_at", &NRLMSISE00::getDensityAt, arg("lla"), arg("instant"))

        ;
}
