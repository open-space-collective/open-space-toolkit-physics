////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Environment/Object/Geometry.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Physics_Environment_Object_Geometry__
#define __Library_Physics_Environment_Object_Geometry__

#include <Library/Physics/Coordinate/Frame.hpp>
#include <Library/Physics/Time/Instant.hpp>

#include <Library/Mathematics/Geometry/3D/Object.hpp>

#include <Library/Core/Types/Shared.hpp>
#include <Library/Core/Types/Unique.hpp>
#include <Library/Core/Types/Unique.hpp>

#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{
namespace env
{
namespace object
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using library::core::types::Unique ;
using library::core::types::Shared ;

using library::physics::time::Instant ;
using library::physics::coord::Frame ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Geometry
{

    public:

        typedef math::geom::d3::Object Object ;

                                Geometry                                    (   const   Geometry::Object&           anObject,
                                                                                const   Shared<const Frame>&        aFrameSPtr                                  ) ;

                                Geometry                                    (   const   Unique<Geometry::Object>&   anObjectUPtr,
                                                                                const   Shared<const Frame>&        aFrameSPtr                                  ) ;

                                Geometry                                    (   const   Geometry&                   aGeometry                                   ) ;

        Geometry&               operator =                                  (   const   Geometry&                   aGeometry                                   ) ;

        bool                    operator ==                                 (   const   Geometry&                   aGeometry                                   ) const ;
        
        bool                    operator !=                                 (   const   Geometry&                   aGeometry                                   ) const ;

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Geometry&                   aGeometry                                   ) ;

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

        Shared<const Frame>     accessFrame                                 ( ) const ;

        Geometry                in                                          (   const   Shared<const Frame>&        aFrameSPtr,
                                                                                const   Instant&                    anInstant                                   ) const ;

        /// @brief              Returns true if geometry's underlying object is of given type
        ///
        /// @return             True if geometry's underlying object is of given type

        template <class Type>
        bool                    is                                          ( ) const
        {
            return this->isDefined() && (dynamic_cast<const Type*>(objectUPtr_.get()) != nullptr) ;
        }

        /// @brief              Access eometry's underlying object
        ///
        /// @return             Reference to underlying object

        template <class Type>
        const Type&             as                                          ( ) const
        {

            if (!this->isDefined())
            {
                throw library::core::error::RuntimeError("Geometry is undefined.") ;
            }

            const Type* objectPtr = dynamic_cast<const Type*>(objectUPtr_.get()) ;

            if (objectPtr == nullptr)
            {
                throw library::core::error::RuntimeError("Cannot convert underlying object to type.") ;
            }

            return *objectPtr ;

        }

        Geometry                intersectionWith                            (   const   Geometry&                   aGeometry                                   ) const ;

        static Geometry         Undefined                                   ( ) ;

    private:

        Unique<Geometry::Object> objectUPtr_ ;

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