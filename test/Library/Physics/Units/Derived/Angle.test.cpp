////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Units/Derived/Angle.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Units/Derived/Angle.hpp>
#include <Library/Mathematics/Geometry/Angle.hpp>
#include <Library/Core/Types/Real.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Physics_Units_Derived_Angle, Constructor)
{

    using library::core::types::Real ;
    using library::physics::units::Angle ;

    {

        const Real value = 123.456 ;
        const Angle::Unit unit = Angle::Unit::Radian ;

        EXPECT_NO_THROW(Angle(value, unit)) ;

    }

    {

        const Real value = Real::Undefined() ;
        const Angle::Unit unit = Angle::Unit::Undefined ;

        EXPECT_NO_THROW(Angle(value, unit)) ;

    }

}

TEST (Library_Physics_Units_Derived_Angle, EqualToOperator)
{

    using library::core::types::Real ;
    using library::physics::units::Angle ;

    {

        EXPECT_TRUE(Angle(0.0, Angle::Unit::Radian) == Angle(0.0, Angle::Unit::Radian)) ;

        EXPECT_TRUE(Angle(+1.0, Angle::Unit::Radian) == Angle(+1.0, Angle::Unit::Radian)) ;
        EXPECT_TRUE(Angle(-1.0, Angle::Unit::Radian) == Angle(-1.0, Angle::Unit::Radian)) ;

    }

    {

        EXPECT_TRUE(Angle(0.0, Angle::Unit::Radian) == Angle(Real::TwoPi(), Angle::Unit::Radian)) ;
        EXPECT_TRUE(Angle(0.0, Angle::Unit::Radian) == Angle(2.0 * Real::TwoPi(), Angle::Unit::Radian)) ;
        EXPECT_TRUE(Angle(0.0, Angle::Unit::Radian) == Angle(4.0 * Real::TwoPi(), Angle::Unit::Radian)) ;

        EXPECT_TRUE(Angle(Real::TwoPi(), Angle::Unit::Radian) == Angle(0.0, Angle::Unit::Radian)) ;
        EXPECT_TRUE(Angle(Real::TwoPi(), Angle::Unit::Radian) == Angle(Real::TwoPi(), Angle::Unit::Radian)) ;
        EXPECT_TRUE(Angle(Real::TwoPi(), Angle::Unit::Radian) == Angle(2.0 * Real::TwoPi(), Angle::Unit::Radian)) ;
        EXPECT_TRUE(Angle(Real::TwoPi(), Angle::Unit::Radian) == Angle(4.0 * Real::TwoPi(), Angle::Unit::Radian)) ;

    }

    {

        EXPECT_TRUE(Angle(0.0, Angle::Unit::Degree) == Angle(0.0, Angle::Unit::Radian)) ;
        EXPECT_TRUE(Angle(0.0, Angle::Unit::Arcminute) == Angle(0.0, Angle::Unit::Radian)) ;
        EXPECT_TRUE(Angle(0.0, Angle::Unit::Arcsecond) == Angle(0.0, Angle::Unit::Radian)) ;
        EXPECT_TRUE(Angle(0.0, Angle::Unit::Revolution) == Angle(0.0, Angle::Unit::Radian)) ;

        EXPECT_TRUE(Angle(90.0, Angle::Unit::Degree) == Angle(Real::HalfPi(), Angle::Unit::Radian)) ;
        EXPECT_TRUE(Angle(5400.0, Angle::Unit::Arcminute) == Angle(Real::HalfPi(), Angle::Unit::Radian)) ;
        EXPECT_TRUE(Angle(324000.0, Angle::Unit::Arcsecond) == Angle(Real::HalfPi(), Angle::Unit::Radian)) ;
        EXPECT_TRUE(Angle(0.25, Angle::Unit::Revolution) == Angle(Real::HalfPi(), Angle::Unit::Radian)) ;

        EXPECT_TRUE(Angle(360.0, Angle::Unit::Degree) == Angle(0.0, Angle::Unit::Radian)) ;
        EXPECT_TRUE(Angle(21600.0, Angle::Unit::Arcminute) == Angle(0.0, Angle::Unit::Radian)) ;
        EXPECT_TRUE(Angle(1296000.0, Angle::Unit::Arcsecond) == Angle(0.0, Angle::Unit::Radian)) ;
        EXPECT_TRUE(Angle(1.0, Angle::Unit::Revolution) == Angle(0.0, Angle::Unit::Radian)) ;

    }

    {

        EXPECT_FALSE(Angle(1.0, Angle::Unit::Radian) == Angle(2.0, Angle::Unit::Radian)) ;
        EXPECT_FALSE(Angle(+1.0, Angle::Unit::Radian) == Angle(-1.0, Angle::Unit::Radian)) ;
        EXPECT_FALSE(Angle::Undefined() == Angle(1.0, Angle::Unit::Radian)) ;
        EXPECT_FALSE(Angle(1.0, Angle::Unit::Radian) == Angle::Undefined()) ;
        EXPECT_FALSE(Angle::Undefined() == Angle::Undefined()) ;

    }

    {

        EXPECT_FALSE(Angle(90.0, Angle::Unit::Degree) == Angle(Real::Pi(), Angle::Unit::Radian)) ;
        EXPECT_FALSE(Angle(5400.0, Angle::Unit::Arcminute) == Angle(Real::Pi(), Angle::Unit::Radian)) ;
        EXPECT_FALSE(Angle(324000.0, Angle::Unit::Arcsecond) == Angle(Real::Pi(), Angle::Unit::Radian)) ;
        EXPECT_FALSE(Angle(0.25, Angle::Unit::Revolution) == Angle(Real::Pi(), Angle::Unit::Radian)) ;

    }

}

TEST (Library_Physics_Units_Derived_Angle, NotEqualToOperator)
{

    using library::core::types::Real ;
    using library::physics::units::Angle ;

    {

        EXPECT_TRUE(Angle(1.0, Angle::Unit::Radian) != Angle(2.0, Angle::Unit::Radian)) ;
        EXPECT_TRUE(Angle(+1.0, Angle::Unit::Radian) != Angle(-1.0, Angle::Unit::Radian)) ;
        EXPECT_TRUE(Angle::Undefined() != Angle(1.0, Angle::Unit::Radian)) ;
        EXPECT_TRUE(Angle(1.0, Angle::Unit::Radian) != Angle::Undefined()) ;
        EXPECT_TRUE(Angle::Undefined() != Angle::Undefined()) ;

    }

    {

        EXPECT_TRUE(Angle(90.0, Angle::Unit::Degree) != Angle(Real::Pi(), Angle::Unit::Radian)) ;
        EXPECT_TRUE(Angle(5400.0, Angle::Unit::Arcminute) != Angle(Real::Pi(), Angle::Unit::Radian)) ;
        EXPECT_TRUE(Angle(324000.0, Angle::Unit::Arcsecond) != Angle(Real::Pi(), Angle::Unit::Radian)) ;
        EXPECT_TRUE(Angle(0.25, Angle::Unit::Revolution) != Angle(Real::Pi(), Angle::Unit::Radian)) ;

    }

    {

        EXPECT_FALSE(Angle(0.0, Angle::Unit::Radian) != Angle(0.0, Angle::Unit::Radian)) ;

        EXPECT_FALSE(Angle(+1.0, Angle::Unit::Radian) != Angle(+1.0, Angle::Unit::Radian)) ;
        EXPECT_FALSE(Angle(-1.0, Angle::Unit::Radian) != Angle(-1.0, Angle::Unit::Radian)) ;

    }

    {

        EXPECT_FALSE(Angle(0.0, Angle::Unit::Radian) != Angle(Real::TwoPi(), Angle::Unit::Radian)) ;
        EXPECT_FALSE(Angle(0.0, Angle::Unit::Radian) != Angle(2.0 * Real::TwoPi(), Angle::Unit::Radian)) ;
        EXPECT_FALSE(Angle(0.0, Angle::Unit::Radian) != Angle(4.0 * Real::TwoPi(), Angle::Unit::Radian)) ;

        EXPECT_FALSE(Angle(Real::TwoPi(), Angle::Unit::Radian) != Angle(0.0, Angle::Unit::Radian)) ;
        EXPECT_FALSE(Angle(Real::TwoPi(), Angle::Unit::Radian) != Angle(Real::TwoPi(), Angle::Unit::Radian)) ;
        EXPECT_FALSE(Angle(Real::TwoPi(), Angle::Unit::Radian) != Angle(2.0 * Real::TwoPi(), Angle::Unit::Radian)) ;
        EXPECT_FALSE(Angle(Real::TwoPi(), Angle::Unit::Radian) != Angle(4.0 * Real::TwoPi(), Angle::Unit::Radian)) ;

    }

    {

        EXPECT_FALSE(Angle(0.0, Angle::Unit::Degree) != Angle(0.0, Angle::Unit::Radian)) ;
        EXPECT_FALSE(Angle(0.0, Angle::Unit::Arcminute) != Angle(0.0, Angle::Unit::Radian)) ;
        EXPECT_FALSE(Angle(0.0, Angle::Unit::Arcsecond) != Angle(0.0, Angle::Unit::Radian)) ;
        EXPECT_FALSE(Angle(0.0, Angle::Unit::Revolution) != Angle(0.0, Angle::Unit::Radian)) ;

        EXPECT_FALSE(Angle(90.0, Angle::Unit::Degree) != Angle(Real::HalfPi(), Angle::Unit::Radian)) ;
        EXPECT_FALSE(Angle(5400.0, Angle::Unit::Arcminute) != Angle(Real::HalfPi(), Angle::Unit::Radian)) ;
        EXPECT_FALSE(Angle(324000.0, Angle::Unit::Arcsecond) != Angle(Real::HalfPi(), Angle::Unit::Radian)) ;
        EXPECT_FALSE(Angle(0.25, Angle::Unit::Revolution) != Angle(Real::HalfPi(), Angle::Unit::Radian)) ;

        EXPECT_FALSE(Angle(360.0, Angle::Unit::Degree) != Angle(0.0, Angle::Unit::Radian)) ;
        EXPECT_FALSE(Angle(21600.0, Angle::Unit::Arcminute) != Angle(0.0, Angle::Unit::Radian)) ;
        EXPECT_FALSE(Angle(1296000.0, Angle::Unit::Arcsecond) != Angle(0.0, Angle::Unit::Radian)) ;
        EXPECT_FALSE(Angle(1.0, Angle::Unit::Revolution) != Angle(0.0, Angle::Unit::Radian)) ;

    }

}

