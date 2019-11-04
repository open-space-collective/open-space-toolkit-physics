////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library ▸ Physics
/// @file           Library/Physics/Environment/Objects/CelestialBodies/Earth.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Environment/Objects/CelestialBodies/Earth.hpp>
#include <Library/Physics/Environment.hpp>
#include <Library/Physics/Coordinate/Spherical/LLA.hpp>
#include <Library/Physics/Time/Interval.hpp>
#include <Library/Physics/Time/Duration.hpp>
#include <Library/Physics/Time/Instant.hpp>
#include <Library/Physics/Time/DateTime.hpp>
#include <Library/Physics/Time/Scale.hpp>
#include <Library/Physics/Units/Length.hpp>

#include <Library/Mathematics/Geometry/3D/Transformations/Rotations/RotationVector.hpp>
#include <Library/Mathematics/Geometry/3D/Transformations/Rotations/Quaternion.hpp>
#include <Library/Mathematics/Geometry/3D/Intersection.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Pyramid.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Ellipsoid.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Polygon.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Segment.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/LineString.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Point.hpp>
#include <Library/Mathematics/Geometry/2D/Objects/Polygon.hpp>
#include <Library/Mathematics/Geometry/2D/Objects/Point.hpp>

#include <Library/Core/Containers/Table.hpp>
#include <Library/Core/Containers/Map.hpp>
#include <Library/Core/Containers/Triple.hpp>
#include <Library/Core/Types/String.hpp>
#include <Library/Core/Types/Weak.hpp>
#include <Library/Core/Types/Shared.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// TEST (Library_Physics_Environment_Objects_CelestialBodies_Earth, Constructor)
// {

//     using library::physics::env::obj::celest::Earth ;

//     {

//         FAIL() ;

//     }

// }

