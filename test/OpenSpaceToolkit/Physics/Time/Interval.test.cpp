/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Time/Interval.hpp>

#include <Global.test.hpp>

TEST(OpenSpaceToolkit_Physics_Time_Interval, Constructor)
{
    using ostk::physics::time::DateTime;
    using ostk::physics::time::Instant;
    using ostk::physics::time::Interval;
    using ostk::physics::time::Scale;

    {
        EXPECT_NO_THROW(Interval(
            Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT),
            Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT),
            Interval::Type::Closed
        ));
        EXPECT_NO_THROW(Interval(
            Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT),
            Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT),
            Interval::Type::Open
        ));
        EXPECT_NO_THROW(Interval(
            Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT),
            Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT),
            Interval::Type::HalfOpenLeft
        ));
        EXPECT_NO_THROW(Interval(
            Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT),
            Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT),
            Interval::Type::HalfOpenRight
        ));

        EXPECT_NO_THROW(Interval(
            Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT),
            Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::TT),
            Interval::Type::Closed
        ));
        EXPECT_NO_THROW(Interval(
            Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT),
            Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::TT),
            Interval::Type::Open
        ));
        EXPECT_NO_THROW(Interval(
            Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT),
            Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::TT),
            Interval::Type::HalfOpenLeft
        ));
        EXPECT_NO_THROW(Interval(
            Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT),
            Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::TT),
            Interval::Type::HalfOpenRight
        ));
    }

    {
        EXPECT_NO_THROW(Interval(
            Instant::Undefined(), Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT), Interval::Type::Closed
        ));
        EXPECT_NO_THROW(Interval(
            Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT), Instant::Undefined(), Interval::Type::Closed
        ));
        EXPECT_NO_THROW(Interval(
            Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT),
            Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::TT),
            Interval::Type::Undefined
        ));
    }

    {
        EXPECT_ANY_THROW(Interval(
            Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::TT),
            Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT),
            Interval::Type::Closed
        ));
    }
}

TEST(OpenSpaceToolkit_Physics_Time_Interval, StreamOperator)
{
    using ostk::physics::time::DateTime;
    using ostk::physics::time::Instant;
    using ostk::physics::time::Interval;
    using ostk::physics::time::Scale;

    {
        testing::internal::CaptureStdout();

        EXPECT_NO_THROW(
            std::cout << Interval(
                             Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT),
                             Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT),
                             Interval::Type::Closed
                         )
                      << std::endl
        );

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    }
}

TEST(OpenSpaceToolkit_Physics_Time_Interval, IsDefined)
{
    using ostk::physics::time::DateTime;
    using ostk::physics::time::Instant;
    using ostk::physics::time::Interval;
    using ostk::physics::time::Scale;

    {
        EXPECT_TRUE(Interval(
                        Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT),
                        Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT),
                        Interval::Type::Closed
        )
                        .isDefined());
        EXPECT_TRUE(Interval(
                        Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT),
                        Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::TT),
                        Interval::Type::Open
        )
                        .isDefined());
        EXPECT_TRUE(Interval(
                        Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT),
                        Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT),
                        Interval::Type::HalfOpenLeft
        )
                        .isDefined());
        EXPECT_TRUE(Interval(
                        Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT),
                        Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT),
                        Interval::Type::HalfOpenRight
        )
                        .isDefined());
    }

    {
        EXPECT_FALSE(Interval::Undefined().isDefined());

        EXPECT_FALSE(Interval(
                         Instant::Undefined(),
                         Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT),
                         Interval::Type::Closed
        )
                         .isDefined());
        EXPECT_FALSE(Interval(
                         Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT),
                         Instant::Undefined(),
                         Interval::Type::Closed
        )
                         .isDefined());
        EXPECT_FALSE(Interval(
                         Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT),
                         Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT),
                         Interval::Type::Undefined
        )
                         .isDefined());
    }
}

