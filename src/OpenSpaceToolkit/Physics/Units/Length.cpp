/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Physics/Units/Length.hpp>

namespace ostk
{
namespace physics
{
namespace units
{

Length::Length(const Real& aValue, const Length::Unit& aUnit)
    : units::Unit(units::Unit::Type::Length, aValue),
      unit_(aUnit)
{
}

Length* Length::clone() const
{
    return new Length(*this);
}

bool Length::operator==(const Length& aLength) const
{
    if ((unit_ == Length::Unit::Undefined) || (aLength.unit_ == Length::Unit::Undefined))
    {
        return false;
    }

    return this->accessValue() == ((unit_ == aLength.unit_) ? aLength.accessValue() : aLength.in(unit_));
}

bool Length::operator!=(const Length& aLength) const
{
    return !((*this) == aLength);
}

bool Length::operator<(const Length& aLength) const
{
    if ((unit_ == Length::Unit::Undefined) || (aLength.unit_ == Length::Unit::Undefined))
    {
        throw ostk::core::error::runtime::Undefined("Length");
    }

    return this->accessValue() < ((unit_ == aLength.unit_) ? aLength.accessValue() : aLength.in(unit_));
}

bool Length::operator<=(const Length& aLength) const
{
    if ((unit_ == Length::Unit::Undefined) || (aLength.unit_ == Length::Unit::Undefined))
    {
        throw ostk::core::error::runtime::Undefined("Length");
    }

    return this->accessValue() <= ((unit_ == aLength.unit_) ? aLength.accessValue() : aLength.in(unit_));
}

bool Length::operator>(const Length& aLength) const
{
    if ((unit_ == Length::Unit::Undefined) || (aLength.unit_ == Length::Unit::Undefined))
    {
        throw ostk::core::error::runtime::Undefined("Length");
    }

    return this->accessValue() > ((unit_ == aLength.unit_) ? aLength.accessValue() : aLength.in(unit_));
}

bool Length::operator>=(const Length& aLength) const
{
    if ((unit_ == Length::Unit::Undefined) || (aLength.unit_ == Length::Unit::Undefined))
    {
        throw ostk::core::error::runtime::Undefined("Length");
    }

    return this->accessValue() >= ((unit_ == aLength.unit_) ? aLength.accessValue() : aLength.in(unit_));
}

Length Length::operator+(const Length& aLength) const
{
    if ((unit_ == Length::Unit::Undefined) || (aLength.unit_ == Length::Unit::Undefined))
    {
        throw ostk::core::error::runtime::Undefined("Length");
    }

    return {(this->accessValue() + ((unit_ == aLength.unit_) ? aLength.accessValue() : aLength.in(unit_))), unit_};
}

Length Length::operator-(const Length& aLength) const
{
    if ((unit_ == Length::Unit::Undefined) || (aLength.unit_ == Length::Unit::Undefined))
    {
        throw ostk::core::error::runtime::Undefined("Length");
    }

    return {(this->accessValue() - ((unit_ == aLength.unit_) ? aLength.accessValue() : aLength.in(unit_))), unit_};
}

Length Length::operator*(const Real& aReal) const
{
    if (unit_ == Length::Unit::Undefined)
    {
        throw ostk::core::error::runtime::Undefined("Length");
    }

    if (!aReal.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Real");
    }

    return {(this->accessValue() * aReal), unit_};
}

Length Length::operator/(const Real& aReal) const
{
    if (unit_ == Length::Unit::Undefined)
    {
        throw ostk::core::error::runtime::Undefined("Length");
    }

    if (!aReal.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Real");
    }

    if (aReal.isZero())
    {
        throw ostk::core::error::RuntimeError("Cannot divide by zero.");
    }

    return {(this->accessValue() / aReal), unit_};
}

Length& Length::operator+=(const Length& aLength)
{
    if ((unit_ == Length::Unit::Undefined) || (aLength.unit_ == Length::Unit::Undefined))
    {
        throw ostk::core::error::runtime::Undefined("Length");
    }

    this->accessValue() += ((unit_ == aLength.unit_) ? aLength.accessValue() : aLength.in(unit_));

    return *this;
}

Length& Length::operator-=(const Length& aLength)
{
    if ((unit_ == Length::Unit::Undefined) || (aLength.unit_ == Length::Unit::Undefined))
    {
        throw ostk::core::error::runtime::Undefined("Length");
    }

    this->accessValue() -= ((unit_ == aLength.unit_) ? aLength.accessValue() : aLength.in(unit_));

    return *this;
}

Length& Length::operator*=(const Real& aReal)
{
    if (unit_ == Length::Unit::Undefined)
    {
        throw ostk::core::error::runtime::Undefined("Length");
    }

    if (!aReal.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Real");
    }

    this->accessValue() *= aReal;

    return *this;
}

Length& Length::operator/=(const Real& aReal)
{
    if (unit_ == Length::Unit::Undefined)
    {
        throw ostk::core::error::runtime::Undefined("Length");
    }

    if (!aReal.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Real");
    }

    if (aReal.isZero())
    {
        throw ostk::core::error::RuntimeError("Cannot divide by zero.");
    }

    this->accessValue() /= aReal;

    return *this;
}

Length operator*(const Real& aReal, const Length& aLength)
{
    if (!aReal.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Real");
    }

    if (aLength.unit_ == Length::Unit::Undefined)
    {
        throw ostk::core::error::runtime::Undefined("Length");
    }

    return {(aLength.accessValue() * aReal), aLength.unit_};
}

Length Length::operator+() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Length");
    }

