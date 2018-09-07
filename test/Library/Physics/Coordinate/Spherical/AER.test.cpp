////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Coordinate/Spherical/AER.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Environment/Objects/CelestialBodies/Earth.hpp>
#include <Library/Physics/Coordinate/Frame.hpp>
#include <Library/Physics/Coordinate/Spherical/AER.hpp>
#include <Library/Physics/Coordinate/Spherical/LLA.hpp>
#include <Library/Physics/Units/Derived/Angle.hpp>

#include <Library/Core/FileSystem/File.hpp>
#include <Library/Core/FileSystem/Path.hpp>
#include <Library/Core/Containers/Table.hpp>
#include <Library/Core/Containers/Array.hpp>
#include <Library/Core/Containers/Tuple.hpp>
#include <Library/Core/Types/Real.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Physics_Coordinate_Spherical_AER, Constructor)
{

    using library::physics::units::Length ;
    using library::physics::units::Angle ;
    using library::physics::coord::Position ;
    using library::physics::coord::spherical::AER ;

    {
        
        const Angle azimuth = Angle::Degrees(10.0) ;
        const Angle elevation = Angle::Degrees(20.0) ;
        const Length range = Length::Meters(30.0) ;

        EXPECT_NO_THROW(AER aer(azimuth, elevation, range) ;) ;

    }

    {

        EXPECT_ANY_THROW(AER aer(Angle::Degrees(-10.0), Angle::Degrees(20.0), Length::Meters(30.0)) ;) ;
        EXPECT_ANY_THROW(AER aer(Angle::Degrees(10.0), Angle::Degrees(-91.0), Length::Meters(30.0)) ;) ;
        EXPECT_ANY_THROW(AER aer(Angle::Degrees(10.0), Angle::Degrees(+91.0), Length::Meters(30.0)) ;) ;
        EXPECT_ANY_THROW(AER aer(Angle::Degrees(10.0), Angle::Degrees(20.0), Length::Meters(-30.0)) ;) ;

    }

}

TEST (Library_Physics_Coordinate_Spherical_AER, EqualToOperator)
{

    using library::physics::units::Length ;
    using library::physics::units::Angle ;
    using library::physics::coord::Position ;
    using library::physics::coord::spherical::AER ;

    {

        const Angle azimuth = Angle::Degrees(10.0) ;
        const Angle elevation = Angle::Degrees(20.0) ;
        const Length range = Length::Meters(30.0) ;

        const AER aer = { azimuth, elevation, range } ;

        EXPECT_TRUE(aer == aer) ;

    }

    {

        EXPECT_FALSE(AER(Angle::Degrees(10.0), Angle::Degrees(20.0), Length::Meters(30.0)) == AER(Angle::Degrees(20.0), Angle::Degrees(20.0), Length::Meters(30.0))) ;

    }

    {

        const Angle azimuth = Angle::Degrees(10.0) ;
        const Angle elevation = Angle::Degrees(20.0) ;
        const Length range = Length::Meters(30.0) ;

        const AER aer = { azimuth, elevation, range } ;

        EXPECT_FALSE(AER::Undefined() == AER::Undefined()) ;
        EXPECT_FALSE(aer == AER::Undefined()) ;
        EXPECT_FALSE(AER::Undefined() == aer) ;

    }

}

TEST (Library_Physics_Coordinate_Spherical_AER, NotEqualToOperator)
{

    using library::physics::units::Length ;
    using library::physics::units::Angle ;
    using library::physics::coord::Position ;
    using library::physics::coord::spherical::AER ;

    {

        const Angle azimuth = Angle::Degrees(10.0) ;
        const Angle elevation = Angle::Degrees(20.0) ;
        const Length range = Length::Meters(30.0) ;

        const AER aer = { azimuth, elevation, range } ;

        EXPECT_FALSE(aer != aer) ;

    }

    {

        EXPECT_TRUE(AER(Angle::Degrees(10.0), Angle::Degrees(20.0), Length::Meters(30.0)) != AER(Angle::Degrees(20.0), Angle::Degrees(20.0), Length::Meters(30.0))) ;

    }

    {

        const Angle azimuth = Angle::Degrees(10.0) ;
        const Angle elevation = Angle::Degrees(20.0) ;
        const Length range = Length::Meters(30.0) ;

        const AER aer = { azimuth, elevation, range } ;

        EXPECT_TRUE(AER::Undefined() != AER::Undefined()) ;
        EXPECT_TRUE(aer != AER::Undefined()) ;
        EXPECT_TRUE(AER::Undefined() != aer) ;

    }

}

