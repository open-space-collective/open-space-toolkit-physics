////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Coordinate/Frame/Providers/TEME.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Coordinate/Frame/Providers/ITRF.hpp>
#include <Library/Physics/Coordinate/Frame/Providers/TEME.hpp>
#include <Library/Physics/Coordinate/Frame.hpp>
#include <Library/Physics/Units/Derived/Angle.hpp>

#include <Library/Mathematics/Geometry/Transformations/Rotations/RotationVector.hpp>
#include <Library/Mathematics/Geometry/Transformations/Rotations/Quaternion.hpp>
#include <Library/Mathematics/Objects/Vector.hpp>

#include <Library/Core/Containers/Table.hpp>
#include <Library/Core/Containers/Array.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Physics_Coordinate_Frame_Providers_TEME, GetTransformAt)
{

    using library::core::ctnr::Pair ;
    using library::core::ctnr::Array ;
    using library::core::ctnr::Table ;
    using library::core::fs::Path ;
    using library::core::fs::File ;

    using library::math::geom::trf::rot::Quaternion ;
    using library::math::geom::trf::rot::RotationVector ;

    using library::physics::units::Angle ;
    using library::physics::time::Scale ;
    using library::physics::time::Instant ;
    using library::physics::time::DateTime ;
    using library::physics::coord::Frame ;
    using library::physics::coord::frame::Transform ;
    using library::physics::coord::frame::provider::TEME ;

    // {

    //     const Array<Pair<File, Angle>> referenceScenarios =
    //     {
    //         { File::Path(Path::Parse("../test/Library/Physics/Coordinate/Frame/Providers/TEME/Scenario_A/Scenario ITRF_TEME.csv")), Angle::Arcseconds(1.0) }, 
    //         { File::Path(Path::Parse("../test/Library/Physics/Coordinate/Frame/Providers/TEME/Scenario_B/Scenario ITRF_TEME.csv")), Angle::Arcseconds(20.0) }
    //     } ;

    //     for (const auto& referenceScenario : referenceScenarios)
    //     {

    //         const TEME temeFrameProvider ;

    //         // Reference data setup

    //         const File referenceDataFile = referenceScenario.first ;

    //         const Table referenceData = Table::Load(referenceDataFile, Table::Format::CSV, true) ;

    //         // Test

    //         for (const auto& referenceRow : referenceData)
    //         {

    //             const Instant instant = Instant::DateTime(DateTime::Parse(referenceRow[0].accessString()), Scale::UTC) ;

    //             const Quaternion referenceOrientation_ITRF_TEME = Quaternion::XYZS(referenceRow[1].accessReal(), referenceRow[2].accessReal(), referenceRow[3].accessReal(), referenceRow[4].accessReal()).normalize().conjugate() ;
    //             const Quaternion referenceOrientation_GCRF_TEME = Quaternion::XYZS(referenceRow[5].accessReal(), referenceRow[6].accessReal(), referenceRow[7].accessReal(), referenceRow[8].accessReal()).normalize() ;

    //             const Transform transform_TEME_ITRF = temeFrameProvider.getTransformAt(instant) ;

    //             const Quaternion dq_ITRF = (transform_TEME_ITRF.getOrientation() / referenceOrientation_ITRF_TEME).normalize().rectify() ;

    //             const Transform transform_TEME_GCRF = Frame::GCRF().getTransformTo(Frame::TEME(), instant) ;

    //             const Quaternion dq_GCRF = (transform_TEME_GCRF.getOrientation() / referenceOrientation_GCRF_TEME).normalize().rectify() ;

    //             // std::cout << instant.toString() 
    //             // << " : [TEME - ITRF]" << referenceOrientation_ITRF_TEME.toString(15) << " " << transform_TEME_ITRF.getOrientation().toString(15)
    //             // << " >> " << RotationVector::Quaternion(dq_ITRF).getAngle().inArcseconds().toString(3) << " [asec]"
    //             // << " : [TEME - GCRF]" << referenceOrientation_GCRF_TEME.toString(15) << " " << transform_TEME_GCRF.getOrientation().toString(15)
    //             // << " >> " << RotationVector::Quaternion(dq_GCRF).getAngle().inArcseconds().toString(3) << " [asec]" << std::endl ;

    //             const Angle toleranceAngle = referenceScenario.second ;

    //             EXPECT_GT(toleranceAngle.inDegrees(), RotationVector::Quaternion(dq_ITRF).getAngle().inDegrees()) ;
    //             EXPECT_GT(toleranceAngle.inDegrees(), RotationVector::Quaternion(dq_GCRF).getAngle().inDegrees()) ;

    //         }

    //     }

    // }

    {

        using library::math::obj::Vector3d ;

        using library::physics::coord::frame::provider::ITRF ;

        const Instant instant = Instant::DateTime(DateTime(2018, 7, 26, 13, 48, 27, 81), Scale::UTC) ;

        std::cout << "instant = " << instant.toString() << std::endl ;

        const TEME temeFrameProvider ;

        const Transform transform_TEME_ITRF = temeFrameProvider.getTransformAt(instant) ;
        
        std::cout << "transform_TEME_ITRF = " << std::endl << transform_TEME_ITRF << std::endl ;
        std::cout << "q_TEME_ITRF = " << transform_TEME_ITRF.getOrientation().toString(15) << std::endl ;
        std::cout << "rot_TEME_ITRF = " << RotationVector::Quaternion(transform_TEME_ITRF.getOrientation()).getAxis().toString(3) << " | " << RotationVector::Quaternion(transform_TEME_ITRF.getOrientation()).getAngle().inDegrees().toString(3) << std::endl ;
        std::cout << "(ITRF.x)_TEME = " << (transform_TEME_ITRF.getOrientation() * Vector3d::X()).toString(12) << std::endl ;
        std::cout << "(TEME.x)_ITRF = " << (transform_TEME_ITRF.getOrientation().conjugate() * Vector3d::X()).toString(12) << std::endl ;

        const Transform transform_GCRF_ITRF = Frame::ITRF().getTransformTo(Frame::GCRF(), instant) ;

        std::cout << "transform_GCRF_ITRF = " << std::endl << transform_GCRF_ITRF << std::endl ;
        std::cout << "q_GCRF_ITRF = " << transform_GCRF_ITRF.getOrientation().toString(15) << std::endl ;
        std::cout << "rot_GCRF_ITRF = " << RotationVector::Quaternion(transform_GCRF_ITRF.getOrientation()).getAxis().toString(6) << " | " << RotationVector::Quaternion(transform_GCRF_ITRF.getOrientation()).getAngle().inDegrees().toString(3) << std::endl ;
        std::cout << "(ITRF.x)_GCRF = " << (transform_GCRF_ITRF.getOrientation() * Vector3d::X()).toString(12) << std::endl ;
        std::cout << "(GCRF.x)_ITRF = " << (transform_GCRF_ITRF.getOrientation().conjugate() * Vector3d::X()).toString(12) << std::endl ;

        const Transform transform_TEME_GCRF = Frame::GCRF().getTransformTo(Frame::TEME(), instant) ;

        std::cout << "transform_TEME_GCRF = " << std::endl << transform_TEME_GCRF << std::endl ;
        std::cout << "q_TEME_GCRF = " << transform_TEME_GCRF.getOrientation().toString(15) << std::endl ;
        std::cout << "rot_TEME_GCRF = " << RotationVector::Quaternion(transform_TEME_GCRF.getOrientation()).getAxis().toString(6) << " | " << RotationVector::Quaternion(transform_TEME_GCRF.getOrientation()).getAngle().inDegrees().toString(3) << std::endl ;
        std::cout << "(GCRF.x)_TEME = " << (transform_TEME_GCRF.getOrientation() * Vector3d::X()).toString(12) << std::endl ;
        std::cout << "(TEME.x)_GCRF = " << (transform_TEME_GCRF.getOrientation().conjugate() * Vector3d::X()).toString(12) << std::endl ;

        // STK
        // 2018-07-26T13:48:27.081
        // (GCRF.x)_ITRF = -0.875335736537 -0.483512341580 0.001778730401
        // q_ITRF_GCRF = +0.000865365971 +0.000205890755 +0.968332497584 +0.249662537985
        // q_ITRF_TEME = +0.000000214096 -0.000001082614 +0.968849072590 +0.247651922141
        // q_GCRF_TEME = -0.000013730697, -0.000889461232, 0.002075913109, 0.999997449624
        // (GCRF.x)_TEME = 0.999989798887, 0.004151840055, 0.001778860920

        // OUT
        // 2018-07-26 13:48:27.081 [UTC]
        // (GCRF.x)_ITRF = -0.875335930496, -0.483511990466, +0.001778723866
        // q_ITRF_GCRF = -0.000865357556002856, -0.000205910291382242, -0.968332547655415, +0.249662343793423
        // q_ITRF_TEME = -2.05049538299239e-07, +1.06249837365252e-06, -0.968849122251044, +0.247651727860339

        // q_TEME_GCRF = [0.000013731243988, 0.000889461657704, -0.002075913111465, 0.999997449623831]
        // rot_TEME_GCRF = [0.006080, 0.393831, -0.919163] | 0.259
        // (GCRF.x)_TEME = [0.999989798885, 0.004151840061, 0.001778861769]
        // (TEME.x)_GCRF = [0.999989798885, -0.004151791207, -0.001778975788]

        std::cout << "|D_(GCRF.x)_ITRF| @ 7000 [km] = " << ((Vector3d(-0.875335736537, -0.483512341580, 0.001778730401) - Vector3d(-0.875335930496, -0.483511990466, +0.001778723866)).norm() * 7000e3) << " [m]" << std::endl ;
        std::cout << "|D_(GCRF.x)_TEME| @ 7000 [km] = " << ((Vector3d(0.999989798887, 0.004151840055, 0.001778860920) - Vector3d(0.999989798885, 0.004151840061, 0.001778861769)).norm() * 7000e3) << " [m]" << std::endl ;

        // q_TEME_GCRF = -1.37312439873506e-05, -0.000889461657704678, 0.0020759131114654, 0.999997449623831
        

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////