/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider.hpp>

#include <OpenSpaceToolkitPhysicsPy/Coordinate/Frame/Provider/Dynamic.cpp>
#include <OpenSpaceToolkitPhysicsPy/Coordinate/Frame/Provider/IAU.cpp>
#include <OpenSpaceToolkitPhysicsPy/Coordinate/Frame/Provider/IERS.cpp>
#include <OpenSpaceToolkitPhysicsPy/Coordinate/Frame/Provider/Static.cpp>

inline void OpenSpaceToolkitPhysicsPy_Coordinate_Frame_Provider(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Shared;

    using ostk::physics::coordinate::frame::Provider;

    class_<Provider, Shared<Provider>>(aModule, "Provider",
        R"doc(
            Frame provider.
        )doc"
    )

        .def("is_defined", &Provider::isDefined,,R"doc()doc")

        .def("get_transform_at", &Provider::getTransformAt, arg("instant"),R"doc()doc")

        ;

    // Create "provider" python submodule
    auto provider = aModule.def_submodule("provider");


    // Add objects to python "provider" submodules
    OpenSpaceToolkitPhysicsPy_Coordinate_Frame_Provider_Static(provider);
    OpenSpaceToolkitPhysicsPy_Coordinate_Frame_Provider_Dynamic(provider);
    OpenSpaceToolkitPhysicsPy_Coordinate_Frame_Provider_IERS(provider);
    OpenSpaceToolkitPhysicsPy_Coordinate_Frame_Provider_IAU(provider);

    // register_ptr_to_python<Shared<const Provider>>() ;

    // implicitly_convertible<Shared<Provider>, Shared<const Provider>>() ;
}
