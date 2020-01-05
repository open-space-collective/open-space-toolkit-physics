////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           OpenSpaceToolkit/Physics/Environment/Ephemerides/SPICE.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OpenSpaceToolkit_Physics_Environment_Ephemerides_SPICE__
#define __OpenSpaceToolkit_Physics_Environment_Ephemerides_SPICE__

#include <OpenSpaceToolkit/Physics/Environment/Ephemeris.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

#include <OpenSpaceToolkit/Core/Types/String.hpp>
#include <OpenSpaceToolkit/Core/Types/Shared.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ostk
{
namespace physics
{
namespace env
{
namespace ephem
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using ostk::core::types::Shared ;
using ostk::core::types::String ;

using ostk::physics::time::Instant ;
using ostk::physics::coord::Frame ;
using ostk::physics::env::Ephemeris ;

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
