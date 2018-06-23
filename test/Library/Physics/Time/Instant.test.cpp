////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Time/Instant.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Time/Instant.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// TEST (Library_Physics_Time_Instant, EqualToOperator)
// {
    
//     using library::physics::time::Scale ;
//     using library::physics::time::Instant ;

//     {

//         EXPECT_TRUE(Instant(0, true, Scale::UTC) == Instant(0, true, Scale::UTC)) ;
//         EXPECT_TRUE(Instant(123, true, Scale::UTC) == Instant(123, true, Scale::UTC)) ;
//         EXPECT_TRUE(Instant(0, true, Scale::UTC) == Instant(0, false, Scale::UTC)) ;

//     }

//     {

//         EXPECT_FALSE(Instant(0, true, Scale::UTC) == Instant(1, true, Scale::UTC)) ;
//         EXPECT_FALSE(Instant(1, true, Scale::UTC) == Instant(0, true, Scale::UTC)) ;

//         EXPECT_FALSE(Instant(0, false, Scale::UTC) == Instant(1, false, Scale::UTC)) ;
//         EXPECT_FALSE(Instant(1, false, Scale::UTC) == Instant(0, false, Scale::UTC)) ;

//         EXPECT_FALSE(Instant(0, true, Scale::UTC) == Instant(0, true, Scale::TAI)) ;
//         EXPECT_FALSE(Instant(0, false, Scale::UTC) == Instant(0, false, Scale::TAI)) ;

//     }

//     {

//         EXPECT_FALSE(Instant::Undefined() == Instant::Undefined()) ;
//         EXPECT_FALSE(Instant::Undefined() == Instant(0, true, Scale::UTC)) ;
//         EXPECT_FALSE(Instant(0, true, Scale::UTC) == Instant::Undefined()) ;

//     }

// }

// TEST (Library_Physics_Time_Instant, NoEqualToOperator)
// {
    
//     using library::physics::time::Scale ;
//     using library::physics::time::Instant ;

//     {

//         EXPECT_TRUE(Instant(0, true, Scale::UTC) != Instant(1, true, Scale::UTC)) ;
//         EXPECT_TRUE(Instant(1, true, Scale::UTC) != Instant(0, true, Scale::UTC)) ;

//         EXPECT_TRUE(Instant(0, false, Scale::UTC) != Instant(1, false, Scale::UTC)) ;
//         EXPECT_TRUE(Instant(1, false, Scale::UTC) != Instant(0, false, Scale::UTC)) ;

//         EXPECT_TRUE(Instant(0, true, Scale::UTC) != Instant(0, true, Scale::TAI)) ;
//         EXPECT_TRUE(Instant(0, false, Scale::UTC) != Instant(0, false, Scale::TAI)) ;

//     }

//     {

//         EXPECT_TRUE(Instant::Undefined() != Instant::Undefined()) ;

//     }

//     {

//         EXPECT_FALSE(Instant(0, true, Scale::UTC) != Instant(0, true, Scale::UTC)) ;
//         EXPECT_FALSE(Instant(123, true, Scale::UTC) != Instant(123, true, Scale::UTC)) ;
//         EXPECT_FALSE(Instant(0, true, Scale::UTC) != Instant(0, false, Scale::UTC)) ;

//     }

// }

// TEST (Library_Physics_Time_Instant, LessThanOperator)
// {
    
//     using library::physics::time::Scale ;
//     using library::physics::time::Instant ;

//     {

//         EXPECT_TRUE(Instant(0, true, Scale::UTC) < Instant(1, true, Scale::UTC)) ;
//         EXPECT_TRUE(Instant(10, false, Scale::UTC) < Instant(10, true, Scale::UTC)) ;

//     }

//     {

//         EXPECT_FALSE(Instant(0, true, Scale::UTC) < Instant(0, true, Scale::UTC)) ;
//         EXPECT_FALSE(Instant(1, true, Scale::UTC) < Instant(0, true, Scale::UTC)) ;
//         EXPECT_FALSE(Instant(1, true, Scale::UTC) < Instant(10, false, Scale::UTC)) ;

//     }

// }

// TEST (Library_Physics_Time_Instant, LessThanOrEqualToOperator)
// {
    
//     using library::physics::time::Scale ;
//     using library::physics::time::Instant ;

//     {

