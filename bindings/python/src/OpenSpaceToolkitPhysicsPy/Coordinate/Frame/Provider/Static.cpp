/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/Static.hpp>

inline void OpenSpaceToolkitPhysicsPy_Coordinate_Frame_Provider_Static(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Shared;

    using ostk::physics::coordinate::Transform;
    using ostk::physics::coordinate::frame::Provider;
    using ostk::physics::coordinate::frame::provider::Static;

    class_<Static, Shared<Static>, Provider>(aModule, "Static",
        R"doc(
            Static provider.

        )doc"
    )

        .def(init<const Transform&>(),
            R"doc(
                Constructor.
            )doc"
        )

        .def("is_defined", &Static::isDefined,
            R"doc(
                Check if the Static provider is defined

                Returns:
                    bool: True if defined
            )doc"
        )

        .def("get_transform_at", &Static::getTransformAt, arg("instant"),
            R"doc(
                Get the transform at a given instant.

                Args:
                    instant (Instant): An instant

                Returns:
                    Transform: Transform
            )doc"
        )

        ;
}
