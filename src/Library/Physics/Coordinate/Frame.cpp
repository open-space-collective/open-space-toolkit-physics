////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Coordinate/Frame.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Coordinate/Frame/Providers/ITRF.hpp>
#include <Library/Physics/Coordinate/Frame/Providers/TIRF.hpp>
#include <Library/Physics/Coordinate/Frame/Providers/CIRF.hpp>
#include <Library/Physics/Coordinate/Frame/Providers/TEME.hpp>
#include <Library/Physics/Coordinate/Frame/Providers/GCRF.hpp>
#include <Library/Physics/Coordinate/Frame/Providers/Fixed.hpp>
#include <Library/Physics/Coordinate/Frame/Manager.hpp>
#include <Library/Physics/Coordinate/Frame.hpp>

#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

#include <iostream>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{
namespace coord
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using library::physics::coord::frame::Manager ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static Manager FrameManager ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Frame::Frame                                (   const   String&                     aName,
                                                                                        bool                        isQuasiInertial,
                                                                                const   Shared<const Frame>&        aParentFrame,
                                                                                const   Shared<Provider>&           aProvider                                   )
                                :   name_(aName),
                                    quasiInertial_(isQuasiInertial),
                                    parentFrameSPtr_(aParentFrame),
                                    providerSPtr_(aProvider)
{

    // std::cout << "Frame :: Frame () @ " << this << std::endl ;

}

                                Frame::Frame                                (   const   Frame&                      aFrame                                      )
                                :   name_(aFrame.name_),
                                    quasiInertial_(aFrame.quasiInertial_),
                                    parentFrameSPtr_(aFrame.parentFrameSPtr_),
                                    providerSPtr_(aFrame.providerSPtr_)
{

    // std::cout << "Frame :: Frame (const Frame&) @ " << &aFrame << " -> " << this << std::endl ;

}

                                Frame::~Frame                               ( )
{

    // std::cout << "Frame :: ~Frame @ " << this << std::endl ;

}

bool                            Frame::operator ==                          (   const   Frame&                      aFrame                                      ) const
{

    if ((!this->isDefined()) || (!aFrame.isDefined()))
    {
        return false ;
    }

    return (name_ == aFrame.name_)
        && (quasiInertial_ == aFrame.quasiInertial_)
        && (((parentFrameSPtr_ == nullptr) && (aFrame.parentFrameSPtr_ == nullptr)) || ((parentFrameSPtr_ != nullptr) && (aFrame.parentFrameSPtr_ != nullptr) && ((*parentFrameSPtr_) == (*aFrame.parentFrameSPtr_)))) ;

}

bool                            Frame::operator !=                          (   const   Frame&                      aFrame                                      ) const
{
    return !((*this) == aFrame) ;
}

std::ostream&                   operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Frame&                      aFrame                                      )
{

    library::core::utils::Print::Header(anOutputStream, "Frame") ;

    library::core::utils::Print::Line(anOutputStream) << "Name:" << (aFrame.isDefined() ? aFrame.getName() : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Quasi-inertial:" << (aFrame.isDefined() ? String::Format("{}", aFrame.isQuasiInertial()) : "Undefined") ;

    library::core::utils::Print::Footer(anOutputStream) ;

    return anOutputStream ;

}

bool                            Frame::isDefined                            ( ) const
{
    return (!name_.isEmpty()) && (providerSPtr_ != nullptr) ;
}

bool                            Frame::isQuasiInertial                      ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Frame") ;
    }
    
    return quasiInertial_ ;

}

bool                            Frame::hasParent                            ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Frame") ;
    }
    
    return parentFrameSPtr_ != nullptr ;

}

const Frame&                    Frame::accessParent                         ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Frame") ;
    }

    if (parentFrameSPtr_ == nullptr)
    {
        throw library::core::error::runtime::Undefined("Parent") ;
    }

    return *parentFrameSPtr_ ;

}

