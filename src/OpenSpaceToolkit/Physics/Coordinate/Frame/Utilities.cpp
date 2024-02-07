/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/RotationMatrix.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Utilities.hpp>

namespace ostk
{
namespace physics
{
namespace coord
{
namespace frame
{
namespace utilities
{

Transform NorthEastDownTransformAt(
    const LLA& aLLA, const Length& anEllipsoidEquatorialRadius, const Real& anEllipsoidFlattening
)
{
    using ostk::mathematics::object::Vector3d;
    using ostk::mathematics::geometry::d3::transformation::rotation::Quaternion;
    using ostk::mathematics::geometry::d3::transformation::rotation::RotationMatrix;

    const Vector3d x_NED_ECEF = aLLA.toCartesian(anEllipsoidEquatorialRadius, anEllipsoidFlattening);
    const Vector3d v_NED_ECEF = {0.0, 0.0, 0.0};

    const Real latitude_rad = aLLA.getLatitude().inRadians();
    const Real longitude_rad = aLLA.getLongitude().inRadians();

    Quaternion q_NED_ECEF = Quaternion::Undefined();

    if (latitude_rad == Real::HalfPi())
    {
        q_NED_ECEF = Quaternion::XYZS(0.0, 1.0, 0.0, 0.0);
    }
    else if (latitude_rad == -Real::HalfPi())
    {
        q_NED_ECEF = Quaternion::XYZS(0.0, 0.0, 0.0, 1.0);
    }
    else
    {
        const Real cos_lat = std::cos(latitude_rad);
        const Real sin_lat = std::sin(latitude_rad);

        const Real cos_lon = std::cos(longitude_rad);
        const Real sin_lon = std::sin(longitude_rad);

        const RotationMatrix dcm_NED_ECEF = {
            -sin_lat * cos_lon,
            -sin_lat * sin_lon,
            +cos_lat,
            -sin_lon,
            +cos_lon,
            0.0,
            -cos_lat * cos_lon,
            -cos_lat * sin_lon,
            -sin_lat
        };

        q_NED_ECEF = Quaternion::RotationMatrix(dcm_NED_ECEF).rectify();
    }

    const Vector3d w_NED_ECEF_in_NED = {0.0, 0.0, 0.0};

    return Transform::Passive(Instant::J2000(), -x_NED_ECEF, v_NED_ECEF, q_NED_ECEF, w_NED_ECEF_in_NED);
}

}  // namespace utilities
}  // namespace frame
}  // namespace coord
}  // namespace physics
}  // namespace ostk
