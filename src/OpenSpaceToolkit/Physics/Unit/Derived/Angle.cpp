/// Apache License 2.0

#include <cmath>
#include <limits>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Physics/Unit/Derived/Angle.hpp>
#include <OpenSpaceToolkit/Physics/Utility/String.hpp>

namespace ostk
{
namespace physics
{
namespace unit
{
using ostk::physics::utility::DoubleToString;

Angle::Angle(double aValue, const Angle::Unit& aUnit)
    : unit::Unit(unit::Unit::Type::Derived, aValue),
      unit_(aUnit)
{
}

Angle::Angle(const ostk::mathematics::geometry::Angle& anAngle)
    : unit::Unit(unit::Unit::Type::Derived, anAngle.in(anAngle.getUnit())),
      unit_(Angle::Unit::Radian)
{
    switch (anAngle.getUnit())
    {
        case ostk::mathematics::geometry::Angle::Unit::Radian:
            unit_ = Angle::Unit::Radian;
            break;

        case ostk::mathematics::geometry::Angle::Unit::Degree:
            unit_ = Angle::Unit::Degree;
            break;

        case ostk::mathematics::geometry::Angle::Unit::Arcminute:
            unit_ = Angle::Unit::Arcminute;
            break;

        case ostk::mathematics::geometry::Angle::Unit::Arcsecond:
            unit_ = Angle::Unit::Arcsecond;
            break;

        case ostk::mathematics::geometry::Angle::Unit::Revolution:
            unit_ = Angle::Unit::Revolution;
            break;

        default:
            throw ostk::core::error::runtime::Wrong("Unit");
            break;
    }
}

Angle* Angle::clone() const
{
    return new Angle(*this);
}

bool Angle::operator==(const Angle& anAngle) const
{
    switch (unit_)
    {
        case Angle::Unit::Radian:
            return this->getValue() ==
                   Angle::ReduceRange(
                       ((anAngle.unit_ == Angle::Unit::Radian) ? anAngle.getValue() : anAngle.in(Angle::Unit::Radian)),
                       this->getValue(),
                       this->getValue() + 2.0 * M_PI
                   );

        case Angle::Unit::Degree:
            return this->getValue() ==
                   Angle::ReduceRange(
                       ((anAngle.unit_ == Angle::Unit::Degree) ? anAngle.getValue() : anAngle.in(Angle::Unit::Degree)),
                       this->getValue(),
                       this->getValue() + 360.0
                   );

        case Angle::Unit::Arcminute:
            return this->getValue() ==
                   Angle::ReduceRange(
                       ((anAngle.unit_ == Angle::Unit::Arcminute) ? anAngle.getValue()
                                                                  : anAngle.in(Angle::Unit::Arcminute)),
                       this->getValue(),
                       this->getValue() + 21600.0
                   );

        case Angle::Unit::Arcsecond:
            return this->getValue() ==
                   Angle::ReduceRange(
                       ((anAngle.unit_ == Angle::Unit::Arcsecond) ? anAngle.getValue()
                                                                  : anAngle.in(Angle::Unit::Arcsecond)),
                       this->getValue(),
                       this->getValue() + 1296000.0
                   );

        case Angle::Unit::Revolution:
            return this->getValue() ==
                   Angle::ReduceRange(
                       ((anAngle.unit_ == Angle::Unit::Revolution) ? anAngle.getValue()
                                                                   : anAngle.in(Angle::Unit::Revolution)),
                       this->getValue(),
                       this->getValue() + 1.0
                   );

        default:
            throw ostk::core::error::runtime::Wrong("Unit");
            break;
    }

    return false;
}

bool Angle::operator!=(const Angle& anAngle) const
{
    return !((*this) == anAngle);
}

Angle Angle::operator+(const Angle& anAngle) const
{
    return Angle((this->getValue() + ((unit_ == anAngle.unit_) ? anAngle.getValue() : anAngle.in(unit_))), unit_);
}

Angle Angle::operator-(const Angle& anAngle) const
{
    return Angle((this->getValue() - ((unit_ == anAngle.unit_) ? anAngle.getValue() : anAngle.in(unit_))), unit_);
}

Angle Angle::operator*(double aReal) const
{
    if (std::isnan(aReal))
    {
        throw ostk::core::error::runtime::Undefined("Real");
    }

    return Angle((this->getValue() * aReal), unit_);
}

Angle Angle::operator/(double aReal) const
{
    if (std::isnan(aReal))
    {
        throw ostk::core::error::runtime::Undefined("Real");
    }

    if (aReal == 0.0)
    {
        throw ostk::core::error::RuntimeError("Cannot divide by zero.");
    }

    return Angle((this->getValue() / aReal), unit_);
}

Angle& Angle::operator+=(const Angle& anAngle)
{
    this->accessValue() += ((unit_ == anAngle.unit_) ? anAngle.getValue() : anAngle.in(unit_));

    return *this;
}

Angle& Angle::operator-=(const Angle& anAngle)
{
    this->accessValue() -= ((unit_ == anAngle.unit_) ? anAngle.getValue() : anAngle.in(unit_));

    return *this;
}

Angle& Angle::operator*=(double aReal)
{
    if (std::isnan(aReal))
    {
        throw ostk::core::error::runtime::Undefined("Real");
    }

    this->accessValue() *= aReal;

    return *this;
}

Angle& Angle::operator/=(double aReal)
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

Angle operator*(double aReal, const Angle& anAngle)
{
    if (std::isnan(aReal))
    {
        throw ostk::core::error::runtime::Undefined("Real");
    }

    return Angle((anAngle.getValue() * aReal), anAngle.unit_);
}

Angle Angle::operator+() const
{
    return Angle(this->getValue(), unit_);
}

Angle Angle::operator-() const
{
    return Angle(-this->getValue(), unit_);
}

Angle::operator ostk::mathematics::geometry::Angle() const
{
    switch (unit_)
    {
        case Angle::Unit::Radian:
            return ostk::mathematics::geometry::Angle(
                this->getValue(), ostk::mathematics::geometry::Angle::Unit::Radian
            );

        case Angle::Unit::Degree:
            return ostk::mathematics::geometry::Angle(
                this->getValue(), ostk::mathematics::geometry::Angle::Unit::Degree
            );

        case Angle::Unit::Arcminute:
            return ostk::mathematics::geometry::Angle(
                this->getValue(), ostk::mathematics::geometry::Angle::Unit::Arcminute
            );

        case Angle::Unit::Arcsecond:
            return ostk::mathematics::geometry::Angle(
                this->getValue(), ostk::mathematics::geometry::Angle::Unit::Arcsecond
            );

        case Angle::Unit::Revolution:
            return ostk::mathematics::geometry::Angle(
                this->getValue(), ostk::mathematics::geometry::Angle::Unit::Revolution
            );

        default:
            throw ostk::core::error::runtime::Wrong("Unit");
            break;
    }

    return ostk::mathematics::geometry::Angle::Undefined();
}

std::ostream& operator<<(std::ostream& anOutputStream, const Angle& anAngle)
{
    ostk::core::utils::Print::Header(anOutputStream, "Angle");

    ostk::core::utils::Print::Line(anOutputStream) << "Value:" << anAngle.getValue();
    ostk::core::utils::Print::Line(anOutputStream) << "Unit:" << Angle::StringFromUnit(anAngle.unit_);

    ostk::core::utils::Print::Footer(anOutputStream);

    return anOutputStream;
}

bool Angle::isZero() const
{
    return this->getValue() == 0.0;
}

Angle::Unit Angle::getUnit() const
{
    return unit_;
}

double Angle::in(const Angle::Unit& aUnit) const
{
    if (unit_ == aUnit)
    {
        return this->getValue();
    }

    return this->getValue() * Angle::SIRatio(unit_) / Angle::SIRatio(aUnit);
}

double Angle::inRadians() const
{
    return this->in(Angle::Unit::Radian);
}

double Angle::inRadians(double aLowerBound, double anUpperBound) const
{
    if (std::isnan(aLowerBound))
    {
        throw ostk::core::error::runtime::Undefined("Lower bound");
    }

    if (std::isnan(anUpperBound))
    {
        throw ostk::core::error::runtime::Undefined("Upper bound");
    }

    if ((anUpperBound - aLowerBound) != 2.0 * M_PI)
    {
        throw ostk::core::error::runtime::Undefined("Range span is not [2π].");
    }

    return Angle::ReduceRange(this->in(Angle::Unit::Radian), aLowerBound, anUpperBound);
}

double Angle::inDegrees() const
{
    return this->in(Angle::Unit::Degree);
}

double Angle::inDegrees(double aLowerBound, double anUpperBound) const
{
    if (std::isnan(aLowerBound))
    {
        throw ostk::core::error::runtime::Undefined("Lower bound");
    }

    if (std::isnan(anUpperBound))
    {
        throw ostk::core::error::runtime::Undefined("Upper bound");
    }

    if ((anUpperBound - aLowerBound) != 360.0)
    {
        throw ostk::core::error::runtime::Undefined("Range span is not [360].");
    }

    return Angle::ReduceRange(this->in(Angle::Unit::Degree), aLowerBound, anUpperBound);
}

double Angle::inArcminutes() const
{
    return this->in(Angle::Unit::Arcminute);
}

double Angle::inArcminutes(double aLowerBound, double anUpperBound) const
{
    if (std::isnan(aLowerBound))
    {
        throw ostk::core::error::runtime::Undefined("Lower bound");
    }

    if (std::isnan(anUpperBound))
    {
        throw ostk::core::error::runtime::Undefined("Upper bound");
    }

    if ((anUpperBound - aLowerBound) != 21600.0)
    {
        throw ostk::core::error::runtime::Undefined("Range span is not [21600].");
    }

    return Angle::ReduceRange(this->in(Angle::Unit::Arcminute), aLowerBound, anUpperBound);
}

double Angle::inArcseconds() const
{
    return this->in(Angle::Unit::Arcsecond);
}

double Angle::inArcseconds(double aLowerBound, double anUpperBound) const
{
    if (std::isnan(aLowerBound))
    {
        throw ostk::core::error::runtime::Undefined("Lower bound");
    }

    if (std::isnan(anUpperBound))
    {
        throw ostk::core::error::runtime::Undefined("Upper bound");
    }

    if ((anUpperBound - aLowerBound) != 1296000.0)
    {
        throw ostk::core::error::runtime::Undefined("Range span is not [1296000].");
    }

    return Angle::ReduceRange(this->in(Angle::Unit::Arcsecond), aLowerBound, anUpperBound);
}

double Angle::inRevolutions() const
{
    return this->in(Angle::Unit::Revolution);
}

String Angle::toString(int aPrecision) const
{
    return DoubleToString(this->getValue(), aPrecision) + " [" + Angle::SymbolFromUnit(unit_) + "]";
}

Angle Angle::Zero()
{
    return {0.0, Angle::Unit::Radian};
}

Angle Angle::HalfPi()
{
    return {M_PI / 2.0, Angle::Unit::Radian};
}

Angle Angle::Pi()
{
    return {M_PI, Angle::Unit::Radian};
}

Angle Angle::TwoPi()
{
    return {M_PI * 2.0, Angle::Unit::Radian};
}

Angle Angle::Radians(double aValue)
{
    return Angle(aValue, Angle::Unit::Radian);
}

Angle Angle::Degrees(double aValue)
{
    return Angle(aValue, Angle::Unit::Degree);
}

Angle Angle::Arcminutes(double aValue)
{
    return Angle(aValue, Angle::Unit::Arcminute);
}

Angle Angle::Arcseconds(double aValue)
{
    return Angle(aValue, Angle::Unit::Arcsecond);
}

Angle Angle::Revolutions(double aValue)
{
    return Angle(aValue, Angle::Unit::Revolution);
}

Angle Angle::Between(const Angle& aFirstAngle, const Angle& aSecondAngle)
{
    const double firstRadians = aFirstAngle.inRadians();
    const double secondRadians = aSecondAngle.inRadians();

    const double delta = std::atan2(std::sin(secondRadians - firstRadians), std::cos(secondRadians - firstRadians));

    return Angle(delta * Angle::SIRatio(Angle::Unit::Radian) / Angle::SIRatio(aFirstAngle.unit_), aFirstAngle.unit_);
}

Angle Angle::Between(const Vector2d& aFirstVector, const Vector2d& aSecondVector)
{
    if ((!aFirstVector.isDefined()) || (!aSecondVector.isDefined()))
    {
        throw ostk::core::error::runtime::Undefined("Vector");
    }

    if ((aFirstVector.squaredNorm() < 1e-15) || (aSecondVector.squaredNorm() < 1e-15))
    {
        throw ostk::core::error::RuntimeError("Vector norm is too small.");
    }

    if (aFirstVector == aSecondVector)
    {
        return Angle::Zero();
    }

    if (aFirstVector == -aSecondVector)
    {
        return Angle::Pi();
    }

    const double dotProduct = aFirstVector.normalized().dot(aSecondVector.normalized());

    if (dotProduct >= 1.0)
    {
        return Angle::Zero();
    }

    if (dotProduct <= -1.0)
    {
        return Angle::Pi();
    }

    return Angle::Radians(std::acos(dotProduct));
}

Angle Angle::Between(const Vector3d& aFirstVector, const Vector3d& aSecondVector)
{
    if ((!aFirstVector.isDefined()) || (!aSecondVector.isDefined()))
    {
        throw ostk::core::error::runtime::Undefined("Vector");
    }

    if ((aFirstVector.squaredNorm() < 1e-15) || (aSecondVector.squaredNorm() < 1e-15))
    {
        throw ostk::core::error::RuntimeError("Vector norm is too small.");
    }

    if (aFirstVector == aSecondVector)
    {
        return Angle::Zero();
    }

    if (aFirstVector == -aSecondVector)
    {
        return Angle::Pi();
    }

    const double dotProduct = aFirstVector.normalized().dot(aSecondVector.normalized());

    if (dotProduct >= 1.0)
    {
        return Angle::Zero();
    }

    if (dotProduct <= -1.0)
    {
        return Angle::Pi();
    }

    return Angle::Radians(std::acos(dotProduct));
}

Angle Angle::Parse(const String& aString)
{
    const auto [value, symbol] = unit::Unit::ParseString(aString);

    return {value, Angle::UnitFromSymbol(symbol)};
}

String Angle::StringFromUnit(const Angle::Unit& aUnit)
{
    switch (aUnit)
    {
        case Angle::Unit::Radian:
            return "Radian";

        case Angle::Unit::Degree:
            return "Degree";

        case Angle::Unit::Arcminute:
            return "Arcminute";

        case Angle::Unit::Arcsecond:
            return "Arcsecond";

        case Angle::Unit::Revolution:
            return "Revolution";

        default:
            break;
    }

    throw ostk::core::error::runtime::Wrong("Unit");

    return String::Empty();
}

String Angle::SymbolFromUnit(const Angle::Unit& aUnit)
{
    switch (aUnit)
    {
        case Angle::Unit::Radian:
            return "rad";

        case Angle::Unit::Degree:
            return "deg";

        case Angle::Unit::Arcminute:
            return "amin";

        case Angle::Unit::Arcsecond:
            return "asec";

        case Angle::Unit::Revolution:
            return "rev";

        default:
            throw ostk::core::error::runtime::Wrong("Unit");
            break;
    }
}

Angle::Unit Angle::UnitFromSymbol(const String& aSymbol)
{
    if (aSymbol == "rad")
    {
        return Angle::Unit::Radian;
    }

    if (aSymbol == "deg")
    {
        return Angle::Unit::Degree;
    }

    if (aSymbol == "amin")
    {
        return Angle::Unit::Arcminute;
    }

    if (aSymbol == "asec")
    {
        return Angle::Unit::Arcsecond;
    }

    if (aSymbol == "rev")
    {
        return Angle::Unit::Revolution;
    }

    throw ostk::core::error::runtime::Wrong("Symbol", aSymbol);
}

double Angle::SIRatio(const Angle::Unit& aUnit)
{
    switch (aUnit)
    {
        case Angle::Unit::Radian:
            return 1.0;

        case Angle::Unit::Degree:
            return M_PI / 180.0;

        case Angle::Unit::Arcminute:
            return M_PI / 10800.0;

        case Angle::Unit::Arcsecond:
            return M_PI / 648000.0;

        case Angle::Unit::Revolution:
            return 2.0 * M_PI;

        default:
            break;
    }

    throw ostk::core::error::runtime::Wrong("Unit");

    return std::numeric_limits<double>::quiet_NaN();
}

double Angle::ReduceRange(double aValue, double aRangeLowerBound, double aRangeUpperBound)
{
    if ((aValue >= aRangeLowerBound) && (aValue < aRangeUpperBound))  // Value already in range
    {
        return aValue;
    }

    if (aRangeLowerBound >= aRangeUpperBound)
    {
        throw ostk::core::error::RuntimeError(
            "Lower bound [{}] greater than or equal to upper bound [{}].", aRangeLowerBound, aRangeUpperBound
        );
    }

    double value = aValue;

    const double range = aRangeUpperBound - aRangeLowerBound;

    while (value < aRangeLowerBound
    )  // [TBM] This is a STUPID implementation: just used as a logic placeholder... should be improved ASAP
    {
        value += range;
    }

    while (value >= aRangeUpperBound
    )  // [TBM] This is a STUPID implementation: just used as a logic placeholder... should be improved ASAP
    {
        value -= range;
    }

    return value;
}
}  // namespace unit
}  // namespace physics
}  // namespace ostk
