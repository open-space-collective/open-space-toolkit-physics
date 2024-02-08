/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Type/Real.hpp>

#include <OpenSpaceToolkit/Physics/Unit/Mass.hpp>

#include <Global.test.hpp>

TEST(OpenSpaceToolkit_Physics_Unit_Mass, Constructor)
{
    using ostk::core::type::Real;
    using ostk::physics::unit::Mass;

    {
        const Real value = 123.456;
        const Mass::Unit unit = Mass::Unit::Kilogram;

        EXPECT_NO_THROW(Mass(value, unit));
    }

    {
        const Real value = Real::Undefined();
        const Mass::Unit unit = Mass::Unit::Undefined;

        EXPECT_NO_THROW(Mass(value, unit));
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Mass, IsDefined)
{
    using ostk::core::type::Real;
    using ostk::physics::unit::Mass;

    {
        EXPECT_TRUE(Mass(0.0, Mass::Unit::Kilogram).isDefined());

        EXPECT_TRUE(Mass(1.0, Mass::Unit::Kilogram).isDefined());
        EXPECT_TRUE(Mass(1.0, Mass::Unit::Tonne).isDefined());
        EXPECT_TRUE(Mass(1.0, Mass::Unit::Pound).isDefined());
    }

    {
        EXPECT_FALSE(Mass::Undefined().isDefined());
        EXPECT_FALSE(Mass(Real::Undefined(), Mass::Unit::Kilogram).isDefined());
        EXPECT_FALSE(Mass(1.0, Mass::Unit::Undefined).isDefined());
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Mass, GetUnit)
{
    using ostk::physics::unit::Mass;

    {
        EXPECT_EQ(Mass::Unit::Undefined, Mass(1.0, Mass::Unit::Undefined).getUnit());
        EXPECT_EQ(Mass::Unit::Kilogram, Mass(1.0, Mass::Unit::Kilogram).getUnit());
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Mass, In)
{
    using ostk::physics::unit::Mass;

    {
        EXPECT_EQ(1.0, Mass(1.0, Mass::Unit::Kilogram).in(Mass::Unit::Kilogram));
        EXPECT_EQ(1 / 2.20462, Mass(1.0, Mass::Unit::Kilogram).in(Mass::Unit::Pound));
        EXPECT_EQ(1 / 1016.047, Mass(1.0, Mass::Unit::Kilogram).in(Mass::Unit::Tonne));
    }

    {
        EXPECT_FALSE(Mass::Undefined().in(Mass::Unit::Kilogram).isDefined());
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Mass, InKilograms)
{
    using ostk::physics::unit::Mass;

    {
        EXPECT_EQ(123.456, Mass(123.456, Mass::Unit::Kilogram).inKilograms());
    }

    {
        EXPECT_FALSE(Mass::Undefined().inKilograms().isDefined());
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Mass, ToString)
{
    using ostk::physics::unit::Mass;

    {
        EXPECT_EQ("1.0 [kg]", Mass(1.0, Mass::Unit::Kilogram).toString());
        EXPECT_EQ("1.0 [t]", Mass(1.0, Mass::Unit::Tonne).toString());
        EXPECT_EQ("1.0 [lb]", Mass(1.0, Mass::Unit::Pound).toString());

        EXPECT_EQ("-1.0 [kg]", Mass(-1.0, Mass::Unit::Kilogram).toString());
        EXPECT_EQ("-1.0 [t]", Mass(-1.0, Mass::Unit::Tonne).toString());
        EXPECT_EQ("-1.0 [lb]", Mass(-1.0, Mass::Unit::Pound).toString());

        EXPECT_EQ("123.456 [kg]", Mass(123.456, Mass::Unit::Kilogram).toString());
        EXPECT_EQ("123.456 [t]", Mass(123.456, Mass::Unit::Tonne).toString());
        EXPECT_EQ("123.456 [lb]", Mass(123.456, Mass::Unit::Pound).toString());
    }

    {
        EXPECT_EQ("1.000 [kg]", Mass(1.0, Mass::Unit::Kilogram).toString(3));
        EXPECT_EQ("1.000 [t]", Mass(1.0, Mass::Unit::Tonne).toString(3));
        EXPECT_EQ("1.000 [lb]", Mass(1.0, Mass::Unit::Pound).toString(3));

        EXPECT_EQ("-1.000 [kg]", Mass(-1.0, Mass::Unit::Kilogram).toString(3));
        EXPECT_EQ("-1.000 [t]", Mass(-1.0, Mass::Unit::Tonne).toString(3));
        EXPECT_EQ("-1.000 [lb]", Mass(-1.0, Mass::Unit::Pound).toString(3));

        EXPECT_EQ("123.456 [kg]", Mass(123.456123, Mass::Unit::Kilogram).toString(3));
        EXPECT_EQ("123.456 [t]", Mass(123.456123, Mass::Unit::Tonne).toString(3));
        EXPECT_EQ("123.456 [lb]", Mass(123.456123, Mass::Unit::Pound).toString(3));
    }

    {
        EXPECT_ANY_THROW(Mass::Undefined().toString());
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Mass, Undefined)
{
    using ostk::physics::unit::Mass;

    {
        EXPECT_NO_THROW(Mass::Undefined());
        EXPECT_FALSE(Mass::Undefined().isDefined());

        // EXPECT_NO_THROW(Mass::Undefined().in(Mass::Unit::Kilogram)) ;
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Mass, Kilograms)
{
    using ostk::physics::unit::Mass;

    {
        EXPECT_NO_THROW(Mass::Kilograms(123.456));
        EXPECT_TRUE(Mass::Kilograms(123.456).isDefined());

        EXPECT_EQ(123.456, Mass::Kilograms(123.456).in(Mass::Unit::Kilogram));
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Mass, StringFromUnit)
{
    using ostk::physics::unit::Mass;

    {
        EXPECT_EQ("Undefined", Mass::StringFromUnit(Mass::Unit::Undefined));
        EXPECT_EQ("Kilogram", Mass::StringFromUnit(Mass::Unit::Kilogram));
        EXPECT_EQ("Tonne", Mass::StringFromUnit(Mass::Unit::Tonne));
        EXPECT_EQ("Pound", Mass::StringFromUnit(Mass::Unit::Pound));
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Mass, SymbolFromUnit)
{
    using ostk::physics::unit::Mass;

    {
        EXPECT_EQ("kg", Mass::SymbolFromUnit(Mass::Unit::Kilogram));
        EXPECT_EQ("t", Mass::SymbolFromUnit(Mass::Unit::Tonne));
        EXPECT_EQ("lb", Mass::SymbolFromUnit(Mass::Unit::Pound));
    }
}
