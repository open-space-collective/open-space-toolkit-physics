////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           Library/Physics/Environment/Objects/CelestialBodies/Sun.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OpenSpaceToolkit_Physics_Environment_Objects_CelestialBodies_Sun__
#define __OpenSpaceToolkit_Physics_Environment_Objects_CelestialBodies_Sun__

#include <Library/Physics/Environment/Objects/Celestial.hpp>
#include <Library/Physics/Environment/Object.hpp>
#include <Library/Physics/Environment/Ephemeris.hpp>
#include <Library/Physics/Units/Derived.hpp>
#include <Library/Physics/Units/Length.hpp>

#include <Library/Mathematics/Geometry/3D/Objects/Sphere.hpp>

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

using ostk::math::geom::d3::objects::Sphere ;

using ostk::physics::units::Length ;
using ostk::physics::units::Derived ;
using ostk::physics::env::Ephemeris ;
using ostk::physics::env::Object ;
using ostk::physics::env::obj::Celestial ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Sun : public Celestial
{

    public:

        static Derived          GravitationalParameter ;
        static Length           EquatorialRadius ;
        static Real             Flattening ;

                                Sun                                         (   const   Shared<Ephemeris>&          anEphemeris,
                                                                                const   Instant&                    anInstant                                   ) ;

        virtual                 ~Sun                                        ( ) override ;

        virtual Sun*            clone                                       ( ) const override ;

        static Sun              Default                                     ( ) ;

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
