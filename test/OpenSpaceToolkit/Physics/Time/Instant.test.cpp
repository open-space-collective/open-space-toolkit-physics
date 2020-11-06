////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           OpenSpaceToolkit/Physics/Time/Instant.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Core/Containers/Array.hpp>
#include <OpenSpaceToolkit/Core/Types/Integer.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using ostk::core::types::Uint8 ;
using ostk::core::types::Uint16 ;
using ostk::core::ctnr::Array ;
using ostk::physics::time::Scale ;

static const Array<Uint16> years = { 1981, 2000, 2030 } ;
static const Array<Uint8> months = { 1, 6, 12 } ;
static const Array<Uint8> days = { 1, 20, 28 } ;

static const Array<Uint8> hours = { 0, 12, 23} ;
static const Array<Uint8> minutes = { 0, 30, 59} ;
static const Array<Uint8> seconds = { 0, 30, 59 } ;

static const Array<Uint16> milliseconds = { 0, 500, 999 } ;
static const Array<Uint16> microseconds = { 0, 500, 999 } ;
static const Array<Uint16> nanoseconds = { 0, 500, 999 } ;

static const Array<Scale> scales = { Scale::TT, Scale::TAI, Scale::UTC, Scale::GPST } ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (OpenSpaceToolkit_Physics_Time_Instant, EqualToOperator)
{

    using ostk::physics::time::Scale ;
    using ostk::physics::time::DateTime ;
    using ostk::physics::time::Instant ;

    {

        for (const auto year : years)
        {

            for (const auto month : months)
            {

                for (const auto day : days)
                {

                    for (const auto hour : hours)
                    {

                        for (const auto minute : minutes)
                        {

                            for (const auto second : seconds)
                            {

                                for (const auto millisecond : milliseconds)
                                {

                                    for (const auto microsecond : microseconds)
                                    {

                                        for (const auto nanosecond : nanoseconds)
                                        {

                                            for (const auto scale : scales)
                                            {

                                                const DateTime dateTime = { year, month, day, hour, minute, second, millisecond, microsecond, nanosecond } ;

                                                EXPECT_TRUE(Instant::DateTime(dateTime, scale) == Instant::DateTime(dateTime, scale)) ;

                                            }

                                        }

                                    }

                                }

                            }

                        }

                    }

                }

            }

        }

    }

    {

        for (const auto year : years)
        {

            for (const auto month : months)
            {

                for (const auto day : days)
                {

                    for (const auto hour : hours)
                    {

                        for (const auto minute : minutes)
                        {

                            for (const auto second : seconds)
                            {

                                for (const auto millisecond : milliseconds)
                                {

                                    for (const auto microsecond : microseconds)
                                    {

                                        for (const auto nanosecond : nanoseconds)
                                        {

                                            for (const auto scale : scales)
                                            {

                                                const DateTime dateTime = { year, month, day, hour, minute, second, millisecond, microsecond, nanosecond } ;

                                                if (nanosecond != 1)
                                                {
                                                    EXPECT_FALSE(Instant::DateTime(dateTime, scale) == Instant::DateTime(DateTime(year, month, day, hour, minute, second, millisecond, microsecond, 1), scale)) ;
                                                }

                                                if (scale != Scale::UTC)
                                                {

                                                    if ((scale == Scale::GPST) && (dateTime.accessDate().getYear() == 1981)) // Because GPST == UTC @ 1981
                                                    {
                                                        continue ;
                                                    }

                                                    EXPECT_FALSE(Instant::DateTime(dateTime, scale) == Instant::DateTime(dateTime, Scale::UTC)) ;

                                                }

                                            }

                                        }

                                    }

                                }

                            }

                        }

                    }

                }

            }

        }

    }

    {

        EXPECT_FALSE(Instant::Undefined() == Instant::Undefined()) ;

        for (const auto year : years)
        {

            for (const auto month : months)
            {

                for (const auto day : days)
                {

                    for (const auto hour : hours)
                    {

                        for (const auto minute : minutes)
                        {

                            for (const auto second : seconds)
                            {

                                for (const auto millisecond : milliseconds)
                                {

                                    for (const auto microsecond : microseconds)
                                    {

                                        for (const auto nanosecond : nanoseconds)
                                        {

                                            for (const auto scale : scales)
                                            {

                                                const DateTime dateTime = { year, month, day, hour, minute, second, millisecond, microsecond, nanosecond } ;

                                                EXPECT_FALSE(Instant::DateTime(dateTime, scale) == Instant::Undefined()) ;
                                                EXPECT_FALSE(Instant::Undefined() == Instant::DateTime(dateTime, scale)) ;

                                            }

                                        }

                                    }

                                }

                            }

                        }

                    }

                }

            }

        }

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Instant, NotEqualToOperator)
{

    using ostk::physics::time::Scale ;
    using ostk::physics::time::DateTime ;
    using ostk::physics::time::Instant ;

    {

        for (const auto year : years)
        {

            for (const auto month : months)
            {

                for (const auto day : days)
                {

                    for (const auto hour : hours)
                    {

                        for (const auto minute : minutes)
                        {

                            for (const auto second : seconds)
                            {

                                for (const auto millisecond : milliseconds)
                                {

                                    for (const auto microsecond : microseconds)
                                    {

                                        for (const auto nanosecond : nanoseconds)
                                        {

                                            for (const auto scale : scales)
                                            {

                                                const DateTime dateTime = { year, month, day, hour, minute, second, millisecond, microsecond, nanosecond } ;

                                                if (nanosecond != 1)
                                                {
                                                    EXPECT_TRUE(Instant::DateTime(dateTime, scale) != Instant::DateTime(DateTime(year, month, day, hour, minute, second, millisecond, microsecond, 1), scale)) ;
                                                }

                                                if (scale != Scale::UTC)
                                                {

                                                    if ((scale == Scale::GPST) && (dateTime.accessDate().getYear() == 1981)) // Because GPST == UTC @ 1981
                                                    {
                                                        continue ;
                                                    }

                                                    EXPECT_TRUE(Instant::DateTime(dateTime, scale) != Instant::DateTime(dateTime, Scale::UTC)) ;

                                                }

                                            }

                                        }

                                    }

                                }

                            }

                        }

                    }

                }

            }

        }

    }

    {

        EXPECT_TRUE(Instant::Undefined() != Instant::Undefined()) ;

        for (const auto year : years)
        {

            for (const auto month : months)
            {

                for (const auto day : days)
                {

                    for (const auto hour : hours)
                    {

                        for (const auto minute : minutes)
                        {

                            for (const auto second : seconds)
                            {

                                for (const auto millisecond : milliseconds)
                                {

                                    for (const auto microsecond : microseconds)
                                    {

                                        for (const auto nanosecond : nanoseconds)
                                        {

                                            for (const auto scale : scales)
                                            {

                                                const DateTime dateTime = { year, month, day, hour, minute, second, millisecond, microsecond, nanosecond } ;

                                                EXPECT_TRUE(Instant::DateTime(dateTime, scale) != Instant::Undefined()) ;
                                                EXPECT_TRUE(Instant::Undefined() != Instant::DateTime(dateTime, scale)) ;

                                            }

                                        }

                                    }

                                }

                            }

                        }

                    }

                }

            }

        }

    }

    {

        for (const auto year : years)
        {

            for (const auto month : months)
            {

                for (const auto day : days)
                {

                    for (const auto hour : hours)
                    {

                        for (const auto minute : minutes)
                        {

                            for (const auto second : seconds)
                            {

                                for (const auto millisecond : milliseconds)
                                {

                                    for (const auto microsecond : microseconds)
                                    {

                                        for (const auto nanosecond : nanoseconds)
                                        {

                                            for (const auto scale : scales)
                                            {

                                                const DateTime dateTime = { year, month, day, hour, minute, second, millisecond, microsecond, nanosecond } ;

                                                EXPECT_FALSE(Instant::DateTime(dateTime, scale) != Instant::DateTime(dateTime, scale)) ;

                                            }

                                        }

                                    }

                                }

                            }

                        }

                    }

                }

            }

        }

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Instant, LessThanOperator)
{

    using ostk::physics::time::Scale ;
    using ostk::physics::time::DateTime ;
    using ostk::physics::time::Instant ;

    {

        for (const auto scale : scales)
        {

            EXPECT_TRUE(Instant::DateTime(DateTime(2000, 1, 1, 12, 0, 0), scale) < Instant::DateTime(DateTime(2001, 1, 1, 12, 0, 0), scale)) ;
            EXPECT_TRUE(Instant::DateTime(DateTime(1999, 1, 1, 12, 0, 0), scale) < Instant::DateTime(DateTime(2000, 1, 1, 12, 0, 0), scale)) ;

        }

    }

    {

        for (const auto scale : scales)
        {

            EXPECT_FALSE(Instant::DateTime(DateTime(2000, 1, 1, 12, 0, 0), scale) < Instant::DateTime(DateTime(2000, 1, 1, 12, 0, 0), scale)) ;
            EXPECT_FALSE(Instant::DateTime(DateTime(2001, 1, 1, 12, 0, 0), scale) < Instant::DateTime(DateTime(2000, 1, 1, 12, 0, 0), scale)) ;
            EXPECT_FALSE(Instant::DateTime(DateTime(2001, 1, 1, 12, 0, 0), scale) < Instant::DateTime(DateTime(1999, 1, 1, 12, 0, 0), scale)) ;

        }

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Instant, LessThanOrEqualToOperator)
{

    using ostk::physics::time::Scale ;
    using ostk::physics::time::DateTime ;
    using ostk::physics::time::Instant ;

    {

        for (const auto scale : scales)
        {

            EXPECT_TRUE(Instant::DateTime(DateTime(2000, 1, 1, 12, 0, 0), scale) <= Instant::DateTime(DateTime(2000, 1, 1, 12, 0, 0), scale)) ;
            EXPECT_TRUE(Instant::DateTime(DateTime(2000, 1, 1, 12, 0, 0), scale) <= Instant::DateTime(DateTime(2001, 1, 1, 12, 0, 0), scale)) ;
            EXPECT_TRUE(Instant::DateTime(DateTime(1999, 1, 1, 12, 0, 0), scale) <= Instant::DateTime(DateTime(2000, 1, 1, 12, 0, 0), scale)) ;

        }

    }

    {

        for (const auto scale : scales)
        {

            EXPECT_FALSE(Instant::DateTime(DateTime(2001, 1, 1, 12, 0, 0), scale) <= Instant::DateTime(DateTime(2000, 1, 1, 12, 0, 0), scale)) ;
            EXPECT_FALSE(Instant::DateTime(DateTime(2001, 1, 1, 12, 0, 0), scale) <= Instant::DateTime(DateTime(1999, 1, 1, 12, 0, 0), scale)) ;

        }

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Instant, GreaterThanOperator)
{

    using ostk::physics::time::Scale ;
    using ostk::physics::time::DateTime ;
    using ostk::physics::time::Instant ;

    {

        for (const auto scale : scales)
        {

            EXPECT_TRUE(Instant::DateTime(DateTime(2001, 1, 1, 12, 0, 0), scale) > Instant::DateTime(DateTime(2000, 1, 1, 12, 0, 0), scale)) ;
            EXPECT_TRUE(Instant::DateTime(DateTime(2001, 1, 1, 12, 0, 0), scale) > Instant::DateTime(DateTime(1999, 1, 1, 12, 0, 0), scale)) ;

        }

    }

    {

        for (const auto scale : scales)
        {

            EXPECT_FALSE(Instant::DateTime(DateTime(2000, 1, 1, 12, 0, 0), scale) > Instant::DateTime(DateTime(2000, 1, 1, 12, 0, 0), scale)) ;
            EXPECT_FALSE(Instant::DateTime(DateTime(2000, 1, 1, 12, 0, 0), scale) > Instant::DateTime(DateTime(2001, 1, 1, 12, 0, 0), scale)) ;
            EXPECT_FALSE(Instant::DateTime(DateTime(1999, 1, 1, 12, 0, 0), scale) > Instant::DateTime(DateTime(2000, 1, 1, 12, 0, 0), scale)) ;

        }

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Instant, GreaterThanOrEqualToOperator)
{

    using ostk::physics::time::Scale ;
    using ostk::physics::time::DateTime ;
    using ostk::physics::time::Instant ;

    {

        for (const auto scale : scales)
        {

            EXPECT_TRUE(Instant::DateTime(DateTime(2000, 1, 1, 12, 0, 0), scale) >= Instant::DateTime(DateTime(2000, 1, 1, 12, 0, 0), scale)) ;
            EXPECT_TRUE(Instant::DateTime(DateTime(2001, 1, 1, 12, 0, 0), scale) >= Instant::DateTime(DateTime(2000, 1, 1, 12, 0, 0), scale)) ;
            EXPECT_TRUE(Instant::DateTime(DateTime(2001, 1, 1, 12, 0, 0), scale) >= Instant::DateTime(DateTime(1999, 1, 1, 12, 0, 0), scale)) ;

        }

    }

    {

        for (const auto scale : scales)
        {

            EXPECT_FALSE(Instant::DateTime(DateTime(2000, 1, 1, 12, 0, 0), scale) >= Instant::DateTime(DateTime(2001, 1, 1, 12, 0, 0), scale)) ;
            EXPECT_FALSE(Instant::DateTime(DateTime(1999, 1, 1, 12, 0, 0), scale) >= Instant::DateTime(DateTime(2000, 1, 1, 12, 0, 0), scale)) ;

        }

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Instant, AdditionOperator)
{

    using ostk::physics::time::Scale ;
    using ostk::physics::time::DateTime ;
    using ostk::physics::time::Instant ;
    using ostk::physics::time::Duration ;

    {

        for (const auto year : years)
        {

            for (const auto month : months)
            {

                for (const auto day : days)
                {

                    for (const auto scale : scales)
                    {

                        EXPECT_EQ(Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) + Duration::Zero()) ;

                        EXPECT_EQ(Instant::DateTime(DateTime(year, month, day, 11, 59, 59, 999, 999, 999), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) + Duration::Nanoseconds(-1)) ;
                        EXPECT_EQ(Instant::DateTime(DateTime(year, month, day, 12, 0, 0, 0, 0, 1), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) + Duration::Nanoseconds(+1)) ;

                        EXPECT_EQ(Instant::DateTime(DateTime(year, month, day, 11, 59, 59, 999, 999), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) + Duration::Microseconds(-1)) ;
                        EXPECT_EQ(Instant::DateTime(DateTime(year, month, day, 12, 0, 0, 0, 1), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) + Duration::Microseconds(+1)) ;

                        EXPECT_EQ(Instant::DateTime(DateTime(year, month, day, 11, 59, 59, 999), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) + Duration::Milliseconds(-1)) ;
                        EXPECT_EQ(Instant::DateTime(DateTime(year, month, day, 12, 0, 0, 1), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) + Duration::Milliseconds(+1)) ;

                        EXPECT_EQ(Instant::DateTime(DateTime(year, month, day, 11, 59, 59), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) + Duration::Seconds(-1)) ;
                        EXPECT_EQ(Instant::DateTime(DateTime(year, month, day, 12, 0, 1), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) + Duration::Seconds(+1)) ;

                        EXPECT_EQ(Instant::DateTime(DateTime(year, month, day, 11, 59, 0), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) + Duration::Minutes(-1)) ;
                        EXPECT_EQ(Instant::DateTime(DateTime(year, month, day, 12, 1, 0), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) + Duration::Minutes(+1)) ;

                        EXPECT_EQ(Instant::DateTime(DateTime(year, month, day, 11, 0, 0), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) + Duration::Hours(-1)) ;
                        EXPECT_EQ(Instant::DateTime(DateTime(year, month, day, 13, 0, 0), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) + Duration::Hours(+1)) ;

                    }

                }

            }

        }

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Instant, SubtractionOperator)
{

    using ostk::physics::time::Scale ;
    using ostk::physics::time::DateTime ;
    using ostk::physics::time::Instant ;
    using ostk::physics::time::Duration ;

    {

        for (const auto year : years)
        {

            for (const auto month : months)
            {

                for (const auto day : days)
                {

                    for (const auto scale : scales)
                    {

                        EXPECT_EQ(Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) - Duration::Zero()) ;

                        EXPECT_EQ(Instant::DateTime(DateTime(year, month, day, 11, 59, 59, 999, 999, 999), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) - Duration::Nanoseconds(+1)) ;
                        EXPECT_EQ(Instant::DateTime(DateTime(year, month, day, 12, 0, 0, 0, 0, 1), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) - Duration::Nanoseconds(-1)) ;

                        EXPECT_EQ(Instant::DateTime(DateTime(year, month, day, 11, 59, 59, 999, 999), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) - Duration::Microseconds(+1)) ;
                        EXPECT_EQ(Instant::DateTime(DateTime(year, month, day, 12, 0, 0, 0, 1), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) - Duration::Microseconds(-1)) ;

                        EXPECT_EQ(Instant::DateTime(DateTime(year, month, day, 11, 59, 59, 999), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) - Duration::Milliseconds(+1)) ;
                        EXPECT_EQ(Instant::DateTime(DateTime(year, month, day, 12, 0, 0, 1), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) - Duration::Milliseconds(-1)) ;

                        EXPECT_EQ(Instant::DateTime(DateTime(year, month, day, 11, 59, 59), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) - Duration::Seconds(+1)) ;
                        EXPECT_EQ(Instant::DateTime(DateTime(year, month, day, 12, 0, 1), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) - Duration::Seconds(-1)) ;

                        EXPECT_EQ(Instant::DateTime(DateTime(year, month, day, 11, 59, 0), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) - Duration::Minutes(+1)) ;
                        EXPECT_EQ(Instant::DateTime(DateTime(year, month, day, 12, 1, 0), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) - Duration::Minutes(-1)) ;

                        EXPECT_EQ(Instant::DateTime(DateTime(year, month, day, 11, 0, 0), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) - Duration::Hours(+1)) ;
                        EXPECT_EQ(Instant::DateTime(DateTime(year, month, day, 13, 0, 0), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) - Duration::Hours(-1)) ;

                    }

                }

            }

        }

    }

    {

        for (const auto year : years)
        {

            for (const auto month : months)
            {

                for (const auto day : days)
                {

                    for (const auto scale : scales)
                    {

                        EXPECT_EQ(Duration::Zero(), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) - Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale)) ;

                        EXPECT_EQ(Duration::Nanoseconds(+1), Instant::DateTime(DateTime(year, month, day, 12, 0, 0, 0, 0, 1), scale) - Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale)) ;
                        EXPECT_EQ(Duration::Nanoseconds(-1), Instant::DateTime(DateTime(year, month, day, 11, 59, 59, 999, 999, 999), scale) - Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale)) ;

                        EXPECT_EQ(Duration::Microseconds(+1), Instant::DateTime(DateTime(year, month, day, 12, 0, 0, 0, 1), scale) - Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale)) ;
                        EXPECT_EQ(Duration::Microseconds(-1), Instant::DateTime(DateTime(year, month, day, 11, 59, 59, 999, 999), scale) - Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale)) ;

                        EXPECT_EQ(Duration::Milliseconds(+1), Instant::DateTime(DateTime(year, month, day, 12, 0, 0, 1), scale) - Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale)) ;
                        EXPECT_EQ(Duration::Milliseconds(-1), Instant::DateTime(DateTime(year, month, day, 11, 59, 59, 999), scale) - Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale)) ;

                        EXPECT_EQ(Duration::Seconds(+1), Instant::DateTime(DateTime(year, month, day, 12, 0, 1), scale) - Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale)) ;
                        EXPECT_EQ(Duration::Seconds(-1), Instant::DateTime(DateTime(year, month, day, 11, 59, 59), scale) - Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale)) ;

                        EXPECT_EQ(Duration::Minutes(+1), Instant::DateTime(DateTime(year, month, day, 12, 1, 0), scale) - Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale)) ;
                        EXPECT_EQ(Duration::Minutes(-1), Instant::DateTime(DateTime(year, month, day, 11, 59, 0), scale) - Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale)) ;

                        EXPECT_EQ(Duration::Hours(+1), Instant::DateTime(DateTime(year, month, day, 13, 0, 0), scale) - Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale)) ;
                        EXPECT_EQ(Duration::Hours(-1), Instant::DateTime(DateTime(year, month, day, 11, 0, 0), scale) - Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale)) ;

                        EXPECT_EQ(Duration::Nanoseconds(-1), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) - Instant::DateTime(DateTime(year, month, day, 12, 0, 0, 0, 0, 1), scale)) ;
                        EXPECT_EQ(Duration::Nanoseconds(+1), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) - Instant::DateTime(DateTime(year, month, day, 11, 59, 59, 999, 999, 999), scale)) ;

                        EXPECT_EQ(Duration::Microseconds(-1), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) - Instant::DateTime(DateTime(year, month, day, 12, 0, 0, 0, 1), scale)) ;
                        EXPECT_EQ(Duration::Microseconds(+1), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) - Instant::DateTime(DateTime(year, month, day, 11, 59, 59, 999, 999), scale)) ;

                        EXPECT_EQ(Duration::Milliseconds(-1), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) - Instant::DateTime(DateTime(year, month, day, 12, 0, 0, 1), scale)) ;
                        EXPECT_EQ(Duration::Milliseconds(+1), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) - Instant::DateTime(DateTime(year, month, day, 11, 59, 59, 999), scale)) ;

                        EXPECT_EQ(Duration::Seconds(-1), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) - Instant::DateTime(DateTime(year, month, day, 12, 0, 1), scale)) ;
                        EXPECT_EQ(Duration::Seconds(+1), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) - Instant::DateTime(DateTime(year, month, day, 11, 59, 59), scale)) ;

                        EXPECT_EQ(Duration::Minutes(-1), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) - Instant::DateTime(DateTime(year, month, day, 12, 1, 0), scale)) ;
                        EXPECT_EQ(Duration::Minutes(+1), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) - Instant::DateTime(DateTime(year, month, day, 11, 59, 0), scale)) ;

                        EXPECT_EQ(Duration::Hours(-1), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) - Instant::DateTime(DateTime(year, month, day, 13, 0, 0), scale)) ;
                        EXPECT_EQ(Duration::Hours(+1), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) - Instant::DateTime(DateTime(year, month, day, 11, 0, 0), scale)) ;

                    }

                }

            }

        }

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Instant, AdditionAssignementOperator)
{

    using ostk::physics::time::Scale ;
    using ostk::physics::time::DateTime ;
    using ostk::physics::time::Instant ;
    using ostk::physics::time::Duration ;

    {

        for (const auto year : years)
        {

            for (const auto month : months)
            {

                for (const auto day : days)
                {

                    for (const auto scale : scales)
                    {

                        EXPECT_EQ(Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) += Duration::Zero()) ;

                        EXPECT_EQ(Instant::DateTime(DateTime(year, month, day, 11, 59, 59, 999, 999, 999), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) += Duration::Nanoseconds(-1)) ;
                        EXPECT_EQ(Instant::DateTime(DateTime(year, month, day, 12, 0, 0, 0, 0, 1), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) += Duration::Nanoseconds(+1)) ;

                        EXPECT_EQ(Instant::DateTime(DateTime(year, month, day, 11, 59, 59, 999, 999), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) += Duration::Microseconds(-1)) ;
                        EXPECT_EQ(Instant::DateTime(DateTime(year, month, day, 12, 0, 0, 0, 1), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) += Duration::Microseconds(+1)) ;

                        EXPECT_EQ(Instant::DateTime(DateTime(year, month, day, 11, 59, 59, 999), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) += Duration::Milliseconds(-1)) ;
                        EXPECT_EQ(Instant::DateTime(DateTime(year, month, day, 12, 0, 0, 1), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) += Duration::Milliseconds(+1)) ;

                        EXPECT_EQ(Instant::DateTime(DateTime(year, month, day, 11, 59, 59), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) += Duration::Seconds(-1)) ;
                        EXPECT_EQ(Instant::DateTime(DateTime(year, month, day, 12, 0, 1), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) += Duration::Seconds(+1)) ;

                        EXPECT_EQ(Instant::DateTime(DateTime(year, month, day, 11, 59, 0), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) += Duration::Minutes(-1)) ;
                        EXPECT_EQ(Instant::DateTime(DateTime(year, month, day, 12, 1, 0), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) += Duration::Minutes(+1)) ;

                        EXPECT_EQ(Instant::DateTime(DateTime(year, month, day, 11, 0, 0), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) += Duration::Hours(-1)) ;
                        EXPECT_EQ(Instant::DateTime(DateTime(year, month, day, 13, 0, 0), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) += Duration::Hours(+1)) ;

                    }

                }

            }

        }

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Instant, SubtractionAssignementOperator)
{

    using ostk::physics::time::Scale ;
    using ostk::physics::time::DateTime ;
    using ostk::physics::time::Instant ;
    using ostk::physics::time::Duration ;

    {

        for (const auto year : years)
        {

            for (const auto month : months)
            {

                for (const auto day : days)
                {

                    for (const auto scale : scales)
                    {

                        EXPECT_EQ(Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) -= Duration::Zero()) ;

                        EXPECT_EQ(Instant::DateTime(DateTime(year, month, day, 11, 59, 59, 999, 999, 999), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) -= Duration::Nanoseconds(+1)) ;
                        EXPECT_EQ(Instant::DateTime(DateTime(year, month, day, 12, 0, 0, 0, 0, 1), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) -= Duration::Nanoseconds(-1)) ;

                        EXPECT_EQ(Instant::DateTime(DateTime(year, month, day, 11, 59, 59, 999, 999), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) -= Duration::Microseconds(+1)) ;
                        EXPECT_EQ(Instant::DateTime(DateTime(year, month, day, 12, 0, 0, 0, 1), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) -= Duration::Microseconds(-1)) ;

                        EXPECT_EQ(Instant::DateTime(DateTime(year, month, day, 11, 59, 59, 999), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) -= Duration::Milliseconds(+1)) ;
                        EXPECT_EQ(Instant::DateTime(DateTime(year, month, day, 12, 0, 0, 1), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) -= Duration::Milliseconds(-1)) ;

                        EXPECT_EQ(Instant::DateTime(DateTime(year, month, day, 11, 59, 59), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) -= Duration::Seconds(+1)) ;
                        EXPECT_EQ(Instant::DateTime(DateTime(year, month, day, 12, 0, 1), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) -= Duration::Seconds(-1)) ;

                        EXPECT_EQ(Instant::DateTime(DateTime(year, month, day, 11, 59, 0), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) -= Duration::Minutes(+1)) ;
                        EXPECT_EQ(Instant::DateTime(DateTime(year, month, day, 12, 1, 0), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) -= Duration::Minutes(-1)) ;

                        EXPECT_EQ(Instant::DateTime(DateTime(year, month, day, 11, 0, 0), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) -= Duration::Hours(+1)) ;
                        EXPECT_EQ(Instant::DateTime(DateTime(year, month, day, 13, 0, 0), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale) -= Duration::Hours(-1)) ;

                    }

                }

            }

        }

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Instant, StreamOperator)
{

    using ostk::physics::time::Scale ;
    using ostk::physics::time::Instant ;

    {

        testing::internal::CaptureStdout() ;

        EXPECT_NO_THROW(std::cout << Instant::J2000() << std::endl) ;

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Instant, IsDefined)
{

    using ostk::physics::time::Scale ;
    using ostk::physics::time::DateTime ;
    using ostk::physics::time::Instant ;

    {

        for (auto const& scale : scales)
        {

            EXPECT_TRUE(Instant::DateTime(DateTime(2000, 1, 1, 12, 0, 0), scale).isDefined()) ;
            EXPECT_TRUE(Instant::DateTime(DateTime(2000, 1, 1, 12, 0, 0, 0, 0, 1), scale).isDefined()) ;
            EXPECT_TRUE(Instant::DateTime(DateTime(2000, 1, 1, 11, 59, 59, 999, 999, 999), scale).isDefined()) ;

        }

    }

    {

        EXPECT_FALSE(Instant::Undefined().isDefined()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Instant, IsPostEpoch)
{

    using ostk::physics::time::Scale ;
    using ostk::physics::time::DateTime ;
    using ostk::physics::time::Instant ;

    {

        EXPECT_TRUE(Instant::DateTime(DateTime(2000, 1, 1, 12, 0, 0), Scale::TT).isPostEpoch()) ;

        EXPECT_TRUE(Instant::DateTime(DateTime(2000, 1, 1, 12, 0, 0, 0, 0, 1), Scale::TT).isPostEpoch()) ;

        EXPECT_FALSE(Instant::DateTime(DateTime(2000, 1, 1, 11, 59, 59, 999, 999, 999), Scale::TT).isPostEpoch()) ;

    }

    {

        EXPECT_TRUE(Instant::J2000().isPostEpoch()) ;

    }

    {

        EXPECT_ANY_THROW(Instant::Undefined().isPostEpoch()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Instant, IsNear)
{

    using ostk::physics::time::Scale ;
    using ostk::physics::time::DateTime ;
    using ostk::physics::time::Instant ;
    using ostk::physics::time::Duration ;

    {

        EXPECT_TRUE(Instant::DateTime(DateTime(2000, 1, 1, 12, 0, 0), Scale::TT).isNear(Instant::DateTime(DateTime(2000, 1, 1, 12, 0, 0), Scale::TT), Duration::Seconds(0.0))) ;
        EXPECT_TRUE(Instant::DateTime(DateTime(2000, 1, 1, 12, 0, 1), Scale::TT).isNear(Instant::DateTime(DateTime(2000, 1, 1, 12, 0, 0), Scale::TT), Duration::Seconds(1.0))) ;
        EXPECT_TRUE(Instant::DateTime(DateTime(2000, 1, 1, 12, 0, 0), Scale::TT).isNear(Instant::DateTime(DateTime(2000, 1, 1, 12, 0, 1), Scale::TT), Duration::Seconds(1.0))) ;

    }

    {

        EXPECT_TRUE(Instant::J2000().isNear(Instant::J2000(), Duration::Zero())) ;
        EXPECT_TRUE(Instant::J2000().isNear(Instant::J2000(), Duration::Seconds(1.0))) ;

    }

    {

        EXPECT_FALSE(Instant::DateTime(DateTime(2000, 1, 1, 12, 0, 2), Scale::TT).isNear(Instant::DateTime(DateTime(2000, 1, 1, 12, 0, 0), Scale::TT), Duration::Seconds(1.0))) ;
        EXPECT_FALSE(Instant::DateTime(DateTime(2000, 1, 1, 12, 0, 0), Scale::TT).isNear(Instant::DateTime(DateTime(2000, 1, 1, 12, 0, 2), Scale::TT), Duration::Seconds(1.0))) ;

    }

    {

        EXPECT_ANY_THROW(Instant::Undefined().isNear(Instant::Undefined(), Duration::Undefined())) ;
        EXPECT_ANY_THROW(Instant::Undefined().isNear(Instant::J2000(), Duration::Zero())) ;
        EXPECT_ANY_THROW(Instant::J2000().isNear(Instant::Undefined(), Duration::Zero())) ;
        EXPECT_ANY_THROW(Instant::J2000().isNear(Instant::J2000(), Duration::Undefined())) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Instant, GetDateTime)
{

    using ostk::physics::time::Scale ;
    using ostk::physics::time::DateTime ;
    using ostk::physics::time::Instant ;

    {

        for (const auto year : years)
        {

            for (const auto month : months)
            {

                for (const auto day : days)
                {

                    for (const auto hour : hours)
                    {

                        for (const auto minute : minutes)
                        {

                            for (const auto second : seconds)
                            {

                                for (const auto scale : scales)
                                {

                                    const Instant instant = Instant::DateTime(DateTime(year, month, day, hour, minute, second, 6, 7, 8), scale) ;

                                    EXPECT_EQ(DateTime(year, month, day, hour, minute, second, 6, 7, 8), instant.getDateTime(scale)) ;

                                }

                            }

                        }

                    }

                }

            }

        }

    }

    {

        for (auto const& scale : scales)
        {
            EXPECT_ANY_THROW(Instant::Undefined().getDateTime(scale)) ;
        }

        EXPECT_ANY_THROW(Instant::J2000().getDateTime(Scale::Undefined)) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Instant, GetJulianDate)
{

    using ostk::physics::time::Scale ;
    using ostk::physics::time::DateTime ;
    using ostk::physics::time::Instant ;

    {

        for (auto const& scale : scales)
        {

            EXPECT_EQ(2451545.0, Instant::DateTime(DateTime(2000, 1, 1, 12, 0, 0), scale).getJulianDate(scale)) ;
            EXPECT_EQ(2451545.25, Instant::DateTime(DateTime(2000, 1, 1, 18, 0, 0), scale).getJulianDate(scale)) ;
            EXPECT_EQ(2451545.50, Instant::DateTime(DateTime(2000, 1, 2, 0, 0, 0), scale).getJulianDate(scale)) ;
            EXPECT_EQ(2451545.75, Instant::DateTime(DateTime(2000, 1, 2, 6, 0, 0), scale).getJulianDate(scale)) ;
            EXPECT_EQ(2451546.0, Instant::DateTime(DateTime(2000, 1, 2, 12, 0, 0), scale).getJulianDate(scale)) ;

        }

    }

    {

        for (auto const& scale : scales)
        {
            EXPECT_ANY_THROW(Instant::Undefined().getJulianDate(scale)) ;
        }

        EXPECT_ANY_THROW(Instant::J2000().getJulianDate(Scale::Undefined)) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Instant, GetModifiedJulianDate)
{

    using ostk::physics::time::Scale ;
    using ostk::physics::time::DateTime ;
    using ostk::physics::time::Instant ;

    {

        for (auto const& scale : scales)
        {

            EXPECT_EQ(51544.0, Instant::DateTime(DateTime(2000, 1, 1, 0, 0, 0), scale).getModifiedJulianDate(scale)) ;
            EXPECT_EQ(54000.0, Instant::DateTime(DateTime(2006, 9, 22, 0, 0, 0), scale).getModifiedJulianDate(scale)) ;

        }

    }

    {

        for (auto const& scale : scales)
        {
            EXPECT_ANY_THROW(Instant::Undefined().getModifiedJulianDate(scale)) ;
        }

        EXPECT_ANY_THROW(Instant::J2000().getModifiedJulianDate(Scale::Undefined)) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Instant, ToString)
{

    using ostk::core::types::String ;
    using ostk::physics::time::Scale ;
    using ostk::physics::time::DateTime ;
    using ostk::physics::time::Instant ;

    {

        EXPECT_EQ("2000-01-01 12:00:00 [TT]", Instant::J2000().toString(Scale::TT)) ;

    }

    {

        for (auto const& scale : scales)
        {

            EXPECT_EQ(String::Format("2000-01-01 12:00:00 [{}]", StringFromScale(scale)), Instant::DateTime(DateTime(2000, 1, 1, 12, 0, 0, 0, 0, 0), scale).toString(scale)) ;
            EXPECT_EQ(String::Format("2000-01-01 11:59:59.999.999.999 [{}]", StringFromScale(scale)), Instant::DateTime(DateTime(2000, 1, 1, 11, 59, 59, 999, 999, 999), scale).toString(scale)) ;
            EXPECT_EQ(String::Format("2000-01-01 12:00:00.000.000.001 [{}]", StringFromScale(scale)), Instant::DateTime(DateTime(2000, 1, 1, 12, 0, 0, 0, 0, 1), scale).toString(scale)) ;

            EXPECT_EQ(String::Format("1999-01-01 00:00:00 [{}]", StringFromScale(scale)), Instant::DateTime(DateTime(1999, 1, 1, 0, 0, 0, 0, 0, 0), scale).toString(scale)) ;
            EXPECT_EQ(String::Format("2000-01-01 00:00:00 [{}]", StringFromScale(scale)), Instant::DateTime(DateTime(2000, 1, 1, 0, 0, 0, 0, 0, 0), scale).toString(scale)) ;
            EXPECT_EQ(String::Format("2001-01-01 00:00:00 [{}]", StringFromScale(scale)), Instant::DateTime(DateTime(2001, 1, 1, 0, 0, 0, 0, 0, 0), scale).toString(scale)) ;

            EXPECT_EQ(String::Format("2018-01-02 03:04:05.006.007.008 [{}]", StringFromScale(scale)), Instant::DateTime(DateTime(2018, 1, 2, 3, 4, 5, 6, 7, 8), scale).toString(scale)) ;

            EXPECT_EQ(String::Format("1981-01-01 00:00:00 [{}]", StringFromScale(scale)), Instant::DateTime(DateTime(1981, 1, 1, 0, 0, 0, 0, 0, 0), scale).toString(scale)) ;
            EXPECT_EQ(String::Format("2030-12-31 23:59:59.999.999.999 [{}]", StringFromScale(scale)), Instant::DateTime(DateTime(2030, 12, 31, 23, 59, 59, 999, 999, 999), scale).toString(scale)) ;

        }

    }

    {

        for (auto const& scale : scales)
        {
            EXPECT_ANY_THROW(Instant::Undefined().toString(scale)) ;
        }

    }

    {

        EXPECT_ANY_THROW(Instant::J2000().toString(Scale::Undefined)) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Instant, Undefined)
{

    using ostk::physics::time::Scale ;
    using ostk::physics::time::Instant ;

    {

        EXPECT_NO_THROW(Instant::Undefined()) ;
        EXPECT_FALSE(Instant::Undefined().isDefined()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Instant, Now)
{

    using ostk::physics::time::Scale ;
    using ostk::physics::time::Duration ;
    using ostk::physics::time::Instant ;

    {

        EXPECT_NO_THROW(Instant::Now()) ;

        Instant now_A = Instant::Now() ;
        Instant now_B = Instant::Now() ;

        EXPECT_TRUE(now_A.isDefined()) ;
        EXPECT_TRUE(now_B.isDefined()) ;

        EXPECT_NE(now_A, now_B) ;
        EXPECT_TRUE(now_A < now_B) ;

        EXPECT_GT(Duration::Milliseconds(1.0), now_B - now_A) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Instant, J2000)
{

    using ostk::physics::time::Scale ;
    using ostk::physics::time::DateTime ;
    using ostk::physics::time::Instant ;

    {

        EXPECT_NO_THROW(Instant::J2000()) ;
        EXPECT_TRUE(Instant::J2000().isDefined()) ;

        EXPECT_EQ(DateTime(2000, 1, 1, 12, 0, 0), Instant::J2000().getDateTime(Scale::TT)) ;
        EXPECT_EQ(DateTime(2000, 1, 1, 11, 59, 27, 816), Instant::J2000().getDateTime(Scale::TAI)) ;
        EXPECT_EQ(DateTime(2000, 1, 1, 11, 58, 55, 816), Instant::J2000().getDateTime(Scale::UTC)) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Instant, DateTime)
{

    using ostk::physics::time::Scale ;
    using ostk::physics::time::DateTime ;
    using ostk::physics::time::Instant ;

    {

        for (const auto year : years)
        {

            for (const auto month : months)
            {

                for (const auto day : days)
                {

                    for (const auto hour : hours)
                    {

                        for (const auto minute : minutes)
                        {

                            for (const auto second : seconds)
                            {

                                for (const auto millisecond : milliseconds)
                                {

                                    for (const auto microsecond : microseconds)
                                    {

                                        for (const auto nanosecond : nanoseconds)
                                        {

                                            for (const auto scale : scales)
                                            {

                                                const DateTime dateTime = { year, month, day, hour, minute, second, millisecond, microsecond, nanosecond } ;

                                                EXPECT_NO_THROW(Instant::DateTime(dateTime, scale)) ;
                                                EXPECT_TRUE(Instant::DateTime(dateTime, scale).isDefined()) ;
                                                EXPECT_EQ(dateTime, Instant::DateTime(dateTime, scale).getDateTime(scale)) ;

                                            }

                                        }

                                    }

                                }

                            }

                        }

                    }

                }

            }

        }

    }

    {

        EXPECT_ANY_THROW(Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::Undefined)) ;

        for (const auto scale : scales)
        {

            EXPECT_ANY_THROW(Instant::DateTime(DateTime(1969, 1, 1, 0, 0, 0), scale)) ;
            EXPECT_ANY_THROW(Instant::DateTime(DateTime(2031, 1, 1, 0, 0, 0), scale)) ;

        }

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Instant, JulianDate)
{

    using ostk::core::types::Real ;
    using ostk::physics::time::Scale ;
    using ostk::physics::time::DateTime ;
    using ostk::physics::time::Instant ;

    {

        for (auto const& scale : scales)
        {

            EXPECT_EQ(DateTime(2000, 1, 1, 12, 0, 0), Instant::JulianDate(2451545.0, scale).getDateTime(scale)) ;
            EXPECT_EQ(DateTime(2000, 1, 1, 18, 0, 0), Instant::JulianDate(2451545.25, scale).getDateTime(scale)) ;
            EXPECT_EQ(DateTime(2000, 1, 2, 0, 0, 0), Instant::JulianDate(2451545.50, scale).getDateTime(scale)) ;
            EXPECT_EQ(DateTime(2000, 1, 2, 6, 0, 0), Instant::JulianDate(2451545.75, scale).getDateTime(scale)) ;
            EXPECT_EQ(DateTime(2000, 1, 2, 12, 0, 0), Instant::JulianDate(2451546.0, scale).getDateTime(scale)) ;

        }

    }

    {

        for (auto const& scale : scales)
        {

            EXPECT_ANY_THROW(Instant::JulianDate(Real::Undefined(), scale)) ;

        }

        EXPECT_ANY_THROW(Instant::JulianDate(0.0, Scale::Undefined)) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Instant, ModifiedJulianDate)
{

    using ostk::core::types::Real ;
    using ostk::physics::time::Scale ;
    using ostk::physics::time::DateTime ;
    using ostk::physics::time::Instant ;

    {

        for (auto const& scale : scales)
        {

            EXPECT_EQ(DateTime(2000, 1, 1, 0, 0, 0), Instant::ModifiedJulianDate(51544.0, scale).getDateTime(scale)) ;
            EXPECT_EQ(DateTime(2006, 9, 22, 0, 0, 0), Instant::ModifiedJulianDate(54000.0, scale).getDateTime(scale)) ;

        }

    }

    {

        for (auto const& scale : scales)
        {

            EXPECT_ANY_THROW(Instant::ModifiedJulianDate(Real::Undefined(), scale)) ;

        }

        EXPECT_ANY_THROW(Instant::ModifiedJulianDate(0.0, Scale::Undefined)) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (OpenSpaceToolkit_Physics_Time_Instant, Test_1)
{

    // Test leap-second jump.

    using ostk::core::ctnr::Array ;

    using ostk::physics::time::Scale ;
    using ostk::physics::time::DateTime ;
    using ostk::physics::time::Instant ;
    using ostk::physics::time::Duration ;

    const Array<Instant> instants =
    {
        Instant::DateTime(DateTime::Parse("2016-12-31 23:59:59"), Scale::UTC),
        Instant::DateTime(DateTime::Parse("2015-06-30 23:59:59"), Scale::UTC),
        Instant::DateTime(DateTime::Parse("2012-06-30 23:59:59"), Scale::UTC),
        Instant::DateTime(DateTime::Parse("2008-12-31 23:59:59"), Scale::UTC),
        Instant::DateTime(DateTime::Parse("2005-12-31 23:59:59"), Scale::UTC),
        Instant::DateTime(DateTime::Parse("1998-12-31 23:59:59"), Scale::UTC),
        Instant::DateTime(DateTime::Parse("1997-06-30 23:59:59"), Scale::UTC),
        Instant::DateTime(DateTime::Parse("1995-12-31 23:59:59"), Scale::UTC),
        Instant::DateTime(DateTime::Parse("1994-06-30 23:59:59"), Scale::UTC),
        Instant::DateTime(DateTime::Parse("1993-06-30 23:59:59"), Scale::UTC),
        Instant::DateTime(DateTime::Parse("1992-06-30 23:59:59"), Scale::UTC),
        Instant::DateTime(DateTime::Parse("1990-12-31 23:59:59"), Scale::UTC),
        Instant::DateTime(DateTime::Parse("1989-12-31 23:59:59"), Scale::UTC),
        Instant::DateTime(DateTime::Parse("1987-12-31 23:59:59"), Scale::UTC),
        Instant::DateTime(DateTime::Parse("1985-06-30 23:59:59"), Scale::UTC),
        Instant::DateTime(DateTime::Parse("1983-06-30 23:59:59"), Scale::UTC),
        Instant::DateTime(DateTime::Parse("1982-06-30 23:59:59"), Scale::UTC),
        Instant::DateTime(DateTime::Parse("1981-06-30 23:59:59"), Scale::UTC),
        Instant::DateTime(DateTime::Parse("1979-12-31 23:59:59"), Scale::UTC),
        Instant::DateTime(DateTime::Parse("1978-12-31 23:59:59"), Scale::UTC),
        Instant::DateTime(DateTime::Parse("1977-12-31 23:59:59"), Scale::UTC),
        Instant::DateTime(DateTime::Parse("1976-12-31 23:59:59"), Scale::UTC),
        Instant::DateTime(DateTime::Parse("1975-12-31 23:59:59"), Scale::UTC),
        Instant::DateTime(DateTime::Parse("1974-12-31 23:59:59"), Scale::UTC),
        Instant::DateTime(DateTime::Parse("1973-12-31 23:59:59"), Scale::UTC),
        Instant::DateTime(DateTime::Parse("1972-12-31 23:59:59"), Scale::UTC),
        Instant::DateTime(DateTime::Parse("1972-06-30 23:59:59"), Scale::UTC)
    } ;

    for (const auto& instant: instants)
    {
        EXPECT_EQ(instant.getDateTime(Scale::UTC), (instant + Duration::Seconds(+1.0)).getDateTime(Scale::UTC)) ;
    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
