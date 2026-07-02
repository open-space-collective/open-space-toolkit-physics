/// Apache License 2.0

#include <cmath>

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>
#include <OpenSpaceToolkit/Core/Type/Shared.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Ephemeris/SPICE.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Ephemeris/SPICE/Engine.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Ephemeris/SPICE/Manager.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Ephemeris/SunMoonAnalytical.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Object/Celestial/Moon.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Object/Celestial/Sun.hpp>
#include <OpenSpaceToolkit/Physics/Time/DateTime.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Time/Scale.hpp>

#include <Global.test.hpp>

using ostk::physics::environment::ephemeris::SunMoonAnalytical;

using ostk::core::container::Array;
using ostk::core::filesystem::Directory;
using ostk::core::filesystem::File;
using ostk::core::filesystem::Path;
using ostk::core::type::Real;
using ostk::core::type::Shared;
using ostk::core::type::String;

using ostk::mathematics::object::Vector3d;

using ostk::physics::coordinate::Frame;
using ostk::physics::environment::ephemeris::SPICE;
using ostk::physics::environment::ephemeris::spice::Engine;
using ostk::physics::environment::ephemeris::spice::Kernel;
using ostk::physics::environment::ephemeris::spice::Manager;
using ostk::physics::environment::object::celestial::Moon;
using ostk::physics::environment::object::celestial::Sun;
using ostk::physics::time::DateTime;
using ostk::physics::time::Instant;
using ostk::physics::time::Scale;

class OpenSpaceToolkit_Physics_Environment_Ephemeris_SunMoonAnalytical : public ::testing::Test
{
   protected:
    Engine& engine_;
    Manager& manager_;

