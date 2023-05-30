/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Types/Real.hpp>

#include <OpenSpaceToolkit/Physics/Units/Derived.hpp>

#include <Global.test.hpp>

TEST(OpenSpaceToolkit_Physics_Units_Derived, Constructor)
{
    using ostk::core::types::Real;
    using ostk::physics::units::Length;
    using ostk::physics::units::Mass;
    using ostk::physics::units::Time;
    using ostk::physics::units::ElectricCurrent;
    using ostk::physics::units::Angle;
    using ostk::physics::units::Derived;

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
            Derived::Order::One()};

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
            {0}};

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
            {0}};

        EXPECT_NO_THROW(Derived(value, unit));
    }

    {
        const Real value = Real::Undefined();
        const Derived::Unit unit = Derived::Unit::Undefined();

        EXPECT_NO_THROW(Derived(value, unit));
    }
}

TEST(OpenSpaceToolkit_Physics_Units_Derived, EqualToOperator)
{
    using ostk::core::types::Real;
    using ostk::physics::units::Length;
    using ostk::physics::units::Mass;
    using ostk::physics::units::Time;
    using ostk::physics::units::ElectricCurrent;
    using ostk::physics::units::Angle;
    using ostk::physics::units::Derived;

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
            Derived::Order::One()};

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
            Derived::Order::One()};

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
            Derived::Order::One()};

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
            Derived::Order::One()};

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
            Derived::Order::One()};

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
            Derived::Order::Zero()};

        EXPECT_ANY_THROW(Derived(1.0, firstUnit) == Derived(1.0, secondUnit));
    }
}

// TEST (OpenSpaceToolkit_Physics_Units_Derived, NotEqualToOperator)
// {

//     using ostk::physics::units::Derived ;

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

// TEST (OpenSpaceToolkit_Physics_Units_Derived, LowerThanOperator)
// {

//     using ostk::physics::units::Derived ;

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

// TEST (OpenSpaceToolkit_Physics_Units_Derived, LowerThanOrEqualToOperator)
// {

//     using ostk::physics::units::Derived ;

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

// TEST (OpenSpaceToolkit_Physics_Units_Derived, GreaterThanOperator)
// {

//     using ostk::physics::units::Derived ;

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

// TEST (OpenSpaceToolkit_Physics_Units_Derived, GreaterThanOrEqualToOperator)
// {

//     using ostk::physics::units::Derived ;

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

// TEST (OpenSpaceToolkit_Physics_Units_Derived, AdditionOperator)
// {

//     using ostk::physics::units::Derived ;

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

// TEST (OpenSpaceToolkit_Physics_Units_Derived, SubtractionOperator)
// {

//     using ostk::physics::units::Derived ;

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

// TEST (OpenSpaceToolkit_Physics_Units_Derived, MultiplicationOperator)
// {

//     using ostk::core::types::Real ;
//     using ostk::physics::units::Derived ;

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

// TEST (OpenSpaceToolkit_Physics_Units_Derived, DivisionOperator)
// {

//     using ostk::core::types::Real ;
//     using ostk::physics::units::Derived ;

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

// TEST (OpenSpaceToolkit_Physics_Units_Derived, AdditionAssignmentOperator)
// {

//     using ostk::physics::units::Derived ;

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

// TEST (OpenSpaceToolkit_Physics_Units_Derived, SubtractionAssignmentOperator)
// {

//     using ostk::physics::units::Derived ;

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

// TEST (OpenSpaceToolkit_Physics_Units_Derived, MultiplicationAssignmentOperator)
// {

//     using ostk::core::types::Real ;
//     using ostk::physics::units::Derived ;

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

// TEST (OpenSpaceToolkit_Physics_Units_Derived, DivisionAssignmentOperator)
// {

//     using ostk::core::types::Real ;
//     using ostk::physics::units::Derived ;

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

// TEST (OpenSpaceToolkit_Physics_Units_Derived, StreamOperator)
// {

//     using ostk::physics::units::Derived ;

//     {

//         testing::internal::CaptureStdout() ;

//         EXPECT_NO_THROW(std::cout << Derived(0.5, Derived::Unit::Foot) << std::endl) ;

//         EXPECT_FALSE(testing::internal::GetCapturedStdout().empty()) ;

//     }

// }

// TEST (OpenSpaceToolkit_Physics_Units_Derived, IsDefined)
// {

//     using ostk::core::types::Real ;
//     using ostk::physics::units::Derived ;

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

// TEST (OpenSpaceToolkit_Physics_Units_Derived, GetUnit)
// {

//     using ostk::physics::units::Derived ;

//     {

