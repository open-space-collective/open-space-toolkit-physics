/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Environment/Magnetic/Dipole.hpp>

inline void OpenSpaceToolkitPhysicsPy_Environment_Magnetic_Dipole(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::mathematics::object::Vector3d;

    using ostk::physics::environment::magnetic::Dipole;

    class_<Dipole>(aModule, "Dipole",
        R"doc(
            Magnetic dipole model.

            .. seealso:: https://en.wikipedia.org/wiki/Magnetic_dipole
            .. seealso:: https://en.wikipedia.org/wiki/Magnetic_moment
            .. seealso:: https://en.wikipedia.org/wiki/Vacuum_permeability
            .. seealso:: https://en.wikipedia.org/wiki/Dipole_model_of_the_Earth%27s_magnetic_field
        )doc"
    )

        .def(init<const Vector3d&>(),
            R"doc(
                Construct a dipole magnetic model.

                Args:
                    magnetic_moment (Vector3d): Magnetic moment [A⋅m2]
            )doc"
        )

        .def("get_field_value_at", &Dipole::getFieldValueAt,
            R"doc(
                Get the magnetic field value at a given position and instant.

                Args:
                    position (Vector3d): Position, expressed in the magnetic object frame [m]
                    instant (Instant): Instant

                Returns:
                    Vector3d: Magnetic field value, expressed in the magnetic object frame [T]
            )doc"
        );

        ;
}
