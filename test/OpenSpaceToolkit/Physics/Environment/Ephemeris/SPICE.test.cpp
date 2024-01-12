/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Container/Table.hpp>
#include <OpenSpaceToolkit/Core/Container/Tuple.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>
#include <OpenSpaceToolkit/Core/Type/Shared.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/Quaternion.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/RotationVector.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Ephemeris/SPICE.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Ephemeris/SPICE/Engine.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Ephemeris/SPICE/Manager.hpp>
#include <OpenSpaceToolkit/Physics/Time/DateTime.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Time/Scale.hpp>

#include <Global.test.hpp>

using ostk::physics::environment::ephemeris::SPICE;

using ostk::core::type::Shared;
using ostk::core::type::Real;
using ostk::core::type::String;
using ostk::core::container::Tuple;
using ostk::core::container::Array;
using ostk::core::container::Table;
using ostk::core::filesystem::Path;
using ostk::core::filesystem::File;
using ostk::core::filesystem::Directory;

using ostk::mathematics::object::Vector3d;
using ostk::mathematics::geometry::d3::transformation::rotation::Quaternion;
using ostk::mathematics::geometry::d3::transformation::rotation::RotationVector;

using ostk::physics::unit::Angle;
using ostk::physics::time::Scale;
using ostk::physics::time::Instant;
using ostk::physics::time::DateTime;
using ostk::physics::coordinate::Frame;
using ostk::physics::coordinate::Position;
using ostk::physics::coordinate::Transform;

using ostk::physics::environment::ephemeris::spice::Engine;
using ostk::physics::environment::ephemeris::spice::Manager;
using ostk::physics::environment::ephemeris::spice::Kernel;

