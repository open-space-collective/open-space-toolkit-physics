////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Units/ElectricCurrent.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Units/ElectricCurrent.hpp>
#include <Library/Core/Types/Real.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Physics_Units_ElectricCurrent, Constructor)
{

    using library::core::types::Real ;
    using library::physics::units::ElectricCurrent ;

    {

        const Real value = 123.456 ;
        const ElectricCurrent::Unit unit = ElectricCurrent::Unit::Ampere ;

        EXPECT_NO_THROW(ElectricCurrent(value, unit)) ;

    }

    {

        const Real value = Real::Undefined() ;
        const ElectricCurrent::Unit unit = ElectricCurrent::Unit::Undefined ;

        EXPECT_NO_THROW(ElectricCurrent(value, unit)) ;

    }

}

TEST (Library_Physics_Units_ElectricCurrent, IsDefined)
{

    using library::core::types::Real ;
    using library::physics::units::ElectricCurrent ;

    {

        EXPECT_TRUE(ElectricCurrent(0.0, ElectricCurrent::Unit::Ampere).isDefined()) ;

        EXPECT_TRUE(ElectricCurrent(1.0, ElectricCurrent::Unit::Ampere).isDefined()) ;

    }

    {

        EXPECT_FALSE(ElectricCurrent::Undefined().isDefined()) ;
        EXPECT_FALSE(ElectricCurrent(Real::Undefined(), ElectricCurrent::Unit::Ampere).isDefined()) ;
        EXPECT_FALSE(ElectricCurrent(1.0, ElectricCurrent::Unit::Undefined).isDefined()) ;

    }

}

TEST (Library_Physics_Units_ElectricCurrent, GetUnit)
{

    using library::physics::units::ElectricCurrent ;

    {

        EXPECT_EQ(ElectricCurrent::Unit::Undefined, ElectricCurrent(1.0, ElectricCurrent::Unit::Undefined).getUnit()) ;
        EXPECT_EQ(ElectricCurrent::Unit::Ampere, ElectricCurrent(1.0, ElectricCurrent::Unit::Ampere).getUnit()) ;

    }

}

TEST (Library_Physics_Units_ElectricCurrent, In)
{

    using library::physics::units::ElectricCurrent ;

    {

        EXPECT_EQ(1.0, ElectricCurrent(1.0, ElectricCurrent::Unit::Ampere).in(ElectricCurrent::Unit::Ampere)) ;

    }

    {

        EXPECT_FALSE(ElectricCurrent::Undefined().in(ElectricCurrent::Unit::Ampere).isDefined()) ;

    }

}

TEST (Library_Physics_Units_ElectricCurrent, InAmperes)
{

    using library::physics::units::ElectricCurrent ;

    {

        EXPECT_EQ(123.456, ElectricCurrent(123.456, ElectricCurrent::Unit::Ampere).inAmperes()) ;

    }

    {

        EXPECT_FALSE(ElectricCurrent::Undefined().inAmperes().isDefined()) ;

    }

}

TEST (Library_Physics_Units_ElectricCurrent, ToString)
{

    using library::physics::units::ElectricCurrent ;

    {

        EXPECT_EQ("1.0 [A]", ElectricCurrent(1.0, ElectricCurrent::Unit::Ampere).toString()) ;

        EXPECT_EQ("-1.0 [A]", ElectricCurrent(-1.0, ElectricCurrent::Unit::Ampere).toString()) ;

        EXPECT_EQ("123.456 [A]", ElectricCurrent(123.456, ElectricCurrent::Unit::Ampere).toString()) ;

    }

    {

        EXPECT_EQ("1.000 [A]", ElectricCurrent(1.0, ElectricCurrent::Unit::Ampere).toString(3)) ;

        EXPECT_EQ("-1.000 [A]", ElectricCurrent(-1.0, ElectricCurrent::Unit::Ampere).toString(3)) ;

        EXPECT_EQ("123.456 [A]", ElectricCurrent(123.456123, ElectricCurrent::Unit::Ampere).toString(3)) ;

    }

    {

        EXPECT_ANY_THROW(ElectricCurrent::Undefined().toString()) ;

    }

}

TEST (Library_Physics_Units_ElectricCurrent, Undefined)
{

    using library::physics::units::ElectricCurrent ;

    {

        EXPECT_NO_THROW(ElectricCurrent::Undefined()) ;
        EXPECT_FALSE(ElectricCurrent::Undefined().isDefined()) ;

        // EXPECT_NO_THROW(ElectricCurrent::Undefined().in(ElectricCurrent::Unit::Ampere)) ;

    }

}

TEST (Library_Physics_Units_ElectricCurrent, Amperes)
{

    using library::physics::units::ElectricCurrent ;

    {

        EXPECT_NO_THROW(ElectricCurrent::Amperes(123.456)) ;
        EXPECT_TRUE(ElectricCurrent::Amperes(123.456).isDefined()) ;

        EXPECT_EQ(123.456, ElectricCurrent::Amperes(123.456).in(ElectricCurrent::Unit::Ampere)) ;

    }

}

TEST (Library_Physics_Units_ElectricCurrent, StringFromUnit)
{

    using library::physics::units::ElectricCurrent ;

    {

        EXPECT_EQ("Undefined", ElectricCurrent::StringFromUnit(ElectricCurrent::Unit::Undefined)) ;
        EXPECT_EQ("Ampere", ElectricCurrent::StringFromUnit(ElectricCurrent::Unit::Ampere)) ;

    }

}

TEST (Library_Physics_Units_ElectricCurrent, SymbolFromUnit)
{

    using library::physics::units::ElectricCurrent ;

    {

        EXPECT_EQ("A", ElectricCurrent::SymbolFromUnit(ElectricCurrent::Unit::Ampere)) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////