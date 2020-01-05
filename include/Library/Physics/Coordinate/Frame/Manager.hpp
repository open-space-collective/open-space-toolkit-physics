////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           Library/Physics/Coordinate/Frame/Manager.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OpenSpaceToolkit_Physics_Coordinate_Frame_Manager__
#define __OpenSpaceToolkit_Physics_Coordinate_Frame_Manager__

#include <Library/Physics/Coordinate/Transform.hpp>
#include <Library/Physics/Coordinate/Frame.hpp>
#include <Library/Physics/Time/Instant.hpp>

#include <Library/Core/Containers/Map.hpp>
#include <Library/Core/Types/String.hpp>
#include <Library/Core/Types/Shared.hpp>

#include <mutex>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ostk
{
namespace physics
{
namespace coord
{
namespace frame
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using ostk::core::types::Shared ;
using ostk::core::types::String ;
using ostk::core::ctnr::Map ;

using ostk::physics::time::Instant ;
using ostk::physics::coord::Frame ;
using ostk::physics::coord::Transform ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Reference frame manager (thread-safe)

class Manager
{

    public:

                                Manager                                     (   const   Manager&                    aManager                                    ) = delete ;

        Manager&                operator =                                  (   const   Manager&                    aManager                                    ) = delete ;

        bool                    hasFrameWithName                            (   const   String&                     aFrameName                                  ) const ;

        Shared<const Frame>     accessFrameWithName                         (   const   String&                     aFrameName                                  ) const ;

        const Transform*        accessCachedTransform                       (   const   Shared<const Frame>&        aFromFrameSPtr,
                                                                                const   Shared<const Frame>&        aToFrameSPtr,
                                                                                const   Instant&                    anInstant                                   ) const ;

        void                    addFrame                                    (   const   Shared<const Frame>&        aFrameSPtr                                  ) ;

        void                    removeFrameWithName                         (   const   String&                     aFrameName                                  ) ;

        void                    addCachedTransform                          (   const   Shared<const Frame>&        aFromFrameSPtr,
                                                                                const   Shared<const Frame>&        aToFrameSPtr,
                                                                                const   Instant&                    anInstant,
                                                                                const   Transform&                  aTransform                                  ) ;

        static Manager&         Get                                         ( ) ;

    private:

        Map<String, Shared<const Frame>> frameMap_ ;

        Map<const Frame*, Map<const Frame*, Map<Instant, Transform>>> transformCache_ ;

        mutable std::mutex      mutex_ ;

                                Manager                                     ( ) = default ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
