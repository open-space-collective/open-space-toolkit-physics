/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_CSSISpaceWeather__
#define __OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_CSSISpaceWeather__

#include <optional>

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Container/Map.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>

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

using ostk::core::container::Array;
using ostk::core::container::Map;
using ostk::core::filesystem::File;
using ostk::core::type::String;

using ostk::physics::time::Date;
using ostk::physics::time::DateTime;
using ostk::physics::time::Duration;
using ostk::physics::time::Instant;
using ostk::physics::time::Interval;
using ostk::physics::time::Scale;

/// @brief Center for Space Weather and Innovation (CSSI) Space Weather data file.
///
/// Consolidated data set which contains solar radiation and geomagnetic indices.
/// Particularly contains the F10.7 solar flux index and Ap/Kp geomagnetic indices,
/// which are commonly used to model atmospheric density.
///
/// @ref http://celestrak.org/SpaceData/SpaceWx-format.php

class CSSISpaceWeather
{
   public:
    /// @brief A daily reading
    ///
    /// Numeric fields are std::nullopt when the cell is empty in the file.
    struct Reading
    {
        Date date;                /// UTC day of reading.
        std::optional<int> BSRN;  /// Bartels Solar Rotation Number. A sequence of 27-day intervals counted continuously
                                  /// from 1832 Feb 8.
        std::optional<int> ND;    /// Number of Day within the Bartels 27-day cycle (01-27).
        std::optional<int> Kp1;   /// Planetary 3-hour Range Index (Kp) for 0000-0300 UT.
        std::optional<int> Kp2;   /// Planetary 3-hour Range Index (Kp) for 0300-0600 UT.
        std::optional<int> Kp3;   /// Planetary 3-hour Range Index (Kp) for 0600-0900 UT.
        std::optional<int> Kp4;   /// Planetary 3-hour Range Index (Kp) for 0900-1200 UT.
        std::optional<int> Kp5;   /// Planetary 3-hour Range Index (Kp) for 1200-1500 UT.
        std::optional<int> Kp6;   /// Planetary 3-hour Range Index (Kp) for 1500-1800 UT.
        std::optional<int> Kp7;   /// Planetary 3-hour Range Index (Kp) for 1800-2100 UT.
        std::optional<int> Kp8;   /// Planetary 3-hour Range Index (Kp) for 2100-0000 UT.
        std::optional<int> KpSum;  /// Sum of the 8 Kp indices for the day.
        std::optional<int> Ap1;    /// Planetary Equivalent Amplitude (Ap) for 0000-0300 UT.
        std::optional<int> Ap2;    /// Planetary Equivalent Amplitude (Ap) for 0300-0600 UT.
        std::optional<int> Ap3;    /// Planetary Equivalent Amplitude (Ap) for 0600-0900 UT.
        std::optional<int> Ap4;    /// Planetary Equivalent Amplitude (Ap) for 0900-1200 UT.
        std::optional<int> Ap5;    /// Planetary Equivalent Amplitude (Ap) for 1200-1500 UT.
        std::optional<int> Ap6;    /// Planetary Equivalent Amplitude (Ap) for 1500-1800 UT.
        std::optional<int> Ap7;    /// Planetary Equivalent Amplitude (Ap) for 1800-2100 UT.
        std::optional<int> Ap8;    /// Planetary Equivalent Amplitude (Ap) for 2100-0000 UT.
        std::optional<int> ApAvg;  /// Arithmetic average of the 8 Ap indices for the day.
        std::optional<double> Cp;  /// Cp or Planetary Daily Character Figure. A qualitative estimate of overall level
                                   /// of magnetic activity for the day determined from the sum of the 8 Ap indices. Cp
                                   /// ranges, in steps of one-tenth, from 0 (quiet) to 2.5 (highly disturbed).
        std::optional<int> C9;  /// C9. A conversion of the 0-to-2.5 range of the Cp index to one digit between 0 and 9.
        std::optional<int> ISN;  /// International Sunspot Number. Records contain the Zurich number through 1980 Dec 31
                                 /// and the International Brussels number thereafter.
        std::optional<double> F107Obs;  /// Observed 10.7-cm Solar Radio Flux (F10.7). Measured at Ottawa at 1700 UT
                                        /// daily from 1947 Feb 14 until 1991 May 31 and measured at Penticton at 2000
                                        /// UT from 1991 Jun 01 on. Expressed in units of 10-22 W/m2/Hz.
        std::optional<double> F107Adj;  /// 10.7-cm Solar Radio Flux (F10.7) adjusted to 1 AU.
        String F107DataType;            /// Flux Qualifier.
                              /// OBS: Observed flux measurement INT: CelesTrak linear interpolation of missing data
                              /// PRD: 45-Day predicted flux PRM: Monthly predicted flux
        std::optional<double> F107ObsCenter81;  /// Centered 81-day arithmetic average of F107 (observed).
        std::optional<double> F107ObsLast81;    /// Last 81-day arithmetic average of F107 (observed).
        std::optional<double> F107AdjCenter81;  /// Centered 81-day arithmetic average of F10.7 (adjusted).
        std::optional<double> F107AdjLast81;    /// Last 81-day arithmetic average of F10.7 (adjusted)
    };

