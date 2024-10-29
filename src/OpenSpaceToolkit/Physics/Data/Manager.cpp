/// Apache License 2.0

#include <chrono>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <string>
#include <thread>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Path.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/IO/IP/TCP/HTTP/Client.hpp>

#include <OpenSpaceToolkit/Physics/Data/Manager.hpp>
#include <OpenSpaceToolkit/Physics/Data/Manifest.hpp>
#include <OpenSpaceToolkit/Physics/Time/DateTime.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

#include <experimental/filesystem>

namespace ostk
{
namespace physics
{
namespace data
{

using ostk::core::filesystem::Path;
using ostk::core::type::String;

using ostk::io::ip::tcp::http::Client;

using ostk::physics::time::DateTime;
using ostk::physics::time::Instant;
using ostk::physics::time::Scale;

const String dataManifestFileName = "manifest.json";

const String temporaryDirectoryName = "tmp";

Manager& Manager::Get()
{
    static Manager manager;

    return manager;
}

const Instant Manager::getLastUpdateTimestampFor(const String& aDataName)
{
    std::lock_guard<std::mutex> lock {mutex_};

    this->checkManifestAgeAndUpdate_();

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
    std::lock_guard<std::mutex> lock {mutex_};

    this->checkManifestAgeAndUpdate_();
    return manifest_.getRemoteDataUrls(remoteUrl_, aDataName);
}

Array<URL> Manager::findRemoteDataUrls(const String& aDataNameRegex) const
{
    std::lock_guard<std::mutex> lock {mutex_};

    this->checkManifestAgeAndUpdate_();
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

    loadManifest_(aManifest);
}

void Manager::reset()
{
    std::lock_guard<std::mutex> lock {mutex_};

    manifest_ = Manifest::Undefined();

    remoteUrl_ = DefaultRemoteUrl();
    manifestRepository_ = DefaultManifestRepository();
    manifestRepositoryLockTimeout_ = DefaultManifestRepositoryLockTimeout_();
}

Manager::Manager()
    : remoteUrl_(DefaultRemoteUrl()),
      manifest_(Manifest::Undefined()),
      manifestRepository_(Manager::DefaultManifestRepository()),
      manifestRepositoryLockTimeout_(Manager::DefaultManifestRepositoryLockTimeout_())
{
    this->setup_();
}

bool Manager::isManifestRepositoryLocked_() const
{
    return this->getManifestRepositoryLockFile_().exists();
}

File Manager::getManifestRepositoryLockFile_() const
{
    return File::Path(manifestRepository_.getPath() + Path::Parse(".lock"));
}

void Manager::setup_()
{
    if (!manifestRepository_.exists())
    {
        manifestRepository_.create();
    }

    remoteUrl_ = DefaultRemoteUrl();
    manifestRepositoryLockTimeout_ = DefaultManifestRepositoryLockTimeout_();
    manifestRepository_ = DefaultManifestRepository();
}

bool Manager::manifestFileExists() const
{
    if (!manifestRepository_.exists())
    {
        return false;
    }

    return File::Path(manifestRepository_.getPath() + Path::Parse(dataManifestFileName)).exists();
}

void Manager::checkManifestAgeAndUpdate_() const
{
    if (!manifest_.isDefined() && !manifestFileExists())
    {
        // There is no file loaded in memory or on the local filesystem. Fetch and load.
        const File manifestFile = this->fetchLatestManifestFile_();
        this->loadManifest_(Manifest::Load(manifestFile));

        return;
    }

    if (!manifest_.isDefined() && manifestFileExists())
    {
        // A manifest file exists but we haven't loaded it yet. Load it.
        this->loadManifest_(Manifest::Load(File::Path(manifestRepository_.getPath() + Path::Parse(dataManifestFileName))
        ));
    }

    // Determine if we need to fetch a new manifest based on the loaded one.
    // The next timestamp at which we expect the remote to update its data.
    Instant nextUpdateCheckTimestamp = Instant::Undefined();
    try
    {
        nextUpdateCheckTimestamp = manifest_.getNextUpdateCheckTimestampFor("manifest");
    }
    catch (ostk::core::error::RuntimeError& e)
    {
        // If there is no "manifest" entry, the file may be old or corrupted. Fetch a new one.
        const File manifestFile = this->fetchLatestManifestFile_();
        this->loadManifest_(Manifest::Load(manifestFile));

        nextUpdateCheckTimestamp = manifest_.getNextUpdateCheckTimestampFor("manifest");
    }

    const Duration manifestAge = Instant::Now() - manifest_.getLastModifiedTimestamp();

    // If loaded manifest is old enough, fetch a new one and load it.
    if (nextUpdateCheckTimestamp < manifest_.getLastModifiedTimestamp() && manifestAge > DataRefreshRate_())
    {
        const File manifestFile = this->fetchLatestManifestFile_();
        this->loadManifest_(Manifest::Load(manifestFile));
    }
}

void Manager::loadManifest_(const Manifest& aManifest) const
{
    manifest_ = aManifest;
}

File Manager::fetchLatestManifestFile_() const
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
                    "Cannot fetch Data Manifest from [{}]: file is empty.", latestDataManifestUrl.toString()
                );
            }
        }

        latestDataManifestFile.moveToDirectory(destinationDirectory);

        temporaryDirectory.remove();

        this->unlockManifestRepository_();

        std::cout << String::Format(
                         "Data Manifest [{}] has been successfully fetched from [{}].",
                         latestDataManifestFile.toString(),
                         latestDataManifestUrl.toString()
                     )
                  << std::endl;
    }
    catch (const ostk::core::error::Exception& anException)
    {
        std::cerr << String::Format(
                         "Error caught while fetching latest Data Manifest from [{}]: [{}].",
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

void Manager::lockManifestRepository_(const Duration& aTimeout) const
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

void Manager::unlockManifestRepository_() const
{
    std::cout << String::Format("Unlocking local repository [{}]...", manifestRepository_.toString()) << std::endl;

    if (!this->isManifestRepositoryLocked_())
    {
        throw ostk::core::error::RuntimeError("Cannot unlock local repository: lock file does not exist.");
    }

    this->getManifestRepositoryLockFile_().remove();
}

Directory Manager::DefaultManifestRepository()
{
    static const Directory defaultLocalRepository =
        Directory::Path(Path::Parse(OSTK_PHYSICS_DATA_MANIFEST_LOCAL_REPOSITORY));

    if (const char* localRepositoryPath = std::getenv("OSTK_PHYSICS_DATA_MANIFEST_LOCAL_REPOSITORY"))
    {
        return Directory::Path(Path::Parse(localRepositoryPath));
    }
    else if (const char* dataPath = std::getenv("OSTK_PHYSICS_DATA_LOCAL_REPOSITORY"))
    {
        return Directory::Path(Path::Parse(dataPath));
    }

    return defaultLocalRepository;
}

Duration Manager::DefaultManifestRepositoryLockTimeout_()
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

Duration Manager::DataRefreshRate_()
{
    static const Duration defaultRefreshRate = Duration::Hours(OSTK_PHYSICS_DATA_REFRESH_RATE_H);

    if (const char* defaultRefreshRateString = std::getenv("OSTK_PHYSICS_DATA_REFRESH_RATE_H"))
    {
        return Duration::Hours(std::stod(std::string(defaultRefreshRateString)));
    }

    return defaultRefreshRate;
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
