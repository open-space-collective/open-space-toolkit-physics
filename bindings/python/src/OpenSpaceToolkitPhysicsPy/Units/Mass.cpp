/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Units/Mass.hpp>

inline void OpenSpaceToolkitPhysicsPy_Units_Mass(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::types::Integer;
    using ostk::core::types::Real;
    using ostk::core::types::String;

    using ostk::physics::units::Mass;

    class_<Mass> mass(aModule, "Mass");

    mass.def(init<Real, Mass::Unit>())

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

        .def("is_defined", &Mass::isDefined)

        .def("get_unit", &Mass::getUnit)
        .def("in_unit", &Mass::in)
        .def("in_kilograms", &Mass::inKilograms)
        .def("to_string", &Mass::toString, "aPrecision"_a = Integer::Undefined())

        .def_static("undefined", &Mass::Undefined)
        .def_static("kilograms", &Mass::Kilograms)
        .def_static("parse", &Mass::Parse)
        .def_static("string_from_unit", &Mass::StringFromUnit)
        .def_static("symbol_from_unit", &Mass::SymbolFromUnit)

        ;

    enum_<Mass::Unit>(mass, "Unit")

        .value("Undefined", Mass::Unit::Undefined)
        .value("Kilogram", Mass::Unit::Kilogram)
        .value("Pound", Mass::Unit::Pound)
        .value("Tonne", Mass::Unit::Tonne)

        ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
