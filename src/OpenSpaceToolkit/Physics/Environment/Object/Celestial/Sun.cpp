/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/Static.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Ephemeris/SPICE.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Object/Celestial/Sun.hpp>

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
SunGravitationalModel::Parameters ParametersOf(const Shared<SunGravitationalModel>& aGravitationalModel)
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

Sun::Sun(const Shared<Ephemeris>& anEphemeris, const Shared<SunGravitationalModel>& aGravitationalModel)
    : Celestial(
          "Sun",
          Celestial::Type::Sun,
          ParametersOf(aGravitationalModel).gravitationalParameter_,
          ParametersOf(aGravitationalModel).equatorialRadius_,
          ParametersOf(aGravitationalModel).flattening_,
          ParametersOf(aGravitationalModel).J2_,
          ParametersOf(aGravitationalModel).J4_,
          anEphemeris,
          aGravitationalModel,
          nullptr,  // [TBI] Add Sun magnetic model
          nullptr,
          Sun::Geometry(EphemerisFrame(anEphemeris))
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
    const double equatorialRadius_m = SunGravitationalModel::Spherical.equatorialRadius_.inMeters();

    const Sphere sphere = {Point::Origin(), equatorialRadius_m};

    return {sphere, aFrame};
}

}  // namespace celestial
}  // namespace object
}  // namespace environment
}  // namespace physics
}  // namespace ostk
