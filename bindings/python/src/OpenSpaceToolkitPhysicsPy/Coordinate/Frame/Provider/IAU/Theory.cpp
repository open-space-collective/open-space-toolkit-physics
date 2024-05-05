/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/IAU/Theory.hpp>

inline void OpenSpaceToolkitPhysicsPy_Coordinate_Frame_Provider_IAU_Theory(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::physics::coordinate::frame::provider::iau::Theory;

    enum_<Theory>(aModule, "Theory",
        R"doc(
            The IAU 2000A precession-nutation theory relates the International Celestial Reference Frame to the International Terrestrial Reference Frame and has been effective since January 2003. In 2006, the IAU moved to adopt a more dynamically consistent precession model to complement the IAU 2000A nutation theory.

        )doc"
    )

        .value("IAU_2000A", Theory::IAU_2000A,
            R"doc(
                The IAU 2000A theory.

            )doc"
        )
        .value("IAU_2000B", Theory::IAU_2000B,
            R"doc(
                The IAU 2000B theory.
                
            )doc"
        )
        .value("IAU_2006", Theory::IAU_2006,
            R"doc(
                The IAU 2006 theory.
                
            )doc"
        )

        ;
}
