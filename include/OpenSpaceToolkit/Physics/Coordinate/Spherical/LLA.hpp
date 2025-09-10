/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Coordinate_Spherical_LLA__
#define __OpenSpaceToolkit_Physics_Coordinate_Spherical_LLA__

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Container/Pair.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>
#include <OpenSpaceToolkit/Core/Type/Shared.hpp>
#include <OpenSpaceToolkit/Core/Type/Size.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object/Point.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Point.hpp>

#include <OpenSpaceToolkit/Physics/Unit/Derived/Angle.hpp>
#include <OpenSpaceToolkit/Physics/Unit/Length.hpp>

namespace ostk
{
namespace physics
{

namespace environment
{
namespace object
{
class Celestial;
}
}  // namespace environment

namespace coordinate
{

class Position;

namespace spherical
{

using ostk::core::container::Array;
using ostk::core::container::Pair;
using ostk::core::type::Real;
using ostk::core::type::Shared;
using ostk::core::type::Size;
using ostk::core::type::String;

using Point2d = ostk::mathematics::geometry::d2::object::Point;
using Point3d = ostk::mathematics::geometry::d3::object::Point;
using ostk::mathematics::object::Vector3d;

using ostk::physics::unit::Angle;
using ostk::physics::unit::Length;

/// @brief                      Geodetic Latitude - Longitude - Altitude (LLA)
///
/// @ref                        https://en.wikipedia.org/wiki/Latitude
/// @ref                        https://en.wikipedia.org/wiki/Longitude

class LLA
{
   public:
    /// @brief Constructs an LLA (Latitude, Longitude, Altitude) object.
    ///
    /// @param aLatitude Latitude angle.
    /// @param aLongitude Longitude angle.
    /// @param anAltitude Altitude length.

    LLA(const Angle& aLatitude, const Angle& aLongitude, const Length& anAltitude);

    /// @brief Equality operator.
    ///
    /// @param aLLA Another LLA object to compare with.
    /// @return True if both LLA objects are equal.

    bool operator==(const LLA& aLLA) const;

    /// @brief Inequality operator.
    ///
    /// @param aLLA Another LLA object to compare with.
    /// @return True if both LLA objects are not equal.

    bool operator!=(const LLA& aLLA) const;

    /// @brief Output stream operator.
    ///
    /// @param anOutputStream Output stream.
    /// @param aLLA LLA object to output.
    /// @return Reference to the output stream.

    friend std::ostream& operator<<(std::ostream& anOutputStream, const LLA& aLLA);

    /// @brief Checks if the LLA object is defined.
    ///
    /// @return True if the LLA object is defined.

    bool isDefined() const;

    /// @brief Gets the latitude angle.
    ///
    /// @return Latitude angle.

    Angle getLatitude() const;

    /// @brief Gets the longitude angle.
    ///
    /// @return Longitude angle.

    Angle getLongitude() const;

    /// @brief Gets the altitude length.
    ///
    /// @return Altitude length.

    Length getAltitude() const;

    /// @brief Returns an LLA object representing the position on the surface.
    /// @return An LLA object on the surface.

    LLA onSurface() const;

    /// @brief                  Calculate the distance between this LLA coordinate and another LLA coordinate
    /// @brief                  Calculate the distance between this LLA coordinate and another LLA coordinate. Will use
    /// the central celestial from the global environment if no ellipsoid parameters are provided.
    ///
    /// @param                  [in] aLLA A LLA coordinate
    /// @param                  [in] anEllipsoidEquatorialRadius An ellipsoid equatorial radius
    /// @param                  [in] anEllipsoidFlattening An ellipsoid flattening
    /// @return                 Distance between the two LLA coordinates

    Length calculateDistanceTo(
        const LLA& aLLA,
        const Length& anEllipsoidEquatorialRadius = Length::Undefined(),
        const Real& anEllipsoidFlattening = Real::Undefined()
    ) const;

    /// @brief                  Calculate the azimuth angles between this LLA coordinate and another LLA coordinate.
    /// Will use the central celestial from the global environment if no ellipsoid parameters are provided.
    ///
    /// @param                  [in] aLLA A LLA coordinate
    /// @param                  [in] anEllipsoidEquatorialRadius An ellipsoid equatorial radius
    /// @param                  [in] anEllipsoidFlattening An ellipsoid flattening
    /// @return                 Azimuth angle from this LLA coordinate to the other LLA coordinate, and azimuth angle
    /// from the other LLA coordinate to this LLA coordinate.

