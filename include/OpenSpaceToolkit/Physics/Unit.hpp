/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Unit__
#define __OpenSpaceToolkit_Physics_Unit__

#include <OpenSpaceToolkit/Core/Type/Real.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>
#include <OpenSpaceToolkit/Core/Type/Unique.hpp>

#include <OpenSpaceToolkit/Physics/Unit/Derived.hpp>
#include <OpenSpaceToolkit/Physics/Unit/Derived/Angle.hpp>
#include <OpenSpaceToolkit/Physics/Unit/Length.hpp>
#include <OpenSpaceToolkit/Physics/Unit/Mass.hpp>
#include <OpenSpaceToolkit/Physics/Unit/Time.hpp>
#include <OpenSpaceToolkit/Physics/Unit/Unit.hpp>

namespace ostk
{
namespace physics
{

using ostk::core::type::Real;
using ostk::core::type::String;
using ostk::core::type::Unique;

/// @brief Unit
///
/// A unit of measurement is a definite magnitude of a quantity, defined and adopted by
/// convention or by law, that is used as a standard for measurement of the same kind of
/// quantity. Any other quantity of that kind can be expressed as a multiple of the unit of measurement.
///
/// @ref https://en.wikipedia.org/wiki/Unit_of_measurement
class Unit
{
   public:
    enum class Type
    {

        Undefined,
        None,
        Length,
        Mass,
        Time,
        Temperature,
        ElectricCurrent,
        LuminousIntensity,
        Derived

    };

    /// @brief Deleted default constructor.
    Unit() = delete;

    /// @brief Copy constructor.
    ///
    /// @code
    ///     Unit unit(Unit::Length(unit::Length::Unit::Meter)) ;
    /// @endcode
    ///
    /// @param [in] aUnit A unit to copy

    Unit(const Unit& aUnit);

    /// @brief Copy assignment operator.
    ///
    /// @code
    ///     Unit unit = Unit::Length(unit::Length::Unit::Meter) ;
    /// @endcode
    ///
    /// @param [in] aUnit A unit to copy
    /// @return A reference to this unit

    Unit& operator=(const Unit& aUnit);

    /// @brief Equal to operator.
    ///
    /// @code
    ///     Unit::Length(unit::Length::Unit::Meter) == Unit::Length(unit::Length::Unit::Meter) ; // True
    /// @endcode
    ///
    /// @param [in] aUnit A unit to compare with
    /// @return True if units are equal

    bool operator==(const Unit& aUnit) const;

    /// @brief Not equal to operator.
    ///
    /// @code
    ///     Unit::Length(unit::Length::Unit::Meter) != Unit::None() ; // True
    /// @endcode
    ///
    /// @param [in] aUnit A unit to compare with
    /// @return True if units are not equal

    bool operator!=(const Unit& aUnit) const;

    /// @brief Output stream operator.
    ///
    /// @code
    ///     std::cout << Unit::Length(unit::Length::Unit::Meter) ;
    /// @endcode
    ///
    /// @param [in] anOutputStream An output stream
    /// @param [in] aUnit A unit
    /// @return A reference to the output stream

    friend std::ostream& operator<<(std::ostream& anOutputStream, const Unit& aUnit);

    /// @brief Check if the unit is defined.
    ///
    /// @code
    ///     Unit::Length(unit::Length::Unit::Meter).isDefined() ; // True
    /// @endcode
    ///
    /// @return True if defined

    bool isDefined() const;

    /// @brief Check if the unit is none.
    ///
    /// @code
    ///     Unit::None().isNone() ; // True
    /// @endcode
    ///
    /// @return True if none

    bool isNone() const;

    /// @brief Get the unit type.
    ///
    /// @code
    ///     Unit::Length(unit::Length::Unit::Meter).getType() ; // Unit::Type::Length
    /// @endcode
    ///
    /// @return The unit type

    Unit::Type getType() const;

    /// @brief Get the conversion ratio to another unit.
    ///
    /// @code
    ///     Unit::Length(unit::Length::Unit::Meter).ratioTo(Unit::Length(unit::Length::Unit::Meter)) ; // 1.0
    /// @endcode
    ///
    /// @param [in] aUnit A unit to convert to
    /// @return The conversion ratio

    Real ratioTo(const Unit& aUnit) const;

    /// @brief Convert to string representation.
    ///
    /// @code
    ///     Unit::Length(unit::Length::Unit::Meter).toString() ;
    /// @endcode
    ///
    /// @return A string representation

    String toString() const;

    /// @brief Construct an undefined unit.
    ///
    /// @code
    ///     Unit unit = Unit::Undefined() ;
    /// @endcode
    ///
    /// @return An undefined unit

    static Unit Undefined();

    /// @brief Construct a dimensionless (none) unit.
    ///
    /// @code
    ///     Unit unit = Unit::None() ;
    /// @endcode
    ///
    /// @return A dimensionless unit

    static Unit None();

    /// @brief Construct a length unit.
    ///
    /// @code
    ///     Unit unit = Unit::Length(unit::Length::Unit::Meter) ;
    /// @endcode
    ///
    /// @param [in] aLengthUnit A length unit
    /// @return A unit

    static Unit Length(const unit::Length::Unit& aLengthUnit);

    /// @brief Construct a derived unit.
    ///
    /// @code
    ///     Unit unit = Unit::Derived(unit::Derived::Unit::MeterPerSecond()) ;
    /// @endcode
    ///
    /// @param [in] aDerivedUnit A derived unit
    /// @return A unit

    static Unit Derived(const unit::Derived::Unit& aDerivedUnit);

    /// @brief Get the string representation of a unit type.
    ///
    /// @code
    ///     Unit::StringFromType(Unit::Type::Length) ; // "Length"
    /// @endcode
    ///
    /// @param [in] aType A unit type
    /// @return The string representation

    static String StringFromType(const Unit::Type& aType);

   private:
    Unit::Type type_;
    Unique<unit::Unit> unitUPtr_;

    Unit(const Unit::Type& aType, const Unique<unit::Unit>& aUnitUPtr);
};

}  // namespace physics
}  // namespace ostk

#endif
