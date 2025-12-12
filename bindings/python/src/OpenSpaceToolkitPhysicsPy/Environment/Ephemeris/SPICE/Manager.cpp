/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Environment/Ephemeris/SPICE/Manager.hpp>
#include <OpenSpaceToolkit/Physics/Manager.hpp>

inline void OpenSpaceToolkitPhysicsPy_Environment_Ephemeris_SPICE_Manager(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::container::Array;
    using ostk::core::filesystem::Path;

    using ostk::physics::environment::ephemeris::spice::Kernel;
    using ostk::physics::environment::ephemeris::spice::Manager;
    using BaseManager = ostk::physics::Manager;

    class_<Manager, BaseManager>(
        aModule,
        "Manager",
        R"doc(
            SPICE Toolkit kernel manager.

            Fetches and manages SPICE kernels. The manager can operate in two modes:
            - Automatic: Fetches kernels from remote repositories if not present locally.
            - Manual: Only uses locally available kernels.

            The following environment variables can be defined:
            - "OSTK_PHYSICS_ENVIRONMENT_EPHEMERIS_SPICE_MANAGER_MODE" overrides the default mode.
            - "OSTK_PHYSICS_ENVIRONMENT_EPHEMERIS_SPICE_MANAGER_LOCAL_REPOSITORY" overrides the default local repository.

            Note:
                This class is a singleton. Use Manager.get() to access the instance.

            Example:
                >>> from ostk.physics.environment.ephemeris.spice import Manager
                >>> manager = Manager.get()
                >>> manager.get_mode()
        )doc"
    )

        .def(
            "fetch_kernel",
            &Manager::fetchKernel,
            arg("kernel"),
            R"doc(
                Fetch a kernel from the remote repository.

                Args:
                    kernel (Kernel): The kernel to fetch.
            )doc"
        )
        .def(
            "fetch_matching_kernels",
            &Manager::fetchMatchingKernels,
            arg("regex_string"),
            R"doc(
                Fetch kernels matching a regular expression.

                Args:
                    regex_string (str): A regular expression to match kernel names.

                Returns:
                    list[Kernel]: An array of matching kernels.
            )doc"
        )
        .def(
            "find_kernel_paths",
            &Manager::findKernelPaths,
            arg("regex_string"),
            R"doc(
                Find kernel paths matching a regular expression in the local repository.

                Args:
                    regex_string (str): A regular expression to match kernel paths.

                Returns:
                    list[Path]: An array of matching kernel paths.
            )doc"
        )
        .def(
            "find_kernel",
            &Manager::findKernel,
            arg("regex_string"),
            R"doc(
                Find a kernel matching a regular expression.

                Searches locally first, then remotely. Always returns the first match.

                Args:
                    regex_string (str): A regular expression to match kernel names.

                Returns:
                    Kernel: The first matching kernel.
            )doc"
        )

        .def_static(
            "get",
            &Manager::Get,
            return_value_policy::reference,
            R"doc(
                Get the manager singleton.

                Returns:
                    Manager: Reference to the manager singleton.
            )doc"
        )

        ;
}
