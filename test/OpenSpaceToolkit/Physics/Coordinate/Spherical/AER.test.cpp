/// Apache License 2.0

#include <cmath>

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Container/Table.hpp>
#include <OpenSpaceToolkit/Core/Container/Tuple.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Path.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Spherical/AER.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Spherical/LLA.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Object/Celestial/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Unit/Derived/Angle.hpp>
#include <OpenSpaceToolkit/Physics/Utility/String.hpp>

#include <Global.test.hpp>

using ostk::core::container::Array;
using ostk::core::container::Table;
using ostk::core::container::Tuple;
using ostk::core::filesystem::File;
using ostk::core::filesystem::Path;
using ostk::core::type::Shared;
using ostk::core::type::String;

using ostk::mathematics::object::Vector3d;

using ostk::physics::coordinate::Frame;
using ostk::physics::coordinate::Position;
using ostk::physics::coordinate::spherical::AER;
using ostk::physics::coordinate::spherical::LLA;
using ostk::physics::environment::object::celestial::Earth;
using ostk::physics::time::DateTime;
using ostk::physics::time::Instant;
using ostk::physics::time::Scale;
using ostk::physics::unit::Angle;
using ostk::physics::unit::Length;
using EarthGravitationalModel = ostk::physics::environment::gravitational::Earth;
using ostk::physics::utility::DoubleToString;

class OpenSpaceToolkit_Physics_Coordinate_Spherical_AER : public ::testing::Test
{
   protected:
    const Angle azimuth_ = Angle::Degrees(10.0);
    const Angle elevation_ = Angle::Degrees(20.0);
    const Length range_ = Length::Meters(30.0);

