/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Unit_Time__
#define __OpenSpaceToolkit_Physics_Unit_Time__

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

/// @brief Time
///
/// @ref https://en.wikipedia.org/wiki/Unit_of_time

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

    /// @brief Constructor
    ///
    /// @code
    ///     Time time(1.0, Time::Unit::Second);
    /// @endcode
    ///
    /// @param [in] aValue A value
    /// @param [in] aUnit A time unit
    Time(const Real& aValue, const Time::Unit& aUnit);

    /// @brief Clone the time unit.
    ///
    /// @code
    ///     Time time = Time::Seconds(1.0);
    ///     Time* clonePtr = time.clone();
    /// @endcode
    ///
    /// @return A pointer to a dynamically allocated clone of this time unit

    virtual Time* clone() const override;

    /// @brief Check if the time unit is defined.
    ///
    /// @code
    ///     Time::Seconds(1.0).isDefined(); // True
    /// @endcode
    ///
    /// @return True if defined

    virtual bool isDefined() const override;

    /// @brief Get the time unit.
    ///
    /// @code
    ///     Time::Seconds(1.0).getUnit(); // Time::Unit::Second
    /// @endcode
    ///
    /// @return The time unit

    Time::Unit getUnit() const;

    /// @brief Get the value in the specified unit.
    ///
    /// @code
    ///     Time::Seconds(60.0).in(Time::Unit::Minute); // 1.0
    /// @endcode
    ///
    /// @param [in] aUnit A time unit
    /// @return The value in the specified unit

    Real in(const Time::Unit& aUnit) const;

    /// @brief Get the value in seconds.
    ///
    /// @code
    ///     Time::Seconds(1.0).inSeconds(); // 1.0
    /// @endcode
    ///
    /// @return The value in seconds

    Real inSeconds() const;

    /// @brief Convert to string representation.
    ///
    /// @code
    ///     Time::Seconds(1.0).toString();
    /// @endcode
    ///
    /// @param [in] aPrecision A precision (number of decimal places)
    /// @return A string representation

    virtual String toString(const Integer& aPrecision = Integer::Undefined()) const override;

    /// @brief Construct an undefined time unit.
    ///
    /// @code
    ///     Time time = Time::Undefined();
    /// @endcode
    ///
    /// @return An undefined time unit

    static Time Undefined();

    /// @brief Construct a time unit from a value in seconds.
    ///
    /// @code
    ///     Time time = Time::Seconds(1.0);
    /// @endcode
    ///
    /// @param [in] aValue A value in seconds
    /// @return A time unit

    static Time Seconds(const Real& aValue);

    /// @brief Get the string representation of a time unit.
    ///
    /// @code
    ///     Time::StringFromUnit(Time::Unit::Second); // "Second"
    /// @endcode
    ///
    /// @param [in] aUnit A time unit
    /// @return The string representation

    static String StringFromUnit(const Time::Unit& aUnit);

    /// @brief Get the symbol of a time unit.
    ///
    /// @code
    ///     Time::SymbolFromUnit(Time::Unit::Second); // "s"
    /// @endcode
    ///
    /// @param [in] aUnit A time unit
    /// @return The unit symbol

    static String SymbolFromUnit(const Time::Unit& aUnit);

   private:
    Time::Unit unit_;

    static Real SIRatio(const Time::Unit& aUnit);
};

}  // namespace unit
}  // namespace physics
}  // namespace ostk

#endif
