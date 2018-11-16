////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Units/Length.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Units/Length.hpp>
#include <Library/Core/Types/Real.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Physics_Units_Length, Constructor)
{

    using library::core::types::Real ;
    using library::physics::units::Length ;

    {

        const Real value = 123.456 ;
        const Length::Unit unit = Length::Unit::Meter ;

        EXPECT_NO_THROW(Length(value, unit)) ;

    }

    {

        const Real value = Real::Undefined() ;
        const Length::Unit unit = Length::Unit::Undefined ;

        EXPECT_NO_THROW(Length(value, unit)) ;

    }

}

TEST (Library_Physics_Units_Length, EqualToOperator)
{

    using library::physics::units::Length ;

    {

        EXPECT_TRUE(Length(1.0, Length::Unit::Meter) == Length(1.0, Length::Unit::Meter)) ;
        EXPECT_TRUE(Length(1.0, Length::Unit::Meter) == Length(+1.0, Length::Unit::Meter)) ;

    }

    {

        EXPECT_TRUE(Length(1.0, Length::Unit::Foot) == Length(0.3048, Length::Unit::Meter)) ;
        EXPECT_TRUE(Length(1.0, Length::Unit::TerrestrialMile) == Length(1609.344, Length::Unit::Meter)) ;
        EXPECT_TRUE(Length(1.0, Length::Unit::NauticalMile) == Length(1852.0, Length::Unit::Meter)) ;
        EXPECT_TRUE(Length(1.0, Length::Unit::AstronomicalUnit) == Length(149597870700.0, Length::Unit::Meter)) ;

    }

    {

        EXPECT_FALSE(Length(1.0, Length::Unit::Meter) == Length(2.0, Length::Unit::Meter)) ;
        EXPECT_FALSE(Length(+1.0, Length::Unit::Meter) == Length(-1.0, Length::Unit::Meter)) ;
        EXPECT_FALSE(Length::Undefined() == Length(1.0, Length::Unit::Meter)) ;
        EXPECT_FALSE(Length(1.0, Length::Unit::Meter) == Length::Undefined()) ;
        EXPECT_FALSE(Length::Undefined() == Length::Undefined()) ;

    }

}

TEST (Library_Physics_Units_Length, NotEqualToOperator)
{

    using library::physics::units::Length ;

    {

        EXPECT_TRUE(Length(+1.0, Length::Unit::Meter) != Length(-1.0, Length::Unit::Meter)) ;
        EXPECT_TRUE(Length(1.0, Length::Unit::Meter) != Length(2.0, Length::Unit::Meter)) ;
        EXPECT_TRUE(Length::Undefined() != Length::Undefined()) ;

    }

    {

        EXPECT_TRUE(Length(1.0, Length::Unit::Meter) != Length(1.0, Length::Unit::Foot)) ;
        EXPECT_TRUE(Length(1.0, Length::Unit::Meter) != Length(1.0, Length::Unit::TerrestrialMile)) ;
        EXPECT_TRUE(Length(1.0, Length::Unit::Meter) != Length(1.0, Length::Unit::NauticalMile)) ;
        EXPECT_TRUE(Length(1.0, Length::Unit::Meter) != Length(1.0, Length::Unit::AstronomicalUnit)) ;

    }

    {

        EXPECT_FALSE(Length(1.0, Length::Unit::Meter) != Length(1.0, Length::Unit::Meter)) ;

    }

}

TEST (Library_Physics_Units_Length, LowerThanOperator)
{

    using library::physics::units::Length ;

    {

        EXPECT_TRUE(Length(1.0, Length::Unit::Meter) < Length(2.0, Length::Unit::Meter)) ;
        EXPECT_TRUE(Length(-1.0, Length::Unit::Meter) < Length(+1.0, Length::Unit::Meter)) ;

    }

    {

        EXPECT_TRUE(Length(1.0, Length::Unit::Meter) < Length(1.0, Length::Unit::TerrestrialMile)) ;
        EXPECT_TRUE(Length(1.0, Length::Unit::Meter) < Length(1.0, Length::Unit::NauticalMile)) ;
        EXPECT_TRUE(Length(1.0, Length::Unit::Meter) < Length(1.0, Length::Unit::AstronomicalUnit)) ;

        EXPECT_TRUE(Length(1.0, Length::Unit::Foot) < Length(1.0, Length::Unit::Meter)) ;

    }

    {

        EXPECT_ANY_THROW(Length::Undefined() < Length(1.0, Length::Unit::Meter)) ;
        EXPECT_ANY_THROW(Length(1.0, Length::Unit::Meter) < Length::Undefined()) ;
        EXPECT_ANY_THROW(Length::Undefined() < Length::Undefined()) ;

    }

}

