////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library ▸ Physics
/// @file           LibraryPhysicsPy/Environment/Objects/Celestial.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

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
    using GravitationalModel = library::physics::environment::gravitational::Model ;
    using MagneticModel = library::physics::environment::magnetic::Model ;

    scope in_Celestial = class_<Celestial, bases<Object>>("Celestial", init<const String&, const Celestial::Type&, const Derived& , const Length&, const Real&, const Real&, const Shared<Ephemeris>&, const Shared<GravitationalModel>&, const Shared<MagneticModel>&, const Instant&>())

        .def(init<const String&, const Celestial::Type&, const Derived& , const Length&, const Real&, const Real&, const Shared<Ephemeris>&, const Shared<GravitationalModel>&, const Shared<MagneticModel>&, const Instant&, const Object::Geometry&>())

        // .def(self == self)
        // .def(self != self)

        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))

        .def("isDefined", &Celestial::isDefined)

        .def("accessEphemeris", &Celestial::accessEphemeris)
        .def("accessGravitationalModel", &Celestial::accessGravitationalModel)
        .def("accessMagneticModel", &Celestial::accessMagneticModel)

        .def("getType", &Celestial::getType)
        .def("getGravitationalParameter", &Celestial::getGravitationalParameter)
        .def("getEquatorialRadius", &Celestial::getEquatorialRadius)
        .def("getFlattening", &Celestial::getFlattening)
        .def("getJ2", &Celestial::getJ2)
        // .def("accessFrame", &Celestial::accessFrame)
        .def("getPositionIn", &Celestial::getPositionIn)
        .def("getTransformTo", &Celestial::getTransformTo)
        .def("getAxesIn", &Celestial::getAxesIn)
        .def("getGravitationalFieldAt", &Celestial::getGravitationalFieldAt)
        .def("getMagneticFieldAt", &Celestial::getMagneticFieldAt)
        .def("getFrameAt", &Celestial::getFrameAt)

        .def("Undefined", &Celestial::Undefined).staticmethod("Undefined")

        .def("StringFromFrameType", &Celestial::StringFromFrameType).staticmethod("StringFromFrameType")

    ;

    enum_<Celestial::Type>("Type")

        .value("Undefined", Celestial::Type::Undefined)
        .value("Sun", Celestial::Type::Sun)
        .value("Mercury", Celestial::Type::Mercury)
        .value("Venus", Celestial::Type::Venus)
        .value("Earth", Celestial::Type::Earth)
        .value("Moon", Celestial::Type::Moon)
        .value("Mars", Celestial::Type::Mars)

    ;

    enum_<Celestial::FrameType>("FrameType")

        .value("Undefined", Celestial::FrameType::Undefined)
        .value("NED", Celestial::FrameType::NED)

    ;

    register_ptr_to_python<Shared<const Celestial>>() ;

    implicitly_convertible<Shared<Celestial>, Shared<const Celestial>>() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
