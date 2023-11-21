/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Environment_Objects_CelestialBodies_Earth__
#define __OpenSpaceToolkit_Physics_Environment_Objects_CelestialBodies_Earth__

#include <OpenSpaceToolkit/Core/Types/Real.hpp>
#include <OpenSpaceToolkit/Core/Types/Shared.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Ellipsoid.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Ephemerides/Analytical.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Ephemeris.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Magnetic/Earth.hpp>
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

using ostk::core::types::Integer;
using ostk::core::types::Real;
using ostk::core::types::String;
using ostk::core::types::Shared;
using ostk::core::fs::Directory;

using ostk::math::geom::d3::objects::Ellipsoid;

using ostk::physics::units::Length;
using ostk::physics::units::Derived;
using ostk::physics::environment::Ephemeris;
using ostk::physics::environment::Object;
using ostk::physics::environment::object::Celestial;
using ostk::physics::environment::ephemerides::Analytical;
using EarthGravitationalModel = ostk::physics::environment::gravitational::Earth;
using EarthMagneticModel = ostk::physics::environment::magnetic::Earth;
using EarthAtmosphericModel = ostk::physics::environment::atmospheric::Earth;

class Earth : public Celestial
{
   public:
    /// @brief              Constructor
    ///

    /// @param              [in] anInstant An instant for the Earth celestial object
    /// @param              [in] aGravitationalParameter A gravitational parameter for the Earth celestial object
    /// @param              [in] anEquatorialRadius An equatorial radius for the Earth celestial object
    /// @param              [in] aFlattening A flattening for the Earth celestial object
    /// @param              [in] aJ2 A J2 coefficient for the Earth celestial object
    /// @param              [in] aJ4 A J4 coefficient for the Earth celestial object
    /// @param              [in] anEphemeris An ephemeris for the Earth celestial object
    /// @param              [in] aGravitationalModel A gravitational model for the Earth celestial object
    /// @param              [in] aMagneticModel A magnetic model for the Earth celestial object
    /// @param              [in] anAtmosphericModel An atmospheric model for the Earth celestial object

    Earth(
        const Derived& aGravitationalParameter,
        const Length& anEquatorialRadius,
        const Real& aFlattening,
        const Real& aJ2,
        const Real& aJ4,
        const Shared<Ephemeris>& anEphemeris,
        const Shared<EarthGravitationalModel>& aGravitationalModel,
        const Shared<EarthMagneticModel>& aMagneticModel,
        const Shared<EarthAtmosphericModel>& anAtmosphericModel
    );

    /// @brief              Constructor
    ///
    /// @param              [in] anInstant An instant for the Earth celestial object
    /// @param              [in] anEphemeris An ephemeris for the Earth celestial object
    /// @param              [in] aGravitationalModel A gravitational model for the Earth celestial object
    /// @param              [in] aMagneticModel A magnetic model for the Earth celestial object
    /// @param              [in] anAtmosphericModel An atmospheric model for the Earth celestial object

    Earth(
        const Shared<Ephemeris>& anEphemeris,
        const Shared<EarthGravitationalModel>& aGravitationalModel = nullptr,
        const Shared<EarthMagneticModel>& aMagneticModel = nullptr,
        const Shared<EarthAtmosphericModel>& anAtmosphericModel = nullptr
    );

    virtual ~Earth() override;

    virtual Earth* clone() const override;

    /// @brief              Default Earth model (EGM2008)
    ///
    /// @return             Earth

    static Earth Default();

    /// @brief              Just gravity model
    ///
    /// @param              [in] aGravitationalModel A gravitational model
    /// @return             Earth

    static Earth GravitationalOnly(const Shared<EarthGravitationalModel>& aGravitationalModel);

    /// @brief              Just atmospheric model
    ///
    /// @param              [in] anAtmosphericModel An atmospheric model
    /// @return             Earth

    static Earth AtmosphericOnly(const Shared<EarthAtmosphericModel>& anAtmosphericModel);

    /// @brief              Just magnetic model
    ///
    /// @param`             [in] aMagneticModel A magnetic model
    /// @return             Earth

    static Earth MagneticOnly(const Shared<EarthMagneticModel>& aMagneticModel);

    /// @brief              Create earth from specified models
    ///
    /// @param              [in] aGravitationalModel A gravitational model
    /// @param              [in] aMagneticModel A magnetic model
    /// @param              [in] anAtmosphericModel An atmospheric model
    ///
    /// @return             Earth

    static Earth FromModels(
        const Shared<EarthGravitationalModel>& aGravitationalModel,
        const Shared<EarthMagneticModel>& aMagneticModel,
        const Shared<EarthAtmosphericModel>& anAtmosphericModel
    );

    /// @brief              Earth Gravity Model 2008 model (EGM2008)
    ///
    /// @return             Earth

    static Earth EGM2008(
        const Integer& aGravityModelDegree = Integer::Undefined(),
        const Integer& aGravityModelOrder = Integer::Undefined()
    );

    /// @brief              World Geodetic System 1984 (WGS84) + Earth Gravity Model 1996 (EGM96)
    ///
    ///                     EGM96 coefficients and WGS84 shape.
    ///                     Gravitational parameter: 398600441800000 [m^3/s^2].
    ///                     Equatorial radius: 6378137.0 [m].
    ///
    /// @ref                NIMA TR8350.2, Third Edition, 4 July 1997.
    ///
    /// @return             Earth

    static Earth WGS84_EGM96(
        const Integer& aGravityModelDegree = Integer::Undefined(),
        const Integer& aGravityModelOrder = Integer::Undefined()
    );

    /// @brief              Earth Gravity Model 1996 (EGM96)
    ///
    /// @return             Earth

    static Earth EGM96(
        const Integer& aGravityModelDegree = Integer::Undefined(),
        const Integer& aGravityModelOrder = Integer::Undefined()
    );

    /// @brief              Earth Gravity Model 1984 (EGM84)
    ///
    /// @return             Earth

    static Earth EGM84(
        const Integer& aGravityModelDegree = Integer::Undefined(),
        const Integer& aGravityModelOrder = Integer::Undefined()
    );

    /// @brief              World Geodetic System 1984 (WGS84)
    ///
    /// @return             Earth

    static Earth WGS84(
        const Integer& aGravityModelDegree = Integer::Undefined(),
        const Integer& aGravityModelOrder = Integer::Undefined()
    );

    /// @brief              Spherical model
    ///
    /// @return             Earth

    static Earth Spherical();

   private:
    static Object::Geometry Geometry(
        const Length& anEquatorialRadius, const Real& aFlattening, const Shared<const Frame>& aFrameSPtr
    );
};

}  // namespace celestial
}  // namespace object
}  // namespace environment
}  // namespace physics
}  // namespace ostk

#endif
