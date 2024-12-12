/// Apache License 2.0

#include <boost/regex.hpp>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Physics/Time/Interval.hpp>

namespace ostk
{
namespace physics
{
namespace time
{

Interval::Interval(const Instant& aLowerBound, const Instant& anUpperBound, const Interval::Type& anIntervalType)
    : mathematics::object::Interval<Instant>(aLowerBound, anUpperBound, anIntervalType)
{
}

std::ostream& operator<<(std::ostream& anOutputStream, const Interval& anInterval)
{
    ostk::core::utils::Print::Header(anOutputStream, "Interval");

    ostk::core::utils::Print::Line(anOutputStream)
        << "Start:" << (anInterval.isDefined() ? anInterval.accessStart().toString(Scale::UTC) : "Undefined");
    ostk::core::utils::Print::Line(anOutputStream)
        << "End:" << (anInterval.isDefined() ? anInterval.accessEnd().toString(Scale::UTC) : "Undefined");

    ostk::core::utils::Print::Footer(anOutputStream);

    return anOutputStream;
}

bool Interval::isDefined() const
{
    return mathematics::object::Interval<Instant>::isDefined() && (this->getType() != Interval::Type::Undefined);
}

const Instant& Interval::accessStart() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Interval");
    }

    return this->accessLowerBound();
}

const Instant& Interval::accessEnd() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Interval");
    }

    return this->accessUpperBound();
}

Instant Interval::getStart() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Interval");
    }

    return this->accessLowerBound();
}

Instant Interval::getEnd() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Interval");
    }

    return this->accessUpperBound();
}

Duration Interval::getDuration() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Interval");
    }

    return Duration::Between(this->accessLowerBound(), this->accessUpperBound());
}

Instant Interval::getCenter() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Interval");
    }

    return this->accessLowerBound() + this->getDuration() / 2.0;
}

Interval Interval::getIntersectionWith(const Interval& anInterval) const
{
    return Interval::FromBase(Interval::ToBase(*this).getIntersectionWith(Interval::ToBase(anInterval)));
}

Interval Interval::getUnionWith(const Interval& anInterval) const
{
    return Interval::FromBase(Interval::ToBase(*this).getUnionWith(Interval::ToBase(anInterval)));
}

String Interval::toString(const Scale& aTimeScale) const
{
    using ostk::physics::time::DateTime;

    if (!this->isDefined())
    {
        return String("Undefined");
    }

    switch (this->getType())
    {
        case Interval::Type::Closed:
            return String::Format(
                "[{0} - {1}] [{2}]",
                this->accessLowerBound().getDateTime(aTimeScale).toString(DateTime::Format::Standard),
                this->accessUpperBound().getDateTime(aTimeScale).toString(DateTime::Format::Standard),
                StringFromScale(aTimeScale)
            );

        case Interval::Type::Open:
            return String::Format(
                "]{0} - {1}[ [{2}]",
                this->accessLowerBound().getDateTime(aTimeScale).toString(DateTime::Format::Standard),
                this->accessUpperBound().getDateTime(aTimeScale).toString(DateTime::Format::Standard),
                StringFromScale(aTimeScale)
            );

        case Interval::Type::HalfOpenLeft:
            return String::Format(
                "]{0} - {1}] [{2}]",
                this->accessLowerBound().getDateTime(aTimeScale).toString(DateTime::Format::Standard),
                this->accessUpperBound().getDateTime(aTimeScale).toString(DateTime::Format::Standard),
                StringFromScale(aTimeScale)
            );

        case Interval::Type::HalfOpenRight:
            return String::Format(
                "[{0} - {1}[ [{2}]",
                this->accessLowerBound().getDateTime(aTimeScale).toString(DateTime::Format::Standard),
                this->accessUpperBound().getDateTime(aTimeScale).toString(DateTime::Format::Standard),
                StringFromScale(aTimeScale)
            );

        default:
            break;
    }

    throw ostk::core::error::runtime::Wrong("Interval type");

    return String::Empty();
}

Array<Instant> Interval::generateGrid(const Duration& aTimeStep) const
{
    return this->generateArrayWithStep(aTimeStep);
}

Interval Interval::Undefined()
{
    return Interval(Instant::Undefined(), Instant::Undefined(), Interval::Type::Undefined);
}

Interval Interval::Closed(const Instant& aLowerBound, const Instant& anUpperBound)
{
    if (!aLowerBound.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Lower bound");
    }

    if (!anUpperBound.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Upper bound");
    }

    return Interval(aLowerBound, anUpperBound, Interval::Type::Closed);
}

Interval Interval::Open(const Instant& aLowerBound, const Instant& anUpperBound)
{
    if (!aLowerBound.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Lower bound");
    }

    if (!anUpperBound.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Upper bound");
    }

    return Interval(aLowerBound, anUpperBound, Interval::Type::Open);
}

Interval Interval::HalfOpenLeft(const Instant& aLowerBound, const Instant& anUpperBound)
{
    if (!aLowerBound.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Lower bound");
    }

    if (!anUpperBound.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Upper bound");
    }

    return Interval(aLowerBound, anUpperBound, Interval::Type::HalfOpenLeft);
}

Interval Interval::HalfOpenRight(const Instant& aLowerBound, const Instant& anUpperBound)
{
    if (!aLowerBound.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Lower bound");
    }

    if (!anUpperBound.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Upper bound");
    }

    return Interval(aLowerBound, anUpperBound, Interval::Type::HalfOpenRight);
}

