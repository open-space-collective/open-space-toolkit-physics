/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Container/Tuple.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Path.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Moon.hpp>
#include <OpenSpaceToolkit/Physics/Time/DateTime.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Time/Scale.hpp>

#include <Global.test.hpp>

using ostk::core::type::Real;
using ostk::core::type::String;
using ostk::core::container::Tuple;
using ostk::core::container::Array;
using ostk::core::filesystem::Path;
using ostk::core::filesystem::Directory;

using ostk::mathematics::object::Vector3d;

using ostk::physics::time::Instant;
using MoonGravitationalModel = ostk::physics::environment::gravitational::Moon;

TEST(OpenSpaceToolkit_Physics_Environment_Gravitational_Moon, Constructor)
{
    {
        EXPECT_NO_THROW(MoonGravitationalModel moonGravitationalModel(MoonGravitationalModel::Type::Spherical));
        EXPECT_NO_THROW(
            std::make_shared<MoonGravitationalModel>(MoonGravitationalModel::Type::Spherical, Directory::Undefined())
        );
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Gravitational_Moon, IsDefined)
{
    {
        EXPECT_FALSE(MoonGravitationalModel(MoonGravitationalModel::Type::Undefined).isDefined());

        EXPECT_TRUE(MoonGravitationalModel(MoonGravitationalModel::Type::Spherical).isDefined());
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Gravitational_Moon, GetType)
{
    {
        EXPECT_EQ(
            MoonGravitationalModel::Type::Spherical,
            MoonGravitationalModel(MoonGravitationalModel::Type::Spherical).getType()
        );
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Gravitational_Moon, GetFieldValueAt)
{
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
