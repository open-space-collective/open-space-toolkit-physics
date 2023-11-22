/// Apache License 2.0

#include <chrono>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <thread>

#include <OpenSpaceToolkit/Core/Containers/Map.hpp>
#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Path.hpp>
#include <OpenSpaceToolkit/Core/Types/Integer.hpp>
#include <OpenSpaceToolkit/Core/Types/String.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

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

using ostk::core::types::Uint8;
using ostk::core::types::Uint16;
using ostk::core::types::Integer;
using ostk::core::types::String;
using ostk::core::ctnr::Map;
using ostk::core::filesystem::Path;

using ostk::io::ip::tcp::http::Client;

using ostk::physics::time::Scale;
using ostk::physics::time::Date;
using ostk::physics::time::Time;
using ostk::physics::time::DateTime;
using ostk::physics::time::Instant;

using ManifestManager = ostk::physics::data::Manager;

const String CSSICSSISpaceWeatherFileName = "SW-Last5Years.csv";
const String CSSISpaceWeatherManifestName = "space-weather-CSSI";

// [TBI]: this path can be obtained from the manifest
const String CSSISpaceWeatherRemotePath = "environment/atmospheric/earth/CSSISpaceWeather/";

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

Array<CSSISpaceWeather> Manager::getCSSISpaceWeatherArray() const
{
    return CSSISpaceWeatherArray_;
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

    if (!localRepository_.exists())
    {
        localRepository_.create();
    }
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

    CSSISpaceWeatherIndex_ = 0;

    CSSISpaceWeatherUpdateTimestamp_ = Instant::Undefined();

    CSSISpaceWeatherArray_.clear();

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
      CSSISpaceWeatherArray_(Array<CSSISpaceWeather>::Empty()),
      CSSISpaceWeatherIndex_(0),
      CSSISpaceWeatherUpdateTimestamp_(Instant::Undefined())
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

    // Try cache
    if (!CSSISpaceWeatherArray_.isEmpty())
    {
        const CSSISpaceWeather& CSSISpaceWeather = CSSISpaceWeatherArray_.at(CSSISpaceWeatherIndex_);

        if (CSSISpaceWeather.accessObservationInterval().contains(anInstant) ||
            CSSISpaceWeather.accessDailyPredictionInterval().contains(anInstant) ||
            CSSISpaceWeather.accessMonthlyPredictionInterval().contains(anInstant))
        {
            return &CSSISpaceWeather;
        }
    }

    // Try observation span of loaded space weather files

    {
        CSSISpaceWeatherIndex_ = 0;

        for (const auto& CSSISpaceWeather : CSSISpaceWeatherArray_)
        {
            if (CSSISpaceWeather.accessObservationInterval().contains(anInstant))
            {
                return &CSSISpaceWeather;
            }

            CSSISpaceWeatherIndex_++;
        }
    }

    // Try fetching latest Space Weather file

    if (mode_ == Manager::Mode::Automatic)
    {
        ManifestManager& manifestManager = ManifestManager::Get();

        const Instant CSSIManifestUpdateTimestamp =
            manifestManager.getLastUpdateTimestampFor(CSSISpaceWeatherManifestName);

        if ((!CSSISpaceWeatherUpdateTimestamp_.isDefined()) ||
            (CSSISpaceWeatherUpdateTimestamp_ < CSSIManifestUpdateTimestamp))
        {
            const File latestCSSICSSISpaceWeatherFile = this->getLatestCSSICSSISpaceWeatherFile();

            if (latestCSSICSSISpaceWeatherFile.isDefined())
            {
                CSSISpaceWeatherUpdateTimestamp_ = Instant::Now();

                const CSSISpaceWeather CSSISpaceWeather = CSSISpaceWeather::Load(latestCSSICSSISpaceWeatherFile);

                if (CSSISpaceWeather.accessObservationInterval().contains(anInstant))
                {
                    const_cast<Manager*>(this)->loadCSSISpaceWeather_(CSSISpaceWeather);

                    CSSISpaceWeatherIndex_ = CSSISpaceWeatherArray_.getSize() - 1;

                    return &CSSISpaceWeatherArray_.accessLast();
                }
            }
        }
    }

    // Try daily prediction span of loaded space weather files

    {
        CSSISpaceWeatherIndex_ = 0;

        for (const auto& CSSISpaceWeather : CSSISpaceWeatherArray_)
        {
            if (CSSISpaceWeather.accessDailyPredictionInterval().contains(anInstant))
            {
                return &CSSISpaceWeather;
            }

            CSSISpaceWeatherIndex_++;
        }
    }

    // Try monthly prediction span of loaded space weather files

    {
        CSSISpaceWeatherIndex_ = 0;

        for (const auto& CSSISpaceWeather : CSSISpaceWeatherArray_)
        {
            if (CSSISpaceWeather.accessMonthlyPredictionInterval().contains(anInstant))
            {
                return &CSSISpaceWeather;
            }

            CSSISpaceWeatherIndex_++;
        }
    }

    // No space weather data found
    CSSISpaceWeatherIndex_ = 0;
    throw ostk::core::error::RuntimeError("Cannot obtain CSSI Space Weather at [{}].", anInstant.toString());
}

