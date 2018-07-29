////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Coordinate/Frames/ITRF.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Coordinate/Frame.hpp>
#include <Library/Physics/Units/Derived/Angle.hpp>

#include <Library/Mathematics/Geometry/Transformations/Rotations/RotationMatrix.hpp>
#include <Library/Mathematics/Geometry/Transformations/Rotations/RotationVector.hpp>

#include <Library/Core/FileSystem/File.hpp>
#include <Library/Core/FileSystem/Path.hpp>
#include <Library/Core/Containers/Table.hpp>
#include <Library/Core/Containers/Array.hpp>
#include <Library/Core/Containers/Triple.hpp>
#include <Library/Core/Types/Real.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Physics_Coordinate_Frames_ITRF, Test_1)
{

    using library::core::types::Real ;
    using library::core::ctnr::Triple ;
    using library::core::ctnr::Array ;
    using library::core::ctnr::Table ;
    using library::core::fs::Path ;
    using library::core::fs::File ;

    using library::math::obj::Vector3d ;

    using library::math::geom::trf::rot::Quaternion ;
    using library::math::geom::trf::rot::RotationVector ;
    using library::math::geom::trf::rot::RotationMatrix ;
    
    using library::physics::units::Angle ;
    using library::physics::time::Scale ;
    using library::physics::time::Instant ;
    using library::physics::time::DateTime ;
    using library::physics::coord::Transform ;
    using library::physics::coord::Frame ;

    {

        const Array<Triple<File, Angle, Real>> referenceScenarios =
        {
            { File::Path(Path::Parse("../test/Library/Physics/Coordinate/Frames/ITRF/Test_1/Test_1 ITRF_GCRF.csv")), Angle::Arcseconds(1.0), 1e-12 }
        } ;

        for (const auto& referenceScenario : referenceScenarios)
        {

            const Frame gcrf = Frame::GCRF() ;
            const Frame itrf = Frame::ITRF() ;

            // Reference data setup

            const File referenceDataFile = referenceScenario.first ;

            const Table referenceData = Table::Load(referenceDataFile, Table::Format::CSV, true) ;

            // Test

            for (const auto& referenceRow : referenceData)
            {

                const Instant instant = Instant::DateTime(DateTime::Parse(referenceRow[0].accessString()), Scale::UTC) ;

                const Quaternion reference_q_ITRF_GCRF = Quaternion::XYZS(referenceRow[1].accessReal(), referenceRow[2].accessReal(), referenceRow[3].accessReal(), referenceRow[4].accessReal()).normalize() ;
                const Vector3d reference_w_ITRF_GCRF_in_ITRF = { referenceRow[5].accessReal(), referenceRow[6].accessReal(), referenceRow[7].accessReal() } ;
                
                const Transform transform_GCRF_ITRF = itrf.getTransformTo(gcrf, instant) ;

                const Quaternion q_GCRF_ITRF = transform_GCRF_ITRF.getOrientation() ;
                const Vector3d w_GCRF_ITRF_in_GCRF = transform_GCRF_ITRF.getAngularVelocity() ;

                const Transform transform_ITRF_GCRF = gcrf.getTransformTo(itrf, instant) ;

                const Quaternion q_ITRF_GCRF = transform_ITRF_GCRF.getOrientation() ;
                const Vector3d w_ITRF_GCRF_in_ITRF = transform_ITRF_GCRF.getAngularVelocity() ;

                EXPECT_EQ(q_GCRF_ITRF, q_ITRF_GCRF.toConjugate()) ;
                EXPECT_EQ(w_GCRF_ITRF_in_GCRF, (q_ITRF_GCRF.toConjugate() * (-w_ITRF_GCRF_in_ITRF))) ;

                const Angle toleranceAngle = referenceScenario.second ;

                EXPECT_GT(toleranceAngle.inDegrees(), RotationVector::Quaternion((q_GCRF_ITRF.toConjugate() / reference_q_ITRF_GCRF).rectify().normalize()).getAngle().inDegrees()) ;
                EXPECT_GT(toleranceAngle.inDegrees(), RotationVector::Quaternion((q_ITRF_GCRF / reference_q_ITRF_GCRF).rectify().normalize()).getAngle().inDegrees()) ;

                const Real toleranceAngularVelocity = referenceScenario.third ;

                EXPECT_GT(toleranceAngularVelocity, (w_ITRF_GCRF_in_ITRF - reference_w_ITRF_GCRF_in_ITRF).norm()) ;

            }

        }

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////