//         EXPECT_TRUE(Instant(0, true, Scale::UTC) <= Instant(0, true, Scale::UTC)) ;
//         EXPECT_TRUE(Instant(0, true, Scale::UTC) <= Instant(1, true, Scale::UTC)) ;
//         EXPECT_TRUE(Instant(10, false, Scale::UTC) <= Instant(10, true, Scale::UTC)) ;

//         EXPECT_TRUE(Instant(0, true, Scale::UTC) <= Instant(0, false, Scale::UTC)) ;
//         EXPECT_TRUE(Instant(0, false, Scale::UTC) <= Instant(0, true, Scale::UTC)) ;
//         EXPECT_TRUE(Instant(0, false, Scale::UTC) <= Instant(0, false, Scale::UTC)) ;

//     }

//     {

//         EXPECT_FALSE(Instant(1, true, Scale::UTC) <= Instant(0, true, Scale::UTC)) ;
//         EXPECT_FALSE(Instant(1, true, Scale::UTC) <= Instant(10, false, Scale::UTC)) ;

//     }

// }

// TEST (Library_Physics_Time_Instant, GreaterThanOperator)
// {
    
//     using library::physics::time::Scale ;
//     using library::physics::time::Instant ;

//     {
        
//         EXPECT_TRUE(Instant(1, true, Scale::UTC) > Instant(0, true, Scale::UTC)) ;
//         EXPECT_TRUE(Instant(1, true, Scale::UTC) > Instant(10, false, Scale::UTC)) ;

//     }

//     {

//         EXPECT_FALSE(Instant(0, true, Scale::UTC) > Instant(0, true, Scale::UTC)) ;
//         EXPECT_FALSE(Instant(0, true, Scale::UTC) > Instant(1, true, Scale::UTC)) ;
//         EXPECT_FALSE(Instant(10, false, Scale::UTC) > Instant(10, true, Scale::UTC)) ;

//     }

// }

// TEST (Library_Physics_Time_Instant, GreaterThanOrEqualToOperator)
// {
    
//     using library::physics::time::Scale ;
//     using library::physics::time::Instant ;

//     {

//         EXPECT_TRUE(Instant(0, true, Scale::UTC) >= Instant(0, true, Scale::UTC)) ;
//         EXPECT_TRUE(Instant(1, true, Scale::UTC) >= Instant(0, true, Scale::UTC)) ;
//         EXPECT_TRUE(Instant(1, true, Scale::UTC) >= Instant(10, false, Scale::UTC)) ;

//         EXPECT_TRUE(Instant(0, true, Scale::UTC) >= Instant(0, false, Scale::UTC)) ;
//         EXPECT_TRUE(Instant(0, false, Scale::UTC) >= Instant(0, true, Scale::UTC)) ;
//         EXPECT_TRUE(Instant(0, false, Scale::UTC) >= Instant(0, false, Scale::UTC)) ;

//     }

//     {

//         EXPECT_FALSE(Instant(0, true, Scale::UTC) >= Instant(1, true, Scale::UTC)) ;
//         EXPECT_FALSE(Instant(10, false, Scale::UTC) >= Instant(10, true, Scale::UTC)) ;

//     }

// }

// TEST (Library_Physics_Time_Instant, AdditionOperator)
// {
    
//     using library::physics::time::Scale ;
//     using library::physics::time::Instant ;
//     using library::physics::time::Duration ;

//     {

//         EXPECT_EQ(Instant(0, true, Scale::UTC), Instant(0, true, Scale::UTC) + Duration(0)) ;

//         EXPECT_EQ(Instant(1, true, Scale::UTC), Instant(1, true, Scale::UTC) + Duration(0)) ;
//         EXPECT_EQ(Instant(1, false, Scale::UTC), Instant(1, false, Scale::UTC) + Duration(0)) ;

//         EXPECT_EQ(Instant(2, true, Scale::UTC), Instant(1, true, Scale::UTC) + Duration(+1)) ;
//         EXPECT_EQ(Instant(0, true, Scale::UTC), Instant(1, true, Scale::UTC) + Duration(-1)) ;

//         EXPECT_EQ(Instant(0, true, Scale::UTC), Instant(1, false, Scale::UTC) + Duration(+1)) ;
//         EXPECT_EQ(Instant(2, false, Scale::UTC), Instant(1, false, Scale::UTC) + Duration(-1)) ;

//         EXPECT_EQ(Instant(1, false, Scale::UTC), Instant(0, true, Scale::UTC) + Duration(-1)) ;
//         EXPECT_EQ(Instant(0, true, Scale::UTC), Instant(1, false, Scale::UTC) + Duration(+1)) ;

