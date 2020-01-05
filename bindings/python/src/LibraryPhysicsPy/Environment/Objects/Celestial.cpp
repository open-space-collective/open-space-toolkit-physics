////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           OpenSpaceToolkitPhysicsPy/Environment/Objects/Celestial.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Physics/Environment/Objects/Celestial.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitPhysicsPy_Environment_Objects_Celestial ( )
{

    using namespace boost::python ;

    using ostk::core::types::Shared ;
    using ostk::core::types::Real ;
    using ostk::core::types::String ;

    using ostk::physics::time::Instant ;
    using ostk::physics::units::Length ;
    using ostk::physics::units::Derived ;
    using ostk::physics::env::Ephemeris ;
    using ostk::physics::env::Object ;
    using ostk::physics::env::obj::Celestial ;
    using GravitationalModel = ostk::physics::environment::gravitational::Model ;
    using MagneticModel = ostk::physics::environment::magnetic::Model ;

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
