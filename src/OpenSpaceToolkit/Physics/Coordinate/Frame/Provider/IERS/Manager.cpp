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

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/IERS/Manager.hpp>
#include <OpenSpaceToolkit/Physics/Data/Manager.hpp>
#include <OpenSpaceToolkit/Physics/Data/Manifest.hpp>
#include <OpenSpaceToolkit/Physics/Time/Date.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Time/Scale.hpp>
#include <OpenSpaceToolkit/Physics/Time/Time.hpp>

#include <experimental/filesystem>

namespace ostk
{
namespace physics
{
namespace coord
{
namespace frame
{
namespace provider
{
namespace iers
{

using ostk::core::type::String;
using ostk::core::filesystem::Path;

using ostk::io::ip::tcp::http::Client;
using ostk::io::URL;

using ManifestManager = ostk::physics::data::Manager;

const String bulletinAFileName = "ser7.dat";
const String finals2000AFileName = "finals2000A.data";

const String bulletinAManifestName = "bulletin-A";
const String finals2000AManifestName = "finals-2000A";

// TBI: this path can be obtained from the manifest
const String bulletinARemotePath = "coordinate/frame/providers/iers/bulletin-A/";
const String finals2000ARemotePath = "coordinate/frame/providers/iers/finals-2000A/";

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

Directory Manager::getBulletinADirectory() const
{
    return Directory::Path(localRepository_.getPath() + Path::Parse("bulletin-A"));
}

Directory Manager::getFinals2000ADirectory() const
{
    return Directory::Path(localRepository_.getPath() + Path::Parse("finals-2000A"));
}

BulletinA Manager::getBulletinA() const
{
    std::lock_guard<std::mutex> lock {mutex_};

    const BulletinA* bulletinAPtr = accessBulletinA_();

    if (bulletinAPtr != nullptr)
    {
        return *bulletinAPtr;
    }

    throw ostk::core::error::RuntimeError("Cannot obtain Bulletin A.");
}

Finals2000A Manager::getFinals2000A() const
{
    std::lock_guard<std::mutex> lock {mutex_};

    const Finals2000A* finals2000aPtr = accessFinals2000A_();

    if (finals2000aPtr != nullptr)
    {
        return *finals2000aPtr;
    }

    throw ostk::core::error::RuntimeError("Cannot obtain Finals 2000A.");
}

Vector2d Manager::getPolarMotionAt(const Instant& anInstant) const
{
    if (!anInstant.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

    std::lock_guard<std::mutex> lock {mutex_};

    // Try data in this order:
    // 1. Bulletin A rapid service observations (released daily)
    // 2. Bulletin A predictions (released daily)
    // 3. Finals 2000A observations (released weekly)
    //
    // https://hpiers.obspm.fr/eoppc/bul/bulb/explanatory.html

    const BulletinA* bulletinAPtr = this->accessBulletinA_();

    if (bulletinAPtr != nullptr)
    {
        if (bulletinAPtr->accessObservationInterval().contains(anInstant))
        {
            const BulletinA::Observation observation = bulletinAPtr->getObservationAt(anInstant);

            return {observation.x, observation.y};
        }
        else if (bulletinAPtr->accessPredictionInterval().contains(anInstant))
        {
            const BulletinA::Prediction prediction = bulletinAPtr->getPredictionAt(anInstant);

            return {prediction.x, prediction.y};
        }
    }

    const Finals2000A* finals2000aPtr = this->accessFinals2000A_();

    if (finals2000aPtr != nullptr)
    {
        const Vector2d polarMotion = finals2000aPtr->getPolarMotionAt(anInstant);
        if (!polarMotion.isDefined())
        {
            throw ostk::core::error::RuntimeError(
                "Cannot obtain polar motion from Finals2000a at [{}].", anInstant.toString()
            );
        }
        return polarMotion;
    }

    throw ostk::core::error::RuntimeError("Cannot obtain polar motion at [{}].", anInstant.toString());

    return Vector2d::Undefined();
}

Real Manager::getUt1MinusUtcAt(const Instant& anInstant) const
{
    if (!anInstant.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

    std::lock_guard<std::mutex> lock {mutex_};

    // Try data in this order:
    // 1. Bulletin A rapid service observations (released daily)
    // 2. Bulletin A predictions (released daily)
    // 3. Finals 2000A observations (released weekly)
    //
    // https://hpiers.obspm.fr/eoppc/bul/bulb/explanatory.html

    const BulletinA* bulletinAPtr = this->accessBulletinA_();

    if (bulletinAPtr != nullptr)
    {
        if (bulletinAPtr->accessObservationInterval().contains(anInstant))
        {
            const BulletinA::Observation observation = bulletinAPtr->getObservationAt(anInstant);

            return observation.ut1MinusUtc;
        }
        else if (bulletinAPtr->accessPredictionInterval().contains(anInstant))
        {
            const BulletinA::Prediction prediction = bulletinAPtr->getPredictionAt(anInstant);

            return prediction.ut1MinusUtc;
        }
    }

    const Finals2000A* finals2000aPtr = this->accessFinals2000A_();

    if (finals2000aPtr != nullptr)
    {
        return finals2000aPtr->getUt1MinusUtcAt(anInstant);
    }

    throw ostk::core::error::RuntimeError("Cannot obtain UT1 - UTC at [{}].", anInstant.toString());

    return Real::Undefined();
}

Real Manager::getLodAt(const Instant& anInstant) const
{
    if (!anInstant.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

    std::lock_guard<std::mutex> lock {mutex_};

    const Finals2000A* finals2000aPtr = this->accessFinals2000A_();

    if (finals2000aPtr != nullptr)
    {
        return finals2000aPtr->getLodAt(anInstant);
    }

    throw ostk::core::error::RuntimeError("Cannot obtain LOD at [{}].", anInstant.toString());

    return Real::Undefined();
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

void Manager::loadBulletinA(const BulletinA& aBulletinA)
{
    if (!aBulletinA.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Bulletin A");
    }

    std::lock_guard<std::mutex> lock {mutex_};

    this->loadBulletinA_(aBulletinA);
}

void Manager::loadFinals2000A(const Finals2000A& aFinals2000A)
{
    if (!aFinals2000A.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Finals 2000A");
    }

    std::lock_guard<std::mutex> lock {mutex_};

    this->loadFinals2000A_(aFinals2000A);
}

File Manager::fetchLatestBulletinA() const
{
    std::lock_guard<std::mutex> lock {mutex_};

    return this->fetchLatestBulletinA_();
}

File Manager::fetchLatestFinals2000A() const
{
    std::lock_guard<std::mutex> lock {mutex_};

    return this->fetchLatestFinals2000A_();
}

void Manager::reset()
{
    std::lock_guard<std::mutex> lock {mutex_};

    bulletinA_ = BulletinA::Undefined();
    finals2000A_ = Finals2000A::Undefined();
}

void Manager::clearLocalRepository()
{
    localRepository_.remove();

    this->setup_();
}

Manager& Manager::Get()
{
    static Manager manager;

    return manager;
}

Manager::Mode Manager::DefaultMode()
{
    static const Manager::Mode defaultMode = OSTK_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_MANAGER_MODE;

    if (const char* modeString = std::getenv("OSTK_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_MANAGER_MODE"))
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
    using ostk::core::filesystem::Path;

    static const Directory defaultLocalRepository =
        Directory::Path(Path::Parse(OSTK_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_MANAGER_LOCAL_REPOSITORY));

    if (const char* localRepositoryPath =
            std::getenv("OSTK_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_MANAGER_LOCAL_REPOSITORY"))
    {
        return Directory::Path(Path::Parse(localRepositoryPath));
    }
    else if (const char* dataPath = std::getenv("OSTK_PHYSICS_DATA_LOCAL_REPOSITORY"))
    {
        return Directory::Path(Path::Parse(dataPath) + Path::Parse("coordinate/frame/providers/iers"));
    }

    return defaultLocalRepository;
}

Duration Manager::DefaultLocalRepositoryLockTimeout()
{
    static const Duration defaultLocalRepositoryLockTimeout =
        Duration::Seconds(OSTK_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_MANAGER_LOCAL_REPOSITORY_LOCK_TIMEOUT);

    if (const char* localRepositoryLockTimeoutString =
            std::getenv("OSTK_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_MANAGER_LOCAL_REPOSITORY_LOCK_TIMEOUT"))
    {
        return Duration::Parse(localRepositoryLockTimeoutString);
    }

    return defaultLocalRepositoryLockTimeout;
}

Manager::Manager(const Manager::Mode& aMode)
    : mode_(aMode),
      localRepository_(Manager::DefaultLocalRepository()),
      localRepositoryLockTimeout_(Manager::DefaultLocalRepositoryLockTimeout()),
      bulletinA_(BulletinA::Undefined()),
      finals2000A_(Finals2000A::Undefined())
{
    this->setup_();
}

void Manager::setup_()
{
    if (!localRepository_.exists())
    {
        localRepository_.create();
    }

    if (!this->getBulletinADirectory().exists())
    {
        this->getBulletinADirectory().create();
    }

    if (!this->getFinals2000ADirectory().exists())
    {
        this->getFinals2000ADirectory().create();
    }
}

bool Manager::isLocalRepositoryLocked_() const
{
    return this->getLocalRepositoryLockFile_().exists();
}

File Manager::getLocalRepositoryLockFile_() const
{
    return File::Path(localRepository_.getPath() + Path::Parse(".lock"));
}

void Manager::lockLocalRepository_(const Duration& aTimeout) const
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

    File lockFile = this->getLocalRepositoryLockFile_();

    while (!tryLock(lockFile))
    {
        if (Instant::Now() >= timeoutInstant)
        {
            throw ostk::core::error::RuntimeError("Cannot lock local repository: timeout reached.");
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void Manager::unlockLocalRepository_() const
{
    std::cout << String::Format("Unlocking local repository [{}]...", localRepository_.toString()) << std::endl;

    if (!this->isLocalRepositoryLocked_())
    {
        throw ostk::core::error::RuntimeError("Cannot unlock local repository: lock file does not exist.");
    }

    this->getLocalRepositoryLockFile_().remove();
}

void Manager::loadBulletinA_(const BulletinA& aBulletinA) const
{
    bulletinA_ = aBulletinA;
}

void Manager::loadFinals2000A_(const Finals2000A& aFinals2000A) const
{
    finals2000A_ = aFinals2000A;
}

const BulletinA* Manager::accessBulletinA_() const
{
    // If we've loaded a file, simply return it
    if (bulletinA_.isDefined())
    {
        return &bulletinA_;
    }

    // If set to automatic, try to load or fetch the latest file
    if (mode_ == Manager::Mode::Automatic)
    {
        // Try from file
        File localBulletinAFile = File::Undefined();

        if (this->getBulletinADirectory().containsFileWithName(bulletinAFileName))
        {
            localBulletinAFile = File::Path(this->getBulletinADirectory().getPath() + Path::Parse(bulletinAFileName));

            // if the file exists locally, load and check timestamp against remote
            const BulletinA bulletinA = BulletinA::Load(localBulletinAFile);

            ManifestManager& manifestManager = ManifestManager::Get();

            // When the file was last updated on the remote (this may trigger a manifest fetch)
            const Instant bulletinARemoteUpdateTimestamp =
                manifestManager.getLastUpdateTimestampFor(bulletinAManifestName);

            // When the file was last updated locally
            const Instant bulletinALocalUpdateTimestamp = bulletinA.accessLastModifiedTimestamp();

            if (bulletinARemoteUpdateTimestamp > bulletinALocalUpdateTimestamp)
            {
                // if the remote file is newer, fetch it
                localBulletinAFile = this->fetchLatestBulletinA_();
            }
        }
        else
        {
            // if it doesn't exist, fetch latest from remote
            localBulletinAFile = this->fetchLatestBulletinA_();
        }

        this->loadBulletinA_(BulletinA::Load(localBulletinAFile));

        return &bulletinA_;
    }

    // No bulletin A found and unable to fetch

    {
        return nullptr;
    }
}

const Finals2000A* Manager::accessFinals2000A_() const
{
    // If we've loaded a file, simply return it
    if (finals2000A_.isDefined())
    {
        return &finals2000A_;
    }

    // If set to automatic, try to load or fetch the latest file
    if (mode_ == Manager::Mode::Automatic)
    {
        // Try from file
        File localFinals2000AFile = File::Undefined();

        if (this->getFinals2000ADirectory().containsFileWithName(finals2000AFileName))
        {
            localFinals2000AFile =
                File::Path(this->getFinals2000ADirectory().getPath() + Path::Parse(finals2000AFileName));

            // if the file exists locally, load and check timestamp against remote
            const Finals2000A finals2000A = Finals2000A::Load(localFinals2000AFile);

            ManifestManager& manifestManager = ManifestManager::Get();

            // When the file was last updated on the remote (this may trigger a manifest fetch)
            const Instant finals2000ARemoteUpdateTimestamp =
                manifestManager.getLastUpdateTimestampFor(finals2000AManifestName);

            // When the file was last updated locally
            const Instant finals2000ALocalUpdateTimestamp = finals2000A.accessLastModifiedTimestamp();

            if (finals2000ARemoteUpdateTimestamp > finals2000ALocalUpdateTimestamp)
            {
                // if the remote file is newer, fetch it
                localFinals2000AFile = this->fetchLatestFinals2000A_();
            }
        }
        else
        {
            // if it doesn't exist, fetch latest from remote
            localFinals2000AFile = this->fetchLatestFinals2000A_();
        }

        this->loadFinals2000A_(Finals2000A::Load(localFinals2000AFile));

        return &finals2000A_;
    }

    // No finals 2000A found and unable to fetch

    {
        return nullptr;
    }
}

File Manager::fetchLatestBulletinA_() const
{
    std::cout << "Fetching latest Bulletin A..." << std::endl;

    ManifestManager& manifestManager = ManifestManager::Get();

    Directory temporaryDirectory =
        Directory::Path(this->getBulletinADirectory().getPath() + Path::Parse(temporaryDirectoryName));

    this->lockLocalRepository_(localRepositoryLockTimeout_);

    const URL latestBulletinAUrl = manifestManager.getRemoteUrl() + bulletinARemotePath + bulletinAFileName;

    File latestBulletinAFile = File::Undefined();
    Directory destinationDirectory = Directory::Undefined();

    try
    {
        // Create temporary Directory,
        // e.g., `.open-space-toolkit/physics/coordinate/frame/providers/iers/bulletin-a/tmp/`.

        if (temporaryDirectory.exists())
        {
            throw ostk::core::error::RuntimeError(
                "Temporary directory [{}] already exists.", temporaryDirectory.toString()
            );
        }

        std::cout << String::Format("Creating temporary directory [{}]...", temporaryDirectory.toString()) << std::endl;

        temporaryDirectory.create();

        // Download latest Bulletin A File into temporary Directory

        std::cout << String::Format("Fetching Bulletin A from [{}]...", latestBulletinAUrl.toString()) << std::endl;

        latestBulletinAFile = Client::Fetch(latestBulletinAUrl, temporaryDirectory, 2);

        if (!latestBulletinAFile.exists())
        {
            throw ostk::core::error::RuntimeError("Cannot fetch Bulletin A from [{}].", latestBulletinAUrl.toString());
        }

        // Check that Bulletin A File size is not zero

        std::uintmax_t latestBulletinAFileSize =
            std::experimental::filesystem::file_size(std::string(latestBulletinAFile.getPath().toString()));

        if (latestBulletinAFileSize == 0)
        {
            throw ostk::core::error::RuntimeError(
                "Cannot fetch Bulletin A from [{}]: file is empty.", latestBulletinAUrl.toString()
            );
        }

        // Move Bulletin A File into destination Directory,
        // e.g., `.open-space-toolkit/physics/coordinate/frame/providers/iers/bulletin-A/`.

        destinationDirectory = Directory::Path(this->getBulletinADirectory().getPath());

        latestBulletinAFile.moveToDirectory(destinationDirectory);

        temporaryDirectory.remove();

        this->unlockLocalRepository_();

        std::cout << String::Format(
                         "Bulletin A [{}] has been successfully fetched from [{}].",
                         latestBulletinAFile.toString(),
                         latestBulletinAUrl.toString()
                     )
                  << std::endl;
    }
    catch (const ostk::core::error::Exception& anException)
    {
        std::cerr << String::Format(
                         "Error caught while fetching latest Bulletin A from [{}]: [{}].",
                         latestBulletinAUrl.toString(),
                         anException.what()
                     )
                  << std::endl;

        if (latestBulletinAFile.isDefined() && latestBulletinAFile.exists())
        {
            latestBulletinAFile.remove();
            latestBulletinAFile = File::Undefined();
        }

        if (temporaryDirectory.isDefined() && temporaryDirectory.exists())
        {
            temporaryDirectory.remove();
        }

        this->unlockLocalRepository_();

        throw;
    }

    return latestBulletinAFile;
}

File Manager::fetchLatestFinals2000A_() const
{
    std::cout << "Fetching latest Finals 2000A..." << std::endl;

    ManifestManager& manifestManager = ManifestManager::Get();

    Directory temporaryDirectory =
        Directory::Path(this->getFinals2000ADirectory().getPath() + Path::Parse(temporaryDirectoryName));

    this->lockLocalRepository_(localRepositoryLockTimeout_);

    const URL latestFinals2000AUrl = manifestManager.getRemoteUrl() + finals2000ARemotePath + finals2000AFileName;

    File latestFinals2000AFile = File::Undefined();
    Directory destinationDirectory = Directory::Undefined();

    try
    {
        destinationDirectory = Directory::Path(this->getFinals2000ADirectory().getPath());

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

        std::cout << String::Format("Fetching Finals 2000A from [{}]...", latestFinals2000AUrl.toString()) << std::endl;

        latestFinals2000AFile = Client::Fetch(latestFinals2000AUrl, temporaryDirectory, 2);

        const Finals2000A latestFinals2000A = Finals2000A::Load(latestFinals2000AFile);

        if (!latestFinals2000AFile.exists())
        {
            throw ostk::core::error::RuntimeError(
                "Cannot fetch Finals 2000A [{}] from [{}].",
                latestFinals2000AFile.toString(),
                latestFinals2000AUrl.toString()
            );
        }
        else
        {
            // Check that file size is not zero

            std::uintmax_t latestFinals2000AFileSize =
                std::experimental::filesystem::file_size(std::string(latestFinals2000AFile.getPath().toString()));

            if (latestFinals2000AFileSize == 0)
            {
                throw ostk::core::error::RuntimeError(
                    "Cannot fetch Finals 2000A from [{}]: file is empty.", latestFinals2000AUrl.toString()
                );
            }
        }

        latestFinals2000AFile.moveToDirectory(destinationDirectory);

        temporaryDirectory.remove();

        this->unlockLocalRepository_();

        std::cout << String::Format(
                         "Finals 2000A [{}] has been successfully fetched from [{}].",
                         latestFinals2000AFile.toString(),
                         latestFinals2000AUrl.toString()
                     )
                  << std::endl;
    }
    catch (const ostk::core::error::Exception& anException)
    {
        std::cerr << String::Format(
                         "Error caught while fetching latest Finals 2000A from [{}]: [{}].",
                         latestFinals2000AUrl.toString(),
                         anException.what()
                     )
                  << std::endl;

        if (latestFinals2000AFile.isDefined() && latestFinals2000AFile.exists())
        {
            latestFinals2000AFile.remove();
            latestFinals2000AFile = File::Undefined();
        }

        if (temporaryDirectory.isDefined() && temporaryDirectory.exists())
        {
            temporaryDirectory.remove();
        }

        this->unlockLocalRepository_();

        throw;
    }

    return latestFinals2000AFile;
}

}  // namespace iers
}  // namespace provider
}  // namespace frame
}  // namespace coord
}  // namespace physics
}  // namespace ostk
