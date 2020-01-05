////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           Library/Physics/Coordinate/Frame/Providers/TEME.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Coordinate/Frame/Providers/IERS/Manager.hpp>
#include <Library/Physics/Coordinate/Frame/Providers/TEME.hpp>
#include <Library/Physics/Units/Derived/Angle.hpp>
#include <Library/Physics/Time/DateTime.hpp>
#include <Library/Physics/Time/Scale.hpp>

#include <Library/Mathematics/Geometry/3D/Transformations/Rotations/RotationMatrix.hpp>

#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

#include <sofa/sofa.h>

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

#define DAYSEC (86400.0)
#define DAS2R (4.848136811095359935899141e-6)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using IersManager = library::physics::coord::frame::provider::iers::Manager ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                TEME::TEME                                  ( )
{

}

                                TEME::~TEME                                 ( )
{

}

TEME*                           TEME::clone                                 ( ) const
{
    return new TEME(*this) ;
}

bool                            TEME::isDefined                             ( ) const
{
    return true ;
}

Transform                       TEME::getTransformAt                        (   const   Instant&                    anInstant                                   ) const
{

    // https://geodesy.geology.ohio-state.edu/course/refpapers/AIAA4025.pdf
    // https://celestrak.com/publications/AIAA/2006-6753/faq.php
    // http://www.dtic.mil/dtic/tr/fulltext/u2/a637370.pdf p.18

    using library::math::obj::Vector2d ;
    using library::math::geom::d3::trf::rot::RotationMatrix ;

    using library::physics::time::Scale ;
    using library::physics::time::DateTime ;
    using library::physics::units::Angle ;

    if (!anInstant.isDefined())
    {
        throw library::core::error::runtime::Undefined("Instant") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("TEME") ;
    }

    // Time (UTC)

    static const Real djmjd0 = 2400000.5 ;
    const Real utc = anInstant.getDateTime(Scale::UTC).getModifiedJulianDate() ;

    const Real date = std::floor(utc) ;
    const Real time = utc - date ;

    // UT1 - UTC (s)

    const Real dut1 = IersManager::Get().getUt1MinusUtcAt(anInstant) ; // [s]
    const Real tut = time + dut1 / DAYSEC ;

    // UT1 as a 2-part Julian Date

    const Real uta = djmjd0 + date ;
    const Real utb = tut ;

    // Greenwich apparent sidereal time (consistent with IAU 1982/94 resolutions)

    const Real gmst_1982 = iauGmst82(uta, utb) ;

    const RotationMatrix R_3 = RotationMatrix::RZ(Angle::Radians(gmst_1982)) ; // dcm_PEF_TEME

    // Polar motion matrix using the IAU 1980 model

    const Vector2d polarMotion = IersManager::Get().getPolarMotionAt(anInstant) ; // [asec]

    const Real xp = polarMotion.x() * DAS2R ; // [rad]
    const Real yp = polarMotion.y() * DAS2R ; // [rad]

    const Real cos_xp = std::cos(xp) ;
    const Real sin_xp = std::sin(xp) ;

    const Real cos_yp = std::cos(yp) ;
    const Real sin_yp = std::sin(yp) ;

    const RotationMatrix W_1980 = RotationMatrix::Rows( { +cos_xp, +sin_xp * sin_yp, +sin_xp * cos_yp },
                                                        { 0.0,     +cos_yp,          -sin_yp          },
                                                        { -sin_xp, +cos_xp * sin_yp, +cos_xp * cos_yp }) ; // dcm_ITRF_PEF

    const RotationMatrix dcm_ITRF_TEME = W_1980 * R_3 ;

    // Output

    const Vector3d x_TEME_ITRF = { 0.0, 0.0, 0.0 } ;
    const Vector3d v_TEME_ITRF = { 0.0, 0.0, 0.0 } ;

    const Quaternion q_TEME_ITRF = Quaternion::RotationMatrix(dcm_ITRF_TEME).conjugate().rectify() ;
    const Vector3d w_TEME_ITRF_in_TEME = { 0.0, 0.0, 0.0 } ; // [TBI]

    return Transform::Passive(anInstant, x_TEME_ITRF, v_TEME_ITRF, q_TEME_ITRF, w_TEME_ITRF_in_TEME) ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
