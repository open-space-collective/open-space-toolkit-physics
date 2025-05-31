/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Manager.hpp>

namespace ostk
{
namespace physics
{
namespace coordinate
{
namespace frame
{

bool Manager::hasFrameWithName(const String& aFrameName) const
{
    const std::lock_guard<std::mutex> lock {mutex_};

    return frameMap_.find(aFrameName) != frameMap_.end();
}

Shared<const Frame> Manager::accessFrameWithName(const String& aFrameName) const
{
    const std::lock_guard<std::mutex> lock {mutex_};

    const auto frameMapIt = frameMap_.find(aFrameName);

    if (frameMapIt != frameMap_.end())
    {
        return frameMapIt->second;
    }

    // throw ostk::core::error::RuntimeError("Cannot access frame with name [{}].", aFrameName) ;

    return nullptr;
}

const Transform Manager::accessCachedTransform(
    const Shared<const Frame>& aFromFrameSPtr, const Shared<const Frame>& aToFrameSPtr, const Instant& anInstant
) const
{
    const std::lock_guard<std::mutex> lock {mutex_};

    const auto transformCacheFromFrameIt = transformCache_.find(aFromFrameSPtr.get());

    if (transformCacheFromFrameIt != transformCache_.end())
    {
        const auto transformCacheToFrameIt = transformCacheFromFrameIt->second.find(aToFrameSPtr.get());

        if (transformCacheToFrameIt != transformCacheFromFrameIt->second.end())
        {
            const auto transformCacheInstantIt = transformCacheToFrameIt->second.find(anInstant);

            if (transformCacheInstantIt != transformCacheToFrameIt->second.end())
            {
                return (transformCacheInstantIt->second);
            }
        }
    }

    return Transform::Undefined();
}

void Manager::addFrame(const Shared<const Frame>& aFrameSPtr)
{
    if (aFrameSPtr == nullptr)
    {
        throw ostk::core::error::runtime::Undefined("Frame");
    }

    const std::lock_guard<std::mutex> lock {mutex_};

    if (frameMap_.find(aFrameSPtr->getName()) == frameMap_.end())
    {
        frameMap_.insert({aFrameSPtr->getName(), aFrameSPtr});
    }
}

void Manager::removeFrameWithName(const String& aFrameName)
{
    const std::lock_guard<std::mutex> lock {mutex_};

    const auto frameMapIt = frameMap_.find(aFrameName);

    if (frameMapIt != frameMap_.end())
    {
        const Frame* framePtr = frameMapIt->second.get();

        // Delete related cached transforms

        const auto transformCacheFromFrameIt = transformCache_.find(framePtr);

        if (transformCacheFromFrameIt != transformCache_.end())
        {
            transformCache_.erase(transformCacheFromFrameIt);
        }

        for (auto& transformCacheIt : transformCache_)
        {
            const auto transformCacheToFrameIt = transformCacheIt.second.find(framePtr);

            if (transformCacheToFrameIt != transformCacheIt.second.end())
            {
                transformCacheIt.second.erase(transformCacheToFrameIt);
            }
        }

        // Delete frame

        frameMap_.erase(frameMapIt);
    }
    else
    {
        throw ostk::core::error::RuntimeError("No frame with name [{}].", aFrameName);
    }
}

void Manager::addCachedTransform(
    const Shared<const Frame>& aFromFrameSPtr,
    const Shared<const Frame>& aToFrameSPtr,
    const Instant& anInstant,
    const Transform& aTransform
)
{
    const std::lock_guard<std::mutex> lock {mutex_};

    if (transformCache_.size() > maxTransformCacheSize_)
    {
        transformCache_.clear();
    }

    const auto transformCacheFromFrameIt = transformCache_.insert({aFromFrameSPtr.get(), {}}).first;
    const auto transformCacheToFrameIt = transformCacheFromFrameIt->second.insert({aToFrameSPtr.get(), {}}).first;
    const auto transformCacheToInstantIt = transformCacheToFrameIt->second.insert({anInstant, aTransform}).first;

    (void)transformCacheToInstantIt;
}

Manager& Manager::Get()
{
    static Size maxTransformCacheSize = []()
    {
        const char* maxTransformCacheSizeEnv = std::getenv("OSTK_PHYSICS_FRAME_MANAGER_MAX_TRANSFORM_CACHE_SIZE");

        Size value = 1000;

        if (maxTransformCacheSizeEnv != nullptr)
        {
            try
            {
                value = std::stoul(maxTransformCacheSizeEnv);
            }
            catch (const std::exception& e)
            {
                throw ostk::core::error::RuntimeError(
                    "Invalid value for OSTK_PHYSICS_FRAME_MANAGER_MAX_TRANSFORM_CACHE_SIZE: {}", e.what()
                );
            }
        }
        return value;
    }();

    static Manager manager {maxTransformCacheSize};

    return manager;
}

Manager::Manager(const Size& maxTransformCacheSize)
    : maxTransformCacheSize_(maxTransformCacheSize)
{
}

}  // namespace frame
}  // namespace coordinate
}  // namespace physics
}  // namespace ostk
