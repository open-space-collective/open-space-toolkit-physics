/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Containers/Map.hpp>
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
#include <OpenSpaceToolkit/Physics/Environment/Ephemerides/SPICE/Engine.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Objects/CelestialBodies/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Objects/CelestialBodies/Moon.hpp>
#include <OpenSpaceToolkit/Physics/Time/DateTime.hpp>
#include <OpenSpaceToolkit/Physics/Time/Duration.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Time/Interval.hpp>
#include <OpenSpaceToolkit/Physics/Time/Scale.hpp>
#include <OpenSpaceToolkit/Physics/Units/Length.hpp>

#include <Global.test.hpp>

using ostk::core::types::Shared;
using ostk::core::types::Weak;
using ostk::core::types::String;
using ostk::core::types::Real;
using ostk::core::ctnr::Array;
using ostk::core::ctnr::Map;

using ostk::math::obj::Interval;
using ostk::math::obj::Vector3d;
using ostk::math::geom::d3::objects::Segment;
using ostk::math::geom::d3::trf::rot::Quaternion;
using ostk::math::geom::d3::trf::rot::RotationVector;
using ostk::math::geom::d3::objects::Point;
using ostk::math::geom::d3::objects::LineString;
using ostk::math::geom::d3::objects::Polygon;
using ostk::math::geom::d3::objects::Ellipsoid;
using ostk::math::geom::d3::objects::Pyramid;
using ostk::math::geom::d3::Intersection;
using Point2d = ostk::math::geom::d2::objects::Point;
using Polygon2d = ostk::math::geom::d2::objects::Polygon;

using ostk::physics::Environment;
using ostk::physics::time::Scale;
using ostk::physics::time::Instant;
using ostk::physics::time::DateTime;
using ostk::physics::time::Duration;
using TimeInterval = ostk::physics::time::Interval;
using ostk::physics::coord::Frame;
using ostk::physics::coord::Position;
using ostk::physics::coord::Velocity;
using ostk::physics::coord::Transform;
using ostk::physics::coord::Axes;
using ostk::physics::coord::spherical::LLA;
using ostk::physics::Environment;
using ostk::physics::environment::Object;
using ostk::physics::environment::object::celestial::Earth;
using ostk::physics::environment::object::celestial::Moon;
using ostk::physics::environment::ephemerides::spice::Engine;
using ostk::physics::units::Length;
using EarthGravitationalModel = ostk::physics::environment::gravitational::Earth;

using ostk::core::types::Shared;
using ostk::core::types::Weak;
using ostk::core::types::String;
using ostk::core::ctnr::Array;

class OpenSpaceToolkit_Physics_Environment : public ::testing::Test
{
   protected:
    void SetUp() override
    {
        environment_ = {instant_, objects_};
    }

    const Instant instant_ = Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::UTC);
    const Array<Shared<Object>> objects_ = {std::make_shared<Earth>(Earth::Default())};
    Environment environment_ = Environment::Undefined();
};

