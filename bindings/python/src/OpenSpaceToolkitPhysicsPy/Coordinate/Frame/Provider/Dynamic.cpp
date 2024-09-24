/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/Dynamic.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Transform.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

inline void OpenSpaceToolkitPhysicsPy_Coordinate_Frame_Provider_Dynamic(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Shared;

    using ostk::physics::coordinate::frame::Provider;
    using ostk::physics::coordinate::frame::provider::Dynamic;
    using ostk::physics::coordinate::Transform;
    using ostk::physics::time::Instant;

    class_<Dynamic, Shared<Dynamic>, Provider>(
        aModule,
        "Dynamic",
        R"doc(
            Dynamic provider.

        )doc"
    )

        // Custom Constructor for Dynamic
        .def(
            "__init__",
            (+[](Dynamic& aDynamicFrameProvider, const pybind11::object& aGeneratorObject)
             {
                 const auto generatorProxy = [aGeneratorObject](const Instant& anInstant) -> Transform
                 {
                     return pybind11::cast<Transform>(aGeneratorObject(anInstant));
                 };

                 // might need to add return type to the function (Shared<Dynamic>)
                 // return std::make_shared<Dynamic>(generatorProxy) ;
                 // aDynamicFrameProviderPtr =  std::make_shared<Dynamic>(generatorProxy) ; "RuntimeError: Unable to
                 // cast from non-held to held instance (T& to Holder<T>)" Will need to check resources with that
                 // formulation
                 new (&aDynamicFrameProvider) Dynamic(generatorProxy);
             }),
            arg("generator"),
            R"doc(
                Constructor.

                Args:
                    generator: Generator function.

            )doc"
        )

        .def(
            "is_defined",
            &Dynamic::isDefined,
            R"doc(
                Check if the Dynamic provider is defined

                Returns:
                    bool: True if defined
            )doc"
        )

        .def(
            "get_transform_at",
            &Dynamic::getTransformAt,
            arg("instant"),
            R"doc(
                Get the transform at a given instant.

                Args:
                    instant (Instant): An instant

                Returns:
                    Transform: Transform
            )doc"
        )

        .def_static(
            "undefined",
            &Dynamic::Undefined,
            R"doc(
                Get an undefined dynamic provider. 
            )doc"
        )

        ;
}
