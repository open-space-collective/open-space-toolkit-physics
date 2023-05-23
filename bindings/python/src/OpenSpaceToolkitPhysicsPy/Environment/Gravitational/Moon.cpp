/// Apache License 2.0 

#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Moon.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitPhysicsPy_Environment_Gravitational_Moon (        pybind11::module& aModule                                     )
{

    using namespace pybind11 ;

    using ostk::core::fs::Directory ;

    using ostk::physics::environment::gravitational::Moon ;

    {

        class_<Moon> moon_class(aModule, "Moon") ;

        moon_class

            .def
            (
                init<const Moon::Type&, const Directory&>(),
                arg("type"),
                arg("directory")
            )

            .def
            (
                init<const Moon::Type&>(),
                arg("type")
            )

            .def
            (
                "get_type",
                &Moon::getType
            )

            .def
            (
                "get_field_value_at",
                &Moon::getFieldValueAt,
                arg("position"),
                arg("instant")
            )

        ;

        enum_<Moon::Type>(moon_class, "MoonType")

            .value("Spherical", Moon::Type::Spherical)

        ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