TEST(OpenSpaceToolkit_Physics_Time_Interval, AccessStart)
{
    using ostk::physics::time::DateTime;
    using ostk::physics::time::Instant;
    using ostk::physics::time::Interval;
    using ostk::physics::time::Scale;

    {
        const Instant startInstant = Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT);
        const Instant endInstant = Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::TT);

        EXPECT_EQ(startInstant, Interval(startInstant, endInstant, Interval::Type::Closed).accessStart());
        EXPECT_EQ(startInstant, Interval(startInstant, endInstant, Interval::Type::Open).accessStart());
        EXPECT_EQ(startInstant, Interval(startInstant, endInstant, Interval::Type::HalfOpenLeft).accessStart());
        EXPECT_EQ(startInstant, Interval(startInstant, endInstant, Interval::Type::HalfOpenRight).accessStart());
    }

    {
        EXPECT_ANY_THROW(Interval::Undefined().accessStart());
    }
}

TEST(OpenSpaceToolkit_Physics_Time_Interval, AccessEnd)
{
    using ostk::physics::time::DateTime;
    using ostk::physics::time::Instant;
    using ostk::physics::time::Interval;
    using ostk::physics::time::Scale;

    {
        const Instant startInstant = Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT);
        const Instant endInstant = Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::TT);

        EXPECT_EQ(endInstant, Interval(startInstant, endInstant, Interval::Type::Closed).accessEnd());
        EXPECT_EQ(endInstant, Interval(startInstant, endInstant, Interval::Type::Open).accessEnd());
        EXPECT_EQ(endInstant, Interval(startInstant, endInstant, Interval::Type::HalfOpenLeft).accessEnd());
        EXPECT_EQ(endInstant, Interval(startInstant, endInstant, Interval::Type::HalfOpenRight).accessEnd());
    }

    {
        EXPECT_ANY_THROW(Interval::Undefined().accessEnd());
    }
}

TEST(OpenSpaceToolkit_Physics_Time_Interval, GetStart)
{
    using ostk::physics::time::DateTime;
    using ostk::physics::time::Instant;
    using ostk::physics::time::Interval;
    using ostk::physics::time::Scale;

    {
        const Instant startInstant = Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT);
        const Instant endInstant = Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::TT);

        EXPECT_EQ(startInstant, Interval(startInstant, endInstant, Interval::Type::Closed).getStart());
        EXPECT_EQ(startInstant, Interval(startInstant, endInstant, Interval::Type::Open).getStart());
        EXPECT_EQ(startInstant, Interval(startInstant, endInstant, Interval::Type::HalfOpenLeft).getStart());
        EXPECT_EQ(startInstant, Interval(startInstant, endInstant, Interval::Type::HalfOpenRight).getStart());
    }

    {
        EXPECT_ANY_THROW(Interval::Undefined().getStart());
    }
}

TEST(OpenSpaceToolkit_Physics_Time_Interval, GetEnd)
{
    using ostk::physics::time::DateTime;
    using ostk::physics::time::Instant;
    using ostk::physics::time::Interval;
    using ostk::physics::time::Scale;

    {
        const Instant startInstant = Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT);
        const Instant endInstant = Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::TT);

        EXPECT_EQ(endInstant, Interval(startInstant, endInstant, Interval::Type::Closed).getEnd());
        EXPECT_EQ(endInstant, Interval(startInstant, endInstant, Interval::Type::Open).getEnd());
        EXPECT_EQ(endInstant, Interval(startInstant, endInstant, Interval::Type::HalfOpenLeft).getEnd());
        EXPECT_EQ(endInstant, Interval(startInstant, endInstant, Interval::Type::HalfOpenRight).getEnd());
    }

    {
        EXPECT_ANY_THROW(Interval::Undefined().getEnd());
    }
}

TEST(OpenSpaceToolkit_Physics_Time_Interval, GetDuration)
{
    using ostk::physics::time::DateTime;
    using ostk::physics::time::Duration;
    using ostk::physics::time::Instant;
    using ostk::physics::time::Interval;
    using ostk::physics::time::Scale;

    {
        const Instant startInstant = Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT);
        const Instant endInstant = Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::TT);

        EXPECT_EQ(Duration::Days(1.0), Interval(startInstant, endInstant, Interval::Type::Closed).getDuration());
        EXPECT_EQ(Duration::Days(1.0), Interval(startInstant, endInstant, Interval::Type::Open).getDuration());
        EXPECT_EQ(Duration::Days(1.0), Interval(startInstant, endInstant, Interval::Type::HalfOpenLeft).getDuration());
        EXPECT_EQ(Duration::Days(1.0), Interval(startInstant, endInstant, Interval::Type::HalfOpenRight).getDuration());
    }

    {
        EXPECT_ANY_THROW(Interval::Undefined().getDuration());
    }
}

