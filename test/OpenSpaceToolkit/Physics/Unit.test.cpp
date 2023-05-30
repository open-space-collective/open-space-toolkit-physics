/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Unit.hpp>

#include <Global.test.hpp>

TEST(OpenSpaceToolkit_Physics_Unit, EqualToOperator)
{
    using ostk::physics::Unit;
    using ostk::physics::units::Length;

    {
        const Unit unit = Unit::Length(Length::Unit::Meter);

        EXPECT_TRUE(unit == unit);
    }

    {
        const Unit firstUnit = Unit::Length(Length::Unit::Meter);
        const Unit secondUnit = Unit::Length(Length::Unit::Meter);

        EXPECT_TRUE(firstUnit == secondUnit);
    }

    {
        const Unit firstUnit = Unit::Length(Length::Unit::Meter);
        const Unit secondUnit = Unit::None();

        EXPECT_FALSE(firstUnit == secondUnit);
    }

    {
        const Unit unit = Unit::Length(Length::Unit::Meter);

        EXPECT_FALSE(unit == Unit::Undefined());
        EXPECT_FALSE(Unit::Undefined() == unit);
        EXPECT_FALSE(Unit::Undefined() == Unit::Undefined());
    }
}

TEST(OpenSpaceToolkit_Physics_Unit, NotEqualToOperator)
{
    using ostk::physics::Unit;
    using ostk::physics::units::Length;

    {
        const Unit unit = Unit::Length(Length::Unit::Meter);

        EXPECT_FALSE(unit != unit);
    }

    {
        const Unit firstUnit = Unit::Length(Length::Unit::Meter);
        const Unit secondUnit = Unit::Length(Length::Unit::Meter);

        EXPECT_FALSE(firstUnit != secondUnit);
    }

    {
        const Unit firstUnit = Unit::Length(Length::Unit::Meter);
        const Unit secondUnit = Unit::None();

        EXPECT_TRUE(firstUnit != secondUnit);
    }

    {
        const Unit unit = Unit::Length(Length::Unit::Meter);

        EXPECT_TRUE(unit != Unit::Undefined());
        EXPECT_TRUE(Unit::Undefined() != unit);
        EXPECT_TRUE(Unit::Undefined() != Unit::Undefined());
    }
}

TEST(OpenSpaceToolkit_Physics_Unit, StreamOperator)
{
    using ostk::physics::Unit;
    using ostk::physics::units::Length;

    {
        const Unit unit = Unit::Length(Length::Unit::Meter);

        testing::internal::CaptureStdout();

        EXPECT_NO_THROW(std::cout << unit << std::endl);

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    }
}

TEST(OpenSpaceToolkit_Physics_Unit, IsDefined)
{
    using ostk::physics::Unit;
    using ostk::physics::units::Length;

    {
        EXPECT_FALSE(Unit::Undefined().isDefined());

        EXPECT_TRUE(Unit::None().isDefined());
        EXPECT_TRUE(Unit::Length(Length::Unit::Meter).isDefined());
    }
}

TEST(OpenSpaceToolkit_Physics_Unit, IsNone)
{
    using ostk::physics::Unit;
    using ostk::physics::units::Length;

    {
        EXPECT_TRUE(Unit::None().isNone());
        EXPECT_FALSE(Unit::Length(Length::Unit::Meter).isNone());
    }

    {
        EXPECT_ANY_THROW(Unit::Undefined().isNone());
    }
}

TEST(OpenSpaceToolkit_Physics_Unit, GetType)
{
    using ostk::physics::Unit;
    using ostk::physics::units::Length;

    {
        EXPECT_EQ(Unit::Type::None, Unit::None().getType());
        EXPECT_EQ(Unit::Type::Length, Unit::Length(Length::Unit::Meter).getType());
    }

    {
        EXPECT_ANY_THROW(Unit::Undefined().getType());
    }
}

TEST(OpenSpaceToolkit_Physics_Unit, RatioTo)
{
    using ostk::physics::Unit;
    using ostk::physics::units::Length;

    {
        const Unit unit = Unit::None();

        EXPECT_EQ(1.0, unit.ratioTo(unit));
    }

    {
        const Unit unit = Unit::Length(Length::Unit::Meter);

        EXPECT_EQ(1.0, unit.ratioTo(unit));
    }

    {
        const Unit firstUnit = Unit::Length(Length::Unit::Meter);
        const Unit secondUnit = Unit::Length(Length::Unit::Foot);

        EXPECT_NEAR(3.28084, firstUnit.ratioTo(secondUnit), 1e-5);
    }

    {
        const Unit unit = Unit::Length(Length::Unit::Meter);

        EXPECT_ANY_THROW(unit.ratioTo(Unit::Undefined()));
        EXPECT_ANY_THROW(Unit::Undefined().ratioTo(unit));
        EXPECT_ANY_THROW(Unit::Undefined().ratioTo(Unit::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Physics_Unit, ToString)
{
    using ostk::physics::Unit;
    using ostk::physics::units::Length;

    {
        EXPECT_EQ("-", Unit::None().toString());
    }

    {
        EXPECT_EQ("m", Unit::Length(Length::Unit::Meter).toString());
        EXPECT_EQ("ft", Unit::Length(Length::Unit::Foot).toString());
    }

    {
        EXPECT_ANY_THROW(Unit::Undefined().toString());
    }
}

TEST(OpenSpaceToolkit_Physics_Unit, Undefined)
{
    using ostk::physics::Unit;

    {
        EXPECT_NO_THROW(Unit::Undefined());

        EXPECT_FALSE(Unit::Undefined().isDefined());
    }
}

TEST(OpenSpaceToolkit_Physics_Unit, None)
{
    using ostk::physics::Unit;

    {
        EXPECT_NO_THROW(Unit::None());

        EXPECT_TRUE(Unit::None().isDefined());
    }
}

TEST(OpenSpaceToolkit_Physics_Unit, Length)
{
    using ostk::physics::Unit;
    using ostk::physics::units::Length;

    {
        EXPECT_NO_THROW(Unit::Length(Length::Unit::Meter));

        EXPECT_TRUE(Unit::Length(Length::Unit::Meter).isDefined());
    }
}

TEST(OpenSpaceToolkit_Physics_Unit, StringFromType)
{
    using ostk::physics::Unit;

    {
        EXPECT_EQ("Undefined", Unit::StringFromType(Unit::Type::Undefined));
        EXPECT_EQ("None", Unit::StringFromType(Unit::Type::None));
        EXPECT_EQ("Length", Unit::StringFromType(Unit::Type::Length));
        EXPECT_EQ("Mass", Unit::StringFromType(Unit::Type::Mass));
        EXPECT_EQ("Time", Unit::StringFromType(Unit::Type::Time));
        EXPECT_EQ("Temperature", Unit::StringFromType(Unit::Type::Temperature));
        EXPECT_EQ("ElectricCurrent", Unit::StringFromType(Unit::Type::ElectricCurrent));
        EXPECT_EQ("LuminousIntensity", Unit::StringFromType(Unit::Type::LuminousIntensity));
        EXPECT_EQ("Derived", Unit::StringFromType(Unit::Type::Derived));
    }
}
