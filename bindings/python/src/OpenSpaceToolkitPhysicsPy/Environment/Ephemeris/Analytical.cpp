/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Environment/Ephemeris/Analytical.hpp>

inline void OpenSpaceToolkitPhysicsPy_Environment_Ephemeris_Analytical(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Shared;

    using ostk::physics::coordinate::Frame;
    using ostk::physics::environment::Ephemeris;
    using ostk::physics::environment::ephemeris::Analytical;

    class_<Analytical, Shared<Analytical>, Ephemeris>(
        aModule,
        "Analytical",
        R"doc(
            Analytical ephemeris.

            An analytical ephemeris that uses a reference frame to provide
            position and orientation information. This is typically used
            for celestial objects whose positions can be computed analytically
            from the reference frame transformations.

            Args:
                frame (Frame): The reference frame for this ephemeris.

            Example:
                >>> from ostk.physics.environment.ephemeris import Analytical
                >>> from ostk.physics.coordinate import Frame
                >>> analytical = Analytical(Frame.GCRF())
        )doc"
    )

        .def(
            init<const Shared<const Frame>&>(),
            arg("frame"),
            R"doc(
                Constructor.

                Args:
                    frame (Frame): The reference frame for this ephemeris.
            )doc"
        )

        .def(
            "is_defined",
            &Analytical::isDefined,
            R"doc(
                Check if the analytical ephemeris is defined.

                Returns:
                    bool: True if the ephemeris is defined, False otherwise.
            )doc"
        )
        .def(
            "access_frame",
            &Analytical::accessFrame,
            R"doc(
                Access the reference frame associated with this ephemeris.

                Returns:
                    Frame: The reference frame.
            )doc"
        )

        ;
}
