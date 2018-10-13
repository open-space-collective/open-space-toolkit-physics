////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Environment/Ephemerides/SPICE.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Environment/Ephemerides/SPICE/Manager.hpp>
#include <Library/Physics/Environment/Ephemerides/SPICE/Engine.hpp>
#include <Library/Physics/Environment/Ephemerides/SPICE.hpp>
#include <Library/Physics/Time/Instant.hpp>
#include <Library/Physics/Time/DateTime.hpp>
#include <Library/Physics/Time/Scale.hpp>

#include <Library/Mathematics/Geometry/3D/Transformations/Rotations/Quaternion.hpp>
#include <Library/Mathematics/Geometry/3D/Transformations/Rotations/RotationVector.hpp>

#include <Library/Core/Containers/Table.hpp>
#include <Library/Core/Containers/Tuple.hpp>
#include <Library/Core/Types/String.hpp>
#include <Library/Core/Types/Real.hpp>
#include <Library/Core/Types/Shared.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Physics_Environment_Ephemerides_SPICE, Constructor)
{

    using library::physics::env::ephem::SPICE ;

    {

        EXPECT_NO_THROW(SPICE spice(SPICE::Object::Earth)) ;

    }

}

TEST (Library_Physics_Environment_Ephemerides_SPICE, IsDefined)
{

    using library::physics::env::ephem::SPICE ;

    {

        const SPICE spice = { SPICE::Object::Earth } ;

        EXPECT_TRUE(spice.isDefined()) ;

    }

}

TEST (Library_Physics_Environment_Ephemerides_SPICE, AccessFrame)
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
    using library::math::geom::d3::trf::rot::Quaternion ;
    using library::math::geom::d3::trf::rot::RotationVector ;

    using library::physics::units::Angle ;
    using library::physics::time::Scale ;
    using library::physics::time::Instant ;
    using library::physics::time::DateTime ;
    using library::physics::coord::Frame ;
    using library::physics::coord::Transform ;
    using library::physics::env::ephem::SPICE ;

    {

        const Array<Tuple<SPICE::Object, File, Real, Real, Real, Real>> referenceScenarios =
        {
            { SPICE::Object::Earth, File::Path(Path::Parse("../test/Library/Physics/Environment/Ephemerides/SPICE/AccessFrame/Scenario_1 Earth.csv")), 0.0, 0.0, 0.03, 1e-10 },
            { SPICE::Object::Sun, File::Path(Path::Parse("../test/Library/Physics/Environment/Ephemerides/SPICE/AccessFrame/Scenario_1 Sun.csv")), 100.0, 1e-5, 0.0, 1e-12 },
            { SPICE::Object::Moon, File::Path(Path::Parse("../test/Library/Physics/Environment/Ephemerides/SPICE/AccessFrame/Scenario_1 Moon.csv")), 10.0, 1e-5, 1.0, 1e-11 }
        } ;

        for (const auto& referenceScenario : referenceScenarios)
        {

            const SPICE::Object object = std::get<0>(referenceScenario) ;
            const File referenceDataFile = std::get<1>(referenceScenario) ;
            const Real positionTolerance_m = std::get<2>(referenceScenario) ;
            const Real velocityTolerance_meterPerSec = std::get<3>(referenceScenario) ;
            const Real orientation_asec = std::get<4>(referenceScenario) ;
            const Real angularVelocityTolerance_radPerSec = std::get<5>(referenceScenario) ;

            const SPICE spice = { object } ;

            const Shared<const Frame> frameSPtr = spice.accessFrame() ;

            const Table referenceData = Table::Load(referenceDataFile, Table::Format::CSV, true) ;

            for (const auto& referenceDataRow : referenceData)
            {

                const Instant instant_reference = Instant::DateTime(DateTime::Parse(referenceDataRow[0].accessString()), Scale::UTC) ;
                const Vector3d x_GCRF_reference = { referenceDataRow[1].accessReal(), referenceDataRow[2].accessReal(), referenceDataRow[3].accessReal() } ;
                const Vector3d v_GCRF_reference = { referenceDataRow[4].accessReal(), referenceDataRow[5].accessReal(), referenceDataRow[6].accessReal() } ;
                const Quaternion q_OBJECT_GCRF_reference = Quaternion::XYZS(referenceDataRow[7].accessReal(), referenceDataRow[8].accessReal(), referenceDataRow[9].accessReal(), referenceDataRow[10].accessReal()).toNormalized() ;
                const Vector3d w_OBJECT_GCRF_in_OBJECT_reference = { referenceDataRow[11].accessReal(), referenceDataRow[12].accessReal(), referenceDataRow[13].accessReal() } ;

                const Vector3d x_GCRF = frameSPtr->getOriginIn(Frame::GCRF(), instant_reference).getCoordinates() ;
                const Vector3d v_GCRF = frameSPtr->getVelocityIn(Frame::GCRF(), instant_reference).getCoordinates() ;
                const Quaternion q_OBJECT_GCRF = Frame::GCRF()->getTransformTo(frameSPtr, instant_reference).getOrientation() ;
                const Vector3d w_OBJECT_GCRF_in_OBJECT = Frame::GCRF()->getTransformTo(frameSPtr, instant_reference).getAngularVelocity() ;

                ASSERT_TRUE(x_GCRF.isNear(x_GCRF_reference, positionTolerance_m)) << String::Format("{} - {} ~ {} = {} [m]", instant_reference.toString(), x_GCRF.toString(), x_GCRF_reference.toString(), (x_GCRF - x_GCRF_reference).norm()) ;
                ASSERT_TRUE(v_GCRF.isNear(v_GCRF_reference, velocityTolerance_meterPerSec)) << String::Format("{} - {} ~ {} = {} [m/s]", instant_reference.toString(), v_GCRF.toString(), v_GCRF_reference.toString(), (v_GCRF - v_GCRF_reference).norm()) ;
                ASSERT_TRUE(q_OBJECT_GCRF.isNear(q_OBJECT_GCRF_reference, Angle::Arcseconds(orientation_asec))) << String::Format("{} - {} ~ {} = {} [asec]", instant_reference.toString(), q_OBJECT_GCRF.toString(), q_OBJECT_GCRF_reference.toString(), q_OBJECT_GCRF.angularDifferenceWith(q_OBJECT_GCRF_reference).inArcseconds().toString()) ;
                ASSERT_TRUE(w_OBJECT_GCRF_in_OBJECT.isNear(w_OBJECT_GCRF_in_OBJECT_reference, angularVelocityTolerance_radPerSec)) << String::Format("{} - {} ~ {} = {} [rad/s]", instant_reference.toString(), w_OBJECT_GCRF_in_OBJECT.toString(), w_OBJECT_GCRF_in_OBJECT_reference.toString(), (w_OBJECT_GCRF_in_OBJECT - w_OBJECT_GCRF_in_OBJECT_reference).norm()) ;

            }

        }

    }

}

