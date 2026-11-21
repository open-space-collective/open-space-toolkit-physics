/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Unit_Mass__
#define __OpenSpaceToolkit_Physics_Unit_Mass__

#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include <OpenSpaceToolkit/Physics/Unit/Unit.hpp>

namespace ostk
{
namespace physics
{
namespace unit
{

using ostk::core::type::String;

/// @brief Mass
///
/// @ref https://en.wikipedia.org/wiki/Mass

class Mass : public Unit
{
   public:
    enum class Unit
    {

        Kilogram,  ///< Kilogram (SI)
        Tonne,     ///< Tonne
        Pound      ///< Pound

    };

    /// @brief Constructor
    ///
    /// @code
    ///     Mass mass(1.0, Mass::Unit::Kilogram);
    /// @endcode
    ///
    /// @param [in] aValue A value
    /// @param [in] aUnit A mass unit
    Mass(double aValue, const Mass::Unit& aUnit);

    /// @brief Clone the mass.
    ///
    /// @code
    ///     Mass mass = Mass::Kilograms(1.0);
    ///     Mass* clonePtr = mass.clone();
    /// @endcode
    ///
    /// @return A pointer to a dynamically allocated clone of this mass

    virtual Mass* clone() const override;

    /// @brief Equal to operator.
    ///
    /// @code
    ///     Mass::Kilograms(1.0) == Mass::Kilograms(1.0); // True
    /// @endcode
    ///
    /// @param [in] aMass A mass to compare with
    /// @return True if masses are equal
    bool operator==(const Mass& aMass) const;

    /// @brief Not equal to operator.
    ///
    /// @code
    ///     Mass::Kilograms(1.0) != Mass::Kilograms(2.0); // True
    /// @endcode
    ///
    /// @param [in] aMass A mass to compare with
    /// @return True if masses are not equal
    bool operator!=(const Mass& aMass) const;

    /// @brief Less than operator.
    ///
    /// @code
    ///     Mass::Kilograms(1.0) < Mass::Kilograms(2.0); // True
    /// @endcode
    ///
    /// @param [in] aMass A mass to compare with
    /// @return True if this mass is less than the given mass
    bool operator<(const Mass& aMass) const;

    /// @brief Less than or equal to operator.
    ///
    /// @code
    ///     Mass::Kilograms(1.0) <= Mass::Kilograms(1.0); // True
    /// @endcode
    ///
    /// @param [in] aMass A mass to compare with
    /// @return True if this mass is less than or equal to the given mass
    bool operator<=(const Mass& aMass) const;

    /// @brief Greater than operator.
    ///
    /// @code
    ///     Mass::Kilograms(2.0) > Mass::Kilograms(1.0); // True
    /// @endcode
    ///
    /// @param [in] aMass A mass to compare with
    /// @return True if this mass is greater than the given mass
    bool operator>(const Mass& aMass) const;

    /// @brief Greater than or equal to operator.
    ///
    /// @code
    ///     Mass::Kilograms(1.0) >= Mass::Kilograms(1.0); // True
    /// @endcode
    ///
    /// @param [in] aMass A mass to compare with
    /// @return True if this mass is greater than or equal to the given mass
    bool operator>=(const Mass& aMass) const;

    /// @brief Addition operator.
    ///
    /// @code
    ///     Mass::Kilograms(1.0) + Mass::Kilograms(2.0); // 3.0 [kg]
    /// @endcode
    ///
    /// @param [in] aMass A mass to add
    /// @return The sum of the two masses
    Mass operator+(const Mass& aMass) const;

    /// @brief Subtraction operator.
    ///
    /// @code
    ///     Mass::Kilograms(3.0) - Mass::Kilograms(1.0); // 2.0 [kg]
    /// @endcode
    ///
    /// @param [in] aMass A mass to subtract
    /// @return The difference of the two masses
    Mass operator-(const Mass& aMass) const;

    /// @brief Multiplication by scalar operator.
    ///
    /// @code
    ///     Mass::Kilograms(2.0) * 3.0; // 6.0 [kg]
    /// @endcode
    ///
    /// @param [in] aReal A scalar multiplier
    /// @return The scaled mass
    Mass operator*(double aReal) const;

    /// @brief Division by scalar operator.
    ///
    /// @code
    ///     Mass::Kilograms(6.0) / 2.0; // 3.0 [kg]
    /// @endcode
    ///
    /// @param [in] aReal A scalar divisor
    /// @return The scaled mass
    Mass operator/(double aReal) const;

    /// @brief Addition assignment operator.
    ///
    /// @code
    ///     Mass mass = Mass::Kilograms(1.0);
    ///     mass += Mass::Kilograms(2.0); // 3.0 [kg]
    /// @endcode
    ///
    /// @param [in] aMass A mass to add
    /// @return A reference to this mass after addition
    Mass& operator+=(const Mass& aMass);

