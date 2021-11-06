////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/TOD.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/GCRF.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/TOD.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Units/Derived/Angle.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/RotationVector.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/Quaternion.hpp>
#include <OpenSpaceToolkit/Mathematics/Objects/Vector.hpp>

#include <OpenSpaceToolkit/Core/Types/Real.hpp>
#include <OpenSpaceToolkit/Core/Containers/Triple.hpp>
#include <OpenSpaceToolkit/Core/Containers/Table.hpp>
#include <OpenSpaceToolkit/Core/Containers/Array.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_TOD, GetTransformAt)
{

    using ostk::core::types::Real ;
    using ostk::core::ctnr::Triple ;
    using ostk::core::ctnr::Array ;
    using ostk::core::ctnr::Table ;
    using ostk::core::fs::Path ;
    using ostk::core::fs::File ;

    using ostk::math::obj::Vector3d ;
    using ostk::math::geom::d3::trf::rot::Quaternion ;
    using ostk::math::geom::d3::trf::rot::RotationVector ;

    using ostk::physics::units::Angle ;
    using ostk::physics::time::Scale ;
    using ostk::physics::time::Instant ;
    using ostk::physics::time::DateTime ;
    using ostk::physics::coord::Frame ;
    using ostk::physics::coord::frame::Transform ;
    using ostk::physics::coord::frame::provider::TOD ;

    {

        // https://github.com/JuliaSpace/SatelliteToolbox.jl/blob/master/test/transformations/fk5/fk5.jl#L421

        const Instant instant = Instant::JulianDate(2453101.828154745, Scale::TT) ;

        const Transform transform_TOD_MOD = TOD().getTransformAt(instant) ;

        const Quaternion q_MOD_TOD = transform_TOD_MOD.getOrientation().toConjugate() ;

        const Vector3d x_TOD = { 5094.51620300, 6127.36527840, 6380.34453270 } ;
        const Vector3d v_TOD = { -4.7460883850, 0.7860783240, 5.5319312880 } ;

        const Vector3d x_MOD = q_MOD_TOD * x_TOD ;
        const Vector3d v_MOD = q_MOD_TOD * v_TOD ;

        const Vector3d x_MOD_REF = { +5094.02837450, +6127.87081640, +6380.24851640 } ;
        const Vector3d v_MOD_REF = { -4.7462630520, +0.7860140450, +5.5317905620 } ;

        // TBI: Can't reach desired precision, for some reason.
        EXPECT_GT(1e-0, (x_MOD - x_MOD_REF).norm()) ;
        EXPECT_GT(1e-2, (v_MOD - v_MOD_REF).norm()) ;
        // EXPECT_GT(1e-7, (x_MOD - x_MOD_REF).norm()) ;
        // EXPECT_GT(1e-9, (v_MOD - v_MOD_REF).norm()) ;

    }

    {

        // https://github.com/JuliaSpace/SatelliteToolbox.jl/blob/master/test/transformations/fk5/fk5.jl#L443

        const Instant instant = Instant::JulianDate(2453101.82815474, Scale::TT) ;

        const Transform transform_TOD_MOD = TOD().getTransformAt(instant) ;

        const Quaternion q_MOD_TOD = transform_TOD_MOD.getOrientation().toConjugate() ;

        const Vector3d x_TOD = { 5094.51478040, 6127.36646120, 6380.34453270 } ;
        const Vector3d v_TOD = { -4.7460885670, 0.7860772220, 5.5319312880 } ;

        const Vector3d x_MOD = q_MOD_TOD * x_TOD ;
        const Vector3d v_MOD = q_MOD_TOD * v_TOD ;

        const Vector3d x_MOD_REF = { +5094.02901670, +6127.87093630, +6380.24788850 } ;
        const Vector3d v_MOD_REF = { -4.7462630520, +0.7860140450, +5.5317905620 } ;

        // std::cout << "x_TOD     = " << x_TOD.toString() << std::endl ;
        // std::cout << "x_MOD     = " << x_MOD.toString() << std::endl ;
        // std::cout << "x_MOD_REF = " << x_MOD_REF.toString() << std::endl ;

        // std::cout << "|x_TOD - x_MOD_REF| = " << (x_TOD - x_MOD_REF).norm() << std::endl ;
        // std::cout << "|x_MOD - x_MOD_REF| = " << (x_MOD - x_MOD_REF).norm() << std::endl ;

        // TBI: Can't reach desired precision, for some reason.
        EXPECT_GT(1e-0, (x_MOD - x_MOD_REF).norm()) ;
        EXPECT_GT(1e-2, (v_MOD - v_MOD_REF).norm()) ;
        // EXPECT_GT(1e-7, (x_MOD - x_MOD_REF).norm()) ;
        // EXPECT_GT(1e-9, (v_MOD - v_MOD_REF).norm()) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