TEST (Library_Physics_Units_Derived_Angle, AdditionOperator)
{

    using library::physics::units::Angle ;

    {

        EXPECT_EQ(Angle(2.0, Angle::Unit::Radian), Angle(1.0, Angle::Unit::Radian) + Angle(1.0, Angle::Unit::Radian)) ;
        EXPECT_EQ(Angle(0.0, Angle::Unit::Radian), Angle(-1.0, Angle::Unit::Radian) + Angle(+1.0, Angle::Unit::Radian)) ;

        EXPECT_EQ(Angle(2.0, Angle::Unit::Degree), Angle(1.0, Angle::Unit::Degree) + Angle(1.0, Angle::Unit::Degree)) ;
        EXPECT_EQ(Angle(0.0, Angle::Unit::Degree), Angle(-1.0, Angle::Unit::Degree) + Angle(+1.0, Angle::Unit::Degree)) ;

        EXPECT_EQ(Angle(2.0, Angle::Unit::Arcminute), Angle(1.0, Angle::Unit::Arcminute) + Angle(1.0, Angle::Unit::Arcminute)) ;
        EXPECT_EQ(Angle(0.0, Angle::Unit::Arcminute), Angle(-1.0, Angle::Unit::Arcminute) + Angle(+1.0, Angle::Unit::Arcminute)) ;

        EXPECT_EQ(Angle(2.0, Angle::Unit::Arcsecond), Angle(1.0, Angle::Unit::Arcsecond) + Angle(1.0, Angle::Unit::Arcsecond)) ;
        EXPECT_EQ(Angle(0.0, Angle::Unit::Arcsecond), Angle(-1.0, Angle::Unit::Arcsecond) + Angle(+1.0, Angle::Unit::Arcsecond)) ;

        EXPECT_EQ(Angle(2.0, Angle::Unit::Revolution), Angle(1.0, Angle::Unit::Revolution) + Angle(1.0, Angle::Unit::Revolution)) ;
        EXPECT_EQ(Angle(0.0, Angle::Unit::Revolution), Angle(-1.0, Angle::Unit::Revolution) + Angle(+1.0, Angle::Unit::Revolution)) ;

    }

    {

        EXPECT_EQ(Angle(2.0, Angle::Unit::Radian), Angle(2.0, Angle::Unit::Radian) + Angle::Revolutions(1.0)) ;
        EXPECT_EQ(Angle(2.0, Angle::Unit::Degree), Angle(2.0, Angle::Unit::Degree) + Angle::Revolutions(1.0)) ;
        EXPECT_EQ(Angle(2.0, Angle::Unit::Arcminute), Angle(2.0, Angle::Unit::Arcminute) + Angle::Revolutions(1.0)) ;
        EXPECT_EQ(Angle(2.0, Angle::Unit::Arcsecond), Angle(2.0, Angle::Unit::Arcsecond) + Angle::Revolutions(1.0)) ;
        EXPECT_EQ(Angle(2.0, Angle::Unit::Revolution), Angle(2.0, Angle::Unit::Revolution) + Angle::Revolutions(1.0)) ;

        EXPECT_EQ(Angle(-2.0, Angle::Unit::Radian), Angle(-2.0, Angle::Unit::Radian) + Angle::Revolutions(-3.0)) ;
        EXPECT_EQ(Angle(-2.0, Angle::Unit::Degree), Angle(-2.0, Angle::Unit::Degree) + Angle::Revolutions(-3.0)) ;
        EXPECT_EQ(Angle(-2.0, Angle::Unit::Arcminute), Angle(-2.0, Angle::Unit::Arcminute) + Angle::Revolutions(-3.0)) ;
        EXPECT_EQ(Angle(-2.0, Angle::Unit::Arcsecond), Angle(-2.0, Angle::Unit::Arcsecond) + Angle::Revolutions(-3.0)) ;
        EXPECT_EQ(Angle(-2.0, Angle::Unit::Revolution), Angle(-2.0, Angle::Unit::Revolution) + Angle::Revolutions(-3.0)) ;

    }

    {

        EXPECT_EQ(Angle(123.456, Angle::Unit::Radian), Angle(123.456, Angle::Unit::Radian) + Angle(360.0, Angle::Unit::Degree)) ;
        EXPECT_EQ(Angle(123.456, Angle::Unit::Radian), Angle(123.456, Angle::Unit::Radian) + Angle(360.0 * 60.0, Angle::Unit::Arcminute)) ;
        EXPECT_EQ(Angle(123.456, Angle::Unit::Radian), Angle(123.456, Angle::Unit::Radian) + Angle(360.0 * 3600.0, Angle::Unit::Arcsecond)) ;
        EXPECT_EQ(Angle(123.456, Angle::Unit::Radian), Angle(123.456, Angle::Unit::Radian) + Angle(1.0, Angle::Unit::Revolution)) ;

    }

    {

        EXPECT_ANY_THROW(Angle(1.0, Angle::Unit::Radian) + Angle::Undefined()) ;
        EXPECT_ANY_THROW(Angle::Undefined() + Angle(1.0, Angle::Unit::Radian)) ;
        EXPECT_ANY_THROW(Angle::Undefined() + Angle::Undefined()) ;

    }

}

