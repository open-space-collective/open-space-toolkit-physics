/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Environment_Object_Geometry__
#define __OpenSpaceToolkit_Physics_Environment_Object_Geometry__

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Composite.hpp>

#include <OpenSpaceToolkit/Core/Types/Shared.hpp>
#include <OpenSpaceToolkit/Core/Types/Unique.hpp>
#include <OpenSpaceToolkit/Core/Types/Unique.hpp>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ostk
{
namespace physics
{
namespace env
{
namespace object
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using ostk::core::types::Unique ;
using ostk::core::types::Shared ;

using ostk::math::geom::d3::objects::Composite ;

using ostk::physics::time::Instant ;
using ostk::physics::coord::Frame ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Geometry
{

    public:

        typedef math::geom::d3::Object Object ;

        /// @brief              Constructor
        ///
        /// @param              [in] anObject An object
        /// @param              [in] aFrameSPtr A shared pointer to frame

                                Geometry                                    (   const   Geometry::Object&           anObject,
                                                                                const   Shared<const Frame>&        aFrameSPtr                                  ) ;

        /// @brief              Constructor
        ///
        /// @param              [in] aComposite A composite
        /// @param              [in] aFrameSPtr A shared pointer to frame

                                Geometry                                    (   const   Composite&                  aComposite,
                                                                                const   Shared<const Frame>&        aFrameSPtr                                  ) ;

        /// @brief              Copy constructor
        ///
        /// @param              [in] aGeometry A geometry

                                Geometry                                    (   const   Geometry&                   aGeometry                                   ) ;

        /// @brief              Copy assignment operator
        ///
        /// @param              [in] aGeometry A geometry
        /// @return             Reference to geometry

        Geometry&               operator =                                  (   const   Geometry&                   aGeometry                                   ) ;

        /// @brief              Equal to operator
        ///
        /// @param              [in] aGeometry A geometry
        /// @return             True if geometries are equal

        bool                    operator ==                                 (   const   Geometry&                   aGeometry                                   ) const ;

        /// @brief              Not equal to operator
        ///
        /// @param              [in] aGeometry A geometry
        /// @return             True if geometries are not equal

        bool                    operator !=                                 (   const   Geometry&                   aGeometry                                   ) const ;

        /// @brief              Output stream operator
        ///
        /// @param              [in] anOutputStream An output stream
        /// @param              [in] aGeometry A geometry
        /// @return             A reference to output stream

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Geometry&                   aGeometry                                   ) ;

        /// @brief              Check if geometry is defined
        ///
        /// @return             True if geometry is defined

        bool                    isDefined                                   ( ) const ;

        /// @brief              Check if geometry intersects another geometry
        ///
        /// @param              [in] aGeometry A geometry
        /// @return             True if geometry intersects another geometry

        bool                    intersects                                  (   const   Geometry&                   aGeometry                                   ) const ;

        /// @brief              Check if geometry contains another geometry
        ///
        /// @param              [in] aGeometry A geometry
        /// @return             True if geometry contains another geometry

        bool                    contains                                    (   const   Geometry&                   aGeometry                                   ) const ;

        /// @brief              Access composite
        ///
        /// @return             Reference to composite

        const Composite&        accessComposite                             ( ) const ;

        /// @brief              Access frame
        ///
        /// @return             Shared pointer to frame

        Shared<const Frame>     accessFrame                                 ( ) const ;

        /// @brief              Get geometry expressed in a given frame
        ///
        /// @param              [in] aFrameSPtr A shared pointer to frame
        /// @param              [in] anInstant An instant
        /// @return             Geometry expressed in a given frame

        Geometry                in                                          (   const   Shared<const Frame>&        aFrameSPtr,
                                                                                const   Instant&                    anInstant                                   ) const ;

        /// @brief              Compute intersection of geometry with another geometry
        ///
        /// @param              [in] aGeometry A geometry
        /// @return             Intersection of geometry with another geometry

        Geometry                intersectionWith                            (   const   Geometry&                   aGeometry                                   ) const ;

        /// @brief              Constructs an undefined geometry
        ///
        /// @code
        ///                     Geometry geometry = Geometry::Undefined() ; // Undefined
        /// @endcode
        ///
        /// @return             Undefined geometry

        static Geometry         Undefined                                   ( ) ;

    private:

        Composite               composite_ ;
        Shared<const Frame>     frameSPtr_ ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
