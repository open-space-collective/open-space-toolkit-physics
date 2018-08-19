////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Environment/Objects/CelestialBodies/Earth.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Physics_Environment_Objects_CelestialBodies_Earth__
#define __Library_Physics_Environment_Objects_CelestialBodies_Earth__

#include <Library/Physics/Environment/Objects/Celestial.hpp>
#include <Library/Physics/Environment/Ephemeris.hpp>
#include <Library/Physics/Units/Derived.hpp>
#include <Library/Physics/Units/Length.hpp>

#include <Library/Mathematics/Geometry/3D/Objects/Ellipsoid.hpp>

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

using library::math::geom::d3::objects::Ellipsoid ;

using library::physics::units::Length ;
using library::physics::units::Derived ;
using library::physics::env::Ephemeris ;
using library::physics::env::obj::Celestial ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Earth : public Celestial
{

    public:

        static Derived          GravitationalConstant ;
        static Length           EquatorialRadius ;
        static Real             Flattening ;
        static Real             C20 ;
        static Real             J2 ;

                                Earth                                       (   const   Shared<Ephemeris>&          anEphemeris,
                                                                                const   Instant&                    anInstant                                   ) ;

        virtual                 ~Earth                                      ( ) override ;

        virtual Earth*          clone                                       ( ) const override ;

        virtual const Ellipsoid& accessGeometry                             ( ) const override ;

        static Earth            Analytical                                  (   const   Instant&                    anInstant                                   ) ; // [TBI] Analytical options

    private:

        static Ellipsoid        Geometry                                   ( ) ;

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