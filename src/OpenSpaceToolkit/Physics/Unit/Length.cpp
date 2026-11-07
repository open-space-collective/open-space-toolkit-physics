/// Apache License 2.0

#include <cmath>
#include <limits>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Physics/Unit/Length.hpp>
#include <OpenSpaceToolkit/Physics/Utility/String.hpp>

namespace ostk
{
namespace physics
{
namespace unit
{

using ostk::physics::utility::DoubleToString;

Length::Length(double aValue, const Length::Unit& aUnit)
    : unit::Unit(unit::Unit::Type::Length, aValue),
      unit_(aUnit)
{
}

Length* Length::clone() const
{
    return new Length(*this);
}

bool Length::operator==(const Length& aLength) const
{
    return this->getValue() == ((unit_ == aLength.unit_) ? aLength.getValue() : aLength.in(unit_));
}

bool Length::operator!=(const Length& aLength) const
{
    return !((*this) == aLength);
}

bool Length::operator<(const Length& aLength) const
{
    return this->getValue() < ((unit_ == aLength.unit_) ? aLength.getValue() : aLength.in(unit_));
}

bool Length::operator<=(const Length& aLength) const
{
    return this->getValue() <= ((unit_ == aLength.unit_) ? aLength.getValue() : aLength.in(unit_));
}

bool Length::operator>(const Length& aLength) const
{
    return this->getValue() > ((unit_ == aLength.unit_) ? aLength.getValue() : aLength.in(unit_));
}

bool Length::operator>=(const Length& aLength) const
{
    return this->getValue() >= ((unit_ == aLength.unit_) ? aLength.getValue() : aLength.in(unit_));
}

Length Length::operator+(const Length& aLength) const
{
    return {(this->getValue() + ((unit_ == aLength.unit_) ? aLength.getValue() : aLength.in(unit_))), unit_};
}

Length Length::operator-(const Length& aLength) const
{
    return {(this->getValue() - ((unit_ == aLength.unit_) ? aLength.getValue() : aLength.in(unit_))), unit_};
}

Length Length::operator*(double aReal) const
{
    if (std::isnan(aReal))
    {
        throw ostk::core::error::runtime::Undefined("Real");
    }

    return {(this->getValue() * aReal), unit_};
}

Length Length::operator/(double aReal) const
{
    if (std::isnan(aReal))
    {
        throw ostk::core::error::runtime::Undefined("Real");
    }

    if (aReal == 0.0)
    {
        throw ostk::core::error::RuntimeError("Cannot divide by zero.");
    }

    return {(this->getValue() / aReal), unit_};
}

Length& Length::operator+=(const Length& aLength)
{
    this->accessValue() += ((unit_ == aLength.unit_) ? aLength.getValue() : aLength.in(unit_));

    return *this;
}

Length& Length::operator-=(const Length& aLength)
{
    this->accessValue() -= ((unit_ == aLength.unit_) ? aLength.getValue() : aLength.in(unit_));

    return *this;
}

Length& Length::operator*=(double aReal)
{
    if (std::isnan(aReal))
    {
        throw ostk::core::error::runtime::Undefined("Real");
    }

    this->accessValue() *= aReal;

    return *this;
}

Length& Length::operator/=(double aReal)
{
    if (std::isnan(aReal))
    {
        throw ostk::core::error::runtime::Undefined("Real");
    }

    if (aReal == 0.0)
    {
        throw ostk::core::error::RuntimeError("Cannot divide by zero.");
    }

    this->accessValue() /= aReal;

    return *this;
}

Length operator*(double aReal, const Length& aLength)
{
    if (std::isnan(aReal))
    {
        throw ostk::core::error::runtime::Undefined("Real");
    }

    return {(aLength.getValue() * aReal), aLength.unit_};
}

Length Length::operator+() const
{
    return Length(this->getValue(), unit_);
}

Length Length::operator-() const
{
    return Length(-this->getValue(), unit_);
}

std::ostream& operator<<(std::ostream& anOutputStream, const Length& aLength)
{
    ostk::core::utils::Print::Header(anOutputStream, "Length");

    ostk::core::utils::Print::Line(anOutputStream) << "Value:" << aLength.getValue();
    ostk::core::utils::Print::Line(anOutputStream) << "Unit:" << Length::StringFromUnit(aLength.unit_);

    ostk::core::utils::Print::Footer(anOutputStream);

    return anOutputStream;
}

bool Length::isZero() const
{
    return this->getValue() == 0.0;
}

Length::Unit Length::getUnit() const
{
    return unit_;
}

double Length::in(const Length::Unit& aUnit) const
{
    if (unit_ == aUnit)
    {
        return this->getValue();
    }

    return this->getValue() * Length::SIRatio(unit_) / Length::SIRatio(aUnit);
}

double Length::inMeters() const
{
    return this->in(Length::Unit::Meter);
}

double Length::inKilometers() const
{
    return this->in(Length::Unit::Meter) / 1e3;
}

String Length::toString(int aPrecision) const
{
    return DoubleToString(this->getValue(), aPrecision) + " [" + Length::SymbolFromUnit(unit_) + "]";
}

Length Length::Millimeters(double aValue)
{
    return {aValue / 1e3, Length::Unit::Meter};
}

Length Length::Meters(double aValue)
{
    return {aValue, Length::Unit::Meter};
}

Length Length::Kilometers(double aValue)
{
    return {aValue * 1e3, Length::Unit::Meter};
}

Length Length::Parse(const String& aString)
{
    const auto [value, symbol] = unit::Unit::ParseString(aString);

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

double Length::SIRatio(const Length::Unit& aUnit)
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
}

}  // namespace unit
}  // namespace physics
}  // namespace ostk
