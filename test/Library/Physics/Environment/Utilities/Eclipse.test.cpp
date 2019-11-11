////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library ▸ Physics
/// @file           Library/Physics/Environment/Utilities/Eclipse.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Environment/Utilities/Eclipse.hpp>
#include <Library/Physics/Environment/Objects/CelestialBodies/Earth.hpp>
#include <Library/Physics/Environment.hpp>
#include <Library/Physics/Coordinate/Frame.hpp>
#include <Library/Physics/Coordinate/Position.hpp>
#include <Library/Physics/Time/DateTime.hpp>
#include <Library/Physics/Time/Interval.hpp>
#include <Library/Physics/Time/Duration.hpp>
#include <Library/Physics/Time/Instant.hpp>
#include <Library/Physics/Time/Scale.hpp>

#include <Library/Core/Containers/Table.hpp>
#include <Library/Core/Containers/Tuple.hpp>
#include <Library/Core/Types/String.hpp>
#include <Library/Core/Types/Shared.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Physics_Environment_Utilities_Eclipse, IsPositionInEclipse)
{

    using library::core::types::Shared ;
    using library::core::types::String ;
    using library::core::ctnr::Array ;
    using library::core::ctnr::Table ;
    using library::core::fs::Path ;
    using library::core::fs::File ;

    using library::physics::time::Scale ;
    using library::physics::time::Instant ;
    using library::physics::time::Duration ;
    using library::physics::time::Interval ;
    using library::physics::time::DateTime ;
    using library::physics::coord::Position ;
    using library::physics::coord::Frame ;
    using library::physics::Environment ;
    using library::physics::env::utilities::isPositionInEclipse ;

    {

        const Position position_ITRF = Position::Meters({ 7000e3, 0.0, 0.0 }, Frame::ITRF()) ;

        Environment environment = Environment::Default() ;

        {

            const Instant instant = Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::UTC) ;

            environment.setInstant(instant) ;

            const Position position_GCRF = position_ITRF.inFrame(Frame::GCRF(), instant) ;

            EXPECT_TRUE(isPositionInEclipse(position_GCRF, environment)) ;

        }

        {

            const Instant instant = Instant::DateTime(DateTime(2018, 1, 1, 12, 0, 0), Scale::UTC) ;

            environment.setInstant(instant) ;

            const Position position_GCRF = position_ITRF.inFrame(Frame::GCRF(), instant) ;

            EXPECT_FALSE(isPositionInEclipse(position_GCRF, environment)) ;

        }

        {

            const Instant instant = Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::UTC) ;

            environment.setInstant(instant) ;

            const Position position_GCRF = position_ITRF.inFrame(Frame::GCRF(), instant) ;

            EXPECT_TRUE(isPositionInEclipse(position_GCRF, environment)) ;

        }

    }

}

