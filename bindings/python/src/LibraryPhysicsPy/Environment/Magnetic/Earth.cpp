////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           LibraryPhysicsPy/Environment/Magnetic/Earth.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Environment/Magnetic/Earth/Manager.hpp>
#include <Library/Physics/Environment/Magnetic/Earth.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryPhysicsPy_Environment_Magnetic_Earth ( )
{

    using namespace boost::python ;

    using library::core::fs::Directory ;

    using library::physics::units::Derived ;
    using library::physics::environment::magnetic::Earth ;
    using library::physics::environment::magnetic::earth::Manager ;

    scope in_Earth = class_<Earth>("Earth", init<const Earth::Type&, const Directory&>())

        .def(init<const Earth::Type&>())

        .def("getType", &Earth::getType)
        .def("getFieldValueAt", &Earth::getFieldValueAt)

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