TEST (Library_Physics_Units_Length, LowerThanOrEqualToOperator)
{

    using library::physics::units::Length ;

    {

        EXPECT_TRUE(Length(1.0, Length::Unit::Meter) <= Length(1.0, Length::Unit::Meter)) ;
        EXPECT_TRUE(Length(1.0, Length::Unit::Meter) <= Length(2.0, Length::Unit::Meter)) ;
        EXPECT_TRUE(Length(-1.0, Length::Unit::Meter) <= Length(+1.0, Length::Unit::Meter)) ;

    }

    {

        EXPECT_TRUE(Length(1.0, Length::Unit::Meter) <= Length(1.0, Length::Unit::TerrestrialMile)) ;
        EXPECT_TRUE(Length(1.0, Length::Unit::Meter) <= Length(1.0, Length::Unit::NauticalMile)) ;
        EXPECT_TRUE(Length(1.0, Length::Unit::Meter) <= Length(1.0, Length::Unit::AstronomicalUnit)) ;

    }

    {

        EXPECT_ANY_THROW(Length::Undefined() <= Length(1.0, Length::Unit::Meter)) ;
        EXPECT_ANY_THROW(Length(1.0, Length::Unit::Meter) <= Length::Undefined()) ;
        EXPECT_ANY_THROW(Length::Undefined() <= Length::Undefined()) ;

    }

}

TEST (Library_Physics_Units_Length, GreaterThanOperator)
{

    using library::physics::units::Length ;

    {

        EXPECT_TRUE(Length(2.0, Length::Unit::Meter) > Length(1.0, Length::Unit::Meter)) ;
        EXPECT_TRUE(Length(+1.0, Length::Unit::Meter) > Length(-1.0, Length::Unit::Meter)) ;

    }

    {

        EXPECT_TRUE(Length(1.0, Length::Unit::TerrestrialMile) > Length(1.0, Length::Unit::Meter)) ;
        EXPECT_TRUE(Length(1.0, Length::Unit::NauticalMile) > Length(1.0, Length::Unit::Meter)) ;
        EXPECT_TRUE(Length(1.0, Length::Unit::AstronomicalUnit) > Length(1.0, Length::Unit::Meter)) ;

        EXPECT_TRUE(Length(1.0, Length::Unit::Meter) > Length(1.0, Length::Unit::Foot)) ;

    }

    {

        EXPECT_ANY_THROW(Length::Undefined() > Length(1.0, Length::Unit::Meter)) ;
        EXPECT_ANY_THROW(Length(1.0, Length::Unit::Meter) > Length::Undefined()) ;
        EXPECT_ANY_THROW(Length::Undefined() > Length::Undefined()) ;

    }

}

TEST (Library_Physics_Units_Length, GreaterThanOrEqualToOperator)
{

    using library::physics::units::Length ;

    {

        EXPECT_TRUE(Length(1.0, Length::Unit::Meter) >= Length(1.0, Length::Unit::Meter)) ;
        EXPECT_TRUE(Length(2.0, Length::Unit::Meter) >= Length(1.0, Length::Unit::Meter)) ;
        EXPECT_TRUE(Length(+1.0, Length::Unit::Meter) >= Length(-1.0, Length::Unit::Meter)) ;

    }

    {

        EXPECT_TRUE(Length(1.0, Length::Unit::TerrestrialMile) >= Length(1.0, Length::Unit::Meter)) ;
        EXPECT_TRUE(Length(1.0, Length::Unit::NauticalMile) >= Length(1.0, Length::Unit::Meter)) ;
        EXPECT_TRUE(Length(1.0, Length::Unit::AstronomicalUnit) >= Length(1.0, Length::Unit::Meter)) ;

    }

    {

        EXPECT_ANY_THROW(Length(1.0, Length::Unit::Meter) >= Length::Undefined()) ;
        EXPECT_ANY_THROW(Length::Undefined() >= Length(1.0, Length::Unit::Meter)) ;
        EXPECT_ANY_THROW(Length::Undefined() >= Length::Undefined()) ;

    }

}

