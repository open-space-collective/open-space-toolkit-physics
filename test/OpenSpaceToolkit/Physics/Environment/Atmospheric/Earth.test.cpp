////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth.test.cpp
/// @author         Kyle Cochran <kyle.cochran@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Units/Derived/Angle.hpp>
#include <OpenSpaceToolkit/Physics/Units/Length.hpp>

#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Path.hpp>
#include <OpenSpaceToolkit/Core/Containers/Array.hpp>
#include <OpenSpaceToolkit/Core/Containers/Tuple.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth, Constructor)
{

    using ostk::core::fs::Path ;
    using ostk::core::fs::Directory ;

    using EarthAtmosphericModel = ostk::physics::environment::atmospheric::Earth ;

    {

        EXPECT_NO_THROW(EarthAtmosphericModel earthAtmosphericModel(EarthAtmosphericModel::Type::Exponential)) ;

    }

    {

        EXPECT_NO_THROW(EarthAtmosphericModel earthAtmosphericModel(EarthAtmosphericModel::Type::Exponential, Directory::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth")))) ;

    }

    {

        EXPECT_NO_THROW(EarthAtmosphericModel earthAtmosphericModel(EarthAtmosphericModel::Type::Exponential, Directory::Path(Path::Parse("/does/not/exist")))) ;

    }

    {

        EXPECT_NO_THROW(EarthAtmosphericModel earthAtmosphericModel(EarthAtmosphericModel::Type::Exponential, Directory::Path(Path::Parse("/does/not/exist")))) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth, GetType)
{

    using EarthAtmosphericModel = ostk::physics::environment::atmospheric::Earth ;

    {

        EXPECT_EQ(EarthAtmosphericModel::Type::Exponential, EarthAtmosphericModel(EarthAtmosphericModel::Type::Exponential).getType()) ;
        EXPECT_EQ(EarthAtmosphericModel::Type::NRLMSISE00, EarthAtmosphericModel(EarthAtmosphericModel::Type::NRLMSISE00).getType()) ;

    }

}


TEST (OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth, GetDensityAt)
{

    using ostk::core::types::Real ;
    using ostk::core::types::String ;
    using ostk::core::ctnr::Tuple ;
    using ostk::core::ctnr::Array ;
    using ostk::core::fs::Path ;
    using ostk::core::fs::Directory ;

    using ostk::physics::coord::spherical::LLA ;
    using ostk::physics::units::Length ;
    using ostk::physics::units::Angle ;
    using ostk::physics::time::Instant ;
    using EarthAtmosphericModel = ostk::physics::environment::atmospheric::Earth ;

    {
        // Hand calculated values to validate
        static const Array<Tuple<EarthAtmosphericModel::Type, LLA, Instant, Real, Real>> testCases =
        {

            { EarthAtmosphericModel::Type::Exponential, LLA( Angle::Degrees(35.076832), Angle::Degrees(-92.546296), Length::Kilometers(123.0) ), Instant::J2000(), 1.77622e-08, 1e-13 },
            { EarthAtmosphericModel::Type::Exponential, LLA( Angle::Degrees(35.076832), Angle::Degrees(-92.546296), Length::Kilometers(499.0) ), Instant::J2000(), 7.08245e-13, 1e-15 },
            { EarthAtmosphericModel::Type::Exponential, LLA( Angle::Degrees(35.076832), Angle::Degrees(-92.546296), Length::Kilometers(501.0) ), Instant::J2000(), 6.85869e-13, 1e-15 },
            { EarthAtmosphericModel::Type::Exponential, LLA( Angle::Degrees(35.076832), Angle::Degrees(-92.546296), Length::Kilometers(550.0) ), Instant::J2000(), 3.18278e-13, 1e-15 }

        } ;

        for (const auto& testCase : testCases)
        {

            const EarthAtmosphericModel earthAtmosphericModel = { std::get<0>(testCase) } ;
            const LLA lla = std::get<1>(testCase) ;
            const Instant instant = std::get<2>(testCase) ;
            const Real referenceDensity = std::get<3>(testCase) ;
            const Real tolerance = std::get<4>(testCase) ;

            const Real density = earthAtmosphericModel.getDensityAt(lla, instant) ;

            EXPECT_TRUE(density.isNear(referenceDensity, tolerance)) << String::Format("{} ≈ {} Δ {} [T]", density.toString(), referenceDensity.toString(), (density - referenceDensity)) ;

        }

    }

    {

        static const Array<Tuple<EarthAtmosphericModel::Type, LLA, Instant>> testCases =
        {

            { EarthAtmosphericModel::Type::Exponential, LLA( Angle::Degrees(35.076832), Angle::Degrees(-92.546296), Length::Kilometers(1001.0) ), Instant::J2000() },
            { EarthAtmosphericModel::Type::NRLMSISE00, LLA( Angle::Degrees(35.076832), Angle::Degrees(-92.546296), Length::Kilometers(100) ), Instant::J2000() }, // NRLMSISE throws because it is not yet implemented

        } ;

        for (const auto& testCase : testCases)
        {

            const EarthAtmosphericModel earthAtmosphericModel = { std::get<0>(testCase) } ;

            const LLA lla = std::get<1>(testCase) ;
            const Instant instant = std::get<2>(testCase) ;

            EXPECT_ANY_THROW(earthAtmosphericModel.getDensityAt(lla, instant)) ;

        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
