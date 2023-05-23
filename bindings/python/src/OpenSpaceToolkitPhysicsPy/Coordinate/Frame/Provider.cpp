/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitPhysicsPy_Coordinate_Frame_Provider (        pybind11::module&      aModule                                     )
{

    using namespace pybind11 ;

    using ostk::core::types::Shared ;

    using ostk::physics::coord::frame::Provider ;

    class_<Provider, Shared<Provider>>(aModule, "Provider")

        .def("is_defined", &Provider::isDefined)

        .def("get_transform_at", &Provider::getTransformAt, arg("instant"))

    ;

    // register_ptr_to_python<Shared<const Provider>>() ;

    // implicitly_convertible<Shared<Provider>, Shared<const Provider>>() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
