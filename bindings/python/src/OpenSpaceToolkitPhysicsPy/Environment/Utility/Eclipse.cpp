/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Environment/Utility/Eclipse.hpp>

inline void OpenSpaceToolkitPhysicsPy_Environment_Utility_Eclipse(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::container::Array;
    using ostk::core::type::Real;
    using ostk::core::type::String;

    using ostk::physics::coordinate::Position;
    using ostk::physics::Environment;
    using ostk::physics::environment::object::Celestial;
    using ostk::physics::time::Duration;
    using ostk::physics::time::Instant;
    using ostk::physics::time::Interval;

    using ostk::physics::environment::utilities::Eclipse;
    using ostk::physics::environment::utilities::EclipsePhase;

    class_<EclipsePhase> eclipse_phase_class(
        aModule,
        "EclipsePhase",
        R"doc(
            Phase of an eclipse.
            
            This class represents a single phase of an eclipse, including the region type
            (umbra or penumbra), the time interval, and whether the phase is complete.
        )doc"
    );

    enum_<EclipsePhase::Region>(eclipse_phase_class, "Region")
        .value("Umbra", EclipsePhase::Region::Umbra)
        .value("Penumbra", EclipsePhase::Region::Penumbra)

        ;

    eclipse_phase_class

        .def(
            init<const EclipsePhase::Region&, const Interval&, const bool&>(),
            arg("region"),
            arg("interval"),
            arg("is_complete"),
            R"doc(
                Constructor

                Args:
                    region (EclipsePhase.Region): The region of the eclipse phase (Umbra or Penumbra).
                    interval (Interval): The time interval of the phase.
                    is_complete (bool): Whether the phase is complete.
            )doc"
        )

        .def(
            self == self,
            R"doc(
                Equality operator.

                Args:
                    other (EclipsePhase): Other EclipsePhase.

                Returns:
                    bool: True if equal.
            )doc"
        )
        .def(
            self != self,
            R"doc(
                Inequality operator.

                Args:
                    other (EclipsePhase): Other EclipsePhase.

                Returns:
                    bool: True if not equal.
            )doc"
        )

        .def("__repr__", &(shiftToString<EclipsePhase>))
        .def("__str__", &(shiftToString<EclipsePhase>))

        .def(
            "get_region",
            &EclipsePhase::getRegion,
            return_value_policy::reference_internal,
            R"doc(
                The region of the eclipse phase (Umbra or Penumbra).
            )doc"
        )

        .def(
            "get_interval",
            &EclipsePhase::getInterval,
            return_value_policy::reference_internal,
            R"doc(
                The time interval of the phase.
            )doc"
        )

        .def(
            "is_complete",
            &EclipsePhase::isComplete,
            R"doc(
                Whether the phase is complete.
            )doc"
        )

        ;

    class_<Eclipse>(
        aModule,
        "Eclipse",
        R"doc(
            Eclipse.
            
            This class represents an eclipse event between two celestial objects,
            containing information about the occulted and occulting objects, as well
            as the phases of the eclipse.
        )doc"
    )

        .def(
            init<const Celestial&, const Celestial&, const Array<EclipsePhase>&>(),
            arg("occulted_celestial_object"),
            arg("occulting_celestial_object"),
            arg("phases"),
            R"doc(
                Constructor

                Args:
                    occulted_celestial_object (Celestial): The occulted celestial object.
                    occulting_celestial_object (Celestial): The occulting celestial object.
                    phases (list[EclipsePhase]): The phases of the eclipse.

                Raises:
                    RuntimeError: If the phases are not contiguous.
            )doc"
        )

        .def("__str__", &(shiftToString<Eclipse>))
        .def("__repr__", &(shiftToString<Eclipse>))

        .def(
            "get_occulted_celestial_object",
            &Eclipse::accessOccultedCelestialObject,
            return_value_policy::reference_internal,
            R"doc(
                Get the occulted celestial object.

                Returns:
                    Celestial: The occulted celestial object.
            )doc"
        )

        .def(
            "get_occulting_celestial_object",
            &Eclipse::accessOccultingCelestialObject,
            return_value_policy::reference_internal,
            R"doc(
                Get the occulting celestial object.

                Returns:
                    Celestial: The occulting celestial object.
            )doc"
        )

        .def(
            "get_phases",
            &Eclipse::getPhases,
            return_value_policy::reference_internal,
            R"doc(
                Get the phases of the eclipse.

                Returns:
                    list[EclipsePhase]: The phases of the eclipse.
            )doc"
        )

        .def(
            "get_duration",
            &Eclipse::getDuration,
            arg("include_penumbra") = true,
            R"doc(
                Get the duration of the eclipse.

                Args:
                    include_penumbra (bool, optional): Whether to include the penumbra phases. Defaults to True.

                Returns:
                    Duration: The duration of the eclipse.
            )doc"
        )

        .def(
            "get_interval",
            &Eclipse::getInterval,
            arg("include_penumbra") = true,
            R"doc(
                Get the interval of the eclipse.

                Args:
                    include_penumbra (bool, optional): Whether to include the penumbra phases. Defaults to True.

                Returns:
                    Interval: The interval of the eclipse. Returns Interval::Undefined() if there are no umbra phases
                            and penumbras are not included.

                Raises:
                    RuntimeError: If there are multiple umbra phases and penumbras are not included.
            )doc"
        )

        ;

    aModule.def(
        "eclipse_intervals_at_position",
        &ostk::physics::environment::utilities::eclipseIntervalsAtPosition,
        arg("analysis_interval"),
        arg("position"),
        arg("environment"),
        arg("include_penumbra") = true,
        arg("time_step") = Duration::Minutes(1.0),
        R"doc(
            Calculate eclipse intervals for a given position.

            Args:
                analysis_interval (Interval): An analysis interval.
                position (Position): A position.
                environment (Environment): An environment.
                include_penumbra (bool, optional): Whether to include penumbra phases. Defaults to True.
                time_step (Duration, optional): The time step for analysis, the lower the more accurate the result will be. Defaults to one minute.

            Returns:
                list[Interval]: Array of eclipse intervals for a given position.
        )doc"
    )

        ;

    aModule.def(
        "montenbruck_gill_shadow_function",
        &ostk::physics::environment::utilities::montenbruckGillShadowFunction,
        arg("instant"),
        arg("position"),
        arg("occulted_celestial_object"),
        arg("occulting_celestial_object"),
        R"doc(
            Montenbruck-Gill shadow function.

            Reference: Montenbruck and Gill, Satellite Orbits: Models, Methods, and Applications, 4th edition, Springer.

            Args:
                instant (Instant): The instant at which the shadow function is evaluated.
                position (Position): The position for which the shadow function is evaluated.
                occulted_celestial_object (Celestial): The occulted celestial object.
                occulting_celestial_object (Celestial): The occulting celestial object.

            Returns:
                float: The value of the shadow function (0.0 for umbra, 1.0 for fully illuminated, and between 0.0 and 1.0 for penumbra).
        )doc"
    )

        ;
}