TEST (Library_Physics_Coordinate_Spherical_AER, StreamOperator)
{

    using library::physics::units::Length ;
    using library::physics::units::Angle ;
    using library::physics::coord::Position ;
    using library::physics::coord::spherical::AER ;

    {

        const Angle azimuth = Angle::Degrees(10.0) ;
        const Angle elevation = Angle::Degrees(20.0) ;
        const Length range = Length::Meters(30.0) ;

        const AER aer = { azimuth, elevation, range } ;

        testing::internal::CaptureStdout() ;

        EXPECT_NO_THROW(std::cout << aer << std::endl) ;

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty()) ;

    }

}

TEST (Library_Physics_Coordinate_Spherical_AER, IsDefined)
{

    using library::physics::units::Length ;
    using library::physics::units::Angle ;
    using library::physics::coord::Position ;
    using library::physics::coord::spherical::AER ;

    {

        const Angle azimuth = Angle::Degrees(10.0) ;
        const Angle elevation = Angle::Degrees(20.0) ;
        const Length range = Length::Meters(30.0) ;

        const AER aer = { azimuth, elevation, range } ;

        EXPECT_TRUE(aer.isDefined()) ;

    }

    {
        
        EXPECT_FALSE(AER::Undefined().isDefined()) ;

    }

}

TEST (Library_Physics_Coordinate_Spherical_AER, GetAzimuth)
{
    
    using library::physics::units::Length ;
    using library::physics::units::Angle ;
    using library::physics::coord::Position ;
    using library::physics::coord::spherical::AER ;

    {

        const Angle azimuth = Angle::Degrees(10.0) ;
        const Angle elevation = Angle::Degrees(20.0) ;
        const Length range = Length::Meters(30.0) ;

        const AER aer = { azimuth, elevation, range } ;

        EXPECT_EQ(azimuth, aer.getAzimuth()) ;

    }

    {

        EXPECT_ANY_THROW(AER::Undefined().getAzimuth()) ;

    }

}

TEST (Library_Physics_Coordinate_Spherical_AER, GetElevation)
{
    
    using library::physics::units::Length ;
    using library::physics::units::Angle ;
    using library::physics::coord::Position ;
    using library::physics::coord::spherical::AER ;

    {

        const Angle azimuth = Angle::Degrees(10.0) ;
        const Angle elevation = Angle::Degrees(20.0) ;
        const Length range = Length::Meters(30.0) ;

        const AER aer = { azimuth, elevation, range } ;

        EXPECT_EQ(elevation, aer.getElevation()) ;

    }

    {

        EXPECT_ANY_THROW(AER::Undefined().getElevation()) ;

    }

}

TEST (Library_Physics_Coordinate_Spherical_AER, GetRange)
{
    
    using library::physics::units::Length ;
    using library::physics::units::Angle ;
    using library::physics::coord::Position ;
    using library::physics::coord::spherical::AER ;

    {

        const Angle azimuth = Angle::Degrees(10.0) ;
        const Angle elevation = Angle::Degrees(20.0) ;
        const Length range = Length::Meters(30.0) ;

        const AER aer = { azimuth, elevation, range } ;

        EXPECT_EQ(range, aer.getRange()) ;

    }

    {

        EXPECT_ANY_THROW(AER::Undefined().getRange()) ;

    }

}

TEST (Library_Physics_Coordinate_Spherical_AER, ToVector)
{

    using library::math::obj::Vector3d ;
    
    using library::physics::units::Length ;
    using library::physics::units::Angle ;
    using library::physics::coord::Position ;
    using library::physics::coord::spherical::AER ;

    {

        const Angle azimuth = Angle::Degrees(10.0) ;
        const Angle elevation = Angle::Degrees(20.0) ;
        const Length range = Length::Meters(30.0) ;

        const AER aer = { azimuth, elevation, range } ;

        EXPECT_EQ(Vector3d(10.0, 20.0, 30.0), aer.toVector()) ;

    }

    {

        EXPECT_ANY_THROW(AER::Undefined().toVector()) ;

    }

}

// TEST (Library_Physics_Coordinate_Spherical_AER, ToCartesian)
// {
    
//     using library::physics::units::Length ;
//     using library::physics::units::Angle ;
//     using library::physics::coord::Position ;
//     using library::physics::coord::spherical::AER ;

//     {

//         const Angle azimuth = Angle::Degrees(10.0) ;
//         const Angle elevation = Angle::Degrees(20.0) ;
//         const Length range = Length::Meters(30.0) ;

//         const AER aer = { azimuth, elevation, range } ;

//         FAIL() ;

//     }

//     {

//         EXPECT_ANY_THROW(AER::Undefined().toCartesian()) ;

//     }

// }

