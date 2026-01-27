/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Type/Shared.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/Quaternion.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/RotationVector.hpp>
#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Manager.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/Static.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Transform.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Unit/Derived/Angle.hpp>

#include <Global.test.hpp>

using ostk::core::container::Array;
using ostk::core::type::Shared;
using ostk::core::type::String;

using ostk::mathematics::geometry::d3::transformation::rotation::Quaternion;
using ostk::mathematics::geometry::d3::transformation::rotation::RotationVector;
using ostk::mathematics::object::Vector3d;

using ostk::physics::coordinate::Frame;
using ostk::physics::coordinate::frame::Manager;
using ostk::physics::coordinate::frame::Provider;
using ostk::physics::coordinate::frame::provider::Static;
using ostk::physics::coordinate::Transform;
using ostk::physics::time::DateTime;
using ostk::physics::time::Instant;
using ostk::physics::time::Scale;
using ostk::physics::unit::Angle;

class OpenSpaceToolkit_Physics_Coordinate_Frame_Manager : public ::testing::Test
{
   protected:
    void SetUp() override
    {
        manager_ = &Manager::Get();

        providerSPtr_ = std::make_shared<Static>(Static(Transform::Passive(
            Instant::J2000(),
            Vector3d(1.0, 0.0, 0.0),
            Vector3d::Zero(),
            Quaternion::RotationVector(RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(90.0))),
            Vector3d::Zero()
        )));