TEST (Library_Physics_Units_Derived_Angle, SubtractionOperator)
{

    using library::physics::units::Angle ;

    {

        EXPECT_EQ(Angle(0.0, Angle::Unit::Radian), Angle(1.0, Angle::Unit::Radian) - Angle(1.0, Angle::Unit::Radian)) ;
        EXPECT_EQ(Angle(-2.0, Angle::Unit::Radian), Angle(-1.0, Angle::Unit::Radian) - Angle(+1.0, Angle::Unit::Radian)) ;

        EXPECT_EQ(Angle(0.0, Angle::Unit::Degree), Angle(1.0, Angle::Unit::Degree) - Angle(1.0, Angle::Unit::Degree)) ;
        EXPECT_EQ(Angle(-2.0, Angle::Unit::Degree), Angle(-1.0, Angle::Unit::Degree) - Angle(+1.0, Angle::Unit::Degree)) ;

        EXPECT_EQ(Angle(0.0, Angle::Unit::Arcminute), Angle(1.0, Angle::Unit::Arcminute) - Angle(1.0, Angle::Unit::Arcminute)) ;
        EXPECT_EQ(Angle(-2.0, Angle::Unit::Arcminute), Angle(-1.0, Angle::Unit::Arcminute) - Angle(+1.0, Angle::Unit::Arcminute)) ;

        EXPECT_EQ(Angle(0.0, Angle::Unit::Arcsecond), Angle(1.0, Angle::Unit::Arcsecond) - Angle(1.0, Angle::Unit::Arcsecond)) ;
        EXPECT_EQ(Angle(-2.0, Angle::Unit::Arcsecond), Angle(-1.0, Angle::Unit::Arcsecond) - Angle(+1.0, Angle::Unit::Arcsecond)) ;

        EXPECT_EQ(Angle(0.0, Angle::Unit::Revolution), Angle(1.0, Angle::Unit::Revolution) - Angle(1.0, Angle::Unit::Revolution)) ;
        EXPECT_EQ(Angle(-2.0, Angle::Unit::Revolution), Angle(-1.0, Angle::Unit::Revolution) - Angle(+1.0, Angle::Unit::Revolution)) ;

    }

    {

        EXPECT_EQ(Angle(2.0, Angle::Unit::Radian), Angle(2.0, Angle::Unit::Radian) - Angle::Revolutions(1.0)) ;
        EXPECT_EQ(Angle(2.0, Angle::Unit::Degree), Angle(2.0, Angle::Unit::Degree) - Angle::Revolutions(1.0)) ;
        EXPECT_EQ(Angle(2.0, Angle::Unit::Arcminute), Angle(2.0, Angle::Unit::Arcminute) - Angle::Revolutions(1.0)) ;
        EXPECT_EQ(Angle(2.0, Angle::Unit::Arcsecond), Angle(2.0, Angle::Unit::Arcsecond) - Angle::Revolutions(1.0)) ;
        EXPECT_EQ(Angle(2.0, Angle::Unit::Revolution), Angle(2.0, Angle::Unit::Revolution) - Angle::Revolutions(1.0)) ;

        EXPECT_EQ(Angle(-2.0, Angle::Unit::Radian), Angle(-2.0, Angle::Unit::Radian) - Angle::Revolutions(-3.0)) ;
        EXPECT_EQ(Angle(-2.0, Angle::Unit::Degree), Angle(-2.0, Angle::Unit::Degree) - Angle::Revolutions(-3.0)) ;
        EXPECT_EQ(Angle(-2.0, Angle::Unit::Arcminute), Angle(-2.0, Angle::Unit::Arcminute) - Angle::Revolutions(-3.0)) ;
        EXPECT_EQ(Angle(-2.0, Angle::Unit::Arcsecond), Angle(-2.0, Angle::Unit::Arcsecond) - Angle::Revolutions(-3.0)) ;
        EXPECT_EQ(Angle(-2.0, Angle::Unit::Revolution), Angle(-2.0, Angle::Unit::Revolution) - Angle::Revolutions(-3.0)) ;

    }

    {

        EXPECT_EQ(Angle(123.456, Angle::Unit::Radian), Angle(123.456, Angle::Unit::Radian) - Angle(360.0, Angle::Unit::Degree)) ;
        EXPECT_EQ(Angle(123.456, Angle::Unit::Radian), Angle(123.456, Angle::Unit::Radian) - Angle(360.0 * 60.0, Angle::Unit::Arcminute)) ;
        EXPECT_EQ(Angle(123.456, Angle::Unit::Radian), Angle(123.456, Angle::Unit::Radian) - Angle(360.0 * 3600.0, Angle::Unit::Arcsecond)) ;
        EXPECT_EQ(Angle(123.456, Angle::Unit::Radian), Angle(123.456, Angle::Unit::Radian) - Angle(1.0, Angle::Unit::Revolution)) ;

    }

    {

        EXPECT_ANY_THROW(Angle(1.0, Angle::Unit::Radian) - Angle::Undefined()) ;
        EXPECT_ANY_THROW(Angle::Undefined() - Angle(1.0, Angle::Unit::Radian)) ;
        EXPECT_ANY_THROW(Angle::Undefined() - Angle::Undefined()) ;

    }

}

TEST (Library_Physics_Units_Derived_Angle, MultiplicationOperator)
{

    using library::core::types::Real ;
    using library::physics::units::Angle ;

    {

        EXPECT_EQ(Angle(+1.0, Angle::Unit::Radian), Angle(+1.0, Angle::Unit::Radian) * +1.0) ;
        EXPECT_EQ(Angle(-1.0, Angle::Unit::Radian), Angle(-1.0, Angle::Unit::Radian) * +1.0) ;
        EXPECT_EQ(Angle(-1.0, Angle::Unit::Radian), Angle(+1.0, Angle::Unit::Radian) * -1.0) ;

        EXPECT_EQ(Angle(+1.0, Angle::Unit::Radian), +1.0 * Angle(+1.0, Angle::Unit::Radian)) ;
        EXPECT_EQ(Angle(-1.0, Angle::Unit::Radian), +1.0 * Angle(-1.0, Angle::Unit::Radian)) ;
        EXPECT_EQ(Angle(-1.0, Angle::Unit::Radian), -1.0 * Angle(+1.0, Angle::Unit::Radian)) ;

        EXPECT_EQ(Angle(+6.0, Angle::Unit::Radian), Angle(+2.0, Angle::Unit::Radian) * +3.0) ;
        EXPECT_EQ(Angle(-6.0, Angle::Unit::Radian), Angle(-2.0, Angle::Unit::Radian) * +3.0) ;
        EXPECT_EQ(Angle(-6.0, Angle::Unit::Radian), Angle(+2.0, Angle::Unit::Radian) * -3.0) ;

        EXPECT_EQ(Angle(+6.0, Angle::Unit::Radian), +2.0 * Angle(+3.0, Angle::Unit::Radian)) ;
        EXPECT_EQ(Angle(-6.0, Angle::Unit::Radian), +2.0 * Angle(-3.0, Angle::Unit::Radian)) ;
        EXPECT_EQ(Angle(-6.0, Angle::Unit::Radian), -2.0 * Angle(+3.0, Angle::Unit::Radian)) ;

        EXPECT_EQ(Angle(0.0, Angle::Unit::Radian), Angle(+1.0, Angle::Unit::Radian) * 0.0) ;
        EXPECT_EQ(Angle(0.0, Angle::Unit::Radian), Angle(-1.0, Angle::Unit::Radian) * 0.0) ;
        EXPECT_EQ(Angle(0.0, Angle::Unit::Radian), Angle(0.0, Angle::Unit::Radian) * 0.0) ;

        EXPECT_EQ(Angle(0.0, Angle::Unit::Radian), 0.0 * Angle(+1.0, Angle::Unit::Radian)) ;
        EXPECT_EQ(Angle(0.0, Angle::Unit::Radian), 0.0 * Angle(-1.0, Angle::Unit::Radian)) ;
        EXPECT_EQ(Angle(0.0, Angle::Unit::Radian), 0.0 * Angle(0.0, Angle::Unit::Radian)) ;

    }

    {

        EXPECT_EQ(Angle(6.0, Angle::Unit::Degree), Angle(3.0, Angle::Unit::Degree) * 2.0) ;
        EXPECT_EQ(Angle(6.0, Angle::Unit::Arcminute), Angle(3.0, Angle::Unit::Arcminute) * 2.0) ;
        EXPECT_EQ(Angle(6.0, Angle::Unit::Arcsecond), Angle(3.0, Angle::Unit::Arcsecond) * 2.0) ;
        EXPECT_EQ(Angle(6.0, Angle::Unit::Revolution), Angle(3.0, Angle::Unit::Revolution) * 2.0) ;

        EXPECT_EQ(Angle(6.0, Angle::Unit::Degree), 2.0 * Angle(3.0, Angle::Unit::Degree)) ;
        EXPECT_EQ(Angle(6.0, Angle::Unit::Arcminute), 2.0 * Angle(3.0, Angle::Unit::Arcminute)) ;
        EXPECT_EQ(Angle(6.0, Angle::Unit::Arcsecond), 2.0 * Angle(3.0, Angle::Unit::Arcsecond)) ;
        EXPECT_EQ(Angle(6.0, Angle::Unit::Revolution), 2.0 * Angle(3.0, Angle::Unit::Revolution)) ;

    }

    {

        EXPECT_ANY_THROW(Angle(1.0, Angle::Unit::Radian) * Real::Undefined()) ;
        EXPECT_ANY_THROW(Real::Undefined() * Angle(1.0, Angle::Unit::Radian)) ;

    }

}

