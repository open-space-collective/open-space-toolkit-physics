/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Coordinate_Spherical_LLA__
#define __OpenSpaceToolkit_Physics_Coordinate_Spherical_LLA__

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Container/Pair.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>
#include <OpenSpaceToolkit/Core/Type/Size.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include <OpenSpaceToolkit/Physics/Unit/Derived/Angle.hpp>
#include <OpenSpaceToolkit/Physics/Unit/Length.hpp>

namespace ostk
{
namespace physics
{
namespace coordinate
{
namespace spherical
{

using ostk::core::type::Real;
using ostk::core::type::String;
using ostk::core::type::Size;
using ostk::core::container::Pair;
using ostk::core::container::Array;

using ostk::mathematics::object::Vector3d;

using ostk::physics::unit::Length;
using ostk::physics::unit::Angle;

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

    /// @brief                  Calculate the azimuth angles between this LLA coordinate and another LLA coordinate
    ///
    /// @param                  [in] aLLA A LLA coordinate
    /// @param                  [in] anEllipsoidEquatorialRadius An ellipsoid equatorial radius
    /// @param                  [in] anEllipsoidFlattening An ellipsoid flattening
    /// @return                 Azimuth angle from this LLA coordinate to the other LLA coordinate, and azimuth angle
    /// from the other LLA coordinate to this LLA coordinate.

    Pair<Angle, Angle> calculateAzimuthTo(
        const LLA& aLLA, const Length& anEllipsoidEquatorialRadius, const Real& anEllipsoidFlattening
    ) const;

    /// @brief                  Calculate a point between this LLA coordinate and another LLA coordinate
    ///
    /// @param                  [in] aLLA A LLA coordinate
    /// @param                  [in] aRatio A ratio
    /// @param                  [in] anEllipsoidEquatorialRadius An ellipsoid equatorial radius
    /// @param                  [in] anEllipsoidFlattening An ellipsoid flattening
    /// @return                 A point between the two LLA coordinates

    LLA calculateIntermediateTo(
        const LLA& aLLA,
        const Real& aRatio,
        const Length& anEllipsoidEquatorialRadius,
        const Real& anEllipsoidFlattening
    ) const;

    /// @brief                  Propagate this LLA coordinate in provided direction and distance
    ///
    /// @param                  [in] aDirection An azimuth angle
    /// @param                  [in] aDistance A distance
    /// @param                  [in] anEllipsoidEquatorialRadius An ellipsoid equatorial radius
    /// @param                  [in] anEllipsoidFlattening An ellipsoid flattening
    /// @return                 Propagated LLA coordinate

    LLA calculateForward(
        const Angle& aDirection,
        const Length& aDistance,
        const Length& anEllipsoidEquatorialRadius,
        const Real& anEllipsoidFlattening
    ) const;

    /// @brief                  Generate LLA between this LLA coordinate and another LLA coordinate at a given interval
    ///
    /// @param                  [in] aLLA A LLA coordinate
    /// @param                  [in] aNumberOfPoints A number of points
    /// @param                  [in] anEllipsoidEquatorialRadius An ellipsoid equatorial radius
    /// @param                  [in] anEllipsoidFlattening An ellipsoid flattening

    Array<LLA> calculateIntermediateLLAsTo(
        const LLA& aLLA,
        const Size& aNumberOfPoints,
        const Length& anEllipsoidEquatorialRadius,
        const Real& anEllipsoidFlattening
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

    /// @brief                  Calculate the azimuth angles between two LLA coordinates
    ///
    /// @param                  [in] aFirstLLA A first LLA coordinate
    /// @param                  [in] aSecondLLA A second LLA coordinate
    /// @param                  [in] anEllipsoidEquatorialRadius An ellipsoid equatorial radius
    /// @param                  [in] anEllipsoidFlattening An ellipsoid flattening
    /// @return                 Azimuth angles between the two LLA coordinates

    static Pair<Angle, Angle> AzimuthBetween(
        const LLA& aFirstLLA,
        const LLA& aSecondLLA,
        const Length& anEllipsoidEquatorialRadius,
        const Real& anEllipsoidFlattening
    );

    /// @brief                  Calculate a point between two LLA coordinates
    ///
    /// @param                  [in] aFirstLLA A first LLA coordinate
    /// @param                  [in] aSecondLLA A second LLA coordinate
    /// @param                  [in] aRatio A ratio
    /// @param                  [in] anEllipsoidEquatorialRadius An ellipsoid equatorial radius
    /// @param                  [in] anEllipsoidFlattening An ellipsoid flattening
    /// @return                 A point between the two LLA coordinates

    static LLA IntermediateBetween(
        const LLA& aFirstLLA,
        const LLA& aSecondLLA,
        const Real& aRatio,
        const Length& anEllipsoidEquatorialRadius,
        const Real& anEllipsoidFlattening
    );

    /// @brief                  Propagate LLA coordinates in provided direction and distance
    ///
    /// @param                  [in] aLLA A LLA coordinate
    /// @param                  [in] aDirection An azimuth angle
    /// @param                  [in] aDistance A distance
    /// @param                  [in] anEllipsoidEquatorialRadius An ellipsoid equatorial radius
    /// @param                  [in] anEllipsoidFlattening An ellipsoid flattening
    /// @return                 Propagated LLA coordinate

    static LLA Forward(
        const LLA& aLLA,
        const Angle& aDirection,
        const Length& aDistance,
        const Length& anEllipsoidEquatorialRadius,
        const Real& anEllipsoidFlattening
    );

    /// @brief                  Generate equidistant intermediate LLAs between two LLA coordinates.
    ///
    /// @param                  [in] aFirstLLA A first LLA coordinate
    /// @param                  [in] aSecondLLA A second LLA coordinate
    /// @param                  [in] aNumberOfPoints A number of points
    /// @param                  [in] anEllipsoidEquatorialRadius An ellipsoid equatorial radius
    /// @param                  [in] anEllipsoidFlattening An ellipsoid flattening
    /// @return                 intermediate equidistant LLAs between the two LLA coordinates

    static Array<LLA> IntermediateLLAs(
        const LLA& aFirstLLA,
        const LLA& aSecondLLA,
        const Size& aNumberOfPoints,
        const Length& anEllipsoidEquatorialRadius,
        const Real& anEllipsoidFlattening
    );

   private:
    Angle latitude_;
    Angle longitude_;
    Length altitude_;
};

}  // namespace spherical
}  // namespace coordinate
}  // namespace physics
}  // namespace ostk

#endif
