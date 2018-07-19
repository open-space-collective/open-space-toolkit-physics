////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Units/Time.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Units/Time.hpp>
#include <Library/Core/Types/Real.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Physics_Units_Time, Constructor)
{

    using library::core::types::Real ;
    using library::physics::units::Time ;

    {

        const Real value = 123.456 ;
        const Time::Unit unit = Time::Unit::Second ;

        EXPECT_NO_THROW(Time(value, unit)) ;

    }

    {

        const Real value = Real::Undefined() ;
        const Time::Unit unit = Time::Unit::Undefined ;

        EXPECT_NO_THROW(Time(value, unit)) ;

    }

}

TEST (Library_Physics_Units_Time, IsDefined)
{

    using library::core::types::Real ;
    using library::physics::units::Time ;

    {

        EXPECT_TRUE(Time(0.0, Time::Unit::Second).isDefined()) ;
        
        EXPECT_TRUE(Time(1.0, Time::Unit::Nanosecond).isDefined()) ;
        EXPECT_TRUE(Time(1.0, Time::Unit::Microsecond).isDefined()) ;
        EXPECT_TRUE(Time(1.0, Time::Unit::Millisecond).isDefined()) ;
        EXPECT_TRUE(Time(1.0, Time::Unit::Second).isDefined()) ;
        EXPECT_TRUE(Time(1.0, Time::Unit::Minute).isDefined()) ;
        EXPECT_TRUE(Time(1.0, Time::Unit::Hour).isDefined()) ;
        EXPECT_TRUE(Time(1.0, Time::Unit::Day).isDefined()) ;
        EXPECT_TRUE(Time(1.0, Time::Unit::Week).isDefined()) ;

    }

    {

        EXPECT_FALSE(Time::Undefined().isDefined()) ;
        EXPECT_FALSE(Time(Real::Undefined(), Time::Unit::Second).isDefined()) ;
        EXPECT_FALSE(Time(1.0, Time::Unit::Undefined).isDefined()) ;

    }

}

TEST (Library_Physics_Units_Time, ToString)
{

    using library::physics::units::Time ; 

    {

        EXPECT_EQ("1.0 [ns]", Time(1.0, Time::Unit::Nanosecond).toString()) ;
        EXPECT_EQ("1.0 [us]", Time(1.0, Time::Unit::Microsecond).toString()) ;
        EXPECT_EQ("1.0 [ms]", Time(1.0, Time::Unit::Millisecond).toString()) ;
        EXPECT_EQ("1.0 [s]", Time(1.0, Time::Unit::Second).toString()) ;
        EXPECT_EQ("1.0 [min]", Time(1.0, Time::Unit::Minute).toString()) ;
        EXPECT_EQ("1.0 [hr]", Time(1.0, Time::Unit::Hour).toString()) ;
        EXPECT_EQ("1.0 [day]", Time(1.0, Time::Unit::Day).toString()) ;
        EXPECT_EQ("1.0 [week]", Time(1.0, Time::Unit::Week).toString()) ;

        EXPECT_EQ("-1.0 [ns]", Time(-1.0, Time::Unit::Nanosecond).toString()) ;
        EXPECT_EQ("-1.0 [us]", Time(-1.0, Time::Unit::Microsecond).toString()) ;
        EXPECT_EQ("-1.0 [ms]", Time(-1.0, Time::Unit::Millisecond).toString()) ;
        EXPECT_EQ("-1.0 [s]", Time(-1.0, Time::Unit::Second).toString()) ;
        EXPECT_EQ("-1.0 [min]", Time(-1.0, Time::Unit::Minute).toString()) ;
        EXPECT_EQ("-1.0 [hr]", Time(-1.0, Time::Unit::Hour).toString()) ;
        EXPECT_EQ("-1.0 [day]", Time(-1.0, Time::Unit::Day).toString()) ;
        EXPECT_EQ("-1.0 [week]", Time(-1.0, Time::Unit::Week).toString()) ;

        EXPECT_EQ("123.456 [ns]", Time(123.456, Time::Unit::Nanosecond).toString()) ;
        EXPECT_EQ("123.456 [us]", Time(123.456, Time::Unit::Microsecond).toString()) ;
        EXPECT_EQ("123.456 [ms]", Time(123.456, Time::Unit::Millisecond).toString()) ;
        EXPECT_EQ("123.456 [s]", Time(123.456, Time::Unit::Second).toString()) ;
        EXPECT_EQ("123.456 [min]", Time(123.456, Time::Unit::Minute).toString()) ;
        EXPECT_EQ("123.456 [hr]", Time(123.456, Time::Unit::Hour).toString()) ;
        EXPECT_EQ("123.456 [day]", Time(123.456, Time::Unit::Day).toString()) ;
        EXPECT_EQ("123.456 [week]", Time(123.456, Time::Unit::Week).toString()) ;

    }

    {

        EXPECT_EQ("1.000 [ns]", Time(1.0, Time::Unit::Nanosecond).toString(3)) ;
        EXPECT_EQ("1.000 [us]", Time(1.0, Time::Unit::Microsecond).toString(3)) ;
        EXPECT_EQ("1.000 [ms]", Time(1.0, Time::Unit::Millisecond).toString(3)) ;
        EXPECT_EQ("1.000 [s]", Time(1.0, Time::Unit::Second).toString(3)) ;
        EXPECT_EQ("1.000 [min]", Time(1.0, Time::Unit::Minute).toString(3)) ;
        EXPECT_EQ("1.000 [hr]", Time(1.0, Time::Unit::Hour).toString(3)) ;
        EXPECT_EQ("1.000 [day]", Time(1.0, Time::Unit::Day).toString(3)) ;
        EXPECT_EQ("1.000 [week]", Time(1.0, Time::Unit::Week).toString(3)) ;

        EXPECT_EQ("-1.000 [ns]", Time(-1.0, Time::Unit::Nanosecond).toString(3)) ;
        EXPECT_EQ("-1.000 [us]", Time(-1.0, Time::Unit::Microsecond).toString(3)) ;
        EXPECT_EQ("-1.000 [ms]", Time(-1.0, Time::Unit::Millisecond).toString(3)) ;
        EXPECT_EQ("-1.000 [s]", Time(-1.0, Time::Unit::Second).toString(3)) ;
        EXPECT_EQ("-1.000 [min]", Time(-1.0, Time::Unit::Minute).toString(3)) ;
        EXPECT_EQ("-1.000 [hr]", Time(-1.0, Time::Unit::Hour).toString(3)) ;
        EXPECT_EQ("-1.000 [day]", Time(-1.0, Time::Unit::Day).toString(3)) ;
        EXPECT_EQ("-1.000 [week]", Time(-1.0, Time::Unit::Week).toString(3)) ;

        EXPECT_EQ("123.456 [ns]", Time(123.456123, Time::Unit::Nanosecond).toString(3)) ;
        EXPECT_EQ("123.456 [us]", Time(123.456123, Time::Unit::Microsecond).toString(3)) ;
        EXPECT_EQ("123.456 [ms]", Time(123.456123, Time::Unit::Millisecond).toString(3)) ;
        EXPECT_EQ("123.456 [s]", Time(123.456123, Time::Unit::Second).toString(3)) ;
        EXPECT_EQ("123.456 [min]", Time(123.456123, Time::Unit::Minute).toString(3)) ;
        EXPECT_EQ("123.456 [hr]", Time(123.456123, Time::Unit::Hour).toString(3)) ;
        EXPECT_EQ("123.456 [day]", Time(123.456123, Time::Unit::Day).toString(3)) ;
        EXPECT_EQ("123.456 [week]", Time(123.456123, Time::Unit::Week).toString(3)) ;

    }

    {

        EXPECT_ANY_THROW(Time::Undefined().toString()) ;
        
    }

}

