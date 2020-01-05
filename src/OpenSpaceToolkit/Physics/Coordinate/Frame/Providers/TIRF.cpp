////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/TIRF.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/IERS/Manager.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/TIRF.hpp>
#include <OpenSpaceToolkit/Physics/Time/DateTime.hpp>
#include <OpenSpaceToolkit/Physics/Time/Scale.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/RotationMatrix.hpp>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

#include <sofa/sofa.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DAYSEC (86400.0)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using IersManager = ostk::physics::coord::frame::provider::iers::Manager ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ostk
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

    using ostk::math::geom::d3::trf::rot::RotationMatrix ;

    using ostk::physics::time::Scale ;
    using ostk::physics::time::DateTime ;

    if (!anInstant.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant") ;
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("TIRF") ;
    }

    // http://www.iausofa.org/2018_0130_C/sofa/sofa_pn_c.pdf

    // Time (UTC)

    static const Real djmjd0 = 2400000.5 ;
    const Real utc = anInstant.getDateTime(Scale::UTC).getModifiedJulianDate() ;

    const Real date = std::floor(utc) ;
    const Real time = utc - date ;

    // UT1 - UTC (s)

    const Real dut1 = IersManager::Get().getUt1MinusUtcAt(anInstant) ; // [s]

    const Real tut = time + dut1 / DAYSEC ;

    // Earth rotation angle, IAU 2000 [rad]

    const Real era = iauEra00(djmjd0 + date, tut) ;

    // CIRS to TIRF matrix

    const Real cosEra = std::cos(era) ;
    const Real sinEra = std::sin(era) ;

    const RotationMatrix dcm_TIRF_CIRF = RotationMatrix::Rows(  { +cosEra, +sinEra, 0.0 },
                                                                { -sinEra, +cosEra, 0.0 },
                                                                { 0.0,     0.0,     1.0 }) ;

    // Angular velocity

    Real lod_ms = IersManager::Get().getLodAt(anInstant) ; // [ms]

    if (!lod_ms.isDefined())
    {
        // throw ostk::core::error::runtime::Undefined("LOD") ; // [TBI] Fail in strict mode
        lod_ms = 0.0 ;
    }

    const Real w_TIRF_CIRF = (72921151.467064 - 0.843994809 * lod_ms) * 1e-12 ; // [rad/s] https://www.iers.org/IERS/EN/Science/EarthRotation/UT1LOD.html

    // Output

    const Vector3d x_TIRF_CIRF = { 0.0, 0.0, 0.0 } ;
    const Vector3d v_TIRF_CIRF = { 0.0, 0.0, 0.0 } ;

    const Quaternion q_TIRF_CIRF = Quaternion::RotationMatrix(dcm_TIRF_CIRF).rectify() ;
    const Vector3d w_TIRF_CIRF_in_TIRF = Vector3d::Z() * w_TIRF_CIRF ;

    return Transform::Passive(anInstant, x_TIRF_CIRF, v_TIRF_CIRF, q_TIRF_CIRF, w_TIRF_CIRF_in_TIRF) ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
