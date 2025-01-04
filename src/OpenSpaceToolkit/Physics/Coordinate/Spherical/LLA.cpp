/// Apache License 2.0

#include <GeographicLib/Geodesic.hpp>
#include <GeographicLib/GeodesicLine.hpp>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Position.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Spherical/LLA.hpp>
#include <OpenSpaceToolkit/Physics/Environment.hpp>

// Include sofa last to avoid type errors in underlying Eigen lib
#include <sofa/sofa.h>

namespace ostk
{
namespace physics
{
namespace coordinate
{
namespace spherical
{

using ostk::physics::Environment;

LLA::LLA(const Angle& aLatitude, const Angle& aLongitude, const Length& anAltitude)
    : latitude_(aLatitude),
      longitude_(aLongitude),
      altitude_(anAltitude)
{
    if (latitude_.isDefined() && ((latitude_.inDegrees() < -90.0) || (latitude_.inDegrees() > 90.0)))
    {
        throw ostk::core::error::runtime::Wrong("Latitude");
    }

    if (longitude_.isDefined() && ((longitude_.inDegrees() < -180.0) || (longitude_.inDegrees() > 180.0)))
    {
        throw ostk::core::error::runtime::Wrong("Longitude");
    }
}

bool LLA::operator==(const LLA& aLLA) const
{
    if ((!this->isDefined()) || (!aLLA.isDefined()))
    {
        return false;
    }

    return (latitude_ == aLLA.latitude_) && (longitude_ == aLLA.longitude_) && (altitude_ == aLLA.altitude_);
}

bool LLA::operator!=(const LLA& aLLA) const
{
    return !((*this) == aLLA);
}

std::ostream& operator<<(std::ostream& anOutputStream, const LLA& aLLA)
{
    ostk::core::utils::Print::Header(anOutputStream, "LLA");

    ostk::core::utils::Print::Line(anOutputStream)
        << "Latitude:" << (aLLA.latitude_.isDefined() ? aLLA.latitude_.toString() : "Undefined");
    ostk::core::utils::Print::Line(anOutputStream)
        << "Longitude:" << (aLLA.longitude_.isDefined() ? aLLA.longitude_.toString() : "Undefined");
    ostk::core::utils::Print::Line(anOutputStream)
        << "Altitude:" << (aLLA.altitude_.isDefined() ? aLLA.altitude_.toString() : "Undefined");

    ostk::core::utils::Print::Footer(anOutputStream);

    return anOutputStream;
}

bool LLA::isDefined() const
{
    return latitude_.isDefined() && longitude_.isDefined() && altitude_.isDefined();
}

Angle LLA::getLatitude() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("LLA");
    }

    return latitude_;
}

Angle LLA::getLongitude() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("LLA");
    }

    return longitude_;
}

Length LLA::getAltitude() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("LLA");
    }

    return altitude_;
}

LLA LLA::onSurface() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("LLA");
    }

    return {latitude_, longitude_, Length::Meters(0.0)};
}

Length LLA::calculateDistanceTo(
    const LLA& aLLA, const Length& anEllipsoidEquatorialRadius, const Real& anEllipsoidFlattening
) const
{
    const Length ellipsoidEquatorialRadius =
        anEllipsoidEquatorialRadius.isDefined()
            ? anEllipsoidEquatorialRadius
            : Environment::AccessGlobalInstance()->accessCentralCelestialObject()->getEquatorialRadius();

    const Real ellipsoidFlattening =
        anEllipsoidFlattening.isDefined()
            ? anEllipsoidFlattening
            : Environment::AccessGlobalInstance()->accessCentralCelestialObject()->getFlattening();

    return LLA::DistanceBetween(*this, aLLA, ellipsoidEquatorialRadius, ellipsoidFlattening);
}

