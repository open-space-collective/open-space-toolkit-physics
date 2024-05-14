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

    class_<Direction, Vector>(
        aModule,
        "Direction",
        R"doc(
            Direction.

            A unit vector, expressed in a given frame. 

        )doc"
    )

        .def(
            init<const Vector3d&, const Shared<const Frame>&>(),
            arg("value"),
            arg("frame"),
            R"doc(
                Construct a Direction.

                Args:
                    np.ndarray: Value
                    Frame: Frame
            )doc"
        )

        .def(
            self == self,
            R"doc(
                Equality operator.

                Args:
                    other (Direction): Other direction.

                Returns:
                    bool: True if equal.
            )doc"
        )
        .def(
            self != self,
            R"doc(
                Inequality operator.

                Args:
                    other (Direction): Other direction.

                Returns:
                    bool: True if not equal.
            )doc"
        )

        .def("__str__", &(shiftToString<Direction>))
        .def("__repr__", &(shiftToString<Direction>))

        .def_static(
            "undefined",
            &Direction::Undefined,
            R"doc(
                Create an undefined direction.

                Returns:
                    Direction: Undefined direction.
            )doc"
        )

        ;
}