const Frame&                    Frame::accessAncestor                       (           Uint8                       anAncestorDegree                            ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Frame") ;
    }

    if (anAncestorDegree == 0)
    {
        return (*this) ;
    }

    if (anAncestorDegree > this->getDepth())
    {
        throw library::core::error::RuntimeError("Ancestor degree [{}] is greater than depth [{}].", anAncestorDegree, this->getDepth()) ;
    }

    const Frame* framePtr = this ;

    for (Uint8 degree = 0; degree < anAncestorDegree; ++degree)
    {
        framePtr = &(framePtr->accessParent()) ;
    }

    return *framePtr ;

}

Shared<const Provider>          Frame::accessProvider                       ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Frame") ;
    }

    return providerSPtr_ ;

}

String                          Frame::getName                              ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Frame") ;
    }
    
    return name_ ;

}

Position                        Frame::getOriginIn                          (   const   Frame&                      aFrame,
                                                                                const   Instant&                    anInstant                                   ) const
{

    if (!anInstant.isDefined())
    {
        throw library::core::error::runtime::Undefined("Instant") ;
    }

    if ((!this->isDefined()) || (!aFrame.isDefined()))
    {
        throw library::core::error::runtime::Undefined("Frame") ;
    }

    return Position(this->getTransformTo(aFrame, anInstant).applyToPosition(Vector3d::Zero()), Position::Unit::Meter, std::make_shared<Frame>(aFrame)) ; // [TBM] Why sharing?

}

Axes                            Frame::getAxesIn                            (   const   Frame&                      aFrame,
                                                                                const   Instant&                    anInstant                                   ) const
{

    if (!anInstant.isDefined())
    {
        throw library::core::error::runtime::Undefined("Instant") ;
    }

    if ((!this->isDefined()) || (!aFrame.isDefined()))
    {
        throw library::core::error::runtime::Undefined("Frame") ;
    }

    const Transform transform = this->getTransformTo(aFrame, anInstant) ;

    const Vector3d xAxis = transform.applyToVector(Vector3d::X()) ;
    const Vector3d yAxis = transform.applyToVector(Vector3d::Y()) ;
    const Vector3d zAxis = transform.applyToVector(Vector3d::Z()) ;

    return Axes(xAxis, yAxis, zAxis, std::make_shared<Frame>(aFrame)) ; // [TBM] Why sharing?

}

Transform                       Frame::getTransformTo                       (   const   Frame&                      aFrame,
                                                                                const   Instant&                    anInstant                                   ) const
{

    if ((!this->isDefined()) || (!aFrame.isDefined()))
    {
        throw library::core::error::runtime::Undefined("Frame") ;
    }

    if ((*this) == aFrame)
    {
        return Transform::Identity(anInstant) ;
    }

    // std::cout << "(*this) = " << (*this) << std::endl ;
    // std::cout << "aFrame = " << aFrame << std::endl ;

    // Find common ancestor

    const Frame& commonAncestor = Frame::FindCommonAncestor((*this), aFrame) ;

    if (!commonAncestor.isDefined())
    {
        throw library::core::error::RuntimeError("No common ancestor between [{}] and [{}].", this->getName(), aFrame.getName()) ;
    }

    // std::cout << "commonAncestor = " << std::endl << commonAncestor << std::endl ;
    // std::cout << "&commonAncestor = " << &commonAncestor << std::endl ;

    // Compute transform from common ancestor to origin

    Transform commonToOriginTransform = Transform::Identity(anInstant) ;

    for (auto framePtr = this; (*framePtr) != commonAncestor; framePtr = &framePtr->accessParent())
    {
        // std::cout << "A framePtr = " << (*framePtr) << std::endl ;
        commonToOriginTransform *= framePtr->accessProvider()->getTransformAt(anInstant) ;
        // commonToOriginTransform = Transform(anInstant, frame.transformProvider.getTransform(anInstant), commonToOriginTransform) ;
    }

    // std::cout << "commonToOriginTransform = " << std::endl << commonToOriginTransform << std::endl ;

    // Compute transform from destination to common ancestor
    
    Transform commonToDestinationTransform = Transform::Identity(anInstant) ;

    for (auto framePtr = &aFrame; (*framePtr) != commonAncestor; framePtr = &framePtr->accessParent())
    {
        // std::cout << "B framePtr = " << (*framePtr) << std::endl ;
        commonToDestinationTransform *= framePtr->accessProvider()->getTransformAt(anInstant) ;
        // commonToDestinationTransform = new Transform(date, frame.transformProvider.getTransform(date), commonToDestinationTransform);
    }

    // std::cout << "commonToDestinationTransform = " << std::endl << commonToDestinationTransform << std::endl ;

    // Compute transform from origin to destination

    const Transform originToDestinationTransform = commonToOriginTransform.getInverse() * commonToDestinationTransform ;

    // std::cout << "originToDestinationTransform = " << std::endl << originToDestinationTransform << std::endl ;
    
    return originToDestinationTransform ;
    
}

