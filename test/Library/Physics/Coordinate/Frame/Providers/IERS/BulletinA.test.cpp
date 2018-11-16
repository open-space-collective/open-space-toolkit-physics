////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Coordinate/Frame/Providers/IERS/BulletinA.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Coordinate/Frame/Providers/IERS/BulletinA.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Physics_Coordinate_Frame_Providers_IERS_BulletinA, StreamOperator)
{

    using library::core::fs::Path ;
    using library::core::fs::File ;

    using library::physics::coord::frame::provider::iers::BulletinA ;

    {

        testing::internal::CaptureStdout() ;

        const File file = File::Path(Path::Parse("/var/library-physics/coordinate/frame/providers/iers/ser7.dat")) ;

        const BulletinA bulletinA = BulletinA::Load(file) ;

        EXPECT_NO_THROW(std::cout << bulletinA << std::endl) ;

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty()) ;

    }

}

TEST (Library_Physics_Coordinate_Frame_Providers_IERS_BulletinA, IsDefined)
{

    using library::core::fs::Path ;
    using library::core::fs::File ;

    using library::physics::coord::frame::provider::iers::BulletinA ;

    {

        const File file = File::Path(Path::Parse("/var/library-physics/coordinate/frame/providers/iers/ser7.dat")) ;

        const BulletinA bulletinA = BulletinA::Load(file) ;

        EXPECT_TRUE(bulletinA.isDefined()) ;

    }

    {

        EXPECT_FALSE(BulletinA::Undefined().isDefined()) ;

    }

}

TEST (Library_Physics_Coordinate_Frame_Providers_IERS_BulletinA, AccessReleaseDate)
{

    using library::physics::coord::frame::provider::iers::BulletinA ;

    SUCCEED() ; // See: GetReleaseDate

}

TEST (Library_Physics_Coordinate_Frame_Providers_IERS_BulletinA, AccessTAIMinusUTC)
{

    using library::physics::coord::frame::provider::iers::BulletinA ;

    SUCCEED() ; // See: GetTAIMinusUTC

}

TEST (Library_Physics_Coordinate_Frame_Providers_IERS_BulletinA, AccessTAIMinusUTCEpoch)
{

    using library::physics::coord::frame::provider::iers::BulletinA ;

    SUCCEED() ; // See: GetTAIMinusUTCEpoch

}

TEST (Library_Physics_Coordinate_Frame_Providers_IERS_BulletinA, AccessObservationInterval)
{

    using library::physics::coord::frame::provider::iers::BulletinA ;

    SUCCEED() ; // See: GetObservationInterval

}

TEST (Library_Physics_Coordinate_Frame_Providers_IERS_BulletinA, AccessPredictionInterval)
{

    using library::physics::coord::frame::provider::iers::BulletinA ;

    SUCCEED() ; // See: GetPredictionInterval

}

TEST (Library_Physics_Coordinate_Frame_Providers_IERS_BulletinA, GetReleaseDate)
{

    using library::core::fs::Path ;
    using library::core::fs::File ;
    
    using library::physics::time::Date ;
    using library::physics::coord::frame::provider::iers::BulletinA ;

    {

        const File file = File::Path(Path::Parse("/var/library-physics/coordinate/frame/providers/iers/ser7.dat")) ;

        const BulletinA bulletinA = BulletinA::Load(file) ;

        EXPECT_EQ(Date(2018, 6, 28), bulletinA.getReleaseDate()) ;

    }

    {

        EXPECT_ANY_THROW(BulletinA::Undefined().getReleaseDate()) ;

    }

}

TEST (Library_Physics_Coordinate_Frame_Providers_IERS_BulletinA, GetTAIMinusUTC)
{

    using library::core::fs::Path ;
    using library::core::fs::File ;
    
    using library::physics::time::Duration ;
    using library::physics::coord::frame::provider::iers::BulletinA ;

    {

        const File file = File::Path(Path::Parse("/var/library-physics/coordinate/frame/providers/iers/ser7.dat")) ;

        const BulletinA bulletinA = BulletinA::Load(file) ;

        EXPECT_EQ(Duration::Seconds(37.0), bulletinA.getTAIMinusUTC()) ;

    }

    {

        EXPECT_ANY_THROW(BulletinA::Undefined().getTAIMinusUTC()) ;

    }

}

