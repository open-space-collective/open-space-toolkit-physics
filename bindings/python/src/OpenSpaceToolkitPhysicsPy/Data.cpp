/// Apache License 2.0

#include <OpenSpaceToolkitPhysicsPy/Data/Scalar.cpp>
#include <OpenSpaceToolkitPhysicsPy/Data/Vector.cpp>
#include <OpenSpaceToolkitPhysicsPy/Data/Direction.cpp>
#include <OpenSpaceToolkitPhysicsPy/Data/Manager.cpp>

inline void OpenSpaceToolkitPhysicsPy_Data(pybind11::module& aModule)
{
    using namespace pybind11;

    // Create "data" python submodule
    auto data = aModule.def_submodule("data");

    // Add objects to python "data" submodules
    OpenSpaceToolkitPhysicsPy_Data_Scalar(data);
    OpenSpaceToolkitPhysicsPy_Data_Vector(data);
    OpenSpaceToolkitPhysicsPy_Data_Direction(data);
    OpenSpaceToolkitPhysicsPy_Data_Manager(data);
}
