/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_Dynamic__
#define __OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_Dynamic__

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Transform.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

namespace ostk
{
namespace physics
{
namespace coord
{
namespace frame
{
namespace provider
{

using ostk::physics::time::Instant;
using ostk::physics::coord::frame::Provider;
using ostk::physics::coord::Transform;

/// @brief                      Dynamic provider

class Dynamic : public Provider
{
   public:
    typedef std::function<Transform(const Instant&)> Generator;

    Dynamic(const Dynamic::Generator& aGenerator);

    virtual ~Dynamic() override;

    virtual Dynamic* clone() const override;

    virtual bool isDefined() const override;

    virtual Transform getTransformAt(const Instant& anInstant) const override;

    static Dynamic Undefined();

   private:
    Dynamic::Generator generator_;
};

}  // namespace provider
}  // namespace frame
}  // namespace coord
}  // namespace physics
}  // namespace ostk

#endif