Interval Interval::Centered(
    const Instant& aCentralInstant, const Duration& aDuration, const Interval::Type& anIntervalType
)
{
    if (!aCentralInstant.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Central instant");
    }

    if (!aDuration.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Duration");
    }

    if (!aDuration.isPositive())
    {
        throw ostk::core::error::RuntimeError("Duration is negative.");
    }

    if (anIntervalType == Interval::Type::Undefined)
    {
        throw ostk::core::error::runtime::Undefined("Interval type");
    }

    return Interval((aCentralInstant - aDuration / 2.0), (aCentralInstant + aDuration / 2.0), anIntervalType);
}

Array<Interval> Interval::Clip(const Array<Interval>& anIntervalArray, const Interval& anInterval)
{
    const auto& baseClip = mathematics::object::Interval<Instant>::Clip(ToBaseArray(anIntervalArray), anInterval);
    return FromBaseArray(baseClip);
}

Array<Interval> Interval::Sort(const Array<Interval>& anIntervalArray, const bool& byLowerBound, const bool& ascending)
{
    const auto& baseSort =
        mathematics::object::Interval<Instant>::Sort(ToBaseArray(anIntervalArray), byLowerBound, ascending);
    return FromBaseArray(baseSort);
}

Array<Interval> Interval::Merge(const Array<Interval>& anIntervalArray)
{
    const auto& baseMerge = mathematics::object::Interval<Instant>::Merge(ToBaseArray(anIntervalArray));
    return FromBaseArray(baseMerge);
}

Array<Interval> Interval::GetGaps(const Array<Interval>& anIntervalArray, const Interval& anInterval)
{
    const auto& baseGetGaps = mathematics::object::Interval<Instant>::GetGaps(ToBaseArray(anIntervalArray), anInterval);
    return FromBaseArray(baseGetGaps);
}

Array<Interval> Interval::LogicalOr(const Array<Interval>& anIntervalArray, const Array<Interval>& anotherIntervalArray)
{
    const auto& baseLogicalOr = mathematics::object::Interval<Instant>::LogicalOr(
        ToBaseArray(anIntervalArray), ToBaseArray(anotherIntervalArray)
    );
    return FromBaseArray(baseLogicalOr);
}

Array<Interval> Interval::LogicalAnd(
    const Array<Interval>& anIntervalArray, const Array<Interval>& anotherIntervalArray
)
{
    const auto& baseLogicalAnd = mathematics::object::Interval<Instant>::LogicalAnd(
        ToBaseArray(anIntervalArray), ToBaseArray(anotherIntervalArray)
    );
    return FromBaseArray(baseLogicalAnd);
}

Interval Interval::Parse(const String& aString)
{
    using ostk::physics::time::DateTime;

    if (aString.isEmpty())
    {
        throw ostk::core::error::runtime::Undefined("String");
    }

    boost::smatch match;

    if (boost::regex_match(
            aString,
            match,
            boost::regex(
                "(\\[|\\])(\\d{4}-\\d{2}-\\d{2} \\d{2}:\\d{2}:\\d{2}(?:\\.\\d{3}\\.\\d{3}\\.\\d{3})?) - "
                "(\\d{4}-\\d{2}-\\d{2} \\d{2}:\\d{2}:\\d{2}(?:\\.\\d{3}\\.\\d{3}\\.\\d{3})?)(\\[|\\]) \\[([A-Z]+)\\]"
            )
        ))
    {
        const String openingBracket = String(match[1]);
        const String startInstantString = String(match[2]);
        const String endInstantString = String(match[3]);
        const String closingBracket = String(match[4]);
        const String timeScaleString = String(match[5]);

        const Scale timeScale = ScaleFromString(timeScaleString);

        const Instant startInstant =
            Instant::DateTime(DateTime::Parse(startInstantString, DateTime::Format::Undefined), timeScale);
        const Instant endInstant =
            Instant::DateTime(DateTime::Parse(endInstantString, DateTime::Format::Undefined), timeScale);

        Interval::Type type = Interval::Type::Undefined;

        if ((openingBracket == "[") && (closingBracket == "]"))
        {
            type = Interval::Type::Closed;
        }
        else if ((openingBracket == "]") && (closingBracket == "["))
        {
            type = Interval::Type::Open;
        }
        else if ((openingBracket == "]") && (closingBracket == "]"))
        {
            type = Interval::Type::HalfOpenLeft;
        }
        else if ((openingBracket == "[") && (closingBracket == "["))
        {
            type = Interval::Type::HalfOpenRight;
        }
        else
        {
            throw ostk::core::error::runtime::Wrong("Brackets");
        }

        return Interval(startInstant, endInstant, type);
    }
    else
    {
        throw ostk::core::error::RuntimeError("Cannot parse interval string [{}].", aString);
    }

    return Interval::Undefined();
}

mathematics::object::Interval<Instant> Interval::ToBase(const Interval& derived)
{
    return reinterpret_cast<const mathematics::object::Interval<Instant>&>(derived);
}

Interval Interval::FromBase(const mathematics::object::Interval<Instant>& base)
{
    return reinterpret_cast<const Interval&>(base);
}

Array<mathematics::object::Interval<Instant>> Interval::ToBaseArray(const Array<Interval>& derivedArray)
{
    return reinterpret_cast<const Array<mathematics::object::Interval<Instant>>&>(derivedArray);
}

Array<Interval> Interval::FromBaseArray(const Array<mathematics::object::Interval<Instant>>& baseArray)
{
    return reinterpret_cast<const Array<Interval>&>(baseArray);
}

}  // namespace time
}  // namespace physics
}  // namespace ostk