TEST (Library_Physics_Units_Length, AdditionOperator)
{

    using library::physics::units::Length ;

    {

        EXPECT_EQ(Length(2.0, Length::Unit::Meter), Length(1.0, Length::Unit::Meter) + Length(1.0, Length::Unit::Meter)) ;
        EXPECT_EQ(Length(0.0, Length::Unit::Meter), Length(-1.0, Length::Unit::Meter) + Length(+1.0, Length::Unit::Meter)) ;

    }

    {

        EXPECT_EQ(Length(1.3048, Length::Unit::Meter), Length(1.0, Length::Unit::Meter) + Length(1.0, Length::Unit::Foot)) ;
        EXPECT_EQ(Length(1610.344, Length::Unit::Meter), Length(1.0, Length::Unit::Meter) + Length(1.0, Length::Unit::TerrestrialMile)) ;
        EXPECT_EQ(Length(1853.0, Length::Unit::Meter), Length(1.0, Length::Unit::Meter) + Length(1.0, Length::Unit::NauticalMile)) ;
        EXPECT_EQ(Length(149597870701.0, Length::Unit::Meter), Length(1.0, Length::Unit::Meter) + Length(1.0, Length::Unit::AstronomicalUnit)) ;

    }

    {

        EXPECT_ANY_THROW(Length(1.0, Length::Unit::Meter) + Length::Undefined()) ;
        EXPECT_ANY_THROW(Length::Undefined() + Length(1.0, Length::Unit::Meter)) ;
        EXPECT_ANY_THROW(Length::Undefined() + Length::Undefined()) ;

    }

}

TEST (Library_Physics_Units_Length, SubtractionOperator)
{

    using library::physics::units::Length ;

    {

        EXPECT_EQ(Length(0.0, Length::Unit::Meter), Length(1.0, Length::Unit::Meter) - Length(1.0, Length::Unit::Meter)) ;
        EXPECT_EQ(Length(-2.0, Length::Unit::Meter), Length(-1.0, Length::Unit::Meter) - Length(+1.0, Length::Unit::Meter)) ;

    }

    {

        EXPECT_EQ(Length(1.0 - 0.3048, Length::Unit::Meter), Length(1.0, Length::Unit::Meter) - Length(1.0, Length::Unit::Foot)) ;
        EXPECT_EQ(Length(-1608.344, Length::Unit::Meter), Length(1.0, Length::Unit::Meter) - Length(1.0, Length::Unit::TerrestrialMile)) ;
        EXPECT_EQ(Length(-1851.0, Length::Unit::Meter), Length(1.0, Length::Unit::Meter) - Length(1.0, Length::Unit::NauticalMile)) ;
        EXPECT_EQ(Length(-149597870699.0, Length::Unit::Meter), Length(1.0, Length::Unit::Meter) - Length(1.0, Length::Unit::AstronomicalUnit)) ;

    }

    {

        EXPECT_ANY_THROW(Length(1.0, Length::Unit::Meter) - Length::Undefined()) ;
        EXPECT_ANY_THROW(Length::Undefined() - Length(1.0, Length::Unit::Meter)) ;
        EXPECT_ANY_THROW(Length::Undefined() - Length::Undefined()) ;

    }

}

TEST (Library_Physics_Units_Length, MultiplicationOperator)
{

    using library::core::types::Real ;
    using library::physics::units::Length ;

    {

        EXPECT_EQ(Length(+1.0, Length::Unit::Meter), Length(+1.0, Length::Unit::Meter) * +1.0) ;
        EXPECT_EQ(Length(-1.0, Length::Unit::Meter), Length(-1.0, Length::Unit::Meter) * +1.0) ;
        EXPECT_EQ(Length(-1.0, Length::Unit::Meter), Length(+1.0, Length::Unit::Meter) * -1.0) ;

        EXPECT_EQ(Length(+1.0, Length::Unit::Meter), +1.0 * Length(+1.0, Length::Unit::Meter)) ;
        EXPECT_EQ(Length(-1.0, Length::Unit::Meter), +1.0 * Length(-1.0, Length::Unit::Meter)) ;
        EXPECT_EQ(Length(-1.0, Length::Unit::Meter), -1.0 * Length(+1.0, Length::Unit::Meter)) ;

        EXPECT_EQ(Length(+6.0, Length::Unit::Meter), Length(+2.0, Length::Unit::Meter) * +3.0) ;
        EXPECT_EQ(Length(-6.0, Length::Unit::Meter), Length(-2.0, Length::Unit::Meter) * +3.0) ;
        EXPECT_EQ(Length(-6.0, Length::Unit::Meter), Length(+2.0, Length::Unit::Meter) * -3.0) ;

        EXPECT_EQ(Length(+6.0, Length::Unit::Meter), +2.0 * Length(+3.0, Length::Unit::Meter)) ;
        EXPECT_EQ(Length(-6.0, Length::Unit::Meter), +2.0 * Length(-3.0, Length::Unit::Meter)) ;
        EXPECT_EQ(Length(-6.0, Length::Unit::Meter), -2.0 * Length(+3.0, Length::Unit::Meter)) ;

        EXPECT_EQ(Length(0.0, Length::Unit::Meter), Length(+1.0, Length::Unit::Meter) * 0.0) ;
        EXPECT_EQ(Length(0.0, Length::Unit::Meter), Length(-1.0, Length::Unit::Meter) * 0.0) ;
        EXPECT_EQ(Length(0.0, Length::Unit::Meter), Length(0.0, Length::Unit::Meter) * 0.0) ;

        EXPECT_EQ(Length(0.0, Length::Unit::Meter), 0.0 * Length(+1.0, Length::Unit::Meter)) ;
        EXPECT_EQ(Length(0.0, Length::Unit::Meter), 0.0 * Length(-1.0, Length::Unit::Meter)) ;
        EXPECT_EQ(Length(0.0, Length::Unit::Meter), 0.0 * Length(0.0, Length::Unit::Meter)) ;

    }

    {

        EXPECT_EQ(Length(6.0, Length::Unit::Foot), Length(3.0, Length::Unit::Foot) * 2.0) ;
        EXPECT_EQ(Length(6.0, Length::Unit::TerrestrialMile), Length(3.0, Length::Unit::TerrestrialMile) * 2.0) ;
        EXPECT_EQ(Length(6.0, Length::Unit::NauticalMile), Length(3.0, Length::Unit::NauticalMile) * 2.0) ;
        EXPECT_EQ(Length(6.0, Length::Unit::AstronomicalUnit), Length(3.0, Length::Unit::AstronomicalUnit) * 2.0) ;

        EXPECT_EQ(Length(6.0, Length::Unit::Foot), 2.0 * Length(3.0, Length::Unit::Foot)) ;
        EXPECT_EQ(Length(6.0, Length::Unit::TerrestrialMile), 2.0 * Length(3.0, Length::Unit::TerrestrialMile)) ;
        EXPECT_EQ(Length(6.0, Length::Unit::NauticalMile), 2.0 * Length(3.0, Length::Unit::NauticalMile)) ;
        EXPECT_EQ(Length(6.0, Length::Unit::AstronomicalUnit), 2.0 * Length(3.0, Length::Unit::AstronomicalUnit)) ;

    }

    {

        EXPECT_ANY_THROW(Length(1.0, Length::Unit::Meter) * Real::Undefined()) ;
        EXPECT_ANY_THROW(Real::Undefined() * Length(1.0, Length::Unit::Meter)) ;

    }

}

