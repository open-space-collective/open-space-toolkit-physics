/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Ephemerides/Analytical.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Objects/CelestialBodies/Earth.hpp>

namespace ostk
{
namespace physics
{
namespace env
{
namespace obj
{
namespace celest
{

using ostk::physics::units::Mass;
using ostk::physics::units::Time;
using ostk::physics::units::Angle;

static const Derived::Unit GravitationalParameterSIUnit =
    Derived::Unit::GravitationalParameter(Length::Unit::Meter, Time::Unit::Second);

// Coefficients taken from https://earth-info.nga.mil/index.php?dir=wgs84&action=wgs84#tab_egm2008
// http://jules.unavco.org/Voyager/Anc/Earth/egm96_geoid_diff
// https://science.gsfc.nasa.gov/sed/content/uploadFiles/publication_files/EGM96_NASA-TP-1998-206861.pdf
// https://geographiclib.sourceforge.io/html/gravity.html
// http://help.agi.com/stk/Content/gator/ab-cb.htm
// https://www.iers.org/SharedDocs/Publikationen/EN/IERS/Publications/tn/TechnNote36/tn36_079.pdf?__blob=publicationFile&v=1
// https://agupubs.onlinelibrary.wiley.com/doi/full/10.1029/2011JB008916
// https://books.google.fr/books?id=SuPQmbqyrFAC

// EGM2008

const Derived Earth::Models::EGM2008::GravitationalParameter = {398600441500000.0, GravitationalParameterSIUnit};
const Length Earth::Models::EGM2008::EquatorialRadius = Length::Meters(6378137.0);
const Real Earth::Models::EGM2008::Flattening = 1.0 / 298.257223563;
const Real Earth::Models::EGM2008::C20 = -4.84169317366974e-04;
const Real Earth::Models::EGM2008::C40 = 5.39965866638991e-07;
const Real Earth::Models::EGM2008::J2 = -Earth::Models::EGM2008::C20 * std::sqrt(5.0);
const Real Earth::Models::EGM2008::J4 = -Earth::Models::EGM2008::C40 * std::sqrt(9.0);

// EGM96 + WGS84

const Derived Earth::Models::WGS84_EGM96::GravitationalParameter = {398600441800000.0, GravitationalParameterSIUnit};
const Length Earth::Models::WGS84_EGM96::EquatorialRadius = Length::Meters(6378137.0);
const Real Earth::Models::WGS84_EGM96::Flattening = 1.0 / 298.257223563;
const Real Earth::Models::WGS84_EGM96::C20 = -4.841653717360e-04;
const Real Earth::Models::WGS84_EGM96::C40 = 5.398738637890e-07;
const Real Earth::Models::WGS84_EGM96::J2 = -Earth::Models::WGS84_EGM96::C20 * std::sqrt(5.0);  // 0.0010826266835531513
const Real Earth::Models::WGS84_EGM96::J4 = -Earth::Models::WGS84_EGM96::C40 * std::sqrt(9.0);

// EGM96

const Derived Earth::Models::EGM96::GravitationalParameter = {398600441500000.0, GravitationalParameterSIUnit};
const Length Earth::Models::EGM96::EquatorialRadius = Length::Meters(6378136.3);
const Real Earth::Models::EGM96::Flattening = 1.0 / 298.257223563;
const Real Earth::Models::EGM96::C20 = -4.841653717360e-04;
const Real Earth::Models::EGM96::C40 = 5.398738637890e-07;
const Real Earth::Models::EGM96::J2 = -Earth::Models::EGM96::C20 * std::sqrt(5.0);
const Real Earth::Models::EGM96::J4 = -Earth::Models::EGM96::C40 * std::sqrt(9.0);

// EGM84

const Derived Earth::Models::EGM84::GravitationalParameter = {398600441800000.0, GravitationalParameterSIUnit};
const Length Earth::Models::EGM84::EquatorialRadius = Length::Meters(6378137.0);
const Real Earth::Models::EGM84::Flattening = 1.0 / 298.257223563;
const Real Earth::Models::EGM84::C20 = -4.841668500000e-04;
const Real Earth::Models::EGM84::C40 = 5.369958670000e-07;
const Real Earth::Models::EGM84::J2 = -Earth::Models::EGM84::C20 * std::sqrt(5.0);
const Real Earth::Models::EGM84::J4 = -Earth::Models::EGM84::C40 * std::sqrt(9.0);

// WGS84

const Derived Earth::Models::WGS84::GravitationalParameter = {398600441800000.0, GravitationalParameterSIUnit};
const Length Earth::Models::WGS84::EquatorialRadius = Length::Meters(6378137.0);
const Real Earth::Models::WGS84::Flattening = 1.0 / 298.257223563;
const Real Earth::Models::WGS84::C20 = -4.841668500000e-04;
const Real Earth::Models::WGS84::C40 = 5.369958670000e-07;
const Real Earth::Models::WGS84::J2 = -Earth::Models::WGS84::C20 * std::sqrt(5.0);
const Real Earth::Models::WGS84::J4 = -Earth::Models::WGS84::C40 * std::sqrt(9.0);

// Spherical

const Derived Earth::Models::Spherical::GravitationalParameter = {398600441500000.0, GravitationalParameterSIUnit};
const Length Earth::Models::Spherical::EquatorialRadius = Length::Meters(6378137.0);
const Real Earth::Models::Spherical::Flattening = 0.0;
const Real Earth::Models::Spherical::C20 = 0.0;
const Real Earth::Models::Spherical::C40 = 0.0;
const Real Earth::Models::Spherical::J2 = 0.0;
const Real Earth::Models::Spherical::J4 = 0.0;

const Derived Earth::GravitationalParameter = Earth::Models::EGM2008::GravitationalParameter;  // [TBR]
const Length Earth::EquatorialRadius = Earth::Models::EGM2008::EquatorialRadius;               // [TBR]
const Real Earth::Flattening = Earth::Models::EGM2008::Flattening;                             // [TBR]
const Real Earth::C20 = Earth::Models::EGM2008::C20;                                           // [TBR]
const Real Earth::C40 = Earth::Models::EGM2008::C40;                                           // [TBR]
const Real Earth::J2 = Earth::Models::EGM2008::J2;                                             // [TBR]
const Real Earth::J4 = Earth::Models::EGM2008::J4;                                             // [TBR]

Earth::Earth(
    const Derived& aGravitationalParameter,
    const Length& anEquatorialRadius,
    const Real& aFlattening,
    const Real& aJ2,
    const Real& aJ4,
    const Shared<Ephemeris>& anEphemeris,
    const EarthGravitationalModel::Type& aGravitationalModelType,
    const EarthMagneticModel::Type& aMagneticModelType,
    const EarthAtmosphericModel::Type& anAtmosphericModelType
)
    : Celestial(
          "Earth",
          Celestial::Type::Earth,
          aGravitationalParameter,
          anEquatorialRadius,
          aFlattening,
          aJ2,
          aJ4,
          anEphemeris,
          std::make_shared<EarthGravitationalModel>(aGravitationalModelType),
          std::make_shared<EarthMagneticModel>(aMagneticModelType),
          std::make_shared<EarthAtmosphericModel>(anAtmosphericModelType),
          Earth::Geometry(anEquatorialRadius, aFlattening, anEphemeris->accessFrame())
      )
{
}

Earth::Earth(
    const Derived& aGravitationalParameter,
    const Length& anEquatorialRadius,
    const Real& aFlattening,
    const Real& aJ2,
    const Real& aJ4,
    const Shared<Ephemeris>& anEphemeris,
    const EarthGravitationalModel::Type& aGravitationalModelType,
    const Integer& aGravityModelDegree,
    const Integer& aGravityModelOrder,
    const EarthMagneticModel::Type& aMagneticModelType,
    const EarthAtmosphericModel::Type& anAtmosphericModelType
)
    : Celestial(
          "Earth",
          Celestial::Type::Earth,
          aGravitationalParameter,
          anEquatorialRadius,
          aFlattening,
          aJ2,
          aJ4,
          anEphemeris,
          std::make_shared<EarthGravitationalModel>(
              aGravitationalModelType, Directory::Undefined(), aGravityModelDegree, aGravityModelOrder
          ),
          std::make_shared<EarthMagneticModel>(aMagneticModelType),
          std::make_shared<EarthAtmosphericModel>(anAtmosphericModelType),
          Earth::Geometry(anEquatorialRadius, aFlattening, anEphemeris->accessFrame())
      )
{
}

Earth::~Earth() {}

Earth* Earth::clone() const
{
    return new Earth(*this);
}

Earth Earth::Default()
{
    return Earth::EGM2008();
}

Earth Earth::EGM2008(const Integer& aGravityModelDegree, const Integer& aGravityModelOrder)
{
    using ostk::physics::coord::Frame;
    using ostk::physics::env::ephem::Analytical;

    const Shared<const Frame> earthFrameSPtr = Frame::ITRF();

    return {
        Earth::Models::EGM2008::GravitationalParameter,
        Earth::Models::EGM2008::EquatorialRadius,
        Earth::Models::EGM2008::Flattening,
        Earth::Models::EGM2008::J2,
        Earth::Models::EGM2008::J4,
        std::make_shared<Analytical>(earthFrameSPtr),
        EarthGravitationalModel::Type::EGM2008,
        aGravityModelDegree,
        aGravityModelOrder,
        EarthMagneticModel::Type::Undefined,
        EarthAtmosphericModel::Type::Undefined};
}

Earth Earth::WGS84_EGM96(const Integer& aGravityModelDegree, const Integer& aGravityModelOrder)
{
    using ostk::physics::coord::Frame;
    using ostk::physics::env::ephem::Analytical;

    const Shared<const Frame> earthFrameSPtr = Frame::ITRF();

    return {
        Earth::Models::WGS84_EGM96::GravitationalParameter,
        Earth::Models::WGS84_EGM96::EquatorialRadius,
        Earth::Models::WGS84_EGM96::Flattening,
        Earth::Models::WGS84_EGM96::J2,
        Earth::Models::WGS84_EGM96::J4,
        std::make_shared<Analytical>(earthFrameSPtr),
        EarthGravitationalModel::Type::EGM96,
        aGravityModelDegree,
        aGravityModelOrder,
        EarthMagneticModel::Type::Undefined,
        EarthAtmosphericModel::Type::Undefined};
}

Earth Earth::EGM96(const Integer& aGravityModelDegree, const Integer& aGravityModelOrder)
{
    using ostk::physics::coord::Frame;
    using ostk::physics::env::ephem::Analytical;

    const Shared<const Frame> earthFrameSPtr = Frame::ITRF();

    return {
        Earth::Models::EGM96::GravitationalParameter,
        Earth::Models::EGM96::EquatorialRadius,
        Earth::Models::EGM96::Flattening,
        Earth::Models::EGM96::J2,
        Earth::Models::EGM96::J4,
        std::make_shared<Analytical>(earthFrameSPtr),
        EarthGravitationalModel::Type::EGM96,
        aGravityModelDegree,
        aGravityModelOrder,
        EarthMagneticModel::Type::Undefined,
        EarthAtmosphericModel::Type::Undefined};
}

Earth Earth::EGM84(const Integer& aGravityModelDegree, const Integer& aGravityModelOrder)
{
    using ostk::physics::coord::Frame;
    using ostk::physics::env::ephem::Analytical;

    const Shared<const Frame> earthFrameSPtr = Frame::ITRF();

    return {
        Earth::Models::EGM84::GravitationalParameter,
        Earth::Models::EGM84::EquatorialRadius,
        Earth::Models::EGM84::Flattening,
        Earth::Models::EGM84::J2,
        Earth::Models::EGM84::J4,
        std::make_shared<Analytical>(earthFrameSPtr),
        EarthGravitationalModel::Type::EGM84,
        aGravityModelDegree,
        aGravityModelOrder,
        EarthMagneticModel::Type::Undefined,
        EarthAtmosphericModel::Type::Undefined};
}

Earth Earth::WGS84(const Integer& aGravityModelDegree, const Integer& aGravityModelOrder)
{
    using ostk::physics::coord::Frame;
    using ostk::physics::env::ephem::Analytical;

    const Shared<const Frame> earthFrameSPtr = Frame::ITRF();

    return {
        Earth::Models::WGS84::GravitationalParameter,
        Earth::Models::WGS84::EquatorialRadius,
        Earth::Models::WGS84::Flattening,
        Earth::Models::WGS84::J2,
        Earth::Models::WGS84::J4,
        std::make_shared<Analytical>(earthFrameSPtr),
        EarthGravitationalModel::Type::WGS84,
        aGravityModelDegree,
        aGravityModelOrder,
        EarthMagneticModel::Type::Undefined,
        EarthAtmosphericModel::Type::Undefined};
}

Earth Earth::Spherical()
{
    using ostk::physics::coord::Frame;
    using ostk::physics::env::ephem::Analytical;

    const Shared<const Frame> earthFrameSPtr = Frame::ITRF();

    return {
        Earth::Models::Spherical::GravitationalParameter,
        Earth::Models::Spherical::EquatorialRadius,
        Earth::Models::Spherical::Flattening,
        Earth::Models::Spherical::J2,
        Earth::Models::Spherical::J4,
        std::make_shared<Analytical>(earthFrameSPtr),
        EarthGravitationalModel::Type::Spherical,
        EarthMagneticModel::Type::Undefined,
        EarthAtmosphericModel::Type::Undefined};
}

Object::Geometry Earth::Geometry(
    const Length& anEquatorialRadius, const Real& aFlattening, const Shared<const Frame>& aFrameSPtr
)
{
    using ostk::math::geom::d3::objects::Point;
    using ostk::math::geom::d3::trf::rot::Quaternion;

    const Real equatorialRadius_m = anEquatorialRadius.inMeters();
    const Real polarRadius_m = equatorialRadius_m * (1.0 - aFlattening);

    const Ellipsoid ellipsoid = {
        Point::Origin(), equatorialRadius_m, equatorialRadius_m, polarRadius_m, Quaternion::Unit()};

    return {ellipsoid, aFrameSPtr};
}

}  // namespace celest
}  // namespace obj
}  // namespace env
}  // namespace physics
}  // namespace ostk
