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

    class_<Celestial, Shared<Celestial>, Object> celestial_class(aModule, "Celestial",
        R"doc(
            Celestial class
        )doc"
    );

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
            arg("atmospheric_model"),
            R"doc(
                Constructor

                Args:
                    name (str): Name
                    type (CelestialType): Type
                    gravitational_parameter (Derived): Gravitational parameter [m³/s²]
                    equatorial_radius (Length): Equatorial radius [m]
                    flattening (Real): Flattening
                    J2_parameter_value (Real): J2 parameter value
                    J4_parameter_value (Real): J4 parameter value
                    ephemeris (Ephemeris): Ephemeris
                    gravitational_model (GravitationalModel): Gravitational model
                    magnetic_model (MagneticModel): Magnetic model
                    atmospheric_model (AtmosphericModel): Atmospheric model
            )doc"
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
            arg("geometry"),
            R"doc(
                Constructor

                Args:
                    name (str): Name
                    type (CelestialType): Type
                    gravitational_parameter (Derived): Gravitational parameter [m³/s²]
                    equatorial_radius (Length): Equatorial radius [m]
                    flattening (Real): Flattening
                    J2_parameter_value (Real): J2 parameter value
                    J4_parameter_value (Real): J4 parameter value
                    ephemeris (Ephemeris): Ephemeris
                    gravitational_model (GravitationalModel): Gravitational model
                    magnetic_model (MagneticModel): Magnetic model
                    atmospheric_model (AtmosphericModel): Atmospheric model
                    geometry (Object.Geometry): Geometry
            )doc"
        )

        // Need to create corresponding operators in C++ source code for proper use of binding code below
        // .def(self == self)
        // .def(self != self)
        // .def("__eq__", [](const Celestial &self, const Celestial &other){ return self == other; })
        // .def("__ne__", [](const Celestial &self, const Celestial &other){ return self != other; })

        .def("__str__", &(shiftToString<Celestial>))
        .def("__repr__", &(shiftToString<Celestial>))

        .def("is_defined", &Celestial::isDefined,
            R"doc(
                Check if the celestial object is defined.

                Returns:
                    bool: True if the celestial object is defined, false otherwise
            )doc"
        )

        .def("access_ephemeris", &Celestial::accessEphemeris,
            R"doc(
                Access the ephemeris.

                Returns:
                    Ephemeris: Ephemeris
            )doc"
        )
        .def("access_gravitational_model", &Celestial::accessGravitationalModel,
            R"doc(
                Access the gravitational model.

                Returns:
                    GravitationalModel: Gravitational model
            )doc"
        )
        .def("access_magnetic_model", &Celestial::accessMagneticModel,
            R"doc(
                Access the magnetic model.

                Returns:
                    MagneticModel: Magnetic model
            )doc"
        )
        .def("access_atmospheric_model", &Celestial::accessAtmosphericModel,
            R"doc(
                Access the atmospheric model.

                Returns:
                    AtmosphericModel: Atmospheric model
            )doc"
        )

        .def("get_type", &Celestial::getType,
            R"doc(
                Get the type of the celestial object.

                Returns:
                    CelestialType: Type
            )doc"
        )
        .def("get_gravitational_parameter", &Celestial::getGravitationalParameter,
            R"doc(
                Get the gravitational parameter of the celestial object.

                Returns:
                    Derived: Gravitational parameter [m³/s²]
            )doc"
        )
        .def("get_equatorial_radius", &Celestial::getEquatorialRadius,
            R"doc(
                Get the equatorial radius of the celestial object.

                Returns:
                    Length: Equatorial radius [m]
            )doc"
        )
        .def("get_flattening", &Celestial::getFlattening,
            R"doc(
                Get the flattening of the celestial object.

                Returns:
                    Real: Flattening
            )doc"
        )
        .def("get_j2", &Celestial::getJ2,
            R"doc(
                Get the J2 parameter value of the celestial object.

                Returns:
                    Real: J2 parameter value
            )doc"
        )
        .def("get_j4", &Celestial::getJ4,
            R"doc(
                Get the J4 parameter value of the celestial object.

                Returns:
                    Real: J4 parameter value
            )doc"
        )
        // .def("access_frame", &Celestial::accessFrame)
        .def("get_position_in", &Celestial::getPositionIn, arg("frame"), arg("instant"),
            R"doc(
                Get the position of the celestial object in a given frame at a given instant.

                Args:
                    frame (Frame): Frame
                    instant (Instant): Instant

                Returns:
                    Position: Position
            )doc"
        )
        .def("get_transform_to", &Celestial::getTransformTo, arg("frame"), arg("instant"),
            R"doc(
                Get the transform of the celestial object to a given frame at a given instant.

                Args:
                    frame (Frame): Frame
                    instant (Instant): Instant

                Returns:
                    Transform: Transform
            )doc"
        )
        .def("get_axes_in", &Celestial::getAxesIn, arg("frame"), arg("instant"),
            R"doc(
                Get the axes of the celestial object in a given frame at a given instant.

                Args:
                    frame (Frame): Frame
                    instant (Instant): Instant

                Returns:
                    Axes: Axes
            )doc"
        )

        // TBI: whenenver data::Vector and data::Scalar is supported in Python
        // .def("get_gravitational_field_at", &Celestial::getGravitationalFieldAt, arg("position"), arg("instant"))
        // .def("get_magnetic_field_at", &Celestial::getMagneticFieldAt, arg("position"), arg("instant"))
        // .def("get_atmospheric_density_at", &Celestial::getAtmosphericDensityAt, arg("position"), arg("instant"))

        .def("gravitational_model_is_defined", &Celestial::gravitationalModelIsDefined,
            R"doc(
                Check if the gravitational model is defined.

                Returns:
                    bool: True if the gravitational model is defined, false otherwise
            )doc"
        )
        .def("magnetic_model_is_defined", &Celestial::magneticModelIsDefined,
            R"doc(
                Check if the magnetic model is defined.

                Returns:
                    bool: True if the magnetic model is defined, false otherwise
            )doc"
        )
        .def("atmospheric_model_is_defined", &Celestial::atmosphericModelIsDefined,
            R"doc(
                Check if the atmospheric model is defined.

                Returns:
                    bool: True if the atmospheric model is defined, false otherwise
            )doc"
        )
        .def("get_frame_at", &Celestial::getFrameAt, arg("lla"), arg("frame_type"),
            R"doc(
                Get the frame at a given LLA and frame type.

                Args:
                    lla (LLA): LLA
                    frame_type (Celestial.FrameType): Frame type

                Returns:
                    Frame: Frame
            )doc"
        )

        .def_static("undefined", &Celestial::Undefined,
            R"doc(
                Create an undefined celestial object.

                Returns:
                    Celestial: Undefined celestial object
            )doc"
        )

        .def_static("string_from_frame_type", &Celestial::StringFromFrameType, arg("frame_type"),
            R"doc(
                Get the string representation of a frame type.

                Args:
                    frame_type (Celestial.FrameType): Frame type

                Returns:
                    str: String representation
            )doc"
        )

        ;

    enum_<Celestial::Type>(celestial_class, "CelestialType")

        .value("Undefined", Celestial::Type::Undefined,
            R"doc(
                Undefined celestial object.
            )doc"
        )
        .value("Sun", Celestial::Type::Sun,
            R"doc(
                Sun.
            )doc"
        )
        .value("Mercury", Celestial::Type::Mercury,
            R"doc(
                Mercury.
            )doc"
        )
        .value("Venus", Celestial::Type::Venus,
            R"doc(
                Venus.
            )doc"
        )
        .value("Earth", Celestial::Type::Earth,
            R"doc(
                Earth.
            )doc"
        )
        .value("Moon", Celestial::Type::Moon,
            R"doc(
                Moon.
            )doc"
        )
        .value("Mars", Celestial::Type::Mars,
            R"doc(
                Mars.
            )doc"
        )

        ;

    enum_<Celestial::FrameType>(celestial_class, "FrameType")

        .value("Undefined", Celestial::FrameType::Undefined,
            R"doc(
                Undefined frame.
            )doc"
        )
        .value("NED", Celestial::FrameType::NED,
            R"doc(
                North-East-Down (NED) frame.
            )doc"
        )

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