    Pair<Angle, Angle> calculateAzimuthTo(
        const LLA& aLLA,
        const Length& anEllipsoidEquatorialRadius = Length::Undefined(),
        const Real& anEllipsoidFlattening = Real::Undefined()
    ) const;

    /// @brief                  Calculate a point between this LLA coordinate and another LLA coordinate. Will use
    /// the central celestial from the global environment if no ellipsoid parameters are provided.
    ///
    /// @param                  [in] aLLA A LLA coordinate
    /// @param                  [in] aRatio A ratio
    /// @param                  [in] anEllipsoidEquatorialRadius An ellipsoid equatorial radius
    /// @param                  [in] anEllipsoidFlattening An ellipsoid flattening
    /// @return                 A point between the two LLA coordinates

    LLA calculateIntermediateTo(
        const LLA& aLLA,
        const Real& aRatio,
        const Length& anEllipsoidEquatorialRadius = Length::Undefined(),
        const Real& anEllipsoidFlattening = Real::Undefined()
    ) const;

    /// @brief                  Propagate this LLA coordinate in provided direction and distance. Will use
    /// the central celestial from the global environment if no ellipsoid parameters are provided.
    ///
    /// @param                  [in] aDirection An azimuth angle
    /// @param                  [in] aDistance A distance
    /// @param                  [in] anEllipsoidEquatorialRadius An ellipsoid equatorial radius
    /// @param                  [in] anEllipsoidFlattening An ellipsoid flattening
    /// @return                 Propagated LLA coordinate

    LLA calculateForward(
        const Angle& aDirection,
        const Length& aDistance,
        const Length& anEllipsoidEquatorialRadius = Length::Undefined(),
        const Real& anEllipsoidFlattening = Real::Undefined()
    ) const;

    /// @brief                  Generate LLAs between this LLA coordinate and another LLA coordinate at a given
    /// interval. Will use the central celestial from the global environment if no ellipsoid parameters are provided.
    ///
    /// @param                  [in] aLLA A LLA coordinate
    /// @param                  [in] aNumberOfPoints A number of points
    /// @param                  [in] anEllipsoidEquatorialRadius An ellipsoid equatorial radius
    /// @param                  [in] anEllipsoidFlattening An ellipsoid flattening

    Array<LLA> calculateLinspaceTo(
        const LLA& aLLA,
        const Size& aNumberOfPoints,
        const Length& anEllipsoidEquatorialRadius = Length::Undefined(),
        const Real& anEllipsoidFlattening = Real::Undefined()
    ) const;

    /// @brief                  Converts the LLA (Latitude, Longitude, Altitude) object to coordinates in the same order.
    ///
    /// @return                 Coordinates of the LLA object.
    Vector3d toCoordinates() const;

    /// @brief                  Convert LLA coordinates to a 2D point
    ///
    /// @return                 2D point (Longitude, Latitude)

    Point2d toPoint2d() const;

    /// @brief                  Convert LLA coordinates to a 3D point
    ///
    /// @return                 3D point (Longitude, Latitude, Altitude)

    Point3d toPoint3d() const;

    /// @brief                  Converts the LLA (Latitude, Longitude, Altitude) object to Cartesian coordinates.
    ///
    /// @param                  [in] anEllipsoidEquatorialRadius Equatorial radius of the ellipsoid
    /// @param                  [in] anEllipsoidFlattening Flattening of the ellipsoid
    /// @return                 3D vector representing the Cartesian coordinates.
    Vector3d toCartesian(
        const Length& anEllipsoidEquatorialRadius = Length::Undefined(),
        const Real& anEllipsoidFlattening = Real::Undefined()
    ) const;

    /// @brief                  Converts the LLA (Latitude, Longitude, Altitude) object to a string representation.
    ///
    /// @return                 String representation of the LLA object.
    String toString() const;

    /// @brief                  Constructs an undefined LLA (Latitude, Longitude, Altitude) object.
    ///
    /// @return                 Undefined LLA object.
    static LLA Undefined();

    /// @brief                  Constructs an LLA (Latitude, Longitude, Altitude) object from coordinates in the same order.
    ///
    /// @param                  [in] aCoordinates representing the LLA coordinates in (Latitude, Longitude, Altitude) order.
    /// @return                  LLA object constructed from the 3D vector.
    static LLA Coordinates(const Vector3d& aCoordinates);

