/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Unit_Unit__
#define __OpenSpaceToolkit_Physics_Unit_Unit__

#include <OpenSpaceToolkit/Core/Container/Pair.hpp>
#include <OpenSpaceToolkit/Core/Type/Integer.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

namespace ostk
{
namespace physics
{
namespace unit
{

using ostk::core::container::Pair;
using ostk::core::type::Integer;
using ostk::core::type::Real;
using ostk::core::type::String;

/// @brief Unit
///
/// @ref https://en.wikipedia.org/wiki/SI_base_unit
///
/// @note Could be (greatly) improved using templating...
/// @note https://benjaminjurke.com/content/articles/2015/compile-time-numerical-unit-dimension-checking/
/// @note https://github.com/nholthaus/units
/// @note https://www.boost.org/doc/libs/1_67_0/doc/html/boost_units.html
class Unit
{
   public:
    enum class Type
    {

        Undefined,
        Length,
        Mass,
        Time,
        Temperature,
        ElectricCurrent,
        LuminousIntensity,
        Derived

    };

    /// @brief Constructor.
    ///
    /// @code
    ///     Unit unit(Unit::Type::Length, 1.0) ;
    /// @endcode
    ///
    /// @param [in] aType A unit type
    /// @param [in] aValue A value
    Unit(const Unit::Type& aType, const Real& aValue);

    /// @brief Pure virtual destructor.
    virtual ~Unit() = 0;

    /// @brief Clone the unit.
    ///
    /// @return A pointer to a dynamically allocated clone of this unit
    virtual Unit* clone() const = 0;

    /// @brief Equal to operator.
    ///
    /// @code
    ///     Unit(Unit::Type::Length, 1.0) == Unit(Unit::Type::Length, 1.0) ; // True
    /// @endcode
    ///
    /// @param [in] aUnit A unit to compare with
    /// @return True if units are equal
    bool operator==(const Unit& aUnit) const;

    /// @brief Not equal to operator.
    ///
    /// @code
    ///     Unit(Unit::Type::Length, 1.0) != Unit(Unit::Type::Mass, 1.0) ; // True
    /// @endcode
    ///
    /// @param [in] aUnit A unit to compare with
    /// @return True if units are not equal
    bool operator!=(const Unit& aUnit) const;

    /// @brief Check if the unit is defined.
    ///
    /// @code
    ///     Unit(Unit::Type::Length, 1.0).isDefined() ; // True
    /// @endcode
    ///
    /// @return True if defined
    virtual bool isDefined() const;

    /// @brief Check if the value is zero.
    ///
    /// @code
    ///     Unit(Unit::Type::Length, 0.0).isZero() ; // True
    /// @endcode
    ///
    /// @return True if zero
    bool isZero() const;

    /// @brief Access the value by const reference.
    ///
    /// @code
    ///     const Real& value = Unit(Unit::Type::Length, 1.0).accessValue() ;
    /// @endcode
    ///
    /// @return A const reference to the value
    const Real& accessValue() const;

    /// @brief Get the unit type.
    ///
    /// @code
    ///     Unit(Unit::Type::Length, 1.0).getType() ; // Unit::Type::Length
    /// @endcode
    ///
    /// @return The unit type
    Unit::Type getType() const;

    /// @brief Get the value.
    ///
    /// @code
    ///     Unit(Unit::Type::Length, 1.0).getValue() ; // 1.0
    /// @endcode
    ///
    /// @return The value
    Real getValue() const;

    /// @brief Convert to string representation.
    ///
    /// @param [in] aPrecision A precision (number of decimal places)
    /// @return A string representation
    virtual String toString(const Integer& aPrecision = Integer::Undefined()) const = 0;

    /// @brief Access the value by mutable reference.
    ///
    /// @code
    ///     Length length = Length::Meters(1.0) ;
    ///     length.accessValue() = 2.0 ;
    /// @endcode
    ///
    /// @return A mutable reference to the value
    Real& accessValue();

    /// @brief Set the value.
    ///
    /// @code
    ///     Length length = Length::Meters(1.0) ;
    ///     length.setValue(2.0) ;
    /// @endcode
    ///
    /// @param [in] aValue A value

    void setValue(const Real& aValue);

   protected:
    /// @brief Parse a string into a value and unit symbol pair.
    ///
    /// @code
    ///     Pair<Real, String> pair = Unit::ParseString("1.0 [m]") ;
    /// @endcode
    ///
    /// @param [in] aString A string to parse
    /// @return A pair of (value, unit symbol)
    static Pair<Real, String> ParseString(const String& aString);

   private:
    Unit::Type type_;
    Real value_;
};

}  // namespace unit
}  // namespace physics
}  // namespace ostk

#endif
