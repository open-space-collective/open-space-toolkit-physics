/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/Static.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Ephemerides/SPICE.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Objects/CelestialBodies/Sun.hpp>

namespace ostk
{
namespace physics
{
namespace env
{
namespace obj
{
namespace celest
{

using ostk::physics::units::Mass;
using ostk::physics::units::Time;
using ostk::physics::units::Angle;

Derived Sun::GravitationalParameter = {
    132712440018e9, Derived::Unit::GravitationalParameter(Length::Unit::Meter, Time::Unit::Second)};
Length Sun::EquatorialRadius = Length::Meters(6.955e8);
Real Sun::Flattening = 0.0;

Sun::Sun(const Shared<Ephemeris>& anEphemeris, const SunGravitationalModel::Type& aGravitationalModelType)
    : Celestial(
          "Sun",
          Celestial::Type::Sun,
          Sun::GravitationalParameter,
          Sun::EquatorialRadius,
          Sun::Flattening,
          0.0,
          0.0,
          anEphemeris,
          std::make_shared<SunGravitationalModel>(aGravitationalModelType),
          nullptr,  // [TBI] Add Sun magnetic model
          nullptr,
          Sun::Geometry(anEphemeris->accessFrame())
      )
{
}

Sun::~Sun() {}

Sun* Sun::clone() const
{
    return new Sun(*this);
}

Sun Sun::Default()
{
    return Sun::Spherical();
}

Sun Sun::Spherical()
{
    using ostk::physics::env::ephem::SPICE;

    return {std::make_shared<SPICE>(SPICE::Object::Sun), SunGravitationalModel::Type::Spherical};
}

Object::Geometry Sun::Geometry(const Shared<const Frame>& aFrame)
{
    using ostk::math::geom::d3::objects::Point;

    const Real equatorialRadius_m = Sun::EquatorialRadius.inMeters();

    const Sphere sphere = {Point::Origin(), equatorialRadius_m};

    return {sphere, aFrame};
}

}  // namespace celest
}  // namespace obj
}  // namespace env
}  // namespace physics
}  // namespace ostk
