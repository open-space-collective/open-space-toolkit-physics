////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/TEME.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/ITRF.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/TEME.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Units/Derived/Angle.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/RotationVector.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/Quaternion.hpp>
#include <OpenSpaceToolkit/Mathematics/Objects/Vector.hpp>

#include <OpenSpaceToolkit/Core/Containers/Table.hpp>
#include <OpenSpaceToolkit/Core/Containers/Array.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_TEME, GetTransformAt)
{

    using ostk::core::ctnr::Pair ;
    using ostk::core::ctnr::Array ;
    using ostk::core::ctnr::Table ;
    using ostk::core::fs::Path ;
    using ostk::core::fs::File ;

    using ostk::math::geom::d3::trf::rot::Quaternion ;
    using ostk::math::geom::d3::trf::rot::RotationVector ;

    using ostk::physics::units::Angle ;
    using ostk::physics::time::Scale ;
    using ostk::physics::time::Instant ;
    using ostk::physics::time::DateTime ;
    using ostk::physics::coord::Frame ;
    using ostk::physics::coord::frame::Transform ;
    using ostk::physics::coord::frame::provider::TEME ;

    {

        const Array<Pair<File, Angle>> referenceScenarios =
        {
            { File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/TEME/Scenario_A/Scenario ITRF_TEME.csv")), Angle::Arcseconds(1.0) },
            { File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/TEME/Scenario_B/Scenario ITRF_TEME.csv")), Angle::Arcseconds(20.0) }
        } ;

        for (const auto& referenceScenario : referenceScenarios)
        {

            const TEME temeFrameProvider ;

            // Reference data setup

            const File referenceDataFile = referenceScenario.first ;

            const Table referenceData = Table::Load(referenceDataFile, Table::Format::CSV, true) ;

            // Test

            for (const auto& referenceRow : referenceData)
            {

                const Instant instant = Instant::DateTime(DateTime::Parse(referenceRow[0].accessString()), Scale::UTC) ;

                const Quaternion referenceOrientation_ITRF_TEME = Quaternion::XYZS(referenceRow[1].accessReal(), referenceRow[2].accessReal(), referenceRow[3].accessReal(), referenceRow[4].accessReal()).normalize().conjugate() ;
                const Quaternion referenceOrientation_GCRF_TEME = Quaternion::XYZS(referenceRow[5].accessReal(), referenceRow[6].accessReal(), referenceRow[7].accessReal(), referenceRow[8].accessReal()).normalize() ;

                const Transform transform_TEME_ITRF = temeFrameProvider.getTransformAt(instant) ;

                const Quaternion dq_ITRF = (transform_TEME_ITRF.getOrientation() / referenceOrientation_ITRF_TEME).normalize().rectify() ;

                const Transform transform_TEME_GCRF = Frame::GCRF()->getTransformTo(Frame::TEME(), instant) ;

                const Quaternion dq_GCRF = (transform_TEME_GCRF.getOrientation() / referenceOrientation_GCRF_TEME).normalize().rectify() ;

                const Angle toleranceAngle = referenceScenario.second ;

                EXPECT_GT(toleranceAngle.inDegrees(), RotationVector::Quaternion(dq_ITRF).getAngle().inDegrees()) ;
                EXPECT_GT(toleranceAngle.inDegrees(), RotationVector::Quaternion(dq_GCRF).getAngle().inDegrees()) ;

                // std::cout << instant.toString()
                // << " : [TEME - ITRF]" << referenceOrientation_ITRF_TEME.toString(15) << " " << transform_TEME_ITRF.getOrientation().toString(15)
                // << " >> " << RotationVector::Quaternion(dq_ITRF).getAngle().inArcseconds().toString(3) << " [asec]"
                // << " : [TEME - GCRF]" << referenceOrientation_GCRF_TEME.toString(15) << " " << transform_TEME_GCRF.getOrientation().toString(15)
                // << " >> " << RotationVector::Quaternion(dq_GCRF).getAngle().inArcseconds().toString(3) << " [asec]" << std::endl ;

                // [TBI] Add angular velocity test

            }

        }

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
