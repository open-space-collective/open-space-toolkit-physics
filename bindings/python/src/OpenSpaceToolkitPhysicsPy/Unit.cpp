/// Apache License 2.0

#include <OpenSpaceToolkitPhysicsPy/Unit/Derived.cpp>
#include <OpenSpaceToolkitPhysicsPy/Unit/Derived/Angle.cpp>
#include <OpenSpaceToolkitPhysicsPy/Unit/ElectricCurrent.cpp>
#include <OpenSpaceToolkitPhysicsPy/Unit/Length.cpp>
#include <OpenSpaceToolkitPhysicsPy/Unit/Mass.cpp>
#include <OpenSpaceToolkitPhysicsPy/Unit/Time.cpp>

inline void OpenSpaceToolkitPhysicsPy_Unit(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::physics::Unit;

    class_<Unit> unit_class(
        aModule,
        "Unit",
        R"doc(
            Unit

            A unit of measurement is a definite magnitude of a quantity, defined and adopted by
            convention or by law, that is used as a standard for measurement of the same kind of
            quantity. Any other quantity of that kind can be expressed as a multiple of the unit of
            measurement.

            :see: https://en.wikipedia.org/wiki/Unit_of_measurement

        )doc"
    );

    enum_<Unit::Type>(unit_class, "Type")
        .value(
            "Undefined",
            Unit::Type::Undefined,
            R"doc(
                Undefined unit type.
            )doc"
        )
        .value(
            "NoneType",
            Unit::Type::None,
            R"doc(
                None unit type.
            )doc"
        )
        .value(
            "Length",
            Unit::Type::Length,
            R"doc(
                Length unit type.
            )doc"
        )
        .value(
            "Mass",
            Unit::Type::Mass,
            R"doc(
                Mass unit type.
            )doc"
        )
        .value(
            "Time",
            Unit::Type::Time,
            R"doc(
                Time unit type.
            )doc"
        )
        .value(
            "Temperature",
            Unit::Type::Temperature,
            R"doc(
                Temperature unit type.
            )doc"
        )
        .value(
            "ElectricCurrent",
            Unit::Type::ElectricCurrent,
            R"doc(
                Electric current unit type.
            )doc"
        )
        .value(
            "LuminousIntensity",
            Unit::Type::LuminousIntensity,
            R"doc(
                Luminous intensity unit type.
            )doc"
        )
        .value(
            "Derived",
            Unit::Type::Derived,
            R"doc(
                Derived unit type.
            )doc"
        )

        ;

    unit_class

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Unit>))
        .def("__repr__", &(shiftToString<Unit>))
        .def(
            "is_defined",
            &Unit::isDefined,
            R"doc(
                Check if the unit is defined.

                Returns:
                    bool: True if defined.
            )doc"
        )
        .def(
            "is_none",
            &Unit::isNone,
            R"doc(
                Check if the unit is none.

                Returns:
                    bool: True if none.
            )doc"
        )
        .def(
            "get_type",
            &Unit::getType,
            R"doc(
                Get the unit type.

                Returns:
                    Type: Unit type.
            )doc"
        )
        .def(
            "ratio_to",
            &Unit::ratioTo,
            arg("unit"),
            R"doc(
                Get the ratio to another unit.

                Args:
                    unit (Unit): Another unit.

                Returns:
                    float:Ratio to another unit.
            )doc"
        )
        .def(
            "to_string",
            &Unit::toString,
            R"doc(
                Get the string representation of the unit.

                Returns:
                    str: String representation.
            )doc"
        )
        .def_static(
            "undefined",
            &Unit::Undefined,
            R"doc(
                Create an undefined unit.

                Returns:
                    Unit: Undefined unit.
            )doc"
        )
        .def_static(
            "none",
            &Unit::None,
            R"doc(
                Create a none unit.

                Returns:
                    Unit: None unit.
            )doc"
        )
        .def_static(
            "length",
            &Unit::Length,
            arg("length_unit"),
            R"doc(
                Create a length unit.

                Args:
                    length_unit (unit.Length.Unit): A length unit.

                Returns:
                    Unit: Length unit.
            )doc"
        )
        .def_static(
            "derived",
            &Unit::Derived,
            arg("derived_unit"),
            R"doc(
                Create a derived unit.

                Args:
                    derived_unit (unit.Derived.Unit): A derived unit.

                Returns:
                    Unit: Derived unit.
            )doc"
        )
        .def_static(
            "string_from_type",
            &Unit::StringFromType,
            arg("type"),
            R"doc(
                Get the string representation of a unit type.

                Args:
                    type (Type): Unit type.

                Returns:
                    str: String representation.
            )doc"
        );

    // Create "unit" python submodule
    auto unit = aModule.def_submodule("unit");

    // Add objects to python "unit" submodules
    OpenSpaceToolkitPhysicsPy_Unit_Length(unit);
    OpenSpaceToolkitPhysicsPy_Unit_Mass(unit);
    OpenSpaceToolkitPhysicsPy_Unit_Time(unit);
    OpenSpaceToolkitPhysicsPy_Unit_ElectricCurrent(unit);
    OpenSpaceToolkitPhysicsPy_Unit_Derived(unit);
    OpenSpaceToolkitPhysicsPy_Unit_Derived_Angle(unit);
}
