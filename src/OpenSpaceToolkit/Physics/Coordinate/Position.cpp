/// Apache License 2.0

#include <boost/stacktrace.hpp>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Position.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Spherical/LLA.hpp>
#include <OpenSpaceToolkit/Physics/Environment.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Object/Celestial.hpp>

namespace ostk
{
namespace physics
{
namespace coordinate
{

Position::Position(const Vector3d& aCoordinateSet, const Position::Unit& aUnit, const Shared<const Frame>& aFrameSPtr)
    : coordinates_(aCoordinateSet),
      unit_(aUnit),
      frameSPtr_(aFrameSPtr)
{
}

Position::Position(const Position& aPosition)
    : coordinates_(aPosition.coordinates_),
      unit_(aPosition.unit_),
      frameSPtr_(aPosition.frameSPtr_)
{
}

Position& Position::operator=(const Position& aPosition)
{
    if (this != &aPosition)
    {
        coordinates_ = aPosition.coordinates_;
        unit_ = aPosition.unit_;
        frameSPtr_ = aPosition.frameSPtr_;
    }

    return *this;
}

bool Position::operator==(const Position& aPosition) const
{
    if ((!this->isDefined()) || (!aPosition.isDefined()))
    {
        return false;
    }

    return (coordinates_ == aPosition.coordinates_) && (unit_ == aPosition.unit_) &&
           ((*frameSPtr_) == (*aPosition.frameSPtr_));
}

bool Position::operator!=(const Position& aPosition) const
{
    return !((*this) == aPosition);
}

std::ostream& operator<<(std::ostream& anOutputStream, const Position& aPosition)
{
    ostk::core::utils::Print::Header(anOutputStream, "Position");

    ostk::core::utils::Print::Line(anOutputStream)
        << "Coordinates:" << (aPosition.coordinates_.isDefined() ? aPosition.coordinates_.toString() : "Undefined");
    ostk::core::utils::Print::Line(anOutputStream)
        << "Unit:"
        << ((aPosition.unit_ != Position::Unit::Undefined) ? Length::StringFromUnit(aPosition.unit_) : "Undefined");
    ostk::core::utils::Print::Line(anOutputStream)
        << "Frame:"
        << (((aPosition.frameSPtr_ != nullptr) && aPosition.frameSPtr_->isDefined()) ? aPosition.frameSPtr_->getName()
                                                                                     : "Undefined");

    ostk::core::utils::Print::Footer(anOutputStream);

    return anOutputStream;
}

bool Position::isDefined() const
{
    return coordinates_.isDefined() && (unit_ != Position::Unit::Undefined) && (frameSPtr_ != nullptr) &&
           frameSPtr_->isDefined();
}

bool Position::isNear(const Position& aPosition, const Length& aTolerance) const
{
    if (!aPosition.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Position");
    }

    if (!aTolerance.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Length");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Position");
    }

    if (frameSPtr_ != aPosition.frameSPtr_)
    {
        throw ostk::core::error::RuntimeError("Position are expressed in different frames.");
    }

    if (unit_ == aPosition.unit_)
    {
        return (coordinates_ - aPosition.coordinates_).norm() <= aTolerance.in(unit_);
    }
    else
    {
        return (coordinates_ - aPosition.inUnit(unit_).coordinates_).norm() <= aTolerance.in(unit_);
    }

    return false;
}

const Vector3d& Position::accessCoordinates() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Position");
    }

    return coordinates_;
}

Shared<const Frame> Position::accessFrame() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Position");
    }

    return frameSPtr_;
}

Vector3d Position::getCoordinates() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Position");
    }

    return coordinates_;
}

Position::Unit Position::getUnit() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Position");
    }

    return unit_;
}

Position Position::inUnit(const Position::Unit& aUnit) const
{
    if (aUnit == Position::Unit::Undefined)
    {
        throw ostk::core::error::runtime::Undefined("Unit");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Position");
    }

    return {coordinates_ * Length(1.0, unit_).in(aUnit), aUnit, frameSPtr_};
}

Position Position::inMeters() const
{
    return this->inUnit(Position::Unit::Meter);
}

Position Position::inFrame(const Shared<const Frame>& aFrameSPtr, const Instant& anInstant) const
{
    if ((aFrameSPtr == nullptr) || (!aFrameSPtr->isDefined()))
    {
        throw ostk::core::error::runtime::Undefined("Frame");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Position");
    }

    return {frameSPtr_->getTransformTo(aFrameSPtr, anInstant).applyToPosition(coordinates_), unit_, aFrameSPtr};
}

String Position::toString(const Integer& aPrecision) const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Position");
    }

    return String::Format(
        "{} [{}] @ {}",
        (aPrecision.isDefined() ? coordinates_.toString(aPrecision) : coordinates_.toString()),
        Length::SymbolFromUnit(unit_),
        frameSPtr_->getName()
    );
}

Position Position::Undefined()
{
    return {Vector3d::Undefined(), Position::Unit::Undefined, nullptr};
}

Position Position::Meters(const Vector3d& aCoordinateSet, const Shared<const Frame>& aFrameSPtr)
{
    return {aCoordinateSet, Position::Unit::Meter, aFrameSPtr};
}

Position Position::FromLLA(
    const spherical::LLA& aLLA, const Shared<const environment::object::Celestial>& aCelestialSPtr
)
{
    if (!aLLA.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("LLA");
    }

    Shared<const environment::object::Celestial> celestialSPtr =
        aCelestialSPtr == nullptr ? ostk::physics::Environment::AccessGlobalInstance()->accessCentralCelestialObject()
                                  : aCelestialSPtr;

    if (celestialSPtr == nullptr || !celestialSPtr->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Celestial");
    }

    return Position::Meters(
        aLLA.toCartesian(celestialSPtr->getEquatorialRadius(), celestialSPtr->getFlattening()),
        celestialSPtr->accessFrame()
    );
}

}  // namespace coordinate
}  // namespace physics
}  // namespace ostk
