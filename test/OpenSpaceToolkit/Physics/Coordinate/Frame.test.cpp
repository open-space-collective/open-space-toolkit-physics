/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/RotationMatrix.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/RotationVector.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/Static.hpp>
#include <OpenSpaceToolkit/Physics/Units/Derived/Angle.hpp>

#include <Global.test.hpp>

namespace iau = ostk::physics::coord::frame::providers::iau;

using ostk::core::types::Shared;
using ostk::core::types::Real;
using ostk::core::types::String;

using ostk::math::obj::Vector3d;
using ostk::math::geom::d3::trf::rot::Quaternion;
using ostk::math::geom::d3::trf::rot::RotationVector;
using ostk::math::geom::d3::trf::rot::RotationMatrix;

using ostk::physics::units::Angle;
using ostk::physics::units::Length;
using ostk::physics::time::Scale;
using ostk::physics::time::Instant;
using ostk::physics::time::DateTime;
using ostk::physics::coord::Transform;
using ostk::physics::coord::Frame;
using ostk::physics::coord::Position;
using ostk::physics::coord::Velocity;
using ostk::physics::coord::Axes;
using ostk::physics::coord::frame::Provider;
using ostk::physics::coord::frame::provider::Static;

class OpenSpaceToolkit_Physics_Coordinate_Frame : public ::testing::Test
{
   protected:
    void SetUp() override
    {
        customFrameSPtr_ = Frame::Construct(name_, isQuasiInertial_, Frame::GCRF(), providerSPtr_);
    }

    void TearDown() override
    {
        Frame::Destruct("Custom");
    }

