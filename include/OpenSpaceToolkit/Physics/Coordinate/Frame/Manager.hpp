/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Coordinate_Frame_Manager__
#define __OpenSpaceToolkit_Physics_Coordinate_Frame_Manager__

#include <mutex>

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

using ostk::core::type::Shared;
using ostk::core::type::String;
using ostk::core::container::Map;

using ostk::physics::time::Instant;
using ostk::physics::coordinate::Frame;
using ostk::physics::coordinate::Transform;

/// @brief                      Reference frame manager (thread-safe)

class Manager
{
   public:
    Manager(const Manager& aManager) = delete;

    Manager& operator=(const Manager& aManager) = delete;

    bool hasFrameWithName(const String& aFrameName) const;

    Shared<const Frame> accessFrameWithName(const String& aFrameName) const;

    const Transform* accessCachedTransform(
        const Shared<const Frame>& aFromFrameSPtr, const Shared<const Frame>& aToFrameSPtr, const Instant& anInstant
    ) const;

    void addFrame(const Shared<const Frame>& aFrameSPtr);

    void removeFrameWithName(const String& aFrameName);

    void addCachedTransform(
        const Shared<const Frame>& aFromFrameSPtr,
        const Shared<const Frame>& aToFrameSPtr,
        const Instant& anInstant,
        const Transform& aTransform
    );

    static Manager& Get();

   private:
    Map<String, Shared<const Frame>> frameMap_;

    Map<const Frame*, Map<const Frame*, Map<Instant, Transform>>> transformCache_;

    mutable std::mutex mutex_;

    Manager() = default;
};

}  // namespace frame
}  // namespace coordinate
}  // namespace physics
}  // namespace ostk

#endif
