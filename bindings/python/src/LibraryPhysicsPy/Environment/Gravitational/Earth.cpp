////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library ▸ Physics
/// @file           LibraryPhysicsPy/Environment/Gravitational/Earth.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Environment/Gravitational/Earth/Manager.hpp>
#include <Library/Physics/Environment/Gravitational/Earth.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryPhysicsPy_Environment_Gravitational_Earth ( )
{

    using namespace boost::python ;

    using library::core::fs::Directory ;

    using library::physics::units::Derived ;
    using library::physics::environment::gravitational::Earth ;
    using library::physics::environment::gravitational::earth::Manager ;

    scope in_Earth = class_<Earth>("Earth", init<const Earth::Type&, const Directory&>())

        .def(init<const Earth::Type&>())

        .def("getType", &Earth::getType)
        .def("getFieldValueAt", &Earth::getFieldValueAt)

    ;

    enum_<Earth::Type>("Type")

        .value("WGS84", Earth::Type::WGS84)
        .value("EGM84", Earth::Type::EGM84)
        .value("EGM96", Earth::Type::EGM96)
        .value("EGM2008", Earth::Type::EGM2008)

    ;

    scope in_Manager = class_<Manager, boost::noncopyable>("Manager", no_init)

        .def("isEnabled", &Manager::isEnabled)
        .def("hasDataFileForType", &Manager::hasDataFileForType)

        .def("getLocalRepository", &Manager::getLocalRepository)
        .def("getRemoteUrl", &Manager::getRemoteUrl)
        .def("fetchDataFileForType", &Manager::fetchDataFileForType)
        .def("setLocalRepository", &Manager::setLocalRepository)
        .def("setRemoteUrl", &Manager::setRemoteUrl)
        .def("enable", &Manager::enable)
        .def("disable", &Manager::disable)

        .def("Get", &Manager::Get, return_value_policy<reference_existing_object>()).staticmethod("Get")
        .def("DefaultLocalRepository", &Manager::DefaultLocalRepository).staticmethod("DefaultLocalRepository")
        .def("DefaultRemoteUrl", &Manager::DefaultRemoteUrl).staticmethod("DefaultRemoteUrl")

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
