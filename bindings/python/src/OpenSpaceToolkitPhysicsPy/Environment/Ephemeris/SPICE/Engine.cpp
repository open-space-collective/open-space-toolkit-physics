/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Environment/Ephemeris/SPICE/Engine.hpp>

inline void OpenSpaceToolkitPhysicsPy_Environment_Ephemeris_SPICE_Engine(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::container::Array;
    using ostk::core::type::Shared;

    using ostk::physics::coordinate::Frame;
    using ostk::physics::environment::ephemeris::SPICE;
    using ostk::physics::environment::ephemeris::spice::Engine;
    using ostk::physics::environment::ephemeris::spice::Kernel;

    class_<Engine>(
        aModule,
        "Engine",
        R"doc(
            SPICE Toolkit engine.

            The Engine is a singleton that manages SPICE kernel loading and provides
            access to SPICE functionality. It handles kernel loading/unloading and
            provides frame information for SPICE objects.

            Note:
                This class is a singleton. Use Engine.get() to access the instance.

            Example:
                >>> from ostk.physics.environment.ephemeris.spice import Engine
                >>> engine = Engine.get()
                >>> engine.reset()
        )doc"
    )

        .def("__str__", &(shiftToString<Engine>))
        .def("__repr__", &(shiftToString<Engine>))

        .def(
            "reset",
            &Engine::reset,
            R"doc(
                Reset the engine.

                Unloads all kernels and clears the cache.
            )doc"
        )
        .def(
            "get_frame_of",
            &Engine::getFrameOf,
            arg("spice_object"),
            R"doc(
                Get the reference frame of a SPICE object.

                Args:
                    spice_object (SPICE.Object): The SPICE object.

                Returns:
                    Frame: The reference frame of the SPICE object.
            )doc"
        )
        .def(
            "is_kernel_loaded",
            &Engine::isKernelLoaded,
            arg("kernel"),
            R"doc(
                Check if a kernel is loaded.

                Args:
                    kernel (Kernel): The kernel to check.

                Returns:
                    bool: True if the kernel is loaded, False otherwise.
            )doc"
        )
        .def(
            "load_kernel",
            &Engine::loadKernel,
            arg("kernel"),
            R"doc(
                Load a kernel.

                Args:
                    kernel (Kernel): The kernel to load.
            )doc"
        )
        .def(
            "unload_kernel",
            &Engine::unloadKernel,
            arg("kernel"),
            R"doc(
                Unload a kernel.

                Args:
                    kernel (Kernel): The kernel to unload.
            )doc"
        )

        .def_static(
            "get",
            &Engine::Get,
            return_value_policy::reference,
            R"doc(
                Get the engine singleton.

                Returns:
                    Engine: Reference to the engine singleton.
            )doc"
        )
        .def_static(
            "default_kernels",
            &Engine::DefaultKernels,
            R"doc(
                Get the default kernels.

                Returns:
                    list[Kernel]: The default kernels.
            )doc"
        )

        ;
}
