////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Environment/Objects/CelestialBodies/Moon.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Physics_Environment_Objects_CelestialBodies_Moon__
#define __Library_Physics_Environment_Objects_CelestialBodies_Moon__

#include <Library/Physics/Environment/Objects/Celestial.hpp>
#include <Library/Physics/Environment/Object.hpp>
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
using library::physics::env::Object ;
using library::physics::env::obj::Celestial ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Moon : public Celestial
{

    public:

        static Derived          GravitationalConstant ;
        static Length           EquatorialRadius ;
        static Real             Flattening ;

                                Moon                                        (   const   Shared<Ephemeris>&          anEphemerisSPtr,
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