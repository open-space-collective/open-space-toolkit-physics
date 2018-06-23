////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Time/DateTime.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Time/DateTime.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Physics_Time_DateTime, Constructor)
{

    using library::physics::time::Date ;
    using library::physics::time::Time ;
    using library::physics::time::DateTime ;

    {

        EXPECT_NO_THROW(DateTime(Date(2018, 1, 1), Time(1, 2, 3))) ;
        
        EXPECT_NO_THROW(DateTime(Date(1400, 1, 1), Time(1, 2, 3, 123, 456, 789))) ;
        EXPECT_NO_THROW(DateTime(Date(9999, 1, 1), Time(1, 2, 3, 123, 456, 789))) ;

    }

    {

        EXPECT_ANY_THROW(DateTime(Date(2018, 2, 29), Time(0, 0, 0))) ;
        
        EXPECT_ANY_THROW(DateTime(Date(0, 1, 1), Time(0, 0, 0))) ;
        EXPECT_ANY_THROW(DateTime(Date(1399, 12, 31), Time(0, 0, 0))) ;
        EXPECT_ANY_THROW(DateTime(Date(10000, 1, 1), Time(0, 0, 0))) ;

        EXPECT_ANY_THROW(DateTime(Date(2018, 0, 1), Time(0, 0, 0))) ;
        EXPECT_ANY_THROW(DateTime(Date(2018, 13, 1), Time(0, 0, 0))) ;

        EXPECT_ANY_THROW(DateTime(Date(2018, 1, 0), Time(0, 0, 0))) ;
        EXPECT_ANY_THROW(DateTime(Date(2018, 1, 32), Time(0, 0, 0))) ;

        EXPECT_ANY_THROW(DateTime(Date(2018, 1, 1), Time(24, 0, 0, 0, 0, 0))) ;

        EXPECT_ANY_THROW(DateTime(Date(2018, 1, 1), Time(0, 60, 0, 0, 0, 0))) ;

        EXPECT_ANY_THROW(DateTime(Date(2018, 1, 1), Time(0, 0, 61, 0, 0, 0))) ;

        EXPECT_ANY_THROW(DateTime(Date(2018, 1, 1), Time(0, 0, 0, 1000, 0, 0))) ;

        EXPECT_ANY_THROW(DateTime(Date(2018, 1, 1), Time(0, 0, 0, 0, 1000, 0))) ;

        EXPECT_ANY_THROW(DateTime(Date(2018, 1, 1), Time(0, 0, 0, 0, 0, 1000))) ;

    }

    {

        EXPECT_NO_THROW(DateTime(2018, 1, 1, 1, 2, 3)) ;
        
        EXPECT_NO_THROW(DateTime(1400, 1, 1, 1, 2, 3, 123, 456, 789)) ;
        EXPECT_NO_THROW(DateTime(9999, 1, 1, 1, 2, 3, 123, 456, 789)) ;

    }

    {

        EXPECT_ANY_THROW(DateTime(2018, 2, 29, 0, 0, 0)) ;

        EXPECT_ANY_THROW(DateTime(0, 1, 1, 0, 0, 0)) ;
        EXPECT_ANY_THROW(DateTime(1399, 12, 31, 0, 0, 0)) ;
        EXPECT_ANY_THROW(DateTime(10000, 1, 1, 0, 0, 0)) ;

        EXPECT_ANY_THROW(DateTime(2018, 0, 1, 0, 0, 0)) ;
        EXPECT_ANY_THROW(DateTime(2018, 13, 1, 0, 0, 0)) ;

        EXPECT_ANY_THROW(DateTime(2018, 1, 0, 0, 0, 0)) ;
        EXPECT_ANY_THROW(DateTime(2018, 1, 32, 0, 0, 0)) ;

        EXPECT_ANY_THROW(DateTime(2018, 1, 1, 24, 0, 0, 0, 0, 0)) ;

        EXPECT_ANY_THROW(DateTime(2018, 1, 1, 0, 60, 0, 0, 0, 0)) ;

        EXPECT_ANY_THROW(DateTime(2018, 1, 1, 0, 0, 61, 0, 0, 0)) ;

        EXPECT_ANY_THROW(DateTime(2018, 1, 1, 0, 0, 0, 1000, 0, 0)) ;

        EXPECT_ANY_THROW(DateTime(2018, 1, 1, 0, 0, 0, 0, 1000, 0)) ;

        EXPECT_ANY_THROW(DateTime(2018, 1, 1, 0, 0, 0, 0, 0, 1000)) ;

    }

}

