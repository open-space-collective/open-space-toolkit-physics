/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
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

Earth::Earth(
    const Derived& aGravitationalParameter,
    const Length& anEquatorialRadius,
    const Real& aFlattening,
    const Real& aJ2,
    const Real& aJ4,
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
          aGravitationalModel->getParameters().gravitationalParameter_,
          aGravitationalModel->getParameters().equatorialRadius_,
          aGravitationalModel->getParameters().flattening_,
          aGravitationalModel->getParameters().J2_,
          aGravitationalModel->getParameters().J4_,
          anEphemeris,
          aGravitationalModel,
          aMagneticModel,
          anAtmosphericModel,
          Earth::Geometry(
              aGravitationalModel->getParameters().equatorialRadius_,
              aGravitationalModel->getParameters().flattening_,
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

Earth Earth::GravitationalOnly(const Shared<EarthGravitationalModel>& aGravitatationalModel)
{
    return Earth::FromModels(
        aGravitatationalModel,
        std::make_shared<EarthMagneticModel>(EarthMagneticModel::Type::Undefined),
        std::make_shared<EarthAtmosphericModel>(EarthAtmosphericModel::Type::Undefined)
    );
}

Earth Earth::MagneticOnly(const Shared<EarthMagneticModel>& aMagneticModel)
{
    return Earth::FromModels(
        std::make_shared<EarthGravitationalModel>(EarthGravitationalModel::Type::Undefined),
        aMagneticModel,
        std::make_shared<EarthAtmosphericModel>(EarthAtmosphericModel::Type::Undefined)
    );
}

Earth Earth::AtmosphericOnly(const Shared<EarthAtmosphericModel>& anAtmosphericModel)
{
    return Earth::FromModels(
        std::make_shared<EarthGravitationalModel>(EarthGravitationalModel::Type::Undefined),
        std::make_shared<EarthMagneticModel>(EarthMagneticModel::Type::Undefined),
        anAtmosphericModel
    );
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

Earth Earth::Default()
{
    return Earth::EGM2008(20, 20);
}

Earth Earth::EGM2008(const Integer& aGravityModelDegree, const Integer& aGravityModelOrder)
{
    return Earth::GravitationalOnly(std::make_shared<EarthGravitationalModel>(
        EarthGravitationalModel::Type::EGM2008, Directory::Undefined(), aGravityModelDegree, aGravityModelOrder
    ));
}

Earth Earth::WGS84_EGM96(const Integer& aGravityModelDegree, const Integer& aGravityModelOrder)
{
    return Earth::GravitationalOnly(std::make_shared<EarthGravitationalModel>(
        EarthGravitationalModel::Type::WGS84_EGM96, Directory::Undefined(), aGravityModelDegree, aGravityModelOrder
    ));
}

Earth Earth::EGM96(const Integer& aGravityModelDegree, const Integer& aGravityModelOrder)
{
    return Earth::GravitationalOnly(std::make_shared<EarthGravitationalModel>(
        EarthGravitationalModel::Type::EGM96, Directory::Undefined(), aGravityModelDegree, aGravityModelOrder
    ));
}

Earth Earth::EGM84(const Integer& aGravityModelDegree, const Integer& aGravityModelOrder)
{
    return Earth::GravitationalOnly(std::make_shared<EarthGravitationalModel>(
        EarthGravitationalModel::Type::EGM84, Directory::Undefined(), aGravityModelDegree, aGravityModelOrder
    ));
}

Earth Earth::WGS84(const Integer& aGravityModelDegree, const Integer& aGravityModelOrder)
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
    const Length& anEquatorialRadius, const Real& aFlattening, const Shared<const Frame>& aFrameSPtr
)
{
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::transformation::rotation::Quaternion;

    const Real equatorialRadius_m = anEquatorialRadius.inMeters();
    const Real polarRadius_m = equatorialRadius_m * (1.0 - aFlattening);

    const Ellipsoid ellipsoid = {
        Point::Origin(), equatorialRadius_m, equatorialRadius_m, polarRadius_m, Quaternion::Unit()
    };

    return {ellipsoid, aFrameSPtr};
}

}  // namespace celestial
}  // namespace object
}  // namespace environment
}  // namespace physics
}  // namespace ostk
