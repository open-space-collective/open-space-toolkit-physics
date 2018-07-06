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
                                    aBulletinIndex_(0)
{

    // [TBR]

    using library::core::fs::Path ;
    using library::core::fs::File ;

    File file = File::Path(Path::Parse("/app/share/data/ser7.dat")) ;

    BulletinA bulletinA = BulletinA::Load(file) ;

    this->addBulletinA(bulletinA) ;

}

const BulletinA&                Manager::accessBulletinAAt                  (   const   Instant&                    anInstant                                   ) const
{

    if (!anInstant.isDefined())
    {
        throw library::core::error::runtime::Undefined("Instant") ;
    }

    std::lock_guard<std::mutex> lock(mutex_) ;

    if (aBulletins_.isEmpty())
    {
        throw library::core::error::RuntimeError("No bulletin A.") ;
    }

    {

        const BulletinA& bulletinA = aBulletins_.at(aBulletinIndex_) ;

        if (bulletinA.accessObservationInterval().contains(anInstant) || bulletinA.accessPredictionInterval().contains(anInstant)) // [TBI] Check that next observation bulletin available first
        {
            return bulletinA ;
        }

    }

    {

        aBulletinIndex_ = 0 ;
    
        for (const auto& bulletinA : aBulletins_)
        {

            if (bulletinA.accessObservationInterval().contains(anInstant))
            {
                return bulletinA ;
            }

            aBulletinIndex_++ ;

        }

        aBulletinIndex_ = 0 ;
    
        for (const auto& bulletinA : aBulletins_)
        {

            if (bulletinA.accessPredictionInterval().contains(anInstant))
            {
                return bulletinA ;
            }

            aBulletinIndex_++ ;

        }

    }

    {

        aBulletinIndex_ = 0 ;

        throw library::core::error::RuntimeError("No bulletin A at [{}].", anInstant.toString()) ;

    }

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////