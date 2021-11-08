////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           OpenSpaceToolkit/Physics/Coordinate/Frame.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/ITRF.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/TIRF.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/CIRF.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/TEME.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/TOD.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/MOD.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/GCRF.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/Static.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Manager.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ostk
{
namespace physics
{
namespace coord
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using FrameManager = ostk::physics::coord::frame::Manager ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// https://stackoverflow.com/questions/8147027/how-do-i-call-stdmake-shared-on-a-class-with-only-protected-or-private-const

struct SharedFrameEnabler : public Frame
{

                                SharedFrameEnabler                          (   const   String&                     aName,
                                                                                        bool                        isQuasiInertial,
                                                                                const   Shared<const Frame>&        aParentFrame,
                                                                                const   Shared<const Provider>&     aProvider                                   )
                                :   Frame(aName, isQuasiInertial, aParentFrame, aProvider)
    {

    }

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
        && (((parentFrameSPtr_ == nullptr) && (aFrame.parentFrameSPtr_ == nullptr)) || ((parentFrameSPtr_ != nullptr) && (aFrame.parentFrameSPtr_ != nullptr) && ((*parentFrameSPtr_) == (*aFrame.parentFrameSPtr_))))
        && ((providerSPtr_ != nullptr) && (aFrame.providerSPtr_ != nullptr) && (providerSPtr_.get() == aFrame.providerSPtr_.get())) ;

}

bool                            Frame::operator !=                          (   const   Frame&                      aFrame                                      ) const
{
    return !((*this) == aFrame) ;
}

std::ostream&                   operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Frame&                      aFrame                                      )
{

    ostk::core::utils::Print::Header(anOutputStream, "Frame") ;

    ostk::core::utils::Print::Line(anOutputStream) << "Name:"                << (aFrame.isDefined() ? aFrame.getName() : "Undefined") ;
    ostk::core::utils::Print::Line(anOutputStream) << "Quasi-inertial:"      << (aFrame.isDefined() ? String::Format("{}", aFrame.isQuasiInertial()) : "Undefined") ;
    ostk::core::utils::Print::Line(anOutputStream) << "Parent frame:"        << (((aFrame.parentFrameSPtr_ != nullptr) && (aFrame.parentFrameSPtr_->isDefined())) ? aFrame.parentFrameSPtr_->getName() : "None") ;

    ostk::core::utils::Print::Footer(anOutputStream) ;

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
        throw ostk::core::error::runtime::Undefined("Frame") ;
    }

    return quasiInertial_ ;

}

bool                            Frame::hasParent                            ( ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Frame") ;
    }

    return parentFrameSPtr_ != nullptr ;

}

Shared<const Frame>             Frame::accessParent                         ( ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Frame") ;
    }

    if (parentFrameSPtr_ == nullptr)
    {
        throw ostk::core::error::runtime::Undefined("Parent") ;
    }

    return parentFrameSPtr_ ;

}

Shared<const Frame>             Frame::accessAncestor                       (   const   Uint8                       anAncestorDegree                            ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Frame") ;
    }

    if (anAncestorDegree == 0)
    {
        return this->shared_from_this() ;
    }

    if (anAncestorDegree > this->getDepth())
    {
        throw ostk::core::error::RuntimeError("Ancestor degree [{}] is greater than depth [{}].", anAncestorDegree, this->getDepth()) ;
    }

    Shared<const Frame> frameSPtr = this->shared_from_this() ;

    for (Uint8 degree = 0; degree < anAncestorDegree; ++degree)
    {
        frameSPtr = frameSPtr->accessParent() ;
    }

    return frameSPtr ;

}

Shared<const Provider>          Frame::accessProvider                       ( ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Frame") ;
    }

    return providerSPtr_ ;

}

String                          Frame::getName                              ( ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Frame") ;
    }

    return name_ ;

}

Position                        Frame::getOriginIn                          (   const   Shared<const Frame>&        aFrameSPtr,
                                                                                const   Instant&                    anInstant                                   ) const
{

    if (!anInstant.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant") ;
    }

    if ((!this->isDefined()) || (aFrameSPtr == nullptr) || (!aFrameSPtr->isDefined()))
    {
        throw ostk::core::error::runtime::Undefined("Frame") ;
    }

    const Transform transform = this->getTransformTo(aFrameSPtr, anInstant) ;

    return { transform.applyToPosition(Vector3d::Zero()), Position::Unit::Meter, aFrameSPtr } ;

}