TEST (Library_Physics_Environment_Utilities_Eclipse, EclipseIntervalsAtPosition)
{

    using library::core::types::Index ;
    using library::core::types::String ;
    using library::core::ctnr::Tuple ;
    using library::core::ctnr::Array ;
    using library::core::ctnr::Table ;
    using library::core::fs::Path ;
    using library::core::fs::File ;

    using library::physics::time::Scale ;
    using library::physics::time::Instant ;
    using library::physics::time::Duration ;
    using library::physics::time::Interval ;
    using library::physics::time::DateTime ;
    using library::physics::units::Length ;
    using library::physics::units::Angle ;
    using library::physics::coord::Position ;
    using library::physics::coord::Frame ;
    using library::physics::coord::spherical::LLA ;
    using library::physics::Environment ;
    using library::physics::env::obj::celest::Earth ;
    using library::physics::env::utilities::eclipseIntervalsAtPosition ;

    {

        const Array<Tuple<Interval, LLA, File, Duration>> referenceScenarios =
        {
            {
                Interval::Closed(Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::UTC),
                Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::UTC)),
                LLA(Angle::Degrees(0.0), Angle::Degrees(0.0), Length::Meters(10.0)), // [TBM] Should be 0 [m]
                File::Path(Path::Parse("/app/test/Library/Physics/Environment/Utilities/Eclipse/EclipseIntervalsAtPosition/Target_1 Eclipse.csv")),
                Duration::Minutes(2.0) // [TBM] Should improve precision
            },
            {
                Interval::Closed(Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::UTC),
                Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::UTC)),
                LLA(Angle::Degrees(0.0), Angle::Degrees(0.0), Length::Kilometers(500.0)),
                File::Path(Path::Parse("/app/test/Library/Physics/Environment/Utilities/Eclipse/EclipseIntervalsAtPosition/Target_2 Eclipse.csv")),
                Duration::Minutes(2.0) // [TBM] Should improve precision
            },
            {
                Interval::Closed(Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::UTC),
                Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::UTC)),
                LLA(Angle::Degrees(+90.0), Angle::Degrees(0.0), Length::Meters(10.0)), // [TBM] Should be 0 [m]
                File::Path(Path::Parse("/app/test/Library/Physics/Environment/Utilities/Eclipse/EclipseIntervalsAtPosition/Target_3 Eclipse.csv")),
                Duration::Minutes(2.0) // [TBM] Should improve precision
            },
            {
                Interval::Closed(Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::UTC),
                Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::UTC)),
                LLA(Angle::Degrees(-90.0), Angle::Degrees(0.0), Length::Meters(10.0)), // [TBM] Should be 0 [m]
                File::Path(Path::Parse("/app/test/Library/Physics/Environment/Utilities/Eclipse/EclipseIntervalsAtPosition/Target_4 Eclipse.csv")),
                Duration::Minutes(2.0) // [TBM] Should improve precision
            },
            {
                Interval::Closed(Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::UTC),
                Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::UTC)),
                LLA(Angle::Degrees(0.0), Angle::Degrees(0.0), Length::Kilometers(5000.0)),
                File::Path(Path::Parse("/app/test/Library/Physics/Environment/Utilities/Eclipse/EclipseIntervalsAtPosition/Target_5 Eclipse.csv")),
                Duration::Minutes(2.0) // [TBM] Should improve precision
            }
        } ;

        for (const auto& referenceScenario : referenceScenarios)
        {

            const Interval analysisInterval = std::get<0>(referenceScenario) ;
            const LLA lla = std::get<1>(referenceScenario) ;
            const File referenceDataFile = std::get<2>(referenceScenario) ;
            const Duration durationTolerance = std::get<3>(referenceScenario) ;

            const Position position_ITRF = Position::Meters(lla.toCartesian(Earth::EquatorialRadius, Earth::Flattening), Frame::ITRF()) ;
            const Environment environment = Environment::Default() ;

            const Array<Interval> eclipseIntervals = eclipseIntervalsAtPosition(analysisInterval, position_ITRF, environment) ;

            const Table referenceData = Table::Load(referenceDataFile, Table::Format::CSV, true) ;

            Index eclipseIntervalIndex = 0 ;

            for (const auto& referenceDataRow : referenceData)
            {

                const Instant startInstant_reference = Instant::DateTime(DateTime::Parse(referenceDataRow["Start Time (UTCG)"].accessString()), Scale::UTC) ;
                const Instant endInstant_reference = Instant::DateTime(DateTime::Parse(referenceDataRow["Stop Time (UTCG)"].accessString()), Scale::UTC) ;
                const String currentCondition = referenceDataRow["Current Condition"].accessString() ;

                if (currentCondition == "Umbra")
                {

                    const Interval& eclipseInterval = eclipseIntervals.at(eclipseIntervalIndex) ;

                    EXPECT_TRUE(eclipseInterval.getStart().isNear(startInstant_reference, durationTolerance)) << String::Format("{} ~ {}", eclipseInterval.getStart().toString(), startInstant_reference.toString()) ;
                    EXPECT_TRUE(eclipseInterval.getEnd().isNear(endInstant_reference, durationTolerance)) << String::Format("{} ~ {}", eclipseInterval.getEnd().toString(), endInstant_reference.toString()) ;

                    eclipseIntervalIndex++ ;

                }

            }

        }

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
