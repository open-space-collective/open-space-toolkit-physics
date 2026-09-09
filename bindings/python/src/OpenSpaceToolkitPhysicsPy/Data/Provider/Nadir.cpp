/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Data/Provider/Nadir.hpp>

inline void OpenSpaceToolkitPhysicsPy_Data_Provider_Nadir(nanobind::module_& aModule)
{
    using namespace nanobind;

    using ostk::physics::coordinate::Frame;
    using ostk::physics::data::provider::Nadir;

    aModule.def(
        "nadir",
        &Nadir,
        R"doc(
            Nadir.

            Compute the nadir direction from a given position.
            The instant of the position is inferred from the environment.

            Args:
                position (Position): Position.
                celestial (Celestial): Celestial object.
                environment (Environment): Environment.

            Returns:
                Direction: Nadir direction.
        )doc",
        arg("position"),
        arg("celestial"),
        arg("environment")
    );
}
