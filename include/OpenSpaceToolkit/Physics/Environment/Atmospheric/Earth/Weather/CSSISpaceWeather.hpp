/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_CSSISpaceWeather__
#define __OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_CSSISpaceWeather__

#include <OpenSpaceToolkit/Core/Containers/Map.hpp>
#include <OpenSpaceToolkit/Core/Containers/Array.hpp>
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
namespace weather
{

namespace fs = ostk::core::fs;

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
    struct Observation
    {
        Date date;
        Integer BSRN;	/// Bartels Solar Rotation Number. A sequence of 27-day intervals counted continuously from 1832 Feb 8.
        Integer ND;	/// Number of Day within the Bartels 27-day cycle (01-27).
        Integer KP1;	/// Planetary 3-hour Range Index (Kp) for 0000-0300 UT.
        Integer KP2;	/// Planetary 3-hour Range Index (Kp) for 0300-0600 UT.
        Integer KP3;	/// Planetary 3-hour Range Index (Kp) for 0600-0900 UT.
        Integer KP4;	/// Planetary 3-hour Range Index (Kp) for 0900-1200 UT.
        Integer KP5;	/// Planetary 3-hour Range Index (Kp) for 1200-1500 UT.
        Integer KP6;	/// Planetary 3-hour Range Index (Kp) for 1500-1800 UT.
        Integer KP7;	/// Planetary 3-hour Range Index (Kp) for 1800-2100 UT.
        Integer KP8;	/// Planetary 3-hour Range Index (Kp) for 2100-0000 UT.
        Integer KP_SUM;	/// Sum of the 8 Kp indices for the day.
        Integer AP1;	/// Planetary Equivalent Amplitude (Ap) for 0000-0300 UT.
        Integer AP2;	/// Planetary Equivalent Amplitude (Ap) for 0300-0600 UT.
        Integer AP3;	/// Planetary Equivalent Amplitude (Ap) for 0600-0900 UT.
        Integer AP4;	/// Planetary Equivalent Amplitude (Ap) for 0900-1200 UT.
        Integer AP5;	/// Planetary Equivalent Amplitude (Ap) for 1200-1500 UT.
        Integer AP6;	/// Planetary Equivalent Amplitude (Ap) for 1500-1800 UT.
        Integer AP7;	/// Planetary Equivalent Amplitude (Ap) for 1800-2100 UT.
        Integer AP8;	/// Planetary Equivalent Amplitude (Ap) for 2100-0000 UT.
        Integer AP_AVG;	/// Arithmetic average of the 8 Ap indices for the day.
        Real CP;	/// Cp or Planetary Daily Character Figure. A qualitative estimate of overall level of magnetic activity for the day determined from the sum of the 8 Ap indices. Cp ranges, in steps of one-tenth, from 0 (quiet) to 2.5 (highly disturbed).
        Integer C9;	/// C9. A conversion of the 0-to-2.5 range of the Cp index to one digit between 0 and 9.
        Integer ISN;	/// International Sunspot Number. Records contain the Zurich number through 1980 Dec 31 and the International Brussels number thereafter.
        Real F107_OBS;	/// Observed 10.7-cm Solar Radio Flux (F10.7). Measured at Ottawa at 1700 UT daily from 1947 Feb 14 until 1991 May 31 and measured at Penticton at 2000 UT from 1991 Jun 01 on. Expressed in units of 10-22 W/m2/Hz.
        Real F107_ADJ;	/// 10.7-cm Solar Radio Flux (F10.7) adjusted to 1 AU.
        String F107_DATA_TYPE;	/// Flux Qualifier.
                        /// OBS: Observed flux measurement
                        /// INT: CelesTrak linear interpolation of missing data
                        /// PRD: 45-Day predicted flux
                        /// PRM: Monthly predicted flux
        Real F107_OBS_CENTER81;	/// Centered 81-day arithmetic average of F107 (observed).
        Real F107_OBS_LAST81;	/// Last 81-day arithmetic average of F107 (observed).
        Real F107_ADJ_CENTER81;	/// Centered 81-day arithmetic average of F10.7 (adjusted).
        Real F107_ADJ_LAST81;	/// Last 81-day arithmetic average of F10.7 (adjusted)
    };

    // Note: daily prediction contains idential values to observations
    using DailyPrediction = Observation;

    struct MonthlyPrediction {
        Date date;
        Integer BSRN;	/// Bartels Solar Rotation Number. A sequence of 27-day intervals counted continuously from 1832 Feb 8.
        Integer ND;	/// Number of Day within the Bartels 27-day cycle (01-27).
        Real F107_OBS;	/// Observed 10.7-cm Solar Radio Flux (F10.7). Measured at Ottawa at 1700 UT daily from 1947 Feb 14 until 1991 May 31 and measured at Penticton at 2000 UT from 1991 Jun 01 on. Expressed in units of 10-22 W/m2/Hz.
        Real F107_ADJ;	/// 10.7-cm Solar Radio Flux (F10.7) adjusted to 1 AU.
        String F107_DATA_TYPE;	/// Flux Qualifier.
                        /// OBS: Observed flux measurement
                        /// INT: CelesTrak linear interpolation of missing data
                        /// PRD: 45-Day predicted flux
                        /// PRM: Monthly predicted flux
        Real F107_OBS_CENTER81;	/// Centered 81-day arithmetic average of F10.7 (observed).
        Real F107_OBS_LAST81;	/// Last 81-day arithmetic average of F10.7 (observed).
        Real F107_ADJ_CENTER81;	/// Centered 81-day arithmetic average of F10.7 (adjusted).
        Real F107_ADJ_LAST81;	/// Last 81-day arithmetic average of F10.7 (adjusted)
    };


    friend std::ostream& operator<<(std::ostream& anOutputStream, const CSSISpaceWeather& aCSSISpaceWeather);

    bool isDefined() const;

    const Interval& accessObservationInterval() const;

    const Interval& accessDailyPredictionInterval() const;

    const Interval& accessMonthlyPredictionInterval() const;

    Interval getObservationInterval() const;

    CSSISpaceWeather::Observation getObservationAt(const Instant& anInstant) const;

    Interval getDailyPredictionInterval() const;

    CSSISpaceWeather::DailyPrediction getDailyPredictionAt(const Instant& anInstant) const;

    Interval getMonthlyPredictionInterval() const;

    CSSISpaceWeather::MonthlyPrediction getMonthlyPredictionAt(const Instant& anInstant) const;
    
    static CSSISpaceWeather Undefined();

    static CSSISpaceWeather Load(const fs::File& aFile);

   private:
    Interval observationInterval_;
    Map<Integer, CSSISpaceWeather::Observation> observations_;

    Interval dailyPredictionInterval_;
    Map<Integer, CSSISpaceWeather::DailyPrediction> dailyPredictions_;

    Interval monthlyPredictionInterval_;
    Map<Integer, CSSISpaceWeather::MonthlyPrediction> monthlyPredictions_;

    CSSISpaceWeather();
};

}  // namespace iers
}  // namespace provider
}  // namespace frame
}  // namespace coord
}  // namespace physics
}  // namespace ostk

#endif
