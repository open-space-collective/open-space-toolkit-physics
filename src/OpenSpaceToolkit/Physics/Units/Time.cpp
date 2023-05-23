/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

#include <OpenSpaceToolkit/Physics/Units/Time.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ostk
{
namespace physics
{
namespace units
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Time::Time(const Real& aValue, const Time::Unit& aUnit)
    : units::Unit(units::Unit::Type::Time, aValue),
      unit_(aUnit)
{
}

Time* Time::clone() const
{
    return new Time(*this);
}

bool Time::isDefined() const
{
    return units::Unit::isDefined() && (unit_ != Time::Unit::Undefined);
}

Time::Unit Time::getUnit() const
{
    return unit_;
}

Real Time::in(const Time::Unit& aUnit) const
{
    if (!this->isDefined())
    {
        return Real::Undefined();
    }

    if (unit_ == aUnit)
    {
        return this->accessValue();
    }

    return this->accessValue() * Time::SIRatio(unit_) / Time::SIRatio(aUnit);
}

Real Time::inSeconds() const
{
    return this->in(Time::Unit::Second);
}

String Time::toString(const Integer& aPrecision) const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Time");
    }

    return this->accessValue().toString(aPrecision) + " [" + Time::SymbolFromUnit(unit_) + "]";
}

Time Time::Undefined()
{
    return {Real::Undefined(), Time::Unit::Undefined};
}

Time Time::Seconds(const Real& aValue)
{
    return {aValue, Time::Unit::Second};
}

// Time                            Time::Parse                                 (   const   String& aString )
// {

// }

String Time::StringFromUnit(const Time::Unit& aUnit)
{
    switch (aUnit)
    {
        case Time::Unit::Undefined:
            return "Undefined";

        case Time::Unit::Nanosecond:
            return "Nanosecond";

        case Time::Unit::Microsecond:
            return "Microsecond";

        case Time::Unit::Millisecond:
            return "Millisecond";

        case Time::Unit::Second:
            return "Second";

        case Time::Unit::Minute:
            return "Minute";

        case Time::Unit::Hour:
            return "Hour";

        case Time::Unit::Day:
            return "Day";

        case Time::Unit::Week:
            return "Week";

        default:
            throw ostk::core::error::runtime::Wrong("Unit");
            break;
    }

    return String::Empty();
}

String Time::SymbolFromUnit(const Time::Unit& aUnit)
{
    switch (aUnit)
    {
        case Time::Unit::Nanosecond:
            return "ns";

        case Time::Unit::Microsecond:
            return "us";

        case Time::Unit::Millisecond:
            return "ms";

        case Time::Unit::Second:
            return "s";

        case Time::Unit::Minute:
            return "min";

        case Time::Unit::Hour:
            return "hr";

        case Time::Unit::Day:
            return "day";

        case Time::Unit::Week:
            return "week";

        default:
            throw ostk::core::error::runtime::Wrong("Unit");
            break;
    }

    return String::Empty();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Real Time::SIRatio(const Time::Unit& aUnit)
{
    switch (aUnit)
    {
        case Time::Unit::Nanosecond:
            return 1e-9;

        case Time::Unit::Microsecond:
            return 1e-6;

        case Time::Unit::Millisecond:
            return 1e-3;

        case Time::Unit::Second:
            return 1.0;

        case Time::Unit::Minute:
            return 60.0;

        case Time::Unit::Hour:
            return 3600.0;

        case Time::Unit::Day:
            return 86400.0;

        case Time::Unit::Week:
            return 604800.0;

        default:
            throw ostk::core::error::runtime::Wrong("Unit");
            break;
    }

    return Real::Undefined();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}  // namespace units
}  // namespace physics
}  // namespace ostk

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
