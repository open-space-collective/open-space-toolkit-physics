////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Coordinate/Frame/Providers/CIRF.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Coordinate/Frame/Providers/CIRF.hpp>
#include <Library/Physics/Time/DateTime.hpp>
#include <Library/Physics/Time/Scale.hpp>
#include <Library/Physics/Units/Derived/Angle.hpp>

#include <Library/Mathematics/Geometry/3D/Transformations/Rotations/RotationMatrix.hpp>

#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

#include <sofa/sofa.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DAS2R (4.848136811095359935899141e-6)
#define DMAS2R (DAS2R / 1e3)

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

    using library::math::geom::d3::trf::rot::RotationMatrix ;

    using library::physics::time::Scale ;
    using library::physics::time::DateTime ;

    if (!anInstant.isDefined())
    {
        throw library::core::error::runtime::Undefined("Instant") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("CIRF") ;
    }

    // http://www.iausofa.org/2018_0130_C/sofa/sofa_pn_c.pdf

    // Time (TT)

    static const double djmjd0 = 2400000.5 ;
    const double tt = anInstant.getDateTime(Scale::TT).getModifiedJulianDate() ;

    // CIP and CIO, IAU 2006/2000A

    double x ;
    double y ;
    double s ;

    iauXys06a(djmjd0, tt, &x, &y, &s) ;

    // CIP offsets wrt IAU 2006/2000A (mas->radians)
    
    static const double dx06 = +0.1750 * DMAS2R ;
    static const double dy06 = -0.2259 * DMAS2R ;

    // Add CIP corrections

    x += dx06 ;
    y += dy06 ;

    // GCRS to CIRS matrix

    double rc2i[3][3] ; // dcm_CIRS_GCRS

    iauC2ixys(x, y, s, rc2i) ;

    const Vector3d GCRF_x_CIRF = Vector3d(rc2i[0][0], rc2i[1][0], rc2i[2][0]).normalized() ;
    const Vector3d GCRF_y_CIRF = Vector3d(rc2i[0][1], rc2i[1][1], rc2i[2][1]).normalized() ;
    const Vector3d GCRF_z_CIRF = Vector3d(rc2i[0][2], rc2i[1][2], rc2i[2][2]).normalized() ;

    const RotationMatrix dcm_CIRF_GCRF = RotationMatrix::Columns(GCRF_x_CIRF, GCRF_y_CIRF, GCRF_z_CIRF) ;
    
    // Output

    const Vector3d x_CIRF_GCRF = { 0.0, 0.0, 0.0 } ;
    const Vector3d v_CIRF_GCRF = { 0.0, 0.0, 0.0 } ;

    const Quaternion q_CIRF_GCRF = Quaternion::RotationMatrix(dcm_CIRF_GCRF).rectify() ;
    const Vector3d w_CIRF_GCRF_in_CIRF = { 0.0, 0.0, 0.0 } ;
    
    return Transform::Passive(anInstant, x_CIRF_GCRF, v_CIRF_GCRF, q_CIRF_GCRF, w_CIRF_GCRF_in_CIRF) ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////