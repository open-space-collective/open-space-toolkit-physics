/// Apache License 2.0

#include <cmath>

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Container/Map.hpp>
#include <OpenSpaceToolkit/Core/Container/Table.hpp>
#include <OpenSpaceToolkit/Core/Container/Triple.hpp>
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

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Position.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Spherical/LLA.hpp>
#include <OpenSpaceToolkit/Physics/Environment.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Ephemeris/SPICE/Engine.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Ephemeris/SPICE/Manager.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Object/Celestial/Sun.hpp>
#include <OpenSpaceToolkit/Physics/Time/DateTime.hpp>
#include <OpenSpaceToolkit/Physics/Time/Duration.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Time/Interval.hpp>
#include <OpenSpaceToolkit/Physics/Time/Scale.hpp>
#include <OpenSpaceToolkit/Physics/Unit/Length.hpp>

#include <Global.test.hpp>

using ostk::core::container::Array;
using ostk::core::filesystem::Directory;
using ostk::core::filesystem::File;
using ostk::core::filesystem::Path;
using ostk::core::type::Real;
using ostk::core::type::String;

using ostk::mathematics::object::Vector3d;

using ostk::physics::coordinate::Frame;
using ostk::physics::coordinate::Position;
using ostk::physics::environment::ephemeris::spice::Engine;
using ostk::physics::environment::ephemeris::spice::Kernel;
using ostk::physics::environment::ephemeris::spice::Manager;
using ostk::physics::environment::object::celestial::Sun;
using ostk::physics::time::DateTime;
using ostk::physics::time::Instant;
using ostk::physics::time::Scale;

// TEST (OpenSpaceToolkit_Physics_Environment_Object_Celestial_Sun, Constructor)
// {

//     using ostk::physics::environment::object::celestial::Sun ;

//     {

//         FAIL() ;

//     }

// }

TEST(OpenSpaceToolkit_Physics_Environment_Object_Celestial_Sun, Spherical)
{
    {
        EXPECT_NO_THROW(Sun::Spherical());
    }
}

class OpenSpaceToolkit_Physics_Environment_Object_Celestial_Sun_Analytical : public ::testing::Test
{
   protected:
    Engine& engine_;
    Manager& manager_;

    OpenSpaceToolkit_Physics_Environment_Object_Celestial_Sun_Analytical()
        : engine_(Engine::Get()),
          manager_(Manager::Get())
    {
    }

    void TearDown() override
    {
        engine_.reset();
        manager_.setMode(Manager::Mode::Automatic);
    }

    void loadSpiceKernels()
    {
        const Directory spiceLocalRepository =
            Directory::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Ephemeris/SPICE"));

        manager_.setMode(Manager::Mode::Manual);

        engine_.reset();

        engine_.loadKernel(Kernel::File(File::Path(spiceLocalRepository.getPath() + Path::Parse("naif0012.tls"))));
        engine_.loadKernel(Kernel::File(File::Path(spiceLocalRepository.getPath() + Path::Parse("de430.bsp"))));
        engine_.loadKernel(Kernel::File(File::Path(spiceLocalRepository.getPath() + Path::Parse("pck00010.tpc"))));
    }

    static Array<Instant> ComparisonInstants()
    {
        return {
            Instant::DateTime(DateTime(2020, 1, 1, 0, 0, 0), Scale::UTC),
            Instant::DateTime(DateTime(2020, 8, 15, 6, 30, 0), Scale::UTC),
            Instant::DateTime(DateTime(2021, 3, 10, 12, 0, 0), Scale::UTC),
            Instant::DateTime(DateTime(2021, 11, 25, 18, 45, 0), Scale::UTC),
            Instant::DateTime(DateTime(2022, 6, 1, 3, 15, 0), Scale::UTC),
            Instant::DateTime(DateTime(2023, 1, 20, 9, 0, 0), Scale::UTC),
            Instant::DateTime(DateTime(2023, 9, 5, 21, 30, 0), Scale::UTC),
            Instant::DateTime(DateTime(2024, 4, 14, 15, 0, 0), Scale::UTC),
            Instant::DateTime(DateTime(2025, 2, 28, 0, 0, 0), Scale::UTC),
            Instant::DateTime(DateTime(2025, 12, 15, 12, 0, 0), Scale::UTC),
            Instant::DateTime(DateTime(2026, 5, 30, 6, 0, 0), Scale::UTC),
        };
    }

    static Real ComputeAngularSeparation_deg(const Vector3d& aFirstVector, const Vector3d& aSecondVector)
    {
        const double cosine = std::clamp(aFirstVector.normalized().dot(aSecondVector.normalized()), -1.0, 1.0);

        return std::acos(cosine) * 180.0 / M_PI;
    }
};

TEST_F(OpenSpaceToolkit_Physics_Environment_Object_Celestial_Sun_Analytical, ComputeAnalyticalPosition)
{
    this->loadSpiceKernels();

    const Sun sun = Sun::Default();

    {
        const Instant instant = Instant::DateTime(DateTime(2024, 1, 1, 0, 0, 0), Scale::UTC);

        const Position position = sun.computeAnalyticalPosition(instant);

        EXPECT_TRUE(position.isDefined());
        EXPECT_EQ(Frame::GCRF(), position.accessFrame());
    }

    {
        EXPECT_ANY_THROW(sun.computeAnalyticalPosition(Instant::Undefined()));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Object_Celestial_Sun_Analytical, ComputeAnalyticalPosition_VersusSpice)
{
    {
        this->loadSpiceKernels();

        const Sun sunSpice = Sun::Default();

        for (const auto& instant : ComparisonInstants())
        {
            const Vector3d x_GCRF_analytical = sunSpice.computeAnalyticalPosition(instant).getCoordinates();
            const Vector3d x_GCRF_spice = sunSpice.getPositionIn(Frame::GCRF(), instant).getCoordinates();

            const Real angularSeparation_deg = ComputeAngularSeparation_deg(x_GCRF_analytical, x_GCRF_spice);
            const Real relativeDistanceError =
                std::abs(x_GCRF_analytical.norm() - x_GCRF_spice.norm()) / x_GCRF_spice.norm();

            // The dominant Sun error is a slow drift (~11.6 arcsec/year) due to the neglected motion of the
            // Earth's perihelion: ~0.07-0.09 deg over 2020-2026.

            EXPECT_LT(angularSeparation_deg, 0.1) << String::Format(
                "{}: angular separation = {} [deg]", instant.toString(), angularSeparation_deg.toString()
            );
            EXPECT_LT(relativeDistanceError, 0.005) << String::Format(
                "{}: relative distance error = {}", instant.toString(), relativeDistanceError.toString()
            );
        }
    }
}
