/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Data_Scalar__
#define __OpenSpaceToolkit_Physics_Data_Scalar__

#include <OpenSpaceToolkit/Core/Type/Real.hpp>
#include <OpenSpaceToolkit/Core/Type/Shared.hpp>

#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Unit.hpp>

namespace ostk
{
namespace physics
{
namespace data
{

using ostk::core::type::Integer;
using ostk::core::type::Real;
using ostk::core::type::String;

using ostk::physics::Unit;

/// @brief Scalar quantity
///
/// A scalar quantity is a physical quantity that can be described by a single element of a
/// number field such as a real number, often accompanied by units of measurement.
///
/// @ref https://en.wikipedia.org/wiki/Scalar_(physics)
class Scalar
{
   public:
    /// @brief Construct a scalar from a value and a unit.
    ///
    /// @code
    ///     Scalar scalar(1.0, Unit::Length(Length::Unit::Meter)) ;
    /// @endcode
    ///
    /// @param [in] aValue A real value
    /// @param [in] aUnit A physical unit
    Scalar(const Real& aValue, const Unit& aUnit);

    /// @brief Equality operator.
    ///
    /// @code
    ///     Boolean isEqual = (scalarA == scalarB) ;
    /// @endcode
    ///
    /// @param [in] aScalar A scalar to compare with
    /// @return True if scalars are equal
    bool operator==(const Scalar& aScalar) const;

    /// @brief Inequality operator.
    ///
    /// @code
    ///     Boolean isNotEqual = (scalarA != scalarB) ;
    /// @endcode
    ///
    /// @param [in] aScalar A scalar to compare with
    /// @return True if scalars are not equal
    bool operator!=(const Scalar& aScalar) const;

    /// @brief Output stream operator.
    ///
    /// @code
    ///     std::cout << scalar ;
    /// @endcode
    ///
    /// @param [in] anOutputStream An output stream
    /// @param [in] aScalar A scalar
    /// @return A reference to the output stream
    friend std::ostream& operator<<(std::ostream& anOutputStream, const Scalar& aScalar);

    /// @brief Check if the scalar is defined.
    ///
    /// @code
    ///     Boolean isDefined = scalar.isDefined() ;
    /// @endcode
    ///
    /// @return True if the scalar is defined
    bool isDefined() const;

    /// @brief Get the scalar value.
    ///
    /// @code
    ///     Real value = scalar.getValue() ;
    /// @endcode
    ///
    /// @return The real value
    Real getValue() const;

    /// @brief Get the scalar unit.
    ///
    /// @code
    ///     Unit unit = scalar.getUnit() ;
    /// @endcode
    ///
    /// @return The physical unit
    Unit getUnit() const;

    /// @brief Convert the scalar to a different unit.
    ///
    /// @code
    ///     Scalar scalarInKm = scalar.inUnit(Unit::Length(Length::Unit::Kilometer)) ;
    /// @endcode
    ///
    /// @param [in] aUnit A target unit
    /// @return The scalar expressed in the given unit
    Scalar inUnit(const Unit& aUnit) const;

    /// @brief Convert the scalar to a string representation.
    ///
    /// @code
    ///     String string = scalar.toString() ;
    /// @endcode
    ///
    /// @param [in] aPrecision A precision for the value (optional)
    /// @return A string representation
    String toString(const Integer& aPrecision = Integer::Undefined()) const;

    /// @brief Construct an undefined scalar.
    ///
    /// @code
    ///     Scalar scalar = Scalar::Undefined() ;
    /// @endcode
    ///
    /// @return An undefined scalar
    static Scalar Undefined();

   private:
    Real value_;
    Unit unit_;
};

}  // namespace data
}  // namespace physics
}  // namespace ostk

#endif