TEST (Library_Physics_Time_DateTime, EqualToOperator)
{

    using library::physics::time::DateTime ;

    {

        EXPECT_TRUE(DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789) == DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789)) ;
        
        EXPECT_TRUE(DateTime(1400, 1, 2, 12, 34, 56, 123, 456, 789) == DateTime(1400, 1, 2, 12, 34, 56, 123, 456, 789)) ;
        EXPECT_TRUE(DateTime(9999, 1, 2, 12, 34, 56, 123, 456, 789) == DateTime(9999, 1, 2, 12, 34, 56, 123, 456, 789)) ;

    }

    {

        EXPECT_FALSE(DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789) == DateTime(2019, 1, 2, 12, 34, 56, 123, 456, 789)) ;
        EXPECT_FALSE(DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789) == DateTime(2018, 2, 2, 12, 34, 56, 123, 456, 789)) ;
        EXPECT_FALSE(DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789) == DateTime(2018, 1, 3, 12, 34, 56, 123, 456, 789)) ;
        EXPECT_FALSE(DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789) == DateTime(2018, 1, 2, 13, 34, 56, 123, 456, 789)) ;
        EXPECT_FALSE(DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789) == DateTime(2018, 1, 2, 12, 35, 56, 123, 456, 789)) ;
        EXPECT_FALSE(DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789) == DateTime(2018, 1, 2, 12, 34, 57, 123, 456, 789)) ;
        EXPECT_FALSE(DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789) == DateTime(2018, 1, 2, 12, 34, 56, 124, 456, 789)) ;
        EXPECT_FALSE(DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789) == DateTime(2018, 1, 2, 12, 34, 56, 123, 457, 789)) ;
        EXPECT_FALSE(DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789) == DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 790)) ;

    }

    {

        EXPECT_FALSE(DateTime::Undefined() == DateTime::Undefined()) ;

    }

}

TEST (Library_Physics_Time_DateTime, NotEqualToOperator)
{

    using library::physics::time::DateTime ;

    {

        EXPECT_TRUE(DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789) != DateTime(2019, 1, 2, 12, 34, 56, 123, 456, 789)) ;
        EXPECT_TRUE(DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789) != DateTime(2018, 2, 2, 12, 34, 56, 123, 456, 789)) ;
        EXPECT_TRUE(DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789) != DateTime(2018, 1, 3, 12, 34, 56, 123, 456, 789)) ;
        EXPECT_TRUE(DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789) != DateTime(2018, 1, 2, 13, 34, 56, 123, 456, 789)) ;
        EXPECT_TRUE(DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789) != DateTime(2018, 1, 2, 12, 35, 56, 123, 456, 789)) ;
        EXPECT_TRUE(DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789) != DateTime(2018, 1, 2, 12, 34, 57, 123, 456, 789)) ;
        EXPECT_TRUE(DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789) != DateTime(2018, 1, 2, 12, 34, 56, 124, 456, 789)) ;
        EXPECT_TRUE(DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789) != DateTime(2018, 1, 2, 12, 34, 56, 123, 457, 789)) ;
        EXPECT_TRUE(DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789) != DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 790)) ;

    }

    {

        EXPECT_FALSE(DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789) != DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789)) ;
        
        EXPECT_FALSE(DateTime(1400, 1, 2, 12, 34, 56, 123, 456, 789) != DateTime(1400, 1, 2, 12, 34, 56, 123, 456, 789)) ;
        EXPECT_FALSE(DateTime(9999, 1, 2, 12, 34, 56, 123, 456, 789) != DateTime(9999, 1, 2, 12, 34, 56, 123, 456, 789)) ;

    }

    {

        EXPECT_TRUE(DateTime::Undefined() != DateTime::Undefined()) ;

    }

}

TEST (Library_Physics_Time_DateTime, StreamOperator)
{

    using library::physics::time::DateTime ;

    {

        testing::internal::CaptureStdout() ;

        EXPECT_NO_THROW(std::cout << DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789) << std::endl) ;

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty()) ;

    }

}

TEST (Library_Physics_Time_DateTime, IsDefined)
{

    using library::physics::time::DateTime ;

    {

        EXPECT_TRUE(DateTime(2018, 1, 2, 12, 34, 56).isDefined()) ;
        EXPECT_TRUE(DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789).isDefined()) ;

    }

    {
        
        EXPECT_FALSE(DateTime::Undefined().isDefined()) ;

    }

}

