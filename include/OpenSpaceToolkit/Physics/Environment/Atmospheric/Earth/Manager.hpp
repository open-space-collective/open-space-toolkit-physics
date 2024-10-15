/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Manager__
#define __OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Manager__

#include <mutex>

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Directory.hpp>
#include <OpenSpaceToolkit/Core/Type/Index.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>

#include <OpenSpaceToolkit/IO/URL.hpp>

#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/CSSISpaceWeather.hpp>
#include <OpenSpaceToolkit/Physics/Manager.hpp>
#include <OpenSpaceToolkit/Physics/Time/Duration.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

#define OSTK_PHYSICS_ENVIRONMENT_ATMOSPHERIC_EARTH_MANAGER_LOCAL_REPOSITORY \
    "./.open-space-toolkit/physics/data/environment/atmospheric/earth"

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
using ostk::core::filesystem::Directory;
using ostk::core::type::Index;
using ostk::core::type::Real;

using ostk::io::URL;

using ostk::mathematics::object::Vector2d;

using ostk::physics::environment::atmospheric::earth::CSSISpaceWeather;
using ostk::physics::time::Duration;
using ostk::physics::time::Instant;
using BaseManager = ostk::physics::Manager;

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

class Manager : public BaseManager
{
   public:
    /// @brief                  Get CSSI Space Weather directory
    ///
    /// @return                 CSSI Space Weather directory

    Directory getCSSISpaceWeatherDirectory() const;

    /// @brief                  Get currently loaded CSSI Space Weather file
    ///
    /// @return                 Currently loaded CSSI Space Weather file

    CSSISpaceWeather getLoadedCSSISpaceWeather() const;

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

    virtual void reset() override;

    /// @brief                  Get manager singleton
    ///
    /// @return                 Reference to manager

    static Manager& Get();

   private:
    CSSISpaceWeather CSSISpaceWeather_;

    Manager();

    const CSSISpaceWeather* accessCSSISpaceWeatherAt_(const Instant& anInstant) const;

    File getLatestCSSISpaceWeatherFile_() const;

    virtual void setup_() override;

    void loadCSSISpaceWeather_(const CSSISpaceWeather& aCSSISpaceWeather);

    File fetchLatestCSSISpaceWeather_();
};

}  // namespace earth
}  // namespace atmospheric
}  // namespace environment
}  // namespace physics
}  // namespace ostk

#endif
