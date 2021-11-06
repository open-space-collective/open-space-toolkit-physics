////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           OpenSpaceToolkit/Physics/Coordinate/Frame.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OpenSpaceToolkit_Physics_Coordinate_Frame__
#define __OpenSpaceToolkit_Physics_Coordinate_Frame__

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Transform.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Axes.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Velocity.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Position.hpp>

#include <OpenSpaceToolkit/Mathematics/Objects/Vector.hpp>

#include <OpenSpaceToolkit/Core/Types/String.hpp>
#include <OpenSpaceToolkit/Core/Types/Real.hpp>
#include <OpenSpaceToolkit/Core/Types/Integer.hpp>
#include <OpenSpaceToolkit/Core/Types/Shared.hpp>

#include <memory>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ostk
{
namespace physics
{
namespace coord
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using ostk::core::types::Uint8 ;
using ostk::core::types::Shared ;
using ostk::core::types::Real ;
using ostk::core::types::String ;

using ostk::math::obj::Vector3d ;

using ostk::physics::coord::Position ;
using ostk::physics::coord::Velocity ;
using ostk::physics::coord::Axes ;
using ostk::physics::coord::Transform ;
using ostk::physics::coord::frame::Provider ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Reference frame
///
/// @ref                        https://en.wikipedia.org/wiki/Frame_of_reference
/// @note                       Implementation heavily inspired by (the great!) https://www.orekit.org/static/architecture/frames.html

class Frame : public std::enable_shared_from_this<Frame>
{

    public:

        /// @brief              Destructor

                                ~Frame                                      ( ) ;

        bool                    operator ==                                 (   const   Frame&                      aFrame                                      ) const ;

        bool                    operator !=                                 (   const   Frame&                      aFrame                                      ) const ;

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Frame&                      aFrame                                      ) ;

        bool                    isDefined                                   ( ) const ;

        bool                    isQuasiInertial                             ( ) const ;

        bool                    hasParent                                   ( ) const ;

        Shared<const Frame>     accessParent                                ( ) const ;

        Shared<const Frame>     accessAncestor                              (   const   Uint8                       anAncestorDegree                            ) const ;

        Shared<const Provider>  accessProvider                              ( ) const ;

        String                  getName                                     ( ) const ;

        Position                getOriginIn                                 (   const   Shared<const Frame>&        aFrame,
                                                                                const   Instant&                    anInstant                                   ) const ;

        Velocity                getVelocityIn                               (   const   Shared<const Frame>&        aFrame,
                                                                                const   Instant&                    anInstant                                   ) const ;

        Axes                    getAxesIn                                   (   const   Shared<const Frame>&        aFrame,
                                                                                const   Instant&                    anInstant                                   ) const ;

        Transform               getTransformTo                              (   const   Shared<const Frame>&        aFrame,
                                                                                const   Instant&                    anInstant                                   ) const ;

        static Shared<const Frame> Undefined                                ( ) ;

        static Shared<const Frame> ICRF                                     ( ) ;

        static Shared<const Frame> GCRF                                     ( ) ;

        static Shared<const Frame> MOD                                      ( ) ;

        static Shared<const Frame> EME2000                                  ( ) ;

        static Shared<const Frame> TEME                                     ( ) ;

        static Shared<const Frame> TEMEOfEpoch                              (   const   Instant&                    anEpoch                                     ) ;

        static Shared<const Frame> CIRF                                     ( ) ;

        static Shared<const Frame> TIRF                                     ( ) ;

        static Shared<const Frame> ITRF                                     ( ) ;

        static Shared<const Frame> WithName                                 (   const   String&                     aName                                       ) ;

        static bool             Exists                                      (   const   String&                     aName                                       ) ;

        /// @brief              Constructor
        ///
        /// @param              [in] aName A frame name
        /// @param              [in] isQuasiInertialT True is frame is quasi-inertial
        /// @param              [in] aParentFrame A shared pointer to the parent frame
        /// @param              [in] aProvider A shared pointer to the transform provider

        static Shared<const Frame> Construct                                (   const   String&                     aName,
                                                                                        bool                        isQuasiInertial,
                                                                                const   Shared<const Frame>&        aParentFrame,
                                                                                const   Shared<const Provider>&     aProvider                                   ) ;

        static void             Destruct                                    (   const   String&                     aName                                       ) ;

    protected:

                                Frame                                       (   const   String&                     aName,
                                                                                        bool                        isQuasiInertial,
                                                                                const   Shared<const Frame>&        aParentFrame,
                                                                                const   Shared<const Provider>&     aProvider                                   ) ;

                                Frame                                       (   const   Frame&                      aFrame                                      ) = default ;

        Frame&                  operator =                                  (   const   Frame&                      aFrame                                      ) = default ;

    private:

        String                  name_ ;
        bool                    quasiInertial_ ;
        Shared<const Frame>     parentFrameSPtr_ ;
        Shared<const Provider>  providerSPtr_ ; // Provides transform from parent to instance -> Unique<> instead?

        Uint8                   getDepth                                    ( ) const ;

        static Shared<const Frame> Emplace                                  (   const   String&                     aName,
                                                                                        bool                        isQuasiInertial,
                                                                                const   Shared<const Frame>&        aParentFrame,
                                                                                const   Shared<const Provider>&     aProvider                                   ) ;

        static Shared<const Frame> FindCommonAncestor                       (   const   Shared<const Frame>&        aFirstFrameSPtr,
                                                                                const   Shared<const Frame>&        aSecondFrameSPtr                            ) ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
