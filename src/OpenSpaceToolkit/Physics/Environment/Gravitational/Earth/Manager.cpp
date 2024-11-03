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

bool Manager::hasDataFilesForType(const EarthGravitationalModel::Type& aModelType) const
{
    const std::lock_guard<std::mutex> lock {mutex_};

    const String dataFileName = Manager::DataFileNameFromType_(aModelType);

    return (
        localRepository_.containsFileWithName(String::Format("{}.egm", dataFileName)) &&
        localRepository_.containsFileWithName(String::Format("{}.egm.cof", dataFileName))
    );
}

Array<File> Manager::localDataFilesForType(const EarthGravitationalModel::Type& aModelType) const
{
    const std::lock_guard<std::mutex> lock {mutex_};

    const String dataFileName = Manager::DataFileNameFromType_(aModelType);

    return {
        File::Path(localRepository_.getPath() + Path::Parse(String::Format("{}.egm", dataFileName))),
        File::Path(localRepository_.getPath() + Path::Parse(String::Format("{}.egm.cof", dataFileName)))
    };
}

void Manager::fetchDataFilesForType(const EarthGravitationalModel::Type& aModelType) const
{
    using ostk::core::type::Index;
    using ostk::core::type::Size;

    using ostk::io::ip::tcp::http::Client;

    if (this->hasDataFilesForType(aModelType))
    {
        throw ostk::core::error::RuntimeError(
            "Cannot fetch data file for type [{}]: files already exist in [{}].",
            DataFileNameFromType_(aModelType),
            localRepository_.toString()
        );
    }

    const_cast<Manager*>(this)->lockLocalRepository_(localRepositoryLockTimeout_);

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

    const Array<URL> remoteUrls = this->getDataFileUrlsForType_(aModelType);

    URL remoteDataUrl = URL::Undefined();
    File gravityDataFile = File::Undefined();

    try
    {
        for (const auto& url : remoteUrls)
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
                std::filesystem::file_size(std::string(gravityDataFile.getPath().toString()));

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

        const_cast<Manager*>(this)->unlockLocalRepository_();
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

        const_cast<Manager*>(this)->unlockLocalRepository_();

        throw;
    }
}

Manager& Manager::Get()
{
    static Manager manager;

    return manager;
}

Manager::Manager()
    : BaseManager(
          "OSTK_PHYSICS_ENVIRONMENT_GRAVITATIONAL_EARTH_MANAGER_MODE",
          Directory::Path(Path::Parse(OSTK_PHYSICS_ENVIRONMENT_GRAVITATIONAL_EARTH_MANAGER_LOCAL_REPOSITORY)),
          "OSTK_PHYSICS_ENVIRONMENT_GRAVITATIONAL_EARTH_MANAGER_LOCAL_REPOSITORY",
          Path::Parse("environment/gravitational/earth"),
          "OSTK_PHYSICS_ENVIRONMENT_GRAVITATIONAL_EARTH_MANAGER_LOCAL_REPOSITORY_LOCK_TIMEOUT"
      )
{
}

Array<URL> Manager::getDataFileUrlsForType_(const EarthGravitationalModel::Type& aModelType) const
{
    ManifestManager& manifestManager = ManifestManager::Get();

    const std::string dataFileName = static_cast<std::string>(Manager::DataFileNameFromType_(aModelType));

    std::string dataFileNameUpper = dataFileName;
    transform(dataFileName.begin(), dataFileName.end(), dataFileNameUpper.begin(), ::toupper);

    const String manifestKey = static_cast<std::string>("earth-gravity-" + dataFileNameUpper);

    return manifestManager.getRemoteDataUrls(manifestKey);
}

String Manager::DataFileNameFromType_(const EarthGravitationalModel::Type& aModelType)
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