TEST (Library_Physics_Coordinate_Frame_Providers_IERS_BulletinA, GetTAIMinusUTCEpoch)
{

    using library::core::fs::Path ;
    using library::core::fs::File ;
    
    using library::physics::time::Scale ;
    using library::physics::time::Instant ;
    using library::physics::time::DateTime ;
    using library::physics::coord::frame::provider::iers::BulletinA ;

    {

        const File file = File::Path(Path::Parse("/var/library-physics/coordinate/frame/providers/iers/ser7.dat")) ;

        const BulletinA bulletinA = BulletinA::Load(file) ;

        EXPECT_EQ(Instant::DateTime(DateTime::Parse("2017-01-01 00:00:00"), Scale::UTC), bulletinA.getTAIMinusUTCEpoch()) ;

    }

    {

        EXPECT_ANY_THROW(BulletinA::Undefined().getTAIMinusUTCEpoch()) ;

    }

}

TEST (Library_Physics_Coordinate_Frame_Providers_IERS_BulletinA, GetObservationInterval)
{

    using library::core::fs::Path ;
    using library::core::fs::File ;
    
    using library::physics::time::Scale ;
    using library::physics::time::Instant ;
    using library::physics::time::Interval ;
    using library::physics::time::DateTime ;
    using library::physics::coord::frame::provider::iers::BulletinA ;

    {

        const File file = File::Path(Path::Parse("/var/library-physics/coordinate/frame/providers/iers/ser7.dat")) ;

        const BulletinA bulletinA = BulletinA::Load(file) ;

        EXPECT_EQ(Interval::Closed(Instant::DateTime(DateTime::Parse("2018-06-22 00:00:00"), Scale::UTC), Instant::DateTime(DateTime::Parse("2018-06-28 00:00:00"), Scale::UTC)), bulletinA.getObservationInterval()) ;

    }

    {

        EXPECT_ANY_THROW(BulletinA::Undefined().getObservationInterval()) ;

    }

}

TEST (Library_Physics_Coordinate_Frame_Providers_IERS_BulletinA, GetObservationAt)
{

    using library::core::fs::Path ;
    using library::core::fs::File ;

    using library::physics::time::Scale ;
    using library::physics::time::Instant ;
    using library::physics::time::DateTime ;
    using library::physics::coord::frame::provider::iers::BulletinA ;

    {

        const File file = File::Path(Path::Parse("/var/library-physics/coordinate/frame/providers/iers/ser7.dat")) ;

        const BulletinA bulletinA = BulletinA::Load(file) ;

        {

            const BulletinA::Observation firstObservation = bulletinA.getObservationAt(Instant::DateTime(DateTime::Parse("2018-06-22 00:00:00"), Scale::UTC)) ;

            EXPECT_EQ(2018, firstObservation.year) ;
            EXPECT_EQ(6, firstObservation.month) ;
            EXPECT_EQ(22, firstObservation.day) ;
            EXPECT_NEAR(58291.0, firstObservation.mjd, 1e-1) ;
            EXPECT_NEAR(0.14461, firstObservation.x, 1e-5) ;
            EXPECT_NEAR(0.00009, firstObservation.xError, 1e-5) ;
            EXPECT_NEAR(0.43734, firstObservation.y, 1e-5) ;
            EXPECT_NEAR(0.00009, firstObservation.yError, 1e-5) ;
            EXPECT_NEAR(0.067056, firstObservation.ut1MinusUtc, 1e-6) ;
            EXPECT_NEAR(0.000031, firstObservation.ut1MinusUtcError, 1e-6) ;

        }

    }

    {

        EXPECT_ANY_THROW(BulletinA::Undefined().getObservationAt(Instant::DateTime(DateTime::Parse("2018-06-29 00:00:00"), Scale::UTC))) ;

    }

}

TEST (Library_Physics_Coordinate_Frame_Providers_IERS_BulletinA, GetPredictionInterval)
{

    using library::core::fs::Path ;
    using library::core::fs::File ;

    using library::physics::time::Scale ;
    using library::physics::time::Instant ;
    using library::physics::time::Interval ;
    using library::physics::time::DateTime ;
    using library::physics::coord::frame::provider::iers::BulletinA ;

    {

        const File file = File::Path(Path::Parse("/var/library-physics/coordinate/frame/providers/iers/ser7.dat")) ;

        const BulletinA bulletinA = BulletinA::Load(file) ;

        EXPECT_EQ(Interval::Closed(Instant::DateTime(DateTime::Parse("2018-06-29 00:00:00"), Scale::UTC), Instant::DateTime(DateTime::Parse("2019-06-28 00:00:00"), Scale::UTC)), bulletinA.getPredictionInterval()) ;

    }

    {

        EXPECT_ANY_THROW(BulletinA::Undefined().getPredictionInterval()) ;

    }

}