//     }

// }

// TEST (Library_Physics_Time_Instant, SubtractionOperator)
// {
    
//     using library::physics::time::Scale ;
//     using library::physics::time::Instant ;
//     using library::physics::time::Duration ;

//     {

//         EXPECT_EQ(Instant(0, true, Scale::UTC), Instant(0, true, Scale::UTC) - Duration(0)) ;

//         EXPECT_EQ(Instant(1, true, Scale::UTC), Instant(1, true, Scale::UTC) - Duration(0)) ;
//         EXPECT_EQ(Instant(1, false, Scale::UTC), Instant(1, false, Scale::UTC) - Duration(0)) ;

//         EXPECT_EQ(Instant(0, true, Scale::UTC), Instant(1, true, Scale::UTC) - Duration(+1)) ;
//         EXPECT_EQ(Instant(2, true, Scale::UTC), Instant(1, true, Scale::UTC) - Duration(-1)) ;

//         EXPECT_EQ(Instant(2, false, Scale::UTC), Instant(1, false, Scale::UTC) - Duration(+1)) ;
//         EXPECT_EQ(Instant(0, true, Scale::UTC), Instant(1, false, Scale::UTC) - Duration(-1)) ;

//         EXPECT_EQ(Instant(1, true, Scale::UTC), Instant(0, true, Scale::UTC) - Duration(-1)) ;
//         EXPECT_EQ(Instant(2, false, Scale::UTC), Instant(1, false, Scale::UTC) - Duration(+1)) ;

//     }

//     {

//         EXPECT_EQ(Duration(0), Instant(0, true, Scale::UTC) - Instant(0, true, Scale::UTC)) ;
//         EXPECT_EQ(Duration(+1), Instant(1, true, Scale::UTC) - Instant(0, true, Scale::UTC)) ;
//         EXPECT_EQ(Duration(-1), Instant(0, true, Scale::UTC) - Instant(1, true, Scale::UTC)) ;
//         EXPECT_EQ(Duration(0), Instant(1, true, Scale::UTC) - Instant(1, true, Scale::UTC)) ;

//         EXPECT_EQ(Duration(0), Instant(0, true, Scale::UTC) - Instant(0, false, Scale::UTC)) ;
//         EXPECT_EQ(Duration(+1), Instant(1, true, Scale::UTC) - Instant(0, false, Scale::UTC)) ;
//         EXPECT_EQ(Duration(+1), Instant(0, true, Scale::UTC) - Instant(1, false, Scale::UTC)) ;
//         EXPECT_EQ(Duration(+2), Instant(1, true, Scale::UTC) - Instant(1, false, Scale::UTC)) ;

//         EXPECT_EQ(Duration(0), Instant(0, false, Scale::UTC) - Instant(0, true, Scale::UTC)) ;
//         EXPECT_EQ(Duration(-1), Instant(1, false, Scale::UTC) - Instant(0, true, Scale::UTC)) ;
//         EXPECT_EQ(Duration(-1), Instant(0, false, Scale::UTC) - Instant(1, true, Scale::UTC)) ;
//         EXPECT_EQ(Duration(-2), Instant(1, false, Scale::UTC) - Instant(1, true, Scale::UTC)) ;

//         EXPECT_EQ(Duration(0), Instant(0, false, Scale::UTC) - Instant(0, false, Scale::UTC)) ;
//         EXPECT_EQ(Duration(-1), Instant(1, false, Scale::UTC) - Instant(0, false, Scale::UTC)) ;
//         EXPECT_EQ(Duration(+1), Instant(0, false, Scale::UTC) - Instant(1, false, Scale::UTC)) ;
//         EXPECT_EQ(Duration(0), Instant(1, false, Scale::UTC) - Instant(1, false, Scale::UTC)) ;

//     }

// }

// TEST (Library_Physics_Time_Instant, AdditionAssignementOperator)
// {
    
//     using library::physics::time::Scale ;
//     using library::physics::time::Instant ;
//     using library::physics::time::Duration ;

//     {

//         EXPECT_EQ(Instant(0, true, Scale::UTC), Instant(0, true, Scale::UTC) += Duration(0)) ;

//         EXPECT_EQ(Instant(1, true, Scale::UTC), Instant(1, true, Scale::UTC) += Duration(0)) ;
//         EXPECT_EQ(Instant(1, false, Scale::UTC), Instant(1, false, Scale::UTC) += Duration(0)) ;