TEST(OpenSpaceToolkit_Physics_Time_Interval, GetCenter)
{
    using ostk::physics::time::DateTime;
    using ostk::physics::time::Instant;
    using ostk::physics::time::Interval;
    using ostk::physics::time::Scale;

    {
        const Instant startInstant = Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT);
        const Instant endInstant = Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::TT);

        EXPECT_EQ(
            Instant::DateTime(DateTime(2018, 1, 1, 12, 0, 0), Scale::TT),
            Interval(startInstant, endInstant, Interval::Type::Closed).getCenter()
        );
        EXPECT_EQ(
            Instant::DateTime(DateTime(2018, 1, 1, 12, 0, 0), Scale::TT),
            Interval(startInstant, endInstant, Interval::Type::Open).getCenter()
        );
        EXPECT_EQ(
            Instant::DateTime(DateTime(2018, 1, 1, 12, 0, 0), Scale::TT),
            Interval(startInstant, endInstant, Interval::Type::HalfOpenLeft).getCenter()
        );
        EXPECT_EQ(
            Instant::DateTime(DateTime(2018, 1, 1, 12, 0, 0), Scale::TT),
            Interval(startInstant, endInstant, Interval::Type::HalfOpenRight).getCenter()
        );
    }

    {
        EXPECT_ANY_THROW(Interval::Undefined().getCenter());
    }
}

TEST(OpenSpaceToolkit_Physics_Time_Interval, ToString)
{
    using ostk::physics::time::DateTime;
    using ostk::physics::time::Instant;
    using ostk::physics::time::Interval;
    using ostk::physics::time::Scale;

    {
        const Instant startInstant = Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT);
        const Instant endInstant = Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::TT);

        EXPECT_EQ(
            "[2018-01-01 00:00:00 - 2018-01-02 00:00:00] [TT]",
            Interval(startInstant, endInstant, Interval::Type::Closed).toString(Scale::TT)
        );
        EXPECT_EQ(
            "]2018-01-01 00:00:00 - 2018-01-02 00:00:00[ [TT]",
            Interval(startInstant, endInstant, Interval::Type::Open).toString(Scale::TT)
        );
        EXPECT_EQ(
            "]2018-01-01 00:00:00 - 2018-01-02 00:00:00] [TT]",
            Interval(startInstant, endInstant, Interval::Type::HalfOpenLeft).toString(Scale::TT)
        );
        EXPECT_EQ(
            "[2018-01-01 00:00:00 - 2018-01-02 00:00:00[ [TT]",
            Interval(startInstant, endInstant, Interval::Type::HalfOpenRight).toString(Scale::TT)
        );
    }

    {
        EXPECT_EQ("Undefined", Interval::Undefined().toString(Scale::TT));
    }
}

