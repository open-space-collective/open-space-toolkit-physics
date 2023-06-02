/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Containers/Map.hpp>
#include <OpenSpaceToolkit/Core/Containers/Table.hpp>
#include <OpenSpaceToolkit/Core/Containers/Triple.hpp>
#include <OpenSpaceToolkit/Core/Types/Shared.hpp>
#include <OpenSpaceToolkit/Core/Types/String.hpp>
#include <OpenSpaceToolkit/Core/Types/Weak.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Objects/Point.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Objects/Polygon.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Intersection.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Ellipsoid.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/LineString.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Point.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Polygon.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Pyramid.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Segment.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/Quaternion.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/RotationVector.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Spherical/LLA.hpp>
#include <OpenSpaceToolkit/Physics/Environment.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Model.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Objects/CelestialBodies/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Time/DateTime.hpp>
#include <OpenSpaceToolkit/Physics/Time/Duration.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Time/Interval.hpp>
#include <OpenSpaceToolkit/Physics/Time/Scale.hpp>
#include <OpenSpaceToolkit/Physics/Units/Length.hpp>

#include <Global.test.hpp>

// TEST (OpenSpaceToolkit_Physics_Environment_Objects_CelestialBodies_Earth, Constructor)
// {

//     using ostk::physics::env::obj::celest::Earth ;

//     {

//         FAIL() ;

//     }

// }