//         EXPECT_EQ(Instant(2, true, Scale::UTC), Instant(1, true, Scale::UTC) += Duration(+1)) ;
//         EXPECT_EQ(Instant(0, true, Scale::UTC), Instant(1, true, Scale::UTC) += Duration(-1)) ;

//         EXPECT_EQ(Instant(0, true, Scale::UTC), Instant(1, false, Scale::UTC) += Duration(+1)) ;
//         EXPECT_EQ(Instant(2, false, Scale::UTC), Instant(1, false, Scale::UTC) += Duration(-1)) ;

//         EXPECT_EQ(Instant(1, false, Scale::UTC), Instant(0, true, Scale::UTC) += Duration(-1)) ;
//         EXPECT_EQ(Instant(0, true, Scale::UTC), Instant(1, false, Scale::UTC) += Duration(+1)) ;

//     }

// }

// TEST (Library_Physics_Time_Instant, SubtractionAssignementOperator)
// {
    
//     using library::physics::time::Scale ;
//     using library::physics::time::Instant ;
//     using library::physics::time::Duration ;

//     {

//         EXPECT_EQ(Instant(0, true, Scale::UTC), Instant(0, true, Scale::UTC) -= Duration(0)) ;

//         EXPECT_EQ(Instant(1, true, Scale::UTC), Instant(1, true, Scale::UTC) -= Duration(0)) ;
//         EXPECT_EQ(Instant(1, false, Scale::UTC), Instant(1, false, Scale::UTC) -= Duration(0)) ;

//         EXPECT_EQ(Instant(0, true, Scale::UTC), Instant(1, true, Scale::UTC) -= Duration(+1)) ;
//         EXPECT_EQ(Instant(2, true, Scale::UTC), Instant(1, true, Scale::UTC) -= Duration(-1)) ;

//         EXPECT_EQ(Instant(2, false, Scale::UTC), Instant(1, false, Scale::UTC) -= Duration(+1)) ;
//         EXPECT_EQ(Instant(0, true, Scale::UTC), Instant(1, false, Scale::UTC) -= Duration(-1)) ;

//         EXPECT_EQ(Instant(1, true, Scale::UTC), Instant(0, true, Scale::UTC) -= Duration(-1)) ;
//         EXPECT_EQ(Instant(2, false, Scale::UTC), Instant(1, false, Scale::UTC) -= Duration(+1)) ;

//     }

// }

// TEST (Library_Physics_Time_Instant, StreamOperator)
// {
    
//     using library::physics::time::Scale ;
//     using library::physics::time::Instant ;

//     {

//         testing::internal::CaptureStdout() ;

//         EXPECT_NO_THROW(std::cout << Instant(123, true, Scale::UTC) << std::endl) ;

//         EXPECT_FALSE(testing::internal::GetCapturedStdout().empty()) ;

//     }

// }

// TEST (Library_Physics_Time_Instant, IsDefined)
// {
    
//     using library::physics::time::Scale ;
//     using library::physics::time::Instant ;

//     {

//         EXPECT_TRUE(Instant(0, true, Scale::UTC).isDefined()) ;
//         EXPECT_TRUE(Instant(1, true, Scale::UTC).isDefined()) ;

//         EXPECT_TRUE(Instant(0, false, Scale::UTC).isDefined()) ;
//         EXPECT_TRUE(Instant(1, false, Scale::UTC).isDefined()) ;

//         EXPECT_TRUE(Instant(0, true, Scale::TAI).isDefined()) ;
//         EXPECT_TRUE(Instant(0, true, Scale::TT).isDefined()) ;

//     }

//     {

//         EXPECT_FALSE(Instant(0, true, Scale::Undefined).isDefined()) ;

//     }
    
//     {

//         EXPECT_FALSE(Instant::Undefined().isDefined()) ;

//     }

// }

// TEST (Library_Physics_Time_Instant, IsPostEpoch)
// {
    
//     using library::physics::time::Scale ;
//     using library::physics::time::Instant ;

//     {

//         EXPECT_TRUE(Instant(0, true, Scale::TT).isPostEpoch()) ;
//         EXPECT_TRUE(Instant(1, true, Scale::TT).isPostEpoch()) ;
//         EXPECT_TRUE(Instant(0, false, Scale::TT).isPostEpoch()) ;
        
//         EXPECT_TRUE(Instant(0, true, Scale::TAI).isPostEpoch()) ;
//         EXPECT_TRUE(Instant(0, true, Scale::GPST).isPostEpoch()) ;

