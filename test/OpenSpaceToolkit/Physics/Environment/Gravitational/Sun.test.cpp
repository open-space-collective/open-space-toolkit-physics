/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Containers/Array.hpp>
#include <OpenSpaceToolkit/Core/Containers/Tuple.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Path.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Sun.hpp>
#include <OpenSpaceToolkit/Physics/Time/DateTime.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Time/Scale.hpp>

#include <Global.test.hpp>

using ostk::core::types::Real;
using ostk::core::types::String;
using ostk::core::ctnr::Tuple;
using ostk::core::ctnr::Array;
using ostk::core::filesystem::Path;
using ostk::core::filesystem::Directory;

using ostk::math::object::Vector3d;

using ostk::physics::time::Instant;
using SunGravitationalModel = ostk::physics::environment::gravitational::Sun;

TEST(OpenSpaceToolkit_Physics_Environment_Gravitational_Sun, Constructor)
{
    {
        EXPECT_NO_THROW(SunGravitationalModel sunGravitationalModel(SunGravitationalModel::Type::Spherical));
        EXPECT_NO_THROW(
            std::make_shared<SunGravitationalModel>(SunGravitationalModel::Type::Spherical, Directory::Undefined())
        );
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Gravitational_Sun, IsDefined)
{
    {
        EXPECT_FALSE(SunGravitationalModel(SunGravitationalModel::Type::Undefined).isDefined());

        EXPECT_TRUE(SunGravitationalModel(SunGravitationalModel::Type::Spherical).isDefined());
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Gravitational_Sun, GetType)
{
    {
        EXPECT_EQ(
            SunGravitationalModel::Type::Spherical,
            SunGravitationalModel(SunGravitationalModel::Type::Spherical).getType()
        );
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Gravitational_Sun, GetFieldValueAt)
{
    {
        static const Array<Tuple<SunGravitationalModel::Type, Vector3d, Instant, Vector3d, Real>> testCases = {

            {SunGravitationalModel::Type::Spherical,
             {1500e6, 0.0, 0.0},
             Instant::J2000(),
             {-58.9833066746667, 0.0, 0.0},
             1e-13},
            {SunGravitationalModel::Type::Spherical,
             {15000e6, 0.0, 0.0},
             Instant::J2000(),
             {-0.589833066746667, 0.0, 0.0},
             1e-13},
            {SunGravitationalModel::Type::Spherical,
             {150000e6, 0.0, 0.0},
             Instant::J2000(),
             {-0.00589833066746667, 0.0, 0.0},
             1e-13},

        };

        for (const auto& testCase : testCases)
        {
            const SunGravitationalModel sunGravitationalModel = {std::get<0>(testCase)};

            const Vector3d position = std::get<1>(testCase);
            const Instant instant = std::get<2>(testCase);

            const Vector3d referenceFieldValue = std::get<3>(testCase);
            const Real tolerance = std::get<4>(testCase);

            const Vector3d fieldValue = sunGravitationalModel.getFieldValueAt(position, instant);

            EXPECT_TRUE(fieldValue.isNear(referenceFieldValue, tolerance)) << String::Format(
                "{} ≈ {} Δ {} [m.s-2]",
                fieldValue.toString(),
                referenceFieldValue.toString(),
                (fieldValue - referenceFieldValue).norm()
            );
        }
    }
}
