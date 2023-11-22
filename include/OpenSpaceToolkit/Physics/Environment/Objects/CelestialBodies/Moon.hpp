/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Environment_Objects_CelestialBodies_Moon__
#define __OpenSpaceToolkit_Physics_Environment_Objects_CelestialBodies_Moon__

#include <OpenSpaceToolkit/Core/Types/Real.hpp>
#include <OpenSpaceToolkit/Core/Types/Shared.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Ellipsoid.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Ephemeris.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Moon.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Object.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Objects/Celestial.hpp>
#include <OpenSpaceToolkit/Physics/Units/Derived.hpp>
#include <OpenSpaceToolkit/Physics/Units/Length.hpp>

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

using ostk::core::types::Shared;
using ostk::core::types::Real;

using ostk::math::geometry::d3::objects::Ellipsoid;

using ostk::physics::units::Length;
using ostk::physics::units::Derived;
using ostk::physics::environment::Ephemeris;
using ostk::physics::environment::Object;
using ostk::physics::environment::object::Celestial;
using MoonGravitationalModel = ostk::physics::environment::gravitational::Moon;

class Moon : public Celestial
{
   public:
    /// @brief              Constructor
    ///
    /// @param              [in] anEphemeris An ephemeris for the Moon celestial object
    /// @param              [in] aGravitationalModel A gravitational model for the Moon celestial object
    /// (Spherical model only)

    Moon(const Shared<Ephemeris>& anEphemeris, const Shared<MoonGravitationalModel>& aGravitationalModel);

    /// @brief              Destructor

    virtual ~Moon() override;

    /// @brief              Clone the Moon celestial object
    ///
    /// @return             Pointer to Moon celestial object

    virtual Moon* clone() const override;

    /// @brief              Default Moon model (Spherical)
    ///
    /// @return             Moon

    static Moon Default();

    /// @brief              Spherical model
    ///
    /// @return             Moon

    static Moon Spherical();

   private:
    static Object::Geometry Geometry(const Shared<const Frame>& aFrameSPtr);
};

}  // namespace celestial
}  // namespace object
}  // namespace environment
}  // namespace physics
}  // namespace ostk

#endif
