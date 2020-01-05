////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           LibraryPhysicsPy/Time/Scale.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Time/Scale.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryPhysicsPy_Time_Scale                 ( )
{

    using namespace boost::python ;

    using library::physics::time::Scale ;

    enum_<Scale>("Scale")

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
