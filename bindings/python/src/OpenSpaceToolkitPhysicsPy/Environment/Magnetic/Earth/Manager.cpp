/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Environment/Magnetic/Earth/Manager.hpp>
#include <OpenSpaceToolkit/Physics/Manager.hpp>

inline void OpenSpaceToolkitPhysicsPy_Environment_Magnetic_Earth_Manager(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::physics::environment::magnetic::earth::Manager;
    using BaseManager = ostk::physics::Manager;

    class_<Manager, BaseManager> manager(
        aModule,
        "Manager",
        R"doc(
            Earth magnetic model data manager

            Fetches and manages necessary magnetic model data files.

            The following environment variables can be defined:

            - "OSTK_PHYSICS_ENVIRONMENT_MAGNETIC_EARTH_MANAGER_ENABLED" will override "DefaultEnabled"
            - "OSTK_PHYSICS_ENVIRONMENT_MAGNETIC_EARTH_MANAGER_LOCAL_REPOSITORY" will override "DefaultLocalRepository"
        )doc"
    );

    manager

        .def(
            "fetch_data_files_for_type",
            &Manager::fetchDataFilesForType,
            arg("model_type"),
            R"doc(
                Fetch data file from remote

                Args:
                    model_type (EarthMagneticModel.Type): Model type
            )doc"
        )
        .def(
            "has_data_files_for_type",
            &Manager::hasDataFilesForType,
            arg("model_type"),
            R"doc(
                Check if data files are available for the given type

                Args:
                    model_type (EarthMagneticModel.Type): Model type

                Returns:
                    bool: True if data files are available for the given type
            )doc"
        )
        .def(
            "local_data_files_for_type",
            &Manager::localDataFilesForType,
            arg("model_type"),
            R"doc(
                Get local data files for the given type

                Args:
                    model_type (EarthMagneticModel.Type): Model type

                Returns:
                    list[File]: Local data files
            )doc"
        )

        .def_static(
            "get",
            &Manager::Get,
            return_value_policy::reference,
            R"doc(
                Get manager singleton

                Returns:
                    Manager: Reference to manager
            )doc"
        )

        ;
}
