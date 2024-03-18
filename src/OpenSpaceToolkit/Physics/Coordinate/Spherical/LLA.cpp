/// Apache License 2.0

#include <GeographicLib/Geodesic.hpp>
#include <GeographicLib/GeodesicLine.hpp>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Spherical/LLA.hpp>

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

Length LLA::calculateDistanceTo(
    const LLA& aLLA, const Length& anEllipsoidEquatorialRadius, const Real& anEllipsoidFlattening
) const
{
    return LLA::DistanceBetween(*this, aLLA, anEllipsoidEquatorialRadius, anEllipsoidFlattening);
}

Pair<Angle, Angle> LLA::calculateAzimuthTo(
    const LLA& aLLA, const Length& anEllipsoidEquatorialRadius, const Real& anEllipsoidFlattening
) const
{
    return LLA::AzimuthBetween(*this, aLLA, anEllipsoidEquatorialRadius, anEllipsoidFlattening);
}

LLA LLA::calculateIntermediateTo(
    const LLA& aLLA, const Real& aRatio, const Length& anEllipsoidEquatorialRadius, const Real& anEllipsoidFlattening
) const
{
    return LLA::IntermediateBetween(*this, aLLA, aRatio, anEllipsoidEquatorialRadius, anEllipsoidFlattening);
}

LLA LLA::calculateForward(
    const Angle& aDirection,
    const Length& aDistance,
    const Length& anEllipsoidEquatorialRadius,
    const Real& anEllipsoidFlattening
) const
{
    return LLA::Forward(*this, aDirection, aDistance, anEllipsoidEquatorialRadius, anEllipsoidFlattening);
}

Array<LLA> LLA::calculateLinspaceTo(
    const LLA& aLLA,
    const Size& aNumberOfPoints,
    const Length& anEllipsoidEquatorialRadius,
    const Real& anEllipsoidFlattening
) const
{
    return LLA::Linspace(*this, aLLA, aNumberOfPoints, anEllipsoidEquatorialRadius, anEllipsoidFlattening);
}

Vector3d LLA::toVector() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("LLA");
    }

    return {latitude_.inDegrees(), longitude_.inDegrees(), altitude_.inMeters()};
}

Vector3d LLA::toCartesian(const Length& anEllipsoidEquatorialRadius, const Real& anEllipsoidFlattening) const
{
    if (!anEllipsoidEquatorialRadius.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Ellipsoid equatorial radius");
    }

    if (!anEllipsoidFlattening.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Ellipsoid flattening");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("LLA");
    }

    const double latitude_rad = latitude_.inRadians();
    const double longitude_rad = longitude_.inRadians();
    const double altitude_m = altitude_.inMeters();

    double cartesianArray[3];

    const int result = iauGd2gce(
        anEllipsoidEquatorialRadius.inMeters(),
        anEllipsoidFlattening,
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

    if (!anEllipsoidEquatorialRadius.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Ellipsoid equatorial radius");
    }

    if (!anEllipsoidFlattening.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Ellipsoid flattening");
    }

    double latitude_rad;
    double longitude_rad;
    double altitude_m;

    const int result = iauGc2gde(
        anEllipsoidEquatorialRadius.inMeters(),
        anEllipsoidFlattening,
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
    const GeographicLib::Geodesic& geodesic =
        GeographicLib::Geodesic(anEllipsoidEquatorialRadius.inMeters(), anEllipsoidFlattening);

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
    const GeographicLib::Geodesic& geodesic =
        GeographicLib::Geodesic(anEllipsoidEquatorialRadius.inMeters(), anEllipsoidFlattening);

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
    const GeographicLib::Geodesic& geodesic =
        GeographicLib::Geodesic(anEllipsoidEquatorialRadius.inMeters(), anEllipsoidFlattening);

    const GeographicLib::GeodesicLine& geodesicLine = geodesic.InverseLine(
        aFirstLLA.getLatitude().inDegrees(),
        aFirstLLA.getLongitude().inDegrees(),
        aSecondLLA.getLatitude().inDegrees(),
        aSecondLLA.getLongitude().inDegrees()
    );

    GeographicLib::Math::real latitude_deg;
    GeographicLib::Math::real longitude_deg;

    const Length distance = DistanceBetween(aFirstLLA, aSecondLLA, anEllipsoidEquatorialRadius, anEllipsoidFlattening);

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
    const GeographicLib::Geodesic& geodesic =
        GeographicLib::Geodesic(anEllipsoidEquatorialRadius.inMeters(), anEllipsoidFlattening);

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
    Array<LLA> intermediateLLAs = Array<LLA>::Empty();
    intermediateLLAs.reserve(aNumberOfPoints);

    const GeographicLib::Geodesic& geodesic =
        GeographicLib::Geodesic(anEllipsoidEquatorialRadius.inMeters(), anEllipsoidFlattening);

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

}  // namespace spherical
}  // namespace coordinate
}  // namespace physics
}  // namespace ostk
