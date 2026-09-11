/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Path.hpp>

#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/IERS/Finals2000A.hpp>
#include <OpenSpaceToolkit/Physics/Time/DateTime.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Time/Scale.hpp>

#include <Global.test.hpp>

using ostk::core::filesystem::File;
using ostk::core::filesystem::Path;

using ostk::mathematics::object::Vector2d;

using ostk::physics::coordinate::frame::provider::iers::Finals2000A;
using ostk::physics::time::DateTime;
using ostk::physics::time::Instant;
using ostk::physics::time::Scale;

class OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_Finals2000A : public ::testing::Test
{
   protected:
    const Finals2000A finals2000A_ = Finals2000A::Load(File::Path(
        Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/IERS/finals-2000A/finals2000A.data")
    ));
};

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_Finals2000A, GetCelestialPoleOffsetsAt)
{
    // Bulletin A dX, dY [mas] in the file: 2020-10-31: (0.239, 0.121), 2020-11-01: (0.209, 0.118)

    {
        const Vector2d celestialPoleOffsets_mas =
            finals2000A_.getCelestialPoleOffsetsAt(Instant::DateTime(DateTime(2020, 10, 31, 0, 0, 0), Scale::UTC));

        EXPECT_TRUE(celestialPoleOffsets_mas.isNear(Vector2d(0.239, 0.121), 1e-12))
            << celestialPoleOffsets_mas.toString();
    }

    // Linear interpolation between the daily values

    {
        const Vector2d celestialPoleOffsets_mas =
            finals2000A_.getCelestialPoleOffsetsAt(Instant::DateTime(DateTime(2020, 10, 31, 12, 0, 0), Scale::UTC));

        EXPECT_TRUE(celestialPoleOffsets_mas.isNear(Vector2d(0.224, 0.1195), 1e-12))
            << celestialPoleOffsets_mas.toString();
    }

    // Undefined where the file carries no dX, dY (far predictions)

    {
        const Vector2d celestialPoleOffsets_mas =
            finals2000A_.getCelestialPoleOffsetsAt(Instant::DateTime(DateTime(2025, 6, 1, 0, 0, 0), Scale::UTC));

        EXPECT_FALSE(celestialPoleOffsets_mas.isDefined());
    }

    // Outside the data span

    {
        EXPECT_THROW(
            finals2000A_.getCelestialPoleOffsetsAt(Instant::DateTime(DateTime(2030, 1, 1, 0, 0, 0), Scale::UTC)),
            ostk::core::error::RuntimeError
        );
    }

    {
        EXPECT_THROW(
            finals2000A_.getCelestialPoleOffsetsAt(Instant::Undefined()), ostk::core::error::runtime::Undefined
        );

        EXPECT_THROW(
            Finals2000A::Undefined().getCelestialPoleOffsetsAt(
                Instant::DateTime(DateTime(2020, 10, 31, 0, 0, 0), Scale::UTC)
            ),
            ostk::core::error::runtime::Undefined
        );
    }
}
