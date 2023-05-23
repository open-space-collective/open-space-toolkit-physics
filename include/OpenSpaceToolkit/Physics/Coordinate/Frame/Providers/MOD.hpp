/// Apache License 2.0 

#ifndef __OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_MOD__
#define __OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_MOD__

#include <OpenSpaceToolkit/Physics/Coordinate/Transform.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

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

using ostk::physics::time::Instant ;
using ostk::physics::coord::frame::Provider ;
using ostk::physics::coord::Transform ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Mean of Date (MOD) frame provider.
///
///                             Transformation from the Geocentric Celestial Reference Frame (GCRF) frame to the Mean of Date (MOD) frame.
///                             This algorithm uses the IAU-76/FK5 theory.
///
///                             The Mean of Date (MOD) frame is rotated into the Geocentric Celestial Reference Frame (GCRF)
///                             considering the IAU 1976 Precession model.
///                             Notice that if the conversion `TOD => MOD` is performed **without** considering
///                             the EOP corrections, then the GCRF obtained by this rotation is what is usually
///                             called the J2000 reference frame.
///
/// @ref                        https://en.wikipedia.org/wiki/Earth-centered_inertial
/// @ref                        https://github.com/JuliaSpace/SatelliteToolbox.jl/blob/master/src/transformations/fk5/fk5.jl#L396

class MOD : public Provider
{

    public:

                                MOD                                         (   const   Instant&                    anEpoch                                     ) ;

        virtual                 ~MOD                                        ( ) override ;

        virtual MOD*            clone                                       ( ) const override ;

        virtual bool            isDefined                                   ( ) const override ;

        Instant                 getEpoch                                    ( ) const ;

        virtual Transform       getTransformAt                              (   const   Instant&                    anInstant                                   ) const override ;

    private:

        Instant                 epoch_ ;

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
