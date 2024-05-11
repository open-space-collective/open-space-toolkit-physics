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

    class_<Vector>(aModule, "Vector",
        R"doc(
            Vector quantity

        )doc"
    )

        .def(init<const Vector3d&, const Unit&, const Shared<const Frame>&>(), arg("value"), arg("unit"), arg("frame"),
            R"doc(
                Construct a Vector.

                Args:
                    value (Vector3d): Value.
                    unit (Unit): Unit.
                    frame (Frame): Frame.
            )doc"
        )

        .def(self == self,
            R"doc(
                Equality operator.

                Args:
                    other (Vector): Other vector.

                Returns:
                    bool: True if equal.
            )doc"
        )
        .def(self != self,
            R"doc(
                Inequality operator.

                Args:
                    other (Vector): Other vector.

                Returns:
                    bool: True if not equal.
            )doc"
        )

        .def("__str__", &(shiftToString<Vector>))
        .def("__repr__", &(shiftToString<Vector>))

        .def("is_defined", &Vector::isDefined,
            R"doc(
                Check if the vector is defined.

                Returns:
                    bool: True if defined.
            )doc"
        )
        .def("get_value", &Vector::getValue,
            R"doc(
                Get value.

                Returns:
                    Vector3d: Value.
            )doc"
        )
        .def("get_unit", &Vector::getUnit,
            R"doc(
                Get unit.

                Returns:
                    Unit: Unit.
            )doc"
        )
        .def("get_frame", &Vector::getFrame,
            R"doc(
                Get frame.

                Returns:
                    Frame: Frame.
            )doc"
        )
        .def("in_unit", &Vector::inUnit, arg("unit"),
            R"doc(
                Convert to unit.

                Args:
                    unit (Unit): Unit.

                Returns:
                    Vector: Vector in unit.
            )doc"
        )
        .def("in_frame", &Vector::inFrame, arg("frame"), arg("instant"),
            R"doc(
                Convert to frame.

                Args:
                    frame (Frame): Frame.
                    instant (Instant): Instant.

                Returns:
                    Vector: Vector in frame.
            )doc"
        )
        .def("to_string", &Vector::toString, arg("precision") = 6,
            R"doc(
                Convert to (formatted) string.

                Args:
                    precision (Integer): Precision.

                Returns:
                    str: String representation.
            )doc"
        )

        .def_static("undefined", &Vector::Undefined,
            R"doc(
                Create an undefined vector.

                Returns:
                    Vector: Undefined vector.
            )doc"
        )

        ;
}