Frame                           Frame::Undefined                            ( )
{
    return Frame(String::Empty(), false, nullptr, nullptr) ;
}

// Frame                           Frame::ICRF                                 ( )
// {
    
// }

Frame                           Frame::GCRF                                 ( )
{

    // std::cout << "Frame :: GCRF..." << std::endl ;

    using GCRFProvider = library::physics::coord::frame::provider::GCRF ;

    if (FrameManager.hasFrameWithName("GCRF"))
    {
        return *FrameManager.accessFrameWithName("GCRF") ;
    }

    // std::cout << "Frame :: GCRF >> new..." << std::endl ;
    
    const Frame gcrf = { "GCRF", true, nullptr, std::make_shared<GCRFProvider>() } ;

    // std::cout << "Frame :: GCRF >> new" << std::endl ;

    // std::cout << "Frame :: GCRF >> addFrame..." << std::endl ;

    FrameManager.addFrame(gcrf) ;

    // std::cout << "Frame :: GCRF >> addFrame" << std::endl ;

    return gcrf ;

}

Shared<const Frame>             Frame::GCRFShared                           ( )
{

    // std::cout << "Frame :: GCRFShared..." << std::endl ;

    using GCRFProvider = library::physics::coord::frame::provider::GCRF ;

    if (FrameManager.hasFrameWithName("GCRF"))
    {
        return FrameManager.accessFrameWithName("GCRF") ;
    }

    // std::cout << "Frame :: GCRF >> new..." << std::endl ;
    
    const Shared<const Frame> gcrfSPtr = std::make_shared<const Frame>("GCRF", true, nullptr, std::make_shared<GCRFProvider>()) ;
    // const Shared<const Frame> gcrfSPtr(new Frame("GCRF", true, nullptr, std::make_shared<GCRFProvider>()), [] (Frame* aFramePtr) { std::cout << "Shared<Frame> :: Deleter @ " << aFramePtr << std::endl ; delete aFramePtr ; }) ;

    // std::cout << "Frame :: GCRF >> new" << std::endl ;

    // std::cout << "Frame :: GCRF >> addFrame..." << std::endl ;

    FrameManager.addFrame(gcrfSPtr) ;

    // std::cout << "Frame :: GCRF >> addFrame" << std::endl ;

    return gcrfSPtr ;

}

// Frame                           Frame::EME2000                              ( )
// {

// }

Frame                           Frame::TEME                                 ( )
{

    using TEMEProvider = library::physics::coord::frame::provider::TEME ;

    if (FrameManager.hasFrameWithName("TEME"))
    {
        return *FrameManager.accessFrameWithName("TEME") ;
    }

    if (!FrameManager.hasFrameWithName("ITRF"))
    {
        FrameManager.addFrame(Frame::ITRF()) ;
    }

    const Shared<const Frame> itrfSPtr = FrameManager.accessFrameWithName("ITRF") ;

    const Frame temeFrame = { "TEME", true, itrfSPtr, std::make_shared<TEMEProvider>() } ;

    FrameManager.addFrame(temeFrame) ;

    return temeFrame ;

}

