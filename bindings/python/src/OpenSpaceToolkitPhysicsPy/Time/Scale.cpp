/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Time/Scale.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitPhysicsPy_Time_Scale        (            pybind11::module&          aModule                                     )
{

    using namespace pybind11 ;

    using ostk::physics::time::Scale ;

    enum_<Scale>(aModule, "Scale")

        .value("Undefined", Scale::Undefined)
        .value("UTC", Scale::UTC)
        .value("TT", Scale::TT)
        .value("TAI", Scale::TAI)
        .value("UT1", Scale::UT1)
        .value("TCG", Scale::TCG)
        .value("TCB", Scale::TCB)
        .value("TDB", Scale::TDB)
        .value("GMST", Scale::GMST)
        .value("GPST", Scale::GPST)
        .value("GST", Scale::GST)
        .value("GLST", Scale::GLST)
        .value("BDT", Scale::BDT)
        .value("QZSST", Scale::QZSST)
        .value("IRNSST", Scale::IRNSST)

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
