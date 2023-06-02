/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Coordinate/Position.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Spherical/LLA.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

inline void OpenSpaceToolkitPhysicsPy_Environment_Atmospheric_Earth(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::fs::Directory;

    using ostk::physics::environment::atmospheric::Earth;
    using ostk::physics::time::Instant;
    using ostk::physics::coord::Position;
    using ostk::physics::coord::Position;
    using ostk::physics::coord::spherical::LLA;

    {
        class_<Earth> earth_class(aModule, "Earth");

        earth_class

            .def(init<const Earth::Type&, const Directory&>(), arg("type"), arg("directory"))

            .def(init<const Earth::Type&>(), arg("type"))

            .def("get_type", &Earth::getType)

            .def("is_defined", &Earth::isDefined)

            .def(
                "get_density_at",
                pybind11::overload_cast<const Position&, const Instant&>(&Earth::getDensityAt, pybind11::const_),
                arg("position"),
                arg("instant")
            )

            .def(
                "get_density_at",
                pybind11::overload_cast<const LLA&, const Instant&>(&Earth::getDensityAt, pybind11::const_),
                arg("lla"),
                arg("instant")
            )

            ;

        enum_<Earth::Type>(earth_class, "Type")

            .value("Exponential", Earth::Type::Exponential);
    }
}
