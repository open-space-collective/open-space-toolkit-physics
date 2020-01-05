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

        .def("isDefined", &Environment::isDefined)
        .def("hasObjectWithName", &Environment::hasObjectWithName)
        .def("intersects", &Environment::intersects)

        .def("accessObjects", &Environment::accessObjects)
        .def("accessObjectWithName", &Environment::accessObjectWithName)
        .def("accessCelestialObjectWithName", &Environment::accessCelestialObjectWithName)
        .def("getInstant", &Environment::getInstant)
        .def("getObjectNames", &Environment::getObjectNames)
        .def("setInstant", &Environment::setInstant)

        .def("Undefined", &Environment::Undefined).staticmethod("Undefined")
        .def("Default", &Environment::Default).staticmethod("Default")

    ;

    IterableConverter()

        .from_python<Array<Shared<Object>>>()
        .to_python<Array<Shared<Object>>>()

    ;

    OpenSpaceToolkitPhysicsPy_Environment_Object() ;
    OpenSpaceToolkitPhysicsPy_Environment_Objects() ;
    OpenSpaceToolkitPhysicsPy_Environment_Gravitational() ;
    OpenSpaceToolkitPhysicsPy_Environment_Magnetic() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
