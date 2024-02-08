/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/RotationMatrix.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/RotationVector.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Transform.hpp>
#include <OpenSpaceToolkit/Physics/Time/DateTime.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Unit/Derived/Angle.hpp>

#include <Global.test.hpp>

using ostk::core::type::Real;

using ostk::mathematics::object::Vector3d;
using ostk::mathematics::geometry::d3::transformation::rotation::Quaternion;
using ostk::mathematics::geometry::d3::transformation::rotation::RotationVector;

using ostk::physics::unit::Angle;
using ostk::physics::time::Scale;
using ostk::physics::time::Instant;
using ostk::physics::time::DateTime;
using ostk::physics::coordinate::Transform;

class OpenSpaceToolkit_Physics_Coordinate_Transform : public ::testing::Test
{
   protected:
    void SetUp() override
    {
        transformActive_ = {instant_, t_B_A_, v_B_A_, q_B_A_, w_B_A_in_B_, Transform::Type::Active};
        transformPassive_ = {instant_, t_B_A_, v_B_A_, q_B_A_, w_B_A_in_B_, Transform::Type::Passive};
    }

    const Vector3d t_B_A_ = {+0.0, +0.0, +0.0};
    const Vector3d v_B_A_ = {+0.0, +0.0, +0.0};

    const Quaternion q_B_A_ = Quaternion::Unit();
    const Vector3d w_B_A_in_B_ = {+0.0, +0.0, +0.0};

    const Instant instant_ = Instant::J2000();

