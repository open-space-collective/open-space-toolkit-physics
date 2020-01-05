////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           OpenSpaceToolkit/Physics/Time/Duration.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Physics/Time/Scale.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Time/Duration.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (OpenSpaceToolkit_Physics_Time_Duration, Constructor)
{

    using ostk::core::types::Int64 ;
    using ostk::physics::time::Duration ;

    {

        const Int64 nanosecondCount = 123456 ;

        EXPECT_NO_THROW(Duration duration(nanosecondCount)) ;

    }

    {

        const Int64 nanosecondCount = -123456 ;

        EXPECT_NO_THROW(Duration duration(nanosecondCount) ;) ;

    }

    {

        const Int64 nanosecondCount = 0 ;

        EXPECT_NO_THROW(Duration duration(nanosecondCount) ;) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Duration, EqualToOperator)
{

    using ostk::physics::time::Duration ;

    {

        EXPECT_TRUE(Duration(0) == Duration(0)) ;
        EXPECT_TRUE(Duration(1) == Duration(1)) ;
        EXPECT_TRUE(Duration(-1) == Duration(-1)) ;

    }

    {

        EXPECT_FALSE(Duration(-1) == Duration(0)) ;
        EXPECT_FALSE(Duration(+1) == Duration(0)) ;

        EXPECT_FALSE(Duration(0) == Duration(-1)) ;
        EXPECT_FALSE(Duration(0) == Duration(+1)) ;

    }

    {

        EXPECT_FALSE(Duration::Undefined() == Duration::Undefined()) ;
        EXPECT_FALSE(Duration::Undefined() == Duration(0)) ;
        EXPECT_FALSE(Duration(0) == Duration::Undefined()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Duration, NoEqualToOperator)
{

    using ostk::physics::time::Duration ;

    {

        EXPECT_TRUE(Duration(-1) != Duration(0)) ;
        EXPECT_TRUE(Duration(+1) != Duration(0)) ;

        EXPECT_TRUE(Duration(0) != Duration(-1)) ;
        EXPECT_TRUE(Duration(0) != Duration(+1)) ;

    }

    {

        EXPECT_TRUE(Duration::Undefined() != Duration::Undefined()) ;
        EXPECT_TRUE(Duration::Undefined() != Duration(0)) ;
        EXPECT_TRUE(Duration(0) != Duration::Undefined()) ;

    }

    {

        EXPECT_FALSE(Duration(0) != Duration(0)) ;
        EXPECT_FALSE(Duration(1) != Duration(1)) ;
        EXPECT_FALSE(Duration(-1) != Duration(-1)) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Duration, LessThanOperator)
{

    using ostk::physics::time::Duration ;

    {

        EXPECT_TRUE(Duration(-1) < Duration(0)) ;
        EXPECT_TRUE(Duration(0) < Duration(+1)) ;
        EXPECT_TRUE(Duration(-1) < Duration(+1)) ;

    }

    {

        EXPECT_FALSE(Duration(0) < Duration(0)) ;
        EXPECT_FALSE(Duration(+1) < Duration(0)) ;
        EXPECT_FALSE(Duration(+1) < Duration(-1)) ;
        EXPECT_FALSE(Duration(0) < Duration(-1)) ;

    }

    {

        EXPECT_ANY_THROW(Duration::Undefined() < Duration::Undefined()) ;
        EXPECT_ANY_THROW(Duration::Undefined() < Duration(0)) ;
        EXPECT_ANY_THROW(Duration(0) < Duration::Undefined()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Duration, LessThanOrEqualToOperator)
{

    using ostk::physics::time::Duration ;

    {

        EXPECT_TRUE(Duration(-1) <= Duration(0)) ;
        EXPECT_TRUE(Duration(0) <= Duration(+1)) ;
        EXPECT_TRUE(Duration(-1) <= Duration(+1)) ;

        EXPECT_TRUE(Duration(0) <= Duration(0)) ;

    }

    {

        EXPECT_FALSE(Duration(+1) <= Duration(0)) ;
        EXPECT_FALSE(Duration(+1) <= Duration(-1)) ;
        EXPECT_FALSE(Duration(0) <= Duration(-1)) ;

    }

    {

        EXPECT_ANY_THROW(Duration::Undefined() <= Duration::Undefined()) ;
        EXPECT_ANY_THROW(Duration::Undefined() <= Duration(0)) ;
        EXPECT_ANY_THROW(Duration(0) <= Duration::Undefined()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Duration, GreaterThanOperator)
{

    using ostk::physics::time::Duration ;

    {

        EXPECT_TRUE(Duration(+1) > Duration(0)) ;
        EXPECT_TRUE(Duration(+1) > Duration(-1)) ;
        EXPECT_TRUE(Duration(0) > Duration(-1)) ;

    }

    {

        EXPECT_FALSE(Duration(0) > Duration(0)) ;

        EXPECT_FALSE(Duration(-1) > Duration(0)) ;
        EXPECT_FALSE(Duration(0) > Duration(+1)) ;
        EXPECT_FALSE(Duration(-1) > Duration(+1)) ;

    }

    {

        EXPECT_ANY_THROW(Duration::Undefined() > Duration::Undefined()) ;
        EXPECT_ANY_THROW(Duration::Undefined() > Duration(0)) ;
        EXPECT_ANY_THROW(Duration(0) > Duration::Undefined()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Duration, GreaterThanOrEqualToOperator)
{

    using ostk::physics::time::Duration ;

    {

        EXPECT_TRUE(Duration(+1) >= Duration(0)) ;
        EXPECT_TRUE(Duration(+1) >= Duration(-1)) ;
        EXPECT_TRUE(Duration(0) >= Duration(-1)) ;

        EXPECT_TRUE(Duration(0) >= Duration(0)) ;

    }

    {

        EXPECT_FALSE(Duration(-1) >= Duration(0)) ;
        EXPECT_FALSE(Duration(0) >= Duration(+1)) ;
        EXPECT_FALSE(Duration(-1) >= Duration(+1)) ;

    }

    {

        EXPECT_ANY_THROW(Duration::Undefined() >= Duration::Undefined()) ;
        EXPECT_ANY_THROW(Duration::Undefined() >= Duration(0)) ;
        EXPECT_ANY_THROW(Duration(0) >= Duration::Undefined()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Duration, AdditionOperator)
{

    using ostk::physics::time::Duration ;

    {

        EXPECT_EQ(Duration(0), Duration(0) + Duration(0)) ;
        EXPECT_EQ(Duration(1), Duration(1) + Duration(0)) ;
        EXPECT_EQ(Duration(1), Duration(0) + Duration(1)) ;
        EXPECT_EQ(Duration(2), Duration(1) + Duration(1)) ;

        EXPECT_EQ(Duration(-1), Duration(-1) + Duration(0)) ;
        EXPECT_EQ(Duration(-1), Duration(0) + Duration(-1)) ;
        EXPECT_EQ(Duration(-2), Duration(-1) + Duration(-1)) ;

    }

    {

        EXPECT_ANY_THROW(Duration::Undefined() + Duration::Undefined()) ;
        EXPECT_ANY_THROW(Duration::Undefined() + Duration(0)) ;
        EXPECT_ANY_THROW(Duration(0) + Duration::Undefined()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Duration, SubtractionOperator)
{

    using ostk::physics::time::Duration ;

    {

        EXPECT_EQ(Duration(0), Duration(0) - Duration(0)) ;
        EXPECT_EQ(Duration(+1), Duration(1) - Duration(0)) ;
        EXPECT_EQ(Duration(-1), Duration(0) - Duration(1)) ;
        EXPECT_EQ(Duration(0), Duration(1) - Duration(1)) ;

        EXPECT_EQ(Duration(-1), Duration(-1) - Duration(0)) ;
        EXPECT_EQ(Duration(+1), Duration(0) - Duration(-1)) ;
        EXPECT_EQ(Duration(0), Duration(-1) - Duration(-1)) ;

    }

    {

        EXPECT_ANY_THROW(Duration::Undefined() - Duration::Undefined()) ;
        EXPECT_ANY_THROW(Duration::Undefined() - Duration(0)) ;
        EXPECT_ANY_THROW(Duration(0) - Duration::Undefined()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Duration, MultiplicationOperator)
{

    using ostk::core::types::Real ;
    using ostk::physics::time::Duration ;

    {

        EXPECT_EQ(Duration(0), Duration(0) * 0) ;
        EXPECT_EQ(Duration(0), Duration(0) * 1) ;

        EXPECT_EQ(Duration(0), Duration(1) * 0) ;
        EXPECT_EQ(Duration(+1), Duration(1) * +1) ;
        EXPECT_EQ(Duration(-1), Duration(1) * -1) ;

        EXPECT_EQ(Duration(0), Duration(-1) * 0) ;
        EXPECT_EQ(Duration(-1), Duration(-1) * +1) ;
        EXPECT_EQ(Duration(+1), Duration(-1) * -1) ;

    }

    {

        EXPECT_EQ(Duration(0), Duration(0) * 0.0) ;
        EXPECT_EQ(Duration(0), Duration(0)) ;

        EXPECT_EQ(Duration(0), Duration(1) * 0.0) ;
        EXPECT_EQ(Duration(+1), Duration(1) * +1.0) ;
        EXPECT_EQ(Duration(-1), Duration(1) * -1.0) ;

        EXPECT_EQ(Duration(0), Duration(-1) * 0.0) ;
        EXPECT_EQ(Duration(-1), Duration(-1) * +1.0) ;
        EXPECT_EQ(Duration(+1), Duration(-1) * -1.0) ;

    }

    {

        EXPECT_EQ(Duration(0), 0 * Duration(0)) ;
        EXPECT_EQ(Duration(0), 1 * Duration(0)) ;

        EXPECT_EQ(Duration(0), 0 * Duration(1)) ;
        EXPECT_EQ(Duration(+1), +1 * Duration(1)) ;
        EXPECT_EQ(Duration(-1), -1 * Duration(1)) ;

        EXPECT_EQ(Duration(0), 0 * Duration(-1)) ;
        EXPECT_EQ(Duration(-1), +1 * Duration(-1)) ;
        EXPECT_EQ(Duration(+1), -1 * Duration(-1)) ;

    }

    {

        EXPECT_EQ(Duration(0), 0.0 * Duration(0)) ;
        EXPECT_EQ(Duration(0), 1.0 * Duration(0)) ;

        EXPECT_EQ(Duration(0), 0.0 * Duration(1)) ;
        EXPECT_EQ(Duration(+1), +1.0 * Duration(1)) ;
        EXPECT_EQ(Duration(-1), -1.0 * Duration(1)) ;

        EXPECT_EQ(Duration(0), 0.0 * Duration(-1)) ;
        EXPECT_EQ(Duration(-1), +1.0 * Duration(-1)) ;
        EXPECT_EQ(Duration(+1), -1.0 * Duration(-1)) ;

    }

    {

        EXPECT_EQ(Duration(+123456), Duration(1000) * +123.456) ;
        EXPECT_EQ(Duration(-123456), Duration(1000) * -123.456) ;

    }

    {

        EXPECT_ANY_THROW(Duration::Undefined() * Real::Undefined()) ;
        EXPECT_ANY_THROW(Duration::Undefined() * 0) ;
        EXPECT_ANY_THROW(Duration::Undefined() * 0.0) ;
        EXPECT_ANY_THROW(0 * Duration::Undefined()) ;
        EXPECT_ANY_THROW(0.0 * Duration::Undefined()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Duration, DivisionOperator)
{

    using ostk::core::types::Real ;
    using ostk::physics::time::Duration ;

    {

        EXPECT_EQ(Duration(0), Duration(0) / 1) ;

        EXPECT_EQ(Duration(+1), Duration(1) / +1) ;
        EXPECT_EQ(Duration(-1), Duration(1) / -1) ;

        EXPECT_EQ(Duration(-1), Duration(-1) / +1) ;
        EXPECT_EQ(Duration(+1), Duration(-1) / -1) ;

    }

    {

        EXPECT_EQ(Duration(0), Duration(0) / 1.0) ;

        EXPECT_EQ(Duration(+1), Duration(1) / +1.0) ;
        EXPECT_EQ(Duration(-1), Duration(1) / -1.0) ;

        EXPECT_EQ(Duration(-1), Duration(-1) / +1.0) ;
        EXPECT_EQ(Duration(+1), Duration(-1) / -1.0) ;

    }

    {

        EXPECT_EQ(Duration(+20), Duration(+1000) / +50.0) ;
        EXPECT_EQ(Duration(-20), Duration(+1000) / -50.0) ;

        EXPECT_EQ(Duration(-20), Duration(-1000) / +50.0) ;
        EXPECT_EQ(Duration(+20), Duration(-1000) / -50.0) ;

    }

    {

        EXPECT_ANY_THROW(Duration::Undefined() / Real::Undefined()) ;
        EXPECT_ANY_THROW(Duration::Undefined() / 1) ;
        EXPECT_ANY_THROW(Duration::Undefined() / 1.0) ;
        EXPECT_ANY_THROW(Duration::Undefined() / 0) ;
        EXPECT_ANY_THROW(Duration::Undefined() / 0.0) ;

        EXPECT_ANY_THROW(Duration(123) / Real::Undefined()) ;
        EXPECT_ANY_THROW(Duration(123) / 0) ;
        EXPECT_ANY_THROW(Duration(123) / 0.0) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Duration, AdditionAssignementOperator)
{

    using ostk::physics::time::Duration ;

    {

        EXPECT_EQ(Duration(0), Duration(0) += Duration(0)) ;
        EXPECT_EQ(Duration(1), Duration(1) += Duration(0)) ;
        EXPECT_EQ(Duration(1), Duration(0) += Duration(1)) ;
        EXPECT_EQ(Duration(2), Duration(1) += Duration(1)) ;

        EXPECT_EQ(Duration(-1), Duration(-1) += Duration(0)) ;
        EXPECT_EQ(Duration(-1), Duration(0) += Duration(-1)) ;
        EXPECT_EQ(Duration(-2), Duration(-1) += Duration(-1)) ;

    }

    {

        EXPECT_ANY_THROW(Duration::Undefined() += Duration::Undefined()) ;
        EXPECT_ANY_THROW(Duration::Undefined() += Duration(0)) ;
        EXPECT_ANY_THROW(Duration(0) += Duration::Undefined()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Duration, SubtractionAssignementOperator)
{

    using ostk::physics::time::Duration ;

    {

        EXPECT_EQ(Duration(0), Duration(0) -= Duration(0)) ;
        EXPECT_EQ(Duration(+1), Duration(1) -= Duration(0)) ;
        EXPECT_EQ(Duration(-1), Duration(0) -= Duration(1)) ;
        EXPECT_EQ(Duration(0), Duration(1) -= Duration(1)) ;

        EXPECT_EQ(Duration(-1), Duration(-1) -= Duration(0)) ;
        EXPECT_EQ(Duration(+1), Duration(0) -= Duration(-1)) ;
        EXPECT_EQ(Duration(0), Duration(-1) -= Duration(-1)) ;

    }

    {

        EXPECT_ANY_THROW(Duration::Undefined() -= Duration::Undefined()) ;
        EXPECT_ANY_THROW(Duration::Undefined() -= Duration(0)) ;
        EXPECT_ANY_THROW(Duration(0) -= Duration::Undefined()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Duration, MultiplicationAssignementOperator)
{

    using ostk::core::types::Real ;
    using ostk::physics::time::Duration ;

    {

        EXPECT_EQ(Duration(0), Duration(0) *= 0) ;
        EXPECT_EQ(Duration(0), Duration(0) *= 1) ;

        EXPECT_EQ(Duration(0), Duration(1) *= 0) ;
        EXPECT_EQ(Duration(+1), Duration(1) *= +1) ;
        EXPECT_EQ(Duration(-1), Duration(1) *= -1) ;

        EXPECT_EQ(Duration(0), Duration(-1) *= 0) ;
        EXPECT_EQ(Duration(-1), Duration(-1) *= +1) ;
        EXPECT_EQ(Duration(+1), Duration(-1) *= -1) ;

    }

    {

        EXPECT_EQ(Duration(0), Duration(0) *= 0.0) ;
        EXPECT_EQ(Duration(0), Duration(0) *= 1.0) ;

        EXPECT_EQ(Duration(0), Duration(1) *= 0.0) ;
        EXPECT_EQ(Duration(+1), Duration(1) *= +1.0) ;
        EXPECT_EQ(Duration(-1), Duration(1) *= -1.0) ;

        EXPECT_EQ(Duration(0), Duration(-1) *= 0.0) ;
        EXPECT_EQ(Duration(-1), Duration(-1) *= +1.0) ;
        EXPECT_EQ(Duration(+1), Duration(-1) *= -1.0) ;

    }

    {

        EXPECT_EQ(Duration(+123456), Duration(1000) *= +123.456) ;
        EXPECT_EQ(Duration(-123456), Duration(1000) *= -123.456) ;

    }

    {

        EXPECT_ANY_THROW(Duration::Undefined() *= Real::Undefined()) ;
        EXPECT_ANY_THROW(Duration::Undefined() *= 0) ;
        EXPECT_ANY_THROW(Duration::Undefined() *= 0.0) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Duration, DivisionAssignementOperator)
{

    using ostk::core::types::Real ;
    using ostk::physics::time::Duration ;

    {

        EXPECT_EQ(Duration(0), Duration(0) /= 1) ;

        EXPECT_EQ(Duration(+1), Duration(1) /= +1) ;
        EXPECT_EQ(Duration(-1), Duration(1) /= -1) ;

        EXPECT_EQ(Duration(-1), Duration(-1) /= +1) ;
        EXPECT_EQ(Duration(+1), Duration(-1) /= -1) ;

    }

    {

        EXPECT_EQ(Duration(0), Duration(0) /= 1.0) ;

        EXPECT_EQ(Duration(+1), Duration(1) /= +1.0) ;
        EXPECT_EQ(Duration(-1), Duration(1) /= -1.0) ;

        EXPECT_EQ(Duration(-1), Duration(-1) /= +1.0) ;
        EXPECT_EQ(Duration(+1), Duration(-1) /= -1.0) ;

    }

    {

        EXPECT_EQ(Duration(+20), Duration(+1000) /= +50.0) ;
        EXPECT_EQ(Duration(-20), Duration(+1000) /= -50.0) ;

        EXPECT_EQ(Duration(-20), Duration(-1000) /= +50.0) ;
        EXPECT_EQ(Duration(+20), Duration(-1000) /= -50.0) ;

    }

    {

        EXPECT_ANY_THROW(Duration::Undefined() /= Real::Undefined()) ;
        EXPECT_ANY_THROW(Duration::Undefined() /= 1) ;
        EXPECT_ANY_THROW(Duration::Undefined() /= 1.0) ;
        EXPECT_ANY_THROW(Duration::Undefined() /= 0) ;
        EXPECT_ANY_THROW(Duration::Undefined() /= 0.0) ;

        EXPECT_ANY_THROW(Duration(123) /= Real::Undefined()) ;
        EXPECT_ANY_THROW(Duration(123) /= 0) ;
        EXPECT_ANY_THROW(Duration(123) /= 0.0) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Duration, StreamOperator)
{

    using ostk::physics::time::Duration ;

    {

        testing::internal::CaptureStdout() ;

        EXPECT_NO_THROW(std::cout << Duration(123) << std::endl) ;

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Duration, IsDefined)
{

    using ostk::physics::time::Duration ;

    {

        EXPECT_TRUE(Duration(0).isDefined()) ;

        EXPECT_TRUE(Duration(+1).isDefined()) ;
        EXPECT_TRUE(Duration(-1).isDefined()) ;

    }

    {

        EXPECT_FALSE(Duration::Undefined().isDefined()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Duration, IsZero)
{

    using ostk::physics::time::Duration ;

    {

        EXPECT_TRUE(Duration(0).isZero()) ;

    }

    {

        EXPECT_FALSE(Duration(+1).isZero()) ;
        EXPECT_FALSE(Duration(-1).isZero()) ;

    }

    {

        EXPECT_ANY_THROW(Duration::Undefined().isZero()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Duration, IsPositive)
{

    using ostk::physics::time::Duration ;

    {

        EXPECT_TRUE(Duration(0).isPositive()) ;
        EXPECT_TRUE(Duration(+1).isPositive()) ;

    }

    {

        EXPECT_FALSE(Duration(-1).isPositive()) ;

    }

    {

        EXPECT_ANY_THROW(Duration::Undefined().isPositive()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Duration, IsStrictlyPositive)
{

    using ostk::physics::time::Duration ;

    {

        EXPECT_TRUE(Duration(+1).isStrictlyPositive()) ;

    }

    {

        EXPECT_FALSE(Duration(0).isStrictlyPositive()) ;
        EXPECT_FALSE(Duration(-1).isStrictlyPositive()) ;

    }

    {

        EXPECT_ANY_THROW(Duration::Undefined().isStrictlyPositive()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Duration, IsNear)
{

    using ostk::physics::time::Duration ;

    {

        EXPECT_TRUE(Duration::Seconds(+0.0).isNear(Duration::Seconds(+0.0), Duration::Seconds(0.0))) ;

        EXPECT_TRUE(Duration::Seconds(-1.0).isNear(Duration::Seconds(-1.0), Duration::Seconds(0.0))) ;
        EXPECT_TRUE(Duration::Seconds(+1.0).isNear(Duration::Seconds(+1.0), Duration::Seconds(0.0))) ;

        EXPECT_TRUE(Duration::Seconds(-2.0).isNear(Duration::Seconds(-1.0), Duration::Seconds(1.0))) ;
        EXPECT_TRUE(Duration::Seconds(+2.0).isNear(Duration::Seconds(+1.0), Duration::Seconds(1.0))) ;

        EXPECT_TRUE(Duration::Seconds(-1.0).isNear(Duration::Seconds(-2.0), Duration::Seconds(1.0))) ;
        EXPECT_TRUE(Duration::Seconds(+1.0).isNear(Duration::Seconds(+2.0), Duration::Seconds(1.0))) ;

    }

    {

        EXPECT_FALSE(Duration::Seconds(-3.0).isNear(Duration::Seconds(-1.0), Duration::Seconds(1.0))) ;
        EXPECT_FALSE(Duration::Seconds(+3.0).isNear(Duration::Seconds(+1.0), Duration::Seconds(1.0))) ;

        EXPECT_FALSE(Duration::Seconds(-1.0).isNear(Duration::Seconds(-3.0), Duration::Seconds(1.0))) ;
        EXPECT_FALSE(Duration::Seconds(+1.0).isNear(Duration::Seconds(+3.0), Duration::Seconds(1.0))) ;

    }

    {

        EXPECT_ANY_THROW(Duration::Undefined().isNear(Duration::Undefined(), Duration::Undefined())) ;
        EXPECT_ANY_THROW(Duration::Undefined().isNear(Duration::Zero(), Duration::Zero())) ;
        EXPECT_ANY_THROW(Duration::Zero().isNear(Duration::Undefined(), Duration::Zero())) ;
        EXPECT_ANY_THROW(Duration::Zero().isNear(Duration::Zero(), Duration::Undefined())) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Duration, GetNanoseconds)
{

    using ostk::physics::time::Duration ;

    {

        EXPECT_EQ(0, Duration(0).getNanoseconds()) ;
        EXPECT_EQ(1, Duration(1).getNanoseconds()) ;
        EXPECT_EQ(10, Duration(10).getNanoseconds()) ;
        EXPECT_EQ(100, Duration(100).getNanoseconds()) ;
        EXPECT_EQ(999, Duration(999).getNanoseconds()) ;

        EXPECT_EQ(0, Duration(1000).getNanoseconds()) ;
        EXPECT_EQ(1, Duration(1001).getNanoseconds()) ;

    }

    {

        EXPECT_EQ(1, Duration(-1).getNanoseconds()) ;
        EXPECT_EQ(10, Duration(-10).getNanoseconds()) ;
        EXPECT_EQ(100, Duration(-100).getNanoseconds()) ;
        EXPECT_EQ(999, Duration(-999).getNanoseconds()) ;

        EXPECT_EQ(0, Duration(-1000).getNanoseconds()) ;
        EXPECT_EQ(1, Duration(-1001).getNanoseconds()) ;

    }

    {

        const Duration duration = Duration::Weeks(12)
                                + Duration::Days(15)
                                + Duration::Hours(12)
                                + Duration::Minutes(34)
                                + Duration::Seconds(56)
                                + Duration::Milliseconds(567)
                                + Duration::Microseconds(890)
                                + Duration::Nanoseconds(123) ;

        EXPECT_EQ(123, duration.getNanoseconds()) ;

    }

    {

        for (auto idx = 0; idx < 100000; ++idx)
        {

            const Duration duration = Duration::Days(idx)
                                    + Duration::Hours(idx)
                                    + Duration::Minutes(idx)
                                    + Duration::Seconds(idx)
                                    + Duration::Milliseconds(idx)
                                    + Duration::Microseconds(idx)
                                    + Duration::Nanoseconds(idx) ;

            EXPECT_LE(0, duration.getNanoseconds()) ;
            EXPECT_GE(999, duration.getNanoseconds()) ;

        }

    }

    {

        EXPECT_ANY_THROW(Duration::Undefined().getNanoseconds()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Duration, GetMicroseconds)
{

    using ostk::physics::time::Duration ;

    {

        EXPECT_EQ(0, Duration(0).getMicroseconds()) ;
        EXPECT_EQ(0, Duration(1).getMicroseconds()) ;
        EXPECT_EQ(0, Duration(10).getMicroseconds()) ;
        EXPECT_EQ(0, Duration(100).getMicroseconds()) ;
        EXPECT_EQ(0, Duration(999).getMicroseconds()) ;

        EXPECT_EQ(1, Duration(1000).getMicroseconds()) ;
        EXPECT_EQ(1, Duration(1001).getMicroseconds()) ;
        EXPECT_EQ(2, Duration(2001).getMicroseconds()) ;

        EXPECT_EQ(0, Duration(1000000).getMicroseconds()) ;
        EXPECT_EQ(1, Duration(1001000).getMicroseconds()) ;
        EXPECT_EQ(2, Duration(1002000).getMicroseconds()) ;

    }

    {

        EXPECT_EQ(0, Duration(-1).getMicroseconds()) ;
        EXPECT_EQ(0, Duration(-10).getMicroseconds()) ;
        EXPECT_EQ(0, Duration(-100).getMicroseconds()) ;
        EXPECT_EQ(0, Duration(-999).getMicroseconds()) ;

        EXPECT_EQ(1, Duration(-1000).getMicroseconds()) ;
        EXPECT_EQ(1, Duration(-1001).getMicroseconds()) ;
        EXPECT_EQ(2, Duration(-2001).getMicroseconds()) ;

        EXPECT_EQ(0, Duration(-1000000).getMicroseconds()) ;
        EXPECT_EQ(1, Duration(-1001000).getMicroseconds()) ;
        EXPECT_EQ(2, Duration(-1002000).getMicroseconds()) ;

    }

    {

        const Duration duration = Duration::Weeks(12)
                                + Duration::Days(15)
                                + Duration::Hours(12)
                                + Duration::Minutes(34)
                                + Duration::Seconds(56)
                                + Duration::Milliseconds(567)
                                + Duration::Microseconds(890)
                                + Duration::Nanoseconds(123) ;

        EXPECT_EQ(890, duration.getMicroseconds()) ;

    }

    {

        for (auto idx = 0; idx < 100000; ++idx)
        {

            const Duration duration = Duration::Days(idx)
                                    + Duration::Hours(idx)
                                    + Duration::Minutes(idx)
                                    + Duration::Seconds(idx)
                                    + Duration::Milliseconds(idx)
                                    + Duration::Microseconds(idx)
                                    + Duration::Nanoseconds(idx) ;

            EXPECT_LE(0, duration.getMicroseconds()) ;
            EXPECT_GE(999, duration.getMicroseconds()) ;

        }

    }

    {

        EXPECT_ANY_THROW(Duration::Undefined().getMicroseconds()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Duration, GetMilliseconds)
{

    using ostk::physics::time::Duration ;

    {

        EXPECT_EQ(0, Duration(0).getMilliseconds()) ;
        EXPECT_EQ(0, Duration(1).getMilliseconds()) ;
        EXPECT_EQ(0, Duration(10).getMilliseconds()) ;
        EXPECT_EQ(0, Duration(100).getMilliseconds()) ;
        EXPECT_EQ(0, Duration(999).getMilliseconds()) ;

        EXPECT_EQ(0, Duration(1000).getMilliseconds()) ;
        EXPECT_EQ(0, Duration(1001).getMilliseconds()) ;
        EXPECT_EQ(0, Duration(1002).getMilliseconds()) ;

        EXPECT_EQ(1, Duration(1000000).getMilliseconds()) ;
        EXPECT_EQ(1, Duration(1001000).getMilliseconds()) ;
        EXPECT_EQ(1, Duration(1002000).getMilliseconds()) ;

        EXPECT_EQ(2, Duration(2000000).getMilliseconds()) ;
        EXPECT_EQ(2, Duration(2001000).getMilliseconds()) ;
        EXPECT_EQ(2, Duration(2002000).getMilliseconds()) ;

    }

    {

        EXPECT_EQ(0, Duration(-1).getMilliseconds()) ;
        EXPECT_EQ(0, Duration(-10).getMilliseconds()) ;
        EXPECT_EQ(0, Duration(-100).getMilliseconds()) ;
        EXPECT_EQ(0, Duration(-999).getMilliseconds()) ;

        EXPECT_EQ(0, Duration(-1000).getMilliseconds()) ;
        EXPECT_EQ(0, Duration(-1001).getMilliseconds()) ;
        EXPECT_EQ(0, Duration(-1002).getMilliseconds()) ;

        EXPECT_EQ(1, Duration(-1000000).getMilliseconds()) ;
        EXPECT_EQ(1, Duration(-1001000).getMilliseconds()) ;
        EXPECT_EQ(1, Duration(-1002000).getMilliseconds()) ;

        EXPECT_EQ(2, Duration(-2000000).getMilliseconds()) ;
        EXPECT_EQ(2, Duration(-2001000).getMilliseconds()) ;
        EXPECT_EQ(2, Duration(-2002000).getMilliseconds()) ;

    }

    {

        const Duration duration = Duration::Weeks(12)
                                + Duration::Days(15)
                                + Duration::Hours(12)
                                + Duration::Minutes(34)
                                + Duration::Seconds(56)
                                + Duration::Milliseconds(567)
                                + Duration::Microseconds(890)
                                + Duration::Nanoseconds(123) ;

        EXPECT_EQ(567, duration.getMilliseconds()) ;

    }

    {

        for (auto idx = 0; idx < 100000; ++idx)
        {

            const Duration duration = Duration::Days(idx)
                                    + Duration::Hours(idx)
                                    + Duration::Minutes(idx)
                                    + Duration::Seconds(idx)
                                    + Duration::Milliseconds(idx)
                                    + Duration::Microseconds(idx)
                                    + Duration::Nanoseconds(idx) ;

            EXPECT_LE(0, duration.getMilliseconds()) ;
            EXPECT_GE(999, duration.getMilliseconds()) ;

        }

    }

    {

        EXPECT_ANY_THROW(Duration::Undefined().getMilliseconds()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Duration, GetSeconds)
{

    using ostk::physics::time::Duration ;

    {

        EXPECT_EQ(0, Duration(0).getSeconds()) ;
        EXPECT_EQ(0, Duration(1).getSeconds()) ;
        EXPECT_EQ(0, Duration(10).getSeconds()) ;
        EXPECT_EQ(0, Duration(100).getSeconds()) ;
        EXPECT_EQ(0, Duration(999).getSeconds()) ;

        EXPECT_EQ(0, Duration(1000).getSeconds()) ;
        EXPECT_EQ(0, Duration(1001).getSeconds()) ;
        EXPECT_EQ(0, Duration(1002).getSeconds()) ;

        EXPECT_EQ(0, Duration(1000000).getSeconds()) ;
        EXPECT_EQ(0, Duration(1001000).getSeconds()) ;
        EXPECT_EQ(0, Duration(1002000).getSeconds()) ;

        EXPECT_EQ(0, Duration(2000000).getSeconds()) ;
        EXPECT_EQ(0, Duration(2001000).getSeconds()) ;
        EXPECT_EQ(0, Duration(2002000).getSeconds()) ;

        EXPECT_EQ(1, Duration(1000000000).getSeconds()) ;
        EXPECT_EQ(1, Duration(1001000000).getSeconds()) ;
        EXPECT_EQ(1, Duration(1002000000).getSeconds()) ;

        EXPECT_EQ(2, Duration(2000000000).getSeconds()) ;
        EXPECT_EQ(2, Duration(2001000000).getSeconds()) ;
        EXPECT_EQ(2, Duration(2002000000).getSeconds()) ;

    }

    {

        EXPECT_EQ(0, Duration(-1).getSeconds()) ;
        EXPECT_EQ(0, Duration(-10).getSeconds()) ;
        EXPECT_EQ(0, Duration(-100).getSeconds()) ;
        EXPECT_EQ(0, Duration(-999).getSeconds()) ;

        EXPECT_EQ(0, Duration(-1000).getSeconds()) ;
        EXPECT_EQ(0, Duration(-1001).getSeconds()) ;
        EXPECT_EQ(0, Duration(-1002).getSeconds()) ;

        EXPECT_EQ(0, Duration(-1000000).getSeconds()) ;
        EXPECT_EQ(0, Duration(-1001000).getSeconds()) ;
        EXPECT_EQ(0, Duration(-1002000).getSeconds()) ;

        EXPECT_EQ(0, Duration(-2000000).getSeconds()) ;
        EXPECT_EQ(0, Duration(-2001000).getSeconds()) ;
        EXPECT_EQ(0, Duration(-2002000).getSeconds()) ;

        EXPECT_EQ(1, Duration(-1000000000).getSeconds()) ;
        EXPECT_EQ(1, Duration(-1001000000).getSeconds()) ;
        EXPECT_EQ(1, Duration(-1002000000).getSeconds()) ;

        EXPECT_EQ(2, Duration(-2000000000).getSeconds()) ;
        EXPECT_EQ(2, Duration(-2001000000).getSeconds()) ;
        EXPECT_EQ(2, Duration(-2002000000).getSeconds()) ;

    }

    {

        const Duration duration = Duration::Weeks(12)
                                + Duration::Days(15)
                                + Duration::Hours(12)
                                + Duration::Minutes(34)
                                + Duration::Seconds(56)
                                + Duration::Milliseconds(567)
                                + Duration::Microseconds(890)
                                + Duration::Nanoseconds(123) ;

        EXPECT_EQ(56, duration.getSeconds()) ;

    }

    {

        for (auto idx = 0; idx < 100000; ++idx)
        {

            const Duration duration = Duration::Days(idx)
                                    + Duration::Hours(idx)
                                    + Duration::Minutes(idx)
                                    + Duration::Seconds(idx)
                                    + Duration::Milliseconds(idx)
                                    + Duration::Microseconds(idx)
                                    + Duration::Nanoseconds(idx) ;

            EXPECT_LE(0, duration.getSeconds()) ;
            EXPECT_GE(59, duration.getSeconds()) ;

        }

    }

    {

        EXPECT_ANY_THROW(Duration::Undefined().getSeconds()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Duration, GetMinutes)
{

    using ostk::physics::time::Duration ;

    {

        EXPECT_EQ(0, Duration(0).getMinutes()) ;
        EXPECT_EQ(0, Duration(1).getMinutes()) ;

        EXPECT_EQ(1, (Duration::Minutes(1.0) + Duration::Seconds(30.0)).getMinutes()) ;
        EXPECT_EQ(2, (Duration::Minutes(1.0) + Duration::Seconds(60.0)).getMinutes()) ;
        EXPECT_EQ(2, (Duration::Minutes(1.0) + Duration::Seconds(61.0)).getMinutes()) ;

        EXPECT_EQ(1, (Duration::Minutes(1.0) + Duration::Hours(1.0)).getMinutes()) ;
        EXPECT_EQ(1, (Duration::Minutes(1.0) + Duration::Hours(2.0)).getMinutes()) ;

    }

    {

        EXPECT_EQ(1, (-(Duration::Minutes(1.0) + Duration::Seconds(30.0))).getMinutes()) ;
        EXPECT_EQ(2, (-(Duration::Minutes(1.0) + Duration::Seconds(60.0))).getMinutes()) ;
        EXPECT_EQ(2, (-(Duration::Minutes(1.0) + Duration::Seconds(61.0))).getMinutes()) ;

        EXPECT_EQ(1, (-(Duration::Minutes(1.0) + Duration::Hours(1.0))).getMinutes()) ;
        EXPECT_EQ(1, (-(Duration::Minutes(1.0) + Duration::Hours(2.0))).getMinutes()) ;

    }

    {

        const Duration duration = Duration::Weeks(12)
                                + Duration::Days(15)
                                + Duration::Hours(12)
                                + Duration::Minutes(34)
                                + Duration::Seconds(56)
                                + Duration::Milliseconds(567)
                                + Duration::Microseconds(890)
                                + Duration::Nanoseconds(123) ;

        EXPECT_EQ(34, duration.getMinutes()) ;

    }

    {

        for (auto idx = 0; idx < 100000; ++idx)
        {

            const Duration duration = Duration::Days(idx)
                                    + Duration::Hours(idx)
                                    + Duration::Minutes(idx)
                                    + Duration::Seconds(idx)
                                    + Duration::Milliseconds(idx)
                                    + Duration::Microseconds(idx)
                                    + Duration::Nanoseconds(idx) ;

            EXPECT_LE(0, duration.getMinutes()) ;
            EXPECT_GE(59, duration.getMinutes()) ;

        }

    }

    {

        EXPECT_ANY_THROW(Duration::Undefined().getMinutes()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Duration, GetHours)
{

    using ostk::physics::time::Duration ;

    {

        EXPECT_EQ(0, Duration(0).getHours()) ;
        EXPECT_EQ(0, Duration(1).getHours()) ;

        EXPECT_EQ(1, (Duration::Hours(1.0) + Duration::Minutes(30.0)).getHours()) ;
        EXPECT_EQ(2, (Duration::Hours(1.0) + Duration::Minutes(60.0)).getHours()) ;
        EXPECT_EQ(2, (Duration::Hours(1.0) + Duration::Minutes(61.0)).getHours()) ;

        EXPECT_EQ(1, (Duration::Hours(1.0) + Duration::Days(1.0)).getHours()) ;
        EXPECT_EQ(1, (Duration::Hours(1.0) + Duration::Days(2.0)).getHours()) ;

    }

    {

        EXPECT_EQ(1, (-(Duration::Hours(1.0) + Duration::Minutes(30.0))).getHours()) ;
        EXPECT_EQ(2, (-(Duration::Hours(1.0) + Duration::Minutes(60.0))).getHours()) ;
        EXPECT_EQ(2, (-(Duration::Hours(1.0) + Duration::Minutes(61.0))).getHours()) ;

        EXPECT_EQ(1, (-(Duration::Hours(1.0) + Duration::Days(1.0))).getHours()) ;
        EXPECT_EQ(1, (-(Duration::Hours(1.0) + Duration::Days(2.0))).getHours()) ;

    }

    {

        const Duration duration = Duration::Weeks(12)
                                + Duration::Days(15)
                                + Duration::Hours(12)
                                + Duration::Minutes(34)
                                + Duration::Seconds(56)
                                + Duration::Milliseconds(567)
                                + Duration::Microseconds(890)
                                + Duration::Nanoseconds(123) ;

        EXPECT_EQ(12, duration.getHours()) ;

    }

    {

        for (auto idx = 0; idx < 100000; ++idx)
        {

            const Duration duration = Duration::Days(idx)
                                    + Duration::Hours(idx)
                                    + Duration::Minutes(idx)
                                    + Duration::Seconds(idx)
                                    + Duration::Milliseconds(idx)
                                    + Duration::Microseconds(idx)
                                    + Duration::Nanoseconds(idx) ;

            EXPECT_LE(0, duration.getHours()) ;
            EXPECT_GE(23, duration.getHours()) ;

        }

    }

    {

        EXPECT_ANY_THROW(Duration::Undefined().getHours()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Duration, GetDays)
{

    using ostk::physics::time::Duration ;

    {

        EXPECT_EQ(0, Duration(0).getDays()) ;
        EXPECT_EQ(0, Duration(1).getDays()) ;

        EXPECT_EQ(1, (Duration::Days(1.0) + Duration::Hours(12.0)).getDays()) ;
        EXPECT_EQ(2, (Duration::Days(1.0) + Duration::Hours(24.0)).getDays()) ;
        EXPECT_EQ(2, (Duration::Days(1.0) + Duration::Hours(25.0)).getDays()) ;

        EXPECT_EQ(8, (Duration::Days(1.0) + Duration::Weeks(1.0)).getDays()) ;
        EXPECT_EQ(15, (Duration::Days(1.0) + Duration::Weeks(2.0)).getDays()) ;

    }

    {

        EXPECT_EQ(1, (-(Duration::Days(1.0) + Duration::Hours(12.0))).getDays()) ;
        EXPECT_EQ(2, (-(Duration::Days(1.0) + Duration::Hours(24.0))).getDays()) ;
        EXPECT_EQ(2, (-(Duration::Days(1.0) + Duration::Hours(25.0))).getDays()) ;

        EXPECT_EQ(8, (-(Duration::Days(1.0) + Duration::Weeks(1.0))).getDays()) ;
        EXPECT_EQ(15, (-(Duration::Days(1.0) + Duration::Weeks(2.0))).getDays()) ;

    }

    {

        const Duration duration = Duration::Weeks(12)
                                + Duration::Days(15)
                                + Duration::Hours(12)
                                + Duration::Minutes(34)
                                + Duration::Seconds(56)
                                + Duration::Milliseconds(567)
                                + Duration::Microseconds(890)
                                + Duration::Nanoseconds(123) ;

        EXPECT_EQ((12 * 7 + 15), duration.getDays()) ;

    }

    {

        for (auto idx = 0; idx < 100000; ++idx)
        {

            const Duration duration = Duration::Days(idx)
                                    + Duration::Hours(idx)
                                    + Duration::Minutes(idx)
                                    + Duration::Seconds(idx)
                                    + Duration::Milliseconds(idx)
                                    + Duration::Microseconds(idx)
                                    + Duration::Nanoseconds(idx) ;

            EXPECT_LE(0, duration.getDays()) ;

        }

    }

    {

        EXPECT_ANY_THROW(Duration::Undefined().getDays()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Duration, GetWeeks)
{

    using ostk::physics::time::Duration ;

    {

        EXPECT_EQ(0, Duration(0).getWeeks()) ;
        EXPECT_EQ(0, Duration(1).getWeeks()) ;

        EXPECT_EQ(1, (Duration::Weeks(1.0) + Duration::Days(4.5)).getWeeks()) ;
        EXPECT_EQ(2, (Duration::Weeks(1.0) + Duration::Days(7.0)).getWeeks()) ;
        EXPECT_EQ(2, (Duration::Weeks(1.0) + Duration::Days(8.0)).getWeeks()) ;

        EXPECT_EQ(2, (Duration::Weeks(1.0) + Duration::Weeks(1.0)).getWeeks()) ;
        EXPECT_EQ(3, (Duration::Weeks(1.0) + Duration::Weeks(2.0)).getWeeks()) ;

    }

    {

        EXPECT_EQ(1, (-(Duration::Weeks(1.0) + Duration::Days(4.5))).getWeeks()) ;
        EXPECT_EQ(2, (-(Duration::Weeks(1.0) + Duration::Days(7.0))).getWeeks()) ;
        EXPECT_EQ(2, (-(Duration::Weeks(1.0) + Duration::Days(8.0))).getWeeks()) ;

        EXPECT_EQ(2, (-(Duration::Weeks(1.0) + Duration::Weeks(1.0))).getWeeks()) ;
        EXPECT_EQ(3, (-(Duration::Weeks(1.0) + Duration::Weeks(2.0))).getWeeks()) ;

    }

    {

        const Duration duration = Duration::Weeks(12)
                                + Duration::Days(15)
                                + Duration::Hours(12)
                                + Duration::Minutes(34)
                                + Duration::Seconds(56)
                                + Duration::Milliseconds(567)
                                + Duration::Microseconds(890)
                                + Duration::Nanoseconds(123) ;

        EXPECT_EQ(14, duration.getWeeks()) ;

    }

    {

        for (auto idx = 0; idx < 1000; ++idx)
        {

            const Duration duration = Duration::Weeks(idx)
                                    + Duration::Days(idx)
                                    + Duration::Hours(idx)
                                    + Duration::Minutes(idx)
                                    + Duration::Seconds(idx)
                                    + Duration::Milliseconds(idx)
                                    + Duration::Microseconds(idx)
                                    + Duration::Nanoseconds(idx) ;

            EXPECT_LE(0, duration.getWeeks()) ;

        }

    }

    {

        EXPECT_ANY_THROW(Duration::Undefined().getWeeks()) ;

    }

}


TEST (OpenSpaceToolkit_Physics_Time_Duration, InNanoseconds)
{

    using ostk::core::types::Int64 ;
    using ostk::physics::time::Duration ;

    {

        EXPECT_NEAR(0.0, Duration(0).inNanoseconds(), 1e-15) ;

        EXPECT_NEAR(1.0, Duration(1).inNanoseconds(), 1e-15) ;
        EXPECT_NEAR(1000.0, Duration(1000).inNanoseconds(), 1e-15) ;
        EXPECT_NEAR(1000000.0, Duration(1000000).inNanoseconds(), 1e-15) ;
        EXPECT_NEAR(1000000000.0, Duration(1000000000).inNanoseconds(), 1e-15) ;
        EXPECT_NEAR((60.0 * 1000000000.0), Duration(Int64(60) * 1000000000).inNanoseconds(), 1e-15) ;
        EXPECT_NEAR((60.0 * 60.0 * 1000000000.0), Duration(Int64(60) * 60 * 1000000000).inNanoseconds(), 1e-15) ;
        EXPECT_NEAR((24.0 * 60.0 * 60.0 * 1000000000.0), Duration(Int64(24) * 60 * 60 * 1000000000).inNanoseconds(), 1e-15) ;
        EXPECT_NEAR((7.0 * 24.0 * 60.0 * 60.0 * 1000000000.0), Duration(Int64(7) * 24 * 60 * 60 * 1000000000).inNanoseconds(), 1e-15) ;
        EXPECT_NEAR((100.0 * 365.0 * 24.0 * 60.0 * 60.0 * 1000000000.0), Duration(Int64(100) * 365 * 24 * 60 * 60 * 1000000000).inNanoseconds(), 1e-15) ;

    }

    {

        EXPECT_ANY_THROW(Duration::Undefined().inNanoseconds()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Duration, InMicroseconds)
{

    using ostk::core::types::Int64 ;
    using ostk::physics::time::Duration ;

    {

        EXPECT_NEAR(0.0, Duration(0).inMicroseconds(), 1e-15) ;

        EXPECT_NEAR(0.001, Duration(1).inMicroseconds(), 1e-15) ;
        EXPECT_NEAR(1.0, Duration(1000).inMicroseconds(), 1e-15) ;
        EXPECT_NEAR(1000.0, Duration(1000000).inMicroseconds(), 1e-15) ;
        EXPECT_NEAR(1000000.0, Duration(1000000000).inMicroseconds(), 1e-15) ;
        EXPECT_NEAR((60.0 * 1000000.0), Duration(Int64(60) * 1000000000).inMicroseconds(), 1e-15) ;
        EXPECT_NEAR((60.0 * 60.0 * 1000000.0), Duration(Int64(60) * 60 * 1000000000).inMicroseconds(), 1e-15) ;
        EXPECT_NEAR((24.0 * 60.0 * 60.0 * 1000000.0), Duration(Int64(24) * 60 * 60 * 1000000000).inMicroseconds(), 1e-15) ;
        EXPECT_NEAR((7.0 * 24.0 * 60.0 * 60.0 * 1000000.0), Duration(Int64(7) * 24 * 60 * 60 * 1000000000).inMicroseconds(), 1e-15) ;
        EXPECT_NEAR((100.0 * 365.0 * 24.0 * 60.0 * 60.0 * 1000000.0), Duration(Int64(100) * 365 * 24 * 60 * 60 * 1000000000).inMicroseconds(), 1e-15) ;

    }

    {

        EXPECT_ANY_THROW(Duration::Undefined().inMicroseconds()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Duration, InMilliseconds)
{

    using ostk::core::types::Int64 ;
    using ostk::physics::time::Duration ;

    {

        EXPECT_NEAR(0.0, Duration(0).inMilliseconds(), 1e-15) ;

        EXPECT_NEAR(0.000001, Duration(1).inMilliseconds(), 1e-15) ;
        EXPECT_NEAR(0.001, Duration(1000).inMilliseconds(), 1e-15) ;
        EXPECT_NEAR(1.0, Duration(1000000).inMilliseconds(), 1e-15) ;
        EXPECT_NEAR(1000.0, Duration(1000000000).inMilliseconds(), 1e-15) ;
        EXPECT_NEAR((60.0 * 1000.0), Duration(Int64(60) * 1000000000).inMilliseconds(), 1e-15) ;
        EXPECT_NEAR((60.0 * 60.0 * 1000.0), Duration(Int64(60) * 60 * 1000000000).inMilliseconds(), 1e-15) ;
        EXPECT_NEAR((24.0 * 60.0 * 60.0 * 1000.0), Duration(Int64(24) * 60 * 60 * 1000000000).inMilliseconds(), 1e-15) ;
        EXPECT_NEAR((7.0 * 24.0 * 60.0 * 60.0 * 1000.0), Duration(Int64(7) * 24 * 60 * 60 * 1000000000).inMilliseconds(), 1e-15) ;
        EXPECT_NEAR((100.0 * 365.0 * 24.0 * 60.0 * 60.0 * 1000.0), Duration(Int64(100) * 365 * 24 * 60 * 60 * 1000000000).inMilliseconds(), 1e-15) ;

    }

    {

        EXPECT_ANY_THROW(Duration::Undefined().inMilliseconds()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Duration, InSeconds)
{

    using ostk::core::types::Int64 ;
    using ostk::physics::time::Duration ;

    {

        EXPECT_NEAR(0.0, Duration(0).inSeconds(), 1e-15) ;

        EXPECT_NEAR(0.000000001, Duration(1).inSeconds(), 1e-15) ;
        EXPECT_NEAR(0.000001, Duration(1000).inSeconds(), 1e-15) ;
        EXPECT_NEAR(0.001, Duration(1000000).inSeconds(), 1e-15) ;
        EXPECT_NEAR(1.0, Duration(1000000000).inSeconds(), 1e-15) ;
        EXPECT_NEAR(60.0, Duration(Int64(60) * 1000000000).inSeconds(), 1e-15) ;
        EXPECT_NEAR((60.0 * 60.0), Duration(Int64(60) * 60 * 1000000000).inSeconds(), 1e-15) ;
        EXPECT_NEAR((24.0 * 60.0 * 60.0), Duration(Int64(24) * 60 * 60 * 1000000000).inSeconds(), 1e-15) ;
        EXPECT_NEAR((7.0 * 24.0 * 60.0 * 60.0), Duration(Int64(7) * 24 * 60 * 60 * 1000000000).inSeconds(), 1e-15) ;
        EXPECT_NEAR((100.0 * 365.0 * 24.0 * 60.0 * 60.0), Duration(Int64(100) * 365 * 24 * 60 * 60 * 1000000000).inSeconds(), 1e-15) ;

    }

    {

        EXPECT_ANY_THROW(Duration::Undefined().inSeconds()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Duration, InMinutes)
{

    using ostk::core::types::Int64 ;
    using ostk::physics::time::Duration ;

    {

        EXPECT_NEAR(0.0, Duration(0).inMinutes(), 1e-15) ;

        EXPECT_NEAR((0.000000001 / 60.0), Duration(1).inMinutes(), 1e-15) ;
        EXPECT_NEAR((0.000001 / 60.0), Duration(1000).inMinutes(), 1e-15) ;
        EXPECT_NEAR((0.001 / 60.0), Duration(1000000).inMinutes(), 1e-15) ;
        EXPECT_NEAR((1.0 / 60.0), Duration(1000000000).inMinutes(), 1e-15) ;
        EXPECT_NEAR(1.0, Duration(Int64(60) * 1000000000).inMinutes(), 1e-15) ;
        EXPECT_NEAR(60.0, Duration(Int64(60) * 60 * 1000000000).inMinutes(), 1e-15) ;
        EXPECT_NEAR((24.0 * 60.0), Duration(Int64(24) * 60 * 60 * 1000000000).inMinutes(), 1e-15) ;
        EXPECT_NEAR((7.0 * 24.0 * 60.0), Duration(Int64(7) * 24 * 60 * 60 * 1000000000).inMinutes(), 1e-15) ;
        EXPECT_NEAR((100.0 * 365.0 * 24.0 * 60.0), Duration(Int64(100) * 365 * 24 * 60 * 60 * 1000000000).inMinutes(), 1e-15) ;

    }

    {

        EXPECT_ANY_THROW(Duration::Undefined().inMinutes()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Duration, InHours)
{

    using ostk::core::types::Int64 ;
    using ostk::physics::time::Duration ;

    {

        EXPECT_NEAR(0.0, Duration(0).inHours(), 1e-15) ;

        EXPECT_NEAR((0.000000001 / 60.0 / 60.0), Duration(1).inHours(), 1e-15) ;
        EXPECT_NEAR((0.000001 / 60.0 / 60.0), Duration(1000).inHours(), 1e-15) ;
        EXPECT_NEAR((0.001 / 60.0 / 60.0), Duration(1000000).inHours(), 1e-15) ;
        EXPECT_NEAR((1.0 / 60.0 / 60.0), Duration(1000000000).inHours(), 1e-15) ;
        EXPECT_NEAR((1.0 / 60.0), Duration(Int64(60) * 1000000000).inHours(), 1e-15) ;
        EXPECT_NEAR(1.0, Duration(Int64(60) * 60 * 1000000000).inHours(), 1e-15) ;
        EXPECT_NEAR(24.0, Duration(Int64(24) * 60 * 60 * 1000000000).inHours(), 1e-15) ;
        EXPECT_NEAR((7.0 * 24.0), Duration(Int64(7) * 24 * 60 * 60 * 1000000000).inHours(), 1e-15) ;
        EXPECT_NEAR((100.0 * 365.0 * 24.0), Duration(Int64(100) * 365 * 24 * 60 * 60 * 1000000000).inHours(), 1e-15) ;

    }

    {

        EXPECT_ANY_THROW(Duration::Undefined().inHours()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Duration, InDays)
{

    using ostk::core::types::Int64 ;
    using ostk::physics::time::Duration ;

    {

        EXPECT_NEAR(0.0, Duration(0).inDays(), 1e-15) ;

        EXPECT_NEAR((0.000000001 / 60.0 / 60.0 / 24.0), Duration(1).inDays(), 1e-15) ;
        EXPECT_NEAR((0.000001 / 60.0 / 60.0 / 24.0), Duration(1000).inDays(), 1e-15) ;
        EXPECT_NEAR((0.001 / 60.0 / 60.0 / 24.0), Duration(1000000).inDays(), 1e-15) ;
        EXPECT_NEAR((1.0 / 60.0 / 60.0 / 24.0), Duration(1000000000).inDays(), 1e-15) ;
        EXPECT_NEAR((1.0 / 60.0 / 24.0), Duration(Int64(60) * 1000000000).inDays(), 1e-15) ;
        EXPECT_NEAR((1.0 / 24.0), Duration(Int64(60) * 60 * 1000000000).inDays(), 1e-15) ;
        EXPECT_NEAR(1.0, Duration(Int64(24) * 60 * 60 * 1000000000).inDays(), 1e-15) ;
        EXPECT_NEAR((7.0), Duration(Int64(7) * 24 * 60 * 60 * 1000000000).inDays(), 1e-15) ;
        EXPECT_NEAR((100.0 * 365.0), Duration(Int64(100) * 365 * 24 * 60 * 60 * 1000000000).inDays(), 1e-15) ;

    }

    {

        EXPECT_ANY_THROW(Duration::Undefined().inDays()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Duration, InWeeks)
{

    using ostk::core::types::Int64 ;
    using ostk::physics::time::Duration ;

    {

        EXPECT_NEAR(0.0, Duration(0).inWeeks(), 1e-15) ;

        EXPECT_NEAR((0.000000001 / 60.0 / 60.0 / 24.0 / 7.0), Duration(1).inWeeks(), 1e-15) ;
        EXPECT_NEAR((0.000001 / 60.0 / 60.0 / 24.0 / 7.0), Duration(1000).inWeeks(), 1e-15) ;
        EXPECT_NEAR((0.001 / 60.0 / 60.0 / 24.0 / 7.0), Duration(1000000).inWeeks(), 1e-15) ;
        EXPECT_NEAR((1.0 / 60.0 / 60.0 / 24.0 / 7.0), Duration(1000000000).inWeeks(), 1e-15) ;
        EXPECT_NEAR((1.0 / 60.0 / 24.0 / 7.0), Duration(Int64(60) * 1000000000).inWeeks(), 1e-15) ;
        EXPECT_NEAR((1.0 / 24.0 / 7.0), Duration(Int64(60) * 60 * 1000000000).inWeeks(), 1e-15) ;
        EXPECT_NEAR((1.0 / 7.0), Duration(Int64(24) * 60 * 60 * 1000000000).inWeeks(), 1e-15) ;
        EXPECT_NEAR(1.0, Duration(Int64(7) * 24 * 60 * 60 * 1000000000).inWeeks(), 1e-15) ;
        EXPECT_NEAR((100.0 * 365.0 / 7.0), Duration(Int64(100) * 365 * 24 * 60 * 60 * 1000000000).inWeeks(), 1e-15) ;

    }

    {

        EXPECT_ANY_THROW(Duration::Undefined().inWeeks()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Duration, In)
{

    using ostk::core::types::Int64 ;
    using ostk::physics::units::Time ;
    using ostk::physics::time::Duration ;

    {

        EXPECT_NEAR((100.0 * 365.0 * 24.0 * 60.0 * 60.0 * 1000000000.0), Duration(Int64(100) * 365 * 24 * 60 * 60 * 1000000000).in(Time::Unit::Nanosecond), 1e-15) ;
        EXPECT_NEAR((100.0 * 365.0 * 24.0 * 60.0 * 60.0 * 1000000.0), Duration(Int64(100) * 365 * 24 * 60 * 60 * 1000000000).in(Time::Unit::Microsecond), 1e-15) ;
        EXPECT_NEAR((100.0 * 365.0 * 24.0 * 60.0 * 60.0 * 1000.0), Duration(Int64(100) * 365 * 24 * 60 * 60 * 1000000000).in(Time::Unit::Millisecond), 1e-15) ;
        EXPECT_NEAR((100.0 * 365.0 * 24.0 * 60.0 * 60.0), Duration(Int64(100) * 365 * 24 * 60 * 60 * 1000000000).in(Time::Unit::Second), 1e-15) ;
        EXPECT_NEAR((100.0 * 365.0 * 24.0 * 60.0), Duration(Int64(100) * 365 * 24 * 60 * 60 * 1000000000).in(Time::Unit::Minute), 1e-15) ;
        EXPECT_NEAR((100.0 * 365.0 * 24.0), Duration(Int64(100) * 365 * 24 * 60 * 60 * 1000000000).in(Time::Unit::Hour), 1e-15) ;
        EXPECT_NEAR((100.0 * 365.0), Duration(Int64(100) * 365 * 24 * 60 * 60 * 1000000000).in(Time::Unit::Day), 1e-15) ;
        EXPECT_NEAR((100.0 * 365.0 / 7.0), Duration(Int64(100) * 365 * 24 * 60 * 60 * 1000000000).in(Time::Unit::Week), 1e-15) ;

    }

    {

        EXPECT_ANY_THROW(Duration::Undefined().in(Time::Unit::Nanosecond)) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Duration, GetAbsolute)
{

    using ostk::physics::time::Duration ;

    {

        EXPECT_EQ(Duration(0), Duration(0).getAbsolute()) ;
        EXPECT_EQ(Duration(+1), Duration(+1).getAbsolute()) ;
        EXPECT_EQ(Duration(+1), Duration(-1).getAbsolute()) ;

    }

    {

        EXPECT_ANY_THROW(Duration::Undefined().getAbsolute()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Duration, ToString)
{

    using ostk::physics::time::Duration ;

    // Standard

    {

        EXPECT_EQ("00.000.000.000", Duration::Zero().toString(Duration::Format::Standard)) ;

        EXPECT_EQ("00.000.000.001", Duration::Nanoseconds(+1.0).toString(Duration::Format::Standard)) ;
        EXPECT_EQ("00.000.000.012", Duration::Nanoseconds(+12.0).toString(Duration::Format::Standard)) ;
        EXPECT_EQ("00.000.000.123", Duration::Nanoseconds(+123.0).toString(Duration::Format::Standard)) ;

        EXPECT_EQ("00.000.001.000", Duration::Microseconds(+1.0).toString(Duration::Format::Standard)) ;
        EXPECT_EQ("00.000.012.000", Duration::Microseconds(+12.0).toString(Duration::Format::Standard)) ;
        EXPECT_EQ("00.000.123.000", Duration::Microseconds(+123.0).toString(Duration::Format::Standard)) ;

        EXPECT_EQ("00.001.000.000", Duration::Milliseconds(+1.0).toString(Duration::Format::Standard)) ;
        EXPECT_EQ("00.012.000.000", Duration::Milliseconds(+12.0).toString(Duration::Format::Standard)) ;
        EXPECT_EQ("00.123.000.000", Duration::Milliseconds(+123.0).toString(Duration::Format::Standard)) ;

        EXPECT_EQ("01.000.000.000", Duration::Seconds(+1.0).toString(Duration::Format::Standard)) ;
        EXPECT_EQ("12.000.000.000", Duration::Seconds(+12.0).toString(Duration::Format::Standard)) ;

        EXPECT_EQ("01:02.000.000.000", (Duration::Minutes(+1.0) + Duration::Seconds(+2.0)).toString(Duration::Format::Standard)) ;
        EXPECT_EQ("12:34.000.000.000", (Duration::Minutes(+12.0) + Duration::Seconds(+34.0)).toString(Duration::Format::Standard)) ;

        EXPECT_EQ("01:02:03.000.000.000", (Duration::Hours(+1.0) + Duration::Minutes(+2.0) + Duration::Seconds(+3.0)).toString(Duration::Format::Standard)) ;
        EXPECT_EQ("12:34:56.000.000.000", (Duration::Hours(+12.0) + Duration::Minutes(+34.0) + Duration::Seconds(+56.0)).toString(Duration::Format::Standard)) ;

        EXPECT_EQ("1 01:02:03.000.000.000", (Duration::Days(+1.0) + Duration::Hours(+1.0) + Duration::Minutes(+2.0) + Duration::Seconds(+3.0)).toString(Duration::Format::Standard)) ;
        EXPECT_EQ("3 12:34:56.000.000.000", (Duration::Days(+3.0) + Duration::Hours(+12.0) + Duration::Minutes(+34.0) + Duration::Seconds(+56.0)).toString(Duration::Format::Standard)) ;
        EXPECT_EQ("7 12:34:56.000.000.000", (Duration::Days(+7.0) + Duration::Hours(+12.0) + Duration::Minutes(+34.0) + Duration::Seconds(+56.0)).toString(Duration::Format::Standard)) ;
        EXPECT_EQ("14 12:34:56.000.000.000", (Duration::Days(+14.0) + Duration::Hours(+12.0) + Duration::Minutes(+34.0) + Duration::Seconds(+56.0)).toString(Duration::Format::Standard)) ;
        EXPECT_EQ("99 12:34:56.000.000.000", (Duration::Days(+99.0) + Duration::Hours(+12.0) + Duration::Minutes(+34.0) + Duration::Seconds(+56.0)).toString(Duration::Format::Standard)) ;

        EXPECT_EQ("1 01:02:03.123.456.789", (Duration::Days(+1.0) + Duration::Hours(+1.0) + Duration::Minutes(+2.0) + Duration::Seconds(+3.0) + Duration::Milliseconds(+123.0) + Duration::Microseconds(+456.0) + Duration::Nanoseconds(+789.0)).toString(Duration::Format::Standard)) ;

        EXPECT_EQ("-00.000.000.001", Duration::Nanoseconds(-1.0).toString(Duration::Format::Standard)) ;
        EXPECT_EQ("-00.000.000.012", Duration::Nanoseconds(-12.0).toString(Duration::Format::Standard)) ;
        EXPECT_EQ("-00.000.000.123", Duration::Nanoseconds(-123.0).toString(Duration::Format::Standard)) ;

        EXPECT_EQ("-00.000.001.000", Duration::Microseconds(-1.0).toString(Duration::Format::Standard)) ;
        EXPECT_EQ("-00.000.012.000", Duration::Microseconds(-12.0).toString(Duration::Format::Standard)) ;
        EXPECT_EQ("-00.000.123.000", Duration::Microseconds(-123.0).toString(Duration::Format::Standard)) ;

        EXPECT_EQ("-00.001.000.000", Duration::Milliseconds(-1.0).toString(Duration::Format::Standard)) ;
        EXPECT_EQ("-00.012.000.000", Duration::Milliseconds(-12.0).toString(Duration::Format::Standard)) ;
        EXPECT_EQ("-00.123.000.000", Duration::Milliseconds(-123.0).toString(Duration::Format::Standard)) ;

        EXPECT_EQ("-01.000.000.000", (-Duration::Seconds(+1.0)).toString(Duration::Format::Standard)) ;
        EXPECT_EQ("-12.000.000.000", (-Duration::Seconds(+12.0)).toString(Duration::Format::Standard)) ;

        EXPECT_EQ("-01:02.000.000.000", (-(Duration::Minutes(+1.0) + Duration::Seconds(+2.0))).toString(Duration::Format::Standard)) ;
        EXPECT_EQ("-12:34.000.000.000", (-(Duration::Minutes(+12.0) + Duration::Seconds(+34.0))).toString(Duration::Format::Standard)) ;

        EXPECT_EQ("-01:02:03.000.000.000", (-(Duration::Hours(+1.0) + Duration::Minutes(+2.0) + Duration::Seconds(+3.0))).toString(Duration::Format::Standard)) ;
        EXPECT_EQ("-12:34:56.000.000.000", (-(Duration::Hours(+12.0) + Duration::Minutes(+34.0) + Duration::Seconds(+56.0))).toString(Duration::Format::Standard)) ;

        EXPECT_EQ("-1 01:02:03.000.000.000", (-(Duration::Days(+1.0) + Duration::Hours(+1.0) + Duration::Minutes(+2.0) + Duration::Seconds(+3.0))).toString(Duration::Format::Standard)) ;
        EXPECT_EQ("-3 12:34:56.000.000.000", (-(Duration::Days(+3.0) + Duration::Hours(+12.0) + Duration::Minutes(+34.0) + Duration::Seconds(+56.0))).toString(Duration::Format::Standard)) ;
        EXPECT_EQ("-7 12:34:56.000.000.000", (-(Duration::Days(+7.0) + Duration::Hours(+12.0) + Duration::Minutes(+34.0) + Duration::Seconds(+56.0))).toString(Duration::Format::Standard)) ;
        EXPECT_EQ("-14 12:34:56.000.000.000", (-(Duration::Days(+14.0) + Duration::Hours(+12.0) + Duration::Minutes(+34.0) + Duration::Seconds(+56.0))).toString(Duration::Format::Standard)) ;
        EXPECT_EQ("-99 12:34:56.000.000.000", (-(Duration::Days(+99.0) + Duration::Hours(+12.0) + Duration::Minutes(+34.0) + Duration::Seconds(+56.0))).toString(Duration::Format::Standard)) ;

        EXPECT_EQ("-1 01:02:03.123.456.789", (-(Duration::Days(+1.0) + Duration::Hours(+1.0) + Duration::Minutes(+2.0) + Duration::Seconds(+3.0) + Duration::Milliseconds(+123.0) + Duration::Microseconds(+456.0) + Duration::Nanoseconds(+789.0))).toString(Duration::Format::Standard)) ;

    }

    // ISO 8601

    {

        EXPECT_EQ("PT0H0M0S", Duration::Zero().toString(Duration::Format::ISO8601)) ;

        EXPECT_EQ("PT0.000000001S", Duration::Nanoseconds(+1.0).toString(Duration::Format::ISO8601)) ;
        EXPECT_EQ("PT0.00000001S", Duration::Nanoseconds(+10.0).toString(Duration::Format::ISO8601)) ;
        EXPECT_EQ("PT0.0000001S", Duration::Nanoseconds(+100.0).toString(Duration::Format::ISO8601)) ;
        EXPECT_EQ("PT0.000000012S", Duration::Nanoseconds(+12.0).toString(Duration::Format::ISO8601)) ;
        EXPECT_EQ("PT0.000000123S", Duration::Nanoseconds(+123.0).toString(Duration::Format::ISO8601)) ;

        EXPECT_EQ("PT0.000001S", Duration::Microseconds(+1.0).toString(Duration::Format::ISO8601)) ;
        EXPECT_EQ("PT0.00001S", Duration::Microseconds(+10.0).toString(Duration::Format::ISO8601)) ;
        EXPECT_EQ("PT0.0001S", Duration::Microseconds(+100.0).toString(Duration::Format::ISO8601)) ;
        EXPECT_EQ("PT0.000012S", Duration::Microseconds(+12.0).toString(Duration::Format::ISO8601)) ;
        EXPECT_EQ("PT0.000123S", Duration::Microseconds(+123.0).toString(Duration::Format::ISO8601)) ;

        EXPECT_EQ("PT0.001S", Duration::Milliseconds(+1.0).toString(Duration::Format::ISO8601)) ;
        EXPECT_EQ("PT0.01S", Duration::Milliseconds(+10.0).toString(Duration::Format::ISO8601)) ;
        EXPECT_EQ("PT0.1S", Duration::Milliseconds(+100.0).toString(Duration::Format::ISO8601)) ;
        EXPECT_EQ("PT0.012S", Duration::Milliseconds(+12.0).toString(Duration::Format::ISO8601)) ;
        EXPECT_EQ("PT0.123S", Duration::Milliseconds(+123.0).toString(Duration::Format::ISO8601)) ;

        EXPECT_EQ("PT1S", Duration::Seconds(+1.0).toString(Duration::Format::ISO8601)) ;
        EXPECT_EQ("PT12S", Duration::Seconds(+12.0).toString(Duration::Format::ISO8601)) ;

        EXPECT_EQ("PT1M2S", (Duration::Minutes(+1.0) + Duration::Seconds(+2.0)).toString(Duration::Format::ISO8601)) ;
        EXPECT_EQ("PT12M34S", (Duration::Minutes(+12.0) + Duration::Seconds(+34.0)).toString(Duration::Format::ISO8601)) ;

        EXPECT_EQ("PT1H2M3S", (Duration::Hours(+1.0) + Duration::Minutes(+2.0) + Duration::Seconds(+3.0)).toString(Duration::Format::ISO8601)) ;
        EXPECT_EQ("PT12H34M56S", (Duration::Hours(+12.0) + Duration::Minutes(+34.0) + Duration::Seconds(+56.0)).toString(Duration::Format::ISO8601)) ;

        EXPECT_EQ("P1D", (Duration::Days(+1.0)).toString(Duration::Format::ISO8601)) ;
        EXPECT_EQ("P1DT1H", (Duration::Days(+1.0) + Duration::Hours(+1.0)).toString(Duration::Format::ISO8601)) ;
        EXPECT_EQ("P1DT1H2M", (Duration::Days(+1.0) + Duration::Hours(+1.0) + Duration::Minutes(+2.0)).toString(Duration::Format::ISO8601)) ;
        EXPECT_EQ("P1DT1H2M3S", (Duration::Days(+1.0) + Duration::Hours(+1.0) + Duration::Minutes(+2.0) + Duration::Seconds(+3.0)).toString(Duration::Format::ISO8601)) ;
        EXPECT_EQ("P3DT12H34M56S", (Duration::Days(+3.0) + Duration::Hours(+12.0) + Duration::Minutes(+34.0) + Duration::Seconds(+56.0)).toString(Duration::Format::ISO8601)) ;
        EXPECT_EQ("P7DT12H34M56S", (Duration::Days(+7.0) + Duration::Hours(+12.0) + Duration::Minutes(+34.0) + Duration::Seconds(+56.0)).toString(Duration::Format::ISO8601)) ;
        EXPECT_EQ("P14DT12H34M56S", (Duration::Days(+14.0) + Duration::Hours(+12.0) + Duration::Minutes(+34.0) + Duration::Seconds(+56.0)).toString(Duration::Format::ISO8601)) ;
        EXPECT_EQ("P99DT12H34M56S", (Duration::Days(+99.0) + Duration::Hours(+12.0) + Duration::Minutes(+34.0) + Duration::Seconds(+56.0)).toString(Duration::Format::ISO8601)) ;

        EXPECT_EQ("P1DT1H2M3.123456789S", (Duration::Days(+1.0) + Duration::Hours(+1.0) + Duration::Minutes(+2.0) + Duration::Seconds(+3.0) + Duration::Milliseconds(+123.0) + Duration::Microseconds(+456.0) + Duration::Nanoseconds(+789.0)).toString(Duration::Format::ISO8601)) ;

        EXPECT_EQ("-PT0.000000001S", Duration::Nanoseconds(-1.0).toString(Duration::Format::ISO8601)) ;
        EXPECT_EQ("-PT0.00000001S", Duration::Nanoseconds(-10.0).toString(Duration::Format::ISO8601)) ;
        EXPECT_EQ("-PT0.0000001S", Duration::Nanoseconds(-100.0).toString(Duration::Format::ISO8601)) ;
        EXPECT_EQ("-PT0.000000012S", Duration::Nanoseconds(-12.0).toString(Duration::Format::ISO8601)) ;
        EXPECT_EQ("-PT0.000000123S", Duration::Nanoseconds(-123.0).toString(Duration::Format::ISO8601)) ;

        EXPECT_EQ("-PT0.000001S", Duration::Microseconds(-1.0).toString(Duration::Format::ISO8601)) ;
        EXPECT_EQ("-PT0.00001S", Duration::Microseconds(-10.0).toString(Duration::Format::ISO8601)) ;
        EXPECT_EQ("-PT0.0001S", Duration::Microseconds(-100.0).toString(Duration::Format::ISO8601)) ;
        EXPECT_EQ("-PT0.000012S", Duration::Microseconds(-12.0).toString(Duration::Format::ISO8601)) ;
        EXPECT_EQ("-PT0.000123S", Duration::Microseconds(-123.0).toString(Duration::Format::ISO8601)) ;

        EXPECT_EQ("-PT0.001S", Duration::Milliseconds(-1.0).toString(Duration::Format::ISO8601)) ;
        EXPECT_EQ("-PT0.01S", Duration::Milliseconds(-10.0).toString(Duration::Format::ISO8601)) ;
        EXPECT_EQ("-PT0.1S", Duration::Milliseconds(-100.0).toString(Duration::Format::ISO8601)) ;
        EXPECT_EQ("-PT0.012S", Duration::Milliseconds(-12.0).toString(Duration::Format::ISO8601)) ;
        EXPECT_EQ("-PT0.123S", Duration::Milliseconds(-123.0).toString(Duration::Format::ISO8601)) ;

        EXPECT_EQ("-PT1S", Duration::Seconds(-1.0).toString(Duration::Format::ISO8601)) ;
        EXPECT_EQ("-PT12S", Duration::Seconds(-12.0).toString(Duration::Format::ISO8601)) ;

        EXPECT_EQ("-PT1M2S", (-(Duration::Minutes(+1.0) + Duration::Seconds(+2.0))).toString(Duration::Format::ISO8601)) ;
        EXPECT_EQ("-PT12M34S", (-(Duration::Minutes(+12.0) + Duration::Seconds(+34.0))).toString(Duration::Format::ISO8601)) ;

        EXPECT_EQ("-PT1H2M3S", (-(Duration::Hours(+1.0) + Duration::Minutes(+2.0) + Duration::Seconds(+3.0))).toString(Duration::Format::ISO8601)) ;
        EXPECT_EQ("-PT12H34M56S", (-(Duration::Hours(+12.0) + Duration::Minutes(+34.0) + Duration::Seconds(+56.0))).toString(Duration::Format::ISO8601)) ;

        EXPECT_EQ("-P1D", (-(Duration::Days(+1.0))).toString(Duration::Format::ISO8601)) ;
        EXPECT_EQ("-P1DT1H", (-(Duration::Days(+1.0) + Duration::Hours(+1.0))).toString(Duration::Format::ISO8601)) ;
        EXPECT_EQ("-P1DT1H2M", (-(Duration::Days(+1.0) + Duration::Hours(+1.0) + Duration::Minutes(+2.0))).toString(Duration::Format::ISO8601)) ;
        EXPECT_EQ("-P1DT1H2M3S", (-(Duration::Days(+1.0) + Duration::Hours(+1.0) + Duration::Minutes(+2.0) + Duration::Seconds(+3.0))).toString(Duration::Format::ISO8601)) ;
        EXPECT_EQ("-P3DT12H34M56S", (-(Duration::Days(+3.0) + Duration::Hours(+12.0) + Duration::Minutes(+34.0) + Duration::Seconds(+56.0))).toString(Duration::Format::ISO8601)) ;
        EXPECT_EQ("-P7DT12H34M56S", (-(Duration::Days(+7.0) + Duration::Hours(+12.0) + Duration::Minutes(+34.0) + Duration::Seconds(+56.0))).toString(Duration::Format::ISO8601)) ;
        EXPECT_EQ("-P14DT12H34M56S", (-(Duration::Days(+14.0) + Duration::Hours(+12.0) + Duration::Minutes(+34.0) + Duration::Seconds(+56.0))).toString(Duration::Format::ISO8601)) ;
        EXPECT_EQ("-P99DT12H34M56S", (-(Duration::Days(+99.0) + Duration::Hours(+12.0) + Duration::Minutes(+34.0) + Duration::Seconds(+56.0))).toString(Duration::Format::ISO8601)) ;

        EXPECT_EQ("-P1DT1H2M3.123456789S", (-(Duration::Days(+1.0) + Duration::Hours(+1.0) + Duration::Minutes(+2.0) + Duration::Seconds(+3.0) + Duration::Milliseconds(+123.0) + Duration::Microseconds(+456.0) + Duration::Nanoseconds(+789.0))).toString(Duration::Format::ISO8601)) ;

    }

    {

        EXPECT_ANY_THROW(Duration::Undefined().toString(Duration::Format::Standard)) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Duration, Undefined)
{

    using ostk::physics::time::Duration ;

    {

        EXPECT_NO_THROW(Duration::Undefined()) ;
        EXPECT_FALSE(Duration::Undefined().isDefined()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Duration, Zero)
{

    using ostk::physics::time::Duration ;

    {

        EXPECT_NO_THROW(Duration::Zero()) ;
        EXPECT_TRUE(Duration::Zero().isDefined()) ;

        EXPECT_EQ(Duration(0), Duration::Zero()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Duration, Nanoseconds)
{

    using ostk::physics::time::Duration ;

    {

        EXPECT_NO_THROW(Duration::Nanoseconds(0)) ;
        EXPECT_TRUE(Duration::Nanoseconds(0).isDefined()) ;

        EXPECT_EQ(Duration(0), Duration::Nanoseconds(0)) ;
        EXPECT_EQ(Duration(123), Duration::Nanoseconds(123)) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Duration, Microseconds)
{

    using ostk::physics::time::Duration ;

    {

        EXPECT_NO_THROW(Duration::Microseconds(0)) ;
        EXPECT_TRUE(Duration::Microseconds(0).isDefined()) ;

        EXPECT_EQ(Duration(0), Duration::Microseconds(0)) ;
        EXPECT_EQ(Duration(123 * 1e3), Duration::Microseconds(123)) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Duration, Milliseconds)
{

    using ostk::physics::time::Duration ;

    {

        EXPECT_NO_THROW(Duration::Milliseconds(0)) ;
        EXPECT_TRUE(Duration::Milliseconds(0).isDefined()) ;

        EXPECT_EQ(Duration(0), Duration::Milliseconds(0)) ;
        EXPECT_EQ(Duration(123 * 1e6), Duration::Milliseconds(123)) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Duration, Seconds)
{

    using ostk::physics::time::Duration ;

    {

        EXPECT_NO_THROW(Duration::Seconds(0)) ;
        EXPECT_TRUE(Duration::Seconds(0).isDefined()) ;

        EXPECT_EQ(Duration(0), Duration::Seconds(0)) ;
        EXPECT_EQ(Duration(123 * 1e9), Duration::Seconds(123)) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Duration, Minutes)
{

    using ostk::physics::time::Duration ;

    {

        EXPECT_NO_THROW(Duration::Minutes(0)) ;
        EXPECT_TRUE(Duration::Minutes(0).isDefined()) ;

        EXPECT_EQ(Duration(0), Duration::Minutes(0)) ;
        EXPECT_EQ(Duration(123 * 60 * 1e9), Duration::Minutes(123)) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Duration, Hours)
{

    using ostk::physics::time::Duration ;

    {

        EXPECT_NO_THROW(Duration::Hours(0)) ;
        EXPECT_TRUE(Duration::Hours(0).isDefined()) ;

        EXPECT_EQ(Duration(0), Duration::Hours(0)) ;
        EXPECT_EQ(Duration(123 * 60 * 60 * 1e9), Duration::Hours(123)) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Duration, Days)
{

    using ostk::physics::time::Duration ;

    {

        EXPECT_NO_THROW(Duration::Days(0)) ;
        EXPECT_TRUE(Duration::Days(0).isDefined()) ;

        EXPECT_EQ(Duration(0), Duration::Days(0)) ;
        EXPECT_EQ(Duration(123 * 24 * 60 * 60 * 1e9), Duration::Days(123)) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Duration, Weeks)
{

    using ostk::physics::time::Duration ;

    {

        EXPECT_NO_THROW(Duration::Weeks(0)) ;
        EXPECT_TRUE(Duration::Weeks(0).isDefined()) ;

        EXPECT_EQ(Duration(0), Duration::Weeks(0)) ;
        EXPECT_EQ(Duration(123 * 7 * 24 * 60 * 60 * 1e9), Duration::Weeks(123)) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Duration, Between)
{

    using ostk::physics::time::Scale ;
    using ostk::physics::time::DateTime ;
    using ostk::physics::time::Instant ;
    using ostk::physics::time::Duration ;

    {

        for (const auto year : { 1981, 2000, 2030 })
        {

            for (const auto month : { 1, 6, 12 })
            {

                for (const auto day : { 1, 20, 28 })
                {

                    for (const auto scale : { Scale::TT, Scale::TAI, Scale::UTC, Scale::GPST })
                    {

                        EXPECT_EQ(Duration::Zero(), Duration::Between(Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale))) ;

                        EXPECT_EQ(Duration::Nanoseconds(-1), Duration::Between(Instant::DateTime(DateTime(year, month, day, 12, 0, 0, 0, 0, 1), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale))) ;
                        EXPECT_EQ(Duration::Nanoseconds(+1), Duration::Between(Instant::DateTime(DateTime(year, month, day, 11, 59, 59, 999, 999, 999), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale))) ;

                        EXPECT_EQ(Duration::Microseconds(-1), Duration::Between(Instant::DateTime(DateTime(year, month, day, 12, 0, 0, 0, 1), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale))) ;
                        EXPECT_EQ(Duration::Microseconds(+1), Duration::Between(Instant::DateTime(DateTime(year, month, day, 11, 59, 59, 999, 999), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale))) ;

                        EXPECT_EQ(Duration::Milliseconds(-1), Duration::Between(Instant::DateTime(DateTime(year, month, day, 12, 0, 0, 1), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale))) ;
                        EXPECT_EQ(Duration::Milliseconds(+1), Duration::Between(Instant::DateTime(DateTime(year, month, day, 11, 59, 59, 999), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale))) ;

                        EXPECT_EQ(Duration::Seconds(-1), Duration::Between(Instant::DateTime(DateTime(year, month, day, 12, 0, 1), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale))) ;
                        EXPECT_EQ(Duration::Seconds(+1), Duration::Between(Instant::DateTime(DateTime(year, month, day, 11, 59, 59), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale))) ;

                        EXPECT_EQ(Duration::Minutes(-1), Duration::Between(Instant::DateTime(DateTime(year, month, day, 12, 1, 0), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale))) ;
                        EXPECT_EQ(Duration::Minutes(+1), Duration::Between(Instant::DateTime(DateTime(year, month, day, 11, 59, 0), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale))) ;

                        EXPECT_EQ(Duration::Hours(-1), Duration::Between(Instant::DateTime(DateTime(year, month, day, 13, 0, 0), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale))) ;
                        EXPECT_EQ(Duration::Hours(+1), Duration::Between(Instant::DateTime(DateTime(year, month, day, 11, 0, 0), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale))) ;

                        EXPECT_EQ(Duration::Nanoseconds(+1), Duration::Between(Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0, 0, 0, 1), scale))) ;
                        EXPECT_EQ(Duration::Nanoseconds(-1), Duration::Between(Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale), Instant::DateTime(DateTime(year, month, day, 11, 59, 59, 999, 999, 999), scale))) ;

                        EXPECT_EQ(Duration::Microseconds(+1), Duration::Between(Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0, 0, 1), scale))) ;
                        EXPECT_EQ(Duration::Microseconds(-1), Duration::Between(Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale), Instant::DateTime(DateTime(year, month, day, 11, 59, 59, 999, 999), scale))) ;

                        EXPECT_EQ(Duration::Milliseconds(+1), Duration::Between(Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 0, 1), scale))) ;
                        EXPECT_EQ(Duration::Milliseconds(-1), Duration::Between(Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale), Instant::DateTime(DateTime(year, month, day, 11, 59, 59, 999), scale))) ;

                        EXPECT_EQ(Duration::Seconds(+1), Duration::Between(Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale), Instant::DateTime(DateTime(year, month, day, 12, 0, 1), scale))) ;
                        EXPECT_EQ(Duration::Seconds(-1), Duration::Between(Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale), Instant::DateTime(DateTime(year, month, day, 11, 59, 59), scale))) ;

                        EXPECT_EQ(Duration::Minutes(+1), Duration::Between(Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale), Instant::DateTime(DateTime(year, month, day, 12, 1, 0), scale))) ;
                        EXPECT_EQ(Duration::Minutes(-1), Duration::Between(Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale), Instant::DateTime(DateTime(year, month, day, 11, 59, 0), scale))) ;

                        EXPECT_EQ(Duration::Hours(+1), Duration::Between(Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale), Instant::DateTime(DateTime(year, month, day, 13, 0, 0), scale))) ;
                        EXPECT_EQ(Duration::Hours(-1), Duration::Between(Instant::DateTime(DateTime(year, month, day, 12, 0, 0), scale), Instant::DateTime(DateTime(year, month, day, 11, 0, 0), scale))) ;

                    }

                }

            }

        }

    }

    {

        EXPECT_ANY_THROW(Duration::Between(Instant::Undefined(), Instant::Undefined())) ;
        EXPECT_ANY_THROW(Duration::Between(Instant::DateTime(DateTime(2000, 1, 1, 0, 0, 0), Scale::UTC), Instant::Undefined())) ;
        EXPECT_ANY_THROW(Duration::Between(Instant::Undefined(), Instant::DateTime(DateTime(2000, 1, 1, 0, 0, 0), Scale::UTC))) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Time_Duration, Parse)
{

    using ostk::physics::time::Duration ;

    // Undefined (automatic format detection)

    {

        EXPECT_EQ(Duration::Zero(), Duration::Parse("00.000.000.000")) ;
        EXPECT_EQ(Duration::Zero(), Duration::Parse("PT0H0M0S")) ;

    }

    // Standard

    {

        EXPECT_EQ(Duration::Zero(), Duration::Parse("00.000.000.000", Duration::Format::Standard)) ;

        EXPECT_EQ(Duration::Nanoseconds(+1.0), Duration::Parse("00.000.000.001", Duration::Format::Standard)) ;
        EXPECT_EQ(Duration::Nanoseconds(+12.0), Duration::Parse("00.000.000.012", Duration::Format::Standard)) ;
        EXPECT_EQ(Duration::Nanoseconds(+123.0), Duration::Parse("00.000.000.123", Duration::Format::Standard)) ;

        EXPECT_EQ(Duration::Microseconds(+1.0), Duration::Parse("00.000.001.000", Duration::Format::Standard)) ;
        EXPECT_EQ(Duration::Microseconds(+12.0), Duration::Parse("00.000.012.000", Duration::Format::Standard)) ;
        EXPECT_EQ(Duration::Microseconds(+123.0), Duration::Parse("00.000.123.000", Duration::Format::Standard)) ;

        EXPECT_EQ(Duration::Milliseconds(+1.0), Duration::Parse("00.001.000.000", Duration::Format::Standard)) ;
        EXPECT_EQ(Duration::Milliseconds(+12.0), Duration::Parse("00.012.000.000", Duration::Format::Standard)) ;
        EXPECT_EQ(Duration::Milliseconds(+123.0), Duration::Parse("00.123.000.000", Duration::Format::Standard)) ;

        EXPECT_EQ(Duration::Seconds(+1.0), Duration::Parse("01.000.000.000", Duration::Format::Standard)) ;
        EXPECT_EQ(Duration::Seconds(+12.0), Duration::Parse("12.000.000.000", Duration::Format::Standard)) ;

        EXPECT_EQ((Duration::Minutes(+1.0) + Duration::Seconds(+2.0)), Duration::Parse("01:02.000.000.000", Duration::Format::Standard)) ;
        EXPECT_EQ((Duration::Minutes(+12.0) + Duration::Seconds(+34.0)), Duration::Parse("12:34.000.000.000", Duration::Format::Standard)) ;

        EXPECT_EQ((Duration::Hours(+1.0) + Duration::Minutes(+2.0) + Duration::Seconds(+3.0)), Duration::Parse("01:02:03.000.000.000", Duration::Format::Standard)) ;
        EXPECT_EQ((Duration::Hours(+12.0) + Duration::Minutes(+34.0) + Duration::Seconds(+56.0)), Duration::Parse("12:34:56.000.000.000", Duration::Format::Standard)) ;

        EXPECT_EQ((Duration::Days(+1.0) + Duration::Hours(+1.0) + Duration::Minutes(+2.0) + Duration::Seconds(+3.0)), Duration::Parse("1 01:02:03.000.000.000", Duration::Format::Standard)) ;
        EXPECT_EQ((Duration::Days(+3.0) + Duration::Hours(+12.0) + Duration::Minutes(+34.0) + Duration::Seconds(+56.0)), Duration::Parse("3 12:34:56.000.000.000", Duration::Format::Standard)) ;
        EXPECT_EQ((Duration::Days(+7.0) + Duration::Hours(+12.0) + Duration::Minutes(+34.0) + Duration::Seconds(+56.0)), Duration::Parse("7 12:34:56.000.000.000", Duration::Format::Standard)) ;
        EXPECT_EQ((Duration::Days(+14.0) + Duration::Hours(+12.0) + Duration::Minutes(+34.0) + Duration::Seconds(+56.0)), Duration::Parse("14 12:34:56.000.000.000", Duration::Format::Standard)) ;
        EXPECT_EQ((Duration::Days(+99.0) + Duration::Hours(+12.0) + Duration::Minutes(+34.0) + Duration::Seconds(+56.0)), Duration::Parse("99 12:34:56.000.000.000", Duration::Format::Standard)) ;

        EXPECT_EQ((Duration::Days(+1.0) + Duration::Hours(+1.0) + Duration::Minutes(+2.0) + Duration::Seconds(+3.0) + Duration::Milliseconds(+123.0) + Duration::Microseconds(+456.0) + Duration::Nanoseconds(+789.0)), Duration::Parse("1 01:02:03.123.456.789", Duration::Format::Standard)) ;

        EXPECT_EQ(Duration::Nanoseconds(-1.0), Duration::Parse("-00.000.000.001", Duration::Format::Standard)) ;
        EXPECT_EQ(Duration::Nanoseconds(-12.0), Duration::Parse("-00.000.000.012", Duration::Format::Standard)) ;
        EXPECT_EQ(Duration::Nanoseconds(-123.0), Duration::Parse("-00.000.000.123", Duration::Format::Standard)) ;

        EXPECT_EQ(Duration::Microseconds(-1.0), Duration::Parse("-00.000.001.000", Duration::Format::Standard)) ;
        EXPECT_EQ(Duration::Microseconds(-12.0), Duration::Parse("-00.000.012.000", Duration::Format::Standard)) ;
        EXPECT_EQ(Duration::Microseconds(-123.0), Duration::Parse("-00.000.123.000", Duration::Format::Standard)) ;

        EXPECT_EQ(Duration::Milliseconds(-1.0), Duration::Parse("-00.001.000.000", Duration::Format::Standard)) ;
        EXPECT_EQ(Duration::Milliseconds(-12.0), Duration::Parse("-00.012.000.000", Duration::Format::Standard)) ;
        EXPECT_EQ(Duration::Milliseconds(-123.0), Duration::Parse("-00.123.000.000", Duration::Format::Standard)) ;

        EXPECT_EQ((-Duration::Seconds(+1.0)), Duration::Parse("-01.000.000.000", Duration::Format::Standard)) ;
        EXPECT_EQ((-Duration::Seconds(+12.0)), Duration::Parse("-12.000.000.000", Duration::Format::Standard)) ;

        EXPECT_EQ((-(Duration::Minutes(+1.0) + Duration::Seconds(+2.0))), Duration::Parse("-01:02.000.000.000", Duration::Format::Standard)) ;
        EXPECT_EQ((-(Duration::Minutes(+12.0) + Duration::Seconds(+34.0))), Duration::Parse("-12:34.000.000.000", Duration::Format::Standard)) ;

        EXPECT_EQ((-(Duration::Hours(+1.0) + Duration::Minutes(+2.0) + Duration::Seconds(+3.0))), Duration::Parse("-01:02:03.000.000.000", Duration::Format::Standard)) ;
        EXPECT_EQ((-(Duration::Hours(+12.0) + Duration::Minutes(+34.0) + Duration::Seconds(+56.0))), Duration::Parse("-12:34:56.000.000.000", Duration::Format::Standard)) ;

        EXPECT_EQ((-(Duration::Days(+1.0) + Duration::Hours(+1.0) + Duration::Minutes(+2.0) + Duration::Seconds(+3.0))), Duration::Parse("-1 01:02:03.000.000.000", Duration::Format::Standard)) ;
        EXPECT_EQ((-(Duration::Days(+3.0) + Duration::Hours(+12.0) + Duration::Minutes(+34.0) + Duration::Seconds(+56.0))), Duration::Parse("-3 12:34:56.000.000.000", Duration::Format::Standard)) ;
        EXPECT_EQ((-(Duration::Days(+7.0) + Duration::Hours(+12.0) + Duration::Minutes(+34.0) + Duration::Seconds(+56.0))), Duration::Parse("-7 12:34:56.000.000.000", Duration::Format::Standard)) ;
        EXPECT_EQ((-(Duration::Days(+14.0) + Duration::Hours(+12.0) + Duration::Minutes(+34.0) + Duration::Seconds(+56.0))), Duration::Parse("-14 12:34:56.000.000.000", Duration::Format::Standard)) ;
        EXPECT_EQ((-(Duration::Days(+99.0) + Duration::Hours(+12.0) + Duration::Minutes(+34.0) + Duration::Seconds(+56.0))), Duration::Parse("-99 12:34:56.000.000.000", Duration::Format::Standard)) ;

        EXPECT_EQ((-(Duration::Days(+1.0) + Duration::Hours(+1.0) + Duration::Minutes(+2.0) + Duration::Seconds(+3.0) + Duration::Milliseconds(+123.0) + Duration::Microseconds(+456.0) + Duration::Nanoseconds(+789.0))), Duration::Parse("-1 01:02:03.123.456.789", Duration::Format::Standard)) ;

        for (auto idx = 0; idx < 100000; idx += 10)
        {

            const Duration duration = Duration::Days(idx)
                                    + Duration::Hours(idx)
                                    + Duration::Minutes(idx)
                                    + Duration::Seconds(idx)
                                    + Duration::Milliseconds(idx)
                                    + Duration::Microseconds(idx)
                                    + Duration::Nanoseconds(idx) ;

            EXPECT_EQ(duration, Duration::Parse(duration.toString(Duration::Format::Standard), Duration::Format::Standard)) ;
            EXPECT_EQ((-duration), Duration::Parse((-duration).toString(Duration::Format::Standard), Duration::Format::Standard)) ;

        }

    }

    // ISO 8601

    {

        EXPECT_EQ(Duration::Zero(), Duration::Parse("PT0H0M0S", Duration::Format::ISO8601)) ;

        EXPECT_EQ(Duration::Nanoseconds(+1.0), Duration::Parse("PT0.000000001S", Duration::Format::ISO8601)) ;
        EXPECT_EQ(Duration::Nanoseconds(+10.0), Duration::Parse("PT0.00000001S", Duration::Format::ISO8601)) ;
        EXPECT_EQ(Duration::Nanoseconds(+100.0), Duration::Parse("PT0.0000001S", Duration::Format::ISO8601)) ;
        EXPECT_EQ(Duration::Nanoseconds(+12.0), Duration::Parse("PT0.000000012S", Duration::Format::ISO8601)) ;
        EXPECT_EQ(Duration::Nanoseconds(+123.0), Duration::Parse("PT0.000000123S", Duration::Format::ISO8601)) ;

        EXPECT_EQ(Duration::Microseconds(+1.0), Duration::Parse("PT0.000001S", Duration::Format::ISO8601)) ;
        EXPECT_EQ(Duration::Microseconds(+10.0), Duration::Parse("PT0.00001S", Duration::Format::ISO8601)) ;
        EXPECT_EQ(Duration::Microseconds(+100.0), Duration::Parse("PT0.0001S", Duration::Format::ISO8601)) ;
        EXPECT_EQ(Duration::Microseconds(+12.0), Duration::Parse("PT0.000012S", Duration::Format::ISO8601)) ;
        EXPECT_EQ(Duration::Microseconds(+123.0), Duration::Parse("PT0.000123S", Duration::Format::ISO8601)) ;

        EXPECT_EQ(Duration::Milliseconds(+1.0), Duration::Parse("PT0.001S", Duration::Format::ISO8601)) ;
        EXPECT_EQ(Duration::Milliseconds(+10.0), Duration::Parse("PT0.01S", Duration::Format::ISO8601)) ;
        EXPECT_EQ(Duration::Milliseconds(+100.0), Duration::Parse("PT0.1S", Duration::Format::ISO8601)) ;
        EXPECT_EQ(Duration::Milliseconds(+12.0), Duration::Parse("PT0.012S", Duration::Format::ISO8601)) ;
        EXPECT_EQ(Duration::Milliseconds(+123.0), Duration::Parse("PT0.123S", Duration::Format::ISO8601)) ;

        EXPECT_EQ(Duration::Seconds(+1.0), Duration::Parse("PT1S", Duration::Format::ISO8601)) ;
        EXPECT_EQ(Duration::Seconds(+12.0), Duration::Parse("PT12S", Duration::Format::ISO8601)) ;

        EXPECT_EQ((Duration::Minutes(+1.0) + Duration::Seconds(+2.0)), Duration::Parse("PT1M2S", Duration::Format::ISO8601)) ;
        EXPECT_EQ((Duration::Minutes(+12.0) + Duration::Seconds(+34.0)), Duration::Parse("PT12M34S", Duration::Format::ISO8601)) ;

        EXPECT_EQ((Duration::Hours(+1.0) + Duration::Minutes(+2.0) + Duration::Seconds(+3.0)), Duration::Parse("PT1H2M3S", Duration::Format::ISO8601)) ;
        EXPECT_EQ((Duration::Hours(+12.0) + Duration::Minutes(+34.0) + Duration::Seconds(+56.0)), Duration::Parse("PT12H34M56S", Duration::Format::ISO8601)) ;

        EXPECT_EQ((Duration::Days(+1.0)), Duration::Parse("P1D", Duration::Format::ISO8601)) ;
        EXPECT_EQ((Duration::Days(+1.0) + Duration::Hours(+1.0)), Duration::Parse("P1DT1H", Duration::Format::ISO8601)) ;
        EXPECT_EQ((Duration::Days(+1.0) + Duration::Hours(+1.0) + Duration::Minutes(+2.0)), Duration::Parse("P1DT1H2M", Duration::Format::ISO8601)) ;
        EXPECT_EQ((Duration::Days(+1.0) + Duration::Hours(+1.0) + Duration::Minutes(+2.0) + Duration::Seconds(+3.0)), Duration::Parse("P1DT1H2M3S", Duration::Format::ISO8601)) ;
        EXPECT_EQ((Duration::Days(+3.0) + Duration::Hours(+12.0) + Duration::Minutes(+34.0) + Duration::Seconds(+56.0)), Duration::Parse("P3DT12H34M56S", Duration::Format::ISO8601)) ;
        EXPECT_EQ((Duration::Days(+7.0) + Duration::Hours(+12.0) + Duration::Minutes(+34.0) + Duration::Seconds(+56.0)), Duration::Parse("P7DT12H34M56S", Duration::Format::ISO8601)) ;
        EXPECT_EQ((Duration::Days(+14.0) + Duration::Hours(+12.0) + Duration::Minutes(+34.0) + Duration::Seconds(+56.0)), Duration::Parse("P14DT12H34M56S", Duration::Format::ISO8601)) ;
        EXPECT_EQ((Duration::Days(+99.0) + Duration::Hours(+12.0) + Duration::Minutes(+34.0) + Duration::Seconds(+56.0)), Duration::Parse("P99DT12H34M56S", Duration::Format::ISO8601)) ;

        EXPECT_EQ((Duration::Days(+1.0) + Duration::Hours(+1.0) + Duration::Minutes(+2.0) + Duration::Seconds(+3.0) + Duration::Milliseconds(+123.0) + Duration::Microseconds(+456.0) + Duration::Nanoseconds(+789.0)), Duration::Parse("P1DT1H2M3.123456789S", Duration::Format::ISO8601)) ;

        EXPECT_EQ(Duration::Nanoseconds(-1.0), Duration::Parse("-PT0.000000001S", Duration::Format::ISO8601)) ;
        EXPECT_EQ(Duration::Nanoseconds(-10.0), Duration::Parse("-PT0.00000001S", Duration::Format::ISO8601)) ;
        EXPECT_EQ(Duration::Nanoseconds(-100.0), Duration::Parse("-PT0.0000001S", Duration::Format::ISO8601)) ;
        EXPECT_EQ(Duration::Nanoseconds(-12.0), Duration::Parse("-PT0.000000012S", Duration::Format::ISO8601)) ;
        EXPECT_EQ(Duration::Nanoseconds(-123.0), Duration::Parse("-PT0.000000123S", Duration::Format::ISO8601)) ;

        EXPECT_EQ(Duration::Microseconds(-1.0), Duration::Parse("-PT0.000001S", Duration::Format::ISO8601)) ;
        EXPECT_EQ(Duration::Microseconds(-10.0), Duration::Parse("-PT0.00001S", Duration::Format::ISO8601)) ;
        EXPECT_EQ(Duration::Microseconds(-100.0), Duration::Parse("-PT0.0001S", Duration::Format::ISO8601)) ;
        EXPECT_EQ(Duration::Microseconds(-12.0), Duration::Parse("-PT0.000012S", Duration::Format::ISO8601)) ;
        EXPECT_EQ(Duration::Microseconds(-123.0), Duration::Parse("-PT0.000123S", Duration::Format::ISO8601)) ;

        EXPECT_EQ(Duration::Milliseconds(-1.0), Duration::Parse("-PT0.001S", Duration::Format::ISO8601)) ;
        EXPECT_EQ(Duration::Milliseconds(-10.0), Duration::Parse("-PT0.01S", Duration::Format::ISO8601)) ;
        EXPECT_EQ(Duration::Milliseconds(-100.0), Duration::Parse("-PT0.1S", Duration::Format::ISO8601)) ;
        EXPECT_EQ(Duration::Milliseconds(-12.0), Duration::Parse("-PT0.012S", Duration::Format::ISO8601)) ;
        EXPECT_EQ(Duration::Milliseconds(-123.0), Duration::Parse("-PT0.123S", Duration::Format::ISO8601)) ;

        EXPECT_EQ(Duration::Seconds(-1.0), Duration::Parse("-PT1S", Duration::Format::ISO8601)) ;
        EXPECT_EQ(Duration::Seconds(-12.0), Duration::Parse("-PT12S", Duration::Format::ISO8601)) ;

        EXPECT_EQ((-(Duration::Minutes(+1.0) + Duration::Seconds(+2.0))), Duration::Parse("-PT1M2S", Duration::Format::ISO8601)) ;
        EXPECT_EQ((-(Duration::Minutes(+12.0) + Duration::Seconds(+34.0))), Duration::Parse("-PT12M34S", Duration::Format::ISO8601)) ;

        EXPECT_EQ((-(Duration::Hours(+1.0) + Duration::Minutes(+2.0) + Duration::Seconds(+3.0))), Duration::Parse("-PT1H2M3S", Duration::Format::ISO8601)) ;
        EXPECT_EQ((-(Duration::Hours(+12.0) + Duration::Minutes(+34.0) + Duration::Seconds(+56.0))), Duration::Parse("-PT12H34M56S", Duration::Format::ISO8601)) ;

        EXPECT_EQ((-(Duration::Days(+1.0))), Duration::Parse("-P1D", Duration::Format::ISO8601)) ;
        EXPECT_EQ((-(Duration::Days(+1.0) + Duration::Hours(+1.0))), Duration::Parse("-P1DT1H", Duration::Format::ISO8601)) ;
        EXPECT_EQ((-(Duration::Days(+1.0) + Duration::Hours(+1.0) + Duration::Minutes(+2.0))), Duration::Parse("-P1DT1H2M", Duration::Format::ISO8601)) ;
        EXPECT_EQ((-(Duration::Days(+1.0) + Duration::Hours(+1.0) + Duration::Minutes(+2.0) + Duration::Seconds(+3.0))), Duration::Parse("-P1DT1H2M3S", Duration::Format::ISO8601)) ;
        EXPECT_EQ((-(Duration::Days(+3.0) + Duration::Hours(+12.0) + Duration::Minutes(+34.0) + Duration::Seconds(+56.0))), Duration::Parse("-P3DT12H34M56S", Duration::Format::ISO8601)) ;
        EXPECT_EQ((-(Duration::Days(+7.0) + Duration::Hours(+12.0) + Duration::Minutes(+34.0) + Duration::Seconds(+56.0))), Duration::Parse("-P7DT12H34M56S", Duration::Format::ISO8601)) ;
        EXPECT_EQ((-(Duration::Days(+14.0) + Duration::Hours(+12.0) + Duration::Minutes(+34.0) + Duration::Seconds(+56.0))), Duration::Parse("-P14DT12H34M56S", Duration::Format::ISO8601)) ;
        EXPECT_EQ((-(Duration::Days(+99.0) + Duration::Hours(+12.0) + Duration::Minutes(+34.0) + Duration::Seconds(+56.0))), Duration::Parse("-P99DT12H34M56S", Duration::Format::ISO8601)) ;

        EXPECT_EQ((-(Duration::Days(+1.0) + Duration::Hours(+1.0) + Duration::Minutes(+2.0) + Duration::Seconds(+3.0) + Duration::Milliseconds(+123.0) + Duration::Microseconds(+456.0) + Duration::Nanoseconds(+789.0))), Duration::Parse("-P1DT1H2M3.123456789S", Duration::Format::ISO8601)) ;

        for (auto idx = 0; idx < 100000; idx += 10)
        {

            const Duration duration = Duration::Days(idx)
                                    + Duration::Hours(idx)
                                    + Duration::Minutes(idx)
                                    + Duration::Seconds(idx)
                                    + Duration::Milliseconds(idx)
                                    + Duration::Microseconds(idx)
                                    + Duration::Nanoseconds(idx) ;

            EXPECT_EQ(duration, Duration::Parse(duration.toString(Duration::Format::ISO8601), Duration::Format::ISO8601)) ;
            EXPECT_EQ((-duration), Duration::Parse((-duration).toString(Duration::Format::ISO8601), Duration::Format::ISO8601)) ;

        }

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
