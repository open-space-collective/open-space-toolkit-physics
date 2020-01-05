////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           bindings/python/src/OpenSpaceToolkitPhysicsPy/Units/Derived/Angle.cpp
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

        .def("is_defined", &Angle::isDefined)
        .def("is_zero", &Angle::isZero)

        .def("get_unit", &Angle::getUnit)
        .def("in_unit", &Angle::in)
        .def("in_radians", +[] (const Angle& anAngle) -> Real { return anAngle.inRadians() ; })
        .def("in_degrees", +[] (const Angle& anAngle) -> Real { return anAngle.inDegrees() ; })
        .def("in_arcminutes", +[] (const Angle& anAngle) -> Real { return anAngle.inArcminutes() ; })
        .def("in_arcseconds", +[] (const Angle& anAngle) -> Real { return anAngle.inArcseconds() ; })
        .def("in_revolutions", &Angle::inRevolutions)
        .def("to_string", &Angle::toString, OpenSpaceToolkitPhysicsPy_Units_Angle_toString_overloads())

        .def("undefined", &Angle::Undefined).staticmethod("undefined")
        .def("zero", &Angle::Zero).staticmethod("zero")
        .def("half_pi", &Angle::HalfPi).staticmethod("half_pi")
        .def("pi", &Angle::Pi).staticmethod("pi")
        .def("two_pi", &Angle::TwoPi).staticmethod("two_pi")
        .def("radians", &Angle::Radians).staticmethod("radians")
        .def("degrees", &Angle::Degrees).staticmethod("degrees")
        .def("arcminutes", &Angle::Arcminutes).staticmethod("arcminutes")
        .def("arcseconds", &Angle::Arcseconds).staticmethod("arcseconds")
        .def("revolutions", &Angle::Revolutions).staticmethod("revolutions")
        .def("between_vector2d", +[] (const Vector2d& aFirstVector, const Vector2d& aSecondVector) -> Angle { return Angle::Between(aFirstVector, aSecondVector) ; })
        .def("between_vector3d", +[] (const Vector3d& aFirstVector, const Vector3d& aSecondVector) -> Angle { return Angle::Between(aFirstVector, aSecondVector) ; })
        .def("parse", &Angle::Parse).staticmethod("parse")
        .def("string_from_unit", &Angle::StringFromUnit).staticmethod("string_from_unit")
        .def("symbol_from_unit", &Angle::SymbolFromUnit).staticmethod("symbol_from_unit")

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

    //     .def("is_defined", &Interval<Angle>::isDefined)
    //     .def("is_degenerate", &Interval<Angle>::isDegenerate)
    //     .def("intersects", &Interval<Angle>::intersects)
    //     .def("contains_angle", +[] (const Interval<Angle>& anInterval, const Angle& anAngle) -> bool { return anInterval.contains(anAngle) ; })
    //     .def("contains_interval", +[] (const Interval<Angle>& anInterval, const Interval<Angle>& anOtherInterval) -> bool { return anInterval.contains(anOtherInterval) ; })

    //     .def("get_lower_bound", &Interval<Angle>::getLowerBound)
    //     .def("get_upper_bound", &Interval<Angle>::getUpperBound)

    //     .def("undefined", &Interval<Angle>::Undefined).staticmethod("undefined")
    //     .def("closed", &Interval<Angle>::Closed).staticmethod("closed")

    // ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
