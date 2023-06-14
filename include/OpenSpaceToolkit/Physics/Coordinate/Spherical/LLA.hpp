/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Coordinate_Spherical_LLA__
#define __OpenSpaceToolkit_Physics_Coordinate_Spherical_LLA__

#include <OpenSpaceToolkit/Core/Types/Real.hpp>
#include <OpenSpaceToolkit/Core/Types/String.hpp>

#include <OpenSpaceToolkit/Physics/Units/Derived/Angle.hpp>
#include <OpenSpaceToolkit/Physics/Units/Length.hpp>

namespace ostk
{
namespace physics
{
namespace coord
{
namespace spherical
{

using ostk::core::types::Real;
using ostk::core::types::String;

using ostk::math::obj::Vector3d;

using ostk::physics::units::Length;
using ostk::physics::units::Angle;

/// @brief                      Geodetic Latitude - Longitude - Altitude (LLA)
///
/// @ref                        https://en.wikipedia.org/wiki/Latitude
/// @ref                        https://en.wikipedia.org/wiki/Longitude

class LLA
{
   public:
    LLA(const Angle& aLatitude, const Angle& aLongitude, const Length& anAltitude);

    bool operator==(const LLA& aLLA) const;

    bool operator!=(const LLA& aLLA) const;

    friend std::ostream& operator<<(std::ostream& anOutputStream, const LLA& aLLA);

    bool isDefined() const;

    Angle getLatitude() const;

    Angle getLongitude() const;

    Length getAltitude() const;

    /// @brief                  Calculate the distance between this LLA coordinate and another LLA coordinate
    ///
    /// @param                  [in] aLLA A LLA coordinate
    /// @param                  [in] anEllipsoidEquatorialRadius An ellipsoid equatorial radius
    /// @param                  [in] anEllipsoidFlattening An ellipsoid flattening
    /// @return                 Distance between the two LLA coordinates

    Length calculateDistanceTo(
        const LLA& aLLA, const Length& anEllipsoidEquatorialRadius, const Real& anEllipsoidFlattening
    ) const;

    Vector3d toVector() const;

    Vector3d toCartesian(const Length& anEllipsoidEquatorialRadius, const Real& anEllipsoidFlattening) const;

    String toString() const;

    static LLA Undefined();

    static LLA Vector(const Vector3d& aVector);

    static LLA Cartesian(
        const Vector3d& aCartesianCoordinateSet,
        const Length& anEllipsoidEquatorialRadius,
        const Real& anEllipsoidFlattening
    );

    /// @brief                  Calculate the distance between two LLA coordinates
    ///
    /// @param                  [in] aFirstLLA A first LLA coordinate
    /// @param                  [in] aSecondLLA A second LLA coordinate
    /// @param                  [in] anEllipsoidEquatorialRadius An ellipsoid equatorial radius
    /// @param                  [in] anEllipsoidFlattening An ellipsoid flattening
    /// @return                 Distance between the two LLA coordinates

    static Length DistanceBetween(
        const LLA& aFirstLLA,
        const LLA& aSecondLLA,
        const Length& anEllipsoidEquatorialRadius,
        const Real& anEllipsoidFlattening
    );

   private:
    Angle latitude_;
    Angle longitude_;
    Length altitude_;
};

}  // namespace spherical
}  // namespace coord
}  // namespace physics
}  // namespace ostk

#endif
