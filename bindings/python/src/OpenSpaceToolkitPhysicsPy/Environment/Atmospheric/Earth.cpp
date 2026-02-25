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

    using ostk::core::type::Real;
    using ostk::core::type::Shared;

    using ostk::physics::environment::atmospheric::Earth;

    using ostk::physics::coordinate::Frame;
    using ostk::physics::coordinate::Position;
    using ostk::physics::coordinate::spherical::LLA;
    using ostk::physics::environment::object::Celestial;
    using ostk::physics::time::Instant;
    using ostk::physics::unit::Length;

    {
        class_<Earth, Shared<Earth>> earth_class(
            aModule,
            "Earth",
            R"doc(
                Earth atmospheric model.

            )doc"
        );

        enum_<Earth::Type>(earth_class, "Type")

            .value(
                "Undefined",
                Earth::Type::Undefined,
                R"doc(
                    Undefined.
                )doc"
            )
            .value(
                "Exponential",
                Earth::Type::Exponential,
                R"doc(
                    Exponential atmospheric density model, valid up to 1000 km.
                )doc"
            )
            .value(
                "NRLMSISE00",
                Earth::Type::NRLMSISE00,
                R"doc(
                    Navy Research Lab Mass Spectrometer and Incoherent Scatter Radar Exosphere 2000.
                )doc"
            );

        enum_<Earth::InputDataType>(earth_class, "InputDataType")

            .value(
                "Undefined",
                Earth::InputDataType::Undefined,
                R"doc(
                    Undefined.
                )doc"
            )
            .value(
                "ConstantFluxAndGeoMag",
                Earth::InputDataType::ConstantFluxAndGeoMag,
                R"doc(
                    Use constant values for F10.7, F10.7a and Kp NRLMSISE00 input parameters.
                )doc"
            )
            .value(
                "CSSISpaceWeatherFile",
                Earth::InputDataType::CSSISpaceWeatherFile,
                R"doc(
                    Use historical and predicted values for F10.7, F10.7a and Kp NRLMSISE00 input parameters from CSSI.
                )doc"
            );

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
                arg_v("earth_radius", Length::Meters(6378137.0), "Length.Meters(6378137.0)"),
                arg("earth_flattening") = 1.0 / 298.257223563,
                arg("sun_celestial") = nullptr,
                R"doc(
                    Constructor.

                Args:
                    type (Earth.Type): Earth atmospheric model type.
                    input_data_type (Earth.InputDataType): Earth atmospheric model input data type.
                    f107_constant_value (Real): F10.7 constant value.
                    f107_average_constant_value (Real): F10.7a constant value.
                    kp_constant_value (Real): Kp constant value.
                    earth_frame (Frame): Earth frame.
                    earth_radius (Length): Earth radius [m].
                    earth_flattening (Real): Earth flattening.
                    sun_celestial (Celestial): Sun celestial object.

                Returns:
                    Earth: Earth atmospheric model.
                )doc"
            )

            .def(
                "get_type",
                &Earth::getType,
                R"doc(
                    Get the Earth atmospheric model type.

                    Returns:
                        Earth.Type: Earth atmospheric model type.
                )doc"
            )

            .def(
                "get_input_data_type",
                &Earth::getInputDataType,
                R"doc(
                    Get the Earth atmospheric model input data type.

                    Returns:
                        Earth.InputDataType: Earth atmospheric model input data type.
                )doc"
            )

            .def(
                "is_defined",
                &Earth::isDefined,
                R"doc(
                    Check if the Earth atmospheric model is defined.

                    Returns:
                        bool: True if defined.
                )doc"
            )

            .def(
                "get_density_at",
                pybind11::overload_cast<const Position&, const Instant&>(&Earth::getDensityAt, pybind11::const_),
                arg("position"),
                arg("instant"),
                R"doc(
                    Get the atmospheric density value at a given position and instant.

                    Args:
                        position (Position): A position.
                        instant (Instant): An instant.

                    Returns:
                        float: Atmospheric density value [kg.m^-3].
                )doc"
            )

            .def(
                "get_density_at",
                pybind11::overload_cast<const LLA&, const Instant&>(&Earth::getDensityAt, pybind11::const_),
                arg("lla"),
                arg("instant"),
                R"doc(
                    Get the atmospheric density value at a given position and instant.

                    Args:
                        lla (LLA): A position, expressed as latitude, longitude, altitude [deg, deg, m].
                        instant (Instant): An instant.

                    Returns:
                        float: Atmospheric density value [kg.m^-3].
                )doc"
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
