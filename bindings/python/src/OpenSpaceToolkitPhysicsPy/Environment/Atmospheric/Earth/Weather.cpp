/// Apache License 2.0

#include <OpenSpaceToolkitPhysicsPy/Environment/Atmospheric/Earth/Weather/CSSISpaceWeather.cpp>
#include <OpenSpaceToolkitPhysicsPy/Environment/Atmospheric/Earth/Weather/Manager.cpp>

inline void OpenSpaceToolkitPhysicsPy_Environment_Atmospheric_Earth_Weather(pybind11::module& aModule)
{
    // Create "weather" python submodule
    auto weather = aModule.def_submodule("weather");

    // Add __path__ attribute for "weather" submodule
    weather.attr("__path__") = "ostk.physics.environment.earth.weather";

    // Add objects to python "weather" submodules
    OpenSpaceToolkitPhysicsPy_Environment_Atmospheric_Earth_Weather_CSSISpaceWeather(weather);
    OpenSpaceToolkitPhysicsPy_Environment_Atmospheric_Earth_Weather_Manager(weather);
}