TEST(OpenSpaceToolkit_Physics_Time_Interval, GenerateGrid)
{
    using ostk::core::container::Array;
    using ostk::physics::time::DateTime;
    using ostk::physics::time::Duration;
    using ostk::physics::time::Instant;
    using ostk::physics::time::Interval;
    using ostk::physics::time::Scale;

    // Positive step

    {
        const Interval interval = {
            Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT),
            Instant::DateTime(DateTime(2018, 1, 1, 0, 1, 0), Scale::TT),
            Interval::Type::Closed
        };
        const Duration step = Duration::Minutes(0.5);

        const Array<Instant> grid = interval.generateGrid(step);

        EXPECT_EQ(
            Array<Instant>(
                {Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT),
                 Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 30), Scale::TT),
                 Instant::DateTime(DateTime(2018, 1, 1, 0, 1, 0), Scale::TT)}
            ),
            grid
        );
    }

    {
        const Interval interval = {
            Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT),
            Instant::DateTime(DateTime(2018, 1, 1, 0, 1, 0), Scale::TT),
            Interval::Type::Closed
        };
        const Duration step = Duration::Minutes(1.0);

        const Array<Instant> grid = interval.generateGrid(step);

        EXPECT_EQ(
            Array<Instant>(
                {Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT),
                 Instant::DateTime(DateTime(2018, 1, 1, 0, 1, 0), Scale::TT)}
            ),
            grid
        );
    }

    {
        const Interval interval = {
            Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT),
            Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT),
            Interval::Type::Closed
        };
        const Duration step = Duration::Minutes(0.5);

        const Array<Instant> grid = interval.generateGrid(step);

        EXPECT_EQ(Array<Instant>({Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT)}), grid);
    }

    {
        const Interval interval = {
            Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT),
            Instant::DateTime(DateTime(2018, 1, 1, 0, 1, 0), Scale::TT),
            Interval::Type::Closed
        };
        const Duration step = Duration::Minutes(2.0);

        const Array<Instant> grid = interval.generateGrid(step);

        EXPECT_EQ(
            Array<Instant>(
                {Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT),
                 Instant::DateTime(DateTime(2018, 1, 1, 0, 1, 0), Scale::TT)}
            ),
            grid
        );
    }

    {
        const Interval interval = {
            Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT),
            Instant::DateTime(DateTime(2018, 1, 1, 0, 1, 0), Scale::TT),
            Interval::Type::Closed
        };
        const Duration step = Duration::Minutes(0.6);

        const Array<Instant> grid = interval.generateGrid(step);

        EXPECT_EQ(
            Array<Instant>(
                {Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT),
                 Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 36), Scale::TT),
                 Instant::DateTime(DateTime(2018, 1, 1, 0, 1, 0), Scale::TT)}
            ),
            grid
        );
    }

    // Negative step

    {
        const Interval interval = {
            Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT),
            Instant::DateTime(DateTime(2018, 1, 1, 0, 1, 0), Scale::TT),
            Interval::Type::Closed
        };
        const Duration step = Duration::Minutes(-0.5);

        const Array<Instant> grid = interval.generateGrid(step);

        EXPECT_EQ(
            Array<Instant>(
                {Instant::DateTime(DateTime(2018, 1, 1, 0, 1, 0), Scale::TT),
                 Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 30), Scale::TT),
                 Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT)}
            ),
            grid
        );
    }

    {
        const Interval interval = {
            Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT),
            Instant::DateTime(DateTime(2018, 1, 1, 0, 1, 0), Scale::TT),
            Interval::Type::Closed
        };
        const Duration step = Duration::Minutes(-1.0);

        const Array<Instant> grid = interval.generateGrid(step);

        EXPECT_EQ(
            Array<Instant>(
                {Instant::DateTime(DateTime(2018, 1, 1, 0, 1, 0), Scale::TT),
                 Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT)}
            ),
            grid
        );
    }

    {
        const Interval interval = {
            Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT),
            Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT),
            Interval::Type::Closed
        };
        const Duration step = Duration::Minutes(-0.5);

        const Array<Instant> grid = interval.generateGrid(step);

        EXPECT_EQ(Array<Instant>({Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT)}), grid);
    }

    {
        const Interval interval = {
            Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT),
            Instant::DateTime(DateTime(2018, 1, 1, 0, 1, 0), Scale::TT),
            Interval::Type::Closed
        };
        const Duration step = Duration::Minutes(-2.0);

        const Array<Instant> grid = interval.generateGrid(step);

        EXPECT_EQ(
            Array<Instant>(
                {Instant::DateTime(DateTime(2018, 1, 1, 0, 1, 0), Scale::TT),
                 Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT)}
            ),
            grid
        );
    }

    {
        const Interval interval = {
            Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT),
            Instant::DateTime(DateTime(2018, 1, 1, 0, 1, 0), Scale::TT),
            Interval::Type::Closed
        };
        const Duration step = Duration::Minutes(-0.6);

        const Array<Instant> grid = interval.generateGrid(step);

        EXPECT_EQ(
            Array<Instant>(
                {Instant::DateTime(DateTime(2018, 1, 1, 0, 1, 0), Scale::TT),
                 Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 24), Scale::TT),
                 Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT)}
            ),
            grid
        );
    }

    // Errors

    {
        EXPECT_ANY_THROW(Interval::Undefined().generateGrid(Duration::Seconds(1.0)));
        EXPECT_ANY_THROW(Interval(
                             Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::TT),
                             Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT),
                             Interval::Type::Closed
        )
                             .generateGrid(Duration::Undefined()));
    }

    {
        const Interval interval = {
            Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT),
            Instant::DateTime(DateTime(2018, 1, 1, 0, 1, 0), Scale::TT),
            Interval::Type::Closed
        };
        const Duration step = Duration::Minutes(0.0);

        EXPECT_ANY_THROW(interval.generateGrid(step));
    }
}

