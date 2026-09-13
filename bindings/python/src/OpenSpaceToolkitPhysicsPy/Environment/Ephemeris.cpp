/// Apache License 2.0

#include <nanobind/trampoline.h>

#include <OpenSpaceToolkit/Physics/Environment/Ephemeris.hpp>

#include <OpenSpaceToolkitPhysicsPy/Environment/Ephemeris/Analytical.cpp>
#include <OpenSpaceToolkitPhysicsPy/Environment/Ephemeris/SPICE.cpp>

using namespace nanobind;

using ostk::core::type::Shared;

using ostk::physics::coordinate::Frame;
using ostk::physics::environment::Ephemeris;

class PyEphemeris : public Ephemeris
{
   public:
    NB_TRAMPOLINE(Ephemeris, 3);

    // Trampoline (need one for each virtual function)

    Ephemeris* clone() const override
    {
        NB_OVERRIDE_PURE_NAME("clone", clone);
    }

    bool isDefined() const override
    {
        NB_OVERRIDE_PURE_NAME("is_defined", isDefined);
    }

    Shared<const Frame> accessFrame() const override
    {
        NB_OVERRIDE_PURE_NAME("access_frame", accessFrame);
    }
};

inline void OpenSpaceToolkitPhysicsPy_Environment_Ephemeris(nanobind::module_& aModule)
{
    class_<Ephemeris, PyEphemeris>(
        aModule,
        "Ephemeris",
        R"doc(
            Abstract base class for ephemeris models.

            An ephemeris provides the position and orientation of celestial objects
            as a function of time. This is the base class for various ephemeris
            implementations including Analytical and SPICE-based ephemerides.

            See Also:
                Analytical: Analytical ephemeris using reference frames.
                SPICE: SPICE Toolkit-based ephemeris.
        )doc"
    )

        .def(
            "is_defined",
            &Ephemeris::isDefined,
            R"doc(
                Check if the ephemeris is defined.

                Returns:
                    bool: True if the ephemeris is defined, False otherwise.
            )doc"
        )
        .def(
            "access_frame",
            &Ephemeris::accessFrame,
            R"doc(
                Access the reference frame associated with this ephemeris.

                Returns:
                    Frame: The reference frame.
            )doc"
        )

        ;

    // Create "ephemeris" python submodule
    auto ephemeris = aModule.def_submodule("ephemeris");

    // Add objects to python "ephemeris" submodules
    OpenSpaceToolkitPhysicsPy_Environment_Ephemeris_Analytical(ephemeris);
    OpenSpaceToolkitPhysicsPy_Environment_Ephemeris_SPICE(ephemeris);
}
