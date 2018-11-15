////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           LibraryPhysicsPy/Environment.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <LibraryPhysicsPy/Environment/Objects.cpp>
#include <LibraryPhysicsPy/Environment/Object.cpp>

#include <LibraryPhysicsPy/Utilities/IterableConverter.hpp>

#include <Library/Physics/Environment.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryPhysicsPy_Environment                ( )
{
    
    using namespace boost::python ;

    using library::core::types::Shared ;
    using library::core::ctnr::Array ;

    using library::physics::time::Instant ;
    using library::physics::Environment ;
    using library::physics::env::Object ;

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
    
    LibraryPhysicsPy_Environment_Object() ;
    LibraryPhysicsPy_Environment_Objects() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////