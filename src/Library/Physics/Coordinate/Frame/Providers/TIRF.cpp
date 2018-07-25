////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Coordinate/Frame/Providers/TIRF.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Coordinate/Frame/Providers/IERS/BulletinA.hpp>
#include <Library/Physics/Coordinate/Frame/Providers/IERS/Manager.hpp>
#include <Library/Physics/Coordinate/Frame/Providers/TIRF.hpp>
#include <Library/Physics/Time/DateTime.hpp>
#include <Library/Physics/Time/Scale.hpp>

#include <Library/Mathematics/Geometry/Transformations/Rotations/RotationMatrix.hpp>

#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

#include <sofa/sofa.h>

#include <iostream>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DAYSEC (86400.0)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using library::physics::coord::frame::provider::iers::Manager ;
using library::physics::coord::frame::provider::iers::BulletinA ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static const Manager IersManager ;

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

                                TIRF::TIRF                                  ( )
{

}

                                TIRF::~TIRF                                 ( )
{

}

TIRF*                           TIRF::clone                                 ( ) const
{
    return new TIRF(*this) ;
}

bool                            TIRF::isDefined                             ( ) const
{
    return true ;
}

Transform                       TIRF::getTransformAt                        (   const   Instant&                    anInstant                                   ) const
{

    using library::math::geom::trf::rot::RotationMatrix ;

    using library::physics::time::Scale ;
    using library::physics::time::DateTime ;
    
    if (!anInstant.isDefined())
    {
        throw library::core::error::runtime::Undefined("Instant") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("TIRF") ;
    }

    // http://www.iausofa.org/2018_0130_C/sofa/sofa_pn_c.pdf

    // Time (UTC)

    static const double djmjd0 = 2400000.5 ;
    const double utc = anInstant.getDateTime(Scale::UTC).getModifiedJulianDate() ;

    const double date = std::floor(utc) ;
    const double time = utc - date ;

    // UT1 - UTC (s)
    
    // const double dut1 = -0.072073685 ; // 2007-04-05 12:00:00
    // const double dut1 = +0.0737816 ; // 2018-06-08 00:00:00

    double dut1 = IersManager.getUt1MinusUtc(anInstant) ; // [s]

    const double tut = time + dut1 / DAYSEC ;

    // Earth rotation angle [rad]

    const double era = iauEra00(djmjd0 + date, tut) ;

    // CIRS to TIRF matrix

    const double cosEra = std::cos(era) ;
    const double sinEra = std::sin(era) ;

    const RotationMatrix dcm_TIRF_CIRS = RotationMatrix::Rows(  { +cosEra, +sinEra, 0.0 },
                                                                { -sinEra, +cosEra, 0.0 },
                                                                { 0.0,     0.0,     1.0 }) ;

    // Output

    const Vector3d x_TIRF_CIRF = { 0.0, 0.0, 0.0 } ;
    const Vector3d v_TIRF_CIRF = { 0.0, 0.0, 0.0 } ;

    const Quaternion q_TIRF_CIRF = Quaternion::RotationMatrix(dcm_TIRF_CIRS) ;
    const Vector3d w_TIRF_CIRF_in_TIRF = { 0.00000000002094, -0.00000000008755, 0.00007292115077 } ; // [TBI]
    
    return Transform::Passive(anInstant, x_TIRF_CIRF, v_TIRF_CIRF, q_TIRF_CIRF, w_TIRF_CIRF_in_TIRF) ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////