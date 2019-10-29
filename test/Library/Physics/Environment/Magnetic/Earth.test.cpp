////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library ▸ Physics
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

        EarthMagneticModelManager::Get().setLocalRepository(Directory::Path(Path::Parse("/app/test/Library/Physics/Environment/Magnetic/Earth"))) ;

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

        EXPECT_NO_THROW(EarthMagneticModel earthMagneticModel(EarthMagneticModel::Type::Dipole, Directory::Path(Path::Parse("/app/test/Library/Physics/Environment/Magnetic/Earth")))) ;
        EXPECT_NO_THROW(EarthMagneticModel earthMagneticModel(EarthMagneticModel::Type::EMM2010, Directory::Path(Path::Parse("/app/test/Library/Physics/Environment/Magnetic/Earth")))) ;
        EXPECT_NO_THROW(EarthMagneticModel earthMagneticModel(EarthMagneticModel::Type::EMM2015, Directory::Path(Path::Parse("/app/test/Library/Physics/Environment/Magnetic/Earth")))) ;
        EXPECT_NO_THROW(EarthMagneticModel earthMagneticModel(EarthMagneticModel::Type::EMM2017, Directory::Path(Path::Parse("/app/test/Library/Physics/Environment/Magnetic/Earth")))) ;
        EXPECT_NO_THROW(EarthMagneticModel earthMagneticModel(EarthMagneticModel::Type::IGRF11, Directory::Path(Path::Parse("/app/test/Library/Physics/Environment/Magnetic/Earth")))) ;
        EXPECT_NO_THROW(EarthMagneticModel earthMagneticModel(EarthMagneticModel::Type::IGRF12, Directory::Path(Path::Parse("/app/test/Library/Physics/Environment/Magnetic/Earth")))) ;
        EXPECT_NO_THROW(EarthMagneticModel earthMagneticModel(EarthMagneticModel::Type::WMM2010, Directory::Path(Path::Parse("/app/test/Library/Physics/Environment/Magnetic/Earth")))) ;
        EXPECT_NO_THROW(EarthMagneticModel earthMagneticModel(EarthMagneticModel::Type::WMM2015, Directory::Path(Path::Parse("/app/test/Library/Physics/Environment/Magnetic/Earth")))) ;

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

        EarthMagneticModelManager::Get().setLocalRepository(Directory::Path(Path::Parse("/app/test/Library/Physics/Environment/Magnetic/Earth"))) ;

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

        EarthMagneticModelManager::Get().setLocalRepository(Directory::Path(Path::Parse("/app/test/Library/Physics/Environment/Magnetic/Earth"))) ;

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

        EarthMagneticModelManager::Get().setLocalRepository(Directory::Path(Path::Parse("/app/test/Library/Physics/Environment/Magnetic/Earth"))) ;

        EarthMagneticModelManager::Get().enable() ;

        static const Array<Tuple<EarthMagneticModel::Type, Vector3d, Instant, Vector3d, Real>> testCases =
        {

            { EarthMagneticModel::Type::Dipole,  { 6378137.0, 0.0, 0.0 }, Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { -3.32722007216433e-06, -5.06143921819291e-06, +2.94583020764477e-05 }, 1e-15 },
            { EarthMagneticModel::Type::EMM2010, { 6378137.0, 0.0, 0.0 }, Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { +1.58827862012718e-05, -2.63805383930342e-06, +2.75101378343132e-05 }, 1e-15 },
            { EarthMagneticModel::Type::EMM2015, { 6378137.0, 0.0, 0.0 }, Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { +1.59008952780146e-05, -2.63958704246927e-06, +2.75090247266022e-05 }, 1e-15 },
            { EarthMagneticModel::Type::EMM2017, { 6378137.0, 0.0, 0.0 }, Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { +1.59316276225456e-05, -2.69855148501253e-06, +2.75243551907758e-05 }, 1e-15 },
            { EarthMagneticModel::Type::IGRF11,  { 6378137.0, 0.0, 0.0 }, Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { +1.58844551141670e-05, -2.62501392504622e-06, +2.75640995568546e-05 }, 1e-15 },
            { EarthMagneticModel::Type::IGRF12,  { 6378137.0, 0.0, 0.0 }, Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { +1.57970940783061e-05, -2.62339310274727e-06, +2.75482784425407e-05 }, 1e-15 },
            { EarthMagneticModel::Type::WMM2010, { 6378137.0, 0.0, 0.0 }, Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { +1.58626311359236e-05, -2.67314942733641e-06, +2.75870918997447e-05 }, 1e-15 },
            { EarthMagneticModel::Type::WMM2015, { 6378137.0, 0.0, 0.0 }, Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { +1.58069379649711e-05, -2.63089832362699e-06, +2.75424226430444e-05 }, 1e-15 },

            { EarthMagneticModel::Type::Dipole,  { 7000e3, 0.0, 0.0 },    Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { -2.51691725295581e-06, -3.82878902409667e-06, +2.22841011808290e-05 }, 1e-15 },
            { EarthMagneticModel::Type::EMM2010, { 7000e3, 0.0, 0.0 },    Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { +9.75689421631405e-06, -2.11723157526624e-06, +2.04720912850195e-05 }, 1e-15 },
            { EarthMagneticModel::Type::EMM2015, { 7000e3, 0.0, 0.0 },    Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { +9.75409996834859e-06, -2.13173699914994e-06, +2.04607003709221e-05 }, 1e-15 },
            { EarthMagneticModel::Type::EMM2017, { 7000e3, 0.0, 0.0 },    Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { +9.75637607892571e-06, -2.13186105666252e-06, +2.04619396634262e-05 }, 1e-15 },
            { EarthMagneticModel::Type::IGRF11,  { 7000e3, 0.0, 0.0 },    Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { +9.80353686311849e-06, -2.13880127231550e-06, +2.04759177339237e-05 }, 1e-15 },
            { EarthMagneticModel::Type::IGRF12,  { 7000e3, 0.0, 0.0 },    Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { +9.75513007678296e-06, -2.13348210823664e-06, +2.04615638145082e-05 }, 1e-15 },
            { EarthMagneticModel::Type::WMM2010, { 7000e3, 0.0, 0.0 },    Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { +9.79347538879988e-06, -2.16450411415906e-06, +2.04846594310706e-05 }, 1e-15 },
            { EarthMagneticModel::Type::WMM2015, { 7000e3, 0.0, 0.0 },    Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { +9.75777875313271e-06, -2.13475991153943e-06, +2.04591421094226e-05 }, 1e-15 },

            { EarthMagneticModel::Type::Dipole,  { 70000e3, 0.0, 0.0 },   Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { -2.51691725295581e-09, -3.82878902409667e-09, +2.22841011808290e-08 }, 1e-15 },
            { EarthMagneticModel::Type::EMM2010, { 70000e3, 0.0, 0.0 },   Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { -1.67106544586857e-09, -3.52280983508088e-09, +2.18417880978892e-08 }, 1e-15 },
            { EarthMagneticModel::Type::EMM2015, { 70000e3, 0.0, 0.0 },   Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { -1.66488718766150e-09, -3.53215983137633e-09, +2.18405404966680e-08 }, 1e-15 },
            { EarthMagneticModel::Type::EMM2017, { 70000e3, 0.0, 0.0 },   Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { -1.66320357347560e-09, -3.53230454059526e-09, +2.18410975151295e-08 }, 1e-15 },
            { EarthMagneticModel::Type::IGRF11,  { 70000e3, 0.0, 0.0 },   Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { -1.66454390207999e-09, -3.53592226084071e-09, +2.18393827626312e-08 }, 1e-15 },
            { EarthMagneticModel::Type::IGRF12,  { 70000e3, 0.0, 0.0 },   Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { -1.66436184894106e-09, -3.53276139090524e-09, +2.18404401512647e-08 }, 1e-15 },
            { EarthMagneticModel::Type::WMM2010, { 70000e3, 0.0, 0.0 },   Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { -1.66690975683029e-09, -3.54688928646407e-09, +2.18389495523421e-08 }, 1e-15 },
            { EarthMagneticModel::Type::WMM2015, { 70000e3, 0.0, 0.0 },   Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { -1.66451227483384e-09, -3.53207231358455e-09, +2.18378525682956e-08 }, 1e-15 },

            { EarthMagneticModel::Type::Dipole,  { 700000e3, 0.0, 0.0 },  Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { -2.51691725295581e-12, -3.82878902409666e-12, +2.22841011808290e-11 }, 1e-15 },
            { EarthMagneticModel::Type::EMM2010, { 700000e3, 0.0, 0.0 },  Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { -2.21601407887724e-12, -3.60013117877065e-12, +2.21642653493488e-11 }, 1e-15 },
            { EarthMagneticModel::Type::EMM2015, { 700000e3, 0.0, 0.0 },  Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { -2.20855216343295e-12, -3.60872335164632e-12, +2.21633814933400e-11 }, 1e-15 },
            { EarthMagneticModel::Type::EMM2017, { 700000e3, 0.0, 0.0 },  Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { -2.20689931026133e-12, -3.60887953401419e-12, +2.21639099057700e-11 }, 1e-15 },
            { EarthMagneticModel::Type::IGRF11,  { 700000e3, 0.0, 0.0 },  Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { -2.20988935842532e-12, -3.61233166112421e-12, +2.21615372056198e-11 }, 1e-15 },
            { EarthMagneticModel::Type::IGRF12,  { 700000e3, 0.0, 0.0 },  Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { -2.20795812746312e-12, -3.60929310317174e-12, +2.21633455227106e-11 }, 1e-15 },
            { EarthMagneticModel::Type::WMM2010, { 700000e3, 0.0, 0.0 },  Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { -2.21203020201404e-12, -3.62279377246905e-12, +2.21608867283079e-11 }, 1e-15 },
            { EarthMagneticModel::Type::WMM2015, { 700000e3, 0.0, 0.0 },  Instant::DateTime(DateTime(2015, 1, 1, 0, 0, 0), Scale::UTC), { -2.20810867125218e-12, -3.60861333200892e-12, +2.21607113255386e-11 }, 1e-15 }

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
