/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Model.hpp>

namespace ostk
{
namespace physics
{
namespace environment
{
namespace atmospheric
{

Model::Model() {}

Model::~Model() {}

Real Model::getDensityAt(const Position& aPosition, const Instant& anInstant, const Position& aSunPosition) const{
    (void)aPosition;
    (void)anInstant;
    (void)aSunPosition;
    return 0.0;
}

}  // namespace atmospheric
}  // namespace environment
}  // namespace physics
}  // namespace ostk
