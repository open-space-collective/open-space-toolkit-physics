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

Array<String> Manager::getAllFrameNames() const
{
    const std::lock_guard<std::mutex> lock {mutex_};

    Array<String> frameNames;
    frameNames.reserve(frameMap_.size());
    for (const auto& frame : frameMap_)
    {
        frameNames.add(frame.first);
    }
    return frameNames;
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
            if (const Transform* transformPtr = transformCacheToFrameIt->second.accessTransformAt(anInstant))
            {
                return (*transformPtr);
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

void Manager::clearAllFrames()
{
    const std::lock_guard<std::mutex> lock {mutex_};

    frameMap_.clear();
    transformCache_.clear();
}

void Manager::addCachedTransform(
    const Shared<const Frame>& aFromFrameSPtr,
    const Shared<const Frame>& aToFrameSPtr,
    const Instant& anInstant,
    const Transform& aTransform
)
{
    const std::lock_guard<std::mutex> lock {mutex_};

    this->accessTransformCache(aFromFrameSPtr.get(), aToFrameSPtr.get()).addTransformAt(anInstant, aTransform);

    // Eagerly cache the reverse transform (toFrame -> fromFrame -> instant)

    this->accessTransformCache(aToFrameSPtr.get(), aFromFrameSPtr.get())
        .addTransformAt(anInstant, aTransform.getInverse());
}

Size Manager::getMaxTransformCacheSize() const
{
    const std::lock_guard<std::mutex> lock {mutex_};

    return maxTransformCacheSize_;
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

Manager::Manager(const Size& aMaxTransformCacheSize)
    : maxTransformCacheSize_(aMaxTransformCacheSize)
{
}

Manager::TransformCache& Manager::accessTransformCache(const Frame* aFromFramePtr, const Frame* aToFramePtr) const
{
    auto& toFrameTransformCacheMap = transformCache_[aFromFramePtr];

    return toFrameTransformCacheMap.try_emplace(aToFramePtr, maxTransformCacheSize_).first->second;
}

Manager::TransformCache::TransformCache(const Size& aMaxSize)
    : maxSize_(aMaxSize)
{
}

const Transform* Manager::TransformCache::accessTransformAt(const Instant& anInstant)
{
    const auto entryMapIt = entryMap_.find(anInstant);

    if (entryMapIt == entryMap_.end())
    {
        return nullptr;
    }

    // Mark the entry as the most recently used one

    entryList_.splice(entryList_.begin(), entryList_, entryMapIt->second);

    return &(entryMapIt->second->second);
}

void Manager::TransformCache::addTransformAt(const Instant& anInstant, const Transform& aTransform)
{
    if (maxSize_ == 0)
    {
        return;
    }

    const auto entryMapIt = entryMap_.find(anInstant);

    if (entryMapIt != entryMap_.end())
    {
        // Replace the cached transform, and mark it as the most recently used one

        entryMapIt->second->second = aTransform;

        entryList_.splice(entryList_.begin(), entryList_, entryMapIt->second);

        return;
    }

    // Evict the least recently used entries, if the cache is full

    while (entryList_.size() >= maxSize_)
    {
        entryMap_.erase(entryList_.back().first);
        entryList_.pop_back();
    }

    entryList_.emplace_front(anInstant, aTransform);
    entryMap_.emplace(anInstant, entryList_.begin());
}

}  // namespace frame
}  // namespace coordinate
}  // namespace physics
}  // namespace ostk
