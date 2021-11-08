////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/TOD.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_TOD__
#define __OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_TOD__

#include <OpenSpaceToolkit/Physics/Coordinate/Transform.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Units/Derived/Angle.hpp>

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

using ostk::physics::units::Angle ;
using ostk::physics::time::Instant ;
using ostk::physics::coord::frame::Provider ;
using ostk::physics::coord::Transform ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      True of Date (TOD) frame provider.
///
///                             Transformation from the Mean of Date (MOD) frame to the True of Date (TOD) frame.
///                             This algorithm uses the IAU-76/FK5 theory.
///                             Notice that one can provide corrections for the nutation in obliquity and in longitude
///                             that are usually obtained from IERS EOP Data.
///
/// @ref                        https://en.wikipedia.org/wiki/Earth-centered_inertial
/// @ref                        https://github.com/JuliaSpace/SatelliteToolbox.jl/blob/master/src/transformations/fk5/fk5.jl#L296

class TOD : public Provider
{

    public:

                                TOD                                         (   const   Instant&                    anEpoch,
                                                                                const   Angle&                      anObliquityCorrection                       =   Angle::Zero(),
                                                                                const   Angle&                      aLongitudeCorrection                        =   Angle::Zero()) ;

        virtual                 ~TOD                                        ( ) override ;

        virtual TOD*            clone                                       ( ) const override ;

        virtual bool            isDefined                                   ( ) const override ;

        Instant                 getEpoch                                    ( ) const ;

        virtual Transform       getTransformAt                              (   const   Instant&                    anInstant                                   ) const override ;

    private:

        Instant                 epoch_ ;
        Angle                   obliquityCorrection_ ;
        Angle                   longitudeCorrection_ ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
