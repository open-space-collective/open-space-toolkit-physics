////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Time/Scale.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Time/Scale.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Physics_Time_Scale, StringFromScale)
{

    using library::physics::time::Scale ;
    using library::physics::time::StringFromScale ;

    {

        EXPECT_EQ("Undefined", StringFromScale(Scale::Undefined)) ;
        EXPECT_EQ("UTC", StringFromScale(Scale::UTC)) ;
        EXPECT_EQ("TT", StringFromScale(Scale::TT)) ;
        EXPECT_EQ("TAI", StringFromScale(Scale::TAI)) ;
        EXPECT_EQ("UT1", StringFromScale(Scale::UT1)) ;
        EXPECT_EQ("TCG", StringFromScale(Scale::TCG)) ;
        EXPECT_EQ("TCB", StringFromScale(Scale::TCB)) ;
        EXPECT_EQ("TDB", StringFromScale(Scale::TDB)) ;
        EXPECT_EQ("GMST", StringFromScale(Scale::GMST)) ;
        EXPECT_EQ("GPST", StringFromScale(Scale::GPST)) ;
        EXPECT_EQ("GST", StringFromScale(Scale::GST)) ;
        EXPECT_EQ("GLST", StringFromScale(Scale::GLST)) ;
        EXPECT_EQ("BDT", StringFromScale(Scale::BDT)) ;
        EXPECT_EQ("QZSST", StringFromScale(Scale::QZSST)) ;
        EXPECT_EQ("IRNSST", StringFromScale(Scale::IRNSST)) ;

    }

}

TEST (Library_Physics_Time_Scale, ScaleFromString)
{

    using library::physics::time::Scale ;
    using library::physics::time::ScaleFromString ;

    {

        EXPECT_EQ(Scale::Undefined, ScaleFromString("Undefined")) ;
        EXPECT_EQ(Scale::UTC, ScaleFromString("UTC")) ;
        EXPECT_EQ(Scale::TT, ScaleFromString("TT")) ;
        EXPECT_EQ(Scale::TAI, ScaleFromString("TAI")) ;
        EXPECT_EQ(Scale::UT1, ScaleFromString("UT1")) ;
        EXPECT_EQ(Scale::TCG, ScaleFromString("TCG")) ;
        EXPECT_EQ(Scale::TCB, ScaleFromString("TCB")) ;
        EXPECT_EQ(Scale::TDB, ScaleFromString("TDB")) ;
        EXPECT_EQ(Scale::GMST, ScaleFromString("GMST")) ;
        EXPECT_EQ(Scale::GPST, ScaleFromString("GPST")) ;
        EXPECT_EQ(Scale::GST, ScaleFromString("GST")) ;
        EXPECT_EQ(Scale::GLST, ScaleFromString("GLST")) ;
        EXPECT_EQ(Scale::BDT, ScaleFromString("BDT")) ;
        EXPECT_EQ(Scale::QZSST, ScaleFromString("QZSST")) ;
        EXPECT_EQ(Scale::IRNSST, ScaleFromString("IRNSST")) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////