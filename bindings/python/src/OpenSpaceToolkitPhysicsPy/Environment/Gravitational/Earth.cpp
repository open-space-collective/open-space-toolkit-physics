////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           bindings/python/src/OpenSpaceToolkitPhysicsPy/Environment/Gravitational/Earth.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Earth/Manager.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Earth.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitPhysicsPy_Environment_Gravitational_Earth (        pybind11::module&aModule                                     )
{

    using namespace pybind11 ;

    using ostk::core::types::Integer ;
    using ostk::core::fs::Directory ;

    using ostk::physics::units::Derived ;
    using ostk::physics::environment::gravitational::Earth ;
    using ostk::physics::environment::gravitational::earth::Manager ;

    {

        class_<Earth> earth_class(aModule, "Earth") ;

        earth_class.def(init<const Earth::Type&, const Directory&>())

            .def(init<const Earth::Type&>())
            .def(init<const Earth::Type&, const Directory&, const Integer&, const Integer&>())

            .def("get_type", &Earth::getType)
            .def("get_field_value_at", &Earth::getFieldValueAt)

        ;

        enum_<Earth::Type>(earth_class, "EarthType")

            .value("spherical", Earth::Type::Spherical)
            .value("WGS84", Earth::Type::WGS84)
            .value("EGM84", Earth::Type::EGM84)
            .value("EGM96", Earth::Type::EGM96)
            .value("EGM2008", Earth::Type::EGM2008)

        ;

    }

    // Create "earth" python submodule
    auto earth = aModule.def_submodule("earth") ;

    // Add __path__ attribute for "earth" submodule
    earth.attr("__path__") = "ostk.physics.environment.gravitational.earth" ;

    class_<Manager>(earth, "Manager")

        .def("is_enabled", &Manager::isEnabled)
        .def("has_data_file_for_type", &Manager::hasDataFileForType)

        .def("get_local_repository", &Manager::getLocalRepository)
        .def("get_remote_url", &Manager::getRemoteUrl)
        .def("fetch_data_file_for_type", &Manager::fetchDataFileForType)
        .def("set_local_repository", &Manager::setLocalRepository)
        .def("set_remote_url", &Manager::setRemoteUrl)
        .def("enable", &Manager::enable)
        .def("disable", &Manager::disable)

        // .def_static("get", &Manager::Get, return_value_policy<reference_existing_object>())
        .def_static("get", &Manager::Get, return_value_policy::reference)
        .def_static("default_local_repository", &Manager::DefaultLocalRepository)
        .def_static("default_remote_url", &Manager::DefaultRemoteUrl)

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
