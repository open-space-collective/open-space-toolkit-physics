////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Environment.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Environment/Objects/CelestialBodies/Moon.hpp>
#include <Library/Physics/Environment/Objects/CelestialBodies/Earth.hpp>
#include <Library/Physics/Environment.hpp>
#include <Library/Physics/Time/Interval.hpp>
#include <Library/Physics/Time/Duration.hpp>
#include <Library/Physics/Time/Instant.hpp>
#include <Library/Physics/Time/DateTime.hpp>
#include <Library/Physics/Time/Scale.hpp>
#include <Library/Physics/Units/Length.hpp>

#include <Library/Mathematics/Geometry/Transformations/Rotations/RotationVector.hpp>
#include <Library/Mathematics/Geometry/Transformations/Rotations/Quaternion.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Segment.hpp>

#include <Library/Core/Containers/Map.hpp>
#include <Library/Core/Types/String.hpp>
#include <Library/Core/Types/Weak.hpp>
#include <Library/Core/Types/Shared.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// TEST (Library_Physics_Environment, Constructor)
// {

//     using library::physics::Environment ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Physics_Environment, isDefined)
// {

//     using library::physics::Environment ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Physics_Environment, accessObjectWithName)
// {

//     using library::physics::Environment ;

//     {

//         FAIL() ;

//     }

// }

TEST (Library_Physics_Environment, getInstant)
{

    using library::physics::Environment ;

    {

        FAIL() ;

    }

}

TEST (Library_Physics_Environment, setInstant)
{

    using library::physics::Environment ;

    {

        FAIL() ;

    }

}

TEST (Library_Physics_Environment, Intersects)
{

    using library::core::types::Shared ;
    using library::core::ctnr::Array ;

    using library::math::geom::d3::objects::Segment ;

    using library::physics::time::Scale ;
    using library::physics::time::Instant ;
    using library::physics::time::DateTime ;
    using library::physics::Environment ;
    using library::physics::env::Object ;
    using library::physics::env::obj::celest::Earth ;

    {

        const Instant instant = Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::UTC) ;

        const Array<Shared<Object>> objects =
        {
            std::make_shared<Earth>(Earth::Analytical(instant))
        } ;

        Environment environment = { instant, objects } ;

        Segment segment = { { 0.0, 0.0, 0.0 }, { 7000e3, 0.0, 0.0 } } ;

        EXPECT_TRUE(environment.intersects(segment)) ;

    }

}

TEST (Library_Physics_Environment, Undefined)
{

    using library::physics::Environment ;

    {

        EXPECT_NO_THROW(Environment::Undefined()) ;

        EXPECT_FALSE(Environment::Undefined().isDefined()) ;

    }

}

// TEST (Library_Physics_Environment, Default)
// {

//     using library::core::types::Shared ;
//     using library::core::types::Weak ;
//     using library::core::types::String ;
//     using library::core::ctnr::Map ;

//     using library::math::geom::trf::rot::Quaternion ;
//     using library::math::geom::trf::rot::RotationVector ;

//     using library::physics::units::Length ;
//     using library::physics::time::Scale ;
//     using library::physics::time::DateTime ;
//     using library::physics::time::Instant ;
//     using library::physics::time::Duration ;
//     using library::physics::time::Interval ;
//     using library::physics::coord::Frame ;
//     using library::physics::Environment ;
//     using library::physics::env::Object ;
//     using library::physics::env::obj::celest::Earth ;

//     {

