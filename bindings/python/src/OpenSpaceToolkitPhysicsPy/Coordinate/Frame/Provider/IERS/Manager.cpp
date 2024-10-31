/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/IERS/Manager.hpp>

#include <OpenSpaceToolkit/Physics/Manager.cpp>

inline void OpenSpaceToolkitPhysicsPy_Coordinate_Frame_Provider_IERS_Manager(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Shared;

    using ostk::physics::coordinate::frame::provider::iers::Manager;
    using BaseManager = ostk::physics::Manager;

    class_<Manager, BaseManager> manager(
        aModule,
        "Manager",
        R"doc(
            IERS bulletins manager (thread-safe)

            The following environment variables can be defined:

            - "OSTK_PHYSICS_COORDINATE_FRAME_PROVIDER_IERS_MANAGER_MODE" will override
            "DefaultMode"
            - "OSTK_PHYSICS_COORDINATE_FRAME_PROVIDER_IERS_MANAGER_LOCAL_REPOSITORY" will override
            "DefaultLocalRepository"
            - "OSTK_PHYSICS_COORDINATE_FRAME_PROVIDER_IERS_MANAGER_LOCAL_REPOSITORY_LOCK_TIMEOUT"
            will override "DefaultLocalRepositoryLockTimeout"

            :reference: https://www.iers.org/IERS/EN/DataProducts/EarthOrientationData/eop.html

        )doc"
    );

    manager

        .def(
            "get_bulletin_a_directory",
            &Manager::getBulletinADirectory,
            R"doc(
                Get Bulletin A directory.

                Returns:
                    Directory: Bulletin A directory.
            )doc"
        )
        .def(
            "get_finals_2000a_directory",
            &Manager::getFinals2000ADirectory,
            R"doc(
                Get Finals 2000A directory.

                Returns:
                    Directory: Finals 2000A directory.
            )doc"
        )
        .def(
            "get_bulletin_a",
            &Manager::getBulletinA,
            R"doc(
                Get Bulletin A.

                Returns:
                    BulletinA: Bulletin A.
            )doc"
        )
        .def(
            "get_finals_2000a",
            &Manager::getFinals2000A,
            R"doc(
                Get Finals 2000A.

                Returns:
                    Finals2000A: Finals 2000A.
            )doc"
        )
        .def(
            "get_polar_motion_at",
            &Manager::getPolarMotionAt,
            arg("instant"),
            R"doc(
                Get polar motion at instant.

                Args:
                    instant (Instant): Instant.

                Returns:
                    np.ndarray: Polar motion.
            )doc"
        )
        .def(
            "get_ut1_minus_utc_at",
            &Manager::getUt1MinusUtcAt,
            arg("instant"),
            R"doc(
                Get UT1 - UTC at instant.

                Args:
                    instant (Instant): Instant.

                Returns:
                    float: UT1 - UTC [sec].
            )doc"
        )
        .def(
            "get_lod_at",
            &Manager::getLodAt,
            arg("instant"),
            R"doc(
                Get length of day at instant.

                Args:
                    instant (Instant): Instant.

                Returns:
                    float: Length of day [ms].
            )doc"
        )

        .def(
            "load_bulletin_a",
            &Manager::loadBulletinA,
            arg("bulletin_a"),
            R"doc(
                Load Bulletin A.

                Returns:
                    bulletin_a (BulletinA): Bulletin A.
            )doc"
        )
        .def(
            "load_finals_2000a",
            &Manager::loadFinals2000A,
            arg("finals_2000a"),
            R"doc(
                Load Finals 2000A.

                Returns:
                    finals_2000a (Finals2000A): Finals 2000A.
            )doc"
        )

        .def(
            "fetch_latest_bulletin_a",
            &Manager::fetchLatestBulletinA,
            R"doc(
                Fetch latest Bulletin A file.

                Returns:
                    File: Latest Bulletin A file.
            )doc"
        )
        .def(
            "fetch_latest_finals_2000a",
            &Manager::fetchLatestFinals2000A,
            R"doc(
                Fetch latest Finals 2000A file.

                Returns:
                    File: Latest Finals 2000A file.
            )doc"
        )

        .def_static(
            "get",
            &Manager::Get,
            return_value_policy::reference,
            R"doc(
                Get manager singleton.

                Returns:
                    Manager: Reference to manager.
            )doc"
        )

        ;
}