TEST(OpenSpaceToolkit_Physics_Environment_Objects_CelestialBodies_Earth, GetFrameAt)
{
    using ostk::core::types::Shared;
    using ostk::core::types::String;
    using ostk::core::ctnr::Triple;
    using ostk::core::ctnr::Array;
    using ostk::core::ctnr::Table;
    using ostk::core::fs::Path;
    using ostk::core::fs::File;

    using ostk::math::obj::Vector3d;
    using ostk::math::geom::d3::trf::rot::Quaternion;
    using ostk::math::geom::d3::trf::rot::RotationVector;

    using ostk::physics::units::Length;
    using ostk::physics::units::Angle;
    using ostk::physics::time::Scale;
    using ostk::physics::time::Instant;
    using ostk::physics::time::DateTime;
    using ostk::physics::time::Duration;
    using ostk::physics::coord::spherical::LLA;
    using ostk::physics::coord::Frame;
    using ostk::physics::env::obj::celest::Earth;

    {
        const Earth earth = Earth::Default();

        const Array<Triple<LLA, File, File>> referenceScenarios = {
            {{Angle::Degrees(0.0), Angle::Degrees(0.0), Length::Kilometers(0.01716)},
             File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Objects/CelestialBodies/Earth/"
                                    "GetFrameAt/NED_ITRF 1.csv")),
             File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Objects/CelestialBodies/Earth/"
                                    "GetFrameAt/NED_GCRF 1.csv"))},
            {{Angle::Degrees(36.5), Angle::Degrees(-123.6), Length::Kilometers(-0.0379749)},
             File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Objects/CelestialBodies/Earth/"
                                    "GetFrameAt/NED_ITRF 2.csv")),
             File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Objects/CelestialBodies/Earth/"
                                    "GetFrameAt/NED_GCRF 2.csv"))},
            {{Angle::Degrees(90.0), Angle::Degrees(123.456), Length::Kilometers(0.0136095)},
             File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Objects/CelestialBodies/Earth/"
                                    "GetFrameAt/NED_ITRF 3.csv")),
             File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Objects/CelestialBodies/Earth/"
                                    "GetFrameAt/NED_GCRF 3.csv"))},
            {{Angle::Degrees(-90.0), Angle::Degrees(-95.31), Length::Kilometers(-0.0295348)},
             File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Objects/CelestialBodies/Earth/"
                                    "GetFrameAt/NED_ITRF 4.csv")),
             File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Objects/CelestialBodies/Earth/"
                                    "GetFrameAt/NED_GCRF 4.csv"))}};

        for (const auto& referenceScenario : referenceScenarios)
        {
            const LLA lla = referenceScenario.first;

            const Shared<const Frame> nedSPtr = earth.getFrameAt(lla, Earth::FrameType::NED);

            const File referenceNedItrfFile = referenceScenario.second;
            const File referenceNedGcrfFile = referenceScenario.third;

            const Table referenceNedItrfData = Table::Load(referenceNedItrfFile, Table::Format::CSV, true);
            const Table referenceNedGcrfData = Table::Load(referenceNedGcrfFile, Table::Format::CSV, true);

            for (const auto& referenceNedItrfRow : referenceNedItrfData)
            {
                const Instant instant =
                    Instant::DateTime(DateTime::Parse(referenceNedItrfRow[0].accessString()), Scale::UTC);

                const Quaternion q_NED_ITRF_ref = Quaternion::XYZS(
                                                      referenceNedItrfRow[1].accessReal(),
                                                      referenceNedItrfRow[2].accessReal(),
                                                      referenceNedItrfRow[3].accessReal(),
                                                      referenceNedItrfRow[4].accessReal()
                )
                                                      .normalize();
                const Vector3d w_NED_ITRF_in_NED_ref = {
                    referenceNedItrfRow[5].accessReal(),
                    referenceNedItrfRow[6].accessReal(),
                    referenceNedItrfRow[7].accessReal()};

                const Quaternion q_ITRF_NED_ref = q_NED_ITRF_ref.toConjugate();
                const Vector3d w_ITRF_NED_in_ITRF_ref = -(q_ITRF_NED_ref * w_NED_ITRF_in_NED_ref);

                const Quaternion q_ITRF_NED = nedSPtr->getTransformTo(Frame::ITRF(), instant).getOrientation();
                const Vector3d w_ITRF_NED_in_ITRF =
                    nedSPtr->getTransformTo(Frame::ITRF(), instant).getAngularVelocity();

                EXPECT_TRUE(q_ITRF_NED.isNear(q_ITRF_NED_ref, Angle::Arcseconds(1.0))) << String::Format(
                    "{} / {} ? {} [asec]",
                    q_ITRF_NED_ref.toString(),
                    q_ITRF_NED.toString(),
                    q_ITRF_NED.angularDifferenceWith(q_ITRF_NED_ref).inArcseconds().toString()
                );
                EXPECT_TRUE(w_ITRF_NED_in_ITRF.isNear(w_ITRF_NED_in_ITRF_ref, 1e-12)) << String::Format(
                    "{} - {} ? {} [rad/s]",
                    w_ITRF_NED_in_ITRF_ref.toString(),
                    w_ITRF_NED_in_ITRF.toString(),
                    (w_ITRF_NED_in_ITRF - w_ITRF_NED_in_ITRF_ref).norm()
                );
            }

            for (const auto& referenceNedGcrfRow : referenceNedGcrfData)
            {
                const Instant instant =
                    Instant::DateTime(DateTime::Parse(referenceNedGcrfRow[0].accessString()), Scale::UTC);

                const Quaternion q_NED_GCRF_ref = Quaternion::XYZS(
                                                      referenceNedGcrfRow[1].accessReal(),
                                                      referenceNedGcrfRow[2].accessReal(),
                                                      referenceNedGcrfRow[3].accessReal(),
                                                      referenceNedGcrfRow[4].accessReal()
                )
                                                      .normalize();
                const Vector3d w_NED_GCRF_in_NED_ref = {
                    referenceNedGcrfRow[5].accessReal(),
                    referenceNedGcrfRow[6].accessReal(),
                    referenceNedGcrfRow[7].accessReal()};

                const Quaternion q_GCRF_NED_ref = q_NED_GCRF_ref.toConjugate();
                const Vector3d w_GCRF_NED_in_GCRF_ref = -(q_GCRF_NED_ref * w_NED_GCRF_in_NED_ref);

                const Quaternion q_GCRF_NED = nedSPtr->getTransformTo(Frame::GCRF(), instant).getOrientation();
                const Vector3d w_GCRF_NED_in_GCRF =
                    nedSPtr->getTransformTo(Frame::GCRF(), instant).getAngularVelocity();

                EXPECT_TRUE(q_GCRF_NED.isNear(q_GCRF_NED_ref, Angle::Arcseconds(1.0))) << String::Format(
                    "{} / {} ? {} [asec]",
                    q_GCRF_NED_ref.toString(),
                    q_GCRF_NED.toString(),
                    q_GCRF_NED.angularDifferenceWith(q_GCRF_NED_ref).inArcseconds().toString()
                );
                EXPECT_TRUE(w_GCRF_NED_in_GCRF.isNear(w_GCRF_NED_in_GCRF_ref, 1e-12)) << String::Format(
                    "{} - {} ? {} [rad/s]",
                    w_GCRF_NED_in_GCRF_ref.toString(),
                    w_GCRF_NED_in_GCRF.toString(),
                    (w_GCRF_NED_in_GCRF - w_GCRF_NED_in_GCRF_ref).norm()
                );
            }
        }
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Objects_CelestialBodies_Earth, StaticMethods)
{
    using ostk::physics::env::obj::celest::Earth;

    EXPECT_NO_THROW(Earth::Default());

    Earth earth = Earth::Default();

    EXPECT_FALSE(earth.accessAtmosphericModel()->isDefined());
    EXPECT_FALSE(earth.accessMagneticModel()->isDefined());
}

