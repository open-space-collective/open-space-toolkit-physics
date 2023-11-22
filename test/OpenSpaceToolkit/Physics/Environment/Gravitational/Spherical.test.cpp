/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Spherical.hpp>
#include <OpenSpaceToolkit/Physics/Time/DateTime.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Time/Scale.hpp>

#include <Global.test.hpp>

using ostk::core::types::Real;

using ostk::math::object::Vector3d;

using ostk::physics::units::Length;
using ostk::physics::units::Time;
using ostk::physics::units::Derived;
using ostk::physics::time::Instant;
using ostk::physics::environment::gravitational::Spherical;
using ostk::physics::environment::gravitational::Model;

TEST(OpenSpaceToolkit_Physics_Environment_Gravitational_Spherical, Constructor)
{
    {
        const Derived gravitationalParameter = {
            1.0, Derived::Unit::GravitationalParameter(Length::Unit::Meter, Time::Unit::Second)
        };

        const Model::Parameters parameterSet(gravitationalParameter, Length::Meters(1.0), 0.0, 0.0, 0.0);
        EXPECT_NO_THROW(Spherical spherical(parameterSet));
    }

    {
        EXPECT_ANY_THROW(Spherical spherical(Model::Parameters::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Gravitational_Spherical, Clone)
{
    {
        const Derived gravitationalParameter = {
            1.0, Derived::Unit::GravitationalParameter(Length::Unit::Meter, Time::Unit::Second)
        };

        const Model::Parameters parameterSet(gravitationalParameter, Length::Meters(1.0), 0.0, 0.0, 0.0);
        const Spherical spherical = {parameterSet};

        EXPECT_NO_THROW(const Spherical* sphericalPtr = spherical.clone(); delete sphericalPtr;);
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Gravitational_Spherical, GetFieldValueAt)
{
    {
        const Derived gravitationalParameter = {
            1.0, Derived::Unit::GravitationalParameter(Length::Unit::Meter, Time::Unit::Second)
        };

        const Model::Parameters parameterSet(gravitationalParameter, Length::Meters(1.0), 0.0, 0.0, 0.0);

        const Spherical spherical = {parameterSet};

        const Vector3d fieldValue = spherical.getFieldValueAt({1.0, 0.0, 0.0}, Instant::J2000());

        EXPECT_EQ(Vector3d(-1.0, 0.0, 0.0), fieldValue);
    }
}
