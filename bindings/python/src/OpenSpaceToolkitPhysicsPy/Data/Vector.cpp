/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Data/Vector.hpp>

inline void OpenSpaceToolkitPhysicsPy_Data_Vector(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Shared;

    using ostk::mathematics::object::Vector3d;

    using ostk::physics::Unit;
    using ostk::physics::data::Vector;
    using ostk::physics::coordinate::Frame;

    class_<Vector>(aModule, "Vector")

        .def(init<const Vector3d&, const Unit&, const Shared<const Frame>&>(), arg("value"), arg("unit"), arg("frame"))

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Vector>))
        .def("__repr__", &(shiftToString<Vector>))

        .def("is_defined", &Vector::isDefined)
        .def("get_value", &Vector::getValue)
        .def("get_unit", &Vector::getUnit)
        .def("get_frame", &Vector::getFrame)
        .def("in_unit", &Vector::inUnit, arg("unit"))
        .def("in_frame", &Vector::inFrame, arg("frame"), arg("instant"))
        .def("to_string", &Vector::toString)
        
        .def_static("undefined", &Vector::Undefined)

        ;
}
