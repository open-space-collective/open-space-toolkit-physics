/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Environment_Object_Celestial_Earth__
#define __OpenSpaceToolkit_Physics_Environment_Object_Celestial_Earth__

#include <OpenSpaceToolkit/Core/Type/Real.hpp>
#include <OpenSpaceToolkit/Core/Type/Shared.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Ellipsoid.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Ephemeris.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Ephemeris/Analytical.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Magnetic/Earth.hpp>
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

using ostk::core::filesystem::Directory;
using ostk::core::type::Integer;
using ostk::core::type::Real;
using ostk::core::type::Shared;
using ostk::core::type::String;

using ostk::mathematics::geometry::d3::object::Ellipsoid;

using ostk::physics::environment::Ephemeris;
using ostk::physics::environment::ephemeris::Analytical;
using ostk::physics::environment::Object;
using ostk::physics::environment::object::Celestial;
using ostk::physics::unit::Derived;
using ostk::physics::unit::Length;
using EarthGravitationalModel = ostk::physics::environment::gravitational::Earth;
using EarthMagneticModel = ostk::physics::environment::magnetic::Earth;
using EarthAtmosphericModel = ostk::physics::environment::atmospheric::Earth;

class Earth : public Celestial
{
   public:
    /// @brief Constructor
    ///
    /// @code
    ///     Earth earth(gravitationalParameter, equatorialRadius, flattening, J2, J4, ephemeris, gravModel, magModel,
    ///     atmosModel) ;
    /// @endcode
    ///
    /// @param [in] anInstant An instant for the Earth celestial object
    /// @param [in] aGravitationalParameter A gravitational parameter for the Earth celestial object
    /// @param [in] anEquatorialRadius An equatorial radius for the Earth celestial object
    /// @param [in] aFlattening A flattening for the Earth celestial object
    /// @param [in] aJ2 A J2 coefficient for the Earth celestial object
    /// @param [in] aJ4 A J4 coefficient for the Earth celestial object
    /// @param [in] anEphemeris An ephemeris for the Earth celestial object
    /// @param [in] aGravitationalModel A gravitational model for the Earth celestial object
    /// @param [in] aMagneticModel A magnetic model for the Earth celestial object
    /// @param [in] anAtmosphericModel An atmospheric model for the Earth celestial object
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

    /// @brief Constructor
    ///
    /// @code
    ///     Earth earth(ephemeris, gravModel, magModel, atmosModel) ;
    /// @endcode
    ///
    /// @param [in] anInstant An instant for the Earth celestial object
    /// @param [in] anEphemeris An ephemeris for the Earth celestial object
    /// @param [in] aGravitationalModel A gravitational model for the Earth celestial object
    /// @param [in] aMagneticModel A magnetic model for the Earth celestial object
    /// @param [in] anAtmosphericModel An atmospheric model for the Earth celestial object
    Earth(
        const Shared<Ephemeris>& anEphemeris,
        const Shared<EarthGravitationalModel>& aGravitationalModel = nullptr,
        const Shared<EarthMagneticModel>& aMagneticModel = nullptr,
        const Shared<EarthAtmosphericModel>& anAtmosphericModel = nullptr
    );

    /// @brief Destructor
    virtual ~Earth() override;

    /// @brief Clone the Earth celestial object.
    ///
    /// @code
    ///     Earth* earthPtr = earth.clone() ;
    /// @endcode
    ///
    /// @return Pointer to Earth celestial object
    virtual Earth* clone() const override;

    /// @brief Default Earth model (EGM2008)
    ///
    /// @code
    ///     Earth earth = Earth::Default() ;
    /// @endcode
    ///
    /// @return Earth
    static Earth Default();

    /// @brief Just gravity model
    ///
    /// @code
    ///     Earth earth = Earth::GravitationalOnly(gravModel) ;
    /// @endcode
    ///
    /// @param [in] aGravitationalModel A gravitational model
    /// @return Earth
    static Earth GravitationalOnly(const Shared<EarthGravitationalModel>& aGravitationalModel);

    /// @brief Just atmospheric model
    ///
    /// @code
    ///     Earth earth = Earth::AtmosphericOnly(atmosModel) ;
    /// @endcode
    ///
    /// @param [in] anAtmosphericModel An atmospheric model
    /// @return Earth
    static Earth AtmosphericOnly(const Shared<EarthAtmosphericModel>& anAtmosphericModel);

    /// @brief Just magnetic model
    ///
    /// @code
    ///     Earth earth = Earth::MagneticOnly(magModel) ;
    /// @endcode
    ///
    /// @param [in] aMagneticModel A magnetic model
    /// @return Earth
    static Earth MagneticOnly(const Shared<EarthMagneticModel>& aMagneticModel);

    /// @brief Create earth from specified models
    ///
    /// @code
    ///     Earth earth = Earth::FromModels(gravModel, magModel, atmosModel) ;
    /// @endcode
    ///
    /// @param [in] aGravitationalModel A gravitational model
    /// @param [in] aMagneticModel A magnetic model
    /// @param [in] anAtmosphericModel An atmospheric model
    ///
    /// @return Earth
    static Earth FromModels(
        const Shared<EarthGravitationalModel>& aGravitationalModel,
        const Shared<EarthMagneticModel>& aMagneticModel,
        const Shared<EarthAtmosphericModel>& anAtmosphericModel
    );

    /// @brief Earth Gravity Model 2008 model (EGM2008)
    ///
    /// @code
    ///     Earth earth = Earth::EGM2008() ;
    /// @endcode
    ///
    /// @return Earth
    static Earth EGM2008(
        const Integer& aGravityModelDegree = Integer::Undefined(),
        const Integer& aGravityModelOrder = Integer::Undefined()
    );

    /// @brief World Geodetic System 1984 (WGS84) + Earth Gravity Model 1996 (EGM96)
    ///
    /// EGM96 coefficients and WGS84 shape. Gravitational parameter: 398600441800000 [m^3/s^2].
    /// Equatorial radius: 6378137.0 [m].
    ///
    /// @code
    ///     Earth earth = Earth::WGS84_EGM96() ;
    /// @endcode
    ///
    /// @ref NIMA TR8350.2, Third Edition, 4 July 1997.
    ///
    /// @return Earth
    static Earth WGS84_EGM96(
        const Integer& aGravityModelDegree = Integer::Undefined(),
        const Integer& aGravityModelOrder = Integer::Undefined()
    );

    /// @brief Earth Gravity Model 1996 (EGM96)
    ///
    /// @code
    ///     Earth earth = Earth::EGM96() ;
    /// @endcode
    ///
    /// @return Earth
    static Earth EGM96(
        const Integer& aGravityModelDegree = Integer::Undefined(),
        const Integer& aGravityModelOrder = Integer::Undefined()
    );

    /// @brief Earth Gravity Model 1984 (EGM84)
    ///
    /// @code
    ///     Earth earth = Earth::EGM84() ;
    /// @endcode
    ///
    /// @return Earth
    static Earth EGM84(
        const Integer& aGravityModelDegree = Integer::Undefined(),
        const Integer& aGravityModelOrder = Integer::Undefined()
    );

    /// @brief World Geodetic System 1984 (WGS84)
    ///
    /// @code
    ///     Earth earth = Earth::WGS84() ;
    /// @endcode
    ///
    /// @return Earth
    static Earth WGS84(
        const Integer& aGravityModelDegree = Integer::Undefined(),
        const Integer& aGravityModelOrder = Integer::Undefined()
    );

    /// @brief Spherical model
    ///
    /// @code
    ///     Earth earth = Earth::Spherical() ;
    /// @endcode
    ///
    /// @return Earth
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