//         EXPECT_FALSE(Instant(1, false, Scale::TT).isPostEpoch()) ;

//     }

//     {

//         EXPECT_TRUE(Instant::Epoch().isPostEpoch()) ;

//     }

//     {

//         EXPECT_ANY_THROW(Instant::Undefined().isPostEpoch()) ;

//     }

// }

// TEST (Library_Physics_Time_Instant, GetScale)
// {
    
//     using library::physics::time::Scale ;
//     using library::physics::time::Instant ;

//     {

//         EXPECT_EQ(Scale::Undefined, Instant(0, true, Scale::Undefined).getScale()) ;
//         EXPECT_EQ(Scale::UTC, Instant(0, true, Scale::UTC).getScale()) ;
//         EXPECT_EQ(Scale::TT, Instant(0, true, Scale::TT).getScale()) ;
//         EXPECT_EQ(Scale::TAI, Instant(0, true, Scale::TAI).getScale()) ;
//         EXPECT_EQ(Scale::UT1, Instant(0, true, Scale::UT1).getScale()) ;
//         EXPECT_EQ(Scale::TCG, Instant(0, true, Scale::TCG).getScale()) ;
//         EXPECT_EQ(Scale::TCB, Instant(0, true, Scale::TCB).getScale()) ;
//         EXPECT_EQ(Scale::TDB, Instant(0, true, Scale::TDB).getScale()) ;
//         EXPECT_EQ(Scale::GMST, Instant(0, true, Scale::GMST).getScale()) ;
//         EXPECT_EQ(Scale::GPST, Instant(0, true, Scale::GPST).getScale()) ;
//         EXPECT_EQ(Scale::GST, Instant(0, true, Scale::GST).getScale()) ;
//         EXPECT_EQ(Scale::GLST, Instant(0, true, Scale::GLST).getScale()) ;
//         EXPECT_EQ(Scale::BDT, Instant(0, true, Scale::BDT).getScale()) ;
//         EXPECT_EQ(Scale::QZSST, Instant(0, true, Scale::QZSST).getScale()) ;
//         EXPECT_EQ(Scale::IRNSST, Instant(0, true, Scale::IRNSST).getScale()) ;

//     }

// }

TEST (Library_Physics_Time_Instant, GetJulianDate)
{
    
    using library::physics::time::Scale ;
    using library::physics::time::Instant ;

    {

        FAIL() ;

    }

}

TEST (Library_Physics_Time_Instant, GetModifiedJulianDate)
{
    
    using library::physics::time::Scale ;
    using library::physics::time::Instant ;

    {

        FAIL() ;

    }

}

TEST (Library_Physics_Time_Instant, GetDateTime)
{
    
    using library::physics::time::Scale ;
    using library::physics::time::Instant ;

    {

        FAIL() ;

    }

}

TEST (Library_Physics_Time_Instant, GetCountSinceEpoch)
{
    
    using library::physics::time::Scale ;
    using library::physics::time::Instant ;

    {

        FAIL() ;

    }

}

