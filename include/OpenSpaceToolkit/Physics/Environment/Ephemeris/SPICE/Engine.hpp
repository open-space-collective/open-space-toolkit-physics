/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Environment_Ephemeris_SPICE_Engine__
#define __OpenSpaceToolkit_Physics_Environment_Ephemeris_SPICE_Engine__

#include <mutex>
#include <unordered_set>

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Container/Pair.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Directory.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Path.hpp>
#include <OpenSpaceToolkit/Core/Type/Index.hpp>
#include <OpenSpaceToolkit/Core/Type/Shared.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/RotationMatrix.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Transform.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Ephemeris/SPICE.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Ephemeris/SPICE/Kernel.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Time/Interval.hpp>

namespace ostk
{
namespace physics
{
namespace environment
{
namespace ephemeris
{
namespace spice
{

using ostk::core::type::Shared;
using IndexType = ostk::core::type::Index;
using ostk::core::container::Array;
using ostk::core::container::Pair;
using ostk::core::filesystem::Directory;
using ostk::core::filesystem::File;
using ostk::core::filesystem::Path;
using ostk::core::type::String;

using ostk::mathematics::geometry::d3::transformation::rotation::RotationMatrix;

using ostk::physics::coordinate::Frame;
using ostk::physics::coordinate::Transform;
using ostk::physics::environment::ephemeris::SPICE;
using ostk::physics::environment::ephemeris::spice::Kernel;
using ostk::physics::time::Instant;
using ostk::physics::time::Interval;

/// @brief                      SPICE Toolkit engine

class Engine
{
   public:
    /// @brief              Copy constructor (deleted)

    Engine(const Engine& aSpiceEngine) = delete;

    /// @brief              Copy assignment operator (deleted)

    Engine& operator=(const Engine& aSpiceEngine) = delete;

    /// @brief                  move constructor (deleted)

    Engine(Engine&&) = delete;

    /// @brief                  move assignment operator (deleted)

    Engine& operator=(Engine&&) = delete;

    /// @brief              Output stream operator
    ///
    /// @param              [in] anOutputStream An output stream
    /// @param              [in] anEngine A SPICE engine
    /// @return             A reference to output stream

    friend std::ostream& operator<<(std::ostream& anOutputStream, const Engine& anEngine);

    /// @brief              Get engine singleton
    ///
    /// @return             Reference to engine

    static Engine& Get();

    /// @brief              Reset engine
    ///
    ///                     Unload all kernels, clears cache and re-sets up the engine.

    void reset();

    /// @brief              Get frame of SPICE object
    ///
    /// @param              [in] A SPICE object
    /// @return             Frame of SPICE object

    Shared<const Frame> getFrameOf(const SPICE::Object& aSpiceObject) const;

    /// @brief              Get kernels
    ///
    /// @return             Kernels

    Array<Kernel> getKernels() const;

    /// @brief              Returns true if kernel is loaded
    ///
    /// @param              [in] aKernel A kernel
    /// @return             True if kernel is loaded

    bool isKernelLoaded(const Kernel& aKernel) const;

    /// @brief              Returns true if kernel is loaded
    ///
    /// @param              [in] aRegexString A regex string
    /// @return             True if kernel is loaded

    bool isKernelLoaded(const String& aRegexString) const;

    /// @brief              Load kernel
    ///
    /// @param              [in] aKernel A kernel

    void loadKernel(const Kernel& aKernel);

    /// @brief              Unload kernel
    ///
    /// @param              [in] aKernel

    void unloadKernel(const Kernel& aKernel);

    /// @brief              Unload all kernels
    ///
    ///                     Unloads all kernels and clears the cache.

    void unloadAllKernels();

    /// @brief              Get default kernels
    ///
    /// @return             Default kernels

    static Array<Kernel> DefaultKernels();

   private:
    std::unordered_set<Kernel> kernelSet_;

    mutable std::mutex mutex_;

    Engine();

    bool isKernelLoaded_(const Kernel& aKernel) const;

    bool isKernelLoaded_(const String& aRegexString) const;

    Transform getTransformAt(const String& aSpiceIdentifier, const String& aFrameName, const Instant& anInstant) const;

    void setup();

    void manageKernels(const String& aSpiceIdentifier) const;

    void loadKernel_(const Kernel& aKernel);

    void unloadKernel_(const Kernel& aKernel);

    static String SpiceIdentifierFromSpiceObject(const SPICE::Object& aSpiceObject);

    static String FrameNameFromSpiceObject(const SPICE::Object& aSpiceObject);
};

}  // namespace spice
}  // namespace ephemeris
}  // namespace environment
}  // namespace physics
}  // namespace ostk

#endif
