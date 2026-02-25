/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Data_Vector__
#define __OpenSpaceToolkit_Physics_Data_Vector__

#include <OpenSpaceToolkit/Core/Type/Shared.hpp>

#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Unit.hpp>

namespace ostk
{
namespace physics
{
namespace data
{

using ostk::core::type::Integer;
using ostk::core::type::Shared;
using ostk::core::type::String;

using ostk::mathematics::object::Vector3d;

using ostk::physics::coordinate::Frame;
using ostk::physics::time::Instant;
using ostk::physics::Unit;

/// @brief Vector quantity
class Vector
{
   public:
    /// @brief Construct a vector from a 3D value, a unit, and a reference frame.
    ///
    /// @code
    ///     Vector vector({1.0, 0.0, 0.0}, Unit::Length(Length::Unit::Meter), Frame::GCRF()) ;
    /// @endcode
    ///
    /// @param [in] aValue A 3D vector value
    /// @param [in] aUnit A physical unit
    /// @param [in] aFrameSPtr A shared pointer to the reference frame
    Vector(const Vector3d& aValue, const Unit& aUnit, const Shared<const Frame>& aFrameSPtr);

    /// @brief Equality operator.
    ///
    /// @code
    ///     Boolean isEqual = (vectorA == vectorB) ;
    /// @endcode
    ///
    /// @param [in] aVector A vector to compare with
    /// @return True if vectors are equal
    bool operator==(const Vector& aVector) const;

    /// @brief Inequality operator.
    ///
    /// @code
    ///     Boolean isNotEqual = (vectorA != vectorB) ;
    /// @endcode
    ///
    /// @param [in] aVector A vector to compare with
    /// @return True if vectors are not equal
    bool operator!=(const Vector& aVector) const;

    /// @brief Output stream operator.
    ///
    /// @code
    ///     std::cout << vector ;
    /// @endcode
    ///
    /// @param [in] anOutputStream An output stream
    /// @param [in] aVector A vector
    /// @return A reference to the output stream
    friend std::ostream& operator<<(std::ostream& anOutputStream, const Vector& aVector);

    /// @brief Check if the vector is defined.
    ///
    /// @code
    ///     Boolean isDefined = vector.isDefined() ;
    /// @endcode
    ///
    /// @return True if the vector is defined
    bool isDefined() const;

    /// @brief Get the 3D vector value.
    ///
    /// @code
    ///     Vector3d value = vector.getValue() ;
    /// @endcode
    ///
    /// @return The 3D vector value
    Vector3d getValue() const;

    /// @brief Get the vector unit.
    ///
    /// @code
    ///     Unit unit = vector.getUnit() ;
    /// @endcode
    ///
    /// @return The physical unit
    Unit getUnit() const;

    /// @brief Get the reference frame.
    ///
    /// @code
    ///     Shared<const Frame> frameSPtr = vector.getFrame() ;
    /// @endcode
    ///
    /// @return A shared pointer to the reference frame
    Shared<const Frame> getFrame() const;

    /// @brief Convert the vector to a different unit.
    ///
    /// @code
    ///     Vector vectorInKm = vector.inUnit(Unit::Length(Length::Unit::Kilometer)) ;
    /// @endcode
    ///
    /// @param [in] aUnit A target unit
    /// @return The vector expressed in the given unit
    Vector inUnit(const Unit& aUnit) const;

    /// @brief Transform the vector into a different reference frame at a given instant.
    ///
    /// @code
    ///     Vector vectorInITRF = vector.inFrame(Frame::ITRF(), instant) ;
    /// @endcode
    ///
    /// @param [in] aFrameSPtr A shared pointer to the target reference frame
    /// @param [in] anInstant An instant of time
    /// @return The vector expressed in the given frame
    Vector inFrame(const Shared<const Frame>& aFrameSPtr, const Instant& anInstant) const;

    /// @brief Convert the vector to a string representation.
    ///
    /// @code
    ///     String string = vector.toString() ;
    /// @endcode
    ///
    /// @param [in] aPrecision A precision for the values (default: 6)
    /// @return A string representation
    String toString(const Integer& aPrecision = 6) const;

    /// @brief Construct an undefined vector.
    ///
    /// @code
    ///     Vector vector = Vector::Undefined() ;
    /// @endcode
    ///
    /// @return An undefined vector
    static Vector Undefined();

   private:
    Vector3d value_;
    Unit unit_;
    Shared<const Frame> frameSPtr_;
};

}  // namespace data
}  // namespace physics
}  // namespace ostk

#endif