TEST (Library_Physics_Coordinate_Frame_Providers_IERS_BulletinA, GetPredictionAt)
{

    using library::core::fs::Path ;
    using library::core::fs::File ;

    using library::physics::time::Scale ;
    using library::physics::time::Instant ;
    using library::physics::time::DateTime ;
    using library::physics::coord::frame::provider::iers::BulletinA ;

    {

        const File file = File::Path(Path::Parse("/var/library-physics/coordinate/frame/providers/iers/ser7.dat")) ;

        const BulletinA bulletinA = BulletinA::Load(file) ;

        {

            const BulletinA::Prediction firstPrediction = bulletinA.getPredictionAt(Instant::DateTime(DateTime::Parse("2018-06-29 00:00:00"), Scale::UTC)) ;

            EXPECT_EQ(2018, firstPrediction.year) ;
            EXPECT_EQ(6, firstPrediction.month) ;
            EXPECT_EQ(29, firstPrediction.day) ;
            EXPECT_NEAR(58298.0, firstPrediction.mjd, 1e-1) ;
            EXPECT_NEAR(0.1580, firstPrediction.x, 1e-5) ;
            EXPECT_NEAR(0.4308, firstPrediction.y, 1e-5) ;
            EXPECT_NEAR(0.06934, firstPrediction.ut1MinusUtc, 1e-6) ;

        }

    }

    {

        EXPECT_ANY_THROW(BulletinA::Undefined().getPredictionAt(Instant::DateTime(DateTime::Parse("2018-06-29 00:00:00"), Scale::UTC))) ;

    }

}

