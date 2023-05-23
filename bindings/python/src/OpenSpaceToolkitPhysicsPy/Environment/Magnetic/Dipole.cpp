/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Environment/Magnetic/Dipole.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitPhysicsPy_Environment_Magnetic_Dipole (        pybind11::module&    aModule                                     )
{

    using namespace pybind11 ;

    using ostk::math::obj::Vector3d ;

    using ostk::physics::environment::magnetic::Dipole ;

    class_<Dipole>(aModule, "Dipole")

        .def(init<const Vector3d&>())

        .def("get_field_value_at", &Dipole::getFieldValueAt)

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