TEST (Library_Physics_Environment_Objects_CelestialBodies_Earth, GetFrameAt)
{

    using library::core::types::Shared ;
    using library::core::types::String ;
    using library::core::ctnr::Triple ;
    using library::core::ctnr::Array ;
    using library::core::ctnr::Table ;
    using library::core::fs::Path ;
    using library::core::fs::File ;

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::trf::rot::Quaternion ;
    using library::math::geom::d3::trf::rot::RotationVector ;

    using library::physics::units::Length ;
    using library::physics::units::Angle ;
    using library::physics::time::Scale ;
    using library::physics::time::Instant ;
    using library::physics::time::DateTime ;
    using library::physics::time::Duration ;
    using library::physics::coord::spherical::LLA ;
    using library::physics::coord::Frame ;
    using library::physics::env::obj::celest::Earth ;

    {

        const Earth earth = Earth::Default() ;

        const Array<Triple<LLA, File, File>> referenceScenarios =
        {
            { { Angle::Degrees(0.0), Angle::Degrees(0.0), Length::Kilometers(0.01716) }, File::Path(Path::Parse("/app/test/Library/Physics/Environment/Objects/CelestialBodies/Earth/GetFrameAt/NED_ITRF 1.csv")), File::Path(Path::Parse("/app/test/Library/Physics/Environment/Objects/CelestialBodies/Earth/GetFrameAt/NED_GCRF 1.csv")) },
            { { Angle::Degrees(36.5), Angle::Degrees(-123.6), Length::Kilometers(-0.0379749) }, File::Path(Path::Parse("/app/test/Library/Physics/Environment/Objects/CelestialBodies/Earth/GetFrameAt/NED_ITRF 2.csv")), File::Path(Path::Parse("/app/test/Library/Physics/Environment/Objects/CelestialBodies/Earth/GetFrameAt/NED_GCRF 2.csv")) },
            { { Angle::Degrees(90.0), Angle::Degrees(123.456), Length::Kilometers(0.0136095) }, File::Path(Path::Parse("/app/test/Library/Physics/Environment/Objects/CelestialBodies/Earth/GetFrameAt/NED_ITRF 3.csv")), File::Path(Path::Parse("/app/test/Library/Physics/Environment/Objects/CelestialBodies/Earth/GetFrameAt/NED_GCRF 3.csv")) },
            { { Angle::Degrees(-90.0), Angle::Degrees(-95.31), Length::Kilometers(-0.0295348 ) }, File::Path(Path::Parse("/app/test/Library/Physics/Environment/Objects/CelestialBodies/Earth/GetFrameAt/NED_ITRF 4.csv")), File::Path(Path::Parse("/app/test/Library/Physics/Environment/Objects/CelestialBodies/Earth/GetFrameAt/NED_GCRF 4.csv")) }
        } ;

        for (const auto& referenceScenario : referenceScenarios)
        {

            const LLA lla = referenceScenario.first ;

            const Shared<const Frame> nedSPtr = earth.getFrameAt(lla, Earth::FrameType::NED) ;

            const File referenceNedItrfFile = referenceScenario.second ;
            const File referenceNedGcrfFile = referenceScenario.third ;

            const Table referenceNedItrfData = Table::Load(referenceNedItrfFile, Table::Format::CSV, true) ;
            const Table referenceNedGcrfData = Table::Load(referenceNedGcrfFile, Table::Format::CSV, true) ;

            for (const auto& referenceNedItrfRow : referenceNedItrfData)
            {

                const Instant instant = Instant::DateTime(DateTime::Parse(referenceNedItrfRow[0].accessString()), Scale::UTC) ;

                const Quaternion q_NED_ITRF_ref = Quaternion::XYZS(referenceNedItrfRow[1].accessReal(), referenceNedItrfRow[2].accessReal(), referenceNedItrfRow[3].accessReal(), referenceNedItrfRow[4].accessReal()).normalize() ;
                const Vector3d w_NED_ITRF_in_NED_ref = { referenceNedItrfRow[5].accessReal(), referenceNedItrfRow[6].accessReal(), referenceNedItrfRow[7].accessReal() } ;

                const Quaternion q_ITRF_NED_ref = q_NED_ITRF_ref.toConjugate() ;
                const Vector3d w_ITRF_NED_in_ITRF_ref = - (q_ITRF_NED_ref * w_NED_ITRF_in_NED_ref) ;

                const Quaternion q_ITRF_NED = nedSPtr->getTransformTo(Frame::ITRF(), instant).getOrientation() ;
                const Vector3d w_ITRF_NED_in_ITRF = nedSPtr->getTransformTo(Frame::ITRF(), instant).getAngularVelocity() ;

                EXPECT_TRUE(q_ITRF_NED.isNear(q_ITRF_NED_ref, Angle::Arcseconds(1.0))) << String::Format("{} / {} ? {} [asec]", q_ITRF_NED_ref.toString(), q_ITRF_NED.toString(), q_ITRF_NED.angularDifferenceWith(q_ITRF_NED_ref).inArcseconds().toString()) ;
                EXPECT_TRUE(w_ITRF_NED_in_ITRF.isNear(w_ITRF_NED_in_ITRF_ref, 1e-12)) << String::Format("{} - {} ? {} [rad/s]", w_ITRF_NED_in_ITRF_ref.toString(), w_ITRF_NED_in_ITRF.toString(), (w_ITRF_NED_in_ITRF - w_ITRF_NED_in_ITRF_ref).norm()) ;

            }

            for (const auto& referenceNedGcrfRow : referenceNedGcrfData)
            {

                const Instant instant = Instant::DateTime(DateTime::Parse(referenceNedGcrfRow[0].accessString()), Scale::UTC) ;

                const Quaternion q_NED_GCRF_ref = Quaternion::XYZS(referenceNedGcrfRow[1].accessReal(), referenceNedGcrfRow[2].accessReal(), referenceNedGcrfRow[3].accessReal(), referenceNedGcrfRow[4].accessReal()).normalize() ;
                const Vector3d w_NED_GCRF_in_NED_ref = { referenceNedGcrfRow[5].accessReal(), referenceNedGcrfRow[6].accessReal(), referenceNedGcrfRow[7].accessReal() } ;

                const Quaternion q_GCRF_NED_ref = q_NED_GCRF_ref.toConjugate() ;
                const Vector3d w_GCRF_NED_in_GCRF_ref = - (q_GCRF_NED_ref * w_NED_GCRF_in_NED_ref) ;

                const Quaternion q_GCRF_NED = nedSPtr->getTransformTo(Frame::GCRF(), instant).getOrientation() ;
                const Vector3d w_GCRF_NED_in_GCRF = nedSPtr->getTransformTo(Frame::GCRF(), instant).getAngularVelocity() ;

                EXPECT_TRUE(q_GCRF_NED.isNear(q_GCRF_NED_ref, Angle::Arcseconds(1.0))) << String::Format("{} / {} ? {} [asec]", q_GCRF_NED_ref.toString(), q_GCRF_NED.toString(), q_GCRF_NED.angularDifferenceWith(q_GCRF_NED_ref).inArcseconds().toString()) ;
                EXPECT_TRUE(w_GCRF_NED_in_GCRF.isNear(w_GCRF_NED_in_GCRF_ref, 1e-12)) << String::Format("{} - {} ? {} [rad/s]", w_GCRF_NED_in_GCRF_ref.toString(), w_GCRF_NED_in_GCRF.toString(), (w_GCRF_NED_in_GCRF - w_GCRF_NED_in_GCRF_ref).norm()) ;

            }

        }

    }

}

TEST (Library_Physics_Environment_Objects_CelestialBodies_Earth, Default)
{

    using library::physics::env::obj::celest::Earth ;

    {

        EXPECT_NO_THROW(Earth::Default()) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
