/// Apache License 2.0

#include <limits>

#include <OpenSpaceToolkit/Physics/Unit/Mass.hpp>

#include <Global.test.hpp>

TEST(OpenSpaceToolkit_Physics_Unit_Mass, Constructor)
{
    using ostk::physics::unit::Mass;

    {
        const double value = 123.456;
        const Mass::Unit unit = Mass::Unit::Kilogram;

        EXPECT_NO_THROW(Mass(value, unit));
    }

    {
        const double value = std::numeric_limits<double>::quiet_NaN();
        const Mass::Unit unit = Mass::Unit::Kilogram;

        EXPECT_NO_THROW(Mass(value, unit));
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Mass, GetUnit)
{
    using ostk::physics::unit::Mass;

    {
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
}

TEST(OpenSpaceToolkit_Physics_Unit_Mass, InKilograms)
{
    using ostk::physics::unit::Mass;

    {
        EXPECT_EQ(123.456, Mass(123.456, Mass::Unit::Kilogram).inKilograms());
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
}

TEST(OpenSpaceToolkit_Physics_Unit_Mass, Kilograms)
{
    using ostk::physics::unit::Mass;

    {
        EXPECT_NO_THROW(Mass::Kilograms(123.456));

        EXPECT_EQ(123.456, Mass::Kilograms(123.456).in(Mass::Unit::Kilogram));
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Mass, StringFromUnit)
{
    using ostk::physics::unit::Mass;

    {
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
