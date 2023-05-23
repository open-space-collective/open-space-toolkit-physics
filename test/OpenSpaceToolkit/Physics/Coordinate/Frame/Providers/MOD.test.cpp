/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Containers/Array.hpp>
#include <OpenSpaceToolkit/Core/Containers/Table.hpp>
#include <OpenSpaceToolkit/Core/Containers/Triple.hpp>
#include <OpenSpaceToolkit/Core/Types/Real.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/Quaternion.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/RotationVector.hpp>
#include <OpenSpaceToolkit/Mathematics/Objects/Vector.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/GCRF.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/MOD.hpp>
#include <OpenSpaceToolkit/Physics/Units/Derived/Angle.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST(OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_MOD, GetTransformAt)
{
    using ostk::core::types::Real;
    using ostk::core::ctnr::Triple;
    using ostk::core::ctnr::Array;
    using ostk::core::ctnr::Table;
    using ostk::core::fs::Path;
    using ostk::core::fs::File;

    using ostk::math::obj::Vector3d;
    using ostk::math::geom::d3::trf::rot::Quaternion;
    using ostk::math::geom::d3::trf::rot::RotationVector;

    using ostk::physics::units::Angle;
    using ostk::physics::time::Scale;
    using ostk::physics::time::Instant;
    using ostk::physics::time::DateTime;
    using ostk::physics::coord::Frame;
    using ostk::physics::coord::frame::Transform;
    using ostk::physics::coord::frame::provider::MOD;

    {
        // https://github.com/JuliaSpace/SatelliteToolbox.jl/blob/master/test/transformations/fk5/fk5.jl#L635

        const Instant epoch = Instant::JulianDate(2453101.828154745, Scale::TT);
        const Instant instant = Instant::DateTime(DateTime(2020, 1, 1, 0, 0, 0), Scale::UTC);

        const Transform transform_MOD_GCRF = MOD(epoch).getTransformAt(instant);

        EXPECT_EQ(instant, transform_MOD_GCRF.getInstant());

        const Quaternion q_GCRF_MOD = transform_MOD_GCRF.getOrientation().toConjugate();

        const Vector3d x_MOD = {5094.02837450, 6127.87081640, 6380.24851640};
        const Vector3d v_MOD = {-4.7462630520, 0.7860140450, 5.5317905620};

        const Vector3d x_GCRF = q_GCRF_MOD * x_MOD;
        const Vector3d v_GCRF = q_GCRF_MOD * v_MOD;

        const Vector3d x_GCRF_REF = {+5102.50895790, +6123.01140070, +6378.13692820};
        const Vector3d v_GCRF_REF = {-4.7432201570, +0.7905364970, +5.5337557270};

        EXPECT_GT(1e-7, (x_GCRF - x_GCRF_REF).norm());
        EXPECT_GT(1e-9, (v_GCRF - v_GCRF_REF).norm());
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