    return Length(this->accessValue(), unit_);
}

Length Length::operator-() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Length");
    }

    return Length(-this->accessValue(), unit_);
}

std::ostream& operator<<(std::ostream& anOutputStream, const Length& aLength)
{
    ostk::core::utils::Print::Header(anOutputStream, "Length");

    ostk::core::utils::Print::Line(anOutputStream) << "Value:" << aLength.accessValue();
    ostk::core::utils::Print::Line(anOutputStream) << "Unit:" << Length::StringFromUnit(aLength.unit_);

    ostk::core::utils::Print::Footer(anOutputStream);

    return anOutputStream;
}

bool Length::isDefined() const
{
    return units::Unit::isDefined() && (unit_ != Length::Unit::Undefined);
}

bool Length::isZero() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Length");
    }

    return this->accessValue() == 0.0;
}

Length::Unit Length::getUnit() const
{
    return unit_;
}

Real Length::in(const Length::Unit& aUnit) const
{
    if (!this->isDefined())
    {
        return Real::Undefined();
    }

    if (unit_ == aUnit)
    {
        return this->accessValue();
    }

    return this->accessValue() * Length::SIRatio(unit_) / Length::SIRatio(aUnit);
}

Real Length::inMeters() const
{
    return this->in(Length::Unit::Meter);
}

Real Length::inKilometers() const
{
    return this->in(Length::Unit::Meter) / 1e3;
}

String Length::toString(const Integer& aPrecision) const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Length");
    }

    return this->accessValue().toString(aPrecision) + " [" + Length::SymbolFromUnit(unit_) + "]";
}

Length Length::Undefined()
{
    return {Real::Undefined(), Length::Unit::Undefined};
}

Length Length::Millimeters(const Real& aValue)
{
    return {aValue / 1e3, Length::Unit::Meter};
}

Length Length::Meters(const Real& aValue)
{
    return {aValue, Length::Unit::Meter};
}

Length Length::Kilometers(const Real& aValue)
{
    return {aValue * 1e3, Length::Unit::Meter};
}

Length Length::Parse(const String& aString)
{
    const auto [value, symbol] = units::Unit::ParseString(aString);

    // Special cases

    if (symbol == "mm")
    {
        return {value / 1000.0, Length::Unit::Meter};
    }

    if (symbol == "km")
    {
        return {value * 1000.0, Length::Unit::Meter};
    }

    return {value, Length::UnitFromSymbol(symbol)};
}

String Length::StringFromUnit(const Length::Unit& aUnit)
{
    switch (aUnit)
    {
        case Length::Unit::Undefined:
            return "Undefined";

        case Length::Unit::Meter:
            return "Meter";

        case Length::Unit::Foot:
            return "Foot";

        case Length::Unit::TerrestrialMile:
            return "Terrestrial Mile";

        case Length::Unit::NauticalMile:
            return "Nautical Mile";

        case Length::Unit::AstronomicalUnit:
            return "Astronomical Unit";

        default:
            throw ostk::core::error::runtime::Wrong("Unit");
            break;
    }

    return String::Empty();
}

String Length::SymbolFromUnit(const Length::Unit& aUnit)
{
    switch (aUnit)
    {
        case Length::Unit::Meter:
            return "m";

        case Length::Unit::Foot:
            return "ft";

        case Length::Unit::TerrestrialMile:
            return "mi";

        case Length::Unit::NauticalMile:
            return "nmi";

        case Length::Unit::AstronomicalUnit:
            return "AU";

        default:
            throw ostk::core::error::runtime::Wrong("Unit");
            break;
    }

    return String::Empty();
}

Length::Unit Length::UnitFromSymbol(const String& aSymbol)
{
    if (aSymbol == "m")
    {
        return Length::Unit::Meter;
    }

    if (aSymbol == "ft")
    {
        return Length::Unit::Foot;
    }

    if (aSymbol == "mi")
    {
        return Length::Unit::TerrestrialMile;
    }

    if (aSymbol == "nmi")
    {
        return Length::Unit::NauticalMile;
    }

    if (aSymbol == "AU")
    {
        return Length::Unit::AstronomicalUnit;
    }

    throw ostk::core::error::runtime::Wrong("Symbol", aSymbol);
}

Real Length::SIRatio(const Length::Unit& aUnit)
{
    switch (aUnit)
    {
        case Length::Unit::Meter:
            return 1.0;

        case Length::Unit::Foot:
            return 0.3048;

        case Length::Unit::TerrestrialMile:
            return 1609.344;

        case Length::Unit::NauticalMile:
            return 1852.0;

        case Length::Unit::AstronomicalUnit:
            return 149597870700.0;

        default:
            throw ostk::core::error::runtime::Wrong("Unit");
            break;
    }

    return Real::Undefined();
}

}  // namespace units
}  // namespace physics
}  // namespace ostk
