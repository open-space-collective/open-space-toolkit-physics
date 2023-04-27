////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth.test.cpp
/// @author         Kyle Cochran <kyle.cochran@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/Manager.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Time/DateTime.hpp>
#include <OpenSpaceToolkit/Physics/Time/Scale.hpp>
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
    //using EarthAtmosphericModelManager = ostk::physics::environment::atmospheric::earth::Manager ;

    {

        //EarthAtmosphericModelManager::Get().setLocalRepository(Directory::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth"))) ;

        //EarthAtmosphericModelManager::Get().enable() ;

        EXPECT_NO_THROW(EarthAtmosphericModel earthAtmosphericModel(EarthAtmosphericModel::Type::exponential)) ;

        //EarthAtmosphericModelManager::Get().setLocalRepository(EarthAtmosphericModelManager::DefaultLocalRepository()) ;

        //EarthAtmosphericModelManager::Get().setEnabled(EarthAtmosphericModelManager::DefaultEnabled()) ;

    }

    {

        EXPECT_NO_THROW(EarthAtmosphericModel earthAtmosphericModel(EarthAtmosphericModel::Type::exponential, Directory::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth")))) ;

    }

    {

        EXPECT_NO_THROW(EarthAtmosphericModel earthAtmosphericModel(EarthAtmosphericModel::Type::exponential, Directory::Path(Path::Parse("/does/not/exist")))) ;

    }

}


TEST (OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth, GetType)
{

    using ostk::core::fs::Path ;
    using ostk::core::fs::Directory ;

    using EarthAtmosphericModel = ostk::physics::environment::atmospheric::Earth ;
    //using EarthAtmosphericModelManager = ostk::physics::environment::atmospheric::earth::Manager ;

    {

        //EarthAtmosphericModelManager::Get().setLocalRepository(Directory::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth"))) ;

        //EarthAtmosphericModelManager::Get().enable() ;

        EXPECT_EQ(EarthAtmosphericModel::Type::exponential, EarthAtmosphericModel(EarthAtmosphericModel::Type::exponential).getType()) ;

        //EarthAtmosphericModelManager::Get().setLocalRepository(EarthAtmosphericModelManager::DefaultLocalRepository()) ;

        //EarthAtmosphericModelManager::Get().setEnabled(EarthAtmosphericModelManager::DefaultEnabled()) ;

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
    using ostk::physics::time::Scale ;
    using ostk::physics::time::Instant ;
    using ostk::physics::time::DateTime ;
    using EarthAtmosphericModel = ostk::physics::environment::atmospheric::Earth ;
    //using EarthAtmosphericModelManager = ostk::physics::environment::atmospheric::earth::Manager ;

    {

        //EarthAtmosphericModelManager::Get().setLocalRepository(Directory::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth"))) ;

        //EarthAtmosphericModelManager::Get().enable() ;

        // Setup test inputs:
        LLA dummy = LLA(Angle(0, Angle::Unit::Degree), Angle(0, Angle::Unit::Degree), Length(0, Length::Unit::Meter)) ;
        Instant instant = Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC) ;

        EarthAtmosphericModel earthAtmosphericModel(EarthAtmosphericModel::Type::exponential, Directory::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth"))) ;
        
        const double density = earthAtmosphericModel.getDensityAt(dummy, instant) ;
        //std::cout << "density is" << (density) ;
        /*
        static const Array<Tuple<EarthAtmosphericModel::Type, Vector3d, Instant, Vector3d, Real>> testCases =
        {
            { EarthAtmosphericModel::Type::NRLMSISE00,  { 6378137.0, 0.0, 0.0 }, Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { -3.32722007216433e-06, -5.06143921819291e-06, +2.94583020764477e-05 }, 1e-15 },
        } ;

        for (const auto& testCase : testCases)
        {

            const EarthAtmosphericModel earthAtmosphericModel = { std::get<0>(testCase) } ;

            const Vector3d position = std::get<1>(testCase) ;
            const Instant instant = std::get<2>(testCase) ;

            const Vector3d referenceFieldValue = std::get<3>(testCase) ;
            const Real tolerance = std::get<4>(testCase) ;

            const Vector3d fieldValue = earthAtmosphericModel.getFieldValueAt(position, instant) ;

            EXPECT_TRUE(fieldValue.isNear(referenceFieldValue, tolerance)) << String::Format("{} ≈ {} Δ {} [T]", fieldValue.toString(), referenceFieldValue.toString(), (fieldValue - referenceFieldValue).norm()) ;

        }

        EarthAtmosphericModelManager::Get().setLocalRepository(EarthAtmosphericModelManager::DefaultLocalRepository()) ;

        EarthAtmosphericModelManager::Get().setEnabled(EarthAtmosphericModelManager::DefaultEnabled()) ;
        */
    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
