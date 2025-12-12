/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Environment/Ephemeris/SPICE.hpp>

#include <OpenSpaceToolkitPhysicsPy/Environment/Ephemeris/SPICE/Engine.cpp>
#include <OpenSpaceToolkitPhysicsPy/Environment/Ephemeris/SPICE/Kernel.cpp>
#include <OpenSpaceToolkitPhysicsPy/Environment/Ephemeris/SPICE/Manager.cpp>

inline void OpenSpaceToolkitPhysicsPy_Environment_Ephemeris_SPICE(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Shared;

    using ostk::physics::coordinate::Frame;
    using ostk::physics::environment::Ephemeris;
    using ostk::physics::environment::ephemeris::SPICE;

    class_<SPICE, Shared<SPICE>, Ephemeris> spice_class(
        aModule,
        "SPICE",
        R"doc(
            SPICE Toolkit ephemeris.

            Provides ephemeris data using NASA's SPICE Toolkit. SPICE (Spacecraft Planet
            Instrument C-matrix Events) is an observation geometry information system
            used by NASA's planetary science missions.

            The SPICE ephemeris supports various celestial objects including the Sun,
            planets, and the Moon.

            Args:
                object (SPICE.Object): The SPICE object for this ephemeris.

            Example:
                >>> from ostk.physics.environment.ephemeris import SPICE
                >>> spice_ephemeris = SPICE(SPICE.Object.Earth)

            See Also:
                https://naif.jpl.nasa.gov/naif/
        )doc"
    );

    enum_<SPICE::Object>(spice_class, "Object")

        .value("Undefined", SPICE::Object::Undefined, "Undefined")
        .value("Sun", SPICE::Object::Sun, "Sun")
        .value("Mercury", SPICE::Object::Mercury, "Mercury")
        .value("Earth", SPICE::Object::Earth, "Earth")
        .value("Mars", SPICE::Object::Mars, "Mars")
        .value("Jupiter", SPICE::Object::Jupiter, "Jupiter")
        .value("Saturn", SPICE::Object::Saturn, "Saturn")
        .value("Uranus", SPICE::Object::Uranus, "Uranus")
        .value("Neptune", SPICE::Object::Neptune, "Neptune");

    spice_class

        .def(
            init<const SPICE::Object&>(),
            arg("object"),
            R"doc(
                Constructor.

                Args:
                    object (SPICE.Object): The SPICE object for this ephemeris.
            )doc"
        )

        .def(
            "is_defined",
            &SPICE::isDefined,
            R"doc(
                Check if the SPICE ephemeris is defined.

                Returns:
                    bool: True if the ephemeris is defined, False otherwise.
            )doc"
        )
        .def(
            "access_frame",
            &SPICE::accessFrame,
            R"doc(
                Access the reference frame of the SPICE object.

                Returns:
                    Frame: The reference frame.
            )doc"
        )

        .def_static(
            "string_from_object",
            &SPICE::StringFromObject,
            arg("object"),
            R"doc(
                Convert a SPICE object to its string representation.

                Args:
                    object (SPICE.Object): The SPICE object.

                Returns:
                    str: String representation of the SPICE object.
            )doc"
        )

        ;

    // Create "spice" python submodule
    auto spice = aModule.def_submodule("spice");

    // Add objects to python "spice" submodules
    OpenSpaceToolkitPhysicsPy_Environment_Ephemeris_SPICE_Kernel(spice);
    OpenSpaceToolkitPhysicsPy_Environment_Ephemeris_SPICE_Engine(spice);
    OpenSpaceToolkitPhysicsPy_Environment_Ephemeris_SPICE_Manager(spice);
}
