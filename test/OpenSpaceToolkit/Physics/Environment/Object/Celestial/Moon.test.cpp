/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Container/Map.hpp>
#include <OpenSpaceToolkit/Core/Container/Table.hpp>
#include <OpenSpaceToolkit/Core/Container/Triple.hpp>
#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Type/Shared.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>
#include <OpenSpaceToolkit/Core/Type/Weak.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object/Point.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object/Polygon.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Intersection.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Ellipsoid.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/LineString.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Point.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Polygon.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Pyramid.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Segment.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/Quaternion.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/RotationVector.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Spherical/LLA.hpp>
#include <OpenSpaceToolkit/Physics/Environment.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Ephemeris/Analytical.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Object/Celestial/Moon.hpp>
#include <OpenSpaceToolkit/Physics/Time/DateTime.hpp>
#include <OpenSpaceToolkit/Physics/Time/Duration.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Time/Interval.hpp>
#include <OpenSpaceToolkit/Physics/Time/Scale.hpp>
#include <OpenSpaceToolkit/Physics/Unit/Length.hpp>

#include <Global.test.hpp>

using ostk::physics::environment::object::celestial::Moon;

// TEST (OpenSpaceToolkit_Physics_Environment_Object_Celestial_Moon, Constructor)
// {

//     using ostk::physics::environment::object::celestial::Moon ;

//     {

//         FAIL() ;

//     }

// }

TEST(OpenSpaceToolkit_Physics_Environment_Object_Celestial_Moon, Spherical)
{
    {
        EXPECT_NO_THROW(Moon::Spherical());
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Object_Celestial_Moon, Constructor_NullArguments)
{
    using ostk::core::type::Shared;

    using ostk::physics::environment::Ephemeris;

    using MoonGravitationalModel = ostk::physics::environment::gravitational::Moon;

    const Shared<MoonGravitationalModel> gravitationalModelSPtr =
        std::make_shared<MoonGravitationalModel>(MoonGravitationalModel::Type::Spherical);

    EXPECT_THROW(Moon(nullptr, gravitationalModelSPtr), ostk::core::error::runtime::Undefined);
    EXPECT_THROW(
        Moon(
            std::make_shared<ostk::physics::environment::ephemeris::Analytical>(ostk::physics::coordinate::Frame::GCRF()
            ),
            nullptr
        ),
        ostk::core::error::runtime::Undefined
    );
}
