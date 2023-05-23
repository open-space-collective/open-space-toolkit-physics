/// Apache License 2.0 

#include <OpenSpaceToolkitPhysicsPy/Environment/Atmospheric.cpp>
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

        .def(init<const Instant&, const Array<Shared<Object>>&>(), arg("instant"), arg("objects"))

        .def("__str__", &(shiftToString<Environment>))
        .def("__repr__", &(shiftToString<Environment>))

        .def("is_defined", &Environment::isDefined)
        .def("has_object_with_name", &Environment::hasObjectWithName, arg("name"))
        .def("intersects", &Environment::intersects, arg("geometry"), arg("objects_to_ignore") = Array<Shared<const Object>>::Empty())

        .def("access_objects", &Environment::accessObjects, return_value_policy::reference)
        .def("access_object_with_name", &Environment::accessObjectWithName, arg("name"), return_value_policy::reference)
        .def("access_celestial_object_with_name", &Environment::accessCelestialObjectWithName, arg("name"), return_value_policy::reference)

        .def("get_instant", &Environment::getInstant)
        .def("get_object_names", &Environment::getObjectNames)

        .def("set_instant", &Environment::setInstant, arg("instant"))

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
    OpenSpaceToolkitPhysicsPy_Environment_Atmospheric(environment) ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
