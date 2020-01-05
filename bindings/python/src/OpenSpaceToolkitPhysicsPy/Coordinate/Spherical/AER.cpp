////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           bindings/python/src/OpenSpaceToolkitPhysicsPy/Coordinate/Spherical/AER.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Physics/Coordinate/Spherical/AER.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitPhysicsPy_Coordinate_Spherical_AER   ( )
{

    using namespace boost::python ;

    using ostk::physics::units::Length ;
    using ostk::physics::units::Angle ;
    using ostk::physics::coord::Position ;
    using ostk::physics::coord::spherical::AER ;

    scope in_AER = class_<AER>("AER", init<const Angle&, const Angle&, const Length&>())

        .def(self == self)
        .def(self != self)

        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))

        .def("isDefined", &AER::isDefined)

        .def("getAzimuth", &AER::getAzimuth)
        .def("getElevation", &AER::getElevation)
        .def("getRange", &AER::getRange)
        .def("toVector", &AER::toVector)
        .def("toString", &AER::toString)

        .def("Undefined", &AER::Undefined).staticmethod("Undefined")
        .def("Vector", &AER::Vector).staticmethod("Vector")
        .def("FromPositionToPosition", +[] (const Position& aFromPosition, const Position& aToPosition) -> AER { return AER::FromPositionToPosition(aFromPosition, aToPosition) ; })
        .def("FromPositionToPosition", +[] (const Position& aFromPosition, const Position& aToPosition, const bool isZNegative) -> AER { return AER::FromPositionToPosition(aFromPosition, aToPosition, isZNegative) ; })

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
