////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Coordinate/Frame/Providers/ITRF.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Coordinate/Frame/Providers/ITRF.hpp>
#include <Library/Physics/Time/Duration.hpp>
#include <Library/Physics/Units/Derived/Angle.hpp>

#include <Library/Mathematics/Geometry/Transformations/Rotations/RotationVector.hpp>

#include <Library/Core/Types/Real.hpp>
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

    using library::core::types::Real ;
    using library::physics::units::Angle ;
    using library::physics::time::Scale ;
    using library::physics::time::Time ;
    using library::math::geom::trf::rot::RotationVector ;
    
    if (!anInstant.isDefined())
    {
        throw library::core::error::runtime::Undefined("Instant") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("ITRF") ;
    }

    const Time& time = anInstant.getDateTime(Scale::TT).accessTime() ;

    const Real dayRatio = ((time.getHour() / 1.0) + (time.getMinute() / 60.0) + (time.getSecond() / 3600.0)) / 24.0 ; // [TBR]
    const Angle rotationAngle = Angle::Degrees(dayRatio * 360.0) ; // [TBR]

    const Vector3d x_ITRF_TIRF = { 0.0, 0.0, 0.0 } ;
    const Vector3d v_ITRF_TIRF = { 0.0, 0.0, 0.0 } ;

    const Quaternion q_ITRF_TIRF = Quaternion::RotationVector(RotationVector({ 0.0, 0.0, 1.0 }, rotationAngle)) ; // [TBI]
    const Vector3d w_ITRF_TIRF_in_ITRF = { 0.0, 0.0, 1e-5 } ; // [TBI]
    
    return Transform::Passive(anInstant, x_ITRF_TIRF, v_ITRF_TIRF, q_ITRF_TIRF, w_ITRF_TIRF_in_ITRF) ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////