////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Coordinate/Frame/Providers/IERS/Manager.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Physics_Coordinate_Frame_Providers_IERS_Manager__
#define __Library_Physics_Coordinate_Frame_Providers_IERS_Manager__

#include <Library/Physics/Coordinate/Frame/Providers/IERS/Finals2000A.hpp>
#include <Library/Physics/Coordinate/Frame/Providers/IERS/BulletinA.hpp>
#include <Library/Physics/Time/Instant.hpp>

#include <Library/Mathematics/Objects/Vector.hpp>

#include <Library/Core/Containers/Array.hpp>
#include <Library/Core/Types/Real.hpp>
#include <Library/Core/Types/Index.hpp>

#include <mutex>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{
namespace coord
{
namespace frame
{
namespace provider
{
namespace iers
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using library::core::types::Index ;
using library::core::types::Real ;
using library::core::ctnr::Array ;

using library::math::obj::Vector2d ;

using library::physics::time::Instant ;
using library::physics::coord::frame::provider::iers::BulletinA ;
using library::physics::coord::frame::provider::iers::Finals2000A ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      IERS bulletins manager (thread-safe)
///
/// @ref                        https://www.iers.org/IERS/EN/DataProducts/EarthOrientationData/eop.html

class Manager
{

    public:

                                Manager                                     ( ) ;

        BulletinA               getBulletinAAt                              (   const   Instant&                    anInstant                                   ) const ;

        Finals2000A             getFinals2000AAt                            (   const   Instant&                    anInstant                                   ) const ;

        /// @brief              Get polar motion at instant
        ///
        /// @param              [in] anInstant An instant
        /// @return             [asec] Polar motion

        Vector2d                getPolarMotionAt                            (   const   Instant&                    anInstant                                   ) const ;

        /// @brief              Get UT1 - UTC at instant
        ///
        /// @param              [in] anInstant An instant
        /// @return             [sec] UT1 - UTC

        Real                    getUt1MinusUtcAt                            (   const   Instant&                    anInstant                                   ) const ;

        /// @brief              Get length of day at instant
        ///
        /// @param              [in] anInstant An instant
        /// @return             [ms] Length of day

        Real                    getLodAt                                    (   const   Instant&                    anInstant                                   ) const ;

        void                    addBulletinA                                (   const   BulletinA&                  aBulletinA                                  ) ;

        void                    addFinals2000A                              (   const   Finals2000A&                aFinals2000A                                ) ;

    private:

        Array<BulletinA>        aBulletins_ ;
        Array<Finals2000A>      finals2000aArray_ ;
        
        mutable std::mutex      mutex_ ;

        mutable Index           aBulletinIndex_ ;
        mutable Index           finals2000aIndex_ ;

        const BulletinA*        accessBulletinAAt                           (   const   Instant&                    anInstant                                   ) const ;

        const Finals2000A*      accessFinals2000AAt                         (   const   Instant&                    anInstant                                   ) const ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////