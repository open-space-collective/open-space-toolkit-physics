////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           OpenSpaceToolkit/Physics/Environment/Objects/CelestialBodies/Earth.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OpenSpaceToolkit_Physics_Environment_Objects_CelestialBodies_Earth__
#define __OpenSpaceToolkit_Physics_Environment_Objects_CelestialBodies_Earth__

#include <OpenSpaceToolkit/Physics/Environment/Magnetic/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Objects/Celestial.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Object.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Ephemeris.hpp>
#include <OpenSpaceToolkit/Physics/Units/Derived.hpp>
#include <OpenSpaceToolkit/Physics/Units/Length.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Ellipsoid.hpp>

#include <OpenSpaceToolkit/Core/Types/Real.hpp>
#include <OpenSpaceToolkit/Core/Types/Shared.hpp>

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
using EarthGravitationalModel = ostk::physics::environment::gravitational::Earth ;
using EarthMagneticModel = ostk::physics::environment::magnetic::Earth ;

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
                static const Real C40 ;
                static const Real J2 ;
                static const Real J4 ;

            } ;

            struct WGS84_EGM96
            {

                static const Derived GravitationalParameter ;
                static const Length EquatorialRadius ;
                static const Real Flattening ;
                static const Real C20 ;
                static const Real C40 ;
                static const Real J2 ;
                static const Real J4 ;

            } ;

            struct EGM96
            {

                static const Derived GravitationalParameter ;
                static const Length EquatorialRadius ;
                static const Real Flattening ;
                static const Real C20 ;
                static const Real C40 ;
                static const Real J2 ;
                static const Real J4 ;

            } ;

            struct WGS84
            {

                static const Derived GravitationalParameter ;
                static const Length EquatorialRadius ;
                static const Real Flattening ;
                static const Real C20 ;
                static const Real C40 ;
                static const Real J2 ;
                static const Real J4 ;

            } ;

        } ;

        static const Derived    GravitationalParameter ; // [TBR]
        static const Length     EquatorialRadius ; // [TBR]
        static const Real       Flattening ; // [TBR]
        static const Real       C20 ; // [TBR]
        static const Real       C40 ; // [TBR]
        static const Real       J2 ; // [TBR]
        static const Real       J4 ; // [TBR]

                                Earth                                       (   const   Derived&                    aGravitationalParameter,
                                                                                const   Length&                     anEquatorialRadius,
                                                                                const   Real&                       aFlattening,
                                                                                const   Real&                       aJ2,
                                                                                const   Real&                       aJ4,
                                                                                const   Shared<Ephemeris>&          anEphemeris,
                                                                                const   EarthGravitationalModel::Type& aGravitationalModelType,
                                                                                const   EarthMagneticModel::Type&   aMagneticModelType,
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
