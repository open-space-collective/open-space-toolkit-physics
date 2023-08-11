/// Apache License 2.0

#include <chrono>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <thread>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Path.hpp>
#include <OpenSpaceToolkit/Core/Types/String.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

#include <OpenSpaceToolkit/IO/IP/TCP/HTTP/Client.hpp>

#include <OpenSpaceToolkit/Physics/Data/Manager.hpp>
#include <OpenSpaceToolkit/Physics/Data/Manifest.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

#include <experimental/filesystem>

namespace ostk
{
namespace physics
{
namespace data
{

using ostk::core::types::String;
using ostk::core::fs::Path;
using ostk::core::types::String;

using ostk::io::ip::tcp::http::Client;

using ostk::physics::time::Scale;
using ostk::physics::time::Instant;

const String dataManifestFileName = "manifest.json";

const String temporaryDirectoryName = "tmp";

Manager& Manager::Get()
{
    static Manager manager;

    return manager;
}

const Instant Manager::getLastUpdateTimestampFor(const String& aDataName)
{
    this->checkManifestAgeAndUpdate();

    return manifest_.getLastUpdateTimestampFor(aDataName);
}

const URL Manager::getRemoteUrl() const
{
    return remoteUrl_;
}

void Manager::setRemoteUrl(const URL& aRemoteUrl)
{
    if (!aRemoteUrl.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("URL");
    }

    remoteUrl_ = aRemoteUrl;
}

const Directory Manager::getManifestRepository() const
{
    return manifestRepository_;
}

void Manager::setManifestRepository(const Directory& aManifestRepository)
{
    if (!aManifestRepository.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Manifest repository");
    }

    manifestRepository_ = aManifestRepository;
}

Array<URL> Manager::getRemoteDataUrls(const String& aDataName) const
{
    const_cast<Manager*>(this)->checkManifestAgeAndUpdate();
    return manifest_.getRemoteDataUrls(remoteUrl_, aDataName);
}

Array<URL> Manager::findRemoteDataUrls(const String& aDataNameRegex) const
{
    const_cast<Manager*>(this)->checkManifestAgeAndUpdate();
    return manifest_.findRemoteDataUrls(remoteUrl_, aDataNameRegex);
}

const Manifest Manager::getManifest() const
{
    return manifest_;
}

void Manager::loadManifest(const Manifest& aManifest)
{
    if (!aManifest.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Manifest");
    }

    std::lock_guard<std::mutex> lock {mutex_};

    this->manifest_ = aManifest;
    this->manifestUpdateTimestamp_ = Instant::Now();
}

void Manager::reset()
{
    std::lock_guard<std::mutex> lock {mutex_};

    manifestUpdateTimestamp_ = Instant::Undefined();

    manifest_ = Manifest::Undefined();

    remoteUrl_ = DefaultRemoteUrl();
    manifestRepository_ = DefaultManifestRepository();
    manifestRepositoryLockTimeout_ = DefaultManifestRepositoryLockTimeout();
}

Manager::Manager()
    : remoteUrl_(DefaultRemoteUrl()),
      manifest_(Manifest::Undefined()),
      manifestUpdateTimestamp_(Instant::Undefined()),
      manifestRepository_(Manager::DefaultManifestRepository()),
      manifestRepositoryLockTimeout_(Manager::DefaultManifestRepositoryLockTimeout())
{
    this->setup();
}

bool Manager::isManifestRepositoryLocked() const
{
    return this->getManifestRepositoryLockFile().exists();
}

File Manager::getManifestRepositoryLockFile() const
{
    return File::Path(manifestRepository_.getPath() + Path::Parse(".lock"));
}

void Manager::setup()
{
    if (!manifestRepository_.exists())
    {
        manifestRepository_.create();
    }

    remoteUrl_ = DefaultRemoteUrl();
    manifestRepositoryLockTimeout_ = DefaultManifestRepositoryLockTimeout();
    manifestRepository_ = DefaultManifestRepository();
}

void Manager::checkManifestAgeAndUpdate()
{
    // Check if the local manifest is too old and fetch a new one if needed
    // TODO make max age overridable
    if (!manifestUpdateTimestamp_.isDefined() || !manifest_.isDefined() ||
        (manifestUpdateTimestamp_ + Duration::Hours(OSTK_PHYSICS_DATA_MANAGER_MANIFEST_MAX_AGE_HOURS) < Instant::Now()))
    {
        File manifestFile = this->fetchLatestManifestFile();
        this->loadManifest(Manifest::Load(manifestFile));
    }
}

File Manager::fetchLatestManifestFile()
{
    Directory temporaryDirectory = Directory::Path(manifestRepository_.getPath() + Path::Parse(temporaryDirectoryName));

    this->lockManifestRepository(manifestRepositoryLockTimeout_);

    const URL latestDataManifestUrl = URL::Parse(OSTK_PHYSICS_DATA_REMOTE_URL) + dataManifestFileName;

    File latestDataManifestFile = File::Undefined();
    Directory destinationDirectory = Directory::Undefined();

    try
    {
        destinationDirectory = manifestRepository_;

        if (!destinationDirectory.exists())
        {
            destinationDirectory.create();
        }

        if (temporaryDirectory.exists())
        {
            throw ostk::core::error::RuntimeError(
                "Temporary directory [{}] already exists.", temporaryDirectory.toString()
            );
        }

        temporaryDirectory.create();

        std::cout << String::Format("Fetching Data Manifest from [{}]...", latestDataManifestUrl.toString())
                  << std::endl;

        latestDataManifestFile = Client::Fetch(latestDataManifestUrl, temporaryDirectory, 2);

        if (!latestDataManifestFile.exists())
        {
            throw ostk::core::error::RuntimeError(
                "Cannot fetch Data Manifest [{}] from [{}].",
                latestDataManifestFile.toString(),
                latestDataManifestUrl.toString()
            );
        }
        else
        {
            // Check that file size is not zero

            std::uintmax_t latestDataManifestFileSize =
                std::experimental::filesystem::file_size(std::string(latestDataManifestFile.getPath().toString()));

            if (latestDataManifestFileSize == 0)
            {
                throw ostk::core::error::RuntimeError(
                    "Cannot fetch Data  Manifest from [{}]: file is empty.", latestDataManifestUrl.toString()
                );
            }
        }

        latestDataManifestFile.moveToDirectory(destinationDirectory);

        temporaryDirectory.remove();

        this->unlockManifestRepository();

        std::cout << String::Format(
                         "Data  Manifest [{}] has been successfully fetched from [{}].",
                         latestDataManifestFile.toString(),
                         latestDataManifestUrl.toString()
                     )
                  << std::endl;
    }
    catch (const ostk::core::error::Exception& anException)
    {
        std::cerr << String::Format(
                         "Error caught while fetching latest Data  Manifest from [{}]: [{}].",
                         latestDataManifestUrl.toString(),
                         anException.what()
                     )
                  << std::endl;

        if (latestDataManifestFile.isDefined() && latestDataManifestFile.exists())
        {
            latestDataManifestFile.remove();
            latestDataManifestFile = File::Undefined();
        }

        if (temporaryDirectory.isDefined() && temporaryDirectory.exists())
        {
            temporaryDirectory.remove();
        }

        this->unlockManifestRepository();

        throw;
    }

    return latestDataManifestFile;
}

void Manager::lockManifestRepository(const Duration& aTimeout)
{
    std::cout << String::Format("Locking local repository [{}]...", manifestRepository_.toString()) << std::endl;

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

    File lockFile = this->getManifestRepositoryLockFile();

    while (!tryLock(lockFile))
    {
        if (Instant::Now() >= timeoutInstant)
        {
            throw ostk::core::error::RuntimeError("Cannot lock local repository: timeout reached.");
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void Manager::unlockManifestRepository()
{
    std::cout << String::Format("Unlocking local repository [{}]...", manifestRepository_.toString()) << std::endl;

    if (!this->isManifestRepositoryLocked())
    {
        throw ostk::core::error::RuntimeError("Cannot unlock local repository: lock file does not exist.");
    }

    this->getManifestRepositoryLockFile().remove();
}

Directory Manager::DefaultManifestRepository()
{
    static const Directory defaultLocalRepository =
        Directory::Path(Path::Parse(OSTK_PHYSICS_DATA_MANIFEST_LOCAL_REPOSITORY));

    if (const char* localRepositoryPath = std::getenv("OSTK_PHYSICS_DATA_MANIFEST_LOCAL_REPOSITORY"))
    {
        return Directory::Path(Path::Parse(localRepositoryPath));
    }

    return defaultLocalRepository;
}

Duration Manager::DefaultManifestRepositoryLockTimeout()
{
    static const Duration defaultLocalRepositoryLockTimeout =
        Duration::Seconds(OSTK_PHYSICS_DATA_MANIFEST_LOCAL_REPOSITORY_LOCK_TIMEOUT);

    if (const char* localRepositoryLockTimeoutString =
            std::getenv("OSTK_PHYSICS_DATA_MANIFEST_LOCAL_REPOSITORY_LOCK_TIMEOUT"))
    {
        return Duration::Parse(localRepositoryLockTimeoutString);
    }

    return defaultLocalRepositoryLockTimeout;
}

URL Manager::DefaultRemoteUrl()
{
    static const URL defaultRemoteUrl = URL::Parse(OSTK_PHYSICS_DATA_REMOTE_URL);

    if (const char* remoteUrlString = std::getenv("OSTK_PHYSICS_DATA_REMOTE_URL"))
    {
        return URL::Parse(remoteUrlString);
    }

    return defaultRemoteUrl;
}

}  // namespace data
}  // namespace physics
}  // namespace ostk