    OpenSpaceToolkit_Physics_Environment_Ephemeris_SunMoonAnalytical()
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

TEST_F(OpenSpaceToolkit_Physics_Environment_Ephemeris_SunMoonAnalytical, Constructor)
{
    {
        EXPECT_NO_THROW(SunMoonAnalytical sunEphemeris {SunMoonAnalytical::Body::Sun});
        EXPECT_NO_THROW(SunMoonAnalytical moonEphemeris {SunMoonAnalytical::Body::Moon});
    }

    // Repeated construction does not throw

    {
        const SunMoonAnalytical firstSunEphemeris = {SunMoonAnalytical::Body::Sun};
        const SunMoonAnalytical secondSunEphemeris = {SunMoonAnalytical::Body::Sun};

        EXPECT_NO_THROW(firstSunEphemeris.accessFrame());
        EXPECT_NO_THROW(secondSunEphemeris.accessFrame());

        EXPECT_EQ(firstSunEphemeris.accessFrame()->getName(), secondSunEphemeris.accessFrame()->getName());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Ephemeris_SunMoonAnalytical, Clone)
{
    {
        const SunMoonAnalytical sunEphemeris = {SunMoonAnalytical::Body::Sun};

        const SunMoonAnalytical* clonedSunEphemerisPtr = sunEphemeris.clone();

        EXPECT_TRUE(clonedSunEphemerisPtr != nullptr);
        EXPECT_EQ(SunMoonAnalytical::Body::Sun, clonedSunEphemerisPtr->getBody());

        delete clonedSunEphemerisPtr;
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Ephemeris_SunMoonAnalytical, IsDefined)
{
    {
        const SunMoonAnalytical sunEphemeris = {SunMoonAnalytical::Body::Sun};

        EXPECT_TRUE(sunEphemeris.isDefined());
    }

    {
        const SunMoonAnalytical moonEphemeris = {SunMoonAnalytical::Body::Moon};

        EXPECT_TRUE(moonEphemeris.isDefined());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Ephemeris_SunMoonAnalytical, AccessFrame)
{
    {
        const SunMoonAnalytical sunEphemeris = {SunMoonAnalytical::Body::Sun};

        const Shared<const Frame> sunFrameSPtr = sunEphemeris.accessFrame();

        EXPECT_TRUE(sunFrameSPtr != nullptr);
        EXPECT_EQ("Sun (Analytical)", sunFrameSPtr->getName());
    }

    {
        const SunMoonAnalytical moonEphemeris = {SunMoonAnalytical::Body::Moon};

        const Shared<const Frame> moonFrameSPtr = moonEphemeris.accessFrame();

        EXPECT_TRUE(moonFrameSPtr != nullptr);
        EXPECT_EQ("Moon (Analytical)", moonFrameSPtr->getName());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Ephemeris_SunMoonAnalytical, GetBody)
{
    {
        EXPECT_EQ(SunMoonAnalytical::Body::Sun, SunMoonAnalytical(SunMoonAnalytical::Body::Sun).getBody());
        EXPECT_EQ(SunMoonAnalytical::Body::Moon, SunMoonAnalytical(SunMoonAnalytical::Body::Moon).getBody());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Ephemeris_SunMoonAnalytical, StringFromBody)
{
    {
        EXPECT_EQ("Sun", SunMoonAnalytical::StringFromBody(SunMoonAnalytical::Body::Sun));
        EXPECT_EQ("Moon", SunMoonAnalytical::StringFromBody(SunMoonAnalytical::Body::Moon));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Ephemeris_SunMoonAnalytical, SunPositionVersusSpice)
{
    {
        this->loadSpiceKernels();

        const SunMoonAnalytical sunEphemeris = {SunMoonAnalytical::Body::Sun};

        const Shared<const Frame> analyticalFrameSPtr = sunEphemeris.accessFrame();

        const Sun sunSpice = Sun::Default();

        for (const auto& instant : ComparisonInstants())
        {
            const Vector3d x_GCRF_analytical =
                analyticalFrameSPtr->getOriginIn(Frame::GCRF(), instant).getCoordinates();
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

TEST_F(OpenSpaceToolkit_Physics_Environment_Ephemeris_SunMoonAnalytical, MoonPositionVersusSpice)
{
    {
        this->loadSpiceKernels();

        const SunMoonAnalytical moonEphemeris = {SunMoonAnalytical::Body::Moon};

        const Shared<const Frame> analyticalFrameSPtr = moonEphemeris.accessFrame();

        const Moon moonSpice = Moon::Default();

        for (const auto& instant : ComparisonInstants())
        {
            const Vector3d x_GCRF_analytical =
                analyticalFrameSPtr->getOriginIn(Frame::GCRF(), instant).getCoordinates();
            const Vector3d x_GCRF_spice = moonSpice.getPositionIn(Frame::GCRF(), instant).getCoordinates();

            const Real angularSeparation_deg = ComputeAngularSeparation_deg(x_GCRF_analytical, x_GCRF_spice);
            const Real relativeDistanceError =
                std::abs(x_GCRF_analytical.norm() - x_GCRF_spice.norm()) / x_GCRF_spice.norm();

            EXPECT_LT(angularSeparation_deg, 0.5) << String::Format(
                "{}: angular separation = {} [deg]", instant.toString(), angularSeparation_deg.toString()
            );
            EXPECT_LT(relativeDistanceError, 0.015) << String::Format(
                "{}: relative distance error = {}", instant.toString(), relativeDistanceError.toString()
            );
        }
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Ephemeris_SunMoonAnalytical, SunVelocityVersusSpice)
{
    {
        this->loadSpiceKernels();

        const SunMoonAnalytical sunEphemeris = {SunMoonAnalytical::Body::Sun};

        const Shared<const Frame> analyticalFrameSPtr = sunEphemeris.accessFrame();

        const Sun sunSpice = Sun::Default();

        for (const auto& instant : ComparisonInstants())
        {
            const Vector3d v_GCRF_analytical =
                analyticalFrameSPtr->getVelocityIn(Frame::GCRF(), instant).getCoordinates();
            const Vector3d v_GCRF_spice = sunSpice.getVelocityIn(Frame::GCRF(), instant).getCoordinates();

            const Real relativeVelocityError = (v_GCRF_analytical - v_GCRF_spice).norm() / v_GCRF_spice.norm();

            EXPECT_LT(relativeVelocityError, 0.05) << String::Format(
                "{}: relative velocity error = {}", instant.toString(), relativeVelocityError.toString()
            );
        }
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Ephemeris_SunMoonAnalytical, SunAnalytical)
{
    {
        EXPECT_NO_THROW(Sun::Analytical());
    }

    {
        const Sun sun = Sun::Analytical();

        const Instant instant = Instant::DateTime(DateTime(2024, 1, 1, 0, 0, 0), Scale::UTC);

        EXPECT_TRUE(sun.getPositionIn(Frame::GCRF(), instant).isDefined());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Ephemeris_SunMoonAnalytical, MoonAnalytical)
{
    {
        EXPECT_NO_THROW(Moon::Analytical());
    }

    {
        const Moon moon = Moon::Analytical();

        const Instant instant = Instant::DateTime(DateTime(2024, 1, 1, 0, 0, 0), Scale::UTC);

        EXPECT_TRUE(moon.getPositionIn(Frame::GCRF(), instant).isDefined());
    }
}
