/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Manager__
#define __OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Manager__

#include <mutex>

#include <OpenSpaceToolkit/Core/Containers/Array.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Directory.hpp>
#include <OpenSpaceToolkit/Core/Types/Index.hpp>
#include <OpenSpaceToolkit/Core/Types/Real.hpp>

#include <OpenSpaceToolkit/IO/URL.hpp>

#include <OpenSpaceToolkit/Mathematics/Objects/Vector.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/CSSISpaceWeather.hpp>
#include <OpenSpaceToolkit/Physics/Time/Duration.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

#define OSTK_PHYSICS_ENVIRONMENT_ATMOSPHERIC_EARTH_MANAGER_MODE Manager::Mode::Automatic
#define OSTK_PHYSICS_ENVIRONMENT_ATMOSPHERIC_EARTH_MANAGER_LOCAL_REPOSITORY \
    "./.open-space-toolkit/physics/environment/atmospheric/earth"
#define OSTK_PHYSICS_ENVIRONMENT_ATMOSPHERIC_EARTH_MANAGER_LOCAL_REPOSITORY_LOCK_TIMEOUT 60

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

using ostk::core::types::Index;
using ostk::core::types::Real;
using ostk::core::ctnr::Array;
using ostk::core::fs::Directory;

using ostk::io::URL;

using ostk::math::obj::Vector2d;

using ostk::physics::time::Instant;
using ostk::physics::time::Duration;
using ostk::physics::environment::atmospheric::earth::CSSISpaceWeather;

/// @brief                      CSSI space weather manager (thread-safe)
///
///                             The following environment variables can be defined:
///
///                             - "OSTK_PHYSICS_ENVIRONMENT_ATMOSPHERIC_EARTH_MANAGER_MODE" will override
///                             "DefaultMode"
///                             - "OSTK_PHYSICS_ENVIRONMENT_ATMOSPHERIC_EARTH_MANAGER_LOCAL_REPOSITORY" will
///                             override "DefaultLocalRepository"
///                             -
///                             "OSTK_PHYSICS_ENVIRONMENT_ATMOSPHERIC_EARTH_MANAGER_LOCAL_REPOSITORY_LOCK_TIMEOUT"
///                             will override "DefaultLocalRepositoryLockTimeout"
///
/// @ref                        https://ai-solutions.com/_help_Files/cssi_space_weather_file.htm

class Manager
{
   public:
    enum class Mode
    {

        Manual,    ///< Manually load and unload space weather files
        Automatic  ///< Automatically fetch, load and unload space weather files (from remote repositories)

    };

    /// @brief                  Get manager mode
    ///
    /// @return                 Manager mode

    Manager::Mode getMode() const;

    /// @brief                  Get local repository
    ///
    /// @return                 Local repository

    Directory getLocalRepository() const;

    /// @brief                  Get CSSI Space Weather directory
    ///
    /// @return                 CSSI Space Weather directory

    Directory getCSSISpaceWeatherDirectory() const;

    /// @brief                  Get array of CSSI Space Weather
    ///
    /// @return                 Array of CSSI Space Weather

    Array<CSSISpaceWeather> getCSSISpaceWeatherArray() const;

    /// @brief                  Get CSSI Space Weather at instant
    ///
    /// @param                  [in] anInstant An instant
    /// @return                 CSSI Space Weather

    CSSISpaceWeather getCSSISpaceWeatherAt(const Instant& anInstant) const;

    /// @brief                  Get an Array of 8 3-hourly Kp solar indices for the day containing instant.
    ///
    /// @param                  [in] anInstant An instant
    /// @return                 Array of 3-hourly Kp solar indices

    Array<Integer> getKp3HourSolarIndicesAt(const Instant& anInstant) const;

    /// @brief                  Get an Array of 8 3-hourly Ap solar indices for the day containing instant.
    ///
    /// @param                  [in] anInstant An instant
    /// @return                 Array of 3-hourly Ap solar indices

    Array<Integer> getAp3HourSolarIndicesAt(const Instant& anInstant) const;

