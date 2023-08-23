/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_CSSISpaceWeather__
#define __OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_CSSISpaceWeather__

#include <OpenSpaceToolkit/Core/Containers/Array.hpp>
#include <OpenSpaceToolkit/Core/Containers/Map.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>
#include <OpenSpaceToolkit/Core/Types/Integer.hpp>
#include <OpenSpaceToolkit/Core/Types/Real.hpp>

#include <OpenSpaceToolkit/Physics/Time/Date.hpp>
#include <OpenSpaceToolkit/Physics/Time/Duration.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Time/Interval.hpp>

namespace ostk
{
namespace physics
{
namespace environment
{
namespace atmospheric
{
namespace earth
{

using ostk::core::types::Integer;
using ostk::core::types::Real;
using ostk::core::types::String;
using ostk::core::ctnr::Map;
using ostk::core::ctnr::Array;
using ostk::core::fs::File;

using ostk::physics::time::Date;
using ostk::physics::time::DateTime;
using ostk::physics::time::Instant;
using ostk::physics::time::Duration;
using ostk::physics::time::Interval;
using ostk::physics::time::Scale;

/// @brief                      Center for Space Weather and Innovation (CSSI) Space Weather data file.
///
///                             Consolidated data set which contains solar radiation and geomagnetic indices.
///                             Particularly contains the F10.7 solar flux index and Ap/Kp geomagnetic indices,
///                             which are commonly used to model atmospheric density.
///
/// @ref                        http://celestrak.org/SpaceData/SpaceWx-format.php

class CSSISpaceWeather
{
   public:
    struct Reading
    {
        Date date;      /// UTC day of reading.
        Integer BSRN;   /// Bartels Solar Rotation Number. A sequence of 27-day intervals counted continuously from 1832
                        /// Feb 8.
        Integer ND;     /// Number of Day within the Bartels 27-day cycle (01-27).
        Integer Kp1;    /// Planetary 3-hour Range Index (Kp) for 0000-0300 UT.
        Integer Kp2;    /// Planetary 3-hour Range Index (Kp) for 0300-0600 UT.
        Integer Kp3;    /// Planetary 3-hour Range Index (Kp) for 0600-0900 UT.
        Integer Kp4;    /// Planetary 3-hour Range Index (Kp) for 0900-1200 UT.
        Integer Kp5;    /// Planetary 3-hour Range Index (Kp) for 1200-1500 UT.
        Integer Kp6;    /// Planetary 3-hour Range Index (Kp) for 1500-1800 UT.
        Integer Kp7;    /// Planetary 3-hour Range Index (Kp) for 1800-2100 UT.
        Integer Kp8;    /// Planetary 3-hour Range Index (Kp) for 2100-0000 UT.
        Integer KpSum;  /// Sum of the 8 Kp indices for the day.
        Integer Ap1;    /// Planetary Equivalent Amplitude (Ap) for 0000-0300 UT.
        Integer Ap2;    /// Planetary Equivalent Amplitude (Ap) for 0300-0600 UT.
        Integer Ap3;    /// Planetary Equivalent Amplitude (Ap) for 0600-0900 UT.
        Integer Ap4;    /// Planetary Equivalent Amplitude (Ap) for 0900-1200 UT.
        Integer Ap5;    /// Planetary Equivalent Amplitude (Ap) for 1200-1500 UT.
        Integer Ap6;    /// Planetary Equivalent Amplitude (Ap) for 1500-1800 UT.
        Integer Ap7;    /// Planetary Equivalent Amplitude (Ap) for 1800-2100 UT.
        Integer Ap8;    /// Planetary Equivalent Amplitude (Ap) for 2100-0000 UT.
        Integer ApAvg;  /// Arithmetic average of the 8 Ap indices for the day.
        Real Cp;        /// Cp or Planetary Daily Character Figure. A qualitative estimate of overall level of magnetic
                        /// activity for the day determined from the sum of the 8 Ap indices. Cp ranges, in steps of
                        /// one-tenth, from 0 (quiet) to 2.5 (highly disturbed).
        Integer C9;     /// C9. A conversion of the 0-to-2.5 range of the Cp index to one digit between 0 and 9.
        Integer ISN;    /// International Sunspot Number. Records contain the Zurich number through 1980 Dec 31 and the
                        /// International Brussels number thereafter.
        Real F107Obs;   /// Observed 10.7-cm Solar Radio Flux (F10.7). Measured at Ottawa at 1700 UT daily from 1947 Feb
                        /// 14 until 1991 May 31 and measured at Penticton at 2000 UT from 1991 Jun 01 on. Expressed in
                        /// units of 10-22 W/m2/Hz.
        Real F107Adj;   /// 10.7-cm Solar Radio Flux (F10.7) adjusted to 1 AU.
        String F107DataType;   /// Flux Qualifier.
                               /// OBS: Observed flux measurement
                               /// INT: CelesTrak linear interpolation of missing data
                               /// PRD: 45-Day predicted flux
                               /// PRM: Monthly predicted flux
        Real F107ObsCenter81;  /// Centered 81-day arithmetic average of F107 (observed).
        Real F107ObsLast81;    /// Last 81-day arithmetic average of F107 (observed).
        Real F107AdjCenter81;  /// Centered 81-day arithmetic average of F10.7 (adjusted).
        Real F107AdjLast81;    /// Last 81-day arithmetic average of F10.7 (adjusted)
    };

