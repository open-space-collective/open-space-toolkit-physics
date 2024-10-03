/// Apache License 2.0

#include <chrono>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <thread>

#include <OpenSpaceToolkit/Core/Container/Map.hpp>
#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Path.hpp>
#include <OpenSpaceToolkit/Core/Type/Integer.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/IO/IP/TCP/HTTP/Client.hpp>

#include <OpenSpaceToolkit/Physics/Data/Manager.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/Manager.hpp>
#include <OpenSpaceToolkit/Physics/Time/Date.hpp>
#include <OpenSpaceToolkit/Physics/Time/DateTime.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Time/Scale.hpp>
#include <OpenSpaceToolkit/Physics/Time/Time.hpp>

#include <experimental/filesystem>

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

using ostk::core::container::Map;
using ostk::core::filesystem::Path;
using ostk::core::type::Integer;
using ostk::core::type::String;
using ostk::core::type::Uint16;
using ostk::core::type::Uint8;

using ostk::io::ip::tcp::http::Client;

using ostk::physics::time::Date;
using ostk::physics::time::DateTime;
using ostk::physics::time::Instant;
using ostk::physics::time::Scale;
using ostk::physics::time::Time;

using ManifestManager = ostk::physics::data::Manager;

const String CSSISpaceWeatherFileName = "SW-Last5Years.csv";
const String CSSISpaceWeatherManifestName = "space-weather-CSSI";

const String temporaryDirectoryName = "tmp";

Manager::Mode Manager::getMode() const
{
    std::lock_guard<std::mutex> lock {mutex_};

    return mode_;
}

Directory Manager::getLocalRepository() const
{
    std::lock_guard<std::mutex> lock {mutex_};

    return localRepository_;
}

Directory Manager::getCSSISpaceWeatherDirectory() const
{
    return Directory::Path(localRepository_.getPath() + Path::Parse("CSSISpaceWeather"));
}

CSSISpaceWeather Manager::getLoadedCSSISpaceWeather() const
{
    std::lock_guard<std::mutex> lock {mutex_};

    return CSSISpaceWeather_;
}

CSSISpaceWeather Manager::getCSSISpaceWeatherAt(const Instant& anInstant) const
{
    std::lock_guard<std::mutex> lock {mutex_};

    const CSSISpaceWeather* CSSISpaceWeatherPtr = this->accessCSSISpaceWeatherAt(anInstant);

    if (CSSISpaceWeatherPtr != nullptr)
    {
        return *CSSISpaceWeatherPtr;
    }

    throw ostk::core::error::RuntimeError("Cannot obtain CSSI Space Weather File at [{}].", anInstant.toString());
}

Array<Integer> Manager::getKp3HourSolarIndicesAt(const Instant& anInstant) const
{
    std::lock_guard<std::mutex> lock {mutex_};
    const CSSISpaceWeather* CSSISpaceWeatherPtr = this->accessCSSISpaceWeatherAt(anInstant);

    static auto getKpArray = [](const CSSISpaceWeather::Reading& aReading) -> Array<Integer>
    {
        return Array<Integer> {
            aReading.Kp1,
            aReading.Kp2,
            aReading.Kp3,
            aReading.Kp4,
            aReading.Kp5,
            aReading.Kp6,
            aReading.Kp7,
            aReading.Kp8,
        };
    };

    static auto outputIsDefined = [](const CSSISpaceWeather::Reading& reading) -> bool
    {
        const Array<Integer>& array = getKpArray(reading);
        return std::all_of(
            array.begin(),
            array.end(),
            [](const Integer& val)
            {
                return val.isDefined();
            }
        );
    };

    const CSSISpaceWeather::Reading& reading = CSSISpaceWeatherPtr->accessReadingAt(anInstant);

    if (outputIsDefined(reading))
    {
        return getKpArray(reading);
    }
    else
    {
        return getKpArray(CSSISpaceWeatherPtr->accessLastReadingWhere(outputIsDefined, anInstant));
    }
}

