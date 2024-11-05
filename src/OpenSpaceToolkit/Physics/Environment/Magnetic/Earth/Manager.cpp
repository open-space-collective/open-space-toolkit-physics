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

bool Manager::hasDataFilesForType(const EarthMagneticModel::Type& aModelType) const
{
    const std::lock_guard<std::mutex> lock {mutex_};

    const String dataFileName = Manager::DataFileNameFromType_(aModelType);

    return (
        localRepository_.containsFileWithName(String::Format("{}.wmm", dataFileName)) &&
        localRepository_.containsFileWithName(String::Format("{}.wmm.cof", dataFileName))
    );
}

Array<File> Manager::localDataFilesForType(const EarthMagneticModel::Type& aModelType) const
{
    const std::lock_guard<std::mutex> lock {mutex_};

    const String dataFileName = Manager::DataFileNameFromType_(aModelType);

    return {
        File::Path(localRepository_.getPath() + Path::Parse(String::Format("{}.wmm", dataFileName))),
        File::Path(localRepository_.getPath() + Path::Parse(String::Format("{}.wmm.cof", dataFileName)))
    };
}

void Manager::fetchDataFilesForType(const EarthMagneticModel::Type& aModelType) const
{
    using ostk::core::type::Index;
    using ostk::core::type::Size;

    using ostk::io::ip::tcp::http::Client;

    if (this->hasDataFilesForType(aModelType))
    {
        throw ostk::core::error::RuntimeError(
            "Cannot fetch data file for type [{}]: files already exist.", DataFileNameFromType_(aModelType)
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
                std::filesystem::file_size(std::string(magneticDataFile.getPath().toString()));

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

        const_cast<Manager*>(this)->unlockLocalRepository_();
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
          "OSTK_PHYSICS_ENVIRONMENT_MAGNETIC_EARTH_MANAGER_MODE",
          Directory::Path(Path::Parse(OSTK_PHYSICS_ENVIRONMENT_MAGNETIC_EARTH_MANAGER_LOCAL_REPOSITORY)),
          "OSTK_PHYSICS_ENVIRONMENT_MAGNETIC_EARTH_MANAGER_LOCAL_REPOSITORY",
          Path::Parse("environment/magnetic/earth"),
          "OSTK_PHYSICS_ENVIRONMENT_MAGNETIC_EARTH_MANAGER_LOCAL_REPOSITORY_LOCK_TIMEOUT"
      )
{
}

Array<URL> Manager::getDataFileUrlsForType_(const EarthMagneticModel::Type& aModelType) const
{
    ManifestManager& manifestManager = ManifestManager::Get();

    const std::string dataFileName = static_cast<std::string>(Manager::DataFileNameFromType_(aModelType));

    std::string dataFileNameUpper = dataFileName;
    transform(dataFileName.begin(), dataFileName.end(), dataFileNameUpper.begin(), ::toupper);

    const String manifestKey = static_cast<std::string>("earth-magnetic-" + dataFileNameUpper);

    return manifestManager.getRemoteDataUrls(manifestKey);
}

String Manager::DataFileNameFromType_(const EarthMagneticModel::Type& aModelType)
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
