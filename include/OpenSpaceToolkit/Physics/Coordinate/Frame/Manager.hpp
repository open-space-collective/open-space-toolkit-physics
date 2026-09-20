/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Coordinate_Frame_Manager__
#define __OpenSpaceToolkit_Physics_Coordinate_Frame_Manager__

#include <list>
#include <mutex>
#include <unordered_map>
#include <utility>

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Container/Map.hpp>
#include <OpenSpaceToolkit/Core/Type/Shared.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Transform.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

namespace ostk
{
namespace physics
{
namespace coordinate
{
namespace frame
{

using ostk::core::container::Array;
using ostk::core::container::Map;
using ostk::core::type::Shared;
using ostk::core::type::Size;
using ostk::core::type::String;

using ostk::physics::coordinate::Frame;
using ostk::physics::coordinate::Transform;
using ostk::physics::time::Instant;

/// @brief Reference frame manager (thread-safe)
///
/// Transforms are cached per frame pair, using a Least Recently Used (LRU) strategy: once the cache of a frame
/// pair is full, adding a transform evicts the least recently used one.

class Manager
{
   public:
    Manager(const Manager& aManager) = delete;

    Manager& operator=(const Manager& aManager) = delete;

    /// @brief Check if a frame with the given name exists.
    ///
    /// @code
    ///     Manager::Get().hasFrameWithName("GCRF"); // True
    /// @endcode
    ///
    /// @param [in] aFrameName A frame name
    /// @return True if a frame with the given name exists

    bool hasFrameWithName(const String& aFrameName) const;

    /// @brief Access frame with the given name.
    ///
    /// @code
    ///     Shared<const Frame> frameSPtr = Manager::Get().accessFrameWithName("GCRF");
    /// @endcode
    ///
    /// @param [in] aFrameName A frame name
    /// @return Shared pointer to the frame

    Shared<const Frame> accessFrameWithName(const String& aFrameName) const;

    /// @brief Get names of all registered frames.
    ///
    /// @code
    ///     Array<String> frameNames = Manager::Get().getAllFrameNames();
    /// @endcode
    ///
    /// @return Array of frame names

    Array<String> getAllFrameNames() const;

    /// @brief Access a cached transform between two frames at a given instant.
    ///
    /// @code
    ///     Transform transform = Manager::Get().accessCachedTransform(fromFrameSPtr, toFrameSPtr, instant);
    /// @endcode
    ///
    /// @param [in] aFromFrameSPtr A shared pointer to the source frame
    /// @param [in] aToFrameSPtr A shared pointer to the destination frame
    /// @param [in] anInstant An instant
    /// @return The cached transform

    const Transform accessCachedTransform(
        const Shared<const Frame>& aFromFrameSPtr, const Shared<const Frame>& aToFrameSPtr, const Instant& anInstant
    ) const;

    /// @brief Add a frame to the manager.
    ///
    /// @code
    ///     Manager::Get().addFrame(frameSPtr);
    /// @endcode
    ///
    /// @param [in] aFrameSPtr A shared pointer to the frame

    void addFrame(const Shared<const Frame>& aFrameSPtr);

    /// @brief Remove a frame with the given name.
    ///
    /// @code
    ///     Manager::Get().removeFrameWithName("MyCustomFrame");
    /// @endcode
    ///
    /// @param [in] aFrameName A frame name

    void removeFrameWithName(const String& aFrameName);

    /// @brief Remove all registered frames.
    ///
    /// @code
    ///     Manager::Get().clearAllFrames();
    /// @endcode

    void clearAllFrames();

    /// @brief Add a transform to the cache.
    ///
    /// @code
    ///     Manager::Get().addCachedTransform(fromFrameSPtr, toFrameSPtr, instant, transform);
    /// @endcode
    ///
    /// @param [in] aFromFrameSPtr A shared pointer to the source frame
    /// @param [in] aToFrameSPtr A shared pointer to the destination frame
    /// @param [in] anInstant An instant
    /// @param [in] aTransform A transform

    void addCachedTransform(
        const Shared<const Frame>& aFromFrameSPtr,
        const Shared<const Frame>& aToFrameSPtr,
        const Instant& anInstant,
        const Transform& aTransform
    );

    /// @brief Get the maximum number of transforms cached per frame pair.
    ///
    /// @code
    ///     Size maxTransformCacheSize = Manager::Get().getMaxTransformCacheSize();
    /// @endcode
    ///
    /// @return The maximum number of transforms cached per frame pair

    Size getMaxTransformCacheSize() const;

    /// @brief Get the manager singleton.
    ///
    /// @code
    ///     Manager& manager = Manager::Get();
    /// @endcode
    ///
    /// @return Reference to the manager

    static Manager& Get();

   private:
    /// @brief Least Recently Used (LRU) cache of transforms, for a single frame pair
    ///
    /// Once the cache is full, adding a transform evicts the least recently used one.

    class TransformCache
    {
       public:
        TransformCache(const Size& aMaxSize);

        /// @brief Access the transform cached at a given instant, marking it as most recently used.
        ///
        /// @param [in] anInstant An instant
        /// @return Pointer to the cached transform, or null pointer if no transform is cached at that instant

        const Transform* accessTransformAt(const Instant& anInstant);

        /// @brief Add a transform at a given instant, evicting the least recently used one if the cache is full.
        ///
        /// @param [in] anInstant An instant
        /// @param [in] aTransform A transform

        void addTransformAt(const Instant& anInstant, const Transform& aTransform);

       private:
        using Entry = std::pair<Instant, Transform>;
        using EntryList = std::list<Entry>;

        Size maxSize_;

        EntryList entryList_;  // Most recently used entry at the front

        std::unordered_map<Instant, EntryList::iterator> entryMap_;
    };

    Size maxTransformCacheSize_;
    Map<String, Shared<const Frame>> frameMap_;

    mutable Map<const Frame*, Map<const Frame*, TransformCache>> transformCache_;

    mutable std::mutex mutex_;

    Manager(const Size& aMaxTransformCacheSize);

    TransformCache& accessTransformCache(const Frame* aFromFramePtr, const Frame* aToFramePtr) const;
};

}  // namespace frame
}  // namespace coordinate
}  // namespace physics
}  // namespace ostk

#endif
