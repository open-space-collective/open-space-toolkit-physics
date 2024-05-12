/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Data/Scalar.hpp>

inline void OpenSpaceToolkitPhysicsPy_Data_Scalar(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Real;
    using ostk::core::type::Integer;

    using ostk::physics::Unit;
    using ostk::physics::data::Scalar;

    class_<Scalar>(
        aModule,
        "Scalar",
        R"doc(
            Scalar quantity.

            A scalar quantity is a physical quantity that can be described by a single element of a
            number field such as a real number, often accompanied by units of measurement.

            :seealso: https://en.wikipedia.org/wiki/Scalar_(physics)
            
        )doc"
    )

        .def(
            init<const Real&, const Unit&>(),
            arg("value"),
            arg("unit"),
            R"doc(
                Construct a Scalar.

                Args:
                    value (Real): Value.
                    unit (Unit): Unit.
            )doc"
        )

        .def(
            self == self,
            R"doc(
                Equality operator.

                Args:
                    other (Scalar): Other scalar.

                Returns:
                    bool: True if equal.
            )doc"
        )
        .def(
            self != self,
            R"doc(
                Inequality operator.

                Args:
                    other (Scalar): Other scalar.

                    Returns:
                        bool: True if not equal.
            )doc"
        )

        .def("__str__", &(shiftToString<Scalar>))
        .def("__repr__", &(shiftToString<Scalar>))

        .def(
            "is_defined",
            &Scalar::isDefined,
            R"doc(
                Check if the scalar is defined.

                Returns:
                    bool: True if defined.
            )doc"
        )
        .def(
            "get_value",
            &Scalar::getValue,
            R"doc(
                Get value.

                Returns:
                    float: Value.
            )doc"
        )
        .def(
            "get_unit",
            &Scalar::getUnit,
            R"doc(
                Get unit.

                Returns:
                    Unit: Unit.
            )doc"
        )
        .def(
            "in_unit",
            &Scalar::inUnit,
            arg("unit"),
            R"doc(
                Convert to unit.

                Args:
                    unit (Unit): Unit.

                Returns:
                    Scalar: Scalar in the specified unit.
            )doc"
        )
        .def(
            "to_string",
            &Scalar::toString,
            arg_v("precision", Integer::Undefined(), "Integer.Undefined()"),
            R"doc(
                Convert to string.

                Args:
                    precision (int): Precision.

                Returns:
                    str: String representation.
            )doc"
        )

        .def_static(
            "undefined",
            &Scalar::Undefined,
            R"doc(
                Create an undefined scalar.

                Returns:
                    Scalar: Undefined scalar.
            )doc"
        )

        ;
}
