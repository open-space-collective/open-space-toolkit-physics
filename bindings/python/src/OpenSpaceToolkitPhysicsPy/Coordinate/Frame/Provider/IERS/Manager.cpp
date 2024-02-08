/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/IERS/Manager.hpp>

inline void OpenSpaceToolkitPhysicsPy_Coordinate_Frame_Provider_IERS_Manager(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Shared;

    using ostk::physics::coord::frame::provider::iers::Manager;

    class_<Manager> manager(aModule, "Manager");

    manager

        .def("get_mode", &Manager::getMode)
        .def("get_local_repository", &Manager::getLocalRepository)
        .def("get_bulletin_a_directory", &Manager::getBulletinADirectory)
        .def("get_finals_2000a_directory", &Manager::getFinals2000ADirectory)
        .def("get_bulletin_a", &Manager::getBulletinA)
        .def("get_finals_2000a", &Manager::getFinals2000A)
        .def("get_polar_motion_at", &Manager::getPolarMotionAt, arg("instant"))
        .def("get_ut1_minus_utc_at", &Manager::getUt1MinusUtcAt, arg("instant"))
        .def("get_lod_at", &Manager::getLodAt)

        .def("set_mode", &Manager::setMode, arg("mode"))
        .def("set_local_repository", &Manager::setLocalRepository, arg("directory"))

        .def("load_bulletin_a", &Manager::loadBulletinA, arg("bulletin_a"))
        .def("load_finals_2000a", &Manager::loadFinals2000A, arg("finals_2000a"))

        .def("fetch_latest_bulletin_a", &Manager::fetchLatestBulletinA)
        .def("fetch_latest_finals_2000a", &Manager::fetchLatestFinals2000A)

        .def("reset", &Manager::reset)
        .def("clear_local_repository", &Manager::clearLocalRepository)

        .def_static("get", &Manager::Get, return_value_policy::reference)
        .def_static("default_mode", &Manager::DefaultMode)
        .def_static("default_local_repository", &Manager::DefaultLocalRepository)
        .def_static("default_local_repository_lock_timeout", &Manager::DefaultLocalRepositoryLockTimeout)

        ;

    enum_<Manager::Mode>(manager, "Mode")

        .value("Manual", Manager::Mode::Manual)
        .value("Automatic", Manager::Mode::Automatic)

        ;
}
