/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Containers/Array.hpp>
#include <OpenSpaceToolkit/Core/Containers/Tuple.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Path.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Moon.hpp>
#include <OpenSpaceToolkit/Physics/Time/DateTime.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Time/Scale.hpp>

#include <Global.test.hpp>

TEST(OpenSpaceToolkit_Physics_Environment_Gravitational_Moon, Constructor)
{
    using ostk::core::fs::Directory;

    using MoonGravitationalModel = ostk::physics::environment::gravitational::Moon;

    {
        EXPECT_NO_THROW(MoonGravitationalModel moonGravitationalModel(MoonGravitationalModel::Type::Spherical));
        EXPECT_NO_THROW(
            std::make_shared<MoonGravitationalModel>(MoonGravitationalModel::Type::Spherical, Directory::Undefined())
        );
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Gravitational_Moon, GetType)
{
    using ostk::core::fs::Path;
    using ostk::core::fs::Directory;

    using MoonGravitationalModel = ostk::physics::environment::gravitational::Moon;

    {
        EXPECT_EQ(
            MoonGravitationalModel::Type::Spherical,
            MoonGravitationalModel(MoonGravitationalModel::Type::Spherical).getType()
        );
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Gravitational_Moon, GetFieldValueAt)
{
    using ostk::core::types::Real;
    using ostk::core::types::String;
    using ostk::core::ctnr::Tuple;
    using ostk::core::ctnr::Array;
    using ostk::core::fs::Path;
    using ostk::core::fs::Directory;

    using ostk::math::obj::Vector3d;

    using ostk::physics::time::Instant;
    using MoonGravitationalModel = ostk::physics::environment::gravitational::Moon;

    {
        static const Array<Tuple<MoonGravitationalModel::Type, Vector3d, Instant, Vector3d, Real>> testCases = {

            {MoonGravitationalModel::Type::Spherical,
             {1600e3, 0.0, 0.0},
             Instant::J2000(),
             {-1.91515625, 0.0, 0.0},
             1e-13},
            {MoonGravitationalModel::Type::Spherical,
             {16000e3, 0.0, 0.0},
             Instant::J2000(),
             {-0.0191515625, 0.0, 0.0},
             1e-13},
            {MoonGravitationalModel::Type::Spherical,
             {160000e3, 0.0, 0.0},
             Instant::J2000(),
             {-0.000191515625, 0.0, 0.0},
             1e-13},

        };

        for (const auto& testCase : testCases)
        {
            const MoonGravitationalModel moonGravitationalModel = {std::get<0>(testCase)};

            const Vector3d position = std::get<1>(testCase);
            const Instant instant = std::get<2>(testCase);

            const Vector3d referenceFieldValue = std::get<3>(testCase);
            const Real tolerance = std::get<4>(testCase);

            const Vector3d fieldValue = moonGravitationalModel.getFieldValueAt(position, instant);

            EXPECT_TRUE(fieldValue.isNear(referenceFieldValue, tolerance)) << String::Format(
                "{} ≈ {} Δ {} [m.s-2]",
                fieldValue.toString(),
                referenceFieldValue.toString(),
                (fieldValue - referenceFieldValue).norm()
            );
        }
    }
}