Frame                           Frame::TEMEOfEpoch                          (   const   Instant&                    anEpoch                                     )
{

    using FixedProvider = library::physics::coord::frame::provider::Fixed ;

    const String temeOfEpochFrameName = String::Format("TEMEOfEpoch @ {}", anEpoch.toString()) ;
    
    if (FrameManager.hasFrameWithName(temeOfEpochFrameName))
    {
        return *FrameManager.accessFrameWithName(temeOfEpochFrameName) ;
    }

    if (!FrameManager.hasFrameWithName("GCRF"))
    {
        FrameManager.addFrame(Frame::GCRF()) ;
    }

    const Shared<const Frame> gcrfSPtr = FrameManager.accessFrameWithName("GCRF") ;

    const Frame temeOfEpochFrame = { temeOfEpochFrameName, true, gcrfSPtr, std::make_shared<FixedProvider>(Frame::GCRF().getTransformTo(Frame::TEME(), anEpoch)) } ;

    FrameManager.addFrame(temeOfEpochFrame) ;

    return temeOfEpochFrame ;

}

Frame                           Frame::CIRF                                 ( )
{

    using CIRFProvider = library::physics::coord::frame::provider::CIRF ;

    if (FrameManager.hasFrameWithName("CIRF"))
    {
        return *FrameManager.accessFrameWithName("CIRF") ;
    }

    if (!FrameManager.hasFrameWithName("GCRF"))
    {
        FrameManager.addFrame(Frame::GCRF()) ;
    }

    const Shared<const Frame> gcrfSPtr = FrameManager.accessFrameWithName("GCRF") ;

    const Frame cirf = { "CIRF", false, gcrfSPtr, std::make_shared<CIRFProvider>() } ;

    FrameManager.addFrame(cirf) ;

    return cirf ;

}

Frame                           Frame::TIRF                                 ( )
{

    using TIRFProvider = library::physics::coord::frame::provider::TIRF ;

    if (FrameManager.hasFrameWithName("TIRF"))
    {
        return *FrameManager.accessFrameWithName("TIRF") ;
    }

    if (!FrameManager.hasFrameWithName("CIRF"))
    {
        FrameManager.addFrame(Frame::CIRF()) ;
    }

    const Shared<const Frame> cirfSPtr = FrameManager.accessFrameWithName("CIRF") ;

    const Frame tirf = { "TIRF", false, cirfSPtr, std::make_shared<TIRFProvider>() } ;

    FrameManager.addFrame(tirf) ;

    return tirf ;

}

Frame                           Frame::ITRF                                 ( )
{

    using ITRFProvider = library::physics::coord::frame::provider::ITRF ;

    if (FrameManager.hasFrameWithName("ITRF"))
    {
        return *FrameManager.accessFrameWithName("ITRF") ;
    }

    if (!FrameManager.hasFrameWithName("TIRF"))
    {
        FrameManager.addFrame(Frame::TIRF()) ;
    }

    const Shared<const Frame> tirfSPtr = FrameManager.accessFrameWithName("TIRF") ;

    const Frame itrf = { "ITRF", false, tirfSPtr, std::make_shared<ITRFProvider>() } ;

    FrameManager.addFrame(itrf) ;

    return itrf ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Uint8                           Frame::getDepth                             ( ) const
{
    
    Uint8 depth = 0 ;

    const Frame* framePtr = this ;

    while (framePtr->hasParent())
    {
        
        depth++ ;

        framePtr = &(framePtr->accessParent()) ;

    }

    return depth ;

}

const Frame&                    Frame::FindCommonAncestor                   (   const   Frame&                      aFirstFrame,
                                                                                const   Frame&                      aSecondFrame                                )
{

    const Uint8 firstFrameDepth = aFirstFrame.getDepth() ;
    const Uint8 secondFrameDepth = aSecondFrame.getDepth() ;

    const Frame* currentFPtr = (firstFrameDepth > secondFrameDepth) ? &aFirstFrame.accessAncestor(firstFrameDepth - secondFrameDepth) : &aFirstFrame ;
    const Frame* currentTPtr = (firstFrameDepth > secondFrameDepth) ? &aSecondFrame : &aSecondFrame.accessAncestor(secondFrameDepth - firstFrameDepth) ;

    while ((*currentFPtr) != (*currentTPtr))
    {
        currentFPtr = &(currentFPtr->accessParent()) ;
        currentTPtr = &(currentTPtr->accessParent()) ;
    }

    return *currentFPtr ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////