    /// @brief                  Get daily Ap index for the day containing instant.
    ///
    /// @param                  [in] anInstant An instant
    /// @return                 daily Ap index

    Integer getApDailyIndexAt(const Instant& anInstant) const;

    /// @brief                  Get the daily value for F10.7 solar flux at instant.
    ///
    /// @param                  [in] anInstant An instant
    /// @return                 Daily value for F10.7 solar flux

    Real getF107SolarFluxAt(const Instant& anInstant) const;

    /// @brief                  Get the 81-day average value for F10.7 solar flux
    ///                         centered on instant.
    ///
    /// @param                  [in] anInstant An instant
    /// @return                 Centered 81-day average value for F10.7 solar flux

    Real getF107SolarFlux81DayAvgAt(const Instant& anInstant) const;

    /// @brief                  Set manager mode
    ///
    /// @param                  [in] aMode A manager mode

    void setMode(const Manager::Mode& aMode);

    /// @brief                  Set local repository
    ///
    /// @param                  [in] aDirectory A repository directory

    void setLocalRepository(const Directory& aDirectory);

    /// @brief                  Load CSSI Space Weather
    ///
    /// @param                  [in] aCSSISpaceWeather A CSSI Space Weather

    void loadCSSISpaceWeather(const CSSISpaceWeather& aCSSISpaceWeather);

    /// @brief                  Fetch latest CSSI Space Weather file
    ///
    /// @return                 Latest CSSI Space Weather file

    File fetchLatestCSSISpaceWeather();

    /// @brief                  Reset manager
    ///
    ///                         Unload all space weather files and clear cache.

    void reset();

    /// @brief                  Clear local repository
    ///
    ///                         Delete all files in local repository.

    void clearLocalRepository();

    /// @brief                  Get manager singleton
    ///
    /// @return                 Reference to manager

    static Manager& Get();

    /// @brief                  Get default manager mode
    ///
    ///                         Overriden by: OSTK_PHYSICS_ENVIRONMENT_ATMOSPHERIC_EARTH_MANAGER_MODE
    ///
    /// @return                 Default manager mode

    static Manager::Mode DefaultMode();

    /// @brief                  Get default local repository
    ///
    ///                         Overriden by: OSTK_PHYSICS_ENVIRONMENT_ATMOSPHERIC_EARTH_MANAGER_LOCAL_REPOSITORY
    ///
    /// @return                 Default local repository

    static Directory DefaultLocalRepository();

    /// @brief                  Get default local repository lock timeout
    ///
    ///                         Overriden by:
    ///                         OSTK_PHYSICS_ENVIRONMENT_ATMOSPHERIC_EARTH_MANAGER_LOCAL_REPOSITORY_LOCK_TIMEOUT
    ///
    /// @return                 Default local repository lock timeout

    static Duration DefaultLocalRepositoryLockTimeout();

   private:
    Manager::Mode mode_;

    Directory localRepository_;
    Duration localRepositoryLockTimeout_;

    Array<CSSISpaceWeather> CSSISpaceWeatherArray_;

    mutable std::mutex mutex_;

    mutable Index CSSISpaceWeatherIndex_;

    mutable Instant CSSISpaceWeatherUpdateTimestamp_;

    Manager(const Manager::Mode& aMode = Manager::DefaultMode());

    bool isLocalRepositoryLocked() const;

    File getLocalRepositoryLockFile() const;

    const CSSISpaceWeather* accessCSSISpaceWeatherAt(const Instant& anInstant) const;

    File getLatestCSSISpaceWeatherFile() const;

    void setup();

    void loadCSSISpaceWeather_(const CSSISpaceWeather& aCSSISpaceWeather);

    File fetchLatestCSSISpaceWeather_();

    void lockLocalRepository(const Duration& aTimeout);

    void unlockLocalRepository();
};

}  // namespace earth
}  // namespace atmospheric
}  // namespace environment
}  // namespace physics
}  // namespace ostk

#endif
