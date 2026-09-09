/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Environment_Object_Celestial_Moon__
#define __OpenSpaceToolkit_Physics_Environment_Object_Celestial_Moon__

#include <OpenSpaceToolkit/Core/Type/Real.hpp>
#include <OpenSpaceToolkit/Core/Type/Shared.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Ellipsoid.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Ephemeris.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Moon.hpp>
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

using ostk::mathematics::geometry::d3::object::Ellipsoid;

using ostk::physics::coordinate::Position;
using ostk::physics::environment::Ephemeris;
using ostk::physics::environment::Object;
using ostk::physics::environment::object::Celestial;
using ostk::physics::time::Instant;
using ostk::physics::unit::Derived;
using ostk::physics::unit::Length;
using MoonGravitationalModel = ostk::physics::environment::gravitational::Moon;

class Moon : public Celestial
{
   public:
    /// @brief Constructor
    ///
    /// @code
    ///     Moon moon(ephemeris, gravModel);
    /// @endcode
    ///
    /// @param [in] anEphemeris An ephemeris for the Moon celestial object
    /// @param [in] aGravitationalModel A gravitational model for the Moon celestial object (Spherical model only)
    Moon(const Shared<Ephemeris>& anEphemeris, const Shared<MoonGravitationalModel>& aGravitationalModel);

    /// @brief Destructor
    virtual ~Moon() override;

    /// @brief Clone the Moon celestial object
    ///
    /// @code
    ///     Moon* moonPtr = moon.clone();
    /// @endcode
    ///
    /// @return Pointer to Moon celestial object
    virtual Moon* clone() const override;

    /// @brief Compute the Moon position from a fast low-precision analytical model, in GCRF
    ///
    /// The position is computed from the analytical series of Montenbruck & Gill, with respect to the mean
    /// equator and equinox of J2000, which is treated as GCRF (the frame bias of ~23 mas is far below the
    /// accuracy of the series).
    ///
    /// Accuracy with respect to high-precision (JPL DE) ephemerides, measured over 2020-2026:
    /// < 0.1 deg in direction, < 0.15% in distance.
    ///
    /// This is orders of magnitude faster than a SPICE-based ephemeris, requires no ephemeris data,
    /// and is well-suited for applications such as third-body point-mass gravity
    /// where only an approximate body position is needed.
    ///
    /// @code
    ///     Position position = moon.computeAnalyticalPosition(instant);
    /// @endcode
    ///
    /// @ref O. Montenbruck, E. Gill, "Satellite Orbits: Models, Methods and Applications", Section 3.3.2.
    ///
    /// @param [in] anInstant An instant
    /// @return Position of the Moon, in GCRF
    virtual Position computeAnalyticalPosition(const Instant& anInstant) const override;

    /// @brief Default Moon model (Spherical)
    ///
    /// @code
    ///     Moon moon = Moon::Default();
    /// @endcode
    ///
    /// @return Moon
    static Moon Default();

    /// @brief Spherical gravitational model with high-precision SPICE based ephemeris
    ///
    /// @code
    ///     Moon moon = Moon::Spherical();
    /// @endcode
    ///
    /// @return Moon
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
