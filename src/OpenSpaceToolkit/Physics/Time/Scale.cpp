////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           OpenSpaceToolkit/Physics/Time/Scale.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Physics/Time/Scale.hpp>

#include <OpenSpaceToolkit/Core/Error.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ostk
{
namespace physics
{
namespace time
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

String                          StringFromScale                             (   const   Scale&                      aScale                                      )
{

    switch (aScale)
    {

        case Scale::Undefined:
            return "Undefined" ;

        case Scale::UTC:
            return "UTC" ;

        case Scale::TT:
            return "TT" ;

        case Scale::TAI:
            return "TAI" ;

        case Scale::UT1:
            return "UT1" ;

        case Scale::TCG:
            return "TCG" ;

        case Scale::TCB:
            return "TCB" ;

        case Scale::TDB:
            return "TDB" ;

        case Scale::GMST:
            return "GMST" ;

        case Scale::GPST:
            return "GPST" ;

        case Scale::GST:
            return "GST" ;

        case Scale::GLST:
            return "GLST" ;

        case Scale::BDT:
            return "BDT" ;

        case Scale::QZSST:
            return "QZSST" ;

        case Scale::IRNSST:
            return "IRNSST" ;

        default:
            throw ostk::core::error::runtime::Wrong("Scale") ;
            break ;

    }

    return String::Empty() ;

}

Scale                           ScaleFromString                             (   const   String&                     aString                                     )
{

    if (aString == "Undefined")
    {
        return Scale::Undefined ;
    }

    if (aString == "UTC")
    {
        return Scale::UTC ;
    }

    if (aString == "TT")
    {
        return Scale::TT ;
    }

    if (aString == "TAI")
    {
        return Scale::TAI ;
    }

    if (aString == "UT1")
    {
        return Scale::UT1 ;
    }

    if (aString == "TCG")
    {
        return Scale::TCG ;
    }

    if (aString == "TCB")
    {
        return Scale::TCB ;
    }

    if (aString == "TDB")
    {
        return Scale::TDB ;
    }

    if (aString == "GMST")
    {
        return Scale::GMST ;
    }

    if (aString == "GPST")
    {
        return Scale::GPST ;
    }

    if (aString == "GST")
    {
        return Scale::GST ;
    }

    if (aString == "GLST")
    {
        return Scale::GLST ;
    }

    if (aString == "BDT")
    {
        return Scale::BDT ;
    }

    if (aString == "QZSST")
    {
        return Scale::QZSST ;
    }

    if (aString == "IRNSST")
    {
        return Scale::IRNSST ;
    }

    throw ostk::core::error::runtime::Wrong("Scale", aString) ;

    return Scale::Undefined ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
