/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Unit_Length__
#define __OpenSpaceToolkit_Physics_Unit_Length__

#include <OpenSpaceToolkit/Core/Type/Integer.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include <OpenSpaceToolkit/Physics/Unit/Unit.hpp>

namespace ostk
{
namespace physics
{
namespace unit
{

using ostk::core::type::Integer;
using ostk::core::type::Real;
using ostk::core::type::String;

/// @brief Length
///
/// @ref https://en.wikipedia.org/wiki/Length

class Length : public Unit
{
   public:
    enum class Unit
    {

        Undefined,        ///< Undefined
        Meter,            ///< Meter (SI)
        Foot,             ///< Foot
        TerrestrialMile,  ///< Terrestrial mile
        NauticalMile,     ///< Nautical mile
        AstronomicalUnit  ///< Astronomical Unit

    };

    /// @brief Constructor
    ///
    /// @code
    ///     Length length(1.0, Length::Unit::Meter) ;
    /// @endcode
    ///
    /// @param [in] aValue A value
    /// @param [in] aUnit A length unit
    Length(const Real& aValue, const Length::Unit& aUnit);

    /// @brief Clone the length.
    ///
    /// @code
    ///     Length length = Length::Meters(1.0) ;
    ///     Length* clonePtr = length.clone() ;
    /// @endcode
    ///
    /// @return A pointer to a dynamically allocated clone of this length
    virtual Length* clone() const override;

    /// @brief Equal to operator.
    ///
    /// @code
    ///     Length::Meters(1.0) == Length::Meters(1.0) ; // True
    /// @endcode
    ///
    /// @param [in] aLength A length to compare with
    /// @return True if lengths are equal
    bool operator==(const Length& aLength) const;

    /// @brief Not equal to operator.
    ///
    /// @code
    ///     Length::Meters(1.0) != Length::Meters(2.0) ; // True
    /// @endcode
    ///
    /// @param [in] aLength A length to compare with
    /// @return True if lengths are not equal
    bool operator!=(const Length& aLength) const;

    /// @brief Less than operator.
    ///
    /// @code
    ///     Length::Meters(1.0) < Length::Meters(2.0) ; // True
    /// @endcode
    ///
    /// @param [in] aLength A length to compare with
    /// @return True if this length is less than the given length
    bool operator<(const Length& aLength) const;

    /// @brief Less than or equal to operator.
    ///
    /// @code
    ///     Length::Meters(1.0) <= Length::Meters(1.0) ; // True
    /// @endcode
    ///
    /// @param [in] aLength A length to compare with
    /// @return True if this length is less than or equal to the given length
    bool operator<=(const Length& aLength) const;

    /// @brief Greater than operator.
    ///
    /// @code
    ///     Length::Meters(2.0) > Length::Meters(1.0) ; // True
    /// @endcode
    ///
    /// @param [in] aLength A length to compare with
    /// @return True if this length is greater than the given length
    bool operator>(const Length& aLength) const;

    /// @brief Greater than or equal to operator.
    ///
    /// @code
    ///     Length::Meters(1.0) >= Length::Meters(1.0) ; // True
    /// @endcode
    ///
    /// @param [in] aLength A length to compare with
    /// @return True if this length is greater than or equal to the given length
    bool operator>=(const Length& aLength) const;

    /// @brief Addition operator.
    ///
    /// @code
    ///     Length::Meters(1.0) + Length::Meters(2.0) ; // 3.0 [m]
    /// @endcode
    ///
    /// @param [in] aLength A length to add
    /// @return The sum of the two lengths
    Length operator+(const Length& aLength) const;

    /// @brief Subtraction operator.
    ///
    /// @code
    ///     Length::Meters(3.0) - Length::Meters(1.0) ; // 2.0 [m]
    /// @endcode
    ///
    /// @param [in] aLength A length to subtract
    /// @return The difference of the two lengths
    Length operator-(const Length& aLength) const;

    /// @brief Multiplication by scalar operator.
    ///
    /// @code
    ///     Length::Meters(2.0) * 3.0 ; // 6.0 [m]
    /// @endcode
    ///
    /// @param [in] aReal A scalar multiplier
    /// @return The scaled length
    Length operator*(const Real& aReal) const;

    /// @brief Division by scalar operator.
    ///
    /// @code
    ///     Length::Meters(6.0) / 2.0 ; // 3.0 [m]
    /// @endcode
    ///
    /// @param [in] aReal A scalar divisor
    /// @return The scaled length
    Length operator/(const Real& aReal) const;

    /// @brief Addition assignment operator.
    ///
    /// @code
    ///     Length length = Length::Meters(1.0) ;
    ///     length += Length::Meters(2.0) ; // 3.0 [m]
    /// @endcode
    ///
    /// @param [in] aLength A length to add
    /// @return A reference to this length after addition
    Length& operator+=(const Length& aLength);

    /// @brief Subtraction assignment operator.
    ///
    /// @code
    ///     Length length = Length::Meters(3.0) ;
    ///     length -= Length::Meters(1.0) ; // 2.0 [m]
    /// @endcode
    ///
    /// @param [in] aLength A length to subtract
    /// @return A reference to this length after subtraction
    Length& operator-=(const Length& aLength);

    /// @brief Multiplication assignment operator.
    ///
    /// @code
    ///     Length length = Length::Meters(2.0) ;
    ///     length *= 3.0 ; // 6.0 [m]
    /// @endcode
    ///
    /// @param [in] aReal A scalar multiplier
    /// @return A reference to this length after multiplication
    Length& operator*=(const Real& aReal);

