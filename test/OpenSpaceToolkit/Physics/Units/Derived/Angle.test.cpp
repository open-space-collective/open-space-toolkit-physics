/// Apache License 2.0

#include <cmath>
#include <limits>

#include <OpenSpaceToolkit/Mathematics/Geometry/Angle.hpp>

#include <OpenSpaceToolkit/Physics/Unit/Derived/Angle.hpp>

#include <Global.test.hpp>

TEST(OpenSpaceToolkit_Physics_Unit_Derived_Angle, Constructor)
{
    using ostk::physics::unit::Angle;

    {
        const double value = 123.456;
        const Angle::Unit unit = Angle::Unit::Radian;

        EXPECT_NO_THROW(Angle(value, unit));
    }

    {
        const double value = std::numeric_limits<double>::quiet_NaN();
        const Angle::Unit unit = Angle::Unit::Radian;

        EXPECT_NO_THROW(Angle(value, unit));
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Derived_Angle, EqualToOperator)
{
    using ostk::physics::unit::Angle;

    {
        EXPECT_TRUE(Angle(0.0, Angle::Unit::Radian) == Angle(0.0, Angle::Unit::Radian));

        EXPECT_TRUE(Angle(+1.0, Angle::Unit::Radian) == Angle(+1.0, Angle::Unit::Radian));
        EXPECT_TRUE(Angle(-1.0, Angle::Unit::Radian) == Angle(-1.0, Angle::Unit::Radian));
    }

    {
        EXPECT_TRUE(Angle(0.0, Angle::Unit::Radian) == Angle(2.0 * M_PI, Angle::Unit::Radian));
        EXPECT_TRUE(Angle(0.0, Angle::Unit::Radian) == Angle(2.0 * 2.0 * M_PI, Angle::Unit::Radian));
        EXPECT_TRUE(Angle(0.0, Angle::Unit::Radian) == Angle(4.0 * 2.0 * M_PI, Angle::Unit::Radian));

        EXPECT_TRUE(Angle(2.0 * M_PI, Angle::Unit::Radian) == Angle(0.0, Angle::Unit::Radian));
        EXPECT_TRUE(Angle(2.0 * M_PI, Angle::Unit::Radian) == Angle(2.0 * M_PI, Angle::Unit::Radian));
        EXPECT_TRUE(Angle(2.0 * M_PI, Angle::Unit::Radian) == Angle(2.0 * 2.0 * M_PI, Angle::Unit::Radian));
        EXPECT_TRUE(Angle(2.0 * M_PI, Angle::Unit::Radian) == Angle(4.0 * 2.0 * M_PI, Angle::Unit::Radian));
    }

    {
        EXPECT_TRUE(Angle(0.0, Angle::Unit::Degree) == Angle(0.0, Angle::Unit::Radian));
        EXPECT_TRUE(Angle(0.0, Angle::Unit::Arcminute) == Angle(0.0, Angle::Unit::Radian));
        EXPECT_TRUE(Angle(0.0, Angle::Unit::Arcsecond) == Angle(0.0, Angle::Unit::Radian));
        EXPECT_TRUE(Angle(0.0, Angle::Unit::Revolution) == Angle(0.0, Angle::Unit::Radian));

        EXPECT_TRUE(Angle(90.0, Angle::Unit::Degree) == Angle(M_PI / 2.0, Angle::Unit::Radian));
        EXPECT_TRUE(Angle(5400.0, Angle::Unit::Arcminute) == Angle(M_PI / 2.0, Angle::Unit::Radian));
        EXPECT_TRUE(Angle(324000.0, Angle::Unit::Arcsecond) == Angle(M_PI / 2.0, Angle::Unit::Radian));
        EXPECT_TRUE(Angle(0.25, Angle::Unit::Revolution) == Angle(M_PI / 2.0, Angle::Unit::Radian));

        EXPECT_TRUE(Angle(360.0, Angle::Unit::Degree) == Angle(0.0, Angle::Unit::Radian));
        EXPECT_TRUE(Angle(21600.0, Angle::Unit::Arcminute) == Angle(0.0, Angle::Unit::Radian));
        EXPECT_TRUE(Angle(1296000.0, Angle::Unit::Arcsecond) == Angle(0.0, Angle::Unit::Radian));
        EXPECT_TRUE(Angle(1.0, Angle::Unit::Revolution) == Angle(0.0, Angle::Unit::Radian));
    }

    {
        EXPECT_FALSE(Angle(1.0, Angle::Unit::Radian) == Angle(2.0, Angle::Unit::Radian));
        EXPECT_FALSE(Angle(+1.0, Angle::Unit::Radian) == Angle(-1.0, Angle::Unit::Radian));
    }

    {
        EXPECT_FALSE(Angle(90.0, Angle::Unit::Degree) == Angle(M_PI, Angle::Unit::Radian));
        EXPECT_FALSE(Angle(5400.0, Angle::Unit::Arcminute) == Angle(M_PI, Angle::Unit::Radian));
        EXPECT_FALSE(Angle(324000.0, Angle::Unit::Arcsecond) == Angle(M_PI, Angle::Unit::Radian));
        EXPECT_FALSE(Angle(0.25, Angle::Unit::Revolution) == Angle(M_PI, Angle::Unit::Radian));
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Derived_Angle, NotEqualToOperator)
{
    using ostk::physics::unit::Angle;

    {
        EXPECT_TRUE(Angle(1.0, Angle::Unit::Radian) != Angle(2.0, Angle::Unit::Radian));
        EXPECT_TRUE(Angle(+1.0, Angle::Unit::Radian) != Angle(-1.0, Angle::Unit::Radian));
    }

    {
        EXPECT_TRUE(Angle(90.0, Angle::Unit::Degree) != Angle(M_PI, Angle::Unit::Radian));
        EXPECT_TRUE(Angle(5400.0, Angle::Unit::Arcminute) != Angle(M_PI, Angle::Unit::Radian));
        EXPECT_TRUE(Angle(324000.0, Angle::Unit::Arcsecond) != Angle(M_PI, Angle::Unit::Radian));
        EXPECT_TRUE(Angle(0.25, Angle::Unit::Revolution) != Angle(M_PI, Angle::Unit::Radian));
    }

    {
        EXPECT_FALSE(Angle(0.0, Angle::Unit::Radian) != Angle(0.0, Angle::Unit::Radian));

        EXPECT_FALSE(Angle(+1.0, Angle::Unit::Radian) != Angle(+1.0, Angle::Unit::Radian));
        EXPECT_FALSE(Angle(-1.0, Angle::Unit::Radian) != Angle(-1.0, Angle::Unit::Radian));
    }

    {
        EXPECT_FALSE(Angle(0.0, Angle::Unit::Radian) != Angle(2.0 * M_PI, Angle::Unit::Radian));
        EXPECT_FALSE(Angle(0.0, Angle::Unit::Radian) != Angle(2.0 * 2.0 * M_PI, Angle::Unit::Radian));
        EXPECT_FALSE(Angle(0.0, Angle::Unit::Radian) != Angle(4.0 * 2.0 * M_PI, Angle::Unit::Radian));

        EXPECT_FALSE(Angle(2.0 * M_PI, Angle::Unit::Radian) != Angle(0.0, Angle::Unit::Radian));
        EXPECT_FALSE(Angle(2.0 * M_PI, Angle::Unit::Radian) != Angle(2.0 * M_PI, Angle::Unit::Radian));
        EXPECT_FALSE(Angle(2.0 * M_PI, Angle::Unit::Radian) != Angle(2.0 * 2.0 * M_PI, Angle::Unit::Radian));
        EXPECT_FALSE(Angle(2.0 * M_PI, Angle::Unit::Radian) != Angle(4.0 * 2.0 * M_PI, Angle::Unit::Radian));
    }

    {
        EXPECT_FALSE(Angle(0.0, Angle::Unit::Degree) != Angle(0.0, Angle::Unit::Radian));
        EXPECT_FALSE(Angle(0.0, Angle::Unit::Arcminute) != Angle(0.0, Angle::Unit::Radian));
        EXPECT_FALSE(Angle(0.0, Angle::Unit::Arcsecond) != Angle(0.0, Angle::Unit::Radian));
        EXPECT_FALSE(Angle(0.0, Angle::Unit::Revolution) != Angle(0.0, Angle::Unit::Radian));

        EXPECT_FALSE(Angle(90.0, Angle::Unit::Degree) != Angle(M_PI / 2.0, Angle::Unit::Radian));
        EXPECT_FALSE(Angle(5400.0, Angle::Unit::Arcminute) != Angle(M_PI / 2.0, Angle::Unit::Radian));
        EXPECT_FALSE(Angle(324000.0, Angle::Unit::Arcsecond) != Angle(M_PI / 2.0, Angle::Unit::Radian));
        EXPECT_FALSE(Angle(0.25, Angle::Unit::Revolution) != Angle(M_PI / 2.0, Angle::Unit::Radian));

        EXPECT_FALSE(Angle(360.0, Angle::Unit::Degree) != Angle(0.0, Angle::Unit::Radian));
        EXPECT_FALSE(Angle(21600.0, Angle::Unit::Arcminute) != Angle(0.0, Angle::Unit::Radian));
        EXPECT_FALSE(Angle(1296000.0, Angle::Unit::Arcsecond) != Angle(0.0, Angle::Unit::Radian));
        EXPECT_FALSE(Angle(1.0, Angle::Unit::Revolution) != Angle(0.0, Angle::Unit::Radian));
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Derived_Angle, AdditionOperator)
{
    using ostk::physics::unit::Angle;

    {
        EXPECT_EQ(Angle(2.0, Angle::Unit::Radian), Angle(1.0, Angle::Unit::Radian) + Angle(1.0, Angle::Unit::Radian));
        EXPECT_EQ(Angle(0.0, Angle::Unit::Radian), Angle(-1.0, Angle::Unit::Radian) + Angle(+1.0, Angle::Unit::Radian));

        EXPECT_EQ(Angle(2.0, Angle::Unit::Degree), Angle(1.0, Angle::Unit::Degree) + Angle(1.0, Angle::Unit::Degree));
        EXPECT_EQ(Angle(0.0, Angle::Unit::Degree), Angle(-1.0, Angle::Unit::Degree) + Angle(+1.0, Angle::Unit::Degree));

        EXPECT_EQ(
            Angle(2.0, Angle::Unit::Arcminute), Angle(1.0, Angle::Unit::Arcminute) + Angle(1.0, Angle::Unit::Arcminute)
        );
        EXPECT_EQ(
            Angle(0.0, Angle::Unit::Arcminute),
            Angle(-1.0, Angle::Unit::Arcminute) + Angle(+1.0, Angle::Unit::Arcminute)
        );

        EXPECT_EQ(
            Angle(2.0, Angle::Unit::Arcsecond), Angle(1.0, Angle::Unit::Arcsecond) + Angle(1.0, Angle::Unit::Arcsecond)
        );
        EXPECT_EQ(
            Angle(0.0, Angle::Unit::Arcsecond),
            Angle(-1.0, Angle::Unit::Arcsecond) + Angle(+1.0, Angle::Unit::Arcsecond)
        );

        EXPECT_EQ(
            Angle(2.0, Angle::Unit::Revolution),
            Angle(1.0, Angle::Unit::Revolution) + Angle(1.0, Angle::Unit::Revolution)
        );
        EXPECT_EQ(
            Angle(0.0, Angle::Unit::Revolution),
            Angle(-1.0, Angle::Unit::Revolution) + Angle(+1.0, Angle::Unit::Revolution)
        );
    }

    {
        EXPECT_EQ(Angle(2.0, Angle::Unit::Radian), Angle(2.0, Angle::Unit::Radian) + Angle::Revolutions(1.0));
        EXPECT_EQ(Angle(2.0, Angle::Unit::Degree), Angle(2.0, Angle::Unit::Degree) + Angle::Revolutions(1.0));
        EXPECT_EQ(Angle(2.0, Angle::Unit::Arcminute), Angle(2.0, Angle::Unit::Arcminute) + Angle::Revolutions(1.0));
        EXPECT_EQ(Angle(2.0, Angle::Unit::Arcsecond), Angle(2.0, Angle::Unit::Arcsecond) + Angle::Revolutions(1.0));
        EXPECT_EQ(Angle(2.0, Angle::Unit::Revolution), Angle(2.0, Angle::Unit::Revolution) + Angle::Revolutions(1.0));

        EXPECT_EQ(Angle(-2.0, Angle::Unit::Radian), Angle(-2.0, Angle::Unit::Radian) + Angle::Revolutions(-3.0));
        EXPECT_EQ(Angle(-2.0, Angle::Unit::Degree), Angle(-2.0, Angle::Unit::Degree) + Angle::Revolutions(-3.0));
        EXPECT_EQ(Angle(-2.0, Angle::Unit::Arcminute), Angle(-2.0, Angle::Unit::Arcminute) + Angle::Revolutions(-3.0));
        EXPECT_EQ(Angle(-2.0, Angle::Unit::Arcsecond), Angle(-2.0, Angle::Unit::Arcsecond) + Angle::Revolutions(-3.0));
        EXPECT_EQ(
            Angle(-2.0, Angle::Unit::Revolution), Angle(-2.0, Angle::Unit::Revolution) + Angle::Revolutions(-3.0)
        );
    }

    {
        EXPECT_EQ(
            Angle(123.456, Angle::Unit::Radian), Angle(123.456, Angle::Unit::Radian) + Angle(360.0, Angle::Unit::Degree)
        );
        EXPECT_EQ(
            Angle(123.456, Angle::Unit::Radian),
            Angle(123.456, Angle::Unit::Radian) + Angle(360.0 * 60.0, Angle::Unit::Arcminute)
        );
        EXPECT_EQ(
            Angle(123.456, Angle::Unit::Radian),
            Angle(123.456, Angle::Unit::Radian) + Angle(360.0 * 3600.0, Angle::Unit::Arcsecond)
        );
        EXPECT_EQ(
            Angle(123.456, Angle::Unit::Radian),
            Angle(123.456, Angle::Unit::Radian) + Angle(1.0, Angle::Unit::Revolution)
        );
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Derived_Angle, SubtractionOperator)
{
    using ostk::physics::unit::Angle;

    {
        EXPECT_EQ(Angle(0.0, Angle::Unit::Radian), Angle(1.0, Angle::Unit::Radian) - Angle(1.0, Angle::Unit::Radian));
        EXPECT_EQ(
            Angle(-2.0, Angle::Unit::Radian), Angle(-1.0, Angle::Unit::Radian) - Angle(+1.0, Angle::Unit::Radian)
        );

        EXPECT_EQ(Angle(0.0, Angle::Unit::Degree), Angle(1.0, Angle::Unit::Degree) - Angle(1.0, Angle::Unit::Degree));
        EXPECT_EQ(
            Angle(-2.0, Angle::Unit::Degree), Angle(-1.0, Angle::Unit::Degree) - Angle(+1.0, Angle::Unit::Degree)
        );

        EXPECT_EQ(
            Angle(0.0, Angle::Unit::Arcminute), Angle(1.0, Angle::Unit::Arcminute) - Angle(1.0, Angle::Unit::Arcminute)
        );
        EXPECT_EQ(
            Angle(-2.0, Angle::Unit::Arcminute),
            Angle(-1.0, Angle::Unit::Arcminute) - Angle(+1.0, Angle::Unit::Arcminute)
        );

        EXPECT_EQ(
            Angle(0.0, Angle::Unit::Arcsecond), Angle(1.0, Angle::Unit::Arcsecond) - Angle(1.0, Angle::Unit::Arcsecond)
        );
        EXPECT_EQ(
            Angle(-2.0, Angle::Unit::Arcsecond),
            Angle(-1.0, Angle::Unit::Arcsecond) - Angle(+1.0, Angle::Unit::Arcsecond)
        );

        EXPECT_EQ(
            Angle(0.0, Angle::Unit::Revolution),
            Angle(1.0, Angle::Unit::Revolution) - Angle(1.0, Angle::Unit::Revolution)
        );
        EXPECT_EQ(
            Angle(-2.0, Angle::Unit::Revolution),
            Angle(-1.0, Angle::Unit::Revolution) - Angle(+1.0, Angle::Unit::Revolution)
        );
    }

    {
        EXPECT_EQ(Angle(2.0, Angle::Unit::Radian), Angle(2.0, Angle::Unit::Radian) - Angle::Revolutions(1.0));
        EXPECT_EQ(Angle(2.0, Angle::Unit::Degree), Angle(2.0, Angle::Unit::Degree) - Angle::Revolutions(1.0));
        EXPECT_EQ(Angle(2.0, Angle::Unit::Arcminute), Angle(2.0, Angle::Unit::Arcminute) - Angle::Revolutions(1.0));
        EXPECT_EQ(Angle(2.0, Angle::Unit::Arcsecond), Angle(2.0, Angle::Unit::Arcsecond) - Angle::Revolutions(1.0));
        EXPECT_EQ(Angle(2.0, Angle::Unit::Revolution), Angle(2.0, Angle::Unit::Revolution) - Angle::Revolutions(1.0));

        EXPECT_EQ(Angle(-2.0, Angle::Unit::Radian), Angle(-2.0, Angle::Unit::Radian) - Angle::Revolutions(-3.0));
        EXPECT_EQ(Angle(-2.0, Angle::Unit::Degree), Angle(-2.0, Angle::Unit::Degree) - Angle::Revolutions(-3.0));
        EXPECT_EQ(Angle(-2.0, Angle::Unit::Arcminute), Angle(-2.0, Angle::Unit::Arcminute) - Angle::Revolutions(-3.0));
        EXPECT_EQ(Angle(-2.0, Angle::Unit::Arcsecond), Angle(-2.0, Angle::Unit::Arcsecond) - Angle::Revolutions(-3.0));
        EXPECT_EQ(
            Angle(-2.0, Angle::Unit::Revolution), Angle(-2.0, Angle::Unit::Revolution) - Angle::Revolutions(-3.0)
        );
    }

    {
        EXPECT_EQ(
            Angle(123.456, Angle::Unit::Radian), Angle(123.456, Angle::Unit::Radian) - Angle(360.0, Angle::Unit::Degree)
        );
        EXPECT_EQ(
            Angle(123.456, Angle::Unit::Radian),
            Angle(123.456, Angle::Unit::Radian) - Angle(360.0 * 60.0, Angle::Unit::Arcminute)
        );
        EXPECT_EQ(
            Angle(123.456, Angle::Unit::Radian),
            Angle(123.456, Angle::Unit::Radian) - Angle(360.0 * 3600.0, Angle::Unit::Arcsecond)
        );
        EXPECT_EQ(
            Angle(123.456, Angle::Unit::Radian),
            Angle(123.456, Angle::Unit::Radian) - Angle(1.0, Angle::Unit::Revolution)
        );
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Derived_Angle, MultiplicationOperator)
{
    using ostk::physics::unit::Angle;

    {
        EXPECT_EQ(Angle(+1.0, Angle::Unit::Radian), Angle(+1.0, Angle::Unit::Radian) * +1.0);
        EXPECT_EQ(Angle(-1.0, Angle::Unit::Radian), Angle(-1.0, Angle::Unit::Radian) * +1.0);
        EXPECT_EQ(Angle(-1.0, Angle::Unit::Radian), Angle(+1.0, Angle::Unit::Radian) * -1.0);

        EXPECT_EQ(Angle(+1.0, Angle::Unit::Radian), +1.0 * Angle(+1.0, Angle::Unit::Radian));
        EXPECT_EQ(Angle(-1.0, Angle::Unit::Radian), +1.0 * Angle(-1.0, Angle::Unit::Radian));
        EXPECT_EQ(Angle(-1.0, Angle::Unit::Radian), -1.0 * Angle(+1.0, Angle::Unit::Radian));

        EXPECT_EQ(Angle(+6.0, Angle::Unit::Radian), Angle(+2.0, Angle::Unit::Radian) * +3.0);
        EXPECT_EQ(Angle(-6.0, Angle::Unit::Radian), Angle(-2.0, Angle::Unit::Radian) * +3.0);
        EXPECT_EQ(Angle(-6.0, Angle::Unit::Radian), Angle(+2.0, Angle::Unit::Radian) * -3.0);

        EXPECT_EQ(Angle(+6.0, Angle::Unit::Radian), +2.0 * Angle(+3.0, Angle::Unit::Radian));
        EXPECT_EQ(Angle(-6.0, Angle::Unit::Radian), +2.0 * Angle(-3.0, Angle::Unit::Radian));
        EXPECT_EQ(Angle(-6.0, Angle::Unit::Radian), -2.0 * Angle(+3.0, Angle::Unit::Radian));

        EXPECT_EQ(Angle(0.0, Angle::Unit::Radian), Angle(+1.0, Angle::Unit::Radian) * 0.0);
        EXPECT_EQ(Angle(0.0, Angle::Unit::Radian), Angle(-1.0, Angle::Unit::Radian) * 0.0);
        EXPECT_EQ(Angle(0.0, Angle::Unit::Radian), Angle(0.0, Angle::Unit::Radian) * 0.0);

        EXPECT_EQ(Angle(0.0, Angle::Unit::Radian), 0.0 * Angle(+1.0, Angle::Unit::Radian));
        EXPECT_EQ(Angle(0.0, Angle::Unit::Radian), 0.0 * Angle(-1.0, Angle::Unit::Radian));
        EXPECT_EQ(Angle(0.0, Angle::Unit::Radian), 0.0 * Angle(0.0, Angle::Unit::Radian));
    }

    {
        EXPECT_EQ(Angle(6.0, Angle::Unit::Degree), Angle(3.0, Angle::Unit::Degree) * 2.0);
        EXPECT_EQ(Angle(6.0, Angle::Unit::Arcminute), Angle(3.0, Angle::Unit::Arcminute) * 2.0);
        EXPECT_EQ(Angle(6.0, Angle::Unit::Arcsecond), Angle(3.0, Angle::Unit::Arcsecond) * 2.0);
        EXPECT_EQ(Angle(6.0, Angle::Unit::Revolution), Angle(3.0, Angle::Unit::Revolution) * 2.0);

        EXPECT_EQ(Angle(6.0, Angle::Unit::Degree), 2.0 * Angle(3.0, Angle::Unit::Degree));
        EXPECT_EQ(Angle(6.0, Angle::Unit::Arcminute), 2.0 * Angle(3.0, Angle::Unit::Arcminute));
        EXPECT_EQ(Angle(6.0, Angle::Unit::Arcsecond), 2.0 * Angle(3.0, Angle::Unit::Arcsecond));
        EXPECT_EQ(Angle(6.0, Angle::Unit::Revolution), 2.0 * Angle(3.0, Angle::Unit::Revolution));
    }

    {
        EXPECT_ANY_THROW(Angle(1.0, Angle::Unit::Radian) * std::numeric_limits<double>::quiet_NaN());
        EXPECT_ANY_THROW(std::numeric_limits<double>::quiet_NaN() * Angle(1.0, Angle::Unit::Radian));
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Derived_Angle, DivisionOperator)
{
    using ostk::physics::unit::Angle;

    {
        EXPECT_EQ(Angle(+1.0, Angle::Unit::Radian), Angle(+1.0, Angle::Unit::Radian) / +1.0);
        EXPECT_EQ(Angle(-1.0, Angle::Unit::Radian), Angle(-1.0, Angle::Unit::Radian) / +1.0);
        EXPECT_EQ(Angle(-1.0, Angle::Unit::Radian), Angle(+1.0, Angle::Unit::Radian) / -1.0);

        EXPECT_EQ(Angle(+1.0, Angle::Unit::Radian), Angle(+2.0, Angle::Unit::Radian) / +2.0);
        EXPECT_EQ(Angle(-1.0, Angle::Unit::Radian), Angle(-2.0, Angle::Unit::Radian) / +2.0);
        EXPECT_EQ(Angle(-1.0, Angle::Unit::Radian), Angle(+2.0, Angle::Unit::Radian) / -2.0);

        EXPECT_EQ(Angle(+2.0, Angle::Unit::Radian), Angle(+4.0, Angle::Unit::Radian) / +2.0);
        EXPECT_EQ(Angle(-2.0, Angle::Unit::Radian), Angle(-4.0, Angle::Unit::Radian) / +2.0);
        EXPECT_EQ(Angle(-2.0, Angle::Unit::Radian), Angle(+4.0, Angle::Unit::Radian) / -2.0);
    }

    {
        EXPECT_EQ(Angle(0.5, Angle::Unit::Degree), Angle(1.0, Angle::Unit::Degree) / 2.0);
        EXPECT_EQ(Angle(0.5, Angle::Unit::Arcminute), Angle(1.0, Angle::Unit::Arcminute) / 2.0);
        EXPECT_EQ(Angle(0.5, Angle::Unit::Arcsecond), Angle(1.0, Angle::Unit::Arcsecond) / 2.0);
        EXPECT_EQ(Angle(0.5, Angle::Unit::Revolution), Angle(1.0, Angle::Unit::Revolution) / 2.0);
    }

    {
        EXPECT_EQ(Angle(0.0, Angle::Unit::Radian), -Angle(0.0, Angle::Unit::Degree));

        EXPECT_EQ(Angle(-123.456, Angle::Unit::Radian), -Angle(123.456, Angle::Unit::Radian));
        EXPECT_EQ(Angle(-123.456, Angle::Unit::Degree), -Angle(123.456, Angle::Unit::Degree));
        EXPECT_EQ(Angle(-123.456, Angle::Unit::Arcminute), -Angle(123.456, Angle::Unit::Arcminute));
        EXPECT_EQ(Angle(-123.456, Angle::Unit::Arcsecond), -Angle(123.456, Angle::Unit::Arcsecond));
        EXPECT_EQ(Angle(-123.456, Angle::Unit::Revolution), -Angle(123.456, Angle::Unit::Revolution));

        EXPECT_EQ(Angle(123.456, Angle::Unit::Radian), -Angle(-123.456, Angle::Unit::Radian));
        EXPECT_EQ(Angle(123.456, Angle::Unit::Degree), -Angle(-123.456, Angle::Unit::Degree));
        EXPECT_EQ(Angle(123.456, Angle::Unit::Arcminute), -Angle(-123.456, Angle::Unit::Arcminute));
        EXPECT_EQ(Angle(123.456, Angle::Unit::Arcsecond), -Angle(-123.456, Angle::Unit::Arcsecond));
        EXPECT_EQ(Angle(123.456, Angle::Unit::Revolution), -Angle(-123.456, Angle::Unit::Revolution));
    }

    {
        EXPECT_ANY_THROW(Angle(1.0, Angle::Unit::Radian) / std::numeric_limits<double>::quiet_NaN());
        EXPECT_ANY_THROW(Angle(1.0, Angle::Unit::Radian) / 0.0);
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Derived_Angle, AdditionAssignmentOperator)
{
    using ostk::physics::unit::Angle;

    {
        EXPECT_EQ(Angle(2.0, Angle::Unit::Radian), Angle(1.0, Angle::Unit::Radian) += Angle(1.0, Angle::Unit::Radian));
        EXPECT_EQ(
            Angle(0.0, Angle::Unit::Radian), Angle(-1.0, Angle::Unit::Radian) += Angle(+1.0, Angle::Unit::Radian)
        );

        EXPECT_EQ(Angle(2.0, Angle::Unit::Degree), Angle(1.0, Angle::Unit::Degree) += Angle(1.0, Angle::Unit::Degree));
        EXPECT_EQ(
            Angle(0.0, Angle::Unit::Degree), Angle(-1.0, Angle::Unit::Degree) += Angle(+1.0, Angle::Unit::Degree)
        );

        EXPECT_EQ(
            Angle(2.0, Angle::Unit::Arcminute), Angle(1.0, Angle::Unit::Arcminute) += Angle(1.0, Angle::Unit::Arcminute)
        );
        EXPECT_EQ(
            Angle(0.0, Angle::Unit::Arcminute),
            Angle(-1.0, Angle::Unit::Arcminute) += Angle(+1.0, Angle::Unit::Arcminute)
        );

        EXPECT_EQ(
            Angle(2.0, Angle::Unit::Arcsecond), Angle(1.0, Angle::Unit::Arcsecond) += Angle(1.0, Angle::Unit::Arcsecond)
        );
        EXPECT_EQ(
            Angle(0.0, Angle::Unit::Arcsecond),
            Angle(-1.0, Angle::Unit::Arcsecond) += Angle(+1.0, Angle::Unit::Arcsecond)
        );

        EXPECT_EQ(
            Angle(2.0, Angle::Unit::Revolution),
            Angle(1.0, Angle::Unit::Revolution) += Angle(1.0, Angle::Unit::Revolution)
        );
        EXPECT_EQ(
            Angle(0.0, Angle::Unit::Revolution),
            Angle(-1.0, Angle::Unit::Revolution) += Angle(+1.0, Angle::Unit::Revolution)
        );
    }

    {
        EXPECT_EQ(Angle(2.0, Angle::Unit::Radian), Angle(2.0, Angle::Unit::Radian) += Angle::Revolutions(1.0));
        EXPECT_EQ(Angle(2.0, Angle::Unit::Degree), Angle(2.0, Angle::Unit::Degree) += Angle::Revolutions(1.0));
        EXPECT_EQ(Angle(2.0, Angle::Unit::Arcminute), Angle(2.0, Angle::Unit::Arcminute) += Angle::Revolutions(1.0));
        EXPECT_EQ(Angle(2.0, Angle::Unit::Arcsecond), Angle(2.0, Angle::Unit::Arcsecond) += Angle::Revolutions(1.0));
        EXPECT_EQ(Angle(2.0, Angle::Unit::Revolution), Angle(2.0, Angle::Unit::Revolution) += Angle::Revolutions(1.0));

        EXPECT_EQ(Angle(-2.0, Angle::Unit::Radian), Angle(-2.0, Angle::Unit::Radian) += Angle::Revolutions(-3.0));
        EXPECT_EQ(Angle(-2.0, Angle::Unit::Degree), Angle(-2.0, Angle::Unit::Degree) += Angle::Revolutions(-3.0));
        EXPECT_EQ(Angle(-2.0, Angle::Unit::Arcminute), Angle(-2.0, Angle::Unit::Arcminute) += Angle::Revolutions(-3.0));
        EXPECT_EQ(Angle(-2.0, Angle::Unit::Arcsecond), Angle(-2.0, Angle::Unit::Arcsecond) += Angle::Revolutions(-3.0));
        EXPECT_EQ(
            Angle(-2.0, Angle::Unit::Revolution), Angle(-2.0, Angle::Unit::Revolution) += Angle::Revolutions(-3.0)
        );
    }

    {
        EXPECT_EQ(
            Angle(123.456, Angle::Unit::Radian),
            Angle(123.456, Angle::Unit::Radian) += Angle(360.0, Angle::Unit::Degree)
        );
        EXPECT_EQ(
            Angle(123.456, Angle::Unit::Radian),
            Angle(123.456, Angle::Unit::Radian) += Angle(360.0 * 60.0, Angle::Unit::Arcminute)
        );
        EXPECT_EQ(
            Angle(123.456, Angle::Unit::Radian),
            Angle(123.456, Angle::Unit::Radian) += Angle(360.0 * 3600.0, Angle::Unit::Arcsecond)
        );
        EXPECT_EQ(
            Angle(123.456, Angle::Unit::Radian),
            Angle(123.456, Angle::Unit::Radian) += Angle(1.0, Angle::Unit::Revolution)
        );
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Derived_Angle, SubtractionAssignmentOperator)
{
    using ostk::physics::unit::Angle;

    {
        EXPECT_EQ(Angle(0.0, Angle::Unit::Radian), Angle(1.0, Angle::Unit::Radian) -= Angle(1.0, Angle::Unit::Radian));
        EXPECT_EQ(
            Angle(-2.0, Angle::Unit::Radian), Angle(-1.0, Angle::Unit::Radian) -= Angle(+1.0, Angle::Unit::Radian)
        );

        EXPECT_EQ(Angle(0.0, Angle::Unit::Degree), Angle(1.0, Angle::Unit::Degree) -= Angle(1.0, Angle::Unit::Degree));
        EXPECT_EQ(
            Angle(-2.0, Angle::Unit::Degree), Angle(-1.0, Angle::Unit::Degree) -= Angle(+1.0, Angle::Unit::Degree)
        );

        EXPECT_EQ(
            Angle(0.0, Angle::Unit::Arcminute), Angle(1.0, Angle::Unit::Arcminute) -= Angle(1.0, Angle::Unit::Arcminute)
        );
        EXPECT_EQ(
            Angle(-2.0, Angle::Unit::Arcminute),
            Angle(-1.0, Angle::Unit::Arcminute) -= Angle(+1.0, Angle::Unit::Arcminute)
        );

        EXPECT_EQ(
            Angle(0.0, Angle::Unit::Arcsecond), Angle(1.0, Angle::Unit::Arcsecond) -= Angle(1.0, Angle::Unit::Arcsecond)
        );
        EXPECT_EQ(
            Angle(-2.0, Angle::Unit::Arcsecond),
            Angle(-1.0, Angle::Unit::Arcsecond) -= Angle(+1.0, Angle::Unit::Arcsecond)
        );

        EXPECT_EQ(
            Angle(0.0, Angle::Unit::Revolution),
            Angle(1.0, Angle::Unit::Revolution) -= Angle(1.0, Angle::Unit::Revolution)
        );
        EXPECT_EQ(
            Angle(-2.0, Angle::Unit::Revolution),
            Angle(-1.0, Angle::Unit::Revolution) -= Angle(+1.0, Angle::Unit::Revolution)
        );
    }

    {
        EXPECT_EQ(Angle(2.0, Angle::Unit::Radian), Angle(2.0, Angle::Unit::Radian) -= Angle::Revolutions(1.0));
        EXPECT_EQ(Angle(2.0, Angle::Unit::Degree), Angle(2.0, Angle::Unit::Degree) -= Angle::Revolutions(1.0));
        EXPECT_EQ(Angle(2.0, Angle::Unit::Arcminute), Angle(2.0, Angle::Unit::Arcminute) -= Angle::Revolutions(1.0));
        EXPECT_EQ(Angle(2.0, Angle::Unit::Arcsecond), Angle(2.0, Angle::Unit::Arcsecond) -= Angle::Revolutions(1.0));
        EXPECT_EQ(Angle(2.0, Angle::Unit::Revolution), Angle(2.0, Angle::Unit::Revolution) -= Angle::Revolutions(1.0));

        EXPECT_EQ(Angle(-2.0, Angle::Unit::Radian), Angle(-2.0, Angle::Unit::Radian) -= Angle::Revolutions(-3.0));
        EXPECT_EQ(Angle(-2.0, Angle::Unit::Degree), Angle(-2.0, Angle::Unit::Degree) -= Angle::Revolutions(-3.0));
        EXPECT_EQ(Angle(-2.0, Angle::Unit::Arcminute), Angle(-2.0, Angle::Unit::Arcminute) -= Angle::Revolutions(-3.0));
        EXPECT_EQ(Angle(-2.0, Angle::Unit::Arcsecond), Angle(-2.0, Angle::Unit::Arcsecond) -= Angle::Revolutions(-3.0));
        EXPECT_EQ(
            Angle(-2.0, Angle::Unit::Revolution), Angle(-2.0, Angle::Unit::Revolution) -= Angle::Revolutions(-3.0)
        );
    }

    {
        EXPECT_EQ(
            Angle(123.456, Angle::Unit::Radian),
            Angle(123.456, Angle::Unit::Radian) -= Angle(360.0, Angle::Unit::Degree)
        );
        EXPECT_EQ(
            Angle(123.456, Angle::Unit::Radian),
            Angle(123.456, Angle::Unit::Radian) -= Angle(360.0 * 60.0, Angle::Unit::Arcminute)
        );
        EXPECT_EQ(
            Angle(123.456, Angle::Unit::Radian),
            Angle(123.456, Angle::Unit::Radian) -= Angle(360.0 * 3600.0, Angle::Unit::Arcsecond)
        );
        EXPECT_EQ(
            Angle(123.456, Angle::Unit::Radian),
            Angle(123.456, Angle::Unit::Radian) -= Angle(1.0, Angle::Unit::Revolution)
        );
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Derived_Angle, MultiplicationAssignmentOperator)
{
    using ostk::physics::unit::Angle;

    {
        EXPECT_EQ(Angle(+1.0, Angle::Unit::Radian), Angle(+1.0, Angle::Unit::Radian) *= +1.0);
        EXPECT_EQ(Angle(-1.0, Angle::Unit::Radian), Angle(-1.0, Angle::Unit::Radian) *= +1.0);
        EXPECT_EQ(Angle(-1.0, Angle::Unit::Radian), Angle(+1.0, Angle::Unit::Radian) *= -1.0);

        EXPECT_EQ(Angle(+6.0, Angle::Unit::Radian), Angle(+2.0, Angle::Unit::Radian) *= +3.0);
        EXPECT_EQ(Angle(-6.0, Angle::Unit::Radian), Angle(-2.0, Angle::Unit::Radian) *= +3.0);
        EXPECT_EQ(Angle(-6.0, Angle::Unit::Radian), Angle(+2.0, Angle::Unit::Radian) *= -3.0);

        EXPECT_EQ(Angle(0.0, Angle::Unit::Radian), Angle(+1.0, Angle::Unit::Radian) *= 0.0);
        EXPECT_EQ(Angle(0.0, Angle::Unit::Radian), Angle(-1.0, Angle::Unit::Radian) *= 0.0);
        EXPECT_EQ(Angle(0.0, Angle::Unit::Radian), Angle(0.0, Angle::Unit::Radian) *= 0.0);
    }

    {
        EXPECT_EQ(Angle(6.0, Angle::Unit::Degree), Angle(3.0, Angle::Unit::Degree) *= 2.0);
        EXPECT_EQ(Angle(6.0, Angle::Unit::Arcminute), Angle(3.0, Angle::Unit::Arcminute) *= 2.0);
        EXPECT_EQ(Angle(6.0, Angle::Unit::Arcsecond), Angle(3.0, Angle::Unit::Arcsecond) *= 2.0);
        EXPECT_EQ(Angle(6.0, Angle::Unit::Revolution), Angle(3.0, Angle::Unit::Revolution) *= 2.0);
    }

    {
        EXPECT_ANY_THROW(Angle(1.0, Angle::Unit::Radian) *= std::numeric_limits<double>::quiet_NaN());
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Derived_Angle, DivisionAssignmentOperator)
{
    using ostk::physics::unit::Angle;

    {
        EXPECT_EQ(Angle(+1.0, Angle::Unit::Radian), Angle(+1.0, Angle::Unit::Radian) /= +1.0);
        EXPECT_EQ(Angle(-1.0, Angle::Unit::Radian), Angle(-1.0, Angle::Unit::Radian) /= +1.0);
        EXPECT_EQ(Angle(-1.0, Angle::Unit::Radian), Angle(+1.0, Angle::Unit::Radian) /= -1.0);

        EXPECT_EQ(Angle(+1.0, Angle::Unit::Radian), Angle(+2.0, Angle::Unit::Radian) /= +2.0);
        EXPECT_EQ(Angle(-1.0, Angle::Unit::Radian), Angle(-2.0, Angle::Unit::Radian) /= +2.0);
        EXPECT_EQ(Angle(-1.0, Angle::Unit::Radian), Angle(+2.0, Angle::Unit::Radian) /= -2.0);

        EXPECT_EQ(Angle(+2.0, Angle::Unit::Radian), Angle(+4.0, Angle::Unit::Radian) /= +2.0);
        EXPECT_EQ(Angle(-2.0, Angle::Unit::Radian), Angle(-4.0, Angle::Unit::Radian) /= +2.0);
        EXPECT_EQ(Angle(-2.0, Angle::Unit::Radian), Angle(+4.0, Angle::Unit::Radian) /= -2.0);
    }

    {
        EXPECT_EQ(Angle(0.5, Angle::Unit::Degree), Angle(1.0, Angle::Unit::Degree) /= 2.0);
        EXPECT_EQ(Angle(0.5, Angle::Unit::Arcminute), Angle(1.0, Angle::Unit::Arcminute) /= 2.0);
        EXPECT_EQ(Angle(0.5, Angle::Unit::Arcsecond), Angle(1.0, Angle::Unit::Arcsecond) /= 2.0);
        EXPECT_EQ(Angle(0.5, Angle::Unit::Revolution), Angle(1.0, Angle::Unit::Revolution) /= 2.0);
    }

    {
        EXPECT_ANY_THROW(Angle(1.0, Angle::Unit::Radian) /= std::numeric_limits<double>::quiet_NaN());
        EXPECT_ANY_THROW(Angle(1.0, Angle::Unit::Radian) /= 0.0);
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Derived_Angle, UnaryAdditionOperator)
{
    using ostk::physics::unit::Angle;

    {
        EXPECT_EQ(Angle(0.0, Angle::Unit::Radian), +Angle(0.0, Angle::Unit::Degree));

        EXPECT_EQ(Angle(+123.456, Angle::Unit::Radian), +Angle(123.456, Angle::Unit::Radian));
        EXPECT_EQ(Angle(+123.456, Angle::Unit::Degree), +Angle(123.456, Angle::Unit::Degree));
        EXPECT_EQ(Angle(+123.456, Angle::Unit::Arcminute), +Angle(123.456, Angle::Unit::Arcminute));
        EXPECT_EQ(Angle(+123.456, Angle::Unit::Arcsecond), +Angle(123.456, Angle::Unit::Arcsecond));
        EXPECT_EQ(Angle(+123.456, Angle::Unit::Revolution), +Angle(123.456, Angle::Unit::Revolution));

        EXPECT_EQ(Angle(-123.456, Angle::Unit::Radian), +Angle(-123.456, Angle::Unit::Radian));
        EXPECT_EQ(Angle(-123.456, Angle::Unit::Degree), +Angle(-123.456, Angle::Unit::Degree));
        EXPECT_EQ(Angle(-123.456, Angle::Unit::Arcminute), +Angle(-123.456, Angle::Unit::Arcminute));
        EXPECT_EQ(Angle(-123.456, Angle::Unit::Arcsecond), +Angle(-123.456, Angle::Unit::Arcsecond));
        EXPECT_EQ(Angle(-123.456, Angle::Unit::Revolution), +Angle(-123.456, Angle::Unit::Revolution));
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Derived_Angle, UnarySubtractionOperator)
{
    using ostk::physics::unit::Angle;

    {
        EXPECT_EQ(Angle(0.0, Angle::Unit::Radian), -Angle(0.0, Angle::Unit::Degree));

        EXPECT_EQ(Angle(-123.456, Angle::Unit::Radian), -Angle(123.456, Angle::Unit::Radian));
        EXPECT_EQ(Angle(-123.456, Angle::Unit::Degree), -Angle(123.456, Angle::Unit::Degree));
        EXPECT_EQ(Angle(-123.456, Angle::Unit::Arcminute), -Angle(123.456, Angle::Unit::Arcminute));
        EXPECT_EQ(Angle(-123.456, Angle::Unit::Arcsecond), -Angle(123.456, Angle::Unit::Arcsecond));
        EXPECT_EQ(Angle(-123.456, Angle::Unit::Revolution), -Angle(123.456, Angle::Unit::Revolution));

        EXPECT_EQ(Angle(123.456, Angle::Unit::Radian), -Angle(-123.456, Angle::Unit::Radian));
        EXPECT_EQ(Angle(123.456, Angle::Unit::Degree), -Angle(-123.456, Angle::Unit::Degree));
        EXPECT_EQ(Angle(123.456, Angle::Unit::Arcminute), -Angle(-123.456, Angle::Unit::Arcminute));
        EXPECT_EQ(Angle(123.456, Angle::Unit::Arcsecond), -Angle(-123.456, Angle::Unit::Arcsecond));
        EXPECT_EQ(Angle(123.456, Angle::Unit::Revolution), -Angle(-123.456, Angle::Unit::Revolution));
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Derived_Angle, AngleConversionOperator)
{
    using ostk::physics::unit::Angle;

    {
        EXPECT_EQ(
            ostk::mathematics::geometry::Angle(+1.0, ostk::mathematics::geometry::Angle::Unit::Radian),
            Angle(+1.0, Angle::Unit::Radian)
        );
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Derived_Angle, StreamOperator)
{
    using ostk::physics::unit::Angle;

    {
        testing::internal::CaptureStdout();

        EXPECT_NO_THROW(std::cout << Angle(0.5, Angle::Unit::Degree) << std::endl);

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Derived_Angle, IsZero)
{
    using ostk::physics::unit::Angle;

    {
        EXPECT_TRUE(Angle(0.0, Angle::Unit::Radian).isZero());
        EXPECT_TRUE(Angle(0.0, Angle::Unit::Degree).isZero());
        EXPECT_TRUE(Angle(0.0, Angle::Unit::Arcminute).isZero());
        EXPECT_TRUE(Angle(0.0, Angle::Unit::Arcsecond).isZero());
        EXPECT_TRUE(Angle(0.0, Angle::Unit::Revolution).isZero());

        EXPECT_TRUE(Angle(+0.0, Angle::Unit::Radian).isZero());
        EXPECT_TRUE(Angle(-0.0, Angle::Unit::Radian).isZero());

        EXPECT_FALSE(Angle(+1.0, Angle::Unit::Radian).isZero());
        EXPECT_FALSE(Angle(-1.0, Angle::Unit::Radian).isZero());

        EXPECT_FALSE(Angle(+1e-9, Angle::Unit::Radian).isZero());
        EXPECT_FALSE(Angle(-1e-9, Angle::Unit::Radian).isZero());
    }

    {
        EXPECT_FALSE(Angle(std::numeric_limits<double>::quiet_NaN(), Angle::Unit::Radian).isZero());
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Derived_Angle, GetUnit)
{
    using ostk::physics::unit::Angle;

    {
        EXPECT_EQ(Angle::Unit::Radian, Angle(1.0, Angle::Unit::Radian).getUnit());
        EXPECT_EQ(Angle::Unit::Degree, Angle(1.0, Angle::Unit::Degree).getUnit());
        EXPECT_EQ(Angle::Unit::Arcminute, Angle(1.0, Angle::Unit::Arcminute).getUnit());
        EXPECT_EQ(Angle::Unit::Arcsecond, Angle(1.0, Angle::Unit::Arcsecond).getUnit());
        EXPECT_EQ(Angle::Unit::Revolution, Angle(1.0, Angle::Unit::Revolution).getUnit());
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Derived_Angle, In)
{
    using ostk::physics::unit::Angle;

    {
        EXPECT_EQ(1.0, Angle(1.0, Angle::Unit::Radian).in(Angle::Unit::Radian));
        EXPECT_EQ(1.0, Angle(1.0, Angle::Unit::Degree).in(Angle::Unit::Degree));
        EXPECT_EQ(1.0, Angle(1.0, Angle::Unit::Arcminute).in(Angle::Unit::Arcminute));
        EXPECT_EQ(1.0, Angle(1.0, Angle::Unit::Arcsecond).in(Angle::Unit::Arcsecond));
        EXPECT_EQ(1.0, Angle(1.0, Angle::Unit::Revolution).in(Angle::Unit::Revolution));
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Derived_Angle, InRadians)
{
    using ostk::physics::unit::Angle;

    {
        EXPECT_EQ(123.456, Angle(123.456, Angle::Unit::Radian).inRadians());
    }

    {
        EXPECT_EQ(0.0, Angle(0.0, Angle::Unit::Radian).inRadians(0.0, 2.0 * M_PI));

        EXPECT_EQ(M_PI, Angle(M_PI, Angle::Unit::Radian).inRadians(0.0, 2.0 * M_PI));
        EXPECT_EQ(0.0, Angle(2.0 * M_PI, Angle::Unit::Radian).inRadians(0.0, 2.0 * M_PI));
        EXPECT_EQ(M_PI, Angle(3.0 * M_PI, Angle::Unit::Radian).inRadians(0.0, 2.0 * M_PI));
        EXPECT_EQ(0.0, Angle(4.0 * M_PI, Angle::Unit::Radian).inRadians(0.0, 2.0 * M_PI));

        EXPECT_EQ(M_PI, Angle(-M_PI, Angle::Unit::Radian).inRadians(0.0, 2.0 * M_PI));
        EXPECT_EQ(0.0, Angle(-2.0 * M_PI, Angle::Unit::Radian).inRadians(0.0, 2.0 * M_PI));
        EXPECT_EQ(M_PI, Angle(-3.0 * M_PI, Angle::Unit::Radian).inRadians(0.0, 2.0 * M_PI));
        EXPECT_EQ(0.0, Angle(-4.0 * M_PI, Angle::Unit::Radian).inRadians(0.0, 2.0 * M_PI));
    }

    {
        EXPECT_EQ(0.0, Angle(0.0, Angle::Unit::Radian).inRadians(-M_PI, M_PI));

        EXPECT_EQ(-M_PI, Angle(M_PI, Angle::Unit::Radian).inRadians(-M_PI, M_PI));
        EXPECT_EQ(0.0, Angle(2.0 * M_PI, Angle::Unit::Radian).inRadians(-M_PI, M_PI));
        EXPECT_EQ(-M_PI, Angle(3.0 * M_PI, Angle::Unit::Radian).inRadians(-M_PI, M_PI));
        EXPECT_EQ(0.0, Angle(4.0 * M_PI, Angle::Unit::Radian).inRadians(-M_PI, M_PI));

        EXPECT_EQ(-M_PI, Angle(-M_PI, Angle::Unit::Radian).inRadians(-M_PI, M_PI));
        EXPECT_EQ(0.0, Angle(-2.0 * M_PI, Angle::Unit::Radian).inRadians(-M_PI, M_PI));
        EXPECT_EQ(-M_PI, Angle(-3.0 * M_PI, Angle::Unit::Radian).inRadians(-M_PI, M_PI));
        EXPECT_EQ(0.0, Angle(-4.0 * M_PI, Angle::Unit::Radian).inRadians(-M_PI, M_PI));
    }

    {
        EXPECT_ANY_THROW(Angle(0.0, Angle::Unit::Radian).inRadians(0.0, 0.0));
        EXPECT_ANY_THROW(Angle(0.0, Angle::Unit::Radian).inRadians(0.0, M_PI));
        EXPECT_ANY_THROW(Angle(0.0, Angle::Unit::Radian).inRadians(+M_PI, -M_PI));
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Derived_Angle, InDegrees)
{
    using ostk::physics::unit::Angle;

    {
        EXPECT_EQ(360.0, Angle(2.0 * M_PI, Angle::Unit::Radian).inDegrees());
    }

    {
        EXPECT_EQ(0.0, Angle(0.0, Angle::Unit::Radian).inDegrees(0.0, 360.0));

        EXPECT_EQ(180.0, Angle(M_PI, Angle::Unit::Radian).inDegrees(0.0, 360.0));
        EXPECT_EQ(0.0, Angle(2.0 * M_PI, Angle::Unit::Radian).inDegrees(0.0, 360.0));
        EXPECT_EQ(180.0, Angle(3.0 * M_PI, Angle::Unit::Radian).inDegrees(0.0, 360.0));
        EXPECT_EQ(0.0, Angle(4.0 * M_PI, Angle::Unit::Radian).inDegrees(0.0, 360.0));

        EXPECT_EQ(180.0, Angle(-M_PI, Angle::Unit::Radian).inDegrees(0.0, 360.0));
        EXPECT_EQ(0.0, Angle(-2.0 * M_PI, Angle::Unit::Radian).inDegrees(0.0, 360.0));
        EXPECT_EQ(180.0, Angle(-3.0 * M_PI, Angle::Unit::Radian).inDegrees(0.0, 360.0));
        EXPECT_EQ(0.0, Angle(-4.0 * M_PI, Angle::Unit::Radian).inDegrees(0.0, 360.0));
    }

    {
        EXPECT_EQ(0.0, Angle(0.0, Angle::Unit::Radian).inDegrees(-180.0, +180.0));

        EXPECT_EQ(-180.0, Angle(M_PI, Angle::Unit::Radian).inDegrees(-180.0, +180.0));
        EXPECT_EQ(0.0, Angle(2.0 * M_PI, Angle::Unit::Radian).inDegrees(-180.0, +180.0));
        EXPECT_EQ(-180.0, Angle(3.0 * M_PI, Angle::Unit::Radian).inDegrees(-180.0, +180.0));
        EXPECT_EQ(0.0, Angle(4.0 * M_PI, Angle::Unit::Radian).inDegrees(-180.0, +180.0));

        EXPECT_EQ(-180.0, Angle(-M_PI, Angle::Unit::Radian).inDegrees(-180.0, +180.0));
        EXPECT_EQ(0.0, Angle(-2.0 * M_PI, Angle::Unit::Radian).inDegrees(-180.0, +180.0));
        EXPECT_EQ(-180.0, Angle(-3.0 * M_PI, Angle::Unit::Radian).inDegrees(-180.0, +180.0));
        EXPECT_EQ(0.0, Angle(-4.0 * M_PI, Angle::Unit::Radian).inDegrees(-180.0, +180.0));
    }

    {
        EXPECT_ANY_THROW(Angle(0.0, Angle::Unit::Radian).inDegrees(0.0, 0.0));
        EXPECT_ANY_THROW(Angle(0.0, Angle::Unit::Radian).inDegrees(0.0, 180.0));
        EXPECT_ANY_THROW(Angle(0.0, Angle::Unit::Radian).inDegrees(+180.0, -180.0));
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Derived_Angle, InArcminutes)
{
    using ostk::physics::unit::Angle;

    {
        EXPECT_EQ(360.0 * 60.0, Angle(2.0 * M_PI, Angle::Unit::Radian).inArcminutes());
    }

    {
        EXPECT_EQ(0.0, Angle(0.0, Angle::Unit::Radian).inArcminutes(0.0, 360.0 * 60.0));

        EXPECT_EQ(180.0 * 60.0, Angle(M_PI, Angle::Unit::Radian).inArcminutes(0.0, 360.0 * 60.0));
        EXPECT_EQ(0.0, Angle(2.0 * M_PI, Angle::Unit::Radian).inArcminutes(0.0, 360.0 * 60.0));
        EXPECT_EQ(180.0 * 60.0, Angle(3.0 * M_PI, Angle::Unit::Radian).inArcminutes(0.0, 360.0 * 60.0));
        EXPECT_EQ(0.0, Angle(4.0 * M_PI, Angle::Unit::Radian).inArcminutes(0.0, 360.0 * 60.0));

        EXPECT_EQ(180.0 * 60.0, Angle(-M_PI, Angle::Unit::Radian).inArcminutes(0.0, 360.0 * 60.0));
        EXPECT_EQ(0.0, Angle(-2.0 * M_PI, Angle::Unit::Radian).inArcminutes(0.0, 360.0 * 60.0));
        EXPECT_EQ(180.0 * 60.0, Angle(-3.0 * M_PI, Angle::Unit::Radian).inArcminutes(0.0, 360.0 * 60.0));
        EXPECT_EQ(0.0, Angle(-4.0 * M_PI, Angle::Unit::Radian).inArcminutes(0.0, 360.0 * 60.0));
    }

    {
        EXPECT_EQ(0.0, Angle(0.0, Angle::Unit::Radian).inArcminutes(-180.0 * 60.0, +180.0 * 60.0));

        EXPECT_EQ(-180.0 * 60.0, Angle(M_PI, Angle::Unit::Radian).inArcminutes(-180.0 * 60.0, +180.0 * 60.0));
        EXPECT_EQ(0.0, Angle(2.0 * M_PI, Angle::Unit::Radian).inArcminutes(-180.0 * 60.0, +180.0 * 60.0));
        EXPECT_EQ(-180.0 * 60.0, Angle(3.0 * M_PI, Angle::Unit::Radian).inArcminutes(-180.0 * 60.0, +180.0 * 60.0));
        EXPECT_EQ(0.0, Angle(4.0 * M_PI, Angle::Unit::Radian).inArcminutes(-180.0 * 60.0, +180.0 * 60.0));

        EXPECT_EQ(-180.0 * 60.0, Angle(-M_PI, Angle::Unit::Radian).inArcminutes(-180.0 * 60.0, +180.0 * 60.0));
        EXPECT_EQ(0.0, Angle(-2.0 * M_PI, Angle::Unit::Radian).inArcminutes(-180.0 * 60.0, +180.0 * 60.0));
        EXPECT_EQ(-180.0 * 60.0, Angle(-3.0 * M_PI, Angle::Unit::Radian).inArcminutes(-180.0 * 60.0, +180.0 * 60.0));
        EXPECT_EQ(0.0, Angle(-4.0 * M_PI, Angle::Unit::Radian).inArcminutes(-180.0 * 60.0, +180.0 * 60.0));
    }

    {
        EXPECT_ANY_THROW(Angle(0.0, Angle::Unit::Radian).inDegrees(0.0, 0.0));
        EXPECT_ANY_THROW(Angle(0.0, Angle::Unit::Radian).inDegrees(0.0, 180.0 * 60.0));
        EXPECT_ANY_THROW(Angle(0.0, Angle::Unit::Radian).inDegrees(+180.0 * 60.0, -180.0 * 60.0));
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Derived_Angle, InArcseconds)
{
    using ostk::physics::unit::Angle;

    {
        EXPECT_EQ(360.0 * 3600.0, Angle(2.0 * M_PI, Angle::Unit::Radian).inArcseconds());
    }

    {
        EXPECT_EQ(0.0, Angle(0.0, Angle::Unit::Radian).inArcseconds(0.0, 360.0 * 3600.0));

        EXPECT_EQ(180.0 * 3600.0, Angle(M_PI, Angle::Unit::Radian).inArcseconds(0.0, 360.0 * 3600.0));
        EXPECT_EQ(0.0, Angle(2.0 * M_PI, Angle::Unit::Radian).inArcseconds(0.0, 360.0 * 3600.0));
        EXPECT_EQ(180.0 * 3600.0, Angle(3.0 * M_PI, Angle::Unit::Radian).inArcseconds(0.0, 360.0 * 3600.0));
        EXPECT_EQ(0.0, Angle(4.0 * M_PI, Angle::Unit::Radian).inArcseconds(0.0, 360.0 * 3600.0));

        EXPECT_EQ(180.0 * 3600.0, Angle(-M_PI, Angle::Unit::Radian).inArcseconds(0.0, 360.0 * 3600.0));
        EXPECT_EQ(0.0, Angle(-2.0 * M_PI, Angle::Unit::Radian).inArcseconds(0.0, 360.0 * 3600.0));
        EXPECT_EQ(180.0 * 3600.0, Angle(-3.0 * M_PI, Angle::Unit::Radian).inArcseconds(0.0, 360.0 * 3600.0));
        EXPECT_EQ(0.0, Angle(-4.0 * M_PI, Angle::Unit::Radian).inArcseconds(0.0, 360.0 * 3600.0));
    }

    {
        EXPECT_EQ(0.0, Angle(0.0, Angle::Unit::Radian).inArcseconds(-180.0 * 3600.0, +180.0 * 3600.0));

        EXPECT_EQ(-180.0 * 3600.0, Angle(M_PI, Angle::Unit::Radian).inArcseconds(-180.0 * 3600.0, +180.0 * 3600.0));
        EXPECT_EQ(0.0, Angle(2.0 * M_PI, Angle::Unit::Radian).inArcseconds(-180.0 * 3600.0, +180.0 * 3600.0));
        EXPECT_EQ(
            -180.0 * 3600.0, Angle(3.0 * M_PI, Angle::Unit::Radian).inArcseconds(-180.0 * 3600.0, +180.0 * 3600.0)
        );
        EXPECT_EQ(0.0, Angle(4.0 * M_PI, Angle::Unit::Radian).inArcseconds(-180.0 * 3600.0, +180.0 * 3600.0));

        EXPECT_EQ(-180.0 * 3600.0, Angle(-M_PI, Angle::Unit::Radian).inArcseconds(-180.0 * 3600.0, +180.0 * 3600.0));
        EXPECT_EQ(0.0, Angle(-2.0 * M_PI, Angle::Unit::Radian).inArcseconds(-180.0 * 3600.0, +180.0 * 3600.0));
        EXPECT_EQ(
            -180.0 * 3600.0, Angle(-3.0 * M_PI, Angle::Unit::Radian).inArcseconds(-180.0 * 3600.0, +180.0 * 3600.0)
        );
        EXPECT_EQ(0.0, Angle(-4.0 * M_PI, Angle::Unit::Radian).inArcseconds(-180.0 * 3600.0, +180.0 * 3600.0));
    }

    {
        EXPECT_ANY_THROW(Angle(0.0, Angle::Unit::Radian).inDegrees(0.0, 0.0));
        EXPECT_ANY_THROW(Angle(0.0, Angle::Unit::Radian).inDegrees(0.0, 180.0 * 3600.0));
        EXPECT_ANY_THROW(Angle(0.0, Angle::Unit::Radian).inDegrees(+180.0 * 3600.0, -180.0 * 3600.0));
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Derived_Angle, InRevolutions)
{
    using ostk::physics::unit::Angle;

    {
        EXPECT_EQ(1.0, Angle(2.0 * M_PI, Angle::Unit::Radian).inRevolutions());
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Derived_Angle, ToString)
{
    using ostk::physics::unit::Angle;

    {
        EXPECT_EQ("1.0 [rad]", Angle(1.0, Angle::Unit::Radian).toString());
        EXPECT_EQ("1.0 [deg]", Angle(1.0, Angle::Unit::Degree).toString());
        EXPECT_EQ("1.0 [amin]", Angle(1.0, Angle::Unit::Arcminute).toString());
        EXPECT_EQ("1.0 [asec]", Angle(1.0, Angle::Unit::Arcsecond).toString());
        EXPECT_EQ("1.0 [rev]", Angle(1.0, Angle::Unit::Revolution).toString());

        EXPECT_EQ("-1.0 [rad]", Angle(-1.0, Angle::Unit::Radian).toString());
        EXPECT_EQ("-1.0 [deg]", Angle(-1.0, Angle::Unit::Degree).toString());
        EXPECT_EQ("-1.0 [amin]", Angle(-1.0, Angle::Unit::Arcminute).toString());
        EXPECT_EQ("-1.0 [asec]", Angle(-1.0, Angle::Unit::Arcsecond).toString());
        EXPECT_EQ("-1.0 [rev]", Angle(-1.0, Angle::Unit::Revolution).toString());

        EXPECT_EQ("123.456 [rad]", Angle(123.456, Angle::Unit::Radian).toString());
        EXPECT_EQ("123.456 [deg]", Angle(123.456, Angle::Unit::Degree).toString());
        EXPECT_EQ("123.456 [amin]", Angle(123.456, Angle::Unit::Arcminute).toString());
        EXPECT_EQ("123.456 [asec]", Angle(123.456, Angle::Unit::Arcsecond).toString());
        EXPECT_EQ("123.456 [rev]", Angle(123.456, Angle::Unit::Revolution).toString());
    }

    {
        EXPECT_EQ("1.000 [rad]", Angle(1.0, Angle::Unit::Radian).toString(3));
        EXPECT_EQ("1.000 [deg]", Angle(1.0, Angle::Unit::Degree).toString(3));
        EXPECT_EQ("1.000 [amin]", Angle(1.0, Angle::Unit::Arcminute).toString(3));
        EXPECT_EQ("1.000 [asec]", Angle(1.0, Angle::Unit::Arcsecond).toString(3));
        EXPECT_EQ("1.000 [rev]", Angle(1.0, Angle::Unit::Revolution).toString(3));

        EXPECT_EQ("-1.000 [rad]", Angle(-1.0, Angle::Unit::Radian).toString(3));
        EXPECT_EQ("-1.000 [deg]", Angle(-1.0, Angle::Unit::Degree).toString(3));
        EXPECT_EQ("-1.000 [amin]", Angle(-1.0, Angle::Unit::Arcminute).toString(3));
        EXPECT_EQ("-1.000 [asec]", Angle(-1.0, Angle::Unit::Arcsecond).toString(3));
        EXPECT_EQ("-1.000 [rev]", Angle(-1.0, Angle::Unit::Revolution).toString(3));

        EXPECT_EQ("123.456 [rad]", Angle(123.456123, Angle::Unit::Radian).toString(3));
        EXPECT_EQ("123.456 [deg]", Angle(123.456123, Angle::Unit::Degree).toString(3));
        EXPECT_EQ("123.456 [amin]", Angle(123.456123, Angle::Unit::Arcminute).toString(3));
        EXPECT_EQ("123.456 [asec]", Angle(123.456123, Angle::Unit::Arcsecond).toString(3));
        EXPECT_EQ("123.456 [rev]", Angle(123.456123, Angle::Unit::Revolution).toString(3));
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Derived_Angle, Radians)
{
    using ostk::physics::unit::Angle;

    {
        EXPECT_NO_THROW(Angle::Radians(123.456));

        EXPECT_EQ(123.456, Angle::Radians(123.456).in(Angle::Unit::Radian));
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Derived_Angle, Degrees)
{
    using ostk::physics::unit::Angle;

    {
        EXPECT_NO_THROW(Angle::Degrees(123.456));

        EXPECT_EQ(123.456, Angle::Degrees(123.456).in(Angle::Unit::Degree));
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Derived_Angle, Arcminutes)
{
    using ostk::physics::unit::Angle;

    {
        EXPECT_NO_THROW(Angle::Arcminutes(123.456));

        EXPECT_EQ(123.456, Angle::Arcminutes(123.456).in(Angle::Unit::Arcminute));
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Derived_Angle, Arcseconds)
{
    using ostk::physics::unit::Angle;

    {
        EXPECT_NO_THROW(Angle::Arcseconds(123.456));

        EXPECT_EQ(123.456, Angle::Arcseconds(123.456).in(Angle::Unit::Arcsecond));
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Derived_Angle, Revolutions)
{
    using ostk::physics::unit::Angle;

    {
        EXPECT_NO_THROW(Angle::Revolutions(123.456));

        EXPECT_EQ(123.456, Angle::Revolutions(123.456).in(Angle::Unit::Revolution));
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Derived_Angle, Parse)
{
    using ostk::physics::unit::Angle;

    {
        EXPECT_EQ(Angle::Degrees(123.0), Angle::Parse("123 [deg]"));
        EXPECT_EQ(Angle::Degrees(123.0), Angle::Parse("123.0 [deg]"));
        EXPECT_EQ(Angle::Degrees(123.456), Angle::Parse("123.456 [deg]"));
        EXPECT_EQ(Angle::Degrees(1.2e6), Angle::Parse("1.2e6 [deg]"));
        EXPECT_EQ(Angle::Degrees(+123.0), Angle::Parse("+123 [deg]"));
        EXPECT_EQ(Angle::Degrees(+123.0), Angle::Parse("+123.0 [deg]"));
        EXPECT_EQ(Angle::Degrees(+123.456), Angle::Parse("+123.456 [deg]"));
        EXPECT_EQ(Angle::Degrees(+1.2e6), Angle::Parse("+1.2e6 [deg]"));
        EXPECT_EQ(Angle::Degrees(-123.0), Angle::Parse("-123 [deg]"));
        EXPECT_EQ(Angle::Degrees(-123.0), Angle::Parse("-123.0 [deg]"));
        EXPECT_EQ(Angle::Degrees(-123.456), Angle::Parse("-123.456 [deg]"));
        EXPECT_EQ(Angle::Degrees(-1.2e6), Angle::Parse("-1.2e6 [deg]"));

        EXPECT_EQ(Angle(123.0, Angle::Unit::Radian), Angle::Parse("123.0 [rad]"));
        EXPECT_EQ(Angle(123.0, Angle::Unit::Arcminute), Angle::Parse("123.0 [amin]"));
        EXPECT_EQ(Angle(123.0, Angle::Unit::Arcsecond), Angle::Parse("123.0 [asec]"));
        EXPECT_EQ(Angle(123.0, Angle::Unit::Revolution), Angle::Parse("123.0 [rev]"));
    }

    {
        EXPECT_ANY_THROW(Angle::Parse(""));
        EXPECT_ANY_THROW(Angle::Parse("1"));
        EXPECT_ANY_THROW(Angle::Parse("1.0"));
        EXPECT_ANY_THROW(Angle::Parse("1.0 []"));
        EXPECT_ANY_THROW(Angle::Parse("1.0 [m]"));
        EXPECT_ANY_THROW(Angle::Parse("abc"));
        EXPECT_ANY_THROW(Angle::Parse("1.0  [deg]"));
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Derived_Angle, Between_Angles)
{
    using ostk::physics::unit::Angle;

    // Basic cases
    {
        const Angle result = Angle::Between(Angle::Degrees(0.0), Angle::Degrees(90.0));
        EXPECT_NEAR(result.inDegrees(), 90.0, 1e-10);
    }

    {
        const Angle result = Angle::Between(Angle::Degrees(90.0), Angle::Degrees(0.0));
        EXPECT_NEAR(result.inDegrees(), -90.0, 1e-10);
    }

    // Wrap-around cases
    {
        const Angle result = Angle::Between(Angle::Degrees(350.0), Angle::Degrees(10.0));
        EXPECT_NEAR(result.inDegrees(), 20.0, 1e-10);
    }

    {
        const Angle result = Angle::Between(Angle::Degrees(10.0), Angle::Degrees(350.0));
        EXPECT_NEAR(result.inDegrees(), -20.0, 1e-10);
    }

    // Unnormalized cases
    {
        const Angle result = Angle::Between(Angle::Degrees(720.0), Angle::Degrees(10.0));
        EXPECT_NEAR(result.inDegrees(), 10.0, 1e-10);
    }

    {
        const Angle result = Angle::Between(Angle::Degrees(0.0), Angle::Degrees(730.0));
        EXPECT_NEAR(result.inDegrees(), 10.0, 1e-10);
    }

    // Half-turn
    {
        const Angle result = Angle::Between(Angle::Degrees(0.0), Angle::Degrees(180.0));
        EXPECT_NEAR(result.inDegrees(), 180.0, 1e-10);
    }

    // Same angle
    {
        const Angle result = Angle::Between(Angle::Degrees(45.0), Angle::Degrees(45.0));
        EXPECT_NEAR(result.inDegrees(), 0.0, 1e-10);
    }

    // Cross-unit: first angle in degrees, second in radians — result should be in degrees
    {
        const Angle result = Angle::Between(Angle::Degrees(0.0), Angle::Radians(M_PI / 2.0));
        EXPECT_EQ(result.getUnit(), Angle::Unit::Degree);
        EXPECT_NEAR(result.inDegrees(), 90.0, 1e-10);
    }

    // Result in radians when first angle is in radians
    {
        const Angle result = Angle::Between(Angle::Radians(0.0), Angle::Degrees(90.0));
        EXPECT_EQ(result.getUnit(), Angle::Unit::Radian);
        EXPECT_NEAR(result.inRadians(), M_PI / 2.0, 1e-10);
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Derived_Angle, StringFromUnit)
{
    using ostk::physics::unit::Angle;

    {
        EXPECT_EQ("Radian", Angle::StringFromUnit(Angle::Unit::Radian));
        EXPECT_EQ("Degree", Angle::StringFromUnit(Angle::Unit::Degree));
        EXPECT_EQ("Arcminute", Angle::StringFromUnit(Angle::Unit::Arcminute));
        EXPECT_EQ("Arcsecond", Angle::StringFromUnit(Angle::Unit::Arcsecond));
        EXPECT_EQ("Revolution", Angle::StringFromUnit(Angle::Unit::Revolution));
    }
}
