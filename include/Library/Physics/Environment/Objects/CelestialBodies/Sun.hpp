////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library ▸ Physics
/// @file           Library/Physics/Environment/Objects/CelestialBodies/Sun.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Physics_Environment_Objects_CelestialBodies_Sun__
#define __Library_Physics_Environment_Objects_CelestialBodies_Sun__

#include <Library/Physics/Environment/Objects/Celestial.hpp>
#include <Library/Physics/Environment/Object.hpp>
#include <Library/Physics/Environment/Ephemeris.hpp>
#include <Library/Physics/Units/Derived.hpp>
#include <Library/Physics/Units/Length.hpp>

#include <Library/Mathematics/Geometry/3D/Objects/Sphere.hpp>

#include <Library/Core/Types/Real.hpp>
#include <Library/Core/Types/Shared.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
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

using library::core::types::Shared ;
using library::core::types::Real ;

using library::math::geom::d3::objects::Sphere ;

using library::physics::units::Length ;
using library::physics::units::Derived ;
using library::physics::env::Ephemeris ;
using library::physics::env::Object ;
using library::physics::env::obj::Celestial ;

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