TEST (Library_Physics_Units_Length, DivisionOperator)
{

    using library::core::types::Real ;
    using library::physics::units::Length ;

    {

        EXPECT_EQ(Length(+1.0, Length::Unit::Meter), Length(+1.0, Length::Unit::Meter) / +1.0) ;
        EXPECT_EQ(Length(-1.0, Length::Unit::Meter), Length(-1.0, Length::Unit::Meter) / +1.0) ;
        EXPECT_EQ(Length(-1.0, Length::Unit::Meter), Length(+1.0, Length::Unit::Meter) / -1.0) ;

        EXPECT_EQ(Length(+1.0, Length::Unit::Meter), Length(+2.0, Length::Unit::Meter) / +2.0) ;
        EXPECT_EQ(Length(-1.0, Length::Unit::Meter), Length(-2.0, Length::Unit::Meter) / +2.0) ;
        EXPECT_EQ(Length(-1.0, Length::Unit::Meter), Length(+2.0, Length::Unit::Meter) / -2.0) ;

        EXPECT_EQ(Length(+2.0, Length::Unit::Meter), Length(+4.0, Length::Unit::Meter) / +2.0) ;
        EXPECT_EQ(Length(-2.0, Length::Unit::Meter), Length(-4.0, Length::Unit::Meter) / +2.0) ;
        EXPECT_EQ(Length(-2.0, Length::Unit::Meter), Length(+4.0, Length::Unit::Meter) / -2.0) ;

    }

    {

        EXPECT_EQ(Length(0.5, Length::Unit::Foot), Length(1.0, Length::Unit::Foot) / 2.0) ;
        EXPECT_EQ(Length(0.5, Length::Unit::TerrestrialMile), Length(1.0, Length::Unit::TerrestrialMile) / 2.0) ;
        EXPECT_EQ(Length(0.5, Length::Unit::NauticalMile), Length(1.0, Length::Unit::NauticalMile) / 2.0) ;
        EXPECT_EQ(Length(0.5, Length::Unit::AstronomicalUnit), Length(1.0, Length::Unit::AstronomicalUnit) / 2.0) ;

    }

    {

        EXPECT_ANY_THROW(Length(1.0, Length::Unit::Meter) / Real::Undefined()) ;
        EXPECT_ANY_THROW(Length(1.0, Length::Unit::Meter) / Real::Zero()) ;

    }

}