//         const Map<Instant, Quaternion> referenceData =
//         {
//             { Instant::DateTime(DateTime::Parse("2018-06-25 00:00:00.000"), Scale::UTC), Quaternion::XYZS(-0.000598421009, 0.000652733203, -0.689296672243, 0.724478649421).normalize() },
//             { Instant::DateTime(DateTime::Parse("2018-06-25 01:00:00.000"), Scale::UTC), Quaternion::XYZS(-0.000507966076, 0.000725182315, -0.588546505639, 0.808462879037).normalize() },
//             { Instant::DateTime(DateTime::Parse("2018-06-25 02:00:00.000"), Scale::UTC), Quaternion::XYZS(-0.000408770122, 0.000785156015, -0.477671008304, 0.878538345357).normalize() },
//             { Instant::DateTime(DateTime::Parse("2018-06-25 03:00:00.000"), Scale::UTC), Quaternion::XYZS(-0.000302539637, 0.000831622281, -0.358577677895, 0.933499472838).normalize() },
//             { Instant::DateTime(DateTime::Parse("2018-06-25 04:00:00.000"), Scale::UTC), Quaternion::XYZS(-0.000191102168, 0.000863781460, -0.233315391344, 0.972400712424).normalize() },
//             { Instant::DateTime(DateTime::Parse("2018-06-25 05:00:00.000"), Scale::UTC), Quaternion::XYZS(-0.000076374877, 0.000881080034, -0.104039156058, 0.994572808733).normalize() },
//             { Instant::DateTime(DateTime::Parse("2018-06-25 06:00:00.000"), Scale::UTC), Quaternion::XYZS( 0.000039668444, 0.000883220149,  0.027026964738, 0.999634313900).normalize() },
//             { Instant::DateTime(DateTime::Parse("2018-06-25 07:00:00.000"), Scale::UTC), Quaternion::XYZS( 0.000155031328, 0.000870164735,  0.157628114704, 0.987498149990).normalize() },
//             { Instant::DateTime(DateTime::Parse("2018-06-25 08:00:00.000"), Scale::UTC), Quaternion::XYZS( 0.000267728980, 0.000842138158,  0.285517436837, 0.958373107086).normalize() },
//             { Instant::DateTime(DateTime::Parse("2018-06-25 09:00:00.000"), Scale::UTC), Quaternion::XYZS( 0.000375822426, 0.000799622357,  0.408494728312, 0.912760251272).normalize() },
//             { Instant::DateTime(DateTime::Parse("2018-06-25 10:00:00.000"), Scale::UTC), Quaternion::XYZS( 0.000477451873, 0.000743348559,  0.524444292687, 0.851444304309).normalize() },
//             { Instant::DateTime(DateTime::Parse("2018-06-25 11:00:00.000"), Scale::UTC), Quaternion::XYZS( 0.000570868707, 0.000674284703,  0.631371338256, 0.775480143317).normalize() },
//             { Instant::DateTime(DateTime::Parse("2018-06-25 12:00:00.000"), Scale::UTC), Quaternion::XYZS( 0.000654465577, 0.000593618789,  0.727436296369, 0.686174652706).normalize() },
//             { Instant::DateTime(DateTime::Parse("2018-06-25 13:00:00.000"), Scale::UTC), Quaternion::XYZS( 0.000726804054, 0.000502738445,  0.810986469299, 0.585064240595).normalize() },
//             { Instant::DateTime(DateTime::Parse("2018-06-25 14:00:00.000"), Scale::UTC), Quaternion::XYZS( 0.000786639380, 0.000403207056,  0.880584463186, 0.473888406503).normalize() },
//             { Instant::DateTime(DateTime::Parse("2018-06-25 15:00:00.000"), Scale::UTC), Quaternion::XYZS( 0.000832941887, 0.000296736867,  0.935032916904, 0.354559815068).normalize() },
//             { Instant::DateTime(DateTime::Parse("2018-06-25 16:00:00.000"), Scale::UTC), Quaternion::XYZS( 0.000864914712, 0.000185159534,  0.973395101416, 0.229131390644).normalize() },
//             { Instant::DateTime(DateTime::Parse("2018-06-25 17:00:00.000"), Scale::UTC), Quaternion::XYZS( 0.000882007517, 0.000070394605,  0.995011035221, 0.099760998867).normalize() },
//             { Instant::DateTime(DateTime::Parse("2018-06-25 18:00:00.000"), Scale::UTC), Quaternion::XYZS(-0.000883925958, 0.000045583497, -0.999508838654, 0.031325677174).normalize() },
//             { Instant::DateTime(DateTime::Parse("2018-06-25 19:00:00.000"), Scale::UTC), Quaternion::XYZS(-0.000870636752, 0.000160779444, -0.986811131681, 0.161873427507).normalize() },
//             { Instant::DateTime(DateTime::Parse("2018-06-25 20:00:00.000"), Scale::UTC), Quaternion::XYZS(-0.000842368256, 0.000273211332, -0.957136365150, 0.289636313813).normalize() },
//             { Instant::DateTime(DateTime::Parse("2018-06-25 21:00:00.000"), Scale::UTC), Quaternion::XYZS(-0.000799606543, 0.000380944776, -0.910995062568, 0.412416308465).normalize() },
//             { Instant::DateTime(DateTime::Parse("2018-06-25 22:00:00.000"), Scale::UTC), Quaternion::XYZS(-0.000743087043, 0.000482126193, -0.849181037073, 0.528101109307).normalize() },
//             { Instant::DateTime(DateTime::Parse("2018-06-25 23:00:00.000"), Scale::UTC), Quaternion::XYZS(-0.000673781895, 0.000575014693, -0.772757734708, 0.634700479616).normalize() },
//             { Instant::DateTime(DateTime::Parse("2018-06-26 00:00:00.000"), Scale::UTC), Quaternion::XYZS(-0.000592883226, 0.000658012030, -0.683039938936, 0.730380488053).normalize() }
//         } ;

//         Environment environment = Environment::Default() ;

//         EXPECT_TRUE(environment.isDefined()) ;

//         const Instant startInstant = Instant::DateTime(DateTime::Parse("2018-06-25 00:00:00"), Scale::UTC) ;
//         const Instant endInstant = Instant::DateTime(DateTime::Parse("2018-06-26 00:00:00"), Scale::UTC) ;
//         const Duration stepDuration = Duration::Hours(1.0) ;

//         const Weak<const Object> earthWPtr = environment.accessObjectWithName("Earth") ;

//         EXPECT_FALSE(earthWPtr.expired()) ;

//         if (auto earthSPtr = earthWPtr.lock())
//         {

//             const Earth& earth = dynamic_cast<const Earth&>(*earthSPtr) ;

