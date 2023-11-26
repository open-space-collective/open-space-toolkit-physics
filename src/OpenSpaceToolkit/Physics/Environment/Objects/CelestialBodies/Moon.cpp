/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/Static.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Ephemerides/SPICE.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Objects/CelestialBodies/Moon.hpp>

namespace ostk
{
namespace physics
{
namespace environment
{
namespace object
{
namespace celestial
{

Moon::Moon(const Shared<Ephemeris>& anEphemeris, const Shared<MoonGravitationalModel>& aGravitationalModel)
    : Celestial(
          "Moon",
          Celestial::Type::Moon,
          aGravitationalModel->getParameters().gravitationalParameter_,
          aGravitationalModel->getParameters().equatorialRadius_,
          aGravitationalModel->getParameters().flattening_,
          aGravitationalModel->getParameters().J2_,
          aGravitationalModel->getParameters().J4_,
          anEphemeris,
          aGravitationalModel,
          nullptr,
          nullptr,
          Moon::Geometry(anEphemeris->accessFrame())
      )
{
}

Moon::~Moon() {}

Moon* Moon::clone() const
{
    return new Moon(*this);
}

Moon Moon::Default()
{
    return Moon::Spherical();
}

Moon Moon::Spherical()
{
    using ostk::physics::environment::ephemerides::SPICE;

    return {
        std::make_shared<SPICE>(SPICE::Object::Moon),
        std::make_shared<MoonGravitationalModel>(MoonGravitationalModel::Type::Spherical),
    };
}

Object::Geometry Moon::Geometry(const Shared<const Frame>& aFrame)
{
    using ostk::math::geometry::d3::objects::Point;
    using ostk::math::geometry::d3::transformations::rotations::Quaternion;

    const Real equatorialRadius_m = MoonGravitationalModel::Spherical.equatorialRadius_.inMeters();
    const Real polarRadius_m = equatorialRadius_m * (1.0 - MoonGravitationalModel::Spherical.flattening_);

    const Ellipsoid ellipsoid = {
        Point::Origin(),
        equatorialRadius_m,
        equatorialRadius_m,
        polarRadius_m,
        Quaternion::Unit(),
    };

    return {ellipsoid, aFrame};
}

}  // namespace celestial
}  // namespace object
}  // namespace environment
}  // namespace physics
}  // namespace ostk