Pair<Angle, Angle> LLA::calculateAzimuthTo(
    const LLA& aLLA, const Length& anEllipsoidEquatorialRadius, const Real& anEllipsoidFlattening
) const
{
    const Length ellipsoidEquatorialRadius =
        anEllipsoidEquatorialRadius.isDefined()
            ? anEllipsoidEquatorialRadius
            : Environment::AccessGlobalInstance()->accessCentralCelestialObject()->getEquatorialRadius();

    const Real ellipsoidFlattening =
        anEllipsoidFlattening.isDefined()
            ? anEllipsoidFlattening
            : Environment::AccessGlobalInstance()->accessCentralCelestialObject()->getFlattening();

    return LLA::AzimuthBetween(*this, aLLA, ellipsoidEquatorialRadius, ellipsoidFlattening);
}

LLA LLA::calculateIntermediateTo(
    const LLA& aLLA, const Real& aRatio, const Length& anEllipsoidEquatorialRadius, const Real& anEllipsoidFlattening
) const
{
    const Length ellipsoidEquatorialRadius =
        anEllipsoidEquatorialRadius.isDefined()
            ? anEllipsoidEquatorialRadius
            : Environment::AccessGlobalInstance()->accessCentralCelestialObject()->getEquatorialRadius();

    const Real ellipsoidFlattening =
        anEllipsoidFlattening.isDefined()
            ? anEllipsoidFlattening
            : Environment::AccessGlobalInstance()->accessCentralCelestialObject()->getFlattening();

    return LLA::IntermediateBetween(*this, aLLA, aRatio, ellipsoidEquatorialRadius, ellipsoidFlattening);
}

LLA LLA::calculateForward(
    const Angle& aDirection,
    const Length& aDistance,
    const Length& anEllipsoidEquatorialRadius,
    const Real& anEllipsoidFlattening
) const
{
    const Length ellipsoidEquatorialRadius =
        anEllipsoidEquatorialRadius.isDefined()
            ? anEllipsoidEquatorialRadius
            : Environment::AccessGlobalInstance()->accessCentralCelestialObject()->getEquatorialRadius();

    const Real ellipsoidFlattening =
        anEllipsoidFlattening.isDefined()
            ? anEllipsoidFlattening
            : Environment::AccessGlobalInstance()->accessCentralCelestialObject()->getFlattening();

    return LLA::Forward(*this, aDirection, aDistance, ellipsoidEquatorialRadius, ellipsoidFlattening);
}

Array<LLA> LLA::calculateLinspaceTo(
    const LLA& aLLA,
    const Size& aNumberOfPoints,
    const Length& anEllipsoidEquatorialRadius,
    const Real& anEllipsoidFlattening
) const
{
    const Length ellipsoidEquatorialRadius =
        anEllipsoidEquatorialRadius.isDefined()
            ? anEllipsoidEquatorialRadius
            : Environment::AccessGlobalInstance()->accessCentralCelestialObject()->getEquatorialRadius();

    const Real ellipsoidFlattening =
        anEllipsoidFlattening.isDefined()
            ? anEllipsoidFlattening
            : Environment::AccessGlobalInstance()->accessCentralCelestialObject()->getFlattening();

    return LLA::Linspace(*this, aLLA, aNumberOfPoints, ellipsoidEquatorialRadius, ellipsoidFlattening);
}

Vector3d LLA::toVector() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("LLA");
    }

    return {latitude_.inDegrees(), longitude_.inDegrees(), altitude_.inMeters()};
}

Point2d LLA::toPoint2d() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("LLA");
    }

    return {longitude_.inDegrees(), latitude_.inDegrees()};
}

Point3d LLA::toPoint3d() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("LLA");
    }

    return {longitude_.inDegrees(), latitude_.inDegrees(), altitude_.inMeters()};
}