TEST (Library_Physics_Units_Derived_Angle, DivisionOperator)
{

    using library::core::types::Real ;
    using library::physics::units::Angle ;

    {

        EXPECT_EQ(Angle(+1.0, Angle::Unit::Radian), Angle(+1.0, Angle::Unit::Radian) / +1.0) ;
        EXPECT_EQ(Angle(-1.0, Angle::Unit::Radian), Angle(-1.0, Angle::Unit::Radian) / +1.0) ;
        EXPECT_EQ(Angle(-1.0, Angle::Unit::Radian), Angle(+1.0, Angle::Unit::Radian) / -1.0) ;

        EXPECT_EQ(Angle(+1.0, Angle::Unit::Radian), Angle(+2.0, Angle::Unit::Radian) / +2.0) ;
        EXPECT_EQ(Angle(-1.0, Angle::Unit::Radian), Angle(-2.0, Angle::Unit::Radian) / +2.0) ;
        EXPECT_EQ(Angle(-1.0, Angle::Unit::Radian), Angle(+2.0, Angle::Unit::Radian) / -2.0) ;

        EXPECT_EQ(Angle(+2.0, Angle::Unit::Radian), Angle(+4.0, Angle::Unit::Radian) / +2.0) ;
        EXPECT_EQ(Angle(-2.0, Angle::Unit::Radian), Angle(-4.0, Angle::Unit::Radian) / +2.0) ;
        EXPECT_EQ(Angle(-2.0, Angle::Unit::Radian), Angle(+4.0, Angle::Unit::Radian) / -2.0) ;

    }

    {

        EXPECT_EQ(Angle(0.5, Angle::Unit::Degree), Angle(1.0, Angle::Unit::Degree) / 2.0) ;
        EXPECT_EQ(Angle(0.5, Angle::Unit::Arcminute), Angle(1.0, Angle::Unit::Arcminute) / 2.0) ;
        EXPECT_EQ(Angle(0.5, Angle::Unit::Arcsecond), Angle(1.0, Angle::Unit::Arcsecond) / 2.0) ;
        EXPECT_EQ(Angle(0.5, Angle::Unit::Revolution), Angle(1.0, Angle::Unit::Revolution) / 2.0) ;

    }

    {

        EXPECT_ANY_THROW(Angle(1.0, Angle::Unit::Radian) / Real::Undefined()) ;
        EXPECT_ANY_THROW(Angle(1.0, Angle::Unit::Radian) / Real::Zero()) ;

    }

}

TEST (Library_Physics_Units_Derived_Angle, AdditionAssignmentOperator)
{

    using library::physics::units::Angle ;

    {

        EXPECT_EQ(Angle(2.0, Angle::Unit::Radian), Angle(1.0, Angle::Unit::Radian) += Angle(1.0, Angle::Unit::Radian)) ;
        EXPECT_EQ(Angle(0.0, Angle::Unit::Radian), Angle(-1.0, Angle::Unit::Radian) += Angle(+1.0, Angle::Unit::Radian)) ;

        EXPECT_EQ(Angle(2.0, Angle::Unit::Degree), Angle(1.0, Angle::Unit::Degree) += Angle(1.0, Angle::Unit::Degree)) ;
        EXPECT_EQ(Angle(0.0, Angle::Unit::Degree), Angle(-1.0, Angle::Unit::Degree) += Angle(+1.0, Angle::Unit::Degree)) ;

        EXPECT_EQ(Angle(2.0, Angle::Unit::Arcminute), Angle(1.0, Angle::Unit::Arcminute) += Angle(1.0, Angle::Unit::Arcminute)) ;
        EXPECT_EQ(Angle(0.0, Angle::Unit::Arcminute), Angle(-1.0, Angle::Unit::Arcminute) += Angle(+1.0, Angle::Unit::Arcminute)) ;

        EXPECT_EQ(Angle(2.0, Angle::Unit::Arcsecond), Angle(1.0, Angle::Unit::Arcsecond) += Angle(1.0, Angle::Unit::Arcsecond)) ;
        EXPECT_EQ(Angle(0.0, Angle::Unit::Arcsecond), Angle(-1.0, Angle::Unit::Arcsecond) += Angle(+1.0, Angle::Unit::Arcsecond)) ;

        EXPECT_EQ(Angle(2.0, Angle::Unit::Revolution), Angle(1.0, Angle::Unit::Revolution) += Angle(1.0, Angle::Unit::Revolution)) ;
        EXPECT_EQ(Angle(0.0, Angle::Unit::Revolution), Angle(-1.0, Angle::Unit::Revolution) += Angle(+1.0, Angle::Unit::Revolution)) ;

    }

    {

        EXPECT_EQ(Angle(2.0, Angle::Unit::Radian), Angle(2.0, Angle::Unit::Radian) += Angle::Revolutions(1.0)) ;
        EXPECT_EQ(Angle(2.0, Angle::Unit::Degree), Angle(2.0, Angle::Unit::Degree) += Angle::Revolutions(1.0)) ;
        EXPECT_EQ(Angle(2.0, Angle::Unit::Arcminute), Angle(2.0, Angle::Unit::Arcminute) += Angle::Revolutions(1.0)) ;
        EXPECT_EQ(Angle(2.0, Angle::Unit::Arcsecond), Angle(2.0, Angle::Unit::Arcsecond) += Angle::Revolutions(1.0)) ;
        EXPECT_EQ(Angle(2.0, Angle::Unit::Revolution), Angle(2.0, Angle::Unit::Revolution) += Angle::Revolutions(1.0)) ;

        EXPECT_EQ(Angle(-2.0, Angle::Unit::Radian), Angle(-2.0, Angle::Unit::Radian) += Angle::Revolutions(-3.0)) ;
        EXPECT_EQ(Angle(-2.0, Angle::Unit::Degree), Angle(-2.0, Angle::Unit::Degree) += Angle::Revolutions(-3.0)) ;
        EXPECT_EQ(Angle(-2.0, Angle::Unit::Arcminute), Angle(-2.0, Angle::Unit::Arcminute) += Angle::Revolutions(-3.0)) ;
        EXPECT_EQ(Angle(-2.0, Angle::Unit::Arcsecond), Angle(-2.0, Angle::Unit::Arcsecond) += Angle::Revolutions(-3.0)) ;
        EXPECT_EQ(Angle(-2.0, Angle::Unit::Revolution), Angle(-2.0, Angle::Unit::Revolution) += Angle::Revolutions(-3.0)) ;

    }

    {

        EXPECT_EQ(Angle(123.456, Angle::Unit::Radian), Angle(123.456, Angle::Unit::Radian) += Angle(360.0, Angle::Unit::Degree)) ;
        EXPECT_EQ(Angle(123.456, Angle::Unit::Radian), Angle(123.456, Angle::Unit::Radian) += Angle(360.0 * 60.0, Angle::Unit::Arcminute)) ;
        EXPECT_EQ(Angle(123.456, Angle::Unit::Radian), Angle(123.456, Angle::Unit::Radian) += Angle(360.0 * 3600.0, Angle::Unit::Arcsecond)) ;
        EXPECT_EQ(Angle(123.456, Angle::Unit::Radian), Angle(123.456, Angle::Unit::Radian) += Angle(1.0, Angle::Unit::Revolution)) ;

    }

    {

        EXPECT_ANY_THROW(Angle(1.0, Angle::Unit::Radian) += Angle::Undefined()) ;
        EXPECT_ANY_THROW(Angle::Undefined() += Angle(1.0, Angle::Unit::Radian)) ;
        EXPECT_ANY_THROW(Angle::Undefined() += Angle::Undefined()) ;

    }

}