    /// @brief Output stream operator.
    ///
    /// @code
    ///     std::cout << cssiSpaceWeather;
    /// @endcode
    ///
    /// @param [in] anOutputStream An output stream.
    /// @param [in] aCSSISpaceWeather A CSSI Space Weather object.
    /// @return Reference to the output stream.

    friend std::ostream& operator<<(std::ostream& anOutputStream, const CSSISpaceWeather& aCSSISpaceWeather);

    /// @brief Get last observation Date. File publication date is the day following the last observation.
    ///
    /// @code
    ///     const Date& date = cssiSpaceWeather.getLastObservationDate();
    /// @endcode
    ///
    /// @return Last observation Date.

    const Date& getLastObservationDate() const;

    /// @brief Get timestamp at which the CSSISpaceWeather file was last modified
    ///
    /// @code
    ///     const Instant& timestamp = cssiSpaceWeather.getLastModifiedTimestamp();
    /// @endcode
    ///
    /// @return Instant indicating when the file was last updated based on file modification time

    const Instant& getLastModifiedTimestamp() const;

    /// @brief Get observation Interval.
    ///
    /// @code
    ///     const std::optional<Interval>& interval = cssiSpaceWeather.getObservationInterval();
    /// @endcode
    ///
    /// @return Observation Interval of Instants.

    const std::optional<Interval>& getObservationInterval() const;

    /// @brief Get daily prediction Interval.
    ///
    /// @code
    ///     const Reading& reading = cssiSpaceWeather.getObservationAt(instant);
    /// @endcode
    ///
    /// @return Daily prediction Interval of Instants.

    const Reading& getObservationAt(const Instant& anInstant) const;

    /// @brief Get daily prediction Interval.
    ///
    /// @code
    ///     const std::optional<Interval>& interval = cssiSpaceWeather.getDailyPredictionInterval();
    /// @endcode
    ///
    /// @return Daily prediction Interval of Instants.

    const std::optional<Interval>& getDailyPredictionInterval() const;

    /// @brief Get daily prediction at Instant.
    ///
    /// @code
    ///     const Reading& reading = cssiSpaceWeather.getDailyPredictionAt(instant);
    /// @endcode
    ///
    /// @return Daily prediction at Instant.

    const Reading& getDailyPredictionAt(const Instant& anInstant) const;

    /// @brief Get monthly prediction Interval.
    ///
    /// @code
    ///     const std::optional<Interval>& interval = cssiSpaceWeather.getMonthlyPredictionInterval();
    /// @endcode
    ///
    /// @return Monthly prediction Interval of Instants.

    const std::optional<Interval>& getMonthlyPredictionInterval() const;

    /// @brief Get monthly prediction at Instant.
    ///
    /// @code
    ///     const Reading& reading = cssiSpaceWeather.getMonthlyPredictionAt(instant);
    /// @endcode
    ///
    /// @return Monthly prediction at Instant.

    const Reading& getMonthlyPredictionAt(const Instant& anInstant) const;

    /// @brief Get reading at Instant.
    /// Look first in observations, then in daily predictions, then monthly predictions.
    ///
    /// @code
    ///     const Reading& reading = cssiSpaceWeather.getReadingAt(instant);
    /// @endcode
    ///
    /// @return Reading prediction at Instant.

    const Reading& getReadingAt(const Instant& anInstant) const;

    /// @brief Get last reading before anInstant where aPredicate is true.
    ///
    /// @code
    ///     const Reading& reading = cssiSpaceWeather.getLastReadingWhere(predicate, instant);
    /// @endcode
    ///
    /// @param [in] aPredicate A predicate.
    /// @param [in] anInstant An Instant.
    /// @return Last Reading satisfying predicate.

    const Reading& getLastReadingWhere(const std::function<bool(const Reading&)>& aPredicate, const Instant& anInstant)
        const;

    /// @brief Load CSSI Space Weather file in csv format.
    ///
    /// @code
    ///     CSSISpaceWeather cssiSpaceWeather = CSSISpaceWeather::Load(file);
    /// @endcode
    ///
    /// @param [in] aFile A CSSI Space Weather file.
    /// @return CSSI Space Weather object.

    static CSSISpaceWeather Load(const File& aFile);

    /// @brief Load CSSI Space Weather file in legacy .txt format.
    ///
    /// @code
    ///     CSSISpaceWeather cssiSpaceWeather = CSSISpaceWeather::LoadLegacy(file);
    /// @endcode
    ///
    /// @param [in] aFile A CSSI Space Weather file.
    /// @return CSSI Space Weather object.

    static CSSISpaceWeather LoadLegacy(const File& aFile);

   private:
    std::optional<Date> lastObservationDate_;
    Instant lastModifiedTimestamp_;

    std::optional<Interval> observationInterval_;
    Map<int, CSSISpaceWeather::Reading> observations_;

    std::optional<Interval> dailyPredictionInterval_;
    Map<int, CSSISpaceWeather::Reading> dailyPredictions_;

    std::optional<Interval> monthlyPredictionInterval_;
    Map<int, CSSISpaceWeather::Reading> monthlyPredictions_;

    CSSISpaceWeather(const Instant& aLastModifiedTimestamp);
};

}  // namespace earth
}  // namespace atmospheric
}  // namespace environment
}  // namespace physics
}  // namespace ostk

#endif
