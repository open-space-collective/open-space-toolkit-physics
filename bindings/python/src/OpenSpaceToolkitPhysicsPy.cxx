/// Apache License 2.0

#include <OpenSpaceToolkitPhysicsPy/Utility/ArrayCasting.hpp>
#include <OpenSpaceToolkitPhysicsPy/Utility/DateTimeCasting.hpp>
#include <OpenSpaceToolkitPhysicsPy/Utility/ShiftToString.hpp>
#include <pybind11/chrono.h>
#include <pybind11/eigen.h>
#include <pybind11/numpy.h>
#include <pybind11/operators.h>
#include <pybind11/pybind11.h>

#include <OpenSpaceToolkitPhysicsPy/Coordinate.cpp>
#include <OpenSpaceToolkitPhysicsPy/Environment.cpp>
#include <OpenSpaceToolkitPhysicsPy/Time.cpp>
#include <OpenSpaceToolkitPhysicsPy/Unit.cpp>
#include <OpenSpaceToolkitPhysicsPy/Data.cpp>

PYBIND11_MODULE(OpenSpaceToolkitPhysicsPy, m)
{
    // Add optional docstring for package OpenSpaceToolkitPhysicsPy
    m.doc() = "Physical units, time, reference frames, environment modeling for OpenSpaceToolkit";

    // Change attribute __name__ to make OpenSpaceToolkitPhysicsPy invisible in modules path
    m.attr("__name__") = "ostk.physics";

// Package version information
#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif

    // Add python submodules to OpenSpaceToolkitPhysicsPy
    OpenSpaceToolkitPhysicsPy_Unit(m);
    OpenSpaceToolkitPhysicsPy_Time(m);
    OpenSpaceToolkitPhysicsPy_Coordinate(m);
    OpenSpaceToolkitPhysicsPy_Data(m);
    OpenSpaceToolkitPhysicsPy_Environment(m);
}