Vector3d LLA::toCartesian(const Length& anEllipsoidEquatorialRadius, const Real& anEllipsoidFlattening) const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("LLA");
    }

    const Length ellipsoidEquatorialRadius =
        anEllipsoidEquatorialRadius.isDefined()
            ? anEllipsoidEquatorialRadius
            : Environment::AccessGlobalInstance()->accessCentralCelestialObject()->getEquatorialRadius();

    const Real ellipsoidFlattening =
        anEllipsoidFlattening.isDefined()
            ? anEllipsoidFlattening
            : Environment::AccessGlobalInstance()->accessCentralCelestialObject()->getFlattening();

    const double latitude_rad = latitude_.inRadians();
    const double longitude_rad = longitude_.inRadians();
    const double altitude_m = altitude_.inMeters();

    double cartesianArray[3];

    const int result = iauGd2gce(
        ellipsoidEquatorialRadius.inMeters(),
        ellipsoidFlattening,
        longitude_rad,
        latitude_rad,
        altitude_m,
        cartesianArray
    );

    if (result != 0)
    {
        throw ostk::core::error::RuntimeError("Cannot convert LLA to Cartesian.");
    }

    return {cartesianArray[0], cartesianArray[1], cartesianArray[2]};
}

String LLA::toString() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("LLA");
    }

    return String::Format("[{}, {}, {}]", latitude_.toString(), longitude_.toString(), altitude_.toString());
}

LLA LLA::Undefined()
{
    return {Angle::Undefined(), Angle::Undefined(), Length::Undefined()};
}

LLA LLA::Vector(const Vector3d& aVector)
{
    if (!aVector.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Vector");
    }

    return {Angle::Degrees(aVector.x()), Angle::Degrees(aVector.y()), Length::Meters(aVector.z())};
}

LLA LLA::Cartesian(
    const Vector3d& aCartesianCoordinateSet,
    const Length& anEllipsoidEquatorialRadius,
    const Real& anEllipsoidFlattening
)
{
    if (!aCartesianCoordinateSet.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Cartesian coordinates");
    }

    const Length ellipsoidEquatorialRadius =
        anEllipsoidEquatorialRadius.isDefined()
            ? anEllipsoidEquatorialRadius
            : Environment::AccessGlobalInstance()->accessCentralCelestialObject()->getEquatorialRadius();

    const Real ellipsoidFlattening =
        anEllipsoidFlattening.isDefined()
            ? anEllipsoidFlattening
            : Environment::AccessGlobalInstance()->accessCentralCelestialObject()->getFlattening();

    double latitude_rad;
    double longitude_rad;
    double altitude_m;

    const int result = iauGc2gde(
        ellipsoidEquatorialRadius.inMeters(),
        ellipsoidFlattening,
        Vector3d(aCartesianCoordinateSet).data(),
        &longitude_rad,
        &latitude_rad,
        &altitude_m
    );

    if (result != 0)
    {
        throw ostk::core::error::RuntimeError("Cannot convert Cartesian to LLA.");
    }

    const Angle latitude = Angle::Degrees(latitude_rad * 180.0 / M_PI);
    const Angle longitude = Angle::Degrees(longitude_rad * 180.0 / M_PI);
    const Length altitude = Length::Meters(altitude_m);

    return {latitude, longitude, altitude};
}

Length LLA::DistanceBetween(
    const LLA& aFirstLLA,
    const LLA& aSecondLLA,
    const Length& anEllipsoidEquatorialRadius,
    const Real& anEllipsoidFlattening
)
{
    const Length ellipsoidEquatorialRadius =
        anEllipsoidEquatorialRadius.isDefined()
            ? anEllipsoidEquatorialRadius
            : Environment::AccessGlobalInstance()->accessCentralCelestialObject()->getEquatorialRadius();

    const Real ellipsoidFlattening =
        anEllipsoidFlattening.isDefined()
            ? anEllipsoidFlattening
            : Environment::AccessGlobalInstance()->accessCentralCelestialObject()->getFlattening();

    const GeographicLib::Geodesic& geodesic =
        GeographicLib::Geodesic(ellipsoidEquatorialRadius.inMeters(), ellipsoidFlattening);

    GeographicLib::Math::real distance_m;
    geodesic.Inverse(
        aFirstLLA.getLatitude().inDegrees(),
        aFirstLLA.getLongitude().inDegrees(),
        aSecondLLA.getLatitude().inDegrees(),
        aSecondLLA.getLongitude().inDegrees(),
        distance_m
    );

    return Length::Meters(distance_m);
}

