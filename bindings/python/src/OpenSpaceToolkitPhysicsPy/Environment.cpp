////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           bindings/python/src/OpenSpaceToolkitPhysicsPy/Environment.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkitPhysicsPy/Environment/Magnetic.cpp>
#include <OpenSpaceToolkitPhysicsPy/Environment/Gravitational.cpp>
#include <OpenSpaceToolkitPhysicsPy/Environment/Objects.cpp>
#include <OpenSpaceToolkitPhysicsPy/Environment/Object.cpp>

#include <OpenSpaceToolkit/Physics/Environment.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitPhysicsPy_Environment       (           pybind11::module&           aModule                                     )
{

    using namespace pybind11 ;

    using ostk::core::types::Shared ;
    using ostk::core::ctnr::Array ;

    using ostk::physics::time::Instant ;
    using ostk::physics::Environment ;
    using ostk::physics::env::Object ;

    class_<Environment>(aModule, "Environment")

        .def(init<const Instant&, const Array<Shared<Object>>&>())

        // .def(self_ns::str(self_ns::self))
        // .def(self_ns::repr(self_ns::self))

        .def("is_defined", &Environment::isDefined)
        .def("has_object_with_name", &Environment::hasObjectWithName)
        .def("intersects", &Environment::intersects)

        .def("access_objects", &Environment::accessObjects)                                       // check return_value_policy
        .def("access_object_with_name", &Environment::accessObjectWithName)                       // check return_value_policy
        .def("access_celestial_object_with_name", &Environment::accessCelestialObjectWithName)    // check return_value_policy
        .def("get_instant", &Environment::getInstant)
        .def("get_object_names", &Environment::getObjectNames)
        .def("set_instant", &Environment::setInstant)

        .def_static("undefined", &Environment::Undefined)
        .def_static("default", &Environment::Default)

    ;

    // Create "environment" python submodule
    auto environment = aModule.def_submodule("environment") ;

    // Add __path__ attribute for "environment" submodule
    environment.attr("__path__") = "ostk.physics.environment" ;

    OpenSpaceToolkitPhysicsPy_Environment_Object(environment) ;
    OpenSpaceToolkitPhysicsPy_Environment_Objects(environment) ;
    OpenSpaceToolkitPhysicsPy_Environment_Gravitational(environment) ;
    OpenSpaceToolkitPhysicsPy_Environment_Magnetic(environment) ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
