////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Environment/Ephemerides/SPICE/Engine.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Environment/Ephemerides/SPICE/Engine.hpp>
#include <Library/Physics/Coordinate/Frame/Providers/Dynamic.hpp>

#include <Library/Mathematics/Geometry/3D/Transformations/Rotations/RotationMatrix.hpp>

#include <Library/Core/Containers/Map.hpp>
#include <Library/Core/Containers/Array.hpp>
#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

extern "C"
{

    #include "cspice/SpiceZfc.h"
    #include "cspice/SpiceUsr.h"

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{
namespace env
{
namespace ephem
{
namespace spice
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void                     handleException                             ( )
{

    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/req/error.html

    char shortMessage[256] ;
    char longMessage[1024] ;

    memset(shortMessage, 0x00, 256) ;
    memset(longMessage, 0x00, 1024) ;

    getmsg_c("SHORT", 256, shortMessage) ;
    getmsg_c("LONG", 1024, longMessage) ;

    throw library::core::error::RuntimeError("SPICE exception: [{}] [{}].", shortMessage, longMessage) ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Shared<const Frame>             Engine::getFrameOf                          (   const   SPICE::Object&              aSpiceObject                                ) const
{

    using DynamicProvider = library::physics::coord::frame::provider::Dynamic ;

    const String frameName = String::Format("{} (SPICE)", SPICE::StringFromObject(aSpiceObject)) ;
    const String objectIdentifier = Engine::SpiceIdentifierFromSpiceObject(aSpiceObject) ;
    const String spiceFrameName = Engine::FrameNameFromSpiceObject(aSpiceObject) ;

    if (const auto frameSPtr = Frame::WithName(frameName))
    {
        return frameSPtr ;
    }
    
    const Shared<const DynamicProvider> transformProviderSPtr = std::make_shared<const DynamicProvider>
    (
        [this, objectIdentifier, spiceFrameName] (const Instant& anInstant) -> Transform // [TBI] Use shared_from_this instead
        {
            return this->getTransformAt(objectIdentifier, spiceFrameName, anInstant) ;
        }
    ) ;

    const Shared<const Frame> frameSPtr = Frame::Construct(frameName, false, Frame::GCRF(), transformProviderSPtr) ;

    return frameSPtr ;

}

void                            Engine::loadKernel                          (   const   File&                       aKernelFile                                 )
{

    if (!aKernelFile.isDefined())
    {
        throw library::core::error::runtime::Undefined("Kernel file") ;
    }

    if (!aKernelFile.exists())
    {
        throw library::core::error::RuntimeError("Kernel file [{}] does not exist.", aKernelFile.toString()) ;
    }

    const String kernelFilePathString = aKernelFile.getPath().toString() ;

    const ConstSpiceChar* kernelFilePathSpiceChar = kernelFilePathString.data() ;

    furnsh_c(kernelFilePathSpiceChar) ;
		
    if (failed_c()) 
    {
        handleException() ;
    }

}

Engine&                         Engine::Get                                 ( )
{

    static Engine engine ;

    return engine ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Engine::Engine                              ( )
{

    this->setup() ;

}

Transform                       Engine::getTransformAt                      (   const   String&                     aSpiceIdentifier,
                                                                                const   String&                     aFrameName,
                                                                                const   Instant&                    anInstant                                   ) const
{

    using library::math::obj::Vector3d ;
    using library::math::obj::Matrix3d ;
    using library::math::geom::d3::trf::rot::Quaternion ;
    using library::math::geom::d3::trf::rot::RotationMatrix ;

    using library::physics::time::Scale ;

    const std::lock_guard<std::mutex> lock(mutex_) ; // [TBR] ?

    // Load kernel (if necessary)

    // [TBI]

    // Setup

    const SpiceDouble ephemerisTime = unitim_c(anInstant.getJulianDate(Scale::TT), "JDTDB", "ET") ;

    if (failed_c()) 
    {
        handleException() ;
    }

    // Position & Velocity

    SpiceDouble lt ;
    SpiceDouble state[6] ;

    #define ABCORR "NONE"
    #define FRAME "J2000"
    #define OBSERVER "earth"

    spkezr_c(aSpiceIdentifier.data(), ephemerisTime, FRAME, ABCORR, OBSERVER, state, &lt) ;
    
    if (failed_c()) 
    {
        handleException() ;
    }

    const Vector3d x_BODY_GCRF = { state[0] * 1e3, state[1] * 1e3, state[2] * 1e3 } ;
    const Vector3d v_BODY_GCRF = { state[3] * 1e3, state[4] * 1e3, state[5] * 1e3 } ;

    // Orientation

    SpiceDouble stateTransformationMatrix[6][6] ;

    sxform_c(aFrameName.data(), "J2000", ephemerisTime, stateTransformationMatrix) ;
    
    if (failed_c())
    {
        handleException() ;
    }

    SpiceDouble rotationMatrix[3][3] ;
    SpiceDouble angularVelocity[3] ;

    xf2rav_c(stateTransformationMatrix, rotationMatrix, angularVelocity) ;
    
    if (failed_c()) 
    {
        handleException() ;
    }

    const RotationMatrix dcm_GCRF_BODY = 
    {
        rotationMatrix[0][0], rotationMatrix[0][1], rotationMatrix[0][2],
        rotationMatrix[1][0], rotationMatrix[1][1], rotationMatrix[1][2],
        rotationMatrix[2][0], rotationMatrix[2][1], rotationMatrix[2][2]
    } ;

    const Quaternion q_BODY_GCRF = Quaternion::RotationMatrix(dcm_GCRF_BODY).toConjugate().toNormalized().rectify() ;

    // Angular velocity

    const Vector3d w_GCRF_BODY_in_BODY = { angularVelocity[0], angularVelocity[1], angularVelocity[2] } ;
    const Vector3d w_BODY_GCRF_in_BODY = -w_GCRF_BODY_in_BODY ;

    return { anInstant, -x_BODY_GCRF, -v_BODY_GCRF, q_BODY_GCRF, w_BODY_GCRF_in_BODY, Transform::Type::Passive } ;

}

void                            Engine::setup                               ( )
{

    using library::core::ctnr::Array ;

    // Set error action

    erract_c("SET", 4096, (SpiceChar*)"RETURN") ;

    // Load kernels [TBI]

    const Array<File> kernelFiles = 
    {
        File::Path(Path::Parse("/app/share/data/naif0012.tls")), // Leap seconds
        File::Path(Path::Parse("/app/share/data/de430.bsp")), // Ephemeris
        File::Path(Path::Parse("/app/share/data/pck00010.tpc")), // System body shape and orientation constants
        File::Path(Path::Parse("/app/share/data/earth_assoc_itrf93.tf")),
        File::Path(Path::Parse("/app/share/data/earth_070425_370426_predict.bpc")),
        File::Path(Path::Parse("/app/share/data/earth_000101_181204_180912.bpc")),
        File::Path(Path::Parse("/app/share/data/moon_080317.tf")),
        File::Path(Path::Parse("/app/share/data/moon_assoc_me.tf")),
        File::Path(Path::Parse("/app/share/data/moon_pa_de421_1900-2050.bpc"))
    } ;

    for (const auto& kernelFile : kernelFiles)
    {
        this->loadKernel(kernelFile) ;
    }

}

String                          Engine::SpiceIdentifierFromSpiceObject      (   const   SPICE::Object&              aSpiceObject                                )
{

    using library::core::ctnr::Map ;

    static const Map<SPICE::Object, String> identifierMap =
    {
        { SPICE::Object::Sun, "10" },
        { SPICE::Object::Mercury, "1" },
        { SPICE::Object::Venus, "2" },
        { SPICE::Object::Earth, "399" },
        { SPICE::Object::Moon, "301" },
        { SPICE::Object::Mars, "4" },
        { SPICE::Object::Jupiter, "5" },
        { SPICE::Object::Saturn, "6" },
        { SPICE::Object::Uranus, "7" },
        { SPICE::Object::Neptune, "8" }
    } ;

    return identifierMap.at(aSpiceObject) ;

}

String                          Engine::FrameNameFromSpiceObject            (   const   SPICE::Object&              aSpiceObject                                )
{

    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/req/frames.html#Appendix.%20%60%60Built%20in''%20PCK-Based%20IAU%20Body-Fixed%20Reference%20Frames
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/Tutorials/pdf/individual_docs/23_lunar-earth_pck-fk.pdf

    using library::core::ctnr::Map ;

    static const Map<SPICE::Object, String> frameNameMap =
    {
        { SPICE::Object::Sun, "IAU_SUN" },
        { SPICE::Object::Mercury, "IAU_MERCURY" },
        { SPICE::Object::Venus, "IAU_VENUS" },
        { SPICE::Object::Earth, "ITRF93" },
        { SPICE::Object::Moon, "MOON_ME" },
        { SPICE::Object::Mars, "IAU_MARS" },
        { SPICE::Object::Jupiter, "IAU_JUPITER" },
        { SPICE::Object::Saturn, "IAU_SATURN" },
        { SPICE::Object::Uranus, "IAU_URANUS" },
        { SPICE::Object::Neptune, "IAU_NEPTUNE" }
    } ;

    return frameNameMap.at(aSpiceObject) ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////