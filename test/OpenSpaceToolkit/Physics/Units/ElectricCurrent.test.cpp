/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Type/Real.hpp>

#include <OpenSpaceToolkit/Physics/Units/ElectricCurrent.hpp>

#include <Global.test.hpp>

TEST(OpenSpaceToolkit_Physics_Units_ElectricCurrent, Constructor)
{
    using ostk::core::type::Real;
    using ostk::physics::units::ElectricCurrent;

    {
        const Real value = 123.456;
        const ElectricCurrent::Unit unit = ElectricCurrent::Unit::Ampere;

        EXPECT_NO_THROW(ElectricCurrent(value, unit));
    }

    {
        const Real value = Real::Undefined();
        const ElectricCurrent::Unit unit = ElectricCurrent::Unit::Undefined;

        EXPECT_NO_THROW(ElectricCurrent(value, unit));
    }
}

TEST(OpenSpaceToolkit_Physics_Units_ElectricCurrent, Clone)
{
    using ostk::core::type::Real;
    using ostk::physics::units::ElectricCurrent;

    {
        const Real value = 123.456;
        const ElectricCurrent::Unit unit = ElectricCurrent::Unit::Ampere;

        const ElectricCurrent electricCurrent = {value, unit};

        EXPECT_NO_THROW(const ElectricCurrent* electricCurrentPtr = electricCurrent.clone(); delete electricCurrentPtr;
        );
    }
}

TEST(OpenSpaceToolkit_Physics_Units_ElectricCurrent, IsDefined)
{
    using ostk::core::type::Real;
    using ostk::physics::units::ElectricCurrent;

    {
        EXPECT_TRUE(ElectricCurrent(0.0, ElectricCurrent::Unit::Ampere).isDefined());

        EXPECT_TRUE(ElectricCurrent(1.0, ElectricCurrent::Unit::Ampere).isDefined());
    }

    {
        EXPECT_FALSE(ElectricCurrent::Undefined().isDefined());
        EXPECT_FALSE(ElectricCurrent(Real::Undefined(), ElectricCurrent::Unit::Ampere).isDefined());
        EXPECT_FALSE(ElectricCurrent(1.0, ElectricCurrent::Unit::Undefined).isDefined());
    }
}

TEST(OpenSpaceToolkit_Physics_Units_ElectricCurrent, GetUnit)
{
    using ostk::physics::units::ElectricCurrent;

    {
        EXPECT_EQ(ElectricCurrent::Unit::Undefined, ElectricCurrent(1.0, ElectricCurrent::Unit::Undefined).getUnit());
        EXPECT_EQ(ElectricCurrent::Unit::Ampere, ElectricCurrent(1.0, ElectricCurrent::Unit::Ampere).getUnit());
    }
}

TEST(OpenSpaceToolkit_Physics_Units_ElectricCurrent, In)
{
    using ostk::physics::units::ElectricCurrent;

    {
        EXPECT_EQ(1.0, ElectricCurrent(1.0, ElectricCurrent::Unit::Ampere).in(ElectricCurrent::Unit::Ampere));
    }

    {
        EXPECT_FALSE(ElectricCurrent::Undefined().in(ElectricCurrent::Unit::Ampere).isDefined());
    }
}

TEST(OpenSpaceToolkit_Physics_Units_ElectricCurrent, InAmperes)
{
    using ostk::physics::units::ElectricCurrent;

    {
        EXPECT_EQ(123.456, ElectricCurrent(123.456, ElectricCurrent::Unit::Ampere).inAmperes());
    }

    {
        EXPECT_FALSE(ElectricCurrent::Undefined().inAmperes().isDefined());
    }
}

TEST(OpenSpaceToolkit_Physics_Units_ElectricCurrent, ToString)
{
    using ostk::physics::units::ElectricCurrent;

    {
        EXPECT_EQ("1.0 [A]", ElectricCurrent(1.0, ElectricCurrent::Unit::Ampere).toString());

        EXPECT_EQ("-1.0 [A]", ElectricCurrent(-1.0, ElectricCurrent::Unit::Ampere).toString());

        EXPECT_EQ("123.456 [A]", ElectricCurrent(123.456, ElectricCurrent::Unit::Ampere).toString());
    }

    {
        EXPECT_EQ("1.000 [A]", ElectricCurrent(1.0, ElectricCurrent::Unit::Ampere).toString(3));

        EXPECT_EQ("-1.000 [A]", ElectricCurrent(-1.0, ElectricCurrent::Unit::Ampere).toString(3));

        EXPECT_EQ("123.456 [A]", ElectricCurrent(123.456123, ElectricCurrent::Unit::Ampere).toString(3));
    }

    {
        EXPECT_ANY_THROW(ElectricCurrent::Undefined().toString());
    }
}

TEST(OpenSpaceToolkit_Physics_Units_ElectricCurrent, Undefined)
{
    using ostk::physics::units::ElectricCurrent;

    {
        EXPECT_NO_THROW(ElectricCurrent::Undefined());
        EXPECT_FALSE(ElectricCurrent::Undefined().isDefined());

        // EXPECT_NO_THROW(ElectricCurrent::Undefined().in(ElectricCurrent::Unit::Ampere)) ;
    }
}

TEST(OpenSpaceToolkit_Physics_Units_ElectricCurrent, Amperes)
{
    using ostk::physics::units::ElectricCurrent;

    {
        EXPECT_NO_THROW(ElectricCurrent::Amperes(123.456));
        EXPECT_TRUE(ElectricCurrent::Amperes(123.456).isDefined());

        EXPECT_EQ(123.456, ElectricCurrent::Amperes(123.456).in(ElectricCurrent::Unit::Ampere));
    }
}

TEST(OpenSpaceToolkit_Physics_Units_ElectricCurrent, StringFromUnit)
{
    using ostk::physics::units::ElectricCurrent;

    {
        EXPECT_EQ("Undefined", ElectricCurrent::StringFromUnit(ElectricCurrent::Unit::Undefined));
        EXPECT_EQ("Ampere", ElectricCurrent::StringFromUnit(ElectricCurrent::Unit::Ampere));
    }
}

TEST(OpenSpaceToolkit_Physics_Units_ElectricCurrent, SymbolFromUnit)
{
    using ostk::physics::units::ElectricCurrent;

    {
        EXPECT_EQ("A", ElectricCurrent::SymbolFromUnit(ElectricCurrent::Unit::Ampere));
    }
}
