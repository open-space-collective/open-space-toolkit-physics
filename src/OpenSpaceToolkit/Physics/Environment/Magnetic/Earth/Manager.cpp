/// Apache License 2.0

#include <algorithm>
#include <chrono>
#include <cstring>
#include <thread>

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Container/Dictionary.hpp>
#include <OpenSpaceToolkit/Core/Container/Object.hpp>
#include <OpenSpaceToolkit/Core/Container/Pair.hpp>
#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Type/Index.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/IO/IP/TCP/HTTP/Client.hpp>

#include <OpenSpaceToolkit/Physics/Data/Manager.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Magnetic/Earth/Manager.hpp>

namespace ostk
{
namespace physics
{
namespace environment
{
namespace magnetic
{
namespace earth
{

using ManifestManager = ostk::physics::data::Manager;

Manager::Mode Manager::getMode() const
{
    std::lock_guard<std::mutex> lock {mutex_};

    return mode_;
}

void Manager::setMode(const Manager::Mode& aMode)
{
    std::lock_guard<std::mutex> lock {mutex_};

    mode_ = aMode;
}

Manager::Mode Manager::DefaultMode()
{
    static const Manager::Mode defaultMode = OSTK_PHYSICS_ENVIRONMENT_MAGNETIC_EARTH_MANAGER_MODE;

    if (const char* modeString = std::getenv("OSTK_PHYSICS_ENVIRONMENT_MAGNETIC_EARTH_MANAGER_MODE"))
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

bool Manager::hasDataFilesForType(const EarthMagneticModel::Type& aModelType) const
{
    const std::lock_guard<std::mutex> lock {mutex_};

    const String dataFileName = Manager::DataFileNameFromType(aModelType);

    return (
        localRepository_.containsFileWithName(String::Format("{}.wmm", dataFileName)) &&
        localRepository_.containsFileWithName(String::Format("{}.wmm.cof", dataFileName))
    );
}

Array<File> Manager::localDataFilesForType(const EarthMagneticModel::Type& aModelType) const
{
    const std::lock_guard<std::mutex> lock {mutex_};

    const String dataFileName = Manager::DataFileNameFromType(aModelType);

    return {
        File::Path(localRepository_.getPath() + Path::Parse(String::Format("{}.wmm", dataFileName))),
        File::Path(localRepository_.getPath() + Path::Parse(String::Format("{}.wmm.cof", dataFileName)))
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
        Directory::Path(Path::Parse(OSTK_PHYSICS_ENVIRONMENT_MAGNETIC_EARTH_MANAGER_LOCAL_REPOSITORY));

    if (const char* localRepositoryPath =
            std::getenv("OSTK_PHYSICS_ENVIRONMENT_MAGNETIC_EARTH_MANAGER_LOCAL_REPOSITORY"))
    {
        return Directory::Path(Path::Parse(localRepositoryPath));
    }
    else if (const char* dataPath = std::getenv("OSTK_PHYSICS_DATA_LOCAL_REPOSITORY"))
    {
        return Directory::Path(Path::Parse(dataPath) + Path::Parse("environment/magnetic/earth"));
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

void Manager::fetchDataFilesForType(const EarthMagneticModel::Type& aModelType) const
{
    using ostk::core::type::Index;
    using ostk::core::type::Size;

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
    File magneticDataFile = File::Undefined();

    try
    {
        for (const auto& url : remoteUrls)
        {
            remoteDataUrl = url;

            std::cout << String::Format("Fetching magnetic data file from [{}]...", remoteDataUrl.toString())
                      << std::endl;

            magneticDataFile = Client::Fetch(remoteDataUrl, localRepository_, 2);

            if (!magneticDataFile.exists())
            {
                throw ostk::core::error::RuntimeError(
                    "Cannot fetch Magnetic Data File from [{}].", remoteDataUrl.toString()
                );
            }

            // Check that Magnetic Data File size is not zero

            std::uintmax_t magneticDataFileSize =
                std::experimental::filesystem::file_size(std::string(magneticDataFile.getPath().toString()));

            if (magneticDataFileSize == 0)
            {
                throw ostk::core::error::RuntimeError(
                    "Cannot fetch Magnetic Data from [{}]: file is empty.", remoteDataUrl.toString()
                );
            }

            std::cout << String::Format(
                             "Magnetic Data [{}] has been successfully fetched from [{}].",
                             magneticDataFile.toString(),
                             remoteDataUrl.toString()
                         )
                      << std::endl;
        }

        const_cast<Manager*>(this)->unlockLocalRepository();
    }
    catch (const ostk::core::error::Exception& anException)
    {
        std::cerr << String::Format(
                         "Error caught while fetching Magnetic Data from [{}]: [{}].",
                         remoteDataUrl.toString(),
                         anException.what()
                     )
                  << std::endl;

        if (magneticDataFile.isDefined() && magneticDataFile.exists())
        {
            magneticDataFile.remove();
            magneticDataFile = File::Undefined();
        }

        const_cast<Manager*>(this)->unlockLocalRepository();

        throw;
    }
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

Duration Manager::DefaultLocalRepositoryLockTimeout()
{
    static const Duration defaultLocalRepositoryLockTimeout =
        Duration::Seconds(OSTK_PHYSICS_ENVIRONMENT_MAGNETIC_EARTH_MANAGER_LOCAL_REPOSITORY_LOCK_TIMEOUT);

    if (const char* localRepositoryLockTimeoutString =
            std::getenv("OSTK_PHYSICS_ENVIRONMENT_MAGNETIC_EARTH_MANAGER_LOCAL_REPOSITORY_LOCK_TIMEOUT"))
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

Array<URL> Manager::getDataFileUrlsForType(const EarthMagneticModel::Type& aModelType) const
{
    ManifestManager& manifestManager = ManifestManager::Get();

    const std::string dataFileName = static_cast<std::string>(Manager::DataFileNameFromType(aModelType));

    std::string dataFileNameUpper = dataFileName;
    transform(dataFileName.begin(), dataFileName.end(), dataFileNameUpper.begin(), ::toupper);

    const String manifestKey = static_cast<std::string>("earth-magnetic-" + dataFileNameUpper);

    return manifestManager.getRemoteDataUrls(manifestKey);
}

String Manager::DataFileNameFromType(const EarthMagneticModel::Type& aModelType)
{
    switch (aModelType)
    {
        case EarthMagneticModel::Type::EMM2010:
            return "emm2010";

        case EarthMagneticModel::Type::EMM2015:
            return "emm2015";

        case EarthMagneticModel::Type::EMM2017:
            return "emm2017";

        case EarthMagneticModel::Type::IGRF11:
            return "igrf11";

        case EarthMagneticModel::Type::IGRF12:
            return "igrf12";

        case EarthMagneticModel::Type::WMM2010:
            return "wmm2010";

        case EarthMagneticModel::Type::WMM2015:
            return "wmm2015";

        default:
            throw ostk::core::error::runtime::Wrong("Type");
    }

    return String::Empty();
}

}  // namespace earth
}  // namespace magnetic
}  // namespace environment
}  // namespace physics
}  // namespace ostk
