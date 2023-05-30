/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Containers/Array.hpp>
#include <OpenSpaceToolkit/Core/Containers/Table.hpp>
#include <OpenSpaceToolkit/Core/Containers/Tuple.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Path.hpp>
#include <OpenSpaceToolkit/Core/Types/Real.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Spherical/LLA.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Objects/CelestialBodies/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Units/Derived/Angle.hpp>

#include <Global.test.hpp>

TEST(OpenSpaceToolkit_Physics_Coordinate_Spherical_LLA, Constructor)
{
    using ostk::physics::units::Length;
    using ostk::physics::units::Angle;
    using ostk::physics::coord::Position;
    using ostk::physics::coord::spherical::LLA;

    {
        const Angle latitude = Angle::Degrees(10.0);
        const Angle longitude = Angle::Degrees(20.0);
        const Length altitude = Length::Meters(30.0);

        EXPECT_NO_THROW(LLA lla(latitude, longitude, altitude););
    }

    {
        EXPECT_ANY_THROW(LLA lla(Angle::Degrees(-91.0), Angle::Degrees(20.0), Length::Meters(30.0)););
        EXPECT_ANY_THROW(LLA lla(Angle::Degrees(+91.0), Angle::Degrees(20.0), Length::Meters(30.0)););

        EXPECT_ANY_THROW(LLA lla(Angle::Degrees(10.0), Angle::Degrees(-181.0), Length::Meters(30.0)););
        EXPECT_ANY_THROW(LLA lla(Angle::Degrees(10.0), Angle::Degrees(+181.0), Length::Meters(30.0)););
    }
}

TEST(OpenSpaceToolkit_Physics_Coordinate_Spherical_LLA, EqualToOperator)
{
    using ostk::physics::units::Length;
    using ostk::physics::units::Angle;
    using ostk::physics::coord::Position;
    using ostk::physics::coord::spherical::LLA;

    {
        const Angle latitude = Angle::Degrees(10.0);
        const Angle longitude = Angle::Degrees(20.0);
        const Length altitude = Length::Meters(30.0);

        const LLA lla = {latitude, longitude, altitude};

        EXPECT_TRUE(lla == lla);
    }

    {
        EXPECT_FALSE(
            LLA(Angle::Degrees(10.0), Angle::Degrees(20.0), Length::Meters(30.0)) ==
            LLA(Angle::Degrees(20.0), Angle::Degrees(20.0), Length::Meters(30.0))
        );
    }

    {
        const Angle latitude = Angle::Degrees(10.0);
        const Angle longitude = Angle::Degrees(20.0);
        const Length altitude = Length::Meters(30.0);

        const LLA lla = {latitude, longitude, altitude};

        EXPECT_FALSE(LLA::Undefined() == LLA::Undefined());
        EXPECT_FALSE(lla == LLA::Undefined());
        EXPECT_FALSE(LLA::Undefined() == lla);
    }
}

TEST(OpenSpaceToolkit_Physics_Coordinate_Spherical_LLA, NotEqualToOperator)
{
    using ostk::physics::units::Length;
    using ostk::physics::units::Angle;
    using ostk::physics::coord::Position;
    using ostk::physics::coord::spherical::LLA;

    {
        const Angle latitude = Angle::Degrees(10.0);
        const Angle longitude = Angle::Degrees(20.0);
        const Length altitude = Length::Meters(30.0);

        const LLA lla = {latitude, longitude, altitude};

        EXPECT_FALSE(lla != lla);
    }

    {
        EXPECT_TRUE(
            LLA(Angle::Degrees(10.0), Angle::Degrees(20.0), Length::Meters(30.0)) !=
            LLA(Angle::Degrees(20.0), Angle::Degrees(20.0), Length::Meters(30.0))
        );
    }

    {
        const Angle latitude = Angle::Degrees(10.0);
        const Angle longitude = Angle::Degrees(20.0);
        const Length altitude = Length::Meters(30.0);

        const LLA lla = {latitude, longitude, altitude};

        EXPECT_TRUE(LLA::Undefined() != LLA::Undefined());
        EXPECT_TRUE(lla != LLA::Undefined());
        EXPECT_TRUE(LLA::Undefined() != lla);
    }
}