TEST(OpenSpaceToolkit_Physics_Time_Interval, Undefined)
{
    using ostk::physics::time::Interval;

    {
        EXPECT_NO_THROW(Interval::Undefined());

        EXPECT_FALSE(Interval::Undefined().isDefined());
    }
}

TEST(OpenSpaceToolkit_Physics_Time_Interval, Closed)
{
    using ostk::physics::time::DateTime;
    using ostk::physics::time::Duration;
    using ostk::physics::time::Instant;
    using ostk::physics::time::Interval;
    using ostk::physics::time::Scale;

    {
        EXPECT_NO_THROW(Interval::Closed(
            Instant::DateTime(DateTime(2018, 1, 1, 0, 1, 0), Scale::TT),
            Instant::DateTime(DateTime(2018, 1, 1, 0, 1, 1), Scale::TT)
        ));
        EXPECT_EQ(
            Interval(
                Instant::DateTime(DateTime(2018, 1, 1, 0, 1, 0), Scale::TT),
                Instant::DateTime(DateTime(2018, 1, 1, 0, 1, 1), Scale::TT),
                Interval::Type::Closed
            ),
            Interval::Closed(
                Instant::DateTime(DateTime(2018, 1, 1, 0, 1, 0), Scale::TT),
                Instant::DateTime(DateTime(2018, 1, 1, 0, 1, 1), Scale::TT)
            )
        );
    }

    {
        EXPECT_ANY_THROW(Interval::Closed(Instant::Undefined(), Instant::Undefined()));
        EXPECT_ANY_THROW(Interval::Closed(Instant::J2000(), Instant::Undefined()));
        EXPECT_ANY_THROW(Interval::Closed(Instant::Undefined(), Instant::J2000()));
    }
}

TEST(OpenSpaceToolkit_Physics_Time_Interval, Centered)
{
    using ostk::physics::time::DateTime;
    using ostk::physics::time::Duration;
    using ostk::physics::time::Instant;
    using ostk::physics::time::Interval;
    using ostk::physics::time::Scale;

    {
        EXPECT_NO_THROW(Interval::Centered(
            Instant::DateTime(DateTime(2018, 1, 1, 0, 1, 0), Scale::TT), Duration::Minutes(2.0), Interval::Type::Closed
        ));
        EXPECT_NO_THROW(Interval::Centered(
            Instant::DateTime(DateTime(2018, 1, 1, 0, 1, 0), Scale::TT), Duration::Minutes(2.0), Interval::Type::Open
        ));
        EXPECT_NO_THROW(Interval::Centered(
            Instant::DateTime(DateTime(2018, 1, 1, 0, 1, 0), Scale::TT),
            Duration::Minutes(2.0),
            Interval::Type::HalfOpenLeft
        ));
        EXPECT_NO_THROW(Interval::Centered(
            Instant::DateTime(DateTime(2018, 1, 1, 0, 1, 0), Scale::TT),
            Duration::Minutes(2.0),
            Interval::Type::HalfOpenRight
        ));

        EXPECT_EQ(
            Interval(
                Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT),
                Instant::DateTime(DateTime(2018, 1, 1, 0, 2, 0), Scale::TT),
                Interval::Type::Closed
            ),
            Interval::Centered(
                Instant::DateTime(DateTime(2018, 1, 1, 0, 1, 0), Scale::TT),
                Duration::Minutes(2.0),
                Interval::Type::Closed
            )
        );
        EXPECT_EQ(
            Interval(
                Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT),
                Instant::DateTime(DateTime(2018, 1, 1, 0, 2, 0), Scale::TT),
                Interval::Type::Open
            ),
            Interval::Centered(
                Instant::DateTime(DateTime(2018, 1, 1, 0, 1, 0), Scale::TT),
                Duration::Minutes(2.0),
                Interval::Type::Open
            )
        );
        EXPECT_EQ(
            Interval(
                Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT),
                Instant::DateTime(DateTime(2018, 1, 1, 0, 2, 0), Scale::TT),
                Interval::Type::HalfOpenLeft
            ),
            Interval::Centered(
                Instant::DateTime(DateTime(2018, 1, 1, 0, 1, 0), Scale::TT),
                Duration::Minutes(2.0),
                Interval::Type::HalfOpenLeft
            )
        );
        EXPECT_EQ(
            Interval(
                Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT),
                Instant::DateTime(DateTime(2018, 1, 1, 0, 2, 0), Scale::TT),
                Interval::Type::HalfOpenRight
            ),
            Interval::Centered(
                Instant::DateTime(DateTime(2018, 1, 1, 0, 1, 0), Scale::TT),
                Duration::Minutes(2.0),
                Interval::Type::HalfOpenRight
            )
        );
    }

    {
        EXPECT_ANY_THROW(Interval::Centered(Instant::Undefined(), Duration::Minutes(1.0), Interval::Type::Closed));
        EXPECT_ANY_THROW(Interval::Centered(Instant::J2000(), Duration::Undefined(), Interval::Type::Closed));
        EXPECT_ANY_THROW(Interval::Centered(Instant::J2000(), Duration::Minutes(1.0), Interval::Type::Undefined));
    }
}

