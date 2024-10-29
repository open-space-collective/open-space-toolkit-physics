/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Coordinate_Frame__
#define __OpenSpaceToolkit_Physics_Coordinate_Frame__

#include <memory>

#include <OpenSpaceToolkit/Core/Type/Integer.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>
#include <OpenSpaceToolkit/Core/Type/Shared.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Axes.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/IAU/Theory.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Position.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Transform.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Velocity.hpp>

namespace ostk
{
namespace physics
{
namespace coordinate
{

namespace iau = ostk::physics::coordinate::frame::provider::iau;

using ostk::core::type::Real;
using ostk::core::type::Shared;
using ostk::core::type::String;
using ostk::core::type::Uint8;

using ostk::mathematics::object::Vector3d;

using ostk::physics::coordinate::Axes;
using ostk::physics::coordinate::frame::Provider;
using ostk::physics::coordinate::Position;
using ostk::physics::coordinate::Transform;
using ostk::physics::coordinate::Velocity;

/// @brief                      Reference frame
///
/// @ref                        https://en.wikipedia.org/wiki/Frame_of_reference
/// @note                       Implementation heavily inspired by (the great!)
/// https://www.orekit.org/static/architecture/frames.html

class Frame : public std::enable_shared_from_this<Frame>
{
   public:
    /// @brief              Destructor

    ~Frame();

    bool operator==(const Frame& aFrame) const;

    bool operator!=(const Frame& aFrame) const;

    friend std::ostream& operator<<(std::ostream& anOutputStream, const Frame& aFrame);

    bool isDefined() const;

    bool isQuasiInertial() const;

    bool hasParent() const;

    Shared<const Frame> accessParent() const;

    Shared<const Frame> accessAncestor(const Uint8 anAncestorDegree) const;

    Shared<const Provider> accessProvider() const;

    String getName() const;

    Position getOriginIn(const Shared<const Frame>& aFrame, const Instant& anInstant) const;

    Velocity getVelocityIn(const Shared<const Frame>& aFrame, const Instant& anInstant) const;

    Axes getAxesIn(const Shared<const Frame>& aFrame, const Instant& anInstant) const;

    Transform getTransformTo(const Shared<const Frame>& aFrame, const Instant& anInstant) const;

    static Shared<const Frame> Undefined();

    static Shared<const Frame> GCRF();

    static Shared<const Frame> J2000(const iau::Theory& aTheory);

    static Shared<const Frame> MOD(const Instant& anEpoch);

    static Shared<const Frame> TOD(const Instant& anEpoch, const iau::Theory& aTheory);

    static Shared<const Frame> TEME();

    static Shared<const Frame> TEMEOfEpoch(const Instant& anEpoch);

    static Shared<const Frame> CIRF();

    static Shared<const Frame> TIRF();

    static Shared<const Frame> ITRF();

    static Shared<const Frame> WithName(const String& aName);

    static bool Exists(const String& aName);

    /// @brief              Constructor
    ///
    /// @param              [in] aName A frame name
    /// @param              [in] isQuasiInertialT True is frame is quasi-inertial
    /// @param              [in] aParentFrame A shared pointer to the parent frame
    /// @param              [in] aProvider A shared pointer to the transform provider

    static Shared<const Frame> Construct(
        const String& aName,
        bool isQuasiInertial,
        const Shared<const Frame>& aParentFrame,
        const Shared<const Provider>& aProvider
    );

    static void Destruct(const String& aName);

   protected:
    Frame(
        const String& aName,
        bool isQuasiInertial,
        const Shared<const Frame>& aParentFrame,
        const Shared<const Provider>& aProvider
    );

    Frame(const Frame& aFrame) = default;

    Frame& operator=(const Frame& aFrame) = default;

   private:
    String name_;
    bool quasiInertial_;
    Shared<const Frame> parentFrameSPtr_;
    Shared<const Provider> providerSPtr_;  // Provides transform from parent to instance -> Unique<> instead?

    Uint8 getDepth() const;

    static Shared<const Frame> Emplace(
        const String& aName,
        bool isQuasiInertial,
        const Shared<const Frame>& aParentFrame,
        const Shared<const Provider>& aProvider
    );

    static Shared<const Frame> FindCommonAncestor(
        const Shared<const Frame>& aFirstFrameSPtr, const Shared<const Frame>& aSecondFrameSPtr
    );
};

}  // namespace coordinate
}  // namespace physics
}  // namespace ostk

#endif
