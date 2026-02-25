/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Coordinate_Transform__
#define __OpenSpaceToolkit_Physics_Coordinate_Transform__

#include <OpenSpaceToolkit/Core/Type/Real.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/Quaternion.hpp>
#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

namespace ostk
{
namespace physics
{
namespace coordinate
{

using ostk::core::type::Real;
using ostk::core::type::String;

using ostk::mathematics::geometry::d3::transformation::rotation::Quaternion;
using ostk::mathematics::object::Vector3d;

using ostk::physics::time::Instant;

/// @brief Transform
///
/// Passive transformation
///
/// @ref https://en.wikipedia.org/wiki/Active_and_passive_transformation
/// @ref https://core.ac.uk/download/pdf/77055186.pdf

class Transform
{
   public:
    enum class Type
    {

        Undefined,
        Active,
        Passive

    };

    /// @brief Constructor
    ///
    /// @code
    ///     Transform transform(Instant::J2000(), {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, Quaternion::Unit(), {0.0, 0.0, 0.0},
    ///     Transform::Type::Passive);
    /// @endcode
    ///
    /// @param [in] anInstant An instant
    /// @param [in] aTranslation A translation vector
    /// @param [in] aVelocity A velocity vector
    /// @param [in] anOrientation An orientation quaternion
    /// @param [in] anAngularVelocity An angular velocity vector
    /// @param [in] aType A transform type (Active or Passive)
    Transform(
        const Instant& anInstant,
        const Vector3d& aTranslation,
        const Vector3d& aVelocity,
        const Quaternion& anOrientation,
        const Vector3d& anAngularVelocity,
        const Transform::Type& aType
    );

    /// @brief Equality operator
    ///
    /// @code
    ///     transform == otherTransform; // True
    /// @endcode
    ///
    /// @param [in] aTransform A transform to compare with
    /// @return True if transforms are equal
    bool operator==(const Transform& aTransform) const;

    /// @brief Inequality operator
    ///
    /// @code
    ///     transform != otherTransform; // False
    /// @endcode
    ///
    /// @param [in] aTransform A transform to compare with
    /// @return True if transforms are not equal
    bool operator!=(const Transform& aTransform) const;

    /// @brief Composition operator
    ///
    /// @code
    ///     Transform composed = firstTransform * secondTransform;
    /// @endcode
    ///
    /// @param [in] aTransform A transform to compose with
    /// @return Composed transform
    Transform operator*(const Transform& aTransform) const;

    /// @brief Composition assignment operator
    ///
    /// @code
    ///     transform *= otherTransform;
    /// @endcode
    ///
    /// @param [in] aTransform A transform to compose with
    /// @return Reference to the composed transform
    Transform& operator*=(const Transform& aTransform);

    /// @brief Output stream operator
    ///
    /// @code
    ///     std::cout << transform;
    /// @endcode
    ///
    /// @param [in] anOutputStream An output stream
    /// @param [in] aTransform A transform
    /// @return A reference to the output stream
    friend std::ostream& operator<<(std::ostream& anOutputStream, const Transform& aTransform);

    /// @brief Check if the transform is defined
    ///
    /// @code
    ///     Transform::Undefined().isDefined(); // False
    /// @endcode
    ///
    /// @return True if the transform is defined
    bool isDefined() const;

    /// @brief Check if the transform is the identity transform
    ///
    /// @code
    ///     Transform::Identity(Instant::J2000()).isIdentity(); // True
    /// @endcode
    ///
    /// @return True if the transform is identity
    bool isIdentity() const;

    /// @brief Access the instant
    ///
    /// @code
    ///     transform.accessInstant();
    /// @endcode
    ///
    /// @return Reference to the instant
    const Instant& accessInstant() const;

    /// @brief Access the translation vector
    ///
    /// @code
    ///     transform.accessTranslation();
    /// @endcode
    ///
    /// @return Reference to the translation vector
    const Vector3d& accessTranslation() const;

    /// @brief Access the velocity vector
    ///
    /// @code
    ///     transform.accessVelocity();
    /// @endcode
    ///
    /// @return Reference to the velocity vector
    const Vector3d& accessVelocity() const;

    /// @brief Access the orientation quaternion
    ///
    /// @code
    ///     transform.accessOrientation();
    /// @endcode
    ///
    /// @return Reference to the orientation quaternion
    const Quaternion& accessOrientation() const;

    /// @brief Access the angular velocity vector
    ///
    /// @code
    ///     transform.accessAngularVelocity();
    /// @endcode
    ///
    /// @return Reference to the angular velocity vector
    const Vector3d& accessAngularVelocity() const;

