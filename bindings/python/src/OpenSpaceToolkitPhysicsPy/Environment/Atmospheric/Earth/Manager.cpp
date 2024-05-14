/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/Manager.hpp>

inline void OpenSpaceToolkitPhysicsPy_Environment_Atmospheric_Earth_Manager(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::physics::environment::atmospheric::earth::Manager;

    class_<Manager> manager(
        aModule,
        "Manager",
        R"doc(
            CSSI space weather manager.

            The following environment variables can be defined:

            - "OSTK_PHYSICS_ENVIRONMENT_ATMOSPHERIC_EARTH_MANAGER_MODE" will override "DefaultMode"
            - "OSTK_PHYSICS_ENVIRONMENT_ATMOSPHERIC_EARTH_MANAGER_LOCAL_REPOSITORY" will override "DefaultLocalRepository"
            - "OSTK_PHYSICS_ENVIRONMENT_ATMOSPHERIC_EARTH_MANAGER_LOCAL_REPOSITORY_LOCK_TIMEOUT" will override "DefaultLocalRepositoryLockTimeout"

            :reference: https://ai-solutions.com/_help_Files/cssi_space_weather_file.htm
        )doc"
    );

    manager

        .def(
            "get_mode",
            &Manager::getMode,
            R"doc(
                Get manager mode.

                Returns:
                    Mode: Manager mode.
            )doc"
        )
        .def(
            "get_local_repository",
            &Manager::getLocalRepository,
            R"doc(
                Get local repository.

                Returns:
                    Directory: Local repository.
            )doc"
        )
        .def(
            "get_cssi_space_weather_directory",
            &Manager::getCSSISpaceWeatherDirectory,
            R"doc(
                Get CSSI space weather directory.

                Returns:
                    Directory: CSSI space weather directory.
            )doc"
        )
        .def(
            "get_loaded_cssi_space_weather",
            &Manager::getLoadedCSSISpaceWeather,
            R"doc(
                Get currently loaded CSSI Space Weather file.

                Returns:
                    CSSISpaceWeather: Currently loaded CSSI Space Weather file.
            )doc"
        )
        .def(
            "get_cssi_space_weather_at",
            &Manager::getCSSISpaceWeatherAt,
            arg("instant"),
            R"doc(
                Get CSSI Space Weather at instant.

                Args:
                    instant (Instant): An instant.

                Returns:
                    CSSISpaceWeather: CSSI Space Weather.
            )doc"
        )
        .def(
            "get_kp_3_hour_solar_indices_at",
            &Manager::getKp3HourSolarIndicesAt,
            arg("instant"),
            R"doc(
                Get a list of 8 3-hourly Kp solar indices for the day containing instant.

                Args:
                    instant (Instant): An instant.

                Returns:
                    list[int]: list of 8 3-hourly Kp solar indices.
            )doc"
        )
        .def(
            "get_ap_3_hour_solar_indices_at",
            &Manager::getAp3HourSolarIndicesAt,
            arg("instant"),
            R"doc(
                Get a list of 8 3-hourly Ap solar indices for the day containing instant.

                Args:
                    instant (Instant): An instant.

                Returns:
                    list[int]: list of 8 3-hourly Ap solar indices.
            )doc"
        )
        .def(
            "get_ap_daily_index_at",
            &Manager::getApDailyIndexAt,
            arg("instant"),
            R"doc(
                Get daily Ap index for the day containing instant.

                Args:
                    instant (Instant): An instant.

                Returns:
                    Integer: Daily Ap index.
            )doc"
        )
        .def(
            "get_f107_solar_flux_at",
            &Manager::getF107SolarFluxAt,
            arg("instant"),
            R"doc(
                Get the daily value for F10.7 solar flux at instant.

                Args:
                    instant (Instant): An instant.

                Returns:
                    float: Daily value for F10.7 solar flux.
            )doc"
        )
        .def(
            "get_f107_solar_flux_81_day_avg_at",
            &Manager::getF107SolarFlux81DayAvgAt,
            arg("instant"),
            R"doc(
                Get the 81-day average value for F10.7 solar flux centered on instant.

                Args:
                    instant (Instant): An instant.

                Returns:
                    float: Centered 81-day average value for F10.7 solar flux.
            )doc"
        )

        .def(
            "set_mode",
            &Manager::setMode,
            arg("mode"),
            R"doc(
                Set manager mode.

                Args:
                    mode (Mode): A manager mode.
            )doc"
        )
        .def(
            "set_local_repository",
            &Manager::setLocalRepository,
            arg("directory"),
            R"doc(
                Set local repository.

                Args:
                    directory (Directory): A repository directory.
            )doc"
        )

        .def(
            "load_cssi_space_weather",
            &Manager::loadCSSISpaceWeather,
            arg("cssi_space_weather"),
            R"doc(
                Load CSSI Space Weather.

                Args:
                    cssi_space_weather (CSSISpaceWeather): A CSSI Space Weather.
            )doc"
        )

        .def(
            "fetch_latest_cssi_space_weather",
            &Manager::fetchLatestCSSISpaceWeather,
            R"doc(
                Fetch latest CSSI Space Weather file.

                Returns:
                    File: Latest CSSI Space Weather file.
            )doc"
        )

        .def(
            "reset",
            &Manager::reset,
            R"doc(
                Reset manager.

                Unload all space weather files and clear cache.
            )doc"
        )
        .def(
            "clear_local_repository",
            &Manager::clearLocalRepository,
            R"doc(
                Clear local repository.

                Delete all files in local repository.
            )doc"
        )

        .def_static(
            "get",
            &Manager::Get,
            return_value_policy::reference,
            R"doc(
                Get manager singleton.

                Returns:
                    Manager: Reference to manager.
            )doc"
        )
        .def_static(
            "default_mode",
            &Manager::DefaultMode,
            R"doc(
                Get default manager mode.

                Returns:
                    Mode: Default manager mode.
            )doc"
        )
        .def_static(
            "default_local_repository",
            &Manager::DefaultLocalRepository,
            R"doc(
                Get default local repository.

                Returns:
                    Directory: Default local repository.
            )doc"
        )
        .def_static(
            "default_local_repository_lock_timeout",
            &Manager::DefaultLocalRepositoryLockTimeout,
            R"doc(
                Get default local repository lock timeout.

                Returns:
                    Duration: Default local repository lock timeout.
            )doc"
        )

        ;

    enum_<Manager::Mode>(manager, "Mode")

        .value(
            "Manual",
            Manager::Mode::Manual,
            R"doc(
                Manual mode.
            )doc"
        )
        .value(
            "Automatic",
            Manager::Mode::Automatic,
            R"doc(
                Automatic mode.
            )doc"
        )

        ;
}
