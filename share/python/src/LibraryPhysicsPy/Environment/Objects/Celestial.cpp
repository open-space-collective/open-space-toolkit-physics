////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           LibraryPhysicsPy/Environment/Objects/Celestial.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Environment/Objects/Celestial.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryPhysicsPy_Environment_Objects_Celestial ( )
{

    using namespace boost::python ;

    using library::core::types::Shared ;
    using library::core::types::Real ;
    using library::core::types::String ;

    using library::physics::time::Instant ;
    using library::physics::units::Length ;
    using library::physics::units::Derived ;
    using library::physics::env::Ephemeris ;
    using library::physics::env::Object ;
    using library::physics::env::obj::Celestial ;

    scope in_Celestial = class_<Celestial, bases<Object>>("Celestial", init<const String&, const Celestial::Type&, const Derived& , const Length&, const Real&, const Real&, const Shared<Ephemeris>&, const Instant&>())

        .def(init<const String&, const Celestial::Type&, const Derived& , const Length&, const Real&, const Real&, const Shared<Ephemeris>&, const Instant&, const Object::Geometry&>())

        // .def(self == self)
        // .def(self != self)

        .def(self_ns::str(self_ns::self))

        .def("isDefined", &Celestial::isDefined)
        
        .def("accessEphemeris", &Celestial::accessEphemeris)
        .def("getType", &Celestial::getType)
        .def("getGravitationalConstant", &Celestial::getGravitationalConstant)
        .def("getEquatorialRadius", &Celestial::getEquatorialRadius)
        .def("getFlattening", &Celestial::getFlattening)
        .def("getJ2", &Celestial::getJ2)
        // .def("accessFrame", &Celestial::accessFrame)
        .def("getPositionIn", &Celestial::getPositionIn)
        .def("getTransformTo", &Celestial::getTransformTo)
        .def("getAxesIn", &Celestial::getAxesIn)
        .def("getGravitationalFieldAt", &Celestial::getGravitationalFieldAt)
        
        .def("Undefined", &Celestial::Undefined).staticmethod("Undefined")

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////