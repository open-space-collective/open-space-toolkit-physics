////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           OpenSpaceToolkit/Physics/Environment/Gravitational/Earth.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Earth/Manager.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Time/DateTime.hpp>
#include <OpenSpaceToolkit/Physics/Time/Scale.hpp>

#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Path.hpp>
#include <OpenSpaceToolkit/Core/Containers/Array.hpp>
#include <OpenSpaceToolkit/Core/Containers/Tuple.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (OpenSpaceToolkit_Physics_Environment_Gravitational_Earth, Constructor)
{

    using ostk::core::fs::Path ;
    using ostk::core::fs::Directory ;

    using EarthGravitationalModel = ostk::physics::environment::gravitational::Earth ;
    using EarthGravitationalModelManager = ostk::physics::environment::gravitational::earth::Manager ;

    {

        EarthGravitationalModelManager::Get().setLocalRepository(Directory::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Gravitational/Earth"))) ;

        EarthGravitationalModelManager::Get().enable() ;

        EXPECT_NO_THROW(EarthGravitationalModel earthGravitationalModel(EarthGravitationalModel::Type::Spherical)) ;
        EXPECT_NO_THROW(EarthGravitationalModel earthGravitationalModel(EarthGravitationalModel::Type::WGS84)) ;
        EXPECT_NO_THROW(EarthGravitationalModel earthGravitationalModel(EarthGravitationalModel::Type::EGM84)) ;
        EXPECT_NO_THROW(EarthGravitationalModel earthGravitationalModel(EarthGravitationalModel::Type::EGM96)) ;
        EXPECT_NO_THROW(EarthGravitationalModel earthGravitationalModel(EarthGravitationalModel::Type::EGM2008)) ;

        EarthGravitationalModelManager::Get().setLocalRepository(EarthGravitationalModelManager::DefaultLocalRepository()) ;

        EarthGravitationalModelManager::Get().setEnabled(EarthGravitationalModelManager::DefaultEnabled()) ;

    }

    // Test correct model order and degree combinations

    {

        EarthGravitationalModelManager::Get().setLocalRepository(Directory::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Gravitational/Earth"))) ;

        EarthGravitationalModelManager::Get().enable() ;

        EXPECT_NO_THROW(std::make_shared<EarthGravitationalModel>(EarthGravitationalModel::Type::Spherical, Directory::Undefined())) ;
        EXPECT_NO_THROW(std::make_shared<EarthGravitationalModel>(EarthGravitationalModel::Type::WGS84, Directory::Undefined(), 20, 0)) ;
        EXPECT_NO_THROW(std::make_shared<EarthGravitationalModel>(EarthGravitationalModel::Type::EGM84, Directory::Undefined(), 180, 180)) ;
        EXPECT_NO_THROW(std::make_shared<EarthGravitationalModel>(EarthGravitationalModel::Type::EGM96, Directory::Undefined(), 360, 360)) ;
        EXPECT_NO_THROW(std::make_shared<EarthGravitationalModel>(EarthGravitationalModel::Type::EGM2008, Directory::Undefined(), 2190, 2160)) ;

        EarthGravitationalModelManager::Get().setLocalRepository(EarthGravitationalModelManager::DefaultLocalRepository()) ;

        EarthGravitationalModelManager::Get().setEnabled(EarthGravitationalModelManager::DefaultEnabled()) ;

    }

    // Test incorrect model order and degree combinations

    {

        EarthGravitationalModelManager::Get().setLocalRepository(Directory::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Gravitational/Earth"))) ;

        EarthGravitationalModelManager::Get().enable() ;

        EXPECT_NO_THROW(std::make_shared<EarthGravitationalModel>(EarthGravitationalModel::Type::Spherical, Directory::Undefined(), 3000, 3000)) ;

        EXPECT_ANY_THROW(std::make_shared<EarthGravitationalModel>(EarthGravitationalModel::Type::WGS84, Directory::Undefined(), 3000, 3000)) ;
        EXPECT_ANY_THROW(std::make_shared<EarthGravitationalModel>(EarthGravitationalModel::Type::EGM84, Directory::Undefined(), 3000, 3000)) ;
        EXPECT_ANY_THROW(std::make_shared<EarthGravitationalModel>(EarthGravitationalModel::Type::EGM96, Directory::Undefined(), 3000, 3000)) ;
        EXPECT_ANY_THROW(std::make_shared<EarthGravitationalModel>(EarthGravitationalModel::Type::EGM2008, Directory::Undefined(), 3000, 3000)) ;

        EarthGravitationalModelManager::Get().setLocalRepository(EarthGravitationalModelManager::DefaultLocalRepository()) ;

        EarthGravitationalModelManager::Get().setEnabled(EarthGravitationalModelManager::DefaultEnabled()) ;

    }

    {

        EXPECT_NO_THROW(EarthGravitationalModel earthGravitationalModel(EarthGravitationalModel::Type::Spherical, Directory::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Gravitational/Earth")))) ;

        EXPECT_NO_THROW(EarthGravitationalModel earthGravitationalModel(EarthGravitationalModel::Type::WGS84, Directory::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Gravitational/Earth")))) ;
        EXPECT_NO_THROW(EarthGravitationalModel earthGravitationalModel(EarthGravitationalModel::Type::EGM84, Directory::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Gravitational/Earth")))) ;
        EXPECT_NO_THROW(EarthGravitationalModel earthGravitationalModel(EarthGravitationalModel::Type::EGM96, Directory::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Gravitational/Earth")))) ;
        EXPECT_NO_THROW(EarthGravitationalModel earthGravitationalModel(EarthGravitationalModel::Type::EGM2008, Directory::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Gravitational/Earth")))) ;

    }

    {

        EXPECT_NO_THROW(EarthGravitationalModel earthGravitationalModel(EarthGravitationalModel::Type::Spherical, Directory::Path(Path::Parse("/does/not/exist")))) ;

        EXPECT_ANY_THROW(EarthGravitationalModel earthGravitationalModel(EarthGravitationalModel::Type::WGS84, Directory::Path(Path::Parse("/does/not/exist")))) ;
        EXPECT_ANY_THROW(EarthGravitationalModel earthGravitationalModel(EarthGravitationalModel::Type::EGM84, Directory::Path(Path::Parse("/does/not/exist")))) ;
        EXPECT_ANY_THROW(EarthGravitationalModel earthGravitationalModel(EarthGravitationalModel::Type::EGM96, Directory::Path(Path::Parse("/does/not/exist")))) ;
        EXPECT_ANY_THROW(EarthGravitationalModel earthGravitationalModel(EarthGravitationalModel::Type::EGM2008, Directory::Path(Path::Parse("/does/not/exist")))) ;

    }

}

// TEST (OpenSpaceToolkit_Physics_Environment_Gravitational_Earth, Clone)
// {

//     using ostk::core::fs::Path ;
//     using ostk::core::fs::Directory ;

//     using EarthGravitationalModel = ostk::physics::environment::gravitational::Earth ;
//     using EarthGravitationalModelManager = ostk::physics::environment::gravitational::earth::Manager ;

//     {

//         EarthGravitationalModelManager::Get().setLocalRepository(Directory::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Gravitational/Earth"))) ;

//         EarthGravitationalModelManager::Get().enable() ;

//         const EarthGravitationalModel earthGravitationalModel = { EarthGravitationalModel::Type::EGM96 } ;

//         EXPECT_NO_THROW(const EarthGravitationalModel* earthGravitationalModelPtr = earthGravitationalModel.clone() ;) ;

//         EarthGravitationalModelManager::Get().setLocalRepository(EarthGravitationalModelManager::DefaultLocalRepository()) ;

//         EarthGravitationalModelManager::Get().setEnabled(EarthGravitationalModelManager::DefaultEnabled()) ;

//     }

// }

TEST (OpenSpaceToolkit_Physics_Environment_Gravitational_Earth, GetType)
{

    using ostk::core::fs::Path ;
    using ostk::core::fs::Directory ;

    using EarthGravitationalModel = ostk::physics::environment::gravitational::Earth ;
    using EarthGravitationalModelManager = ostk::physics::environment::gravitational::earth::Manager ;

    {

        EarthGravitationalModelManager::Get().setLocalRepository(Directory::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Gravitational/Earth"))) ;

        EarthGravitationalModelManager::Get().enable() ;

        EXPECT_EQ(EarthGravitationalModel::Type::Spherical, EarthGravitationalModel(EarthGravitationalModel::Type::Spherical).getType()) ;
        EXPECT_EQ(EarthGravitationalModel::Type::WGS84, EarthGravitationalModel(EarthGravitationalModel::Type::WGS84).getType()) ;
        EXPECT_EQ(EarthGravitationalModel::Type::EGM84, EarthGravitationalModel(EarthGravitationalModel::Type::EGM84).getType()) ;
        EXPECT_EQ(EarthGravitationalModel::Type::EGM96, EarthGravitationalModel(EarthGravitationalModel::Type::EGM96).getType()) ;
        EXPECT_EQ(EarthGravitationalModel::Type::EGM2008, EarthGravitationalModel(EarthGravitationalModel::Type::EGM2008).getType()) ;

        EarthGravitationalModelManager::Get().setLocalRepository(EarthGravitationalModelManager::DefaultLocalRepository()) ;

        EarthGravitationalModelManager::Get().setEnabled(EarthGravitationalModelManager::DefaultEnabled()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Environment_Gravitational_Earth, GetFieldValueAtNoTruncation)
{

    using ostk::core::types::Real ;
    using ostk::core::types::String ;
    using ostk::core::ctnr::Tuple ;
    using ostk::core::ctnr::Array ;
    using ostk::core::fs::Path ;
    using ostk::core::fs::Directory ;

    using ostk::math::obj::Vector3d ;

    using ostk::physics::time::Instant ;
    using EarthGravitationalModel = ostk::physics::environment::gravitational::Earth ;
    using EarthGravitationalModelManager = ostk::physics::environment::gravitational::earth::Manager ;

    {

        EarthGravitationalModelManager::Get().setLocalRepository(Directory::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Gravitational/Earth"))) ;

        EarthGravitationalModelManager::Get().enable() ;

        static const Array<Tuple<EarthGravitationalModel::Type, Vector3d, Instant, Vector3d, Real>> testCases =
        {

            { EarthGravitationalModel::Type::Spherical, { 6378137.0, 0.0, 0.0 }, Instant::J2000(), { -9.79828547181278, 0.0, 0.0 },                                        1e-13 },
            { EarthGravitationalModel::Type::WGS84,     { 6378137.0, 0.0, 0.0 }, Instant::J2000(), { -9.81424104188087, 0.0, 0.0 },                                        1e-13 },
            { EarthGravitationalModel::Type::EGM84,     { 6378137.0, 0.0, 0.0 }, Instant::J2000(), { -9.81430714161684, -2.31935469758198e-05, -1.30080088064139e-05 },    1e-13 },
            { EarthGravitationalModel::Type::EGM96,     { 6378137.0, 0.0, 0.0 }, Instant::J2000(), { -9.81428438755087, -1.81424333238398e-05, 7.75546781913697e-06 },     1e-13 },
            { EarthGravitationalModel::Type::EGM2008,   { 6378137.0, 0.0, 0.0 }, Instant::J2000(), { -9.81427987766325, -1.38769560673262e-05, 6.83924677252542e-06 },     1e-13 },

            { EarthGravitationalModel::Type::Spherical, { 7000e3, 0.0, 0.0 },    Instant::J2000(), { -8.1347028877551, 0.0, 0.0 },                                         1e-13 },
            { EarthGravitationalModel::Type::WGS84,     { 7000e3, 0.0, 0.0 },    Instant::J2000(), { -8.14569530314416, 0.0, 0.0 },                                        1e-13 },
            { EarthGravitationalModel::Type::EGM84,     { 7000e3, 0.0, 0.0 },    Instant::J2000(), { -8.14574728460001, -2.05387541298693e-05, 2.89745888403438e-05 },     1e-13 },
            { EarthGravitationalModel::Type::EGM96,     { 7000e3, 0.0, 0.0 },    Instant::J2000(), { -8.14574567850702, -2.19120214388815e-05, 3.01312644719760e-05 },     1e-13 },
            { EarthGravitationalModel::Type::EGM2008,   { 7000e3, 0.0, 0.0 },    Instant::J2000(), { -8.14574563988817, -2.17632276310511e-05, 2.98622097530464e-05 },     1e-13 },

            { EarthGravitationalModel::Type::Spherical, { 70000e3, 0.0, 0.0 },   Instant::J2000(), { -0.081347028877551, 0.0, 0.0 },                                       1e-13 },
            { EarthGravitationalModel::Type::WGS84,     { 70000e3, 0.0, 0.0 },   Instant::J2000(), { -0.0813481257058837, 0.0, 0.0 },                                      1e-13 },
            { EarthGravitationalModel::Type::EGM84,     { 70000e3, 0.0, 0.0 },   Instant::J2000(), { -0.0813481348043554, -3.13557991717857e-09, 1.04503585231838e-10 },   1e-13 },
            { EarthGravitationalModel::Type::EGM96,     { 70000e3, 0.0, 0.0 },   Instant::J2000(), { -0.0813481348016591, -3.14162880220011e-09, 1.03321189670023e-10 },   1e-13 },
            { EarthGravitationalModel::Type::EGM2008,   { 70000e3, 0.0, 0.0 },   Instant::J2000(), { -0.0813481347405648, -3.14187787214874e-09, 1.03341418225995e-10 },   1e-13 },

            { EarthGravitationalModel::Type::Spherical, { 700000e3, 0.0, 0.0 },  Instant::J2000(), { -0.00081347028877551, 0.0, 0.0 },                                     1e-13 },
            { EarthGravitationalModel::Type::WGS84,     { 700000e3, 0.0, 0.0 },  Instant::J2000(), { -0.000813470399061998, 0.0, 0.0 },                                    1e-13 },
            { EarthGravitationalModel::Type::EGM84,     { 700000e3, 0.0, 0.0 },  Instant::J2000(), { -0.000813470400014733, -3.60438110107890e-13, 5.77106688430063e-16 }, 1e-13 },
            { EarthGravitationalModel::Type::EGM96,     { 700000e3, 0.0, 0.0 },  Instant::J2000(), { -0.000813470400014252, -3.61017933053639e-13, 5.21321633031416e-16 }, 1e-13 },
            { EarthGravitationalModel::Type::EGM2008,   { 700000e3, 0.0, 0.0 },  Instant::J2000(), { -0.000813470399402024, -3.61045520881784e-13, 5.16916001900846e-16 }, 1e-13 }

        } ;

        for (const auto& testCase : testCases)
        {

            const EarthGravitationalModel earthGravitationalModel = { std::get<0>(testCase) } ;

            const Vector3d position = std::get<1>(testCase) ;
            const Instant instant = std::get<2>(testCase) ;

            const Vector3d referenceFieldValue = std::get<3>(testCase) ;
            const Real tolerance = std::get<4>(testCase) ;

            const Vector3d fieldValue = earthGravitationalModel.getFieldValueAt(position, instant) ;

            EXPECT_TRUE(fieldValue.isNear(referenceFieldValue, tolerance)) << String::Format("{} ≈ {} Δ {} [m.s-2]", fieldValue.toString(), referenceFieldValue.toString(), (fieldValue - referenceFieldValue).norm()) ;

        }

        EarthGravitationalModelManager::Get().setLocalRepository(EarthGravitationalModelManager::DefaultLocalRepository()) ;

        EarthGravitationalModelManager::Get().setEnabled(EarthGravitationalModelManager::DefaultEnabled()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Environment_Gravitational_Earth, GetFieldValueAtWithTruncation)
{

    using ostk::core::types::Real ;
    using ostk::core::types::Integer ;
    using ostk::core::types::String ;
    using ostk::core::ctnr::Tuple ;
    using ostk::core::ctnr::Array ;
    using ostk::core::fs::Path ;
    using ostk::core::fs::Directory ;

    using ostk::math::obj::Vector3d ;

    using ostk::physics::time::Instant ;
    using EarthGravitationalModel = ostk::physics::environment::gravitational::Earth ;
    using EarthGravitationalModelManager = ostk::physics::environment::gravitational::earth::Manager ;

    {

        EarthGravitationalModelManager::Get().setLocalRepository(Directory::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Gravitational/Earth"))) ;

        EarthGravitationalModelManager::Get().enable() ;

        static const Array<Tuple<EarthGravitationalModel::Type, Integer, Integer, Vector3d, Instant, Vector3d, Real>> testCases =
        {

            { EarthGravitationalModel::Type::WGS84,   2,   0,     { 6378137.0, 0.0, 0.0 }, Instant::J2000(), { -9.81419735327356, 0.0, 0.0 },                                        1e-13 },
            { EarthGravitationalModel::Type::EGM84,   35,  35,    { 6378137.0, 0.0, 0.0 }, Instant::J2000(), { -9.81426334721039, 1.99395502092729e-05, -3.14244321914859e-05 },     1e-13 },
            { EarthGravitationalModel::Type::EGM96,   70,  70,    { 6378137.0, 0.0, 0.0 }, Instant::J2000(), { -9.81436993747785, -4.31456586427424e-07, -5.07246874662475e-05 },    1e-13 },
            { EarthGravitationalModel::Type::EGM2008, 100, 100,   { 6378137.0, 0.0, 0.0 }, Instant::J2000(), { -9.81427497884837, -5.76980449670929e-05, -2.2508284743958e-05 },     1e-13 },

            { EarthGravitationalModel::Type::WGS84,   4,   0,     { 6378137.0, 0.0, 0.0 }, Instant::J2000(), { -9.81424091114504, 0.0, 0.0 },                                        1e-13 },
            { EarthGravitationalModel::Type::EGM84,   60,  60,    { 6378137.0, 0.0, 0.0 }, Instant::J2000(), { -9.81437262986811, 2.28752661687178e-05, -6.49048878719256e-05 },     1e-13 },
            { EarthGravitationalModel::Type::EGM96,   100, 100,   { 6378137.0, 0.0, 0.0 }, Instant::J2000(), { -9.81428102205007, -5.25816746052165e-05, -2.48057498027795e-05 },    1e-13 },
            { EarthGravitationalModel::Type::EGM2008, 500, 500,   { 6378137.0, 0.0, 0.0 }, Instant::J2000(), { -9.81427466428249, -3.07124249937458e-05, 1.10685209288415e-06 },     1e-13 },

            { EarthGravitationalModel::Type::WGS84,   10,   0,    { 6378137.0, 0.0, 0.0 }, Instant::J2000(), { -9.81424104188087, 0.0, 0.0 },                                        1e-13 },
            { EarthGravitationalModel::Type::EGM84,   100,  100,  { 6378137.0, 0.0, 0.0 }, Instant::J2000(), { -9.81427332735423, -1.85164532971254e-05, -1.44465171851511e-05 },    1e-13 },
            { EarthGravitationalModel::Type::EGM96,   250,  250,  { 6378137.0, 0.0, 0.0 }, Instant::J2000(), { -9.8142767596212, 1.05605885798904e-05, -5.71216776245046e-05 },      1e-13 },
            { EarthGravitationalModel::Type::EGM2008, 1000, 1000, { 6378137.0, 0.0, 0.0 }, Instant::J2000(), { -9.81427696990211, -1.28079338026626e-05, -8.61360014196899e-06 },    1e-13 },

        } ;

        for (const auto& testCase : testCases)
        {

            const EarthGravitationalModel earthGravitationalModel = { std::get<0>(testCase), Directory::Undefined(), std::get<1>(testCase), std::get<2>(testCase) } ;

            const Vector3d position = std::get<3>(testCase) ;
            const Instant instant = std::get<4>(testCase) ;

            const Vector3d referenceFieldValue = std::get<5>(testCase) ;
            const Real tolerance = std::get<6>(testCase) ;

            const Vector3d fieldValue = earthGravitationalModel.getFieldValueAt(position, instant) ;

            EXPECT_TRUE(fieldValue.isNear(referenceFieldValue, tolerance)) << String::Format("{} ≈ {} Δ {} [m.s-2]", fieldValue.toString(), referenceFieldValue.toString(), (fieldValue - referenceFieldValue).norm()) ;

        }

        EarthGravitationalModelManager::Get().setLocalRepository(EarthGravitationalModelManager::DefaultLocalRepository()) ;

        EarthGravitationalModelManager::Get().setEnabled(EarthGravitationalModelManager::DefaultEnabled()) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
