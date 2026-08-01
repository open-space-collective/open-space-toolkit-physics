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

using ostk::core::type::Real;
using ostk::core::type::Shared;

using ostk::mathematics::geometry::d3::object::Sphere;

using ostk::physics::coordinate::Position;
using ostk::physics::environment::Ephemeris;
using ostk::physics::environment::Object;
using ostk::physics::environment::object::Celestial;
using ostk::physics::time::Instant;
using ostk::physics::unit::Derived;
using ostk::physics::unit::Length;
using SunGravitationalModel = ostk::physics::environment::gravitational::Sun;

class Sun : public Celestial
{
   public:
    /// @brief Constructor
    ///
    /// @code
    ///     Sun sun(ephemeris, gravModel);
    /// @endcode
    ///
    /// @param [in] anEphemeris An ephemeris for the Sun celestial object
    /// @param [in] aGravitationalModel A shared pointer to a gravitational model for the Sun celestial object
    Sun(const Shared<Ephemeris>& anEphemeris, const Shared<SunGravitationalModel>& aGravitationalModel);

    /// @brief Destructor
    virtual ~Sun() override;

    /// @brief Clone the Sun celestial object
    ///
    /// @code
    ///     Sun* sunPtr = sun.clone();
    /// @endcode
    ///
    /// @return Pointer to Sun celestial object
    virtual Sun* clone() const override;

    /// @brief Compute the Sun position from a fast low-precision analytical model, in GCRF
    ///
    /// The position is computed from the analytical series of Montenbruck & Gill, with respect to the mean
    /// equator and equinox of J2000, which is treated as GCRF (the frame bias of ~23 mas is far below the
    /// accuracy of the series).
    ///
    /// Accuracy with respect to high-precision (JPL DE) ephemerides, measured over 2020-2026:
    /// < 0.1 deg in direction, < 0.01% in distance. The dominant error is a slow drift (~11.6 arcsec/year)
    /// due to the neglected motion of the Earth's perihelion.
    ///
    /// This is orders of magnitude faster than a SPICE-based ephemeris, requires no ephemeris data,
    /// and is well-suited for applications such as third-body point-mass gravity
    /// where only an approximate body position is needed.
    ///
    /// @code
    ///     Position position = sun.computeAnalyticalPosition(instant);
    /// @endcode
    ///
    /// @ref O. Montenbruck, E. Gill, "Satellite Orbits: Models, Methods and Applications", Section 3.3.2.
    ///
    /// @param [in] anInstant An instant
    /// @return Position of the Sun, in GCRF
    virtual Position computeAnalyticalPosition(const Instant& anInstant) const override;

    /// @brief Default Sun model (Spherical)
    ///
    /// @code
    ///     Sun sun = Sun::Default();
    /// @endcode
    ///
    /// @return Sun
    static Sun Default();

    /// @brief Spherical gravitational model with a high-precision SPICE based ephemeris
    ///
    /// @code
    ///     Sun sun = Sun::Spherical();
    /// @endcode
    ///
    /// @return Sun
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