    const String name_ = "Custom";
    const bool isQuasiInertial_ = true;
    const Shared<const Provider> providerSPtr_ = std::make_shared<Static>(Static(Transform::Passive(
        Instant::J2000(),
        Vector3d(0.0, 0.0, 0.0),
        Vector3d::Zero(),
        Quaternion::RotationVector(RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(-90.0))),
        Vector3d(0.0, 0.0, +2.0)
    )));
    Shared<const Frame> customFrameSPtr_ = nullptr;
};

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame, EqualToOperator)
{
    {
        EXPECT_TRUE(customFrameSPtr_ == customFrameSPtr_);
    }

    {
        const Instant epoch = Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::UTC);

        EXPECT_TRUE(Frame::GCRF() == Frame::GCRF());
        EXPECT_TRUE(Frame::J2000(iau::Theory::IAU_2006) == Frame::J2000(iau::Theory::IAU_2006));
        EXPECT_TRUE(Frame::ITRF() == Frame::ITRF());
        EXPECT_TRUE(Frame::MOD(epoch) == Frame::MOD(epoch));
        EXPECT_TRUE(Frame::TOD(epoch, iau::Theory::IAU_2006) == Frame::TOD(epoch, iau::Theory::IAU_2006));
        EXPECT_TRUE(Frame::TEMEOfEpoch(epoch) == Frame::TEMEOfEpoch(epoch));
    }

    {
        const Shared<const Frame> firstCustomFrameSPtr =
            Frame::Construct("Custom A", isQuasiInertial_, Frame::GCRF(), providerSPtr_);
        const Shared<const Frame> secondCustomFrameSPtr =
            Frame::Construct("Custom B", isQuasiInertial_, Frame::GCRF(), providerSPtr_);

        EXPECT_FALSE(firstCustomFrameSPtr == secondCustomFrameSPtr);

        Frame::Destruct("Custom A");
        Frame::Destruct("Custom B");
    }

    {
        const Shared<const Frame> firstCustomFrameSPtr =
            Frame::Construct("Custom A", true, Frame::GCRF(), providerSPtr_);
        const Shared<const Frame> secondCustomFrameSPtr =
            Frame::Construct("Custom B", false, Frame::GCRF(), providerSPtr_);

        EXPECT_FALSE(firstCustomFrameSPtr == secondCustomFrameSPtr);

        Frame::Destruct("Custom A");
        Frame::Destruct("Custom B");
    }

    {
        const Shared<const Frame> firstCustomFrameSPtr =
            Frame::Construct("Custom A", isQuasiInertial_, Frame::GCRF(), providerSPtr_);
        const Shared<const Frame> secondCustomFrameSPtr =
            Frame::Construct("Custom B", isQuasiInertial_, Frame::ITRF(), providerSPtr_);

        EXPECT_FALSE(firstCustomFrameSPtr == secondCustomFrameSPtr);

        Frame::Destruct("Custom A");
        Frame::Destruct("Custom B");
    }

    {
        const Shared<const Provider> firstProviderSPtr = std::make_shared<Static>(Static(Transform::Passive(
            Instant::J2000(),
            Vector3d(0.0, 0.0, 0.0),
            Vector3d::Zero(),
            Quaternion::RotationVector(RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(-90.0))),
            Vector3d(0.0, 0.0, +2.0)
        )));
        const Shared<const Provider> secondProviderSPtr = std::make_shared<Static>(Static(Transform::Passive(
            Instant::J2000(),
            Vector3d(1.0, 0.0, 0.0),
            Vector3d::Zero(),
            Quaternion::RotationVector(RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(-90.0))),
            Vector3d(0.0, 0.0, +2.0)
        )));

        const Shared<const Frame> firstCustomFrameSPtr =
            Frame::Construct("Custom A", isQuasiInertial_, Frame::GCRF(), firstProviderSPtr);
        const Shared<const Frame> secondCustomFrameSPtr =
            Frame::Construct("Custom B", isQuasiInertial_, Frame::GCRF(), secondProviderSPtr);

        EXPECT_FALSE(firstCustomFrameSPtr == secondCustomFrameSPtr);

        Frame::Destruct("Custom A");
        Frame::Destruct("Custom B");
    }

    {
        EXPECT_FALSE(Frame::GCRF() == Frame::ITRF());
        EXPECT_FALSE(
            Frame::TEMEOfEpoch(Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::UTC)) ==
            Frame::TEMEOfEpoch(Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 1), Scale::UTC))
        );
    }

    {
        EXPECT_FALSE(Frame::Undefined() == Frame::Undefined());
        EXPECT_FALSE(Frame::GCRF() == Frame::Undefined());
        EXPECT_FALSE(Frame::Undefined() == Frame::GCRF());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame, NotEqualToOperator)
{
    {
        EXPECT_FALSE(customFrameSPtr_ != customFrameSPtr_);
    }

    {
        EXPECT_FALSE(Frame::GCRF() != Frame::GCRF());
        EXPECT_FALSE(Frame::ITRF() != Frame::ITRF());

        EXPECT_FALSE(
            Frame::TEMEOfEpoch(Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::UTC)) !=
            Frame::TEMEOfEpoch(Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::UTC))
        );
    }

    {
        const Shared<const Frame> firstCustomFrameSPtr =
            Frame::Construct("Custom A", isQuasiInertial_, Frame::GCRF(), providerSPtr_);
        const Shared<const Frame> secondCustomFrameSPtr =
            Frame::Construct("Custom B", isQuasiInertial_, Frame::GCRF(), providerSPtr_);

        EXPECT_TRUE(firstCustomFrameSPtr != secondCustomFrameSPtr);

        Frame::Destruct("Custom A");
        Frame::Destruct("Custom B");
    }

    {
        const Shared<const Frame> firstCustomFrameSPtr =
            Frame::Construct("Custom A", true, Frame::GCRF(), providerSPtr_);
        const Shared<const Frame> secondCustomFrameSPtr =
            Frame::Construct("Custom B", false, Frame::GCRF(), providerSPtr_);

        EXPECT_TRUE(firstCustomFrameSPtr != secondCustomFrameSPtr);

        Frame::Destruct("Custom A");
        Frame::Destruct("Custom B");
    }

    {
        const Shared<const Frame> firstCustomFrameSPtr =
            Frame::Construct("Custom A", isQuasiInertial_, Frame::GCRF(), providerSPtr_);
        const Shared<const Frame> secondCustomFrameSPtr =
            Frame::Construct("Custom B", isQuasiInertial_, Frame::ITRF(), providerSPtr_);

        EXPECT_TRUE(firstCustomFrameSPtr != secondCustomFrameSPtr);

        Frame::Destruct("Custom A");
        Frame::Destruct("Custom B");
    }

    {
        const Shared<const Provider> firstProviderSPtr = std::make_shared<Static>(Static(Transform::Passive(
            Instant::J2000(),
            Vector3d(0.0, 0.0, 0.0),
            Vector3d::Zero(),
            Quaternion::RotationVector(RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(-90.0))),
            Vector3d(0.0, 0.0, +2.0)
        )));
        const Shared<const Provider> secondProviderSPtr = std::make_shared<Static>(Static(Transform::Passive(
            Instant::J2000(),
            Vector3d(1.0, 0.0, 0.0),
            Vector3d::Zero(),
            Quaternion::RotationVector(RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(-90.0))),
            Vector3d(0.0, 0.0, +2.0)
        )));

        const Shared<const Frame> firstCustomFrameSPtr =
            Frame::Construct("Custom A", isQuasiInertial_, Frame::GCRF(), firstProviderSPtr);
        const Shared<const Frame> secondCustomFrameSPtr =
            Frame::Construct("Custom B", isQuasiInertial_, Frame::GCRF(), secondProviderSPtr);

        EXPECT_TRUE(firstCustomFrameSPtr != secondCustomFrameSPtr);

        Frame::Destruct("Custom A");
        Frame::Destruct("Custom B");
    }

    {
        EXPECT_TRUE(Frame::GCRF() != Frame::ITRF());
        EXPECT_TRUE(
            Frame::TEMEOfEpoch(Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::UTC)) !=
            Frame::TEMEOfEpoch(Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 1), Scale::UTC))
        );
    }

    {
        EXPECT_TRUE(Frame::Undefined() != Frame::Undefined());
        EXPECT_TRUE(Frame::GCRF() != Frame::Undefined());
        EXPECT_TRUE(Frame::Undefined() != Frame::GCRF());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame, StreamOperator)
{
    {
        testing::internal::CaptureStdout();

        EXPECT_NO_THROW(std::cout << (*customFrameSPtr_) << std::endl);

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame, IsDefined)
{
    {
        EXPECT_TRUE(customFrameSPtr_->isDefined());
    }

    {
        EXPECT_TRUE(Frame::GCRF()->isDefined());
        EXPECT_TRUE(Frame::J2000(iau::Theory::IAU_2006)->isDefined());
        EXPECT_TRUE(Frame::MOD(Instant::J2000())->isDefined());
        EXPECT_TRUE(Frame::TOD(Instant::J2000(), iau::Theory::IAU_2006)->isDefined());
        EXPECT_TRUE(Frame::TEME()->isDefined());
        EXPECT_TRUE(Frame::TEMEOfEpoch(Instant::J2000())->isDefined());
        EXPECT_TRUE(Frame::CIRF()->isDefined());
        EXPECT_TRUE(Frame::TIRF()->isDefined());
        EXPECT_TRUE(Frame::ITRF()->isDefined());
    }

    {
        EXPECT_FALSE(Frame::Undefined()->isDefined());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame, IsQuasiInertial)
{
    {
        EXPECT_TRUE(customFrameSPtr_->isQuasiInertial());
    }

    {
        EXPECT_TRUE(Frame::GCRF()->isQuasiInertial());
        EXPECT_TRUE(Frame::J2000(iau::Theory::IAU_2006)->isQuasiInertial());
        EXPECT_TRUE(Frame::MOD(Instant::J2000())->isQuasiInertial());
        EXPECT_TRUE(Frame::TOD(Instant::J2000(), iau::Theory::IAU_2006)->isQuasiInertial());
        EXPECT_TRUE(Frame::TEME()->isQuasiInertial());
        EXPECT_TRUE(Frame::TEMEOfEpoch(Instant::J2000())->isQuasiInertial());
        EXPECT_FALSE(Frame::CIRF()->isQuasiInertial());
        EXPECT_FALSE(Frame::TIRF()->isQuasiInertial());
        EXPECT_FALSE(Frame::ITRF()->isQuasiInertial());
    }

    {
        EXPECT_ANY_THROW(Frame::Undefined()->isQuasiInertial());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame, HasParent)
{
    {
        EXPECT_TRUE(customFrameSPtr_->hasParent());
    }

    {
        EXPECT_FALSE(Frame::GCRF()->hasParent());
        EXPECT_TRUE(Frame::J2000(iau::Theory::IAU_2006)->hasParent());
        EXPECT_TRUE(Frame::MOD(Instant::J2000())->hasParent());
        EXPECT_TRUE(Frame::TOD(Instant::J2000(), iau::Theory::IAU_2006)->hasParent());
        EXPECT_TRUE(Frame::TEME()->hasParent());
        EXPECT_TRUE(Frame::TEMEOfEpoch(Instant::J2000())->hasParent());
        EXPECT_TRUE(Frame::CIRF()->hasParent());
        EXPECT_TRUE(Frame::TIRF()->hasParent());
        EXPECT_TRUE(Frame::ITRF()->hasParent());
    }

    {
        EXPECT_ANY_THROW(Frame::Undefined()->hasParent());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame, AccessParent)
{
    {
        EXPECT_EQ(Frame::GCRF(), customFrameSPtr_->accessParent());
    }

    {
        EXPECT_ANY_THROW(Frame::GCRF()->accessParent());
        EXPECT_EQ(Frame::GCRF(), Frame::J2000(iau::Theory::IAU_2006)->accessParent());
        EXPECT_EQ(Frame::GCRF(), Frame::MOD(Instant::J2000())->accessParent());
        EXPECT_EQ(Frame::GCRF(), Frame::TOD(Instant::J2000(), iau::Theory::IAU_2006)->accessParent());
        EXPECT_EQ(Frame::ITRF(), Frame::TEME()->accessParent());
        EXPECT_EQ(Frame::GCRF(), Frame::TEMEOfEpoch(Instant::J2000())->accessParent());
        EXPECT_EQ(Frame::GCRF(), Frame::CIRF()->accessParent());
        EXPECT_EQ(Frame::CIRF(), Frame::TIRF()->accessParent());
        EXPECT_EQ(Frame::TIRF(), Frame::ITRF()->accessParent());
    }

    {
        EXPECT_ANY_THROW(Frame::Undefined()->accessParent());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame, GetName)
{
    {
        EXPECT_EQ(name_, customFrameSPtr_->getName());
    }

    {
        EXPECT_EQ("GCRF", Frame::GCRF()->getName());
        EXPECT_EQ("J2000 (IAU 2006)", Frame::J2000(iau::Theory::IAU_2006)->getName());
        EXPECT_EQ("MOD @ 2000-01-01 12:00:00 [TT]", Frame::MOD(Instant::J2000())->getName());
        EXPECT_EQ(
            "TOD (IAU 2006) @ 2000-01-01 12:00:00 [TT]", Frame::TOD(Instant::J2000(), iau::Theory::IAU_2006)->getName()
        );
        EXPECT_EQ("TEME", Frame::TEME()->getName());
        EXPECT_EQ("TEMEOfEpoch @ 2000-01-01 12:00:00 [TT]", Frame::TEMEOfEpoch(Instant::J2000())->getName());
        EXPECT_EQ("CIRF", Frame::CIRF()->getName());
        EXPECT_EQ("TIRF", Frame::TIRF()->getName());
        EXPECT_EQ("ITRF", Frame::ITRF()->getName());
    }

    {
        EXPECT_ANY_THROW(Frame::Undefined()->getName());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame, GetOriginIn)
{
    {
        const Position referenceOrigin = Position::Meters({0.0, 0.0, 0.0}, Frame::GCRF());

        EXPECT_EQ(referenceOrigin, Frame::ITRF()->getOriginIn(Frame::GCRF(), Instant::J2000()));
    }

    {
        const Position referenceOrigin = Position::Meters({0.0, 0.0, 0.0}, Frame::ITRF());

        EXPECT_EQ(referenceOrigin, Frame::GCRF()->getOriginIn(Frame::ITRF(), Instant::J2000()));
    }

    {
        const Instant epoch = Instant::J2000();

        {
            const String name = "Custom A";

            const Shared<const Provider> providerSPtr = std::make_shared<Static>(Static(Transform::Passive(
                epoch,
                Vector3d(0.0, -1.0, 0.0),
                Vector3d::Zero(),
                Quaternion::RotationVector(RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(+90.0))),
                Vector3d::Zero()
            )));

            Frame::Construct(name, isQuasiInertial_, Frame::GCRF(), providerSPtr);

            const Position origin = Frame::WithName("Custom A")->getOriginIn(Frame::GCRF(), epoch);

            const Position referenceOrigin = Position::Meters({0.0, +1.0, 0.0}, Frame::GCRF());

            EXPECT_TRUE(origin.isNear(referenceOrigin, Length::Meters(Real::Epsilon()))) << origin;
        }

        {
            const String name = "Custom B";
            const Shared<const Provider> providerSPtr = std::make_shared<Static>(Static(Transform::Passive(
                epoch,
                Vector3d(-1.0, 0.0, 0.0),
                Vector3d::Zero(),
                Quaternion::RotationVector(RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(-90.0))),
                Vector3d::Zero()
            )));

            Frame::Construct(name, isQuasiInertial_, Frame::GCRF(), providerSPtr);

            const Position origin = Frame::WithName("Custom B")->getOriginIn(Frame::GCRF(), epoch);

            const Position referenceOrigin = Position::Meters({+1.0, 0.0, 0.0}, Frame::GCRF());

            EXPECT_TRUE(origin.isNear(referenceOrigin, Length::Meters(Real::Epsilon()))) << origin;
        }

        const Position origin = Frame::WithName("Custom B")->getOriginIn(Frame::WithName("Custom A"), epoch);

        const Position referenceOrigin = Position::Meters({-1.0, -1.0, 0.0}, Frame::WithName("Custom A"));

        EXPECT_TRUE(origin.isNear(referenceOrigin, Length::Meters(Real::Epsilon()))) << origin;

        Frame::Destruct("Custom A");
        Frame::Destruct("Custom B");
    }

    {
        EXPECT_ANY_THROW(Frame::Undefined()->getOriginIn(Frame::Undefined(), Instant::J2000()));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame, GetVelocityIn)
{
    {
        const Velocity referenceVelocity = Velocity::MetersPerSecond({0.0, 0.0, 0.0}, Frame::GCRF());

        EXPECT_EQ(referenceVelocity, Frame::ITRF()->getVelocityIn(Frame::GCRF(), Instant::J2000()));
    }

    {
        const Velocity referenceVelocity = Velocity::MetersPerSecond({0.0, 0.0, 0.0}, Frame::ITRF());

        EXPECT_EQ(referenceVelocity, Frame::GCRF()->getVelocityIn(Frame::ITRF(), Instant::J2000()));
    }

    {
        const Instant epoch = Instant::J2000();

        {
            const String name = "Custom A";

            const Shared<const Provider> providerSPtr = std::make_shared<Static>(Static(Transform::Passive(
                epoch,
                Vector3d(0.0, -1.0, 0.0),
                Vector3d(-1.0, 0.0, 0.0),
                Quaternion::RotationVector(RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(+90.0))),
                Vector3d::Zero()
            )));

            Frame::Construct(name, isQuasiInertial_, Frame::GCRF(), providerSPtr);

            const Velocity velocity = Frame::WithName("Custom A")->getVelocityIn(Frame::GCRF(), epoch);

            const Velocity referenceVelocity = Velocity::MetersPerSecond({+1.0, 0.0, 0.0}, Frame::GCRF());

            EXPECT_TRUE(velocity.getCoordinates().isNear(referenceVelocity.getCoordinates(), Real::Epsilon()))
                << velocity;
        }

        {
            const String name = "Custom B";

            const Shared<const Provider> providerSPtr = std::make_shared<Static>(Static(Transform::Passive(
                epoch,
                Vector3d(-1.0, 0.0, 0.0),
                Vector3d(0.0, -1.0, 0.0),
                Quaternion::RotationVector(RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(-90.0))),
                Vector3d::Zero()
            )));

            Frame::Construct(name, isQuasiInertial_, Frame::GCRF(), providerSPtr);

            const Velocity velocity = Frame::WithName("Custom B")->getVelocityIn(Frame::GCRF(), epoch);

            const Velocity referenceVelocity = Velocity::MetersPerSecond({0.0, +1.0, 0.0}, Frame::GCRF());

            EXPECT_TRUE(velocity.getCoordinates().isNear(referenceVelocity.getCoordinates(), Real::Epsilon()))
                << velocity;
        }

        const Velocity velocity = Frame::WithName("Custom B")->getVelocityIn(Frame::WithName("Custom A"), epoch);

        const Velocity referenceVelocity = Velocity::MetersPerSecond({+1.0, +1.0, 0.0}, Frame::WithName("Custom A"));

        EXPECT_TRUE(velocity.getCoordinates().isNear(referenceVelocity.getCoordinates(), Real::Epsilon())) << velocity;

        Frame::Destruct("Custom A");
        Frame::Destruct("Custom B");
    }

    {
        EXPECT_ANY_THROW(Frame::Undefined()->getVelocityIn(Frame::Undefined(), Instant::J2000()));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame, GetAxesIn)
{
    {
        const Instant epoch = Instant::J2000();

        {
            const String name = "Custom A";

            const Shared<const Provider> providerSPtr = std::make_shared<Static>(Static(Transform::Passive(
                epoch,
                Vector3d(0.0, -1.0, 0.0),
                Vector3d::Zero(),
                Quaternion::RotationVector(RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(+90.0))),
                Vector3d::Zero()
            )));

            Frame::Construct(name, isQuasiInertial_, Frame::GCRF(), providerSPtr);

            const Axes axes = Frame::WithName("Custom A")->getAxesIn(Frame::GCRF(), epoch);

            const Axes referenceAxes = Axes({0.0, +1.0, 0.0}, {-1.0, 0.0, 0.0}, {0.0, 0.0, +1.0}, Frame::GCRF());

            EXPECT_TRUE(axes.x().isNear(referenceAxes.x(), Real::Epsilon())) << axes;
            EXPECT_TRUE(axes.y().isNear(referenceAxes.y(), Real::Epsilon())) << axes;
            EXPECT_TRUE(axes.z().isNear(referenceAxes.z(), Real::Epsilon())) << axes;
        }

        {
            const String name = "Custom B";

            const Shared<const Provider> providerSPtr = std::make_shared<Static>(Static(Transform::Passive(
                epoch,
                Vector3d(-1.0, 0.0, 0.0),
                Vector3d::Zero(),
                Quaternion::RotationVector(RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(-90.0))),
                Vector3d::Zero()
            )));

            Frame::Construct(name, isQuasiInertial_, Frame::GCRF(), providerSPtr);

            const Axes axes = Frame::WithName("Custom B")->getAxesIn(Frame::GCRF(), epoch);

            const Axes referenceAxes = Axes({0.0, -1.0, 0.0}, {+1.0, 0.0, 0.0}, {0.0, 0.0, +1.0}, Frame::GCRF());

            EXPECT_TRUE(axes.x().isNear(referenceAxes.x(), Real::Epsilon())) << axes;
            EXPECT_TRUE(axes.y().isNear(referenceAxes.y(), Real::Epsilon())) << axes;
            EXPECT_TRUE(axes.z().isNear(referenceAxes.z(), Real::Epsilon())) << axes;
        }

        const Axes axes = Frame::WithName("Custom B")->getAxesIn(Frame::WithName("Custom A"), epoch);

        const Axes referenceAxes = Axes({-1.0, 0.0, 0.0}, {0.0, -1.0, 0.0}, {0.0, 0.0, +1.0}, Frame::GCRF());

        EXPECT_TRUE(axes.x().isNear(referenceAxes.x(), Real::Epsilon())) << axes;
        EXPECT_TRUE(axes.y().isNear(referenceAxes.y(), Real::Epsilon())) << axes;
        EXPECT_TRUE(axes.z().isNear(referenceAxes.z(), Real::Epsilon())) << axes;

        Frame::Destruct("Custom A");
        Frame::Destruct("Custom B");
    }

    {
        EXPECT_ANY_THROW(Frame::Undefined()->getAxesIn(Frame::Undefined(), Instant::J2000()));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame, GetTransformTo)
{
    {
        const Transform transform = Frame::GCRF()->getTransformTo(Frame::GCRF(), Instant::J2000());

        EXPECT_TRUE(transform.isIdentity());
    }

    {
        const Instant instant = Instant::J2000();

        const Shared<const Frame> gcrfSPtr = Frame::GCRF();
        const Shared<const Frame> itrfSPtr = Frame::ITRF();

        const Transform transform = itrfSPtr->getTransformTo(gcrfSPtr, instant);

        EXPECT_EQ(instant, transform.getInstant());

        EXPECT_TRUE(transform.getTranslation().isNear(Vector3d(+0.0, +0.0, +0.0), Real::Epsilon()));
        EXPECT_TRUE(transform.getVelocity().isNear(Vector3d(+0.0, +0.0, +0.0), Real::Epsilon()));
        EXPECT_TRUE(transform.getOrientation().isNear(
            Quaternion::XYZS(-1.86147346436534e-05, 8.45983422546411e-07, 0.641490222201766, 0.767131210727542),
            Angle::Degrees(Real::Epsilon())
        ));
        EXPECT_TRUE(transform.getAngularVelocity().isNear(
            Vector3d(1.96489918038813e-09, 2.04221635598212e-09, -7.29211506735101e-05), Real::Epsilon()
        ));
    }

    {
        EXPECT_ANY_THROW(Frame::Undefined()->getTransformTo(Frame::GCRF(), Instant::J2000()));
        EXPECT_ANY_THROW(Frame::GCRF()->getTransformTo(Frame::Undefined(), Instant::J2000()));
        EXPECT_ANY_THROW(Frame::GCRF()->getTransformTo(Frame::GCRF(), Instant::Undefined()));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame, Undefined)
{
    {
        EXPECT_FALSE(Frame::Undefined()->isDefined());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame, GCRF)
{
    {
        EXPECT_TRUE(Frame::GCRF()->isDefined());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame, J2000)
{
    {
        EXPECT_TRUE(Frame::J2000(iau::Theory::IAU_2000A)->isDefined());
        EXPECT_TRUE(Frame::J2000(iau::Theory::IAU_2006)->isDefined());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame, MOD)
{
    {
        EXPECT_TRUE(Frame::MOD(Instant::J2000())->isDefined());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame, TOD)
{
    {
        EXPECT_TRUE(Frame::TOD(Instant::J2000(), iau::Theory::IAU_2000A)->isDefined());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame, TEME)
{
    {
        EXPECT_TRUE(Frame::TEME()->isDefined());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame, TEMEOfEpoch)
{
    {
        EXPECT_TRUE(Frame::TEMEOfEpoch(Instant::J2000())->isDefined());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame, CIRF)
{
    {
        EXPECT_TRUE(Frame::CIRF()->isDefined());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame, TIRF)
{
    {
        EXPECT_TRUE(Frame::TIRF()->isDefined());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame, ITRF)
{
    {
        EXPECT_TRUE(Frame::ITRF()->isDefined());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame, WithName)
{
    {
        if (!Frame::Exists("ITRF"))
        {
            Frame::ITRF();
        }

        EXPECT_TRUE(Frame::WithName("ITRF")->isDefined());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame, Exists)
{
    {
        const String name = "Custom A";

        EXPECT_FALSE(Frame::Exists("Custom A"));

        Frame::Construct(name, isQuasiInertial_, Frame::GCRF(), providerSPtr_);

        EXPECT_TRUE(Frame::Exists("Custom A"));

        Frame::Destruct("Custom A");

        EXPECT_FALSE(Frame::Exists("Custom A"));
    }

    {
        EXPECT_ANY_THROW(Frame::Exists(""));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame, Construct)
{
    {
        const String name = "Custom A";

        EXPECT_NO_THROW(Frame::Construct(name, isQuasiInertial_, Frame::GCRF(), providerSPtr_));
        EXPECT_ANY_THROW(Frame::Construct(name, isQuasiInertial_, Frame::GCRF(), providerSPtr_));

        Frame::Destruct(name);
    }

    {
        const String name = "";

        EXPECT_ANY_THROW(Frame::Construct(name, isQuasiInertial_, Frame::GCRF(), providerSPtr_));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame, Destruct)
{
    {
        const String name = "Custom A";

        const Shared<const Frame> customFrameSPtr =
            Frame::Construct(name, isQuasiInertial_, Frame::GCRF(), providerSPtr_);

        EXPECT_NO_THROW(Frame::Destruct(name));
        EXPECT_ANY_THROW(Frame::Destruct(name));
    }

    {
        EXPECT_ANY_THROW(Frame::Destruct(""));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame, Test_1)
{
    const String name = "Custom A";

    // Pure static translation

    {
        const Shared<const Provider> providerSPtr = std::make_shared<Static>(Static(Transform::Passive(
            Instant::J2000(), Vector3d(-1.0, +0.0, +0.0), Vector3d::Zero(), Quaternion::Unit(), Vector3d::Zero()
        )));

        const Shared<const Frame> customFrameSPtr =
            Frame::Construct(name, isQuasiInertial_, Frame::GCRF(), providerSPtr);

        EXPECT_TRUE(customFrameSPtr->isDefined());

        // Position

        {
            const Vector3d x_CUSTOM = {+1.0, +0.0, +0.0};

            const Vector3d x_GCRF =
                customFrameSPtr->getTransformTo(Frame::GCRF(), Instant::J2000()).applyToPosition(x_CUSTOM);

            EXPECT_TRUE(x_GCRF.isNear(Vector3d(+2.0, +0.0, +0.0), Real::Epsilon())) << x_GCRF.toString();
        }

        // Velocity

        {
            const Vector3d x_CUSTOM = {+1.0, +0.0, +0.0};
            const Vector3d v_CUSTOM = {+1.0, +0.0, +0.0};

            const Vector3d v_GCRF =
                customFrameSPtr->getTransformTo(Frame::GCRF(), Instant::J2000()).applyToVelocity(x_CUSTOM, v_CUSTOM);

            EXPECT_TRUE(v_GCRF.isNear(Vector3d(+1.0, +0.0, +0.0), Real::Epsilon())) << v_GCRF.toString();
        }

        // Vector

        {
            const Vector3d u_CUSTOM = {+1.0, +0.0, +0.0};

            const Vector3d u_GCRF =
                customFrameSPtr->getTransformTo(Frame::GCRF(), Instant::J2000()).applyToVector(u_CUSTOM);

            EXPECT_TRUE(u_GCRF.isNear(Vector3d(+1.0, +0.0, +0.0), Real::Epsilon())) << u_GCRF.toString();
        }

        Frame::Destruct(name);
    }

    // Pure dynamic translation

    {
        const Shared<const Provider> providerSPtr = std::make_shared<Static>(Static(Transform::Passive(
            Instant::J2000(),
            Vector3d(-1.0, +0.0, +0.0),
            Vector3d(-2.0, +0.0, +0.0),
            Quaternion::Unit(),
            Vector3d::Zero()
        )));

        const Shared<const Frame> customFrameSPtr =
            Frame::Construct(name, isQuasiInertial_, Frame::GCRF(), providerSPtr);

        EXPECT_TRUE(customFrameSPtr->isDefined());

        // Position

        {
            const Vector3d x_CUSTOM = {+1.0, +0.0, +0.0};

            const Vector3d x_GCRF =
                customFrameSPtr->getTransformTo(Frame::GCRF(), Instant::J2000()).applyToPosition(x_CUSTOM);

            EXPECT_TRUE(x_GCRF.isNear(Vector3d(+2.0, +0.0, +0.0), Real::Epsilon())) << x_GCRF.toString();
        }

        // Velocity

        {
            const Vector3d x_CUSTOM = {+1.0, +0.0, +0.0};
            const Vector3d v_CUSTOM = {+0.0, +1.0, +0.0};

            const Vector3d v_GCRF =
                customFrameSPtr->getTransformTo(Frame::GCRF(), Instant::J2000()).applyToVelocity(x_CUSTOM, v_CUSTOM);

            EXPECT_TRUE(v_GCRF.isNear(Vector3d(+2.0, +1.0, +0.0), Real::Epsilon())) << v_GCRF.toString();
        }

        // Vector

        {
            const Vector3d u_CUSTOM = {+1.0, +0.0, +0.0};

            const Vector3d u_GCRF =
                customFrameSPtr->getTransformTo(Frame::GCRF(), Instant::J2000()).applyToVector(u_CUSTOM);

            EXPECT_TRUE(u_GCRF.isNear(Vector3d(+1.0, +0.0, +0.0), Real::Epsilon())) << u_GCRF.toString();
        }

        Frame::Destruct(name);
    }

    // Pure static rotation

    {
        const Shared<const Provider> providerSPtr = std::make_shared<Static>(Static(Transform::Passive(
            Instant::J2000(),
            Vector3d::Zero(),
            Vector3d::Zero(),
            Quaternion::RotationVector(RotationVector({+0.0, +0.0, +1.0}, Angle::Degrees(90.0))),
            Vector3d::Zero()
        )));

        const Shared<const Frame> customFrameSPtr =
            Frame::Construct(name, isQuasiInertial_, Frame::GCRF(), providerSPtr);

        EXPECT_TRUE(customFrameSPtr->isDefined());

        // Position

        {
            const Vector3d x_CUSTOM = {+1.0, +0.0, +0.0};

            const Vector3d x_GCRF =
                customFrameSPtr->getTransformTo(Frame::GCRF(), Instant::J2000()).applyToPosition(x_CUSTOM);

            EXPECT_TRUE(x_GCRF.isNear(Vector3d(+0.0, +1.0, +0.0), Real::Epsilon())) << x_GCRF.toString();
        }

        // Velocity

        {
            const Vector3d x_CUSTOM = {+1.0, +0.0, +0.0};
            const Vector3d v_CUSTOM = {+1.0, +0.0, +0.0};

            const Vector3d v_GCRF =
                customFrameSPtr->getTransformTo(Frame::GCRF(), Instant::J2000()).applyToVelocity(x_CUSTOM, v_CUSTOM);

            EXPECT_TRUE(v_GCRF.isNear(Vector3d(+0.0, +1.0, +0.0), Real::Epsilon())) << v_GCRF.toString();
        }

        // Vector

        {
            const Vector3d u_CUSTOM = {+1.0, +0.0, +0.0};

            const Vector3d u_GCRF =
                customFrameSPtr->getTransformTo(Frame::GCRF(), Instant::J2000()).applyToVector(u_CUSTOM);

            EXPECT_TRUE(u_GCRF.isNear(Vector3d(+0.0, +1.0, +0.0), Real::Epsilon())) << u_GCRF.toString();
        }

        Frame::Destruct(name);
    }

    // Pure dynamic rotation

    {
        const Shared<const Provider> providerSPtr = std::make_shared<Static>(Static(Transform::Passive(
            Instant::J2000(), Vector3d::Zero(), Vector3d::Zero(), Quaternion::Unit(), Vector3d(+0.0, +0.0, -1.0)
        )));

        const Shared<const Frame> customFrameSPtr =
            Frame::Construct(name, isQuasiInertial_, Frame::GCRF(), providerSPtr);

        EXPECT_TRUE(customFrameSPtr->isDefined());

        // Position

        {
            const Vector3d x_CUSTOM = {+1.0, +0.0, +0.0};

            const Vector3d x_GCRF =
                customFrameSPtr->getTransformTo(Frame::GCRF(), Instant::J2000()).applyToPosition(x_CUSTOM);

            EXPECT_TRUE(x_GCRF.isNear(Vector3d(+1.0, +0.0, +0.0), Real::Epsilon())) << x_GCRF.toString();
        }

        // Velocity

        {
            const Vector3d x_CUSTOM = {+1.0, +0.0, +0.0};
            const Vector3d v_CUSTOM = {+1.0, +0.0, +0.0};

            const Vector3d v_GCRF =
                customFrameSPtr->getTransformTo(Frame::GCRF(), Instant::J2000()).applyToVelocity(x_CUSTOM, v_CUSTOM);

            EXPECT_TRUE(v_GCRF.isNear(Vector3d(+1.0, -1.0, +0.0), Real::Epsilon())) << v_GCRF.toString();
        }

        // Vector

        {
            const Vector3d u_CUSTOM = {+1.0, +0.0, +0.0};

            const Vector3d u_GCRF =
                customFrameSPtr->getTransformTo(Frame::GCRF(), Instant::J2000()).applyToVector(u_CUSTOM);

            EXPECT_TRUE(u_GCRF.isNear(Vector3d(+1.0, +0.0, +0.0), Real::Epsilon())) << u_GCRF.toString();
        }

        Frame::Destruct(name);
    }

    {
        const Shared<const Provider> providerSPtr = std::make_shared<Static>(Static(Transform::Passive(
            Instant::J2000(), Vector3d(0.0, 0.0, 0.0), Vector3d::Zero(), Quaternion::Unit(), Vector3d(0.0, 0.0, +2.0)
        )));

        const Shared<const Frame> customFrameSPtr =
            Frame::Construct(name, isQuasiInertial_, Frame::GCRF(), providerSPtr);

        EXPECT_TRUE(customFrameSPtr->isDefined());

        // Position

        {
            const Vector3d x_CUSTOM = {0.0, +1.0, 0.0};

            const Vector3d x_GCRF =
                customFrameSPtr->getTransformTo(Frame::GCRF(), Instant::J2000()).applyToPosition(x_CUSTOM);

            EXPECT_TRUE(x_GCRF.isNear(Vector3d(0.0, +1.0, 0.0), Real::Epsilon())) << x_GCRF.toString();
        }

        // Velocity

        {
            const Vector3d x_CUSTOM = {+0.0, +1.0, +0.0};
            const Vector3d v_CUSTOM = {-2.0, +1.0, +0.0};

            const Vector3d v_GCRF =
                customFrameSPtr->getTransformTo(Frame::GCRF(), Instant::J2000()).applyToVelocity(x_CUSTOM, v_CUSTOM);

            EXPECT_TRUE(v_GCRF.isNear(Vector3d(-4.0, +1.0, 0.0), Real::Epsilon())) << v_GCRF.toString();
        }

        // Vector

        {
            const Vector3d v_CUSTOM = {0.0, +1.0, 0.0};

            const Vector3d v_GCRF =
                customFrameSPtr->getTransformTo(Frame::GCRF(), Instant::J2000()).applyToVector(v_CUSTOM);

            EXPECT_TRUE(v_GCRF.isNear(Vector3d(0.0, +1.0, 0.0), Real::Epsilon())) << v_GCRF.toString();
        }

        Frame::Destruct(name);
    }

    {
        const Shared<const Provider> providerSPtr = std::make_shared<Static>(Static(Transform::Passive(
            Instant::J2000(),
            Vector3d(0.0, 0.0, 0.0),
            Vector3d::Zero(),
            Quaternion::RotationVector(RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(-90.0))),
            Vector3d(0.0, 0.0, +2.0)
        )));

        const Shared<const Frame> customFrameSPtr =
            Frame::Construct(name, isQuasiInertial_, Frame::GCRF(), providerSPtr);

        EXPECT_TRUE(customFrameSPtr_->isDefined());

        // Position

        {
            const Vector3d x_CUSTOM = {0.0, +1.0, 0.0};

            const Vector3d x_GCRF =
                customFrameSPtr->getTransformTo(Frame::GCRF(), Instant::J2000()).applyToPosition(x_CUSTOM);

            EXPECT_TRUE(x_GCRF.isNear(Vector3d(+1.0, 0.0, 0.0), Real::Epsilon())) << x_GCRF.toString();
        }

        // Velocity

        {
            const Vector3d x_CUSTOM = {+0.0, +1.0, +0.0};
            const Vector3d v_CUSTOM = {-2.0, +1.0, +0.0};

            const Vector3d v_GCRF =
                customFrameSPtr->getTransformTo(Frame::GCRF(), Instant::J2000()).applyToVelocity(x_CUSTOM, v_CUSTOM);

            EXPECT_TRUE(v_GCRF.isNear(Vector3d(+1.0, +4.0, 0.0), Real::Epsilon())) << v_GCRF.toString();
        }

        // Vector

        {
            const Vector3d v_CUSTOM = {0.0, +1.0, 0.0};

            const Vector3d v_GCRF =
                customFrameSPtr->getTransformTo(Frame::GCRF(), Instant::J2000()).applyToVector(v_CUSTOM);

            EXPECT_TRUE(v_GCRF.isNear(Vector3d(+1.0, 0.0, 0.0), Real::Epsilon())) << v_GCRF.toString();
        }

        Frame::Destruct(name);
    }
}
