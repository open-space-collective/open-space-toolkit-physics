////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Coordinate/Frame/Providers/IERS/Manager.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Coordinate/Frame/Providers/IERS/Manager.hpp>

#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

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

                                Manager::Manager                            ( )
                                :   aBulletins_(Array<BulletinA>::Empty()),
                                    finals2000aArray_(Array<Finals2000A>::Empty()),
                                    aBulletinIndex_(0),
                                    finals2000aIndex_(0)
{

    // [TBR]

    using library::core::fs::Path ;
    using library::core::fs::File ;

    {

        const File file = File::Path(Path::Parse("/app/share/data/ser7.dat")) ;

        if (file.exists())
        {

            const BulletinA bulletinA = BulletinA::Load(file) ;

            this->addBulletinA(bulletinA) ;

        }

    }

    {

        const File file = File::Path(Path::Parse("/app/share/data/10.txt")) ;

        if (file.exists())
        {

            const Finals2000A finals2000a = Finals2000A::Load(file) ;

            this->addFinals2000A(finals2000a) ;

        }

    }

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

    return Real::Undefined() ;

}

void                            Manager::addBulletinA                       (   const   BulletinA&                  aBulletinA                                  )
{

    if (!aBulletinA.isDefined())
    {
        throw library::core::error::runtime::Undefined("Bulletin A") ;
    }

    std::lock_guard<std::mutex> lock(mutex_) ;

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

void                            Manager::addFinals2000A                     (   const   Finals2000A&                aFinals2000A                                )
{

    if (!aFinals2000A.isDefined())
    {
        throw library::core::error::runtime::Undefined("Finals 2000A") ;
    }

    std::lock_guard<std::mutex> lock(mutex_) ;

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const BulletinA*                Manager::accessBulletinAAt                  (   const   Instant&                    anInstant                                   ) const
{

    if (aBulletins_.isEmpty())
    {
        return nullptr ;
    }

    {

        const BulletinA& bulletinA = aBulletins_.at(aBulletinIndex_) ;

        if (bulletinA.accessObservationInterval().contains(anInstant) || bulletinA.accessPredictionInterval().contains(anInstant)) // [TBI] Check that next observation bulletin available first
        {
            return &bulletinA ;
        }

    }

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

    {

        aBulletinIndex_ = 0 ;

        return nullptr ;

    }

}

const Finals2000A*              Manager::accessFinals2000AAt                (   const   Instant&                    anInstant                                   ) const
{

    if (finals2000aArray_.isEmpty())
    {
        return nullptr ;
    }

    {

        const Finals2000A& finals2000a = finals2000aArray_.at(finals2000aIndex_) ;

        if (finals2000a.getInterval().contains(anInstant))
        {
            return &finals2000a ;
        }

    }

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

    {

        finals2000aIndex_ = 0 ;

        return nullptr ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////