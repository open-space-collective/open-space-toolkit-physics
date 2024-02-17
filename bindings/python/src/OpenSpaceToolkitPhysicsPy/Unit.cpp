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

    class_<Unit> unit_class(aModule, "Unit");

    enum_<Unit::Type>(unit_class, "Type")
        .value("Undefined", Unit::Type::Undefined)
        .value("None", Unit::Type::None)
        .value("Length", Unit::Type::Length)
        .value("Mass", Unit::Type::Mass)
        .value("Time", Unit::Type::Time)
        .value("Temperature", Unit::Type::Temperature)
        .value("ElectricCurrent", Unit::Type::ElectricCurrent)
        .value("LuminousIntensity", Unit::Type::LuminousIntensity)
        .value("Derived", Unit::Type::Derived)
        
        ;
    
    unit_class
        .def("is_defined", &Unit::isDefined)
        .def("is_none", &Unit::isNone)
        .def("get_type", &Unit::getType)
        .def("ratio_to", &Unit::ratioTo, arg("unit"))
        .def("to_string", &Unit::toString)
        .def_static("undefined", &Unit::Undefined)
        .def_static("none", &Unit::None)
        .def_static("length", &Unit::Length, arg("length_unit"))
        .def_static("derived", &Unit::Derived, arg("derived_unit"))
        .def_static("string_from_type", &Unit::StringFromType, arg("type"));

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
