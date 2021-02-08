////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           bindings/python/src/OpenSpaceToolkitPhysicsPy/Coordinate/Frame/Providers/Dynamic.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/Dynamic.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Transform.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitPhysicsPy_Coordinate_Frame_Providers_Dynamic (        pybind11::module& aModule                                 )
{

    using namespace pybind11 ;

    using ostk::core::types::Shared ;

    using ostk::physics::time::Instant ;
    using ostk::physics::coord::Transform ;
    using ostk::physics::coord::frame::Provider ;
    using ostk::physics::coord::frame::provider::Dynamic ;

    class_<Dynamic, Shared<Dynamic>, Provider>(aModule, "Dynamic")

        // Custom Constructor for Dynamic
        .def(
            "__init__",
            (
                +[] (Dynamic& aDynamicFrameProvider, const pybind11::object& aGeneratorObject)
                {

                    const auto generatorProxy = [aGeneratorObject] (const Instant& anInstant) -> Transform
                    {
                        return pybind11::cast<Transform>(aGeneratorObject(anInstant)) ;
                    } ;

                    // might need to add return type to the function (Shared<Dynamic>)
                    // return std::make_shared<Dynamic>(generatorProxy) ;
                    // aDynamicFrameProviderPtr =  std::make_shared<Dynamic>(generatorProxy) ; "RuntimeError: Unable to cast from non-held to held instance (T& to Holder<T>)"
                    // Will need to check resources with that formulation
                    new (&aDynamicFrameProvider) Dynamic(generatorProxy) ;

                }
            )
        )

        .def("is_defined", &Dynamic::isDefined)

        .def("get_transform_at", &Dynamic::getTransformAt)

        .def_static("undefined", &Dynamic::Undefined)

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
