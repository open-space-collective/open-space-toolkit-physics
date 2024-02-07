/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Container/Map.hpp>
#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Ephemerides/SPICE.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Ephemerides/SPICE/Engine.hpp>

namespace ostk
{
namespace physics
{
namespace environment
{
namespace ephemerides
{

SPICE::SPICE(const SPICE::Object& anObject)
    : object_(anObject)
{
}

SPICE::~SPICE() {}

SPICE* SPICE::clone() const
{
    return new SPICE(*this);
}

bool SPICE::isDefined() const
{
    return object_ != SPICE::Object::Undefined;
}

Shared<const Frame> SPICE::accessFrame() const
{
    using ostk::physics::environment::ephemerides::spice::Engine;

    return Engine::Get().getFrameOf(object_);
}

String SPICE::StringFromObject(const SPICE::Object& anObject)
{
    using ostk::core::container::Map;

    static const Map<SPICE::Object, String> objectStringMap = {
        {SPICE::Object::Undefined, "Undefined"},
        {SPICE::Object::Sun, "Sun"},
        {SPICE::Object::Mercury, "Mercury"},
        {SPICE::Object::Venus, "Venus"},
        {SPICE::Object::Earth, "Earth"},
        {SPICE::Object::Moon, "Moon"},
        {SPICE::Object::Mars, "Mars"},
        {SPICE::Object::Jupiter, "Jupiter"},
        {SPICE::Object::Saturn, "Saturn"},
        {SPICE::Object::Uranus, "Uranus"},
        {SPICE::Object::Neptune, "Neptune"}
    };

    return objectStringMap.at(anObject);
}

}  // namespace ephemerides
}  // namespace environment
}  // namespace physics
}  // namespace ostk
