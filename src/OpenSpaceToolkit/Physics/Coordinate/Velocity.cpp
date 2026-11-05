/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Velocity.hpp>

namespace ostk
{
namespace physics
{
namespace coordinate
{
Velocity::Velocity(const Vector3d& aCoordinateSet, const Velocity::Unit& aUnit, const Shared<const Frame>& aFrameSPtr)
    : coordinates_(aCoordinateSet),
      unit_(aUnit),
      frameSPtr_(aFrameSPtr)
{
    if (aFrameSPtr == nullptr)
    {
        throw ostk::core::error::runtime::Undefined("Frame");
    }
}

bool Velocity::operator==(const Velocity& aVelocity) const
{
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

    ostk::core::utils::Print::Line(anOutputStream) << "Coordinates:" << aVelocity.coordinates_.toString();
    ostk::core::utils::Print::Line(anOutputStream) << "Unit:" << Velocity::StringFromUnit(aVelocity.unit_);
    ostk::core::utils::Print::Line(anOutputStream) << "Frame:" << aVelocity.frameSPtr_->getName();

    ostk::core::utils::Print::Footer(anOutputStream);

    return anOutputStream;
}

const Vector3d& Velocity::accessCoordinates() const
{
    return coordinates_;
}

Shared<const Frame> Velocity::accessFrame() const
{
    return frameSPtr_;
}

Vector3d Velocity::getCoordinates() const
{
    return coordinates_;
}

Velocity::Unit Velocity::getUnit() const
{
    return unit_;
}

Velocity Velocity::inUnit(const Velocity::Unit& aUnit) const
{
    const double conversionFactor =
        Derived(1.0, Velocity::DerivedUnitFromVelocityUnit(unit_)).in(Velocity::DerivedUnitFromVelocityUnit(aUnit));

    return {coordinates_ * conversionFactor, aUnit, frameSPtr_};
}

Velocity Velocity::inFrame(const Position& aPosition, const Shared<const Frame>& aFrameSPtr, const Instant& anInstant)
    const
{
    if ((aFrameSPtr == nullptr))
    {
        throw ostk::core::error::runtime::Undefined("Frame");
    }

    return {
        frameSPtr_->getTransformTo(aFrameSPtr, anInstant)
            .applyToVelocity(aPosition.inFrame(frameSPtr_, anInstant).inMeters().accessCoordinates(), coordinates_),
        unit_,
        aFrameSPtr
    };
}

String Velocity::toString(int aPrecision) const
{
    return String::Format(
        "{} [{}] @ {}",
        ((aPrecision >= 0) ? coordinates_.toString(aPrecision) : coordinates_.toString()),
        Velocity::StringFromUnit(unit_),
        frameSPtr_->getName()
    );
}

Velocity Velocity::MetersPerSecond(const Vector3d& aCoordinateSet, const Shared<const Frame>& aFrameSPtr)
{
    return {aCoordinateSet, Velocity::Unit::MeterPerSecond, aFrameSPtr};
}

String Velocity::StringFromUnit(const Velocity::Unit& aUnit)
{
    switch (aUnit)
    {
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
    using ostk::physics::unit::Length;
    using ostk::physics::unit::Time;

    switch (aUnit)
    {
        case Velocity::Unit::MeterPerSecond:
            return Derived::Unit::Velocity(Length::Unit::Meter, Time::Unit::Second);

        default:
            throw ostk::core::error::runtime::Wrong("Unit");
            break;
    }
}
}  // namespace coordinate
}  // namespace physics
}  // namespace ostk
