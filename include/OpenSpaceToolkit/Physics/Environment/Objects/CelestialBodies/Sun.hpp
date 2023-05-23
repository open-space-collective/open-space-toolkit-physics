/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Environment_Objects_CelestialBodies_Sun__
#define __OpenSpaceToolkit_Physics_Environment_Objects_CelestialBodies_Sun__

#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Sun.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Objects/Celestial.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Object.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Ephemeris.hpp>
#include <OpenSpaceToolkit/Physics/Units/Derived.hpp>
#include <OpenSpaceToolkit/Physics/Units/Length.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Sphere.hpp>

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

using ostk::math::geom::d3::objects::Sphere ;

using ostk::physics::units::Length ;
using ostk::physics::units::Derived ;
using ostk::physics::env::Ephemeris ;
using ostk::physics::env::Object ;
using ostk::physics::env::obj::Celestial ;
using SunGravitationalModel = ostk::physics::environment::gravitational::Sun ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Sun : public Celestial
{

    public:

        static Derived          GravitationalParameter ;
        static Length           EquatorialRadius ;
        static Real             Flattening ;

        /// @brief              Constructor
        ///
        /// @param              [in] anEphemeris An ephemeris for the Sun celestial object
        /// @param              [in] aGravitationalModelType A gravitational model type for the Sun celestial object (Spherical model only)
        /// @param              [in] anInstant An instant 

                                Sun                                         (   const   Shared<Ephemeris>&          anEphemeris,
                                                                                const   SunGravitationalModel::Type& aGravitationalModelType,
                                                                                const   Instant&                    anInstant                                   ) ;

        /// @brief              Destructor

        virtual                 ~Sun                                        ( ) override ;

        /// @brief              Clone the Sun celestial object
        ///
        /// @return             Pointer to Sun celestial object

        virtual Sun*            clone                                       ( ) const override ;

        /// @brief              Default Sun model (Spherical)
        ///
        /// @return             Sun

        static Sun              Default                                     ( ) ;

        /// @brief              Spherical model
        ///
        /// @return             Sun

        static Sun              Spherical                                   ( ) ;

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