Velocity                        Frame::getVelocityIn                        (   const   Shared<const Frame>&        aFrameSPtr,
                                                                                const   Instant&                    anInstant                                   ) const
{

    if (!anInstant.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant") ;
    }

    if ((!this->isDefined()) || (aFrameSPtr == nullptr) || (!aFrameSPtr->isDefined()))
    {
        throw ostk::core::error::runtime::Undefined("Frame") ;
    }

    return { this->getTransformTo(aFrameSPtr, anInstant).applyToVelocity(Vector3d::Zero(), Vector3d::Zero()), Velocity::Unit::MeterPerSecond, aFrameSPtr } ;

}

Axes                            Frame::getAxesIn                            (   const   Shared<const Frame>&        aFrameSPtr,
                                                                                const   Instant&                    anInstant                                   ) const
{

    if (!anInstant.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant") ;
    }

    if ((!this->isDefined()) || (aFrameSPtr == nullptr) || (!aFrameSPtr->isDefined()))
    {
        throw ostk::core::error::runtime::Undefined("Frame") ;
    }

    const Transform transform = this->getTransformTo(aFrameSPtr, anInstant) ;

    const Vector3d xAxis = transform.applyToVector(Vector3d::X()).normalized() ;
    const Vector3d yAxis = transform.applyToVector(Vector3d::Y()).normalized() ;
    const Vector3d zAxis = xAxis.cross(yAxis) ;

    return { xAxis, yAxis, zAxis, aFrameSPtr } ;

}

Transform                       Frame::getTransformTo                       (   const   Shared<const Frame>&        aFrameSPtr,
                                                                                const   Instant&                    anInstant                                   ) const
{

    if (!anInstant.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant") ;
    }

    if ((!this->isDefined()) || (aFrameSPtr == nullptr) || (!aFrameSPtr->isDefined()))
    {
        throw ostk::core::error::runtime::Undefined("Frame") ;
    }

    if ((*this) == (*aFrameSPtr))
    {
        return Transform::Identity(anInstant) ;
    }

    // std::cout << "From: " << std::endl << (*this) << std::endl ;
    // std::cout << "To: " << std::endl << (*aFrameSPtr) << std::endl ;

    const Shared<const Frame> thisSPtr = this->shared_from_this() ;

    if (auto transformPtr = FrameManager::Get().accessCachedTransform(thisSPtr, aFrameSPtr, anInstant))
    {
        return *transformPtr ;
    }

    // Find common ancestor

    const Shared<const Frame> commonAncestorSPtr = Frame::FindCommonAncestor(thisSPtr, aFrameSPtr) ;

    if ((commonAncestorSPtr == nullptr) || (!commonAncestorSPtr->isDefined()))
    {
        throw ostk::core::error::RuntimeError("No common ancestor between [{}] and [{}].", this->getName(), aFrameSPtr->getName()) ;
    }

    // std::cout << "Common ancestor:" << std::endl << (*commonAncestorSPtr) << std::endl ;

    // Compute transform from common ancestor to origin

    Transform transform_origin_common = Transform::Identity(anInstant) ;

    for (auto framePtr = this; framePtr != commonAncestorSPtr.get(); framePtr = framePtr->accessParent().get())
    {
        transform_origin_common *= framePtr->accessProvider()->getTransformAt(anInstant) ;
    }

    // std::cout << String::Format("{} → {}:", commonAncestorSPtr->getName(), this->getName()) << std::endl << transform_origin_common << std::endl ;

    // Compute transform from destination to common ancestor

    Transform transform_destination_common = Transform::Identity(anInstant) ;

    for (auto framePtr = aFrameSPtr.get(); framePtr != commonAncestorSPtr.get(); framePtr = framePtr->accessParent().get())
    {
        transform_destination_common *= framePtr->accessProvider()->getTransformAt(anInstant) ;
    }

    // std::cout << String::Format("{} → {}:", commonAncestorSPtr->getName(), aFrameSPtr->getName()) << std::endl << transform_destination_common << std::endl ;

    // Compute transform from origin to destination

    const Transform transform_destination_origin = transform_destination_common * transform_origin_common.getInverse() ;

    // std::cout << String::Format("{} → {}:", this->getName(), aFrameSPtr->getName()) << std::endl << transform_destination_origin << std::endl ;

    FrameManager::Get().addCachedTransform(thisSPtr, aFrameSPtr, anInstant, transform_destination_origin) ;

    return transform_destination_origin ;

}