TEST(OpenSpaceToolkit_Physics_Environment_Objects_CelestialBodies_Earth, EGM2008)
{
    using ostk::physics::env::obj::celest::Earth;

    EXPECT_NO_THROW(Earth::EGM2008());
    EXPECT_NO_THROW(Earth::EGM2008(2190, 2160));
    EXPECT_ANY_THROW(Earth::EGM2008(3000, 3000));
}

TEST(OpenSpaceToolkit_Physics_Environment_Objects_CelestialBodies_Earth, EGM96)
{
    using ostk::physics::env::obj::celest::Earth;

    EXPECT_NO_THROW(Earth::EGM96());
    EXPECT_NO_THROW(Earth::EGM96(360, 360));
    EXPECT_ANY_THROW(Earth::EGM96(3000, 3000));

    Earth earth = Earth::EGM96();

    EXPECT_FALSE(earth.accessAtmosphericModel()->isDefined());
    EXPECT_FALSE(earth.accessMagneticModel()->isDefined());
}

TEST(OpenSpaceToolkit_Physics_Environment_Objects_CelestialBodies_Earth, EGM84)
{
    using ostk::physics::env::obj::celest::Earth;

    EXPECT_NO_THROW(Earth::EGM84());
    EXPECT_NO_THROW(Earth::EGM84(180, 180));
    EXPECT_ANY_THROW(Earth::EGM84(3000, 3000));

    Earth earth = Earth::EGM84();

    EXPECT_FALSE(earth.accessAtmosphericModel()->isDefined());
    EXPECT_FALSE(earth.accessMagneticModel()->isDefined());
}

TEST(OpenSpaceToolkit_Physics_Environment_Objects_CelestialBodies_Earth, WGS84_EGM96)
{
    using ostk::physics::env::obj::celest::Earth;

    EXPECT_NO_THROW(Earth::WGS84_EGM96());
    EXPECT_NO_THROW(Earth::WGS84_EGM96(360, 360));
    EXPECT_ANY_THROW(Earth::WGS84_EGM96(3000, 3000));

    Earth earth = Earth::WGS84_EGM96();

    EXPECT_FALSE(earth.accessAtmosphericModel()->isDefined());
    EXPECT_FALSE(earth.accessMagneticModel()->isDefined());
}

TEST(OpenSpaceToolkit_Physics_Environment_Objects_CelestialBodies_Earth, WGS84)
{
    using ostk::physics::env::obj::celest::Earth;

    EXPECT_NO_THROW(Earth::WGS84());
    EXPECT_NO_THROW(Earth::WGS84(20, 0));
    EXPECT_ANY_THROW(Earth::WGS84(3000, 3000));

    Earth earth = Earth::WGS84();

    EXPECT_FALSE(earth.accessAtmosphericModel()->isDefined());
    EXPECT_FALSE(earth.accessMagneticModel()->isDefined());
}

TEST(OpenSpaceToolkit_Physics_Environment_Objects_CelestialBodies_Earth, Spherical)
{
    using ostk::physics::env::obj::celest::Earth;

    Earth earth = Earth::Spherical();
    EXPECT_TRUE(earth.isDefined());

    EXPECT_FALSE(earth.accessAtmosphericModel()->isDefined());
    EXPECT_FALSE(earth.accessMagneticModel()->isDefined());
}
