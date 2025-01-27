/// Apache License 2.0

#include <OpenSpaceToolkitPhysicsPy/Coordinate/Axes.cpp>
#include <OpenSpaceToolkitPhysicsPy/Coordinate/Frame.cpp>
#include <OpenSpaceToolkitPhysicsPy/Coordinate/Position.cpp>
#include <OpenSpaceToolkitPhysicsPy/Coordinate/Spherical.cpp>
#include <OpenSpaceToolkitPhysicsPy/Coordinate/Transform.cpp>
#include <OpenSpaceToolkitPhysicsPy/Coordinate/Velocity.cpp>

inline void OpenSpaceToolkitPhysicsPy_Coordinate(pybind11::module& aModule)
{
    // Create "coordinate" python submodule
    auto coordinate = aModule.def_submodule("coordinate");

    // Add objects to python "coordinate" submodules
    OpenSpaceToolkitPhysicsPy_Coordinate_Spherical(coordinate);
    OpenSpaceToolkitPhysicsPy_Coordinate_Position(coordinate);
    OpenSpaceToolkitPhysicsPy_Coordinate_Velocity(coordinate);
    OpenSpaceToolkitPhysicsPy_Coordinate_Frame(coordinate);
    OpenSpaceToolkitPhysicsPy_Coordinate_Transform(coordinate);
    OpenSpaceToolkitPhysicsPy_Coordinate_Axes(
        coordinate
    );  // Cannot be binded without Frame.cpp (class forward declared)
}
