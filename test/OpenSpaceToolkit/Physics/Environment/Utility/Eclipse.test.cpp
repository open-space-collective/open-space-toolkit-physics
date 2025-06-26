/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Container/Table.hpp>
#include <OpenSpaceToolkit/Core/Container/Tuple.hpp>
#include <OpenSpaceToolkit/Core/Type/Shared.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include <OpenSpaceToolkit/Mathematics/Object/Interval.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Position.hpp>
#include <OpenSpaceToolkit/Physics/Environment.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Object/Celestial.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Object/Celestial/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Utility/Eclipse.hpp>
#include <OpenSpaceToolkit/Physics/Time/DateTime.hpp>
#include <OpenSpaceToolkit/Physics/Time/Duration.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Time/Interval.hpp>
#include <OpenSpaceToolkit/Physics/Time/Scale.hpp>

#include <Global.test.hpp>

using ostk::core::container::Array;
using ostk::core::container::Table;
using ostk::core::container::Tuple;
using ostk::core::filesystem::File;
using ostk::core::filesystem::Path;
using ostk::core::type::Index;
using ostk::core::type::Real;
using ostk::core::type::Shared;
using ostk::core::type::String;

using ostk::physics::coordinate::Frame;
using ostk::physics::coordinate::Position;
using ostk::physics::coordinate::spherical::LLA;
using ostk::physics::Environment;
using ostk::physics::environment::object::Celestial;
using ostk::physics::environment::object::celestial::Earth;
using ostk::physics::environment::utilities::Eclipse;
using ostk::physics::environment::utilities::eclipseIntervalsAtPosition;
using ostk::physics::environment::utilities::EclipsePhase;
using ostk::physics::environment::utilities::montenbruckGillShadowFunction;
using ostk::physics::time::DateTime;
using ostk::physics::time::Duration;
using ostk::physics::time::Instant;
using ostk::physics::time::Scale;
using ostk::physics::unit::Angle;
using ostk::physics::unit::Length;
using EarthGravitationalModel = ostk::physics::environment::gravitational::Earth;