TEST (Library_Physics_Units_Length, AdditionAssignmentOperator)
{

    using library::physics::units::Length ;

    {

        EXPECT_EQ(Length(2.0, Length::Unit::Meter), Length(1.0, Length::Unit::Meter) += Length(1.0, Length::Unit::Meter)) ;
        EXPECT_EQ(Length(0.0, Length::Unit::Meter), Length(-1.0, Length::Unit::Meter) += Length(+1.0, Length::Unit::Meter)) ;

    }

    {

        EXPECT_EQ(Length(1.3048, Length::Unit::Meter), Length(1.0, Length::Unit::Meter) += Length(1.0, Length::Unit::Foot)) ;
        EXPECT_EQ(Length(1610.344, Length::Unit::Meter), Length(1.0, Length::Unit::Meter) += Length(1.0, Length::Unit::TerrestrialMile)) ;
        EXPECT_EQ(Length(1853.0, Length::Unit::Meter), Length(1.0, Length::Unit::Meter) += Length(1.0, Length::Unit::NauticalMile)) ;
        EXPECT_EQ(Length(149597870701.0, Length::Unit::Meter), Length(1.0, Length::Unit::Meter) += Length(1.0, Length::Unit::AstronomicalUnit)) ;

    }

    {

        EXPECT_ANY_THROW(Length(1.0, Length::Unit::Meter) += Length::Undefined()) ;
        EXPECT_ANY_THROW(Length::Undefined() += Length(1.0, Length::Unit::Meter)) ;
        EXPECT_ANY_THROW(Length::Undefined() += Length::Undefined()) ;

    }

}

TEST (Library_Physics_Units_Length, SubtractionAssignmentOperator)
{

    using library::physics::units::Length ;

    {

        EXPECT_EQ(Length(0.0, Length::Unit::Meter), Length(1.0, Length::Unit::Meter) -= Length(1.0, Length::Unit::Meter)) ;
        EXPECT_EQ(Length(-2.0, Length::Unit::Meter), Length(-1.0, Length::Unit::Meter) -= Length(+1.0, Length::Unit::Meter)) ;

    }

    {

        EXPECT_EQ(Length(1.0 - 0.3048, Length::Unit::Meter), Length(1.0, Length::Unit::Meter) -= Length(1.0, Length::Unit::Foot)) ;
        EXPECT_EQ(Length(-1608.344, Length::Unit::Meter), Length(1.0, Length::Unit::Meter) -= Length(1.0, Length::Unit::TerrestrialMile)) ;
        EXPECT_EQ(Length(-1851.0, Length::Unit::Meter), Length(1.0, Length::Unit::Meter) -= Length(1.0, Length::Unit::NauticalMile)) ;
        EXPECT_EQ(Length(-149597870699.0, Length::Unit::Meter), Length(1.0, Length::Unit::Meter) -= Length(1.0, Length::Unit::AstronomicalUnit)) ;

    }

    {

        EXPECT_ANY_THROW(Length(1.0, Length::Unit::Meter) -= Length::Undefined()) ;
        EXPECT_ANY_THROW(Length::Undefined() -= Length(1.0, Length::Unit::Meter)) ;
        EXPECT_ANY_THROW(Length::Undefined() -= Length::Undefined()) ;

    }

}

TEST (Library_Physics_Units_Length, MultiplicationAssignmentOperator)
{

    using library::core::types::Real ;
    using library::physics::units::Length ;

    {

        EXPECT_EQ(Length(+1.0, Length::Unit::Meter), Length(+1.0, Length::Unit::Meter) *= +1.0) ;
        EXPECT_EQ(Length(-1.0, Length::Unit::Meter), Length(-1.0, Length::Unit::Meter) *= +1.0) ;
        EXPECT_EQ(Length(-1.0, Length::Unit::Meter), Length(+1.0, Length::Unit::Meter) *= -1.0) ;

        EXPECT_EQ(Length(+6.0, Length::Unit::Meter), Length(+2.0, Length::Unit::Meter) *= +3.0) ;
        EXPECT_EQ(Length(-6.0, Length::Unit::Meter), Length(-2.0, Length::Unit::Meter) *= +3.0) ;
        EXPECT_EQ(Length(-6.0, Length::Unit::Meter), Length(+2.0, Length::Unit::Meter) *= -3.0) ;

        EXPECT_EQ(Length(0.0, Length::Unit::Meter), Length(+1.0, Length::Unit::Meter) *= 0.0) ;
        EXPECT_EQ(Length(0.0, Length::Unit::Meter), Length(-1.0, Length::Unit::Meter) *= 0.0) ;
        EXPECT_EQ(Length(0.0, Length::Unit::Meter), Length(0.0, Length::Unit::Meter) *= 0.0) ;

    }

    {

        EXPECT_EQ(Length(6.0, Length::Unit::Foot), Length(3.0, Length::Unit::Foot) *= 2.0) ;
        EXPECT_EQ(Length(6.0, Length::Unit::TerrestrialMile), Length(3.0, Length::Unit::TerrestrialMile) *= 2.0) ;
        EXPECT_EQ(Length(6.0, Length::Unit::NauticalMile), Length(3.0, Length::Unit::NauticalMile) *= 2.0) ;
        EXPECT_EQ(Length(6.0, Length::Unit::AstronomicalUnit), Length(3.0, Length::Unit::AstronomicalUnit) *= 2.0) ;

    }

    {

        EXPECT_ANY_THROW(Length(1.0, Length::Unit::Meter) *= Real::Undefined()) ;

    }

}

