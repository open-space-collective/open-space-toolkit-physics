/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Environment.hpp>

#include <OpenSpaceToolkitPhysicsPy/Environment/Atmospheric.cpp>
#include <OpenSpaceToolkitPhysicsPy/Environment/Gravitational.cpp>
#include <OpenSpaceToolkitPhysicsPy/Environment/Magnetic.cpp>
#include <OpenSpaceToolkitPhysicsPy/Environment/Object.cpp>

inline void OpenSpaceToolkitPhysicsPy_Environment(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Shared;
    using ostk::core::container::Array;

    using ostk::physics::time::Instant;
    using ostk::physics::Environment;
    using ostk::physics::environment::Object;

    class_<Environment>(
        aModule,
        "Environment",
        R"doc(
            Environment modelling
        )doc"
    )

        .def(
            init<const Instant&, const Array<Shared<Object>>&>(),
            arg("instant"),
            arg("objects"),
            R"doc(
                Constructor

                Args:
                    instant (Instant): An Instant
                    objects (Array): Array of objects
            )doc"
        )

        .def("__str__", &(shiftToString<Environment>))
        .def("__repr__", &(shiftToString<Environment>))

        .def(
            "is_defined",
            &Environment::isDefined,
            R"doc(
                Check if the environment is defined

                Returns:
                    bool: True if the environment is defined, False otherwise
            )doc"
        )
        .def(
            "has_object_with_name",
            &Environment::hasObjectWithName,
            arg("name"),
            R"doc(
                Returns true if environment contains objects with a given name

                Args:
                    name (str): The name of the object

                Returns:
                    bool: True if environment contains objects with a given name, False otherwise
            )doc"
        )
        .def(
            "intersects",
            &Environment::intersects,
            arg("geometry"),
            arg_v("objects_to_ignore", Array<Shared<const Object>>::Empty(), "[]"),
            R"doc(
                Returns true if a given geometry intersects any of the environment objects

                Args:
                    geometry (Geometry): The geometry to check for intersection
                    objects_to_ignore (Array, optional): Array of objects to ignore during intersection check

                Returns:
                    bool: True if the geometry intersects with any objects, False otherwise
            )doc"
        )

        .def(
            "access_objects",
            &Environment::accessObjects,
            return_value_policy::reference,
            R"doc(
                Access objects

                Returns:
                    Array: The array of objects
            )doc"
        )
        .def(
            "access_object_with_name",
            &Environment::accessObjectWithName,
            arg("name"),
            return_value_policy::reference,
            R"doc(
                Access object with a given name

                Args:
                    name (str): An object name

                Returns:
                    Object: The object with the given name
            )doc"
        )
        .def(
            "access_celestial_object_with_name",
            &Environment::accessCelestialObjectWithName,
            arg("name"),
            return_value_policy::reference,
            R"doc(
                Access celestial object with a given name

                Args:
                    name (str): The name of the celestial object

                Returns:
                    Object: The celestial object with the given name
            )doc"
        )

        .def(
            "get_instant",
            &Environment::getInstant,
            R"doc(
                Get instant

                Returns:
                    Instant: The instant
            )doc"
        )
        .def(
            "get_object_names",
            &Environment::getObjectNames,
            R"doc(
                Get names of objects

                Returns:
                    Array: Array of objects names
            )doc"
        )

        .def(
            "set_instant",
            &Environment::setInstant,
            arg("instant"),
            R"doc(
                Set the instant of the environment

                Args:
                    instant (Instant): The new instant of the environment
            )doc"
        )

        .def(
            "is_position_in_eclipse",
            &Environment::isPositionInEclipse,
            arg("position"),
            R"doc(
                Is position in eclipse

                Args:
                    position (Position): A position

                Returns:
                    bool: True if the position is in eclipse, False otherwise
            )doc"
        )

        .def_static(
            "undefined",
            &Environment::Undefined,
            R"doc(
                Get an undefined Environment object

                Returns:
                    Environment: An undefined Environment object
            )doc"
        )
        .def_static(
            "default",
            &Environment::Default,
            R"doc(
                Get the default Environment object

                Returns:
                    Environment: The default Environment object
            )doc"
        );

    // Create "environment" python submodule
    auto environment = aModule.def_submodule("environment");

    OpenSpaceToolkitPhysicsPy_Environment_Object(environment);
    OpenSpaceToolkitPhysicsPy_Environment_Gravitational(environment);
    OpenSpaceToolkitPhysicsPy_Environment_Magnetic(environment);
    OpenSpaceToolkitPhysicsPy_Environment_Atmospheric(environment);
}
