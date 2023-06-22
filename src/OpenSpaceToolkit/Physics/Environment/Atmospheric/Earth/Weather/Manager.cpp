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

#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/Weather/Manager.hpp>
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
namespace weather
{

using ostk::core::types::Uint8;
using ostk::core::types::Uint16;
using ostk::core::types::Integer;
using ostk::core::types::String;
using ostk::core::ctnr::Map;
using ostk::core::fs::Path;

using ostk::io::ip::tcp::http::Client;

using ostk::physics::time::Scale;
using ostk::physics::time::Date;
using ostk::physics::time::Time;
using ostk::physics::time::DateTime;
using ostk::physics::time::Instant;

const String CSSISpaceWeatherFileName = "SW-Last5Years.csv";

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
    using ostk::core::fs::Path;

    return Directory::Path(localRepository_.getPath() + Path::Parse("CSSISpaceWeather"));
}

URL Manager::getRemoteUrl() const
{
    const std::lock_guard<std::mutex> lock {mutex_};

    return remoteUrl_;
}

Array<CSSISpaceWeather> Manager::getCSSISpaceWeatherArray() const
{
    return CSSISpaceWeatherArray_;
}

CSSISpaceWeather Manager::getCSSISpaceWeatherAt(const Instant& anInstant) const
{
    if (!anInstant.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

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
    if (!anInstant.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

    const Date day = anInstant.getDateTime(Scale::UTC).getDate();
    const Instant dayInstant = Instant::DateTime(DateTime(day, Time::Midnight()), Scale::UTC);

    std::lock_guard<std::mutex> lock {mutex_};
    const CSSISpaceWeather* CSSISpaceWeatherPtr = this->accessCSSISpaceWeatherAt(dayInstant);

    if (CSSISpaceWeatherPtr != nullptr)
    {
        if (CSSISpaceWeatherPtr->accessObservationInterval().contains(dayInstant))
        {
            const CSSISpaceWeather::Observation observation = CSSISpaceWeatherPtr->accessObservationAt(dayInstant);

            return Array<Integer> {
                observation.Kp1,
                observation.Kp2,
                observation.Kp3,
                observation.Kp4,
                observation.Kp5,
                observation.Kp6,
                observation.Kp7,
                observation.Kp8,
            };
        }
        else if (CSSISpaceWeatherPtr->accessDailyPredictionInterval().contains(dayInstant))
        {
            const CSSISpaceWeather::Observation prediction = CSSISpaceWeatherPtr->accessDailyPredictionAt(dayInstant);

            return Array<Integer> {
                prediction.Kp1,
                prediction.Kp2,
                prediction.Kp3,
                prediction.Kp4,
                prediction.Kp5,
                prediction.Kp6,
                prediction.Kp7,
                prediction.Kp8,
            };
        }
    }

    throw ostk::core::error::RuntimeError("Cannot obtain Kp Solar Indices at [{}].", anInstant.toString());
}

Array<Integer> Manager::getAp3HourSolarIndicesAt(const Instant& anInstant) const
{
    if (!anInstant.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

    const Date day = anInstant.getDateTime(Scale::UTC).getDate();
    const Instant dayInstant = Instant::DateTime(DateTime(day, Time::Midnight()), Scale::UTC);

    std::lock_guard<std::mutex> lock {mutex_};
    const CSSISpaceWeather* CSSISpaceWeatherPtr = this->accessCSSISpaceWeatherAt(dayInstant);

    if (CSSISpaceWeatherPtr != nullptr)
    {
        if (CSSISpaceWeatherPtr->accessObservationInterval().contains(dayInstant))
        {
            const CSSISpaceWeather::Observation observation = CSSISpaceWeatherPtr->accessObservationAt(dayInstant);

            return Array<Integer> {
                observation.Ap1,
                observation.Ap2,
                observation.Ap3,
                observation.Ap4,
                observation.Ap5,
                observation.Ap6,
                observation.Ap7,
                observation.Ap8,
                observation.ApAvg,
            };
        }
        else if (CSSISpaceWeatherPtr->accessDailyPredictionInterval().contains(dayInstant))
        {
            const CSSISpaceWeather::Observation prediction = CSSISpaceWeatherPtr->accessDailyPredictionAt(dayInstant);

            return Array<Integer> {
                prediction.Ap1,
                prediction.Ap2,
                prediction.Ap3,
                prediction.Ap4,
                prediction.Ap5,
                prediction.Ap6,
                prediction.Ap7,
                prediction.Ap8,
                prediction.ApAvg,
            };
        }
    }

    throw ostk::core::error::RuntimeError("Cannot obtain Ap Solar Indices at [{}].", anInstant.toString());
}

Real Manager::getF107SolarFluxAt(const Instant& anInstant) const
{
    if (!anInstant.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

    const Date day = anInstant.getDateTime(Scale::UTC).getDate();
    const Instant dayInstant = Instant::DateTime(DateTime(day, Time::Midnight()), Scale::UTC);

    std::lock_guard<std::mutex> lock {mutex_};
    const CSSISpaceWeather* CSSISpaceWeatherPtr = this->accessCSSISpaceWeatherAt(dayInstant);

    if (CSSISpaceWeatherPtr != nullptr)
    {
        if (CSSISpaceWeatherPtr->accessObservationInterval().contains(dayInstant))
        {
            return CSSISpaceWeatherPtr->accessObservationAt(dayInstant).F107Obs;
        }
        else if (CSSISpaceWeatherPtr->accessDailyPredictionInterval().contains(dayInstant))
        {
            return CSSISpaceWeatherPtr->accessDailyPredictionAt(dayInstant).F107Obs;
        }
        else if (CSSISpaceWeatherPtr->accessMonthlyPredictionInterval().contains(dayInstant))
        {
            return CSSISpaceWeatherPtr->accessMonthlyPredictionAt(dayInstant).F107Obs;
        }
    }

    throw ostk::core::error::RuntimeError("Cannot obtain F10.7 Solar Flux at [{}].", anInstant.toString());
}

Real Manager::getF107SolarFlux81DayAvgAt(const Instant& anInstant) const
{
    if (!anInstant.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

    const Date day = anInstant.getDateTime(Scale::UTC).getDate();
    const Instant dayInstant = Instant::DateTime(DateTime(day, Time::Midnight()), Scale::UTC);

    std::lock_guard<std::mutex> lock {mutex_};
    const CSSISpaceWeather* CSSISpaceWeatherPtr = this->accessCSSISpaceWeatherAt(dayInstant);

    if (CSSISpaceWeatherPtr != nullptr)
    {
        if (CSSISpaceWeatherPtr->accessObservationInterval().contains(dayInstant))
        {
            return CSSISpaceWeatherPtr->accessObservationAt(dayInstant).F107ObsCenter81;
        }
        else if (CSSISpaceWeatherPtr->accessDailyPredictionInterval().contains(dayInstant))
        {
            return CSSISpaceWeatherPtr->accessDailyPredictionAt(dayInstant).F107ObsCenter81;
        }
        else if (CSSISpaceWeatherPtr->accessMonthlyPredictionInterval().contains(dayInstant))
        {
            return CSSISpaceWeatherPtr->accessMonthlyPredictionAt(dayInstant).F107ObsCenter81;
        }
    }

    throw ostk::core::error::RuntimeError(
        "Cannot obtain F10.7 Solar Flux 81 Day Avereage at [{}].", anInstant.toString()
    );
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

void Manager::setRemoteUrl(const URL& aRemoteUrl)
{
    if (!aRemoteUrl.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Remote URL");
    }

    const std::lock_guard<std::mutex> lock {mutex_};

    remoteUrl_ = aRemoteUrl;
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
    static const Manager::Mode defaultMode = OSTK_PHYSICS_ENVIRONMENT_ATMOSPHERIC_EARTH_WEATHER_MANAGER_MODE;

    if (const char* modeString = std::getenv("OSTK_PHYSICS_ENVIRONMENT_ATMOSPHERIC_EARTH_WEATHER_MANAGER_MODE"))
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
        Directory::Path(Path::Parse(OSTK_PHYSICS_ENVIRONMENT_ATMOSPHERIC_EARTH_WEATHER_MANAGER_LOCAL_REPOSITORY));

    if (const char* localRepositoryPath =
            std::getenv("OSTK_PHYSICS_ENVIRONMENT_ATMOSPHERIC_EARTH_WEATHER_MANAGER_LOCAL_REPOSITORY"))
    {
        return Directory::Path(Path::Parse(localRepositoryPath));
    }

    return defaultLocalRepository;
}

Duration Manager::DefaultLocalRepositoryLockTimeout()
{
    static const Duration defaultLocalRepositoryLockTimeout =
        Duration::Seconds(OSTK_PHYSICS_ENVIRONMENT_ATMOSPHERIC_EARTH_WEATHER_MANAGER_LOCAL_REPOSITORY_LOCK_TIMEOUT);

    if (const char* localRepositoryLockTimeoutString =
            std::getenv("OSTK_PHYSICS_ENVIRONMENT_ATMOSPHERIC_EARTH_WEATHER_MANAGER_LOCAL_REPOSITORY_LOCK_TIMEOUT"))
    {
        return Duration::Parse(localRepositoryLockTimeoutString);
    }

    return defaultLocalRepositoryLockTimeout;
}

URL Manager::DefaultRemoteUrl()
{
    static const URL defaultRemoteUrl =
        URL::Parse(OSTK_PHYSICS_ENVIRONMENT_ATMOSPHERIC_EARTH_WEATHER_MANAGER_REMOTE_URL);

    if (const char* remoteUrl = std::getenv("OSTK_PHYSICS_ENVIRONMENT_ATMOSPHERIC_EARTH_WEATHER_MANAGER_REMOTE_URL"))
    {
        return URL::Parse(remoteUrl);
    }

    return defaultRemoteUrl;
}

Manager::Manager(const Manager::Mode& aMode)
    : mode_(aMode),
      localRepository_(Manager::DefaultLocalRepository()),
      localRepositoryLockTimeout_(Manager::DefaultLocalRepositoryLockTimeout()),
      remoteUrl_(Manager::DefaultRemoteUrl()),
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
        const Instant currentInstant = Instant::Now();

        if ((!CSSISpaceWeatherUpdateTimestamp_.isDefined()) ||
            ((CSSISpaceWeatherUpdateTimestamp_ + Duration::Weeks(1.0)) < currentInstant))  // [TBM] Param
        {
            const File latestCSSISpaceWeatherFile = this->getLatestCSSISpaceWeatherFile();

            if (latestCSSISpaceWeatherFile.isDefined())
            {
                CSSISpaceWeatherUpdateTimestamp_ = currentInstant;

                const CSSISpaceWeather CSSISpaceWeather = CSSISpaceWeather::Load(latestCSSISpaceWeatherFile);

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

    {
        CSSISpaceWeatherIndex_ = 0;

        return nullptr;
    }
}

File Manager::getLocalRepositoryLockFile() const
{
    return File::Path(localRepository_.getPath() + Path::Parse(".lock"));
}

File Manager::getLatestCSSISpaceWeatherFile() const
{
    // Parse CSSI Space Weather Directories, e.g.,
    // `.open-space-toolkit/physics/environment/atmospheric/earth/weather/CSSI-Space-Weather/2022-05-19/`, and find the
    // latest one.

    Map<Instant, File> CSSISpaceWeatherMap = {};

    for (const auto& directory : this->getCSSISpaceWeatherDirectory().getDirectories())
    {
        if ((directory.getName() != temporaryDirectoryName) && directory.containsFileWithName(CSSISpaceWeatherFileName))
        {
            const Date date = Date::Parse(directory.getName());

            const Instant instant = Instant::DateTime({date, Time::Midnight()}, Scale::UTC);

            const File bulletinFile = File::Path(directory.getPath() + Path::Parse(CSSISpaceWeatherFileName));

            CSSISpaceWeatherMap.insert({instant, bulletinFile});
        }
    }

    if (!CSSISpaceWeatherMap.empty())
    {
        return CSSISpaceWeatherMap.rbegin()->second;
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

    Directory temporaryDirectory =
        Directory::Path(this->getCSSISpaceWeatherDirectory().getPath() + Path::Parse(temporaryDirectoryName));

    this->lockLocalRepository(localRepositoryLockTimeout_);

    const URL latestCSSISpaceWeatherUrl = remoteUrl_ + CSSISpaceWeatherFileName;
    std::cout << latestCSSISpaceWeatherUrl.toString() << std::endl;

    File latestCSSISpaceWeatherFile = File::Undefined();
    Directory destinationDirectory = Directory::Undefined();

    try
    {
        // Create temporary Directory,
        // e.g., `.open-space-toolkit/physics/enviroment/atmospheric/earth/weather/cssi-space-weather/tmp/`.

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

        latestCSSISpaceWeatherFile = Client::Fetch(latestCSSISpaceWeatherUrl, temporaryDirectory);

        if (!latestCSSISpaceWeatherFile.exists())
        {
            throw ostk::core::error::RuntimeError(
                "Cannot fetch CSSI Space Weather from [{}].", latestCSSISpaceWeatherUrl.toString()
            );
        }

        // Check that CSSI Space Weather File size is not zero

        std::uintmax_t latestCSSISpaceWeatherFileSize =
            std::experimental::filesystem::file_size(std::string(latestCSSISpaceWeatherFile.getPath().toString()));

        if (latestCSSISpaceWeatherFileSize == 0)
        {
            throw ostk::core::error::RuntimeError(
                "Cannot fetch CSSI Space Weather from [{}]: file is empty.", latestCSSISpaceWeatherUrl.toString()
            );
        }

        // Load CSSI Space Weather from File

        const CSSISpaceWeather latestCSSISpaceWeather = CSSISpaceWeather::Load(latestCSSISpaceWeatherFile);

        // Move CSSI Space Weather File into destination Directory,
        // e.g., `.open-space-toolkit/physics/enviroment/atmospheric/earth/weather/cssi-space-weather/2022-05-19/`.

        destinationDirectory = Directory::Path(
            this->getCSSISpaceWeatherDirectory().getPath() +
            Path::Parse(latestCSSISpaceWeather.accessLastObservationDate().toString())
        );

        if (destinationDirectory.exists())
        {
            destinationDirectory.remove();
        }

        destinationDirectory.create();

        latestCSSISpaceWeatherFile.moveToDirectory(destinationDirectory);

        temporaryDirectory.remove();

        this->unlockLocalRepository();

        std::cout << String::Format(
                         "CSSI Space Weather [{}] has been successfully fetched from [{}].",
                         latestCSSISpaceWeatherFile.toString(),
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

}  // namespace weather
}  // namespace earth
}  // namespace atmospheric
}  // namespace environment
}  // namespace physics
}  // namespace ostk
