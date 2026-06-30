/// Apache License 2.0

#include <gtest/gtest.h>

#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>
#include <OpenSpaceToolkit/Core/Type/Shared.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Ephemeris/SPICE/Engine.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Ephemeris/SPICE/Kernel.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Ephemeris/SPICE/Manager.hpp>

using ostk::core::container::Array;
using ostk::core::filesystem::File;
using ostk::core::filesystem::Path;
using ostk::core::type::Shared;
using ostk::core::type::String;

using ostk::physics::coordinate::Frame;
using ostk::physics::environment::ephemeris::SPICE;
using ostk::physics::environment::ephemeris::spice::Engine;
using ostk::physics::environment::ephemeris::spice::Kernel;
using ostk::physics::environment::ephemeris::spice::Manager;

class OpenSpaceToolkit_Physics_Environment_Ephemeris_SPICE_Engine : public ::testing::Test
{
   protected:
    Engine& engine_;
    Kernel kernel_;
    Manager& manager_;

    OpenSpaceToolkit_Physics_Environment_Ephemeris_SPICE_Engine()
        : engine_(Engine::Get()),
          kernel_(Kernel::File(
              File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Ephemeris/SPICE/de430.bsp"))
          )),
          manager_(Manager::Get())
    {
    }

    void SetUp() override
    {
        engine_.loadKernel(kernel_);
    }

    void TearDown() override
    {
        engine_.unloadKernel(kernel_);
        manager_.setMode(Manager::Mode::Automatic);
    }
};

TEST_F(OpenSpaceToolkit_Physics_Environment_Ephemeris_SPICE_Engine, IsKernelLoaded)
{
    {
        EXPECT_TRUE(engine_.isKernelLoaded(kernel_));
    }

    {
        EXPECT_TRUE(engine_.isKernelLoaded("de430.bsp"));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Ephemeris_SPICE_Engine, GetFrameOf)
{
    {
        Shared<const Frame> frame = engine_.getFrameOf(SPICE::Object::Earth);

        EXPECT_TRUE(frame != nullptr);
        EXPECT_EQ(frame->getName(), "Earth (SPICE)");

        Frame::Destruct("Earth (SPICE)");
    }

    {
        manager_.setMode(Manager::Mode::Manual);
        engine_.reset();

        Shared<const Frame> frame = engine_.getFrameOf(SPICE::Object::Earth);

        EXPECT_TRUE(frame != nullptr);
        EXPECT_EQ(frame->getName(), "Earth (SPICE)");

        Frame::Destruct("Earth (SPICE)");
    }

    // Test automatic kernel management
    {
        manager_.setMode(Manager::Mode::Automatic);
        engine_.reset();

        const Array<Kernel> kernelsBefore = engine_.getKernels();

        engine_.unloadAllKernels();

        // When no Earth kernels are loaded
        // Call getFrameOf for Earth - should trigger automatic kernel fetching
        Shared<const Frame> earthFrame = engine_.getFrameOf(SPICE::Object::Earth);

        EXPECT_TRUE(earthFrame != nullptr);
        EXPECT_EQ(earthFrame->getName(), "Earth (SPICE)");

        EXPECT_EQ(engine_.getKernels().getSize(), 1);
        EXPECT_EQ(engine_.getKernels().accessFirst().getName(), "earth_latest_high_prec.bpc");

        Frame::Destruct("Earth (SPICE)");
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Ephemeris_SPICE_Engine, GetKernels)
{
    const Array<Kernel> kernels = engine_.getKernels();
    EXPECT_TRUE(kernels.contains(kernel_));
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Ephemeris_SPICE_Engine, LoadKernel)
{
    {
        EXPECT_NO_THROW(engine_.loadKernel(kernel_));
        EXPECT_TRUE(engine_.isKernelLoaded(kernel_));
    }

    {
        engine_.reset();
        const Kernel newKernel = Kernel::File(File::Path(Path::Parse("earth_assoc_itrf93.tf")));

        // automatic
        {
            EXPECT_NO_THROW(engine_.loadKernel(newKernel));
        }

        // manual
        {
            manager_.setMode(Manager::Mode::Manual);
            engine_.reset();

            EXPECT_ANY_THROW(engine_.loadKernel(newKernel));
        }
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Ephemeris_SPICE_Engine, UnloadKernel)
{
    EXPECT_TRUE(engine_.isKernelLoaded(kernel_));

    EXPECT_NO_THROW(engine_.unloadKernel(kernel_));
    EXPECT_FALSE(engine_.isKernelLoaded(kernel_));
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Ephemeris_SPICE_Engine, UnloadAllKernels)
{
    EXPECT_TRUE(engine_.isKernelLoaded(kernel_));

    EXPECT_NO_THROW(engine_.unloadAllKernels());
    EXPECT_FALSE(engine_.isKernelLoaded(kernel_));
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Ephemeris_SPICE_Engine, Reset)
{
    EXPECT_TRUE(engine_.isKernelLoaded(kernel_));

    engine_.reset();
    EXPECT_FALSE(engine_.isKernelLoaded(kernel_));
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Ephemeris_SPICE_Engine, DefaultKernels)
{
    const Array<Kernel> kernels = Engine::DefaultKernels();

    for (const auto& kernel : kernels)
    {
        EXPECT_TRUE(kernel.isDefined());
    }
}
