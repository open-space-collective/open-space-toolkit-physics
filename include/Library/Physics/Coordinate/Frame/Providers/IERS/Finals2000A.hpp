////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library ▸ Physics
/// @file           Library/Physics/Coordinate/Frame/Providers/IERS/Finals2000A.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Physics_Coordinate_Frame_Providers_IERS_Finals2000A__
#define __Library_Physics_Coordinate_Frame_Providers_IERS_Finals2000A__

#include <Library/Physics/Time/Interval.hpp>
#include <Library/Physics/Time/Duration.hpp>
#include <Library/Physics/Time/Instant.hpp>
#include <Library/Physics/Time/Date.hpp>

#include <Library/Mathematics/Objects/Vector.hpp>

#include <Library/Core/FileSystem/File.hpp>
#include <Library/Core/Containers/Map.hpp>
#include <Library/Core/Containers/Pair.hpp>
#include <Library/Core/Types/Real.hpp>
#include <Library/Core/Types/Integer.hpp>

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

namespace fs = library::core::fs ;

using library::core::types::Integer ;
using library::core::types::Real ;
using library::core::ctnr::Pair ;
using library::core::ctnr::Map ;
using library::core::fs::File ;

using library::math::obj::Vector2d ;

using library::physics::time::Date ;
using library::physics::time::Instant ;
using library::physics::time::Duration ;
using library::physics::time::Interval ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Standard Rapid EOP Data since 01. January 1992 (IAU2000)
///
///                             This file (updated weekly) is the complete Earth orientation data set, since 1 January 1992 with 1 year of predictions.
///                             The nutation series in dX and dY uses the IAU 2000A Nutation Theory.
///
/// @ref                        https://www.iers.org/IERS/EN/DataProducts/EarthOrientationData/eop.html -> finals.data (IAU2000)

class Finals2000A
{

    public:

        struct Data
        {

            Integer             year ;                                          ///< Year (to get true calendar year, add 1900 for MJD <= 51543 or add 2000 for MJD >= 51544)
            Integer             month ;                                         ///< Month number
            Integer             day ;                                           ///< Day of month

            Real                mjd ;                                           ///< Fractional Modified Julian Date (MJD UTC)

            char                polarMotionflag ;                               ///< IERS (I) or Prediction (P) flag for Bulletin A polar motion values

            Real                x_A ;                                           ///< [asec] Bulletin A PM-x
            Real                xError_A ;                                      ///< [asec] Error in PM-x
            Real                y_A ;                                           ///< [asec] Bulletin A PM-y
            Real                yError_A ;                                      ///< [asec] Error in PM-y

            char                ut1MinusUtcFlag ;                               ///< IERS (I) or Prediction (P) flag for Bulletin A UT1-UTC values

            Real                ut1MinusUtc_A ;                                 ///< [s] Bulletin A UT1-UTC
            Real                ut1MinusUtcError_A ;                            ///< [s] Error in UT1-UTC
            Real                lod_A ;                                         ///< [ms] Bulletin A LOD (not always filled)
            Real                lodError_A ;                                    ///< [ms] Error in LOD (not always filled)

            char                nutationFlag ;                                  ///< IERS (I) or Prediction (P) flag for Bulletin A nutation values

            Real                dx_A ;                                          ///< [amsec] Bulletin A dX wrt IAU2000A Nutation, Free Core Nutation NOT Removed
            Real                dxError_A ;                                     ///< [amsec] Error in dX
            Real                dy_A ;                                          ///< [amsec] Bulletin A dY wrt IAU2000A Nutation, Free Core Nutation NOT Removed
            Real                dyError_A ;                                     ///< [amsec] Error in dY
            Real                x_B ;                                           ///< [asec] Bulletin B PM-x
            Real                y_B ;                                           ///< [asec] Bulletin B PM-y
            Real                ut1MinusUtc_B ;                                 ///< [s] Bulletin B UT1-UTC
            Real                dx_B ;                                          ///< [amsec] Bulletin B dX wrt IAU2000A Nutation
            Real                dy_B ;                                          ///< [amsec] Bulletin B dY wrt IAU2000A Nutation

        } ;

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Finals2000A&                  aFinals2000A                                  ) ;

        bool                    isDefined                                   ( ) const ;

        Interval                getInterval                                 ( ) const ;

        Vector2d                getPolarMotionAt                            (   const   Instant&                    anInstant                                   ) const ;

        Real                    getUt1MinusUtcAt                            (   const   Instant&                    anInstant                                   ) const ;

        Real                    getLodAt                                    (   const   Instant&                    anInstant                                   ) const ;

        Finals2000A::Data       getDataAt                                   (   const   Instant&                    anInstant                                   ) const ;

        static Finals2000A      Undefined                                   ( ) ;

        static Finals2000A      Load                                        (   const   fs::File&                   aFile                                       ) ;

    private:

        Interval                span_ ;
        Map<Real, Finals2000A::Data> data_ ;

                                Finals2000A                             ( ) ;

        Pair<const Finals2000A::Data*, const Finals2000A::Data*> accessDataRange ( const   Instant&                 anInstant                                   ) const ;

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
