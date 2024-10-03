/// Apache License 2.0

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <numeric>

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Container/Dictionary.hpp>
#include <OpenSpaceToolkit/Core/Container/Object.hpp>
#include <OpenSpaceToolkit/Core/Container/Pair.hpp>
#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Type/Index.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/IO/IP/TCP/HTTP/Client.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Ephemeris/SPICE/Manager.hpp>

#include <experimental/filesystem>

namespace ostk
{
namespace physics
{
namespace environment
{
namespace ephemeris
{
namespace spice
{

using ostk::core::type::String;

using ostk::io::ip::tcp::http::Client;
using ostk::io::URL;

const String temporaryDirectoryName = "tmp";

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

    setup();
}

Directory Manager::DefaultLocalRepository()
{
    static const Directory defaultLocalRepository =
        Directory::Path(Path::Parse(OSTK_PHYSICS_ENVIRONMENT_EPHEMERIS_SPICE_MANAGER_LOCAL_REPOSITORY));

    if (const char* localRepositoryPath =
            std::getenv("OSTK_PHYSICS_ENVIRONMENT_EPHEMERIS_SPICE_MANAGER_LOCAL_REPOSITORY"))
    {
        return Directory::Path(Path::Parse(localRepositoryPath));
    }
    else if (const char* dataPath = std::getenv("OSTK_PHYSICS_DATA_LOCAL_REPOSITORY"))
    {
        return Directory::Path(Path::Parse(dataPath) + Path::Parse("environment/ephemeris/spice"));
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

    const Array<URL> kernelFileUrls = manifestManager.getRemoteDataUrls(aKernel.getName());

    // Only one remote file for each kernel
    const URL kernelFileUrl = kernelFileUrls.accessFirst();

    std::cout << String::Format(
                     "Fetching SPICE Kernel [{}] from [{}]...", kernelFile.toString(), kernelFileUrl.toString()
                 )
              << std::endl;

    File fetchedKernelFile = Client::Fetch(kernelFileUrl, localRepository_, 2);

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

    std::cout << String::Format(
                     "Successfully fetched SPICE Kernel [{}] from [{}]...",
                     kernelFile.toString(),
                     kernelFileUrl.toString()
                 )
              << std::endl;
}

Array<Kernel> Manager::fetchMatchingKernels(const String& aRegexString) const
{
    const std::lock_guard<std::mutex> lock {mutex_};

    ManifestManager& manifestManager = ManifestManager::Get();

    Array<Kernel> matchingKernels = Array<Kernel>::Empty();

    for (const auto& remoteUrl : manifestManager.findRemoteDataUrls(aRegexString))
    {
        std::cout << String::Format("Fetching SPICE Kernel from [{}]...", remoteUrl.toString()) << std::endl;

        File fetchedKernelFile = Client::Fetch(remoteUrl, localRepository_, 2);

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

        std::cout << String::Format(
                         "Successfully fetched SPICE Kernel [{}] from [{}]...",
                         fetchedKernelFile.toString(),
                         remoteUrl.toString()
                     )
                  << std::endl;

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
        Array<Kernel> fetchedKernels = const_cast<Manager*>(this)->fetchMatchingKernels(aRegexString);

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

void Manager::setup()
{
    if (!localRepository_.exists())
    {
        localRepository_.create();
    }
}

}  // namespace spice
}  // namespace ephemeris
}  // namespace environment
}  // namespace physics
}  // namespace ostk
