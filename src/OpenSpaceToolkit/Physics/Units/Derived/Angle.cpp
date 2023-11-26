/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

#include <OpenSpaceToolkit/Physics/Units/Derived/Angle.hpp>

namespace ostk
{
namespace physics
{
namespace units
{

Angle::Angle(const Real& aValue, const Angle::Unit& aUnit)
    : units::Unit(units::Unit::Type::Derived, aValue),
      unit_(aUnit)
{
}

Angle::Angle(const ostk::math::geometry::Angle& anAngle)
    : units::Unit(units::Unit::Type::Derived, anAngle.in(anAngle.getUnit())),
      unit_(Angle::Unit::Undefined)
{
    switch (anAngle.getUnit())
    {
        case ostk::math::geometry::Angle::Unit::Radian:
            unit_ = Angle::Unit::Radian;
            break;

        case ostk::math::geometry::Angle::Unit::Degree:
            unit_ = Angle::Unit::Degree;
            break;

        case ostk::math::geometry::Angle::Unit::Arcminute:
            unit_ = Angle::Unit::Arcminute;
            break;

        case ostk::math::geometry::Angle::Unit::Arcsecond:
            unit_ = Angle::Unit::Arcsecond;
            break;

        case ostk::math::geometry::Angle::Unit::Revolution:
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
    if ((unit_ == Angle::Unit::Undefined) || (anAngle.unit_ == Angle::Unit::Undefined))
    {
        return false;
    }

    switch (unit_)
    {
        case Angle::Unit::Radian:
            return this->accessValue() ==
                   Angle::ReduceRange(
                       ((anAngle.unit_ == Angle::Unit::Radian) ? anAngle.accessValue() : anAngle.in(Angle::Unit::Radian)
                       ),
                       this->accessValue(),
                       this->accessValue() + Real::TwoPi()
                   );

        case Angle::Unit::Degree:
            return this->accessValue() ==
                   Angle::ReduceRange(
                       ((anAngle.unit_ == Angle::Unit::Degree) ? anAngle.accessValue() : anAngle.in(Angle::Unit::Degree)
                       ),
                       this->accessValue(),
                       this->accessValue() + 360.0
                   );

        case Angle::Unit::Arcminute:
            return this->accessValue() ==
                   Angle::ReduceRange(
                       ((anAngle.unit_ == Angle::Unit::Arcminute) ? anAngle.accessValue()
                                                                  : anAngle.in(Angle::Unit::Arcminute)),
                       this->accessValue(),
                       this->accessValue() + 21600.0
                   );

        case Angle::Unit::Arcsecond:
            return this->accessValue() ==
                   Angle::ReduceRange(
                       ((anAngle.unit_ == Angle::Unit::Arcsecond) ? anAngle.accessValue()
                                                                  : anAngle.in(Angle::Unit::Arcsecond)),
                       this->accessValue(),
                       this->accessValue() + 1296000.0
                   );

        case Angle::Unit::Revolution:
            return this->accessValue() ==
                   Angle::ReduceRange(
                       ((anAngle.unit_ == Angle::Unit::Revolution) ? anAngle.accessValue()
                                                                   : anAngle.in(Angle::Unit::Revolution)),
                       this->accessValue(),
                       this->accessValue() + 1.0
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
    if ((unit_ == Angle::Unit::Undefined) || (anAngle.unit_ == Angle::Unit::Undefined))
    {
        throw ostk::core::error::runtime::Undefined("Angle");
    }

    return Angle((this->accessValue() + ((unit_ == anAngle.unit_) ? anAngle.accessValue() : anAngle.in(unit_))), unit_);
}

Angle Angle::operator-(const Angle& anAngle) const
{
    if ((unit_ == Angle::Unit::Undefined) || (anAngle.unit_ == Angle::Unit::Undefined))
    {
        throw ostk::core::error::runtime::Undefined("Angle");
    }

    return Angle((this->accessValue() - ((unit_ == anAngle.unit_) ? anAngle.accessValue() : anAngle.in(unit_))), unit_);
}

Angle Angle::operator*(const Real& aReal) const
{
    if (unit_ == Angle::Unit::Undefined)
    {
        throw ostk::core::error::runtime::Undefined("Angle");
    }

    if (!aReal.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Real");
    }

    return Angle((this->accessValue() * aReal), unit_);
}

Angle Angle::operator/(const Real& aReal) const
{
    if (unit_ == Angle::Unit::Undefined)
    {
        throw ostk::core::error::runtime::Undefined("Angle");
    }

    if (!aReal.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Real");
    }

    if (aReal.isZero())
    {
        throw ostk::core::error::RuntimeError("Cannot divide by zero.");
    }

    return Angle((this->accessValue() / aReal), unit_);
}

Angle& Angle::operator+=(const Angle& anAngle)
{
    if ((unit_ == Angle::Unit::Undefined) || (anAngle.unit_ == Angle::Unit::Undefined))
    {
        throw ostk::core::error::runtime::Undefined("Angle");
    }

    this->accessValue() += ((unit_ == anAngle.unit_) ? anAngle.accessValue() : anAngle.in(unit_));

    return *this;
}

Angle& Angle::operator-=(const Angle& anAngle)
{
    if ((unit_ == Angle::Unit::Undefined) || (anAngle.unit_ == Angle::Unit::Undefined))
    {
        throw ostk::core::error::runtime::Undefined("Angle");
    }

    this->accessValue() -= ((unit_ == anAngle.unit_) ? anAngle.accessValue() : anAngle.in(unit_));

    return *this;
}

Angle& Angle::operator*=(const Real& aReal)
{
    if (unit_ == Angle::Unit::Undefined)
    {
        throw ostk::core::error::runtime::Undefined("Angle");
    }

    if (!aReal.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Real");
    }

    this->accessValue() *= aReal;

    return *this;
}

Angle& Angle::operator/=(const Real& aReal)
{
    if (unit_ == Angle::Unit::Undefined)
    {
        throw ostk::core::error::runtime::Undefined("Angle");
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

Angle operator*(const Real& aReal, const Angle& anAngle)
{
    if (!aReal.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Real");
    }

    if (anAngle.unit_ == Angle::Unit::Undefined)
    {
        throw ostk::core::error::runtime::Undefined("Angle");
    }

    return Angle((anAngle.accessValue() * aReal), anAngle.unit_);
}

Angle Angle::operator+() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Angle");
    }

    return Angle(this->accessValue(), unit_);
}

Angle Angle::operator-() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Angle");
    }

    return Angle(-this->accessValue(), unit_);
}

Angle::operator ostk::math::geometry::Angle() const
{
    if (!this->isDefined())
    {
        return ostk::math::geometry::Angle::Undefined();
    }

    switch (unit_)
    {
        case Angle::Unit::Radian:
            return ostk::math::geometry::Angle(this->accessValue(), ostk::math::geometry::Angle::Unit::Radian);

        case Angle::Unit::Degree:
            return ostk::math::geometry::Angle(this->accessValue(), ostk::math::geometry::Angle::Unit::Degree);

        case Angle::Unit::Arcminute:
            return ostk::math::geometry::Angle(this->accessValue(), ostk::math::geometry::Angle::Unit::Arcminute);

        case Angle::Unit::Arcsecond:
            return ostk::math::geometry::Angle(this->accessValue(), ostk::math::geometry::Angle::Unit::Arcsecond);

        case Angle::Unit::Revolution:
            return ostk::math::geometry::Angle(this->accessValue(), ostk::math::geometry::Angle::Unit::Revolution);

        default:
            throw ostk::core::error::runtime::Wrong("Unit");
            break;
    }

    return ostk::math::geometry::Angle::Undefined();
}

std::ostream& operator<<(std::ostream& anOutputStream, const Angle& anAngle)
{
    ostk::core::utils::Print::Header(anOutputStream, "Angle");

    ostk::core::utils::Print::Line(anOutputStream) << "Value:" << anAngle.accessValue();
    ostk::core::utils::Print::Line(anOutputStream) << "Unit:" << Angle::StringFromUnit(anAngle.unit_);

    ostk::core::utils::Print::Footer(anOutputStream);

    return anOutputStream;
}

bool Angle::isDefined() const
{
    return units::Unit::isDefined() && (unit_ != Angle::Unit::Undefined);
}

bool Angle::isZero() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Angle");
    }