Pair<Angle, Angle> LLA::AzimuthBetween(
    const LLA& aFirstLLA,
    const LLA& aSecondLLA,
    const Length& anEllipsoidEquatorialRadius,
    const Real& anEllipsoidFlattening
)
{
    const Length ellipsoidEquatorialRadius =
        anEllipsoidEquatorialRadius.isDefined()
            ? anEllipsoidEquatorialRadius
            : Environment::AccessGlobalInstance()->accessCentralCelestialObject()->getEquatorialRadius();

    const Real ellipsoidFlattening =
        anEllipsoidFlattening.isDefined()
            ? anEllipsoidFlattening
            : Environment::AccessGlobalInstance()->accessCentralCelestialObject()->getFlattening();

    const GeographicLib::Geodesic& geodesic =
        GeographicLib::Geodesic(ellipsoidEquatorialRadius.inMeters(), ellipsoidFlattening);

    GeographicLib::Math::real azimuth1_deg;
    GeographicLib::Math::real azimuth2_deg;
    geodesic.Inverse(
        aFirstLLA.getLatitude().inDegrees(),
        aFirstLLA.getLongitude().inDegrees(),
        aSecondLLA.getLatitude().inDegrees(),
        aSecondLLA.getLongitude().inDegrees(),
        azimuth1_deg,
        azimuth2_deg
    );

    return {Angle::Degrees(azimuth1_deg), Angle::Degrees(azimuth2_deg)};
}

LLA LLA::IntermediateBetween(
    const LLA& aFirstLLA,
    const LLA& aSecondLLA,
    const Real& aRatio,
    const Length& anEllipsoidEquatorialRadius,
    const Real& anEllipsoidFlattening
)
{
    const Length ellipsoidEquatorialRadius =
        anEllipsoidEquatorialRadius.isDefined()
            ? anEllipsoidEquatorialRadius
            : Environment::AccessGlobalInstance()->accessCentralCelestialObject()->getEquatorialRadius();

    const Real ellipsoidFlattening =
        anEllipsoidFlattening.isDefined()
            ? anEllipsoidFlattening
            : Environment::AccessGlobalInstance()->accessCentralCelestialObject()->getFlattening();

    const GeographicLib::Geodesic& geodesic =
        GeographicLib::Geodesic(ellipsoidEquatorialRadius.inMeters(), ellipsoidFlattening);

    const GeographicLib::GeodesicLine& geodesicLine = geodesic.InverseLine(
        aFirstLLA.getLatitude().inDegrees(),
        aFirstLLA.getLongitude().inDegrees(),
        aSecondLLA.getLatitude().inDegrees(),
        aSecondLLA.getLongitude().inDegrees()
    );

    GeographicLib::Math::real latitude_deg;
    GeographicLib::Math::real longitude_deg;

    const Length distance = DistanceBetween(aFirstLLA, aSecondLLA, ellipsoidEquatorialRadius, ellipsoidFlattening);

    geodesicLine.Position(distance.inMeters() * aRatio, latitude_deg, longitude_deg);

    return {Angle::Degrees(latitude_deg), Angle::Degrees(longitude_deg), Length::Meters(0.0)};
}

