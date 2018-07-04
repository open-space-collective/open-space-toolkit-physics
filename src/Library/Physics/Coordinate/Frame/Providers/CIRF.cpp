////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Coordinate/Frame/Providers/CIRF.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Coordinate/Frame/Providers/CIRF.hpp>

#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{
namespace coord
{
namespace frame
{
namespace provider
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                CIRF::CIRF                                  ( )
{

}

                                CIRF::~CIRF                                 ( )
{

}

CIRF*                           CIRF::clone                                 ( ) const
{
    return new CIRF(*this) ;
}

bool                            CIRF::isDefined                             ( ) const
{
    return true ;
}

Transform                       CIRF::getTransformAt                        (   const   Instant&                    anInstant                                   ) const
{

    if (!anInstant.isDefined())
    {
        throw library::core::error::runtime::Undefined("Instant") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("CIRF") ;
    }

    const Vector3d x_CIRF_GCRF = { 0.0, 0.0, 0.0 } ;
    const Vector3d v_CIRF_GCRF = { 0.0, 0.0, 0.0 } ;

    const Quaternion q_CIRF_GCRF = Quaternion::XYZS(0.0, 0.0, 0.0, 1.0) ; // [TBI]
    const Vector3d w_CIRF_GCRF_in_CIRF = { 0.0, 0.0, 0.0 } ; // [TBI]
    
    return Transform::Passive(anInstant, x_CIRF_GCRF, v_CIRF_GCRF, q_CIRF_GCRF, w_CIRF_GCRF_in_CIRF) ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////