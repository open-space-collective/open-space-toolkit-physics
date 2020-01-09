////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/IERS/Manager.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/IERS/Manager.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Time/DateTime.hpp>
#include <OpenSpaceToolkit/Physics/Time/Time.hpp>
#include <OpenSpaceToolkit/Physics/Time/Date.hpp>
#include <OpenSpaceToolkit/Physics/Time/Scale.hpp>

#include <OpenSpaceToolkit/IO/IP/TCP/HTTP/Client.hpp>

#include <OpenSpaceToolkit/Core/FileSystem/Path.hpp>
#include <OpenSpaceToolkit/Core/Containers/Map.hpp>
#include <OpenSpaceToolkit/Core/Types/String.hpp>
#include <OpenSpaceToolkit/Core/Types/Integer.hpp>
#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

#include <experimental/filesystem>
#include <thread>
#include <chrono>
#include <fstream>
#include <numeric>
#include <cstdlib>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using ostk::core::types::String ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const String bulletinAFileName = "ser7.dat" ;
const String finals2000AFileName = "finals2000A.data" ;

const String temporaryDirectoryName = "tmp" ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Manager::Mode                   Manager::getMode                            ( ) const
{

    std::lock_guard<std::mutex> lock { mutex_ } ;

    return mode_ ;

}

Directory                       Manager::getLocalRepository                 ( ) const
{

    std::lock_guard<std::mutex> lock { mutex_ } ;

    return localRepository_ ;

}

URL                             Manager::getRemoteUrl                       ( ) const
{

    const std::lock_guard<std::mutex> lock { mutex_ } ;

    return remoteUrl_ ;

}

BulletinA                       Manager::getBulletinAAt                     (   const   Instant&                    anInstant                                   ) const
{

    if (!anInstant.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant") ;
    }

    std::lock_guard<std::mutex> lock { mutex_ } ;

    const BulletinA* bulletinAPtr = this->accessBulletinAAt(anInstant) ;

    if (bulletinAPtr != nullptr)
    {
        return *bulletinAPtr ;
    }

    throw ostk::core::error::RuntimeError("Cannot obtain Bulletin A at [{}].", anInstant.toString()) ;

}

Finals2000A                     Manager::getFinals2000AAt                   (   const   Instant&                    anInstant                                   ) const
{

    if (!anInstant.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant") ;
    }

    std::lock_guard<std::mutex> lock { mutex_ } ;

    const Finals2000A* finals2000aPtr = this->accessFinals2000AAt(anInstant) ;

    if (finals2000aPtr != nullptr)
    {
        return *finals2000aPtr ;
    }

    throw ostk::core::error::RuntimeError("Cannot obtain Finals 2000A at [{}].", anInstant.toString()) ;

}

Vector2d                        Manager::getPolarMotionAt                   (   const   Instant&                    anInstant                                   ) const
{

    if (!anInstant.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant") ;
    }

    std::lock_guard<std::mutex> lock { mutex_ } ;

    const BulletinA* bulletinAPtr = this->accessBulletinAAt(anInstant) ;

    if (bulletinAPtr != nullptr)
    {

        if (bulletinAPtr->accessObservationInterval().contains(anInstant))
        {

            const BulletinA::Observation observation = bulletinAPtr->getObservationAt(anInstant) ;

            return { observation.x, observation.y } ;

        }
        else if (bulletinAPtr->accessPredictionInterval().contains(anInstant))
        {

            const BulletinA::Prediction prediction = bulletinAPtr->getPredictionAt(anInstant) ;

            return { prediction.x, prediction.y } ;

        }
        else
        {
            throw ostk::core::error::RuntimeError("Cannot obtain polar motion from Bulletin A at [{}].", anInstant.toString()) ;
        }

    }

    const Finals2000A* finals2000aPtr = this->accessFinals2000AAt(anInstant) ;

    if (finals2000aPtr != nullptr)
    {
        return finals2000aPtr->getPolarMotionAt(anInstant) ;
    }

    throw ostk::core::error::RuntimeError("Cannot obtain polar motion at [{}].", anInstant.toString()) ;

    return Vector2d::Undefined() ;

}

