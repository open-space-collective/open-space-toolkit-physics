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

/// @brief                      Unit
///
/// @ref                        https://en.wikipedia.org/wiki/SI_base_unit
///
/// @note                       Could be (greatly) improved using templating...
/// @note https://benjaminjurke.com/content/articles/2015/compile-time-numerical-unit-dimension-checking/
/// @note                       https://github.com/nholthaus/units
/// @note                       https://www.boost.org/doc/libs/1_67_0/doc/html/boost_units.html

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

    Unit(const Unit::Type& aType, const Real& aValue);

    virtual ~Unit() = 0;

    virtual Unit* clone() const = 0;

    bool operator==(const Unit& aUnit) const;

    bool operator!=(const Unit& aUnit) const;

    virtual bool isDefined() const;

    bool isZero() const;

    const Real& accessValue() const;

    Unit::Type getType() const;

    Real getValue() const;

    virtual String toString(const Integer& aPrecision = Integer::Undefined()) const = 0;

    Real& accessValue();

    void setValue(const Real& aValue);

   protected:
    static Pair<Real, String> ParseString(const String& aString);

   private:
    Unit::Type type_;
    Real value_;
};

}  // namespace unit
}  // namespace physics
}  // namespace ostk

#endif
