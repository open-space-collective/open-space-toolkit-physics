////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Coordinate/Frame/Providers/TIRF.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Coordinate/Frame/Providers/TIRF.hpp>
#include <Library/Physics/Time/DateTime.hpp>
#include <Library/Physics/Time/Scale.hpp>

#include <Library/Mathematics/Geometry/Transformations/Rotations/RotationMatrix.hpp>

#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

#include <sofa/sofa.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DAYSEC (86400.0)

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

    // UT1 - UTC (s) [TBI] Load data from Bulletin A
    
    // const double dut1 = -0.072073685 ; // 2007-04-05 12:00:00

    // 18 6 8 58277.00 I  0.123539 0.000027  0.447183 0.000011  I 0.0737816 0.0000097  0.7420 0.0067  I    -0.131    0.137    -0.119    0.132

    const double dut1 = +0.0737816 ; // 2018-06-08 00:00:00

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
    const Vector3d w_TIRF_CIRF_in_TIRF = { 0.0, 0.0, 0.0 } ; // [TBI]
    
    return Transform::Passive(anInstant, x_TIRF_CIRF, v_TIRF_CIRF, q_TIRF_CIRF, w_TIRF_CIRF_in_TIRF) ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////