////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           bindings/python/src/OpenSpaceToolkitPhysicsPy/Environment/Magnetic/Earth.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Physics/Environment/Magnetic/Earth/Manager.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Magnetic/Earth.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitPhysicsPy_Environment_Magnetic_Earth ( )
{

    using namespace boost::python ;

    using ostk::core::fs::Directory ;

    using ostk::physics::units::Derived ;
    using ostk::physics::environment::magnetic::Earth ;
    using ostk::physics::environment::magnetic::earth::Manager ;

    scope in_Earth = class_<Earth>("Earth", init<const Earth::Type&, const Directory&>())

        .def(init<const Earth::Type&>())

        .def("get_type", &Earth::getType)
        .def("get_field_value_at", &Earth::getFieldValueAt)

    ;

    enum_<Earth::Type>("Type")

        .value("Dipole", Earth::Type::Dipole)
        .value("EMM2010", Earth::Type::EMM2010)
        .value("EMM2015", Earth::Type::EMM2015)
        .value("EMM2017", Earth::Type::EMM2017)
        .value("IGRF11", Earth::Type::IGRF11)
        .value("IGRF12", Earth::Type::IGRF12)
        .value("WMM2010", Earth::Type::WMM2010)
        .value("WMM2015", Earth::Type::WMM2015)

    ;

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
