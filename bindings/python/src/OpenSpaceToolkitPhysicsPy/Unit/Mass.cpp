/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Unit/Mass.hpp>

inline void OpenSpaceToolkitPhysicsPy_Unit_Mass(nanobind::module_& aModule)
{
    using namespace nanobind;

    using ostk::core::type::String;

    using ostk::physics::unit::Mass;

    class_<Mass> mass(
        aModule,
        "Mass",
        R"doc(
            Mass.

            https://en.wikipedia.org/wiki/Mass
        )doc"
    );

    mass.def(
            init<double, Mass::Unit>(),
            R"doc(
            Constructor.

            Args:
                aReal (float): A real number.
                aUnit (Mass.Unit): A mass unit.
        )doc"
    )

        .def(
            "__eq__",
            [](const Mass& self, const Mass& other)
            {
                return self == other;
            },
            is_operator()
        )
        .def(
            "__ne__",
            [](const Mass& self, const Mass& other)
            {
                return self != other;
            },
            is_operator()
        )

        .def(
            "__lt__",
            [](const Mass& self, const Mass& other)
            {
                return self < other;
            },
            is_operator()
        )
        .def(
            "__le__",
            [](const Mass& self, const Mass& other)
            {
                return self <= other;
            },
            is_operator()
        )
        .def(
            "__gt__",
            [](const Mass& self, const Mass& other)
            {
                return self > other;
            },
            is_operator()
        )
        .def(
            "__ge__",
            [](const Mass& self, const Mass& other)
            {
                return self >= other;
            },
            is_operator()
        )

        .def(
            "__add__",
            [](const Mass& self, const Mass& other)
            {
                return self + other;
            },
            is_operator()
        )
        .def(
            "__sub__",
            [](const Mass& self, const Mass& other)
            {
                return self - other;
            },
            is_operator()
        )
        .def(
            "__mul__",
            [](const Mass& self, double other)
            {
                return self * other;
            },
            is_operator()
        )
        .def(
            "__truediv__",
            [](const Mass& self, double other)
            {
                return self / other;
            },
            is_operator()
        )
        .def(
            "__rmul__",
            [](const Mass& self, double other)
            {
                return other * self;
            },
            is_operator()
        )

        .def(
            "__iadd__",
            [](Mass& self, const Mass& other) -> Mass&
            {
                self += other;
                return self;
            },
            rv_policy::none,
            is_operator()
        )
        .def(
            "__isub__",
            [](Mass& self, const Mass& other) -> Mass&
            {
                self -= other;
                return self;
            },
            rv_policy::none,
            is_operator()
        )
        .def(
            "__imul__",
            [](Mass& self, double other) -> Mass&
            {
                self *= other;
                return self;
            },
            rv_policy::none,
            is_operator()
        )
        .def(
            "__itruediv__",
            [](Mass& self, double other) -> Mass&
            {
                self /= other;
                return self;
            },
            rv_policy::none,
            is_operator()
        )

        .def(
            "__pos__",
            [](const Mass& self)
            {
                return +self;
            },
            is_operator()
        )
        .def(
            "__neg__",
            [](const Mass& self)
            {
                return -self;
            },
            is_operator()
        )

        .def("__str__", &(shiftToString<Mass>))
        .def(
            "__repr__",
            +[](const Mass& aMass) -> std::string
            {
                return aMass.toString();
            }
        )

        .def(
            "get_unit",
            &Mass::getUnit,
            R"doc(
                Get the mass unit.

                Returns:
                    Mass.Unit: Mass unit.
            )doc"
        )
        .def(
            "in_unit",
            &Mass::in,
            R"doc(
                Convert mass to unit.

                Returns:
                    float: Mass in unit.
            )doc"
        )
        .def(
            "in_kilograms",
            &Mass::inKilograms,
            R"doc(
                Convert mass to kilograms.

                Returns:
                    float: Mass in kilograms.
            )doc"
        )
        .def(
            "to_string",
            &Mass::toString,
            "aPrecision"_a = -1,
            R"doc(
                Convert mass to string.

                Args:
                    aPrecision (int): Precision.

                Returns:
                    str: Mass as string.
            )doc"
        )

        .def_static(
            "kilograms",
            &Mass::Kilograms,
            R"doc(
                Create a mass in kilograms.

                Returns:
                    Mass: A mass in kilograms.
            )doc"
        )
        .def_static(
            "parse",
            &Mass::Parse,
            R"doc(
                Parse a mass.

                Returns:
                    Mass: A mass.
            )doc"
        )
        .def_static(
            "string_from_unit",
            &Mass::StringFromUnit,
            R"doc(
                Get string from unit.

                Returns:
                    str: A string.
            )doc"
        )
        .def_static(
            "symbol_from_unit",
            &Mass::SymbolFromUnit,
            R"doc(
                Get symbol from unit.

                Returns:
                    str: A symbol.
            )doc"
        )

        ;

    enum_<Mass::Unit>(mass, "Unit")

        .value(
            "Kilogram",
            Mass::Unit::Kilogram,
            R"doc(
                Kilogram (SI).
            )doc"
        )
        .value(
            "Pound",
            Mass::Unit::Pound,
            R"doc(
                Pound.
            )doc"
        )
        .value(
            "Tonne",
            Mass::Unit::Tonne,
            R"doc(
                Tonne.
            )doc"
        )

        ;
}