TEST(OpenSpaceToolkit_Physics_Environment_Utility_Eclipse, ConstructorAndProperties)
{
    using ostk::physics::time::Interval;

    const Environment environment = Environment::Default();
    const Shared<const Celestial> sun = environment.accessCelestialObjectWithName("Sun");
    const Shared<const Celestial> earth = environment.accessCelestialObjectWithName("Earth");

    const Instant referenceEpoch = Instant::J2000();
    const Array<Interval> intervals = {
        Interval::Closed(referenceEpoch + Duration::Minutes(0.0), referenceEpoch + Duration::Minutes(1.0)),
        Interval::Closed(referenceEpoch + Duration::Minutes(1.0), referenceEpoch + Duration::Minutes(2.0)),
        Interval::Closed(referenceEpoch + Duration::Minutes(2.0), referenceEpoch + Duration::Minutes(3.0))
    };

    // Test Case 1: Penumbra-Umbra-Penumbra
    {
        const Array<EclipsePhase> phases = {
            EclipsePhase(EclipsePhase::Region::PENUMBRA, intervals[0], true),
            EclipsePhase(EclipsePhase::Region::UMBRA, intervals[1], true),
            EclipsePhase(EclipsePhase::Region::PENUMBRA, intervals[2], true)
        };

        const Eclipse eclipse(*sun, *earth, phases);

        EXPECT_EQ(eclipse.getOccultedCelestialObject().getName(), "Sun");
        EXPECT_EQ(eclipse.getOccultingCelestialObject().getName(), "Earth");
        EXPECT_EQ(eclipse.getPhases().getSize(), 3);

        EXPECT_EQ(eclipse.getDuration(true), Duration::Minutes(3.0));
        EXPECT_EQ(eclipse.getDuration(false), Duration::Minutes(1.0));

        const Interval intervalWithPenumbra = eclipse.getInterval(true);
        EXPECT_EQ(intervalWithPenumbra, Interval::Closed(intervals[0].getStart(), intervals[2].getEnd()));

        const Interval intervalWithoutPenumbra = eclipse.getInterval(false);
        EXPECT_EQ(intervalWithoutPenumbra, intervals[1]);
    }

    // Test Case 2: Umbra-Penumbra
    {
        const Array<EclipsePhase> phases = {
            EclipsePhase(EclipsePhase::Region::UMBRA, intervals[0], true),
            EclipsePhase(EclipsePhase::Region::PENUMBRA, intervals[1], true)
        };

        const Eclipse eclipse(*sun, *earth, phases);

        EXPECT_EQ(eclipse.getDuration(true), Duration::Minutes(2.0));
        EXPECT_EQ(eclipse.getDuration(false), Duration::Minutes(1.0));

        const Interval intervalWithPenumbra = eclipse.getInterval(true);
        EXPECT_EQ(intervalWithPenumbra, Interval::Closed(intervals[0].getStart(), intervals[1].getEnd()));

        const Interval intervalWithoutPenumbra = eclipse.getInterval(false);
        EXPECT_EQ(intervalWithoutPenumbra, intervals[0]);
    }

    // Test Case 3: Penumbra-Umbra
    {
        const Array<EclipsePhase> phases = {
            EclipsePhase(EclipsePhase::Region::PENUMBRA, intervals[0], true),
            EclipsePhase(EclipsePhase::Region::UMBRA, intervals[1], true)
        };

        const Eclipse eclipse(*sun, *earth, phases);

        EXPECT_EQ(eclipse.getDuration(true), Duration::Minutes(2.0));
        EXPECT_EQ(eclipse.getDuration(false), Duration::Minutes(1.0));

        const Interval intervalWithPenumbra = eclipse.getInterval(true);
        EXPECT_EQ(intervalWithPenumbra, Interval::Closed(intervals[0].getStart(), intervals[1].getEnd()));

        const Interval intervalWithoutPenumbra = eclipse.getInterval(false);
        EXPECT_EQ(intervalWithoutPenumbra, intervals[1]);
    }

    // Test Case 4: Umbra only
    {
        const Array<EclipsePhase> phases = {EclipsePhase(EclipsePhase::Region::UMBRA, intervals[0], true)};

        const Eclipse eclipse(*sun, *earth, phases);

        EXPECT_EQ(eclipse.getDuration(true), Duration::Minutes(1.0));
        EXPECT_EQ(eclipse.getDuration(false), Duration::Minutes(1.0));

        const Interval intervalWithPenumbra = eclipse.getInterval(true);
        EXPECT_EQ(intervalWithPenumbra, intervals[0]);

        const Interval intervalWithoutPenumbra = eclipse.getInterval(false);
        EXPECT_EQ(intervalWithoutPenumbra, intervals[0]);
    }

    // Test Case 5: Penumbra only
    {
        const Array<EclipsePhase> phases = {EclipsePhase(EclipsePhase::Region::PENUMBRA, intervals[0], true)};

        const Eclipse eclipse(*sun, *earth, phases);

        EXPECT_EQ(eclipse.getDuration(true), Duration::Minutes(1.0));
        EXPECT_EQ(eclipse.getDuration(false), Duration::Minutes(0.0));

        const Interval intervalWithPenumbra = eclipse.getInterval(true);
        EXPECT_EQ(intervalWithPenumbra, intervals[0]);

        const Interval intervalWithoutPenumbra = eclipse.getInterval(false);
        EXPECT_FALSE(intervalWithoutPenumbra.isDefined());
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Utility_Eclipse, ConstructorFailureNoPhases)
{
    const Environment environment = Environment::Default();
    const Shared<const Celestial> sun = environment.accessCelestialObjectWithName("Sun");
    const Shared<const Celestial> earth = environment.accessCelestialObjectWithName("Earth");

    const Array<EclipsePhase> emptyPhases = {};

    EXPECT_THROW({ const Eclipse eclipse(*sun, *earth, emptyPhases); }, ostk::core::error::RuntimeError);
}

TEST(OpenSpaceToolkit_Physics_Environment_Utility_Eclipse, ConstructorFailurePhasesOverlap)
{
    using ostk::physics::time::Interval;

    const Environment environment = Environment::Default();
    const Shared<const Celestial> sun = environment.accessCelestialObjectWithName("Sun");
    const Shared<const Celestial> earth = environment.accessCelestialObjectWithName("Earth");

    const Instant referenceEpoch = Instant::J2000();
    const Array<EclipsePhase> overlappingPhases = {
        EclipsePhase(
            EclipsePhase::Region::PENUMBRA,
            Interval::Closed(referenceEpoch, referenceEpoch + Duration::Minutes(10.0)),
            true
        ),
        EclipsePhase(
            EclipsePhase::Region::UMBRA,
            Interval::Closed(referenceEpoch + Duration::Minutes(9.0), referenceEpoch + Duration::Minutes(20.0)),
            true
        )
    };

    EXPECT_THROW({ const Eclipse eclipse(*sun, *earth, overlappingPhases); }, ostk::core::error::RuntimeError);
}

TEST(OpenSpaceToolkit_Physics_Environment_Utility_Eclipse, ConstructorFailurePhasesHaveGaps)
{
    using ostk::physics::time::Interval;

    const Environment environment = Environment::Default();
    const Shared<const Celestial> sun = environment.accessCelestialObjectWithName("Sun");
    const Shared<const Celestial> earth = environment.accessCelestialObjectWithName("Earth");

    const Instant referenceEpoch = Instant::J2000();
    const Array<EclipsePhase> gappedPhases = {
        EclipsePhase(
            EclipsePhase::Region::PENUMBRA,
            Interval::Closed(referenceEpoch, referenceEpoch + Duration::Minutes(10.0)),
            true
        ),
        EclipsePhase(
            EclipsePhase::Region::UMBRA,
            Interval::Closed(referenceEpoch + Duration::Minutes(11.0), referenceEpoch + Duration::Minutes(20.0)),
            true
        )
    };

    EXPECT_THROW({ const Eclipse eclipse(*sun, *earth, gappedPhases); }, ostk::core::error::RuntimeError);
}

TEST(OpenSpaceToolkit_Physics_Environment_Utility_Eclipse, MultipleUmbas)
{
    using ostk::physics::time::Interval;

    const Environment environment = Environment::Default();
    const Shared<const Celestial> sun = environment.accessCelestialObjectWithName("Sun");
    const Shared<const Celestial> earth = environment.accessCelestialObjectWithName("Earth");

    const Instant referenceEpoch = Instant::J2000();
    const Array<Interval> intervals = {
        Interval::Closed(referenceEpoch + Duration::Minutes(0.0), referenceEpoch + Duration::Minutes(1.0)),
        Interval::Closed(referenceEpoch + Duration::Minutes(1.0), referenceEpoch + Duration::Minutes(2.0)),
        Interval::Closed(referenceEpoch + Duration::Minutes(2.0), referenceEpoch + Duration::Minutes(3.0))
    };

    const Array<EclipsePhase> phases = {
        EclipsePhase(EclipsePhase::Region::UMBRA, intervals[0], true),
        EclipsePhase(EclipsePhase::Region::PENUMBRA, intervals[1], true),
        EclipsePhase(EclipsePhase::Region::UMBRA, intervals[2], true)
    };

    const Eclipse eclipse(*sun, *earth, phases);

    EXPECT_EQ(eclipse.getDuration(true), Duration::Minutes(3.0));
    EXPECT_EQ(eclipse.getDuration(false), Duration::Minutes(2.0));

    const Interval intervalWithPenumbra = eclipse.getInterval(true);
    EXPECT_EQ(intervalWithPenumbra, Interval::Closed(intervals[0].getStart(), intervals[2].getEnd()));

    EXPECT_THROW({ eclipse.getInterval(false); }, ostk::core::error::RuntimeError);
}

TEST(OpenSpaceToolkit_Physics_Environment_Utility_Eclipse, NoUmbras)
{
    using ostk::physics::time::Interval;

    const Environment environment = Environment::Default();
    const Shared<const Celestial> sun = environment.accessCelestialObjectWithName("Sun");
    const Shared<const Celestial> earth = environment.accessCelestialObjectWithName("Earth");

    const Instant referenceEpoch = Instant::J2000();

    const Array<EclipsePhase> phases = {
        EclipsePhase(
            EclipsePhase::Region::PENUMBRA,
            Interval::Closed(referenceEpoch, referenceEpoch + Duration::Minutes(1.0)),
            true
        ),
    };

    const Eclipse eclipse(*sun, *earth, phases);

    EXPECT_EQ(eclipse.getDuration(true), Duration::Minutes(1.0));
    EXPECT_EQ(eclipse.getDuration(false), Duration::Minutes(0.0));

    const Interval intervalWithPenumbra = eclipse.getInterval(true);
    EXPECT_EQ(intervalWithPenumbra, Interval::Closed(referenceEpoch, referenceEpoch + Duration::Minutes(1.0)));

    const Interval intervalWithoutPenumbra = eclipse.getInterval(false);
    EXPECT_FALSE(intervalWithoutPenumbra.isDefined());
}

TEST(OpenSpaceToolkit_Physics_Environment_Utility_Eclipse, EclipseIntervalsAtPosition)
{
    using ostk::physics::time::Interval;

    {
        const Array<Tuple<Interval, LLA, File, Duration>> referenceScenarios = {
            {
                Interval::Closed(
                    Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::UTC),
                    Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::UTC)
                ),
                LLA(Angle::Degrees(0.0), Angle::Degrees(0.0), Length::Meters(10.0)),  // [TBM] Should be 0 [m]
                File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Utility/Eclipse/"
                                       "EclipseIntervalsAtPosition/Target_1 Eclipse.csv")),
                Duration::Minutes(2.0)  // [TBM] Should improve precision
            },
            {
                Interval::Closed(
                    Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::UTC),
                    Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::UTC)
                ),
                LLA(Angle::Degrees(0.0), Angle::Degrees(0.0), Length::Kilometers(500.0)),
                File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Utility/Eclipse/"
                                       "EclipseIntervalsAtPosition/Target_2 Eclipse.csv")),
                Duration::Minutes(2.0)  // [TBM] Should improve precision
            },
            {
                Interval::Closed(
                    Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::UTC),
                    Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::UTC)
                ),
                LLA(Angle::Degrees(+90.0), Angle::Degrees(0.0), Length::Meters(10.0)),  // [TBM] Should be 0 [m]
                File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Utility/Eclipse/"
                                       "EclipseIntervalsAtPosition/Target_3 Eclipse.csv")),
                Duration::Minutes(2.0)  // [TBM] Should improve precision
            },
            {
                Interval::Closed(
                    Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::UTC),
                    Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::UTC)
                ),
                LLA(Angle::Degrees(-90.0), Angle::Degrees(0.0), Length::Meters(10.0)),  // [TBM] Should be 0 [m]
                File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Utility/Eclipse/"
                                       "EclipseIntervalsAtPosition/Target_4 Eclipse.csv")),
                Duration::Minutes(2.0)  // [TBM] Should improve precision
            },
            {
                Interval::Closed(
                    Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::UTC),
                    Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::UTC)
                ),
                LLA(Angle::Degrees(0.0), Angle::Degrees(0.0), Length::Kilometers(5000.0)),
                File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Utility/Eclipse/"
                                       "EclipseIntervalsAtPosition/Target_5 Eclipse.csv")),
                Duration::Minutes(2.0)  // [TBM] Should improve precision
            }
        };

        for (const auto& referenceScenario : referenceScenarios)
        {
            const Interval analysisInterval = std::get<0>(referenceScenario);
            const LLA lla = std::get<1>(referenceScenario);
            const File referenceDataFile = std::get<2>(referenceScenario);
            const Duration durationTolerance = std::get<3>(referenceScenario);

            const Position position_ITRF = Position::Meters(
                lla.toCartesian(
                    EarthGravitationalModel::EGM2008.equatorialRadius_, EarthGravitationalModel::EGM2008.flattening_
                ),
                Frame::ITRF()
            );
            const Environment environment = Environment::Default();

            const Array<Interval> eclipseIntervals =
                eclipseIntervalsAtPosition(analysisInterval, position_ITRF, environment);

            const Table referenceData = Table::Load(referenceDataFile, Table::Format::CSV, true);

            Index eclipseIntervalIndex = 0;

            for (const auto& referenceDataRow : referenceData)
            {
                const Instant startInstant_reference = Instant::DateTime(
                    DateTime::Parse(referenceDataRow["Start Time (UTCG)"].accessString()), Scale::UTC
                );
                const Instant endInstant_reference =
                    Instant::DateTime(DateTime::Parse(referenceDataRow["Stop Time (UTCG)"].accessString()), Scale::UTC);
                const String currentCondition = referenceDataRow["Current Condition"].accessString();

                if (currentCondition == "Umbra")
                {
                    const Interval& eclipseInterval = eclipseIntervals.at(eclipseIntervalIndex);

                    EXPECT_TRUE(eclipseInterval.getStart().isNear(startInstant_reference, durationTolerance))
                        << String::Format(
                               "{} ~ {}", eclipseInterval.getStart().toString(), startInstant_reference.toString()
                           );
                    EXPECT_TRUE(eclipseInterval.getEnd().isNear(endInstant_reference, durationTolerance))
                        << String::Format(
                               "{} ~ {}", eclipseInterval.getEnd().toString(), endInstant_reference.toString()
                           );

                    eclipseIntervalIndex++;
                }
            }
        }
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Utility_Eclipse, MontenbruckGillShadowFunction)
{
    using ostk::mathematics::object::Interval;
    using ostk::mathematics::object::Vector3d;

    const Environment environment = Environment::Default();
    const Shared<const Celestial> sun = environment.accessCelestialObjectWithName("Sun");
    const Shared<const Celestial> earth = environment.accessCelestialObjectWithName("Earth");

    const Real tolerance = 1e-3;

    // Test cases with timestamps obtained using Orekit v12.2.1 EclipseDetector
    const Array<Tuple<Instant, Vector3d, Interval<Real>>> testCases = {
        // Before penumbra
        {Instant::DateTime(DateTime::Parse("2026-01-01T00:30:58.893704395"), Scale::UTC),
         Vector3d(3868261.294497, 9221526.693422, 0.0),
         Interval<Real>::Closed(1.0, 1.0)},
        // Penumbra start
        {Instant::DateTime(DateTime::Parse("2026-01-01T00:31:08.893704395"), Scale::UTC),
         Vector3d(3809964.652101, 9245764.941298, 0.0),
         Interval<Real>::Closed(1.0 - tolerance, 1.0)},
        // Mid point between penumbra start and umbra start
        {Instant::DateTime(DateTime::Parse("2026-01-01T00:31:18.381233978"), Scale::UTC),
         Vector3d(3754515.113065, 9268420.375974, 0.0),
         Interval<Real>::Closed(0.5 - tolerance, 0.5 + tolerance)},
        // Umbra start
        {Instant::DateTime(DateTime::Parse("2026-01-01T00:31:27.868763562"), Scale::UTC),
         Vector3d(3698930.865026, 9290743.267132, 0.0),
         Interval<Real>::Closed(0.0, tolerance)},
        // Mid point between umbra start and umbra end
        {Instant::DateTime(DateTime::Parse("2026-01-01T00:46:36.017335289"), Scale::UTC),
         Vector3d(-1932406.121736, 9811513.980048, 0.0),
         Interval<Real>::Closed(0.0, 0.0)},
        // Umbra end
        {Instant::DateTime(DateTime::Parse("2026-01-01T01:01:44.165907016"), Scale::UTC),
         Vector3d(-6945698.597771, 7194252.635884, 0.0),
         Interval<Real>::Closed(0.0, tolerance)},
        // Mid point between umbra end and penumbra end
        {Instant::DateTime(DateTime::Parse("2026-01-01T01:01:53.653358409"), Scale::UTC),
         Vector3d(-6988666.481775, 7152519.892074, 0.0),
         Interval<Real>::Closed(0.5 - tolerance, 0.5 + tolerance)},
        // Penumbra end
        {Instant::DateTime(DateTime::Parse("2026-01-01T01:02:03.140809803"), Scale::UTC),
         Vector3d(-7031383.622142, 7110530.525795, 0.0),
         Interval<Real>::Closed(1.0 - tolerance, 1.0)},
        // After penumbra
        {Instant::DateTime(DateTime::Parse("2026-01-01T01:02:13.140809803"), Scale::UTC),
         Vector3d(-7076135.389139, 7065996.600238, 0.0),
         Interval<Real>::Closed(1.0, 1.0)}
    };

    for (const auto& testCase : testCases)
    {
        const Instant instant = std::get<0>(testCase);
        const Vector3d coordinates = std::get<1>(testCase);
        const Interval<Real> expectedShadowValueBoundaries = std::get<2>(testCase);

        const Position position = Position::Meters(coordinates, Frame::GCRF());

        const Real shadowValue = montenbruckGillShadowFunction(instant, position, *sun, *earth);

        EXPECT_TRUE(expectedShadowValueBoundaries.contains(shadowValue)) << String::Format(
            "Shadow value {} is not within expected boundaries [{}, {}]",
            shadowValue,
            expectedShadowValueBoundaries.getLowerBound(),
            expectedShadowValueBoundaries.getUpperBound()
        );
    }
}