TEST (Library_Physics_Environment_Ephemerides_SPICE, StringFromObject)
{

    using library::physics::env::ephem::SPICE ;

    {

        EXPECT_EQ("Sun", SPICE::StringFromObject(SPICE::Object::Sun)) ;
        EXPECT_EQ("Mercury", SPICE::StringFromObject(SPICE::Object::Mercury)) ;
        EXPECT_EQ("Venus", SPICE::StringFromObject(SPICE::Object::Venus)) ;
        EXPECT_EQ("Earth", SPICE::StringFromObject(SPICE::Object::Earth)) ;
        EXPECT_EQ("Moon", SPICE::StringFromObject(SPICE::Object::Moon)) ;
        EXPECT_EQ("Mars", SPICE::StringFromObject(SPICE::Object::Mars)) ;
        EXPECT_EQ("Jupiter", SPICE::StringFromObject(SPICE::Object::Jupiter)) ;
        EXPECT_EQ("Saturn", SPICE::StringFromObject(SPICE::Object::Saturn)) ;
        EXPECT_EQ("Uranus", SPICE::StringFromObject(SPICE::Object::Uranus)) ;
        EXPECT_EQ("Neptune", SPICE::StringFromObject(SPICE::Object::Neptune)) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Physics_Environment_Ephemerides_SPICE, ManualMode)
{

    using library::core::types::Shared ;
    using library::core::types::Real ;
    using library::core::types::String ;
    using library::core::fs::Path ;
    using library::core::fs::File ;
    using library::core::fs::Directory ;

    using library::physics::time::Scale ;
    using library::physics::time::Instant ;
    using library::physics::time::DateTime ;
    using library::physics::coord::Position ;
    using library::physics::coord::Frame ;
    using library::physics::env::ephem::SPICE ;
    using library::physics::env::ephem::spice::Engine ;
    using library::physics::env::ephem::spice::Manager ;
    using library::physics::env::ephem::spice::Kernel ;

    {

        Engine::Get().reset() ;

        Engine::Get().setMode(Engine::Mode::Manual) ;

        const SPICE spice = { SPICE::Object::Sun } ;

        const Shared<const Frame> sunFrameSPtr = spice.accessFrame() ;

        const Instant instant = Instant::DateTime(DateTime(2016, 1, 1, 0, 0, 0), Scale::UTC) ;

        Position sunPosition = Position::Undefined() ;

        EXPECT_ANY_THROW
        (

            {

                sunPosition = sunFrameSPtr->getOriginIn(Frame::GCRF(), instant) ;

            }

        ) ;

        Engine::Get().loadKernel(Kernel::File(File::Path(Path::Parse("/app/share/data/naif0012.tls")))) ;
        Engine::Get().loadKernel(Kernel::File(File::Path(Path::Parse("/app/share/data/de430.bsp")))) ;
        Engine::Get().loadKernel(Kernel::File(File::Path(Path::Parse("/app/share/data/pck00010.tpc")))) ;

        EXPECT_NO_THROW
        (

            {

                sunPosition = sunFrameSPtr->getOriginIn(Frame::GCRF(), instant) ;

            }

        ) ;

        EXPECT_TRUE(sunPosition.isDefined()) ;

        Engine::Get().reset() ;

        Engine::Get().setMode(Engine::Mode::Automatic) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////