TEST (Library_Physics_Time_Instant, GetString)
{
    
    using library::physics::time::Scale ;
    using library::physics::time::DateTime ;
    using library::physics::time::Instant ;

    {

        EXPECT_EQ("2000-01-01 12:00:00 [TT]", Instant::J2000().getString(Scale::TT)) ;

    }

    {

        EXPECT_EQ("2000-01-01 12:00:00 [TT]", Instant::DateTime(DateTime(2000, 1, 1, 12, 0, 0, 0, 0, 0), Scale::TT).getString(Scale::TT)) ;
        EXPECT_EQ("2000-01-01 11:59:59.999.999.999 [TT]", Instant::DateTime(DateTime(2000, 1, 1, 11, 59, 59, 999, 999, 999), Scale::TT).getString(Scale::TT)) ;
        EXPECT_EQ("2000-01-01 12:00:00.000.000.001 [TT]", Instant::DateTime(DateTime(2000, 1, 1, 12, 0, 0, 0, 0, 1), Scale::TT).getString(Scale::TT)) ;

        EXPECT_EQ("1999-01-01 00:00:00 [TT]", Instant::DateTime(DateTime(1999, 1, 1, 0, 0, 0, 0, 0, 0), Scale::TT).getString(Scale::TT)) ;        
        EXPECT_EQ("2000-01-01 00:00:00 [TT]", Instant::DateTime(DateTime(2000, 1, 1, 0, 0, 0, 0, 0, 0), Scale::TT).getString(Scale::TT)) ;
        EXPECT_EQ("2001-01-01 00:00:00 [TT]", Instant::DateTime(DateTime(2001, 1, 1, 0, 0, 0, 0, 0, 0), Scale::TT).getString(Scale::TT)) ;

        EXPECT_EQ("2018-01-02 03:04:05.006.007.008 [TT]", Instant::DateTime(DateTime(2018, 1, 2, 3, 4, 5, 6, 7, 8), Scale::TT).getString(Scale::TT)) ;

        EXPECT_EQ("1970-01-01 00:00:00 [TT]", Instant::DateTime(DateTime(1970, 1, 1, 0, 0, 0, 0, 0, 0), Scale::TT).getString(Scale::TT)) ;
        EXPECT_EQ("2030-12-31 23:59:59.999.999.999 [TT]", Instant::DateTime(DateTime(2030, 12, 31, 23, 59, 59, 999, 999, 999), Scale::TT).getString(Scale::TT)) ;

    }

    {

        for (auto year = 1970; year <= 2030; year += 1)
        {

            for (auto month = 1; month <= 12; month += 3)
            {

                for (auto day = 1; day <= 28; day += 5)
                {

                    for (auto hour = 0; hour <= 23; hour += 4)
                    {

                        for (auto minute = 0; minute <= 59; minute += 20)
                        {

                            for (auto second = 0; second <= 59; second += 20)
                            {

                                for (auto const& scale : { Scale::TT, Scale::TAI, Scale::UTC, Scale::GPST })
                                {

                                    if ((year < 1981) && (scale == Scale::UTC))
                                    {
                                        continue ; // Because dAT not implemented there
                                    }
                                    
                                    Instant intant = Instant::DateTime(DateTime(year, month, day, hour, minute, second, 6, 7, 8), scale) ;

                                    EXPECT_EQ(DateTime(year, month, day, hour, minute, second, 6, 7, 8), intant.getDateTime(scale)) ;

                                }

                            }

                        }

                    }

                }

            }

        }

    }

}

TEST (Library_Physics_Time_Instant, InScale)
{
    
    using library::physics::time::Scale ;
    using library::physics::time::Instant ;

    {

        FAIL() ;

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
    using library::physics::time::Instant ;

    {

        FAIL() ;

        // EXPECT_NO_THROW(Instant::J2000()) ;
        // EXPECT_TRUE(Instant::J2000().isDefined()) ;

        // EXPECT_EQ(Instant(0, true, Scale::TT), Instant::J2000()) ;

    }

}

TEST (Library_Physics_Time_Instant, DateTime)
{
    
    using library::physics::time::Scale ;
    using library::physics::time::Instant ;

    {

        FAIL() ;

    }

}

TEST (Library_Physics_Time_Instant, JulianDate)
{
    
    using library::physics::time::Scale ;
    using library::physics::time::Instant ;

    {

        FAIL() ;

    }

}

TEST (Library_Physics_Time_Instant, ModifiedJulianDate)
{
    
    using library::physics::time::Scale ;
    using library::physics::time::Instant ;

    {

        FAIL() ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Physics_Time_Instant, Test_1)
{
    
    using library::physics::time::Scale ;
    using library::physics::time::DateTime ;
    using library::physics::time::Instant ;

    {

        Instant instant = Instant::DateTime(DateTime::Parse("2000-01-01 12:00:00"), Scale::TT) ;

        std::cout << instant.getString(Scale::TT) << std::endl  ;
        std::cout << instant.getString(Scale::TAI) << std::endl  ;
        std::cout << instant.getString(Scale::UTC) << std::endl  ;

    }

    {

        Instant instant = Instant::DateTime(DateTime::Parse("2000-01-01 12:00:00"), Scale::TAI) ;

        std::cout << instant.getString(Scale::TT) << std::endl  ;
        std::cout << instant.getString(Scale::TAI) << std::endl  ;
        std::cout << instant.getString(Scale::UTC) << std::endl  ;

    }

    {

        Instant instant = Instant::DateTime(DateTime::Parse("2000-01-01 12:00:00"), Scale::UTC) ;

        std::cout << instant.getString(Scale::TT) << std::endl  ;
        std::cout << instant.getString(Scale::TAI) << std::endl  ;
        std::cout << instant.getString(Scale::UTC) << std::endl  ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////