    Transform transformActive_ = Transform::Undefined();
    Transform transformPassive_ = Transform::Undefined();
};

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Transform, Constructor)
{
    {
        EXPECT_NO_THROW(Transform(instant_, t_B_A_, v_B_A_, q_B_A_, w_B_A_in_B_, Transform::Type::Active));
    }

    {
        EXPECT_NO_THROW(Transform(instant_, t_B_A_, v_B_A_, q_B_A_, w_B_A_in_B_, Transform::Type::Passive));
    }

    {
        EXPECT_NO_THROW(Transform(instant_, t_B_A_, v_B_A_, q_B_A_, w_B_A_in_B_, Transform::Type::Undefined));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Transform, EqualToOperator)
{
    {
        EXPECT_TRUE(transformActive_ == transformActive_);

        EXPECT_FALSE(
            transformActive_ == Transform(
                                    Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::UTC),
                                    t_B_A_,
                                    v_B_A_,
                                    q_B_A_,
                                    w_B_A_in_B_,
                                    Transform::Type::Active
                                )
        );
        EXPECT_FALSE(
            transformActive_ ==
            Transform(instant_, {+0.0, +0.0, +1.0}, v_B_A_, q_B_A_, w_B_A_in_B_, Transform::Type::Active)
        );
        EXPECT_FALSE(
            transformActive_ ==
            Transform(instant_, t_B_A_, {+0.0, +0.0, +1.0}, q_B_A_, w_B_A_in_B_, Transform::Type::Active)
        );
        EXPECT_FALSE(
            transformActive_ ==
            Transform(
                instant_,
                t_B_A_,
                v_B_A_,
                Quaternion::RotationVector(RotationVector({+0.0, +0.0, +1.0}, Angle::Degrees(+1.0))),
                w_B_A_in_B_,
                Transform::Type::Active
            )
        );
        EXPECT_FALSE(
            transformActive_ == Transform(instant_, t_B_A_, v_B_A_, q_B_A_, {+0.0, +0.0, +1.0}, Transform::Type::Active)
        );
        EXPECT_FALSE(
            Transform(
                instant_,
                {+0.0, +0.0, +1.0},
                {+0.0, +0.0, +1.0},
                Quaternion::RotationVector(RotationVector({+0.0, +0.0, +1.0}, Angle::Degrees(+1.0))),
                {+0.0, +0.0, +1.0},
                Transform::Type::Active
            ) ==
            Transform(
                instant_,
                {+0.0, +0.0, +1.0},
                {+0.0, +0.0, +1.0},
                Quaternion::RotationVector(RotationVector({+0.0, +0.0, +1.0}, Angle::Degrees(+1.0))),
                {+0.0, +0.0, +1.0},
                Transform::Type::Passive
            )
        );

        EXPECT_FALSE(transformActive_ == Transform::Undefined());
        EXPECT_FALSE(Transform::Undefined() == transformActive_);
    }

    {
        EXPECT_FALSE(Transform::Undefined() == Transform::Undefined());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Transform, NotEqualToOperator)
{
    {
        EXPECT_FALSE(transformActive_ != transformActive_);

        EXPECT_TRUE(
            transformActive_ != Transform(
                                    Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::UTC),
                                    t_B_A_,
                                    v_B_A_,
                                    q_B_A_,
                                    w_B_A_in_B_,
                                    Transform::Type::Active
                                )
        );
        EXPECT_TRUE(
            transformActive_ !=
            Transform(instant_, {+0.0, +0.0, +1.0}, v_B_A_, q_B_A_, w_B_A_in_B_, Transform::Type::Active)
        );
        EXPECT_TRUE(
            transformActive_ !=
            Transform(instant_, t_B_A_, {+0.0, +0.0, +1.0}, q_B_A_, w_B_A_in_B_, Transform::Type::Active)
        );
        EXPECT_TRUE(
            transformActive_ !=
            Transform(
                instant_,
                t_B_A_,
                v_B_A_,
                Quaternion::RotationVector(RotationVector({+0.0, +0.0, +1.0}, Angle::Degrees(+1.0))),
                w_B_A_in_B_,
                Transform::Type::Active
            )
        );
        EXPECT_TRUE(
            transformActive_ != Transform(instant_, t_B_A_, v_B_A_, q_B_A_, {+0.0, +0.0, +1.0}, Transform::Type::Active)
        );
        EXPECT_TRUE(
            Transform(
                instant_,
                {+0.0, +0.0, +1.0},
                {+0.0, +0.0, +1.0},
                Quaternion::RotationVector(RotationVector({+0.0, +0.0, +1.0}, Angle::Degrees(+1.0))),
                {+0.0, +0.0, +1.0},
                Transform::Type::Active
            ) !=
            Transform(
                instant_,
                {+0.0, +0.0, +1.0},
                {+0.0, +0.0, +1.0},
                Quaternion::RotationVector(RotationVector({+0.0, +0.0, +1.0}, Angle::Degrees(+1.0))),
                {+0.0, +0.0, +1.0},
                Transform::Type::Passive
            )
        );

        EXPECT_TRUE(transformActive_ != Transform::Undefined());
        EXPECT_TRUE(Transform::Undefined() != transformActive_);
    }

    {
        EXPECT_TRUE(Transform::Undefined() != Transform::Undefined());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Transform, MultiplicationOperator)
{
    // Translation + Velocity + Rotation

    {
        // A to B

        const Vector3d t_B_A = {+0.0, -1.0, +0.0};
        const Vector3d v_B_A = {+0.0, -1.0, +0.0};

        const Quaternion q_B_A = Quaternion::RotationVector(RotationVector({+0.0, +0.0, +1.0}, Angle::Degrees(+90.0)));
        const Vector3d w_B_A_in_B = Vector3d::Zero();

        const Transform transform_B_A = Transform::Passive(instant_, t_B_A, v_B_A, q_B_A, w_B_A_in_B);

        // B to C

        const Vector3d t_C_B = {+0.0, -1.0, +0.0};
        const Vector3d v_C_B = {+1.0, +0.0, +0.0};

        const Quaternion q_C_B = Quaternion::RotationVector(RotationVector({+0.0, +1.0, +0.0}, Angle::Degrees(-90.0)));
        const Vector3d w_C_B_in_C = Vector3d::Zero();

        const Transform transform_C_B = Transform::Passive(instant_, t_C_B, v_C_B, q_C_B, w_C_B_in_C);

        // A to C

        const Vector3d t_C_A = {+1.0, -1.0, +0.0};
        const Vector3d v_C_A = {+0.0, +0.0, +0.0};

        const Quaternion q_C_A = q_C_B * q_B_A;
        const Vector3d w_C_A_in_C = Vector3d::Zero();

        const Transform transform_C_A = Transform::Passive(instant_, t_C_A, v_C_A, q_C_A, w_C_A_in_C);

        // Comparison

        EXPECT_GT(
            1e-14, ((transform_C_B * transform_B_A).accessTranslation() - transform_C_A.accessTranslation()).norm()
        );
        EXPECT_GT(1e-14, ((transform_C_B * transform_B_A).getVelocity() - transform_C_A.getVelocity()).norm());
        EXPECT_TRUE((transform_C_B * transform_B_A)
                        .accessOrientation()
                        .isNear(transform_C_A.accessOrientation(), Angle::Degrees(1e-7)));
        EXPECT_GT(
            1e-14,
            ((transform_C_B * transform_B_A).accessAngularVelocity() - transform_C_A.accessAngularVelocity()).norm()
        );
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Transform, StreamOperator)
{
    {
        testing::internal::CaptureStdout();

        EXPECT_NO_THROW(std::cout << transformActive_ << std::endl);

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Transform, IsDefined)
{
    {
        EXPECT_TRUE(transformActive_.isDefined());
    }

    {
        EXPECT_FALSE(Transform::Undefined().isDefined());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Transform, IsIdentity)
{
    {
        const Vector3d t_B_A = Vector3d::Zero();
        const Vector3d v_B_A = Vector3d::Zero();

        const Quaternion q_B_A = Quaternion::Unit();
        const Vector3d w_B_A_in_B = Vector3d::Zero();

        EXPECT_TRUE(Transform(instant_, t_B_A, v_B_A, q_B_A, w_B_A_in_B, Transform::Type::Passive).isIdentity());
        EXPECT_TRUE(Transform(instant_, t_B_A, v_B_A, q_B_A, w_B_A_in_B, Transform::Type::Passive).isIdentity());
    }

    {
        const Vector3d t_B_A = {0.0, 0.0, 1.0};
        const Vector3d v_B_A = Vector3d::Zero();

        const Quaternion q_B_A = Quaternion::Unit();
        const Vector3d w_B_A_in_B = Vector3d::Zero();

        EXPECT_FALSE(Transform(instant_, t_B_A, v_B_A, q_B_A, w_B_A_in_B, Transform::Type::Passive).isIdentity());
        EXPECT_FALSE(Transform(instant_, t_B_A, v_B_A, q_B_A, w_B_A_in_B, Transform::Type::Passive).isIdentity());
    }

    {
        EXPECT_ANY_THROW(Transform::Undefined().isIdentity());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Transform, AccessInstant)
{
    {
        EXPECT_EQ(instant_, transformPassive_.accessInstant());
    }

    {
        EXPECT_ANY_THROW(Transform::Undefined().accessInstant());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Transform, AccessTranslation)
{
    {
        EXPECT_EQ(t_B_A_, transformPassive_.accessTranslation());
    }

    {
        EXPECT_ANY_THROW(Transform::Undefined().accessTranslation());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Transform, AccessVelocity)
{
    {
        EXPECT_EQ(v_B_A_, transformPassive_.accessVelocity());
    }

    {
        EXPECT_ANY_THROW(Transform::Undefined().accessVelocity());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Transform, AccessOrientation)
{
    {
        EXPECT_EQ(q_B_A_, transformPassive_.accessOrientation());
    }

    {
        EXPECT_ANY_THROW(Transform::Undefined().accessOrientation());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Transform, AccessAngularVelocity)
{
    {
        EXPECT_EQ(w_B_A_in_B_, transformPassive_.accessAngularVelocity());
    }

    {
        EXPECT_ANY_THROW(Transform::Undefined().accessAngularVelocity());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Transform, GetInstant)
{
    {
        EXPECT_EQ(instant_, transformPassive_.getInstant());
    }

    {
        EXPECT_ANY_THROW(Transform::Undefined().getInstant());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Transform, GetTranslation)
{
    {
        EXPECT_EQ(t_B_A_, transformPassive_.getTranslation());
    }

    {
        EXPECT_ANY_THROW(Transform::Undefined().getTranslation());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Transform, GetVelocity)
{
    {
        EXPECT_EQ(v_B_A_, transformPassive_.getVelocity());
    }

    {
        EXPECT_ANY_THROW(Transform::Undefined().getVelocity());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Transform, GetOrientation)
{
    {
        EXPECT_EQ(q_B_A_, transformPassive_.getOrientation());
    }

    {
        EXPECT_ANY_THROW(Transform::Undefined().getOrientation());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Transform, GetAngularVelocity)
{
    {
        EXPECT_EQ(w_B_A_in_B_, transformPassive_.getAngularVelocity());
    }

    {
        EXPECT_ANY_THROW(Transform::Undefined().getAngularVelocity());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Transform, GetInverse)
{
    {
        for (auto idx = 1; idx < 10000; ++idx)
        {
            const Vector3d t_A_B = {std::cos(+1.0 * idx), std::cos(+2.0 * idx), std::cos(+3.0 * idx)};
            const Vector3d v_A_B = {std::cos(+4.0 * idx), std::cos(+5.0 * idx), std::cos(+6.0 * idx)};

            const Quaternion q_B_A = Quaternion::RotationVector(RotationVector(
                Vector3d(
                    std::cos(+0.1 * idx) * std::sin(+0.3 * idx),
                    std::cos(+0.2 * idx) * std::sin(+0.2 * idx),
                    std::cos(+0.3 * idx) * std::sin(+0.1 * idx)
                )
                    .normalized(),
                Angle::Degrees(0.1 * idx)
            ));
            const Vector3d w_B_A_in_B = {std::cos(+7.0 * idx), std::cos(+8.0 * idx), std::cos(+9.0 * idx)};

            const Transform transform = Transform::Passive(Instant::J2000(), t_A_B, v_A_B, q_B_A, w_B_A_in_B);

            EXPECT_TRUE(
                transform.getInverse().getInverse().accessTranslation().isNear(transform.accessTranslation(), 1e-14)
            );
            EXPECT_TRUE(transform.getInverse().getInverse().accessVelocity().isNear(transform.accessVelocity(), 1e-14));
            EXPECT_TRUE(transform.getInverse().getInverse().accessOrientation().isNear(
                transform.accessOrientation(), Angle::Radians(1e-7)
            ));
            EXPECT_TRUE(transform.getInverse().getInverse().accessAngularVelocity().isNear(
                transform.accessAngularVelocity(), 1e-14
            ));
        }
    }

    {
        EXPECT_ANY_THROW(Transform::Undefined().getInverse());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Transform, ApplyToPosition)
{
    // Identity

    {
        const Transform transform_B_A = Transform::Identity(instant_);

        const Vector3d x_A = {+0.0, +0.0, +0.0};

        const Vector3d x_B = transform_B_A.applyToPosition(x_A);

        EXPECT_TRUE(x_B.isNear(x_A, 1e-14));
    }

    // Translation

    {
        const Vector3d t_B_A = {+0.0, -1.0, +0.0};
        const Vector3d v_B_A = Vector3d::Zero();

        const Quaternion q_B_A = Quaternion::Unit();
        const Vector3d w_B_A_in_B = Vector3d::Zero();

        const Transform transform_B_A = Transform::Passive(instant_, t_B_A, v_B_A, q_B_A, w_B_A_in_B);

        const Vector3d x_A = {+0.0, +1.0, +0.0};

        const Vector3d x_B = transform_B_A.applyToPosition(x_A);

        EXPECT_TRUE(x_B.isNear(Vector3d(+0.0, +0.0, +0.0), 1e-14));
    }

    // Rotation

    {
        const Vector3d t_B_A = Vector3d::Zero();
        const Vector3d v_B_A = Vector3d::Zero();

        const Quaternion q_B_A = Quaternion::RotationVector(RotationVector({+0.0, +0.0, +1.0}, Angle::Degrees(+90.0)));
        const Vector3d w_B_A_in_B = Vector3d::Zero();

        const Transform transform_B_A = Transform::Passive(instant_, t_B_A, v_B_A, q_B_A, w_B_A_in_B);

        const Vector3d x_A = {+0.0, +1.0, +0.0};

        const Vector3d x_B = transform_B_A.applyToPosition(x_A);

        EXPECT_TRUE(x_B.isNear(Vector3d(+1.0, +0.0, +0.0), 1e-14));
    }

    // Translation + Rotation

    {
        const Vector3d t_B_A = {+0.0, -1.0, +0.0};
        const Vector3d v_B_A = Vector3d::Zero();

        const Quaternion q_B_A = Quaternion::RotationVector(RotationVector({+0.0, +0.0, +1.0}, Angle::Degrees(+90.0)));
        const Vector3d w_B_A_in_B = Vector3d::Zero();

        const Transform transform_B_A = Transform::Passive(instant_, t_B_A, v_B_A, q_B_A, w_B_A_in_B);

        const Vector3d x_A = {+0.0, +2.0, +0.0};

        const Vector3d x_B = transform_B_A.applyToPosition(x_A);

        EXPECT_TRUE(x_B.isNear(Vector3d(+1.0, +0.0, +0.0), 1e-14));
    }

    // Translation + Velocity

    {
        const Vector3d t_B_A = {+0.0, -1.0, +0.0};
        const Vector3d v_B_A = {+0.0, -1.0, +0.0};

        const Quaternion q_B_A = Quaternion::Unit();
        const Vector3d w_B_A_in_B = Vector3d::Zero();

        const Transform transform_B_A = Transform::Passive(instant_, t_B_A, v_B_A, q_B_A, w_B_A_in_B);

        const Vector3d x_A = {+0.0, +1.0, +0.0};

        const Vector3d x_B = transform_B_A.applyToPosition(x_A);

        EXPECT_TRUE(x_B.isNear(Vector3d(+0.0, +0.0, +0.0), 1e-14));
    }

    // Translation + Velocity + Rotation

    {
        const Vector3d t_B_A = {+0.0, -1.0, +0.0};
        const Vector3d v_B_A = {+0.0, -1.0, +0.0};

        const Quaternion q_B_A = Quaternion::RotationVector(RotationVector({+0.0, +0.0, +1.0}, Angle::Degrees(+90.0)));
        const Vector3d w_B_A_in_B = Vector3d::Zero();

        const Transform transform_B_A = Transform::Passive(instant_, t_B_A, v_B_A, q_B_A, w_B_A_in_B);

        const Vector3d x_A = {+0.0, +2.0, +0.0};

        const Vector3d x_B = transform_B_A.applyToPosition(x_A);

        EXPECT_TRUE(x_B.isNear(Vector3d(+1.0, +0.0, +0.0), 1e-14));
    }

    // Translation + Velocity + Rotation + Angular Velocity

    {
        const Vector3d t_B_A = {+0.0, -1.0, +0.0};
        const Vector3d v_B_A = {+0.0, -1.0, +0.0};

        const Quaternion q_B_A = Quaternion::RotationVector(RotationVector({+0.0, +0.0, +1.0}, Angle::Degrees(+90.0)));
        const Vector3d w_B_A_in_B = {+0.0, +0.0, +1.0};

        const Transform transform_B_A = Transform::Passive(instant_, t_B_A, v_B_A, q_B_A, w_B_A_in_B);

        const Vector3d x_A = {+0.0, +2.0, +0.0};

        const Vector3d x_B = transform_B_A.applyToPosition(x_A);

        EXPECT_TRUE(x_B.isNear(Vector3d(+1.0, +0.0, +0.0), 1e-14));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Transform, ApplyToVelocity)
{
    // Identity

    {
        const Transform transform_B_A = Transform::Identity(instant_);

        const Vector3d x_A = {+0.0, +0.0, +0.0};
        const Vector3d v_A = {+0.0, +0.0, +0.0};

        const Vector3d v_B = transform_B_A.applyToVelocity(x_A, v_A);

        EXPECT_TRUE(v_B.isNear(v_A, 1e-14));
    }

    // Translation

    {
        const Vector3d t_B_A = {+0.0, -1.0, +0.0};
        const Vector3d v_B_A = Vector3d::Zero();

        const Quaternion q_B_A = Quaternion::Unit();
        const Vector3d w_B_A_in_B = Vector3d::Zero();

        const Transform transform_B_A = Transform::Passive(instant_, t_B_A, v_B_A, q_B_A, w_B_A_in_B);

        const Vector3d x_A = {+0.0, +0.0, +0.0};
        const Vector3d v_A = {+0.0, +1.0, +0.0};

        const Vector3d v_B = transform_B_A.applyToVelocity(x_A, v_A);

        EXPECT_TRUE(v_B.isNear(Vector3d(+0.0, +1.0, +0.0), 1e-14));
    }

    // Rotation

    {
        const Vector3d t_B_A = Vector3d::Zero();
        const Vector3d v_B_A = Vector3d::Zero();

        const Quaternion q_B_A = Quaternion::RotationVector(RotationVector({+0.0, +0.0, +1.0}, Angle::Degrees(+90.0)));
        const Vector3d w_B_A_in_B = Vector3d::Zero();

        const Transform transform_B_A = Transform::Passive(instant_, t_B_A, v_B_A, q_B_A, w_B_A_in_B);

        const Vector3d x_A = {+0.0, +0.0, +0.0};
        const Vector3d v_A = {+0.0, +1.0, +0.0};

        const Vector3d v_B = transform_B_A.applyToVelocity(x_A, v_A);

        EXPECT_TRUE(v_B.isNear(Vector3d(+1.0, +0.0, +0.0), 1e-14));
    }

    // Translation + Rotation

    {
        const Vector3d t_B_A = {+0.0, -1.0, +0.0};
        const Vector3d v_B_A = Vector3d::Zero();

        const Quaternion q_B_A = Quaternion::RotationVector(RotationVector({+0.0, +0.0, +1.0}, Angle::Degrees(+90.0)));
        const Vector3d w_B_A_in_B = Vector3d::Zero();

        const Transform transform_B_A = Transform::Passive(instant_, t_B_A, v_B_A, q_B_A, w_B_A_in_B);

        const Vector3d x_A = {+0.0, +2.0, +0.0};
        const Vector3d v_A = {+0.0, +1.0, +0.0};

        const Vector3d v_B = transform_B_A.applyToVelocity(x_A, v_A);

        EXPECT_TRUE(v_B.isNear(Vector3d(+1.0, +0.0, +0.0), 1e-14));
    }

    // Translation + Velocity

    {
        const Vector3d t_B_A = {+0.0, -1.0, +0.0};
        const Vector3d v_B_A = {+0.0, -1.0, +0.0};

        const Quaternion q_B_A = Quaternion::Unit();
        const Vector3d w_B_A_in_B = Vector3d::Zero();

        const Transform transform_B_A = Transform::Passive(instant_, t_B_A, v_B_A, q_B_A, w_B_A_in_B);

        const Vector3d x_A = {+0.0, +2.0, +0.0};
        const Vector3d v_A = {+0.0, +2.0, +0.0};

        const Vector3d v_B = transform_B_A.applyToVelocity(x_A, v_A);

        EXPECT_TRUE(v_B.isNear(Vector3d(+0.0, +1.0, +0.0), 1e-14));
    }

    // Translation + Velocity + Rotation

    {
        const Vector3d t_B_A = {+0.0, -1.0, +0.0};
        const Vector3d v_B_A = {+0.0, -1.0, +0.0};

        const Quaternion q_B_A = Quaternion::RotationVector(RotationVector({+0.0, +0.0, +1.0}, Angle::Degrees(+90.0)));
        const Vector3d w_B_A_in_B = Vector3d::Zero();

        const Transform transform_B_A = Transform::Passive(instant_, t_B_A, v_B_A, q_B_A, w_B_A_in_B);

        const Vector3d x_A = {+0.0, +2.0, +0.0};
        const Vector3d v_A = {+0.0, +2.0, +0.0};

        const Vector3d v_B = transform_B_A.applyToVelocity(x_A, v_A);

        EXPECT_TRUE(v_B.isNear(Vector3d(+1.0, +0.0, +0.0), 1e-14));
    }

    // Translation + Velocity + Rotation + Angular Velocity

    {
        const Vector3d t_B_A = {+0.0, -1.0, +0.0};
        const Vector3d v_B_A = {+0.0, -1.0, +0.0};

        const Quaternion q_B_A = Quaternion::RotationVector(RotationVector({+0.0, +0.0, +1.0}, Angle::Degrees(+90.0)));
        const Vector3d w_B_A_in_B = {+0.0, +0.0, +1.0};

        const Transform transform_B_A = Transform::Passive(instant_, t_B_A, v_B_A, q_B_A, w_B_A_in_B);

        const Vector3d x_A = {+0.0, +2.0, +0.0};
        const Vector3d v_A = {+0.0, +2.0, +0.0};

        const Vector3d v_B = transform_B_A.applyToVelocity(x_A, v_A);

        EXPECT_TRUE(v_B.isNear(Vector3d(+1.0, -1.0, +0.0), 1e-14));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Transform, ApplyToVector)
{
    // Identity

    {
        const Transform transform_B_A = Transform::Identity(instant_);

        const Vector3d v_A = {+0.0, +0.0, +0.0};

        const Vector3d v_B = transform_B_A.applyToVector(v_A);

        EXPECT_TRUE(v_B.isNear(v_A, 1e-14));
    }

    // Translation

    {
        const Vector3d t_B_A = {+0.0, -1.0, +0.0};
        const Vector3d v_B_A = Vector3d::Zero();

        const Quaternion q_B_A = Quaternion::Unit();
        const Vector3d w_B_A_in_B = Vector3d::Zero();

        const Transform transform_B_A = Transform::Passive(instant_, t_B_A, v_B_A, q_B_A, w_B_A_in_B);

        const Vector3d v_A = {+0.0, +1.0, +0.0};

        const Vector3d v_B = transform_B_A.applyToVector(v_A);

        EXPECT_TRUE(v_B.isNear(v_A, 1e-14));
    }

    // Rotation

    {
        const Vector3d t_B_A = Vector3d::Zero();
        const Vector3d v_B_A = Vector3d::Zero();

        const Quaternion q_B_A = Quaternion::RotationVector(RotationVector({+0.0, +0.0, +1.0}, Angle::Degrees(+90.0)));
        const Vector3d w_B_A_in_B = Vector3d::Zero();

        const Transform transform_B_A = Transform::Passive(instant_, t_B_A, v_B_A, q_B_A, w_B_A_in_B);

        const Vector3d v_A = {+0.0, +1.0, +0.0};

        const Vector3d v_B = transform_B_A.applyToVector(v_A);

        EXPECT_TRUE(v_B.isNear(Vector3d(+1.0, +0.0, +0.0), 1e-14));
    }

    // Translation + Rotation

    {
        const Vector3d t_B_A = {+0.0, -1.0, +0.0};
        const Vector3d v_B_A = Vector3d::Zero();

        const Quaternion q_B_A = Quaternion::RotationVector(RotationVector({+0.0, +0.0, +1.0}, Angle::Degrees(+90.0)));
        const Vector3d w_B_A_in_B = Vector3d::Zero();

        const Transform transform_B_A = Transform::Passive(instant_, t_B_A, v_B_A, q_B_A, w_B_A_in_B);

        const Vector3d v_A = {+0.0, +1.0, +0.0};

        const Vector3d v_B = transform_B_A.applyToVector(v_A);

        EXPECT_TRUE(v_B.isNear(Vector3d(+1.0, +0.0, +0.0), 1e-14));
    }

    // Translation + Velocity

    {
        const Vector3d t_B_A = {+0.0, -1.0, +0.0};
        const Vector3d v_B_A = {+0.0, -1.0, +0.0};

        const Quaternion q_B_A = Quaternion::Unit();
        const Vector3d w_B_A_in_B = Vector3d::Zero();

        const Transform transform_B_A = Transform::Passive(instant_, t_B_A, v_B_A, q_B_A, w_B_A_in_B);

        const Vector3d v_A = {+0.0, +2.0, +0.0};

        const Vector3d v_B = transform_B_A.applyToVector(v_A);

        EXPECT_TRUE(v_B.isNear(Vector3d(+0.0, +2.0, +0.0), 1e-14));
    }

    // Translation + Velocity + Rotation

    {
        const Vector3d t_B_A = {+0.0, -1.0, +0.0};
        const Vector3d v_B_A = {+0.0, -1.0, +0.0};

        const Quaternion q_B_A = Quaternion::RotationVector(RotationVector({+0.0, +0.0, +1.0}, Angle::Degrees(+90.0)));
        const Vector3d w_B_A_in_B = Vector3d::Zero();

        const Transform transform_B_A = Transform::Passive(instant_, t_B_A, v_B_A, q_B_A, w_B_A_in_B);

        const Vector3d v_A = {+0.0, +2.0, +0.0};

        const Vector3d v_B = transform_B_A.applyToVector(v_A);

        EXPECT_TRUE(v_B.isNear(Vector3d(+2.0, +0.0, +0.0), 1e-14));
    }

    // Translation + Velocity + Rotation + Angular Velocity

    {
        const Vector3d t_B_A = {+0.0, -1.0, +0.0};
        const Vector3d v_B_A = {+0.0, -1.0, +0.0};

        const Quaternion q_B_A = Quaternion::RotationVector(RotationVector({+0.0, +0.0, +1.0}, Angle::Degrees(+90.0)));
        const Vector3d w_B_A_in_B = {+0.0, +0.0, +1.0};

        const Transform transform_B_A = Transform::Passive(instant_, t_B_A, v_B_A, q_B_A, w_B_A_in_B);

        const Vector3d v_A = {+0.0, +2.0, +0.0};

        const Vector3d v_B = transform_B_A.applyToVector(v_A);

        EXPECT_TRUE(v_B.isNear(Vector3d(+2.0, +0.0, +0.0), 1e-14));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Transform, Undefined)
{
    {
        EXPECT_NO_THROW(Transform::Undefined());

        EXPECT_FALSE(Transform::Undefined().isDefined());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Transform, Identity)
{
    {
        EXPECT_NO_THROW(Transform::Identity(instant_));

        EXPECT_EQ(Transform::Identity(instant_), Transform::Identity(instant_).getInverse());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Transform, Active)
{
    {
        EXPECT_EQ(transformActive_, Transform::Active(instant_, t_B_A_, v_B_A_, q_B_A_, w_B_A_in_B_));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Transform, Passive)
{
    {
        EXPECT_EQ(
            Transform(instant_, t_B_A_, v_B_A_, q_B_A_, w_B_A_in_B_, Transform::Type::Passive),
            Transform::Passive(instant_, t_B_A_, v_B_A_, q_B_A_, w_B_A_in_B_)
        );
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Transform, Test_1)
{
    {
        const Vector3d t_A_G = {+0.0, -1.0, +0.0};
        const Vector3d v_A_G = {+0.0, +0.0, +0.0};

        const Quaternion q_A_G = Quaternion::XYZS(0.0, 0.0, 0.707106781186547, 0.707106781186548).toNormalized();
        const Vector3d w_A_G_in_A = {+0.0, +0.0, +0.0};

        const Transform transform_A_G = {instant_, t_A_G, v_A_G, q_A_G, w_A_G_in_A, Transform::Type::Passive};

        {
            const Vector3d x_G = {+0.0, +1.0, +0.0};
            const Vector3d x_A = transform_A_G.applyToPosition(x_G);

            EXPECT_TRUE(x_A.isNear(Vector3d(+0.0, +0.0, +0.0), 1e-5)) << x_A.toString();
        }

        {
            const Vector3d x_G = {+0.0, +2.0, +0.0};
            const Vector3d x_A = transform_A_G.applyToPosition(x_G);

            EXPECT_TRUE(x_A.isNear(Vector3d(+1.0, +0.0, +0.0), 1e-5)) << x_A.toString();
        }

        const Vector3d t_B_G = {-1.0, +0.0, +0.0};
        const Vector3d v_B_G = {+0.0, +0.0, +0.0};

        const Quaternion q_B_G = Quaternion::XYZS(0.0, 0.0, -0.707106781186547, 0.707106781186548).toNormalized();
        const Vector3d w_B_G_in_B = {+0.0, +0.0, +0.0};

        const Transform transform_B_G = {instant_, t_B_G, v_B_G, q_B_G, w_B_G_in_B, Transform::Type::Passive};

        {
            const Vector3d x_G = {+1.0, +0.0, +0.0};
            const Vector3d x_B = transform_B_G.applyToPosition(x_G);

            EXPECT_TRUE(x_B.isNear(Vector3d(+0.0, +0.0, +0.0), 1e-5)) << x_B.toString();
        }

        {
            const Vector3d x_G = {+2.0, +0.0, +0.0};
            const Vector3d x_B = transform_B_G.applyToPosition(x_G);

            EXPECT_TRUE(x_B.isNear(Vector3d(+0.0, +1.0, +0.0), 1e-5)) << x_B.toString();
        }

        const Transform transform_A_B = transform_A_G * transform_B_G.getInverse();

        {
            const Vector3d x_B = {+0.0, +0.0, +0.0};
            const Vector3d x_A = transform_A_B.applyToPosition(x_B);

            EXPECT_TRUE(x_A.isNear(Vector3d(-1.0, -1.0, +0.0), 1e-5)) << x_A.toString();
        }
    }
}