TEST (Library_Physics_Time_DateTime, AccessDate)
{

    using library::physics::time::Date ;
    using library::physics::time::DateTime ;

    {

        EXPECT_EQ(Date(2018, 1, 2), DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789).accessDate()) ;

    }

    {
        
        EXPECT_ANY_THROW(DateTime::Undefined().accessDate()) ;

    }

}

TEST (Library_Physics_Time_DateTime, AccessTime)
{

    using library::physics::time::Time ;
    using library::physics::time::DateTime ;

    {

        EXPECT_EQ(Time(12, 34, 56, 123, 456, 789), DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789).accessTime()) ;

    }

    {
        
        EXPECT_ANY_THROW(DateTime::Undefined().accessTime()) ;

    }

}

TEST (Library_Physics_Time_DateTime, GetString)
{
    
    using library::physics::time::DateTime ;

    {

        EXPECT_EQ("2018-01-02 12:34:56.123.456.789", DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789).getString()) ;

        EXPECT_EQ("1400-01-02 12:34:56.123.456.789", DateTime(1400, 1, 2, 12, 34, 56, 123, 456, 789).getString()) ;
        EXPECT_EQ("9999-12-31 12:34:56.123.456.789", DateTime(9999, 12, 31, 12, 34, 56, 123, 456, 789).getString()) ;

    }

    {

        EXPECT_EQ("2018-01-02 12:34:56", DateTime(2018, 1, 2, 12, 34, 56, 0, 0, 0).getString(DateTime::Format::Standard)) ;
        EXPECT_EQ("2018-01-02 12:34:56.123", DateTime(2018, 1, 2, 12, 34, 56, 123, 0, 0).getString(DateTime::Format::Standard)) ;
        EXPECT_EQ("2018-01-02 12:34:56.123.456", DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 0).getString(DateTime::Format::Standard)) ;
        EXPECT_EQ("2018-01-02 12:34:56.123.456.789", DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789).getString(DateTime::Format::Standard)) ;

        EXPECT_EQ("1400-01-02 12:34:56.123.456.789", DateTime(1400, 1, 2, 12, 34, 56, 123, 456, 789).getString(DateTime::Format::Standard)) ;
        EXPECT_EQ("9999-12-31 12:34:56.123.456.789", DateTime(9999, 12, 31, 12, 34, 56, 123, 456, 789).getString(DateTime::Format::Standard)) ;

    }

    {

        EXPECT_EQ("2018-01-02T12:34:56", DateTime(2018, 1, 2, 12, 34, 56, 0, 0, 0).getString(DateTime::Format::ISO8601)) ;
        EXPECT_EQ("2018-01-02T12:34:56.123", DateTime(2018, 1, 2, 12, 34, 56, 123, 0, 0).getString(DateTime::Format::ISO8601)) ;
        EXPECT_EQ("2018-01-02T12:34:56.123456", DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 0).getString(DateTime::Format::ISO8601)) ;
        EXPECT_EQ("2018-01-02T12:34:56.123456789", DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789).getString(DateTime::Format::ISO8601)) ;

        EXPECT_EQ("1400-01-02T12:34:56.123456789", DateTime(1400, 1, 2, 12, 34, 56, 123, 456, 789).getString(DateTime::Format::ISO8601)) ;
        EXPECT_EQ("9999-12-31T12:34:56.123456789", DateTime(9999, 12, 31, 12, 34, 56, 123, 456, 789).getString(DateTime::Format::ISO8601)) ;

    }

    {
        
        EXPECT_ANY_THROW(DateTime::Undefined().getString()) ;

    }

}

TEST (Library_Physics_Time_DateTime, Undefined)
{

    using library::physics::time::DateTime ;

    {

        EXPECT_NO_THROW(DateTime::Undefined()) ;

        EXPECT_FALSE(DateTime::Undefined().isDefined()) ;

    }

}

TEST (Library_Physics_Time_DateTime, J2000)
{

    using library::physics::time::DateTime ;

    {

        EXPECT_EQ(DateTime(2000, 1, 1, 12, 0, 0), DateTime::J2000()) ;

    }

}

TEST (Library_Physics_Time_DateTime, GPS)
{

    using library::physics::time::DateTime ;

    {

        EXPECT_EQ(DateTime(1980, 1, 6, 0, 0, 0), DateTime::GPS()) ;

    }

}

TEST (Library_Physics_Time_DateTime, Unix)
{

    using library::physics::time::DateTime ;

    {

        EXPECT_EQ(DateTime(1970, 1, 1, 0, 0, 0), DateTime::Unix()) ;

    }

}

