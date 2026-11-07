/// Apache License 2.0

#include <limits>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Physics/Unit/Time.hpp>
#include <OpenSpaceToolkit/Physics/Utility/String.hpp>

namespace ostk
{
namespace physics
{
namespace unit
{
using ostk::physics::utility::DoubleToString;

Time::Time(double aValue, const Time::Unit& aUnit)
    : unit::Unit(unit::Unit::Type::Time, aValue),
      unit_(aUnit)
{
}

Time* Time::clone() const
{
    return new Time(*this);
}

Time::Unit Time::getUnit() const
{
    return unit_;
}

double Time::in(const Time::Unit& aUnit) const
{
    if (unit_ == aUnit)
    {
        return this->getValue();
    }

    return this->getValue() * Time::SIRatio(unit_) / Time::SIRatio(aUnit);
}

double Time::inSeconds() const
{
    return this->in(Time::Unit::Second);
}

String Time::toString(int aPrecision) const
{
    return DoubleToString(this->getValue(), aPrecision) + " [" + Time::SymbolFromUnit(unit_) + "]";
}

Time Time::Seconds(double aValue)
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

double Time::SIRatio(const Time::Unit& aUnit)
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
}
}  // namespace unit
}  // namespace physics
}  // namespace ostk
