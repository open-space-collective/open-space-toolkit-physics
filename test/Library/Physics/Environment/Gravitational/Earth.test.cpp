////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Environment/Gravitational/Earth.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Environment/Gravitational/Earth/Manager.hpp>
#include <Library/Physics/Environment/Gravitational/Earth.hpp>
#include <Library/Physics/Time/Instant.hpp>
#include <Library/Physics/Time/DateTime.hpp>
#include <Library/Physics/Time/Scale.hpp>

#include <Library/Core/FileSystem/File.hpp>
#include <Library/Core/FileSystem/Path.hpp>
#include <Library/Core/Containers/Array.hpp>
#include <Library/Core/Containers/Tuple.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Physics_Environment_Gravitational_Earth, Constructor)
{

    using library::core::fs::Path ;
    using library::core::fs::Directory ;

    using EarthGravitationalModel = library::physics::environment::gravitational::Earth ;
    using library::physics::environment::gravitational::earth::Manager ;

    {

        EXPECT_NO_THROW(EarthGravitationalModel earthGravitationalModel(EarthGravitationalModel::Type::WGS84)) ;
        EXPECT_NO_THROW(EarthGravitationalModel earthGravitationalModel(EarthGravitationalModel::Type::EGM84)) ;
        EXPECT_NO_THROW(EarthGravitationalModel earthGravitationalModel(EarthGravitationalModel::Type::EGM96)) ;
        EXPECT_NO_THROW(EarthGravitationalModel earthGravitationalModel(EarthGravitationalModel::Type::EGM2008)) ;

    }

    {

        EXPECT_NO_THROW(EarthGravitationalModel earthGravitationalModel(EarthGravitationalModel::Type::WGS84, Directory::Path(Path::Parse("/app/share/environment/gravitational/earth")))) ;
        EXPECT_NO_THROW(EarthGravitationalModel earthGravitationalModel(EarthGravitationalModel::Type::EGM84, Directory::Path(Path::Parse("/app/share/environment/gravitational/earth")))) ;
        EXPECT_NO_THROW(EarthGravitationalModel earthGravitationalModel(EarthGravitationalModel::Type::EGM96, Directory::Path(Path::Parse("/app/share/environment/gravitational/earth")))) ;
        EXPECT_NO_THROW(EarthGravitationalModel earthGravitationalModel(EarthGravitationalModel::Type::EGM2008, Directory::Path(Path::Parse("/app/share/environment/gravitational/earth")))) ;

    }

    {

        EXPECT_ANY_THROW(EarthGravitationalModel earthGravitationalModel(EarthGravitationalModel::Type::WGS84, Directory::Path(Path::Parse("/does/not/exist")))) ;
        EXPECT_ANY_THROW(EarthGravitationalModel earthGravitationalModel(EarthGravitationalModel::Type::EGM84, Directory::Path(Path::Parse("/does/not/exist")))) ;
        EXPECT_ANY_THROW(EarthGravitationalModel earthGravitationalModel(EarthGravitationalModel::Type::EGM96, Directory::Path(Path::Parse("/does/not/exist")))) ;
        EXPECT_ANY_THROW(EarthGravitationalModel earthGravitationalModel(EarthGravitationalModel::Type::EGM2008, Directory::Path(Path::Parse("/does/not/exist")))) ;

    }

}

TEST (Library_Physics_Environment_Gravitational_Earth, Clone)
{

    using EarthGravitationalModel = library::physics::environment::gravitational::Earth ;

    {

        const EarthGravitationalModel earthGravitationalModel = { EarthGravitationalModel::Type::EGM96 } ;

        EXPECT_NO_THROW(const EarthGravitationalModel* earthGravitationalModelPtr = earthGravitationalModel.clone() ; delete earthGravitationalModelPtr ;) ;

    }

}

TEST (Library_Physics_Environment_Gravitational_Earth, GetType)
{

    using EarthGravitationalModel = library::physics::environment::gravitational::Earth ;

    {

        EXPECT_EQ(EarthGravitationalModel::Type::WGS84, EarthGravitationalModel(EarthGravitationalModel::Type::WGS84).getType()) ;
        EXPECT_EQ(EarthGravitationalModel::Type::EGM84, EarthGravitationalModel(EarthGravitationalModel::Type::EGM84).getType()) ;
        EXPECT_EQ(EarthGravitationalModel::Type::EGM96, EarthGravitationalModel(EarthGravitationalModel::Type::EGM96).getType()) ;
        EXPECT_EQ(EarthGravitationalModel::Type::EGM2008, EarthGravitationalModel(EarthGravitationalModel::Type::EGM2008).getType()) ;

    }

}

