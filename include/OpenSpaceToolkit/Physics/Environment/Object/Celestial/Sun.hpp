/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Environment_Object_Celestial_Sun__
#define __OpenSpaceToolkit_Physics_Environment_Object_Celestial_Sun__

#include <OpenSpaceToolkit/Core/Type/Real.hpp>
#include <OpenSpaceToolkit/Core/Type/Shared.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Sphere.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Ephemeris.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Sun.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Object.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Object/Celestial.hpp>
#include <OpenSpaceToolkit/Physics/Unit/Derived.hpp>
#include <OpenSpaceToolkit/Physics/Unit/Length.hpp>

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

using ostk::core::type::Shared;
using ostk::core::type::Real;

using ostk::mathematics::geometry::d3::object::Sphere;

using ostk::physics::unit::Length;
using ostk::physics::unit::Derived;
using ostk::physics::environment::Ephemeris;
using ostk::physics::environment::Object;
using ostk::physics::environment::object::Celestial;
using SunGravitationalModel = ostk::physics::environment::gravitational::Sun;

class Sun : public Celestial
{
   public:
    /// @brief              Constructor
    ///
    /// @param              [in] anEphemeris An ephemeris for the Sun celestial object
    /// @param              [in] aGravitationalModel A shared pointer to a gravitational model for the Sun celestial
    /// object

    Sun(const Shared<Ephemeris>& anEphemeris, const Shared<SunGravitationalModel>& aGravitationalModel);

    /// @brief              Destructor

    virtual ~Sun() override;

    /// @brief              Clone the Sun celestial object
    ///
    /// @return             Pointer to Sun celestial object

    virtual Sun* clone() const override;

    /// @brief              Default Sun model (Spherical)
    ///
    /// @return             Sun

    static Sun Default();

    /// @brief              Spherical model
    ///
    /// @return             Sun

    static Sun Spherical();

   private:
    static Object::Geometry Geometry(const Shared<const Frame>& aFrameSPtr);
};

}  // namespace celestial
}  // namespace object
}  // namespace environment
}  // namespace physics
}  // namespace ostk

#endif
