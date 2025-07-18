/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Environment.hpp>

#include <OpenSpaceToolkitPhysicsPy/Environment/Atmospheric.cpp>
#include <OpenSpaceToolkitPhysicsPy/Environment/Gravitational.cpp>
#include <OpenSpaceToolkitPhysicsPy/Environment/Magnetic.cpp>
#include <OpenSpaceToolkitPhysicsPy/Environment/Object.cpp>
#include <OpenSpaceToolkitPhysicsPy/Environment/Utility.cpp>

inline void OpenSpaceToolkitPhysicsPy_Environment(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::container::Array;
    using ostk::core::type::Shared;

    using ostk::physics::Environment;
    using ostk::physics::environment::Object;
    using ostk::physics::time::Instant;

    class_<Environment, Shared<Environment>>(
        aModule,
        "Environment",
        R"doc(
            Environment modelling
        )doc"
    )

        .def(
            init<const Instant&, const Array<Shared<const Object>>&, const bool&>(),
            arg("instant"),
            arg("objects"),
            arg("set_global_instance") = false,
            R"doc(
                Constructor

                Args:
                    instant (Instant): An Instant.
                    objects (list[Object]): List of objects.
                    set_global_instance (bool, optional): True if the global environment instance should be set. Defaults to False.
            )doc"
        )
        .def(
            init<const Shared<const Object>&, const Array<Shared<const Object>>&, const Instant&, const bool&>(),
            arg("central_celestial_object"),
            arg("objects"),
            arg("instant") = Instant::J2000(),
            arg("set_global_instance") = false,
            R"doc(
                Constructor

                Args:
                    central_celestial_object (Object): A central celestial object.
                    objects (list[Object]): List of objects.
                    instant (Instant, optional): An Instant. Default is J2000 epoch.
                    set_global_instance (bool, optional): True if the global environment instance should be set. Defaults to False.
            )doc"
        )

        .def("__str__", &(shiftToString<Environment>))
        .def("__repr__", &(shiftToString<Environment>))

        .def(
            "is_defined",
            &Environment::isDefined,
            R"doc(
                Check if the environment is defined,

                Returns:
                    bool: True if the environment is defined, False otherwise,
            )doc"
        )
        .def(
            "has_object_with_name",
            &Environment::hasObjectWithName,
            arg("name"),
            R"doc(
                Returns true if environment contains objects with a given name.

                Args:
                    name (str): The name of the object.

                Returns:
                    bool: True if environment contains objects with a given name, False otherwise.
            )doc"
        )
        .def(
            "has_central_celestial_object",
            &Environment::hasCentralCelestialObject,
            R"doc(
                Returns true if the environment has a central celestial object.

                Returns:
                    bool: True if the environment has a central celestial object, False otherwise.
            )doc"
        )
        .def(
            "intersects",
            &Environment::intersects,
            arg("geometry"),
            arg_v("objects_to_ignore", Array<Shared<const Object>>::Empty(), "[]"),
            R"doc(
                Returns true if a given geometry intersects any of the environment objects.

                Args:
                    geometry (Geometry): The geometry to check for intersection.
                    objects_to_ignore (list[Object], optional): List of objects to ignore during intersection check.

                Returns:
                    bool: True if the geometry intersects with any objects, False otherwise.
            )doc"
        )

        .def(
            "access_objects",
            &Environment::accessObjects,
            return_value_policy::reference,
            R"doc(
                Access the objects in the environment.

                Returns:
                    list(Object): The list of objects.
            )doc"
        )
        .def(
            "access_object_with_name",
            &Environment::accessObjectWithName,
            arg("name"),
            return_value_policy::reference,
            R"doc(
                Access an object with a given name.

                Args:
                    name (str): An object name.

                Returns:
                    Object: The object with the given name.
            )doc"
        )
        .def(
            "access_celestial_object_with_name",
            &Environment::accessCelestialObjectWithName,
            arg("name"),
            return_value_policy::reference,
            R"doc(
                Access celestial object with a given name.

                Args:
                    name (str): The name of the celestial object.

                Returns:
                    Celestial: The celestial object with the given name.
            )doc"
        )
        .def(
            "access_central_celestial_object",
            &Environment::accessCentralCelestialObject,
            return_value_policy::reference,
            R"doc(
                Access the central celestial object.

                Returns:
                    Celestial: The central celestial object.
            )doc"
        )

        .def(
            "get_instant",
            &Environment::getInstant,
            R"doc(
                Get instant.

                Returns:
                    Instant: The instant.
            )doc"
        )
        .def(
            "get_object_names",
            &Environment::getObjectNames,
            R"doc(
                Get names of objects.

                Returns:
                    list(str): List of objects names.
            )doc"
        )

        .def(
            "set_instant",
            &Environment::setInstant,
            arg("instant"),
            R"doc(
                Set the instant of the environment.

                Args:
                    instant (Instant): The new instant of the environment.
            )doc"
        )

        .def(
            "is_position_in_eclipse",
            &Environment::isPositionInEclipse,
            arg("position"),
            arg("include_penumbra") = true,
            R"doc(
                Is position in eclipse.

                Args:
                    position (Position): A position.
                    include_penumbra (bool, optional): Whether to include penumbra in eclipse calculation. Defaults to True.

                Returns:
                    bool: True if the position is in eclipse, False otherwise.
            )doc"
        )

        .def_static(
            "undefined",
            &Environment::Undefined,
            R"doc(
                Get an undefined Environment object.

                Returns:
                    Environment: An undefined Environment object.
            )doc"
        )
        .def_static(
            "default",
            &Environment::Default,
            R"doc(
                Get the default Environment object.

                Args:
                    (set_global_instance): True if the global environment instance should be set.

                Returns:
                    Environment: The default Environment object.
            )doc",
            arg("set_global_instance") = false
        )
        .def_static(
            "reset_global_instance",
            &Environment::ResetGlobalInstance,
            R"doc(
                Reset the global environment instance.
            )doc"
        )
        .def_static(
            "access_global_instance",
            &Environment::AccessGlobalInstance,
            return_value_policy::reference,
            R"doc(
                Access the global environment instance.

                Returns:
                    Environment: The global environment instance.
            )doc"
        )
        .def_static(
            "has_global_instance",
            &Environment::HasGlobalInstance,
            R"doc(
                Check if the global environment instance is set.

                Returns:
                    bool: True if the global environment instance is set, False otherwise.
            )doc"
        )

        ;

    // Create "environment" python submodule
    auto environment = aModule.def_submodule("environment");

    OpenSpaceToolkitPhysicsPy_Environment_Object(environment);
    OpenSpaceToolkitPhysicsPy_Environment_Gravitational(environment);
    OpenSpaceToolkitPhysicsPy_Environment_Magnetic(environment);
    OpenSpaceToolkitPhysicsPy_Environment_Atmospheric(environment);
    OpenSpaceToolkitPhysicsPy_Environment_Utility(environment);
}