Array<Integer> Manager::getAp3HourSolarIndicesAt(const Instant& anInstant) const
{
    std::lock_guard<std::mutex> lock {mutex_};
    const CSSISpaceWeather* CSSISpaceWeatherPtr = this->accessCSSISpaceWeatherAt(anInstant);

    static auto getApArray = [](const CSSISpaceWeather::Reading& aReading) -> Array<Integer>
    {
        return Array<Integer> {
            aReading.Ap1,
            aReading.Ap2,
            aReading.Ap3,
            aReading.Ap4,
            aReading.Ap5,
            aReading.Ap6,
            aReading.Ap7,
            aReading.Ap8,
        };
    };

    static auto outputIsDefined = [](const CSSISpaceWeather::Reading& aReading) -> bool
    {
        const Array<Integer>& array = getApArray(aReading);
        return std::all_of(
            array.begin(),
            array.end(),
            [](const Integer& val)
            {
                return val.isDefined();
            }
        );
    };

    const CSSISpaceWeather::Reading& reading = CSSISpaceWeatherPtr->accessReadingAt(anInstant);

    if (outputIsDefined(reading))
    {
        return getApArray(reading);
    }
    else
    {
        return getApArray(CSSISpaceWeatherPtr->accessLastReadingWhere(outputIsDefined, anInstant));
    }
}

Integer Manager::getApDailyIndexAt(const Instant& anInstant) const
{
    std::lock_guard<std::mutex> lock {mutex_};
    const CSSISpaceWeather* CSSISpaceWeatherPtr = this->accessCSSISpaceWeatherAt(anInstant);

    static auto getApDaily = [](const CSSISpaceWeather::Reading& aReading) -> Integer
    {
        return aReading.ApAvg;
    };

    static auto outputIsDefined = [](const CSSISpaceWeather::Reading& aReading) -> bool
    {
        return aReading.ApAvg.isDefined();
    };

    const CSSISpaceWeather::Reading& reading = CSSISpaceWeatherPtr->accessReadingAt(anInstant);

    if (outputIsDefined(reading))
    {
        return getApDaily(reading);
    }
    else
    {
        return getApDaily(CSSISpaceWeatherPtr->accessLastReadingWhere(outputIsDefined, anInstant));
    }
}

Real Manager::getF107SolarFluxAt(const Instant& anInstant) const
{
    std::lock_guard<std::mutex> lock {mutex_};
    const CSSISpaceWeather* CSSISpaceWeatherPtr = this->accessCSSISpaceWeatherAt(anInstant);

    static auto getF107Obs = [](const CSSISpaceWeather::Reading& aReading) -> Real
    {
        return aReading.F107Obs;
    };

    static auto outputIsDefined = [](const CSSISpaceWeather::Reading& aReading) -> bool
    {
        return aReading.F107Obs.isDefined();
    };

    const CSSISpaceWeather::Reading& reading = CSSISpaceWeatherPtr->accessReadingAt(anInstant);

    if (outputIsDefined(reading))
    {
        return getF107Obs(reading);
    }
    else
    {
        return getF107Obs(CSSISpaceWeatherPtr->accessLastReadingWhere(outputIsDefined, anInstant));
    }
}

Real Manager::getF107SolarFlux81DayAvgAt(const Instant& anInstant) const
{
    std::lock_guard<std::mutex> lock {mutex_};
    const CSSISpaceWeather* CSSISpaceWeatherPtr = this->accessCSSISpaceWeatherAt(anInstant);

    static auto getF107ObsCenter81 = [](const CSSISpaceWeather::Reading& aReading) -> Real
    {
        return aReading.F107ObsCenter81;
    };

    static auto outputIsDefined = [](const CSSISpaceWeather::Reading& aReading) -> bool
    {
        return aReading.F107ObsCenter81.isDefined();
    };

    const CSSISpaceWeather::Reading& reading = CSSISpaceWeatherPtr->accessReadingAt(anInstant);

    if (outputIsDefined(reading))
    {
        return getF107ObsCenter81(reading);
    }
    else
    {
        return getF107ObsCenter81(CSSISpaceWeatherPtr->accessLastReadingWhere(outputIsDefined, anInstant));
    }
}

void Manager::setMode(const Manager::Mode& aMode)
{
    std::lock_guard<std::mutex> lock {mutex_};

    mode_ = aMode;
}

void Manager::setLocalRepository(const Directory& aDirectory)
{
    if (!aDirectory.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Directory");
    }

    const std::lock_guard<std::mutex> lock {mutex_};

    localRepository_ = aDirectory;

    this->setup();
}

