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

namespace ostk
{
namespace physics
{
namespace coordinate
{
namespace frame
{
namespace provider
{
namespace iers
{

using ostk::core::filesystem::Directory;
using ostk::core::filesystem::Path;
using ostk::core::type::String;

using ostk::io::ip::tcp::http::Client;
using ostk::io::URL;

using ManifestManager = ostk::physics::data::Manager;

const String bulletinAFileName = "ser7.dat";
const String finals2000AFileName = "finals2000A.data";

const String bulletinAManifestName = "bulletin-A";
const String finals2000AManifestName = "finals-2000A";

const String temporaryDirectoryName = "tmp";

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
    BaseManager::reset();

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

Manager::Manager()
    : BaseManager(
          "OSTK_PHYSICS_COORDINATE_FRAME_PROVIDER_IERS_MANAGER_MODE",
          Directory::Path(Path::Parse(OSTK_PHYSICS_COORDINATE_FRAME_PROVIDER_IERS_MANAGER_LOCAL_REPOSITORY)),
          "OSTK_PHYSICS_COORDINATE_FRAME_PROVIDER_IERS_MANAGER_LOCAL_REPOSITORY",
          Path::Parse("coordinate/frame/provider/iers"),
          "OSTK_PHYSICS_COORDINATE_FRAME_PROVIDER_IERS_MANAGER_LOCAL_REPOSITORY_LOCK_TIMEOUT"
      ),
      bulletinA_(BulletinA::Undefined()),
      finals2000A_(Finals2000A::Undefined())
{
    this->setup_();
}

void Manager::setup_()
{
    BaseManager::setup_();

    if (!this->getBulletinADirectory().exists())
    {
        this->getBulletinADirectory().create();
    }

    if (!this->getFinals2000ADirectory().exists())
    {
        this->getFinals2000ADirectory().create();
    }
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
    switch (mode_)
    {
        case Manager::Mode::Automatic:
        {
            // Try from file
            File localBulletinAFile = File::Undefined();

            if (this->getBulletinADirectory().containsFileWithName(bulletinAFileName))
            {
                localBulletinAFile =
                    File::Path(this->getBulletinADirectory().getPath() + Path::Parse(bulletinAFileName));

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

        case Manager::Mode::Manual:
        {
            if (!this->getBulletinADirectory().containsFileWithName(bulletinAFileName))
            {
                return nullptr;
            }

            const File localBulletinAFile =
                File::Path(this->getBulletinADirectory().getPath() + Path::Parse(bulletinAFileName));

            this->loadBulletinA_(BulletinA::Load(localBulletinAFile));

            return &bulletinA_;
        }

        default:
            return nullptr;
    }

    // No bulletin A found and unable to fetch
    return nullptr;
}

const Finals2000A* Manager::accessFinals2000A_() const
{
    // If we've loaded a file, simply return it
    if (finals2000A_.isDefined())
    {
        return &finals2000A_;
    }

    // If set to automatic, try to load or fetch the latest file
    switch (mode_)
    {
        case Manager::Mode::Automatic:
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
        case Manager::Mode::Manual:
        {
            if (!this->getFinals2000ADirectory().containsFileWithName(finals2000AFileName))
            {
                return nullptr;
            }

            const File localFinals2000AFile =
                File::Path(this->getFinals2000ADirectory().getPath() + Path::Parse(finals2000AFileName));

            const Finals2000A finals2000A = Finals2000A::Load(localFinals2000AFile);

            this->loadFinals2000A_(finals2000A);

            return &finals2000A_;
        }
        default:
            return nullptr;
    }

    // No finals 2000A found and unable to fetch
    return nullptr;
}

File Manager::fetchLatestBulletinA_() const
{
    std::cout << "Fetching latest Bulletin A..." << std::endl;

    ManifestManager& manifestManager = ManifestManager::Get();

    Directory temporaryDirectory =
        Directory::Path(this->getBulletinADirectory().getPath() + Path::Parse(temporaryDirectoryName));

    this->lockLocalRepository_(localRepositoryLockTimeout_);

    const Array<URL> bulletinAUrls = manifestManager.getRemoteDataUrls(bulletinAManifestName);

    // Only one remote file for Bulletin A
    const URL bulletinAUrl = bulletinAUrls.accessFirst();

    File latestBulletinAFile = File::Undefined();
    Directory destinationDirectory = Directory::Undefined();

    try
    {
        // Create temporary Directory,
        // e.g., `.open-space-toolkit/physics/coordinate/frame/provider/iers/bulletin-a/tmp/`.

        if (temporaryDirectory.exists())
        {
            throw ostk::core::error::RuntimeError(
                "Temporary directory [{}] already exists.", temporaryDirectory.toString()
            );
        }

        std::cout << String::Format("Creating temporary directory [{}]...", temporaryDirectory.toString()) << std::endl;

        temporaryDirectory.create();

        // Download latest Bulletin A File into temporary Directory

        std::cout << String::Format("Fetching Bulletin A from [{}]...", bulletinAUrl.toString()) << std::endl;

        latestBulletinAFile = Client::Fetch(bulletinAUrl, temporaryDirectory, 2);

        if (!latestBulletinAFile.exists())
        {
            throw ostk::core::error::RuntimeError("Cannot fetch Bulletin A from [{}].", bulletinAUrl.toString());
        }

        // Check that Bulletin A File size is not zero

        std::uintmax_t latestBulletinAFileSize =
            std::filesystem::file_size(std::string(latestBulletinAFile.getPath().toString()));

        if (latestBulletinAFileSize == 0)
        {
            throw ostk::core::error::RuntimeError(
                "Cannot fetch Bulletin A from [{}]: file is empty.", bulletinAUrl.toString()
            );
        }

        // Move Bulletin A File into destination Directory,
        // e.g., `.open-space-toolkit/physics/coordinate/frame/provider/iers/bulletin-A/`.

        destinationDirectory = Directory::Path(this->getBulletinADirectory().getPath());

        latestBulletinAFile.moveToDirectory(destinationDirectory);

        temporaryDirectory.remove();

        this->unlockLocalRepository_();

        std::cout << String::Format(
                         "Bulletin A [{}] has been successfully fetched from [{}].",
                         latestBulletinAFile.toString(),
                         bulletinAUrl.toString()
                     )
                  << std::endl;
    }
    catch (const ostk::core::error::Exception& anException)
    {
        std::cerr << String::Format(
                         "Error caught while fetching latest Bulletin A from [{}]: [{}].",
                         bulletinAUrl.toString(),
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

    const Array<URL> finals2000AUrls = manifestManager.getRemoteDataUrls(finals2000AManifestName);

    // Only one remote file for Finals 2000 A
    const URL finals2000AUrl = finals2000AUrls.accessFirst();

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

        std::cout << String::Format("Fetching Finals 2000A from [{}]...", finals2000AUrl.toString()) << std::endl;

        latestFinals2000AFile = Client::Fetch(finals2000AUrl, temporaryDirectory, 2);

        const Finals2000A latestFinals2000A = Finals2000A::Load(latestFinals2000AFile);

        if (!latestFinals2000AFile.exists())
        {
            throw ostk::core::error::RuntimeError(
                "Cannot fetch Finals 2000A [{}] from [{}].", latestFinals2000AFile.toString(), finals2000AUrl.toString()
            );
        }
        else
        {
            // Check that file size is not zero

            std::uintmax_t latestFinals2000AFileSize =
                std::filesystem::file_size(std::string(latestFinals2000AFile.getPath().toString()));

            if (latestFinals2000AFileSize == 0)
            {
                throw ostk::core::error::RuntimeError(
                    "Cannot fetch Finals 2000A from [{}]: file is empty.", finals2000AUrl.toString()
                );
            }
        }

        latestFinals2000AFile.moveToDirectory(destinationDirectory);

        temporaryDirectory.remove();

        this->unlockLocalRepository_();

        std::cout << String::Format(
                         "Finals 2000A [{}] has been successfully fetched from [{}].",
                         latestFinals2000AFile.toString(),
                         finals2000AUrl.toString()
                     )
                  << std::endl;
    }
    catch (const ostk::core::error::Exception& anException)
    {
        std::cerr << String::Format(
                         "Error caught while fetching latest Finals 2000A from [{}]: [{}].",
                         finals2000AUrl.toString(),
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
}  // namespace coordinate
}  // namespace physics
}  // namespace ostk
