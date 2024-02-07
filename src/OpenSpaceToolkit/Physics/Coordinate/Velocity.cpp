/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Velocity.hpp>

namespace ostk
{
namespace physics
{
namespace coord
{

Velocity::Velocity(const Vector3d& aCoordinateSet, const Velocity::Unit& aUnit, const Shared<const Frame>& aFrameSPtr)
    : coordinates_(aCoordinateSet),
      unit_(aUnit),
      frameSPtr_(aFrameSPtr)
{
}

bool Velocity::operator==(const Velocity& aVelocity) const
{
    if ((!this->isDefined()) || (!aVelocity.isDefined()))
    {
        return false;
    }

    return (coordinates_ == aVelocity.coordinates_) && (unit_ == aVelocity.unit_) &&
           ((*frameSPtr_) == (*aVelocity.frameSPtr_));
}

bool Velocity::operator!=(const Velocity& aVelocity) const
{
    return !((*this) == aVelocity);
}

std::ostream& operator<<(std::ostream& anOutputStream, const Velocity& aVelocity)
{
    ostk::core::utils::Print::Header(anOutputStream, "Velocity");

    ostk::core::utils::Print::Line(anOutputStream)
        << "Coordinates:" << (aVelocity.isDefined() ? aVelocity.coordinates_.toString() : "Undefined");
    ostk::core::utils::Print::Line(anOutputStream)
        << "Unit:" << (aVelocity.isDefined() ? Velocity::StringFromUnit(aVelocity.unit_) : "Undefined");
    ostk::core::utils::Print::Line(anOutputStream)
        << "Frame:"
        << (((aVelocity.frameSPtr_ != nullptr) && aVelocity.frameSPtr_->isDefined()) ? aVelocity.frameSPtr_->getName()
                                                                                     : "Undefined");

    ostk::core::utils::Print::Footer(anOutputStream);

    return anOutputStream;
}

bool Velocity::isDefined() const
{
    return coordinates_.isDefined() && (unit_ != Velocity::Unit::Undefined) && (frameSPtr_ != nullptr) &&
           frameSPtr_->isDefined();
}

const Vector3d& Velocity::accessCoordinates() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Velocity");
    }

    return coordinates_;
}

Shared<const Frame> Velocity::accessFrame() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Velocity");
    }

    return frameSPtr_;
}

Vector3d Velocity::getCoordinates() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Velocity");
    }

    return coordinates_;
}

Velocity::Unit Velocity::getUnit() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Velocity");
    }

    return unit_;
}

Velocity Velocity::inUnit(const Velocity::Unit& aUnit) const
{
    if (aUnit == Velocity::Unit::Undefined)
    {
        throw ostk::core::error::runtime::Undefined("Unit");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Velocity");
    }

    const Real conversionFactor =
        Derived(1.0, Velocity::DerivedUnitFromVelocityUnit(unit_)).in(Velocity::DerivedUnitFromVelocityUnit(aUnit));

    return {coordinates_ * conversionFactor, aUnit, frameSPtr_};
}

Velocity Velocity::inFrame(const Position& aPosition, const Shared<const Frame>& aFrameSPtr, const Instant& anInstant)
    const
{
    if ((aFrameSPtr == nullptr) || (!aFrameSPtr->isDefined()))
    {
        throw ostk::core::error::runtime::Undefined("Frame");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Velocity");
    }

    return {
        frameSPtr_->getTransformTo(aFrameSPtr, anInstant)
            .applyToVelocity(aPosition.inFrame(frameSPtr_, anInstant).accessCoordinates(), coordinates_),
        unit_,
        aFrameSPtr
    };
}

String Velocity::toString(const Integer& aPrecision) const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Velocity");
    }

    return String::Format(
        "{} [{}] @ {}",
        (aPrecision.isDefined() ? coordinates_.toString(aPrecision) : coordinates_.toString()),
        Velocity::StringFromUnit(unit_),
        frameSPtr_->getName()
    );
}

Velocity Velocity::Undefined()
{
    return {Vector3d::Undefined(), Velocity::Unit::Undefined, nullptr};
}

Velocity Velocity::MetersPerSecond(const Vector3d& aCoordinateSet, const Shared<const Frame>& aFrameSPtr)
{
    return {aCoordinateSet, Velocity::Unit::MeterPerSecond, aFrameSPtr};
}

String Velocity::StringFromUnit(const Velocity::Unit& aUnit)
{
    switch (aUnit)
    {
        case Velocity::Unit::Undefined:
            return "Undefined";

        case Velocity::Unit::MeterPerSecond:
            return "m/s";

        default:
            throw ostk::core::error::runtime::Wrong("Unit");
            break;
    }

    return String::Empty();
}

Derived::Unit Velocity::DerivedUnitFromVelocityUnit(const Velocity::Unit& aUnit)
{
    using ostk::physics::units::Length;
    using ostk::physics::units::Time;

    switch (aUnit)
    {
        case Velocity::Unit::Undefined:
            return Derived::Unit::Undefined();

        case Velocity::Unit::MeterPerSecond:
            return Derived::Unit::Velocity(Length::Unit::Meter, Time::Unit::Second);

        default:
            throw ostk::core::error::runtime::Wrong("Unit");
            break;
    }

    return Derived::Unit::Undefined();
}

}  // namespace coord
}  // namespace physics
}  // namespace ostk
