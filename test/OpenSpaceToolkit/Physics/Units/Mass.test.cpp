/// Apache License 2.0

#include <cmath>
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

TEST(OpenSpaceToolkit_Physics_Unit_Mass, EqualToOperator)
{
    using ostk::physics::unit::Mass;

    // Same value, same unit
    {
        EXPECT_TRUE(Mass(1.0, Mass::Unit::Kilogram) == Mass(1.0, Mass::Unit::Kilogram));
        EXPECT_TRUE(Mass(1.0, Mass::Unit::Tonne) == Mass(1.0, Mass::Unit::Tonne));
        EXPECT_TRUE(Mass(1.0, Mass::Unit::Pound) == Mass(1.0, Mass::Unit::Pound));
    }

    // Different value or unit
    {
        EXPECT_FALSE(Mass(1.0, Mass::Unit::Kilogram) == Mass(2.0, Mass::Unit::Kilogram));
        EXPECT_FALSE(Mass(+1.0, Mass::Unit::Kilogram) == Mass(-1.0, Mass::Unit::Kilogram));
        EXPECT_FALSE(Mass(1.0, Mass::Unit::Kilogram) == Mass(1.0, Mass::Unit::Tonne));
    }

    // Equivalent value, different units: result must not depend on operand order
    {
        EXPECT_TRUE(Mass(10.3, Mass::Unit::Pound) == Mass(10.3 * 0.45359237, Mass::Unit::Kilogram));
        EXPECT_TRUE(Mass(10.3 * 0.45359237, Mass::Unit::Kilogram) == Mass(10.3, Mass::Unit::Pound));
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Mass, NotEqualToOperator)
{
    using ostk::physics::unit::Mass;

    // Same value, same unit
    {
        EXPECT_FALSE(Mass(1.0, Mass::Unit::Kilogram) != Mass(1.0, Mass::Unit::Kilogram));
        EXPECT_FALSE(Mass(1.0, Mass::Unit::Tonne) != Mass(1.0, Mass::Unit::Tonne));
        EXPECT_FALSE(Mass(1.0, Mass::Unit::Pound) != Mass(1.0, Mass::Unit::Pound));
    }

    // Different value or unit
    {
        EXPECT_TRUE(Mass(1.0, Mass::Unit::Kilogram) != Mass(2.0, Mass::Unit::Kilogram));
        EXPECT_TRUE(Mass(+1.0, Mass::Unit::Kilogram) != Mass(-1.0, Mass::Unit::Kilogram));
        EXPECT_TRUE(Mass(1.0, Mass::Unit::Kilogram) != Mass(1.0, Mass::Unit::Tonne));
    }

    // Equivalent value, different units: result must not depend on operand order
    {
        EXPECT_FALSE(Mass(10.3, Mass::Unit::Pound) != Mass(10.3 * 0.45359237, Mass::Unit::Kilogram));
        EXPECT_FALSE(Mass(10.3 * 0.45359237, Mass::Unit::Kilogram) != Mass(10.3, Mass::Unit::Pound));
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Mass, LowerThanOperator)
{
    using ostk::physics::unit::Mass;

    // Same value, same unit
    {
        EXPECT_FALSE(Mass(1.0, Mass::Unit::Kilogram) < Mass(1.0, Mass::Unit::Kilogram));
        EXPECT_FALSE(Mass(1.0, Mass::Unit::Tonne) < Mass(1.0, Mass::Unit::Tonne));
        EXPECT_FALSE(Mass(1.0, Mass::Unit::Pound) < Mass(1.0, Mass::Unit::Pound));
    }

    // Different value or unit
    {
        EXPECT_TRUE(Mass(1.0, Mass::Unit::Kilogram) < Mass(2.0, Mass::Unit::Kilogram));
        EXPECT_TRUE(Mass(-1.0, Mass::Unit::Kilogram) < Mass(+1.0, Mass::Unit::Kilogram));
        EXPECT_TRUE(Mass(1.0, Mass::Unit::Kilogram) < Mass(1.0, Mass::Unit::Tonne));

        EXPECT_FALSE(Mass(2.0, Mass::Unit::Kilogram) < Mass(1.0, Mass::Unit::Kilogram));
        EXPECT_FALSE(Mass(1.0, Mass::Unit::Tonne) < Mass(1.0, Mass::Unit::Kilogram));
    }

    // Equivalent value, different units: result must not depend on operand order
    {
        EXPECT_FALSE(Mass(10.3, Mass::Unit::Pound) < Mass(10.3 * 0.45359237, Mass::Unit::Kilogram));
        EXPECT_FALSE(Mass(10.3 * 0.45359237, Mass::Unit::Kilogram) < Mass(10.3, Mass::Unit::Pound));
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Mass, LowerThanOrEqualToOperator)
{
    using ostk::physics::unit::Mass;

    // Same value, same unit
    {
        EXPECT_TRUE(Mass(1.0, Mass::Unit::Kilogram) <= Mass(1.0, Mass::Unit::Kilogram));
        EXPECT_TRUE(Mass(1.0, Mass::Unit::Tonne) <= Mass(1.0, Mass::Unit::Tonne));
        EXPECT_TRUE(Mass(1.0, Mass::Unit::Pound) <= Mass(1.0, Mass::Unit::Pound));
    }

    // Different value or unit
    {
        EXPECT_TRUE(Mass(1.0, Mass::Unit::Kilogram) <= Mass(2.0, Mass::Unit::Kilogram));
        EXPECT_TRUE(Mass(-1.0, Mass::Unit::Kilogram) <= Mass(+1.0, Mass::Unit::Kilogram));
        EXPECT_TRUE(Mass(1.0, Mass::Unit::Kilogram) <= Mass(1.0, Mass::Unit::Tonne));

        EXPECT_FALSE(Mass(2.0, Mass::Unit::Kilogram) <= Mass(1.0, Mass::Unit::Kilogram));
        EXPECT_FALSE(Mass(1.0, Mass::Unit::Tonne) <= Mass(1.0, Mass::Unit::Kilogram));
    }

    // Equivalent value, different units: result must not depend on operand order
    {
        EXPECT_TRUE(Mass(10.3, Mass::Unit::Pound) <= Mass(10.3 * 0.45359237, Mass::Unit::Kilogram));
        EXPECT_TRUE(Mass(10.3 * 0.45359237, Mass::Unit::Kilogram) <= Mass(10.3, Mass::Unit::Pound));
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Mass, GreaterThanOperator)
{
    using ostk::physics::unit::Mass;

    // Same value, same unit
    {
        EXPECT_FALSE(Mass(1.0, Mass::Unit::Kilogram) > Mass(1.0, Mass::Unit::Kilogram));
        EXPECT_FALSE(Mass(1.0, Mass::Unit::Tonne) > Mass(1.0, Mass::Unit::Tonne));
        EXPECT_FALSE(Mass(1.0, Mass::Unit::Pound) > Mass(1.0, Mass::Unit::Pound));
    }

    // Different value or unit
    {
        EXPECT_TRUE(Mass(2.0, Mass::Unit::Kilogram) > Mass(1.0, Mass::Unit::Kilogram));
        EXPECT_TRUE(Mass(+1.0, Mass::Unit::Kilogram) > Mass(-1.0, Mass::Unit::Kilogram));
        EXPECT_TRUE(Mass(1.0, Mass::Unit::Tonne) > Mass(1.0, Mass::Unit::Kilogram));

        EXPECT_FALSE(Mass(1.0, Mass::Unit::Kilogram) > Mass(2.0, Mass::Unit::Kilogram));
        EXPECT_FALSE(Mass(1.0, Mass::Unit::Kilogram) > Mass(1.0, Mass::Unit::Tonne));
    }

    // Equivalent value, different units: result must not depend on operand order
    {
        EXPECT_FALSE(Mass(10.3, Mass::Unit::Pound) > Mass(10.3 * 0.45359237, Mass::Unit::Kilogram));
        EXPECT_FALSE(Mass(10.3 * 0.45359237, Mass::Unit::Kilogram) > Mass(10.3, Mass::Unit::Pound));
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Mass, GreaterThanOrEqualToOperator)
{
    using ostk::physics::unit::Mass;

    // Same value, same unit
    {
        EXPECT_TRUE(Mass(1.0, Mass::Unit::Kilogram) >= Mass(1.0, Mass::Unit::Kilogram));
        EXPECT_TRUE(Mass(1.0, Mass::Unit::Tonne) >= Mass(1.0, Mass::Unit::Tonne));
        EXPECT_TRUE(Mass(1.0, Mass::Unit::Pound) >= Mass(1.0, Mass::Unit::Pound));
    }

    // Different value or unit
    {
        EXPECT_TRUE(Mass(2.0, Mass::Unit::Kilogram) >= Mass(1.0, Mass::Unit::Kilogram));
        EXPECT_TRUE(Mass(+1.0, Mass::Unit::Kilogram) >= Mass(-1.0, Mass::Unit::Kilogram));
        EXPECT_TRUE(Mass(1.0, Mass::Unit::Tonne) >= Mass(1.0, Mass::Unit::Kilogram));

        EXPECT_FALSE(Mass(1.0, Mass::Unit::Kilogram) >= Mass(2.0, Mass::Unit::Kilogram));
        EXPECT_FALSE(Mass(1.0, Mass::Unit::Kilogram) >= Mass(1.0, Mass::Unit::Tonne));
    }

    // Equivalent value, different units: result must not depend on operand order
    {
        EXPECT_TRUE(Mass(10.3, Mass::Unit::Pound) >= Mass(10.3 * 0.45359237, Mass::Unit::Kilogram));
        EXPECT_TRUE(Mass(10.3 * 0.45359237, Mass::Unit::Kilogram) >= Mass(10.3, Mass::Unit::Pound));
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Mass, AdditionOperator)
{
    using ostk::physics::unit::Mass;

    // Same unit
    {
        EXPECT_EQ(Mass(2.0, Mass::Unit::Kilogram), Mass(1.0, Mass::Unit::Kilogram) + Mass(1.0, Mass::Unit::Kilogram));
        EXPECT_EQ(Mass(0.0, Mass::Unit::Kilogram), Mass(-1.0, Mass::Unit::Kilogram) + Mass(+1.0, Mass::Unit::Kilogram));
    }

    // Different units: result is expressed in the left operand's unit
    {
        EXPECT_EQ(Mass(1001.0, Mass::Unit::Kilogram), Mass(1.0, Mass::Unit::Kilogram) + Mass(1.0, Mass::Unit::Tonne));

        EXPECT_EQ(Mass::Unit::Kilogram, (Mass(1.0, Mass::Unit::Kilogram) + Mass(1.0, Mass::Unit::Tonne)).getUnit());
        EXPECT_EQ(Mass::Unit::Tonne, (Mass(1.0, Mass::Unit::Tonne) + Mass(1.0, Mass::Unit::Kilogram)).getUnit());
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Mass, SubtractionOperator)
{
    using ostk::physics::unit::Mass;

    // Same unit
    {
        EXPECT_EQ(Mass(0.0, Mass::Unit::Kilogram), Mass(1.0, Mass::Unit::Kilogram) - Mass(1.0, Mass::Unit::Kilogram));
        EXPECT_EQ(
            Mass(-2.0, Mass::Unit::Kilogram), Mass(-1.0, Mass::Unit::Kilogram) - Mass(+1.0, Mass::Unit::Kilogram)
        );
    }

    // Different units: result is expressed in the left operand's unit
    {
        EXPECT_EQ(Mass(-999.0, Mass::Unit::Kilogram), Mass(1.0, Mass::Unit::Kilogram) - Mass(1.0, Mass::Unit::Tonne));

        EXPECT_EQ(Mass::Unit::Kilogram, (Mass(1.0, Mass::Unit::Kilogram) - Mass(1.0, Mass::Unit::Tonne)).getUnit());
        EXPECT_EQ(Mass::Unit::Tonne, (Mass(1.0, Mass::Unit::Tonne) - Mass(1.0, Mass::Unit::Kilogram)).getUnit());
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Mass, MultiplicationOperator)
{
    using ostk::physics::unit::Mass;

    // Kilogram
    {
        EXPECT_EQ(Mass(+1.0, Mass::Unit::Kilogram), Mass(+1.0, Mass::Unit::Kilogram) * +1.0);
        EXPECT_EQ(Mass(-1.0, Mass::Unit::Kilogram), Mass(-1.0, Mass::Unit::Kilogram) * +1.0);
        EXPECT_EQ(Mass(-1.0, Mass::Unit::Kilogram), Mass(+1.0, Mass::Unit::Kilogram) * -1.0);

        EXPECT_EQ(Mass(+1.0, Mass::Unit::Kilogram), +1.0 * Mass(+1.0, Mass::Unit::Kilogram));
        EXPECT_EQ(Mass(-1.0, Mass::Unit::Kilogram), +1.0 * Mass(-1.0, Mass::Unit::Kilogram));
        EXPECT_EQ(Mass(-1.0, Mass::Unit::Kilogram), -1.0 * Mass(+1.0, Mass::Unit::Kilogram));

        EXPECT_EQ(Mass(+6.0, Mass::Unit::Kilogram), Mass(+2.0, Mass::Unit::Kilogram) * +3.0);
        EXPECT_EQ(Mass(-6.0, Mass::Unit::Kilogram), Mass(-2.0, Mass::Unit::Kilogram) * +3.0);
        EXPECT_EQ(Mass(-6.0, Mass::Unit::Kilogram), Mass(+2.0, Mass::Unit::Kilogram) * -3.0);

        EXPECT_EQ(Mass(+6.0, Mass::Unit::Kilogram), +2.0 * Mass(+3.0, Mass::Unit::Kilogram));
        EXPECT_EQ(Mass(-6.0, Mass::Unit::Kilogram), +2.0 * Mass(-3.0, Mass::Unit::Kilogram));
        EXPECT_EQ(Mass(-6.0, Mass::Unit::Kilogram), -2.0 * Mass(+3.0, Mass::Unit::Kilogram));

        EXPECT_EQ(Mass(0.0, Mass::Unit::Kilogram), Mass(+1.0, Mass::Unit::Kilogram) * 0.0);
        EXPECT_EQ(Mass(0.0, Mass::Unit::Kilogram), Mass(-1.0, Mass::Unit::Kilogram) * 0.0);
        EXPECT_EQ(Mass(0.0, Mass::Unit::Kilogram), Mass(0.0, Mass::Unit::Kilogram) * 0.0);

        EXPECT_EQ(Mass(0.0, Mass::Unit::Kilogram), 0.0 * Mass(+1.0, Mass::Unit::Kilogram));
        EXPECT_EQ(Mass(0.0, Mass::Unit::Kilogram), 0.0 * Mass(-1.0, Mass::Unit::Kilogram));
        EXPECT_EQ(Mass(0.0, Mass::Unit::Kilogram), 0.0 * Mass(0.0, Mass::Unit::Kilogram));
    }

    // Other units: unit is preserved
    {
        EXPECT_EQ(Mass(6.0, Mass::Unit::Tonne), Mass(3.0, Mass::Unit::Tonne) * 2.0);
        EXPECT_EQ(Mass(6.0, Mass::Unit::Pound), Mass(3.0, Mass::Unit::Pound) * 2.0);

        EXPECT_EQ(Mass(6.0, Mass::Unit::Tonne), 2.0 * Mass(3.0, Mass::Unit::Tonne));
        EXPECT_EQ(Mass(6.0, Mass::Unit::Pound), 2.0 * Mass(3.0, Mass::Unit::Pound));
    }

    // Invalid scalar
    {
        EXPECT_ANY_THROW(Mass(1.0, Mass::Unit::Kilogram) * std::numeric_limits<double>::quiet_NaN());
        EXPECT_ANY_THROW(std::numeric_limits<double>::quiet_NaN() * Mass(1.0, Mass::Unit::Kilogram));
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Mass, DivisionOperator)
{
    using ostk::physics::unit::Mass;

    // Kilogram
    {
        EXPECT_EQ(Mass(+1.0, Mass::Unit::Kilogram), Mass(+1.0, Mass::Unit::Kilogram) / +1.0);
        EXPECT_EQ(Mass(-1.0, Mass::Unit::Kilogram), Mass(-1.0, Mass::Unit::Kilogram) / +1.0);
        EXPECT_EQ(Mass(-1.0, Mass::Unit::Kilogram), Mass(+1.0, Mass::Unit::Kilogram) / -1.0);

        EXPECT_EQ(Mass(+2.0, Mass::Unit::Kilogram), Mass(+4.0, Mass::Unit::Kilogram) / +2.0);
        EXPECT_EQ(Mass(-2.0, Mass::Unit::Kilogram), Mass(-4.0, Mass::Unit::Kilogram) / +2.0);
        EXPECT_EQ(Mass(-2.0, Mass::Unit::Kilogram), Mass(+4.0, Mass::Unit::Kilogram) / -2.0);
    }

    // Other units: unit is preserved
    {
        EXPECT_EQ(Mass(0.5, Mass::Unit::Tonne), Mass(1.0, Mass::Unit::Tonne) / 2.0);
        EXPECT_EQ(Mass(0.5, Mass::Unit::Pound), Mass(1.0, Mass::Unit::Pound) / 2.0);
    }

    // Invalid scalar
    {
        EXPECT_ANY_THROW(Mass(1.0, Mass::Unit::Kilogram) / std::numeric_limits<double>::quiet_NaN());
        EXPECT_ANY_THROW(Mass(1.0, Mass::Unit::Kilogram) / 0.0);
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Mass, AdditionAssignmentOperator)
{
    using ostk::physics::unit::Mass;

    // Same unit
    {
        EXPECT_EQ(Mass(2.0, Mass::Unit::Kilogram), Mass(1.0, Mass::Unit::Kilogram) += Mass(1.0, Mass::Unit::Kilogram));
        EXPECT_EQ(
            Mass(0.0, Mass::Unit::Kilogram), Mass(-1.0, Mass::Unit::Kilogram) += Mass(+1.0, Mass::Unit::Kilogram)
        );
    }

    // Different units: result is expressed in the left operand's unit
    {
        EXPECT_EQ(Mass(1001.0, Mass::Unit::Kilogram), Mass(1.0, Mass::Unit::Kilogram) += Mass(1.0, Mass::Unit::Tonne));

        EXPECT_EQ(Mass::Unit::Kilogram, (Mass(1.0, Mass::Unit::Kilogram) += Mass(1.0, Mass::Unit::Tonne)).getUnit());
        EXPECT_EQ(Mass::Unit::Tonne, (Mass(1.0, Mass::Unit::Tonne) += Mass(1.0, Mass::Unit::Kilogram)).getUnit());
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Mass, SubtractionAssignmentOperator)
{
    using ostk::physics::unit::Mass;

    // Same unit
    {
        EXPECT_EQ(Mass(0.0, Mass::Unit::Kilogram), Mass(1.0, Mass::Unit::Kilogram) -= Mass(1.0, Mass::Unit::Kilogram));
        EXPECT_EQ(
            Mass(-2.0, Mass::Unit::Kilogram), Mass(-1.0, Mass::Unit::Kilogram) -= Mass(+1.0, Mass::Unit::Kilogram)
        );
    }

    // Different units: result is expressed in the left operand's unit
    {
        EXPECT_EQ(Mass(-999.0, Mass::Unit::Kilogram), Mass(1.0, Mass::Unit::Kilogram) -= Mass(1.0, Mass::Unit::Tonne));

        EXPECT_EQ(Mass::Unit::Kilogram, (Mass(1.0, Mass::Unit::Kilogram) -= Mass(1.0, Mass::Unit::Tonne)).getUnit());
        EXPECT_EQ(Mass::Unit::Tonne, (Mass(1.0, Mass::Unit::Tonne) -= Mass(1.0, Mass::Unit::Kilogram)).getUnit());
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Mass, MultiplicationAssignmentOperator)
{
    using ostk::physics::unit::Mass;

    // Kilogram
    {
        EXPECT_EQ(Mass(+1.0, Mass::Unit::Kilogram), Mass(+1.0, Mass::Unit::Kilogram) *= +1.0);
        EXPECT_EQ(Mass(-1.0, Mass::Unit::Kilogram), Mass(-1.0, Mass::Unit::Kilogram) *= +1.0);
        EXPECT_EQ(Mass(-1.0, Mass::Unit::Kilogram), Mass(+1.0, Mass::Unit::Kilogram) *= -1.0);

        EXPECT_EQ(Mass(+6.0, Mass::Unit::Kilogram), Mass(+2.0, Mass::Unit::Kilogram) *= +3.0);
        EXPECT_EQ(Mass(-6.0, Mass::Unit::Kilogram), Mass(-2.0, Mass::Unit::Kilogram) *= +3.0);
        EXPECT_EQ(Mass(-6.0, Mass::Unit::Kilogram), Mass(+2.0, Mass::Unit::Kilogram) *= -3.0);

        EXPECT_EQ(Mass(0.0, Mass::Unit::Kilogram), Mass(+1.0, Mass::Unit::Kilogram) *= 0.0);
        EXPECT_EQ(Mass(0.0, Mass::Unit::Kilogram), Mass(-1.0, Mass::Unit::Kilogram) *= 0.0);
        EXPECT_EQ(Mass(0.0, Mass::Unit::Kilogram), Mass(0.0, Mass::Unit::Kilogram) *= 0.0);
    }

    // Other units: unit is preserved
    {
        EXPECT_EQ(Mass(6.0, Mass::Unit::Tonne), Mass(3.0, Mass::Unit::Tonne) *= 2.0);
        EXPECT_EQ(Mass(6.0, Mass::Unit::Pound), Mass(3.0, Mass::Unit::Pound) *= 2.0);
    }

    // Invalid scalar
    {
        EXPECT_ANY_THROW(Mass(1.0, Mass::Unit::Kilogram) *= std::numeric_limits<double>::quiet_NaN());
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Mass, DivisionAssignmentOperator)
{
    using ostk::physics::unit::Mass;

    // Kilogram
    {
        EXPECT_EQ(Mass(+1.0, Mass::Unit::Kilogram), Mass(+1.0, Mass::Unit::Kilogram) /= +1.0);
        EXPECT_EQ(Mass(-1.0, Mass::Unit::Kilogram), Mass(-1.0, Mass::Unit::Kilogram) /= +1.0);
        EXPECT_EQ(Mass(-1.0, Mass::Unit::Kilogram), Mass(+1.0, Mass::Unit::Kilogram) /= -1.0);

        EXPECT_EQ(Mass(+2.0, Mass::Unit::Kilogram), Mass(+4.0, Mass::Unit::Kilogram) /= +2.0);
        EXPECT_EQ(Mass(-2.0, Mass::Unit::Kilogram), Mass(-4.0, Mass::Unit::Kilogram) /= +2.0);
        EXPECT_EQ(Mass(-2.0, Mass::Unit::Kilogram), Mass(+4.0, Mass::Unit::Kilogram) /= -2.0);
    }

    // Other units: unit is preserved
    {
        EXPECT_EQ(Mass(0.5, Mass::Unit::Tonne), Mass(1.0, Mass::Unit::Tonne) /= 2.0);
        EXPECT_EQ(Mass(0.5, Mass::Unit::Pound), Mass(1.0, Mass::Unit::Pound) /= 2.0);
    }

    // Invalid scalar
    {
        EXPECT_ANY_THROW(Mass(1.0, Mass::Unit::Kilogram) /= std::numeric_limits<double>::quiet_NaN());
        EXPECT_ANY_THROW(Mass(1.0, Mass::Unit::Kilogram) /= 0.0);
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Mass, UnaryAdditionOperator)
{
    using ostk::physics::unit::Mass;

    {
        EXPECT_EQ(Mass(0.0, Mass::Unit::Kilogram), +Mass(0.0, Mass::Unit::Tonne));

        EXPECT_EQ(Mass(+123.456, Mass::Unit::Kilogram), +Mass(123.456, Mass::Unit::Kilogram));
        EXPECT_EQ(Mass(+123.456, Mass::Unit::Tonne), +Mass(123.456, Mass::Unit::Tonne));

        EXPECT_EQ(Mass(-123.456, Mass::Unit::Kilogram), +Mass(-123.456, Mass::Unit::Kilogram));
        EXPECT_EQ(Mass(-123.456, Mass::Unit::Tonne), +Mass(-123.456, Mass::Unit::Tonne));
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Mass, UnarySubtractionOperator)
{
    using ostk::physics::unit::Mass;

    {
        EXPECT_EQ(Mass(0.0, Mass::Unit::Kilogram), -Mass(0.0, Mass::Unit::Tonne));

        EXPECT_EQ(Mass(-123.456, Mass::Unit::Kilogram), -Mass(123.456, Mass::Unit::Kilogram));
        EXPECT_EQ(Mass(-123.456, Mass::Unit::Tonne), -Mass(123.456, Mass::Unit::Tonne));

        EXPECT_EQ(Mass(123.456, Mass::Unit::Kilogram), -Mass(-123.456, Mass::Unit::Kilogram));
        EXPECT_EQ(Mass(123.456, Mass::Unit::Tonne), -Mass(-123.456, Mass::Unit::Tonne));
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Mass, StreamOperator)
{
    using ostk::physics::unit::Mass;

    {
        testing::internal::CaptureStdout();

        EXPECT_NO_THROW(std::cout << Mass(0.5, Mass::Unit::Tonne) << std::endl);

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
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
        EXPECT_EQ(1 / 0.45359237, Mass(1.0, Mass::Unit::Kilogram).in(Mass::Unit::Pound));
        EXPECT_EQ(1 / 1000.0, Mass(1.0, Mass::Unit::Kilogram).in(Mass::Unit::Tonne));
    }

    {
        EXPECT_NEAR(2.20462262, Mass(1.0, Mass::Unit::Kilogram).in(Mass::Unit::Pound), 1e-8);
        EXPECT_NEAR(1.0, Mass(1000.0, Mass::Unit::Kilogram).in(Mass::Unit::Tonne), 1e-15);
        EXPECT_NEAR(2204.62262185, Mass(1.0, Mass::Unit::Tonne).in(Mass::Unit::Pound), 1e-8);
        EXPECT_NEAR(1.0, Mass(2204.62262185, Mass::Unit::Pound).in(Mass::Unit::Tonne), 1e-10);
    }
}

TEST(OpenSpaceToolkit_Physics_Unit_Mass, InKilograms)
{
    using ostk::physics::unit::Mass;

    {
        EXPECT_EQ(123.456, Mass(123.456, Mass::Unit::Kilogram).inKilograms());
        EXPECT_EQ(0.45359237, Mass(1.0, Mass::Unit::Pound).inKilograms());
        EXPECT_EQ(1000.0, Mass(1.0, Mass::Unit::Tonne).inKilograms());
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
