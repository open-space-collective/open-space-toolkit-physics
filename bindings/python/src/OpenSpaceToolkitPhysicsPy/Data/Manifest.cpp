/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Data/Manifest.hpp>

inline void OpenSpaceToolkitPhysicsPy_Data_Manifest(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::physics::data::Manifest;

    class_<Manifest> ManifestClass(aModule, "Manifest");

    ManifestClass

        .def("__str__", &(shiftToString<Manifest>))
        .def("__repr__", &(shiftToString<Manifest>))

        .def("is_defined", &Manifest::isDefined)

        .def("get_last_modified_timestamp", &Manifest::getLastModifiedTimestamp)
        .def("get_last_update_timestamp_for", &Manifest::getLastUpdateTimestampFor, arg("data_name"))
        .def("get_next_update_check_timestamp_for", &Manifest::getNextUpdateCheckTimestampFor, arg("data_name"))
        .def("get_remote_data_urls", &Manifest::getRemoteDataUrls, arg("base_url"), arg("data_name"))

        .def("find_remote_data_urls", &Manifest::findRemoteDataUrls, arg("base_url"), arg("data_name_regex_pattern"))

        .def_static("undefined", &Manifest::Undefined)
        .def_static("load", &Manifest::Load, arg("file"))

        ;
}
