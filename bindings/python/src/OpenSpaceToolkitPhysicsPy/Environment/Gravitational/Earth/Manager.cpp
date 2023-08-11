/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Earth/Manager.hpp>

inline void OpenSpaceToolkitPhysicsPy_Environment_Gravitational_Earth_Manager(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::physics::environment::gravitational::earth::Manager;

    class_<Manager> manager(aModule, "Manager");

    manager

        .def("get_mode", &Manager::getMode)
        .def("set_mode", &Manager::setMode, arg("mode"))
        .def_static("default_mode", &Manager::DefaultMode)

        .def("get_local_repository", &Manager::getLocalRepository)
        .def("set_local_repository", &Manager::setLocalRepository, arg("directory"))
        .def_static("default_local_repository", &Manager::DefaultLocalRepository)
        .def_static("default_local_repository_lock_timeout", &Manager::DefaultLocalRepositoryLockTimeout)

        .def("fetch_data_files_for_type", &Manager::fetchDataFilesForType, arg("model_type"))
        .def("has_data_files_for_type", &Manager::hasDataFilesForType, arg("model_type"))
        .def("local_data_files_for_type", &Manager::localDataFilesForType, arg("model_type"))

        .def_static("get", &Manager::Get, return_value_policy::reference)

        ;

    enum_<Manager::Mode>(manager, "Mode")

        .value("Manual", Manager::Mode::Manual)
        .value("Automatic", Manager::Mode::Automatic)

        ;
}
