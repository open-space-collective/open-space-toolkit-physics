////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Coordinate/Frame/Providers/IERS/Manager.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Coordinate/Frame/Providers/IERS/Manager.hpp>
#include <Library/Physics/Time/Instant.hpp>
#include <Library/Physics/Time/DateTime.hpp>
#include <Library/Physics/Time/Time.hpp>
#include <Library/Physics/Time/Date.hpp>
#include <Library/Physics/Time/Scale.hpp>

#include <Library/IO/IP/TCP/HTTP/Client.hpp>

#include <Library/Core/FileSystem/Path.hpp>
#include <Library/Core/Containers/Map.hpp>
#include <Library/Core/Types/String.hpp>
#include <Library/Core/Types/Integer.hpp>
#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

#include <fstream>
#include <numeric>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
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

Manager::Mode                   Manager::getMode                            ( ) const
{

    std::lock_guard<std::mutex> lock(mutex_) ;

    return mode_ ;

}

Directory                       Manager::getLocalRepository                 ( ) const
{

    std::lock_guard<std::mutex> lock(mutex_) ;

    return localRepository_ ;

}

URL                             Manager::getRemoteUrl                       ( ) const
{

    const std::lock_guard<std::mutex> lock(mutex_) ;

    return remoteUrl_ ;

}

BulletinA                       Manager::getBulletinAAt                     (   const   Instant&                    anInstant                                   ) const
{

    if (!anInstant.isDefined())
    {
        throw library::core::error::runtime::Undefined("Instant") ;
    }

    std::lock_guard<std::mutex> lock(mutex_) ;

    const BulletinA* bulletinAPtr = this->accessBulletinAAt(anInstant) ;

    if (bulletinAPtr != nullptr)
    {
        return *bulletinAPtr ;
    }

    throw library::core::error::RuntimeError("Cannot obtain Bulletin A at [{}].", anInstant.toString()) ;

}

Finals2000A                     Manager::getFinals2000AAt                   (   const   Instant&                    anInstant                                   ) const
{

    if (!anInstant.isDefined())
    {
        throw library::core::error::runtime::Undefined("Instant") ;
    }

    std::lock_guard<std::mutex> lock(mutex_) ;

    const Finals2000A* finals2000aPtr = this->accessFinals2000AAt(anInstant) ;

    if (finals2000aPtr != nullptr)
    {
        return *finals2000aPtr ;
    }

    throw library::core::error::RuntimeError("Cannot obtain Finals 2000A at [{}].", anInstant.toString()) ;

}

Vector2d                        Manager::getPolarMotionAt                   (   const   Instant&                    anInstant                                   ) const
{

    if (!anInstant.isDefined())
    {
        throw library::core::error::runtime::Undefined("Instant") ;
    }

    std::lock_guard<std::mutex> lock(mutex_) ;

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
            throw library::core::error::RuntimeError("Cannot obtain polar motion from Bulletin A at [{}].", anInstant.toString()) ;
        }

    }

    const Finals2000A* finals2000aPtr = this->accessFinals2000AAt(anInstant) ;

    if (finals2000aPtr != nullptr)
    {
        return finals2000aPtr->getPolarMotionAt(anInstant) ;
    }

    throw library::core::error::RuntimeError("Cannot obtain polar motion at [{}].", anInstant.toString()) ;

    return Vector2d::Undefined() ;

}

Real                            Manager::getUt1MinusUtcAt                   (   const   Instant&                    anInstant                                   ) const
{

    if (!anInstant.isDefined())
    {
        throw library::core::error::runtime::Undefined("Instant") ;
    }

    std::lock_guard<std::mutex> lock(mutex_) ;

    const BulletinA* bulletinAPtr = this->accessBulletinAAt(anInstant) ;

    if (bulletinAPtr != nullptr)
    {

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
            throw library::core::error::RuntimeError("Cannot obtain UT1 - UTC from Bulletin A at [{}].", anInstant.toString()) ;
        }

    }

    const Finals2000A* finals2000aPtr = this->accessFinals2000AAt(anInstant) ;

    if (finals2000aPtr != nullptr)
    {
        return finals2000aPtr->getUt1MinusUtcAt(anInstant) ;
    }

    throw library::core::error::RuntimeError("Cannot obtain UT1 - UTC at [{}].", anInstant.toString()) ;

    return Real::Undefined() ;

}

