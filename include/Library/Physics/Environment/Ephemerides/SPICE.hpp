////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Environment/Ephemerides/SPICE.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Physics_Environment_Ephemerides_SPICE__
#define __Library_Physics_Environment_Ephemerides_SPICE__

#include <Library/Physics/Environment/Ephemeris.hpp>
#include <Library/Physics/Coordinate/Frame.hpp>
#include <Library/Physics/Time/Instant.hpp>

#include <Library/Core/Types/String.hpp>
#include <Library/Core/Types/Shared.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{
namespace env
{
namespace ephem
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using library::core::types::Shared ;
using library::core::types::String ;

using library::physics::time::Instant ;
using library::physics::coord::Frame ;
using library::physics::env::Ephemeris ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      SPICE Toolkit ephemeris
///
/// @ref                        https://en.wikipedia.org/wiki/Jet_Propulsion_Laboratory_Development_Ephemeris

class SPICE : public Ephemeris
{

    public:

        enum class Object
        {

            Sun,
            Mercury,
            Venus,
            Earth,
            Moon,
            Mars,
            Jupiter,
            Saturn,
            Uranus,
            Neptune

        } ;

                                SPICE                                       (   const   SPICE::Object&              anObject                                    ) ;

        virtual                 ~SPICE                                      ( ) override ;

        virtual SPICE*          clone                                       ( ) const override ;

        virtual bool            isDefined                                   ( ) const override ;

        virtual Shared<const Frame> accessFrame                             ( ) const override ;

        static String           StringFromObject                            (   const   SPICE::Object&              anObject                                    ) ;

    private:

        SPICE::Object           object_ ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////