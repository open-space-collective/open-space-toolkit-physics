/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Environment/Object/Celestial.hpp>

#include <OpenSpaceToolkitPhysicsPy/Environment/Object/Celestial/Earth.cpp>
#include <OpenSpaceToolkitPhysicsPy/Environment/Object/Celestial/Moon.cpp>
#include <OpenSpaceToolkitPhysicsPy/Environment/Object/Celestial/Sun.cpp>

inline void OpenSpaceToolkitPhysicsPy_Environment_Object_Celestial(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Shared;
    using ostk::core::type::Real;
    using ostk::core::type::String;

    using ostk::physics::time::Instant;
    using ostk::physics::unit::Length;
    using ostk::physics::unit::Derived;
    using ostk::physics::environment::Ephemeris;
    using ostk::physics::environment::Object;
    using ostk::physics::environment::object::Celestial;
    using GravitationalModel = ostk::physics::environment::gravitational::Model;
    using MagneticModel = ostk::physics::environment::magnetic::Model;
    using AtmosphericModel = ostk::physics::environment::atmospheric::Model;

    class_<Celestial, Shared<Celestial>, Object> celestial_class(aModule, "Celestial");

    celestial_class
        .def(
            init<
                const String&,
                const Celestial::Type&,
                const Derived&,
                const Length&,
                const Real&,
                const Real&,
                const Real&,
                const Shared<Ephemeris>&,
                const Shared<GravitationalModel>&,
                const Shared<MagneticModel>&,
                const Shared<AtmosphericModel>&>(),
            arg("name"),
            arg("type"),
            arg("gravitational_parameter"),
            arg("equatorial_radius"),
            arg("flattening"),
            arg("J2_parameter_value"),
            arg("J4_parameter_value"),
            arg("ephemeris"),
            arg("gravitational_model"),
            arg("magnetic_model"),
            arg("atmospheric_model")
        )

        .def(
            init<
                const String&,
                const Celestial::Type&,
                const Derived&,
                const Length&,
                const Real&,
                const Real&,
                const Real&,
                const Shared<Ephemeris>&,
                const Shared<GravitationalModel>&,
                const Shared<MagneticModel>&,
                const Shared<AtmosphericModel>&,
                const Object::Geometry&>(),
            arg("name"),
            arg("type"),
            arg("gravitational_parameter"),
            arg("equatorial_radius"),
            arg("flattening"),
            arg("J2_parameter_value"),
            arg("J4_parameter_value"),
            arg("ephemeris"),
            arg("gravitational_model"),
            arg("magnetic_model"),
            arg("atmospheric_model"),
            arg("geometry")
        )

        // Need to create corresponding operators in C++ source code for proper use of binding code below
        // .def(self == self)
        // .def(self != self)
        // .def("__eq__", [](const Celestial &self, const Celestial &other){ return self == other; })
        // .def("__ne__", [](const Celestial &self, const Celestial &other){ return self != other; })

        .def("__str__", &(shiftToString<Celestial>))
        .def("__repr__", &(shiftToString<Celestial>))

        .def("is_defined", &Celestial::isDefined)

        .def("access_ephemeris", &Celestial::accessEphemeris)
        .def("access_gravitational_model", &Celestial::accessGravitationalModel)
        .def("access_magnetic_model", &Celestial::accessMagneticModel)
        .def("access_atmospheric_model", &Celestial::accessAtmosphericModel)

        .def("get_type", &Celestial::getType)
        .def("get_gravitational_parameter", &Celestial::getGravitationalParameter)
        .def("get_equatorial_radius", &Celestial::getEquatorialRadius)
        .def("get_flattening", &Celestial::getFlattening)
        .def("get_j2", &Celestial::getJ2)
        .def("get_j4", &Celestial::getJ4)
        // .def("access_frame", &Celestial::accessFrame)
        .def("get_position_in", &Celestial::getPositionIn, arg("frame"), arg("instant"))
        .def("get_transform_to", &Celestial::getTransformTo, arg("frame"), arg("instant"))
        .def("get_axes_in", &Celestial::getAxesIn, arg("frame"), arg("instant"))
        .def("get_gravitational_field_at", &Celestial::getGravitationalFieldAt, arg("position"), arg("instant"))
        .def("get_magnetic_field_at", &Celestial::getMagneticFieldAt, arg("position"), arg("instant"))
        .def("get_atmospheric_density_at", &Celestial::getAtmosphericDensityAt, arg("position"), arg("instant"))
        .def("gravitational_model_is_defined", &Celestial::gravitationalModelIsDefined)
        .def("magnetic_model_is_defined", &Celestial::magneticModelIsDefined)
        .def("atmospheric_model_is_defined", &Celestial::atmosphericModelIsDefined)
        .def("get_frame_at", &Celestial::getFrameAt, arg("lla"), arg("frame_type"))

        .def_static("undefined", &Celestial::Undefined)

        .def_static("string_from_frame_type", &Celestial::StringFromFrameType, arg("frame_type"))

        ;

    enum_<Celestial::Type>(celestial_class, "CelestialType")

        .value("Undefined", Celestial::Type::Undefined)
        .value("Sun", Celestial::Type::Sun)
        .value("Mercury", Celestial::Type::Mercury)
        .value("Venus", Celestial::Type::Venus)
        .value("Earth", Celestial::Type::Earth)
        .value("Moon", Celestial::Type::Moon)
        .value("Mars", Celestial::Type::Mars)

        ;

    enum_<Celestial::FrameType>(celestial_class, "FrameType")

        .value("Undefined", Celestial::FrameType::Undefined)
        .value("NED", Celestial::FrameType::NED)

        ;

    // register_ptr_to_python<Shared<const Celestial>>() ;

    // implicitly_convertible<Shared<Celestial>, Shared<const Celestial>>() ;

    // Create "celestial" python submodule
    auto celestial = aModule.def_submodule("celestial");


    // Add objects to python "celestial" submodules
    OpenSpaceToolkitPhysicsPy_Environment_Object_Celestial_Earth(celestial);
    OpenSpaceToolkitPhysicsPy_Environment_Object_Celestial_Moon(celestial);
    OpenSpaceToolkitPhysicsPy_Environment_Object_Celestial_Sun(celestial);
}
