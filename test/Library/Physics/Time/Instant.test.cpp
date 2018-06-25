////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Time/Instant.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Time/Instant.hpp>
#include <Library/Core/Containers/Array.hpp>
#include <Library/Core/Types/Integer.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using library::core::types::Uint8 ;
using library::core::types::Uint16 ;
using library::core::ctnr::Array ;
using library::physics::time::Scale ;

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

TEST (Library_Physics_Time_Instant, EqualToOperator)
{
    
    using library::physics::time::Scale ;
    using library::physics::time::DateTime ;
    using library::physics::time::Instant ;

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

TEST (Library_Physics_Time_Instant, NotEqualToOperator)
{
    
    using library::physics::time::Scale ;
    using library::physics::time::DateTime ;
    using library::physics::time::Instant ;

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

TEST (Library_Physics_Time_Instant, LessThanOperator)
{
    
    using library::physics::time::Scale ;
    using library::physics::time::DateTime ;
    using library::physics::time::Instant ;

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

TEST (Library_Physics_Time_Instant, LessThanOrEqualToOperator)
{
    
    using library::physics::time::Scale ;
    using library::physics::time::DateTime ;
    using library::physics::time::Instant ;

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

TEST (Library_Physics_Time_Instant, GreaterThanOperator)
{
    
    using library::physics::time::Scale ;
    using library::physics::time::DateTime ;
    using library::physics::time::Instant ;

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

TEST (Library_Physics_Time_Instant, GreaterThanOrEqualToOperator)
{
    
    using library::physics::time::Scale ;
    using library::physics::time::DateTime ;
    using library::physics::time::Instant ;

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

TEST (Library_Physics_Time_Instant, AdditionOperator)
{
    
    using library::physics::time::Scale ;
    using library::physics::time::DateTime ;
    using library::physics::time::Instant ;
    using library::physics::time::Duration ;

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

TEST (Library_Physics_Time_Instant, SubtractionOperator)
{
    
    using library::physics::time::Scale ;
    using library::physics::time::DateTime ;
    using library::physics::time::Instant ;
    using library::physics::time::Duration ;

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

TEST (Library_Physics_Time_Instant, AdditionAssignementOperator)
{
    
    using library::physics::time::Scale ;
    using library::physics::time::DateTime ;
    using library::physics::time::Instant ;
    using library::physics::time::Duration ;

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

TEST (Library_Physics_Time_Instant, SubtractionAssignementOperator)
{
    
    using library::physics::time::Scale ;
    using library::physics::time::DateTime ;
    using library::physics::time::Instant ;
    using library::physics::time::Duration ;

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

TEST (Library_Physics_Time_Instant, StreamOperator)
{
    
    using library::physics::time::Scale ;
    using library::physics::time::Instant ;

    {

        testing::internal::CaptureStdout() ;

        EXPECT_NO_THROW(std::cout << Instant::J2000() << std::endl) ;

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty()) ;

    }

}

TEST (Library_Physics_Time_Instant, IsDefined)
{
    
    using library::physics::time::Scale ;
    using library::physics::time::DateTime ;
    using library::physics::time::Instant ;

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

TEST (Library_Physics_Time_Instant, IsPostEpoch)
{
    
    using library::physics::time::Scale ;
    using library::physics::time::DateTime ;
    using library::physics::time::Instant ;

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

TEST (Library_Physics_Time_Instant, GetDateTime)
{
    
    using library::physics::time::Scale ;
    using library::physics::time::DateTime ;
    using library::physics::time::Instant ;

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

TEST (Library_Physics_Time_Instant, GetJulianDate)
{
    
    using library::physics::time::Scale ;
    using library::physics::time::DateTime ;
    using library::physics::time::Instant ;

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

TEST (Library_Physics_Time_Instant, GetModifiedJulianDate)
{
    
    using library::physics::time::Scale ;
    using library::physics::time::DateTime ;
    using library::physics::time::Instant ;

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

TEST (Library_Physics_Time_Instant, GetString)
{
    
    using library::core::types::String ;
    using library::physics::time::Scale ;
    using library::physics::time::DateTime ;
    using library::physics::time::Instant ;

    {

        EXPECT_EQ("2000-01-01 12:00:00 [TT]", Instant::J2000().getString(Scale::TT)) ;

    }

    {

        for (auto const& scale : scales)
        {

            EXPECT_EQ(String::Format("2000-01-01 12:00:00 [{}]", StringFromScale(scale)), Instant::DateTime(DateTime(2000, 1, 1, 12, 0, 0, 0, 0, 0), scale).getString(scale)) ;
            EXPECT_EQ(String::Format("2000-01-01 11:59:59.999.999.999 [{}]", StringFromScale(scale)), Instant::DateTime(DateTime(2000, 1, 1, 11, 59, 59, 999, 999, 999), scale).getString(scale)) ;
            EXPECT_EQ(String::Format("2000-01-01 12:00:00.000.000.001 [{}]", StringFromScale(scale)), Instant::DateTime(DateTime(2000, 1, 1, 12, 0, 0, 0, 0, 1), scale).getString(scale)) ;

            EXPECT_EQ(String::Format("1999-01-01 00:00:00 [{}]", StringFromScale(scale)), Instant::DateTime(DateTime(1999, 1, 1, 0, 0, 0, 0, 0, 0), scale).getString(scale)) ;        
            EXPECT_EQ(String::Format("2000-01-01 00:00:00 [{}]", StringFromScale(scale)), Instant::DateTime(DateTime(2000, 1, 1, 0, 0, 0, 0, 0, 0), scale).getString(scale)) ;
            EXPECT_EQ(String::Format("2001-01-01 00:00:00 [{}]", StringFromScale(scale)), Instant::DateTime(DateTime(2001, 1, 1, 0, 0, 0, 0, 0, 0), scale).getString(scale)) ;

            EXPECT_EQ(String::Format("2018-01-02 03:04:05.006.007.008 [{}]", StringFromScale(scale)), Instant::DateTime(DateTime(2018, 1, 2, 3, 4, 5, 6, 7, 8), scale).getString(scale)) ;

            EXPECT_EQ(String::Format("1981-01-01 00:00:00 [{}]", StringFromScale(scale)), Instant::DateTime(DateTime(1981, 1, 1, 0, 0, 0, 0, 0, 0), scale).getString(scale)) ;
            EXPECT_EQ(String::Format("2030-12-31 23:59:59.999.999.999 [{}]", StringFromScale(scale)), Instant::DateTime(DateTime(2030, 12, 31, 23, 59, 59, 999, 999, 999), scale).getString(scale)) ;

        }

    }

    {

        for (auto const& scale : scales)
        {
            EXPECT_ANY_THROW(Instant::Undefined().getString(scale)) ;
        }

    }

    {

        EXPECT_ANY_THROW(Instant::J2000().getString(Scale::Undefined)) ;

    }

}

TEST (Library_Physics_Time_Instant, Undefined)
{
    
    using library::physics::time::Scale ;
    using library::physics::time::Instant ;

    {

        EXPECT_NO_THROW(Instant::Undefined()) ;
        EXPECT_FALSE(Instant::Undefined().isDefined()) ;

    }

}

TEST (Library_Physics_Time_Instant, Now)
{
    
    using library::physics::time::Scale ;
    using library::physics::time::Duration ;
    using library::physics::time::Instant ;

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

TEST (Library_Physics_Time_Instant, J2000)
{
    
    using library::physics::time::Scale ;
    using library::physics::time::DateTime ;
    using library::physics::time::Instant ;

    {

        EXPECT_NO_THROW(Instant::J2000()) ;
        EXPECT_TRUE(Instant::J2000().isDefined()) ;

        EXPECT_EQ(DateTime(2000, 1, 1, 12, 0, 0), Instant::J2000().getDateTime(Scale::TT)) ;
        EXPECT_EQ(DateTime(2000, 1, 1, 11, 59, 27, 816), Instant::J2000().getDateTime(Scale::TAI)) ;
        EXPECT_EQ(DateTime(2000, 1, 1, 11, 58, 55, 816), Instant::J2000().getDateTime(Scale::UTC)) ;

    }

}

TEST (Library_Physics_Time_Instant, DateTime)
{
    
    using library::physics::time::Scale ;
    using library::physics::time::DateTime ;
    using library::physics::time::Instant ;

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

TEST (Library_Physics_Time_Instant, JulianDate)
{
    
    using library::core::types::Real ;
    using library::physics::time::Scale ;
    using library::physics::time::DateTime ;
    using library::physics::time::Instant ;

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

TEST (Library_Physics_Time_Instant, ModifiedJulianDate)
{
    
    using library::core::types::Real ;
    using library::physics::time::Scale ;
    using library::physics::time::DateTime ;
    using library::physics::time::Instant ;

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

// TEST (Library_Physics_Time_Instant, Test_1)
// {
    
//     using library::physics::time::Scale ;
//     using library::physics::time::DateTime ;
//     using library::physics::time::Instant ;

//     {

//         Instant instant = Instant::DateTime(DateTime::Parse("2000-01-01 12:00:00"), Scale::TT) ;

//         std::cout << instant.getString(Scale::TT) << std::endl  ;
//         std::cout << instant.getString(Scale::TAI) << std::endl  ;
//         std::cout << instant.getString(Scale::UTC) << std::endl  ;

//     }

//     {

//         Instant instant = Instant::DateTime(DateTime::Parse("2000-01-01 12:00:00"), Scale::TAI) ;

//         std::cout << instant.getString(Scale::TT) << std::endl  ;
//         std::cout << instant.getString(Scale::TAI) << std::endl  ;
//         std::cout << instant.getString(Scale::UTC) << std::endl  ;

//     }

//     {

//         Instant instant = Instant::DateTime(DateTime::Parse("2000-01-01 12:00:00"), Scale::UTC) ;

//         std::cout << instant.getString(Scale::TT) << std::endl  ;
//         std::cout << instant.getString(Scale::TAI) << std::endl  ;
//         std::cout << instant.getString(Scale::UTC) << std::endl  ;

//     }

// }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////