void Manager::loadCSSISpaceWeather(const CSSISpaceWeather& aCSSISpaceWeather)
{
    if (!aCSSISpaceWeather.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("CSSI Space Weather");
    }

    std::lock_guard<std::mutex> lock {mutex_};

    this->loadCSSISpaceWeather_(aCSSISpaceWeather);
}

File Manager::fetchLatestCSSISpaceWeather()
{
    std::lock_guard<std::mutex> lock {mutex_};

    return this->fetchLatestCSSISpaceWeather_();
}

void Manager::reset()
{
    std::lock_guard<std::mutex> lock {mutex_};

    CSSISpaceWeather_ = CSSISpaceWeather::Undefined();

    localRepository_ = DefaultLocalRepository();
    localRepositoryLockTimeout_ = DefaultLocalRepositoryLockTimeout();
    mode_ = DefaultMode();
}

void Manager::clearLocalRepository()
{
    localRepository_.remove();

    this->setup();
}

Manager& Manager::Get()
{
    static Manager manager;

    return manager;
}

Manager::Mode Manager::DefaultMode()
{
    static const Manager::Mode defaultMode = OSTK_PHYSICS_ENVIRONMENT_ATMOSPHERIC_EARTH_MANAGER_MODE;

    if (const char* modeString = std::getenv("OSTK_PHYSICS_ENVIRONMENT_ATMOSPHERIC_EARTH_MANAGER_MODE"))
    {
        if (strcmp(modeString, "Manual") == 0)
        {
            return Manager::Mode::Manual;
        }
        else if (strcmp(modeString, "Automatic") == 0)
        {
            return Manager::Mode::Automatic;
        }
        else
        {
            throw ostk::core::error::runtime::Wrong("Mode", modeString);
        }
    }

    return defaultMode;
}

Directory Manager::DefaultLocalRepository()
{
    static const Directory defaultLocalRepository =
        Directory::Path(Path::Parse(OSTK_PHYSICS_ENVIRONMENT_ATMOSPHERIC_EARTH_MANAGER_LOCAL_REPOSITORY));

    if (const char* localRepositoryPath =
            std::getenv("OSTK_PHYSICS_ENVIRONMENT_ATMOSPHERIC_EARTH_MANAGER_LOCAL_REPOSITORY"))
    {
        return Directory::Path(Path::Parse(localRepositoryPath));
    }
    else if (const char* dataPath = std::getenv("OSTK_PHYSICS_DATA_LOCAL_REPOSITORY"))
    {
        return Directory::Path(Path::Parse(dataPath) + Path::Parse("environment/atmospheric/earth"));
    }

    return defaultLocalRepository;
}

Duration Manager::DefaultLocalRepositoryLockTimeout()
{
    static const Duration defaultLocalRepositoryLockTimeout =
        Duration::Seconds(OSTK_PHYSICS_ENVIRONMENT_ATMOSPHERIC_EARTH_MANAGER_LOCAL_REPOSITORY_LOCK_TIMEOUT);

    if (const char* localRepositoryLockTimeoutString =
            std::getenv("OSTK_PHYSICS_ENVIRONMENT_ATMOSPHERIC_EARTH_MANAGER_LOCAL_REPOSITORY_LOCK_TIMEOUT"))
    {
        return Duration::Parse(localRepositoryLockTimeoutString);
    }

    return defaultLocalRepositoryLockTimeout;
}

Manager::Manager(const Manager::Mode& aMode)
    : mode_(aMode),
      localRepository_(Manager::DefaultLocalRepository()),
      localRepositoryLockTimeout_(Manager::DefaultLocalRepositoryLockTimeout()),
      CSSISpaceWeather_(CSSISpaceWeather::Undefined())
{
    this->setup();
}

bool Manager::isLocalRepositoryLocked() const
{
    return this->getLocalRepositoryLockFile().exists();
}