TEST (Library_Physics_Units_Derived_Angle, SubtractionAssignmentOperator)
{

    using library::physics::units::Angle ;

    {

        EXPECT_EQ(Angle(0.0, Angle::Unit::Radian), Angle(1.0, Angle::Unit::Radian) -= Angle(1.0, Angle::Unit::Radian)) ;
        EXPECT_EQ(Angle(-2.0, Angle::Unit::Radian), Angle(-1.0, Angle::Unit::Radian) -= Angle(+1.0, Angle::Unit::Radian)) ;

        EXPECT_EQ(Angle(0.0, Angle::Unit::Degree), Angle(1.0, Angle::Unit::Degree) -= Angle(1.0, Angle::Unit::Degree)) ;
        EXPECT_EQ(Angle(-2.0, Angle::Unit::Degree), Angle(-1.0, Angle::Unit::Degree) -= Angle(+1.0, Angle::Unit::Degree)) ;

        EXPECT_EQ(Angle(0.0, Angle::Unit::Arcminute), Angle(1.0, Angle::Unit::Arcminute) -= Angle(1.0, Angle::Unit::Arcminute)) ;
        EXPECT_EQ(Angle(-2.0, Angle::Unit::Arcminute), Angle(-1.0, Angle::Unit::Arcminute) -= Angle(+1.0, Angle::Unit::Arcminute)) ;

        EXPECT_EQ(Angle(0.0, Angle::Unit::Arcsecond), Angle(1.0, Angle::Unit::Arcsecond) -= Angle(1.0, Angle::Unit::Arcsecond)) ;
        EXPECT_EQ(Angle(-2.0, Angle::Unit::Arcsecond), Angle(-1.0, Angle::Unit::Arcsecond) -= Angle(+1.0, Angle::Unit::Arcsecond)) ;

        EXPECT_EQ(Angle(0.0, Angle::Unit::Revolution), Angle(1.0, Angle::Unit::Revolution) -= Angle(1.0, Angle::Unit::Revolution)) ;
        EXPECT_EQ(Angle(-2.0, Angle::Unit::Revolution), Angle(-1.0, Angle::Unit::Revolution) -= Angle(+1.0, Angle::Unit::Revolution)) ;

    }

    {

        EXPECT_EQ(Angle(2.0, Angle::Unit::Radian), Angle(2.0, Angle::Unit::Radian) -= Angle::Revolutions(1.0)) ;
        EXPECT_EQ(Angle(2.0, Angle::Unit::Degree), Angle(2.0, Angle::Unit::Degree) -= Angle::Revolutions(1.0)) ;
        EXPECT_EQ(Angle(2.0, Angle::Unit::Arcminute), Angle(2.0, Angle::Unit::Arcminute) -= Angle::Revolutions(1.0)) ;
        EXPECT_EQ(Angle(2.0, Angle::Unit::Arcsecond), Angle(2.0, Angle::Unit::Arcsecond) -= Angle::Revolutions(1.0)) ;
        EXPECT_EQ(Angle(2.0, Angle::Unit::Revolution), Angle(2.0, Angle::Unit::Revolution) -= Angle::Revolutions(1.0)) ;

        EXPECT_EQ(Angle(-2.0, Angle::Unit::Radian), Angle(-2.0, Angle::Unit::Radian) -= Angle::Revolutions(-3.0)) ;
        EXPECT_EQ(Angle(-2.0, Angle::Unit::Degree), Angle(-2.0, Angle::Unit::Degree) -= Angle::Revolutions(-3.0)) ;
        EXPECT_EQ(Angle(-2.0, Angle::Unit::Arcminute), Angle(-2.0, Angle::Unit::Arcminute) -= Angle::Revolutions(-3.0)) ;
        EXPECT_EQ(Angle(-2.0, Angle::Unit::Arcsecond), Angle(-2.0, Angle::Unit::Arcsecond) -= Angle::Revolutions(-3.0)) ;
        EXPECT_EQ(Angle(-2.0, Angle::Unit::Revolution), Angle(-2.0, Angle::Unit::Revolution) -= Angle::Revolutions(-3.0)) ;

    }

    {

        EXPECT_EQ(Angle(123.456, Angle::Unit::Radian), Angle(123.456, Angle::Unit::Radian) -= Angle(360.0, Angle::Unit::Degree)) ;
        EXPECT_EQ(Angle(123.456, Angle::Unit::Radian), Angle(123.456, Angle::Unit::Radian) -= Angle(360.0 * 60.0, Angle::Unit::Arcminute)) ;
        EXPECT_EQ(Angle(123.456, Angle::Unit::Radian), Angle(123.456, Angle::Unit::Radian) -= Angle(360.0 * 3600.0, Angle::Unit::Arcsecond)) ;
        EXPECT_EQ(Angle(123.456, Angle::Unit::Radian), Angle(123.456, Angle::Unit::Radian) -= Angle(1.0, Angle::Unit::Revolution)) ;

    }

    {

        EXPECT_ANY_THROW(Angle(1.0, Angle::Unit::Radian) -= Angle::Undefined()) ;
        EXPECT_ANY_THROW(Angle::Undefined() -= Angle(1.0, Angle::Unit::Radian)) ;
        EXPECT_ANY_THROW(Angle::Undefined() -= Angle::Undefined()) ;

    }

}

TEST (Library_Physics_Units_Derived_Angle, MultiplicationAssignmentOperator)
{

    using library::core::types::Real ;
    using library::physics::units::Angle ;

    {

        EXPECT_EQ(Angle(+1.0, Angle::Unit::Radian), Angle(+1.0, Angle::Unit::Radian) *= +1.0) ;
        EXPECT_EQ(Angle(-1.0, Angle::Unit::Radian), Angle(-1.0, Angle::Unit::Radian) *= +1.0) ;
        EXPECT_EQ(Angle(-1.0, Angle::Unit::Radian), Angle(+1.0, Angle::Unit::Radian) *= -1.0) ;

        EXPECT_EQ(Angle(+6.0, Angle::Unit::Radian), Angle(+2.0, Angle::Unit::Radian) *= +3.0) ;
        EXPECT_EQ(Angle(-6.0, Angle::Unit::Radian), Angle(-2.0, Angle::Unit::Radian) *= +3.0) ;
        EXPECT_EQ(Angle(-6.0, Angle::Unit::Radian), Angle(+2.0, Angle::Unit::Radian) *= -3.0) ;

        EXPECT_EQ(Angle(0.0, Angle::Unit::Radian), Angle(+1.0, Angle::Unit::Radian) *= 0.0) ;
        EXPECT_EQ(Angle(0.0, Angle::Unit::Radian), Angle(-1.0, Angle::Unit::Radian) *= 0.0) ;
        EXPECT_EQ(Angle(0.0, Angle::Unit::Radian), Angle(0.0, Angle::Unit::Radian) *= 0.0) ;

    }

    {

        EXPECT_EQ(Angle(6.0, Angle::Unit::Degree), Angle(3.0, Angle::Unit::Degree) *= 2.0) ;
        EXPECT_EQ(Angle(6.0, Angle::Unit::Arcminute), Angle(3.0, Angle::Unit::Arcminute) *= 2.0) ;
        EXPECT_EQ(Angle(6.0, Angle::Unit::Arcsecond), Angle(3.0, Angle::Unit::Arcsecond) *= 2.0) ;
        EXPECT_EQ(Angle(6.0, Angle::Unit::Revolution), Angle(3.0, Angle::Unit::Revolution) *= 2.0) ;

    }

    {

        EXPECT_ANY_THROW(Angle(1.0, Angle::Unit::Radian) *= Real::Undefined()) ;

    }

}

TEST (Library_Physics_Units_Derived_Angle, DivisionAssignmentOperator)
{

    using library::core::types::Real ;
    using library::physics::units::Angle ;

    {

        EXPECT_EQ(Angle(+1.0, Angle::Unit::Radian), Angle(+1.0, Angle::Unit::Radian) /= +1.0) ;
        EXPECT_EQ(Angle(-1.0, Angle::Unit::Radian), Angle(-1.0, Angle::Unit::Radian) /= +1.0) ;
        EXPECT_EQ(Angle(-1.0, Angle::Unit::Radian), Angle(+1.0, Angle::Unit::Radian) /= -1.0) ;

        EXPECT_EQ(Angle(+1.0, Angle::Unit::Radian), Angle(+2.0, Angle::Unit::Radian) /= +2.0) ;
        EXPECT_EQ(Angle(-1.0, Angle::Unit::Radian), Angle(-2.0, Angle::Unit::Radian) /= +2.0) ;
        EXPECT_EQ(Angle(-1.0, Angle::Unit::Radian), Angle(+2.0, Angle::Unit::Radian) /= -2.0) ;

        EXPECT_EQ(Angle(+2.0, Angle::Unit::Radian), Angle(+4.0, Angle::Unit::Radian) /= +2.0) ;
        EXPECT_EQ(Angle(-2.0, Angle::Unit::Radian), Angle(-4.0, Angle::Unit::Radian) /= +2.0) ;
        EXPECT_EQ(Angle(-2.0, Angle::Unit::Radian), Angle(+4.0, Angle::Unit::Radian) /= -2.0) ;

    }

    {

        EXPECT_EQ(Angle(0.5, Angle::Unit::Degree), Angle(1.0, Angle::Unit::Degree) /= 2.0) ;
        EXPECT_EQ(Angle(0.5, Angle::Unit::Arcminute), Angle(1.0, Angle::Unit::Arcminute) /= 2.0) ;
        EXPECT_EQ(Angle(0.5, Angle::Unit::Arcsecond), Angle(1.0, Angle::Unit::Arcsecond) /= 2.0) ;
        EXPECT_EQ(Angle(0.5, Angle::Unit::Revolution), Angle(1.0, Angle::Unit::Revolution) /= 2.0) ;

    }

    {

        EXPECT_ANY_THROW(Angle(1.0, Angle::Unit::Radian) /= Real::Undefined()) ;
        EXPECT_ANY_THROW(Angle(1.0, Angle::Unit::Radian) /= Real::Zero()) ;

    }

}

TEST (Library_Physics_Units_Derived_Angle, AngleConversionOperator)
{

    using library::physics::units::Angle ;

    {

        EXPECT_EQ(library::math::geom::Angle(+1.0, library::math::geom::Angle::Unit::Radian), Angle(+1.0, Angle::Unit::Radian)) ;

    }

    {

        EXPECT_NO_THROW(library::math::geom::Angle angle = Angle::Undefined() ; (void) angle ;) ;

    }

}

TEST (Library_Physics_Units_Derived_Angle, StreamOperator)
{

    using library::physics::units::Angle ;

    {

        testing::internal::CaptureStdout() ;

        EXPECT_NO_THROW(std::cout << Angle(0.5, Angle::Unit::Degree) << std::endl) ;

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty()) ;

    }

}

