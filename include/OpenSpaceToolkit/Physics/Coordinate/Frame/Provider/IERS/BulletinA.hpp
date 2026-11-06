/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_BulletinA__
#define __OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_BulletinA__

#include <optional>

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
namespace coordinate
{
namespace frame
{
namespace provider
{
namespace iers
{

namespace filesystem = ostk::core::filesystem;

using ostk::core::container::Map;
using ostk::core::filesystem::File;

using ostk::physics::time::Date;
using ostk::physics::time::Duration;
using ostk::physics::time::Instant;
using ostk::physics::time::Interval;

/// @brief IERS Bulletin A
///
/// Contains rapid determinations for Earth orientation parameters:
/// x/y pole, UT1-UTC and their errors at daily intervals and predictions for 1 year into the future.
///
/// The contents of IERS Bulletin A are divided into four sections:
///
/// 1. General information including key definitions and the most recently adopted values of DUT1 and TAI-UTC.
///
/// 2. Quick-look daily estimates of the EOPs determined by smoothing the observed data.
/// This involves the application of systematic corrections and statistical weighting.
/// The results are published with a delay of about one to three days between the date of
/// publication and the last available date with estimated EOP.
///
/// 3. Predictions of x, y, and UT1-UTC, up to 365 days following the last day of data.
/// The predictions use similar algorithms based on seasonal filtering and autoregressive processing for x, y, and UT1.
///
/// 4. The combination series for the celestial pole offsets.
/// Bulletin A contains celestial pole offsets with respect to the IAU1980 Nutation theory
/// (dpsi and deps) and the IAU 2000 Resolutions (dX and dY), beginning on 1 January 2003.
///
/// @ref https://datacenter.iers.org/productMetadata.php?id=6
class BulletinA
{
   public:
    struct Observation
    {
        int year;   ///< Year (to get true calendar year, add 1900 for MJD <= 51543 or add 2000 for MJD >= 51544)
        int month;  ///< Month number
        int day;    ///< Day of month

        double mjd;  ///< Modified Julian Day

        double x;       ///< [asec] PM-x
        double xError;  ///< [asec] Error in PM-x
        double y;       ///< [asec] PM-y
        double yError;  ///< [asec] Error in PM-y

        double ut1MinusUtc;       ///< [s] UT1-UTC
        double ut1MinusUtcError;  ///< [s] Error in UT1-UTC
    };

    struct Prediction
    {
        int year;   ///< Year (to get true calendar year, add 1900 for MJD <= 51543 or add 2000 for MJD >= 51544)
        int month;  ///< Month number
        int day;    ///< Day of month

        double mjd;  ///< Modified Julian Day

        double x;  ///< [asec] PM-x
        double y;  ///< [asec] PM-y

        double ut1MinusUtc;  ///< [s] UT1-UTC
    };

    /// @brief Output stream operator.
    ///
    /// @code
    ///     std::cout << bulletinA;
    /// @endcode
    ///
    /// @param [in] anOutputStream An output stream
    /// @param [in] aBulletinA A Bulletin A
    /// @return A reference to the output stream
    friend std::ostream& operator<<(std::ostream& anOutputStream, const BulletinA& aBulletinA);

    /// @brief Access release Date
    ///
    /// @code
    ///     const Date& date = bulletinA.accessReleaseDate();
    /// @endcode
    ///
    /// @return Release Date
    const Date& accessReleaseDate() const;

    /// @brief Access timestamp at which the BulletinA file was last modified
    ///
    /// @code
    ///     const Instant& timestamp = bulletinA.accessLastModifiedTimestamp();
    /// @endcode
    ///
    /// @return Instant indicating when the file was last updated based on file modification time
    const Instant& accessLastModifiedTimestamp() const;

    /// @brief Access TAI-UTC
    ///
    /// @code
    ///     const std::optional<Duration>& taiMinusUtc = bulletinA.accessTAIMinusUTC();
    /// @endcode
    ///
    /// @return TAI-UTC
    const std::optional<Duration>& accessTAIMinusUTC() const;

    /// @brief Access TAI-UTC epoch
    ///
    /// @code
    ///     const Instant& epoch = bulletinA.accessTAIMinusUTCEpoch();
    /// @endcode
    ///
    /// @return TAI-UTC epoch
    const Instant& accessTAIMinusUTCEpoch() const;

    /// @brief Access observation Interval
    ///
    /// @code
    ///     const Interval& interval = bulletinA.accessObservationInterval();
    /// @endcode
    ///
    /// @return Observation Interval of Instants
    const Interval& accessObservationInterval() const;

    /// @brief Access prediction Interval
    ///
    /// @code
    ///     const Interval& interval = bulletinA.accessPredictionInterval();
    /// @endcode
    ///
    /// @return Prediction Interval of Instants
    const Interval& accessPredictionInterval() const;

    /// @brief Get release Date of Bulletin A
    ///
    /// @code
    ///     Date date = bulletinA.getReleaseDate();
    /// @endcode
    ///
    /// @return Release Date of Bulletin A
    Date getReleaseDate() const;

    /// @brief Get TAI-UTC
    ///
    /// @code
    ///     std::optional<Duration> taiMinusUtc = bulletinA.getTAIMinusUTC();
    /// @endcode
    ///
    /// @return TAI-UTC
    std::optional<Duration> getTAIMinusUTC() const;

    /// @brief Get TAI-UTC epoch
    ///
    /// @code
    ///     Instant epoch = bulletinA.getTAIMinusUTCEpoch();
    /// @endcode
    ///
    /// @return TAI-UTC epoch Instant
    Instant getTAIMinusUTCEpoch() const;

    /// @brief Get observation Interval
    ///
    /// @code
    ///     Interval interval = bulletinA.getObservationInterval();
    /// @endcode
    ///
    /// @return Observation Interval of Instants
    Interval getObservationInterval() const;

    /// @brief Get observation at Instant
    ///
    /// @code
    ///     BulletinA::Observation observation = bulletinA.getObservationAt(anInstant);
    /// @endcode
    ///
    /// @param [in] anInstant An Instant
    /// @return Observation at Instant
    BulletinA::Observation getObservationAt(const Instant& anInstant) const;

    /// @brief Get prediction Interval
    ///
    /// @code
    ///     Interval interval = bulletinA.getPredictionInterval();
    /// @endcode
    ///
    /// @return Prediction Interval of Instants
    Interval getPredictionInterval() const;

    /// @brief Get prediction at Instant
    ///
    /// @code
    ///     BulletinA::Prediction prediction = bulletinA.getPredictionAt(anInstant);
    /// @endcode
    ///
    /// @param [in] anInstant An Instant
    /// @return Prediction at Instant
    BulletinA::Prediction getPredictionAt(const Instant& anInstant) const;

    /// @brief Load Bulletin A from file
    ///
    /// @code
    ///     BulletinA bulletinA = BulletinA::Load(file);
    /// @endcode
    ///
    /// @param [in] aFile A file
    /// @return Bulletin A object
    static BulletinA Load(const filesystem::File& aFile);

   private:
    std::optional<Date> releaseDate_;
    Instant lastModifiedTimestamp_;

    std::optional<Duration> taiMinusUtc_;
    Instant taiMinusUtcEpoch_;

    Interval observationInterval_;
    Map<int, BulletinA::Observation> observations_;

    Interval predictionInterval_;
    Map<int, BulletinA::Prediction> predictions_;

    BulletinA();
};

}  // namespace iers
}  // namespace provider
}  // namespace frame
}  // namespace coordinate
}  // namespace physics
}  // namespace ostk

#endif
