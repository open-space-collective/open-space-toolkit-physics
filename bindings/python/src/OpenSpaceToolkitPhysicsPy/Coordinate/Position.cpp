/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Coordinate/Position.hpp>

inline void OpenSpaceToolkitPhysicsPy_Coordinate_Position(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Integer;
    using ostk::core::type::Shared;

    using ostk::mathematics::object::Vector3d;

    using ostk::physics::coordinate::Position;
    using ostk::physics::coordinate::Frame;

    class_<Position>(aModule, "Position")

        .def(init<Vector3d, Position::Unit, Shared<const Frame>&>(), arg("coordinates"), arg("unit"), arg("frame"))

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Position>))
        .def("__repr__", &(shiftToString<Position>))

        .def("is_defined", &Position::isDefined)
        .def("is_near", &Position::isNear, arg("position"), arg("tolerance"))

        .def("access_frame", &Position::accessFrame)
        .def("get_coordinates", &Position::getCoordinates)
        .def("get_unit", &Position::getUnit)
        .def("in_unit", &Position::inUnit)
        .def("in_meters", &Position::inMeters)
        .def("in_frame", &Position::inFrame, arg("frame"), arg("instant"))
        .def("to_string", &Position::toString, arg("precision") = DEFAULT_PRECISION)

        .def_static("undefined", &Position::Undefined)
        .def_static("meters", &Position::Meters, arg("coordinates"), arg("frame"))

        ;
}