Shared<const Frame>             Frame::Undefined                            ( )
{
    return std::make_shared<const SharedFrameEnabler>(String::Empty(), false, nullptr, nullptr) ;
}

Shared<const Frame>             Frame::GCRF                                 ( )
{

    using GCRFProvider = ostk::physics::coord::frame::provider::GCRF ;

    static const Shared<const Provider> providerSPtr = std::make_shared<const GCRFProvider>() ;

    return Frame::Emplace("GCRF", true, nullptr, providerSPtr) ;

}

Shared<const Frame>             Frame::MOD                                  (   const   Instant&                    anEpoch                                     )
{

    using Scale = ostk::physics::time::Scale ;

    const String frameName = String::Format("MOD @ {}", anEpoch.toString(Scale::TT)) ;

    using MODProvider = ostk::physics::coord::frame::provider::MOD ;

    static const Shared<const Provider> providerSPtr = std::make_shared<const MODProvider>(anEpoch) ;

    return Frame::Emplace(frameName, true, Frame::GCRF(), providerSPtr) ;

}

Shared<const Frame>             Frame::TOD                                  (   const   Instant&                    anEpoch                                     )
{

    using Scale = ostk::physics::time::Scale ;

    const String frameName = String::Format("TOD @ {}", anEpoch.toString(Scale::TT)) ;

    using TODProvider = ostk::physics::coord::frame::provider::TOD ;

    static const Shared<const Provider> providerSPtr = std::make_shared<const TODProvider>(anEpoch) ;

    return Frame::Emplace(frameName, true, Frame::MOD(anEpoch), providerSPtr) ;

}

Shared<const Frame>             Frame::TEME                                 ( )
{

    using TEMEProvider = ostk::physics::coord::frame::provider::TEME ;

    static const Shared<const Provider> providerSPtr = std::make_shared<const TEMEProvider>() ;

    return Frame::Emplace("TEME", true, Frame::ITRF(), providerSPtr) ;

}

Shared<const Frame>             Frame::TEMEOfEpoch                          (   const   Instant&                    anEpoch                                     )
{

    using Scale = ostk::physics::time::Scale ;
    using StaticProvider = ostk::physics::coord::frame::provider::Static ;

    const String temeOfEpochFrameName = String::Format("TEMEOfEpoch @ {}", anEpoch.toString(Scale::TT)) ;

    const Shared<const Provider> providerSPtr = std::make_shared<const StaticProvider>(Frame::GCRF()->getTransformTo(Frame::TEME(), anEpoch)) ;

    return Frame::Emplace(temeOfEpochFrameName, true, Frame::GCRF(), providerSPtr) ;

}

Shared<const Frame>             Frame::CIRF                                 ( )
{

    using CIRFProvider = ostk::physics::coord::frame::provider::CIRF ;

    static const Shared<const Provider> providerSPtr = std::make_shared<const CIRFProvider>() ;

    return Frame::Emplace("CIRF", false, Frame::GCRF(), providerSPtr) ;

}

Shared<const Frame>             Frame::TIRF                                 ( )
{

    using TIRFProvider = ostk::physics::coord::frame::provider::TIRF ;

    static const Shared<const Provider> providerSPtr = std::make_shared<const TIRFProvider>() ;

    return Frame::Emplace("TIRF", false, Frame::CIRF(), providerSPtr) ;

}

Shared<const Frame>             Frame::ITRF                                 ( )
{

    using ITRFProvider = ostk::physics::coord::frame::provider::ITRF ;

    static const Shared<const Provider> providerSPtr = std::make_shared<const ITRFProvider>() ;

    return Frame::Emplace("ITRF", false, Frame::TIRF(), providerSPtr) ;

}

