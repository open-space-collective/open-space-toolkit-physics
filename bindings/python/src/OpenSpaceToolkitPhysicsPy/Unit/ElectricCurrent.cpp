/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Object/Interval.hpp>

#include <OpenSpaceToolkit/Physics/Unit/ElectricCurrent.hpp>

inline void OpenSpaceToolkitPhysicsPy_Unit_ElectricCurrent(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Integer;
    using ostk::core::type::Real;

    using ostk::physics::unit::ElectricCurrent;

    class_<ElectricCurrent> elec_current(
        aModule,
        "ElectricCurrent",
        R"doc(
            Electric current.

            https://en.wikipedia.org/wiki/Electric_current
        )doc"
    );

    elec_current
        .def(
            init<Real, ElectricCurrent::Unit>(),
            R"doc(
                Constructor.

                Args:
                    aReal (Real): A real number.
                    aUnit (ElectricCurrent.Unit): An electric current unit.
            )doc"
        )

        .def(self == self)
        .def(self != self)

        // .def(self < self)
        // .def(self <= self)
        // .def(self > self)
        // .def(self >= self)

        // .def(self + self)
        // .def(self - self)

        // .def(self += self)
        // .def(self -= self)

        // .def("__mul__", [](const ElectricCurrent &anElectricCurrent, Real aReal) {return anElectricCurrent * aReal;},
        // is_operator()) .def("__truediv__", [](const ElectricCurrent &anElectricCurrent, Real aReal) {return
        // anElectricCurrent / aReal;}, is_operator()) .def("__imul__", [](const ElectricCurrent &anElectricCurrent,
        // Real aReal) {return anElectricCurrent * aReal;}, is_operator()) .def("__itruediv__", [](const ElectricCurrent
        // &anElectricCurrent, Real aReal) {return anElectricCurrent / aReal;}, is_operator())

        // .def("__str__", &(shiftToString<ElectricCurrent>))
        .def(
            "__repr__",
            +[](const ElectricCurrent& aElectricCurrent) -> std::string
            {
                return aElectricCurrent.toString();
            }
        )

        .def(
            "is_defined",
            &ElectricCurrent::isDefined,
            R"doc(
                Check if the electric current is defined.

                Returns:
                    bool: True if defined.
            )doc"
        )

        .def(
            "get_unit",
            &ElectricCurrent::getUnit,
            R"doc(
                Get the electric current unit.

                Returns:
                    ElectricCurrent.Unit: The electric current unit.
            )doc"
        )
        .def(
            "in_unit",
            &ElectricCurrent::in,
            R"doc(
                Get the electric current in a given unit.

                Returns:
                    float: The electric current in the given unit.
            )doc"
        )
        .def(
            "in_amperes",
            &ElectricCurrent::inAmperes,
            R"doc(
                Get the electric current in amperes.

                Returns:
                    float: The electric current in amperes.
            )doc"
        )
        .def(
            "to_string",
            &ElectricCurrent::toString,
            "aPrecision"_a = Integer::Undefined(),
            R"doc(
                Get the string representation of the electric current.

                Args:
                    aPrecision (int): A precision.

                Returns:
                    str: The string representation.
            )doc"
        )

        .def_static(
            "undefined",
            &ElectricCurrent::Undefined,
            R"doc(
                Get an undefined electric current.

                Returns:
                    ElectricCurrent: An undefined electric current.
            )doc"
        )
        .def_static(
            "amperes",
            &ElectricCurrent::Amperes,
            R"doc(
                Construct an electric current in amperes.

                Returns:
                    ElectricCurrent: An electric current in amperes.
            )doc"
        )
        // .def_static("parse", &ElectricCurrent::Parse)
        .def_static(
            "string_from_unit",
            &ElectricCurrent::StringFromUnit,
            R"doc(
                Get the string representation of an electric current unit.

                Returns:
                    str: The string representation.
            )doc"
        )
        .def_static(
            "symbol_from_unit",
            &ElectricCurrent::SymbolFromUnit,
            R"doc(
                Get the symbol of an electric current unit.

                Returns:
                    str: The symbol.
            )doc"
        )

        ;

    enum_<ElectricCurrent::Unit>(elec_current, "Unit")

        .value(
            "Undefined",
            ElectricCurrent::Unit::Undefined,
            R"doc(
                Undefined.
            )doc"
        )
        .value(
            "Ampere",
            ElectricCurrent::Unit::Ampere,
            R"doc(
                Ampere (SI).
            )doc"
        )

        ;
}