LLA LLA::Forward(
    const LLA& aLLA,
    const Angle& aDirection,
    const Length& aDistance,
    const Length& anEllipsoidEquatorialRadius,
    const Real& anEllipsoidFlattening
)
{
    const Length ellipsoidEquatorialRadius =
        anEllipsoidEquatorialRadius.isDefined()
            ? anEllipsoidEquatorialRadius
            : Environment::AccessGlobalInstance()->accessCentralCelestialObject()->getEquatorialRadius();

    const Real ellipsoidFlattening =
        anEllipsoidFlattening.isDefined()
            ? anEllipsoidFlattening
            : Environment::AccessGlobalInstance()->accessCentralCelestialObject()->getFlattening();

    const GeographicLib::Geodesic& geodesic =
        GeographicLib::Geodesic(ellipsoidEquatorialRadius.inMeters(), ellipsoidFlattening);

    GeographicLib::Math::real latitude_deg;
    GeographicLib::Math::real longitude_deg;

    geodesic.Direct(
        aLLA.getLatitude().inDegrees(),
        aLLA.getLongitude().inDegrees(),
        aDirection.inDegrees(),
        aDistance.inMeters(),
        latitude_deg,
        longitude_deg
    );

    return {Angle::Degrees(latitude_deg), Angle::Degrees(longitude_deg), Length::Meters(0.0)};
}

Array<LLA> LLA::Linspace(
    const LLA& aFirstLLA,
    const LLA& aSecondLLA,
    const Size& aNumberOfPoints,
    const Length& anEllipsoidEquatorialRadius,
    const Real& anEllipsoidFlattening
)
{
    const Length ellipsoidEquatorialRadius =
        anEllipsoidEquatorialRadius.isDefined()
            ? anEllipsoidEquatorialRadius
            : Environment::AccessGlobalInstance()->accessCentralCelestialObject()->getEquatorialRadius();

    const Real ellipsoidFlattening =
        anEllipsoidFlattening.isDefined()
            ? anEllipsoidFlattening
            : Environment::AccessGlobalInstance()->accessCentralCelestialObject()->getFlattening();

    Array<LLA> intermediateLLAs = Array<LLA>::Empty();
    intermediateLLAs.reserve(aNumberOfPoints);

    const GeographicLib::Geodesic& geodesic =
        GeographicLib::Geodesic(ellipsoidEquatorialRadius.inMeters(), ellipsoidFlattening);

    const GeographicLib::GeodesicLine& geodesicLine = geodesic.InverseLine(
        aFirstLLA.getLatitude().inDegrees(),
        aFirstLLA.getLongitude().inDegrees(),
        aSecondLLA.getLatitude().inDegrees(),
        aSecondLLA.getLongitude().inDegrees()
    );

    GeographicLib::Math::real latitude_deg;
    GeographicLib::Math::real longitude_deg;

    for (Size i = 0; i < aNumberOfPoints; ++i)
    {
        geodesicLine.Position((i + 1) * geodesicLine.Distance() / (aNumberOfPoints + 1), latitude_deg, longitude_deg);
        intermediateLLAs.add(LLA(Angle::Degrees(latitude_deg), Angle::Degrees(longitude_deg), Length::Meters(0.0)));
    }

    return intermediateLLAs;
}

LLA LLA::FromPosition(const Position& aPosition, const Shared<const environment::object::Celestial>& aCelestialSPtr)
{
    if (!aPosition.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Position");
    }

    const auto celestialObjectSPtr = aCelestialSPtr != nullptr
                                       ? aCelestialSPtr
                                       : Environment::AccessGlobalInstance()->accessCentralCelestialObject();

    if (celestialObjectSPtr == nullptr)
    {
        throw ostk::core::error::runtime::Undefined("Celestial object");
    }

    const Length equatorialRadius = celestialObjectSPtr->getEquatorialRadius();
    const Real flattening = celestialObjectSPtr->getFlattening();

    return LLA::Cartesian(aPosition.inMeters().getCoordinates(), equatorialRadius, flattening);
}

}  // namespace spherical
}  // namespace coordinate
}  // namespace physics
}  // namespace ostk