    return this->accessValue() == 0.0;
}

Angle::Unit Angle::getUnit() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Angle");
    }

    return unit_;
}

Real Angle::in(const Angle::Unit& aUnit) const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Angle");
    }

    if (unit_ == aUnit)
    {
        return this->accessValue();
    }

    return this->accessValue() * Angle::SIRatio(unit_) / Angle::SIRatio(aUnit);
}

Real Angle::inRadians() const
{
    return this->in(Angle::Unit::Radian);
}

Real Angle::inRadians(const Real& aLowerBound, const Real& anUpperBound) const
{
    if (!aLowerBound.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Lower bound");
    }

    if (!anUpperBound.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Upper bound");
    }

    if ((anUpperBound - aLowerBound) != Real::TwoPi())
    {
        throw ostk::core::error::runtime::Undefined("Range span is not [2π].");
    }

    return Angle::ReduceRange(this->in(Angle::Unit::Radian), aLowerBound, anUpperBound);
}

Real Angle::inDegrees() const
{
    return this->in(Angle::Unit::Degree);
}

Real Angle::inDegrees(const Real& aLowerBound, const Real& anUpperBound) const
{
    if (!aLowerBound.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Lower bound");
    }

    if (!anUpperBound.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Upper bound");
    }

    if ((anUpperBound - aLowerBound) != 360.0)
    {
        throw ostk::core::error::runtime::Undefined("Range span is not [360].");
    }

    return Angle::ReduceRange(this->in(Angle::Unit::Degree), aLowerBound, anUpperBound);
}