    /// @brief Subtraction assignment operator.
    ///
    /// @code
    ///     Mass mass = Mass::Kilograms(3.0);
    ///     mass -= Mass::Kilograms(1.0); // 2.0 [kg]
    /// @endcode
    ///
    /// @param [in] aMass A mass to subtract
    /// @return A reference to this mass after subtraction
    Mass& operator-=(const Mass& aMass);

    /// @brief Multiplication assignment operator.
    ///
    /// @code
    ///     Mass mass = Mass::Kilograms(2.0);
    ///     mass *= 3.0; // 6.0 [kg]
    /// @endcode
    ///
    /// @param [in] aReal A scalar multiplier
    /// @return A reference to this mass after multiplication
    Mass& operator*=(double aReal);

    /// @brief Division assignment operator.
    ///
    /// @code
    ///     Mass mass = Mass::Kilograms(6.0);
    ///     mass /= 2.0; // 3.0 [kg]
    /// @endcode
    ///
    /// @param [in] aReal A scalar divisor
    /// @return A reference to this mass after division
    Mass& operator/=(double aReal);

    /// @brief Scalar multiplication operator (scalar * mass).
    ///
    /// @code
    ///     2.0 * Mass::Kilograms(3.0); // 6.0 [kg]
    /// @endcode
    ///
    /// @param [in] aReal A scalar multiplier
    /// @param [in] aMass A mass
    /// @return The scaled mass
    friend Mass operator*(double aReal, const Mass& aMass);

    /// @brief Unary plus operator.
    ///
    /// @code
    ///     +Mass::Kilograms(1.0); // 1.0 [kg]
    /// @endcode
    ///
    /// @return A copy of this mass
    Mass operator+() const;

    /// @brief Unary minus operator.
    ///
    /// @code
    ///     -Mass::Kilograms(1.0); // -1.0 [kg]
    /// @endcode
    ///
    /// @return The negated mass
    Mass operator-() const;

    /// @brief Output stream operator.
    ///
    /// @code
    ///     std::cout << Mass::Kilograms(1.0);
    /// @endcode
    ///
    /// @param [in] anOutputStream An output stream
    /// @param [in] aMass A mass
    /// @return A reference to the output stream
    friend std::ostream& operator<<(std::ostream& anOutputStream, const Mass& aMass);

    /// @brief Get the mass unit.
    ///
    /// @code
    ///     Mass::Kilograms(1.0).getUnit(); // Mass::Unit::Kilogram
    /// @endcode
    ///
    /// @return The mass unit

    Mass::Unit getUnit() const;

    /// @brief Get the value in the specified unit.
    ///
    /// @code
    ///     Mass::Kilograms(1.0).in(Mass::Unit::Kilogram); // 1.0
    /// @endcode
    ///
    /// @param [in] aUnit A mass unit
    /// @return The value in the specified unit

    double in(const Mass::Unit& aUnit) const;

    /// @brief Get the value in kilograms.
    ///
    /// @code
    ///     Mass::Kilograms(1.0).inKilograms(); // 1.0
    /// @endcode
    ///
    /// @return The value in kilograms

    double inKilograms() const;

    /// @brief Convert to string representation.
    ///
    /// @code
    ///     Mass::Kilograms(1.0).toString();
    /// @endcode
    ///
    /// @param [in] aPrecision A precision (number of decimal places)
    /// @return A string representation

    virtual String toString(int aPrecision = -1) const override;

    /// @brief Construct a mass from a value in kilograms.
    ///
    /// @code
    ///     Mass mass = Mass::Kilograms(100.0);
    /// @endcode
    ///
    /// @param [in] aValue A value in kilograms
    /// @return A mass

    static Mass Kilograms(double aValue);

    /// @brief Parse a mass from a string.
    ///
    /// @code
    ///     Mass mass = Mass::Parse("1.0 [kg]");
    /// @endcode
    ///
    /// @param [in] aString A string to parse
    /// @return A mass

    static Mass Parse(const String& aString);

    /// @brief Get the string representation of a mass unit.
    ///
    /// @code
    ///     Mass::StringFromUnit(Mass::Unit::Kilogram); // "Kilogram"
    /// @endcode
    ///
    /// @param [in] aUnit A mass unit
    /// @return The string representation

    static String StringFromUnit(const Mass::Unit& aUnit);

    /// @brief Get the symbol of a mass unit.
    ///
    /// @code
    ///     Mass::SymbolFromUnit(Mass::Unit::Kilogram); // "kg"
    /// @endcode
    ///
    /// @param [in] aUnit A mass unit
    /// @return The unit symbol

    static String SymbolFromUnit(const Mass::Unit& aUnit);

   private:
    Mass::Unit unit_;

    static double SIRatio(const Mass::Unit& aUnit);
};

}  // namespace unit
}  // namespace physics
}  // namespace ostk

#endif