TEST (Library_Physics_Units_Derived_Angle, IsDefined)
{

    using library::core::types::Real ;
    using library::physics::units::Angle ;

    {

        EXPECT_TRUE(Angle(0.0, Angle::Unit::Radian).isDefined()) ;
        
        EXPECT_TRUE(Angle(1.0, Angle::Unit::Radian).isDefined()) ;
        EXPECT_TRUE(Angle(1.0, Angle::Unit::Degree).isDefined()) ;
        EXPECT_TRUE(Angle(1.0, Angle::Unit::Arcminute).isDefined()) ;
        EXPECT_TRUE(Angle(1.0, Angle::Unit::Arcsecond).isDefined()) ;
        EXPECT_TRUE(Angle(1.0, Angle::Unit::Revolution).isDefined()) ;

    }

    {

        EXPECT_FALSE(Angle::Undefined().isDefined()) ;
        EXPECT_FALSE(Angle(Real::Undefined(), Angle::Unit::Radian).isDefined()) ;
        EXPECT_FALSE(Angle(1.0, Angle::Unit::Undefined).isDefined()) ;

    }

}

TEST (Library_Physics_Units_Derived_Angle, GetUnit)
{

    using library::physics::units::Angle ;

    {

        EXPECT_EQ(Angle::Unit::Radian, Angle(1.0, Angle::Unit::Radian).getUnit()) ;
        EXPECT_EQ(Angle::Unit::Degree, Angle(1.0, Angle::Unit::Degree).getUnit()) ;
        EXPECT_EQ(Angle::Unit::Arcminute, Angle(1.0, Angle::Unit::Arcminute).getUnit()) ;
        EXPECT_EQ(Angle::Unit::Arcsecond, Angle(1.0, Angle::Unit::Arcsecond).getUnit()) ;
        EXPECT_EQ(Angle::Unit::Revolution, Angle(1.0, Angle::Unit::Revolution).getUnit()) ;

    }

    {

        EXPECT_ANY_THROW(Angle::Undefined().getUnit()) ;

    }

}

TEST (Library_Physics_Units_Derived_Angle, In)
{

    using library::physics::units::Angle ;

    {

        EXPECT_EQ(1.0, Angle(1.0, Angle::Unit::Radian).in(Angle::Unit::Radian)) ;
        EXPECT_EQ(1.0, Angle(1.0, Angle::Unit::Degree).in(Angle::Unit::Degree)) ;
        EXPECT_EQ(1.0, Angle(1.0, Angle::Unit::Arcminute).in(Angle::Unit::Arcminute)) ;
        EXPECT_EQ(1.0, Angle(1.0, Angle::Unit::Arcsecond).in(Angle::Unit::Arcsecond)) ;
        EXPECT_EQ(1.0, Angle(1.0, Angle::Unit::Revolution).in(Angle::Unit::Revolution)) ;

    }

    {

        EXPECT_ANY_THROW(Angle::Undefined().in(Angle::Unit::Radian)) ;

    }

}

TEST (Library_Physics_Units_Derived_Angle, InRadians)
{

    using library::core::types::Real ;

    using library::physics::units::Angle ;

    {

        EXPECT_EQ(123.456, Angle(123.456, Angle::Unit::Radian).inRadians()) ;

    }

    {

        EXPECT_EQ(0.0, Angle(0.0, Angle::Unit::Radian).inRadians(0.0, Real::TwoPi())) ;

        EXPECT_EQ(Real::Pi(), Angle(Real::Pi(), Angle::Unit::Radian).inRadians(0.0, Real::TwoPi())) ;
        EXPECT_EQ(0.0, Angle(Real::TwoPi(), Angle::Unit::Radian).inRadians(0.0, Real::TwoPi())) ;
        EXPECT_EQ(Real::Pi(), Angle(3.0 * Real::Pi(), Angle::Unit::Radian).inRadians(0.0, Real::TwoPi())) ;
        EXPECT_EQ(0.0, Angle(4.0 * Real::Pi(), Angle::Unit::Radian).inRadians(0.0, Real::TwoPi())) ;

        EXPECT_EQ(Real::Pi(), Angle(-Real::Pi(), Angle::Unit::Radian).inRadians(0.0, Real::TwoPi())) ;
        EXPECT_EQ(0.0, Angle(-Real::TwoPi(), Angle::Unit::Radian).inRadians(0.0, Real::TwoPi())) ;
        EXPECT_EQ(Real::Pi(), Angle(-3.0 * Real::Pi(), Angle::Unit::Radian).inRadians(0.0, Real::TwoPi())) ;
        EXPECT_EQ(0.0, Angle(-4.0 * Real::Pi(), Angle::Unit::Radian).inRadians(0.0, Real::TwoPi())) ;

    }

    {

        EXPECT_EQ(0.0, Angle(0.0, Angle::Unit::Radian).inRadians(-Real::Pi(), Real::Pi())) ;

        EXPECT_EQ(-Real::Pi(), Angle(Real::Pi(), Angle::Unit::Radian).inRadians(-Real::Pi(), Real::Pi())) ;
        EXPECT_EQ(0.0, Angle(Real::TwoPi(), Angle::Unit::Radian).inRadians(-Real::Pi(), Real::Pi())) ;
        EXPECT_EQ(-Real::Pi(), Angle(3.0 * Real::Pi(), Angle::Unit::Radian).inRadians(-Real::Pi(), Real::Pi())) ;
        EXPECT_EQ(0.0, Angle(4.0 * Real::Pi(), Angle::Unit::Radian).inRadians(-Real::Pi(), Real::Pi())) ;

        EXPECT_EQ(-Real::Pi(), Angle(-Real::Pi(), Angle::Unit::Radian).inRadians(-Real::Pi(), Real::Pi())) ;
        EXPECT_EQ(0.0, Angle(-Real::TwoPi(), Angle::Unit::Radian).inRadians(-Real::Pi(), Real::Pi())) ;
        EXPECT_EQ(-Real::Pi(), Angle(-3.0 * Real::Pi(), Angle::Unit::Radian).inRadians(-Real::Pi(), Real::Pi())) ;
        EXPECT_EQ(0.0, Angle(-4.0 * Real::Pi(), Angle::Unit::Radian).inRadians(-Real::Pi(), Real::Pi())) ;

    }

    {

        EXPECT_ANY_THROW(Angle::Undefined().inRadians()) ;

    }

    {

        EXPECT_ANY_THROW(Angle(0.0, Angle::Unit::Radian).inRadians(0.0, 0.0)) ;
        EXPECT_ANY_THROW(Angle(0.0, Angle::Unit::Radian).inRadians(0.0, Real::Pi())) ;
        EXPECT_ANY_THROW(Angle(0.0, Angle::Unit::Radian).inRadians(+Real::Pi(), -Real::Pi())) ;
        
    }

}

TEST (Library_Physics_Units_Derived_Angle, InDegrees)
{

    using library::core::types::Real ;
    using library::physics::units::Angle ; 

    {

        EXPECT_EQ(360.0, Angle(Real::TwoPi(), Angle::Unit::Radian).inDegrees()) ;

    }

    {

        EXPECT_EQ(0.0, Angle(0.0, Angle::Unit::Radian).inDegrees(0.0, 360.0)) ;

        EXPECT_EQ(180.0, Angle(Real::Pi(), Angle::Unit::Radian).inDegrees(0.0, 360.0)) ;
        EXPECT_EQ(0.0, Angle(Real::TwoPi(), Angle::Unit::Radian).inDegrees(0.0, 360.0)) ;
        EXPECT_EQ(180.0, Angle(3.0 * Real::Pi(), Angle::Unit::Radian).inDegrees(0.0, 360.0)) ;
        EXPECT_EQ(0.0, Angle(4.0 * Real::Pi(), Angle::Unit::Radian).inDegrees(0.0, 360.0)) ;

        EXPECT_EQ(180.0, Angle(-Real::Pi(), Angle::Unit::Radian).inDegrees(0.0, 360.0)) ;
        EXPECT_EQ(0.0, Angle(-Real::TwoPi(), Angle::Unit::Radian).inDegrees(0.0, 360.0)) ;
        EXPECT_EQ(180.0, Angle(-3.0 * Real::Pi(), Angle::Unit::Radian).inDegrees(0.0, 360.0)) ;
        EXPECT_EQ(0.0, Angle(-4.0 * Real::Pi(), Angle::Unit::Radian).inDegrees(0.0, 360.0)) ;

    }

    {

        EXPECT_EQ(0.0, Angle(0.0, Angle::Unit::Radian).inDegrees(-180.0, +180.0)) ;

        EXPECT_EQ(-180.0, Angle(Real::Pi(), Angle::Unit::Radian).inDegrees(-180.0, +180.0)) ;
        EXPECT_EQ(0.0, Angle(Real::TwoPi(), Angle::Unit::Radian).inDegrees(-180.0, +180.0)) ;
        EXPECT_EQ(-180.0, Angle(3.0 * Real::Pi(), Angle::Unit::Radian).inDegrees(-180.0, +180.0)) ;
        EXPECT_EQ(0.0, Angle(4.0 * Real::Pi(), Angle::Unit::Radian).inDegrees(-180.0, +180.0)) ;

        EXPECT_EQ(-180.0, Angle(-Real::Pi(), Angle::Unit::Radian).inDegrees(-180.0, +180.0)) ;
        EXPECT_EQ(0.0, Angle(-Real::TwoPi(), Angle::Unit::Radian).inDegrees(-180.0, +180.0)) ;
        EXPECT_EQ(-180.0, Angle(-3.0 * Real::Pi(), Angle::Unit::Radian).inDegrees(-180.0, +180.0)) ;
        EXPECT_EQ(0.0, Angle(-4.0 * Real::Pi(), Angle::Unit::Radian).inDegrees(-180.0, +180.0)) ;

    }

    {

        EXPECT_ANY_THROW(Angle::Undefined().inDegrees()) ;

    }

    {

        EXPECT_ANY_THROW(Angle(0.0, Angle::Unit::Radian).inDegrees(0.0, 0.0)) ;
        EXPECT_ANY_THROW(Angle(0.0, Angle::Unit::Radian).inDegrees(0.0, 180.0)) ;
        EXPECT_ANY_THROW(Angle(0.0, Angle::Unit::Radian).inDegrees(+180.0, -180.0)) ;
        
    }

}