TEST (Library_Physics_Coordinate_Frame_Providers_IERS_BulletinA, Load)
{

    using library::core::fs::Path ;
    using library::core::fs::File ;

    using library::physics::time::Scale ;
    using library::physics::time::Instant ;
    using library::physics::time::Duration ;
    using library::physics::time::Interval ;
    using library::physics::time::Date ;
    using library::physics::time::DateTime ;
    using library::physics::coord::frame::provider::iers::BulletinA ;

    {

        const File file = File::Path(Path::Parse("/var/library-physics/coordinate/frame/providers/iers/ser7.dat")) ;

        const BulletinA bulletinA = BulletinA::Load(file) ;

        EXPECT_TRUE(bulletinA.isDefined()) ;

        EXPECT_EQ(Date(2018, 6, 28), bulletinA.getReleaseDate()) ;

        EXPECT_EQ(Duration::Seconds(37.0), bulletinA.getTAIMinusUTC()) ;
        EXPECT_EQ(Instant::DateTime(DateTime::Parse("2017-01-01 00:00:00"), Scale::UTC), bulletinA.getTAIMinusUTCEpoch()) ;

        EXPECT_EQ(Interval::Closed(Instant::DateTime(DateTime::Parse("2018-06-22 00:00:00"), Scale::UTC), Instant::DateTime(DateTime::Parse("2018-06-28 00:00:00"), Scale::UTC)), bulletinA.getObservationInterval()) ;

        {

            const BulletinA::Observation firstObservation = bulletinA.getObservationAt(Instant::DateTime(DateTime::Parse("2018-06-22 00:00:00"), Scale::UTC)) ;

            EXPECT_EQ(2018, firstObservation.year) ;
            EXPECT_EQ(6, firstObservation.month) ;
            EXPECT_EQ(22, firstObservation.day) ;
            EXPECT_NEAR(58291.0, firstObservation.mjd, 1e-1) ;
            EXPECT_NEAR(0.14461, firstObservation.x, 1e-5) ;
            EXPECT_NEAR(0.00009, firstObservation.xError, 1e-5) ;
            EXPECT_NEAR(0.43734, firstObservation.y, 1e-5) ;
            EXPECT_NEAR(0.00009, firstObservation.yError, 1e-5) ;
            EXPECT_NEAR(0.067056, firstObservation.ut1MinusUtc, 1e-6) ;
            EXPECT_NEAR(0.000031, firstObservation.ut1MinusUtcError, 1e-6) ;

        }

        {

            const BulletinA::Observation lastObservation = bulletinA.getObservationAt(Instant::DateTime(DateTime::Parse("2018-06-28 00:00:00"), Scale::UTC)) ;

            EXPECT_EQ(2018, lastObservation.year) ;
            EXPECT_EQ(6, lastObservation.month) ;
            EXPECT_EQ(28, lastObservation.day) ;
            EXPECT_NEAR(58297.0, lastObservation.mjd, 1e11) ;
            EXPECT_NEAR(0.15609, lastObservation.x, 1e-5) ;
            EXPECT_NEAR(0.00009, lastObservation.xError, 1e-5) ;
            EXPECT_NEAR(0.43164, lastObservation.y, 1e-5) ;
            EXPECT_NEAR(0.00009, lastObservation.yError, 1e-5) ;
            EXPECT_NEAR(0.068744, lastObservation.ut1MinusUtc, 1e-6) ;
            EXPECT_NEAR(0.000018, lastObservation.ut1MinusUtcError, 1e-6) ;

        }

        {

            const BulletinA::Observation interpolatedObservation = bulletinA.getObservationAt(Instant::DateTime(DateTime::Parse("2018-06-22 12:00:00"), Scale::UTC)) ;

            EXPECT_EQ(2018, interpolatedObservation.year) ;
            EXPECT_EQ(6, interpolatedObservation.month) ;
            EXPECT_EQ(22, interpolatedObservation.day) ;
            EXPECT_NEAR(58291.5, interpolatedObservation.mjd, 1e-1) ;
            EXPECT_NEAR(0.14461 + (0.14665 - 0.14461) / 2.0, interpolatedObservation.x, 1e-5) ;
            EXPECT_NEAR(0.00009 + (0.00009 - 0.00009) / 2.0, interpolatedObservation.xError, 1e-5) ;
            EXPECT_NEAR(0.43734 + (0.43659 - 0.43734) / 2.0, interpolatedObservation.y, 1e-5) ;
            EXPECT_NEAR(0.00009 + (0.00009 - 0.00009) / 2.0, interpolatedObservation.yError, 1e-5) ;
            EXPECT_NEAR(0.067056 + (0.066865 - 0.067056) / 2.0, interpolatedObservation.ut1MinusUtc, 1e-6) ;
            EXPECT_NEAR(0.000031 + (0.000030 - 0.000031) / 2.0, interpolatedObservation.ut1MinusUtcError, 1e-6) ;

        }

        EXPECT_EQ(Interval::Closed(Instant::DateTime(DateTime::Parse("2018-06-29 00:00:00"), Scale::UTC), Instant::DateTime(DateTime::Parse("2019-06-28 00:00:00"), Scale::UTC)), bulletinA.getPredictionInterval()) ;

        {

            const BulletinA::Prediction firstPrediction = bulletinA.getPredictionAt(Instant::DateTime(DateTime::Parse("2018-06-29 00:00:00"), Scale::UTC)) ;

            EXPECT_EQ(2018, firstPrediction.year) ;
            EXPECT_EQ(6, firstPrediction.month) ;
            EXPECT_EQ(29, firstPrediction.day) ;
            EXPECT_NEAR(58298.0, firstPrediction.mjd, 1e-1) ;
            EXPECT_NEAR(0.1580, firstPrediction.x, 1e-5) ;
            EXPECT_NEAR(0.4308, firstPrediction.y, 1e-5) ;
            EXPECT_NEAR(0.06934, firstPrediction.ut1MinusUtc, 1e-6) ;

        }

        {

            const BulletinA::Prediction lastPrediction = bulletinA.getPredictionAt(Instant::DateTime(DateTime::Parse("2019-06-28 00:00:00"), Scale::UTC)) ;

            EXPECT_EQ(2019, lastPrediction.year) ;
            EXPECT_EQ(6, lastPrediction.month) ;
            EXPECT_EQ(28, lastPrediction.day) ;
            EXPECT_NEAR(58662.0, lastPrediction.mjd, 1e11) ;
            EXPECT_NEAR(0.1741, lastPrediction.x, 1e-5) ;
            EXPECT_NEAR(0.4422, lastPrediction.y, 1e-5) ;
            EXPECT_NEAR(-0.19681, lastPrediction.ut1MinusUtc, 1e-6) ;

        }

        {

            const BulletinA::Prediction interpolatedPrediction = bulletinA.getPredictionAt(Instant::DateTime(DateTime::Parse("2018-06-29 12:00:00"), Scale::UTC)) ;

            EXPECT_EQ(2018, interpolatedPrediction.year) ;
            EXPECT_EQ(6, interpolatedPrediction.month) ;
            EXPECT_EQ(29, interpolatedPrediction.day) ;
            EXPECT_NEAR(58298.5, interpolatedPrediction.mjd, 1e-1) ;
            EXPECT_NEAR(0.1580 + (0.1599 - 0.1580) / 2.0, interpolatedPrediction.x, 1e-5) ;
            EXPECT_NEAR(0.4308 + (0.4301 - 0.4308) / 2.0, interpolatedPrediction.y, 1e-5) ;
            EXPECT_NEAR(0.06934 + (0.06994 - 0.06934) / 2.0, interpolatedPrediction.ut1MinusUtc, 1e-6) ;

        }

    }

    {

        EXPECT_ANY_THROW(BulletinA::Load(File::Undefined())) ;
        EXPECT_ANY_THROW(BulletinA::Load(File::Path(Path::Parse("/does/not/exist")))) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////