////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           OpenSpaceToolkit/Physics/Environment/Objects/CelestialBodies/Moon.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OpenSpaceToolkit_Physics_Environment_Objects_CelestialBodies_Moon__
#define __OpenSpaceToolkit_Physics_Environment_Objects_CelestialBodies_Moon__

#include <OpenSpaceToolkit/Physics/Environment/Objects/Celestial.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Object.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Ephemeris.hpp>
#include <OpenSpaceToolkit/Physics/Units/Derived.hpp>
#include <OpenSpaceToolkit/Physics/Units/Length.hpp>

#include <Library/Mathematics/Geometry/3D/Objects/Ellipsoid.hpp>

#include <Library/Core/Types/Real.hpp>
#include <Library/Core/Types/Shared.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ostk
{
namespace physics
{
namespace env
{
namespace obj
{
namespace celest
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using ostk::core::types::Shared ;
using ostk::core::types::Real ;

using ostk::math::geom::d3::objects::Ellipsoid ;

using ostk::physics::units::Length ;
using ostk::physics::units::Derived ;
using ostk::physics::env::Ephemeris ;
using ostk::physics::env::Object ;
using ostk::physics::env::obj::Celestial ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Moon : public Celestial
{

    public:

        static Derived          GravitationalParameter ;
        static Length           EquatorialRadius ;
        static Real             Flattening ;

                                Moon                                        (   const   Shared<Ephemeris>&          anEphemeris,
                                                                                const   Instant&                    anInstant                                   ) ;

        virtual                 ~Moon                                       ( ) override ;

        virtual Moon*           clone                                       ( ) const override ;

        static Moon             Default                                     ( ) ;

    private:

        static Object::Geometry Geometry                                    (   const   Shared<const Frame>&        aFrameSPtr                                  ) ;

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
