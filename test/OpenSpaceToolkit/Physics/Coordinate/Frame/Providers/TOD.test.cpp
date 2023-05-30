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
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/TOD.hpp>
#include <OpenSpaceToolkit/Physics/Units/Derived/Angle.hpp>

#include <Global.test.hpp>

TEST(OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_TOD, GetTransformAt)
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
    using ostk::physics::coord::frame::provider::TOD;

    {
        // https://github.com/JuliaSpace/SatelliteToolbox.jl/blob/master/test/transformations/fk5/fk5.jl#L443

        const Instant epoch = Instant::JulianDate(2453101.82815474, Scale::TT);
        const Instant instant = Instant::DateTime(DateTime(2020, 1, 1, 0, 0, 0), Scale::UTC);

        const Transform transform_TOD_MOD = TOD(epoch).getTransformAt(instant);

        EXPECT_EQ(instant, transform_TOD_MOD.getInstant());

        const Quaternion q_MOD_TOD = transform_TOD_MOD.getOrientation().toConjugate();

        const Vector3d x_TOD = {5094.51478040, 6127.36646120, 6380.34453270};
        const Vector3d v_TOD = {-4.7460885670, 0.7860772220, 5.5319312880};

        const Vector3d x_MOD = q_MOD_TOD * x_TOD;
        const Vector3d v_MOD = q_MOD_TOD * v_TOD;

        const Vector3d x_MOD_REF = {+5094.02901670, +6127.87093630, +6380.24788850};
        const Vector3d v_MOD_REF = {-4.7462630520, +0.7860140450, +5.5317905620};

        EXPECT_GT(1e-6, (x_MOD - x_MOD_REF).norm());
        EXPECT_GT(1e-6, (v_MOD - v_MOD_REF).norm());
    }

    {
        // https://github.com/JuliaSpace/SatelliteToolbox.jl/blob/master/test/transformations/fk5/fk5.jl#L421

        const Instant epoch = Instant::JulianDate(2453101.828154745, Scale::TT);
        const Instant instant = Instant::DateTime(DateTime(2020, 1, 1, 0, 0, 0), Scale::UTC);

        const Angle obliquityCorrection = Angle::Radians(-0.003875 * M_PI / (180 * 3600));
        const Angle longitudeCorrection = Angle::Radians(-0.052195 * M_PI / (180 * 3600));

        const Transform transform_TOD_MOD =
            TOD(epoch, obliquityCorrection, longitudeCorrection).getTransformAt(instant);

        EXPECT_EQ(instant, transform_TOD_MOD.getInstant());

        const Quaternion q_MOD_TOD = transform_TOD_MOD.getOrientation().toConjugate();

        const Vector3d x_TOD = {5094.51620300, 6127.36527840, 6380.34453270};
        const Vector3d v_TOD = {-4.7460883850, 0.7860783240, 5.5319312880};

        const Vector3d x_MOD = q_MOD_TOD * x_TOD;
        const Vector3d v_MOD = q_MOD_TOD * v_TOD;

        const Vector3d x_MOD_REF = {+5094.02837450, +6127.87081640, +6380.24851640};
        const Vector3d v_MOD_REF = {-4.7462630520, +0.7860140450, +5.5317905620};

        EXPECT_GT(1e-6, (x_MOD - x_MOD_REF).norm());
        EXPECT_GT(1e-6, (v_MOD - v_MOD_REF).norm());
    }
}