    /// @brief                  Constructs an LLA (Latitude, Longitude, Altitude) object from Cartesian coordinates.
    ///
    /// @param                  [in] aCartesianCoordinateSet 3D vector representing the Cartesian coordinates.
    /// @param                  [in] anEllipsoidEquatorialRadius Equatorial radius of the ellipsoid (optional).
    /// @param                  [in] anEllipsoidFlattening Flattening of the ellipsoid (optional).
    /// @return                  LLA object constructed from the Cartesian coordinates.
    static LLA Cartesian(
        const Vector3d& aCartesianCoordinateSet,
        const Length& anEllipsoidEquatorialRadius = Length::Undefined(),
        const Real& anEllipsoidFlattening = Real::Undefined()
    );

    /// @brief                  Calculate the distance between two LLA coordinates. Will use
    /// the central celestial from the global environment if no ellipsoid parameters are provided.
    ///
    /// @param                  [in] aFirstLLA A first LLA coordinate
    /// @param                  [in] aSecondLLA A second LLA coordinate
    /// @param                  [in] anEllipsoidEquatorialRadius An ellipsoid equatorial radius
    /// @param                  [in] anEllipsoidFlattening An ellipsoid flattening
    /// @return                 Distance between the two LLA coordinates

    static Length DistanceBetween(
        const LLA& aFirstLLA,
        const LLA& aSecondLLA,
        const Length& anEllipsoidEquatorialRadius = Length::Undefined(),
        const Real& anEllipsoidFlattening = Real::Undefined()
    );

    /// @brief                  Calculate the azimuth angles between two LLA coordinates. Will use
    /// the central celestial from the global environment if no ellipsoid parameters are provided.
    ///
    /// @param                  [in] aFirstLLA A first LLA coordinate
    /// @param                  [in] aSecondLLA A second LLA coordinate
    /// @param                  [in] anEllipsoidEquatorialRadius An ellipsoid equatorial radius
    /// @param                  [in] anEllipsoidFlattening An ellipsoid flattening
    /// @return                 Azimuth angles between the two LLA coordinates

    static Pair<Angle, Angle> AzimuthBetween(
        const LLA& aFirstLLA,
        const LLA& aSecondLLA,
        const Length& anEllipsoidEquatorialRadius = Length::Undefined(),
        const Real& anEllipsoidFlattening = Real::Undefined()
    );

    /// @brief                  Calculate a point between two LLA coordinates. Will use
    /// the central celestial from the global environment if no ellipsoid parameters are provided.
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
        const Length& anEllipsoidEquatorialRadius = Length::Undefined(),
        const Real& anEllipsoidFlattening = Real::Undefined()
    );

    /// @brief                  Propagate LLA coordinates in provided direction and distance. Will use
    /// the central celestial from the global environment if no ellipsoid parameters are provided.
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
        const Length& anEllipsoidEquatorialRadius = Length::Undefined(),
        const Real& anEllipsoidFlattening = Real::Undefined()
    );

    /// @brief                  Generate equidistant LLAs between two LLA coordinates for the specified number of
    /// points. Will use the central celestial from the global environment if no ellipsoid parameters are provided.
    ///
    /// @param                  [in] aFirstLLA A first LLA coordinate
    /// @param                  [in] aSecondLLA A second LLA coordinate
    /// @param                  [in] aNumberOfPoints A number of points
    /// @param                  [in] anEllipsoidEquatorialRadius An ellipsoid equatorial radius
    /// @param                  [in] anEllipsoidFlattening An ellipsoid flattening
    /// @return                 intermediate equidistant LLAs between the two LLA coordinates

    static Array<LLA> Linspace(
        const LLA& aFirstLLA,
        const LLA& aSecondLLA,
        const Size& aNumberOfPoints,
        const Length& anEllipsoidEquatorialRadius = Length::Undefined(),
        const Real& anEllipsoidFlattening = Real::Undefined()
    );

    /// @brief                  Constructs an LLA from a Position. If a celestial object is not provided, the
    /// central body from the global environment instance will be used if it's available.
    ///
    /// @param                  [in] aPosition A Position
    /// @param                  [in] aCelestialSPtr A shared pointer to a celestial object
    /// @return                 LLA
    static LLA FromPosition(
        const Position& aPosition, const Shared<const environment::object::Celestial>& aCelestialSPtr = nullptr
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
