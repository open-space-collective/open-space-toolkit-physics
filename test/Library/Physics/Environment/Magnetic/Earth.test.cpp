////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Environment/Magnetic/Earth.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Environment/Magnetic/Earth/Manager.hpp>
#include <Library/Physics/Environment/Magnetic/Earth.hpp>
#include <Library/Physics/Time/Instant.hpp>
#include <Library/Physics/Time/DateTime.hpp>
#include <Library/Physics/Time/Scale.hpp>

#include <Library/Core/FileSystem/File.hpp>
#include <Library/Core/FileSystem/Path.hpp>
#include <Library/Core/Containers/Array.hpp>
#include <Library/Core/Containers/Tuple.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Physics_Environment_Magnetic_Earth, Constructor)
{

    using library::core::fs::Path ;
    using library::core::fs::Directory ;

    using EarthMagneticModel = library::physics::environment::magnetic::Earth ;
    using EarthMagneticModelManager = library::physics::environment::magnetic::earth::Manager ;

    {

        EarthMagneticModelManager::Get().setLocalRepository(Directory::Path(Path::Parse("/app/share/environment/magnetic/earth"))) ;

        EarthMagneticModelManager::Get().enable() ;

        EXPECT_NO_THROW(EarthMagneticModel earthMagneticModel(EarthMagneticModel::Type::Dipole)) ;
        EXPECT_NO_THROW(EarthMagneticModel earthMagneticModel(EarthMagneticModel::Type::EMM2010)) ;
        EXPECT_NO_THROW(EarthMagneticModel earthMagneticModel(EarthMagneticModel::Type::EMM2015)) ;
        EXPECT_NO_THROW(EarthMagneticModel earthMagneticModel(EarthMagneticModel::Type::EMM2017)) ;
        EXPECT_NO_THROW(EarthMagneticModel earthMagneticModel(EarthMagneticModel::Type::IGRF11)) ;
        EXPECT_NO_THROW(EarthMagneticModel earthMagneticModel(EarthMagneticModel::Type::IGRF12)) ;
        EXPECT_NO_THROW(EarthMagneticModel earthMagneticModel(EarthMagneticModel::Type::WMM2010)) ;
        EXPECT_NO_THROW(EarthMagneticModel earthMagneticModel(EarthMagneticModel::Type::WMM2015)) ;

        EarthMagneticModelManager::Get().setLocalRepository(EarthMagneticModelManager::DefaultLocalRepository()) ;

        EarthMagneticModelManager::Get().setEnabled(EarthMagneticModelManager::DefaultEnabled()) ;

    }

    {

        EXPECT_NO_THROW(EarthMagneticModel earthMagneticModel(EarthMagneticModel::Type::Dipole, Directory::Path(Path::Parse("/app/share/environment/magnetic/earth")))) ;
        EXPECT_NO_THROW(EarthMagneticModel earthMagneticModel(EarthMagneticModel::Type::EMM2010, Directory::Path(Path::Parse("/app/share/environment/magnetic/earth")))) ;
        EXPECT_NO_THROW(EarthMagneticModel earthMagneticModel(EarthMagneticModel::Type::EMM2015, Directory::Path(Path::Parse("/app/share/environment/magnetic/earth")))) ;
        EXPECT_NO_THROW(EarthMagneticModel earthMagneticModel(EarthMagneticModel::Type::EMM2017, Directory::Path(Path::Parse("/app/share/environment/magnetic/earth")))) ;
        EXPECT_NO_THROW(EarthMagneticModel earthMagneticModel(EarthMagneticModel::Type::IGRF11, Directory::Path(Path::Parse("/app/share/environment/magnetic/earth")))) ;
        EXPECT_NO_THROW(EarthMagneticModel earthMagneticModel(EarthMagneticModel::Type::IGRF12, Directory::Path(Path::Parse("/app/share/environment/magnetic/earth")))) ;
        EXPECT_NO_THROW(EarthMagneticModel earthMagneticModel(EarthMagneticModel::Type::WMM2010, Directory::Path(Path::Parse("/app/share/environment/magnetic/earth")))) ;
        EXPECT_NO_THROW(EarthMagneticModel earthMagneticModel(EarthMagneticModel::Type::WMM2015, Directory::Path(Path::Parse("/app/share/environment/magnetic/earth")))) ;

    }

    {

        EXPECT_NO_THROW(EarthMagneticModel earthMagneticModel(EarthMagneticModel::Type::Dipole, Directory::Path(Path::Parse("/does/not/exist")))) ;

        EXPECT_ANY_THROW(EarthMagneticModel earthMagneticModel(EarthMagneticModel::Type::EMM2010, Directory::Path(Path::Parse("/does/not/exist")))) ;
        EXPECT_ANY_THROW(EarthMagneticModel earthMagneticModel(EarthMagneticModel::Type::EMM2015, Directory::Path(Path::Parse("/does/not/exist")))) ;
        EXPECT_ANY_THROW(EarthMagneticModel earthMagneticModel(EarthMagneticModel::Type::EMM2017, Directory::Path(Path::Parse("/does/not/exist")))) ;
        EXPECT_ANY_THROW(EarthMagneticModel earthMagneticModel(EarthMagneticModel::Type::IGRF11, Directory::Path(Path::Parse("/does/not/exist")))) ;
        EXPECT_ANY_THROW(EarthMagneticModel earthMagneticModel(EarthMagneticModel::Type::IGRF12, Directory::Path(Path::Parse("/does/not/exist")))) ;
        EXPECT_ANY_THROW(EarthMagneticModel earthMagneticModel(EarthMagneticModel::Type::WMM2010, Directory::Path(Path::Parse("/does/not/exist")))) ;
        EXPECT_ANY_THROW(EarthMagneticModel earthMagneticModel(EarthMagneticModel::Type::WMM2015, Directory::Path(Path::Parse("/does/not/exist")))) ;

    }

}

