////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           Library/Physics/Coordinate/Frame/Providers/IERS/BulletinA.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Physics_Coordinate_Frame_Providers_IERS_BulletinA__
#define __Library_Physics_Coordinate_Frame_Providers_IERS_BulletinA__

#include <Library/Physics/Time/Interval.hpp>
#include <Library/Physics/Time/Duration.hpp>
#include <Library/Physics/Time/Instant.hpp>
#include <Library/Physics/Time/Date.hpp>

#include <Library/Core/FileSystem/File.hpp>
#include <Library/Core/Containers/Map.hpp>
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
using library::core::ctnr::Map ;
using library::core::fs::File ;

using library::physics::time::Date ;
using library::physics::time::Instant ;
using library::physics::time::Duration ;
using library::physics::time::Interval ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      IERS Bulletin A
///
///                             Contains rapid determinations for eEarth orientation parameters:
///                             x/y pole, UT1-UTC and their errors at daily intervals and predictions for 1 year into the future.
///
///                             The contents of IERS Bulletin A are divided into four sections:
///
///                             1. General information including key definitions and the most recently adopted values of DUT1 and TAI-UTC.
///
///                             2. Quick-look daily estimates of the EOPs determined by smoothing the observed data.
///                             This involves the application of systematic corrections and statistical weighting.
///                             The results are published with a delay of about one to three days between the date of publication and the last available date with estimated EOP.
///
///                             3. Predictions of x, y, and UT1-UTC, up to 365 days following the last day of data.
///                             The predictions use similar algorithms based on seasonal filtering and autoregressive processing for x, y, and UT1.
///
///                             4. The combination series for the celestial pole offsets.
///                             Bulletin A contains celestial pole offsets with respect to the IAU1980 Nutation theroy (dpsi and deps)
///                             and the IAU 2000 Resolutions (dX and dY), beginning on 1 January 2003.
///
/// @ref                        https://datacenter.iers.org/productMetadata.php?id=6

class BulletinA
{

    public:

        struct Observation
        {

            Integer             year ;                                          ///< Year (to get true calendar year, add 1900 for MJD <= 51543 or add 2000 for MJD >= 51544)
            Integer             month ;                                         ///< Month number
            Integer             day ;                                           ///< Day of month

            Real                mjd ;                                           ///< Modified Julian Day

            Real                x ;                                             ///< [asec] PM-x
            Real                xError ;                                        ///< [asec] Error in PM-x
            Real                y ;                                             ///< [asec] PM-y
            Real                yError ;                                        ///< [asec] Error in PM-y

            Real                ut1MinusUtc ;                                   ///< [s] UT1-UTC
            Real                ut1MinusUtcError ;                              ///< [s] Error in UT1-UTC

        } ;

        struct Prediction
        {

            Integer             year ;                                          ///< Year (to get true calendar year, add 1900 for MJD <= 51543 or add 2000 for MJD >= 51544)
            Integer             month ;                                         ///< Month number
            Integer             day ;                                           ///< Day of month

            Real                mjd ;                                           ///< Modified Julian Day

            Real                x ;                                             ///< [asec] PM-x
            Real                y ;                                             ///< [asec] PM-y

            Real                ut1MinusUtc ;                                   ///< [s] UT1-UTC

        } ;

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   BulletinA&                  aBulletinA                                  ) ;

        bool                    isDefined                                   ( ) const ;

        const Date&             accessReleaseDate                           ( ) const ;

        const Duration&         accessTAIMinusUTC                           ( ) const ;

        const Instant&          accessTAIMinusUTCEpoch                      ( ) const ;

        const Interval&         accessObservationInterval                   ( ) const ;

        const Interval&         accessPredictionInterval                    ( ) const ;

        Date                    getReleaseDate                              ( ) const ;

        Duration                getTAIMinusUTC                              ( ) const ;

        Instant                 getTAIMinusUTCEpoch                         ( ) const ;

        Interval                getObservationInterval                      ( ) const ;

        BulletinA::Observation  getObservationAt                            (   const   Instant&                    anInstant                                   ) const ;

        Interval                getPredictionInterval                       ( ) const ;

        BulletinA::Prediction   getPredictionAt                             (   const   Instant&                    anInstant                                   ) const ;

        static BulletinA        Undefined                                   ( ) ;

        static BulletinA        Load                                        (   const   fs::File&                   aFile                                       ) ;

    private:

        Date                    releaseDate_ ;

        Duration                taiMinusUtc_ ;
        Instant                 taiMinusUtcEpoch_ ;

        Interval                observationInterval_ ;
        Map<Integer, BulletinA::Observation> observations_ ;

        Interval                predictionInterval_ ;
        Map<Integer, BulletinA::Prediction> predictions_ ;

                                BulletinA                                   ( ) ;

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
