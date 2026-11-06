/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/RotationVector.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Transform.hpp>

namespace ostk
{
namespace physics
{
namespace coordinate
{

Transform::Transform(
    const Instant& anInstant,
    const Vector3d& aTranslation,
    const Vector3d& aVelocity,
    const Quaternion& anOrientation,
    const Vector3d& anAngularVelocity,
    const Transform::Type& aType
)
    : instant_(anInstant),
      translation_(aTranslation),
      velocity_(aVelocity),
      orientation_(anOrientation),
      angularVelocity_(anAngularVelocity)
{
    switch (aType)
    {
        case Transform::Type::Active:
            (*this) = this->getInverse();
            break;

        case Transform::Type::Passive:
            break;

        default:
            throw ostk::core::error::runtime::Wrong("Type");
            break;
    }
}

bool Transform::operator==(const Transform& aTransform) const
{
    return (instant_ == aTransform.instant_) && (translation_ == aTransform.translation_) &&
           (velocity_ == aTransform.velocity_) && (orientation_ == aTransform.orientation_) &&
           (angularVelocity_ == aTransform.angularVelocity_);
}

bool Transform::operator!=(const Transform& aTransform) const
{
    return !((*this) == aTransform);
}

Transform Transform::operator*(const Transform& aTransform) const
{
    if (instant_ != aTransform.instant_)
    {
        throw ostk::core::error::RuntimeError("Instants are different.");
    }

    Transform transform(*this);

    transform *= aTransform;

    return transform;
}

Transform& Transform::operator*=(const Transform& aTransform)
{
    if (instant_ != aTransform.instant_)
    {
        throw ostk::core::error::RuntimeError("Instants are different.");
    }

    // C_A = C_B * B_A

    // t_C_A_in_A = t_B_A_in_A + q_A_B * t_C_B_in_B

    const Vector3d translation = aTransform.translation_ + aTransform.orientation_.toConjugate() * translation_;

    // v_C_A_in_A = v_B_A_in_A + q_A_B * v_C_B_in_B + Ω_B_C_in_A x t_B_A_in_A

    const Vector3d velocity = aTransform.velocity_ + aTransform.orientation_.toConjugate() * velocity_ +
                              angularVelocity_.cross(aTransform.translation_);

    // q_C_A = q_C_B * q_B_A

    const Quaternion orientation = (orientation_ * aTransform.orientation_).toNormalized();

    // Ω_C_A_in_C = Ω_C_B_in_C + q_C_B * Ω_B_A_in_B

    const Vector3d angularVelocity = angularVelocity_ + orientation_ * aTransform.angularVelocity_;

    translation_ = translation;
    velocity_ = velocity;
    orientation_ = orientation;
    angularVelocity_ = angularVelocity;

    return *this;
}

std::ostream& operator<<(std::ostream& anOutputStream, const Transform& aTransform)
{
    using ostk::mathematics::geometry::d3::transformation::rotation::RotationVector;

    using ostk::physics::time::Scale;

    ostk::core::utils::Print::Header(anOutputStream, "Transform");

    ostk::core::utils::Print::Line(anOutputStream) << "Instant:" << aTransform.getInstant().toString(Scale::UTC);

    ostk::core::utils::Print::Line(anOutputStream)
        << "Translation:" << (aTransform.getTranslation().toString() + " [m]");
    ostk::core::utils::Print::Line(anOutputStream) << "Velocity:" << (aTransform.getVelocity().toString() + " [m/s]");

    ostk::core::utils::Print::Line(anOutputStream)
        << "Orientation:"
        << String::Format(
               "{} == {}",
               aTransform.getOrientation().toString(),
               RotationVector::Quaternion(aTransform.getOrientation()).toString()
           );
    ostk::core::utils::Print::Line(anOutputStream)
        << "Angular Velocity:" << (aTransform.getAngularVelocity().toString() + " [rad/s]");

    ostk::core::utils::Print::Footer(anOutputStream);

    return anOutputStream;
}

bool Transform::isIdentity() const
{
    return (translation_ == Vector3d::Zero()) && (velocity_ == Vector3d::Zero()) &&
           (orientation_ == Quaternion::Unit()) && (angularVelocity_ == Vector3d::Zero());
}

const Instant& Transform::getInstant() const
{
    return instant_;
}

const Vector3d& Transform::getTranslation() const
{
    return translation_;
}

const Vector3d& Transform::getVelocity() const
{
    return velocity_;
}

const Quaternion& Transform::getOrientation() const
{
    return orientation_;
}

const Vector3d& Transform::getAngularVelocity() const
{
    return angularVelocity_;
}

Transform Transform::getInverse() const
{
    // t_A_B_in_B = - q_B_A * t_B_A_in_A

    const Vector3d translation = -(orientation_ * translation_);

    // v_A_B_in_B = - q_B_A * v_B_A_in_A + Ω_B_A_in_B x (q_B_A * t_B_A_in_A)

    const Vector3d velocity = -(orientation_ * velocity_) + angularVelocity_.cross(orientation_ * translation_);

    // q_A_B = q_B_A'

    const Quaternion orientation = orientation_.toConjugate();

    // Ω_A_B_in_A = - q_A_B * Ω_B_A_in_B

    const Vector3d angularVelocity = -(orientation * angularVelocity_);

    return {instant_, translation, velocity, orientation, angularVelocity, Transform::Type::Passive};
}

Vector3d Transform::applyToPosition(const Vector3d& aPosition) const
{
    if (!aPosition.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Position");
    }

    // x_B = q_B_A * (x_A + t_B_A_in_A)

    return orientation_ * (aPosition + translation_);
}

Vector3d Transform::applyToVelocity(const Vector3d& aPosition, const Vector3d& aVelocity) const
{
    if (!aPosition.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Position");
    }

    if (!aVelocity.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Velocity");
    }

    // v_B_in_B = q_B_A * (v_A_in_A + v_B_A_in_A) - Ω_B_A_in_B x (q_B_A * (x_A + t_B_A_in_A))

    return orientation_ * (aVelocity + velocity_) - angularVelocity_.cross(orientation_ * (aPosition + translation_));
}

Vector3d Transform::applyToVector(const Vector3d& aVector) const
{
    if (!aVector.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Vector");
    }

    return orientation_ * aVector;
}

Transform Transform::Identity(const Instant& anInstant)
{
    return {
        anInstant, Vector3d::Zero(), Vector3d::Zero(), Quaternion::Unit(), Vector3d::Zero(), Transform::Type::Passive
    };
}

Transform Transform::Active(
    const Instant& anInstant,
    const Vector3d& aTranslation,
    const Vector3d& aVelocity,
    const Quaternion& anOrientation,
    const Vector3d& anAngularVelocity
)
{
    return {anInstant, aTranslation, aVelocity, anOrientation, anAngularVelocity, Transform::Type::Active};
}

Transform Transform::Passive(
    const Instant& anInstant,
    const Vector3d& aTranslation,
    const Vector3d& aVelocity,
    const Quaternion& anOrientation,
    const Vector3d& anAngularVelocity
)
{
    return {anInstant, aTranslation, aVelocity, anOrientation, anAngularVelocity, Transform::Type::Passive};
}

}  // namespace coordinate
}  // namespace physics
}  // namespace ostk
