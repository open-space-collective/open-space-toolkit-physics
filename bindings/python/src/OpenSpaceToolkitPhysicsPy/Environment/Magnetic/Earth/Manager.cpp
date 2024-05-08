/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Environment/Magnetic/Earth/Manager.hpp>

inline void OpenSpaceToolkitPhysicsPy_Environment_Magnetic_Earth_Manager(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::physics::environment::magnetic::earth::Manager;

    class_<Manager> manager(aModule, "Manager",
        R"doc(
            Earth magnetic model data manager

            Fetches and manages necessary magnetic model data files.

            The following environment variables can be defined:

            - "OSTK_PHYSICS_ENVIRONMENT_MAGNETIC_EARTH_MANAGER_ENABLED" will override "DefaultEnabled"
            - "OSTK_PHYSICS_ENVIRONMENT_MAGNETIC_EARTH_MANAGER_LOCAL_REPOSITORY" will override "DefaultLocalRepository"
        )doc"
    );

    manager

        .def("get_mode", &Manager::getMode,
            R"doc(
                Get manager mode

                Returns:
                    Manager.Mode: Manager mode
            )doc"
        )
        .def("set_mode", &Manager::setMode, arg("mode"),
            R"doc(
                Set manager mode

                Args:
                    mode (Manager.Mode): Manager mode
            )doc"
        )
        .def_static("default_mode", &Manager::DefaultMode,
            R"doc(
                Get default manager mode

                Returns:
                    Manager.Mode: Default manager mode
            )doc"
        )

        .def("get_local_repository", &Manager::getLocalRepository,
            R"doc(
                Get local repository

                Returns:
                    Directory: Local repository
            )doc"
        )
        .def("set_local_repository", &Manager::setLocalRepository, arg("directory"),
            R"doc(
                Set local repository

                Args:
                    directory (Directory): Local repository
            )doc"
        )
        .def_static("default_local_repository", &Manager::DefaultLocalRepository,
            R"doc(
                Get default local repository

                Returns:
                    Directory: Default local repository
            )doc"
        )
        .def_static("default_local_repository_lock_timeout", &Manager::DefaultLocalRepositoryLockTimeout,
            R"doc(
                Get default local repository lock timeout

                Returns:
                    Duration: Default local repository lock timeout
            )doc"
        )

        .def("reset", &Manager::reset,
            R"doc(
                Reset the manager

                Reset path and mode to default values
            )doc"
        )

        .def("fetch_data_files_for_type", &Manager::fetchDataFilesForType, arg("model_type"),
            R"doc(
                Fetch data file from remote

                Args:
                    model_type (EarthMagneticModel.Type): Model type
            )doc"
        )
        .def("has_data_files_for_type", &Manager::hasDataFilesForType, arg("model_type"),
            R"doc(
                Check if data files are available for the given type

                Args:
                    model_type (EarthMagneticModel.Type): Model type

                Returns:
                    bool: True if data files are available for the given type
            )doc"
        )
        .def("local_data_files_for_type", &Manager::localDataFilesForType, arg("model_type"),
            R"doc(
                Get local data files for the given type

                Args:
                    model_type (EarthMagneticModel.Type): Model type

                Returns:
                    Array[File]: Local data files
            )doc"
        )

        .def_static("get", &Manager::Get, return_value_policy::reference,
            R"doc(
                Get manager singleton

                Returns:
                    Manager: Reference to manager
            )doc"
        )

        ;

    enum_<Manager::Mode>(manager, "Mode")

        .value("Manual", Manager::Mode::Manual,
            R"doc(
                Manual mode

                Manually load and unload magnetic files
            )doc"
        )
        .value("Automatic", Manager::Mode::Automatic,
            R"doc(
                Automatic mode

                Automatically fetch magnetic files from remote repositories
            )doc"
        )

        ;
}
