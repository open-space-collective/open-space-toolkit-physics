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
using ostk::physics::coord::Position;
using ostk::physics::coord::spherical::LLA;
using ostk::physics::time::Scale;
using ostk::physics::time::Instant;
using ostk::physics::time::DateTime;
using ostk::physics::coord::Frame;
using ostk::physics::env::obj::celest::Earth;
using EarthGravitational = ostk::physics::environment::gravitational::Earth;

class OpenSpaceToolkit_Physics_Coordinate_Spherical_LLA : public ::testing::Test
{
   protected:
    void SetUp() override
    {
        this->lla_ = LLA(latitude_, longitude_, altitude_);
    }

    const Angle latitude_ = Angle::Degrees(10.0);
    const Angle longitude_ = Angle::Degrees(20.0);
    const Length altitude_ = Length::Meters(30.0);

    LLA lla_ = LLA::Undefined();
};

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Spherical_LLA, Constructor)
{
    {
        EXPECT_ANY_THROW(LLA lla(Angle::Degrees(-91.0), Angle::Degrees(20.0), Length::Meters(30.0)););
        EXPECT_ANY_THROW(LLA lla(Angle::Degrees(+91.0), Angle::Degrees(20.0), Length::Meters(30.0)););

        EXPECT_ANY_THROW(LLA lla(Angle::Degrees(10.0), Angle::Degrees(-181.0), Length::Meters(30.0)););
        EXPECT_ANY_THROW(LLA lla(Angle::Degrees(10.0), Angle::Degrees(+181.0), Length::Meters(30.0)););
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Spherical_LLA, EqualToOperator)
{
    {
        EXPECT_TRUE(lla_ == lla_);
    }

    {
        EXPECT_FALSE(
            LLA(Angle::Degrees(10.0), Angle::Degrees(20.0), Length::Meters(30.0)) ==
            LLA(Angle::Degrees(20.0), Angle::Degrees(20.0), Length::Meters(30.0))
        );
    }

    {
        const LLA lla = {latitude_, longitude_, altitude_};

        EXPECT_FALSE(LLA::Undefined() == LLA::Undefined());
        EXPECT_FALSE(lla_ == LLA::Undefined());
        EXPECT_FALSE(LLA::Undefined() == lla_);
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Spherical_LLA, NotEqualToOperator)
{
    {
        EXPECT_FALSE(lla_ != lla_);
    }

    {
        EXPECT_TRUE(
            LLA(Angle::Degrees(10.0), Angle::Degrees(20.0), Length::Meters(30.0)) !=
            LLA(Angle::Degrees(20.0), Angle::Degrees(20.0), Length::Meters(30.0))
        );
    }

    {
        EXPECT_TRUE(LLA::Undefined() != LLA::Undefined());
        EXPECT_TRUE(lla_ != LLA::Undefined());
        EXPECT_TRUE(LLA::Undefined() != lla_);
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Spherical_LLA, StreamOperator)
{
    {
        testing::internal::CaptureStdout();

        EXPECT_NO_THROW(std::cout << lla_ << std::endl);

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Spherical_LLA, IsDefined)
{
    {
        EXPECT_TRUE(lla_.isDefined());
    }

    {
        EXPECT_FALSE(LLA::Undefined().isDefined());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Spherical_LLA, GetLatitude)
{
    {
        EXPECT_EQ(latitude_, lla_.getLatitude());
    }

    {
        EXPECT_ANY_THROW(LLA::Undefined().getLatitude());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Spherical_LLA, GetLongitude)
{
    {
        EXPECT_EQ(longitude_, lla_.getLongitude());
    }

    {
        EXPECT_ANY_THROW(LLA::Undefined().getLongitude());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Spherical_LLA, GetAltitude)
{
    {
        EXPECT_EQ(altitude_, lla_.getAltitude());
    }

    {
        EXPECT_ANY_THROW(LLA::Undefined().getAltitude());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Spherical_LLA, CalculateDistanceTo_Spherical)
{
    const Earth sphericalEarth = Earth::Spherical();

    const Length sphericalEarthEquatorialRadius = sphericalEarth.getEquatorialRadius();
    const Real sphericalEarthFlattening = sphericalEarth.getFlattening();

    const double pi = 3.14159265358979323846;

    {
        const Length distance =
            lla_.calculateDistanceTo(lla_, sphericalEarthEquatorialRadius, sphericalEarthFlattening);

        EXPECT_EQ(distance.inMeters(), 0.0);
    }

    {
        const LLA llaEquatorial0 = LLA(Angle::Degrees(0.0), Angle::Degrees(0.0), Length::Meters(1.0));
        const LLA llaEquatorial90 = LLA(Angle::Degrees(0.0), Angle::Degrees(90.0), Length::Meters(1.0));

        const Length distanceQuarterEquatorialOneDirection = llaEquatorial0.calculateDistanceTo(
            llaEquatorial90, sphericalEarthEquatorialRadius, sphericalEarthFlattening
        );
        const Length distanceQuarterEquatorialOtherDirection = llaEquatorial90.calculateDistanceTo(
            llaEquatorial0, sphericalEarthEquatorialRadius, sphericalEarthFlattening
        );

        EXPECT_EQ(distanceQuarterEquatorialOneDirection, distanceQuarterEquatorialOtherDirection);
        EXPECT_EQ(
            distanceQuarterEquatorialOneDirection.inMeters(), pi * sphericalEarthEquatorialRadius.inMeters() / 2.0
        );
    }

    {
        const LLA llaEquatorial0 = LLA(Angle::Degrees(0.0), Angle::Degrees(0.0), Length::Meters(1.0));
        const LLA llaEquatorial180 = LLA(Angle::Degrees(0.0), Angle::Degrees(180.0), Length::Meters(1.0));

        const Length distanceSemiEquatorialOneDirection = llaEquatorial0.calculateDistanceTo(
            llaEquatorial180, sphericalEarthEquatorialRadius, sphericalEarthFlattening
        );
        const Length distanceSemiEquatorialOtherDirection = llaEquatorial180.calculateDistanceTo(
            llaEquatorial0, sphericalEarthEquatorialRadius, sphericalEarthFlattening
        );

        EXPECT_EQ(distanceSemiEquatorialOneDirection, distanceSemiEquatorialOtherDirection);
        EXPECT_EQ(distanceSemiEquatorialOneDirection.inMeters(), pi * sphericalEarthEquatorialRadius.inMeters());
    }

    {
        const LLA llaNorthPole = LLA(Angle::Degrees(90.0), Angle::Degrees(15.0), Length::Meters(1.0));
        const LLA llaSouthPole = LLA(Angle::Degrees(-90.0), Angle::Degrees(15.0), Length::Meters(1.0));

        const Length distanceSemiPolesOneDirection =
            llaNorthPole.calculateDistanceTo(llaSouthPole, sphericalEarthEquatorialRadius, sphericalEarthFlattening);
        const Length distanceSemiPolesOtherDirection =
            llaSouthPole.calculateDistanceTo(llaNorthPole, sphericalEarthEquatorialRadius, sphericalEarthFlattening);

        EXPECT_EQ(distanceSemiPolesOneDirection, distanceSemiPolesOtherDirection);
        EXPECT_EQ(distanceSemiPolesOneDirection.inMeters(), pi * sphericalEarthEquatorialRadius.inMeters());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Spherical_LLA, ToVector)
{
    {
        EXPECT_EQ(Vector3d(10.0, 20.0, 30.0), lla_.toVector());
    }

    {
        EXPECT_ANY_THROW(LLA::Undefined().toVector());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Spherical_LLA, ToCartesian)
{
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

                const Vector3d position_ITRF = lla.toCartesian(
                    EarthGravitational::EGM2008Parameters.equatorialRadius_,
                    EarthGravitational::EGM2008Parameters.flattening_
                );

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

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Spherical_LLA, ToString)
{
    {
        EXPECT_EQ("[10.0 [deg], 20.0 [deg], 30.0 [m]]", lla_.toString());
    }

    {
        EXPECT_ANY_THROW(LLA::Undefined().toString());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Spherical_LLA, Undefined)
{
    {
        EXPECT_NO_THROW(LLA::Undefined());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Spherical_LLA, Vector)
{
    {
        const Vector3d vector = {10.0, 20.0, 30.0};

        EXPECT_EQ(lla_, LLA::Vector(vector));
    }

    {
        EXPECT_ANY_THROW(LLA::Vector(Vector3d::Undefined()));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Spherical_LLA, Cartesian)
{
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

                const LLA lla = LLA::Cartesian(
                    reference_position_ITRF,
                    EarthGravitational::EGM2008Parameters.equatorialRadius_,
                    EarthGravitational::EGM2008Parameters.flattening_
                );

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

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Spherical_LLA, DistanceBetween_Spherical)
{
    const Earth sphericalEarth = Earth::Spherical();

    const Length sphericalEarthEquatorialRadius = sphericalEarth.getEquatorialRadius();
    const Real sphericalEarthFlattening = sphericalEarth.getFlattening();

    const double pi = 3.14159265358979323846;

    {
        const Length distance =
            LLA::DistanceBetween(lla_, lla_, sphericalEarthEquatorialRadius, sphericalEarthFlattening);

        EXPECT_EQ(distance.inMeters(), 0.0);
    }

    {
        const LLA llaEquatorial0 = LLA(Angle::Degrees(0.0), Angle::Degrees(0.0), Length::Meters(1.0));
        const LLA llaEquatorial90 = LLA(Angle::Degrees(0.0), Angle::Degrees(90.0), Length::Meters(1.0));

        const Length distanceQuarterEquatorialOneDirection = LLA::DistanceBetween(
            llaEquatorial0, llaEquatorial90, sphericalEarthEquatorialRadius, sphericalEarthFlattening
        );
        const Length distanceQuarterEquatorialOtherDirection = LLA::DistanceBetween(
            llaEquatorial90, llaEquatorial0, sphericalEarthEquatorialRadius, sphericalEarthFlattening
        );

        EXPECT_EQ(distanceQuarterEquatorialOneDirection, distanceQuarterEquatorialOtherDirection);
        EXPECT_EQ(
            distanceQuarterEquatorialOneDirection.inMeters(), pi * sphericalEarthEquatorialRadius.inMeters() / 2.0
        );
    }

    {
        const LLA llaEquatorial0 = LLA(Angle::Degrees(0.0), Angle::Degrees(0.0), Length::Meters(1.0));
        const LLA llaEquatorial180 = LLA(Angle::Degrees(0.0), Angle::Degrees(180.0), Length::Meters(1.0));

        const Length distanceSemiEquatorialOneDirection = LLA::DistanceBetween(
            llaEquatorial0, llaEquatorial180, sphericalEarthEquatorialRadius, sphericalEarthFlattening
        );
        const Length distanceSemiEquatorialOtherDirection = LLA::DistanceBetween(
            llaEquatorial180, llaEquatorial0, sphericalEarthEquatorialRadius, sphericalEarthFlattening
        );

        EXPECT_EQ(distanceSemiEquatorialOneDirection, distanceSemiEquatorialOtherDirection);
        EXPECT_EQ(distanceSemiEquatorialOneDirection.inMeters(), pi * sphericalEarthEquatorialRadius.inMeters());
    }

    {
        const LLA llaNorthPole = LLA(Angle::Degrees(90.0), Angle::Degrees(15.0), Length::Meters(1.0));
        const LLA llaSouthPole = LLA(Angle::Degrees(-90.0), Angle::Degrees(15.0), Length::Meters(1.0));

        const Length distanceSemiPolesOneDirection =
            LLA::DistanceBetween(llaNorthPole, llaSouthPole, sphericalEarthEquatorialRadius, sphericalEarthFlattening);
        const Length distanceSemiPolesOtherDirection =
            LLA::DistanceBetween(llaSouthPole, llaNorthPole, sphericalEarthEquatorialRadius, sphericalEarthFlattening);

        EXPECT_EQ(distanceSemiPolesOneDirection, distanceSemiPolesOtherDirection);
        EXPECT_EQ(distanceSemiPolesOneDirection.inMeters(), pi * sphericalEarthEquatorialRadius.inMeters());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Spherical_LLA, DistanceBetween_WGS84)
{
    const Earth WGS84Earth = Earth::WGS84();
    const Earth sphericalEarth = Earth::Spherical();

    const Length sphericalEarthEquatorialRadius = sphericalEarth.getEquatorialRadius();
    const Real sphericalEarthFlattening = sphericalEarth.getFlattening();

    const Length WGS84EarthEquatorialRadius = WGS84Earth.getEquatorialRadius();
    const Real WGS84EarthFlattening = WGS84Earth.getFlattening();

    const double pi = 3.14159265358979323846;

    {
        const Length distance = LLA::DistanceBetween(lla_, lla_, WGS84EarthEquatorialRadius, WGS84EarthFlattening);

        EXPECT_EQ(distance.inMeters(), 0.0);
    }

    {
        const LLA llaNorthPole = LLA(Angle::Degrees(90.0), Angle::Degrees(15.0), Length::Meters(1.0));
        const LLA llaSouthPole = LLA(Angle::Degrees(-90.0), Angle::Degrees(15.0), Length::Meters(1.0));

        const Length distanceSemiPolesOneDirection =
            LLA::DistanceBetween(llaNorthPole, llaSouthPole, WGS84EarthEquatorialRadius, WGS84EarthFlattening);
        const Length distanceSemiPolesOtherDirection =
            LLA::DistanceBetween(llaSouthPole, llaNorthPole, WGS84EarthEquatorialRadius, WGS84EarthFlattening);

        EXPECT_EQ(distanceSemiPolesOneDirection, distanceSemiPolesOtherDirection);
        ASSERT_GT(pi * sphericalEarthEquatorialRadius.inMeters(), distanceSemiPolesOneDirection.inMeters());
    }

    {
        const LLA llaEquatorial0 = LLA(Angle::Degrees(0.0), Angle::Degrees(0.0), Length::Meters(1.0));
        const LLA llaEquatorial90 = LLA(Angle::Degrees(0.0), Angle::Degrees(90.0), Length::Meters(1.0));
        const LLA llaEquatorial180 = LLA(Angle::Degrees(0.0), Angle::Degrees(180.0), Length::Meters(1.0));

        const Length distanceFirstQuarterEquatorial =
            LLA::DistanceBetween(llaEquatorial0, llaEquatorial90, WGS84EarthEquatorialRadius, WGS84EarthFlattening);
        const Length distanceSecondQuarterEquatorial =
            LLA::DistanceBetween(llaEquatorial90, llaEquatorial180, WGS84EarthEquatorialRadius, WGS84EarthFlattening);

        const Length distanceSemiEquatorial =
            LLA::DistanceBetween(llaEquatorial0, llaEquatorial180, WGS84EarthEquatorialRadius, WGS84EarthFlattening);

        ASSERT_GT(distanceFirstQuarterEquatorial + distanceSecondQuarterEquatorial, distanceSemiEquatorial);
    }

    {
        const LLA llaEquatorial0 = LLA(Angle::Degrees(0.0), Angle::Degrees(0.0), Length::Meters(1.0));
        const LLA llaEquatorial180 = LLA(Angle::Degrees(0.0), Angle::Degrees(180.0), Length::Meters(1.0));

        const LLA llaNorthPole = LLA(Angle::Degrees(90.0), Angle::Degrees(15.0), Length::Meters(1.0));
        const LLA llaSouthPole = LLA(Angle::Degrees(-90.0), Angle::Degrees(15.0), Length::Meters(1.0));

        const Length distanceSemiEquatorial =
            LLA::DistanceBetween(llaEquatorial0, llaEquatorial180, WGS84EarthEquatorialRadius, WGS84EarthFlattening);
        const Length distanceSemiPoles =
            LLA::DistanceBetween(llaNorthPole, llaSouthPole, WGS84EarthEquatorialRadius, WGS84EarthFlattening);

        EXPECT_EQ(distanceSemiEquatorial, distanceSemiPoles);
    }

    {
        const LLA llaEquatorial0 = LLA(Angle::Degrees(0.0), Angle::Degrees(0.0), Length::Meters(1.0));
        const LLA llaNorthPole = LLA(Angle::Degrees(90.0), Angle::Degrees(0.0), Length::Meters(1.0));

        const Length distanceQuarterNorthSpherical = LLA::DistanceBetween(
            llaEquatorial0, llaNorthPole, sphericalEarthEquatorialRadius, sphericalEarthFlattening
        );
        const Length distanceQuarterNorthWGS84 =
            LLA::DistanceBetween(llaEquatorial0, llaNorthPole, WGS84EarthEquatorialRadius, WGS84EarthFlattening);

        ASSERT_GT(distanceQuarterNorthSpherical, distanceQuarterNorthWGS84);
    }
}
