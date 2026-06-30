/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Unit_ElectricCurrent__
#define __OpenSpaceToolkit_Physics_Unit_ElectricCurrent__

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

/// @brief Electric current
///
/// @ref https://en.wikipedia.org/wiki/Electric_current

class ElectricCurrent : public Unit
{
   public:
    enum class Unit
    {

        Undefined,  ///< Undefined
        Ampere      ///< Ampere (SI)

    };

    /// @brief Constructor
    ///
    /// @code
    ///     ElectricCurrent electricCurrent { 1.0, ElectricCurrent::Unit::Ampere };
    /// @endcode
    ///
    /// @param [in] aValue A value
    /// @param [in] aUnit An electric current unit

    ElectricCurrent(const Real& aValue, const ElectricCurrent::Unit& aUnit);

    /// @brief Clone the electric current.
    ///
    /// @code
    ///     ElectricCurrent current = ElectricCurrent::Amperes(1.0);
    ///     ElectricCurrent* clonePtr = current.clone();
    /// @endcode
    ///
    /// @return A pointer to a dynamically allocated clone of this electric current

    virtual ElectricCurrent* clone() const override;

    /// @brief Check if the electric current is defined.
    ///
    /// @code
    ///     ElectricCurrent::Amperes(1.0).isDefined(); // True
    /// @endcode
    ///
    /// @return True if defined

    virtual bool isDefined() const override;

    /// @brief Get the electric current unit.
    ///
    /// @code
    ///     ElectricCurrent::Amperes(1.0).getUnit(); // ElectricCurrent::Unit::Ampere
    /// @endcode
    ///
    /// @return The electric current unit

    ElectricCurrent::Unit getUnit() const;

    /// @brief Get the value in the specified unit.
    ///
    /// @code
    ///     ElectricCurrent::Amperes(1.0).in(ElectricCurrent::Unit::Ampere); // 1.0
    /// @endcode
    ///
    /// @param [in] aUnit An electric current unit
    /// @return The value in the specified unit

    Real in(const ElectricCurrent::Unit& aUnit) const;

    /// @brief Get the value in amperes.
    ///
    /// @code
    ///     ElectricCurrent::Amperes(1.0).inAmperes(); // 1.0
    /// @endcode
    ///
    /// @return The value in amperes

    Real inAmperes() const;

    /// @brief Convert to string representation.
    ///
    /// @code
    ///     ElectricCurrent::Amperes(1.0).toString();
    /// @endcode
    ///
    /// @param [in] aPrecision A precision (number of decimal places)
    /// @return A string representation

    virtual String toString(const Integer& aPrecision = Integer::Undefined()) const override;

    /// @brief Construct an undefined electric current.
    ///
    /// @code
    ///     ElectricCurrent current = ElectricCurrent::Undefined();
    /// @endcode
    ///
    /// @return An undefined electric current

    static ElectricCurrent Undefined();

    /// @brief Construct an electric current from a value in amperes.
    ///
    /// @code
    ///     ElectricCurrent current = ElectricCurrent::Amperes(1.0);
    /// @endcode
    ///
    /// @param [in] aValue A value in amperes
    /// @return An electric current

    static ElectricCurrent Amperes(const Real& aValue);

    /// @brief Parse an electric current from a string.
    ///
    /// @code
    ///     ElectricCurrent current = ElectricCurrent::Parse("1.0 [A]");
    /// @endcode
    ///
    /// @param [in] aString A string to parse
    /// @return An electric current

    static ElectricCurrent Parse(const String& aString);

    /// @brief Get the string representation of an electric current unit.
    ///
    /// @code
    ///     ElectricCurrent::StringFromUnit(ElectricCurrent::Unit::Ampere); // "Ampere"
    /// @endcode
    ///
    /// @param [in] aUnit An electric current unit
    /// @return The string representation

    static String StringFromUnit(const ElectricCurrent::Unit& aUnit);

    /// @brief Get the symbol of an electric current unit.
    ///
    /// @code
    ///     ElectricCurrent::SymbolFromUnit(ElectricCurrent::Unit::Ampere); // "A"
    /// @endcode
    ///
    /// @param [in] aUnit An electric current unit
    /// @return The unit symbol

    static String SymbolFromUnit(const ElectricCurrent::Unit& aUnit);

   private:
    ElectricCurrent::Unit unit_;

    static Real SIRatio(const ElectricCurrent::Unit& aUnit);
};

}  // namespace unit
}  // namespace physics
}  // namespace ostk

#endif
