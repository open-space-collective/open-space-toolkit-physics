////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Coordinate/Frame/Manager.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Coordinate/Frame/Manager.hpp>

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool                            Manager::hasFrameWithName                   (   const   String&                     aFrameName                                  ) const
{

    const std::lock_guard<std::mutex> lock { mutex_ } ;

    return frameMap_.find(aFrameName) != frameMap_.end() ;

}

Shared<const Frame>             Manager::accessFrameWithName                (   const   String&                     aFrameName                                  ) const
{

    const std::lock_guard<std::mutex> lock { mutex_ } ;

    const auto frameMapIt = frameMap_.find(aFrameName) ;

    if (frameMapIt != frameMap_.end())
    {
        return frameMapIt->second ;
    }

    // throw library::core::error::RuntimeError("Cannot access frame with name [{}].", aFrameName) ;

    return nullptr ;

}

const Transform*                Manager::accessCachedTransform              (   const   Shared<const Frame>&        aFromFrameSPtr,
                                                                                const   Shared<const Frame>&        aToFrameSPtr,
                                                                                const   Instant&                    anInstant                                   ) const
{

    const std::lock_guard<std::mutex> lock { mutex_ } ;

    const auto transformCacheFromFrameIt = transformCache_.find(aFromFrameSPtr.get()) ;

    if (transformCacheFromFrameIt != transformCache_.end())
    {

        const auto transformCacheToFrameIt = transformCacheFromFrameIt->second.find(aToFrameSPtr.get()) ;

        if (transformCacheToFrameIt != transformCacheFromFrameIt->second.end())
        {

            const auto transformCacheInstantIt = transformCacheToFrameIt->second.find(anInstant) ;

            if (transformCacheInstantIt != transformCacheToFrameIt->second.end())
            {
                return &(transformCacheInstantIt->second) ;
            }

        }

    }

    return nullptr ;

}

void                            Manager::addFrame                           (   const   Shared<const Frame>&        aFrameSPtr                                  )
{

    if (aFrameSPtr == nullptr)
    {
        throw library::core::error::runtime::Undefined("Frame") ;
    }

    const std::lock_guard<std::mutex> lock { mutex_ } ;

    // std::cout << "Manager :: addFrame | Frame @ " << aFrameSPtr.get() << std::endl ;

    if (frameMap_.find(aFrameSPtr->getName()) == frameMap_.end())
    {
        frameMap_.insert({ aFrameSPtr->getName(), aFrameSPtr }) ;
    }

}

void                            Manager::removeFrameWithName                (   const   String&                     aFrameName                                  )
{

    const std::lock_guard<std::mutex> lock { mutex_ } ;

    const auto frameMapIt = frameMap_.find(aFrameName) ;

    if (frameMapIt != frameMap_.end())
    {

        const Frame* framePtr = frameMapIt->second.get() ;

        // Delete related cached transforms

        const auto transformCacheFromFrameIt = transformCache_.find(framePtr) ;

        if (transformCacheFromFrameIt != transformCache_.end())
        {
            transformCache_.erase(transformCacheFromFrameIt) ;
        }

        for (auto& transformCacheIt : transformCache_)
        {

            const auto transformCacheToFrameIt = transformCacheIt.second.find(framePtr) ;

            if (transformCacheToFrameIt != transformCacheIt.second.end())
            {
                transformCacheIt.second.erase(transformCacheToFrameIt) ;
            }

        }

        // Delete frame

        frameMap_.erase(frameMapIt) ;

    }
    else
    {
        throw library::core::error::RuntimeError("No frame with name [{}].", aFrameName) ;
    }

}

void                            Manager::addCachedTransform                 (   const   Shared<const Frame>&        aFromFrameSPtr,
                                                                                const   Shared<const Frame>&        aToFrameSPtr,
                                                                                const   Instant&                    anInstant,
                                                                                const   Transform&                  aTransform                                  )
{

    const std::lock_guard<std::mutex> lock { mutex_ } ;

    const auto transformCacheFromFrameIt = transformCache_.insert({ aFromFrameSPtr.get(), {} }).first ;
    const auto transformCacheToFrameIt = transformCacheFromFrameIt->second.insert({ aToFrameSPtr.get(), {} }).first ;
    const auto transformCacheToInstantIt = transformCacheToFrameIt->second.insert({ anInstant, aTransform }).first ;

    (void) transformCacheToInstantIt ;

}

Manager&                        Manager::Get                                ( )
{

    static Manager manager ;

    return manager ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////