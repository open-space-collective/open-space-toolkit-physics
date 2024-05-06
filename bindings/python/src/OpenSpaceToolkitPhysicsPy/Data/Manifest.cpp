/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Data/Manifest.hpp>

inline void OpenSpaceToolkitPhysicsPy_Data_Manifest(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::physics::data::Manifest;

    class_<Manifest> ManifestClass(aModule, "Manifest",
        R"doc(
            Data class for the OSTk Data Manifest.

        )doc"
    );

    ManifestClass

        .def("__str__", &(shiftToString<Manifest>))
        .def("__repr__", &(shiftToString<Manifest>))

        .def("is_defined", &Manifest::isDefined,
            R"doc(
                Check if the manifest is defined.

                Returns:
                    bool: True if defined.
            )doc"
        )

        .def("get_last_modified_timestamp", &Manifest::getLastModifiedTimestamp,
            R"doc(
                Get last update timestamp.

                Returns:
                    Instant: Instant indicating when the manifest was last updated based on file modification time 
            )doc"
        )
        .def("get_last_update_timestamp_for", &Manifest::getLastUpdateTimestampFor, arg("data_name"),
            R"doc(
                Get last update timestamp for data. 

                Args:
                    data_name (String): A data name 

                Returns:
                    Instant: Last update instant for data
            )doc"
        )
        .def("get_next_update_check_timestamp_for", &Manifest::getNextUpdateCheckTimestampFor, arg("data_name"),
            R"doc(
                Get next update check timestamp for data. 

                Args:
                    data_name (String): A data name 

                Returns:
                    Instant: Next update check instant for data
            )doc"
        )
        .def("get_remote_data_urls", &Manifest::getRemoteDataUrls, arg("base_url"), arg("data_name"),
            R"doc(
                Get the remote data URL for a given data name.

                Args:
                    base_url (URL): A base URL for remote data 
                    data_name (String): Name of the data. i.e. the key for the data entry in the manifest 

                Returns:
                    Array of URL: Array of remote data URLs 
            )doc"
        )

        .def("find_remote_data_urls", &Manifest::findRemoteDataUrls, arg("base_url"), arg("data_name_regex_pattern"),
            R"doc(
                Return remote data URLs the for data items matching the given name regex string. 

                Args:
                    base_url (URL): A base URL for remote data 
                    data_name_regex_pattern (String): A data name regex string

                Returns:
                    Array of URL: Array of remote data URLs 
            )doc"
        )

        .def_static("undefined", &Manifest::Undefined,
            R"doc(
                Create an undefined manifest.

                Returns:
                    Manifest: Undefined manifest.
            )doc"
        )
        .def_static("load", &Manifest::Load, arg("file"),
            R"doc(
                Load a manifest from a file.

                Args:
                    file (File): A manifest file

                Returns:
                    Manifest: Manifest
            )doc"
        )

        ;
}
