/// Apache License 2.0

#include <regex>

#include <OpenSpaceToolkit/Core/Containers/Array.hpp>
#include <OpenSpaceToolkit/Core/Containers/Map.hpp>
#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Types/Integer.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/RotationMatrix.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/Dynamic.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Ephemerides/SPICE/Engine.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Ephemerides/SPICE/Manager.hpp>

extern "C"
{
#include "cspice/SpiceUsr.h"
#include "cspice/SpiceZfc.h"
}

namespace ostk
{
namespace physics
{
namespace env
{
namespace ephem
{
namespace spice
{

static void handleException()
{
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/req/error.html

    char shortMessage[256];
    char longMessage[1024];

    memset(shortMessage, 0x00, 256);
    memset(longMessage, 0x00, 1024);

    getmsg_c("SHORT", 256, shortMessage);
    getmsg_c("LONG", 1024, longMessage);

    // Reset the CSPICE error status to a value of "no error
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/reset_c.html

    reset_c();
    clpool_c();

    throw ostk::core::error::RuntimeError("SPICE exception: [{}] [{}].", shortMessage, longMessage);
}

std::ostream& operator<<(std::ostream& anOutputStream, const Engine& anEngine)
{
    ostk::core::utils::Print::Header(anOutputStream, "SPICE :: Engine");

    const std::lock_guard<std::mutex> lock {anEngine.mutex_};

    SpiceInt kernelCount = 0;

    ktotal_c("ALL", &kernelCount);

    if (failed_c())
    {
        handleException();
    }

    if (kernelCount > 0)
    {
        for (SpiceInt kernelIndex = 0; kernelIndex < kernelCount; ++kernelIndex)
        {
            // Return data for the nth kernel that is among a list of specified kernel types
            // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/kdata_c.html

            SpiceChar fileName[256];
            SpiceChar fileType[81];
            SpiceChar fileSource[256];
            SpiceInt handle = 0;
            SpiceBoolean found = SPICEFALSE;

            kdata_c(kernelIndex, "ALL", 256, 81, 256, fileName, fileType, fileSource, &handle, &found);

            if (failed_c())
            {
                handleException();
            }

            if (found)
            {
                ostk::core::utils::Print::Line(anOutputStream) << fileName;
            }
        }
    }
    else
    {
        ostk::core::utils::Print::Line(anOutputStream) << "No kernel loaded.";
    }

    ostk::core::utils::Print::Footer(anOutputStream);

    return anOutputStream;
}

bool Engine::isKernelLoaded(const Kernel& aKernel) const
{
    if (!aKernel.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Kernel");
    }

    const std::lock_guard<std::mutex> lock {mutex_};

    return this->isKernelLoaded_(aKernel);
}

Engine::Mode Engine::getMode() const
{
    const std::lock_guard<std::mutex> lock {mutex_};

    return mode_;
}

Shared<const Frame> Engine::getFrameOf(const SPICE::Object& aSpiceObject) const
{
    using DynamicProvider = ostk::physics::coord::frame::provider::Dynamic;

    const String frameName = String::Format("{} (SPICE)", SPICE::StringFromObject(aSpiceObject));
    const String objectIdentifier = Engine::SpiceIdentifierFromSpiceObject(aSpiceObject);
    const String spiceFrameName = Engine::FrameNameFromSpiceObject(aSpiceObject);

    if (const auto frameSPtr = Frame::WithName(frameName))
    {
        return frameSPtr;
    }

    const Shared<const DynamicProvider> transformProviderSPtr = std::make_shared<const DynamicProvider>(
        [objectIdentifier, spiceFrameName](const Instant& anInstant) -> Transform
        {
            return Engine::Get().getTransformAt(objectIdentifier, spiceFrameName, anInstant);
        }
    );

    return Frame::Construct(frameName, false, Frame::GCRF(), transformProviderSPtr);
}

void Engine::setMode(const Engine::Mode& aMode)
{
    const std::lock_guard<std::mutex> lock {mutex_};

    mode_ = aMode;
}

void Engine::loadKernel(const Kernel& aKernel)
{
    if (!aKernel.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Kernel");
    }

    const std::lock_guard<std::mutex> lock {mutex_};

    this->loadKernel_(aKernel);
}

void Engine::unloadKernel(const Kernel& aKernel)
{
    if (!aKernel.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Kernel");
    }

    const std::lock_guard<std::mutex> lock {mutex_};

    this->unloadKernel_(aKernel);
}

void Engine::reset()
{
    const std::lock_guard<std::mutex> lock {mutex_};

    earthKernelCache_.clear();
    earthKernelCacheIndex_ = 0;

    kernelSet_.clear();

    // Unload all kernels, clear the kernel pool, and re-initialize the subsystem
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/kclear_c.html

    kclear_c();

    this->setup();
}

Engine& Engine::Get()
{
    static Engine engine;

    return engine;
}

Engine::Mode Engine::DefaultMode()
{
    static const Engine::Mode defaultMode = OSTK_PHYSICS_ENVIRONMENT_EPHEMERIDES_SPICE_ENGINE_MODE;

    if (const char* modeString = std::getenv("OSTK_PHYSICS_ENVIRONMENT_EPHEMERIDES_SPICE_ENGINE_MODE"))
    {
        if (strcmp(modeString, "Manual") == 0)
        {
            return Engine::Mode::Manual;
        }
        else if (strcmp(modeString, "Automatic") == 0)
        {
            return Engine::Mode::Automatic;
        }
        else
        {
            throw ostk::core::error::runtime::Wrong("Mode", modeString);
        }
    }

    return defaultMode;
}

Array<Kernel> Engine::DefaultKernels(const Directory& aLocalRepository)
{
    // Use regex to pull Earth body shape and orientation kernels, as the file name can be updated.

    static const Array<Kernel> defaultKernels = {

        Manager::Get().findKernel("latest_leapseconds.tls"),  // Leap seconds
        Manager::Get().findKernel("de430.bsp"),               // Ephemeris
        Manager::Get().findKernel("pck[0-9]*\\.tpc"),         // System body shape and orientation constants
        Manager::Get().findKernel("earth_assoc_itrf93.tf"),   // Associates Earth to the ITRF93 frame
        Manager::Get().findKernel("earth\\_200101\\_[0-9]*\\_predict\\.bpc"),  // Earth orientation
        Manager::Get().findKernel("moon_080317.tf"),
        Manager::Get().findKernel("moon_assoc_me.tf"),
        Manager::Get().findKernel("moon_pa_de421_1900-2050.bpc")
    };

    return defaultKernels;
}

Engine::Engine(const Engine::Mode& aMode)
    : mode_(aMode),
      earthKernelCache_(Array<Pair<Interval, const Kernel*>>::Empty()),
      earthKernelCacheIndex_(0)
{
    this->setup();
}

bool Engine::isKernelLoaded_(const Kernel& aKernel) const
{
    return kernelSet_.find(aKernel) != kernelSet_.end();
}

Transform Engine::getTransformAt(const String& aSpiceIdentifier, const String& aFrameName, const Instant& anInstant)
    const
{
    using ostk::math::obj::Vector3d;
    using ostk::math::obj::Matrix3d;
    using ostk::math::geom::d3::trf::rot::Quaternion;
    using ostk::math::geom::d3::trf::rot::RotationMatrix;

    using ostk::physics::time::Scale;

    // Load required kernels

    this->manageKernels(aSpiceIdentifier, anInstant);

    // Time

    const SpiceDouble ephemerisTime = unitim_c(anInstant.getJulianDate(Scale::TT), "JDTDB", "ET");

    if (failed_c())
    {
        handleException();
    }

    // Position & Velocity

    SpiceDouble lt;
    SpiceDouble state[6];

    spkezr_c(aSpiceIdentifier.data(), ephemerisTime, "J2000", "NONE", "earth", state, &lt);

    if (failed_c())
    {
        handleException();
    }

    const Vector3d x_BODY_GCRF = {state[0] * 1e3, state[1] * 1e3, state[2] * 1e3};
    const Vector3d v_BODY_GCRF = {state[3] * 1e3, state[4] * 1e3, state[5] * 1e3};

    // Orientation

    SpiceDouble stateTransformationMatrix[6][6];

    sxform_c(aFrameName.data(), "J2000", ephemerisTime, stateTransformationMatrix);

    if (failed_c())
    {
        handleException();
    }

    SpiceDouble rotationMatrix[3][3];
    SpiceDouble angularVelocity[3];

    xf2rav_c(stateTransformationMatrix, rotationMatrix, angularVelocity);

    if (failed_c())
    {
        handleException();
    }

    const RotationMatrix dcm_GCRF_BODY = {
        rotationMatrix[0][0],
        rotationMatrix[0][1],
        rotationMatrix[0][2],
        rotationMatrix[1][0],
        rotationMatrix[1][1],
        rotationMatrix[1][2],
        rotationMatrix[2][0],
        rotationMatrix[2][1],
        rotationMatrix[2][2]
    };

    const Quaternion q_BODY_GCRF = Quaternion::RotationMatrix(dcm_GCRF_BODY).toConjugate().toNormalized().rectify();

    // Angular velocity

    const Vector3d w_GCRF_BODY_in_BODY = {angularVelocity[0], angularVelocity[1], angularVelocity[2]};
    const Vector3d w_BODY_GCRF_in_BODY = -w_GCRF_BODY_in_BODY;

    return {anInstant, -x_BODY_GCRF, -v_BODY_GCRF, q_BODY_GCRF, w_BODY_GCRF_in_BODY, Transform::Type::Passive};
}

void Engine::setup()
{
    // Set error action
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/erract_c.html

    erract_c("SET", 4096, (SpiceChar*)"RETURN");

    // Set the name of the current output device for error messages
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/errdev_c.html

    errdev_c("SET", 4096, (SpiceChar*)"NULL");

    if (mode_ == Engine::Mode::Automatic)
    {
        Directory kernelDirectory = Manager::Get().getLocalRepository();
        if (!kernelDirectory.exists())
        {
            kernelDirectory.create();
        }

        // Load default kernels

        for (const auto& kernel : Engine::DefaultKernels(kernelDirectory))
        {
            this->loadKernel_(kernel);
        }
    }
}

void Engine::manageKernels(const String& aSpiceIdentifier, const Instant& anInstant) const
{
    if (mode_ == Engine::Mode::Automatic)
    {
        // Load kernel (if necessary)

        if (aSpiceIdentifier == "399")  // Earth
        {
            bool earthKernelFound = false;

            if (!earthKernelCache_.isEmpty())
            {
                if (earthKernelCache_.at(earthKernelCacheIndex_).first.contains(anInstant))
                {
                    earthKernelFound = true;
                }
                else
                {
                    for (earthKernelCacheIndex_ = 0; earthKernelCacheIndex_ < earthKernelCache_.getSize();
                         ++earthKernelCacheIndex_)
                    {
                        if (earthKernelCache_.at(earthKernelCacheIndex_).first.contains(anInstant))
                        {
                            earthKernelFound = true;

                            break;
                        }
                    }
                }
            }

            if (!earthKernelFound)
            {
                const std::function<void(const bool)> loadEarthKernel = [&](const bool isFirstTime) -> void
                {
                    (void)isFirstTime;

                    // List available Earth kernels

                    const Array<Kernel> earthKernels =
                        Manager::Get().fetchMatchingKernels(std::regex("^earth_000101_[\\d]{6}_[\\d]{6}.bpc$"));

                    if (!earthKernels.isEmpty())
                    {
                        const_cast<Engine*>(this)->loadKernel_(earthKernels.accessFirst()
                        );  // [TBM] The first kernel is not necessarily the correct one
                    }
                    else
                    {
                        throw ostk::core::error::RuntimeError(
                            "Cannot fetch BPC Earth kernel at [{}].", anInstant.toString()
                        );
                    }
                };

                loadEarthKernel(true);
            }
        }
    }
}

void Engine::loadKernel_(const Kernel& aKernel)
{
    if (this->isKernelLoaded_(aKernel))
    {
        return;
    }

    const File kernelFile = aKernel.getFile();

    if (!kernelFile.exists())
    {
        if (mode_ == Engine::Mode::Automatic)
        {
            // Fetch kernel

            Manager::Get().fetchKernel(aKernel);
        }
        else
        {
            throw ostk::core::error::RuntimeError("Kernel file [{}] does not exist.", kernelFile.toString());
        }
    }

    const String kernelFilePathString = kernelFile.getPath().toString();

    const ConstSpiceChar* kernelFilePathSpiceChar = kernelFilePathString.data();

    furnsh_c(kernelFilePathSpiceChar);

    if (failed_c())
    {
        handleException();
    }

    kernelSet_.insert(aKernel);

    this->updateEarthKernelCache();
}

void Engine::unloadKernel_(const Kernel& aKernel)
{
    if (!this->isKernelLoaded_(aKernel))
    {
        return;
    }

    const File kernelFile = aKernel.getFile();

    const String kernelFilePathString = kernelFile.getPath().toString();

    const ConstSpiceChar* kernelFilePathSpiceChar = kernelFilePathString.data();

    unload_c(kernelFilePathSpiceChar);

    if (failed_c())
    {
        handleException();
    }

    kernelSet_.erase(aKernel);

    // Reset cache

    this->updateEarthKernelCache();
}

void Engine::updateEarthKernelCache()
{
    using ostk::core::types::Uint8;
    using ostk::core::types::Uint16;
    using ostk::core::types::Integer;

    using ostk::physics::time::Scale;
    using ostk::physics::time::Date;
    using ostk::physics::time::Time;
    using ostk::physics::time::DateTime;

    earthKernelCache_.clear();
    earthKernelCacheIndex_ = 0;

    for (const auto& kernel : kernelSet_)
    {
        if (kernel.getType() == Kernel::Type::BPCK)
        {
            if (kernel.getName().getHead(13) == "earth_000101_")
            {
                // earth_000101_190103_181012.bpc

                static const Instant startInstant = Instant::DateTime(DateTime(2000, 1, 1, 0, 0, 0), Scale::UTC);

                const String endDateString = kernel.getName().getSubstring(20, 6);

                const Integer endYear = Integer::Parse(endDateString.getSubstring(0, 2));
                const Integer endMonth = Integer::Parse(endDateString.getSubstring(2, 2));
                const Integer endDay = Integer::Parse(endDateString.getSubstring(4, 2));

                const Date endDate = {
                    static_cast<Uint16>(2000 + endYear), static_cast<Uint8>(endMonth), static_cast<Uint8>(endDay)
                };

                const Instant endInstant = Instant::DateTime(DateTime(endDate, Time::Midnight()), Scale::UTC);

                const Interval interval = Interval::Closed(startInstant, endInstant);

                earthKernelCache_.add({interval, &kernel});
            }
        }
    }
}

String Engine::SpiceIdentifierFromSpiceObject(const SPICE::Object& aSpiceObject)
{
    using ostk::core::ctnr::Map;

    static const Map<SPICE::Object, String> identifierMap = {
        {SPICE::Object::Sun, "10"},
        {SPICE::Object::Mercury, "1"},
        {SPICE::Object::Venus, "2"},
        {SPICE::Object::Earth, "399"},
        {SPICE::Object::Moon, "301"},
        {SPICE::Object::Mars, "4"},
        {SPICE::Object::Jupiter, "5"},
        {SPICE::Object::Saturn, "6"},
        {SPICE::Object::Uranus, "7"},
        {SPICE::Object::Neptune, "8"}
    };

    return identifierMap.at(aSpiceObject);
}

String Engine::FrameNameFromSpiceObject(const SPICE::Object& aSpiceObject)
{
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/req/frames.html#Appendix.%20%60%60Built%20in''%20PCK-Based%20IAU%20Body-Fixed%20Reference%20Frames
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/Tutorials/pdf/individual_docs/23_lunar-earth_pck-fk.pdf

    using ostk::core::ctnr::Map;

    static const Map<SPICE::Object, String> frameNameMap = {
        {SPICE::Object::Sun, "IAU_SUN"},
        {SPICE::Object::Mercury, "IAU_MERCURY"},
        {SPICE::Object::Venus, "IAU_VENUS"},
        {SPICE::Object::Earth, "ITRF93"},
        {SPICE::Object::Moon, "MOON_ME"},
        {SPICE::Object::Mars, "IAU_MARS"},
        {SPICE::Object::Jupiter, "IAU_JUPITER"},
        {SPICE::Object::Saturn, "IAU_SATURN"},
        {SPICE::Object::Uranus, "IAU_URANUS"},
        {SPICE::Object::Neptune, "IAU_NEPTUNE"}
    };

    return frameNameMap.at(aSpiceObject);
}

}  // namespace spice
}  // namespace ephem
}  // namespace env
}  // namespace physics
}  // namespace ostk
