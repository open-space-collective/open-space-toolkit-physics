/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/Manager.hpp>

inline void OpenSpaceToolkitPhysicsPy_Environment_Atmospheric_Earth_Manager(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::types::Shared;

    using ostk::physics::environment::atmospheric::earth::Manager;

    class_<Manager> manager(aModule, "Manager");

    manager

        .def("get_mode", &Manager::getMode)
        .def("get_local_repository", &Manager::getLocalRepository)
        .def("get_cssi_space_weather_directory", &Manager::getCSSISpaceWeatherDirectory)
        .def("get_remote_url", &Manager::getRemoteUrl)
        .def("get_cssi_space_weather_array", &Manager::getCSSISpaceWeatherArray)
        .def("get_cssi_space_weather_at", &Manager::getCSSISpaceWeatherAt, arg("instant"))
        .def("get_kp_3_hour_solar_indices_at", &Manager::getKp3HourSolarIndicesAt, arg("instant"))
        .def("get_ap_3_hour_solar_indices_at", &Manager::getAp3HourSolarIndicesAt, arg("instant"))
        .def("get_ap_daily_index_at", &Manager::getApDailyIndexAt, arg("instant"))
        .def("get_f107_solar_flux_at", &Manager::getF107SolarFluxAt, arg("instant"))
        .def("get_f107_solar_flux_81_day_avg_at", &Manager::getF107SolarFlux81DayAvgAt, arg("instant"))

        .def("set_mode", &Manager::setMode, arg("mode"))
        .def("set_local_repository", &Manager::setLocalRepository, arg("directory"))
        .def("set_remote_url", &Manager::setRemoteUrl, arg("url"))

        .def("load_cssi_space_weather", &Manager::loadCSSISpaceWeather, arg("cssi_space_weather"))

        .def("fetch_latest_cssi_space_weather", &Manager::fetchLatestCSSISpaceWeather)

        .def("reset", &Manager::reset)
        .def("clear_local_repository", &Manager::clearLocalRepository)

        .def_static("get", &Manager::Get, return_value_policy::reference)
        .def_static("default_mode", &Manager::DefaultMode)
        .def_static("default_local_repository", &Manager::DefaultLocalRepository)
        .def_static("default_local_repository_lock_timeout", &Manager::DefaultLocalRepositoryLockTimeout)
        .def_static("default_remote_url", &Manager::DefaultRemoteUrl)

        ;

    enum_<Manager::Mode>(manager, "Mode")

        .value("Manual", Manager::Mode::Manual)
        .value("Automatic", Manager::Mode::Automatic)

        ;
}