TEST(OpenSpaceToolkit_Physics_Coordinate_Spherical_LLA, StreamOperator)
{
    using ostk::physics::units::Length;
    using ostk::physics::units::Angle;
    using ostk::physics::coord::Position;
    using ostk::physics::coord::spherical::LLA;

    {
        const Angle latitude = Angle::Degrees(10.0);
        const Angle longitude = Angle::Degrees(20.0);
        const Length altitude = Length::Meters(30.0);

        const LLA lla = {latitude, longitude, altitude};

        testing::internal::CaptureStdout();

        EXPECT_NO_THROW(std::cout << lla << std::endl);

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    }
}

TEST(OpenSpaceToolkit_Physics_Coordinate_Spherical_LLA, IsDefined)
{
    using ostk::physics::units::Length;
    using ostk::physics::units::Angle;
    using ostk::physics::coord::Position;
    using ostk::physics::coord::spherical::LLA;

    {
        const Angle latitude = Angle::Degrees(10.0);
        const Angle longitude = Angle::Degrees(20.0);
        const Length altitude = Length::Meters(30.0);

        const LLA lla = {latitude, longitude, altitude};

        EXPECT_TRUE(lla.isDefined());
    }

    {
        EXPECT_FALSE(LLA::Undefined().isDefined());
    }
}

TEST(OpenSpaceToolkit_Physics_Coordinate_Spherical_LLA, GetLatitude)
{
    using ostk::physics::units::Length;
    using ostk::physics::units::Angle;
    using ostk::physics::coord::Position;
    using ostk::physics::coord::spherical::LLA;

    {
        const Angle latitude = Angle::Degrees(10.0);
        const Angle longitude = Angle::Degrees(20.0);
        const Length altitude = Length::Meters(30.0);

        const LLA lla = {latitude, longitude, altitude};

        EXPECT_EQ(latitude, lla.getLatitude());
    }

    {
        EXPECT_ANY_THROW(LLA::Undefined().getLatitude());
    }
}

TEST(OpenSpaceToolkit_Physics_Coordinate_Spherical_LLA, GetLongitude)
{
    using ostk::physics::units::Length;
    using ostk::physics::units::Angle;
    using ostk::physics::coord::Position;
    using ostk::physics::coord::spherical::LLA;

    {
        const Angle latitude = Angle::Degrees(10.0);
        const Angle longitude = Angle::Degrees(20.0);
        const Length altitude = Length::Meters(30.0);

        const LLA lla = {latitude, longitude, altitude};

        EXPECT_EQ(longitude, lla.getLongitude());
    }

    {
        EXPECT_ANY_THROW(LLA::Undefined().getLongitude());
    }
}

TEST(OpenSpaceToolkit_Physics_Coordinate_Spherical_LLA, GetAltitude)
{
    using ostk::physics::units::Length;
    using ostk::physics::units::Angle;
    using ostk::physics::coord::Position;
    using ostk::physics::coord::spherical::LLA;

    {
        const Angle latitude = Angle::Degrees(10.0);
        const Angle longitude = Angle::Degrees(20.0);
        const Length altitude = Length::Meters(30.0);

        const LLA lla = {latitude, longitude, altitude};

        EXPECT_EQ(altitude, lla.getAltitude());
    }

    {
        EXPECT_ANY_THROW(LLA::Undefined().getAltitude());
    }
}

TEST(OpenSpaceToolkit_Physics_Coordinate_Spherical_LLA, ToVector)
{
    using ostk::math::obj::Vector3d;

    using ostk::physics::units::Length;
    using ostk::physics::units::Angle;
    using ostk::physics::coord::Position;
    using ostk::physics::coord::spherical::LLA;

    {
        const Angle latitude = Angle::Degrees(10.0);
        const Angle longitude = Angle::Degrees(20.0);
        const Length altitude = Length::Meters(30.0);

        const LLA lla = {latitude, longitude, altitude};

        EXPECT_EQ(Vector3d(10.0, 20.0, 30.0), lla.toVector());
    }

    {
        EXPECT_ANY_THROW(LLA::Undefined().toVector());
    }
}

