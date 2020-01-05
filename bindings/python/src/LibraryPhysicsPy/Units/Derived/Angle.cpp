////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           OpenSpaceToolkitPhysicsPy/Units/Derived/Angle.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Physics/Units/Derived/Angle.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS (OpenSpaceToolkitPhysicsPy_Units_Angle_toString_overloads, ostk::physics::units::Angle::toString, 0, 1)

inline void                     OpenSpaceToolkitPhysicsPy_Units_Derived_Angle        ( )
{

    using namespace boost::python ;

    using ostk::core::types::Real ;

    using ostk::math::obj::Vector2d ;
    using ostk::math::obj::Vector3d ;

    using ostk::physics::units::Angle ;

    scope in_Angle = class_<Angle>("Angle", init<Real, Angle::Unit>())

        .def(self == self)
        .def(self != self)

        .def(self + self)
        .def(self - self)

        .def(self * other<Real>())
        .def(self / other<Real>())

        .def(self += self)
        .def(self -= self)

        .def(self *= other<Real>())
        .def(self /= other<Real>())

        .def(self_ns::str(self_ns::self))

        .def("__repr__", +[] (const Angle& anAngle) -> std::string { return anAngle.toString() ; })

        .def("isDefined", &Angle::isDefined)
        .def("isZero", &Angle::isZero)

        .def("getUnit", &Angle::getUnit)
        .def("inUnit", &Angle::in)
        .def("inRadians", +[] (const Angle& anAngle) -> Real { return anAngle.inRadians() ; })
        .def("inDegrees", +[] (const Angle& anAngle) -> Real { return anAngle.inDegrees() ; })
        .def("inArcminutes", +[] (const Angle& anAngle) -> Real { return anAngle.inArcminutes() ; })
        .def("inArcseconds", +[] (const Angle& anAngle) -> Real { return anAngle.inArcseconds() ; })
        .def("inRevolutions", &Angle::inRevolutions)
        .def("toString", &Angle::toString, OpenSpaceToolkitPhysicsPy_Units_Angle_toString_overloads())

        .def("Undefined", &Angle::Undefined).staticmethod("Undefined")
        .def("Zero", &Angle::Zero).staticmethod("Zero")
        .def("HalfPi", &Angle::HalfPi).staticmethod("HalfPi")
        .def("Pi", &Angle::Pi).staticmethod("Pi")
        .def("TwoPi", &Angle::TwoPi).staticmethod("TwoPi")
        .def("Radians", &Angle::Radians).staticmethod("Radians")
        .def("Degrees", &Angle::Degrees).staticmethod("Degrees")
        .def("Arcminutes", &Angle::Arcminutes).staticmethod("Arcminutes")
        .def("Arcseconds", &Angle::Arcseconds).staticmethod("Arcseconds")
        .def("Revolutions", &Angle::Revolutions).staticmethod("Revolutions")
        .def("BetweenVector2d", +[] (const Vector2d& aFirstVector, const Vector2d& aSecondVector) -> Angle { return Angle::Between(aFirstVector, aSecondVector) ; })
        .def("BetweenVector3d", +[] (const Vector3d& aFirstVector, const Vector3d& aSecondVector) -> Angle { return Angle::Between(aFirstVector, aSecondVector) ; })
        .def("Parse", &Angle::Parse).staticmethod("Parse")
        .def("StringFromUnit", &Angle::StringFromUnit).staticmethod("StringFromUnit")
        .def("SymbolFromUnit", &Angle::SymbolFromUnit).staticmethod("SymbolFromUnit")

    ;

    enum_<Angle::Unit>("Unit")

        .value("Undefined", Angle::Unit::Undefined)
        .value("Radian", Angle::Unit::Radian)
        .value("Degree", Angle::Unit::Degree)
        .value("Arcminute", Angle::Unit::Arcminute)
        .value("Arcsecond", Angle::Unit::Arcsecond)
        .value("Revolution", Angle::Unit::Revolution)

    ;

    implicitly_convertible<ostk::physics::units::Angle, ostk::math::geom::Angle>() ;
    implicitly_convertible<ostk::math::geom::Angle, ostk::physics::units::Angle>() ;

    // using ostk::math::obj::Interval ;

    // class_<Interval<Angle>>("Interval", init<const Angle&, const Angle&, const Interval<Angle>::Type&>())

    //     .def(self == self)
    //     .def(self != self)

    //     .def("isDefined", &Interval<Angle>::isDefined)
    //     .def("isDegenerate", &Interval<Angle>::isDegenerate)
    //     .def("intersects", &Interval<Angle>::intersects)
    //     .def("containsAngle", +[] (const Interval<Angle>& anInterval, const Angle& anAngle) -> bool { return anInterval.contains(anAngle) ; })
    //     .def("containsInterval", +[] (const Interval<Angle>& anInterval, const Interval<Angle>& anOtherInterval) -> bool { return anInterval.contains(anOtherInterval) ; })

    //     .def("getLowerBound", &Interval<Angle>::getLowerBound)
    //     .def("getUpperBound", &Interval<Angle>::getUpperBound)

    //     .def("Undefined", &Interval<Angle>::Undefined).staticmethod("Undefined")
    //     .def("Closed", &Interval<Angle>::Closed).staticmethod("Closed")

    // ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
