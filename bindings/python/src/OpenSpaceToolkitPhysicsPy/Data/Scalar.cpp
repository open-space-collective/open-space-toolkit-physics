/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Data/Scalar.hpp>

inline void OpenSpaceToolkitPhysicsPy_Data_Scalar(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Real;
    using ostk::core::type::Integer;

    using ostk::physics::Unit;
    using ostk::physics::data::Scalar;

    class_<Scalar>(aModule, "Scalar")

        .def(init<const Real&, const Unit&>(), arg("value"), arg("unit"))

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Scalar>))
        .def("__repr__", &(shiftToString<Scalar>))

        .def("is_defined", &Scalar::isDefined)
        .def("get_value", &Scalar::getValue)
        .def("get_unit", &Scalar::getUnit)
        .def("in_unit", &Scalar::inUnit, arg("unit"))
        .def("to_string", &Scalar::toString, arg("precision") = Integer::Undefined())

        .def_static("undefined", &Scalar::Undefined)

        ;
}