TEST(OpenSpaceToolkit_Physics_Environment_Ephemeris_SPICE, Constructor)
{
    {
        EXPECT_NO_THROW(SPICE spice {SPICE::Object::Earth});
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Ephemeris_SPICE, IsDefined)
{
    {
        const SPICE spice = {SPICE::Object::Earth};

        EXPECT_TRUE(spice.isDefined());
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Ephemeris_SPICE, AccessFrame)
{
    {
        const Directory spiceLocalRepository =
            Directory::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Ephemeris/SPICE"));

        const Array<Tuple<SPICE::Object, File, Real, Real, Real, Real, Array<Kernel>>> referenceScenarios = {
            {SPICE::Object::Earth,
             File::Path(Path::Parse(
                 "/app/test/OpenSpaceToolkit/Physics/Environment/Ephemeris/SPICE/AccessFrame/Scenario_1 Earth.csv"
             )),
             0.0,
             0.0,
             0.03,
             1e-10,
             {Kernel::File(File::Path(spiceLocalRepository.getPath() + Path::Parse("naif0012.tls"))),  // Leap seconds
              Kernel::File(File::Path(spiceLocalRepository.getPath() + Path::Parse("de430.bsp"))),     // Ephemeris
              Kernel::File(File::Path(spiceLocalRepository.getPath() + Path::Parse("pck00010.tpc"))
              ),  // System body shape and orientation constants
              Kernel::File(File::Path(spiceLocalRepository.getPath() + Path::Parse("earth_assoc_itrf93.tf"))),
              Kernel::File(File::Path(spiceLocalRepository.getPath() + Path::Parse("earth_000101_181204_180912.bpc")))}
            },
            {SPICE::Object::Sun,
             File::Path(Path::Parse(
                 "/app/test/OpenSpaceToolkit/Physics/Environment/Ephemeris/SPICE/AccessFrame/Scenario_1 Sun.csv"
             )),
             100.0,
             1e-5,
             0.0,
             1e-12,
             {
                 Kernel::File(File::Path(spiceLocalRepository.getPath() + Path::Parse("naif0012.tls"))
                 ),                                                                                    // Leap seconds
                 Kernel::File(File::Path(spiceLocalRepository.getPath() + Path::Parse("de430.bsp"))),  // Ephemeris
                 Kernel::File(File::Path(spiceLocalRepository.getPath() + Path::Parse("pck00010.tpc"))
                 )  // System body shape and orientation constants
             }},
            {SPICE::Object::Moon,
             File::Path(Path::Parse(
                 "/app/test/OpenSpaceToolkit/Physics/Environment/Ephemeris/SPICE/AccessFrame/Scenario_1 Moon.csv"
             )),
             10.0,
             1e-5,
             1.0,
             1e-11,
             {Kernel::File(File::Path(spiceLocalRepository.getPath() + Path::Parse("naif0012.tls"))),  // Leap seconds
              Kernel::File(File::Path(spiceLocalRepository.getPath() + Path::Parse("de430.bsp"))),     // Ephemeris
              Kernel::File(File::Path(spiceLocalRepository.getPath() + Path::Parse("pck00010.tpc"))
              ),  // System body shape and orientation constants
              Kernel::File(File::Path(spiceLocalRepository.getPath() + Path::Parse("moon_080317.tf"))),
              Kernel::File(File::Path(spiceLocalRepository.getPath() + Path::Parse("moon_assoc_me.tf"))),
              Kernel::File(File::Path(spiceLocalRepository.getPath() + Path::Parse("moon_pa_de421_1900-2050.bpc")))}}
        };

        for (const auto& referenceScenario : referenceScenarios)
        {
            const SPICE::Object object = std::get<0>(referenceScenario);
            const File referenceDataFile = std::get<1>(referenceScenario);
            const Real positionTolerance_m = std::get<2>(referenceScenario);
            const Real velocityTolerance_meterPerSec = std::get<3>(referenceScenario);
            const Real orientation_asec = std::get<4>(referenceScenario);
            const Real angularVelocityTolerance_radPerSec = std::get<5>(referenceScenario);
            const Array<Kernel> kernels = std::get<6>(referenceScenario);

            Engine::Get().setMode(Engine::Mode::Manual);

            Engine::Get().reset();

            for (const auto& kernel : kernels)
            {
                Engine::Get().loadKernel(kernel);
            }

            const SPICE spice = {object};

            const Shared<const Frame> frameSPtr = spice.accessFrame();

            const Table referenceData = Table::Load(referenceDataFile, Table::Format::CSV, true);

            for (const auto& referenceDataRow : referenceData)
            {
                const Instant instant_reference =
                    Instant::DateTime(DateTime::Parse(referenceDataRow[0].accessString()), Scale::UTC);
                const Vector3d x_GCRF_reference = {
                    referenceDataRow[1].accessReal(), referenceDataRow[2].accessReal(), referenceDataRow[3].accessReal()
                };
                const Vector3d v_GCRF_reference = {
                    referenceDataRow[4].accessReal(), referenceDataRow[5].accessReal(), referenceDataRow[6].accessReal()
                };
                const Quaternion q_OBJECT_GCRF_reference = Quaternion::XYZS(
                                                               referenceDataRow[7].accessReal(),
                                                               referenceDataRow[8].accessReal(),
                                                               referenceDataRow[9].accessReal(),
                                                               referenceDataRow[10].accessReal()
                )
                                                               .toNormalized();
                const Vector3d w_OBJECT_GCRF_in_OBJECT_reference = {
                    referenceDataRow[11].accessReal(),
                    referenceDataRow[12].accessReal(),
                    referenceDataRow[13].accessReal()
                };

                const Vector3d x_GCRF = frameSPtr->getOriginIn(Frame::GCRF(), instant_reference).getCoordinates();
                const Vector3d v_GCRF = frameSPtr->getVelocityIn(Frame::GCRF(), instant_reference).getCoordinates();
                const Quaternion q_OBJECT_GCRF =
                    Frame::GCRF()->getTransformTo(frameSPtr, instant_reference).getOrientation();
                const Vector3d w_OBJECT_GCRF_in_OBJECT =
                    Frame::GCRF()->getTransformTo(frameSPtr, instant_reference).getAngularVelocity();

                ASSERT_TRUE(x_GCRF.isNear(x_GCRF_reference, positionTolerance_m)) << String::Format(
                    "{} - {} ~ {} = {} [m]",
                    instant_reference.toString(),
                    x_GCRF.toString(),
                    x_GCRF_reference.toString(),
                    (x_GCRF - x_GCRF_reference).norm()
                );
                ASSERT_TRUE(v_GCRF.isNear(v_GCRF_reference, velocityTolerance_meterPerSec)) << String::Format(
                    "{} - {} ~ {} = {} [m/s]",
                    instant_reference.toString(),
                    v_GCRF.toString(),
                    v_GCRF_reference.toString(),
                    (v_GCRF - v_GCRF_reference).norm()
                );
                ASSERT_TRUE(q_OBJECT_GCRF.isNear(q_OBJECT_GCRF_reference, Angle::Arcseconds(orientation_asec)))
                    << String::Format(
                           "{} - {} ~ {} = {} [asec]",
                           instant_reference.toString(),
                           q_OBJECT_GCRF.toString(),
                           q_OBJECT_GCRF_reference.toString(),
                           q_OBJECT_GCRF.angularDifferenceWith(q_OBJECT_GCRF_reference).inArcseconds().toString()
                       );
                ASSERT_TRUE(w_OBJECT_GCRF_in_OBJECT.isNear(
                    w_OBJECT_GCRF_in_OBJECT_reference, angularVelocityTolerance_radPerSec
                ))
                    << String::Format(
                           "{} - {} ~ {} = {} [rad/s]",
                           instant_reference.toString(),
                           w_OBJECT_GCRF_in_OBJECT.toString(),
                           w_OBJECT_GCRF_in_OBJECT_reference.toString(),
                           (w_OBJECT_GCRF_in_OBJECT - w_OBJECT_GCRF_in_OBJECT_reference).norm()
                       );
            }

            Engine::Get().setMode(Engine::DefaultMode());

            Engine::Get().reset();
        }
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Ephemeris_SPICE, StringFromObject)
{
    {
        EXPECT_EQ("Sun", SPICE::StringFromObject(SPICE::Object::Sun));
        EXPECT_EQ("Mercury", SPICE::StringFromObject(SPICE::Object::Mercury));
        EXPECT_EQ("Venus", SPICE::StringFromObject(SPICE::Object::Venus));
        EXPECT_EQ("Earth", SPICE::StringFromObject(SPICE::Object::Earth));
        EXPECT_EQ("Moon", SPICE::StringFromObject(SPICE::Object::Moon));
        EXPECT_EQ("Mars", SPICE::StringFromObject(SPICE::Object::Mars));
        EXPECT_EQ("Jupiter", SPICE::StringFromObject(SPICE::Object::Jupiter));
        EXPECT_EQ("Saturn", SPICE::StringFromObject(SPICE::Object::Saturn));
        EXPECT_EQ("Uranus", SPICE::StringFromObject(SPICE::Object::Uranus));
        EXPECT_EQ("Neptune", SPICE::StringFromObject(SPICE::Object::Neptune));
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Ephemeris_SPICE, ManualMode)
{
    {
        const Directory spiceLocalRepository =
            Directory::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Ephemeris/SPICE"));

        Engine::Get().setMode(Engine::Mode::Manual);

        Engine::Get().reset();

        const SPICE spice = {SPICE::Object::Sun};

        const Shared<const Frame> sunFrameSPtr = spice.accessFrame();

        const Instant instant = Instant::DateTime(DateTime(2016, 1, 1, 0, 0, 0), Scale::UTC);

        Position sunPosition = Position::Undefined();

        EXPECT_ANY_THROW({ sunPosition = sunFrameSPtr->getOriginIn(Frame::GCRF(), instant); });

        Engine::Get().loadKernel(Kernel::File(File::Path(spiceLocalRepository.getPath() + Path::Parse("./naif0012.tls"))
        ));
        Engine::Get().loadKernel(Kernel::File(File::Path(spiceLocalRepository.getPath() + Path::Parse("./de430.bsp"))));
        Engine::Get().loadKernel(Kernel::File(File::Path(spiceLocalRepository.getPath() + Path::Parse("./pck00010.tpc"))
        ));

        EXPECT_NO_THROW(

            { sunPosition = sunFrameSPtr->getOriginIn(Frame::GCRF(), instant); }

        );

        EXPECT_TRUE(sunPosition.isDefined());

        Engine::Get().setMode(Engine::DefaultMode());

        Engine::Get().reset();
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Ephemeris_SPICE, AutomaticMode)
{
    {
        Manager::Get().setLocalRepository(
            Directory::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Ephemeris/SPICE"))
        );

        Engine::Get().setMode(Engine::Mode::Automatic);

        Engine::Get().reset();

        const SPICE spice = {SPICE::Object::Sun};

        const Shared<const Frame> sunFrameSPtr = spice.accessFrame();

        const Instant instant = Instant::DateTime(DateTime(2016, 1, 1, 0, 0, 0), Scale::UTC);

        Position sunPosition = Position::Undefined();

        EXPECT_NO_THROW(

            { sunPosition = sunFrameSPtr->getOriginIn(Frame::GCRF(), instant); }

        );

        EXPECT_TRUE(sunPosition.isDefined());

        Manager::Get().setLocalRepository(Manager::DefaultLocalRepository());

        Engine::Get().setMode(Engine::DefaultMode());

        Engine::Get().reset();
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Ephemeris_SPICE_Engine, DefaultKernels)
{
    using ostk::core::container::Array;
    using ostk::core::filesystem::Path;
    using ostk::core::filesystem::Directory;

    using ostk::physics::environment::ephemeris::spice::Engine;
    using ostk::physics::environment::ephemeris::spice::Kernel;

    {
        Manager::Get().setLocalRepository(
            Directory::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Ephemeris/SPICE"))
        );

        const Array<Kernel> kernels = Engine::DefaultKernels();

        for (const auto& kernel : kernels)
        {
            EXPECT_TRUE(kernel.isDefined());
        }
    }
}
