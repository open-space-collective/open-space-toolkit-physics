/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/IAU/Theory.hpp>

inline void OpenSpaceToolkitPhysicsPy_Coordinate_Frame_Provider_IAU_Theory(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::physics::coordinate::frame::provider::iau::Theory;

    enum_<Theory>(aModule, "Theory")

        .value("IAU_2000A", Theory::IAU_2000A)
        .value("IAU_2000B", Theory::IAU_2000B)
        .value("IAU_2006", Theory::IAU_2006)

        ;
}
