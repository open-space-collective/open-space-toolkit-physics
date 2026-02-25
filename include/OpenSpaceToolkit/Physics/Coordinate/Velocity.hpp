/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Coordinate_Velocity__
#define __OpenSpaceToolkit_Physics_Coordinate_Velocity__

#include <OpenSpaceToolkit/Core/Type/Integer.hpp>
#include <OpenSpaceToolkit/Core/Type/Shared.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Position.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Unit/Derived.hpp>

namespace ostk
{
namespace physics
{
namespace coordinate
{

#define DEFAULT_PRECISION Integer::Undefined()

using ostk::core::type::Integer;
using ostk::core::type::Shared;
using ostk::core::type::String;

using ostk::mathematics::object::Vector3d;

using ostk::physics::coordinate::Position;
using ostk::physics::time::Instant;
using ostk::physics::unit::Derived;

class Frame;

/// @brief Velocity

class Velocity
{
   public:
    enum class Unit
    {

        Undefined,
        MeterPerSecond

    };

    /// @brief Constructor
    ///
    /// @code
    ///     Velocity velocity({0.0, 7546.0, 0.0}, Velocity::Unit::MeterPerSecond, Frame::GCRF()) ;
    /// @endcode
    ///
    /// @param [in] aCoordinateSet A coordinate set
    /// @param [in] aUnit A velocity unit
    /// @param [in] aFrameSPtr A shared pointer to a frame
    Velocity(const Vector3d& aCoordinateSet, const Velocity::Unit& aUnit, const Shared<const Frame>& aFrameSPtr);

    /// @brief Equality operator
    ///
    /// @code
    ///     velocity == otherVelocity ; // True
    /// @endcode
    ///
    /// @param [in] aVelocity A velocity to compare with
    /// @return True if velocities are equal
    bool operator==(const Velocity& aVelocity) const;

    /// @brief Inequality operator
    ///
    /// @code
    ///     velocity != otherVelocity ; // False
    /// @endcode
    ///
    /// @param [in] aVelocity A velocity to compare with
    /// @return True if velocities are not equal
    bool operator!=(const Velocity& aVelocity) const;

    /// @brief Output stream operator
    ///
    /// @code
    ///     std::cout << velocity ;
    /// @endcode
    ///
    /// @param [in] anOutputStream An output stream
    /// @param [in] aVelocity A velocity
    /// @return A reference to the output stream
    friend std::ostream& operator<<(std::ostream& anOutputStream, const Velocity& aVelocity);

    /// @brief Check if the velocity is defined
    ///
    /// @code
    ///     Velocity::Undefined().isDefined() ; // False
    /// @endcode
    ///
    /// @return True if the velocity is defined
    bool isDefined() const;

    /// @brief Access coordinates
    ///
    /// @code
    ///     velocity.accessCoordinates() ;
    /// @endcode
    ///
    /// @return Reference to coordinates
    const Vector3d& accessCoordinates() const;

    /// @brief Access frame
    ///
    /// @code
    ///     velocity.accessFrame() ;
    /// @endcode
    ///
    /// @return Shared pointer to the frame
    Shared<const Frame> accessFrame() const;

    /// @brief Get coordinates
    ///
    /// @code
    ///     velocity.getCoordinates() ;
    /// @endcode
    ///
    /// @return Coordinates
    Vector3d getCoordinates() const;

    /// @brief Get the velocity unit
    ///
    /// @code
    ///     velocity.getUnit() ;
    /// @endcode
    ///
    /// @return Velocity unit
    Velocity::Unit getUnit() const;

    /// @brief Convert velocity to a different unit
    ///
    /// @code
    ///     velocity.inUnit(Velocity::Unit::MeterPerSecond) ;
    /// @endcode
    ///
    /// @param [in] aUnit A velocity unit
    /// @return Velocity in the specified unit
    Velocity inUnit(const Velocity::Unit& aUnit) const;

    /// @brief Convert velocity to a different frame at a given instant
    ///
    /// @code
    ///     velocity.inFrame(position, Frame::ITRF(), Instant::J2000()) ;
    /// @endcode
    ///
    /// @param [in] aPosition The associated position
    /// @param [in] aFrameSPtr A shared pointer to the target frame
    /// @param [in] anInstant An instant
    /// @return Velocity in the specified frame
    Velocity inFrame(const Position& aPosition, const Shared<const Frame>& aFrameSPtr, const Instant& anInstant) const;

    /// @brief Convert velocity to string
    ///
    /// @code
    ///     velocity.toString() ;
    /// @endcode
    ///
    /// @param [in] aPrecision A precision
    /// @return String representation of the velocity
    String toString(const Integer& aPrecision = DEFAULT_PRECISION) const;

    /// @brief Construct an undefined velocity
    ///
    /// @code
    ///     Velocity velocity = Velocity::Undefined() ;
    /// @endcode
    ///
    /// @return Undefined velocity
    static Velocity Undefined();

    /// @brief Construct a velocity in meters per second
    ///
    /// @code
    ///     Velocity velocity = Velocity::MetersPerSecond({0.0, 7546.0, 0.0}, Frame::GCRF()) ;
    /// @endcode
    ///
    /// @param [in] aCoordinateSet A coordinate set
    /// @param [in] aFrameSPtr A shared pointer to a frame
    /// @return Velocity in meters per second
    static Velocity MetersPerSecond(const Vector3d& aCoordinateSet, const Shared<const Frame>& aFrameSPtr);

    /// @brief Get the string representation of a velocity unit
    ///
    /// @code
    ///     Velocity::StringFromUnit(Velocity::Unit::MeterPerSecond) ; // "m/s"
    /// @endcode
    ///
    /// @param [in] aUnit A velocity unit
    /// @return String representation of the unit
    static String StringFromUnit(const Velocity::Unit& aUnit);

   private:
    Vector3d coordinates_;
    Velocity::Unit unit_;
    Shared<const Frame> frameSPtr_;  // [TBR] With Transform instead, as Frame is a function of time...

    static Derived::Unit DerivedUnitFromVelocityUnit(const Velocity::Unit& aUnit);
};

}  // namespace coordinate
}  // namespace physics
}  // namespace ostk

#endif
