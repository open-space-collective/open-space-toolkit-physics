/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Container/Table.hpp>
#include <OpenSpaceToolkit/Core/Container/Tuple.hpp>
#include <OpenSpaceToolkit/Core/Type/Index.hpp>
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

TEST(OpenSpaceToolkit_Physics_Environment_Utility_Eclipse, EclipsePhaseConstructorAndProperties)
{
    using ostk::physics::time::Interval;

    const Instant referenceEpoch = Instant::J2000();
    const Interval interval = Interval::Closed(referenceEpoch, referenceEpoch + Duration::Minutes(1.0));

    {
        const EclipsePhase phase(EclipsePhase::Region::Penumbra, interval, false);

        EXPECT_EQ(phase.getRegion(), EclipsePhase::Region::Penumbra);
        EXPECT_EQ(phase.getInterval(), interval);
        EXPECT_EQ(phase.isComplete(), false);
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Utility_Eclipse, EclipsePhaseStreamOperator)
{
    {
        using ostk::physics::time::Interval;

        const EclipsePhase phase(
            EclipsePhase::Region::Penumbra,
            Interval::Closed(Instant::J2000(), Instant::J2000() + Duration::Minutes(1.0)),
            false
        );

        testing::internal::CaptureStdout();

        EXPECT_NO_THROW(std::cout << phase << std::endl);

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Utility_Eclipse, EclipsePhaseEqualityOperators)
{
    using ostk::physics::time::Interval;

    const Instant referenceEpoch = Instant::J2000();
    const Interval interval1 = Interval::Closed(referenceEpoch, referenceEpoch + Duration::Minutes(1.0));
    const Interval interval2 =
        Interval::Closed(referenceEpoch + Duration::Minutes(1.0), referenceEpoch + Duration::Minutes(2.0));

    {
        const EclipsePhase phase1(EclipsePhase::Region::Penumbra, interval1, false);

        EXPECT_TRUE(phase1 == phase1);
        EXPECT_FALSE(phase1 != phase1);
    }

    {
        const EclipsePhase phase1(EclipsePhase::Region::Umbra, interval1, true);
        const EclipsePhase phase2(EclipsePhase::Region::Umbra, interval1, true);

        EXPECT_TRUE(phase1 == phase2);
        EXPECT_FALSE(phase1 != phase2);
    }

    {
        const EclipsePhase phase1(EclipsePhase::Region::Umbra, interval1, true);
        const EclipsePhase phase2(EclipsePhase::Region::Penumbra, interval1, true);

        EXPECT_FALSE(phase1 == phase2);
        EXPECT_TRUE(phase1 != phase2);
    }

    {
        const EclipsePhase phase1(EclipsePhase::Region::Umbra, interval1, true);
        const EclipsePhase phase2(EclipsePhase::Region::Umbra, interval2, true);

        EXPECT_FALSE(phase1 == phase2);
        EXPECT_TRUE(phase1 != phase2);
    }

    {
        const EclipsePhase phase1(EclipsePhase::Region::Umbra, interval1, true);
        const EclipsePhase phase2(EclipsePhase::Region::Umbra, interval1, false);

        EXPECT_FALSE(phase1 == phase2);
        EXPECT_TRUE(phase1 != phase2);
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Utility_Eclipse, EclipseConstructorAndProperties)
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
            EclipsePhase(EclipsePhase::Region::Penumbra, intervals[0], true),
            EclipsePhase(EclipsePhase::Region::Umbra, intervals[1], true),
            EclipsePhase(EclipsePhase::Region::Penumbra, intervals[2], true)
        };

        const Eclipse eclipse(*sun, *earth, phases);

        EXPECT_EQ(eclipse.accessOccultedCelestialObject().getName(), "Sun");
        EXPECT_EQ(eclipse.accessOccultingCelestialObject().getName(), "Earth");
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
            EclipsePhase(EclipsePhase::Region::Umbra, intervals[0], true),
            EclipsePhase(EclipsePhase::Region::Penumbra, intervals[1], true)
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
            EclipsePhase(EclipsePhase::Region::Penumbra, intervals[0], true),
            EclipsePhase(EclipsePhase::Region::Umbra, intervals[1], true)
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
        const Array<EclipsePhase> phases = {EclipsePhase(EclipsePhase::Region::Umbra, intervals[0], true)};

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
        const Array<EclipsePhase> phases = {EclipsePhase(EclipsePhase::Region::Penumbra, intervals[0], true)};

        const Eclipse eclipse(*sun, *earth, phases);

        EXPECT_EQ(eclipse.getDuration(true), Duration::Minutes(1.0));
        EXPECT_EQ(eclipse.getDuration(false), Duration::Minutes(0.0));

        const Interval intervalWithPenumbra = eclipse.getInterval(true);
        EXPECT_EQ(intervalWithPenumbra, intervals[0]);

        const Interval intervalWithoutPenumbra = eclipse.getInterval(false);
        EXPECT_FALSE(intervalWithoutPenumbra.isDefined());
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Utility_Eclipse, EclipseStreamOperator)
{
    using ostk::physics::time::Interval;

    {
        const Environment environment = Environment::Default();
        const Shared<const Celestial> sun = environment.accessCelestialObjectWithName("Sun");
        const Shared<const Celestial> earth = environment.accessCelestialObjectWithName("Earth");
        const Instant referenceEpoch = Instant::J2000();
        const Array<EclipsePhase> phases = {
            EclipsePhase(
                EclipsePhase::Region::Penumbra,
                Interval::Closed(referenceEpoch + Duration::Minutes(0.0), referenceEpoch + Duration::Minutes(1.0)),
                true
            ),
            EclipsePhase(
                EclipsePhase::Region::Umbra,
                Interval::Closed(referenceEpoch + Duration::Minutes(1.0), referenceEpoch + Duration::Minutes(2.0)),
                true
            )
        };

        const Eclipse eclipse(*sun, *earth, phases);

        testing::internal::CaptureStdout();

        EXPECT_NO_THROW(std::cout << eclipse << std::endl);

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Utility_Eclipse, EclipseConstructorFailureNoPhases)
{
    const Environment environment = Environment::Default();
    const Shared<const Celestial> sun = environment.accessCelestialObjectWithName("Sun");
    const Shared<const Celestial> earth = environment.accessCelestialObjectWithName("Earth");

    const Array<EclipsePhase> emptyPhases = {};

    EXPECT_THROW({ const Eclipse eclipse(*sun, *earth, emptyPhases); }, ostk::core::error::RuntimeError);
}

TEST(OpenSpaceToolkit_Physics_Environment_Utility_Eclipse, EclipseConstructorFailurePhasesOverlap)
{
    using ostk::physics::time::Interval;

    const Environment environment = Environment::Default();
    const Shared<const Celestial> sun = environment.accessCelestialObjectWithName("Sun");
    const Shared<const Celestial> earth = environment.accessCelestialObjectWithName("Earth");

    const Instant referenceEpoch = Instant::J2000();
    const Array<EclipsePhase> overlappingPhases = {
        EclipsePhase(
            EclipsePhase::Region::Penumbra,
            Interval::Closed(referenceEpoch, referenceEpoch + Duration::Minutes(10.0)),
            true
        ),
        EclipsePhase(
            EclipsePhase::Region::Umbra,
            Interval::Closed(referenceEpoch + Duration::Minutes(9.0), referenceEpoch + Duration::Minutes(20.0)),
            true
        )
    };

    EXPECT_THROW({ const Eclipse eclipse(*sun, *earth, overlappingPhases); }, ostk::core::error::RuntimeError);
}

TEST(OpenSpaceToolkit_Physics_Environment_Utility_Eclipse, EclipseConstructorFailurePhasesHaveGaps)
{
    using ostk::physics::time::Interval;

    const Environment environment = Environment::Default();
    const Shared<const Celestial> sun = environment.accessCelestialObjectWithName("Sun");
    const Shared<const Celestial> earth = environment.accessCelestialObjectWithName("Earth");

    const Instant referenceEpoch = Instant::J2000();
    const Array<EclipsePhase> gappedPhases = {
        EclipsePhase(
            EclipsePhase::Region::Penumbra,
            Interval::Closed(referenceEpoch, referenceEpoch + Duration::Minutes(10.0)),
            true
        ),
        EclipsePhase(
            EclipsePhase::Region::Umbra,
            Interval::Closed(referenceEpoch + Duration::Minutes(11.0), referenceEpoch + Duration::Minutes(20.0)),
            true
        )
    };

    EXPECT_THROW({ const Eclipse eclipse(*sun, *earth, gappedPhases); }, ostk::core::error::RuntimeError);
}

TEST(OpenSpaceToolkit_Physics_Environment_Utility_Eclipse, EclipseMultipleUmbas)
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
        EclipsePhase(EclipsePhase::Region::Umbra, intervals[0], true),
        EclipsePhase(EclipsePhase::Region::Penumbra, intervals[1], true),
        EclipsePhase(EclipsePhase::Region::Umbra, intervals[2], true)
    };

    const Eclipse eclipse(*sun, *earth, phases);

    EXPECT_EQ(eclipse.getDuration(true), Duration::Minutes(3.0));
    EXPECT_EQ(eclipse.getDuration(false), Duration::Minutes(2.0));

    const Interval intervalWithPenumbra = eclipse.getInterval(true);
    EXPECT_EQ(intervalWithPenumbra, Interval::Closed(intervals[0].getStart(), intervals[2].getEnd()));

    EXPECT_THROW({ eclipse.getInterval(false); }, ostk::core::error::RuntimeError);
}

