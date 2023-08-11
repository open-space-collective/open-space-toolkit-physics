/// Apache License 2.0

#include <algorithm>
#include <chrono>
#include <cstring>
#include <thread>

#include <OpenSpaceToolkit/Core/Containers/Array.hpp>
#include <OpenSpaceToolkit/Core/Containers/Dictionary.hpp>
#include <OpenSpaceToolkit/Core/Containers/Object.hpp>
#include <OpenSpaceToolkit/Core/Containers/Pair.hpp>
#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Types/Index.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

#include <OpenSpaceToolkit/IO/IP/TCP/HTTP/Client.hpp>

#include <OpenSpaceToolkit/Physics/Data/Manager.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Earth/Manager.hpp>

namespace ostk
{
namespace physics
{
namespace environment
{
namespace gravitational
{
namespace earth
{

using ManifestManager = ostk::physics::data::Manager;

Manager::Mode Manager::getMode() const
{
    std::lock_guard<std::mutex> lock {mutex_};

    return mode_;
}

bool Manager::hasDataFilesForType(const EarthGravitationalModel::Type& aModelType) const
{
    const std::lock_guard<std::mutex> lock {mutex_};

    const String dataFileName = Manager::DataFileNameFromType(aModelType);

    return (
        localRepository_.containsFileWithName(String::Format("{}.egm", dataFileName)) &&
        localRepository_.containsFileWithName(String::Format("{}.egm.cof", dataFileName))
    );
}

Array<File> Manager::localDataFilesForType(const EarthGravitationalModel::Type& aModelType) const
{
    const std::lock_guard<std::mutex> lock {mutex_};

    const String dataFileName = Manager::DataFileNameFromType(aModelType);

    return {
        File::Path(localRepository_.getPath() + Path::Parse(String::Format("{}.egm", dataFileName))),
        File::Path(localRepository_.getPath() + Path::Parse(String::Format("{}.egm.cof", dataFileName)))
    };
}

Directory Manager::getLocalRepository() const
{
    const std::lock_guard<std::mutex> lock {mutex_};

    return localRepository_;
}

void Manager::setLocalRepository(const Directory& aDirectory)
{
    if (!aDirectory.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Directory");
    }

    const std::lock_guard<std::mutex> lock {mutex_};

    localRepository_ = aDirectory;
}

Directory Manager::DefaultLocalRepository()
{
    static const Directory defaultLocalRepository =
        Directory::Path(Path::Parse(OSTK_PHYSICS_ENVIRONMENT_GRAVITATIONAL_EARTH_MANAGER_LOCAL_REPOSITORY));

    if (const char* localRepositoryPath =
            std::getenv("OSTK_PHYSICS_ENVIRONMENT_GRAVITATIONAL_EARTH_MANAGER_LOCAL_REPOSITORY"))
    {
        return Directory::Path(Path::Parse(localRepositoryPath));
    }

    return defaultLocalRepository;
}

void Manager::reset()
{
    std::lock_guard<std::mutex> lock {mutex_};

    localRepository_ = DefaultLocalRepository();
    localRepositoryLockTimeout_ = DefaultLocalRepositoryLockTimeout();
    mode_ = DefaultMode();
}

void Manager::fetchDataFilesForType(const EarthGravitationalModel::Type& aModelType) const
{
    using ostk::core::types::Index;
    using ostk::core::types::Size;

    using ostk::io::ip::tcp::http::Client;

    if (this->hasDataFilesForType(aModelType))
    {
        throw ostk::core::error::RuntimeError(
            "Cannot fetch data file for type [{}]: files already exist.", DataFileNameFromType(aModelType)
        );
    }

    const_cast<Manager*>(this)->lockLocalRepository(localRepositoryLockTimeout_);

    // Handle partial data since there are usually 2 files
    for (File& dataFile : this->localDataFilesForType(aModelType))
    {
        if (dataFile.exists())
        {
            std::cout << String::Format("Removing existing partial data file [{}]...", dataFile.toString())
                      << std::endl;
            dataFile.remove();
        }
    }

    const Array<URL> remoteUrls = this->getDataFileUrlsForType(aModelType);

    URL remoteDataUrl = URL::Undefined();
    File gravityDataFile = File::Undefined();

    try
    {
        for (const auto url : remoteUrls)
        {
            remoteDataUrl = url;

            std::cout << String::Format("Fetching gravitational data file from [{}]...", remoteDataUrl.toString())
                      << std::endl;

            gravityDataFile = Client::Fetch(remoteDataUrl, localRepository_, 2);

            if (!gravityDataFile.exists())
            {
                throw ostk::core::error::RuntimeError(
                    "Cannot fetch Gravity Data File from [{}].", remoteDataUrl.toString()
                );
            }

            // Check that Gravity Data File size is not zero

            std::uintmax_t gravityDataFileSize =
                std::experimental::filesystem::file_size(std::string(gravityDataFile.getPath().toString()));

            if (gravityDataFileSize == 0)
            {
                throw ostk::core::error::RuntimeError(
                    "Cannot fetch Gravity Data from [{}]: file is empty.", remoteDataUrl.toString()
                );
            }

            std::cout << String::Format(
                             "Gravity Data [{}] has been successfully fetched from [{}].",
                             gravityDataFile.toString(),
                             remoteDataUrl.toString()
                         )
                      << std::endl;
        }

        const_cast<Manager*>(this)->unlockLocalRepository();
    }
    catch (const ostk::core::error::Exception& anException)
    {
        std::cerr << String::Format(
                         "Error caught while fetching Gravity Data from [{}]: [{}].",
                         remoteDataUrl.toString(),
                         anException.what()
                     )
                  << std::endl;

        if (gravityDataFile.isDefined() && gravityDataFile.exists())
        {
            gravityDataFile.remove();
            gravityDataFile = File::Undefined();
        }

        const_cast<Manager*>(this)->unlockLocalRepository();

        throw;
    }
}

void Manager::setMode(const Manager::Mode& aMode)
{
    std::lock_guard<std::mutex> lock {mutex_};

    mode_ = aMode;
}

bool Manager::isLocalRepositoryLocked() const
{
    return this->getLocalRepositoryLockFile().exists();
}

File Manager::getLocalRepositoryLockFile() const
{
    return File::Path(localRepository_.getPath() + Path::Parse(".lock"));
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

Manager& Manager::Get()
{
    static Manager manager;

    return manager;
}

Manager::Mode Manager::DefaultMode()
{
    static const Manager::Mode defaultMode = OSTK_PHYSICS_ENVIRONMENT_GRAVITATIONAL_EARTH_MANAGER_MODE;

    if (const char* modeString = std::getenv("OSTK_PHYSICS_ENVIRONMENT_GRAVITATIONAL_EARTH_MANAGER_MODE"))
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

Duration Manager::DefaultLocalRepositoryLockTimeout()
{
    static const Duration defaultLocalRepositoryLockTimeout =
        Duration::Seconds(OSTK_PHYSICS_ENVIRONMENT_GRAVITATIONAL_EARTH_MANAGER_LOCAL_REPOSITORY_LOCK_TIMEOUT);

    if (const char* localRepositoryLockTimeoutString =
            std::getenv("OSTK_PHYSICS_ENVIRONMENT_GRAVITATIONAL_EARTH_MANAGER_LOCAL_REPOSITORY_LOCK_TIMEOUT"))
    {
        return Duration::Parse(localRepositoryLockTimeoutString);
    }

    return defaultLocalRepositoryLockTimeout;
}

Manager::Manager()
    : mode_(Manager::DefaultMode()),
      localRepository_(Manager::DefaultLocalRepository()),
      localRepositoryLockTimeout_(Manager::DefaultLocalRepositoryLockTimeout())
{
    if (!localRepository_.exists())
    {
        localRepository_.create();
    }
}

Array<URL> Manager::getDataFileUrlsForType(const EarthGravitationalModel::Type& aModelType) const
{
    ManifestManager& manifestManager = ManifestManager::Get();

    const std::string dataFileName = static_cast<std::string>(Manager::DataFileNameFromType(aModelType));

    std::string dataFileNameUpper = dataFileName;
    transform(dataFileName.begin(), dataFileName.end(), dataFileNameUpper.begin(), ::toupper);

    const String manifestKey = static_cast<std::string>("earth-gravity-" + dataFileNameUpper);

    return manifestManager.getRemoteDataUrls(manifestKey);
}

String Manager::DataFileNameFromType(const EarthGravitationalModel::Type& aModelType)
{
    switch (aModelType)
    {
        case EarthGravitationalModel::Type::WGS84:
            return "wgs84";

        case EarthGravitationalModel::Type::EGM84:
            return "egm84";

        case EarthGravitationalModel::Type::WGS84_EGM96:
        case EarthGravitationalModel::Type::EGM96:
            return "egm96";

        case EarthGravitationalModel::Type::EGM2008:
            return "egm2008";

        default:
            throw ostk::core::error::runtime::Wrong("Type");
    }

    return String::Empty();
}

}  // namespace earth
}  // namespace gravitational
}  // namespace environment
}  // namespace physics
}  // namespace ostk
