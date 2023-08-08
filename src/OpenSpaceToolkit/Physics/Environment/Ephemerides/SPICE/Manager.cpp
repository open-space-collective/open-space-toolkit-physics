/// Apache License 2.0

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <numeric>

#include <OpenSpaceToolkit/Core/Containers/Array.hpp>
#include <OpenSpaceToolkit/Core/Containers/Dictionary.hpp>
#include <OpenSpaceToolkit/Core/Containers/Object.hpp>
#include <OpenSpaceToolkit/Core/Containers/Pair.hpp>
#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Types/Index.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

#include <OpenSpaceToolkit/IO/IP/TCP/HTTP/Client.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Ephemerides/SPICE/Manager.hpp>

#include <experimental/filesystem>

namespace ostk
{
namespace physics
{
namespace env
{
namespace ephem
{
namespace spice
{

using ostk::core::types::String;

using ostk::io::URL;
using ostk::io::ip::tcp::http::Client;

const String temporaryDirectoryName = "tmp";

const String spiceFilesRemotePath = "environment/ephemerides/spice/";

Manager& Manager::Get()
{
    static Manager manager;

    return manager;
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
        Directory::Path(Path::Parse(OSTK_PHYSICS_ENVIRONMENT_EPHEMERIDES_SPICE_MANAGER_LOCAL_REPOSITORY));

    if (const char* localRepositoryPath =
            std::getenv("OSTK_PHYSICS_ENVIRONMENT_EPHEMERIDES_SPICE_MANAGER_LOCAL_REPOSITORY"))
    {
        return Directory::Path(Path::Parse(localRepositoryPath));
    }

    return defaultLocalRepository;
}

void Manager::fetchKernel(const Kernel& aKernel) const
{
    const std::lock_guard<std::mutex> lock {mutex_};

    if (!aKernel.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Kernel");
    }

    const File kernelFile = aKernel.getFile();

    if (kernelFile.exists())
    {
        throw ostk::core::error::RuntimeError("Kernel file [{}] already exists.", kernelFile.toString());
    }

    ManifestManager& manifestManager = ManifestManager::Get();
    const URL kernelFileUrl = manifestManager.getRemoteUrl() + spiceFilesRemotePath + aKernel.getName();

    File fetchedKernelFile = Client::Fetch(kernelFileUrl, localRepository_);

    if (!fetchedKernelFile.exists())
    {
        throw ostk::core::error::RuntimeError(
            "Cannot fetch kernel file [{}] at [{}].", fetchedKernelFile.toString(), kernelFileUrl.toString()
        );
    }

    // Check that file size is not zero

    std::uintmax_t fetchedKernelFileSize =
        std::experimental::filesystem::file_size(std::string(fetchedKernelFile.getPath().toString()));

    if (fetchedKernelFileSize == 0)
    {
        fetchedKernelFile.remove();

        throw ostk::core::error::RuntimeError(
            "Cannot fetch kernel from [{}]: file is empty.", kernelFileUrl.toString()
        );
    }
}

Array<Kernel> Manager::fetchMatchingKernels(const std::regex& aRegex) const
{
    const std::lock_guard<std::mutex> lock {mutex_};

    ManifestManager& manifestManager = ManifestManager::Get();

    Array<Kernel> matchingKernels = Array<Kernel>::Empty();

    for (const auto& remoteUrl : manifestManager.findRemoteDataUrls(aRegex))
    {
        File fetchedKernelFile = Client::Fetch(remoteUrl, localRepository_);

        if (!fetchedKernelFile.exists())
        {
            throw ostk::core::error::RuntimeError(
                "Cannot fetch kernel file [{}] at [{}].", fetchedKernelFile.toString(), remoteUrl.toString()
            );
        }
        else
        {
            // Check that file size is not zero

            std::uintmax_t fetchedKernelFileSize =
                std::experimental::filesystem::file_size(std::string(fetchedKernelFile.getPath().toString()));

            if (fetchedKernelFileSize == 0)
            {
                fetchedKernelFile.remove();

                throw ostk::core::error::RuntimeError(
                    "Cannot fetch kernel from [{}]: file is empty.", remoteUrl.toString()
                );
            }
        }

        const Kernel fetchedKernel = {
            Kernel::TypeFromFileExtension(fetchedKernelFile.getExtension()), fetchedKernelFile
        };

        matchingKernels.add(fetchedKernel);
    }

    return matchingKernels;
}

Kernel Manager::findKernel(const String& aRegexString) const
{
    using iterator = std::filesystem::directory_iterator;

    const std::regex aRegex {aRegexString};

    Array<Path> kernelPaths;

    // Try to find kernel in local repository
    std::filesystem::path directory = std::string(localRepository_.getPath().toString());

    const iterator end;
    for (iterator iter {directory}; iter != end; ++iter)
    {
        const String filename = iter->path().filename().string();
        if (std::filesystem::is_regular_file(*iter) && std::regex_match(filename, aRegex))
        {
            kernelPaths.add(Path::Parse(iter->path().string()));
        }
    }

    // If none found, fall back to fetching from remote
    if (kernelPaths.isEmpty())
    {
        Array<Kernel> fetchedKernels = const_cast<Manager*>(this)->fetchMatchingKernels(aRegex);

        if (fetchedKernels.isEmpty())
        {
            throw ostk::core::error::RuntimeError("Failed to find or fetch SPICE Kernel matching [{}].", aRegexString);
        }

        return fetchedKernels.accessFirst();
    }

    return Kernel::File(File::Path(kernelPaths.accessFirst()));
}

Manager::Manager()
    : localRepository_(Manager::DefaultLocalRepository())
{
}

}  // namespace spice
}  // namespace ephem
}  // namespace env
}  // namespace physics
}  // namespace ostk
