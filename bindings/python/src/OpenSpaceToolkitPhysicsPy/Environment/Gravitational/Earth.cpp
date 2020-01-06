////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           bindings/python/src/OpenSpaceToolkitPhysicsPy/Environment/Gravitational/Earth.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Earth/Manager.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Earth.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitPhysicsPy_Environment_Gravitational_Earth ( )
{

    using namespace boost::python ;

    using ostk::core::fs::Directory ;

    using ostk::physics::units::Derived ;
    using ostk::physics::environment::gravitational::Earth ;
    using ostk::physics::environment::gravitational::earth::Manager ;

    scope in_Earth = class_<Earth>("Earth", init<const Earth::Type&, const Directory&>())

        .def(init<const Earth::Type&>())

        .def("get_type", &Earth::getType)
        .def("get_field_value_at", &Earth::getFieldValueAt)

    ;

    enum_<Earth::Type>("Type")

        .value("WGS84", Earth::Type::WGS84)
        .value("EGM84", Earth::Type::EGM84)
        .value("EGM96", Earth::Type::EGM96)
        .value("EGM2008", Earth::Type::EGM2008)

    ;

    boost::python::object module(boost::python::handle<>(boost::python::borrowed(PyImport_AddModule("ostk.physics.environment.gravitational.earth")))) ;

    boost::python::scope().attr("earth") = module ;

    boost::python::scope scope = module ;

    scope in_Manager = class_<Manager, boost::noncopyable>("Manager", no_init)

        .def("is_enabled", &Manager::isEnabled)
        .def("has_data_file_for_type", &Manager::hasDataFileForType)

        .def("get_local_repository", &Manager::getLocalRepository)
        .def("get_remote_url", &Manager::getRemoteUrl)
        .def("fetch_data_file_for_type", &Manager::fetchDataFileForType)
        .def("set_local_repository", &Manager::setLocalRepository)
        .def("set_remote_url", &Manager::setRemoteUrl)
        .def("enable", &Manager::enable)
        .def("disable", &Manager::disable)

        .def("get", &Manager::Get, return_value_policy<reference_existing_object>()).staticmethod("get")
        .def("default_local_repository", &Manager::DefaultLocalRepository).staticmethod("default_local_repository")
        .def("default_remote_url", &Manager::DefaultRemoteUrl).staticmethod("default_remote_url")

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
