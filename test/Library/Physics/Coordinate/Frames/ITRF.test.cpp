////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library ▸ Physics
/// @file           Library/Physics/Coordinate/Frames/ITRF.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Environment/Objects/CelestialBodies/Earth.hpp>
#include <Library/Physics/Coordinate/Frame.hpp>
#include <Library/Physics/Units/Length.hpp>
#include <Library/Physics/Units/Derived/Angle.hpp>

#include <Library/Mathematics/Geometry/3D/Transformations/Rotations/RotationMatrix.hpp>
#include <Library/Mathematics/Geometry/3D/Transformations/Rotations/RotationVector.hpp>

#include <Library/Core/FileSystem/File.hpp>
#include <Library/Core/FileSystem/Path.hpp>
#include <Library/Core/Containers/Table.hpp>
#include <Library/Core/Containers/Array.hpp>
#include <Library/Core/Containers/Tuple.hpp>
#include <Library/Core/Types/Real.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Physics_Coordinate_Frames_ITRF, Test)
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
    using library::math::geom::d3::trf::rot::RotationMatrix ;

    using library::physics::units::Length ;
    using library::physics::units::Angle ;
    using library::physics::time::Scale ;
    using library::physics::time::Instant ;
    using library::physics::time::DateTime ;
    using library::physics::coord::Transform ;
    using library::physics::coord::Frame ;
    using library::physics::env::obj::celest::Earth ;

    {

        const Array<Tuple<File, Angle, Length, Length, Real>> referenceScenarios =
        {
            { File::Path(Path::Parse("../test/Library/Physics/Coordinate/Frames/ITRF/Test/ITRF_GCRF 1.csv")), Angle::Arcseconds(1.0), Length::Meters(0.1), Length::Meters(0.1), 1e-12 }, // 1 Jan 2018 00:00:37.000 [TAI] -> 2 Jan 2018 00:00:37.000 [TAI] @ 1.0 [min]
            { File::Path(Path::Parse("../test/Library/Physics/Coordinate/Frames/ITRF/Test/ITRF_GCRF 2.csv")), Angle::Arcseconds(20.0), Length::Meters(1000.0), Length::Meters(1000.0), 1e-10 }, // 1 Jan 2008 00:00:33.000 [TAI] -> 1 Jan 2018 00:00:37.000 [TAI] @ 1.0 [day]
            { File::Path(Path::Parse("../test/Library/Physics/Coordinate/Frames/ITRF/Test/ITRF_GCRF 3.csv")), Angle::Arcseconds(10.0), Length::Meters(1000.0), Length::Meters(1000.0), 1e-8 } // 1 Jan 2018 00:00:37.000 [TAI] -> 30 Jun 2019 00:00:37.000 [TAI] @ 1.0 [day]
        } ;

        for (const auto& referenceScenario : referenceScenarios)
        {

            const Shared<const Frame> gcrfSPtr = Frame::GCRF() ;
            const Shared<const Frame> itrfSPtr = Frame::ITRF() ;

            // Reference data setup

            const File referenceDataFile = std::get<0>(referenceScenario) ;
            const Angle toleranceAngle = std::get<1>(referenceScenario) ;
            const Length positionalToleranceAtSurface = std::get<2>(referenceScenario) ;
            const Length positionalToleranceAt1000km = std::get<3>(referenceScenario) ;
            const Real toleranceAngularVelocity = std::get<4>(referenceScenario) ;

            const Table referenceData = Table::Load(referenceDataFile, Table::Format::CSV, true) ;

            // Test

            for (const auto& referenceRow : referenceData)
            {

                const Instant instant = Instant::DateTime(DateTime::Parse(referenceRow[0].accessString()), Scale::TAI) ;

                const Quaternion reference_q_ITRF_GCRF = Quaternion::XYZS(referenceRow[1].accessReal(), referenceRow[2].accessReal(), referenceRow[3].accessReal(), referenceRow[4].accessReal()).normalize() ;
                const Vector3d reference_w_ITRF_GCRF_in_ITRF = { referenceRow[5].accessReal(), referenceRow[6].accessReal(), referenceRow[7].accessReal() } ;

                // ITRF -> GCRF

                const Transform transform_GCRF_ITRF = itrfSPtr->getTransformTo(gcrfSPtr, instant) ;

                const Quaternion q_GCRF_ITRF = transform_GCRF_ITRF.getOrientation() ;
                const Vector3d w_GCRF_ITRF_in_GCRF = transform_GCRF_ITRF.getAngularVelocity() ;

                // GCRF -> ITRF

                const Transform transform_ITRF_GCRF = gcrfSPtr->getTransformTo(itrfSPtr, instant) ;

                const Quaternion q_ITRF_GCRF = transform_ITRF_GCRF.getOrientation() ;
                const Vector3d w_ITRF_GCRF_in_ITRF = transform_ITRF_GCRF.getAngularVelocity() ;

                // Instant

                {

                    EXPECT_EQ(instant, transform_GCRF_ITRF.getInstant()) ;

                }

                // Translation

                {

                    EXPECT_EQ(Vector3d(0.0, 0.0, 0.0), transform_GCRF_ITRF.getTranslation()) ;

                }

                // Velocity

                {

                    EXPECT_EQ(Vector3d(0.0, 0.0, 0.0), transform_GCRF_ITRF.getVelocity()) ;

                }

                // Orientation

                ASSERT_EQ(q_GCRF_ITRF, q_ITRF_GCRF.toConjugate()) ;

                {

                    const Angle delta = RotationVector::Quaternion((q_GCRF_ITRF.toConjugate() / reference_q_ITRF_GCRF).rectify().normalize()).getAngle() ;

                    ASSERT_GT(toleranceAngle.inDegrees(), delta.inDegrees()) << String::Format("{} - {} [deg] > {} [deg]", instant.toString(Scale::TAI), toleranceAngle.inDegrees().toString(), delta.inDegrees().toString()) ;

                }

                {

                    const Angle delta = RotationVector::Quaternion((q_ITRF_GCRF / reference_q_ITRF_GCRF).rectify().normalize()).getAngle() ;

                    ASSERT_GT(toleranceAngle.inDegrees(), delta.inDegrees()) << String::Format("{} - {} [deg] > {} [deg]", instant.toString(Scale::TAI), toleranceAngle.inDegrees().toString(), delta.inDegrees().toString()) ;

                }

                {

                    const Length positionalDelta = Earth::EquatorialRadius * (q_GCRF_ITRF * Vector3d::X() - (reference_q_ITRF_GCRF.toConjugate() * Vector3d::X())).norm() ;

                    ASSERT_GT(positionalToleranceAtSurface, positionalDelta) << String::Format("{} - {} > {}", instant.toString(Scale::TAI), positionalToleranceAtSurface.toString(), positionalDelta.toString()) ;

                }

                {

                    const Length positionalDelta = (Earth::EquatorialRadius + Length::Kilometers(1000.0)) * (q_GCRF_ITRF * Vector3d::X() - (reference_q_ITRF_GCRF.toConjugate() * Vector3d::X())).norm() ;

                    ASSERT_GT(positionalToleranceAt1000km, positionalDelta) << String::Format("{} - {} > {}", instant.toString(Scale::TAI), positionalToleranceAt1000km.toString(), positionalDelta.toString()) ;

                }

                // Angular velocity

                {

                    const Vector3d test_w_GCRF_ITRF_in_GCRF = (q_ITRF_GCRF.toConjugate() * (-w_ITRF_GCRF_in_ITRF)) ;

                    ASSERT_TRUE(test_w_GCRF_ITRF_in_GCRF.isNear(w_GCRF_ITRF_in_GCRF, toleranceAngularVelocity)) << String::Format("{} - {} [rad/s] > {} [rad/s]", instant.toString(Scale::TAI), test_w_GCRF_ITRF_in_GCRF.toString(), w_GCRF_ITRF_in_GCRF.toString()) ;

                }

                {

                    const Real deltaAngularVelocity = (w_ITRF_GCRF_in_ITRF - reference_w_ITRF_GCRF_in_ITRF).norm() ;

                    ASSERT_GT(toleranceAngularVelocity, deltaAngularVelocity) << String::Format("{} - {} [rad/s] > {} [rad/s]", instant.toString(Scale::TAI), toleranceAngularVelocity.toString(), deltaAngularVelocity.toString()) ;

                }

            }

        }

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