const CSSISpaceWeather* Manager::accessCSSISpaceWeatherAt(const Instant& anInstant) const
{
    if (!anInstant.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

    // Try currently loaded
    if (CSSISpaceWeather_.isDefined())
    {
        if (CSSISpaceWeather_.accessObservationInterval().contains(anInstant) ||
            CSSISpaceWeather_.accessDailyPredictionInterval().contains(anInstant) ||
            CSSISpaceWeather_.accessMonthlyPredictionInterval().contains(anInstant))
        {
            return &CSSISpaceWeather_;
        }

        throw ostk::core::error::RuntimeError(
            "Loaded CSSI Space Weather file is not valid for [{}].", anInstant.toString()
        );
    }

    // Try loading or fetching latest Space Weather file
    if (mode_ == Manager::Mode::Automatic)
    {
        const File latestCSSISpaceWeatherFile = this->getLatestCSSISpaceWeatherFile();

        if (latestCSSISpaceWeatherFile.isDefined())
        {
            const CSSISpaceWeather CSSISpaceWeather = CSSISpaceWeather::Load(latestCSSISpaceWeatherFile);
            const_cast<Manager*>(this)->loadCSSISpaceWeather_(CSSISpaceWeather);

            return &CSSISpaceWeather_;
        }

        throw ostk::core::error::RuntimeError(
            "Failed to load or fetch latest CSSI Space Weather file at {}.",
            latestCSSISpaceWeatherFile.getPath().toString()
        );
    }

    if (mode_ == Manager::Mode::Manual)
    {
        if (!this->getCSSISpaceWeatherDirectory().containsFileWithName(CSSISpaceWeatherFileName))
        {
            throw ostk::core::error::RuntimeError("No CSSI Space Weather data loaded and manager set to Manual mode.");
        }

        const File localCSSISpaceWeatherFile =
            File::Path(this->getCSSISpaceWeatherDirectory().getPath() + Path::Parse(CSSISpaceWeatherFileName));

        if (!localCSSISpaceWeatherFile.isDefined())
        {
            throw ostk::core::error::RuntimeError(
                "Failed to load latest CSSI Space Weather file at {}.", localCSSISpaceWeatherFile.getPath().toString()
            );
        }

        const CSSISpaceWeather CSSISpaceWeather = CSSISpaceWeather::Load(localCSSISpaceWeatherFile);
        const_cast<Manager*>(this)->loadCSSISpaceWeather_(CSSISpaceWeather);

        return &CSSISpaceWeather_;
    }

    throw ostk::core::error::RuntimeError("No CSSI Space Weather data loaded and manager set to Manual mode.");
}

File Manager::getLocalRepositoryLockFile() const
{
    return File::Path(localRepository_.getPath() + Path::Parse(".lock"));
}

File Manager::getLatestCSSISpaceWeatherFile() const
{
    // Parse CSSI Space Weather Directories, e.g.,
    // `.open-space-toolkit/physics/environment/atmospheric/earth/CSSI-Space-Weather/2022-05-19/`, and find the
    // latest one.

    if (this->getCSSISpaceWeatherDirectory().containsFileWithName(CSSISpaceWeatherFileName))
    {
        return File::Path(this->getCSSISpaceWeatherDirectory().getPath() + Path::Parse(CSSISpaceWeatherFileName));
    }

    return const_cast<Manager*>(this)->fetchLatestCSSISpaceWeather_();
}

void Manager::setup()
{
    if (!localRepository_.exists())
    {
        localRepository_.create();
    }

    if (!this->getCSSISpaceWeatherDirectory().exists())
    {
        this->getCSSISpaceWeatherDirectory().create();
    }
}

void Manager::loadCSSISpaceWeather_(const CSSISpaceWeather& aCSSISpaceWeather)
{
    if (CSSISpaceWeather_.isDefined() &&
        (CSSISpaceWeather_.accessLastObservationDate() == aCSSISpaceWeather.accessLastObservationDate()))
    {
        throw ostk::core::error::RuntimeError("Identical CSSI Space Weather already loaded.");
    }

    CSSISpaceWeather_ = aCSSISpaceWeather;
}

File Manager::fetchLatestCSSISpaceWeather_()
{
    std::cout << "Fetching latest CSSI Space Weather..." << std::endl;

    ManifestManager& manifestManager = ManifestManager::Get();

    Directory temporaryDirectory =
        Directory::Path(this->getCSSISpaceWeatherDirectory().getPath() + Path::Parse(temporaryDirectoryName));

    this->lockLocalRepository(localRepositoryLockTimeout_);

    const Array<URL> CSSISpaceWeatherUrls = manifestManager.getRemoteDataUrls(CSSISpaceWeatherManifestName);

    // Only one remote file for CSSI Space Weather
    const URL CSSISpaceWeatherUrl = CSSISpaceWeatherUrls.accessFirst();

    File latestCSSISpaceWeatherFile = File::Undefined();
    Directory destinationDirectory = Directory::Undefined();

    try
    {
        // Create temporary Directory,
        // e.g., `.open-space-toolkit/physics/enviroment/atmospheric/earth/cssi-space-weather/tmp/`.

        if (temporaryDirectory.exists())
        {
            throw ostk::core::error::RuntimeError(
                "Temporary directory [{}] already exists.", temporaryDirectory.toString()
            );
        }

        std::cout << String::Format("Creating temporary directory [{}]...", temporaryDirectory.toString()) << std::endl;

        temporaryDirectory.create();

        // Download latest CSSI Space Weather File into temporary Directory

        std::cout << String::Format("Fetching CSSI Space Weather from [{}]...", CSSISpaceWeatherUrl.toString())
                  << std::endl;

        latestCSSISpaceWeatherFile = Client::Fetch(CSSISpaceWeatherUrl, temporaryDirectory, 2);

        if (!latestCSSISpaceWeatherFile.exists())
        {
            throw ostk::core::error::RuntimeError(
                "Cannot fetch CSSI Space Weather from [{}].", CSSISpaceWeatherUrl.toString()
            );
        }

        // Check that CSSI Space Weather File size is not zero

        std::uintmax_t latestCSSISpaceWeatherFileSize =
            std::experimental::filesystem::file_size(std::string(latestCSSISpaceWeatherFile.getPath().toString()));

        if (latestCSSISpaceWeatherFileSize == 0)
        {
            throw ostk::core::error::RuntimeError(
                "Cannot fetch CSSI Space Weather from [{}]: file is empty.", CSSISpaceWeatherUrl.toString()
            );
        }

        // Move CSSI Space Weather File into destination Directory,
        // e.g., `.open-space-toolkit/physics/enviroment/atmospheric/earth/cssi-space-weather/`.

        destinationDirectory = Directory::Path(this->getCSSISpaceWeatherDirectory().getPath());

        latestCSSISpaceWeatherFile.moveToDirectory(destinationDirectory);

        temporaryDirectory.remove();

        this->unlockLocalRepository();

        std::cout << String::Format(
                         "CSSI Space Weather [{}] has been successfully fetched from [{}].",
                         latestCSSISpaceWeatherFile.toString(),
                         CSSISpaceWeatherUrl.toString()
                     )
                  << std::endl;
    }
    catch (const ostk::core::error::Exception& anException)
    {
        std::cerr << String::Format(
                         "Error caught while fetching latest CSSI Space Weather from [{}]: [{}].",
                         CSSISpaceWeatherUrl.toString(),
                         anException.what()
                     )
                  << std::endl;

        if (latestCSSISpaceWeatherFile.isDefined() && latestCSSISpaceWeatherFile.exists())
        {
            latestCSSISpaceWeatherFile.remove();
            latestCSSISpaceWeatherFile = File::Undefined();
        }

        if (temporaryDirectory.isDefined() && temporaryDirectory.exists())
        {
            temporaryDirectory.remove();
        }

        this->unlockLocalRepository();

        throw;
    }

    return latestCSSISpaceWeatherFile;
}

void Manager::lockLocalRepository(const Duration& aTimeout)
{
    std::cout << String::Format("Locking local repository [{}]...", localRepository_.toString()) << std::endl;

    const auto tryLock = [](File& aLockFile) -> bool
    {
        if (!aLockFile.exists())  // [TBM] Should use system-wide semaphore instead (race condition can still occur)
        {
            try
            {
                aLockFile.create();

                return true;
            }
            catch (...)
            {
                // Do nothing
            }

            return false;
        }

        return false;
    };

    const Instant timeoutInstant = Instant::Now() + aTimeout;

    File lockFile = this->getLocalRepositoryLockFile();

    while (!tryLock(lockFile))
    {
        if (Instant::Now() >= timeoutInstant)
        {
            throw ostk::core::error::RuntimeError("Cannot lock local repository: timeout reached.");
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void Manager::unlockLocalRepository()
{
    std::cout << String::Format("Unlocking local repository [{}]...", localRepository_.toString()) << std::endl;

    if (!this->isLocalRepositoryLocked())
    {
        throw ostk::core::error::RuntimeError("Cannot unlock local repository: lock file does not exist.");
    }

    this->getLocalRepositoryLockFile().remove();
}

}  // namespace earth
}  // namespace atmospheric
}  // namespace environment
}  // namespace physics
}  // namespace ostk