TEST (Library_Physics_Environment_Magnetic_Earth, Clone)
{

    using library::core::fs::Path ;
    using library::core::fs::Directory ;

    using EarthMagneticModel = library::physics::environment::magnetic::Earth ;
    using EarthMagneticModelManager = library::physics::environment::magnetic::earth::Manager ;

    {

        EarthMagneticModelManager::Get().setLocalRepository(Directory::Path(Path::Parse("/app/share/environment/magnetic/earth"))) ;

        EarthMagneticModelManager::Get().enable() ;

        const EarthMagneticModel earthMagneticModel = { EarthMagneticModel::Type::EMM2017 } ;

        EXPECT_NO_THROW(const EarthMagneticModel* earthMagneticModelPtr = earthMagneticModel.clone() ; delete earthMagneticModelPtr ;) ;

        EarthMagneticModelManager::Get().setLocalRepository(EarthMagneticModelManager::DefaultLocalRepository()) ;

        EarthMagneticModelManager::Get().setEnabled(EarthMagneticModelManager::DefaultEnabled()) ;

    }

}

TEST (Library_Physics_Environment_Magnetic_Earth, GetType)
{

    using library::core::fs::Path ;
    using library::core::fs::Directory ;

    using EarthMagneticModel = library::physics::environment::magnetic::Earth ;
    using EarthMagneticModelManager = library::physics::environment::magnetic::earth::Manager ;

    {

        EarthMagneticModelManager::Get().setLocalRepository(Directory::Path(Path::Parse("/app/share/environment/magnetic/earth"))) ;

        EarthMagneticModelManager::Get().enable() ;

        EXPECT_EQ(EarthMagneticModel::Type::Dipole, EarthMagneticModel(EarthMagneticModel::Type::Dipole).getType()) ;
        EXPECT_EQ(EarthMagneticModel::Type::EMM2010, EarthMagneticModel(EarthMagneticModel::Type::EMM2010).getType()) ;
        EXPECT_EQ(EarthMagneticModel::Type::EMM2015, EarthMagneticModel(EarthMagneticModel::Type::EMM2015).getType()) ;
        EXPECT_EQ(EarthMagneticModel::Type::EMM2017, EarthMagneticModel(EarthMagneticModel::Type::EMM2017).getType()) ;
        EXPECT_EQ(EarthMagneticModel::Type::IGRF11, EarthMagneticModel(EarthMagneticModel::Type::IGRF11).getType()) ;
        EXPECT_EQ(EarthMagneticModel::Type::IGRF12, EarthMagneticModel(EarthMagneticModel::Type::IGRF12).getType()) ;
        EXPECT_EQ(EarthMagneticModel::Type::WMM2010, EarthMagneticModel(EarthMagneticModel::Type::WMM2010).getType()) ;
        EXPECT_EQ(EarthMagneticModel::Type::WMM2015, EarthMagneticModel(EarthMagneticModel::Type::WMM2015).getType()) ;

        EarthMagneticModelManager::Get().setLocalRepository(EarthMagneticModelManager::DefaultLocalRepository()) ;

        EarthMagneticModelManager::Get().setEnabled(EarthMagneticModelManager::DefaultEnabled()) ;

    }

}

