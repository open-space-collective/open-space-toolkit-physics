/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Earth/Manager.hpp>
#include <OpenSpaceToolkit/Physics/Manager.hpp>

inline void OpenSpaceToolkitPhysicsPy_Environment_Gravitational_Earth_Manager(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::physics::environment::gravitational::earth::Manager;
    using BaseManager = ostk::physics::Manager;

    class_<Manager, BaseManager> manager(
        aModule,
        "Manager",
        R"doc(
            Earth gravitational model data manager.

            Fetches and manages necessary gravity model data files.

            The following environment variables can be defined:

            - "OSTK_PHYSICS_ENVIRONMENT_GRAVITATIONAL_EARTH_MANAGER_MODE" will override "DefaultMode"
            - "OSTK_PHYSICS_ENVIRONMENT_GRAVITATIONAL_EARTH_MANAGER_LOCAL_REPOSITORY" will override "DefaultLocalRepository"
        )doc"
    );

    manager

        .def(
            "fetch_data_files_for_type",
            &Manager::fetchDataFilesForType,
            arg("model_type"),
            R"doc(
                Fetch data file from remote.

                Args:
                    model_type (EarthGravitationalModel::Type): A model type.
            )doc"
        )
        .def(
            "has_data_files_for_type",
            &Manager::hasDataFilesForType,
            arg("model_type"),
            R"doc(
                Returns true if manager has data file for the given model type.

                Args:
                    model_type (EarthGravitationalModel::Type): A model type.

                Returns:
                    bool: True if manager has data file for the given model type.
            )doc"
        )
        .def(
            "local_data_files_for_type",
            &Manager::localDataFilesForType,
            arg("model_type"),
            R"doc(
                Returns list of file objects for the given type.

                Args:
                    model_type (EarthGravitationalModel::Type): A model type.

                Returns:
                    list[File]: list of Files.
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

        ;
}
