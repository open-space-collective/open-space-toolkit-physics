////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/Manager.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/Manager.hpp>

#include <OpenSpaceToolkit/IO/IP/TCP/HTTP/Client.hpp>

#include <OpenSpaceToolkit/Core/Containers/Object.hpp>
#include <OpenSpaceToolkit/Core/Containers/Dictionary.hpp>
#include <OpenSpaceToolkit/Core/Containers/Array.hpp>
#include <OpenSpaceToolkit/Core/Containers/Pair.hpp>
#include <OpenSpaceToolkit/Core/Types/Index.hpp>
#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

#include <thread>
#include <chrono>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ostk
{
namespace physics
{
namespace environment
{
namespace atmospheric
{
namespace earth
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool                            Manager::isEnabled                          ( ) const
{

    const std::lock_guard<std::mutex> lock { mutex_ } ;

    return enabled_ ;

}

bool                            Manager::hasDataFileForType                 (   const   EarthAtmosphericModel::Type&   aModelType                                  ) const
{

    const std::lock_guard<std::mutex> lock { mutex_ } ;

    return localRepository_.containsFileWithName(String::Format("{}.wmm", Manager::DataFileNameFromType(aModelType))) ;

}

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

void                            Manager::fetchDataFileForType               (   const   EarthAtmosphericModel::Type&   aModelType                                  ) const
{

    using ostk::core::types::Index ;
    using ostk::core::types::Size ;

    using ostk::io::ip::tcp::http::Client ;

    const std::lock_guard<std::mutex> lock { mutex_ } ;

    // Lock file

    File lockFile = File::Path(localRepository_.getPath() + Path::Parse(".lock")) ;

    Index lockWaitIndex = 0 ;
    const Size lockWaitMaxCount = 60 ; // [TBM] Param

    while (lockFile.exists() && (lockWaitIndex < lockWaitMaxCount))
    {

        std::cout << String::Format("Lock file [{}] found: waiting [{}/{}]...", lockFile.toString(), lockWaitIndex, lockWaitMaxCount) << std::endl ;

        lockWaitIndex++ ;

        std::this_thread::sleep_for(std::chrono::seconds(1)) ;

    }

    if (!lockFile.exists())
    {
        lockFile.create() ;
    }
    else
    {
        throw ostk::core::error::RuntimeError("Cannot create lock file [{}].", lockFile.toString()) ;
    }

    try
    {

        // If file already in global cache, just clone it

        // static const Directory globalRepository = Directory::Path(Path::Parse("/usr/local/share/open-space-toolkit-physics/environment/atmospheric/earth")) ;

        // if (globalRepository.containsFileWithName(String::Format("{}.egm", Manager::DataFileNameFromType(aModelType))))
        // {

        // }

        // Download file (this is a simple version, using std::system and the wget command)

        File fetchedFile = File::Path(localRepository_.getPath() + Path::Parse(String::Format("{}.zip", Manager::DataFileNameFromType(aModelType)))) ;

        if (!fetchedFile.exists())
        {

            const URL remoteUrl = this->getDataFileUrlForType(aModelType) ;

            std::cout << String::Format("Fetching atmospheric data file from [{}]...", remoteUrl.toString()) << std::endl ;

            // const String fetchCommand = String::Format("curl --silent -L {} --output {} > /dev/null", remoteUrl.toString(), fetchedFile.getPath().toString()) ;
            const String fetchCommand = String::Format("wget --quiet --output-document {} {} > /dev/null", fetchedFile.getPath().toString(), remoteUrl.toString()) ;

            if (std::system(fetchCommand.data()) != 0)
            {
                throw ostk::core::error::RuntimeError("Cannot fetch file at [{}]: [{}].", remoteUrl.toString(), fetchCommand) ;
            }

        }

        // File fetchedFile = Client::Fetch(remoteUrl, localRepository_) ; // This does not work because of the redirects

        // if (!fetchedFile.exists())
        // {
        //     throw ostk::core::error::RuntimeError("Cannot fetch data file [{}] at [{}].", fetchedFile.toString(), remoteUrl.toString()) ;
        // }

        // [TBI] Add file size verification

        // Unzip file (this is a simple version, using std::system and the unzip command)

        const String unzipCommand = String::Format("unzip {} -d {} > /dev/null", fetchedFile.toString(), localRepository_.toString()) ;

        if (std::system(unzipCommand.data()) != 0)
        {
            throw ostk::core::error::RuntimeError("Cannot unzip file [{}]: [{}].", fetchedFile.toString(), unzipCommand) ;
        }

        const String moveCommand = String::Format("mv {} {} && rmdir {} > /dev/null", localRepository_.toString() + "/atmospheric/*", localRepository_.toString(), localRepository_.toString() + "/atmospheric") ;

        if (std::system(moveCommand.data()) != 0)
        {
            throw ostk::core::error::RuntimeError("Cannot move files: [{}].", moveCommand) ;
        }

        // Delete zip file

        fetchedFile.remove() ;

    }
    catch (...)
    {

        lockFile.remove() ;

        throw ;

    }

    lockFile.remove() ;

}

void                            Manager::setLocalRepository                 (   const   Directory&                  aDirectory                                  )
{

    if (!aDirectory.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Directory") ;
    }

    const std::lock_guard<std::mutex> lock { mutex_ } ;

    localRepository_ = aDirectory ;

}

void                            Manager::setRemoteUrl                       (   const   URL&                        aRemoteUrl                                  )
{

    if (!aRemoteUrl.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Remote URL") ;
    }

    const std::lock_guard<std::mutex> lock { mutex_ } ;

    remoteUrl_ = aRemoteUrl ;

}

void                            Manager::enable                             ( )
{

    const std::lock_guard<std::mutex> lock { mutex_ } ;

    enabled_ = true ;

}

void                            Manager::disable                            ( )
{

    const std::lock_guard<std::mutex> lock { mutex_ } ;

    enabled_ = false ;

}

void                            Manager::setEnabled                         (   const   bool                        aBoolean                                    )
{

    const std::lock_guard<std::mutex> lock { mutex_ } ;

    enabled_ = aBoolean ;

}

Manager&                        Manager::Get                                ( )
{

    static Manager manager ;

    return manager ;

}

bool                            Manager::DefaultEnabled                     ( )
{

    static const bool defaultEnabled = OSTK_PHYSICS_ENVIRONMENT_ATMOSPHERIC_EARTH_MANAGER_ENABLED ;

    if (const char* enabledString = std::getenv("OSTK_PHYSICS_ENVIRONMENT_ATMOSPHERIC_EARTH_MANAGER_ENABLED"))
    {
        return strcmp(enabledString, "true") == 0 ;
    }

    return defaultEnabled ;

}

Directory                       Manager::DefaultLocalRepository             ( )
{

    static const Directory defaultLocalRepository = Directory::Path(Path::Parse(OSTK_PHYSICS_ENVIRONMENT_ATMOSPHERIC_EARTH_MANAGER_LOCAL_REPOSITORY)) ;

    if (const char* localRepositoryPath = std::getenv("OSTK_PHYSICS_ENVIRONMENT_ATMOSPHERIC_EARTH_MANAGER_LOCAL_REPOSITORY"))
    {
        return Directory::Path(Path::Parse(localRepositoryPath)) ;
    }

    return defaultLocalRepository ;

}

URL                             Manager::DefaultRemoteUrl                   ( )
{

    static const URL defaultRemoteUrl = URL::Parse(OSTK_PHYSICS_ENVIRONMENT_ATMOSPHERIC_EARTH_MANAGER_REMOTE_URL) ;

    if (const char* remoteUrl = std::getenv("OSTK_PHYSICS_ENVIRONMENT_ATMOSPHERIC_EARTH_MANAGER_REMOTE_URL"))
    {
        return URL::Parse(remoteUrl) ;
    }

    return defaultRemoteUrl ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Manager::Manager                            ( )
                                :   localRepository_(Manager::DefaultLocalRepository()),
                                    remoteUrl_(Manager::DefaultRemoteUrl()),
                                    enabled_(Manager::DefaultEnabled())
{

    if (!localRepository_.exists())
    {
        localRepository_.create() ;
    }

}

URL                             Manager::getDataFileUrlForType              (   const   EarthAtmosphericModel::Type&   aModelType                                  ) const
{
    return remoteUrl_ + String::Format("{}.zip", Manager::DataFileNameFromType(aModelType)) ;
}

String                          Manager::DataFileNameFromType               (   const   EarthAtmosphericModel::Type&   aModelType                                  )
{

    switch (aModelType)
    {

        case EarthAtmosphericModel::Type::NRLMSISE00:
            return "nrlmsise00" ;

            throw ostk::core::error::runtime::Wrong("Type") ;

    }

    return String::Empty() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
