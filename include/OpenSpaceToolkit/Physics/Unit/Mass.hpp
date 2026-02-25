/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Unit_Mass__
#define __OpenSpaceToolkit_Physics_Unit_Mass__

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

/// @brief Mass
///
/// @ref https://en.wikipedia.org/wiki/Mass

class Mass : public Unit
{
   public:
    enum class Unit
    {

        Undefined,  ///< Undefined
        Kilogram,   ///< Kilogram (SI)
        Tonne,      ///< Tonne
        Pound       ///< Pound

    };

    /// @brief Constructor
    ///
    /// @code
    ///     Mass mass(1.0, Mass::Unit::Kilogram);
    /// @endcode
    ///
    /// @param [in] aValue A value
    /// @param [in] aUnit A mass unit
    Mass(const Real& aValue, const Mass::Unit& aUnit);

    /// @brief Clone the mass.
    ///
    /// @code
    ///     Mass mass = Mass::Kilograms(1.0);
    ///     Mass* clonePtr = mass.clone();
    /// @endcode
    ///
    /// @return A pointer to a dynamically allocated clone of this mass

    virtual Mass* clone() const override;

    /// @brief Check if the mass is defined.
    ///
    /// @code
    ///     Mass::Kilograms(1.0).isDefined(); // True
    /// @endcode
    ///
    /// @return True if defined

    virtual bool isDefined() const override;

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

    Real in(const Mass::Unit& aUnit) const;

    /// @brief Get the value in kilograms.
    ///
    /// @code
    ///     Mass::Kilograms(1.0).inKilograms(); // 1.0
    /// @endcode
    ///
    /// @return The value in kilograms

    Real inKilograms() const;

    /// @brief Convert to string representation.
    ///
    /// @code
    ///     Mass::Kilograms(1.0).toString();
    /// @endcode
    ///
    /// @param [in] aPrecision A precision (number of decimal places)
    /// @return A string representation

    virtual String toString(const Integer& aPrecision = Integer::Undefined()) const override;

    /// @brief Construct an undefined mass.
    ///
    /// @code
    ///     Mass mass = Mass::Undefined();
    /// @endcode
    ///
    /// @return An undefined mass

    static Mass Undefined();

    /// @brief Construct a mass from a value in kilograms.
    ///
    /// @code
    ///     Mass mass = Mass::Kilograms(100.0);
    /// @endcode
    ///
    /// @param [in] aValue A value in kilograms
    /// @return A mass

    static Mass Kilograms(const Real& aValue);

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

    static Real SIRatio(const Mass::Unit& aUnit);
};

}  // namespace unit
}  // namespace physics
}  // namespace ostk

#endif