TEST (Library_Physics_Units_Length, DivisionAssignmentOperator)
{

    using library::core::types::Real ;
    using library::physics::units::Length ;

    {

        EXPECT_EQ(Length(+1.0, Length::Unit::Meter), Length(+1.0, Length::Unit::Meter) /= +1.0) ;
        EXPECT_EQ(Length(-1.0, Length::Unit::Meter), Length(-1.0, Length::Unit::Meter) /= +1.0) ;
        EXPECT_EQ(Length(-1.0, Length::Unit::Meter), Length(+1.0, Length::Unit::Meter) /= -1.0) ;

        EXPECT_EQ(Length(+1.0, Length::Unit::Meter), Length(+2.0, Length::Unit::Meter) /= +2.0) ;
        EXPECT_EQ(Length(-1.0, Length::Unit::Meter), Length(-2.0, Length::Unit::Meter) /= +2.0) ;
        EXPECT_EQ(Length(-1.0, Length::Unit::Meter), Length(+2.0, Length::Unit::Meter) /= -2.0) ;

        EXPECT_EQ(Length(+2.0, Length::Unit::Meter), Length(+4.0, Length::Unit::Meter) /= +2.0) ;
        EXPECT_EQ(Length(-2.0, Length::Unit::Meter), Length(-4.0, Length::Unit::Meter) /= +2.0) ;
        EXPECT_EQ(Length(-2.0, Length::Unit::Meter), Length(+4.0, Length::Unit::Meter) /= -2.0) ;

    }

    {

        EXPECT_EQ(Length(0.5, Length::Unit::Foot), Length(1.0, Length::Unit::Foot) /= 2.0) ;
        EXPECT_EQ(Length(0.5, Length::Unit::TerrestrialMile), Length(1.0, Length::Unit::TerrestrialMile) /= 2.0) ;
        EXPECT_EQ(Length(0.5, Length::Unit::NauticalMile), Length(1.0, Length::Unit::NauticalMile) /= 2.0) ;
        EXPECT_EQ(Length(0.5, Length::Unit::AstronomicalUnit), Length(1.0, Length::Unit::AstronomicalUnit) /= 2.0) ;

    }

    {

        EXPECT_ANY_THROW(Length(1.0, Length::Unit::Meter) /= Real::Undefined()) ;
        EXPECT_ANY_THROW(Length(1.0, Length::Unit::Meter) /= Real::Zero()) ;

    }

}

TEST (Library_Physics_Units_Length, StreamOperator)
{

    using library::physics::units::Length ;

    {

        testing::internal::CaptureStdout() ;

        EXPECT_NO_THROW(std::cout << Length(0.5, Length::Unit::Foot) << std::endl) ;

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty()) ;

    }

}

TEST (Library_Physics_Units_Length, IsDefined)
{

    using library::core::types::Real ;
    using library::physics::units::Length ;

    {

        EXPECT_TRUE(Length(0.0, Length::Unit::Meter).isDefined()) ;
        
        EXPECT_TRUE(Length(1.0, Length::Unit::Meter).isDefined()) ;
        EXPECT_TRUE(Length(1.0, Length::Unit::Foot).isDefined()) ;
        EXPECT_TRUE(Length(1.0, Length::Unit::TerrestrialMile).isDefined()) ;
        EXPECT_TRUE(Length(1.0, Length::Unit::NauticalMile).isDefined()) ;
        EXPECT_TRUE(Length(1.0, Length::Unit::AstronomicalUnit).isDefined()) ;

    }

    {

        EXPECT_FALSE(Length::Undefined().isDefined()) ;
        EXPECT_FALSE(Length(Real::Undefined(), Length::Unit::Meter).isDefined()) ;
        EXPECT_FALSE(Length(1.0, Length::Unit::Undefined).isDefined()) ;

    }

}