    friend std::ostream& operator<<(std::ostream& anOutputStream, const CSSISpaceWeather& aCSSISpaceWeather);

    /// @brief                  true if defined
    ///
    /// @return                 True if defined.

    bool isDefined() const;

    /// @brief                  Access last observation Date. File publication date is the day following the last
    /// observation.
    ///
    /// @return                 Last observation Date.

    const Date& accessLastObservationDate() const;

    /// @brief                  Access observation Interval.
    ///
    /// @return                 Observation Interval of Instants.

    const Interval& accessObservationInterval() const;

    /// @brief                  Access daily prediction Interval.
    ///
    /// @return                 Daily prediction Interval of Instants.

    const Reading& accessObservationAt(const Instant& anInstant) const;

    /// @brief                  Access daily prediction Interval.
    ///
    /// @return                 Daily prediction Interval of Instants.

    const Interval& accessDailyPredictionInterval() const;

    /// @brief                  Access daily prediction at Instant.
    ///
    /// @return                 Daily prediction at Instant.

    const Reading& accessDailyPredictionAt(const Instant& anInstant) const;

    /// @brief                  Access monthly prediction Interval.
    ///
    /// @return                 Monthly prediction Interval of Instants.

    const Interval& accessMonthlyPredictionInterval() const;

    /// @brief                  Access monthly prediction at Instant.
    ///
    /// @return                 Monthly prediction at Instant.

    const Reading& accessMonthlyPredictionAt(const Instant& anInstant) const;

    /// @brief                  Access reading at Instant.
    ///                         Look first in observations, then in daily predictions, then monthly predictions.
    ///
    /// @return                 Reading prediction at Instant.

    const Reading& accessReadingAt(const Instant& anInstant) const;

    /// @brief                  Access last reading before anInstant where aPredicate is true.
    ///
    /// @param                  [in] aPredicate A predicate.
    /// @param                  [in] anInstant An Instant.
    /// @return                 Last Reading satisfying predicate.

    const Reading& accessLastReadingWhere(
        const std::function<bool(const Reading&)>& aPredicate, const Instant& anInstant
    ) const;

    /// @brief                  Undefined factory function
    ///
    /// @return                 Undefined CSSI Space Weather object.

    static CSSISpaceWeather Undefined();

    /// @brief                  Load CSSI Space Weather file.
    ///
    /// @param                  [in] aFile A CSSI Space Weather file.
    /// @return                 CSSI Space Weather object.

    static CSSISpaceWeather Load(const File& aFile);

    static CSSISpaceWeather LoadLegacy(const File& aFile);

   private:
    Date lastObservationDate_;

    Interval observationInterval_;
    Map<Integer, CSSISpaceWeather::Reading> observations_;

    Interval dailyPredictionInterval_;
    Map<Integer, CSSISpaceWeather::Reading> dailyPredictions_;

    Interval monthlyPredictionInterval_;
    Map<Integer, CSSISpaceWeather::Reading> monthlyPredictions_;

    CSSISpaceWeather();
};

}  // namespace earth
}  // namespace atmospheric
}  // namespace environment
}  // namespace physics
}  // namespace ostk

#endif
