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
                +[] (const pybind11::object& aGeneratorObject) -> Shared<Dynamic>
                {

                    const auto generatorProxy = [aGeneratorObject] (const Instant& anInstant) -> Transform
                    {
                        return pybind11::cast<Transform>(aGeneratorObject(anInstant)) ;
                    } ;

                    return std::make_shared<Dynamic>(generatorProxy) ;

                }
            )
        )

        .def("is_defined", &Dynamic::isDefined)

        .def("get_transform_at", &Dynamic::getTransformAt)

        .def_static("undefined", &Dynamic::Undefined)

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