TEST(OpenSpaceToolkit_Physics_Coordinate_Spherical_LLA, ToCartesian)
{
    using ostk::physics::units::Length;
    using ostk::physics::units::Angle;
    using ostk::physics::coord::Position;
    using ostk::physics::coord::spherical::LLA;

    using ostk::core::types::Shared;
    using ostk::core::types::Real;
    using ostk::core::types::String;
    using ostk::core::ctnr::Tuple;
    using ostk::core::ctnr::Array;
    using ostk::core::ctnr::Table;
    using ostk::core::fs::Path;
    using ostk::core::fs::File;

    using ostk::math::obj::Vector3d;

    using ostk::physics::units::Length;
    using ostk::physics::units::Angle;
    using ostk::physics::time::Scale;
    using ostk::physics::time::Instant;
    using ostk::physics::time::DateTime;
    using ostk::physics::coord::Position;
    using ostk::physics::coord::spherical::LLA;
    using ostk::physics::coord::Frame;
    using ostk::physics::env::obj::celest::Earth;

    {
        const Array<Tuple<File, Length>> referenceScenarios = {
            {File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Spherical/LLA/ToCartesian/LLA 1.csv")
             ),
             Length::Meters(1.0)}};

        for (const auto& referenceScenario : referenceScenarios)
        {
            // Reference data setup

            const File referenceDataFile = std::get<0>(referenceScenario);
            const Length toleranceLength = std::get<1>(referenceScenario);

            const Table referenceData = Table::Load(referenceDataFile, Table::Format::CSV, true);

            // Test

            const Earth earth = Earth::Default();

            for (const auto& referenceRow : referenceData)
            {
                const Instant instant = Instant::DateTime(DateTime::Parse(referenceRow[0].accessString()), Scale::UTC);

                const Vector3d reference_position_ITRF = {
                    referenceRow[1].accessReal(), referenceRow[2].accessReal(), referenceRow[3].accessReal()};

                const Angle reference_latitude = Angle::Degrees(referenceRow[4].accessReal());
                const Angle reference_longitude = Angle::Degrees(referenceRow[5].accessReal());
                const Length reference_altitude = Length::Meters(referenceRow[6].accessReal());

                const LLA lla = {reference_latitude, reference_longitude, reference_altitude};

                const Vector3d position_ITRF = lla.toCartesian(Earth::EquatorialRadius, Earth::Flattening);

                {
                    const Real error_m = (position_ITRF - reference_position_ITRF).norm();

                    ASSERT_TRUE(position_ITRF.isNear(reference_position_ITRF, toleranceLength.inMeters()))
                        << String::Format(
                               "{} - {} [m] ~ {} [m] ? {} [m]",
                               instant.toString(),
                               reference_position_ITRF.toString(),
                               position_ITRF.toString(),
                               error_m.toString()
                           );
                }
            }
        }
    }

    {
        EXPECT_ANY_THROW(LLA::Undefined().toCartesian(Length::Undefined(), Real::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Physics_Coordinate_Spherical_LLA, ToString)
{
    using ostk::physics::units::Length;
    using ostk::physics::units::Angle;
    using ostk::physics::coord::Position;
    using ostk::physics::coord::spherical::LLA;

    {
        const Angle latitude = Angle::Degrees(10.0);
        const Angle longitude = Angle::Degrees(20.0);
        const Length altitude = Length::Meters(30.0);

        const LLA lla = {latitude, longitude, altitude};

        EXPECT_EQ("[10.0 [deg], 20.0 [deg], 30.0 [m]]", lla.toString());
    }

    {
        EXPECT_ANY_THROW(LLA::Undefined().toString());
    }
}

TEST(OpenSpaceToolkit_Physics_Coordinate_Spherical_LLA, Undefined)
{
    using ostk::physics::coord::spherical::LLA;

    {
        EXPECT_NO_THROW(LLA::Undefined());
    }
}

TEST(OpenSpaceToolkit_Physics_Coordinate_Spherical_LLA, Vector)
{
    using ostk::math::obj::Vector3d;

    using ostk::physics::units::Length;
    using ostk::physics::units::Angle;
    using ostk::physics::coord::Position;
    using ostk::physics::coord::spherical::LLA;

    {
        const Vector3d vector = {10.0, 20.0, 30.0};

        const Angle latitude = Angle::Degrees(10.0);
        const Angle longitude = Angle::Degrees(20.0);
        const Length altitude = Length::Meters(30.0);

        const LLA lla = {latitude, longitude, altitude};

        EXPECT_EQ(lla, LLA::Vector(vector));
    }

    {
        EXPECT_ANY_THROW(LLA::Vector(Vector3d::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Physics_Coordinate_Spherical_LLA, Cartesian)
{
    using ostk::core::types::Shared;
    using ostk::core::types::Real;
    using ostk::core::types::String;
    using ostk::core::ctnr::Tuple;
    using ostk::core::ctnr::Array;
    using ostk::core::ctnr::Table;
    using ostk::core::fs::Path;
    using ostk::core::fs::File;

    using ostk::math::obj::Vector3d;

    using ostk::physics::units::Length;
    using ostk::physics::units::Angle;
    using ostk::physics::time::Scale;
    using ostk::physics::time::Instant;
    using ostk::physics::time::DateTime;
    using ostk::physics::coord::Position;
    using ostk::physics::coord::spherical::LLA;
    using ostk::physics::coord::Frame;
    using ostk::physics::env::obj::celest::Earth;

    {
        const Array<Tuple<File, Angle, Length>> referenceScenarios = {
            {File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Spherical/LLA/Cartesian/LLA 1.csv")),
             Angle::Arcseconds(0.01),
             Length::Meters(1.0)}};

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
                const Instant instant = Instant::DateTime(DateTime::Parse(referenceRow[0].accessString()), Scale::UTC);

                const Vector3d reference_position_ITRF = {
                    referenceRow[1].accessReal(), referenceRow[2].accessReal(), referenceRow[3].accessReal()};

                const Angle reference_latitude = Angle::Degrees(referenceRow[4].accessReal());
                const Angle reference_longitude = Angle::Degrees(referenceRow[5].accessReal());
                const Length reference_altitude = Length::Meters(referenceRow[6].accessReal());

                const LLA lla = LLA::Cartesian(reference_position_ITRF, Earth::EquatorialRadius, Earth::Flattening);

                {
                    const Real reference_latitude_deg = reference_latitude.inDegrees();
                    const Real latitude_deg = lla.getLatitude().inDegrees();
                    const Real tolerance_deg = toleranceAngle.inDegrees();

                    const Real error_deg = (latitude_deg - reference_latitude_deg).abs();

                    ASSERT_TRUE(latitude_deg.isNear(reference_latitude_deg, tolerance_deg)) << String::Format(
                        "{} - {} [deg] ~ {} [deg] ? {} [deg]",
                        instant.toString(),
                        reference_latitude_deg.toString(),
                        latitude_deg.toString(),
                        error_deg.toString()
                    );
                }

                {
                    const Real reference_longitude_deg = reference_longitude.inDegrees();
                    const Real longitude_deg = lla.getLongitude().inDegrees();
                    const Real tolerance_deg = toleranceAngle.inDegrees();

                    const Real error_deg = (longitude_deg - reference_longitude_deg).abs();

                    ASSERT_TRUE(longitude_deg.isNear(reference_longitude_deg, tolerance_deg)) << String::Format(
                        "{} - {} [deg] ~ {} [deg] ? {} [deg]",
                        instant.toString(),
                        reference_longitude_deg.toString(),
                        longitude_deg.toString(),
                        error_deg.toString()
                    );
                }

                {
                    const Real reference_altitude_m = reference_altitude.inMeters();
                    const Real altitude_m = lla.getAltitude().inMeters();
                    const Real tolerance_m = toleranceLength.inMeters();

                    const Real error_m = (altitude_m - reference_altitude_m).abs();

                    ASSERT_TRUE(altitude_m.isNear(reference_altitude_m, tolerance_m)) << String::Format(
                        "{} - {} [m] ~ {} [m] ? {} [m]",
                        instant.toString(),
                        reference_altitude_m.toString(),
                        altitude_m.toString(),
                        error_m.toString()
                    );
                }
            }
        }
    }

    {
        EXPECT_ANY_THROW(LLA::Cartesian(Vector3d::Undefined(), Length::Undefined(), Real::Undefined()));
    }
}
