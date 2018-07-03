////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Coordinate/Frame.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Physics_Coordinate_Frame__
#define __Library_Physics_Coordinate_Frame__

#include <Library/Physics/Coordinate/Frame/Provider.hpp>
#include <Library/Physics/Coordinate/Transform.hpp>
#include <Library/Physics/Coordinate/Axes.hpp>
#include <Library/Mathematics/Objects/Vector.hpp>
#include <Library/Core/Types/String.hpp>
#include <Library/Core/Types/Real.hpp>
#include <Library/Core/Types/Integer.hpp>
#include <Library/Core/Types/Shared.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{
namespace coord
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using library::core::types::Uint8 ;
using library::core::types::Shared ;
using library::core::types::Real ;
using library::core::types::String ;
using library::math::obj::Vector3d ;
using library::physics::coord::Axes ;
using library::physics::coord::Transform ;
using library::physics::coord::frame::Provider ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Reference frame
///
/// @ref                        https://en.wikipedia.org/wiki/Frame_of_reference
/// @note                       Implementation heavily inspired by (the great!) https://www.orekit.org/static/architecture/frames.html

class Frame
{

    public:

                                Frame                                       (   const   String&                     aName,
                                                                                        bool                        isQuasiInertial,
                                                                                const   Shared<const Frame>&        aParentFrame,
                                                                                const   Shared<Provider>&           aProvider                                   ) ;

                                ~Frame                                      ( ) ;

        bool                    operator ==                                 (   const   Frame&                      aFrame                                      ) const ;
        
        bool                    operator !=                                 (   const   Frame&                      aFrame                                      ) const ;

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Frame&                      aFrame                                      ) ;

        bool                    isDefined                                   ( ) const ;

        bool                    isQuasiInertial                             ( ) const ;

        bool                    hasParent                                   ( ) const ;

        const Frame&            accessParent                                ( ) const ;

        const Frame&            accessAncestor                              (           Uint8                       anAncestorDegree                            ) const ;

        Shared<const Provider>  accessProvider                              ( ) const ;

        String                  getName                                     ( ) const ;

        Vector3d                getOriginIn                                 (   const   Frame&                      aFrame,
                                                                                const   Instant&                    anInstant                                   ) const ;

        Axes                    getAxesIn                                   (   const   Frame&                      aFrame,
                                                                                const   Instant&                    anInstant                                   ) const ;

        Transform               getTransformTo                              (   const   Frame&                      aFrame,
                                                                                const   Instant&                    anInstant                                   ) const ;

        static Frame            Undefined                                   ( ) ;

        static Frame            ICRF                                        ( ) ;

        static Frame            GCRF                                        ( ) ;

        static Frame            EME2000                                     ( ) ;

        static Frame            CIRF                                        ( ) ;

        static Frame            TIRF                                        ( ) ;

        static Frame            ITRF                                        ( ) ;

    private:

        String                  name_ ;
        bool                    quasiInertial_ ;

        Shared<const Frame>     parentFrameSPtr_ ;

        Shared<Provider>        providerSPtr_ ; // Provides transform from parent to instance

        Uint8                   getDepth                                    ( ) const ;

        static const Frame&     FindCommonAncestor                          (   const   Frame&                      aFirstFrame,
                                                                                const   Frame&                      aSecondFrame                                ) ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////