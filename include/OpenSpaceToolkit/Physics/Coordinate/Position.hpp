/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Coordinate_Position__
#define __OpenSpaceToolkit_Physics_Coordinate_Position__

#include <OpenSpaceToolkit/Core/Type/Integer.hpp>
#include <OpenSpaceToolkit/Core/Type/Shared.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Point.hpp>
#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
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

#define DEFAULT_PRECISION Integer::Undefined()

using ostk::core::type::Integer;
using ostk::core::type::Shared;
using ostk::core::type::String;

using ostk::mathematics::geometry::d3::object::Point;
using ostk::mathematics::object::Vector3d;

using ostk::physics::time::Instant;
using ostk::physics::unit::Length;

class Frame;

namespace spherical
{
class LLA;
}

/// @brief                      Position

class Position
{
   public:
    typedef Length::Unit Unit;

    /// @brief                  Constructor
    ///
    /// @param                  [in] aCoordinateSet A coordinate set
    /// @param                  [in] aUnit A unit
    /// @param                  [in] aFrameSPtr A shared pointer to a frame
    Position(
        const Vector3d& aCoordinateSet,  // [TBI] Replace w/ Point
        const Position::Unit& aUnit,
        const Shared<const Frame>& aFrameSPtr
    );

    /// @brief                  Copy constructor
    ///
    /// @param                  [in] aPosition A position
    Position(const Position& aPosition);

    /// @brief                  Copy assignment operator
    ///
    /// @param                  [in] aPosition A position
    /// @return                 Reference to position
    Position& operator=(const Position& aPosition);

    /// @brief                  Equality operator
    ///
    /// @param                  [in] aPosition A position
    /// @return                 True if positions are equal
    bool operator==(const Position& aPosition) const;

    /// @brief                  Inequality operator
    ///
    /// @param                  [in] aPosition A position
    /// @return                 True if positions are not equal
    bool operator!=(const Position& aPosition) const;

    /// @brief                  Output stream operator
    ///
    /// @param                  [in] anOutputStream An output stream
    /// @param                  [in] aPosition A position
    /// @return                 A reference to output stream
    friend std::ostream& operator<<(std::ostream& anOutputStream, const Position& aPosition);

    /// @brief                  Check if position is defined
    ///
    /// @return                 True if position is defined
    bool isDefined() const;

    /// @brief                  Check if position is near another position within a tolerance
    ///
    /// @param                  [in] aPosition A position
    /// @param                  [in] aTolerance A tolerance
    /// @return                 True if position is near the other position within the tolerance
    bool isNear(const Position& aPosition, const Length& aTolerance) const;

    /// @brief                  Access coordinates
    ///
    /// @return                 Reference to coordinates
    const Vector3d& accessCoordinates() const;

    /// @brief                  Access frame
    ///
    /// @return                 Shared pointer to frame
    Shared<const Frame> accessFrame() const;

    /// @brief                  Get coordinates
    ///
    /// @return                 Coordinates
    Vector3d getCoordinates() const;

    /// @brief                  Get unit
    ///
    /// @return                 Unit
    Position::Unit getUnit() const;

    /// @brief                  Convert position to a different unit
    ///
    /// @param                  [in] aUnit A unit
    /// @return                 Position in the specified unit
    Position inUnit(const Position::Unit& aUnit) const;

    /// @brief                  Convert position to meters
    ///
    /// @return                 Position in meters
    Position inMeters() const;

    /// @brief                  Convert position to a different frame at a given instant
    ///
    /// @param                  [in] aFrameSPtr A shared pointer to a frame
    /// @param                  [in] anInstant An instant
    /// @return                 Position in the specified frame
    Position inFrame(const Shared<const Frame>& aFrameSPtr, const Instant& anInstant) const;

    /// @brief                  Convert position to string
    ///
    /// @param                  [in] aPrecision A precision
    /// @return                 String representation of the position
    String toString(const Integer& aPrecision = DEFAULT_PRECISION) const;

    /// @brief                  Constructs an undefined position
    ///
    /// @return                 Undefined position
    static Position Undefined();

    /// @brief                  Constructs a position in meters
    ///
    /// @param                  [in] aCoordinateSet A coordinate set
    /// @param                  [in] aFrameSPtr A shared pointer to a frame
    /// @return                 Position in meters
    static Position Meters(const Vector3d& aCoordinateSet, const Shared<const Frame>& aFrameSPtr);

    /// @brief                  Constructs a position from an LLA coordinate. If a celestial object is not provided, the
    /// central body from the global environment instance will be used if it's available.
    ///
    /// @param                  [in] aLLA A LLA coordinate
    /// @param                  [in] aCelestialSPtr A shared pointer to a celestial object
    /// @return                 Position
    static Position FromLLA(
        const spherical::LLA& aLLA, const Shared<const environment::object::Celestial>& aCelestialSPtr = nullptr
    );

   private:
    Vector3d coordinates_;
    Position::Unit unit_;
    Shared<const Frame> frameSPtr_;  // [TBR] With Transform instead, as Frame is a function of time...
};

}  // namespace coordinate
}  // namespace physics
}  // namespace ostk

#endif
