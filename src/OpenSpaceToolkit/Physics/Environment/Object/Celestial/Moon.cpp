/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/Static.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Ephemeris/SPICE.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Object/Celestial/Moon.hpp>

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

namespace
{

// The Celestial constructor rejects a null ephemeris, but the arguments below dereference both pointers first.
MoonGravitationalModel::Parameters ParametersOf(const Shared<MoonGravitationalModel>& aGravitationalModel)
{
    if (aGravitationalModel == nullptr)
    {
        throw ostk::core::error::runtime::Undefined("Gravitational model");
    }

    return aGravitationalModel->getParameters();
}

Shared<const Frame> EphemerisFrame(const Shared<Ephemeris>& anEphemeris)
{
    if (anEphemeris == nullptr)
    {
        throw ostk::core::error::runtime::Undefined("Ephemeris");
    }

    return anEphemeris->accessFrame();
}

}  // namespace

Moon::Moon(const Shared<Ephemeris>& anEphemeris, const Shared<MoonGravitationalModel>& aGravitationalModel)
    : Celestial(
          "Moon",
          Celestial::Type::Moon,
          ParametersOf(aGravitationalModel).gravitationalParameter_,
          ParametersOf(aGravitationalModel).equatorialRadius_,
          ParametersOf(aGravitationalModel).flattening_,
          ParametersOf(aGravitationalModel).J2_,
          ParametersOf(aGravitationalModel).J4_,
          anEphemeris,
          aGravitationalModel,
          nullptr,
          nullptr,
          Moon::Geometry(EphemerisFrame(anEphemeris))
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
    using ostk::physics::environment::ephemeris::SPICE;

    return {
        std::make_shared<SPICE>(SPICE::Object::Moon),
        std::make_shared<MoonGravitationalModel>(MoonGravitationalModel::Type::Spherical),
    };
}

Object::Geometry Moon::Geometry(const Shared<const Frame>& aFrame)
{
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::transformation::rotation::Quaternion;

    const double equatorialRadius_m = MoonGravitationalModel::Spherical.equatorialRadius_.inMeters();
    const double polarRadius_m = equatorialRadius_m * (1.0 - MoonGravitationalModel::Spherical.flattening_);

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