Real                            Manager::getUt1MinusUtcAt                   (   const   Instant&                    anInstant                                   ) const
{

    if (!anInstant.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant") ;
    }

    std::lock_guard<std::mutex> lock { mutex_ } ;

    const BulletinA* bulletinAPtr = this->accessBulletinAAt(anInstant) ;

    if (bulletinAPtr != nullptr)
    {

        // std::cout << String::Format("Bulletin A found for [{}].", anInstant.toString()) << std::endl ;

        if (bulletinAPtr->accessObservationInterval().contains(anInstant))
        {

            const BulletinA::Observation observation = bulletinAPtr->getObservationAt(anInstant) ;

            return observation.ut1MinusUtc ;

        }
        else if (bulletinAPtr->accessPredictionInterval().contains(anInstant))
        {

            const BulletinA::Prediction prediction = bulletinAPtr->getPredictionAt(anInstant) ;

            return prediction.ut1MinusUtc ;

        }
        else
        {
            throw ostk::core::error::RuntimeError("Cannot obtain UT1 - UTC from Bulletin A at [{}].", anInstant.toString()) ;
        }

    }

    const Finals2000A* finals2000aPtr = this->accessFinals2000AAt(anInstant) ;

    if (finals2000aPtr != nullptr)
    {

        // std::cout << String::Format("Finals 2000A found for [{}].", anInstant.toString()) << std::endl ;

        return finals2000aPtr->getUt1MinusUtcAt(anInstant) ;

    }

    throw ostk::core::error::RuntimeError("Cannot obtain UT1 - UTC at [{}].", anInstant.toString()) ;

    return Real::Undefined() ;

}

Real                            Manager::getLodAt                           (   const   Instant&                    anInstant                                   ) const
{

    if (!anInstant.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant") ;
    }

    std::lock_guard<std::mutex> lock { mutex_ } ;

    const Finals2000A* finals2000aPtr = this->accessFinals2000AAt(anInstant) ;

    if (finals2000aPtr != nullptr)
    {
        return finals2000aPtr->getLodAt(anInstant) ;
    }

    throw ostk::core::error::RuntimeError("Cannot obtain LOD at [{}].", anInstant.toString()) ;

    return Real::Undefined() ;

}

void                            Manager::setMode                            (   const   Manager::Mode&              aMode                                       )
{

    std::lock_guard<std::mutex> lock { mutex_ } ;

    mode_ = aMode ;

}