TEST (Library_Physics_Time_DateTime, ModifiedJulianDate)
{

    using library::physics::time::DateTime ;

    {

        EXPECT_EQ(DateTime(1858, 11, 17, 0, 0, 0), DateTime::ModifiedJulianDate()) ;

    }

}

TEST (Library_Physics_Time_DateTime, Parse)
{

    using library::physics::time::DateTime ;

    // Undefined (automatic format detection)

    {

        EXPECT_EQ(DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789), DateTime::Parse("2018-01-02 12:34:56.123.456.789")) ;
        EXPECT_EQ(DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789), DateTime::Parse("2018-01-02T12:34:56.123456789")) ;

    }

    // Standard

    {

        EXPECT_EQ(DateTime(2018, 1, 2, 12, 34, 56), DateTime::Parse("2018-01-02 12:34:56", DateTime::Format::Standard)) ;

        EXPECT_EQ(DateTime(2018, 1, 2, 12, 34, 56, 100), DateTime::Parse("2018-01-02 12:34:56.1", DateTime::Format::Standard)) ;
        EXPECT_EQ(DateTime(2018, 1, 2, 12, 34, 56, 120), DateTime::Parse("2018-01-02 12:34:56.12", DateTime::Format::Standard)) ;
        EXPECT_EQ(DateTime(2018, 1, 2, 12, 34, 56, 123), DateTime::Parse("2018-01-02 12:34:56.123", DateTime::Format::Standard)) ;

        EXPECT_EQ(DateTime(2018, 1, 2, 12, 34, 56, 123, 400), DateTime::Parse("2018-01-02 12:34:56.123.4", DateTime::Format::Standard)) ;
        EXPECT_EQ(DateTime(2018, 1, 2, 12, 34, 56, 123, 450), DateTime::Parse("2018-01-02 12:34:56.123.45", DateTime::Format::Standard)) ;
        EXPECT_EQ(DateTime(2018, 1, 2, 12, 34, 56, 123, 456), DateTime::Parse("2018-01-02 12:34:56.123.456", DateTime::Format::Standard)) ;

        EXPECT_EQ(DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 700), DateTime::Parse("2018-01-02 12:34:56.123.456.7", DateTime::Format::Standard)) ;
        EXPECT_EQ(DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 780), DateTime::Parse("2018-01-02 12:34:56.123.456.78", DateTime::Format::Standard)) ;
        EXPECT_EQ(DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789), DateTime::Parse("2018-01-02 12:34:56.123.456.789", DateTime::Format::Standard)) ;

        EXPECT_EQ(DateTime(1400, 1, 1, 0, 0, 0), DateTime::Parse("1400-01-01 00:00:00", DateTime::Format::Standard)) ;
        EXPECT_EQ(DateTime(9999, 12, 31, 23, 59, 59), DateTime::Parse("9999-12-31 23:59:59", DateTime::Format::Standard)) ;

    }

    {

        EXPECT_ANY_THROW(DateTime::Parse("", DateTime::Format::Standard)) ;
        EXPECT_ANY_THROW(DateTime::Parse("abc", DateTime::Format::Standard)) ;
        EXPECT_ANY_THROW(DateTime::Parse("2018", DateTime::Format::Standard)) ;
        EXPECT_ANY_THROW(DateTime::Parse("2018-01", DateTime::Format::Standard)) ;
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-02", DateTime::Format::Standard)) ;
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-02 01", DateTime::Format::Standard)) ;
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-02 1:34", DateTime::Format::Standard)) ;
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-02 1:34:56", DateTime::Format::Standard)) ;
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-02 12:3:56", DateTime::Format::Standard)) ;
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-02 12:34:5", DateTime::Format::Standard)) ;
        EXPECT_ANY_THROW(DateTime::Parse("2018-00-01 24:34:56", DateTime::Format::Standard)) ;
        EXPECT_ANY_THROW(DateTime::Parse("2018-13-01 24:34:56", DateTime::Format::Standard)) ;
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-00 24:34:56", DateTime::Format::Standard)) ;
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-32 24:34:56", DateTime::Format::Standard)) ;
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-02 24:34:56", DateTime::Format::Standard)) ;
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-02 12:60:56", DateTime::Format::Standard)) ;
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-02 12:34:61", DateTime::Format::Standard)) ;
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-02 12:34:61.", DateTime::Format::Standard)) ;
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-02 -12:34:56", DateTime::Format::Standard)) ;
        EXPECT_ANY_THROW(DateTime::Parse("1399-12-31 23:59:59", DateTime::Format::Standard)) ;
        EXPECT_ANY_THROW(DateTime::Parse("10000-01-01 00:00:00", DateTime::Format::Standard)) ;

    }

    // ISO 8601

    {

        EXPECT_EQ(DateTime(2018, 1, 2, 12, 34, 56), DateTime::Parse("2018-01-02T12:34:56", DateTime::Format::ISO8601)) ;

        EXPECT_EQ(DateTime(2018, 1, 2, 12, 34, 56, 100), DateTime::Parse("2018-01-02T12:34:56.1", DateTime::Format::ISO8601)) ;
        EXPECT_EQ(DateTime(2018, 1, 2, 12, 34, 56, 120), DateTime::Parse("2018-01-02T12:34:56.12", DateTime::Format::ISO8601)) ;
        EXPECT_EQ(DateTime(2018, 1, 2, 12, 34, 56, 123), DateTime::Parse("2018-01-02T12:34:56.123", DateTime::Format::ISO8601)) ;

        EXPECT_EQ(DateTime(2018, 1, 2, 12, 34, 56, 123, 400), DateTime::Parse("2018-01-02T12:34:56.1234", DateTime::Format::ISO8601)) ;
        EXPECT_EQ(DateTime(2018, 1, 2, 12, 34, 56, 123, 450), DateTime::Parse("2018-01-02T12:34:56.12345", DateTime::Format::ISO8601)) ;
        EXPECT_EQ(DateTime(2018, 1, 2, 12, 34, 56, 123, 456), DateTime::Parse("2018-01-02T12:34:56.123456", DateTime::Format::ISO8601)) ;

        EXPECT_EQ(DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 700), DateTime::Parse("2018-01-02T12:34:56.1234567", DateTime::Format::ISO8601)) ;
        EXPECT_EQ(DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 780), DateTime::Parse("2018-01-02T12:34:56.12345678", DateTime::Format::ISO8601)) ;
        EXPECT_EQ(DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789), DateTime::Parse("2018-01-02T12:34:56.123456789", DateTime::Format::ISO8601)) ;

        EXPECT_EQ(DateTime(1400, 1, 1, 0, 0, 0), DateTime::Parse("1400-01-01T00:00:00", DateTime::Format::ISO8601)) ;
        EXPECT_EQ(DateTime(9999, 12, 31, 23, 59, 59), DateTime::Parse("9999-12-31T23:59:59", DateTime::Format::ISO8601)) ;

    }

    {

        EXPECT_ANY_THROW(DateTime::Parse("", DateTime::Format::ISO8601)) ;
        EXPECT_ANY_THROW(DateTime::Parse("abc", DateTime::Format::ISO8601)) ;
        EXPECT_ANY_THROW(DateTime::Parse("2018", DateTime::Format::ISO8601)) ;
        EXPECT_ANY_THROW(DateTime::Parse("2018-01", DateTime::Format::ISO8601)) ;
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-02", DateTime::Format::ISO8601)) ;
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-02T01", DateTime::Format::ISO8601)) ;
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-02T1:34", DateTime::Format::ISO8601)) ;
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-02T1:34:56", DateTime::Format::ISO8601)) ;
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-02T12:3:56", DateTime::Format::ISO8601)) ;
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-02T12:34:5", DateTime::Format::ISO8601)) ;
        EXPECT_ANY_THROW(DateTime::Parse("2018-00-01T24:34:56", DateTime::Format::ISO8601)) ;
        EXPECT_ANY_THROW(DateTime::Parse("2018-13-01T24:34:56", DateTime::Format::ISO8601)) ;
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-00T24:34:56", DateTime::Format::ISO8601)) ;
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-32T24:34:56", DateTime::Format::ISO8601)) ;
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-02T24:34:56", DateTime::Format::ISO8601)) ;
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-02T12:60:56", DateTime::Format::ISO8601)) ;
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-02T12:34:61", DateTime::Format::ISO8601)) ;
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-02T12:34:61.", DateTime::Format::ISO8601)) ;
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-02T-12:34:56", DateTime::Format::ISO8601)) ;
        EXPECT_ANY_THROW(DateTime::Parse("1399-12-31T23:59:59", DateTime::Format::ISO8601)) ;
        EXPECT_ANY_THROW(DateTime::Parse("10000-01-01T00:00:00", DateTime::Format::ISO8601)) ;
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-02T12:34:56.123.456", DateTime::Format::ISO8601)) ;
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-02T12:34:56.123.456.789", DateTime::Format::ISO8601)) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////