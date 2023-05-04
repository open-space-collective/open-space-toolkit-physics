////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           bindings/python/src/OpenSpaceToolkitPhysicsPy/Environment/Atmospheric/Earth.cpp
/// @author         Kyle Cochran <kyle.cochran@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitPhysicsPy_Environment_Atmospheric_Earth ( pybind11::module&         aModule                                     )
{

    using namespace pybind11 ;

    using ostk::core::fs::Directory ;

    using ostk::physics::environment::atmospheric::Earth ;

    {

        class_<Earth> earth_class(aModule, "Earth") ;

        earth_class

            .def
            (
                init<const Earth::Type&, const Directory&>(),
                arg("type"),
                arg("directory")
            )

            .def
            (
                init<const Earth::Type&>(),
                arg("type")
            )

            .def
            (
                "get_type",
                &Earth::getType
            )

            .def
            (
                "get_density_at",
                &Earth::getDensityAt,
                arg("position"),
                arg("instant")
            )

        ;

        enum_<Earth::Type>(earth_class, "Type")

            .value("Exponential", Earth::Type::Exponential)
        ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
