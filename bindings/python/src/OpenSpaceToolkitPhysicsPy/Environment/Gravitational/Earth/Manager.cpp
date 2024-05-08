/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Earth/Manager.hpp>

inline void OpenSpaceToolkitPhysicsPy_Environment_Gravitational_Earth_Manager(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::physics::environment::gravitational::earth::Manager;

    class_<Manager> manager(aModule, "Manager",
        R"doc(
            Earth gravitational model data manager.

            Fetches and manages necessary gravity model data files.

            The following environment variables can be defined:

            - "OSTK_PHYSICS_ENVIRONMENT_GRAVITATIONAL_EARTH_MANAGER_MODE" will override "DefaultMode"
            - "OSTK_PHYSICS_ENVIRONMENT_GRAVITATIONAL_EARTH_MANAGER_LOCAL_REPOSITORY" will override "DefaultLocalRepository"
        )doc"
    );

    manager

        .def("get_mode", &Manager::getMode,
            R"doc(
                Get mode.

                Returns:
                    Mode: Mode
            )doc"
        )
        .def("set_mode", &Manager::setMode, arg("mode"),
            R"doc(
                Set mode.

                Args:
                    mode (Mode): Mode
            )doc"
        )
        .def_static("default_mode", &Manager::DefaultMode,
            R"doc(
                Get default mode.

                Returns:
                    Mode: Default mode
            )doc"
        )

        .def("get_local_repository", &Manager::getLocalRepository,
            R"doc(
                Get local repository.

                Returns:
                    Path: Local repository
            )doc"
        )
        .def("set_local_repository", &Manager::setLocalRepository, arg("directory"),
            R"doc(
                Set local repository.

                Args:
                    directory (Path): Local repository
            )doc"
        )
        .def_static("default_local_repository", &Manager::DefaultLocalRepository,
            R"doc(
                Get default local repository.

                Returns:
                    Path: Default local repository
            )doc"
        )
        .def_static("default_local_repository_lock_timeout", &Manager::DefaultLocalRepositoryLockTimeout,
            R"doc(
                Get default local repository lock timeout.

                Returns:
                    Duration: Default local repository lock timeout
            )doc"
        )

        .def("reset", &Manager::reset,
            R"doc(
                Reset the manager.

                Reset path and mode to default values.
            )doc"
        )

        .def("fetch_data_files_for_type", &Manager::fetchDataFilesForType, arg("model_type"),
            R"doc(
                Fetch data file from remote.

                Args:
                    model_type (EarthGravitationalModel::Type): A model type
            )doc"
        )
        .def("has_data_files_for_type", &Manager::hasDataFilesForType, arg("model_type"),
            R"doc(
                Returns true if manager has data file for the given model type.

                Args:
                    model_type (EarthGravitationalModel::Type): A model type

                Returns:
                    bool: True if manager has data file for the given model type
            )doc"
        )
        .def("local_data_files_for_type", &Manager::localDataFilesForType, arg("model_type"),
            R"doc(
                Returns array of file objects for the given type.

                Args:
                    model_type (EarthGravitationalModel::Type): A model type

                Returns:
                    Array[File]: Array of Files
            )doc"
        )

        .def_static("get", &Manager::Get, return_value_policy::reference,
            R"doc(
                Get manager singleton.

                Returns:
                    Manager: Reference to manager
            )doc"
        )

        ;

    enum_<Manager::Mode>(manager, "Mode")

        .value("Manual", Manager::Mode::Manual,
            R"doc(
                Manual mode.
            )doc"
        )
        .value("Automatic", Manager::Mode::Automatic,
            R"doc(
                Automatic mode.
            )doc"
        )

        ;
}
