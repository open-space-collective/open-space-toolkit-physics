/// Apache License 2.0

#include <OpenSpaceToolkitPhysicsPy/Utility/ArrayCasting.hpp>
#include <OpenSpaceToolkitPhysicsPy/Utility/DateTimeCasting.hpp>
#include <OpenSpaceToolkitPhysicsPy/Utility/EigenSequenceCasting.hpp>
#include <OpenSpaceToolkitPhysicsPy/Utility/ShiftToString.hpp>
#include <nanobind/eigen/dense.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/stl/chrono.h>

#include <OpenSpaceToolkitPhysicsPy/Coordinate.cpp>
#include <OpenSpaceToolkitPhysicsPy/Data.cpp>
#include <OpenSpaceToolkitPhysicsPy/Environment.cpp>
#include <OpenSpaceToolkitPhysicsPy/Manager.cpp>
#include <OpenSpaceToolkitPhysicsPy/Time.cpp>
#include <OpenSpaceToolkitPhysicsPy/Unit.cpp>

NB_MODULE(OpenSpaceToolkitPhysicsPy, m)
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
    OpenSpaceToolkitPhysicsPy_Manager(m);
    OpenSpaceToolkitPhysicsPy_Unit(m);
    OpenSpaceToolkitPhysicsPy_Time(m);
    OpenSpaceToolkitPhysicsPy_Coordinate(m);
    OpenSpaceToolkitPhysicsPy_Environment(m);
    OpenSpaceToolkitPhysicsPy_Data(m);
}
