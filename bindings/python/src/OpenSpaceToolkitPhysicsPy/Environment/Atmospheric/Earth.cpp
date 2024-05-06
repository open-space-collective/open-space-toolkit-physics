/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Coordinate/Position.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Spherical/LLA.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

#include <OpenSpaceToolkitPhysicsPy/Environment/Atmospheric/Earth/CSSISpaceWeather.cpp>
#include <OpenSpaceToolkitPhysicsPy/Environment/Atmospheric/Earth/Exponential.cpp>
#include <OpenSpaceToolkitPhysicsPy/Environment/Atmospheric/Earth/Manager.cpp>
#include <OpenSpaceToolkitPhysicsPy/Environment/Atmospheric/Earth/NRLMSISE00.cpp>

inline void OpenSpaceToolkitPhysicsPy_Environment_Atmospheric_Earth(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Shared;
    using ostk::core::type::Real;

    using ostk::physics::environment::atmospheric::Earth;
    using EarthGravityModel = ostk::physics::environment::gravitational::Earth;

    using ostk::physics::environment::object::Celestial;
    using ostk::physics::unit::Length;
    using ostk::physics::time::Instant;
    using ostk::physics::coordinate::Position;
    using ostk::physics::coordinate::spherical::LLA;
    using ostk::physics::coordinate::Frame;

    {
        class_<Earth, Shared<Earth>> earth_class(aModule, "Earth");

        enum_<Earth::Type>(earth_class, "Type")

            .value("Undefined", Earth::Type::Undefined)
            .value("Exponential", Earth::Type::Exponential)
            .value("NRLMSISE00", Earth::Type::NRLMSISE00);

        enum_<Earth::InputDataType>(earth_class, "InputDataType")

            .value("Undefined", Earth::InputDataType::Undefined)
            .value("ConstantFluxAndGeoMag", Earth::InputDataType::ConstantFluxAndGeoMag)
            .value("CSSISpaceWeatherFile", Earth::InputDataType::CSSISpaceWeatherFile);

        earth_class

            .def(
                init<
                    const Earth::Type&,
                    const Earth::InputDataType&,
                    const Real&,
                    const Real&,
                    const Real&,
                    const Shared<const Frame>&,
                    const Length&,
                    const Real&,
                    const Shared<Celestial>&>(),
                arg("type"),
                arg("input_data_type") = Earth::InputDataType::Undefined,
                arg("f107_constant_value") = Earth::defaultF107ConstantValue,
                arg("f107_average_constant_value") = Earth::defaultF107AConstantValue,
                arg("kp_constant_value") = Earth::defaultKpConstantValue,
                arg_v("earth_frame", Frame::ITRF(), "Frame.ITRF()"),
                arg_v("earth_radius", EarthGravityModel::WGS84.equatorialRadius_, "WGS84.equatorialRadius_"),
                arg_v("earth_flattening", EarthGravityModel::WGS84.flattening_, "WGS84.flattening_"),
                arg("sun_celestial") = nullptr
            )

            .def("get_type", &Earth::getType)

            .def("get_input_data_type", &Earth::getInputDataType)

            .def("is_defined", &Earth::isDefined)

            .def(
                "get_density_at",
                pybind11::overload_cast<const Position&, const Instant&>(&Earth::getDensityAt, pybind11::const_),
                arg("position"),
                arg("instant")
            )

            .def(
                "get_density_at",
                pybind11::overload_cast<const LLA&, const Instant&>(&Earth::getDensityAt, pybind11::const_),
                arg("lla"),
                arg("instant")
            )

            ;
    }

    // Create "earth" python submodule
    auto earth = aModule.def_submodule("earth");

    OpenSpaceToolkitPhysicsPy_Environment_Atmospheric_Earth_CSSISpaceWeather(earth);
    OpenSpaceToolkitPhysicsPy_Environment_Atmospheric_Earth_Manager(earth);
    OpenSpaceToolkitPhysicsPy_Environment_Atmospheric_Earth_Exponential(earth);
    OpenSpaceToolkitPhysicsPy_Environment_Atmospheric_Earth_NRLMSISE00(earth);
}