TEST (Library_Physics_Environment_Gravitational_Earth, GetFieldValueAt)
{

    using library::core::types::Real ;
    using library::core::types::String ;
    using library::core::ctnr::Tuple ;
    using library::core::ctnr::Array ;

    using library::math::obj::Vector3d ;

    using library::physics::time::Instant ;
    using EarthGravitationalModel = library::physics::environment::gravitational::Earth ;

    {

        static const Array<Tuple<EarthGravitationalModel::Type, Vector3d, Instant, Vector3d, Real>> testCases =
        {

            { EarthGravitationalModel::Type::WGS84,   { 6378137.0, 0.0, 0.0 }, Instant::J2000(), { -9.81424104188087, 0.0, 0.0 },                                        1e-10 },
            { EarthGravitationalModel::Type::EGM84,   { 6378137.0, 0.0, 0.0 }, Instant::J2000(), { -9.81430714161684, -2.31935469758198e-05, -1.30080088064139e-05 },    1e-10 },
            { EarthGravitationalModel::Type::EGM96,   { 6378137.0, 0.0, 0.0 }, Instant::J2000(), { -9.81428438755087, -1.81424333238398e-05, 7.75546781913697e-06 },     1e-10 },
            { EarthGravitationalModel::Type::EGM2008, { 6378137.0, 0.0, 0.0 }, Instant::J2000(), { -9.81427987766325, -1.38769560673262e-05, 6.83924677252542e-06 },     1e-10 },

            { EarthGravitationalModel::Type::WGS84,   { 7000e3, 0.0, 0.0 },    Instant::J2000(), { -8.14569530314416, 0.0, 0.0 },                                        1e-10 },
            { EarthGravitationalModel::Type::EGM84,   { 7000e3, 0.0, 0.0 },    Instant::J2000(), { -8.14574728460001, -2.05387541298693e-05, 2.89745888403438e-05 },     1e-10 },
            { EarthGravitationalModel::Type::EGM96,   { 7000e3, 0.0, 0.0 },    Instant::J2000(), { -8.14574567850702, -2.19120214388815e-05, 3.01312644719760e-05 },     1e-10 },
            { EarthGravitationalModel::Type::EGM2008, { 7000e3, 0.0, 0.0 },    Instant::J2000(), { -8.14574563988817, -2.17632276310511e-05, 2.98622097530464e-05 },     1e-10 },

            { EarthGravitationalModel::Type::WGS84,   { 70000e3, 0.0, 0.0 },   Instant::J2000(), { -0.0813481257058837, 0.0, 0.0 },                                      1e-10 },
            { EarthGravitationalModel::Type::EGM84,   { 70000e3, 0.0, 0.0 },   Instant::J2000(), { -0.0813481348043554, -3.13557991717857e-09, 1.04503585231838e-10 },   1e-10 },
            { EarthGravitationalModel::Type::EGM96,   { 70000e3, 0.0, 0.0 },   Instant::J2000(), { -0.0813481348016591, -3.14162880220011e-09, 1.03321189670023e-10 },   1e-10 },
            { EarthGravitationalModel::Type::EGM2008, { 70000e3, 0.0, 0.0 },   Instant::J2000(), { -0.0813481347405648, -3.14187787214874e-09, 1.03341418225995e-10 },   1e-10 },

            { EarthGravitationalModel::Type::WGS84,   { 700000e3, 0.0, 0.0 },  Instant::J2000(), { -0.000813470399061998, 0.0, 0.0 },                                    1e-10 },
            { EarthGravitationalModel::Type::EGM84,   { 700000e3, 0.0, 0.0 },  Instant::J2000(), { -0.000813470400014733, -3.60438110107890e-13, 5.77106688430063e-16 }, 1e-10 },
            { EarthGravitationalModel::Type::EGM96,   { 700000e3, 0.0, 0.0 },  Instant::J2000(), { -0.000813470400014252, -3.61017933053639e-13, 5.21321633031416e-16 }, 1e-10 },
            { EarthGravitationalModel::Type::EGM2008, { 700000e3, 0.0, 0.0 },  Instant::J2000(), { -0.000813470399402024, -3.61045520881784e-13, 5.16916001900846e-16 }, 1e-10 }

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

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////