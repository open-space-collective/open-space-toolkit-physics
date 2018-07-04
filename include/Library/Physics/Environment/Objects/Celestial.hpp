////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Environment/Objects/Celestial.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Physics_Environment_Objects_Celestial__
#define __Library_Physics_Environment_Objects_Celestial__

#include <Library/Physics/Environment/Ephemeris.hpp>
#include <Library/Physics/Environment/Object.hpp>
#include <Library/Physics/Coordinate/Frame.hpp>
#include <Library/Physics/Coordinate/Axes.hpp>
#include <Library/Physics/Coordinate/Position.hpp>
#include <Library/Physics/Time/Instant.hpp>

#include <Library/Mathematics/Objects/Vector.hpp>

#include <Library/Core/Types/Weak.hpp>
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using library::core::types::Shared ;
using library::core::types::Weak ;

using library::math::obj::Vector3d ;

using library::physics::time::Instant ;
using library::physics::coord::Position ;
using library::physics::coord::Axes ;
using library::physics::coord::Frame ;
using library::physics::env::Object ;
using library::physics::env::Ephemeris ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Celestial : public Object
{

    public:

        enum class Type
        {

            Undefined,
            Sun,
            Mercury,
            Venus,
            Earth,
            Moon,
            Mars

        } ;

                                Celestial                                   (   const   String&                     aName,
                                                                                const   Celestial::Type&            aType,
                                                                                const   Shared<Ephemeris>&          anEphemeris,
                                                                                const   Instant&                    anInstant                                   ) ;

        virtual                 ~Celestial                                  ( ) override ;

        virtual Celestial*      clone                                       ( ) const override ;

        virtual bool            isDefined                                   ( ) const override ;

        Shared<const Ephemeris> accessEphemeris                             ( ) const ;

        Celestial::Type         getType                                     ( ) const ;

        virtual Weak<const Frame> accessFrame                               ( ) const override ;

        virtual Position        getPositionIn                               (   const   Frame&                      aFrame                                      ) const override ;

        virtual Axes            getAxesIn                                   (   const   Frame&                      aFrame                                      ) const override ;

        Vector3d                getGravitationalFieldAt                     (   const   Position&                   aPosition                                   ) const ;

        static Celestial        Undefined                                   ( ) ;

    private:

        Celestial::Type         type_ ;
        Shared<Ephemeris>       ephemeris_ ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////