TEST(OpenSpaceToolkit_Physics_Time_Interval, Parse)
{
    using ostk::physics::time::DateTime;
    using ostk::physics::time::Instant;
    using ostk::physics::time::Interval;
    using ostk::physics::time::Scale;

    {
        EXPECT_NO_THROW(Interval::Parse("[2018-01-01 00:00:00 - 2018-01-02 00:00:00] [TT]"));
        EXPECT_NO_THROW(Interval::Parse("]2018-01-01 00:00:00 - 2018-01-02 00:00:00[ [TT]"));
        EXPECT_NO_THROW(Interval::Parse("]2018-01-01 00:00:00 - 2018-01-02 00:00:00] [TT]"));
        EXPECT_NO_THROW(Interval::Parse("[2018-01-01 00:00:00 - 2018-01-02 00:00:00[ [TT]"));

        EXPECT_EQ(
            Interval(
                Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT),
                Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::TT),
                Interval::Type::Closed
            ),
            Interval::Parse("[2018-01-01 00:00:00 - 2018-01-02 00:00:00] [TT]")
        );
        EXPECT_EQ(
            Interval(
                Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT),
                Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::TT),
                Interval::Type::Open
            ),
            Interval::Parse("]2018-01-01 00:00:00 - 2018-01-02 00:00:00[ [TT]")
        );
        EXPECT_EQ(
            Interval(
                Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT),
                Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::TT),
                Interval::Type::HalfOpenLeft
            ),
            Interval::Parse("]2018-01-01 00:00:00 - 2018-01-02 00:00:00] [TT]")
        );
        EXPECT_EQ(
            Interval(
                Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT),
                Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::TT),
                Interval::Type::HalfOpenRight
            ),
            Interval::Parse("[2018-01-01 00:00:00 - 2018-01-02 00:00:00[ [TT]")
        );
    }

    {
        EXPECT_ANY_THROW(Interval::Parse(""));
        EXPECT_ANY_THROW(Interval::Parse("abc"));
        EXPECT_ANY_THROW(Interval::Parse("[]"));
        EXPECT_ANY_THROW(Interval::Parse("[2018-01-01 00:00:00 - 2018-01-01 00:00:00]"));
        EXPECT_ANY_THROW(Interval::Parse("/2018-01-01 00:00:00 - 2018-01-01 00:00:00/ [TT]"));
        EXPECT_ANY_THROW(Interval::Parse("[2018-01-01 00:00:00 - 2018-01-01 00:00:00] []"));
    }
}