Real                            Manager::getLodAt                           (   const   Instant&                    anInstant                                   ) const
{

    if (!anInstant.isDefined())
    {
        throw library::core::error::runtime::Undefined("Instant") ;
    }

    std::lock_guard<std::mutex> lock(mutex_) ;

    const Finals2000A* finals2000aPtr = this->accessFinals2000AAt(anInstant) ;

    if (finals2000aPtr != nullptr)
    {
        return finals2000aPtr->getLodAt(anInstant) ;
    }

    throw library::core::error::RuntimeError("Cannot obtain LOD at [{}].", anInstant.toString()) ;

    return Real::Undefined() ;

}

void                            Manager::setMode                            (   const   Manager::Mode&              aMode                                       )
{

    std::lock_guard<std::mutex> lock(mutex_) ;

    mode_ = aMode ;

}

void                            Manager::setLocalRepository                 (   const   Directory&                  aDirectory                                  )
{

    if (!aDirectory.isDefined())
    {
        throw library::core::error::runtime::Undefined("Directory") ;
    }

    const std::lock_guard<std::mutex> lock(mutex_) ;

    localRepository_ = aDirectory ;

}

void                            Manager::setRemoteUrl                       (   const   URL&                        aRemoteUrl                                  )
{

    if (!aRemoteUrl.isDefined())
    {
        throw library::core::error::runtime::Undefined("Remote URL") ;
    }

    const std::lock_guard<std::mutex> lock(mutex_) ;

    remoteUrl_ = aRemoteUrl ;

}

void                            Manager::loadBulletinA                      (   const   BulletinA&                  aBulletinA                                  )
{

    if (!aBulletinA.isDefined())
    {
        throw library::core::error::runtime::Undefined("Bulletin A") ;
    }

    std::lock_guard<std::mutex> lock(mutex_) ;

    this->loadBulletinA_(aBulletinA) ;

}

void                            Manager::loadFinals2000A                    (   const   Finals2000A&                aFinals2000A                                )
{

    if (!aFinals2000A.isDefined())
    {
        throw library::core::error::runtime::Undefined("Finals 2000A") ;
    }

    std::lock_guard<std::mutex> lock(mutex_) ;

    this->loadFinals2000A_(aFinals2000A) ;

}

File                            Manager::fetchLatestBulletinA               ( )
{

    std::lock_guard<std::mutex> lock(mutex_) ;

    return this->fetchLatestBulletinA_() ;

}

File                            Manager::fetchLatestFinals2000A             ( )
{

    std::lock_guard<std::mutex> lock(mutex_) ;

    return this->fetchLatestFinals2000A_() ;

}

void                            Manager::reset                              ( )
{

    std::lock_guard<std::mutex> lock(mutex_) ;

    aBulletinIndex_ = 0 ;
    finals2000aIndex_ = 0 ;

    aBulletins_.clear() ;
    finals2000aArray_.clear() ;
        
}

Manager&                        Manager::Get                                (   const   Manager::Mode&              aMode                                       )
{

    static Manager manager = { aMode } ;

    return manager ;

}

Directory                       Manager::DefaultLocalRepository             ( )
{

    using library::core::fs::Path ;
    
    return Directory::Path(Path::Parse("/var/library-physics/coordinate/frame/providers/iers")) ;

}

