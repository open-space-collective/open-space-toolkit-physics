/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Spherical/LLA.hpp>

// Include sofa last to avoid type errors in underlying Eigen lib
#include <sofa/sofa.h>

namespace ostk
{
namespace physics
{
namespace coord
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

}  // namespace spherical
}  // namespace coord
}  // namespace physics
}  // namespace ostk

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