    /// @brief Get the instant
    ///
    /// @code
    ///     transform.getInstant();
    /// @endcode
    ///
    /// @return Instant
    Instant getInstant() const;

    /// @brief Get the translation vector
    ///
    /// @code
    ///     transform.getTranslation();
    /// @endcode
    ///
    /// @return Translation vector
    Vector3d getTranslation() const;

    /// @brief Get the velocity vector
    ///
    /// @code
    ///     transform.getVelocity();
    /// @endcode
    ///
    /// @return Velocity vector
    Vector3d getVelocity() const;

    /// @brief Get the orientation quaternion
    ///
    /// @code
    ///     transform.getOrientation();
    /// @endcode
    ///
    /// @return Orientation quaternion
    Quaternion getOrientation() const;

    /// @brief Get the angular velocity vector
    ///
    /// @code
    ///     transform.getAngularVelocity();
    /// @endcode
    ///
    /// @return Angular velocity vector
    Vector3d getAngularVelocity() const;

    /// @brief Get the inverse of the transform
    ///
    /// @code
    ///     Transform inverse = transform.getInverse();
    /// @endcode
    ///
    /// @return Inverse transform
    Transform getInverse() const;

    /// @brief Apply the transform to a position vector
    ///
    /// @code
    ///     Vector3d result = transform.applyToPosition({7000000.0, 0.0, 0.0});
    /// @endcode
    ///
    /// @param [in] aPosition A position vector
    /// @return Transformed position vector
    Vector3d applyToPosition(const Vector3d& aPosition) const;

    /// @brief Apply the transform to a velocity vector
    ///
    /// @code
    ///     Vector3d result = transform.applyToVelocity({7000000.0, 0.0, 0.0}, {0.0, 7546.0, 0.0});
    /// @endcode
    ///
    /// @param [in] aPosition A position vector
    /// @param [in] aVelocity A velocity vector
    /// @return Transformed velocity vector
    Vector3d applyToVelocity(const Vector3d& aPosition, const Vector3d& aVelocity) const;

    /// @brief Apply the transform rotation to a vector
    ///
    /// @code
    ///     Vector3d result = transform.applyToVector({1.0, 0.0, 0.0});
    /// @endcode
    ///
    /// @param [in] aVector A vector
    /// @return Rotated vector
    Vector3d applyToVector(const Vector3d& aVector) const;

    /// @brief Construct an undefined transform
    ///
    /// @code
    ///     Transform transform = Transform::Undefined();
    /// @endcode
    ///
    /// @return Undefined transform
    static Transform Undefined();

    /// @brief Construct an identity transform at a given instant
    ///
    /// @code
    ///     Transform transform = Transform::Identity(Instant::J2000());
    /// @endcode
    ///
    /// @param [in] anInstant An instant
    /// @return Identity transform
    static Transform Identity(const Instant& anInstant);

    /// @brief Construct an active transform
    ///
    /// @code
    ///     Transform transform = Transform::Active(Instant::J2000(), {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
    ///     Quaternion::Unit(), {0.0, 0.0, 0.0});
    /// @endcode
    ///
    /// @param [in] anInstant An instant
    /// @param [in] aTranslation A translation vector
    /// @param [in] aVelocity A velocity vector
    /// @param [in] anOrientation An orientation quaternion
    /// @param [in] anAngularVelocity An angular velocity vector
    /// @return Active transform
    static Transform Active(
        const Instant& anInstant,
        const Vector3d& aTranslation,
        const Vector3d& aVelocity,
        const Quaternion& anOrientation,
        const Vector3d& anAngularVelocity
    );

    /// @brief Construct a passive transform
    ///
    /// @code
    ///     Transform transform = Transform::Passive(Instant::J2000(), {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
    ///     Quaternion::Unit(), {0.0, 0.0, 0.0});
    /// @endcode
    ///
    /// @param [in] anInstant An instant
    /// @param [in] aTranslation A translation vector
    /// @param [in] aVelocity A velocity vector
    /// @param [in] anOrientation An orientation quaternion
    /// @param [in] anAngularVelocity An angular velocity vector
    /// @return Passive transform
    static Transform Passive(
        const Instant& anInstant,
        const Vector3d& aTranslation,
        const Vector3d& aVelocity,
        const Quaternion& anOrientation,
        const Vector3d& anAngularVelocity
    );

   private:
    Instant instant_;

    Vector3d translation_;
    Vector3d velocity_;

    Quaternion orientation_;
    Vector3d angularVelocity_;
};

}  // namespace coordinate
}  // namespace physics
}  // namespace ostk

#endif
