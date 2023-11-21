/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Data_Providers_Nadir__
#define __OpenSpaceToolkit_Physics_Data_Providers_Nadir__

#include <OpenSpaceToolkit/Physics/Coordinate/Position.hpp>
#include <OpenSpaceToolkit/Physics/Data/Direction.hpp>
#include <OpenSpaceToolkit/Physics/Environment.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Objects/Celestial.hpp>

namespace ostk
{
namespace physics
{
namespace data
{
namespace providers
{

using ostk::physics::data::Direction;
using ostk::physics::coord::Position;
using ostk::physics::Environment;
using ostk::physics::environment::object::Celestial;

Direction Nadir(const Position& aPosition, const Celestial& aCelestialObject, const Environment& anEnvironment);

}  // namespace providers
}  // namespace data
}  // namespace physics
}  // namespace ostk

#endif