File Manager::getLocalRepositoryLockFile() const
{
    return File::Path(localRepository_.getPath() + Path::Parse(".lock"));
}

File Manager::getLatestCSSICSSISpaceWeatherFile() const
{
    // Parse CSSI Space Weather Directories, e.g.,
    // `.open-space-toolkit/physics/environment/atmospheric/earth/CSSI-Space-Weather/2022-05-19/`, and find the
    // latest one.

    if (this->getCSSISpaceWeatherDirectory().containsFileWithName(CSSICSSISpaceWeatherFileName))
    {
        return File::Path(this->getCSSISpaceWeatherDirectory().getPath() + Path::Parse(CSSICSSISpaceWeatherFileName));
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
    for (const auto& CSSISpaceWeather : CSSISpaceWeatherArray_)
    {
        if (CSSISpaceWeather.accessLastObservationDate() == aCSSISpaceWeather.accessLastObservationDate())
        {
            throw ostk::core::error::RuntimeError("CSSI Space Weather already added.");
        }
    }

    CSSISpaceWeatherArray_.add(aCSSISpaceWeather);  // [TBI] Add in ascending time order

    CSSISpaceWeatherIndex_ = 0;
}

File Manager::fetchLatestCSSISpaceWeather_()
{
    std::cout << "Fetching latest CSSI Space Weather..." << std::endl;

    ManifestManager& manifestManager = ManifestManager::Get();

    Directory temporaryDirectory =
        Directory::Path(this->getCSSISpaceWeatherDirectory().getPath() + Path::Parse(temporaryDirectoryName));

    this->lockLocalRepository(localRepositoryLockTimeout_);

    const URL latestCSSISpaceWeatherUrl =
        manifestManager.getRemoteUrl() + CSSISpaceWeatherRemotePath + CSSICSSISpaceWeatherFileName;

    File latestCSSICSSISpaceWeatherFile = File::Undefined();
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

        std::cout << String::Format("Fetching CSSI Space Weather from [{}]...", latestCSSISpaceWeatherUrl.toString())
                  << std::endl;

        latestCSSICSSISpaceWeatherFile = Client::Fetch(latestCSSISpaceWeatherUrl, temporaryDirectory, 2);

        if (!latestCSSICSSISpaceWeatherFile.exists())
        {
            throw ostk::core::error::RuntimeError(
                "Cannot fetch CSSI Space Weather from [{}].", latestCSSISpaceWeatherUrl.toString()
            );
        }

        // Check that CSSI Space Weather File size is not zero

        std::uintmax_t latestCSSICSSISpaceWeatherFileSize =
            std::experimental::filesystem::file_size(std::string(latestCSSICSSISpaceWeatherFile.getPath().toString()));

        if (latestCSSICSSISpaceWeatherFileSize == 0)
        {
            throw ostk::core::error::RuntimeError(
                "Cannot fetch CSSI Space Weather from [{}]: file is empty.", latestCSSISpaceWeatherUrl.toString()
            );
        }

        // Load CSSI Space Weather from File

        const CSSISpaceWeather latestCSSISpaceWeather = CSSISpaceWeather::Load(latestCSSICSSISpaceWeatherFile);

        // Move CSSI Space Weather File into destination Directory,
        // e.g., `.open-space-toolkit/physics/enviroment/atmospheric/earth/cssi-space-weather/`.

        destinationDirectory = Directory::Path(this->getCSSISpaceWeatherDirectory().getPath());

        latestCSSICSSISpaceWeatherFile.moveToDirectory(destinationDirectory);

        temporaryDirectory.remove();

        this->unlockLocalRepository();

        std::cout << String::Format(
                         "CSSI Space Weather [{}] has been successfully fetched from [{}].",
                         latestCSSICSSISpaceWeatherFile.toString(),
                         latestCSSISpaceWeatherUrl.toString()
                     )
                  << std::endl;
    }
    catch (const ostk::core::error::Exception& anException)
    {
        std::cerr << String::Format(
                         "Error caught while fetching latest CSSI Space Weather from [{}]: [{}].",
                         latestCSSISpaceWeatherUrl.toString(),
                         anException.what()
                     )
                  << std::endl;

        if (latestCSSICSSISpaceWeatherFile.isDefined() && latestCSSICSSISpaceWeatherFile.exists())
        {
            latestCSSICSSISpaceWeatherFile.remove();
            latestCSSICSSISpaceWeatherFile = File::Undefined();
        }

        if (temporaryDirectory.isDefined() && temporaryDirectory.exists())
        {
            temporaryDirectory.remove();
        }

        this->unlockLocalRepository();

        throw;
    }

    return latestCSSICSSISpaceWeatherFile;
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