TEST (Library_Physics_Units_Length, GetUnit)
{

    using library::physics::units::Length ;

    {

        EXPECT_EQ(Length::Unit::Undefined, Length(1.0, Length::Unit::Undefined).getUnit()) ;
        EXPECT_EQ(Length::Unit::Meter, Length(1.0, Length::Unit::Meter).getUnit()) ;
        EXPECT_EQ(Length::Unit::Foot, Length(1.0, Length::Unit::Foot).getUnit()) ;
        EXPECT_EQ(Length::Unit::TerrestrialMile, Length(1.0, Length::Unit::TerrestrialMile).getUnit()) ;
        EXPECT_EQ(Length::Unit::NauticalMile, Length(1.0, Length::Unit::NauticalMile).getUnit()) ;
        EXPECT_EQ(Length::Unit::AstronomicalUnit, Length(1.0, Length::Unit::AstronomicalUnit).getUnit()) ;

    }

}

TEST (Library_Physics_Units_Length, In)
{

    using library::physics::units::Length ;

    {

        EXPECT_EQ(1.0, Length(1.0, Length::Unit::Meter).in(Length::Unit::Meter)) ;
        EXPECT_EQ(1.0, Length(1.0, Length::Unit::Foot).in(Length::Unit::Foot)) ;
        EXPECT_EQ(1.0, Length(1.0, Length::Unit::TerrestrialMile).in(Length::Unit::TerrestrialMile)) ;
        EXPECT_EQ(1.0, Length(1.0, Length::Unit::NauticalMile).in(Length::Unit::NauticalMile)) ;
        EXPECT_EQ(1.0, Length(1.0, Length::Unit::AstronomicalUnit).in(Length::Unit::AstronomicalUnit)) ;

    }

    {

        EXPECT_FALSE(Length::Undefined().in(Length::Unit::Meter).isDefined()) ;

    }

}

TEST (Library_Physics_Units_Length, InMeters)
{

    using library::physics::units::Length ;

    {

        EXPECT_EQ(123.456, Length(123.456, Length::Unit::Meter).inMeters()) ;

    }

    {

        EXPECT_FALSE(Length::Undefined().inMeters().isDefined()) ;

    }

}

TEST (Library_Physics_Units_Length, InKilometers)
{

    using library::physics::units::Length ; 

    {

        EXPECT_EQ(123.456, Length(123456.0, Length::Unit::Meter).inKilometers()) ;

    }

    {

        EXPECT_FALSE(Length::Undefined().inKilometers().isDefined()) ;

    }

}

TEST (Library_Physics_Units_Length, ToString)
{

    using library::physics::units::Length ; 

    {

        EXPECT_EQ("1.0 [m]", Length(1.0, Length::Unit::Meter).toString()) ;
        EXPECT_EQ("1.0 [ft]", Length(1.0, Length::Unit::Foot).toString()) ;
        EXPECT_EQ("1.0 [mi]", Length(1.0, Length::Unit::TerrestrialMile).toString()) ;
        EXPECT_EQ("1.0 [nmi]", Length(1.0, Length::Unit::NauticalMile).toString()) ;
        EXPECT_EQ("1.0 [AU]", Length(1.0, Length::Unit::AstronomicalUnit).toString()) ;

        EXPECT_EQ("-1.0 [m]", Length(-1.0, Length::Unit::Meter).toString()) ;
        EXPECT_EQ("-1.0 [ft]", Length(-1.0, Length::Unit::Foot).toString()) ;
        EXPECT_EQ("-1.0 [mi]", Length(-1.0, Length::Unit::TerrestrialMile).toString()) ;
        EXPECT_EQ("-1.0 [nmi]", Length(-1.0, Length::Unit::NauticalMile).toString()) ;
        EXPECT_EQ("-1.0 [AU]", Length(-1.0, Length::Unit::AstronomicalUnit).toString()) ;

        EXPECT_EQ("123.456 [m]", Length(123.456, Length::Unit::Meter).toString()) ;
        EXPECT_EQ("123.456 [ft]", Length(123.456, Length::Unit::Foot).toString()) ;
        EXPECT_EQ("123.456 [mi]", Length(123.456, Length::Unit::TerrestrialMile).toString()) ;
        EXPECT_EQ("123.456 [nmi]", Length(123.456, Length::Unit::NauticalMile).toString()) ;
        EXPECT_EQ("123.456 [AU]", Length(123.456, Length::Unit::AstronomicalUnit).toString()) ;

    }

    {

        EXPECT_EQ("1.000 [m]", Length(1.0, Length::Unit::Meter).toString(3)) ;
        EXPECT_EQ("1.000 [ft]", Length(1.0, Length::Unit::Foot).toString(3)) ;
        EXPECT_EQ("1.000 [mi]", Length(1.0, Length::Unit::TerrestrialMile).toString(3)) ;
        EXPECT_EQ("1.000 [nmi]", Length(1.0, Length::Unit::NauticalMile).toString(3)) ;
        EXPECT_EQ("1.000 [AU]", Length(1.0, Length::Unit::AstronomicalUnit).toString(3)) ;

        EXPECT_EQ("-1.000 [m]", Length(-1.0, Length::Unit::Meter).toString(3)) ;
        EXPECT_EQ("-1.000 [ft]", Length(-1.0, Length::Unit::Foot).toString(3)) ;
        EXPECT_EQ("-1.000 [mi]", Length(-1.0, Length::Unit::TerrestrialMile).toString(3)) ;
        EXPECT_EQ("-1.000 [nmi]", Length(-1.0, Length::Unit::NauticalMile).toString(3)) ;
        EXPECT_EQ("-1.000 [AU]", Length(-1.0, Length::Unit::AstronomicalUnit).toString(3)) ;

        EXPECT_EQ("123.456 [m]", Length(123.456123, Length::Unit::Meter).toString(3)) ;
        EXPECT_EQ("123.456 [ft]", Length(123.456123, Length::Unit::Foot).toString(3)) ;
        EXPECT_EQ("123.456 [mi]", Length(123.456123, Length::Unit::TerrestrialMile).toString(3)) ;
        EXPECT_EQ("123.456 [nmi]", Length(123.456123, Length::Unit::NauticalMile).toString(3)) ;
        EXPECT_EQ("123.456 [AU]", Length(123.456123, Length::Unit::AstronomicalUnit).toString(3)) ;

    }

    {

        EXPECT_ANY_THROW(Length::Undefined().toString()) ;
        
    }

}