URL                             Manager::DefaultRemoteUrl                   ( )
{
    return URL::Parse("ftp://maia.usno.navy.mil/ser7/") ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Manager::Manager                            (   const   Manager::Mode&              aMode                                       )
                                :   mode_(aMode),
                                    localRepository_(Manager::DefaultLocalRepository()),
                                    remoteUrl_(Manager::DefaultRemoteUrl()),
                                    aBulletins_(Array<BulletinA>::Empty()),
                                    finals2000aArray_(Array<Finals2000A>::Empty()),
                                    aBulletinIndex_(0),
                                    finals2000aIndex_(0),
                                    bulletinAUpdateInstant_(Instant::Undefined()),
                                    finals2000AUpdateInstant_(Instant::Undefined())
{

    this->setup() ;

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

    // Try getting latest Bulletin A

    if (mode_ == Manager::Mode::Automatic)
    {

        const Instant currentInstant = Instant::Now() ;

        if ((!bulletinAUpdateInstant_.isDefined()) || ((bulletinAUpdateInstant_ + Duration::Weeks(1.0)) < currentInstant))
        {

            const File latestBulletinAFile = const_cast<Manager*>(this)->getLatestBulletinAFile() ;

            if (latestBulletinAFile.isDefined())
            {

                bulletinAUpdateInstant_ = currentInstant ;

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

        if ((!finals2000AUpdateInstant_.isDefined()) || ((finals2000AUpdateInstant_ + Duration::Weeks(1.0)) < currentInstant))
        {

            const File latestFinals2000AFile = const_cast<Manager*>(this)->getLatestFinals2000AFile() ;

            if (latestFinals2000AFile.isDefined())
            {

                finals2000AUpdateInstant_ = currentInstant ;

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

File                            Manager::getLatestBulletinAFile             ( ) const
{

    using library::core::ctnr::Map ;
    using library::core::fs::Path ;
    
    using library::physics::time::Scale ;
    using library::physics::time::Date ;
    using library::physics::time::Time ;
    using library::physics::time::DateTime ;
    using library::physics::time::Instant ;

    Map<Instant, File> bulletinAMap = {} ;

    for (const auto& directory : localRepository_.getDirectories())
    {

        if (directory.containsFileWithName("ser7.dat"))
        {

            const Date date = Date::Parse(directory.getName()) ;

            const Instant instant = Instant::DateTime({date, Time::Midnight()}, Scale::UTC) ;

            const File bulletinFile = File::Path(directory.getPath() + Path::Parse("ser7.dat")) ;
            
            bulletinAMap.insert({ instant, bulletinFile }) ;

        }

    }

    if ((!bulletinAMap.empty()) && (Duration::Between(bulletinAMap.rbegin()->first, Instant::Now()) < Duration::Weeks(1.0))) // [TBM] 1 week is arbitrary
    {
        return bulletinAMap.rbegin()->second ; // Latest bulletin
    }

    return const_cast<Manager*>(this)->fetchLatestBulletinA_() ;

}

File                            Manager::getLatestFinals2000AFile           ( ) const
{

    using library::core::ctnr::Map ;
    using library::core::fs::Path ;
    
    using library::physics::time::Scale ;
    using library::physics::time::Date ;
    using library::physics::time::Time ;
    using library::physics::time::DateTime ;
    using library::physics::time::Instant ;

    Map<Instant, File> finals2000AMap = {} ;

    for (const auto& directory : localRepository_.getDirectories())
    {

        if (directory.containsFileWithName("finals2000A.data"))
        {

            const Date date = Date::Parse(directory.getName()) ;

            const Instant instant = Instant::DateTime({date, Time::Midnight()}, Scale::UTC) ;

            const File finals2000AFile = File::Path(directory.getPath() + Path::Parse("finals2000A.data")) ;
            
            finals2000AMap.insert({ instant, finals2000AFile }) ;

        }

    }

    if ((!finals2000AMap.empty()) && (Duration::Between(finals2000AMap.rbegin()->first, Instant::Now()) < Duration::Weeks(1.0))) // [TBM] 1 week is arbitrary
    {
        return finals2000AMap.rbegin()->second ; // Latest Finals 2000A
    }

    return const_cast<Manager*>(this)->fetchLatestFinals2000A_() ;

}

void                            Manager::setup                              ( )
{

    using library::core::fs::Path ;
    using library::core::fs::File ;

    if (!localRepository_.exists())
    {
        localRepository_.create() ;
    }

    if (mode_ == Manager::Mode::Automatic)
    {

        // const File aaa = this->fetchLatestBulletinA_() ;

        // this->loadBulletinA_(bulletinA) ;

        // {

        //     File file = File::Path(localRepository_.getPath() + Path::Parse("ser7.dat")) ;

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
        //         throw library::core::error::RuntimeError("Cannot load Bulletin A [{}].", file.toString()) ;
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
            throw library::core::error::RuntimeError("Bulletin A already added.") ;
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
            throw library::core::error::RuntimeError("Finals 2000A already added.") ;
        }

    }

    finals2000aArray_.add(aFinals2000A) ; // [TBI] Add in ascending time order

    finals2000aIndex_ = 0 ;

}

File                            Manager::fetchLatestBulletinA_              ( )
{

    using library::core::types::Uint8 ;
    using library::core::types::Uint16 ;
    using library::core::types::Integer ;
    using library::core::types::String ;
    using library::core::ctnr::Map ;
    using library::core::fs::Path ;

    using library::io::ip::tcp::http::Client ;
    
    using library::physics::time::Scale ;
    using library::physics::time::Date ;
    using library::physics::time::Time ;
    using library::physics::time::DateTime ;
    using library::physics::time::Instant ;

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

    //         if (fileName == "ser7.dat")
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

    Directory temporaryDirectory = Directory::Path(localRepository_.getPath() + Path::Parse("tmp")) ;

    if (temporaryDirectory.exists())
    {
        throw library::core::error::RuntimeError("Temporary directory [{}] already exists.", temporaryDirectory.toString()) ;
    }

    temporaryDirectory.create() ;

    const URL remoteUrl = remoteUrl_ + "ser7.dat" ;

    File latestBulletinAFile = Client::Fetch(remoteUrl, temporaryDirectory) ;

    // [TBI] Add file size verification

    const BulletinA latestBulletinA = BulletinA::Load(latestBulletinAFile) ;

    if (!latestBulletinAFile.exists())
    {
        throw library::core::error::RuntimeError("Cannot fetch Bulletin A file [{}] at [{}].", latestBulletinAFile.toString(), remoteUrl.toString()) ;
    }

    Directory destinationDirectory = Directory::Path(localRepository_.getPath() + Path::Parse(latestBulletinA.accessReleaseDate().toString())) ;

    if (destinationDirectory.exists())
    {
        destinationDirectory.remove() ;
    }

    destinationDirectory.create() ;

    latestBulletinAFile.moveToDirectory(destinationDirectory) ;

    temporaryDirectory.remove() ;

    return latestBulletinAFile ;

}

File                            Manager::fetchLatestFinals2000A_            ( )
{

    using library::core::types::Uint8 ;
    using library::core::types::Uint16 ;
    using library::core::types::Integer ;
    using library::core::types::String ;
    using library::core::ctnr::Map ;
    using library::core::fs::Path ;

    using library::io::ip::tcp::http::Client ;
    
    using library::physics::time::Scale ;
    using library::physics::time::Date ;
    using library::physics::time::Time ;
    using library::physics::time::DateTime ;
    using library::physics::time::Instant ;

    Directory temporaryDirectory = Directory::Path(localRepository_.getPath() + Path::Parse("tmp")) ;

    if (temporaryDirectory.exists())
    {
        throw library::core::error::RuntimeError("Temporary directory [{}] already exists.", temporaryDirectory.toString()) ;
    }

    temporaryDirectory.create() ;

    const URL remoteUrl = remoteUrl_ + "finals2000A.data" ;

    File latestFinals2000AFile = Client::Fetch(remoteUrl, temporaryDirectory) ;

    // [TBI] Add file size verification

    const Finals2000A latestFinals2000A = Finals2000A::Load(latestFinals2000AFile) ;

    if (!latestFinals2000AFile.exists())
    {
        throw library::core::error::RuntimeError("Cannot fetch Finals 2000A file [{}] at [{}].", latestFinals2000AFile.toString(), remoteUrl.toString()) ;
    }

    Directory destinationDirectory = Directory::Path(localRepository_.getPath() + Path::Parse(Instant::Now().getDateTime(Scale::UTC).getDate().toString())) ;

    if (destinationDirectory.exists())
    {
        destinationDirectory.remove() ;
    }

    destinationDirectory.create() ;

    latestFinals2000AFile.moveToDirectory(destinationDirectory) ;

    temporaryDirectory.remove() ;

    return latestFinals2000AFile ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////