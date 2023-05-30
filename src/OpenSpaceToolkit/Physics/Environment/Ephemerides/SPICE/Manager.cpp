/// Apache License 2.0

#include <cstdlib>
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

const String temporaryDirectoryName = "tmp";

Directory Manager::getLocalRepository() const
{
    const std::lock_guard<std::mutex> lock {mutex_};

    return localRepository_;
}

URL Manager::getRemoteUrl() const
{
    const std::lock_guard<std::mutex> lock {mutex_};

    return remoteUrl_;
}

File Manager::getIndexFile() const
{
    const std::lock_guard<std::mutex> lock {mutex_};

    return this->getIndexFile_();
}

void Manager::fetchKernel(const Kernel& aKernel) const
{
    using ostk::io::ip::tcp::http::Client;

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

    const_cast<Manager*>(this)->updateIndex();

    const URL kernelFileUrl = index_.getRemoteUrlOfKernel(aKernel);

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
    using ostk::io::ip::tcp::http::Client;

    const std::lock_guard<std::mutex> lock {mutex_};

    const auto fetch = [&]() -> Array<Kernel>
    {
        const_cast<Manager*>(this)->updateIndex();

        Array<Kernel> matchingKernels = Array<Kernel>::Empty();

        for (const auto& remoteUrl : index_.findRemoteUrls(aRegex))
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
                Kernel::TypeFromFileExtension(fetchedKernelFile.getExtension()), fetchedKernelFile};

            matchingKernels.add(fetchedKernel);
        }

        return matchingKernels;
    };

    // [TBM] This is a quick hack, should be improved

    try
    {
        return fetch();
    }
    catch (const ostk::core::error::Exception& anException)
    {
        const_cast<Manager*>(this)->flushIndex();

        const_cast<Manager*>(this)->updateIndex();
    }

    return fetch();
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

void Manager::setRemoteUrl(const URL& aRemoteUrl)
{
    if (!aRemoteUrl.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Remote URL");
    }

    const std::lock_guard<std::mutex> lock {mutex_};

    remoteUrl_ = aRemoteUrl;
}

void Manager::refresh()
{
    const std::lock_guard<std::mutex> lock {mutex_};

    this->flushIndex();

    this->updateIndex();
}

Manager& Manager::Get()
{
    static Manager manager;

    return manager;
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

URL Manager::DefaultRemoteUrl()
{
    static const URL defaultRemoteUrl = URL::Parse(OSTK_PHYSICS_ENVIRONMENT_EPHEMERIDES_SPICE_MANAGER_REMOTE_URL);

    if (const char* remoteUrl = std::getenv("OSTK_PHYSICS_ENVIRONMENT_EPHEMERIDES_SPICE_MANAGER_REMOTE_URL"))
    {
        return URL::Parse(remoteUrl);
    }

    return defaultRemoteUrl;
}

Manager::Manager()
    : localRepository_(Manager::DefaultLocalRepository()),
      remoteUrl_(Manager::DefaultRemoteUrl()),
      index_(Index::Empty())
{
}

File Manager::getIndexFile_() const
{
    return File::Path(localRepository_.getPath() + Path::Parse("./spice_index.json"));
}

void Manager::updateIndex()
{
    if (!localRepository_.exists())
    {
        localRepository_.create();
    }

    const File indexFile = this->getIndexFile_();

    if (!indexFile.exists())
    {
        this->fetchIndexAt(remoteUrl_);
    }

    if (index_.isEmpty())
    {
        if (!indexFile.exists())
        {
            throw ostk::core::error::RuntimeError("Index file [{}] does not exist.", remoteUrl_.toString());
        }

        index_ = Index::Load(indexFile);
    }

    // [TBI] Implement index file cache timeout (using index_.getTimestamp())
}

void Manager::fetchIndexAt(const URL& aUrl)
{
    using ostk::core::types::Index;
    using ostk::core::ctnr::Pair;
    using ostk::core::ctnr::Array;
    using ostk::core::ctnr::Dictionary;
    using ostk::core::ctnr::Object;

    using ostk::io::ip::tcp::http::Client;

    if (!aUrl.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("URL");
    }

    Dictionary fileListingDictionary = Dictionary::Empty();

    Directory temporaryDirectory = Directory::Path(localRepository_.getPath() + Path::Parse(temporaryDirectoryName));

    if (!temporaryDirectory.exists())
    {
        temporaryDirectory.create();
    }

    // Group by kernel type

    const std::function<void(const URL&, const Index&)> fetchListing =
        [&temporaryDirectory, &fetchListing, &fileListingDictionary](const URL& aListingUrl, const Index& aDepth)
    {
        File listingFile =
            File::Path(temporaryDirectory.getPath() + Path::Parse(String::Format("listing-{}.txt", aDepth)));

        if (listingFile.exists())
        {
            listingFile.remove();
        }

        URL ftpListingUrl = aListingUrl;  // [TBR]

        ftpListingUrl.setScheme("ftp");

        Client::List(ftpListingUrl, listingFile, false);

        std::ifstream listingFileStream {listingFile.getPath().toString()};

        String listingLine;

        while (std::getline(listingFileStream, listingLine))
        {
            // <a href="[/w+]">

            // Split spaces into tokens

            std::istringstream iss {listingLine};

            std::vector<std::string> tokens {
                std::istream_iterator<std::string> {iss}, std::istream_iterator<std::string> {}};

            if (tokens.size() >= 9)
            {
                // Recombine tokens into filename

                const String fileName = std::accumulate(tokens.begin() + 8, tokens.end(), std::string(""));

                if (listingLine.getHead(1) == "d")  // Directory
                {
                    if (listingLine.find("old_versions") == std::string::npos)
                    {
                        const URL childListingUrl = aListingUrl + (fileName + "/");

                        fetchListing(childListingUrl, aDepth + 1);
                    }
                }
                else  // File
                {
                    const File kernelFile = File::Path(Path::Parse(fileName));

                    const String kernelFileExtension = kernelFile.getExtension();

                    if (!kernelFileExtension.isEmpty())
                    {
                        const Kernel::Type kernelType = Kernel::TypeFromFileExtension(kernelFileExtension);

                        if (kernelType != Kernel::Type::Undefined)
                        {
                            // fileListing.add(Pair<String, String> { aListingUrl.toString(), fileName }) ;

                            fileListingDictionary[Kernel::StringFromType(kernelType)][fileName] =
                                Object::String(aListingUrl.toString());
                        }
                    }
                }
            }
        }

        if (listingFile.exists())
        {
            listingFile.remove();
        }
    };

    try
    {
        fetchListing(aUrl, 0);
    }
    catch (const ostk::core::error::RuntimeError& anException)
    {
        throw ostk::core::error::RuntimeError(
            "Error when fetching index at [{}]: [{}].", aUrl.toString(), anException.what()
        );
    }

    File remoteIndexFile = this->getIndexFile_();

    remoteIndexFile.create();

    remoteIndexFile.open(File::OpenMode::Truncate);

    remoteIndexFile << Object::Dictionary(fileListingDictionary);

    remoteIndexFile.close();

    temporaryDirectory.remove();
}

void Manager::flushIndex()
{
    index_ = Index::Empty();

    File indexFile = this->getIndexFile_();

    if (indexFile.exists())
    {
        indexFile.remove();

        if (indexFile.exists())
        {
            throw ostk::core::error::RuntimeError("Cannot flush index at [{}].", indexFile.toString());
        }
    }
}

}  // namespace spice
}  // namespace ephem
}  // namespace env
}  // namespace physics
}  // namespace ostk

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
