/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Container/Iterator/Zip.hpp>
#include <OpenSpaceToolkit/Core/Container/Table.hpp>
#include <OpenSpaceToolkit/Core/Container/Tuple.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Path.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Spherical/LLA.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Object/Celestial/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Unit/Derived/Angle.hpp>

#include <Global.test.hpp>

using ostk::core::container::Array;
using ostk::core::container::iterator::Zip;
using ostk::core::container::Pair;
using ostk::core::container::Table;
using ostk::core::container::Tuple;
using ostk::core::filesystem::File;
using ostk::core::filesystem::Path;
using ostk::core::type::Real;
using ostk::core::type::Shared;
using ostk::core::type::String;

using ostk::mathematics::object::Vector3d;
using Point2d = ostk::mathematics::geometry::d2::object::Point;
using Point3d = ostk::mathematics::geometry::d3::object::Point;

using ostk::physics::coordinate::Frame;
using ostk::physics::coordinate::Position;
using ostk::physics::coordinate::spherical::LLA;
using ostk::physics::environment::object::celestial::Earth;
using ostk::physics::time::DateTime;
using ostk::physics::time::Instant;
using ostk::physics::time::Scale;
using ostk::physics::unit::Angle;
using ostk::physics::unit::Length;
using EarthGravitationalModel = ostk::physics::environment::gravitational::Earth;

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

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Spherical_LLA, OnSurface)
{
    {
        const LLA lla = lla_.onSurface();
        EXPECT_EQ(lla.getLatitude(), lla_.getLatitude());
        EXPECT_EQ(lla.getLongitude(), lla_.getLongitude());
        EXPECT_EQ(lla.getAltitude(), Length::Meters(0.0));
    }

    {
        EXPECT_ANY_THROW(LLA::Undefined().onSurface());
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

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Spherical_LLA, calcluateAzimuthTo_WGS84)
{
    const Earth WGS84Earth = Earth::WGS84();

    const Length WGS84EarthEquatorialRadius = WGS84Earth.getEquatorialRadius();
    const Real WGS84EarthFlattening = WGS84Earth.getFlattening();

    // from pole to pole
    {
        const LLA llaNorthPole = LLA(Angle::Degrees(90.0), Angle::Degrees(15.0), Length::Meters(1.0));
        const LLA llaSouthPole = LLA(Angle::Degrees(-90.0), Angle::Degrees(15.0), Length::Meters(1.0));

        const Pair<Angle, Angle> azimuthsSemiPolesOneDirection =
            llaNorthPole.calculateAzimuthTo(llaSouthPole, WGS84EarthEquatorialRadius, WGS84EarthFlattening);
        const Pair<Angle, Angle> azimuthsSemiPolesOtherDirection =
            llaSouthPole.calculateAzimuthTo(llaNorthPole, WGS84EarthEquatorialRadius, WGS84EarthFlattening);

        EXPECT_EQ(azimuthsSemiPolesOneDirection.first, Angle::Degrees(180.0));
        EXPECT_EQ(azimuthsSemiPolesOneDirection.second, Angle::Degrees(180.0));
        EXPECT_EQ(azimuthsSemiPolesOtherDirection.first, Angle::Degrees(0.0));
        EXPECT_EQ(azimuthsSemiPolesOtherDirection.second, Angle::Degrees(0.0));
    }

    // along equator
    {
        const LLA llaEquatorial0 = LLA(Angle::Degrees(0.0), Angle::Degrees(0.0), Length::Meters(1.0));
        const LLA llaEquatorial10 = LLA(Angle::Degrees(0.0), Angle::Degrees(10.0), Length::Meters(1.0));

        const Pair<Angle, Angle> azimuths =
            llaEquatorial0.calculateAzimuthTo(llaEquatorial10, WGS84EarthEquatorialRadius, WGS84EarthFlattening);

        EXPECT_EQ(azimuths.first, Angle::Degrees(90.0));
        EXPECT_EQ(azimuths.second, Angle::Degrees(90.0));
    }

    // arbitrary points
    {
        const LLA lla1 = LLA(Angle::Degrees(57.23487), Angle::Degrees(23.5343), Length::Meters(1.0));
        const LLA lla2 = LLA(Angle::Degrees(-20.573), Angle::Degrees(-58.128), Length::Meters(1.0));

        const Pair<Angle, Angle> azimuths =
            lla1.calculateAzimuthTo(lla2, WGS84EarthEquatorialRadius, WGS84EarthFlattening);

        EXPECT_NEAR(azimuths.first.inDegrees(), -108.0281189033601, 1e-12);
        EXPECT_NEAR(azimuths.second.inDegrees(), -146.58082723289277, 1e-12);
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Spherical_LLA, calculateIntermediateTo_WGS84)
{
    const Earth WGS84Earth = Earth::WGS84();

    const Length WGS84EarthEquatorialRadius = WGS84Earth.getEquatorialRadius();
    const Real WGS84EarthFlattening = WGS84Earth.getFlattening();

    // from pole to pole
    {
        const LLA llaNorthPole = LLA(Angle::Degrees(90.0), Angle::Degrees(15.0), Length::Meters(1.0));
        const LLA llaSouthPole = LLA(Angle::Degrees(-90.0), Angle::Degrees(15.0), Length::Meters(1.0));

        const LLA llaIntermediate =
            llaNorthPole.calculateIntermediateTo(llaSouthPole, 0.5, WGS84EarthEquatorialRadius, WGS84EarthFlattening);

        EXPECT_EQ(llaIntermediate.getLatitude(), Angle::Degrees(-9.244860342938533e-15));
        EXPECT_EQ(llaIntermediate.getLongitude(), Angle::Degrees(15.0));
    }

    // along equator
    {
        const LLA llaEquatorial0 = LLA(Angle::Degrees(0.0), Angle::Degrees(0.0), Length::Meters(1.0));
        const LLA llaEquatorial10 = LLA(Angle::Degrees(0.0), Angle::Degrees(10.0), Length::Meters(1.0));

        const LLA llaIntermediate = llaEquatorial0.calculateIntermediateTo(
            llaEquatorial10, 0.5, WGS84EarthEquatorialRadius, WGS84EarthFlattening
        );

        EXPECT_EQ(llaIntermediate.getLatitude(), Angle::Degrees(0.0));
        EXPECT_EQ(llaIntermediate.getLongitude(), Angle::Degrees(5.000000000000001));
    }

    // arbitrary points
    {
        const LLA lla1 = LLA(Angle::Degrees(57.23487), Angle::Degrees(23.5343), Length::Meters(1.0));
        const LLA lla2 = LLA(Angle::Degrees(-20.573), Angle::Degrees(-58.128), Length::Meters(1.0));

        const LLA llaIntermediate =
            lla1.calculateIntermediateTo(lla2, 0.5, WGS84EarthEquatorialRadius, WGS84EarthFlattening);

        EXPECT_EQ(llaIntermediate.getLatitude(), Angle::Degrees(23.21714909968633));
        EXPECT_EQ(llaIntermediate.getLongitude(), Angle::Degrees(-30.281783237740761));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Spherical_LLA, calculateForward_WGS84)
{
    const Earth WGS84Earth = Earth::WGS84();

    const Length WGS84EarthEquatorialRadius = WGS84Earth.getEquatorialRadius();
    const Real WGS84EarthFlattening = WGS84Earth.getFlattening();

    // self validated
    {
        const LLA lla = LLA(Angle::Degrees(50.0), Angle::Degrees(15.0), Length::Meters(0.0));
        const LLA llaExpected = LLA(Angle::Degrees(-50.0), Angle::Degrees(15.0), Length::Meters(0.0));

        const Pair<Angle, Angle> azimuths =
            LLA::AzimuthBetween(lla, llaExpected, WGS84EarthEquatorialRadius, WGS84EarthFlattening);
        const Length distance =
            LLA::DistanceBetween(lla, llaExpected, WGS84EarthEquatorialRadius, WGS84EarthFlattening);

        const LLA llaCalculated =
            lla.calculateForward(azimuths.first, distance, WGS84EarthEquatorialRadius, WGS84EarthFlattening);

        EXPECT_NEAR(llaCalculated.getLatitude().inDegrees(), llaExpected.getLatitude().inDegrees(), 1e-13);
        EXPECT_NEAR(llaCalculated.getLongitude().inDegrees(), llaExpected.getLongitude().inDegrees(), 1e-13);
    }

    // along equator
    {
        const LLA lla = LLA(Angle::Degrees(0.0), Angle::Degrees(0.0), Length::Meters(0.0));
        const Angle azimuth = Angle::Degrees(90.0);
        const Length distance = Length::Meters(1113194.9079327357);

        const LLA llaExpected = LLA(Angle::Degrees(0.0), Angle::Degrees(10.0), Length::Meters(0.0));

        const LLA llaCalculated =
            lla.calculateForward(azimuth, distance, WGS84EarthEquatorialRadius, WGS84EarthFlattening);

        EXPECT_NEAR(llaCalculated.getLatitude().inDegrees(), llaExpected.getLatitude().inDegrees(), 1e-13);
        EXPECT_NEAR(llaCalculated.getLongitude().inDegrees(), llaExpected.getLongitude().inDegrees(), 1e-13);
    }

    // arbitrary points
    {
        const LLA lla = LLA(Angle::Degrees(57.23487), Angle::Degrees(23.5343), Length::Meters(1.0));
        const Angle azimuth = Angle::Degrees(-108.0281189033601);
        const Length distance = Length::Meters(11419275.689591393);

        const LLA llaExpected = LLA(Angle::Degrees(-20.573), Angle::Degrees(-58.128), Length::Meters(1.0));

        const LLA llaCalculated =
            lla.calculateForward(azimuth, distance, WGS84EarthEquatorialRadius, WGS84EarthFlattening);

        EXPECT_NEAR(llaExpected.getLatitude().inDegrees(), llaCalculated.getLatitude().inDegrees(), 1e-13);
        EXPECT_NEAR(llaExpected.getLongitude().inDegrees(), llaCalculated.getLongitude().inDegrees(), 1e-13);
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Spherical_LLA, calculateLinspaceTo_WGS84)
{
    const Earth WGS84Earth = Earth::WGS84();

    const Length WGS84EarthEquatorialRadius = WGS84Earth.getEquatorialRadius();
    const Real WGS84EarthFlattening = WGS84Earth.getFlattening();

    {
        const LLA lla1 = LLA(Angle::Degrees(30.0), Angle::Degrees(15.0), Length::Meters(0.0));
        const LLA lla2 = LLA(Angle::Degrees(40.0), Angle::Degrees(-20.0), Length::Meters(0.0));

        const Array<LLA> llas = lla1.calculateLinspaceTo(lla2, 4, WGS84EarthEquatorialRadius, WGS84EarthFlattening);

        const Array<LLA> llasExpected = {
            LLA(Angle::Degrees(32.77300035484225), Angle::Degrees(8.723208061296164), Length::Meters(0.0)),
            LLA(Angle::Degrees(35.21133849773737), Angle::Degrees(2.0702066434751725), Length::Meters(0.0)),
            LLA(Angle::Degrees(37.26216299007888), Angle::Degrees(-4.958642779319256), Length::Meters(0.0)),
            LLA(Angle::Degrees(38.87378674131851), Angle::Degrees(-12.335452344768232), Length::Meters(0.0))
        };

        EXPECT_EQ(llas.getSize(), 4);
        for (const auto& element : Zip(llas, llasExpected))
        {
            const LLA lla = std::get<0>(element);
            const LLA llaExpected = std::get<1>(element);
            EXPECT_NEAR(lla.getLatitude().inDegrees(), llaExpected.getLatitude().inDegrees(), 1e-13);
            EXPECT_NEAR(lla.getLongitude().inDegrees(), llaExpected.getLongitude().inDegrees(), 1e-13);
        }
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

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Spherical_LLA, ToPoint2d)
{
    {
        EXPECT_EQ(Point2d(longitude_.inDegrees(), latitude_.inDegrees()), lla_.toPoint2d());
    }

    {
        EXPECT_ANY_THROW(LLA::Undefined().toPoint2d());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Spherical_LLA, ToPoint3d)
{
    {
        EXPECT_EQ(Point3d(longitude_.inDegrees(), latitude_.inDegrees(), altitude_.inMeters()), lla_.toPoint3d());
    }

    {
        EXPECT_ANY_THROW(LLA::Undefined().toPoint3d());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Spherical_LLA, ToCartesian)
{
    {
        const Array<Tuple<File, Length>> referenceScenarios = {
            {File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Spherical/LLA/ToCartesian/LLA 1.csv")
             ),
             Length::Meters(1.0)}
        };

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
                    referenceRow[1].accessReal(), referenceRow[2].accessReal(), referenceRow[3].accessReal()
                };

                const Angle reference_latitude = Angle::Degrees(referenceRow[4].accessReal());
                const Angle reference_longitude = Angle::Degrees(referenceRow[5].accessReal());
                const Length reference_altitude = Length::Meters(referenceRow[6].accessReal());

                const LLA lla = {reference_latitude, reference_longitude, reference_altitude};

                const Vector3d position_ITRF = lla.toCartesian(
                    EarthGravitationalModel::EGM2008.equatorialRadius_, EarthGravitationalModel::EGM2008.flattening_
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
             Length::Meters(1.0)}
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
                const Instant instant = Instant::DateTime(DateTime::Parse(referenceRow[0].accessString()), Scale::UTC);

                const Vector3d reference_position_ITRF = {
                    referenceRow[1].accessReal(), referenceRow[2].accessReal(), referenceRow[3].accessReal()
                };

                const Angle reference_latitude = Angle::Degrees(referenceRow[4].accessReal());
                const Angle reference_longitude = Angle::Degrees(referenceRow[5].accessReal());
                const Length reference_altitude = Length::Meters(referenceRow[6].accessReal());

                const LLA lla = LLA::Cartesian(
                    reference_position_ITRF,
                    EarthGravitationalModel::EGM2008.equatorialRadius_,
                    EarthGravitationalModel::EGM2008.flattening_
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

// values compared against pyproj
TEST_F(OpenSpaceToolkit_Physics_Coordinate_Spherical_LLA, AzimuthBetween_WGS84)
{
    const Earth WGS84Earth = Earth::WGS84();

    const Length WGS84EarthEquatorialRadius = WGS84Earth.getEquatorialRadius();
    const Real WGS84EarthFlattening = WGS84Earth.getFlattening();

    // from pole to pole
    {
        const LLA llaNorthPole = LLA(Angle::Degrees(90.0), Angle::Degrees(15.0), Length::Meters(1.0));
        const LLA llaSouthPole = LLA(Angle::Degrees(-90.0), Angle::Degrees(15.0), Length::Meters(1.0));

        const Pair<Angle, Angle> azimuthsSemiPolesOneDirection =
            LLA::AzimuthBetween(llaNorthPole, llaSouthPole, WGS84EarthEquatorialRadius, WGS84EarthFlattening);
        const Pair<Angle, Angle> azimuthsSemiPolesOtherDirection =
            LLA::AzimuthBetween(llaSouthPole, llaNorthPole, WGS84EarthEquatorialRadius, WGS84EarthFlattening);

        EXPECT_EQ(azimuthsSemiPolesOneDirection.first, Angle::Degrees(180.0));
        EXPECT_EQ(azimuthsSemiPolesOneDirection.second, Angle::Degrees(180.0));
        EXPECT_EQ(azimuthsSemiPolesOtherDirection.first, Angle::Degrees(0.0));
        EXPECT_EQ(azimuthsSemiPolesOtherDirection.second, Angle::Degrees(0.0));
    }

    // along equator
    {
        const LLA llaEquatorial0 = LLA(Angle::Degrees(0.0), Angle::Degrees(0.0), Length::Meters(1.0));
        const LLA llaEquatorial10 = LLA(Angle::Degrees(0.0), Angle::Degrees(10.0), Length::Meters(1.0));

        const Pair<Angle, Angle> azimuths =
            LLA::AzimuthBetween(llaEquatorial0, llaEquatorial10, WGS84EarthEquatorialRadius, WGS84EarthFlattening);

        EXPECT_EQ(azimuths.first, Angle::Degrees(90.0));
        EXPECT_EQ(azimuths.second, Angle::Degrees(90.0));
    }

    // arbitrary points
    {
        const LLA lla1 = LLA(Angle::Degrees(57.23487), Angle::Degrees(23.5343), Length::Meters(1.0));
        const LLA lla2 = LLA(Angle::Degrees(-20.573), Angle::Degrees(-58.128), Length::Meters(1.0));

        const Pair<Angle, Angle> azimuths =
            LLA::AzimuthBetween(lla1, lla2, WGS84EarthEquatorialRadius, WGS84EarthFlattening);

        EXPECT_NEAR(azimuths.first.inDegrees(), -108.0281189033601, 1e-12);
        EXPECT_NEAR(azimuths.second.inDegrees(), -146.58082723289277, 1e-12);
    }
}

// values compared against pyproj
TEST_F(OpenSpaceToolkit_Physics_Coordinate_Spherical_LLA, IntermediateBetween_WGS84)
{
    const Earth WGS84Earth = Earth::WGS84();

    const Length WGS84EarthEquatorialRadius = WGS84Earth.getEquatorialRadius();
    const Real WGS84EarthFlattening = WGS84Earth.getFlattening();

    // from pole to pole
    {
        const LLA llaNorthPole = LLA(Angle::Degrees(90.0), Angle::Degrees(15.0), Length::Meters(1.0));
        const LLA llaSouthPole = LLA(Angle::Degrees(-90.0), Angle::Degrees(15.0), Length::Meters(1.0));

        const LLA llaIntermediate =
            LLA::IntermediateBetween(llaNorthPole, llaSouthPole, 0.5, WGS84EarthEquatorialRadius, WGS84EarthFlattening);

        EXPECT_EQ(llaIntermediate.getLatitude(), Angle::Degrees(-9.244860342938533e-15));
        EXPECT_EQ(llaIntermediate.getLongitude(), Angle::Degrees(15.0));
    }

    // along equator
    {
        const LLA llaEquatorial0 = LLA(Angle::Degrees(0.0), Angle::Degrees(0.0), Length::Meters(1.0));
        const LLA llaEquatorial10 = LLA(Angle::Degrees(0.0), Angle::Degrees(10.0), Length::Meters(1.0));

        const LLA llaIntermediate = LLA::IntermediateBetween(
            llaEquatorial0, llaEquatorial10, 0.5, WGS84EarthEquatorialRadius, WGS84EarthFlattening
        );

        EXPECT_EQ(llaIntermediate.getLatitude(), Angle::Degrees(0.0));
        EXPECT_EQ(llaIntermediate.getLongitude(), Angle::Degrees(5.000000000000001));
    }

    // arbitrary points
    {
        const LLA lla1 = LLA(Angle::Degrees(57.23487), Angle::Degrees(23.5343), Length::Meters(1.0));
        const LLA lla2 = LLA(Angle::Degrees(-20.573), Angle::Degrees(-58.128), Length::Meters(1.0));

        const LLA llaIntermediate =
            LLA::IntermediateBetween(lla1, lla2, 0.5, WGS84EarthEquatorialRadius, WGS84EarthFlattening);

        EXPECT_EQ(llaIntermediate.getLatitude(), Angle::Degrees(23.21714909968633));
        EXPECT_EQ(llaIntermediate.getLongitude(), Angle::Degrees(-30.281783237740761));
    }
}

// values compared against pyproj
TEST_F(OpenSpaceToolkit_Physics_Coordinate_Spherical_LLA, Forward_WGS84)
{
    const Earth WGS84Earth = Earth::WGS84();

    const Length WGS84EarthEquatorialRadius = WGS84Earth.getEquatorialRadius();
    const Real WGS84EarthFlattening = WGS84Earth.getFlattening();

    // self validated
    {
        const LLA lla = LLA(Angle::Degrees(50.0), Angle::Degrees(15.0), Length::Meters(0.0));
        const LLA llaExpected = LLA(Angle::Degrees(-50.0), Angle::Degrees(15.0), Length::Meters(0.0));

        const Pair<Angle, Angle> azimuths =
            LLA::AzimuthBetween(lla, llaExpected, WGS84EarthEquatorialRadius, WGS84EarthFlattening);
        const Length distance =
            LLA::DistanceBetween(lla, llaExpected, WGS84EarthEquatorialRadius, WGS84EarthFlattening);

        const LLA llaCalculated =
            LLA::Forward(lla, azimuths.first, distance, WGS84EarthEquatorialRadius, WGS84EarthFlattening);

        EXPECT_NEAR(llaCalculated.getLatitude().inDegrees(), llaExpected.getLatitude().inDegrees(), 1e-13);
        EXPECT_NEAR(llaCalculated.getLongitude().inDegrees(), llaExpected.getLongitude().inDegrees(), 1e-13);
    }

    // along equator
    {
        const LLA lla = LLA(Angle::Degrees(0.0), Angle::Degrees(0.0), Length::Meters(0.0));
        const Angle azimuth = Angle::Degrees(90.0);
        const Length distance = Length::Meters(1113194.9079327357);

        const LLA llaExpected = LLA(Angle::Degrees(0.0), Angle::Degrees(10.0), Length::Meters(0.0));

        const LLA llaCalculated =
            LLA::Forward(lla, azimuth, distance, WGS84EarthEquatorialRadius, WGS84EarthFlattening);

        EXPECT_NEAR(llaCalculated.getLatitude().inDegrees(), llaExpected.getLatitude().inDegrees(), 1e-13);
        EXPECT_NEAR(llaCalculated.getLongitude().inDegrees(), llaExpected.getLongitude().inDegrees(), 1e-13);
    }

    // arbitrary points
    {
        const LLA lla = LLA(Angle::Degrees(57.23487), Angle::Degrees(23.5343), Length::Meters(1.0));
        const Angle azimuth = Angle::Degrees(-108.0281189033601);
        const Length distance = Length::Meters(11419275.689591393);

        const LLA llaExpected = LLA(Angle::Degrees(-20.573), Angle::Degrees(-58.128), Length::Meters(1.0));

        const LLA llaCalculated =
            LLA::Forward(lla, azimuth, distance, WGS84EarthEquatorialRadius, WGS84EarthFlattening);

        EXPECT_NEAR(llaExpected.getLatitude().inDegrees(), llaCalculated.getLatitude().inDegrees(), 1e-13);
        EXPECT_NEAR(llaExpected.getLongitude().inDegrees(), llaCalculated.getLongitude().inDegrees(), 1e-13);
    }
}

// values compared against pyproj
TEST_F(OpenSpaceToolkit_Physics_Coordinate_Spherical_LLA, Linspace_WGS84)
{
    const Earth WGS84Earth = Earth::WGS84();

    const Length WGS84EarthEquatorialRadius = WGS84Earth.getEquatorialRadius();
    const Real WGS84EarthFlattening = WGS84Earth.getFlattening();

    {
        const LLA lla1 = LLA(Angle::Degrees(30.0), Angle::Degrees(15.0), Length::Meters(0.0));
        const LLA lla2 = LLA(Angle::Degrees(40.0), Angle::Degrees(-20.0), Length::Meters(0.0));

        const Array<LLA> llas = LLA::Linspace(lla1, lla2, 4, WGS84EarthEquatorialRadius, WGS84EarthFlattening);

        const Array<LLA> llasExpected = {
            LLA(Angle::Degrees(32.77300035484225), Angle::Degrees(8.723208061296164), Length::Meters(0.0)),
            LLA(Angle::Degrees(35.21133849773737), Angle::Degrees(2.0702066434751725), Length::Meters(0.0)),
            LLA(Angle::Degrees(37.26216299007888), Angle::Degrees(-4.958642779319256), Length::Meters(0.0)),
            LLA(Angle::Degrees(38.87378674131851), Angle::Degrees(-12.335452344768232), Length::Meters(0.0))
        };

        EXPECT_EQ(llas.getSize(), 4);
        for (const auto& element : Zip(llas, llasExpected))
        {
            const LLA lla = std::get<0>(element);
            const LLA llaExpected = std::get<1>(element);
            EXPECT_NEAR(lla.getLatitude().inDegrees(), llaExpected.getLatitude().inDegrees(), 1e-13);
            EXPECT_NEAR(lla.getLongitude().inDegrees(), llaExpected.getLongitude().inDegrees(), 1e-13);
        }
    }
}
