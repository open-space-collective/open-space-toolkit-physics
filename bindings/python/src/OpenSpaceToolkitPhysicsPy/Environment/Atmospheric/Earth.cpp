////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           bindings/python/src/OpenSpaceToolkitPhysicsPy/Environment/Atmospheric/Earth.cpp
/// @author         Kyle Cochran <kyle.cochran@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/Manager.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitPhysicsPy_Environment_Atmospheric_Earth (        
  pybind11::module&aModule                                     )
{

    using namespace pybind11 ;

    using ostk::core::fs::Directory ;

    using ostk::physics::environment::atmospheric::Earth ;
    using ostk::physics::environment::atmospheric::earth::Manager ;

    {

        class_<Earth> earth_class(aModule, "Earth") ;

        earth_class

            .def
            (
                init<const Earth::Type&, const Directory&>(),
                arg("type"),
                arg("directory")
            )

            .def
            (
                init<const Earth::Type&>(),
                arg("type")
            )

            .def
            (
                "get_type",
                &Earth::getType
            )

            .def
            (
                "get_density_at",
                &Earth::getDensityAt,
                arg("position"),
                arg("instant")
            )

        ;

        enum_<Earth::Type>(earth_class, "EarthType")

            .value("Exponential", Earth::Type::Exponential)
        ;

    }

    // Create "earth" python submodule
    auto earth = aModule.def_submodule("earth") ;

    // Add __path__ attribute for "earth" submodule
    earth.attr("__path__") = "ostk.physics.environment.atmospheric.earth" ;

    /*class_<Manager>(earth, "Manager")

        .def("is_enabled", &Manager::isEnabled)

        .def
        (
            "has_data_file_for_type",
            &Manager::hasDataFileForType,
            arg("model_type")
        )

        .def("get_local_repository", &Manager::getLocalRepository)
        .def("get_remote_url", &Manager::getRemoteUrl)

        .def
        (
            "fetch_data_file_for_type",
            &Manager::fetchDataFileForType,
            arg("model_type")
        )

        .def
        (
            "set_local_repository",
            &Manager::setLocalRepository,
            arg("directory")
        )

        .def
        (
            "set_remote_url",
            &Manager::setRemoteUrl,
            arg("remote_url")
        )

        .def("enable", &Manager::enable)
        .def("disable", &Manager::disable)

        .def_static("get", &Manager::Get, return_value_policy::reference)
        .def_static("default_local_repository", &Manager::DefaultLocalRepository)
        .def_static("default_remote_url", &Manager::DefaultRemoteUrl)

    ;
    */

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
