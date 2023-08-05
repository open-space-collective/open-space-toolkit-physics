/// Apache License 2.0

#include <chrono>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <thread>
#include <experimental/filesystem>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Path.hpp>
#include <OpenSpaceToolkit/Core/Types/String.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

#include <OpenSpaceToolkit/IO/IP/TCP/HTTP/Client.hpp>

#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Data/Manifest.hpp>

#include <OpenSpaceToolkit/Physics/Data/ManagerBase.hpp>

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

Instant ManagerBase::getLastUpdateTimestampFor(const String& aDataName)
{
    this->manifest_ = this->getUpdatedManifest_();

    return manifest_.getLastUpdateTimestampFor(aDataName);
}

void ManagerBase::loadManifest_(const Manifest& aManifest)
{
    if (!aManifest.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Manifest");
    }

    std::lock_guard<std::mutex> lock {manifestMutex_};

    this->manifest_ = aManifest;
}

void ManagerBase::resetManifest_()
{
    std::lock_guard<std::mutex> lock {manifestMutex_};

    manifestUpdateTimestamp_ = Instant::Undefined();

    manifest_ = Manifest::Undefined();
}

void ManagerBase::clearManifestRepository_()
{
    manifestRepository_.remove();

    this->setupBase_();
}

ManagerBase::ManagerBase()
    : remoteUrl(DefaultRemoteUrl_()),
      manifest_(Manifest::Undefined()),
      manifestUpdateTimestamp_(Instant::Undefined()),
      manifestRepository_(ManagerBase::DefaultManifestRepository_()),
      manifestRepositoryLockTimeout_(ManagerBase::DefaultManifestRepositoryLockTimeout_())
{
    this->setupBase_();
}

bool ManagerBase::isManifestRepositoryLocked_() const
{
    return this->getManifestRepositoryLockFile_().exists();
}

File ManagerBase::getManifestRepositoryLockFile_() const
{
    return File::Path(manifestRepository_.getPath() + Path::Parse(".lock"));
}

void ManagerBase::setupBase_()
{
    if (!manifestRepository_.exists())
    {
        manifestRepository_.create();
    }

    remoteUrl = DefaultRemoteUrl_();

    if (!remoteUrl.isDefined())
    {
        throw ostk::core::error::RuntimeError("Cannot parse remote URL [{}].", OSTK_PHYSICS_DATA_REMOTE_URL);
    }
}

Manifest ManagerBase::getUpdatedManifest_()
{
    // Check if the local manifest is too old and fetch a new one if needed

    File dataManifestFile = File::Path(manifestRepository_.getPath() + Path::Parse(dataManifestFileName));

    // TODO make max age overridable
    if (!manifestUpdateTimestamp_.isDefined() || !dataManifestFile.exists() ||
        (manifestUpdateTimestamp_ + Duration::Hours(OSTK_PHYSICS_DATA_MANAGER_MANIFEST_MAX_AGE_HOURS) < Instant::Now()))
    {
        dataManifestFile = const_cast<ManagerBase*>(this)->fetchLatestManifestFile_();
        manifestUpdateTimestamp_ = Instant::Now();
    }

    return Manifest::Load(dataManifestFile);
}

File ManagerBase::fetchLatestManifestFile_()
{

    Directory temporaryDirectory = Directory::Path(manifestRepository_.getPath() + Path::Parse(temporaryDirectoryName));

    this->lockManifestRepository_(manifestRepositoryLockTimeout_);

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

        this->unlockManifestRepository_();

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

        this->unlockManifestRepository_();

        throw;
    }

    return latestDataManifestFile;
}

void ManagerBase::lockManifestRepository_(const Duration& aTimeout)
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

    File lockFile = this->getManifestRepositoryLockFile_();

    while (!tryLock(lockFile))
    {
        if (Instant::Now() >= timeoutInstant)
        {
            throw ostk::core::error::RuntimeError("Cannot lock local repository: timeout reached.");
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void ManagerBase::unlockManifestRepository_()
{
    std::cout << String::Format("Unlocking local repository [{}]...", manifestRepository_.toString()) << std::endl;

    if (!this->isManifestRepositoryLocked_())
    {
        throw ostk::core::error::RuntimeError("Cannot unlock local repository: lock file does not exist.");
    }

    this->getManifestRepositoryLockFile_().remove();
}

Directory ManagerBase::DefaultManifestRepository_()
{
    static const Directory defaultLocalRepository =
        Directory::Path(Path::Parse(OSTK_PHYSICS_DATA_MANIFEST_LOCAL_REPOSITORY));

    if (const char* localRepositoryPath = std::getenv("OSTK_PHYSICS_DATA_MANIFEST_LOCAL_REPOSITORY"))
    {
        return Directory::Path(Path::Parse(localRepositoryPath));
    }

    return defaultLocalRepository;
}

Duration ManagerBase::DefaultManifestRepositoryLockTimeout_()
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

URL ManagerBase::DefaultRemoteUrl_()
{
    static const URL defaultRemoteUrl =
        URL::Parse(OSTK_PHYSICS_DATA_REMOTE_URL);

    if (const char* remoteUrlString =
            std::getenv("OSTK_PHYSICS_DATA_REMOTE_URL"))
    {
        return URL::Parse(remoteUrlString);
    }

    return defaultRemoteUrl;
}

}  // namespace data
}  // namespace physics
}  // namespace ostk
