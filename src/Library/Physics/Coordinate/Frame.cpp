////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Coordinate/Frame.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Coordinate/Frame/Providers/ITRF.hpp>
#include <Library/Physics/Coordinate/Frame/Providers/TIRF.hpp>
#include <Library/Physics/Coordinate/Frame/Providers/CIRF.hpp>
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

}

                                Frame::~Frame                               ( )
{

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

Transform                       Frame::getTransformTo                       (   const   Frame&                      aFrame,
                                                                                const   Instant&                    anInstant                                   ) const
{

    if ((!this->isDefined()) || (!aFrame.isDefined()))
    {
        throw library::core::error::runtime::Undefined("Frame") ;
    }

    if (!anInstant.isDefined())
    {
        throw library::core::error::runtime::Undefined("Instant") ;
    }

    if ((*this) == aFrame)
    {
        return Transform::Identity() ;
    }

    std::cout << "(*this) = " << (*this) << std::endl ;
    // std::cout << "this = " << this << std::endl ;

    std::cout << "aFrame = " << aFrame << std::endl ;
    // std::cout << "&aFrame = " << &aFrame << std::endl ;

    // Find common ancestor

    const Frame& commonAncestor = Frame::FindCommonAncestor((*this), aFrame) ;

    if (!commonAncestor.isDefined())
    {
        throw library::core::error::RuntimeError("No common ancestor between [{}] and [{}].", this->getName(), aFrame.getName()) ;
    }

    std::cout << "commonAncestor = " << std::endl << commonAncestor << std::endl ;
    // std::cout << "&commonAncestor = " << &commonAncestor << std::endl ;

    // Compute transform from common ancestor to origin

    Transform commonToOriginTransform = Transform::Identity(anInstant) ;

    for (auto framePtr = this; (*framePtr) != commonAncestor; framePtr = &framePtr->accessParent())
    {
        std::cout << "A framePtr = " << (*framePtr) << std::endl ;
        commonToOriginTransform *= framePtr->accessProvider()->getTransformAt(anInstant) ;
        // commonToOriginTransform = Transform(anInstant, frame.transformProvider.getTransform(anInstant), commonToOriginTransform) ;
    }

    std::cout << "commonToOriginTransform = " << std::endl << commonToOriginTransform << std::endl ;

    // Compute transform from destination to common ancestor
    
    Transform commonToDestinationTransform = Transform::Identity(anInstant) ;

    for (auto framePtr = &aFrame; (*framePtr) != commonAncestor; framePtr = &framePtr->accessParent())
    {
        std::cout << "B framePtr = " << (*framePtr) << std::endl ;
        commonToDestinationTransform *= framePtr->accessProvider()->getTransformAt(anInstant) ;
        // commonToDestinationTransform = new Transform(date, frame.transformProvider.getTransform(date), commonToDestinationTransform);
    }

    std::cout << "commonToDestinationTransform = " << std::endl << commonToDestinationTransform << std::endl ;

    // Compute transform from origin to destination

    const Transform originToDestinationTransform = commonToOriginTransform.getInverse() * commonToDestinationTransform ;

    std::cout << "originToDestinationTransform = " << std::endl << originToDestinationTransform << std::endl ;
    
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

    using GCRFProvider = library::physics::coord::frame::provider::GCRF ;

    if (FrameManager.hasFrameWithName("GCRF"))
    {
        return *FrameManager.accessFrameWithName("GCRF") ;
    }
    
    const Frame gcrf = { "GCRF", true, nullptr, std::make_shared<GCRFProvider>() } ;

    FrameManager.addFrame(gcrf) ;

    return gcrf ;

}

// Frame                           Frame::EME2000                              ( )
// {

// }

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