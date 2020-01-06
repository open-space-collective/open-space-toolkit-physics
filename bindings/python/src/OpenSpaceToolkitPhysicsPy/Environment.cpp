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

#include <OpenSpaceToolkitPhysicsPy/Utilities/IterableConverter.hpp>

#include <OpenSpaceToolkit/Physics/Environment.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitPhysicsPy_Environment                ( )
{

    using namespace boost::python ;

    using ostk::core::types::Shared ;
    using ostk::core::ctnr::Array ;

    using ostk::physics::time::Instant ;
    using ostk::physics::Environment ;
    using ostk::physics::env::Object ;

    scope in_Environment = class_<Environment>("Environment", init<const Instant&, const Array<Shared<Object>>&>())

        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))

        .def("is_defined", &Environment::isDefined)
        .def("has_object_with_name", &Environment::hasObjectWithName)
        .def("intersects", &Environment::intersects)

        .def("access_objects", &Environment::accessObjects)
        .def("access_object_with_name", &Environment::accessObjectWithName)
        .def("access_celestial_object_with_name", &Environment::accessCelestialObjectWithName)
        .def("get_instant", &Environment::getInstant)
        .def("get_object_names", &Environment::getObjectNames)
        .def("set_instant", &Environment::setInstant)

        .def("undefined", &Environment::Undefined).staticmethod("undefined")
        .def("default", &Environment::Default).staticmethod("default")

    ;

    IterableConverter()

        .from_python<Array<Shared<Object>>>()
        .to_python<Array<Shared<Object>>>()

    ;

    boost::python::object module(boost::python::handle<>(boost::python::borrowed(PyImport_AddModule("ostk.physics.environment")))) ;

    boost::python::scope().attr("environment") = module ;

    boost::python::scope scope = module ;

    OpenSpaceToolkitPhysicsPy_Environment_Object() ;
    OpenSpaceToolkitPhysicsPy_Environment_Objects() ;
    OpenSpaceToolkitPhysicsPy_Environment_Gravitational() ;
    OpenSpaceToolkitPhysicsPy_Environment_Magnetic() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
