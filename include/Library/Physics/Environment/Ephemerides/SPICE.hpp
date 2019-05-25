////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library ▸ Physics
/// @file           Library/Physics/Environment/Ephemerides/SPICE.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

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

        /// @brief              SPICE object

        enum class Object
        {

            Undefined,
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

        /// @brief              Constructor
        ///
        /// @param              [in] anObject A SPICE object

                                SPICE                                       (   const   SPICE::Object&              anObject                                    ) ;

        /// @brief              Destructor

        virtual                 ~SPICE                                      ( ) override ;

        /// @brief              Clone
        ///
        /// @return             Pointer to SPICE

        virtual SPICE*          clone                                       ( ) const override ;

        /// @brief              Returns true if SPICE is defined
        ///
        /// @return             True if SPICE is defined

        virtual bool            isDefined                                   ( ) const override ;

        /// @brief              Access frame of SPICE object
        ///
        /// @return             Shared pointer to frame

        virtual Shared<const Frame> accessFrame                             ( ) const override ;

        /// @brief              Convert SPICE object to string
        ///
        /// @param              [in] anObject A SPICE object
        /// @return             String representation of SPICE object

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