TEST (Library_Physics_Coordinate_Spherical_AER, ToString)
{
    
    using library::physics::units::Length ;
    using library::physics::units::Angle ;
    using library::physics::coord::Position ;
    using library::physics::coord::spherical::AER ;

    {

        const Angle azimuth = Angle::Degrees(10.0) ;
        const Angle elevation = Angle::Degrees(20.0) ;
        const Length range = Length::Meters(30.0) ;

        const AER aer = { azimuth, elevation, range } ;

        EXPECT_EQ("[10.0 [deg], 20.0 [deg], 30.0 [m]]", aer.toString()) ;

    }

    {

        EXPECT_ANY_THROW(AER::Undefined().toString()) ;

    }

}

TEST (Library_Physics_Coordinate_Spherical_AER, Undefined)
{
    
    using library::physics::coord::spherical::AER ;

    {

        EXPECT_NO_THROW(AER::Undefined()) ;

    }

}

TEST (Library_Physics_Coordinate_Spherical_AER, Vector)
{

    using library::math::obj::Vector3d ;
    
    using library::physics::units::Length ;
    using library::physics::units::Angle ;
    using library::physics::coord::Position ;
    using library::physics::coord::spherical::AER ;

    {

        const Vector3d vector = { 10.0, 20.0, 30.0 } ;

        const Angle azimuth = Angle::Degrees(10.0) ;
        const Angle elevation = Angle::Degrees(20.0) ;
        const Length range = Length::Meters(30.0) ;

        const AER aer = { azimuth, elevation, range } ;

        EXPECT_EQ(aer, AER::Vector(vector)) ;

    }

    {

        EXPECT_ANY_THROW(AER::Vector(Vector3d::Undefined())) ;

    }

}