void                            Manager::setLocalRepository                 (   const   Directory&                  aDirectory                                  )
{

    if (!aDirectory.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Directory") ;
    }

    const std::lock_guard<std::mutex> lock { mutex_ } ;

    localRepository_ = aDirectory ;

    if (!localRepository_.exists())
    {
        localRepository_.create() ;
    }

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

void                            Manager::loadBulletinA                      (   const   BulletinA&                  aBulletinA                                  )
{

    if (!aBulletinA.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Bulletin A") ;
    }

    std::lock_guard<std::mutex> lock { mutex_ } ;

    this->loadBulletinA_(aBulletinA) ;

}

void                            Manager::loadFinals2000A                    (   const   Finals2000A&                aFinals2000A                                )
{

    if (!aFinals2000A.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Finals 2000A") ;
    }

    std::lock_guard<std::mutex> lock { mutex_ } ;

    this->loadFinals2000A_(aFinals2000A) ;

}

File                            Manager::fetchLatestBulletinA               ( )
{

    std::lock_guard<std::mutex> lock { mutex_ } ;

    return this->fetchLatestBulletinA_() ;

}

File                            Manager::fetchLatestFinals2000A             ( )
{

    std::lock_guard<std::mutex> lock { mutex_ } ;

    return this->fetchLatestFinals2000A_() ;

}

void                            Manager::reset                              ( )
{

    std::lock_guard<std::mutex> lock { mutex_ } ;

    aBulletinIndex_ = 0 ;
    finals2000aIndex_ = 0 ;

    aBulletins_.clear() ;
    finals2000aArray_.clear() ;

}

Manager&                        Manager::Get                                ( )
{

    static Manager manager ;

    return manager ;

}

Manager::Mode                   Manager::DefaultMode                        ( )
{

    static const Manager::Mode defaultMode = OSTK_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_MANAGER_MODE ;

    if (const char* modeString = std::getenv("OSTK_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_MANAGER_MODE"))
    {

        if (strcmp(modeString, "Manual") == 0)
        {
            return Manager::Mode::Manual ;
        }
        else if (strcmp(modeString, "Automatic") == 0)
        {
            return Manager::Mode::Automatic ;
        }
        else
        {
            throw ostk::core::error::runtime::Wrong("Mode", modeString) ;
        }

    }

    return defaultMode ;

}

Directory                       Manager::DefaultLocalRepository             ( )
{

    using ostk::core::fs::Path ;

    static const Directory defaultLocalRepository = Directory::Path(Path::Parse(OSTK_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_MANAGER_LOCAL_REPOSITORY)) ;

    if (const char* localRepositoryPath = std::getenv("OSTK_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_MANAGER_LOCAL_REPOSITORY"))
    {
        return Directory::Path(Path::Parse(localRepositoryPath)) ;
    }

    return defaultLocalRepository ;

}

Duration                        Manager::DefaultLocalRepositoryLockTimeout  ( )
{

    static const Duration defaultLocalRepositoryLockTimeout = Duration::Seconds(OSTK_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_MANAGER_LOCAL_REPOSITORY_LOCK_TIMEOUT) ;

    if (const char* localRepositoryLockTimeoutString = std::getenv("OSTK_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_MANAGER_LOCAL_REPOSITORY_LOCK_TIMEOUT"))
    {
        return Duration::Parse(localRepositoryLockTimeoutString) ;
    }

    return defaultLocalRepositoryLockTimeout ;

}

URL                             Manager::DefaultRemoteUrl                   ( )
{

    static const URL defaultRemoteUrl = URL::Parse(OSTK_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_MANAGER_REMOTE_URL) ;

    if (const char* remoteUrl = std::getenv("OSTK_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_MANAGER_REMOTE_URL"))
    {
        return URL::Parse(remoteUrl) ;
    }

    return defaultRemoteUrl ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Manager::Manager                            (   const   Manager::Mode&              aMode                                       )
                                :   mode_(aMode),
                                    localRepository_(Manager::DefaultLocalRepository()),
                                    localRepositoryLockTimeout_(Manager::DefaultLocalRepositoryLockTimeout()),
                                    remoteUrl_(Manager::DefaultRemoteUrl()),
                                    aBulletins_(Array<BulletinA>::Empty()),
                                    finals2000aArray_(Array<Finals2000A>::Empty()),
                                    aBulletinIndex_(0),
                                    finals2000aIndex_(0),
                                    bulletinAUpdateTimestamp_(Instant::Undefined()),
                                    finals2000AUpdateTimestamp_(Instant::Undefined())
{

    this->setup() ;

}

bool                            Manager::isLocalRepositoryLocked            ( ) const
{
    return this->getLocalRepositoryLockFile().exists() ;
}

const BulletinA*                Manager::accessBulletinAAt                  (   const   Instant&                    anInstant                                   ) const
{

    // Try cache

    if (!aBulletins_.isEmpty())
    {

        const BulletinA& bulletinA = aBulletins_.at(aBulletinIndex_) ;

        if (bulletinA.accessObservationInterval().contains(anInstant) || bulletinA.accessPredictionInterval().contains(anInstant)) // [TBI] Check that next observation bulletin available first
        {
            return &bulletinA ;
        }

    }

    // Try observation span of loaded bulletins

    {

        aBulletinIndex_ = 0 ;

        for (const auto& bulletinA : aBulletins_)
        {

            if (bulletinA.accessObservationInterval().contains(anInstant))
            {
                return &bulletinA ;
            }

            aBulletinIndex_++ ;

        }

    }

    // Try fetching latest Bulletin A

    if (mode_ == Manager::Mode::Automatic)
    {

        const Instant currentInstant = Instant::Now() ;

        if ((!bulletinAUpdateTimestamp_.isDefined()) || ((bulletinAUpdateTimestamp_ + Duration::Weeks(1.0)) < currentInstant)) // [TBM] Param
        {

            const File latestBulletinAFile = const_cast<Manager*>(this)->getLatestBulletinAFile() ;

            if (latestBulletinAFile.isDefined())
            {

                bulletinAUpdateTimestamp_ = currentInstant ;

                const BulletinA bulletinA = BulletinA::Load(latestBulletinAFile) ;

                if (bulletinA.accessObservationInterval().contains(anInstant))
                {

                    const_cast<Manager*>(this)->loadBulletinA_(bulletinA) ;

                    aBulletinIndex_ = aBulletins_.getSize() - 1 ;

                    return &aBulletins_.accessLast() ;

                }

            }

        }

    }

    // Try prediction span of loaded bulletins

    {

        aBulletinIndex_ = 0 ;

        for (const auto& bulletinA : aBulletins_)
        {

            if (bulletinA.accessPredictionInterval().contains(anInstant))
            {
                return &bulletinA ;
            }

            aBulletinIndex_++ ;

        }

    }

    // No bulletin A found

    {

        aBulletinIndex_ = 0 ;

        return nullptr ;

    }

}

const Finals2000A*              Manager::accessFinals2000AAt                (   const   Instant&                    anInstant                                   ) const
{

    // Try cache

    if (!finals2000aArray_.isEmpty())
    {

        const Finals2000A& finals2000a = finals2000aArray_.at(finals2000aIndex_) ;

        if (finals2000a.getInterval().contains(anInstant))
        {
            return &finals2000a ;
        }

    }

    // Try loaded files

    {

        finals2000aIndex_ = 0 ;

        for (const auto& finals2000a : finals2000aArray_)
        {

            if (finals2000a.getInterval().contains(anInstant))
            {
                return &finals2000a ;
            }

            finals2000aIndex_++ ;

        }

    }

    // Try getting latest file

    if (mode_ == Manager::Mode::Automatic)
    {

        const Instant currentInstant = Instant::Now() ;

        if ((!finals2000AUpdateTimestamp_.isDefined()) || ((finals2000AUpdateTimestamp_ + Duration::Weeks(1.0)) < currentInstant))
        {

            const File latestFinals2000AFile = const_cast<Manager*>(this)->getLatestFinals2000AFile() ;

            if (latestFinals2000AFile.isDefined())
            {

                finals2000AUpdateTimestamp_ = currentInstant ;

                const Finals2000A finals2000A = Finals2000A::Load(latestFinals2000AFile) ;

                if (finals2000A.getInterval().contains(anInstant))
                {

                    const_cast<Manager*>(this)->loadFinals2000A_(finals2000A) ;

                    finals2000aIndex_ = finals2000aArray_.getSize() - 1 ;

                    return &finals2000aArray_.accessLast() ;

                }

            }

        }

    }

    {

        finals2000aIndex_ = 0 ;

        return nullptr ;

    }

}

File                            Manager::getLocalRepositoryLockFile         ( ) const
{

    using ostk::core::fs::Path ;

    return File::Path(localRepository_.getPath() + Path::Parse(".lock")) ;

}

File                            Manager::getLatestBulletinAFile             ( ) const
{

    using ostk::core::ctnr::Map ;
    using ostk::core::fs::Path ;

    using ostk::physics::time::Scale ;
    using ostk::physics::time::Date ;
    using ostk::physics::time::Time ;
    using ostk::physics::time::DateTime ;
    using ostk::physics::time::Instant ;

    Map<Instant, File> bulletinAMap = {} ;

    for (const auto& directory : localRepository_.getDirectories())
    {

        if ((directory.getName() != temporaryDirectoryName) && directory.containsFileWithName(bulletinAFileName))
        {

            const Date date = Date::Parse(directory.getName()) ;

            const Instant instant = Instant::DateTime({date, Time::Midnight()}, Scale::UTC) ;

            const File bulletinFile = File::Path(directory.getPath() + Path::Parse(bulletinAFileName)) ;

            bulletinAMap.insert({ instant, bulletinFile }) ;

        }

    }

    if (!bulletinAMap.empty())
    {
        return bulletinAMap.rbegin()->second ; // Latest bulletin
    }

    return const_cast<Manager*>(this)->fetchLatestBulletinA_() ;

}

File                            Manager::getLatestFinals2000AFile           ( ) const
{

    using ostk::core::ctnr::Map ;
    using ostk::core::fs::Path ;

    using ostk::physics::time::Scale ;
    using ostk::physics::time::Date ;
    using ostk::physics::time::Time ;
    using ostk::physics::time::DateTime ;
    using ostk::physics::time::Instant ;

    Map<Instant, File> finals2000AMap = {} ;

    for (const auto& directory : localRepository_.getDirectories())
    {

        if (directory.containsFileWithName(finals2000AFileName))
        {

            const Date date = Date::Parse(directory.getName()) ;

            const Instant instant = Instant::DateTime({date, Time::Midnight()}, Scale::UTC) ;

            const File finals2000AFile = File::Path(directory.getPath() + Path::Parse(finals2000AFileName)) ;

            finals2000AMap.insert({ instant, finals2000AFile }) ;

        }

    }

    if (!finals2000AMap.empty())
    {
        return finals2000AMap.rbegin()->second ; // Latest Finals 2000A
    }

    return const_cast<Manager*>(this)->fetchLatestFinals2000A_() ;

}

void                            Manager::setup                              ( )
{

    using ostk::core::fs::Path ;
    using ostk::core::fs::File ;

    if (!localRepository_.exists())
    {
        localRepository_.create() ;
    }

    if (mode_ == Manager::Mode::Automatic)
    {

        // const File aaa = this->fetchLatestBulletinA_() ;

        // this->loadBulletinA_(bulletinA) ;

        // {

        //     File file = File::Path(localRepository_.getPath() + Path::Parse(bulletinAFileName)) ;

        //     if (!file.exists())
        //     {
        //         file = this->fetchLatestBulletinA() ;
        //     }

        //     if (file.exists())
        //     {

        //         const BulletinA bulletinA = BulletinA::Load(file) ;

        //         this->loadBulletinA(bulletinA) ;

        //     }
        //     else
        //     {
        //         throw ostk::core::error::RuntimeError("Cannot load Bulletin A [{}].", file.toString()) ;
        //     }

        // }

        // {

        //     const File file = File::Path(localRepository_.getPath() + Path::Parse("10.txt")) ;

        //     if (file.exists())
        //     {

        //         const Finals2000A finals2000a = Finals2000A::Load(file) ;

        //         this->loadFinals2000A(finals2000a) ;

        //     }

        // }

    }

}

void                            Manager::loadBulletinA_                     (   const   BulletinA&                  aBulletinA                                  )
{

    for (const auto& bulletinA : aBulletins_)
    {

        if (bulletinA.accessReleaseDate() == aBulletinA.accessReleaseDate())
        {
            throw ostk::core::error::RuntimeError("Bulletin A already added.") ;
        }

    }

    aBulletins_.add(aBulletinA) ; // [TBI] Add in ascending time order

    aBulletinIndex_ = 0 ;

}

void                            Manager::loadFinals2000A_                   (   const   Finals2000A&                aFinals2000A                                )
{

    for (const auto& finals2000a : finals2000aArray_)
    {

        if (finals2000a.getInterval() == aFinals2000A.getInterval())
        {
            throw ostk::core::error::RuntimeError("Finals 2000A already added.") ;
        }

    }

    finals2000aArray_.add(aFinals2000A) ; // [TBI] Add in ascending time order

    finals2000aIndex_ = 0 ;

}

File                            Manager::fetchLatestBulletinA_              ( )
{

    using ostk::core::types::Uint8 ;
    using ostk::core::types::Uint16 ;
    using ostk::core::types::Integer ;
    using ostk::core::types::String ;
    using ostk::core::ctnr::Map ;
    using ostk::core::fs::Path ;

    using ostk::io::ip::tcp::http::Client ;

    using ostk::physics::time::Scale ;
    using ostk::physics::time::Date ;
    using ostk::physics::time::Time ;
    using ostk::physics::time::DateTime ;
    using ostk::physics::time::Instant ;

    std::cout << "Fetching latest Bulletin A..." << std::endl ;

    // File listingFile = File::Path(localRepository_.getPath() + Path::Parse("listing.txt")) ;

    // if (listingFile.exists())
    // {
    //     listingFile.remove() ;
    // }

    // Client::List(remoteUrl_, listingFile, false) ;

    // const Integer currentYear = Instant::Now().getDateTime(Scale::UTC).getDate().getYear() ;

    // static const Map<String, Uint8> monthStringIntegerMap =
    // {
    //     { "Jan", 1 },
    //     { "Feb", 2 },
    //     { "Mar", 3 },
    //     { "Apr", 4 },
    //     { "May", 5 },
    //     { "Jun", 6 },
    //     { "Jul", 7 },
    //     { "Aug", 8 },
    //     { "Sep", 9 },
    //     { "Oct", 10 },
    //     { "Nov", 11 },
    //     { "Dec", 12 }
    // } ;

    // std::ifstream listingFileStream { listingFile.getPath().toString() } ;

    // String listingLine ;

    // while (std::getline(listingFileStream, listingLine))
    // {

    //     // Split spaces into tokens

    //     std::istringstream iss { listingLine } ;

    //     std::vector<std::string> tokens { std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{} } ;

    //     // -rw-r--r--    1 1010     1011        69744 Aug 24 12:21 archive.notes

    //     if (tokens.size() >= 9)
    //     {

    //         // Recombine tokens into filename

    //         const String fileName = std::accumulate(tokens.begin() + 8, tokens.end(), std::string("")) ;

    //         if (fileName == bulletinAFileName)
    //         {

    //             const String monthString = tokens.at(5) ;
    //             const String dayString = tokens.at(6) ;

    //             const Integer month = monthStringIntegerMap.at(monthString) ;
    //             const Integer day = Integer::Parse(dayString) ;

    //             const Date fileLastModifiedDate = { static_cast<Uint16>(currentYear), static_cast<Uint8>(month), static_cast<Uint8>(day) } ;

    //             const Instant fileLastModifiedInstant = Instant::DateTime({ fileLastModifiedDate, Time::Midnight() }, Scale::UTC) ;

    //             break ;

    //         }

    //     }

    // }

    // if (listingFile.exists())
    // {
    //     listingFile.remove() ;
    // }

    Directory temporaryDirectory = Directory::Path(localRepository_.getPath() + Path::Parse(temporaryDirectoryName)) ;

    if (temporaryDirectory.exists())
    {
        throw ostk::core::error::RuntimeError("Temporary directory [{}] already exists.", temporaryDirectory.toString()) ;
    }

    std::cout << String::Format("Creating temporary directory [{}]...", temporaryDirectory.toString()) << std::endl ;

    temporaryDirectory.create() ;

    const URL latestBulletinAUrl = remoteUrl_ + bulletinAFileName ;

    File latestBulletinAFile = File::Undefined() ;
    Directory destinationDirectory = Directory::Undefined() ;

    try
    {

        this->lockLocalRepository(localRepositoryLockTimeout_) ;

        std::cout << String::Format("Fetching Bulletin A from [{}]...", latestBulletinAUrl.toString()) << std::endl ;

        latestBulletinAFile = Client::Fetch(latestBulletinAUrl, temporaryDirectory) ;

        if (!latestBulletinAFile.exists())
        {
            throw ostk::core::error::RuntimeError("Cannot fetch Bulletin A from [{}].", latestBulletinAUrl.toString()) ;
        }
        else
        {

            // Check that file size is not zero

            std::uintmax_t latestBulletinAFileSize = std::experimental::filesystem::file_size(std::string(latestBulletinAFile.getPath().toString())) ;

            if (latestBulletinAFileSize == 0)
            {
                throw ostk::core::error::RuntimeError("Cannot fetch Bulletin A from [{}]: file is empty.", latestBulletinAUrl.toString()) ;
            }

        }

        const BulletinA latestBulletinA = BulletinA::Load(latestBulletinAFile) ;

        destinationDirectory = Directory::Path(localRepository_.getPath() + Path::Parse(latestBulletinA.accessReleaseDate().toString())) ;

        if (destinationDirectory.exists())
        {
            destinationDirectory.remove() ;
        }

        destinationDirectory.create() ;

        latestBulletinAFile.moveToDirectory(destinationDirectory) ;

        temporaryDirectory.remove() ;

        this->unlockLocalRepository() ;

        std::cout << String::Format("Bulletin A [{}] has been successfully fetched from [{}].", latestBulletinAFile.toString(), latestBulletinAUrl.toString()) << std::endl ;

    }
    catch (const ostk::core::error::Exception& anException)
    {

        std::cerr << String::Format("Error caught while fetching latest Bulletin A from [{}]: [{}].", latestBulletinAUrl.toString(), anException.what()) << std::endl ;

        if (latestBulletinAFile.isDefined() && latestBulletinAFile.exists())
        {

            latestBulletinAFile.remove() ;

            latestBulletinAFile = File::Undefined() ;

        }

        if (temporaryDirectory.isDefined() && temporaryDirectory.exists())
        {
            temporaryDirectory.remove() ;
        }

        this->unlockLocalRepository() ;

    }

    return latestBulletinAFile ;

}

File                            Manager::fetchLatestFinals2000A_            ( )
{

    using ostk::core::types::Uint8 ;
    using ostk::core::types::Uint16 ;
    using ostk::core::types::Integer ;
    using ostk::core::types::String ;
    using ostk::core::ctnr::Map ;
    using ostk::core::fs::Path ;

    using ostk::io::ip::tcp::http::Client ;

    using ostk::physics::time::Scale ;
    using ostk::physics::time::Date ;
    using ostk::physics::time::Time ;
    using ostk::physics::time::DateTime ;
    using ostk::physics::time::Instant ;

    Directory temporaryDirectory = Directory::Path(localRepository_.getPath() + Path::Parse(temporaryDirectoryName)) ;

    if (temporaryDirectory.exists())
    {
        throw ostk::core::error::RuntimeError("Temporary directory [{}] already exists.", temporaryDirectory.toString()) ;
    }

    temporaryDirectory.create() ;

    const URL latestFinals2000AUrl = remoteUrl_ + finals2000AFileName ;

    File latestFinals2000AFile = File::Undefined() ;
    Directory destinationDirectory = Directory::Undefined() ;

    try
    {

        this->lockLocalRepository(localRepositoryLockTimeout_) ;

        std::cout << String::Format("Fetching Finals 2000A from [{}]...", latestFinals2000AUrl.toString()) << std::endl ;

        latestFinals2000AFile = Client::Fetch(latestFinals2000AUrl, temporaryDirectory) ;

        const Finals2000A latestFinals2000A = Finals2000A::Load(latestFinals2000AFile) ;

        if (!latestFinals2000AFile.exists())
        {
            throw ostk::core::error::RuntimeError("Cannot fetch Finals 2000A [{}] from [{}].", latestFinals2000AFile.toString(), latestFinals2000AUrl.toString()) ;
        }
        else
        {

            // Check that file size is not zero

            std::uintmax_t latestFinals2000AFileSize = std::experimental::filesystem::file_size(std::string(latestFinals2000AFile.getPath().toString())) ;

            if (latestFinals2000AFileSize == 0)
            {
                throw ostk::core::error::RuntimeError("Cannot fetch Finals 2000A from [{}]: file is empty.", latestFinals2000AUrl.toString()) ;
            }

        }

        destinationDirectory = Directory::Path(localRepository_.getPath() + Path::Parse(Instant::Now().getDateTime(Scale::UTC).getDate().toString())) ;

        if (destinationDirectory.exists())
        {
            destinationDirectory.remove() ;
        }

        destinationDirectory.create() ;

        latestFinals2000AFile.moveToDirectory(destinationDirectory) ;

        temporaryDirectory.remove() ;

        this->unlockLocalRepository() ;

        std::cout << String::Format("Finals 2000A [{}] has been successfully fetched from [{}].", latestFinals2000AFile.toString(), latestFinals2000AUrl.toString()) << std::endl ;

    }
    catch (const ostk::core::error::Exception& anException)
    {

        std::cerr << String::Format("Error caught while fetching latest Finals 2000A from [{}]: [{}].", latestFinals2000AUrl.toString(), anException.what()) << std::endl ;

        if (latestFinals2000AFile.isDefined() && latestFinals2000AFile.exists())
        {

            latestFinals2000AFile.remove() ;

            latestFinals2000AFile = File::Undefined() ;

        }

        if (temporaryDirectory.isDefined() && temporaryDirectory.exists())
        {
            temporaryDirectory.remove() ;
        }

        this->unlockLocalRepository() ;

    }

    return latestFinals2000AFile ;

}

void                            Manager::lockLocalRepository                (   const   Duration&                   aTimeout                                    )
{

    std::cout << String::Format("Locking local repository [{}]...", localRepository_.toString()) << std::endl ;

    const auto tryLock = [] (File& aLockFile) -> bool
    {

        if (!aLockFile.exists()) // [TBM] Should use system-wide semaphore instead (race condition can still occur)
        {

            try
            {

                aLockFile.create() ;

                return true ;

            }
            catch (...)
            {
                // Do nothing
            }

            return false ;

        }

        return false ;

    } ;

    const Instant timeoutInstant = Instant::Now() + aTimeout ;

    File lockFile = this->getLocalRepositoryLockFile() ;

    while (!tryLock(lockFile))
    {

        if (Instant::Now() >= timeoutInstant)
        {
            throw ostk::core::error::RuntimeError("Cannot lock local repository: timeout reached.") ;
        }

        std::this_thread::sleep_for(std::chrono::seconds(1)) ;

    }

}

void                            Manager::unlockLocalRepository              ( )
{

    std::cout << String::Format("Unlocking local repository [{}]...", localRepository_.toString()) << std::endl ;

    if (!this->isLocalRepositoryLocked())
    {
        throw ostk::core::error::RuntimeError("Cannot unlock local repository: lock file does not exist.") ;
    }

    this->getLocalRepositoryLockFile().remove() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
