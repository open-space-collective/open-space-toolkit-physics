/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Containers/Array.hpp>
#include <OpenSpaceToolkit/Core/Containers/Table.hpp>
#include <OpenSpaceToolkit/Core/Containers/Triple.hpp>
#include <OpenSpaceToolkit/Core/Types/Real.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/Quaternion.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/RotationVector.hpp>
#include <OpenSpaceToolkit/Mathematics/Objects/Vector.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/ITRF.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/TEME.hpp>
#include <OpenSpaceToolkit/Physics/Units/Derived/Angle.hpp>

#include <Global.test.hpp>

TEST(OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_TEME, GetTransformAt)
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
    using ostk::physics::coord::frame::provider::TEME;

    {
        const Array<Triple<File, Angle, Real>> referenceScenarios = {
            {File::Path(Path::Parse(
                 "/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/TEME/Scenario_A/Scenario ITRF_TEME.csv"
             )),
             Angle::Arcseconds(1.0),
             1e-9},
            {File::Path(Path::Parse(
                 "/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/TEME/Scenario_B/Scenario ITRF_TEME.csv"
             )),
             Angle::Arcseconds(20.0),
             1e-9}};

        for (const auto& referenceScenario : referenceScenarios)
        {
            const TEME temeFrameProvider;

            // Reference data setup

            const File referenceDataFile = referenceScenario.first;

            const Table referenceData = Table::Load(referenceDataFile, Table::Format::CSV, true);

            // Test

            for (const auto& referenceRow : referenceData)
            {
                const Instant instant = Instant::DateTime(DateTime::Parse(referenceRow[0].accessString()), Scale::UTC);

                const Quaternion referenceOrientation_ITRF_TEME = Quaternion::XYZS(
                                                                      referenceRow[1].accessReal(),
                                                                      referenceRow[2].accessReal(),
                                                                      referenceRow[3].accessReal(),
                                                                      referenceRow[4].accessReal()
                )
                                                                      .normalize()
                                                                      .conjugate();
                const Quaternion referenceOrientation_GCRF_TEME = Quaternion::XYZS(
                                                                      referenceRow[9].accessReal(),
                                                                      referenceRow[10].accessReal(),
                                                                      referenceRow[11].accessReal(),
                                                                      referenceRow[12].accessReal()
                )
                                                                      .normalize();

                const Transform transform_TEME_ITRF = temeFrameProvider.getTransformAt(instant);

                const Quaternion dq_ITRF = (transform_TEME_ITRF.getOrientation() / referenceOrientation_ITRF_TEME)
                                               .normalize()
                                               .rectify();  // Why / not *?

                const Transform transform_TEME_GCRF = Frame::GCRF()->getTransformTo(Frame::TEME(), instant);

                const Quaternion dq_GCRF =
                    (transform_TEME_GCRF.getOrientation() / referenceOrientation_GCRF_TEME).normalize().rectify();

                const Angle toleranceAngle = referenceScenario.second;

                EXPECT_GT(toleranceAngle.inDegrees(), RotationVector::Quaternion(dq_ITRF).getAngle().inDegrees());
                EXPECT_GT(toleranceAngle.inDegrees(), RotationVector::Quaternion(dq_GCRF).getAngle().inDegrees());

                // Angular velocity test

                const Vector3d referenceAngularVelocity_ITRF_TEME_in_TEME = {
                    referenceRow[5].accessReal(), referenceRow[6].accessReal(), referenceRow[7].accessReal()};
                const Vector3d referenceAngularVelocity_TEME_ITRF_in_TEME = -referenceAngularVelocity_ITRF_TEME_in_TEME;

                const Vector3d w_TEME_ITRF_in_TEME = transform_TEME_ITRF.accessAngularVelocity();

                const Real dw = referenceScenario.third;

                EXPECT_GT(dw, (w_TEME_ITRF_in_TEME - referenceAngularVelocity_TEME_ITRF_in_TEME).norm());
            }
        }
    }
}
