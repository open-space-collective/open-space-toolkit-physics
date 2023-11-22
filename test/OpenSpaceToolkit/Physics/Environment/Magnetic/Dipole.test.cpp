/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Environment/Magnetic/Dipole.hpp>
#include <OpenSpaceToolkit/Physics/Time/DateTime.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Time/Scale.hpp>

#include <Global.test.hpp>

using ostk::math::object::Vector3d;

using ostk::physics::time::Instant;

using ostk::physics::environment::magnetic::Dipole;

TEST(OpenSpaceToolkit_Physics_Environment_Magnetic_Dipole, Constructor)
{
    {
        const Vector3d magneticMoment = {0.0, 0.0, 1.0};

        EXPECT_NO_THROW(Dipole dipole(magneticMoment));
    }

    {
        EXPECT_ANY_THROW(Dipole dipole(Vector3d::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Magnetic_Dipole, Clone)
{
    {
        const Vector3d magneticMoment = {0.0, 0.0, 1.0};

        const Dipole dipole = {magneticMoment};

        EXPECT_NO_THROW(const Dipole* dipolePtr = dipole.clone(); delete dipolePtr;);
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Magnetic_Dipole, IsDefined)
{
    using ostk::math::object::Vector3d;

    using ostk::physics::environment::magnetic::Dipole;

    {
        const Vector3d magneticMoment = {0.0, 0.0, 1.0};

        const Dipole dipole = {magneticMoment};

        EXPECT_TRUE(dipole.isDefined());
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Magnetic_Dipole, GetFieldValueAt)
{
    {
        const Vector3d magneticMoment = {0.0, 0.0, 1.0};

        const Dipole dipole = {magneticMoment};

        EXPECT_TRUE(
            dipole.getFieldValueAt({+1.0, 0.0, 0.0}, Instant::J2000()).isApprox(Vector3d(0.0, 0.0, -1e-7), 1e-20)
        );
        EXPECT_TRUE(
            dipole.getFieldValueAt({-1.0, 0.0, 0.0}, Instant::J2000()).isApprox(Vector3d(0.0, 0.0, -1e-7), 1e-20)
        );

        EXPECT_TRUE(
            dipole.getFieldValueAt({0.0, +1.0, 0.0}, Instant::J2000()).isApprox(Vector3d(0.0, 0.0, -1e-7), 1e-20)
        );
        EXPECT_TRUE(
            dipole.getFieldValueAt({0.0, -1.0, 0.0}, Instant::J2000()).isApprox(Vector3d(0.0, 0.0, -1e-7), 1e-20)
        );

        EXPECT_TRUE(
            dipole.getFieldValueAt({0.0, 0.0, +1.0}, Instant::J2000()).isApprox(Vector3d(0.0, 0.0, +2e-7), 1e-20)
        );
        EXPECT_TRUE(
            dipole.getFieldValueAt({0.0, 0.0, -1.0}, Instant::J2000()).isApprox(Vector3d(0.0, 0.0, +2e-7), 1e-20)
        );
    }
}
