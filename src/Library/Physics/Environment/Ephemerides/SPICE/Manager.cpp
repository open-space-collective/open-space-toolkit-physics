////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Environment/Ephemerides/SPICE/Manager.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Environment/Ephemerides/SPICE/Manager.hpp>

#include <Library/IO/IP/TCP/HTTP/Client.hpp>

#include <Library/Core/Containers/Object.hpp>
#include <Library/Core/Containers/Dictionary.hpp>
#include <Library/Core/Containers/Array.hpp>
#include <Library/Core/Containers/Pair.hpp>
#include <Library/Core/Types/Index.hpp>
#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

#include <fstream>
#include <numeric>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{
namespace env
{
namespace ephem
{
namespace spice
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Directory                       Manager::getLocalRepository                 ( ) const
{

    const std::lock_guard<std::mutex> lock { mutex_ } ;

    return localRepository_ ;

}

URL                             Manager::getRemoteUrl                       ( ) const
{

    const std::lock_guard<std::mutex> lock { mutex_ } ;

    return remoteUrl_ ;

}

void                            Manager::fetchKernel                        (   const   Kernel&                     aKernel                                     ) const
{

    using library::io::ip::tcp::http::Client ;

    const std::lock_guard<std::mutex> lock { mutex_ } ;

    if (!aKernel.isDefined())
    {
        throw library::core::error::runtime::Undefined("Kernel") ;
    }

    const File kernelFile = aKernel.getFile() ;

    if (kernelFile.exists())
    {
        throw library::core::error::RuntimeError("Kernel file [{}] already exists.", kernelFile.toString()) ;
    }

    const_cast<Manager*>(this)->updateIndex() ;

    const URL remoteUrl = index_.getRemoteUrlOfKernel(aKernel) ;

    const File fetchedKernelFile = Client::Fetch(remoteUrl, localRepository_) ;

    // [TBI] Add file size verification

    if (!fetchedKernelFile.exists())
    {
        throw library::core::error::RuntimeError("Cannot fetch kernel file [{}] at [{}].", fetchedKernelFile.toString(), remoteUrl.toString()) ;
    }

}

Array<Kernel>                   Manager::fetchMatchingKernels               (   const   std::regex&                 aRegex                                      ) const
{

    using library::io::ip::tcp::http::Client ;

    const std::lock_guard<std::mutex> lock { mutex_ } ;

    const auto fetch = [&] () -> Array<Kernel>
    {

        const_cast<Manager*>(this)->updateIndex() ;

        Array<Kernel> matchingKernels = Array<Kernel>::Empty() ;

        for (const auto& remoteUrl : index_.findRemoteUrls(aRegex))
        {

            const File fetchedKernelFile = Client::Fetch(remoteUrl, localRepository_) ;

            const Kernel fetchedKernel = { Kernel::TypeFromFileExtension(fetchedKernelFile.getExtension()), fetchedKernelFile } ;

            matchingKernels.add(fetchedKernel) ;

        }

        return matchingKernels ;

    } ;

    // [TBM] This is a quick hack, should be improved

    try
    {
        return fetch() ;
    }
    catch (const library::core::error::Exception& anException)
    {
        
        const_cast<Manager*>(this)->flushIndex() ;
    
        const_cast<Manager*>(this)->updateIndex() ;

    }

    return fetch() ;

}

void                            Manager::setLocalRepository                 (   const   Directory&                  aDirectory                                  )
{

    if (!aDirectory.isDefined())
    {
        throw library::core::error::runtime::Undefined("Directory") ;
    }

    const std::lock_guard<std::mutex> lock { mutex_ } ;

    localRepository_ = aDirectory ;

}

void                            Manager::setRemoteUrl                       (   const   URL&                        aRemoteUrl                                  )
{

    if (!aRemoteUrl.isDefined())
    {
        throw library::core::error::runtime::Undefined("Remote URL") ;
    }

    const std::lock_guard<std::mutex> lock { mutex_ } ;

    remoteUrl_ = aRemoteUrl ;

}

void                            Manager::refresh                            ( )
{

    const std::lock_guard<std::mutex> lock { mutex_ } ;

    this->flushIndex() ;
    
    this->updateIndex() ;

}

Manager&                        Manager::Get                                ( )
{

    static Manager manager ;

    return manager ;

}

Directory                       Manager::DefaultLocalRepository             ( )
{
    return Directory::Path(Path::Parse("/var/library-physics/environment/ephemerides/spice")) ;
}

URL                             Manager::DefaultRemoteUrl                   ( )
{
    return URL::Parse("https://naif.jpl.nasa.gov/pub/naif/generic_kernels/") ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Manager::Manager                            ( )
                                :   localRepository_(Manager::DefaultLocalRepository()),
                                    remoteUrl_(Manager::DefaultRemoteUrl()),
                                    indexFile_(File::Path(localRepository_.getPath() + Path::Parse("./index.json"))),
                                    index_(Index::Empty())
{

    if (!localRepository_.exists())
    {
        localRepository_.create() ;
    }

    this->updateIndex() ;
    
}

void                            Manager::updateIndex                        ( )
{

    if (!indexFile_.exists())
    {

        this->fetchIndexAt(remoteUrl_) ;

    }

    if (index_.isEmpty())
    {
        
        if (!indexFile_.exists())
        {
            throw library::core::error::RuntimeError("Index file [{}] does not exist.", remoteUrl_.toString()) ;
        }

        index_ = Index::Load(indexFile_) ;

    }

    // [TBI] Implement index file cache timeout (using index_.getTimestamp())

}

void                            Manager::fetchIndexAt                       (   const   URL&                        aUrl                                        )
{

    using library::core::types::Index ;
    using library::core::ctnr::Pair ;
    using library::core::ctnr::Array ;
    using library::core::ctnr::Dictionary ;
    using library::core::ctnr::Object ;

    using library::io::ip::tcp::http::Client ;

    if (!aUrl.isDefined())
    {
        throw library::core::error::runtime::Undefined("URL") ;
    }

    Dictionary fileListingDictionary = Dictionary::Empty() ;

    Directory temporaryDirectory = Directory::Path(localRepository_.getPath() + Path::Parse("tmp")) ;

    if (!temporaryDirectory.exists())
    {
        temporaryDirectory.create() ;
    }
    
    // Group by kernel type

    const std::function<void (const URL&, const Index&)> fetchListing = [&temporaryDirectory, &fetchListing, &fileListingDictionary] (const URL& aListingUrl, const Index& aDepth)
    {

        File listingFile = File::Path(temporaryDirectory.getPath() + Path::Parse(String::Format("listing-{}.txt", aDepth))) ;

        if (listingFile.exists())
        {
            listingFile.remove() ;
        }

        URL ftpListingUrl = aListingUrl ; // [TBR]

        ftpListingUrl.setScheme("ftp") ;

        Client::List(ftpListingUrl, listingFile, false) ;

        std::ifstream listingFileStream { listingFile.getPath().toString() } ;

        String listingLine ;

        while (std::getline(listingFileStream, listingLine))
        {

            // <a href="[/w+]">

            // Split spaces into tokens

            std::istringstream iss { listingLine } ;

            std::vector<std::string> tokens { std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{} } ;

            if (tokens.size() >= 9)
            {

                // Recombine tokens into filename

                const String fileName = std::accumulate(tokens.begin() + 8, tokens.end(), std::string("")) ;

                if (listingLine.getHead(1) == "d") // Directory
                {

                    if (listingLine.find("old_versions") == std::string::npos)
                    {

                        const URL childListingUrl = aListingUrl + (fileName + "/") ;

                        fetchListing(childListingUrl, aDepth + 1) ;

                    }

                }
                else // File
                {

                    const File kernelFile = File::Path(Path::Parse(fileName)) ;

                    const String kernelFileExtension = kernelFile.getExtension() ;

                    if (!kernelFileExtension.isEmpty())
                    {

                        const Kernel::Type kernelType = Kernel::TypeFromFileExtension(kernelFileExtension) ;

                        if (kernelType != Kernel::Type::Undefined)
                        {
                            
                            // fileListing.add(Pair<String, String> { aListingUrl.toString(), fileName }) ;

                            fileListingDictionary[Kernel::StringFromType(kernelType)][fileName] = Object::String(aListingUrl.toString()) ;

                        }

                    }                    

                }

            }
            
        }

        if (listingFile.exists())
        {
            listingFile.remove() ;
        }

    } ;

    try
    {
        
        fetchListing(aUrl, 0) ;

    }
    catch (const library::core::error::RuntimeError& anException)
    {
        throw library::core::error::RuntimeError("Error when fetching index at [{}]: [{}].", aUrl.toString(), anException.what()) ;
    }

    File remoteIndexFile = indexFile_ ;

    remoteIndexFile.create() ;
    
    remoteIndexFile.open(File::OpenMode::Truncate) ;

    remoteIndexFile << Object::Dictionary(fileListingDictionary) ;

    remoteIndexFile.close() ;

    temporaryDirectory.remove() ;

}

void                            Manager::flushIndex                         ( )
{

    index_ = Index::Empty() ;

    if (indexFile_.exists())
    {

        File(indexFile_).remove() ;

        if (indexFile_.exists())
        {
            throw library::core::error::RuntimeError("Cannot flush index at [{}].", indexFile_.toString()) ;
        }
        
    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////