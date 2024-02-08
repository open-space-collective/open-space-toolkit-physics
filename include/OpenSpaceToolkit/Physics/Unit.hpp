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

using ostk::core::type::Unique;
using ostk::core::type::Real;
using ostk::core::type::String;

/// @brief                      Unit
///
///                             A unit of measurement is a definite magnitude of a quantity, defined and adopted by
///                             convention or by law, that is used as a standard for measurement of the same kind of
///                             quantity. Any other quantity of that kind can be expressed as a multiple of the unit of
///                             measurement.
///
/// @ref                        https://en.wikipedia.org/wiki/Unit_of_measurement

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

    Unit() = delete;

    Unit(const Unit& aUnit);

    Unit& operator=(const Unit& aUnit);

    bool operator==(const Unit& aUnit) const;

    bool operator!=(const Unit& aUnit) const;

    friend std::ostream& operator<<(std::ostream& anOutputStream, const Unit& aUnit);

    bool isDefined() const;

    bool isNone() const;

    Unit::Type getType() const;

    Real ratioTo(const Unit& aUnit) const;

    String toString() const;

    static Unit Undefined();

    static Unit None();

    static Unit Length(const unit::Length::Unit& aLengthUnit);

    static Unit Derived(const unit::Derived::Unit& aDerivedUnit);

    static String StringFromType(const Unit::Type& aType);

   private:
    Unit::Type type_;
    Unique<unit::Unit> unitUPtr_;

    Unit(const Unit::Type& aType, const Unique<unit::Unit>& aUnitUPtr);
};

}  // namespace physics
}  // namespace ostk

#endif
