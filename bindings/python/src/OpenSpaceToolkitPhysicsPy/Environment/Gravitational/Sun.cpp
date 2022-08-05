////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           bindings/python/src/OpenSpaceToolkitPhysicsPy/Environment/Gravitational/Sun.cpp
/// @author         Antoine Paletta <antoine.paletta@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Sun.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitPhysicsPy_Environment_Gravitational_Sun                         (   pybind11::module&aModule                    )
{

    using namespace pybind11 ;

    using ostk::core::types::Integer ;
    using ostk::core::fs::Directory ;

    using ostk::physics::units::Derived ;
    using ostk::physics::environment::gravitational::Sun ;

    {

        class_<Sun> sun_class(aModule, "Sun") ;

        sun_class.def(init<const Sun::Type&, const Directory&>())

            .def(init<const Sun::Type&>())

            .def("get_type", &Sun::getType)
            .def("get_field_value_at", &Sun::getFieldValueAt)

        ;

        enum_<Sun::Type>(sun_class, "SunType")

            .value("Spherical", Sun::Type::Spherical)

        ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