    /// @brief Division assignment operator.
    ///
    /// @code
    ///     Length length = Length::Meters(6.0) ;
    ///     length /= 2.0 ; // 3.0 [m]
    /// @endcode
    ///
    /// @param [in] aReal A scalar divisor
    /// @return A reference to this length after division
    Length& operator/=(const Real& aReal);

    /// @brief Scalar multiplication operator (scalar * length).
    ///
    /// @code
    ///     2.0 * Length::Meters(3.0) ; // 6.0 [m]
    /// @endcode
    ///
    /// @param [in] aReal A scalar multiplier
    /// @param [in] aLength A length
    /// @return The scaled length
    friend Length operator*(const Real& aReal, const Length& aLength);

    /// @brief Unary plus operator.
    ///
    /// @code
    ///     +Length::Meters(1.0) ; // 1.0 [m]
    /// @endcode
    ///
    /// @return A copy of this length
    Length operator+() const;

    /// @brief Unary minus operator.
    ///
    /// @code
    ///     -Length::Meters(1.0) ; // -1.0 [m]
    /// @endcode
    ///
    /// @return The negated length
    Length operator-() const;

    /// @brief Output stream operator.
    ///
    /// @code
    ///     std::cout << Length::Meters(1.0) ;
    /// @endcode
    ///
    /// @param [in] anOutputStream An output stream
    /// @param [in] aLength A length
    /// @return A reference to the output stream
    friend std::ostream& operator<<(std::ostream& anOutputStream, const Length& aLength);

    /// @brief Check if the length is defined.
    ///
    /// @code
    ///     Length::Meters(1.0).isDefined() ; // True
    /// @endcode
    ///
    /// @return True if defined
    virtual bool isDefined() const override;

    /// @brief Check if the length value is zero.
    ///
    /// @code
    ///     Length::Meters(0.0).isZero() ; // True
    /// @endcode
    ///
    /// @return True if zero
    bool isZero() const;

    /// @brief Get the length unit.
    ///
    /// @code
    ///     Length::Meters(1.0).getUnit() ; // Length::Unit::Meter
    /// @endcode
    ///
    /// @return The length unit
    Length::Unit getUnit() const;

    /// @brief Get the value in the specified unit.
    ///
    /// @code
    ///     Length::Meters(1000.0).in(Length::Unit::Meter) ; // 1000.0
    /// @endcode
    ///
    /// @param [in] aUnit A length unit
    /// @return The value in the specified unit
    Real in(const Length::Unit& aUnit) const;

    /// @brief Get the value in meters.
    ///
    /// @code
    ///     Length::Kilometers(1.0).inMeters() ; // 1000.0
    /// @endcode
    ///
    /// @return The value in meters
    Real inMeters() const;

    /// @brief Get the value in kilometers.
    ///
    /// @code
    ///     Length::Meters(1000.0).inKilometers() ; // 1.0
    /// @endcode
    ///
    /// @return The value in kilometers
    Real inKilometers() const;

    /// @brief Convert to string representation.
    ///
    /// @code
    ///     Length::Meters(1.0).toString() ; // "1.0 [m]"
    /// @endcode
    ///
    /// @param [in] aPrecision A precision (number of decimal places)
    /// @return A string representation
    virtual String toString(const Integer& aPrecision = Integer::Undefined()) const override;

    /// @brief Construct an undefined length.
    ///
    /// @code
    ///     Length length = Length::Undefined() ;
    /// @endcode
    ///
    /// @return An undefined length
    static Length Undefined();

    /// @brief Construct a length from a value in millimeters.
    ///
    /// @code
    ///     Length length = Length::Millimeters(1000.0) ;
    /// @endcode
    ///
    /// @param [in] aValue A value in millimeters
    /// @return A length
    static Length Millimeters(const Real& aValue);

    /// @brief Construct a length from a value in meters.
    ///
    /// @code
    ///     Length length = Length::Meters(1.0) ;
    /// @endcode
    ///
    /// @param [in] aValue A value in meters
    /// @return A length
    static Length Meters(const Real& aValue);

    /// @brief Construct a length from a value in kilometers.
    ///
    /// @code
    ///     Length length = Length::Kilometers(1.0) ;
    /// @endcode
    ///
    /// @param [in] aValue A value in kilometers
    /// @return A length
    static Length Kilometers(const Real& aValue);

    /// @brief Parse a length from a string.
    ///
    /// @code
    ///     Length length = Length::Parse("1.0 [m]") ;
    /// @endcode
    ///
    /// @param [in] aString A string to parse
    /// @return A length
    static Length Parse(const String& aString);

    /// @brief Get the string representation of a length unit.
    ///
    /// @code
    ///     Length::StringFromUnit(Length::Unit::Meter) ; // "Meter"
    /// @endcode
    ///
    /// @param [in] aUnit A length unit
    /// @return The string representation
    static String StringFromUnit(const Length::Unit& aUnit);

    /// @brief Get the symbol of a length unit.
    ///
    /// @code
    ///     Length::SymbolFromUnit(Length::Unit::Meter) ; // "m"
    /// @endcode
    ///
    /// @param [in] aUnit A length unit
    /// @return The unit symbol
    static String SymbolFromUnit(const Length::Unit& aUnit);

    /// @brief Get the length unit from a symbol string.
    ///
    /// @code
    ///     Length::UnitFromSymbol("m") ; // Length::Unit::Meter
    /// @endcode
    ///
    /// @param [in] aSymbol A unit symbol
    /// @return The length unit
    static Length::Unit UnitFromSymbol(const String& aSymbol);

   private:
    Length::Unit unit_;

    static Real SIRatio(const Length::Unit& aUnit);
};

}  // namespace unit
}  // namespace physics
}  // namespace ostk

#endif
