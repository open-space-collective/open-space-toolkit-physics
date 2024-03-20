/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Data/Manager.hpp>

inline void OpenSpaceToolkitPhysicsPy_Data_Manager(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::physics::data::Manager;

    class_<Manager> manager(aModule, "Manager");

    manager.def("get_last_update_timestamp_for", &Manager::getLastUpdateTimestampFor, arg("data_name"))
        .def("get_remote_url", &Manager::getRemoteUrl)
        .def("get_manifest_repository", &Manager::getManifestRepository)
        .def("get_remote_data_urls", &Manager::getRemoteDataUrls, arg("data_name"))
        .def("get_manifest", &Manager::getManifest)

        .def("set_remote_url", &Manager::setRemoteUrl, arg("remote_url"))
        .def("set_manifest_repository", &Manager::setManifestRepository, arg("directory"))

        .def("find_remote_data_urls", &Manager::findRemoteDataUrls, arg("data_name_regex_pattern"))
        .def("load_manifest", &Manager::loadManifest, arg("manifest"))
        .def("manifest_file_exists", &Manager::manifestFileExists)
        .def("reset", &Manager::reset)

        .def_static("get", &Manager::Get, return_value_policy::reference)
        .def_static("default_remote_url", &Manager::DefaultRemoteUrl)
        .def_static("default_manifest_repository", &Manager::DefaultManifestRepository)

        ;
}