TEST (Library_Physics_Units_Derived_Angle, InArcminutes)
{

    using library::core::types::Real ;
    using library::physics::units::Angle ; 

    {

        EXPECT_EQ(360.0 * 60.0, Angle(Real::TwoPi(), Angle::Unit::Radian).inArcminutes()) ;

    }

    {

        EXPECT_EQ(0.0, Angle(0.0, Angle::Unit::Radian).inArcminutes(0.0, 360.0 * 60.0)) ;

        EXPECT_EQ(180.0 * 60.0, Angle(Real::Pi(), Angle::Unit::Radian).inArcminutes(0.0, 360.0 * 60.0)) ;
        EXPECT_EQ(0.0, Angle(Real::TwoPi(), Angle::Unit::Radian).inArcminutes(0.0, 360.0 * 60.0)) ;
        EXPECT_EQ(180.0 * 60.0, Angle(3.0 * Real::Pi(), Angle::Unit::Radian).inArcminutes(0.0, 360.0 * 60.0)) ;
        EXPECT_EQ(0.0, Angle(4.0 * Real::Pi(), Angle::Unit::Radian).inArcminutes(0.0, 360.0 * 60.0)) ;

        EXPECT_EQ(180.0 * 60.0, Angle(-Real::Pi(), Angle::Unit::Radian).inArcminutes(0.0, 360.0 * 60.0)) ;
        EXPECT_EQ(0.0, Angle(-Real::TwoPi(), Angle::Unit::Radian).inArcminutes(0.0, 360.0 * 60.0)) ;
        EXPECT_EQ(180.0 * 60.0, Angle(-3.0 * Real::Pi(), Angle::Unit::Radian).inArcminutes(0.0, 360.0 * 60.0)) ;
        EXPECT_EQ(0.0, Angle(-4.0 * Real::Pi(), Angle::Unit::Radian).inArcminutes(0.0, 360.0 * 60.0)) ;

    }

    {

        EXPECT_EQ(0.0, Angle(0.0, Angle::Unit::Radian).inArcminutes(-180.0 * 60.0, +180.0 * 60.0)) ;

        EXPECT_EQ(-180.0 * 60.0, Angle(Real::Pi(), Angle::Unit::Radian).inArcminutes(-180.0 * 60.0, +180.0 * 60.0)) ;
        EXPECT_EQ(0.0, Angle(Real::TwoPi(), Angle::Unit::Radian).inArcminutes(-180.0 * 60.0, +180.0 * 60.0)) ;
        EXPECT_EQ(-180.0 * 60.0, Angle(3.0 * Real::Pi(), Angle::Unit::Radian).inArcminutes(-180.0 * 60.0, +180.0 * 60.0)) ;
        EXPECT_EQ(0.0, Angle(4.0 * Real::Pi(), Angle::Unit::Radian).inArcminutes(-180.0 * 60.0, +180.0 * 60.0)) ;

        EXPECT_EQ(-180.0 * 60.0, Angle(-Real::Pi(), Angle::Unit::Radian).inArcminutes(-180.0 * 60.0, +180.0 * 60.0)) ;
        EXPECT_EQ(0.0, Angle(-Real::TwoPi(), Angle::Unit::Radian).inArcminutes(-180.0 * 60.0, +180.0 * 60.0)) ;
        EXPECT_EQ(-180.0 * 60.0, Angle(-3.0 * Real::Pi(), Angle::Unit::Radian).inArcminutes(-180.0 * 60.0, +180.0 * 60.0)) ;
        EXPECT_EQ(0.0, Angle(-4.0 * Real::Pi(), Angle::Unit::Radian).inArcminutes(-180.0 * 60.0, +180.0 * 60.0)) ;

    }

    {

        EXPECT_ANY_THROW(Angle::Undefined().inArcminutes()) ;

    }

    {

        EXPECT_ANY_THROW(Angle(0.0, Angle::Unit::Radian).inDegrees(0.0, 0.0)) ;
        EXPECT_ANY_THROW(Angle(0.0, Angle::Unit::Radian).inDegrees(0.0, 180.0 * 60.0)) ;
        EXPECT_ANY_THROW(Angle(0.0, Angle::Unit::Radian).inDegrees(+180.0 * 60.0, -180.0 * 60.0)) ;
        
    }

}

TEST (Library_Physics_Units_Derived_Angle, InArcseconds)
{

    using library::core::types::Real ;
    using library::physics::units::Angle ; 

    {

        EXPECT_EQ(360.0 * 3600.0, Angle(Real::TwoPi(), Angle::Unit::Radian).inArcseconds()) ;

    }

    {

        EXPECT_EQ(0.0, Angle(0.0, Angle::Unit::Radian).inArcseconds(0.0, 360.0 * 3600.0)) ;

        EXPECT_EQ(180.0 * 3600.0, Angle(Real::Pi(), Angle::Unit::Radian).inArcseconds(0.0, 360.0 * 3600.0)) ;
        EXPECT_EQ(0.0, Angle(Real::TwoPi(), Angle::Unit::Radian).inArcseconds(0.0, 360.0 * 3600.0)) ;
        EXPECT_EQ(180.0 * 3600.0, Angle(3.0 * Real::Pi(), Angle::Unit::Radian).inArcseconds(0.0, 360.0 * 3600.0)) ;
        EXPECT_EQ(0.0, Angle(4.0 * Real::Pi(), Angle::Unit::Radian).inArcseconds(0.0, 360.0 * 3600.0)) ;

        EXPECT_EQ(180.0 * 3600.0, Angle(-Real::Pi(), Angle::Unit::Radian).inArcseconds(0.0, 360.0 * 3600.0)) ;
        EXPECT_EQ(0.0, Angle(-Real::TwoPi(), Angle::Unit::Radian).inArcseconds(0.0, 360.0 * 3600.0)) ;
        EXPECT_EQ(180.0 * 3600.0, Angle(-3.0 * Real::Pi(), Angle::Unit::Radian).inArcseconds(0.0, 360.0 * 3600.0)) ;
        EXPECT_EQ(0.0, Angle(-4.0 * Real::Pi(), Angle::Unit::Radian).inArcseconds(0.0, 360.0 * 3600.0)) ;

    }

    {

        EXPECT_EQ(0.0, Angle(0.0, Angle::Unit::Radian).inArcseconds(-180.0 * 3600.0, +180.0 * 3600.0)) ;

        EXPECT_EQ(-180.0 * 3600.0, Angle(Real::Pi(), Angle::Unit::Radian).inArcseconds(-180.0 * 3600.0, +180.0 * 3600.0)) ;
        EXPECT_EQ(0.0, Angle(Real::TwoPi(), Angle::Unit::Radian).inArcseconds(-180.0 * 3600.0, +180.0 * 3600.0)) ;
        EXPECT_EQ(-180.0 * 3600.0, Angle(3.0 * Real::Pi(), Angle::Unit::Radian).inArcseconds(-180.0 * 3600.0, +180.0 * 3600.0)) ;
        EXPECT_EQ(0.0, Angle(4.0 * Real::Pi(), Angle::Unit::Radian).inArcseconds(-180.0 * 3600.0, +180.0 * 3600.0)) ;

        EXPECT_EQ(-180.0 * 3600.0, Angle(-Real::Pi(), Angle::Unit::Radian).inArcseconds(-180.0 * 3600.0, +180.0 * 3600.0)) ;
        EXPECT_EQ(0.0, Angle(-Real::TwoPi(), Angle::Unit::Radian).inArcseconds(-180.0 * 3600.0, +180.0 * 3600.0)) ;
        EXPECT_EQ(-180.0 * 3600.0, Angle(-3.0 * Real::Pi(), Angle::Unit::Radian).inArcseconds(-180.0 * 3600.0, +180.0 * 3600.0)) ;
        EXPECT_EQ(0.0, Angle(-4.0 * Real::Pi(), Angle::Unit::Radian).inArcseconds(-180.0 * 3600.0, +180.0 * 3600.0)) ;

    }

    {

        EXPECT_ANY_THROW(Angle::Undefined().inArcseconds()) ;

    }

    {

        EXPECT_ANY_THROW(Angle(0.0, Angle::Unit::Radian).inDegrees(0.0, 0.0)) ;
        EXPECT_ANY_THROW(Angle(0.0, Angle::Unit::Radian).inDegrees(0.0, 180.0 * 3600.0)) ;
        EXPECT_ANY_THROW(Angle(0.0, Angle::Unit::Radian).inDegrees(+180.0 * 3600.0, -180.0 * 3600.0)) ;
        
    }

}