TEST(OpenSpaceToolkit_Physics_Environment_Utility_Eclipse, EclipseNoUmbras)
{
    using ostk::physics::time::Interval;

    const Environment environment = Environment::Default();
    const Shared<const Celestial> sun = environment.accessCelestialObjectWithName("Sun");
    const Shared<const Celestial> earth = environment.accessCelestialObjectWithName("Earth");

    const Instant referenceEpoch = Instant::J2000();

    const Array<EclipsePhase> phases = {EclipsePhase(
        EclipsePhase::Region::Penumbra, Interval::Closed(referenceEpoch, referenceEpoch + Duration::Minutes(1.0)), true
    )};

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
        // Scenarios obtained from STK (see directory
        // test/OpenSpaceToolkit/Physics/Environment/Utility/Eclipse/EclipseIntervalsAtPosition)
        const Array<std::tuple<Interval, LLA, Array<Interval>, Array<Interval>, Duration, Duration>>
            referenceScenarios = {

                // Target 1
                {
                    Interval::Closed(
                        Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::UTC),
                        Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::UTC)
                    ),
                    LLA(Angle::Degrees(0.0), Angle::Degrees(0.0), Length::Kilometers(0.0)),
                    {
                        Interval::Closed(
                            Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::UTC),
                            Instant::DateTime(DateTime(2018, 1, 1, 6, 2, 18, 211), Scale::UTC)
                        ),
                        Interval::Closed(
                            Instant::DateTime(DateTime(2018, 1, 1, 18, 4, 52, 262), Scale::UTC),
                            Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::UTC)
                        ),
                    },
                    {Interval::Closed(
                         Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::UTC),
                         Instant::DateTime(DateTime(2018, 1, 1, 6, 4, 39, 519), Scale::UTC)
                     ),
                     Interval::Closed(
                         Instant::DateTime(DateTime(2018, 1, 1, 18, 2, 30, 998), Scale::UTC),
                         Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::UTC)
                     )},
                    Duration::Seconds(30.0),
                    Duration::Seconds(30.0),
                },

                // Target 2
                {
                    Interval::Closed(
                        Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::UTC),
                        Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::UTC)
                    ),
                    LLA(Angle::Degrees(0.0), Angle::Degrees(0.0), Length::Kilometers(500.0)),
                    {
                        Interval::Closed(
                            Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::UTC),
                            Instant::DateTime(DateTime(2018, 1, 1, 4, 26, 13, 544), Scale::UTC)
                        ),
                        Interval::Closed(
                            Instant::DateTime(DateTime(2018, 1, 1, 19, 40, 54, 466), Scale::UTC),
                            Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::UTC)
                        ),
                    },
                    {Interval::Closed(
                         Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::UTC),
                         Instant::DateTime(DateTime(2018, 1, 1, 4, 28, 37, 012), Scale::UTC)
                     ),
                     Interval::Closed(
                         Instant::DateTime(DateTime(2018, 1, 1, 19, 38, 31, 80), Scale::UTC),
                         Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::UTC)
                     )},
                    Duration::Seconds(30.0),
                    Duration::Seconds(30.0),
                },

                // Target 3
                {
                    Interval::Closed(
                        Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::UTC),
                        Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::UTC)
                    ),
                    LLA(Angle::Degrees(+90.0), Angle::Degrees(0.0), Length::Kilometers(0.0)),
                    {Interval::Closed(
                        Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::UTC),
                        Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::UTC)
                    )},
                    {Interval::Closed(
                        Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::UTC),
                        Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::UTC)
                    )},
                    Duration::Seconds(30.0),
                    Duration::Seconds(30.0),
                },

                // Target 4
                {
                    Interval::Closed(
                        Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::UTC),
                        Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::UTC)
                    ),
                    LLA(Angle::Degrees(-90.0), Angle::Degrees(0.0), Length::Kilometers(0.0)),
                    {},
                    {},
                    Duration::Seconds(30.0),
                    Duration::Seconds(30.0),
                },

                // Target 5
                {
                    Interval::Closed(
                        Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::UTC),
                        Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::UTC)
                    ),
                    LLA(Angle::Degrees(0.0), Angle::Degrees(0.0), Length::Kilometers(5000.0)),
                    {
                        Interval::Closed(
                            Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::UTC),
                            Instant::DateTime(DateTime(2018, 1, 1, 1, 45, 9, 118), Scale::UTC)
                        ),
                        Interval::Closed(
                            Instant::DateTime(DateTime(2018, 1, 1, 22, 21, 45, 807), Scale::UTC),
                            Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::UTC)
                        ),
                    },
                    {
                        Interval::Closed(
                            Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::UTC),
                            Instant::DateTime(DateTime(2018, 1, 1, 1, 48, 11, 252), Scale::UTC)
                        ),
                        Interval::Closed(
                            Instant::DateTime(DateTime(2018, 1, 1, 22, 18, 44, 257), Scale::UTC),
                            Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::UTC)
                        ),
                    },
                    Duration::Seconds(30.0),
                    Duration::Seconds(30.0),
                }
            };

        for (const auto& referenceScenario : referenceScenarios)
        {
            const Interval analysisInterval = std::get<0>(referenceScenario);
            const LLA lla = std::get<1>(referenceScenario);
            const Array<Interval> expectedIntervalsUmbra = std::get<2>(referenceScenario);
            const Array<Interval> expectedIntervalsWithPenumbra = std::get<3>(referenceScenario);
            const Duration timeStep = std::get<4>(referenceScenario);
            const Duration tolerance = std::get<5>(referenceScenario);

            const Position position_ITRF = Position::Meters(
                lla.toCartesian(
                    EarthGravitationalModel::EGM2008.equatorialRadius_, EarthGravitationalModel::EGM2008.flattening_
                ),
                Frame::ITRF()
            );
            const Environment environment = Environment::Default();

            const Array<Interval> computedIntervalsUmbra =
                eclipseIntervalsAtPosition(analysisInterval, position_ITRF, environment, false, timeStep);

            EXPECT_EQ(expectedIntervalsUmbra.getSize(), computedIntervalsUmbra.getSize());

            for (Index index = 0; index < expectedIntervalsUmbra.getSize(); index++)
            {
                const Interval& expectedIntervalUmbra = expectedIntervalsUmbra.at(index);
                const Interval& computedIntervalUmbra = computedIntervalsUmbra.at(index);

                EXPECT_TRUE(computedIntervalUmbra.getStart().isNear(expectedIntervalUmbra.getStart(), tolerance))
                    << String::Format(
                           "{} ~ {}",
                           computedIntervalUmbra.getStart().toString(),
                           expectedIntervalUmbra.getStart().toString()
                       );
                EXPECT_TRUE(computedIntervalUmbra.getEnd().isNear(expectedIntervalUmbra.getEnd(), tolerance))
                    << String::Format(
                           "{} ~ {}",
                           computedIntervalUmbra.getEnd().toString(),
                           expectedIntervalUmbra.getEnd().toString()
                       );
            }

            const Array<Interval> computedIntervalsWithPenumbra =
                eclipseIntervalsAtPosition(analysisInterval, position_ITRF, environment, true, timeStep);

            EXPECT_EQ(expectedIntervalsWithPenumbra.getSize(), computedIntervalsWithPenumbra.getSize());

            for (Index index = 0; index < expectedIntervalsWithPenumbra.getSize(); index++)
            {
                const Interval& expectedIntervalWithPenumbra = expectedIntervalsWithPenumbra.at(index);
                const Interval& computedIntervalWithPenumbra = computedIntervalsWithPenumbra.at(index);

                EXPECT_TRUE(
                    computedIntervalWithPenumbra.getStart().isNear(expectedIntervalWithPenumbra.getStart(), tolerance)
                )
                    << String::Format(
                           "{} ~ {}",
                           computedIntervalWithPenumbra.getStart().toString(),
                           expectedIntervalWithPenumbra.getStart().toString()
                       );
                EXPECT_TRUE(
                    computedIntervalWithPenumbra.getEnd().isNear(expectedIntervalWithPenumbra.getEnd(), tolerance)
                )
                    << String::Format(
                           "{} ~ {}",
                           computedIntervalWithPenumbra.getEnd().toString(),
                           expectedIntervalWithPenumbra.getEnd().toString()
                       );
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
         Interval<Real>::Closed(1.0, 1.0)},

        // Inside the Earth
        {Instant::DateTime(DateTime::Parse("2026-01-01T00:30:58.893704395"), Scale::UTC),
         Vector3d(3868261.294497e-6, 9221526.693422e-6, 0.0),
         Interval<Real>::Closed(0.0, 0.0)},

        // At the Earth's center
        {Instant::DateTime(DateTime::Parse("2026-01-01T00:00:00.000000000"), Scale::UTC),
         Vector3d(0.0, 0.0, 0.0),
         Interval<Real>::Closed(0.0, 0.0)},

        // Inside the Sun
        {Instant::J2000(),
         sun->getPositionIn(Frame::GCRF(), Instant::J2000()).inMeters().getCoordinates() + Vector3d(1.0, 1.0, 1.0),
         Interval<Real>::Closed(1.0, 1.0)},

        // At the Sun's Center
        {Instant::J2000(),
         sun->getPositionIn(Frame::GCRF(), Instant::J2000()).inMeters().getCoordinates(),
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
            "Shadow value {} for coordinates {} is not within expected boundaries [{}, {}]",
            shadowValue,
            coordinates.toString(),
            expectedShadowValueBoundaries.getLowerBound(),
            expectedShadowValueBoundaries.getUpperBound()
        );
    }
}
