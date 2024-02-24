/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Data/Direction.hpp>

inline void OpenSpaceToolkitPhysicsPy_Data_Direction(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Shared;

    using ostk::mathematics::object::Vector3d;
    
    using ostk::physics::coordinate::Frame;
    using ostk::physics::data::Direction;
    using ostk::physics::data::Vector;

    class_<Direction, Vector>(aModule, "Direction")

        .def(init<const Vector3d&, const Shared<const Frame>&>(), arg("value"), arg("frame"))

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Direction>))
        .def("__repr__", &(shiftToString<Direction>))

        .def_static("undefined", &Direction::Undefined)

        ;
}