TEST (Library_Physics_Units_Derived_Angle, InRevolutions)
{

    using library::core::types::Real ;
    using library::physics::units::Angle ; 

    {

        EXPECT_EQ(1.0, Angle(Real::TwoPi(), Angle::Unit::Radian).inRevolutions()) ;

    }

    {

        EXPECT_ANY_THROW(Angle::Undefined().inRevolutions()) ;

    }

}

TEST (Library_Physics_Units_Derived_Angle, ToString)
{

    using library::physics::units::Angle ; 

    {

        EXPECT_EQ("1.0 [rad]", Angle(1.0, Angle::Unit::Radian).toString()) ;
        EXPECT_EQ("1.0 [deg]", Angle(1.0, Angle::Unit::Degree).toString()) ;
        EXPECT_EQ("1.0 [amin]", Angle(1.0, Angle::Unit::Arcminute).toString()) ;
        EXPECT_EQ("1.0 [asec]", Angle(1.0, Angle::Unit::Arcsecond).toString()) ;
        EXPECT_EQ("1.0 [rev]", Angle(1.0, Angle::Unit::Revolution).toString()) ;

        EXPECT_EQ("-1.0 [rad]", Angle(-1.0, Angle::Unit::Radian).toString()) ;
        EXPECT_EQ("-1.0 [deg]", Angle(-1.0, Angle::Unit::Degree).toString()) ;
        EXPECT_EQ("-1.0 [amin]", Angle(-1.0, Angle::Unit::Arcminute).toString()) ;
        EXPECT_EQ("-1.0 [asec]", Angle(-1.0, Angle::Unit::Arcsecond).toString()) ;
        EXPECT_EQ("-1.0 [rev]", Angle(-1.0, Angle::Unit::Revolution).toString()) ;

        EXPECT_EQ("123.456 [rad]", Angle(123.456, Angle::Unit::Radian).toString()) ;
        EXPECT_EQ("123.456 [deg]", Angle(123.456, Angle::Unit::Degree).toString()) ;
        EXPECT_EQ("123.456 [amin]", Angle(123.456, Angle::Unit::Arcminute).toString()) ;
        EXPECT_EQ("123.456 [asec]", Angle(123.456, Angle::Unit::Arcsecond).toString()) ;
        EXPECT_EQ("123.456 [rev]", Angle(123.456, Angle::Unit::Revolution).toString()) ;

    }

    {

        EXPECT_EQ("1.000 [rad]", Angle(1.0, Angle::Unit::Radian).toString(3)) ;
        EXPECT_EQ("1.000 [deg]", Angle(1.0, Angle::Unit::Degree).toString(3)) ;
        EXPECT_EQ("1.000 [amin]", Angle(1.0, Angle::Unit::Arcminute).toString(3)) ;
        EXPECT_EQ("1.000 [asec]", Angle(1.0, Angle::Unit::Arcsecond).toString(3)) ;
        EXPECT_EQ("1.000 [rev]", Angle(1.0, Angle::Unit::Revolution).toString(3)) ;

        EXPECT_EQ("-1.000 [rad]", Angle(-1.0, Angle::Unit::Radian).toString(3)) ;
        EXPECT_EQ("-1.000 [deg]", Angle(-1.0, Angle::Unit::Degree).toString(3)) ;
        EXPECT_EQ("-1.000 [amin]", Angle(-1.0, Angle::Unit::Arcminute).toString(3)) ;
        EXPECT_EQ("-1.000 [asec]", Angle(-1.0, Angle::Unit::Arcsecond).toString(3)) ;
        EXPECT_EQ("-1.000 [rev]", Angle(-1.0, Angle::Unit::Revolution).toString(3)) ;

        EXPECT_EQ("123.456 [rad]", Angle(123.456123, Angle::Unit::Radian).toString(3)) ;
        EXPECT_EQ("123.456 [deg]", Angle(123.456123, Angle::Unit::Degree).toString(3)) ;
        EXPECT_EQ("123.456 [amin]", Angle(123.456123, Angle::Unit::Arcminute).toString(3)) ;
        EXPECT_EQ("123.456 [asec]", Angle(123.456123, Angle::Unit::Arcsecond).toString(3)) ;
        EXPECT_EQ("123.456 [rev]", Angle(123.456123, Angle::Unit::Revolution).toString(3)) ;

    }

    {

        EXPECT_ANY_THROW(Angle::Undefined().toString()) ;
        
    }

}

TEST (Library_Physics_Units_Derived_Angle, Undefined)
{

    using library::physics::units::Angle ;

    {

        EXPECT_NO_THROW(Angle::Undefined()) ;
        EXPECT_FALSE(Angle::Undefined().isDefined()) ;

    }

}

TEST (Library_Physics_Units_Derived_Angle, Radians)
{

    using library::physics::units::Angle ;

    {

        EXPECT_NO_THROW(Angle::Radians(123.456)) ;
        EXPECT_TRUE(Angle::Radians(123.456).isDefined()) ;

        EXPECT_EQ(123.456, Angle::Radians(123.456).in(Angle::Unit::Radian)) ;

    }

}

TEST (Library_Physics_Units_Derived_Angle, Degrees)
{

    using library::physics::units::Angle ;

    {

        EXPECT_NO_THROW(Angle::Degrees(123.456)) ;
        EXPECT_TRUE(Angle::Degrees(123.456).isDefined()) ;

        EXPECT_EQ(123.456, Angle::Degrees(123.456).in(Angle::Unit::Degree)) ;

    }

}

TEST (Library_Physics_Units_Derived_Angle, Arcminutes)
{

    using library::physics::units::Angle ;

    {

        EXPECT_NO_THROW(Angle::Arcminutes(123.456)) ;
        EXPECT_TRUE(Angle::Arcminutes(123.456).isDefined()) ;

        EXPECT_EQ(123.456, Angle::Arcminutes(123.456).in(Angle::Unit::Arcminute)) ;

    }

}

TEST (Library_Physics_Units_Derived_Angle, Arcseconds)
{

    using library::physics::units::Angle ;

    {

        EXPECT_NO_THROW(Angle::Arcseconds(123.456)) ;
        EXPECT_TRUE(Angle::Arcseconds(123.456).isDefined()) ;

        EXPECT_EQ(123.456, Angle::Arcseconds(123.456).in(Angle::Unit::Arcsecond)) ;

    }

}

TEST (Library_Physics_Units_Derived_Angle, Revolutions)
{

    using library::physics::units::Angle ;

    {

        EXPECT_NO_THROW(Angle::Revolutions(123.456)) ;
        EXPECT_TRUE(Angle::Revolutions(123.456).isDefined()) ;

        EXPECT_EQ(123.456, Angle::Revolutions(123.456).in(Angle::Unit::Revolution)) ;

    }

}

// TEST (Library_Physics_Units_Derived_Angle, Parse)
// {

//     using library::physics::units::Angle ;

//     {

//         FAIL() ;

//     }

// }

TEST (Library_Physics_Units_Derived_Angle, StringFromUnit)
{

    using library::physics::units::Angle ;

    {

        EXPECT_EQ("Undefined", Angle::StringFromUnit(Angle::Unit::Undefined)) ;
        EXPECT_EQ("Radian", Angle::StringFromUnit(Angle::Unit::Radian)) ;
        EXPECT_EQ("Degree", Angle::StringFromUnit(Angle::Unit::Degree)) ;
        EXPECT_EQ("Arcminute", Angle::StringFromUnit(Angle::Unit::Arcminute)) ;
        EXPECT_EQ("Arcsecond", Angle::StringFromUnit(Angle::Unit::Arcsecond)) ;
        EXPECT_EQ("Revolution", Angle::StringFromUnit(Angle::Unit::Revolution)) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////