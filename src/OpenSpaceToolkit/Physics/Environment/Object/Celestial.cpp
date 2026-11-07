/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/Static.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Utility.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Object/Celestial.hpp>
#include <OpenSpaceToolkit/Physics/Unit.hpp>

namespace ostk
{
namespace physics
{
namespace environment
{
namespace object
{
Celestial::Celestial(
    const String& aName,
    const Celestial::Type& aType,
    const std::optional<Derived>& aGravitationalParameter,
    const Length& anEquatorialRadius,
    double aFlattening,
    const std::optional<double>& aJ2,
    const std::optional<double>& aJ4,
    const Shared<Ephemeris>& anEphemeris,
    const Shared<GravitationalModel>& aGravitationalModel,
    const Shared<MagneticModel>& aMagneticModel,
    const Shared<AtmosphericModel>& anAtmosphericModel
)
    : Object(aName),
      type_(aType),
      gravitationalParameter_(aGravitationalParameter),
      equatorialRadius_(anEquatorialRadius),
      flattening_(aFlattening),
      j2_(aJ2),
      j4_(aJ4),
      ephemeris_(anEphemeris),
      gravitationalModelSPtr_(aGravitationalModel),
      magneticModelSPtr_(aMagneticModel),
      atmosphericModelSPtr_(anAtmosphericModel)
{
    if (ephemeris_ == nullptr)
    {
        throw ostk::core::error::runtime::Undefined("Ephemeris");
    }
}

Celestial::Celestial(
    const String& aName,
    const Celestial::Type& aType,
    const std::optional<Derived>& aGravitationalParameter,
    const Length& anEquatorialRadius,
    double aFlattening,
    const std::optional<double>& aJ2,
    const std::optional<double>& aJ4,
    const Shared<Ephemeris>& anEphemeris,
    const Shared<GravitationalModel>& aGravitationalModel,
    const Shared<MagneticModel>& aMagneticModel,
    const Shared<AtmosphericModel>& anAtmosphericModel,
    const Object::Geometry& aGeometry
)
    : Object(aName, aGeometry),
      type_(aType),
      gravitationalParameter_(aGravitationalParameter),
      equatorialRadius_(anEquatorialRadius),
      flattening_(aFlattening),
      j2_(aJ2),
      j4_(aJ4),
      ephemeris_(anEphemeris),
      gravitationalModelSPtr_(aGravitationalModel),
      magneticModelSPtr_(aMagneticModel),
      atmosphericModelSPtr_(anAtmosphericModel)
{
    if (ephemeris_ == nullptr)
    {
        throw ostk::core::error::runtime::Undefined("Ephemeris");
    }
}

Celestial::~Celestial() {}

Celestial* Celestial::clone() const
{
    return new Celestial(*this);
}

bool Celestial::gravitationalModelIsDefined() const
{
    return gravitationalModelSPtr_ != nullptr;
}

bool Celestial::magneticModelIsDefined() const
{
    return magneticModelSPtr_ != nullptr;
}

bool Celestial::atmosphericModelIsDefined() const
{
    return atmosphericModelSPtr_ != nullptr;
}

const Shared<const Ephemeris>& Celestial::getEphemeris() const
{
    return ephemeris_;
}

const Shared<const GravitationalModel>& Celestial::getGravitationalModel() const
{
    return gravitationalModelSPtr_;
}

const Shared<const MagneticModel>& Celestial::getMagneticModel() const
{
    return magneticModelSPtr_;
}

const Shared<const AtmosphericModel>& Celestial::getAtmosphericModel() const
{
    return atmosphericModelSPtr_;
}

Shared<const Frame> Celestial::getFrame() const
{
    return ephemeris_->getFrame();
}

Celestial::Type Celestial::getType() const
{
    return type_;
}

const Derived& Celestial::getGravitationalParameter() const
{
    if (!gravitationalParameter_.has_value())
    {
        throw ostk::core::error::runtime::Undefined("Gravitational parameter");
    }

    return gravitationalParameter_.value();
}

const Length& Celestial::getEquatorialRadius() const
{
    return equatorialRadius_;
}

double Celestial::getFlattening() const
{
    return flattening_;
}

double Celestial::getJ2() const
{
    if (!j2_.has_value())
    {
        throw ostk::core::error::runtime::Undefined("J2");
    }

    return j2_.value();
}

double Celestial::getJ4() const
{
    if (!j4_.has_value())
    {
        throw ostk::core::error::runtime::Undefined("J4");
    }

    return j4_.value();
}

Position Celestial::getPositionIn(const Shared<const Frame>& aFrameSPtr, const Instant& anInstant) const
{
    if ((aFrameSPtr == nullptr))
    {
        throw ostk::core::error::runtime::Undefined("Frame");
    }

    return ephemeris_->getFrame()->getOriginIn(aFrameSPtr, anInstant);
}

Velocity Celestial::getVelocityIn(const Shared<const Frame>& aFrameSPtr, const Instant& anInstant) const
{
    return Velocity::MetersPerSecond(
        this->getTransformTo(aFrameSPtr, anInstant).applyToVelocity(Vector3d::Zero(), Vector3d::Zero()), aFrameSPtr
    );
}

Transform Celestial::getTransformTo(const Shared<const Frame>& aFrameSPtr, const Instant& anInstant) const
{
    if ((aFrameSPtr == nullptr))
    {
        throw ostk::core::error::runtime::Undefined("Frame");
    }

    return ephemeris_->getFrame()->getTransformTo(aFrameSPtr, anInstant);
}

Axes Celestial::getAxesIn(const Shared<const Frame>& aFrameSPtr, const Instant& anInstant) const
{
    if ((aFrameSPtr == nullptr))
    {
        throw ostk::core::error::runtime::Undefined("Frame");
    }

    return ephemeris_->getFrame()->getAxesIn(aFrameSPtr, anInstant);
}

Vector Celestial::getGravitationalFieldAt(const Position& aPosition, const Instant& anInstant) const
{
    using ostk::physics::Unit;
    using ostk::physics::unit::Time;

    if (gravitationalModelSPtr_ == nullptr)
    {
        throw ostk::core::error::runtime::Undefined("Gravitational model");
    }

    const Vector3d positionInBodyFrame = aPosition.inFrame(ephemeris_->getFrame(), anInstant).getCoordinates();

    const Vector3d gravitationalFieldValue = gravitationalModelSPtr_->getFieldValueAt(positionInBodyFrame, anInstant);

    const static Unit gravitationalFieldUnit =
        Unit::Derived(Derived::Unit::Acceleration(Length::Unit::Meter, Time::Unit::Second));

    return {gravitationalFieldValue, gravitationalFieldUnit, ephemeris_->getFrame()};
}

Vector Celestial::getMagneticFieldAt(const Position& aPosition, const Instant& anInstant) const
{
    using ostk::physics::Unit;
    using ostk::physics::unit::Time;

    if (magneticModelSPtr_ == nullptr)
    {
        throw ostk::core::error::runtime::Undefined("Magnetic model");
    }

    const Vector3d positionInBodyFrame = aPosition.inFrame(ephemeris_->getFrame(), anInstant).getCoordinates();

    const Vector3d magneticFieldValue = magneticModelSPtr_->getFieldValueAt(positionInBodyFrame, anInstant);

    const static Unit magneticFieldUnit = Unit::Derived(Derived::Unit::Tesla());

    return {magneticFieldValue, magneticFieldUnit, ephemeris_->getFrame()};
}

Scalar Celestial::getAtmosphericDensityAt(const Position& aPosition, const Instant& anInstant) const
{
    using ostk::physics::Unit;
    using ostk::physics::unit::Time;

    if (atmosphericModelSPtr_ == nullptr)
    {
        throw ostk::core::error::runtime::Undefined("Atmospheric model");
    }

    const double atmosphericDensityValue = atmosphericModelSPtr_->getDensityAt(aPosition, anInstant);

    const static Unit atmosphericDensityUnit =
        Unit::Derived(Derived::Unit::MassDensity(Mass::Unit::Kilogram, Length::Unit::Meter));

    return {atmosphericDensityValue, atmosphericDensityUnit};
}

Shared<const Frame> Celestial::getFrameAt(const LLA& aLla, const Celestial::FrameType& aFrameType) const
{
    using StaticProvider = ostk::physics::coordinate::frame::provider::Static;

    switch (aFrameType)
    {
        case Celestial::FrameType::NED:
        {
            const String frameName = String::Format("{} NED @ {}", this->getName(), aLla.toString());

            if (const auto frameSPtr = Frame::WithName(frameName))
            {
                return frameSPtr;
            }

            const Transform transform = ostk::physics::coordinate::frame::utilities::NorthEastDownTransformAt(
                aLla, this->getEquatorialRadius(), this->getFlattening()
            );

            const Shared<const Frame> nedSPtr = Frame::Construct(
                frameName, false, ephemeris_->getFrame(), std::make_shared<const StaticProvider>(transform)
            );

            return nedSPtr;
        }

        default:
            throw ostk::core::error::runtime::Wrong("Frame type");
            break;
    }

    return nullptr;
}

String Celestial::StringFromFrameType(const Celestial::FrameType& aFrameType)
{
    switch (aFrameType)
    {
        case Celestial::FrameType::NED:
            return "NED";

        default:
            throw ostk::core::error::runtime::Wrong("Frame type");
            break;
    }

    return String::Empty();
}
}  // namespace object
}  // namespace environment
}  // namespace physics
}  // namespace ostk
