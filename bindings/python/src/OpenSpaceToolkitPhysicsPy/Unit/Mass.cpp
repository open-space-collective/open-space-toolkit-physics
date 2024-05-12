/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Unit/Mass.hpp>

inline void OpenSpaceToolkitPhysicsPy_Unit_Mass(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Integer;
    using ostk::core::type::Real;
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
            init<Real, Mass::Unit>(),
            R"doc(
            Constructor.

            Args:
                aReal (Real): A real number.
                aUnit (Mass.Unit): A mass unit.
        )doc"
    )

        .def(self == self)
        .def(self != self)

        // .def("__str__", &(shiftToString<Mass>))
        .def(
            "__repr__",
            +[](const Mass& aMass) -> std::string
            {
                return aMass.toString();
            }
        )

        .def(
            "is_defined",
            &Mass::isDefined,
            R"doc(
                Check if the mass is defined.

                Returns:
                    bool: True if defined.
            )doc"
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
            "aPrecision"_a = Integer::Undefined(),
            R"doc(
                Convert mass to string.

                Args:
                    aPrecision (int): Precision.

                Returns:
                    str: Mass as string.
            )doc"
        )

        .def_static(
            "undefined",
            &Mass::Undefined,
            R"doc(
                Get an undefined mass.

                Returns:
                    Mass: An undefined mass.
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
            "Undefined",
            Mass::Unit::Undefined,
            R"doc(
                Undefined.
            )doc"
        )
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
