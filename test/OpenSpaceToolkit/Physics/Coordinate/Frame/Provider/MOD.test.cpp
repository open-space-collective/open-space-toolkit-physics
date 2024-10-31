/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Container/Table.hpp>
#include <OpenSpaceToolkit/Core/Container/Triple.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/Quaternion.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/RotationVector.hpp>
#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/GCRF.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/MOD.hpp>
#include <OpenSpaceToolkit/Physics/Unit/Derived/Angle.hpp>

#include <Global.test.hpp>

using ostk::core::container::Array;
using ostk::core::container::Table;
using ostk::core::container::Triple;
using ostk::core::filesystem::File;
using ostk::core::filesystem::Path;
using ostk::core::type::Real;

using ostk::mathematics::geometry::d3::transformation::rotation::Quaternion;
using ostk::mathematics::geometry::d3::transformation::rotation::RotationVector;
using ostk::mathematics::object::Vector3d;

using ostk::physics::coordinate::Frame;
using ostk::physics::coordinate::frame::provider::MOD;
using ostk::physics::coordinate::frame::Transform;
using ostk::physics::time::DateTime;
using ostk::physics::time::Instant;
using ostk::physics::time::Scale;
using ostk::physics::unit::Angle;

TEST(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_MOD, GetTransformAt)
{
    {
        // https://github.com/JuliaSpace/SatelliteToolbox.jl/blob/master/test/Transformation/fk5/fk5.jl#L635

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