TEST (Library_Physics_Environment_Magnetic_Earth, GetFieldValueAt)
{

    using library::core::types::Real ;
    using library::core::types::String ;
    using library::core::ctnr::Tuple ;
    using library::core::ctnr::Array ;
    using library::core::fs::Path ;
    using library::core::fs::Directory ;

    using library::math::obj::Vector3d ;

    using library::physics::time::Scale ;
    using library::physics::time::Instant ;
    using library::physics::time::DateTime ;
    using EarthMagneticModel = library::physics::environment::magnetic::Earth ;
    using EarthMagneticModelManager = library::physics::environment::magnetic::earth::Manager ;

    {

        EarthMagneticModelManager::Get().setLocalRepository(Directory::Path(Path::Parse("/app/share/environment/magnetic/earth"))) ;

        EarthMagneticModelManager::Get().enable() ;

        static const Array<Tuple<EarthMagneticModel::Type, Vector3d, Instant, Vector3d, Real>> testCases =
        {

            { EarthMagneticModel::Type::Dipole,  { 6378137.0, 0.0, 0.0 }, Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { 0.0, 0.0, 0.0 }, 1e-10 },
            { EarthMagneticModel::Type::EMM2010, { 6378137.0, 0.0, 0.0 }, Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { 0.0, 0.0, 0.0 }, 1e-10 },
            { EarthMagneticModel::Type::EMM2015, { 6378137.0, 0.0, 0.0 }, Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { 0.0, 0.0, 0.0 }, 1e-10 },
            { EarthMagneticModel::Type::EMM2017, { 6378137.0, 0.0, 0.0 }, Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { 0.0, 0.0, 0.0 }, 1e-10 },
            { EarthMagneticModel::Type::IGRF11,  { 6378137.0, 0.0, 0.0 }, Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { 0.0, 0.0, 0.0 }, 1e-10 },
            { EarthMagneticModel::Type::IGRF12,  { 6378137.0, 0.0, 0.0 }, Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { 0.0, 0.0, 0.0 }, 1e-10 },
            { EarthMagneticModel::Type::WMM2010, { 6378137.0, 0.0, 0.0 }, Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { 0.0, 0.0, 0.0 }, 1e-10 },
            { EarthMagneticModel::Type::WMM2015, { 6378137.0, 0.0, 0.0 }, Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { 0.0, 0.0, 0.0 }, 1e-10 },

            { EarthMagneticModel::Type::Dipole,  { 7000e3, 0.0, 0.0 },    Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { 0.0, 0.0, 0.0 }, 1e-10 },
            { EarthMagneticModel::Type::EMM2010, { 7000e3, 0.0, 0.0 },    Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { 0.0, 0.0, 0.0 }, 1e-10 },
            { EarthMagneticModel::Type::EMM2015, { 7000e3, 0.0, 0.0 },    Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { 0.0, 0.0, 0.0 }, 1e-10 },
            { EarthMagneticModel::Type::EMM2017, { 7000e3, 0.0, 0.0 },    Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { 0.0, 0.0, 0.0 }, 1e-10 },
            { EarthMagneticModel::Type::IGRF11,  { 7000e3, 0.0, 0.0 },    Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { 0.0, 0.0, 0.0 }, 1e-10 },
            { EarthMagneticModel::Type::IGRF12,  { 7000e3, 0.0, 0.0 },    Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { 0.0, 0.0, 0.0 }, 1e-10 },
            { EarthMagneticModel::Type::WMM2010, { 7000e3, 0.0, 0.0 },    Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { 0.0, 0.0, 0.0 }, 1e-10 },
            { EarthMagneticModel::Type::WMM2015, { 7000e3, 0.0, 0.0 },    Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { 0.0, 0.0, 0.0 }, 1e-10 },

            { EarthMagneticModel::Type::Dipole,  { 70000e3, 0.0, 0.0 },   Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { 0.0, 0.0, 0.0 }, 1e-10 },
            { EarthMagneticModel::Type::EMM2010, { 70000e3, 0.0, 0.0 },   Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { 0.0, 0.0, 0.0 }, 1e-10 },
            { EarthMagneticModel::Type::EMM2015, { 70000e3, 0.0, 0.0 },   Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { 0.0, 0.0, 0.0 }, 1e-10 },
            { EarthMagneticModel::Type::EMM2017, { 70000e3, 0.0, 0.0 },   Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { 0.0, 0.0, 0.0 }, 1e-10 },
            { EarthMagneticModel::Type::IGRF11,  { 70000e3, 0.0, 0.0 },   Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { 0.0, 0.0, 0.0 }, 1e-10 },
            { EarthMagneticModel::Type::IGRF12,  { 70000e3, 0.0, 0.0 },   Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { 0.0, 0.0, 0.0 }, 1e-10 },
            { EarthMagneticModel::Type::WMM2010, { 70000e3, 0.0, 0.0 },   Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { 0.0, 0.0, 0.0 }, 1e-10 },
            { EarthMagneticModel::Type::WMM2015, { 70000e3, 0.0, 0.0 },   Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { 0.0, 0.0, 0.0 }, 1e-10 },

            { EarthMagneticModel::Type::Dipole,  { 700000e3, 0.0, 0.0 },  Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { 0.0, 0.0, 0.0 }, 1e-10 },
            { EarthMagneticModel::Type::EMM2010, { 700000e3, 0.0, 0.0 },  Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { 0.0, 0.0, 0.0 }, 1e-10 },
            { EarthMagneticModel::Type::EMM2015, { 700000e3, 0.0, 0.0 },  Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { 0.0, 0.0, 0.0 }, 1e-10 },
            { EarthMagneticModel::Type::EMM2017, { 700000e3, 0.0, 0.0 },  Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { 0.0, 0.0, 0.0 }, 1e-10 },
            { EarthMagneticModel::Type::IGRF11,  { 700000e3, 0.0, 0.0 },  Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { 0.0, 0.0, 0.0 }, 1e-10 },
            { EarthMagneticModel::Type::IGRF12,  { 700000e3, 0.0, 0.0 },  Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { 0.0, 0.0, 0.0 }, 1e-10 },
            { EarthMagneticModel::Type::WMM2010, { 700000e3, 0.0, 0.0 },  Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { 0.0, 0.0, 0.0 }, 1e-10 },
            { EarthMagneticModel::Type::WMM2015, { 700000e3, 0.0, 0.0 },  Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { 0.0, 0.0, 0.0 }, 1e-10 }

        } ;

        for (const auto& testCase : testCases)
        {

            const EarthMagneticModel earthMagneticModel = { std::get<0>(testCase) } ;

            const Vector3d position = std::get<1>(testCase) ;
            const Instant instant = std::get<2>(testCase) ;

            const Vector3d referenceFieldValue = std::get<3>(testCase) ;
            const Real tolerance = std::get<4>(testCase) ;

            const Vector3d fieldValue = earthMagneticModel.getFieldValueAt(position, instant) ;

            EXPECT_TRUE(fieldValue.isNear(referenceFieldValue, tolerance)) << String::Format("{} ≈ {} Δ {} [T]", fieldValue.toString(), referenceFieldValue.toString(), (fieldValue - referenceFieldValue).norm()) ;

        }

        EarthMagneticModelManager::Get().setLocalRepository(EarthMagneticModelManager::DefaultLocalRepository()) ;

        EarthMagneticModelManager::Get().setEnabled(EarthMagneticModelManager::DefaultEnabled()) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////