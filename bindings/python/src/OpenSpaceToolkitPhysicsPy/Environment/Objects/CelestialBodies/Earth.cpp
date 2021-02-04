////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           bindings/python/src/OpenSpaceToolkitPhysicsPy/Environment/Objects/CelestialBodies/Earth.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Physics/Environment/Objects/CelestialBodies/Earth.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitPhysicsPy_Environment_Objects_CelestialBodies_Earth (        pybind11::module& aModule                          )
{

    using namespace pybind11 ;

    using ostk::core::types::Real ;
    using ostk::core::types::Shared ;

    using ostk::physics::units::Length ;
    using ostk::physics::units::Derived ;
    using ostk::physics::time::Instant ;
    using ostk::physics::env::Ephemeris ;
    using ostk::physics::env::obj::Celestial ;
    using ostk::physics::env::obj::celest::Earth ;
    using EarthGravitationalModel = ostk::physics::environment::gravitational::Earth ;
    using EarthMagneticModel = ostk::physics::environment::magnetic::Earth ;

    {

        class_<Earth, Celestial>(aModule, "Earth")

            .def(init<const Derived&, const Length&, const Real&, const Real&, const Shared<Ephemeris>&, const EarthGravitationalModel::Type&, const EarthMagneticModel::Type&, const Instant&>())

            .def_readonly_static("gravitational_parameter", &Earth::GravitationalParameter)
            .def_readonly_static("equatorial_radius", &Earth::EquatorialRadius)
            .def_readonly_static("flattening", &Earth::Flattening)
            .def_readonly_static("C20", &Earth::C20)
            .def_readonly_static("J2", &Earth::J2)

            .def("__str__", &(shiftToString<Earth>))
            .def("__repr__", &(shiftToString<Earth>))

            .def_static("default", &Earth::Default)
            .def_static("EGM2008", &Earth::EGM2008)
            .def_static("WGS84_EGM96", &Earth::WGS84_EGM96)
            .def_static("EGM96", &Earth::EGM96)
            .def_static("WGS84", &Earth::WGS84)

        ;

    }

    {

        // Create "earth" python submodule
        auto earth = aModule.def_submodule("earth") ;

        // Add __path__ attribute for "earth" submodule
        earth.attr("__path__") = "ostk.physics.environment.objects.celestial_bodies.earth" ;

    }

    {

        // Create "models" python submodule
        auto models = aModule.def_submodule("models") ;

        // Add __path__ attribute for "models" submodule
        models.attr("__path__") = "ostk.physics.environment.objects.celestial_bodies.earth.models" ;

        class_<Earth::Models::EGM2008>(models, "EGM2008")

            .def_readonly_static("gravitational_parameter", &Earth::Models::EGM2008::GravitationalParameter)
            .def_readonly_static("equatorial_radius", &Earth::Models::EGM2008::EquatorialRadius)
            .def_readonly_static("flattening", &Earth::Models::EGM2008::Flattening)
            .def_readonly_static("C20", &Earth::Models::EGM2008::C20)
            .def_readonly_static("J2", &Earth::Models::EGM2008::J2)

        ;

        class_<Earth::Models::WGS84_EGM96>(models, "WGS84_EGM96")

            .def_readonly_static("gravitational_parameter", &Earth::Models::WGS84_EGM96::GravitationalParameter)
            .def_readonly_static("equatorial_radius", &Earth::Models::WGS84_EGM96::EquatorialRadius)
            .def_readonly_static("flattening", &Earth::Models::WGS84_EGM96::Flattening)
            .def_readonly_static("C20", &Earth::Models::WGS84_EGM96::C20)
            .def_readonly_static("J2", &Earth::Models::WGS84_EGM96::J2)

        ;

        class_<Earth::Models::EGM96>(models, "EGM96")

            .def_readonly_static("gravitational_parameter", &Earth::Models::EGM96::GravitationalParameter)
            .def_readonly_static("equatorial_radius", &Earth::Models::EGM96::EquatorialRadius)
            .def_readonly_static("flattening", &Earth::Models::EGM96::Flattening)
            .def_readonly_static("C20", &Earth::Models::EGM96::C20)
            .def_readonly_static("J2", &Earth::Models::EGM96::J2)

        ;

        class_<Earth::Models::WGS84>(models, "WGS84")

            .def_readonly_static("gravitational_parameter", &Earth::Models::WGS84::GravitationalParameter)
            .def_readonly_static("equatorial_radius", &Earth::Models::WGS84::EquatorialRadius)
            .def_readonly_static("flattening", &Earth::Models::WGS84::Flattening)
            .def_readonly_static("C20", &Earth::Models::WGS84::C20)
            .def_readonly_static("J2", &Earth::Models::WGS84::J2)

        ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
