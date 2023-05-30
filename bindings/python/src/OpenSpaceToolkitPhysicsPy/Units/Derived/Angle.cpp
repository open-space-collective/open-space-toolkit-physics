/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Units/Derived/Angle.hpp>

inline void OpenSpaceToolkitPhysicsPy_Units_Derived_Angle(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::types::Integer;
    using ostk::core::types::Real;

    using ostk::math::obj::Vector2d;
    using ostk::math::obj::Vector3d;

    using ostk::physics::units::Angle;

    class_<Angle> angle(aModule, "Angle");

    angle
        .def(init<Real, Angle::Unit>())

        .def(self == self)
        .def(self != self)

        .def(self + self)
        .def(self - self)

        .def(self += self)
        .def(self -= self)

        .def(+self)
        .def(-self)

        .def(
            "__mul__",
            [](const Angle& anAngle, Real aReal)
            {
                return anAngle * aReal;
            },
            is_operator()
        )
        .def(
            "__truediv__",
            [](const Angle& anAngle, Real aReal)
            {
                return anAngle / aReal;
            },
            is_operator()
        )
        .def(
            "__imul__",
            [](const Angle& anAngle, Real aReal)
            {
                return anAngle * aReal;
            },
            is_operator()
        )
        .def(
            "__itruediv__",
            [](const Angle& anAngle, Real aReal)
            {
                return anAngle / aReal;
            },
            is_operator()
        )

        .def("__str__", &(shiftToString<Angle>))
        .def(
            "__repr__",
            +[](const Angle& anAngle) -> std::string
            {
                return anAngle.toString();
            }
        )

        .def("is_defined", &Angle::isDefined)
        .def("is_zero", &Angle::isZero)

        .def("get_unit", &Angle::getUnit)
        .def("in_unit", &Angle::in)
        .def(
            "in_radians",
            +[](const Angle& anAngle) -> Real
            {
                return anAngle.inRadians();
            }
        )
        .def(
            "in_degrees",
            +[](const Angle& anAngle) -> Real
            {
                return anAngle.inDegrees();
            }
        )
        .def(
            "in_arcminutes",
            +[](const Angle& anAngle) -> Real
            {
                return anAngle.inArcminutes();
            }
        )
        .def(
            "in_arcseconds",
            +[](const Angle& anAngle) -> Real
            {
                return anAngle.inArcseconds();
            }
        )
        .def("in_revolutions", &Angle::inRevolutions)
        .def("to_string", &Angle::toString, "aPrecision"_a = Integer::Undefined())

        .def_static("undefined", &Angle::Undefined)
        .def_static("zero", &Angle::Zero)
        .def_static("half_pi", &Angle::HalfPi)
        .def_static("pi", &Angle::Pi)
        .def_static("two_pi", &Angle::TwoPi)
        .def_static("radians", &Angle::Radians)
        .def_static("degrees", &Angle::Degrees)
        .def_static("arcminutes", &Angle::Arcminutes)
        .def_static("arcseconds", &Angle::Arcseconds)
        .def_static("revolutions", &Angle::Revolutions)
        .def(
            "between_vector2d",
            +[](const Vector2d& aFirstVector, const Vector2d& aSecondVector) -> Angle
            {
                return Angle::Between(aFirstVector, aSecondVector);
            }
        )
        .def(
            "between_vector3d",
            +[](const Vector3d& aFirstVector, const Vector3d& aSecondVector) -> Angle
            {
                return Angle::Between(aFirstVector, aSecondVector);
            }
        )
        .def_static("parse", &Angle::Parse)
        .def_static("string_from_unit", &Angle::StringFromUnit)
        .def_static("symbol_from_unit", &Angle::SymbolFromUnit)

        ;

    enum_<Angle::Unit>(angle, "Unit")

        .value("Undefined", Angle::Unit::Undefined)
        .value("Radian", Angle::Unit::Radian)
        .value("Degree", Angle::Unit::Degree)
        .value("Arcminute", Angle::Unit::Arcminute)
        .value("Arcsecond", Angle::Unit::Arcsecond)
        .value("Revolution", Angle::Unit::Revolution)

        ;

    implicitly_convertible<ostk::physics::units::Angle, ostk::math::geom::Angle>();
    implicitly_convertible<ostk::math::geom::Angle, ostk::physics::units::Angle>();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
