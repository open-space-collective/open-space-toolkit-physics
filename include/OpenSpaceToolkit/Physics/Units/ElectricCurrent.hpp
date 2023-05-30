/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Units_ElectricCurrent__
#define __OpenSpaceToolkit_Physics_Units_ElectricCurrent__

#include <OpenSpaceToolkit/Core/Types/Integer.hpp>
#include <OpenSpaceToolkit/Core/Types/Real.hpp>
#include <OpenSpaceToolkit/Core/Types/String.hpp>

#include <OpenSpaceToolkit/Physics/Units/Unit.hpp>

namespace ostk
{
namespace physics
{
namespace units
{

using ostk::core::types::Integer;
using ostk::core::types::Real;
using ostk::core::types::String;

/// @brief                      Electric current
///
/// @ref                        https://en.wikipedia.org/wiki/Electric_current

class ElectricCurrent : public Unit
{
   public:
    enum class Unit
    {

        Undefined,  ///< Undefined
        Ampere      ///< Ampere (SI)

    };

    /// @brief              Constructor
    ///
    /// @code
    ///                     ElectricCurrent electricCurrent { 1.0, ElectricCurrent::Unit::Ampere } ;
    /// @endcode
    ///
    /// @param              [in] aValue A value
    /// @param              [in] aUnit An electric current unit

    ElectricCurrent(const Real& aValue, const ElectricCurrent::Unit& aUnit);

    virtual ElectricCurrent* clone() const override;

    virtual bool isDefined() const override;

    ElectricCurrent::Unit getUnit() const;

    Real in(const ElectricCurrent::Unit& aUnit) const;

    Real inAmperes() const;

    virtual String toString(const Integer& aPrecision = Integer::Undefined()) const override;

    static ElectricCurrent Undefined();

    static ElectricCurrent Amperes(const Real& aValue);

    static ElectricCurrent Parse(const String& aString);

    static String StringFromUnit(const ElectricCurrent::Unit& aUnit);

    static String SymbolFromUnit(const ElectricCurrent::Unit& aUnit);

   private:
    ElectricCurrent::Unit unit_;

    static Real SIRatio(const ElectricCurrent::Unit& aUnit);
};

}  // namespace units
}  // namespace physics
}  // namespace ostk

#endif
