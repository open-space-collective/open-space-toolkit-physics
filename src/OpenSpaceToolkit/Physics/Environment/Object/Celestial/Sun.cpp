/// Apache License 2.0

#include <cmath>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/Static.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Ephemeris/SPICE.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Object/Celestial/Sun.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Object/Celestial/Utility.hpp>

using ostk::physics::environment::object::celestial::utilities::EquatorialFromEcliptic;
using ostk::physics::environment::object::celestial::utilities::FractionalPart;
using ostk::physics::environment::object::celestial::utilities::JulianCenturiesSinceJ2000;

namespace
{

constexpr double TwoPi = 2.0 * M_PI;

}  // namespace

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

Position Sun::computeAnalyticalPosition(const Instant& anInstant) const
{
    // Accuracy: < 0.1 deg in direction over 2020-2026,
    // dominated by a slow drift (~11.6 arcsec/year) due to the neglected motion of the Earth's perihelion.

    if (!anInstant.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

    const double T = JulianCenturiesSinceJ2000(anInstant);

    // Mean anomaly, ecliptic longitude and radius

    const double M = TwoPi * FractionalPart(0.9931267 + 99.9973583 * T);  // [rad]
    const double L = TwoPi * FractionalPart(
                                 0.7859444 + (M / TwoPi) + (6892.0 * std::sin(M) + 72.0 * std::sin(2.0 * M)) / 1296.0e3
                             );                                                        // [rad]
    const double r = 149.619e9 - 2.499e9 * std::cos(M) - 0.021e9 * std::cos(2.0 * M);  // [m]

    // Equatorial position vector

    return Position::Meters(EquatorialFromEcliptic({r * std::cos(L), r * std::sin(L), 0.0}), Frame::GCRF());
}

Sun Sun::Default()
{
    return Sun::Spherical();
}

Sun Sun::Spherical()
{
    using ostk::physics::environment::ephemeris::SPICE;

    return {
        std::make_shared<SPICE>(SPICE::Object::Sun),
        std::make_shared<SunGravitationalModel>(SunGravitationalModel::Type::Spherical),
    };
}

Object::Geometry Sun::Geometry(const Shared<const Frame>& aFrame)
{
    using ostk::mathematics::geometry::d3::object::Point;

    // [TBI] inherit from actual gravitational model if present
    const Real equatorialRadius_m = SunGravitationalModel::Spherical.equatorialRadius_.inMeters();

    const Sphere sphere = {Point::Origin(), equatorialRadius_m};

    return {sphere, aFrame};
}

}  // namespace celestial
}  // namespace object
}  // namespace environment
}  // namespace physics
}  // namespace ostk
