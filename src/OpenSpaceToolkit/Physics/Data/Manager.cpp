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
    BaseManager::reset();

    manifest_ = Manifest::Undefined();

    remoteUrl_ = DefaultRemoteUrl();
}

Manager::Manager()
    : BaseManager(
          "OSTK_PHYSICS_DATA_MANIFEST_MANAGER_MODE",
          Directory::Path(Path::Parse(OSTK_PHYSICS_DATA_MANIFEST_LOCAL_REPOSITORY)),
          "OSTK_PHYSICS_DATA_MANIFEST_LOCAL_REPOSITORY",
          Path::Parse("manifest"),
          "OSTK_PHYSICS_DATA_MANIFEST_LOCAL_REPOSITORY_LOCK_TIMEOUT"
      ),
      remoteUrl_(DefaultRemoteUrl()),
      manifest_(Manifest::Undefined())
{
}

bool Manager::manifestFileExists() const
{
    if (!localRepository_.exists())
    {
        return false;
    }

    return File::Path(localRepository_.getPath() + Path::Parse(dataManifestFileName)).exists();
}

void Manager::checkManifestAgeAndUpdate_() const
{
    if (!manifest_.isDefined() && !manifestFileExists())
    {
        if (mode_ == Manager::Mode::Manual)
        {
            throw ostk::core::error::RuntimeError(
                "No manifest file loaded and no manifest file found in local repository. Manager mode is Manual."
            );
        }
        else if (mode_ == Manager::Mode::Automatic)
        {
            // There is no file loaded in memory or on the local filesystem. Fetch and load.
            const File manifestFile = this->fetchLatestManifestFile_();
            this->loadManifest_(Manifest::Load(manifestFile));
            return;
        }
    }

    if (!manifest_.isDefined() && manifestFileExists())
    {
        // A manifest file exists but we haven't loaded it yet. Load it.
        this->loadManifest_(Manifest::Load(File::Path(localRepository_.getPath() + Path::Parse(dataManifestFileName))));
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
        if (mode_ == Manager::Mode::Manual)
        {
            throw ostk::core::error::RuntimeError(
                "Manifest file is old or corrupted. Cannot fetch as manager mode is Manual."
            );
        }
        else if (mode_ == Manager::Mode::Automatic)
        {
            const File manifestFile = this->fetchLatestManifestFile_();
            this->loadManifest_(Manifest::Load(manifestFile));

            nextUpdateCheckTimestamp = manifest_.getNextUpdateCheckTimestampFor("manifest");
        }
    }

    const Duration manifestAge = Instant::Now() - manifest_.getLastUpdateTimestampFor("manifest");

    // If current time is past next update check time or manifest is old enough, fetch a new one and load it.
    if (Instant::Now() > nextUpdateCheckTimestamp && manifestAge > DataRefreshRate_())
    {
        if (mode_ == Manager::Mode::Manual)
        {
            throw ostk::core::error::RuntimeError("Manifest file is old. Cannot fetch as manager mode is Manual.");
        }
        else if (mode_ == Manager::Mode::Automatic)
        {
            const File manifestFile = this->fetchLatestManifestFile_();
            this->loadManifest_(Manifest::Load(manifestFile));
        }
    }
}

void Manager::loadManifest_(const Manifest& aManifest) const
{
    manifest_ = aManifest;
}

File Manager::fetchLatestManifestFile_() const
{
    Directory temporaryDirectory = Directory::Path(localRepository_.getPath() + Path::Parse(temporaryDirectoryName));

    this->lockLocalRepository_(localRepositoryLockTimeout_);

    String remoteUrlString = Manager::DefaultRemoteUrl().toString();

    if (remoteUrlString.getLast() == '/')
    {
        remoteUrlString = remoteUrlString + dataManifestFileName;
    }
    else
    {
        remoteUrlString = remoteUrlString + "/" + dataManifestFileName;
    }

    const URL latestDataManifestUrl = URL::Parse(remoteUrlString);

    File latestDataManifestFile = File::Undefined();
    Directory destinationDirectory = Directory::Undefined();

    try
    {
        destinationDirectory = localRepository_;

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
                std::filesystem::file_size(std::string(latestDataManifestFile.getPath().toString()));

            if (latestDataManifestFileSize == 0)
            {
                throw ostk::core::error::RuntimeError(
                    "Cannot fetch Data Manifest from [{}]: file is empty.", latestDataManifestUrl.toString()
                );
            }
        }

        latestDataManifestFile.moveToDirectory(destinationDirectory);

        temporaryDirectory.remove();

        this->unlockLocalRepository_();

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

        this->unlockLocalRepository_();

        throw;
    }

    return latestDataManifestFile;
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

Manager& Manager::Get()
{
    static Manager manager;

    return manager;
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
