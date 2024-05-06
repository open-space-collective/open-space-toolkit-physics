/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Data/Manager.hpp>

inline void OpenSpaceToolkitPhysicsPy_Data_Manager(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::physics::data::Manager;

    class_<Manager> manager(aModule, "Manager",
        R"doc(
            OSTk Data manager base class (thread-safe).

            The base manager defines methods for tracking and checking the manifest file.
        )doc"
    );

    manager
    
        .def("get_last_update_timestamp_for", &Manager::getLastUpdateTimestampFor, arg("data_name"),
            R"doc(
                Check if there are updates for data of a certain name. 

                Args:
                    data_name (String): Name of the data to query. This is the key for the data entry in the manifest file.

                Returns:
                    Instant: Instant indicating when the data was last updated on the remote, according to the manifest record. 
            )doc"
        )
        .def("get_remote_url", &Manager::getRemoteUrl,
            R"doc(
                Get the remote URL. This points to the base URL for the OSTk input data. 

                Returns:
                    URL: Remote URL.
            )doc"
        )
        .def("get_manifest_repository", &Manager::getManifestRepository,
            R"doc(
                Get the manifest repository. 

                Returns:
                    Directory: Manifest repository.
            )doc"
        )
        .def("get_remote_data_urls", &Manager::getRemoteDataUrls, arg("data_name"),
            R"doc(
                Get the remote data URL for a given data name.

                Args:
                    data_name (String): Name of the data. i.e. the key for the data entry in the manifest 

                Returns:
                    Array of URL: Array of URLs.
            )doc"
        )
        .def("get_manifest", &Manager::getManifest,
            R"doc(
                Get a copy of the current manifest file.

                Returns:
                    Manifest: Manifest.
            )doc"
        )

        .def("set_remote_url", &Manager::setRemoteUrl, arg("remote_url"),
            R"doc(
                Set the remote URL. 

                Args:
                    remote_url (Directory): Remote URL.
            )doc"
        )
        .def("set_manifest_repository", &Manager::setManifestRepository, arg("directory"),
            R"doc(
                Set the manifest repository. 

                Args:
                    directory (Directory): Manifest repository.
            )doc"
        )

        .def("find_remote_data_urls", &Manager::findRemoteDataUrls, arg("data_name_regex_pattern"),
            R"doc(
                Find remote URLs of data matching regular expression string. 

                Args:
                    data_name_regex_pattern (String): A regular expression string

                Returns:
                    Array of URL: Array of URLs.
            )doc"
        )
        .def("load_manifest", &Manager::loadManifest, arg("manifest"),
            R"doc(
                Load a new manifest file.

                Args:
                    manifest (Manifest): Manifest.
            )doc"
        )
        .def("manifest_file_exists", &Manager::manifestFileExists,
            R"doc(
                Return true if a manifest file already exists in the directory. 

                Returns:
                    bool: True if the manifest file exists.
            )doc"
        )
        .def("reset", &Manager::reset,
            R"doc(
                Reset the manager.

                Unload the manifest file and forget manifest age. 
            )doc"
        )

        .def_static("get", &Manager::Get, return_value_policy::reference,
            R"doc(
                Get manager singleton.

                Returns:
                    Manager: Manager instance.
            )doc"
        )
        .def_static("default_remote_url", &Manager::DefaultRemoteUrl,
            R"doc(
                Get the default remote URL for data fetching. 

                Returns:
                    URL: Default remote URL.
            )doc"
        )
        .def_static("default_manifest_repository", &Manager::DefaultManifestRepository,
            R"doc(
                Get the default manifest repository. 

                Returns:
                    Directory: Default manifest repository.
            )doc"
        )

        ;
}
