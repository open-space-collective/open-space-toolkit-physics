/// Apache License 2.0

#include <OpenSpaceToolkitPhysicsPy/Data/Direction.cpp>
#include <OpenSpaceToolkitPhysicsPy/Data/Manager.cpp>
#include <OpenSpaceToolkitPhysicsPy/Data/Manifest.cpp>
#include <OpenSpaceToolkitPhysicsPy/Data/Provider.cpp>
#include <OpenSpaceToolkitPhysicsPy/Data/Scalar.cpp>
#include <OpenSpaceToolkitPhysicsPy/Data/Vector.cpp>

inline void OpenSpaceToolkitPhysicsPy_Data(nanobind::module_& aModule)
{
    using namespace nanobind;

    // Create "data" python submodule
    auto data = aModule.def_submodule("data");

    // Add objects to python "data" submodules
    OpenSpaceToolkitPhysicsPy_Data_Scalar(data);
    OpenSpaceToolkitPhysicsPy_Data_Vector(data);
    OpenSpaceToolkitPhysicsPy_Data_Direction(data);
    OpenSpaceToolkitPhysicsPy_Data_Manager(data);
    OpenSpaceToolkitPhysicsPy_Data_Manifest(data);
    OpenSpaceToolkitPhysicsPy_Data_Provider(data);
}