    AER aer_ = AER(azimuth_, elevation_, range_);
};

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Spherical_AER, Constructor)
{
    {
        EXPECT_ANY_THROW(AER aer(Angle::Degrees(-1.0), Angle::Degrees(20.0), Length::Meters(30.0)););
        EXPECT_ANY_THROW(AER aer(Angle::Degrees(+361.0), Angle::Degrees(20.0), Length::Meters(30.0)););

        EXPECT_ANY_THROW(AER aer(Angle::Degrees(10.0), Angle::Degrees(-91.0), Length::Meters(30.0)););
        EXPECT_ANY_THROW(AER aer(Angle::Degrees(10.0), Angle::Degrees(+91.0), Length::Meters(30.0)););

        EXPECT_ANY_THROW(AER aer(Angle::Degrees(10.0), Angle::Degrees(20.0), Length::Meters(-30.0)););
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Spherical_AER, EqualToOperator)
{
    {
        EXPECT_TRUE(aer_ == aer_);
    }

    {
        EXPECT_FALSE(
            AER(Angle::Degrees(10.0), Angle::Degrees(20.0), Length::Meters(30.0)) ==
            AER(Angle::Degrees(20.0), Angle::Degrees(20.0), Length::Meters(30.0))
        );
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Spherical_AER, NotEqualToOperator)
{
    {
        EXPECT_FALSE(aer_ != aer_);
    }

    {
        EXPECT_TRUE(
            AER(Angle::Degrees(10.0), Angle::Degrees(20.0), Length::Meters(30.0)) !=
            AER(Angle::Degrees(20.0), Angle::Degrees(20.0), Length::Meters(30.0))
        );
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Spherical_AER, StreamOperator)
{
    {
        testing::internal::CaptureStdout();

        EXPECT_NO_THROW(std::cout << aer_ << std::endl);

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Spherical_AER, GetAzimuth)
{
    {
        EXPECT_EQ(azimuth_, aer_.getAzimuth());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Spherical_AER, GetElevation)
{
    {
        EXPECT_EQ(elevation_, aer_.getElevation());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Spherical_AER, GetRange)
{
    {
        EXPECT_EQ(range_, aer_.getRange());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Spherical_AER, ToVector)
{
    using ostk::mathematics::object::Vector3d;

    {
        EXPECT_EQ(Vector3d(10.0, 20.0, 30.0), aer_.toVector());
    }
}

// TEST_F (OpenSpaceToolkit_Physics_Coordinate_Spherical_AER, ToCartesian)
// {

//     using ostk::physics::unit::Length ;
//     using ostk::physics::unit::Angle ;
//     using ostk::physics::coordinate::Position ;
//     using ostk::physics::coordinate::spherical::AER ;

//     {

//         const Angle azimuth = Angle::Degrees(10.0) ;
//         const Angle elevation = Angle::Degrees(20.0) ;
//         const Length range = Length::Meters(30.0) ;

//         const AER aer_ = { azimuth, elevation, range } ;

//         FAIL() ;

//     }

//     {

//     }

// }

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Spherical_AER, ToString)
{
    {
        EXPECT_EQ("[10.0 [deg], 20.0 [deg], 30.0 [m]]", aer_.toString());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Spherical_AER, Vector)
{
    {
        const Vector3d vector = {10.0, 20.0, 30.0};

        EXPECT_EQ(aer_, AER::Vector(vector));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Spherical_AER, FromPositionToPosition)
{
    {
        const Array<Tuple<File, Angle, Length>> referenceScenarios = {
            {File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Spherical/AER/"
                                    "FromPositionToPosition/AER NoLightTimeDelay.csv")),
             Angle::Arcseconds(0.01),
             Length::Meters(0.01)},
            {File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Spherical/AER/"
                                    "FromPositionToPosition/AER WithLightTimeDelay.csv")),
             Angle::Arcseconds(100.0),
             Length::Meters(20.0)}  // [TBI]
        };

        for (const auto& referenceScenario : referenceScenarios)
        {
            // Reference data setup

            const File referenceDataFile = std::get<0>(referenceScenario);
            const Angle toleranceAngle = std::get<1>(referenceScenario);
            const Length toleranceLength = std::get<2>(referenceScenario);

            const Table referenceData = Table::Load(referenceDataFile, Table::Format::CSV, true);

            // Test

            const Earth earth = Earth::Default();

            for (const auto& referenceRow : referenceData)
            {
                const Instant instant = Instant::DateTime(DateTime::Parse(referenceRow[0].getString()), Scale::UTC);

                const Vector3d reference_fromPosition_ITRF = {
                    referenceRow[1].getReal(), referenceRow[2].getReal(), referenceRow[3].getReal()
                };
                const Vector3d reference_fromPosition_LLA = {
                    referenceRow[4].getReal(), referenceRow[5].getReal(), referenceRow[6].getReal()
                };
                const Vector3d reference_toPosition_ITRF = {
                    referenceRow[7].getReal(), referenceRow[8].getReal(), referenceRow[9].getReal()
                };
                const Vector3d reference_toPosition_LLA = {
                    referenceRow[10].getReal(), referenceRow[11].getReal(), referenceRow[12].getReal()
                };

                (void)reference_fromPosition_LLA;
                (void)reference_toPosition_LLA;

                const Angle reference_azimuth = Angle::Degrees(referenceRow[13].getReal());
                const Angle reference_elevation = Angle::Degrees(referenceRow[14].getReal());
                const Length reference_range = Length::Meters(referenceRow[15].getReal());

                const Position fromPosition_ITRF = Position::Meters(reference_fromPosition_ITRF, Frame::ITRF());
                const Position toPosition_ITRF = Position::Meters(reference_toPosition_ITRF, Frame::ITRF());

                const LLA fromLla = LLA::Cartesian(
                    fromPosition_ITRF.getCoordinates(),
                    EarthGravitationalModel::EGM2008.equatorialRadius_,
                    EarthGravitationalModel::EGM2008.flattening_
                );

                const Shared<const Frame> nedFrameSPtr = earth.getFrameAt(fromLla, Earth::FrameType::NED);

                const Position fromPosition_NED = fromPosition_ITRF.inFrame(nedFrameSPtr, instant);
                const Position toPosition_NED = toPosition_ITRF.inFrame(nedFrameSPtr, instant);

                const AER aer = AER::FromPositionToPosition(fromPosition_NED, toPosition_NED);

                {
                    const double reference_azimuth_deg = reference_azimuth.inDegrees();
                    const double azimuth_deg = aer.getAzimuth().inDegrees();
                    const double tolerance_deg = toleranceAngle.inDegrees();

                    const double error_deg = std::abs(azimuth_deg - reference_azimuth_deg);

                    ASSERT_TRUE(std::abs(azimuth_deg - reference_azimuth_deg) <= tolerance_deg) << String::Format(
                        "{} - {} [deg] ~ {} [deg] ? {} [deg]",
                        instant.toString(),
                        DoubleToString(reference_azimuth_deg),
                        DoubleToString(azimuth_deg),
                        DoubleToString(error_deg)
                    );
                }

                {
                    const double reference_elevation_deg = reference_elevation.inDegrees();
                    const double elevation_deg = aer.getElevation().inDegrees();
                    const double tolerance_deg = toleranceAngle.inDegrees();

                    const double error_deg = std::abs(elevation_deg - reference_elevation_deg);

                    ASSERT_TRUE(std::abs(elevation_deg - reference_elevation_deg) <= tolerance_deg) << String::Format(
                        "{} - {} [deg] ~ {} [deg] ? {} [deg]",
                        instant.toString(),
                        DoubleToString(reference_elevation_deg),
                        DoubleToString(elevation_deg),
                        DoubleToString(error_deg)
                    );
                }

                {
                    const double reference_range_m = reference_range.inMeters();
                    const double range_m = aer.getRange().inMeters();
                    const double tolerance_m = toleranceLength.inMeters();

                    const double error_m = std::abs(range_m - reference_range_m);

                    ASSERT_TRUE(std::abs(range_m - reference_range_m) <= tolerance_m) << String::Format(
                        "{} - {} [m] ~ {} [m] ? {} [m]",
                        instant.toString(),
                        DoubleToString(reference_range_m),
                        DoubleToString(range_m),
                        DoubleToString(error_m)
                    );
                }
            }
        }
    }

    {
        const Position fromPosition = Position::Meters({0.0, 0.0, +0.0}, Frame::ITRF());
        const Position toPosition = Position::Meters({0.0, 0.0, -1.0}, Frame::ITRF());

        const AER aer = AER::FromPositionToPosition(fromPosition, toPosition);

        const AER referenceAer = {Angle::Degrees(0.0), Angle::Degrees(+90.0), Length::Meters(1.0)};

        EXPECT_EQ(referenceAer, aer);
    }

    {
        const Position fromPosition = Position::Meters({0.0, 0.0, +0.0}, Frame::ITRF());
        const Position toPosition = Position::Meters({0.0, 0.0, -1.0}, Frame::ITRF());

        const AER aer = AER::FromPositionToPosition(fromPosition, toPosition, false);

        const AER referenceAer = {Angle::Degrees(0.0), Angle::Degrees(-90.0), Length::Meters(1.0)};

        EXPECT_EQ(referenceAer, aer);
    }

    {
        const Position fromPosition = Position::Meters({0.0, 0.0, 0.0}, Frame::ITRF());
        const Position toPosition = Position::Meters({0.0, 0.0, 0.0}, Frame::ITRF());

        const AER aer = AER::FromPositionToPosition(fromPosition, toPosition);

        const AER referenceAer = {Angle::Degrees(0.0), Angle::Degrees(0.0), Length::Meters(0.0)};

        EXPECT_EQ(referenceAer, aer);
    }
}