//             const Length earthEquatorialRadius = earth.getEquatorialRadius() ;

//             for (const auto& instant : Interval::Closed(startInstant, endInstant).generateGrid(stepDuration))
//             {

//                 environment.setInstant(instant) ;

//                 // const Quaternion orientation = earth.getFrame().getTransformTo(Frame::GCRF()).getOrientation() ;

//                 // const Quaternion referenceOrientation = referenceData.at(instant).toConjugate() ; // [TBR] REMOVE CONJUGATE !!!!

//                 // const Length errorAtSurface = earthEquatorialRadius * RotationVector::Quaternion((orientation * referenceOrientation.toConjugate())).getAngle().inRadians() ;

//                 // EXPECT_GT(Length::Millimeters(1.0), errorAtSurface) ;

//                 FAIL() ;

//             }

//         }
//         else
//         {
//             FAIL() ;
//         }

//     }

// }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Physics_Environment, Test_1)
{

    using library::core::types::Shared ;
    using library::core::types::Weak ;
    using library::core::types::String ;
    using library::core::ctnr::Array ;

    using library::math::geom::trf::rot::Quaternion ;

    using library::physics::time::Scale ;
    using library::physics::time::Instant ;
    using library::physics::time::Duration ;
    using library::physics::time::Interval ;
    using library::physics::time::DateTime ;
    using library::physics::coord::Position ;
    using library::physics::coord::Velocity ;
    using library::physics::coord::Transform ;
    using library::physics::coord::Frame ;
    using library::physics::coord::Axes ;
    using library::physics::Environment ;
    using library::physics::env::Object ;
    using library::physics::env::obj::celest::Earth ;
    using library::physics::env::obj::celest::Moon ;

    const Instant startInstant = Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::UTC) ;
    const Instant endInstant = Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::UTC) ;
    const Duration step = Duration::Minutes(1.0) ;

    const Array<Shared<Object>> objects =
    {
        std::make_shared<Earth>(Earth::Analytical(startInstant)),
        std::make_shared<Moon>(Moon::Analytical(startInstant))
    } ;

    Environment environment = { startInstant, objects } ;

    Shared<const Earth> earthSPtr = nullptr ;
    Shared<const Moon> moonSPtr = nullptr ;

    if (auto objectSPtr = environment.accessObjectWithName("Earth").lock())
    {
        
        earthSPtr = std::dynamic_pointer_cast<const Earth>(objectSPtr) ;

        if (earthSPtr == nullptr)
        {
            FAIL() ;
        }

    }
    else
    {
        FAIL() ;
    }

    if (auto objectSPtr = environment.accessObjectWithName("Moon").lock())
    {
        
        moonSPtr = std::dynamic_pointer_cast<const Moon>(objectSPtr) ;

        if (moonSPtr == nullptr)
        {
            FAIL() ;
        }

    }
    else
    {
        FAIL() ;
    }

    for (const auto& instant : Interval::Closed(startInstant, endInstant).generateGrid(step))
    {

        environment.setInstant(instant) ;

        // Earth

        const Transform earthFrameTransform = earthSPtr->getTransformTo(Frame::GCRF()) ;

        EXPECT_TRUE(earthFrameTransform.isDefined()) ;

        const Position earthPosition = earthSPtr->getPositionIn(Frame::GCRF()) ;
        const Velocity earthVelocity = earthSPtr->getVelocityIn(Frame::GCRF()) ;

        EXPECT_TRUE(earthPosition.isDefined()) ;
        EXPECT_TRUE(earthVelocity.isDefined()) ;

        const Quaternion earthOrientation = earthSPtr->getTransformTo(Frame::GCRF()).getOrientation() ;

        EXPECT_TRUE(earthOrientation.isDefined()) ;

        const Axes earthAxes = earthSPtr->getAxesIn(Frame::GCRF()) ;

        EXPECT_TRUE(earthAxes.isDefined()) ;

        std::cout << String::Format("Earth @ {}: {} --- {} --- {}", instant.toString(), earthPosition.toString(), earthVelocity.toString(), earthOrientation.toString()) << std::endl ;

        // Moon

        const Transform moonFrameTransform = moonSPtr->getTransformTo(Frame::GCRF()) ;

        EXPECT_TRUE(moonFrameTransform.isDefined()) ;

        const Position moonPosition = moonSPtr->getPositionIn(Frame::GCRF()) ;
        const Velocity moonVelocity = moonSPtr->getVelocityIn(Frame::GCRF()) ;

        EXPECT_TRUE(moonPosition.isDefined()) ;
        EXPECT_TRUE(moonVelocity.isDefined()) ;

        const Quaternion moonOrientation = moonSPtr->getTransformTo(Frame::GCRF()).getOrientation() ;

        EXPECT_TRUE(moonOrientation.isDefined()) ;

        const Axes moonAxes = moonSPtr->getAxesIn(Frame::GCRF()) ;

        EXPECT_TRUE(moonAxes.isDefined()) ;

        std::cout << String::Format("Moon @ {}: {} --- {} --- {}", instant.toString(), moonPosition.toString(), moonVelocity.toString(), moonOrientation.toString()) << std::endl ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////