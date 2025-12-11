/// Apache License 2.0

#include <regex>

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Container/Map.hpp>
#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Type/Integer.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/Dynamic.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Ephemeris/SPICE/Engine.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Ephemeris/SPICE/Manager.hpp>

extern "C"
{
#include "cspice/SpiceUsr.h"
#include "cspice/SpiceZfc.h"
}

using ostk::core::type::String;

using ostk::mathematics::geometry::d3::transformation::rotation::Quaternion;
using ostk::mathematics::object::Matrix3d;
using ostk::mathematics::object::Vector3d;

using ostk::physics::time::Scale;

static const String earthHighPrecisionKernel = "earth_latest_high_prec.bpc";

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

    throw ostk::core::error::RuntimeError(
        "SPICE exception: [{}] [{}].", std::string(shortMessage), std::string(longMessage)
    );
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

Shared<const Frame> Engine::getFrameOf(const SPICE::Object& aSpiceObject) const
{
    using DynamicProvider = ostk::physics::coordinate::frame::provider::Dynamic;

    const String frameName = String::Format("{} (SPICE)", SPICE::StringFromObject(aSpiceObject));
    const String objectIdentifier = Engine::SpiceIdentifierFromSpiceObject(aSpiceObject);
    const String spiceFrameName = Engine::FrameNameFromSpiceObject(aSpiceObject);

    if (const auto frameSPtr = Frame::WithName(frameName))
    {
        return frameSPtr;
    }

    // Load required kernels

    this->manageKernels(objectIdentifier);

    const Shared<const DynamicProvider> transformProviderSPtr = std::make_shared<const DynamicProvider>(
        [objectIdentifier, spiceFrameName](const Instant& anInstant) -> Transform
        {
            return Engine::Get().getTransformAt(objectIdentifier, spiceFrameName, anInstant);
        }
    );

    return Frame::Construct(frameName, false, Frame::GCRF(), transformProviderSPtr);
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

Array<Kernel> Engine::DefaultKernels()
{
    // Use regex to pull Earth body shape and orientation kernels, as the file name can be updated.

    static const Array<Kernel> defaultKernels = {

        Manager::Get().findKernel("latest_leapseconds.tls"),              // Leap seconds
        Manager::Get().findKernel("de430.bsp"),                           // Ephemeris
        Manager::Get().findKernel("pck[0-9]*\\.tpc"),                     // System body shape and orientation constants
        Manager::Get().findKernel("earth_assoc_itrf93.tf"),               // Associates Earth to the ITRF93 frame
        Manager::Get().findKernel(earthHighPrecisionKernel),              // Earth orientation (high precision)
        Manager::Get().findKernel("moon_080317.tf"),
        Manager::Get().findKernel("moon_assoc_me.tf"),
        Manager::Get().findKernel("moon_pa_de421_1900-2050.bpc")
    };

    return defaultKernels;
}

Engine::Engine()
{
    this->setup();
}

bool Engine::isKernelLoaded_(const Kernel& aKernel) const
{
    return kernelSet_.find(aKernel) != kernelSet_.end();
}

bool Engine::isKernelLoaded_(const String& aRegexString) const
{
    for (const auto& kernel : kernelSet_)
    {
        if (std::regex_match(kernel.getName(), std::regex(aRegexString)))
        {
            return true;
        }
    }
    return false;
}

Transform Engine::getTransformAt(const String& aSpiceIdentifier, const String& aFrameName, const Instant& anInstant)
    const
{
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

    // Load default kernels

    for (const auto& kernel : Engine::DefaultKernels())
    {
        this->loadKernel_(kernel);
    }
}

void Engine::manageKernels(const String& aSpiceIdentifier) const
{
    if (Manager::Get().getMode() == Manager::Mode::Automatic)
    {
        if (aSpiceIdentifier == "399")  // Earth
        {
            if (!isKernelLoaded_(earthHighPrecisionKernel))
            {
                const Array<Kernel> earthKernels =
                    Manager::Get().fetchMatchingKernels(earthHighPrecisionKernel);
                if (!earthKernels.isEmpty())
                {
                    const_cast<Engine*>(this)->loadKernel_(earthKernels.accessFirst()
                    );  // Should only be one
                }
                else
                {
                    throw ostk::core::error::RuntimeError("Cannot fetch BPC Earth kernel.");
                }
            }
        }
        else
        {
            if (!isKernelLoaded_("de[0-9]+\\.bsp"))
            {
                const Array<Kernel> planetaryKernels =
                    Manager::Get().fetchMatchingKernels("de[0-9]+\\.bsp");
                if (!planetaryKernels.isEmpty())
                {
                    const_cast<Engine*>(this)->loadKernel_(planetaryKernels.accessFirst());
                }
                else
                {
                    throw ostk::core::error::RuntimeError("Cannot fetch DE kernel.");
                }
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

    File kernelFile = aKernel.getFile();

    if (!kernelFile.exists())
    {
        if (Manager::Get().getMode() == Manager::Mode::Automatic)
        {
            Manager::Get().fetchKernel(aKernel);
            const Path filePath = Manager::Get().getLocalRepository().getPath() + Path::Parse(aKernel.getName());
            kernelFile = File::Path(filePath);
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

}

String Engine::SpiceIdentifierFromSpiceObject(const SPICE::Object& aSpiceObject)
{
    using ostk::core::container::Map;

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

    using ostk::core::container::Map;

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
}  // namespace ephemeris
}  // namespace environment
}  // namespace physics
}  // namespace ostk