TEST (Library_Physics_Units_Length, Undefined)
{

    using library::physics::units::Length ;

    {

        EXPECT_NO_THROW(Length::Undefined()) ;
        EXPECT_FALSE(Length::Undefined().isDefined()) ;

        EXPECT_NO_THROW(Length::Undefined().in(Length::Unit::Meter)) ;

    }

}

TEST (Library_Physics_Units_Length, Millimeters)
{

    using library::physics::units::Length ;

    {

        EXPECT_NO_THROW(Length::Millimeters(123.456)) ;
        EXPECT_TRUE(Length::Millimeters(123.456).isDefined()) ;

        EXPECT_EQ(0.123456, Length::Millimeters(123.456).in(Length::Unit::Meter)) ;

    }

}

TEST (Library_Physics_Units_Length, Meters)
{

    using library::physics::units::Length ;

    {

        EXPECT_NO_THROW(Length::Meters(123.456)) ;
        EXPECT_TRUE(Length::Meters(123.456).isDefined()) ;

        EXPECT_EQ(123.456, Length::Meters(123.456).in(Length::Unit::Meter)) ;

    }

}

TEST (Library_Physics_Units_Length, Kilometers)
{

    using library::physics::units::Length ;

    {

        EXPECT_NO_THROW(Length::Kilometers(123.456)) ;
        EXPECT_TRUE(Length::Kilometers(123.456).isDefined()) ;

        EXPECT_EQ(123456.0, Length::Kilometers(123.456).in(Length::Unit::Meter)) ;

    }

}

// TEST (Library_Physics_Units_Length, Parse)
// {

//     using library::physics::units::Length ;

//     {

//         FAIL() ;

//     }

// }

TEST (Library_Physics_Units_Length, StringFromUnit)
{

    using library::physics::units::Length ;

    {

        EXPECT_EQ("Undefined", Length::StringFromUnit(Length::Unit::Undefined)) ;
        EXPECT_EQ("Meter", Length::StringFromUnit(Length::Unit::Meter)) ;
        EXPECT_EQ("Foot", Length::StringFromUnit(Length::Unit::Foot)) ;
        EXPECT_EQ("Terrestrial Mile", Length::StringFromUnit(Length::Unit::TerrestrialMile)) ;
        EXPECT_EQ("Nautical Mile", Length::StringFromUnit(Length::Unit::NauticalMile)) ;
        EXPECT_EQ("Astronomical Unit", Length::StringFromUnit(Length::Unit::AstronomicalUnit)) ;

    }

}

TEST (Library_Physics_Units_Length, SymbolFromUnit)
{

    using library::physics::units::Length ;

    {

        EXPECT_EQ("m", Length::SymbolFromUnit(Length::Unit::Meter)) ;
        EXPECT_EQ("ft", Length::SymbolFromUnit(Length::Unit::Foot)) ;
        EXPECT_EQ("mi", Length::SymbolFromUnit(Length::Unit::TerrestrialMile)) ;
        EXPECT_EQ("nmi", Length::SymbolFromUnit(Length::Unit::NauticalMile)) ;
        EXPECT_EQ("AU", Length::SymbolFromUnit(Length::Unit::AstronomicalUnit)) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////