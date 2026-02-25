/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Unit/Derived/Angle.hpp>

inline void OpenSpaceToolkitPhysicsPy_Unit_Derived_Angle(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Integer;
    using ostk::core::type::Real;

    using ostk::mathematics::object::Vector2d;
    using ostk::mathematics::object::Vector3d;

    using ostk::physics::unit::Angle;

    // Extend the mathematics module constructor
    module math_module = module::import("ostk.mathematics.geometry");

    // Get the Mathematics Angle class
    class_<ostk::mathematics::geometry::Angle> math_angle =
        math_module.attr("Angle").cast<class_<ostk::mathematics::geometry::Angle>>();

    // Add a new constructor to the Mathematics Angle class
    math_angle.def(init<const ostk::physics::unit::Angle&>());

    class_<Angle> angle(
        aModule,
        "Angle",
        R"doc(
            Angle.
            
            :reference: https://en.wikipedia.org/wiki/Angle
            )doc"
    );

    // Define constructor
    angle
        .def(
            init<const Real&, const Angle::Unit&>(),
            arg("value"),
            arg("unit"),
            R"doc(
                Constructor.

                Args:
                    value (Real): A value.
                    unit (Unit): An angle unit.
            )doc"
        )
        .def(
            init<const ostk::mathematics::geometry::Angle&>(),
            arg("angle"),
            R"doc(
                Constructor.

                Args:
                    angle (Angle): An angle.
            )doc"
        )

        // Define methods
        .def(self == self)
        .def(self != self)

        .def(self + self)
        .def(self - self)

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

        .def(self += self)
        .def(self -= self)

        .def("__str__", &(shiftToString<Angle>))
        .def(
            "__repr__",
            +[](const Angle& anAngle) -> std::string
            {
                return anAngle.toString();
            }
        )

        .def(
            "is_defined",
            &Angle::isDefined,
            R"doc(
                Check if the angle is defined.

                Returns:
                    bool: True if defined.
            )doc"
        )
        .def(
            "is_zero",
            &Angle::isZero,
            R"doc(
                Check if the angle is zero.

                Returns:
                    bool: True if zero.
            )doc"
        )

        .def(
            "get_unit",
            &Angle::getUnit,
            R"doc(
                Get the unit of the angle.

                Returns:
                    Unit: The unit of the angle.
            )doc"
        )
        .def(
            "in_unit",
            &Angle::in,
            arg("unit"),
            R"doc(
                Get the angle in the specified unit.

                Args:
                    unit (Unit): An angle unit.

                Returns:
                    float: The angle in the specified unit.
            )doc"
        )
        .def(
            "in_radians",
            overload_cast<>(&Angle::inRadians, const_),
            R"doc(
                Get the angle in radians.

                Returns:
                    float: The angle in radians.
            )doc"
        )
        .def(
            "in_radians",
            overload_cast<const Real&, const Real&>(&Angle::inRadians, const_),
            arg("lower_bound"),
            arg("upper_bound"),
            R"doc(
                Get the angle in radians.

                Args:
                    lower_bound (Real): A lower bound.
                    upper_bound (Real): An upper bound.

                Returns:
                    float: The angle in radians.
            )doc"
        )
        .def(
            "in_degrees",
            overload_cast<>(&Angle::inDegrees, const_),
            R"doc(
                Get the angle in degrees.

                Returns:
                    float: The angle in degrees.
            )doc"
        )
        .def(
            "in_degrees",
            overload_cast<const Real&, const Real&>(&Angle::inDegrees, const_),
            arg("lower_bound"),
            arg("upper_bound"),
            R"doc(
                Get the angle in degrees.

                Args:
                    lower_bound (Real): A lower bound.
                    upper_bound (Real): An upper bound.

                Returns:
                    float: The angle in degrees.
            )doc"
        )
        .def(
            "in_arcminutes",
            overload_cast<>(&Angle::inArcminutes, const_),
            R"doc(
                Get the angle in arcminutes.

                Returns:
                    float: The angle in arcminutes.
            )doc"
        )
        .def(
            "in_arcminutes",
            overload_cast<const Real&, const Real&>(&Angle::inArcminutes, const_),
            arg("lower_bound"),
            arg("upper_bound"),
            R"doc(
                Get the angle in arcminutes.

                Args:
                    lower_bound (Real): A lower bound.
                    upper_bound (Real): An upper bound.

                Returns:
                    float: The angle in arcminutes.
            )doc"
        )
        .def(
            "in_arcseconds",
            overload_cast<>(&Angle::inArcseconds, const_),
            R"doc(
                Get the angle in arcseconds.

                Returns:
                    float: The angle in arcseconds.
            )doc"
        )
        .def(
            "in_arcseconds",
            overload_cast<const Real&, const Real&>(&Angle::inArcseconds, const_),
            arg("lower_bound"),
            arg("upper_bound"),
            R"doc(
                Get the angle in arcseconds.

                Args:
                    lower_bound (Real): A lower bound.
                    upper_bound (Real): An upper bound.

                Returns:
                    float: The angle in arcseconds.
            )doc"
        )
        .def(
            "in_revolutions",
            &Angle::inRevolutions,
            R"doc(
                Get the angle in revolutions.

                Returns:
                    float: The angle in revolutions.
            )doc"
        )
        .def(
            "to_string",
            &Angle::toString,
            arg_v("precision", Integer::Undefined(), "Integer.undefined()"),
            R"doc(
                Get the string representation of the angle.

                Args:
                    precision (int): A precision.

                Returns:
                    str: The string representation of the angle.
            )doc"
        )

        // Define static methods
        .def_static(
            "undefined",
            &Angle::Undefined,
            R"doc(
                Create an undefined angle.

                Returns:
                    Angle: An undefined angle.
            )doc"
        )
        .def_static(
            "zero",
            &Angle::Zero,
            R"doc(
                Create a zero angle.

                Returns:
                    Angle: A zero angle.
            )doc"
        )
        .def_static(
            "half_pi",
            &Angle::HalfPi,
            R"doc(
                Create a half pi angle.

                Returns:
                    Angle: A half pi angle.
            )doc"
        )
        .def_static(
            "pi",
            &Angle::Pi,
            R"doc(
                Create a pi angle.

                Returns:
                    Angle: A pi angle.
            )doc"
        )
        .def_static(
            "two_pi",
            &Angle::TwoPi,
            R"doc(
                Create a two pi angle.

                Returns:
                    Angle: A two pi angle.
            )doc"
        )
        .def_static(
            "radians",
            &Angle::Radians,
            arg("value"),
            R"doc(
                Create an angle in radians.

                Args:
                    value (Real): A value.

                Returns:
                    Angle: An angle in radians.
            )doc"
        )
        .def_static(
            "degrees",
            &Angle::Degrees,
            arg("value"),
            R"doc(
                Create an angle in degrees.

                Args:
                    value (Real): A value.

                Returns:
                    Angle: An angle in degrees.
            )doc"
        )
        .def_static(
            "arcminutes",
            &Angle::Arcminutes,
            arg("value"),
            R"doc(
                Create an angle in arcminutes.

                Args:
                    value (Real): A value.

                Returns:
                    Angle: An angle in arcminutes.
            )doc"
        )
        .def_static(
            "arcseconds",
            &Angle::Arcseconds,
            arg("value"),
            R"doc(
                Create an angle in arcseconds.

                Args:
                    value (Real): A value.

                Returns:
                    Angle: An angle in arcseconds.
            )doc"
        )
        .def_static(
            "revolutions",
            &Angle::Revolutions,
            arg("value"),
            R"doc(
                Create an angle in revolutions.

                Args:
                    value (Real): A value.

                Returns:
                    Angle: An angle in revolutions.
            )doc"
        )
        .def_static(
            "between",
            overload_cast<const Angle&, const Angle&>(&Angle::Between),
            arg("first_angle"),
            arg("second_angle"),
            R"doc(
                Compute the shortest signed angle from the first angle to the second.

                The result is in the range (-180, +180] degrees and is returned in the unit of the first angle.

                Args:
                    first_angle (Angle): The first angle.
                    second_angle (Angle): The second angle.

                Returns:
                    Angle: The shortest signed angular difference.
            )doc"
        )
        .def_static(
            "between",
            overload_cast<const Vector2d&, const Vector2d&>(&Angle::Between),
            arg("first_vector"),
            arg("second_vector"),
            R"doc(
                Create an angle between two vectors.

                Args:
                    first_vector (Vector2d): A first vector.
                    second_vector (Vector2d): A second vector.

                Returns:
                    Angle: An angle between two vectors.
            )doc"
        )
        .def_static(
            "between",
            overload_cast<const Vector3d&, const Vector3d&>(&Angle::Between),
            arg("first_vector"),
            arg("second_vector"),
            R"doc(
                Create an angle between two vectors.

                Args:
                    first_vector (np.ndarray): A first vector.
                    second_vector (np.ndarray): A second vector.

                Returns:
                    Angle: An angle between two vectors.
            )doc"
        )
        .def_static(
            "parse",
            &Angle::Parse,
            arg("string"),
            R"doc(
                Parse an angle from a string.

                Args:
                    string (str): A string.

                Returns:
                    Angle: An angle.
            )doc"
        )
        .def_static(
            "string_from_unit",
            &Angle::StringFromUnit,
            arg("unit"),
            R"doc(
                Get the string representation of an angle unit.

                Args:
                    unit (Unit): An angle unit.

                Returns:
                    str: The string representation of an angle unit.
            )doc"
        )
        .def_static(
            "symbol_from_unit",
            &Angle::SymbolFromUnit,
            arg("unit"),
            R"doc(
                Get the symbol representation of an angle unit.

                Args:
                    unit (Unit): An angle unit.

                Returns:
                    str: The symbol representation of an angle unit.
            )doc"
        )

        ;

    // Define emuneration unit for "angle"
    enum_<Angle::Unit>(angle, "Unit")
        .value(
            "Undefined",
            Angle::Unit::Undefined,
            R"doc(
                Undefined unit.
            )doc"
        )
        .value(
            "Radian",
            Angle::Unit::Radian,
            R"doc(
                Radian unit.
            )doc"
        )
        .value(
            "Degree",
            Angle::Unit::Degree,
            R"doc(
                Degree unit.
            )doc"
        )
        .value(
            "Arcminute",
            Angle::Unit::Arcminute,
            R"doc(
                Arcminute unit.
            )doc"
        )
        .value(
            "Arcsecond",
            Angle::Unit::Arcsecond,
            R"doc(
                Arcsecond unit.
            )doc"
        )
        .value(
            "Revolution",
            Angle::Unit::Revolution,
            R"doc(
                Revolution unit.
            )doc"
        )

        ;

    implicitly_convertible<ostk::physics::unit::Angle, ostk::mathematics::geometry::Angle>();
    implicitly_convertible<ostk::mathematics::geometry::Angle, ostk::physics::unit::Angle>();
}