TEST_F(OpenSpaceToolkit_Physics_Environment, Constructor)
{
    {
        EXPECT_NO_THROW(Environment environment(instant_, objects_););
    }

    {
        const Array<Shared<Object>> objects = {std::make_shared<Earth>(Earth::EGM2008(2190, 2160))};

        EXPECT_NO_THROW(Environment environment(instant_, objects););
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment, IsDefined)
{
    {
        EXPECT_TRUE(environment_.isDefined());
    }

    {
        EXPECT_FALSE(Environment::Undefined().isDefined());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment, HasObjectWithName)
{
    {
        EXPECT_TRUE(environment_.hasObjectWithName("Earth"));
        EXPECT_FALSE(environment_.hasObjectWithName("Moon"));
    }

    {
        EXPECT_ANY_THROW(Environment::Undefined().hasObjectWithName("Earth"));
        EXPECT_ANY_THROW(Environment::Default().hasObjectWithName(""));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment, Intersects)
{
    {
        // for (const auto& y_ECI : Interval<Real>::Closed(-Earth::EquatorialRadius.inMeters(),
        // +Earth::EquatorialRadius.inMeters()).generateArrayWithStep(Real(1000.0)))
        for (const auto& y_ECI :
             Interval<Real>::Closed(
                 -EarthGravitationalModel::EGM2008.equatorialRadius_.inMeters() + 1.0,
                 +EarthGravitationalModel::EGM2008.equatorialRadius_.inMeters() - 1.0
             )
                 .generateArrayWithStep(Real(1000.0)))  // [TBI] Precision issues are preventing the tangential rays to
                                                        // be recognised as intersecting, hence the 1.0 [m] offset
        {
            const Segment segment = {{-10000e3, y_ECI, 0.0}, {+10000e3, y_ECI, 0.0}};

            const Object::Geometry segmentGeometry = {segment, Frame::GCRF()};

            ASSERT_TRUE(environment_.intersects(segmentGeometry)) << segmentGeometry;
        }
    }

    {
        const Segment segment = {{-7000e3, 0.0, 0.0}, {+7000e3, 0.0, 0.0}};
        const Object::Geometry geometry = {segment, Frame::GCRF()};

        EXPECT_ANY_THROW(Environment::Undefined().intersects(Object::Geometry::Undefined()));
        EXPECT_ANY_THROW(Environment::Undefined().intersects(geometry));
        EXPECT_ANY_THROW(environment_.intersects(Object::Geometry::Undefined()));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment, AccessObjects)
{
    {
        ASSERT_EQ(1, environment_.accessObjects().getSize());

        EXPECT_EQ("Earth", environment_.accessObjects()[0]->getName());
    }

    {
        EXPECT_ANY_THROW(Environment::Undefined().accessObjects());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment, AccessObjectWithName)
{
    {
        EXPECT_NO_THROW(environment_.accessObjectWithName("Earth"));

        const Shared<const Object> objectSPtr = environment_.accessObjectWithName("Earth");

        EXPECT_TRUE(objectSPtr);

        EXPECT_EQ("Earth", objectSPtr->getName());
    }

    {
        EXPECT_ANY_THROW(Environment::Undefined().accessObjectWithName("Earth"));
        EXPECT_ANY_THROW(Environment::Default().accessObjectWithName(""));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment, AccessCelestialObjectWithName)
{
    {
        EXPECT_NO_THROW(environment_.accessCelestialObjectWithName("Earth"));

        const Shared<const Object> objectSPtr = environment_.accessCelestialObjectWithName("Earth");

        EXPECT_TRUE(objectSPtr);

        EXPECT_EQ("Earth", objectSPtr->getName());
    }

    {
        EXPECT_ANY_THROW(Environment::Undefined().accessCelestialObjectWithName("Earth"));
        EXPECT_ANY_THROW(Environment::Default().accessCelestialObjectWithName(""));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment, GetInstant)
{
    {
        EXPECT_EQ(instant_, environment_.getInstant());
    }

    {
        EXPECT_ANY_THROW(Environment::Undefined().getInstant());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment, GetObjectNames)
{
    {
        EXPECT_EQ(Array<String>({"Earth"}), environment_.getObjectNames());
    }

    {
        EXPECT_ANY_THROW(Environment::Undefined().getObjectNames());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment, SetInstant)
{
    {
        EXPECT_EQ(instant_, environment_.getInstant());

        const Instant secondInstant = Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::UTC);

        environment_.setInstant(secondInstant);

        EXPECT_EQ(secondInstant, environment_.getInstant());

        EXPECT_ANY_THROW(environment_.setInstant(Instant::Undefined()));
    }

    {
        EXPECT_ANY_THROW(Environment::Undefined().setInstant(Instant::Undefined()));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment, IsPositionInEclipse)
{
    {
        const Position position = Position::Meters({7000e3, 0.0, 0.0}, Frame::ITRF());

        Environment environment = Environment::Default();

        {
            const Instant instant = Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::UTC);

            environment.setInstant(instant);

            EXPECT_TRUE(environment.isPositionInEclipse(position));
        }

        {
            const Instant instant = Instant::DateTime(DateTime(2018, 1, 1, 12, 0, 0), Scale::UTC);

            environment.setInstant(instant);

            EXPECT_FALSE(environment.isPositionInEclipse(position));
        }

        {
            const Instant instant = Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::UTC);

            environment.setInstant(instant);

            EXPECT_TRUE(environment.isPositionInEclipse(position));
        }
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment, Undefined)
{
    {
        EXPECT_NO_THROW(Environment::Undefined());

        EXPECT_FALSE(Environment::Undefined().isDefined());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment, Default)
{
    {
        EXPECT_NO_THROW(Environment::Default());

        EXPECT_TRUE(Environment::Default().isDefined());

        EXPECT_TRUE(Environment::Default().hasObjectWithName("Earth"));
        EXPECT_TRUE(Environment::Default().hasObjectWithName("Sun"));
        EXPECT_TRUE(Environment::Default().hasObjectWithName("Moon"));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment, Test_1)
{
    const Instant startInstant = Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::UTC);
    const Instant endInstant = Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::UTC);
    const Duration step = Duration::Minutes(1.0);

    const Array<Shared<Object>> objects = {
        std::make_shared<Earth>(Earth::Default()), std::make_shared<Moon>(Moon::Default())
    };

    Environment environment = {startInstant, objects};

    const Shared<const Earth> earthSPtr =
        std::dynamic_pointer_cast<const Earth>(environment.accessObjectWithName("Earth"));
    const Shared<const Moon> moonSPtr = std::dynamic_pointer_cast<const Moon>(environment.accessObjectWithName("Moon"));

    for (const auto& instant : TimeInterval::Closed(startInstant, endInstant).generateGrid(step))
    {
        environment.setInstant(instant);

        // Earth

        const Transform earthFrameTransform = earthSPtr->getTransformTo(Frame::GCRF(), instant);

        EXPECT_TRUE(earthFrameTransform.isDefined());

        const Position earthPosition = earthSPtr->getPositionIn(Frame::GCRF(), instant);
        const Velocity earthVelocity = earthSPtr->getVelocityIn(Frame::GCRF(), instant);

        EXPECT_TRUE(earthPosition.isDefined());
        EXPECT_TRUE(earthVelocity.isDefined());

        const Quaternion earthOrientation = earthSPtr->getTransformTo(Frame::GCRF(), instant).getOrientation();

        EXPECT_TRUE(earthOrientation.isDefined());

        const Axes earthAxes = earthSPtr->getAxesIn(Frame::GCRF(), instant);

        EXPECT_TRUE(earthAxes.isDefined());

        // Moon

        const Transform moonFrameTransform = moonSPtr->getTransformTo(Frame::GCRF(), instant);

        EXPECT_TRUE(moonFrameTransform.isDefined());

        const Position moonPosition = moonSPtr->getPositionIn(Frame::GCRF(), instant);
        const Velocity moonVelocity = moonSPtr->getVelocityIn(Frame::GCRF(), instant);

        EXPECT_TRUE(moonPosition.isDefined());
        EXPECT_TRUE(moonVelocity.isDefined());

        const Quaternion moonOrientation = moonSPtr->getTransformTo(Frame::GCRF(), instant).getOrientation();

        EXPECT_TRUE(moonOrientation.isDefined());

        const Axes moonAxes = moonSPtr->getAxesIn(Frame::GCRF(), instant);

        EXPECT_TRUE(moonAxes.isDefined());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment, Test_2)
{
    // Setup scene

    const Instant startInstant = Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::UTC);

    const Array<Shared<Object>> objects = {std::make_shared<Earth>(Earth::Default())};

    Environment environment = {startInstant, objects};

    const Shared<const Earth> earthSPtr =
        std::dynamic_pointer_cast<const Earth>(environment.accessObjectWithName("Earth"));

    const Object::Geometry earthGeometry = earthSPtr->getGeometryIn(Frame::ITRF(), startInstant);

    const Ellipsoid& ellipsoid = earthGeometry.accessComposite().as<Ellipsoid>();

    // Setup observer

    const Point apex = {7000e3, 0.0, 0.0};
    const Polygon base = {
        {{{-1.0, -1.0}, {+1.0, -1.0}, {+1.0, +1.0}, {-1.0, +1.0}}},
        apex - Vector3d(1.0, 0.4, 0.4),
        {0.0, 1.0, 0.0},
        {0.0, 0.0, 1.0}
    };

    const Pyramid pyramid = {base, apex};

    // Compute intersection

    const Intersection intersection = pyramid.intersectionWith(ellipsoid, true, 32);

    EXPECT_TRUE(intersection.isDefined()) << intersection;
    EXPECT_FALSE(intersection.isEmpty()) << intersection;

    // Project intersection

    const LineString intersectionLineString = intersection.accessComposite().as<LineString>();

    Array<Point2d> intersectionPoints2d = Array<Point2d>::Empty();

    for (const auto& intersectionPoint : intersectionLineString)  // Implement segment and point iterators...
    {
        const LLA intersectionLla = LLA::Cartesian(
            intersectionPoint.asVector(),
            EarthGravitationalModel::EGM2008.equatorialRadius_,
            EarthGravitationalModel::EGM2008.flattening_
        );

        const Point2d intersectionPoint2d = {
            intersectionLla.getLongitude().inDegrees(), intersectionLla.getLatitude().inDegrees()
        };

        intersectionPoints2d.add(intersectionPoint2d);
    }

    const Polygon2d intersectionPolygon2d = {intersectionPoints2d};

    EXPECT_TRUE(intersectionPolygon2d.isDefined()) << intersectionPolygon2d;
}

TEST_F(OpenSpaceToolkit_Physics_Environment, Test_3)
{
    {
        const Map<Instant, Quaternion> referenceData = {
            {Instant::DateTime(DateTime::Parse("2018-06-25 00:00:00.000"), Scale::UTC),
             Quaternion::XYZS(-0.000598421009, 0.000652733203, -0.689296672243, 0.724478649421).normalize()},
            {Instant::DateTime(DateTime::Parse("2018-06-25 01:00:00.000"), Scale::UTC),
             Quaternion::XYZS(-0.000507966076, 0.000725182315, -0.588546505639, 0.808462879037).normalize()},
            {Instant::DateTime(DateTime::Parse("2018-06-25 02:00:00.000"), Scale::UTC),
             Quaternion::XYZS(-0.000408770122, 0.000785156015, -0.477671008304, 0.878538345357).normalize()},
            {Instant::DateTime(DateTime::Parse("2018-06-25 03:00:00.000"), Scale::UTC),
             Quaternion::XYZS(-0.000302539637, 0.000831622281, -0.358577677895, 0.933499472838).normalize()},
            {Instant::DateTime(DateTime::Parse("2018-06-25 04:00:00.000"), Scale::UTC),
             Quaternion::XYZS(-0.000191102168, 0.000863781460, -0.233315391344, 0.972400712424).normalize()},
            {Instant::DateTime(DateTime::Parse("2018-06-25 05:00:00.000"), Scale::UTC),
             Quaternion::XYZS(-0.000076374877, 0.000881080034, -0.104039156058, 0.994572808733).normalize()},
            {Instant::DateTime(DateTime::Parse("2018-06-25 06:00:00.000"), Scale::UTC),
             Quaternion::XYZS(0.000039668444, 0.000883220149, 0.027026964738, 0.999634313900).normalize()},
            {Instant::DateTime(DateTime::Parse("2018-06-25 07:00:00.000"), Scale::UTC),
             Quaternion::XYZS(0.000155031328, 0.000870164735, 0.157628114704, 0.987498149990).normalize()},
            {Instant::DateTime(DateTime::Parse("2018-06-25 08:00:00.000"), Scale::UTC),
             Quaternion::XYZS(0.000267728980, 0.000842138158, 0.285517436837, 0.958373107086).normalize()},
            {Instant::DateTime(DateTime::Parse("2018-06-25 09:00:00.000"), Scale::UTC),
             Quaternion::XYZS(0.000375822426, 0.000799622357, 0.408494728312, 0.912760251272).normalize()},
            {Instant::DateTime(DateTime::Parse("2018-06-25 10:00:00.000"), Scale::UTC),
             Quaternion::XYZS(0.000477451873, 0.000743348559, 0.524444292687, 0.851444304309).normalize()},
            {Instant::DateTime(DateTime::Parse("2018-06-25 11:00:00.000"), Scale::UTC),
             Quaternion::XYZS(0.000570868707, 0.000674284703, 0.631371338256, 0.775480143317).normalize()},
            {Instant::DateTime(DateTime::Parse("2018-06-25 12:00:00.000"), Scale::UTC),
             Quaternion::XYZS(0.000654465577, 0.000593618789, 0.727436296369, 0.686174652706).normalize()},
            {Instant::DateTime(DateTime::Parse("2018-06-25 13:00:00.000"), Scale::UTC),
             Quaternion::XYZS(0.000726804054, 0.000502738445, 0.810986469299, 0.585064240595).normalize()},
            {Instant::DateTime(DateTime::Parse("2018-06-25 14:00:00.000"), Scale::UTC),
             Quaternion::XYZS(0.000786639380, 0.000403207056, 0.880584463186, 0.473888406503).normalize()},
            {Instant::DateTime(DateTime::Parse("2018-06-25 15:00:00.000"), Scale::UTC),
             Quaternion::XYZS(0.000832941887, 0.000296736867, 0.935032916904, 0.354559815068).normalize()},
            {Instant::DateTime(DateTime::Parse("2018-06-25 16:00:00.000"), Scale::UTC),
             Quaternion::XYZS(0.000864914712, 0.000185159534, 0.973395101416, 0.229131390644).normalize()},
            {Instant::DateTime(DateTime::Parse("2018-06-25 17:00:00.000"), Scale::UTC),
             Quaternion::XYZS(0.000882007517, 0.000070394605, 0.995011035221, 0.099760998867).normalize()},
            {Instant::DateTime(DateTime::Parse("2018-06-25 18:00:00.000"), Scale::UTC),
             Quaternion::XYZS(-0.000883925958, 0.000045583497, -0.999508838654, 0.031325677174).normalize()},
            {Instant::DateTime(DateTime::Parse("2018-06-25 19:00:00.000"), Scale::UTC),
             Quaternion::XYZS(-0.000870636752, 0.000160779444, -0.986811131681, 0.161873427507).normalize()},
            {Instant::DateTime(DateTime::Parse("2018-06-25 20:00:00.000"), Scale::UTC),
             Quaternion::XYZS(-0.000842368256, 0.000273211332, -0.957136365150, 0.289636313813).normalize()},
            {Instant::DateTime(DateTime::Parse("2018-06-25 21:00:00.000"), Scale::UTC),
             Quaternion::XYZS(-0.000799606543, 0.000380944776, -0.910995062568, 0.412416308465).normalize()},
            {Instant::DateTime(DateTime::Parse("2018-06-25 22:00:00.000"), Scale::UTC),
             Quaternion::XYZS(-0.000743087043, 0.000482126193, -0.849181037073, 0.528101109307).normalize()},
            {Instant::DateTime(DateTime::Parse("2018-06-25 23:00:00.000"), Scale::UTC),
             Quaternion::XYZS(-0.000673781895, 0.000575014693, -0.772757734708, 0.634700479616).normalize()},
            {Instant::DateTime(DateTime::Parse("2018-06-26 00:00:00.000"), Scale::UTC),
             Quaternion::XYZS(-0.000592883226, 0.000658012030, -0.683039938936, 0.730380488053).normalize()}
        };

        Environment environment = Environment::Default();

        EXPECT_TRUE(environment.isDefined());

        const Instant startInstant = Instant::DateTime(DateTime::Parse("2018-06-25 00:00:00"), Scale::UTC);
        const Instant endInstant = Instant::DateTime(DateTime::Parse("2018-06-26 00:00:00"), Scale::UTC);
        const Duration stepDuration = Duration::Hours(1.0);

        const Shared<const Earth> earthSPtr =
            std::dynamic_pointer_cast<const Earth>(environment.accessObjectWithName("Earth"));

        const Length earthEquatorialRadius = earthSPtr->getEquatorialRadius();

        EXPECT_EQ(EarthGravitationalModel::EGM2008.equatorialRadius_, earthEquatorialRadius);

        for (const auto& instant : TimeInterval::Closed(startInstant, endInstant).generateGrid(stepDuration))
        {
            environment.setInstant(instant);

            const Quaternion referenceOrientation = referenceData.at(instant).toConjugate();

            const Quaternion orientation =
                earthSPtr->accessFrame()->getTransformTo(Frame::GCRF(), instant).getOrientation();

            const Length errorAtSurface =
                earthEquatorialRadius *
                RotationVector::Quaternion((orientation * referenceOrientation.toConjugate()).toNormalized())
                    .getAngle()
                    .inRadians();

            EXPECT_GE(Length::Millimeters(1.0), errorAtSurface) << errorAtSurface;
        }
    }
}