Real Angle::inArcminutes() const
{
    return this->in(Angle::Unit::Arcminute);
}

Real Angle::inArcminutes(const Real& aLowerBound, const Real& anUpperBound) const
{
    if (!aLowerBound.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Lower bound");
    }

    if (!anUpperBound.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Upper bound");
    }

    if ((anUpperBound - aLowerBound) != 21600.0)
    {
        throw ostk::core::error::runtime::Undefined("Range span is not [21600].");
    }

    return Angle::ReduceRange(this->in(Angle::Unit::Arcminute), aLowerBound, anUpperBound);
}

Real Angle::inArcseconds() const
{
    return this->in(Angle::Unit::Arcsecond);
}

Real Angle::inArcseconds(const Real& aLowerBound, const Real& anUpperBound) const
{
    if (!aLowerBound.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Lower bound");
    }

    if (!anUpperBound.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Upper bound");
    }

    if ((anUpperBound - aLowerBound) != 1296000.0)
    {
        throw ostk::core::error::runtime::Undefined("Range span is not [1296000].");
    }

    return Angle::ReduceRange(this->in(Angle::Unit::Arcsecond), aLowerBound, anUpperBound);
}

Real Angle::inRevolutions() const
{
    return this->in(Angle::Unit::Revolution);
}

String Angle::toString(const Integer& aPrecision) const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Angle");
    }

    return this->accessValue().toString(aPrecision) + " [" + Angle::SymbolFromUnit(unit_) + "]";
}

Angle Angle::Undefined()
{
    return Angle(Real::Undefined(), Angle::Unit::Undefined);
}

Angle Angle::Zero()
{
    return {Real::Zero(), Angle::Unit::Radian};
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

Angle Angle::Radians(const Real& aValue)
{
    return Angle(aValue, Angle::Unit::Radian);
}

Angle Angle::Degrees(const Real& aValue)
{
    return Angle(aValue, Angle::Unit::Degree);
}

Angle Angle::Arcminutes(const Real& aValue)
{
    return Angle(aValue, Angle::Unit::Arcminute);
}

Angle Angle::Arcseconds(const Real& aValue)
{
    return Angle(aValue, Angle::Unit::Arcsecond);
}

Angle Angle::Revolutions(const Real& aValue)
{
    return Angle(aValue, Angle::Unit::Revolution);
}

Angle Angle::Between(const Vector2d& aFirstVector, const Vector2d& aSecondVector)
{
    if ((!aFirstVector.isDefined()) || (!aSecondVector.isDefined()))
    {
        throw ostk::core::error::runtime::Undefined("Vector");
    }

    if ((aFirstVector.squaredNorm() < Real::Epsilon()) || (aSecondVector.squaredNorm() < Real::Epsilon()))
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

    const Real dotProduct = aFirstVector.normalized().dot(aSecondVector.normalized());

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

    if ((aFirstVector.squaredNorm() < Real::Epsilon()) || (aSecondVector.squaredNorm() < Real::Epsilon()))
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

    const Real dotProduct = aFirstVector.normalized().dot(aSecondVector.normalized());

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
    const auto [value, symbol] = units::Unit::ParseString(aString);

    return {value, Angle::UnitFromSymbol(symbol)};
}

String Angle::StringFromUnit(const Angle::Unit& aUnit)
{
    switch (aUnit)
    {
        case Angle::Unit::Undefined:
            return "Undefined";

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

Real Angle::SIRatio(const Angle::Unit& aUnit)
{
    switch (aUnit)
    {
        case Angle::Unit::Radian:
            return 1.0;

        case Angle::Unit::Degree:
            return Real::Pi() / 180.0;

        case Angle::Unit::Arcminute:
            return Real::Pi() / 10800.0;

        case Angle::Unit::Arcsecond:
            return Real::Pi() / 648000.0;

        case Angle::Unit::Revolution:
            return Real::TwoPi();

        default:
            break;
    }

    throw ostk::core::error::runtime::Wrong("Unit");

    return Real::Undefined();
}

Real Angle::ReduceRange(const Real& aValue, const Real& aRangeLowerBound, const Real& aRangeUpperBound)
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

    Real value = aValue;

    const Real range = aRangeUpperBound - aRangeLowerBound;

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

}  // namespace units
}  // namespace physics
}  // namespace ostk
