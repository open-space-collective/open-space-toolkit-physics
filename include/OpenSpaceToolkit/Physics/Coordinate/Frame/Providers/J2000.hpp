/// Apache License 2.0 

#ifndef __OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_J2000__
#define __OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_J2000__

#include <OpenSpaceToolkit/Physics/Coordinate/Transform.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/IAU/Theory.hpp>
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

namespace iau = ostk::physics::coord::frame::providers::iau ;

using ostk::physics::time::Instant ;
using ostk::physics::coord::frame::Provider ;
using ostk::physics::coord::Transform ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      J2000 frame provider.
///
///                             Defined with the Earth's Mean Equator and Mean Equinox (MEME) at 12:00 Terrestrial Time on 1 January 2000.
///                             Also known as EME2000.
///
/// @ref                        https://en.wikipedia.org/wiki/Earth-centered_inertial

class J2000 : public Provider
{

    public:

                                J2000                                       (   const   iau::Theory&                aTheory                                     ) ;

        virtual                 ~J2000                                      ( ) override ;

        virtual J2000*           clone                                      ( ) const override ;

        virtual bool            isDefined                                   ( ) const override ;

        iau::Theory             getTheory                                   ( ) const ;

        Instant                 getEpoch                                    ( ) const ;

        virtual Transform       getTransformAt                              (   const   Instant&                    anInstant                                   ) const override ;

    private:

        iau::Theory             theory_ ;

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
