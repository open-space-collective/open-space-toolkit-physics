/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Coordinate_Frame_Manager__
#define __OpenSpaceToolkit_Physics_Coordinate_Frame_Manager__

#include <mutex>

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

    /// @brief Get the manager singleton.
    ///
    /// @code
    ///     Manager& manager = Manager::Get();
    /// @endcode
    ///
    /// @return Reference to the manager

    static Manager& Get();

   private:
    Size maxTransformCacheSize_;
    Map<String, Shared<const Frame>> frameMap_;

    Map<const Frame*, Map<const Frame*, Map<Instant, Transform>>> transformCache_;

    mutable std::mutex mutex_;

    Manager(const Size& aMaxTransformCacheSize);
};

}  // namespace frame
}  // namespace coordinate
}  // namespace physics
}  // namespace ostk

#endif
