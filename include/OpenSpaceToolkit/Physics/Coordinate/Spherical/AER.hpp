/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Coordinate_Spherical_AER__
#define __OpenSpaceToolkit_Physics_Coordinate_Spherical_AER__

#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Position.hpp>
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

#define DEFAULT_IS_Z_NEGATIVE true

using ostk::core::type::String;

using ostk::mathematics::object::Vector3d;

using ostk::physics::coordinate::Position;
using ostk::physics::unit::Angle;
using ostk::physics::unit::Length;

/// @brief Azimuth - Elevation - Range (AER)

class AER
{
   public:
    /// @brief Constructor
    ///
    /// @code
    ///     AER aer(Angle::Degrees(45.0), Angle::Degrees(30.0), Length::Meters(1000.0));
    /// @endcode
    ///
    /// @param [in] anAzimuth An azimuth angle
    /// @param [in] anElevation An elevation angle
    /// @param [in] aRange A range
    AER(const Angle& anAzimuth, const Angle& anElevation, const Length& aRange);

    /// @brief Equality operator
    ///
    /// @code
    ///     aer == otherAER; // True
    /// @endcode
    ///
    /// @param [in] anAER An AER object to compare with
    /// @return True if AER objects are equal
    bool operator==(const AER& anAER) const;

    /// @brief Inequality operator
    ///
    /// @code
    ///     aer != otherAER; // False
    /// @endcode
    ///
    /// @param [in] anAER An AER object to compare with
    /// @return True if AER objects are not equal
    bool operator!=(const AER& anAER) const;

    /// @brief Output stream operator
    ///
    /// @code
    ///     std::cout << aer;
    /// @endcode
    ///
    /// @param [in] anOutputStream An output stream
    /// @param [in] anAER An AER object
    /// @return A reference to the output stream
    friend std::ostream& operator<<(std::ostream& anOutputStream, const AER& anAER);

    /// @brief Check if the AER object is defined
    ///
    /// @code
    ///     AER::Undefined().isDefined(); // False
    /// @endcode
    ///
    /// @return True if the AER object is defined
    bool isDefined() const;

    /// @brief Get the azimuth angle
    ///
    /// @code
    ///     aer.getAzimuth();
    /// @endcode
    ///
    /// @return Azimuth angle
    Angle getAzimuth() const;

    /// @brief Get the elevation angle
    ///
    /// @code
    ///     aer.getElevation();
    /// @endcode
    ///
    /// @return Elevation angle
    Angle getElevation() const;

    /// @brief Get the range
    ///
    /// @code
    ///     aer.getRange();
    /// @endcode
    ///
    /// @return Range
    Length getRange() const;

    /// @brief Convert AER to a 3D vector (azimuth, elevation, range)
    ///
    /// @code
    ///     aer.toVector();
    /// @endcode
    ///
    /// @return 3D vector representation
    Vector3d toVector() const;

    /// @brief Convert AER to Cartesian coordinates
    ///
    /// @code
    ///     aer.toCartesian();
    /// @endcode
    ///
    /// @return Cartesian coordinate vector
    Vector3d toCartesian() const;  // [TBI]

    /// @brief Convert AER to string
    ///
    /// @code
    ///     aer.toString();
    /// @endcode
    ///
    /// @return String representation of the AER object
    String toString() const;

    /// @brief Construct an undefined AER object
    ///
    /// @code
    ///     AER aer = AER::Undefined();
    /// @endcode
    ///
    /// @return Undefined AER
    static AER Undefined();

    /// @brief Construct an AER object from a 3D vector
    ///
    /// @code
    ///     AER aer = AER::Vector({45.0, 30.0, 1000.0});
    /// @endcode
    ///
    /// @param [in] aVector A 3D vector (azimuth, elevation, range)
    /// @return AER object
    static AER Vector(const Vector3d& aVector);

    /// @brief AER from the relative position between two positions
    ///
    /// @code
    ///     AER aer = AER::FromPositionToPosition(fromPosition, toPosition);
    /// @endcode
    ///
    /// @param [in] aFromPosition A FROM position
    /// @param [in] aToPosition A TO position
    /// @param [in] (optional) isZNegative If true, elevation is measured positive toward the -Z axis

    static AER FromPositionToPosition(
        const Position& aFromPosition, const Position& aToPosition, const bool isZNegative = DEFAULT_IS_Z_NEGATIVE
    );

   private:
    Angle azimuth_;
    Angle elevation_;
    Length range_;
};

}  // namespace spherical
}  // namespace coordinate
}  // namespace physics
}  // namespace ostk

#endif
