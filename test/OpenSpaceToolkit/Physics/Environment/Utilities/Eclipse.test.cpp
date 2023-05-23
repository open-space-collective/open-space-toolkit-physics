/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Containers/Table.hpp>
#include <OpenSpaceToolkit/Core/Containers/Tuple.hpp>
#include <OpenSpaceToolkit/Core/Types/Shared.hpp>
#include <OpenSpaceToolkit/Core/Types/String.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Position.hpp>
#include <OpenSpaceToolkit/Physics/Environment.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Objects/CelestialBodies/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Utilities/Eclipse.hpp>
#include <OpenSpaceToolkit/Physics/Time/DateTime.hpp>
#include <OpenSpaceToolkit/Physics/Time/Duration.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Time/Interval.hpp>
#include <OpenSpaceToolkit/Physics/Time/Scale.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST(OpenSpaceToolkit_Physics_Environment_Utilities_Eclipse, IsPositionInEclipse)
{
    using ostk::core::types::Shared;
    using ostk::core::types::String;
    using ostk::core::ctnr::Array;
    using ostk::core::ctnr::Table;
    using ostk::core::fs::Path;
    using ostk::core::fs::File;

    using ostk::physics::time::Scale;
    using ostk::physics::time::Instant;
    using ostk::physics::time::Duration;
    using ostk::physics::time::Interval;
    using ostk::physics::time::DateTime;
    using ostk::physics::coord::Position;
    using ostk::physics::coord::Frame;
    using ostk::physics::Environment;
    using ostk::physics::env::utilities::isPositionInEclipse;

    {
        const Position position_ITRF = Position::Meters({7000e3, 0.0, 0.0}, Frame::ITRF());

        Environment environment = Environment::Default();

        {
            const Instant instant = Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::UTC);

            environment.setInstant(instant);

            const Position position_GCRF = position_ITRF.inFrame(Frame::GCRF(), instant);

            EXPECT_TRUE(isPositionInEclipse(position_GCRF, environment));
        }

        {
            const Instant instant = Instant::DateTime(DateTime(2018, 1, 1, 12, 0, 0), Scale::UTC);

            environment.setInstant(instant);

            const Position position_GCRF = position_ITRF.inFrame(Frame::GCRF(), instant);

            EXPECT_FALSE(isPositionInEclipse(position_GCRF, environment));
        }

        {
            const Instant instant = Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::UTC);

            environment.setInstant(instant);

            const Position position_GCRF = position_ITRF.inFrame(Frame::GCRF(), instant);

            EXPECT_TRUE(isPositionInEclipse(position_GCRF, environment));
        }
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Utilities_Eclipse, EclipseIntervalsAtPosition)
{
    using ostk::core::types::Index;
    using ostk::core::types::String;
    using ostk::core::ctnr::Tuple;
    using ostk::core::ctnr::Array;
    using ostk::core::ctnr::Table;
    using ostk::core::fs::Path;
    using ostk::core::fs::File;

    using ostk::physics::time::Scale;
    using ostk::physics::time::Instant;
    using ostk::physics::time::Duration;
    using ostk::physics::time::Interval;
    using ostk::physics::time::DateTime;
    using ostk::physics::units::Length;
    using ostk::physics::units::Angle;
    using ostk::physics::coord::Position;
    using ostk::physics::coord::Frame;
    using ostk::physics::coord::spherical::LLA;
    using ostk::physics::Environment;
    using ostk::physics::env::obj::celest::Earth;
    using ostk::physics::env::utilities::eclipseIntervalsAtPosition;

    {
        const Array<Tuple<Interval, LLA, File, Duration>> referenceScenarios = {
            {
                Interval::Closed(
                    Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::UTC),
                    Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::UTC)
                ),
                LLA(Angle::Degrees(0.0), Angle::Degrees(0.0), Length::Meters(10.0)),  // [TBM] Should be 0 [m]
                File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Utilities/Eclipse/"
                                       "EclipseIntervalsAtPosition/Target_1 Eclipse.csv")),
                Duration::Minutes(2.0)  // [TBM] Should improve precision
            },
            {
                Interval::Closed(
                    Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::UTC),
                    Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::UTC)
                ),
                LLA(Angle::Degrees(0.0), Angle::Degrees(0.0), Length::Kilometers(500.0)),
                File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Utilities/Eclipse/"
                                       "EclipseIntervalsAtPosition/Target_2 Eclipse.csv")),
                Duration::Minutes(2.0)  // [TBM] Should improve precision
            },
            {
                Interval::Closed(
                    Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::UTC),
                    Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::UTC)
                ),
                LLA(Angle::Degrees(+90.0), Angle::Degrees(0.0), Length::Meters(10.0)),  // [TBM] Should be 0 [m]
                File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Utilities/Eclipse/"
                                       "EclipseIntervalsAtPosition/Target_3 Eclipse.csv")),
                Duration::Minutes(2.0)  // [TBM] Should improve precision
            },
            {
                Interval::Closed(
                    Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::UTC),
                    Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::UTC)
                ),
                LLA(Angle::Degrees(-90.0), Angle::Degrees(0.0), Length::Meters(10.0)),  // [TBM] Should be 0 [m]
                File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Utilities/Eclipse/"
                                       "EclipseIntervalsAtPosition/Target_4 Eclipse.csv")),
                Duration::Minutes(2.0)  // [TBM] Should improve precision
            },
            {
                Interval::Closed(
                    Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::UTC),
                    Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::UTC)
                ),
                LLA(Angle::Degrees(0.0), Angle::Degrees(0.0), Length::Kilometers(5000.0)),
                File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Utilities/Eclipse/"
                                       "EclipseIntervalsAtPosition/Target_5 Eclipse.csv")),
                Duration::Minutes(2.0)  // [TBM] Should improve precision
            }};

        for (const auto& referenceScenario : referenceScenarios)
        {
            const Interval analysisInterval = std::get<0>(referenceScenario);
            const LLA lla = std::get<1>(referenceScenario);
            const File referenceDataFile = std::get<2>(referenceScenario);
            const Duration durationTolerance = std::get<3>(referenceScenario);

            const Position position_ITRF =
                Position::Meters(lla.toCartesian(Earth::EquatorialRadius, Earth::Flattening), Frame::ITRF());
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