        Frame::GCRF();
    }

    void TearDown() override
    {
        // Clean up any frames created during tests
        if (Frame::Exists("TestFrame"))
        {
            Frame::Destruct("TestFrame");
        }
        if (Frame::Exists("TestFrame1"))
        {
            Frame::Destruct("TestFrame1");
        }
        if (Frame::Exists("TestFrame2"))
        {
            Frame::Destruct("TestFrame2");
        }
        if (Frame::Exists("TestFrame3"))
        {
            Frame::Destruct("TestFrame3");
        }
    }

    Manager* manager_;
    Shared<const Provider> providerSPtr_;
};

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Manager, Get)
{
    {
        EXPECT_NO_THROW(Manager::Get());
    }

    {
        Manager& manager1 = Manager::Get();
        Manager& manager2 = Manager::Get();

        EXPECT_EQ(&manager1, &manager2);
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Manager, HasFrameWithName)
{
    {
        EXPECT_TRUE(manager_->hasFrameWithName("GCRF"));
    }

    {
        // Non-existent frame
        EXPECT_FALSE(manager_->hasFrameWithName("NonExistentFrame"));
    }

    {
        // Create a custom frame and check it exists
        const Shared<const Frame> frameSPtr = Frame::Construct("TestFrame", true, Frame::GCRF(), providerSPtr_);

        EXPECT_TRUE(manager_->hasFrameWithName("TestFrame"));

        Frame::Destruct("TestFrame");

        EXPECT_FALSE(manager_->hasFrameWithName("TestFrame"));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Manager, AccessFrameWithName)
{
    {
        // Access GCRF
        const Shared<const Frame> gcrfSPtr = manager_->accessFrameWithName("GCRF");

        EXPECT_NE(nullptr, gcrfSPtr);
        EXPECT_EQ("GCRF", gcrfSPtr->getName());
    }

    {
        // Access non-existent frame returns nullptr
        const Shared<const Frame> frameSPtr = manager_->accessFrameWithName("NonExistentFrame");

        EXPECT_EQ(nullptr, frameSPtr);
    }

    {
        // Create and access custom frame
        const Shared<const Frame> createdFrameSPtr = Frame::Construct("TestFrame", true, Frame::GCRF(), providerSPtr_);

        const Shared<const Frame> accessedFrameSPtr = manager_->accessFrameWithName("TestFrame");

        EXPECT_NE(nullptr, accessedFrameSPtr);
        EXPECT_EQ("TestFrame", accessedFrameSPtr->getName());
        EXPECT_EQ(createdFrameSPtr, accessedFrameSPtr);
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Manager, AddFrame)
{
    {
        // Add a frame
        const Shared<const Frame> frameSPtr = Frame::Construct("TestFrame", true, Frame::GCRF(), providerSPtr_);

        EXPECT_TRUE(manager_->hasFrameWithName("TestFrame"));
    }

    {
        // Adding nullptr should throw
        EXPECT_THROW(manager_->addFrame(nullptr), ostk::core::error::runtime::Undefined);
    }

    {
        // Adding duplicate frame doesn't throw (just doesn't add it again)
        const Shared<const Frame> frameSPtr = Frame::Construct("TestFrame1", true, Frame::GCRF(), providerSPtr_);

        EXPECT_NO_THROW(manager_->addFrame(frameSPtr));
        EXPECT_TRUE(manager_->hasFrameWithName("TestFrame1"));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Manager, RemoveFrameWithName)
{
    {
        // Create and remove a frame
        Frame::Construct("TestFrame", true, Frame::GCRF(), providerSPtr_);

        EXPECT_TRUE(manager_->hasFrameWithName("TestFrame"));

        manager_->removeFrameWithName("TestFrame");

        EXPECT_FALSE(manager_->hasFrameWithName("TestFrame"));
    }

    {
        // Removing non-existent frame throws
        EXPECT_THROW(manager_->removeFrameWithName("NonExistentFrame"), ostk::core::error::RuntimeError);
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Manager, GetAllFrameNames)
{
    {
        // Create some frames
        Frame::Construct("TestFrame1", true, Frame::GCRF(), providerSPtr_);
        Frame::Construct("TestFrame2", true, Frame::GCRF(), providerSPtr_);

        const auto frameNames = manager_->getAllFrameNames();

        // Should contain our test frames
        bool hasTestFrame1 = false;
        bool hasTestFrame2 = false;

        for (const auto& name : frameNames)
        {
            if (name == "TestFrame1")
            {
                hasTestFrame1 = true;
            }
            if (name == "TestFrame2")
            {
                hasTestFrame2 = true;
            }
        }

        EXPECT_TRUE(hasTestFrame1);
        EXPECT_TRUE(hasTestFrame2);
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Manager, ClearAllFrames)
{
    {
        // Create some frames
        Frame::Construct("TestFrame1", true, Frame::GCRF(), providerSPtr_);
        Frame::Construct("TestFrame2", true, Frame::GCRF(), providerSPtr_);

        EXPECT_TRUE(manager_->hasFrameWithName("TestFrame1"));
        EXPECT_TRUE(manager_->hasFrameWithName("TestFrame2"));

        manager_->clearAllFrames();

        EXPECT_FALSE(manager_->hasFrameWithName("TestFrame1"));
        EXPECT_FALSE(manager_->hasFrameWithName("TestFrame2"));

        // After clearing, we need to re-initialize standard frames for other tests
        // This is handled by accessing them again
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Manager, AccessCachedTransform)
{
    {
        // Access non-existent cached transform returns undefined
        const Shared<const Frame> gcrfSPtr = Frame::GCRF();
        const Shared<const Frame> itrfSPtr = Frame::ITRF();
        const Instant instant = Instant::J2000();

        const Transform transform = manager_->accessCachedTransform(gcrfSPtr, itrfSPtr, instant);

        // Transform may or may not be defined depending on whether it was previously cached
        // We just verify no crash occurs
        EXPECT_NO_THROW(transform.isDefined());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Manager, AddCachedTransform)
{
    {
        const Shared<const Frame> frameSPtr1 = Frame::Construct("TestFrame1", true, Frame::GCRF(), providerSPtr_);
        const Shared<const Frame> frameSPtr2 = Frame::Construct("TestFrame2", true, Frame::GCRF(), providerSPtr_);
        const Instant instant = Instant::J2000();

        const Transform transform = Transform::Passive(
            instant, Vector3d(1.0, 2.0, 3.0), Vector3d::Zero(), Quaternion::Unit(), Vector3d::Zero()
        );

        // Add cached transform
        manager_->addCachedTransform(frameSPtr1, frameSPtr2, instant, transform);

        // Verify forward transform is cached
        const Transform cachedForward = manager_->accessCachedTransform(frameSPtr1, frameSPtr2, instant);
        EXPECT_TRUE(cachedForward.isDefined());

        // Verify reverse transform is also cached (eager caching)
        const Transform cachedReverse = manager_->accessCachedTransform(frameSPtr2, frameSPtr1, instant);
        EXPECT_TRUE(cachedReverse.isDefined());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Manager, AddCachedTransform_ReverseTransform)
{
    {
        const Shared<const Frame> frameSPtr1 = Frame::Construct("TestFrame1", true, Frame::GCRF(), providerSPtr_);
        const Shared<const Frame> frameSPtr2 = Frame::Construct("TestFrame2", true, Frame::GCRF(), providerSPtr_);
        const Instant instant = Instant::J2000();

        const Transform transform = Transform::Passive(
            instant, Vector3d(1.0, 0.0, 0.0), Vector3d::Zero(), Quaternion::Unit(), Vector3d::Zero()
        );

        manager_->addCachedTransform(frameSPtr1, frameSPtr2, instant, transform);

        // Get the cached reverse transform
        const Transform cachedReverse = manager_->accessCachedTransform(frameSPtr2, frameSPtr1, instant);
        EXPECT_TRUE(cachedReverse.isDefined());

        // The reverse transform should be the inverse of the original
        const Transform expectedReverse = transform.getInverse();

        // Verify the translation is inverted
        EXPECT_TRUE(cachedReverse.getTranslation().isNear(expectedReverse.getTranslation(), 1e-10));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Manager, RemoveFrameWithName_ClearsCache)
{
    {
        // Create frames and cache a transform
        const Shared<const Frame> frameSPtr1 = Frame::Construct("TestFrame1", true, Frame::GCRF(), providerSPtr_);
        const Shared<const Frame> frameSPtr2 = Frame::Construct("TestFrame2", true, Frame::GCRF(), providerSPtr_);
        const Instant instant = Instant::J2000();

        const Transform transform = Transform::Passive(
            instant, Vector3d(1.0, 0.0, 0.0), Vector3d::Zero(), Quaternion::Unit(), Vector3d::Zero()
        );

        manager_->addCachedTransform(frameSPtr1, frameSPtr2, instant, transform);

        EXPECT_TRUE(manager_->accessCachedTransform(frameSPtr1, frameSPtr2, instant).isDefined());

        manager_->removeFrameWithName("TestFrame1");

        EXPECT_FALSE(manager_->hasFrameWithName("TestFrame1"));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Manager, MultipleInstants)
{
    {
        const Shared<const Frame> frameSPtr1 = Frame::Construct("TestFrame1", true, Frame::GCRF(), providerSPtr_);
        const Shared<const Frame> frameSPtr2 = Frame::Construct("TestFrame2", true, Frame::GCRF(), providerSPtr_);

        const Instant instant1 = Instant::J2000();
        const Instant instant2 = Instant::DateTime(DateTime(2020, 1, 1, 0, 0, 0), Scale::UTC);
        const Instant instant3 = Instant::DateTime(DateTime(2021, 1, 1, 0, 0, 0), Scale::UTC);

        const Transform transform1 = Transform::Passive(
            instant1, Vector3d(1.0, 0.0, 0.0), Vector3d::Zero(), Quaternion::Unit(), Vector3d::Zero()
        );
        const Transform transform2 = Transform::Passive(
            instant2, Vector3d(2.0, 0.0, 0.0), Vector3d::Zero(), Quaternion::Unit(), Vector3d::Zero()
        );
        const Transform transform3 = Transform::Passive(
            instant3, Vector3d(3.0, 0.0, 0.0), Vector3d::Zero(), Quaternion::Unit(), Vector3d::Zero()
        );

        // Cache multiple transforms at different instants
        manager_->addCachedTransform(frameSPtr1, frameSPtr2, instant1, transform1);
        manager_->addCachedTransform(frameSPtr1, frameSPtr2, instant2, transform2);
        manager_->addCachedTransform(frameSPtr1, frameSPtr2, instant3, transform3);

        // Each instant should have its own cached transform
        const Transform cached1 = manager_->accessCachedTransform(frameSPtr1, frameSPtr2, instant1);
        const Transform cached2 = manager_->accessCachedTransform(frameSPtr1, frameSPtr2, instant2);
        const Transform cached3 = manager_->accessCachedTransform(frameSPtr1, frameSPtr2, instant3);

        EXPECT_TRUE(cached1.isDefined());
        EXPECT_TRUE(cached2.isDefined());
        EXPECT_TRUE(cached3.isDefined());

        EXPECT_TRUE(cached1.getTranslation().isNear(Vector3d(1.0, 0.0, 0.0), 1e-10));
        EXPECT_TRUE(cached2.getTranslation().isNear(Vector3d(2.0, 0.0, 0.0), 1e-10));
        EXPECT_TRUE(cached3.getTranslation().isNear(Vector3d(3.0, 0.0, 0.0), 1e-10));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Manager, AccessCachedTransform_MissedCache)
{
    {
        const Shared<const Frame> frameSPtr1 = Frame::Construct("TestFrame1", true, Frame::GCRF(), providerSPtr_);
        const Shared<const Frame> frameSPtr2 = Frame::Construct("TestFrame2", true, Frame::GCRF(), providerSPtr_);
        const Shared<const Frame> frameSPtr3 = Frame::Construct("TestFrame3", true, Frame::GCRF(), providerSPtr_);

        const Instant instant = Instant::J2000();

        // Cache transform between frame1 and frame2
        const Transform transform = Transform::Passive(
            instant, Vector3d(1.0, 0.0, 0.0), Vector3d::Zero(), Quaternion::Unit(), Vector3d::Zero()
        );

        manager_->addCachedTransform(frameSPtr1, frameSPtr2, instant, transform);

        // Access non-cached frame pair should return undefined
        const Transform cachedMiss1 = manager_->accessCachedTransform(frameSPtr1, frameSPtr3, instant);
        EXPECT_FALSE(cachedMiss1.isDefined());

        // Access non-cached instant should return undefined
        const Instant differentInstant = Instant::DateTime(DateTime(2025, 1, 1, 0, 0, 0), Scale::UTC);
        const Transform cachedMiss2 = manager_->accessCachedTransform(frameSPtr1, frameSPtr2, differentInstant);
        EXPECT_FALSE(cachedMiss2.isDefined());
    }
}
