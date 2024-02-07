/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/Static.hpp>

inline void OpenSpaceToolkitPhysicsPy_Coordinate_Frame_Provider_Static(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Shared;

    using ostk::physics::coord::Transform;
    using ostk::physics::coord::frame::Provider;
    using ostk::physics::coord::frame::provider::Static;

    class_<Static, Shared<Static>, Provider>(aModule, "Static")

        .def(init<const Transform&>())

        .def("is_defined", &Static::isDefined)

        .def("get_transform_at", &Static::getTransformAt, arg("instant"))

        ;
}