TEST (Library_Physics_Coordinate_Spherical_AER, FromPositionToPosition)
{

    using library::core::types::Shared ;
    using library::core::types::Real ;
    using library::core::types::String ;
    using library::core::ctnr::Tuple ;
    using library::core::ctnr::Array ;
    using library::core::ctnr::Table ;
    using library::core::fs::Path ;
    using library::core::fs::File ;

    using library::math::obj::Vector3d ;
    
    using library::physics::units::Length ;
    using library::physics::units::Angle ;
    using library::physics::time::Scale ;
    using library::physics::time::Instant ;
    using library::physics::time::DateTime ;
    using library::physics::coord::Position ;
    using library::physics::coord::spherical::LLA ;
    using library::physics::coord::spherical::AER ;
    using library::physics::coord::Frame ;
    using library::physics::env::obj::celest::Earth ;
    
    {

        const Array<Tuple<File, Angle, Length>> referenceScenarios =
        {
            { File::Path(Path::Parse("../test/Library/Physics/Coordinate/Spherical/AER/FromPositionToPosition/AER NoLightTimeDelay.csv")), Angle::Arcseconds(0.01), Length::Meters(0.01) },
            { File::Path(Path::Parse("../test/Library/Physics/Coordinate/Spherical/AER/FromPositionToPosition/AER WithLightTimeDelay.csv")), Angle::Arcseconds(100.0), Length::Meters(20.0) } // [TBI]
        } ;

        for (const auto& referenceScenario : referenceScenarios)
        {

            // Reference data setup

            const File referenceDataFile = std::get<0>(referenceScenario) ;
            const Angle toleranceAngle = std::get<1>(referenceScenario) ;
            const Length toleranceLength = std::get<2>(referenceScenario) ;

            const Table referenceData = Table::Load(referenceDataFile, Table::Format::CSV, true) ;

            // Test

            const Earth earth = Earth::Analytical() ;

            for (const auto& referenceRow : referenceData)
            {

                const Instant instant = Instant::DateTime(DateTime::Parse(referenceRow[0].accessString()), Scale::UTC) ;

                const Vector3d reference_fromPosition_ITRF = { referenceRow[1].accessReal(), referenceRow[2].accessReal(), referenceRow[3].accessReal() } ;
                const Vector3d reference_fromPosition_LLA = { referenceRow[4].accessReal(), referenceRow[5].accessReal(), referenceRow[6].accessReal() } ;
                const Vector3d reference_toPosition_ITRF = { referenceRow[7].accessReal(), referenceRow[8].accessReal(), referenceRow[9].accessReal() } ;
                const Vector3d reference_toPosition_LLA = { referenceRow[10].accessReal(), referenceRow[11].accessReal(), referenceRow[12].accessReal() } ;

                (void) reference_fromPosition_LLA ;
                (void) reference_toPosition_LLA ;

                const Angle reference_azimuth = Angle::Degrees(referenceRow[13].accessReal()) ;
                const Angle reference_elevation = Angle::Degrees(referenceRow[14].accessReal()) ;
                const Length reference_range = Length::Meters(referenceRow[15].accessReal()) ;

                const Position fromPosition_ITRF = Position::Meters(reference_fromPosition_ITRF, Frame::ITRF()) ;
                const Position toPosition_ITRF = Position::Meters(reference_toPosition_ITRF, Frame::ITRF()) ;

                const LLA fromLla = LLA::Cartesian(fromPosition_ITRF.getCoordinates(), Earth::EquatorialRadius, Earth::Flattening) ;

                const Shared<const Frame> nedFrameSPtr = earth.getFrameAt(fromLla, Earth::FrameType::NED) ;

                const Position fromPosition_NED = fromPosition_ITRF.inFrame(nedFrameSPtr, instant) ;
                const Position toPosition_NED = toPosition_ITRF.inFrame(nedFrameSPtr, instant) ;

                const AER aer = AER::FromPositionToPosition(fromPosition_NED, toPosition_NED) ;

                {

                    const Real reference_azimuth_deg = reference_azimuth.inDegrees() ;
                    const Real azimuth_deg = aer.getAzimuth().inDegrees() ;
                    const Real tolerance_deg = toleranceAngle.inDegrees() ;

                    const Real error_deg = (azimuth_deg - reference_azimuth_deg).abs() ;

                    ASSERT_TRUE(azimuth_deg.isNear(reference_azimuth_deg, tolerance_deg)) << String::Format("{} - {} [deg] ~ {} [deg] ? {} [deg]", instant.toString(), reference_azimuth_deg.toString(), azimuth_deg.toString(), error_deg.toString()) ;

                }

                {

                    const Real reference_elevation_deg = reference_elevation.inDegrees() ;
                    const Real elevation_deg = aer.getElevation().inDegrees() ;
                    const Real tolerance_deg = toleranceAngle.inDegrees() ;

                    const Real error_deg = (elevation_deg - reference_elevation_deg).abs() ;

                    ASSERT_TRUE(elevation_deg.isNear(reference_elevation_deg, tolerance_deg)) << String::Format("{} - {} [deg] ~ {} [deg] ? {} [deg]", instant.toString(), reference_elevation_deg.toString(), elevation_deg.toString(), error_deg.toString()) ;

                }

                {

                    const Real reference_range_m = reference_range.inMeters() ;
                    const Real range_m = aer.getRange().inMeters() ;
                    const Real tolerance_m = toleranceLength.inMeters() ;

                    const Real error_m = (range_m - reference_range_m).abs() ;

                    ASSERT_TRUE(range_m.isNear(reference_range_m, tolerance_m)) << String::Format("{} - {} [m] ~ {} [m] ? {} [m]", instant.toString(), reference_range_m.toString(), range_m.toString(), error_m.toString()) ;

                }
                
            }

        }
        
    }

    {

        const Position fromPosition = Position::Meters({ 0.0, 0.0, +0.0 }, Frame::ITRF()) ;
        const Position toPosition = Position::Meters({ 0.0, 0.0, -1.0 }, Frame::ITRF()) ;

        const AER aer = AER::FromPositionToPosition(fromPosition, toPosition) ;

        const AER referenceAer = { Angle::Degrees(0.0), Angle::Degrees(+90.0), Length::Meters(1.0) } ;

        EXPECT_EQ(referenceAer, aer) ;

    }

    {

        const Position fromPosition = Position::Meters({ 0.0, 0.0, +0.0 }, Frame::ITRF()) ;
        const Position toPosition = Position::Meters({ 0.0, 0.0, -1.0 }, Frame::ITRF()) ;

        const AER aer = AER::FromPositionToPosition(fromPosition, toPosition, false) ;

        const AER referenceAer = { Angle::Degrees(0.0), Angle::Degrees(-90.0), Length::Meters(1.0) } ;

        EXPECT_EQ(referenceAer, aer) ;

    }

    {

        const Position fromPosition = Position::Meters({ 0.0, 0.0, 0.0 }, Frame::ITRF()) ;
        const Position toPosition = Position::Meters({ 0.0, 0.0, 0.0 }, Frame::ITRF()) ;

        const AER aer = AER::FromPositionToPosition(fromPosition, toPosition) ;

        const AER referenceAer = { Angle::Degrees(0.0), Angle::Degrees(0.0), Length::Meters(0.0) } ;

        EXPECT_EQ(referenceAer, aer) ;

    }

    {

        EXPECT_ANY_THROW(AER::FromPositionToPosition(Position::Undefined(), Position::Undefined())) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////