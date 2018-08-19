////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Coordinate/Frame/Manager.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

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

                                Manager::Manager                            ( )
{

}

bool                            Manager::hasFrameWithName                   (   const   String&                     aFrameName                                  ) const
{

    std::lock_guard<std::mutex> lock(mutex_) ;

    return frameMap_.find(aFrameName) != frameMap_.end() ;

}

Shared<const Frame>             Manager::accessFrameWithName                (   const   String&                     aFrameName                                  ) const
{

    std::lock_guard<std::mutex> lock(mutex_) ;

    const auto frameMapIt = frameMap_.find(aFrameName) ;

    if (frameMapIt == frameMap_.end())
    {
        throw library::core::error::RuntimeError("Cannot access frame with name [{}].", aFrameName) ;
    }

    return frameMapIt->second ;

}

void                            Manager::addFrame                           (   const   Frame&                      aFrame                                      )
{

    std::lock_guard<std::mutex> lock(mutex_) ;

    if (frameMap_.find(aFrame.getName()) == frameMap_.end())
    {
        frameMap_.insert({ aFrame.getName(), std::make_shared<Frame>(aFrame) }) ;
    }

}

void                            Manager::removeFrameWithName                (   const   String&                     aFrameName                                  )
{

    std::lock_guard<std::mutex> lock(mutex_) ;

    auto frameMapIt = frameMap_.find(aFrameName) ;

    if (frameMapIt != frameMap_.end())
    {
        frameMap_.erase(frameMapIt) ;
    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////