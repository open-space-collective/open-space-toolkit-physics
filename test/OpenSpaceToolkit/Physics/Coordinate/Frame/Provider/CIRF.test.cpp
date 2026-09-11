/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Directory.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Path.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/Quaternion.hpp>
#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/CIRF.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/IERS/Finals2000A.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/IERS/Manager.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Transform.hpp>
#include <OpenSpaceToolkit/Physics/Time/DateTime.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Time/Scale.hpp>

#include <Global.test.hpp>

using ostk::core::filesystem::Directory;
using ostk::core::filesystem::File;
using ostk::core::filesystem::Path;

using ostk::mathematics::geometry::d3::transformation::rotation::Quaternion;
using ostk::mathematics::object::Vector2d;
using ostk::mathematics::object::Vector3d;

using ostk::physics::coordinate::frame::provider::CIRF;
using ostk::physics::coordinate::frame::provider::iers::Finals2000A;
using ostk::physics::coordinate::frame::provider::iers::Manager;
using ostk::physics::coordinate::Transform;
using ostk::physics::time::DateTime;
using ostk::physics::time::Instant;
using ostk::physics::time::Scale;

// 1 milliarcsecond in radians
static const double MAS_IN_RAD = 4.848136811095359935899141e-9;

// These tests control which IERS data the provider sees: the IERS manager is put in Manual mode with an empty local
// repository, so that Finals 2000A data is available only once a test loads it explicitly.
class OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_CIRF : public ::testing::Test
{
   protected:
    void SetUp() override
    {
        initialMode_ = manager_.getMode();
        initialLocalRepository_ = manager_.getLocalRepository();

        if (!emptyLocalRepository_.exists())
        {
            emptyLocalRepository_.create();
        }

        manager_.reset();
        manager_.setMode(Manager::Mode::Manual);
        manager_.setLocalRepository(emptyLocalRepository_);
    }

    void TearDown() override
    {
        manager_.reset();
        manager_.setLocalRepository(initialLocalRepository_);
        manager_.setMode(initialMode_);

        if (emptyLocalRepository_.exists())
        {
            emptyLocalRepository_.remove();
        }
    }

    void loadFinals2000A()
    {
        manager_.loadFinals2000A(Finals2000A::Load(finals2000AFile_));
    }

    /// Direction of the CIRF z-axis, i.e. of the Celestial Intermediate Pole, expressed in GCRF: the unit vector
    /// (X, Y, Z) of the CIP coordinates.
    static Vector3d CipDirectionInGcrf(const Transform& aTransform_CIRF_GCRF)
    {
        return aTransform_CIRF_GCRF.getInverse().applyToVector({0.0, 0.0, 1.0});
    }

    const File finals2000AFile_ = File::Path(
        Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/IERS/finals-2000A/finals2000A.data")
    );

    Directory emptyLocalRepository_ = Directory::Path(Path::Parse("/tmp/open-space-toolkit-physics-cirf-test"));

    // Inside the Finals 2000A fixture span, where the observed celestial pole offsets are (0.239, 0.121) mas
    const Instant instant_ = Instant::DateTime(DateTime(2020, 10, 31, 0, 0, 0), Scale::UTC);

    const CIRF provider_;

    Manager& manager_ = Manager::Get();

    Manager::Mode initialMode_ = Manager::Mode::Automatic;
    Directory initialLocalRepository_ = Directory::Undefined();
};

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_CIRF, GetTransformAt)
{
    {
        EXPECT_THROW(provider_.getTransformAt(Instant::Undefined()), ostk::core::error::runtime::Undefined);
    }

    {
        const Transform transform = provider_.getTransformAt(instant_);

        EXPECT_EQ(instant_, transform.getInstant());

        EXPECT_TRUE(transform.getTranslation().isNear(Vector3d(0.0, 0.0, 0.0), 0.0));
        EXPECT_TRUE(transform.getVelocity().isNear(Vector3d(0.0, 0.0, 0.0), 0.0));
        EXPECT_TRUE(transform.getAngularVelocity().isNear(Vector3d(0.0, 0.0, 0.0), 0.0));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_CIRF, GetTransformAt_CelestialPoleOffsets)
{
    // Without IERS data, the IAU 2006/2000A model is used as is

    ASSERT_THROW(manager_.getCelestialPoleOffsetsAt(instant_), ostk::core::error::RuntimeError);

    const Vector3d cipDirection_GCRF_model = CipDirectionInGcrf(provider_.getTransformAt(instant_));

    // With IERS data, the observed celestial pole offsets are applied

    this->loadFinals2000A();

    const Vector2d celestialPoleOffsets_mas = manager_.getCelestialPoleOffsetsAt(instant_);

    ASSERT_TRUE(celestialPoleOffsets_mas.isDefined());
    ASSERT_GT(celestialPoleOffsets_mas.norm(), 0.1);  // [mas]

    const Vector3d cipDirection_GCRF_observed = CipDirectionInGcrf(provider_.getTransformAt(instant_));

    // The CIP direction in GCRF is (X, Y, Z): the offsets shift its first two components by exactly (dX, dY) [rad],
    // while the third one only changes to second order, by -(X dX + Y dY) / Z ~ 1e-12.

    const Vector3d shift = cipDirection_GCRF_observed - cipDirection_GCRF_model;

    EXPECT_NEAR(celestialPoleOffsets_mas.x() * MAS_IN_RAD, shift.x(), 1e-14) << shift.toString();
    EXPECT_NEAR(celestialPoleOffsets_mas.y() * MAS_IN_RAD, shift.y(), 1e-14) << shift.toString();
    EXPECT_NEAR(0.0, shift.z(), 1e-11) << shift.toString();
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_CIRF, GetTransformAt_CelestialPoleOffsetsUnavailable)
{
    // Instants for which the Finals 2000A fixture carries no celestial pole offsets: inside its span but not filled in
    // (far predictions), and beyond its span

    const Instant instantWithoutOffsets = Instant::DateTime(DateTime(2025, 6, 1, 0, 0, 0), Scale::UTC);
    const Instant instantBeyondSpan = Instant::DateTime(DateTime(2100, 1, 1, 0, 0, 0), Scale::UTC);

    // Without any IERS data

    const Quaternion q_CIRF_GCRF_withoutData_1 = provider_.getTransformAt(instantWithoutOffsets).getOrientation();
    const Quaternion q_CIRF_GCRF_withoutData_2 = provider_.getTransformAt(instantBeyondSpan).getOrientation();

    this->loadFinals2000A();

    EXPECT_FALSE(manager_.getCelestialPoleOffsetsAt(instantWithoutOffsets).isDefined());
    EXPECT_THROW(manager_.getCelestialPoleOffsetsAt(instantBeyondSpan), ostk::core::error::RuntimeError);

    // The model is used as is in both cases, exactly as without data

    EXPECT_EQ(q_CIRF_GCRF_withoutData_1, provider_.getTransformAt(instantWithoutOffsets).getOrientation());
    EXPECT_EQ(q_CIRF_GCRF_withoutData_2, provider_.getTransformAt(instantBeyondSpan).getOrientation());
}
