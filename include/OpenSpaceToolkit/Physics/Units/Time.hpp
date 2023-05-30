/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Units_Time__
#define __OpenSpaceToolkit_Physics_Units_Time__

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

/// @brief                      Time
///
/// @ref                        https://en.wikipedia.org/wiki/Unit_of_time

class Time : public Unit
{
   public:
    enum class Unit
    {

        Undefined,    ///< Undefined
        Nanosecond,   ///< Nanosecond
        Microsecond,  ///< Microsecond
        Millisecond,  ///< Millisecond
        Second,       ///< Second (SI)
        Minute,       ///< Minute
        Hour,         ///< Hour
        Day,          ///< Day
        Week          ///< Week

    };

    /// @brief              Constructor
    ///
    /// @code
    ///                     Time time(1.0, Time::Unit::Second) ;
    /// @endcode
    ///
    /// @param              [in] aValue A value
    /// @param              [in] aUnit A time unit

    Time(const Real& aValue, const Time::Unit& aUnit);

    virtual Time* clone() const override;

    virtual bool isDefined() const override;

    Time::Unit getUnit() const;

    Real in(const Time::Unit& aUnit) const;

    Real inSeconds() const;

    virtual String toString(const Integer& aPrecision = Integer::Undefined()) const override;

    static Time Undefined();

    static Time Seconds(const Real& aValue);

    static String StringFromUnit(const Time::Unit& aUnit);

    static String SymbolFromUnit(const Time::Unit& aUnit);

   private:
    Time::Unit unit_;

    static Real SIRatio(const Time::Unit& aUnit);
};

}  // namespace units
}  // namespace physics
}  // namespace ostk

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
