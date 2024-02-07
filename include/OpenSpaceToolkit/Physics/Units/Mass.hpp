/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Units_Mass__
#define __OpenSpaceToolkit_Physics_Units_Mass__

#include <OpenSpaceToolkit/Core/Type/Integer.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include <OpenSpaceToolkit/Physics/Units/Unit.hpp>

namespace ostk
{
namespace physics
{
namespace units
{

using ostk::core::type::Integer;
using ostk::core::type::Real;
using ostk::core::type::String;

/// @brief                      Mass
///
/// @ref                        https://en.wikipedia.org/wiki/Mass

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

    /// @brief              Constructor
    ///
    /// @code
    ///                     Mass mass(1.0, Mass::Unit::Kilogram) ;
    /// @endcode
    ///
    /// @param              [in] aValue A value
    /// @param              [in] aUnit A mass unit

    Mass(const Real& aValue, const Mass::Unit& aUnit);

    virtual Mass* clone() const override;

    virtual bool isDefined() const override;

    Mass::Unit getUnit() const;

    Real in(const Mass::Unit& aUnit) const;

    Real inKilograms() const;

    virtual String toString(const Integer& aPrecision = Integer::Undefined()) const override;

    static Mass Undefined();

    static Mass Kilograms(const Real& aValue);

    static Mass Parse(const String& aString);

    static String StringFromUnit(const Mass::Unit& aUnit);

    static String SymbolFromUnit(const Mass::Unit& aUnit);

   private:
    Mass::Unit unit_;

    static Real SIRatio(const Mass::Unit& aUnit);
};

}  // namespace units
}  // namespace physics
}  // namespace ostk

#endif
