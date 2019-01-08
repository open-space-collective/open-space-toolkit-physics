////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Environment/Objects/CelestialBodies/Earth.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Physics_Environment_Objects_CelestialBodies_Earth__
#define __Library_Physics_Environment_Objects_CelestialBodies_Earth__

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

class Earth : public Celestial
{

    public:

        struct Models
        {

            struct EGM2008
            {

                static const Derived GravitationalParameter ;
                static const Length EquatorialRadius ;
                static const Real Flattening ;
                static const Real C20 ;
                static const Real J2 ;

            } ;

            struct WGS84_EGM96
            {

                static const Derived GravitationalParameter ;
                static const Length EquatorialRadius ;
                static const Real Flattening ;
                static const Real C20 ;
                static const Real J2 ;

            } ;

            struct EGM96
            {

                static const Derived GravitationalParameter ;
                static const Length EquatorialRadius ;
                static const Real Flattening ;
                static const Real C20 ;
                static const Real J2 ;

            } ;

            struct WGS84
            {

                static const Derived GravitationalParameter ;
                static const Length EquatorialRadius ;
                static const Real Flattening ;
                static const Real C20 ;
                static const Real J2 ;

            } ;
            
        } ;

        static const Derived    GravitationalParameter ; // [TBR]
        static const Length     EquatorialRadius ; // [TBR]
        static const Real       Flattening ; // [TBR]
        static const Real       C20 ; // [TBR]
        static const Real       J2 ; // [TBR]

                                Earth                                       (   const   Derived&                    aGravitationalParameter,
                                                                                const   Length&                     anEquatorialRadius,
                                                                                const   Real&                       aFlattening,
                                                                                const   Real&                       aJ2,
                                                                                const   Shared<Ephemeris>&          anEphemerisSPtr,
                                                                                const   Instant&                    anInstant                                   ) ;

        virtual                 ~Earth                                      ( ) override ;

        virtual Earth*          clone                                       ( ) const override ;

        /// @brief              Default Earth model (EGM2008)
        ///
        /// @return             Earth

        static Earth            Default                                     ( ) ;

        /// @brief              Earth Gravity Model 2008 model (EGM2008)
        ///
        /// @return             Earth

        static Earth            EGM2008                                     ( ) ;

        /// @brief              World Geodetic System 1984 (WGS84) + Earth Gravity Model 1996 (EGM96)
        ///
        ///                     EGM96 coefficients and WGS84 shape.
        ///                     Gravitational parameter: 398600441800000 [m^3/s^2].
        ///                     Equatorial radius: 6378137.0 [m].
        ///
        /// @ref                NIMA TR8350.2, Third Edition, 4 July 1997.
        ///
        /// @return             Earth

        static Earth            WGS84_EGM96                                 ( ) ;

        /// @brief              Earth Gravity Model 1996 (EGM96)
        ///
        /// @return             Earth
        
        static Earth            EGM96                                       ( ) ;

        /// @brief              World Geodetic System 1984 (WGS84)
        ///
        /// @return             Earth

        static Earth            WGS84                                       ( ) ;

    private:

        static Object::Geometry Geometry                                    (   const   Length&                     anEquatorialRadius,
                                                                                const   Real&                       aFlattening,
                                                                                const   Shared<const Frame>&        aFrameSPtr                                  ) ;

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