Shared<const Frame>             Frame::WithName                             (   const   String&                     aName                                       )
{

    if (aName.isEmpty())
    {
        throw ostk::core::error::runtime::Undefined("Name") ;
    }

    if (const auto frameSPtr = FrameManager::Get().accessFrameWithName(aName))
    {
        return frameSPtr ;
    }

    return nullptr ;

}

bool                            Frame::Exists                               (   const   String&                     aName                                       )
{

    if (aName.isEmpty())
    {
        throw ostk::core::error::runtime::Undefined("Name") ;
    }

    return FrameManager::Get().hasFrameWithName(aName) ;

}

Shared<const Frame>             Frame::Construct                            (   const   String&                     aName,
                                                                                        bool                        isQuasiInertial,
                                                                                const   Shared<const Frame>&        aParentFrame,
                                                                                const   Shared<const Provider>&     aProvider                                   )
{

    if (FrameManager::Get().hasFrameWithName(aName))
    {
        throw ostk::core::error::RuntimeError("Frame with name [{}] already exist.", aName) ;
    }

    return Frame::Emplace(aName, isQuasiInertial, aParentFrame, aProvider) ;

}

void                            Frame::Destruct                             (   const   String&                     aName                                       )
{

    if (FrameManager::Get().hasFrameWithName(aName))
    {
        FrameManager::Get().removeFrameWithName(aName) ;
    }
    else
    {
        throw ostk::core::error::RuntimeError("No frame with name [{}].", aName) ;
    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Frame::Frame                                (   const   String&                     aName,
                                                                                        bool                        isQuasiInertial,
                                                                                const   Shared<const Frame>&        aParentFrame,
                                                                                const   Shared<const Provider>&     aProvider                                   )
                                :   std::enable_shared_from_this<ostk::physics::coord::Frame>(),
                                    name_(aName),
                                    quasiInertial_(isQuasiInertial),
                                    parentFrameSPtr_(aParentFrame),
                                    providerSPtr_(aProvider)
{

}

Uint8                           Frame::getDepth                             ( ) const
{

    Uint8 depth = 0 ;

    Shared<const Frame> frameSPtr = this->shared_from_this() ;

    while (frameSPtr->hasParent())
    {

        if (depth == 255)
        {
            throw ostk::core::error::RuntimeError("Depth overflow.") ;
        }

        depth++ ;

        frameSPtr = frameSPtr->accessParent() ;

    }

    return depth ;

}

Shared<const Frame>             Frame::Emplace                              (   const   String&                     aName,
                                                                                        bool                        isQuasiInertial,
                                                                                const   Shared<const Frame>&        aParentFrame,
                                                                                const   Shared<const Provider>&     aProvider                                   )
{

    if (const auto frameSPtr = FrameManager::Get().accessFrameWithName(aName))
    {
        return frameSPtr ;
    }

    const Shared<const Frame> frameSPtr = std::make_shared<const SharedFrameEnabler>(aName, isQuasiInertial, aParentFrame, aProvider) ;

    FrameManager::Get().addFrame(frameSPtr) ;

    return frameSPtr ;

}

Shared<const Frame>             Frame::FindCommonAncestor                   (   const   Shared<const Frame>&        aFirstFrameSPtr,
                                                                                const   Shared<const Frame>&        aSecondFrameSPtr                            )
{

    const Uint8 firstFrameDepth = aFirstFrameSPtr->getDepth() ;
    const Uint8 secondFrameDepth = aSecondFrameSPtr->getDepth() ;

    Shared<const Frame> currentFSPtr = (firstFrameDepth > secondFrameDepth) ? aFirstFrameSPtr->accessAncestor(firstFrameDepth - secondFrameDepth) : aFirstFrameSPtr ;
    Shared<const Frame> currentTSPtr = (firstFrameDepth > secondFrameDepth) ? aSecondFrameSPtr : aSecondFrameSPtr->accessAncestor(secondFrameDepth - firstFrameDepth) ;

    while ((*currentFSPtr) != (*currentTSPtr))
    {
        currentFSPtr = currentFSPtr->accessParent() ;
        currentTSPtr = currentTSPtr->accessParent() ;
    }

    return currentFSPtr ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
