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

Sun::Sun(const Shared<Ephemeris>& anEphemeris, const Shared<SunGravitationalModel>& aGravitationalModel)
    : Celestial(
          "Sun",
          Celestial::Type::Sun,
          aGravitationalModel->getParameters().gravitationalParameter_,
          aGravitationalModel->getParameters().equatorialRadius_,
          aGravitationalModel->getParameters().flattening_,
          aGravitationalModel->getParameters().J2_,
          aGravitationalModel->getParameters().J4_,
          anEphemeris,
          aGravitationalModel,
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

    return {
        std::make_shared<SPICE>(SPICE::Object::Sun),
        std::make_shared<SunGravitationalModel>(SunGravitationalModel::Type::Spherical),
    };
}

Object::Geometry Sun::Geometry(const Shared<const Frame>& aFrame)
{
    using ostk::math::geom::d3::objects::Point;

    const Real equatorialRadius_m = SunGravitationalModel::Spherical.equatorialRadius_.inMeters();

    const Sphere sphere = {Point::Origin(), equatorialRadius_m};

    return {sphere, aFrame};
}

}  // namespace celest
}  // namespace obj
}  // namespace env
}  // namespace physics
}  // namespace ostk
