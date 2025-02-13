/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Type/Real.hpp>

#include <OpenSpaceToolkit/Physics/Unit/Derived.hpp>

#include <Global.test.hpp>

using ostk::core::type::Real;

using ostk::physics::unit::Angle;
using ostk::physics::unit::Derived;
using ostk::physics::unit::ElectricCurrent;
using ostk::physics::unit::Length;
using ostk::physics::unit::Mass;
using ostk::physics::unit::Time;

TEST(OpenSpaceToolkit_Physics_Unit_Derived, Constructor)
{
    {
        const Real value = 123.456;
        const Derived::Unit unit = {
            Length::Unit::Meter,
            Derived::Order::One(),
            Mass::Unit::Kilogram,
            Derived::Order::One(),
            Time::Unit::Second,
            Derived::Order::One(),
            ElectricCurrent::Unit::Ampere,
            Derived::Order::One(),
            Angle::Unit::Radian,
            Derived::Order::One()
        };

        EXPECT_NO_THROW(Derived(value, unit));
    }

    {
        const Real value = 123.456;
        const Derived::Unit unit = {
            Length::Unit::Meter,
            Derived::Order::Two(),
            Mass::Unit::Kilogram,
            {1},
            Time::Unit::Second,
            {3, 2},
            ElectricCurrent::Unit::Ampere,
            {0},
            Angle::Unit::Undefined,
            {0}
        };

        EXPECT_NO_THROW(Derived(value, unit));
    }

    {
        const Real value = 123.456;
        const Derived::Unit unit = {
            Length::Unit::Meter,
            {1, 2},
            Mass::Unit::Kilogram,
            {1},
            Time::Unit::Second,
            {3, 2},
            ElectricCurrent::Unit::Undefined,
            {0},
            Angle::Unit::Undefined,
            {0}
        };

        EXPECT_NO_THROW(Derived(value, unit));
    }

    {
        const Real value = Real::Undefined();
        const Derived::Unit unit = Derived::Unit::Undefined();

        EXPECT_NO_THROW(Derived(value, unit));
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Derived, EqualToOperator)
{
    {
        const Derived::Unit unit = {
            Length::Unit::Meter,
            Derived::Order::One(),
            Mass::Unit::Kilogram,
            Derived::Order::One(),
            Time::Unit::Second,
            Derived::Order::One(),
            ElectricCurrent::Unit::Ampere,
            Derived::Order::One(),
            Angle::Unit::Radian,
            Derived::Order::One()
        };

        EXPECT_TRUE(Derived(1.0, unit) == Derived(1.0, unit));
        EXPECT_TRUE(Derived(1.0, unit) == Derived(+1.0, unit));
    }

    {
        const Derived::Unit firstUnit = {
            Length::Unit::Foot,
            Derived::Order::One(),
            Mass::Unit::Kilogram,
            Derived::Order::One(),
            Time::Unit::Second,
            Derived::Order::One(),
            ElectricCurrent::Unit::Ampere,
            Derived::Order::One(),
            Angle::Unit::Radian,
            Derived::Order::One()
        };

        const Derived::Unit secondUnit = {
            Length::Unit::Meter,
            Derived::Order::One(),
            Mass::Unit::Kilogram,
            Derived::Order::One(),
            Time::Unit::Second,
            Derived::Order::One(),
            ElectricCurrent::Unit::Ampere,
            Derived::Order::One(),
            Angle::Unit::Radian,
            Derived::Order::One()
        };

        EXPECT_TRUE(Derived(1.0, firstUnit) == Derived(0.3048, secondUnit));
    }

    {
        const Derived::Unit unit = {
            Length::Unit::Meter,
            Derived::Order::One(),
            Mass::Unit::Kilogram,
            Derived::Order::One(),
            Time::Unit::Second,
            Derived::Order::One(),
            ElectricCurrent::Unit::Ampere,
            Derived::Order::One(),
            Angle::Unit::Radian,
            Derived::Order::One()
        };

        EXPECT_FALSE(Derived(1.0, unit) == Derived(2.0, unit));
    }

    {
        const Derived::Unit firstUnit = {
            Length::Unit::Meter,
            Derived::Order::One(),
            Mass::Unit::Kilogram,
            Derived::Order::One(),
            Time::Unit::Second,
            Derived::Order::One(),
            ElectricCurrent::Unit::Ampere,
            Derived::Order::One(),
            Angle::Unit::Radian,
            Derived::Order::One()
        };

        const Derived::Unit secondUnit = {
            Length::Unit::Meter,
            Derived::Order::One(),
            Mass::Unit::Kilogram,
            Derived::Order::One(),
            Time::Unit::Second,
            Derived::Order::One(),
            ElectricCurrent::Unit::Ampere,
            Derived::Order::One(),
            Angle::Unit::Radian,
            Derived::Order::Zero()
        };

        EXPECT_ANY_THROW(Derived(1.0, firstUnit) == Derived(1.0, secondUnit));
    }
}

// TEST (OpenSpaceToolkit_Physics_Unit_Derived, NotEqualToOperator)
// {

//     {

//         EXPECT_TRUE(Derived(+1.0, Derived::Unit::Meter) != Derived(-1.0, Derived::Unit::Meter)) ;
//         EXPECT_TRUE(Derived(1.0, Derived::Unit::Meter) != Derived(2.0, Derived::Unit::Meter)) ;
//         EXPECT_TRUE(Derived::Undefined() != Derived::Undefined()) ;

//     }

//     {

//         EXPECT_TRUE(Derived(1.0, Derived::Unit::Meter) != Derived(1.0, Derived::Unit::Foot)) ;
//         EXPECT_TRUE(Derived(1.0, Derived::Unit::Meter) != Derived(1.0, Derived::Unit::TerrestrialMile)) ;
//         EXPECT_TRUE(Derived(1.0, Derived::Unit::Meter) != Derived(1.0, Derived::Unit::NauticalMile)) ;
//         EXPECT_TRUE(Derived(1.0, Derived::Unit::Meter) != Derived(1.0, Derived::Unit::AstronomicalUnit)) ;

//     }

//     {

//         EXPECT_FALSE(Derived(1.0, Derived::Unit::Meter) != Derived(1.0, Derived::Unit::Meter)) ;

//     }

// }

// TEST (OpenSpaceToolkit_Physics_Unit_Derived, LowerThanOperator)
// {

//     {

//         EXPECT_TRUE(Derived(1.0, Derived::Unit::Meter) < Derived(2.0, Derived::Unit::Meter)) ;
//         EXPECT_TRUE(Derived(-1.0, Derived::Unit::Meter) < Derived(+1.0, Derived::Unit::Meter)) ;

//     }

//     {

//         EXPECT_TRUE(Derived(1.0, Derived::Unit::Meter) < Derived(1.0, Derived::Unit::TerrestrialMile)) ;
//         EXPECT_TRUE(Derived(1.0, Derived::Unit::Meter) < Derived(1.0, Derived::Unit::NauticalMile)) ;
//         EXPECT_TRUE(Derived(1.0, Derived::Unit::Meter) < Derived(1.0, Derived::Unit::AstronomicalUnit)) ;

//         EXPECT_TRUE(Derived(1.0, Derived::Unit::Foot) < Derived(1.0, Derived::Unit::Meter)) ;

//     }

//     {

//         EXPECT_ANY_THROW(Derived::Undefined() < Derived(1.0, Derived::Unit::Meter)) ;
//         EXPECT_ANY_THROW(Derived(1.0, Derived::Unit::Meter) < Derived::Undefined()) ;
//         EXPECT_ANY_THROW(Derived::Undefined() < Derived::Undefined()) ;

//     }

// }

// TEST (OpenSpaceToolkit_Physics_Unit_Derived, LowerThanOrEqualToOperator)
// {

//     {

//         EXPECT_TRUE(Derived(1.0, Derived::Unit::Meter) <= Derived(1.0, Derived::Unit::Meter)) ;
//         EXPECT_TRUE(Derived(1.0, Derived::Unit::Meter) <= Derived(2.0, Derived::Unit::Meter)) ;
//         EXPECT_TRUE(Derived(-1.0, Derived::Unit::Meter) <= Derived(+1.0, Derived::Unit::Meter)) ;

//     }

//     {

//         EXPECT_TRUE(Derived(1.0, Derived::Unit::Meter) <= Derived(1.0, Derived::Unit::TerrestrialMile)) ;
//         EXPECT_TRUE(Derived(1.0, Derived::Unit::Meter) <= Derived(1.0, Derived::Unit::NauticalMile)) ;
//         EXPECT_TRUE(Derived(1.0, Derived::Unit::Meter) <= Derived(1.0, Derived::Unit::AstronomicalUnit)) ;

//     }

//     {

//         EXPECT_ANY_THROW(Derived::Undefined() <= Derived(1.0, Derived::Unit::Meter)) ;
//         EXPECT_ANY_THROW(Derived(1.0, Derived::Unit::Meter) <= Derived::Undefined()) ;
//         EXPECT_ANY_THROW(Derived::Undefined() <= Derived::Undefined()) ;

//     }

// }

// TEST (OpenSpaceToolkit_Physics_Unit_Derived, GreaterThanOperator)
// {

//     {

//         EXPECT_TRUE(Derived(2.0, Derived::Unit::Meter) > Derived(1.0, Derived::Unit::Meter)) ;
//         EXPECT_TRUE(Derived(+1.0, Derived::Unit::Meter) > Derived(-1.0, Derived::Unit::Meter)) ;

//     }

//     {

//         EXPECT_TRUE(Derived(1.0, Derived::Unit::TerrestrialMile) > Derived(1.0, Derived::Unit::Meter)) ;
//         EXPECT_TRUE(Derived(1.0, Derived::Unit::NauticalMile) > Derived(1.0, Derived::Unit::Meter)) ;
//         EXPECT_TRUE(Derived(1.0, Derived::Unit::AstronomicalUnit) > Derived(1.0, Derived::Unit::Meter)) ;

//         EXPECT_TRUE(Derived(1.0, Derived::Unit::Meter) > Derived(1.0, Derived::Unit::Foot)) ;

//     }

//     {

//         EXPECT_ANY_THROW(Derived::Undefined() > Derived(1.0, Derived::Unit::Meter)) ;
//         EXPECT_ANY_THROW(Derived(1.0, Derived::Unit::Meter) > Derived::Undefined()) ;
//         EXPECT_ANY_THROW(Derived::Undefined() > Derived::Undefined()) ;

//     }

// }

// TEST (OpenSpaceToolkit_Physics_Unit_Derived, GreaterThanOrEqualToOperator)
// {

//     {

//         EXPECT_TRUE(Derived(1.0, Derived::Unit::Meter) >= Derived(1.0, Derived::Unit::Meter)) ;
//         EXPECT_TRUE(Derived(2.0, Derived::Unit::Meter) >= Derived(1.0, Derived::Unit::Meter)) ;
//         EXPECT_TRUE(Derived(+1.0, Derived::Unit::Meter) >= Derived(-1.0, Derived::Unit::Meter)) ;

//     }

//     {

//         EXPECT_TRUE(Derived(1.0, Derived::Unit::TerrestrialMile) >= Derived(1.0, Derived::Unit::Meter)) ;
//         EXPECT_TRUE(Derived(1.0, Derived::Unit::NauticalMile) >= Derived(1.0, Derived::Unit::Meter)) ;
//         EXPECT_TRUE(Derived(1.0, Derived::Unit::AstronomicalUnit) >= Derived(1.0, Derived::Unit::Meter)) ;

//     }

//     {

//         EXPECT_ANY_THROW(Derived(1.0, Derived::Unit::Meter) >= Derived::Undefined()) ;
//         EXPECT_ANY_THROW(Derived::Undefined() >= Derived(1.0, Derived::Unit::Meter)) ;
//         EXPECT_ANY_THROW(Derived::Undefined() >= Derived::Undefined()) ;

//     }

// }

// TEST (OpenSpaceToolkit_Physics_Unit_Derived, AdditionOperator)
// {

//     {

//         EXPECT_EQ(Derived(2.0, Derived::Unit::Meter), Derived(1.0, Derived::Unit::Meter) + Derived(1.0,
//         Derived::Unit::Meter)) ; EXPECT_EQ(Derived(0.0, Derived::Unit::Meter), Derived(-1.0, Derived::Unit::Meter) +
//         Derived(+1.0, Derived::Unit::Meter)) ;

//     }

//     {

//         EXPECT_EQ(Derived(1.3048, Derived::Unit::Meter), Derived(1.0, Derived::Unit::Meter) + Derived(1.0,
//         Derived::Unit::Foot)) ; EXPECT_EQ(Derived(1610.344, Derived::Unit::Meter), Derived(1.0, Derived::Unit::Meter)
//         + Derived(1.0, Derived::Unit::TerrestrialMile)) ; EXPECT_EQ(Derived(1853.0, Derived::Unit::Meter),
//         Derived(1.0, Derived::Unit::Meter) + Derived(1.0, Derived::Unit::NauticalMile)) ;
//         EXPECT_EQ(Derived(149597870701.0, Derived::Unit::Meter), Derived(1.0, Derived::Unit::Meter) + Derived(1.0,
//         Derived::Unit::AstronomicalUnit)) ;

//     }

//     {

//         EXPECT_ANY_THROW(Derived(1.0, Derived::Unit::Meter) + Derived::Undefined()) ;
//         EXPECT_ANY_THROW(Derived::Undefined() + Derived(1.0, Derived::Unit::Meter)) ;
//         EXPECT_ANY_THROW(Derived::Undefined() + Derived::Undefined()) ;

//     }

// }

// TEST (OpenSpaceToolkit_Physics_Unit_Derived, SubtractionOperator)
// {

//     {

//         EXPECT_EQ(Derived(0.0, Derived::Unit::Meter), Derived(1.0, Derived::Unit::Meter) - Derived(1.0,
//         Derived::Unit::Meter)) ; EXPECT_EQ(Derived(-2.0, Derived::Unit::Meter), Derived(-1.0, Derived::Unit::Meter) -
//         Derived(+1.0, Derived::Unit::Meter)) ;

//     }

//     {

//         EXPECT_EQ(Derived(1.0 - 0.3048, Derived::Unit::Meter), Derived(1.0, Derived::Unit::Meter) - Derived(1.0,
//         Derived::Unit::Foot)) ; EXPECT_EQ(Derived(-1608.344, Derived::Unit::Meter), Derived(1.0,
//         Derived::Unit::Meter) - Derived(1.0, Derived::Unit::TerrestrialMile)) ; EXPECT_EQ(Derived(-1851.0,
//         Derived::Unit::Meter), Derived(1.0, Derived::Unit::Meter) - Derived(1.0, Derived::Unit::NauticalMile)) ;
//         EXPECT_EQ(Derived(-149597870699.0, Derived::Unit::Meter), Derived(1.0, Derived::Unit::Meter) - Derived(1.0,
//         Derived::Unit::AstronomicalUnit)) ;

//     }

//     {

//         EXPECT_ANY_THROW(Derived(1.0, Derived::Unit::Meter) - Derived::Undefined()) ;
//         EXPECT_ANY_THROW(Derived::Undefined() - Derived(1.0, Derived::Unit::Meter)) ;
//         EXPECT_ANY_THROW(Derived::Undefined() - Derived::Undefined()) ;

//     }

// }

// TEST (OpenSpaceToolkit_Physics_Unit_Derived, MultiplicationOperator)
// {

//     using ostk::core::type::Real ;

//     {

//         EXPECT_EQ(Derived(+1.0, Derived::Unit::Meter), Derived(+1.0, Derived::Unit::Meter) * +1.0) ;
//         EXPECT_EQ(Derived(-1.0, Derived::Unit::Meter), Derived(-1.0, Derived::Unit::Meter) * +1.0) ;
//         EXPECT_EQ(Derived(-1.0, Derived::Unit::Meter), Derived(+1.0, Derived::Unit::Meter) * -1.0) ;

//         EXPECT_EQ(Derived(+1.0, Derived::Unit::Meter), +1.0 * Derived(+1.0, Derived::Unit::Meter)) ;
//         EXPECT_EQ(Derived(-1.0, Derived::Unit::Meter), +1.0 * Derived(-1.0, Derived::Unit::Meter)) ;
//         EXPECT_EQ(Derived(-1.0, Derived::Unit::Meter), -1.0 * Derived(+1.0, Derived::Unit::Meter)) ;

//         EXPECT_EQ(Derived(+6.0, Derived::Unit::Meter), Derived(+2.0, Derived::Unit::Meter) * +3.0) ;
//         EXPECT_EQ(Derived(-6.0, Derived::Unit::Meter), Derived(-2.0, Derived::Unit::Meter) * +3.0) ;
//         EXPECT_EQ(Derived(-6.0, Derived::Unit::Meter), Derived(+2.0, Derived::Unit::Meter) * -3.0) ;

//         EXPECT_EQ(Derived(+6.0, Derived::Unit::Meter), +2.0 * Derived(+3.0, Derived::Unit::Meter)) ;
//         EXPECT_EQ(Derived(-6.0, Derived::Unit::Meter), +2.0 * Derived(-3.0, Derived::Unit::Meter)) ;
//         EXPECT_EQ(Derived(-6.0, Derived::Unit::Meter), -2.0 * Derived(+3.0, Derived::Unit::Meter)) ;

//         EXPECT_EQ(Derived(0.0, Derived::Unit::Meter), Derived(+1.0, Derived::Unit::Meter) * 0.0) ;
//         EXPECT_EQ(Derived(0.0, Derived::Unit::Meter), Derived(-1.0, Derived::Unit::Meter) * 0.0) ;
//         EXPECT_EQ(Derived(0.0, Derived::Unit::Meter), Derived(0.0, Derived::Unit::Meter) * 0.0) ;

//         EXPECT_EQ(Derived(0.0, Derived::Unit::Meter), 0.0 * Derived(+1.0, Derived::Unit::Meter)) ;
//         EXPECT_EQ(Derived(0.0, Derived::Unit::Meter), 0.0 * Derived(-1.0, Derived::Unit::Meter)) ;
//         EXPECT_EQ(Derived(0.0, Derived::Unit::Meter), 0.0 * Derived(0.0, Derived::Unit::Meter)) ;

//     }

//     {

//         EXPECT_EQ(Derived(6.0, Derived::Unit::Foot), Derived(3.0, Derived::Unit::Foot) * 2.0) ;
//         EXPECT_EQ(Derived(6.0, Derived::Unit::TerrestrialMile), Derived(3.0, Derived::Unit::TerrestrialMile) * 2.0) ;
//         EXPECT_EQ(Derived(6.0, Derived::Unit::NauticalMile), Derived(3.0, Derived::Unit::NauticalMile) * 2.0) ;
//         EXPECT_EQ(Derived(6.0, Derived::Unit::AstronomicalUnit), Derived(3.0, Derived::Unit::AstronomicalUnit) * 2.0)
//         ;

//         EXPECT_EQ(Derived(6.0, Derived::Unit::Foot), 2.0 * Derived(3.0, Derived::Unit::Foot)) ;
//         EXPECT_EQ(Derived(6.0, Derived::Unit::TerrestrialMile), 2.0 * Derived(3.0, Derived::Unit::TerrestrialMile)) ;
//         EXPECT_EQ(Derived(6.0, Derived::Unit::NauticalMile), 2.0 * Derived(3.0, Derived::Unit::NauticalMile)) ;
//         EXPECT_EQ(Derived(6.0, Derived::Unit::AstronomicalUnit), 2.0 * Derived(3.0, Derived::Unit::AstronomicalUnit))
//         ;

//     }

//     {

//         EXPECT_ANY_THROW(Derived(1.0, Derived::Unit::Meter) * Real::Undefined()) ;
//         EXPECT_ANY_THROW(Real::Undefined() * Derived(1.0, Derived::Unit::Meter)) ;

//     }

// }

// TEST (OpenSpaceToolkit_Physics_Unit_Derived, DivisionOperator)
// {

//     using ostk::core::type::Real ;

//     {

//         EXPECT_EQ(Derived(+1.0, Derived::Unit::Meter), Derived(+1.0, Derived::Unit::Meter) / +1.0) ;
//         EXPECT_EQ(Derived(-1.0, Derived::Unit::Meter), Derived(-1.0, Derived::Unit::Meter) / +1.0) ;
//         EXPECT_EQ(Derived(-1.0, Derived::Unit::Meter), Derived(+1.0, Derived::Unit::Meter) / -1.0) ;

//         EXPECT_EQ(Derived(+1.0, Derived::Unit::Meter), Derived(+2.0, Derived::Unit::Meter) / +2.0) ;
//         EXPECT_EQ(Derived(-1.0, Derived::Unit::Meter), Derived(-2.0, Derived::Unit::Meter) / +2.0) ;
//         EXPECT_EQ(Derived(-1.0, Derived::Unit::Meter), Derived(+2.0, Derived::Unit::Meter) / -2.0) ;

//         EXPECT_EQ(Derived(+2.0, Derived::Unit::Meter), Derived(+4.0, Derived::Unit::Meter) / +2.0) ;
//         EXPECT_EQ(Derived(-2.0, Derived::Unit::Meter), Derived(-4.0, Derived::Unit::Meter) / +2.0) ;
//         EXPECT_EQ(Derived(-2.0, Derived::Unit::Meter), Derived(+4.0, Derived::Unit::Meter) / -2.0) ;

//     }

//     {

//         EXPECT_EQ(Derived(0.5, Derived::Unit::Foot), Derived(1.0, Derived::Unit::Foot) / 2.0) ;
//         EXPECT_EQ(Derived(0.5, Derived::Unit::TerrestrialMile), Derived(1.0, Derived::Unit::TerrestrialMile) / 2.0) ;
//         EXPECT_EQ(Derived(0.5, Derived::Unit::NauticalMile), Derived(1.0, Derived::Unit::NauticalMile) / 2.0) ;
//         EXPECT_EQ(Derived(0.5, Derived::Unit::AstronomicalUnit), Derived(1.0, Derived::Unit::AstronomicalUnit) / 2.0)
//         ;

//     }

//     {

//         EXPECT_ANY_THROW(Derived(1.0, Derived::Unit::Meter) / Real::Undefined()) ;
//         EXPECT_ANY_THROW(Derived(1.0, Derived::Unit::Meter) / Real::Zero()) ;

//     }

// }

// TEST (OpenSpaceToolkit_Physics_Unit_Derived, AdditionAssignmentOperator)
// {

//     {

//         EXPECT_EQ(Derived(2.0, Derived::Unit::Meter), Derived(1.0, Derived::Unit::Meter) += Derived(1.0,
//         Derived::Unit::Meter)) ; EXPECT_EQ(Derived(0.0, Derived::Unit::Meter), Derived(-1.0, Derived::Unit::Meter) +=
//         Derived(+1.0, Derived::Unit::Meter)) ;

//     }

//     {

//         EXPECT_EQ(Derived(1.3048, Derived::Unit::Meter), Derived(1.0, Derived::Unit::Meter) += Derived(1.0,
//         Derived::Unit::Foot)) ; EXPECT_EQ(Derived(1610.344, Derived::Unit::Meter), Derived(1.0, Derived::Unit::Meter)
//         += Derived(1.0, Derived::Unit::TerrestrialMile)) ; EXPECT_EQ(Derived(1853.0, Derived::Unit::Meter),
//         Derived(1.0, Derived::Unit::Meter) += Derived(1.0, Derived::Unit::NauticalMile)) ;
//         EXPECT_EQ(Derived(149597870701.0, Derived::Unit::Meter), Derived(1.0, Derived::Unit::Meter) += Derived(1.0,
//         Derived::Unit::AstronomicalUnit)) ;

//     }

//     {

//         EXPECT_ANY_THROW(Derived(1.0, Derived::Unit::Meter) += Derived::Undefined()) ;
//         EXPECT_ANY_THROW(Derived::Undefined() += Derived(1.0, Derived::Unit::Meter)) ;
//         EXPECT_ANY_THROW(Derived::Undefined() += Derived::Undefined()) ;

//     }

// }

// TEST (OpenSpaceToolkit_Physics_Unit_Derived, SubtractionAssignmentOperator)
// {

//     {

//         EXPECT_EQ(Derived(0.0, Derived::Unit::Meter), Derived(1.0, Derived::Unit::Meter) -= Derived(1.0,
//         Derived::Unit::Meter)) ; EXPECT_EQ(Derived(-2.0, Derived::Unit::Meter), Derived(-1.0, Derived::Unit::Meter)
//         -= Derived(+1.0, Derived::Unit::Meter)) ;

//     }

//     {

//         EXPECT_EQ(Derived(1.0 - 0.3048, Derived::Unit::Meter), Derived(1.0, Derived::Unit::Meter) -= Derived(1.0,
//         Derived::Unit::Foot)) ; EXPECT_EQ(Derived(-1608.344, Derived::Unit::Meter), Derived(1.0,
//         Derived::Unit::Meter) -= Derived(1.0, Derived::Unit::TerrestrialMile)) ; EXPECT_EQ(Derived(-1851.0,
//         Derived::Unit::Meter), Derived(1.0, Derived::Unit::Meter) -= Derived(1.0, Derived::Unit::NauticalMile)) ;
//         EXPECT_EQ(Derived(-149597870699.0, Derived::Unit::Meter), Derived(1.0, Derived::Unit::Meter) -= Derived(1.0,
//         Derived::Unit::AstronomicalUnit)) ;

//     }

//     {

//         EXPECT_ANY_THROW(Derived(1.0, Derived::Unit::Meter) -= Derived::Undefined()) ;
//         EXPECT_ANY_THROW(Derived::Undefined() -= Derived(1.0, Derived::Unit::Meter)) ;
//         EXPECT_ANY_THROW(Derived::Undefined() -= Derived::Undefined()) ;

//     }

// }

// TEST (OpenSpaceToolkit_Physics_Unit_Derived, MultiplicationAssignmentOperator)
// {

//     using ostk::core::type::Real ;

//     {

//         EXPECT_EQ(Derived(+1.0, Derived::Unit::Meter), Derived(+1.0, Derived::Unit::Meter) *= +1.0) ;
//         EXPECT_EQ(Derived(-1.0, Derived::Unit::Meter), Derived(-1.0, Derived::Unit::Meter) *= +1.0) ;
//         EXPECT_EQ(Derived(-1.0, Derived::Unit::Meter), Derived(+1.0, Derived::Unit::Meter) *= -1.0) ;

//         EXPECT_EQ(Derived(+6.0, Derived::Unit::Meter), Derived(+2.0, Derived::Unit::Meter) *= +3.0) ;
//         EXPECT_EQ(Derived(-6.0, Derived::Unit::Meter), Derived(-2.0, Derived::Unit::Meter) *= +3.0) ;
//         EXPECT_EQ(Derived(-6.0, Derived::Unit::Meter), Derived(+2.0, Derived::Unit::Meter) *= -3.0) ;

//         EXPECT_EQ(Derived(0.0, Derived::Unit::Meter), Derived(+1.0, Derived::Unit::Meter) *= 0.0) ;
//         EXPECT_EQ(Derived(0.0, Derived::Unit::Meter), Derived(-1.0, Derived::Unit::Meter) *= 0.0) ;
//         EXPECT_EQ(Derived(0.0, Derived::Unit::Meter), Derived(0.0, Derived::Unit::Meter) *= 0.0) ;

//     }

//     {

//         EXPECT_EQ(Derived(6.0, Derived::Unit::Foot), Derived(3.0, Derived::Unit::Foot) *= 2.0) ;
//         EXPECT_EQ(Derived(6.0, Derived::Unit::TerrestrialMile), Derived(3.0, Derived::Unit::TerrestrialMile) *= 2.0)
//         ; EXPECT_EQ(Derived(6.0, Derived::Unit::NauticalMile), Derived(3.0, Derived::Unit::NauticalMile) *= 2.0) ;
//         EXPECT_EQ(Derived(6.0, Derived::Unit::AstronomicalUnit), Derived(3.0, Derived::Unit::AstronomicalUnit)
//         *= 2.0) ;

//     }

//     {

//         EXPECT_ANY_THROW(Derived(1.0, Derived::Unit::Meter) *= Real::Undefined()) ;

//     }

// }

// TEST (OpenSpaceToolkit_Physics_Unit_Derived, DivisionAssignmentOperator)
// {

//     using ostk::core::type::Real ;

//     {

//         EXPECT_EQ(Derived(+1.0, Derived::Unit::Meter), Derived(+1.0, Derived::Unit::Meter) /= +1.0) ;
//         EXPECT_EQ(Derived(-1.0, Derived::Unit::Meter), Derived(-1.0, Derived::Unit::Meter) /= +1.0) ;
//         EXPECT_EQ(Derived(-1.0, Derived::Unit::Meter), Derived(+1.0, Derived::Unit::Meter) /= -1.0) ;

//         EXPECT_EQ(Derived(+1.0, Derived::Unit::Meter), Derived(+2.0, Derived::Unit::Meter) /= +2.0) ;
//         EXPECT_EQ(Derived(-1.0, Derived::Unit::Meter), Derived(-2.0, Derived::Unit::Meter) /= +2.0) ;
//         EXPECT_EQ(Derived(-1.0, Derived::Unit::Meter), Derived(+2.0, Derived::Unit::Meter) /= -2.0) ;

//         EXPECT_EQ(Derived(+2.0, Derived::Unit::Meter), Derived(+4.0, Derived::Unit::Meter) /= +2.0) ;
//         EXPECT_EQ(Derived(-2.0, Derived::Unit::Meter), Derived(-4.0, Derived::Unit::Meter) /= +2.0) ;
//         EXPECT_EQ(Derived(-2.0, Derived::Unit::Meter), Derived(+4.0, Derived::Unit::Meter) /= -2.0) ;

//     }

//     {

//         EXPECT_EQ(Derived(0.5, Derived::Unit::Foot), Derived(1.0, Derived::Unit::Foot) /= 2.0) ;
//         EXPECT_EQ(Derived(0.5, Derived::Unit::TerrestrialMile), Derived(1.0, Derived::Unit::TerrestrialMile) /= 2.0)
//         ; EXPECT_EQ(Derived(0.5, Derived::Unit::NauticalMile), Derived(1.0, Derived::Unit::NauticalMile) /= 2.0) ;
//         EXPECT_EQ(Derived(0.5, Derived::Unit::AstronomicalUnit), Derived(1.0, Derived::Unit::AstronomicalUnit)
//         /= 2.0) ;

//     }

//     {

//         EXPECT_ANY_THROW(Derived(1.0, Derived::Unit::Meter) /= Real::Undefined()) ;
//         EXPECT_ANY_THROW(Derived(1.0, Derived::Unit::Meter) /= Real::Zero()) ;

//     }

// }

// TEST (OpenSpaceToolkit_Physics_Unit_Derived, StreamOperator)
// {

//     {

//         testing::internal::CaptureStdout() ;

//         EXPECT_NO_THROW(std::cout << Derived(0.5, Derived::Unit::Foot) << std::endl) ;

//         EXPECT_FALSE(testing::internal::GetCapturedStdout().empty()) ;

//     }

// }

// TEST (OpenSpaceToolkit_Physics_Unit_Derived, IsDefined)
// {

//     using ostk::core::type::Real ;

//     {

//         EXPECT_TRUE(Derived(0.0, Derived::Unit::Meter).isDefined()) ;

//         EXPECT_TRUE(Derived(1.0, Derived::Unit::Meter).isDefined()) ;
//         EXPECT_TRUE(Derived(1.0, Derived::Unit::Foot).isDefined()) ;
//         EXPECT_TRUE(Derived(1.0, Derived::Unit::TerrestrialMile).isDefined()) ;
//         EXPECT_TRUE(Derived(1.0, Derived::Unit::NauticalMile).isDefined()) ;
//         EXPECT_TRUE(Derived(1.0, Derived::Unit::AstronomicalUnit).isDefined()) ;

//     }

//     {

//         EXPECT_FALSE(Derived::Undefined().isDefined()) ;
//         EXPECT_FALSE(Derived(Real::Undefined(), Derived::Unit::Meter).isDefined()) ;
//         EXPECT_FALSE(Derived(1.0, Derived::Unit::Undefined).isDefined()) ;

//     }

// }

// TEST (OpenSpaceToolkit_Physics_Unit_Derived, GetUnit)
// {

//     {

//         EXPECT_EQ(Derived::Unit::Undefined, Derived(1.0, Derived::Unit::Undefined).getUnit()) ;
//         EXPECT_EQ(Derived::Unit::Meter, Derived(1.0, Derived::Unit::Meter).getUnit()) ;
//         EXPECT_EQ(Derived::Unit::Foot, Derived(1.0, Derived::Unit::Foot).getUnit()) ;
//         EXPECT_EQ(Derived::Unit::TerrestrialMile, Derived(1.0, Derived::Unit::TerrestrialMile).getUnit()) ;
//         EXPECT_EQ(Derived::Unit::NauticalMile, Derived(1.0, Derived::Unit::NauticalMile).getUnit()) ;
//         EXPECT_EQ(Derived::Unit::AstronomicalUnit, Derived(1.0, Derived::Unit::AstronomicalUnit).getUnit()) ;

//     }

// }

// TEST (OpenSpaceToolkit_Physics_Unit_Derived, In)
// {

//     {

//         EXPECT_EQ(1.0, Derived(1.0, Derived::Unit::Meter).in(Derived::Unit::Meter)) ;
//         EXPECT_EQ(1.0, Derived(1.0, Derived::Unit::Foot).in(Derived::Unit::Foot)) ;
//         EXPECT_EQ(1.0, Derived(1.0, Derived::Unit::TerrestrialMile).in(Derived::Unit::TerrestrialMile)) ;
//         EXPECT_EQ(1.0, Derived(1.0, Derived::Unit::NauticalMile).in(Derived::Unit::NauticalMile)) ;
//         EXPECT_EQ(1.0, Derived(1.0, Derived::Unit::AstronomicalUnit).in(Derived::Unit::AstronomicalUnit)) ;

//     }

//     {

//         EXPECT_FALSE(Derived::Undefined().in(Derived::Unit::Meter).isDefined()) ;

//     }

// }

// TEST (OpenSpaceToolkit_Physics_Unit_Derived, InMeters)
// {

//     {

//         EXPECT_EQ(123.456, Derived(123.456, Derived::Unit::Meter).inMeters()) ;

//     }

//     {

//         EXPECT_FALSE(Derived::Undefined().inMeters().isDefined()) ;

//     }

// }

// TEST (OpenSpaceToolkit_Physics_Unit_Derived, InKilometers)
// {

//     {

//         EXPECT_EQ(123.456, Derived(123456.0, Derived::Unit::Meter).inKilometers()) ;

//     }

//     {

//         EXPECT_FALSE(Derived::Undefined().inKilometers().isDefined()) ;

//     }

// }

// TEST (OpenSpaceToolkit_Physics_Unit_Derived, ToString)
// {

//     {

//         EXPECT_EQ("1.0 [m]", Derived(1.0, Derived::Unit::Meter).toString()) ;
//         EXPECT_EQ("1.0 [ft]", Derived(1.0, Derived::Unit::Foot).toString()) ;
//         EXPECT_EQ("1.0 [mi]", Derived(1.0, Derived::Unit::TerrestrialMile).toString()) ;
//         EXPECT_EQ("1.0 [nmi]", Derived(1.0, Derived::Unit::NauticalMile).toString()) ;
//         EXPECT_EQ("1.0 [AU]", Derived(1.0, Derived::Unit::AstronomicalUnit).toString()) ;

//         EXPECT_EQ("-1.0 [m]", Derived(-1.0, Derived::Unit::Meter).toString()) ;
//         EXPECT_EQ("-1.0 [ft]", Derived(-1.0, Derived::Unit::Foot).toString()) ;
//         EXPECT_EQ("-1.0 [mi]", Derived(-1.0, Derived::Unit::TerrestrialMile).toString()) ;
//         EXPECT_EQ("-1.0 [nmi]", Derived(-1.0, Derived::Unit::NauticalMile).toString()) ;
//         EXPECT_EQ("-1.0 [AU]", Derived(-1.0, Derived::Unit::AstronomicalUnit).toString()) ;

//         EXPECT_EQ("123.456 [m]", Derived(123.456, Derived::Unit::Meter).toString()) ;
//         EXPECT_EQ("123.456 [ft]", Derived(123.456, Derived::Unit::Foot).toString()) ;
//         EXPECT_EQ("123.456 [mi]", Derived(123.456, Derived::Unit::TerrestrialMile).toString()) ;
//         EXPECT_EQ("123.456 [nmi]", Derived(123.456, Derived::Unit::NauticalMile).toString()) ;
//         EXPECT_EQ("123.456 [AU]", Derived(123.456, Derived::Unit::AstronomicalUnit).toString()) ;

//     }

//     {

//         EXPECT_ANY_THROW(Derived::Undefined().toString()) ;

//     }

// }

// TEST (OpenSpaceToolkit_Physics_Unit_Derived, Undefined)
// {

//     {

//         EXPECT_NO_THROW(Derived::Undefined()) ;
//         EXPECT_FALSE(Derived::Undefined().isDefined()) ;

//         EXPECT_NO_THROW(Derived::Undefined().in(Derived::Unit::Meter)) ;

//     }

// }

// TEST (OpenSpaceToolkit_Physics_Unit_Derived, Meters)
// {

//     {

//         EXPECT_NO_THROW(Derived::Meters(123.456)) ;
//         EXPECT_TRUE(Derived::Meters(123.456).isDefined()) ;

//         EXPECT_EQ(123.456, Derived::Meters(123.456).in(Derived::Unit::Meter)) ;

//     }

// }

// TEST (OpenSpaceToolkit_Physics_Unit_Derived, Kilometers)
// {

//     {

//         EXPECT_NO_THROW(Derived::Kilometers(123.456)) ;
//         EXPECT_TRUE(Derived::Kilometers(123.456).isDefined()) ;

//         EXPECT_EQ(123456.0, Derived::Kilometers(123.456).in(Derived::Unit::Meter)) ;

//     }

// }

// // TEST (OpenSpaceToolkit_Physics_Unit_Derived, Parse)
// // {

//

// //     {

// //         FAIL() ;

// //     }

// // }

// TEST (OpenSpaceToolkit_Physics_Unit_Derived, StringFromUnit)
// {

//     {

//         EXPECT_EQ("Undefined", Derived::StringFromUnit(Derived::Unit::Undefined)) ;
//         EXPECT_EQ("Meter", Derived::StringFromUnit(Derived::Unit::Meter)) ;
//         EXPECT_EQ("Foot", Derived::StringFromUnit(Derived::Unit::Foot)) ;
//         EXPECT_EQ("Terrestrial Mile", Derived::StringFromUnit(Derived::Unit::TerrestrialMile)) ;
//         EXPECT_EQ("Nautical Mile", Derived::StringFromUnit(Derived::Unit::NauticalMile)) ;
//         EXPECT_EQ("Astronomical Unit", Derived::StringFromUnit(Derived::Unit::AstronomicalUnit)) ;

//     }

// }

TEST(OpenSpaceToolkit_Physics_Unit_Derived_Unit, SquareMeter)
{
    {
        const Derived::Unit derivedUnit = Derived::Unit::SquareMeter();

        EXPECT_TRUE(derivedUnit.isDefined());

        const Derived::Unit expectedDerivedUnit = {
            Length::Unit::Meter,
            {2},
            Mass::Unit::Undefined,
            {0},
            Time::Unit::Undefined,
            {0},
            ElectricCurrent::Unit::Undefined,
            {0},
            Angle::Unit::Undefined,
            {0}
        };

        EXPECT_EQ(expectedDerivedUnit, derivedUnit);
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Derived_Unit, CubicMeter)
{
    {
        const Derived::Unit derivedUnit = Derived::Unit::CubicMeter();

        EXPECT_TRUE(derivedUnit.isDefined());

        const Derived::Unit expectedDerivedUnit = {
            Length::Unit::Meter,
            {3},
            Mass::Unit::Undefined,
            {0},
            Time::Unit::Undefined,
            {0},
            ElectricCurrent::Unit::Undefined,
            {0},
            Angle::Unit::Undefined,
            {0}
        };

        EXPECT_EQ(expectedDerivedUnit, derivedUnit);
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Derived_Unit, Hertz)
{
    {
        const Derived::Unit derivedUnit = Derived::Unit::Hertz();

        EXPECT_TRUE(derivedUnit.isDefined());

        const Derived::Unit expectedDerivedUnit = {
            Length::Unit::Undefined,
            {0},
            Mass::Unit::Undefined,
            {0},
            Time::Unit::Second,
            {-1},
            ElectricCurrent::Unit::Undefined,
            {0},
            Angle::Unit::Undefined,
            {0}
        };

        EXPECT_EQ(expectedDerivedUnit, derivedUnit);
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Derived_Unit, Watt)
{
    {
        const Derived::Unit derivedUnit = Derived::Unit::Watt();

        EXPECT_TRUE(derivedUnit.isDefined());

        const Derived::Unit expectedDerivedUnit = {
            Length::Unit::Meter,
            {2},
            Mass::Unit::Kilogram,
            {1},
            Time::Unit::Second,
            {-3},
            ElectricCurrent::Unit::Undefined,
            {0},
            Angle::Unit::Undefined,
            {0}
        };

        EXPECT_EQ(expectedDerivedUnit, derivedUnit);
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Derived_Unit, Tesla)
{
    {
        const Derived::Unit derivedUnit = Derived::Unit::Tesla();

        EXPECT_TRUE(derivedUnit.isDefined());

        const Derived::Unit expectedDerivedUnit = {
            Length::Unit::Undefined,
            {0},
            Mass::Unit::Kilogram,
            {1},
            Time::Unit::Second,
            {-2},
            ElectricCurrent::Unit::Ampere,
            {-1},
            Angle::Unit::Undefined,
            {0}
        };

        EXPECT_EQ(expectedDerivedUnit, derivedUnit);
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Derived_Unit, Newton)
{
    {
        const Derived::Unit derivedUnit = Derived::Unit::Newton();

        EXPECT_TRUE(derivedUnit.isDefined());

        const Derived::Unit expectedDerivedUnit = {
            Length::Unit::Meter,
            {1},
            Mass::Unit::Kilogram,
            {1},
            Time::Unit::Second,
            {-2},
            ElectricCurrent::Unit::Undefined,
            {0},
            Angle::Unit::Undefined,
            {0}
        };

        EXPECT_EQ(expectedDerivedUnit, derivedUnit);
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Derived_Unit, KilogramPerSecond)
{
    {
        const Derived::Unit derivedUnit = Derived::Unit::KilogramPerSecond();

        EXPECT_TRUE(derivedUnit.isDefined());

        const Derived::Unit expectedDerivedUnit = {
            Length::Unit::Undefined,
            {0},
            Mass::Unit::Kilogram,
            {1},
            Time::Unit::Second,
            {-1},
            ElectricCurrent::Unit::Undefined,
            {0},
            Angle::Unit::Undefined,
            {0}
        };

        EXPECT_EQ(expectedDerivedUnit, derivedUnit);
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Derived_Unit, MeterPerSecond)
{
    {
        const Derived::Unit derivedUnit = Derived::Unit::MeterPerSecond();

        EXPECT_TRUE(derivedUnit.isDefined());

        const Derived::Unit expectedDerivedUnit = {
            Length::Unit::Meter,
            {1},
            Mass::Unit::Undefined,
            {0},
            Time::Unit::Second,
            {-1},
            ElectricCurrent::Unit::Undefined,
            {0},
            Angle::Unit::Undefined,
            {0}
        };

        EXPECT_EQ(expectedDerivedUnit, derivedUnit);
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Derived_Unit, MeterPerSecondSquared)
{
    {
        const Derived::Unit derivedUnit = Derived::Unit::MeterPerSecondSquared();

        EXPECT_TRUE(derivedUnit.isDefined());

        const Derived::Unit expectedDerivedUnit = {
            Length::Unit::Meter,
            {1},
            Mass::Unit::Undefined,
            {0},
            Time::Unit::Second,
            {-2},
            ElectricCurrent::Unit::Undefined,
            {0},
            Angle::Unit::Undefined,
            {0}
        };

        EXPECT_EQ(expectedDerivedUnit, derivedUnit);
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Derived_Unit, MeterCubedPerSecondSquared)
{
    {
        const Derived::Unit derivedUnit = Derived::Unit::MeterCubedPerSecondSquared();

        EXPECT_TRUE(derivedUnit.isDefined());

        const Derived::Unit expectedDerivedUnit = {
            Length::Unit::Meter,
            {3},
            Mass::Unit::Undefined,
            {0},
            Time::Unit::Second,
            {-2},
            ElectricCurrent::Unit::Undefined,
            {0},
            Angle::Unit::Undefined,
            {0}
        };

        EXPECT_EQ(expectedDerivedUnit, derivedUnit);
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Derived_Unit, RadianPerSecond)
{
    {
        const Derived::Unit derivedUnit = Derived::Unit::RadianPerSecond();

        EXPECT_TRUE(derivedUnit.isDefined());

        const Derived::Unit expectedDerivedUnit = {
            Length::Unit::Undefined,
            {0},
            Mass::Unit::Undefined,
            {0},
            Time::Unit::Second,
            {-1},
            ElectricCurrent::Unit::Undefined,
            {0},
            Angle::Unit::Radian,
            {1}
        };

        EXPECT_EQ(expectedDerivedUnit, derivedUnit);
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Derived_Unit, RevolutionPerDay)
{
    {
        const Derived::Unit derivedUnit = Derived::Unit::RevolutionPerDay();

        EXPECT_TRUE(derivedUnit.isDefined());

        const Derived::Unit expectedDerivedUnit = {
            Length::Unit::Undefined,
            {0},
            Mass::Unit::Undefined,
            {0},
            Time::Unit::Day,
            {-1},
            ElectricCurrent::Unit::Undefined,
            {0},
            Angle::Unit::Revolution,
            {1}
        };

        EXPECT_EQ(expectedDerivedUnit, derivedUnit);
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Derived_Unit, Velocity)
{
    {
        const Derived::Unit derivedUnit = Derived::Unit::Velocity(Length::Unit::Meter, Time::Unit::Second);

        EXPECT_TRUE(derivedUnit.isDefined());

        const Derived::Unit expectedDerivedUnit = {
            Length::Unit::Meter,
            {1},
            Mass::Unit::Undefined,
            {0},
            Time::Unit::Second,
            {-1},
            ElectricCurrent::Unit::Undefined,
            {0},
            Angle::Unit::Undefined,
            {0}
        };

        EXPECT_EQ(expectedDerivedUnit, derivedUnit);
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Derived_Unit, Acceleration)
{
    {
        const Derived::Unit derivedUnit = Derived::Unit::Acceleration(Length::Unit::Meter, Time::Unit::Second);

        EXPECT_TRUE(derivedUnit.isDefined());

        const Derived::Unit expectedDerivedUnit = {
            Length::Unit::Meter,
            {1},
            Mass::Unit::Undefined,
            {0},
            Time::Unit::Second,
            {-2},
            ElectricCurrent::Unit::Undefined,
            {0},
            Angle::Unit::Undefined,
            {0}
        };

        EXPECT_EQ(expectedDerivedUnit, derivedUnit);
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Derived_Unit, GravitationalParameter)
{
    {
        const Derived::Unit derivedUnit =
            Derived::Unit::GravitationalParameter(Length::Unit::Meter, Time::Unit::Second);

        EXPECT_TRUE(derivedUnit.isDefined());

        const Derived::Unit expectedDerivedUnit = {
            Length::Unit::Meter,
            {3},
            Mass::Unit::Undefined,
            {0},
            Time::Unit::Second,
            {-2},
            ElectricCurrent::Unit::Undefined,
            {0},
            Angle::Unit::Undefined,
            {0}
        };

        EXPECT_EQ(expectedDerivedUnit, derivedUnit);
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Derived_Unit, AngularVelocity)
{
    {
        const Derived::Unit derivedUnit = Derived::Unit::AngularVelocity(Angle::Unit::Radian, Time::Unit::Second);

        EXPECT_TRUE(derivedUnit.isDefined());

        const Derived::Unit expectedDerivedUnit = {
            Length::Unit::Undefined,
            {0},
            Mass::Unit::Undefined,
            {0},
            Time::Unit::Second,
            {-1},
            ElectricCurrent::Unit::Undefined,
            {0},
            Angle::Unit::Radian,
            {1}
        };

        EXPECT_EQ(expectedDerivedUnit, derivedUnit);
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Derived_Unit, Force)
{
    {
        const Derived::Unit derivedUnit =
            Derived::Unit::Force(Mass::Unit::Kilogram, Length::Unit::Meter, Time::Unit::Second);

        EXPECT_TRUE(derivedUnit.isDefined());

        const Derived::Unit expectedDerivedUnit = {
            Length::Unit::Meter,
            {1},
            Mass::Unit::Kilogram,
            {1},
            Time::Unit::Second,
            {-2},
            ElectricCurrent::Unit::Undefined,
            {0},
            Angle::Unit::Undefined,
            {0},
        };

        EXPECT_EQ(expectedDerivedUnit, derivedUnit);
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Derived_Unit, MassFlowRate)
{
    {
        const Derived::Unit derivedUnit = Derived::Unit::MassFlowRate(Mass::Unit::Kilogram, Time::Unit::Second);

        EXPECT_TRUE(derivedUnit.isDefined());

        const Derived::Unit expectedDerivedUnit = {
            Length::Unit::Undefined,
            {0},
            Mass::Unit::Kilogram,
            {1},
            Time::Unit::Second,
            {-1},
            ElectricCurrent::Unit::Undefined,
            {0},
            Angle::Unit::Undefined,
            {0},
        };

        EXPECT_EQ(expectedDerivedUnit, derivedUnit);
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Derived_Unit, MassDensity)
{
    {
        const Derived::Unit derivedUnit = Derived::Unit::MassDensity(Mass::Unit::Kilogram, Length::Unit::Meter);

        EXPECT_TRUE(derivedUnit.isDefined());

        const Derived::Unit expectedDerivedUnit = {
            Length::Unit::Meter,
            {-3},
            Mass::Unit::Kilogram,
            {1},
            Time::Unit::Undefined,
            {0},
            ElectricCurrent::Unit::Undefined,
            {0},
            Angle::Unit::Undefined,
            {0},
        };

        EXPECT_EQ(expectedDerivedUnit, derivedUnit);
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Derived_Unit, Undefined)
{
    {
        const Derived::Unit derivedUnit = Derived::Unit::Undefined();

        EXPECT_FALSE(derivedUnit.isDefined());

        const Derived::Unit expectedDerivedUnit = {
            Length::Unit::Undefined,
            {0},
            Mass::Unit::Undefined,
            {0},
            Time::Unit::Undefined,
            {0},
            ElectricCurrent::Unit::Undefined,
            {0},
            Angle::Unit::Undefined,
            {0}
        };

        // Undefined objects are returned as false when == is used
        EXPECT_FALSE(expectedDerivedUnit == derivedUnit);
    }
}
