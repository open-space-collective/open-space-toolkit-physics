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

    class_<NRLMSISE00, Shared<NRLMSISE00>> nrlmsise(aModule, "NRLMSISE00",
        R"doc(
            NRLMSISE00 atmospheric model.

        )doc"
    );

    enum_<NRLMSISE00::InputDataType>(nrlmsise, "InputDataType")

        .value("ConstantFluxAndGeoMag", NRLMSISE00::InputDataType::ConstantFluxAndGeoMag,
            R"doc(
                Use constant values for F10.7, F10.7a and Kp NRLMSISE00 input parameters.
            )doc"
        )
        .value("CSSISpaceWeatherFile", NRLMSISE00::InputDataType::CSSISpaceWeatherFile,
            R"doc(
                Use historical and predicted values for F10.7, F10.7a and Kp NRLMSISE00 input parameters.
            )doc"
        );

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
            arg("earth_frame") = Frame::ITRF(),
            arg("earth_radius") = EarthGravityModel::WGS84.equatorialRadius_,
            arg("earth_flattening") = EarthGravityModel::WGS84.flattening_,
            arg("sun_celestial") = nullptr,
            R"doc(
                Constructor.
            )doc"
        )

        .def("is_defined", &NRLMSISE00::isDefined,
            R"doc(
                Check if the NRLMSISE00 atmospheric model is defined.

                Returns:
                    bool: True if defined.
            )doc"
        )

        .def("get_input_data_type", &NRLMSISE00::getInputDataType,
            R"doc(
                Get the input data source type used to construct the NRLMSISE00 atmospheric model.

                Returns:
                    NRLMSISE00 input data source type.
            )doc"
        )

        .def("get_density_at", &NRLMSISE00::getDensityAt, arg("lla"), arg("instant"),
            R"doc(
                Get the atmospheric density value at a given position and instant.

                Args:
                    lla (LLA): A position, expressed as latitude, longitude, altitude [deg, deg, m].
                    instant (Instant): An instant.

                Returns:
                    Real: Atmospheric density value [kg.m^-3]
            )doc"
        )

        ;
}
