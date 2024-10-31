/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Manager.hpp>

inline void OpenSpaceToolkitPhysicsPy_Manager(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::physics::Manager;

    class_<Manager> manager_class(
        aModule,
        "Manager",
        R"doc(
            Manager

            Abstract Base Manager class. 
        )doc"
    );

    enum_<Manager::Mode>(manager_class, "Mode")
        .value("Manual", Manager::Mode::Manual)
        .value("Automatic", Manager::Mode::Automatic)

        ;

    manager_class

        .def(
            "get_mode",
            &Manager::getMode,
            R"doc(
                Get the manager mode.

                Returns:
                    Mode: Manager mode.
            )doc"
        )
        .def(
            "get_local_repository",
            &Manager::getLocalRepository,
            R"doc(
                Get the local repository.

                Returns:
                    Directory: Local repository.
            )doc"
        )
        .def(
            "get_local_repository_lock_timeout",
            &Manager::getLocalRepositoryLockTimeout,
            R"doc(
                Get the local repository lock timeout.

                Returns:
                    Duration: Local repository lock timeout.
            )doc"
        )
        .def(
            "set_mode",
            &Manager::setMode,
            arg("mode"),
            R"doc(
                Set the manager mode.

                Args:
                    mode (Mode): Manager mode.
            )doc"
        )
        .def(
            "set_local_repository",
            &Manager::setLocalRepository,
            arg("directory"),
            R"doc(
                Set the local repository.

                Args:
                    directory (Directory): Local repository.
            )doc"
        )
        .def(
            "reset",
            &Manager::reset,
            R"doc(
                Reset the manager.
            )doc"
        )
        .def(
            "clear_local_repository",
            &Manager::clearLocalRepository,
            R"doc(
                Clear the local repository.
            )doc"
        )

        ;
}