//         EXPECT_EQ(Derived::Unit::Undefined, Derived(1.0, Derived::Unit::Undefined).getUnit()) ;
//         EXPECT_EQ(Derived::Unit::Meter, Derived(1.0, Derived::Unit::Meter).getUnit()) ;
//         EXPECT_EQ(Derived::Unit::Foot, Derived(1.0, Derived::Unit::Foot).getUnit()) ;
//         EXPECT_EQ(Derived::Unit::TerrestrialMile, Derived(1.0, Derived::Unit::TerrestrialMile).getUnit()) ;
//         EXPECT_EQ(Derived::Unit::NauticalMile, Derived(1.0, Derived::Unit::NauticalMile).getUnit()) ;
//         EXPECT_EQ(Derived::Unit::AstronomicalUnit, Derived(1.0, Derived::Unit::AstronomicalUnit).getUnit()) ;

//     }

// }

// TEST (OpenSpaceToolkit_Physics_Units_Derived, In)
// {

//     using ostk::physics::units::Derived ;

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

// TEST (OpenSpaceToolkit_Physics_Units_Derived, InMeters)
// {

//     using ostk::physics::units::Derived ;

//     {

//         EXPECT_EQ(123.456, Derived(123.456, Derived::Unit::Meter).inMeters()) ;

//     }

//     {

//         EXPECT_FALSE(Derived::Undefined().inMeters().isDefined()) ;

//     }

// }

// TEST (OpenSpaceToolkit_Physics_Units_Derived, InKilometers)
// {

//     using ostk::physics::units::Derived ;

//     {

//         EXPECT_EQ(123.456, Derived(123456.0, Derived::Unit::Meter).inKilometers()) ;

//     }

//     {

//         EXPECT_FALSE(Derived::Undefined().inKilometers().isDefined()) ;

//     }

// }

// TEST (OpenSpaceToolkit_Physics_Units_Derived, ToString)
// {

//     using ostk::physics::units::Derived ;

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

// TEST (OpenSpaceToolkit_Physics_Units_Derived, Undefined)
// {

//     using ostk::physics::units::Derived ;

//     {

//         EXPECT_NO_THROW(Derived::Undefined()) ;
//         EXPECT_FALSE(Derived::Undefined().isDefined()) ;

//         EXPECT_NO_THROW(Derived::Undefined().in(Derived::Unit::Meter)) ;

//     }

// }

// TEST (OpenSpaceToolkit_Physics_Units_Derived, Meters)
// {

//     using ostk::physics::units::Derived ;

//     {

//         EXPECT_NO_THROW(Derived::Meters(123.456)) ;
//         EXPECT_TRUE(Derived::Meters(123.456).isDefined()) ;

//         EXPECT_EQ(123.456, Derived::Meters(123.456).in(Derived::Unit::Meter)) ;

//     }

// }

// TEST (OpenSpaceToolkit_Physics_Units_Derived, Kilometers)
// {

//     using ostk::physics::units::Derived ;

//     {

//         EXPECT_NO_THROW(Derived::Kilometers(123.456)) ;
//         EXPECT_TRUE(Derived::Kilometers(123.456).isDefined()) ;

//         EXPECT_EQ(123456.0, Derived::Kilometers(123.456).in(Derived::Unit::Meter)) ;

//     }

// }

// // TEST (OpenSpaceToolkit_Physics_Units_Derived, Parse)
// // {

// //     using ostk::physics::units::Derived ;

// //     {

// //         FAIL() ;

// //     }

// // }

// TEST (OpenSpaceToolkit_Physics_Units_Derived, StringFromUnit)
// {

//     using ostk::physics::units::Derived ;

//     {

//         EXPECT_EQ("Undefined", Derived::StringFromUnit(Derived::Unit::Undefined)) ;
//         EXPECT_EQ("Meter", Derived::StringFromUnit(Derived::Unit::Meter)) ;
//         EXPECT_EQ("Foot", Derived::StringFromUnit(Derived::Unit::Foot)) ;
//         EXPECT_EQ("Terrestrial Mile", Derived::StringFromUnit(Derived::Unit::TerrestrialMile)) ;
//         EXPECT_EQ("Nautical Mile", Derived::StringFromUnit(Derived::Unit::NauticalMile)) ;
//         EXPECT_EQ("Astronomical Unit", Derived::StringFromUnit(Derived::Unit::AstronomicalUnit)) ;

//     }

// }

TEST(OpenSpaceToolkit_Physics_Units_Derived_Unit, MassDensity)
{
    using ostk::physics::units::Length;
    using ostk::physics::units::Mass;
    using ostk::physics::units::Derived;

    {
        const Derived::Unit massDensity = Derived::Unit::MassDensity(Mass::Unit::Kilogram, Length::Unit::Meter);

        EXPECT_TRUE(massDensity.isDefined());
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
