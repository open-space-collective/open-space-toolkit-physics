////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Coordinate/Frame/Providers/ITRF.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Coordinate/Frame/Providers/IERS/BulletinA.hpp>
#include <Library/Physics/Coordinate/Frame/Providers/IERS/Manager.hpp>
#include <Library/Physics/Coordinate/Frame/Providers/ITRF.hpp>
#include <Library/Physics/Time/DateTime.hpp>
#include <Library/Physics/Time/Scale.hpp>

#include <Library/Mathematics/Geometry/Transformations/Rotations/RotationMatrix.hpp>

#include <Library/Core/Types/Real.hpp>
#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

#include <sofa/sofa.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DAS2R (4.848136811095359935899141e-6)

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

                                ITRF::ITRF                                  ( )
{

}

                                ITRF::~ITRF                                 ( )
{

}

ITRF*                           ITRF::clone                                 ( ) const
{
    return new ITRF(*this) ;
}

bool                            ITRF::isDefined                             ( ) const
{
    return true ;
}

Transform                       ITRF::getTransformAt                        (   const   Instant&                    anInstant                                   ) const
{

    using library::math::obj::Vector2d ;
    using library::math::geom::trf::rot::RotationMatrix ;

    using library::physics::time::Scale ;
    using library::physics::time::DateTime ;
    
    if (!anInstant.isDefined())
    {
        throw library::core::error::runtime::Undefined("Instant") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("ITRF") ;
    }

    // Time (TT)

    static const double djmjd0 = 2400000.5 ;
    const double tt = anInstant.getDateTime(Scale::TT).getModifiedJulianDate() ;

    // The polar motion xp,yp can be obtained from IERS bulletins.  The
    // values are the coordinates (in radians) of the Celestial
    // Intermediate Pole with respect to the International Terrestrial
    // Reference System (see IERS Conventions 2003), measured along the
    // meridians 0 and 90 deg west respectively.  For many applications,
    // xp and yp can be set to zero.

    // IERS Bulletin A
    
    // Bulletin A: http://maia.usno.navy.mil/ser7/ser7.dat
    // Data: http://maia.usno.navy.mil/ser7/finals2000A.data
    // Format: http://maia.usno.navy.mil/ser7/readme.finals2000A

    // Polar motion

    const Vector2d polarMotion = IersManager.getPolarMotionAt(anInstant) ; // [asec]

    const double xp = polarMotion.x() * DAS2R ; // [rad]
    const double yp = polarMotion.y() * DAS2R ; // [rad]

    // TIO locator s', in radians, which positions the Terrestrial Intermediate Origin on the equator. 
    // It is obtained from polar motion observations by numerical integration, and so is in essence unpredictable.
    // However, it is dominated by a secular drift of about 47 microarcseconds per century, and so can be taken into account by using s' = -47*t,
    // where t is centuries since J2000.0.

    const double sp = iauSp00(djmjd0, tt) ;

    // Polar motion matrix (TIRS -> ITRS, IERS 2003)
    // The matrix operates in the sense V(TRS) = rpom * V(CIP), meaning
    // that it is the final rotation when computing the pointing direction to a celestial source.
	
	double rpom[3][3] ;
	
    iauPom00(xp, yp, sp, rpom) ;

    const Vector3d TIRF_x_ITRF = Vector3d(rpom[0][0], rpom[1][0], rpom[2][0]).normalized() ;
    const Vector3d TIRF_y_ITRF = Vector3d(rpom[0][1], rpom[1][1], rpom[2][1]).normalized() ;
    const Vector3d TIRF_z_ITRF = Vector3d(rpom[0][2], rpom[1][2], rpom[2][2]).normalized() ;

    const RotationMatrix dcm_ITRF_TIRF = RotationMatrix::Columns(TIRF_x_ITRF, TIRF_y_ITRF, TIRF_z_ITRF) ;

    // Output

    const Vector3d x_ITRF_TIRF = { 0.0, 0.0, 0.0 } ;
    const Vector3d v_ITRF_TIRF = { 0.0, 0.0, 0.0 } ;

    const Quaternion q_ITRF_TIRF = Quaternion::RotationMatrix(dcm_ITRF_TIRF).rectify() ;
    // const Quaternion q_ITRF_TIRF = Quaternion::RotationMatrix(dcm_ITRF_TIRF).conjugate().rectify() ; // ANGULAR VELOCITY WORKS IF CONJUGATED
    const Vector3d w_ITRF_TIRF_in_ITRF = { 0.0, 0.0, 0.0 } ;
    
    return Transform::Passive(anInstant, x_ITRF_TIRF, v_ITRF_TIRF, q_ITRF_TIRF, w_ITRF_TIRF_in_ITRF) ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////