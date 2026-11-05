/// Apache License 2.0

#include <cmath>
#include <limits>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Object/Celestial/Earth.hpp>

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

using ostk::physics::coordinate::Frame;

namespace
{

// An Earth without a gravitational model has no gravitational parameters: they are NaN (and the equatorial radius is
// an undefined length).
EarthGravitationalModel::Parameters ParametersFromModel(const Shared<EarthGravitationalModel>& aGravitationalModel)
{
    using ostk::physics::unit::Derived;
    using ostk::physics::unit::Length;
    using ostk::physics::unit::Time;

    if (aGravitationalModel != nullptr)
    {
        return aGravitationalModel->getParameters();
    }

    const double nan = std::numeric_limits<double>::quiet_NaN();

    return {
        Derived(nan, Derived::Unit::GravitationalParameter(Length::Unit::Meter, Time::Unit::Second)),
        Length::Undefined(),
        nan,
        nan,
        nan,
        nan
    };
}

}  // namespace

Earth::Earth(
    const Derived& aGravitationalParameter,
    const Length& anEquatorialRadius,
    double aFlattening,
    double aJ2,
    double aJ4,
    const Shared<Ephemeris>& anEphemeris,
    const Shared<EarthGravitationalModel>& aGravitationalModel,
    const Shared<EarthMagneticModel>& aMagneticModel,
    const Shared<EarthAtmosphericModel>& anAtmosphericModel
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
          aGravitationalModel,
          aMagneticModel,
          anAtmosphericModel,
          Earth::Geometry(anEquatorialRadius, aFlattening, anEphemeris->accessFrame())
      )
{
}

Earth::Earth(
    const Shared<Ephemeris>& anEphemeris,
    const Shared<EarthGravitationalModel>& aGravitationalModel,
    const Shared<EarthMagneticModel>& aMagneticModel,
    const Shared<EarthAtmosphericModel>& anAtmosphericModel
)
    : Celestial(
          "Earth",
          Celestial::Type::Earth,
          ParametersFromModel(aGravitationalModel).gravitationalParameter_,
          ParametersFromModel(aGravitationalModel).equatorialRadius_,
          ParametersFromModel(aGravitationalModel).flattening_,
          ParametersFromModel(aGravitationalModel).J2_,
          ParametersFromModel(aGravitationalModel).J4_,
          anEphemeris,
          aGravitationalModel,
          aMagneticModel,
          anAtmosphericModel,
          Earth::Geometry(
              ParametersFromModel(aGravitationalModel).equatorialRadius_,
              ParametersFromModel(aGravitationalModel).flattening_,
              anEphemeris->accessFrame()
          )
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
    return Earth::EGM2008(20, 20);
}

Earth Earth::GravitationalOnly(const Shared<EarthGravitationalModel>& aGravitatationalModel)
{
    return Earth::FromModels(aGravitatationalModel, nullptr, nullptr);
}

Earth Earth::AtmosphericOnly(const Shared<EarthAtmosphericModel>& anAtmosphericModel)
{
    return Earth::FromModels(nullptr, nullptr, anAtmosphericModel);
}

Earth Earth::MagneticOnly(const Shared<EarthMagneticModel>& aMagneticModel)
{
    return Earth::FromModels(nullptr, aMagneticModel, nullptr);
}

Earth Earth::FromModels(
    const Shared<EarthGravitationalModel>& aGravitationalModel,
    const Shared<EarthMagneticModel>& aMagneticModel,
    const Shared<EarthAtmosphericModel>& anAtmosphericModel
)
{
    const Shared<const Frame> earthFrameSPtr = Frame::ITRF();

    return {
        std::make_shared<Analytical>(earthFrameSPtr),
        aGravitationalModel,
        aMagneticModel,
        anAtmosphericModel,
    };
}

Earth Earth::EGM2008(const std::optional<int>& aGravityModelDegree, const std::optional<int>& aGravityModelOrder)
{
    return Earth::GravitationalOnly(std::make_shared<EarthGravitationalModel>(
        EarthGravitationalModel::Type::EGM2008, Directory::Undefined(), aGravityModelDegree, aGravityModelOrder
    ));
}

Earth Earth::WGS84_EGM96(const std::optional<int>& aGravityModelDegree, const std::optional<int>& aGravityModelOrder)
{
    return Earth::GravitationalOnly(std::make_shared<EarthGravitationalModel>(
        EarthGravitationalModel::Type::WGS84_EGM96, Directory::Undefined(), aGravityModelDegree, aGravityModelOrder
    ));
}

Earth Earth::EGM96(const std::optional<int>& aGravityModelDegree, const std::optional<int>& aGravityModelOrder)
{
    return Earth::GravitationalOnly(std::make_shared<EarthGravitationalModel>(
        EarthGravitationalModel::Type::EGM96, Directory::Undefined(), aGravityModelDegree, aGravityModelOrder
    ));
}

Earth Earth::EGM84(const std::optional<int>& aGravityModelDegree, const std::optional<int>& aGravityModelOrder)
{
    return Earth::GravitationalOnly(std::make_shared<EarthGravitationalModel>(
        EarthGravitationalModel::Type::EGM84, Directory::Undefined(), aGravityModelDegree, aGravityModelOrder
    ));
}

Earth Earth::WGS84(const std::optional<int>& aGravityModelDegree, const std::optional<int>& aGravityModelOrder)
{
    return Earth::GravitationalOnly(std::make_shared<EarthGravitationalModel>(
        EarthGravitationalModel::Type::WGS84, Directory::Undefined(), aGravityModelDegree, aGravityModelOrder
    ));
}

Earth Earth::Spherical()
{
    return Earth::GravitationalOnly(
        std::make_shared<EarthGravitationalModel>(EarthGravitationalModel::Type::Spherical, Directory::Undefined())
    );
}

Object::Geometry Earth::Geometry(
    const Length& anEquatorialRadius, double aFlattening, const Shared<const Frame>& aFrameSPtr
)
{
    using ostk::core::type::Real;

    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::transformation::rotation::Quaternion;

    // Ellipsoid still takes ostk::core::type::Real, which treats NaN as a defined value: map NaN to Real::Undefined()
    // so that an undefined radius or flattening still yields an undefined ellipsoid.
    const auto toReal = [](double aValue) -> Real
    {
        return std::isnan(aValue) ? Real::Undefined() : Real(aValue);
    };

    const double equatorialRadius_m = anEquatorialRadius.inMeters();
    const double polarRadius_m = equatorialRadius_m * (1.0 - aFlattening);

    const Ellipsoid ellipsoid = {
        Point::Origin(),
        toReal(equatorialRadius_m),
        toReal(equatorialRadius_m),
        toReal(polarRadius_m),
        Quaternion::Unit()
    };

    return {ellipsoid, aFrameSPtr};
}

}  // namespace celestial
}  // namespace object
}  // namespace environment
}  // namespace physics
}  // namespace ostk