TEST (Library_Physics_Units_Time, Undefined)
{

    using library::physics::units::Time ;

    {

        EXPECT_NO_THROW(Time::Undefined()) ;
        EXPECT_FALSE(Time::Undefined().isDefined()) ;

        // EXPECT_NO_THROW(Time::Undefined().in(Time::Unit::Second)) ;

    }

}

TEST (Library_Physics_Units_Time, StringFromUnit)
{

    using library::physics::units::Time ;

    {

        EXPECT_EQ("Undefined", Time::StringFromUnit(Time::Unit::Undefined)) ;
        EXPECT_EQ("Nanosecond", Time::StringFromUnit(Time::Unit::Nanosecond)) ;
        EXPECT_EQ("Microsecond", Time::StringFromUnit(Time::Unit::Microsecond)) ;
        EXPECT_EQ("Millisecond", Time::StringFromUnit(Time::Unit::Millisecond)) ;
        EXPECT_EQ("Second", Time::StringFromUnit(Time::Unit::Second)) ;
        EXPECT_EQ("Minute", Time::StringFromUnit(Time::Unit::Minute)) ;
        EXPECT_EQ("Hour", Time::StringFromUnit(Time::Unit::Hour)) ;
        EXPECT_EQ("Day", Time::StringFromUnit(Time::Unit::Day)) ;
        EXPECT_EQ("Week", Time::StringFromUnit(Time::Unit::Week)) ;

    }

}

TEST (Library_Physics_Units_Time, SymbolFromUnit)
{

    using library::physics::units::Time ;

    {

        EXPECT_EQ("ns", Time::SymbolFromUnit(Time::Unit::Nanosecond)) ;
        EXPECT_EQ("us", Time::SymbolFromUnit(Time::Unit::Microsecond)) ;
        EXPECT_EQ("ms", Time::SymbolFromUnit(Time::Unit::Millisecond)) ;
        EXPECT_EQ("s", Time::SymbolFromUnit(Time::Unit::Second)) ;
        EXPECT_EQ("min", Time::SymbolFromUnit(Time::Unit::Minute)) ;
        EXPECT_EQ("hr", Time::SymbolFromUnit(Time::Unit::Hour)) ;
        EXPECT_EQ("day", Time::SymbolFromUnit(Time::Unit::Day)) ;
        EXPECT_EQ("week", Time::SymbolFromUnit(Time::Unit::Week)) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////