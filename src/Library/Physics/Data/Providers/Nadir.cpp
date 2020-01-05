////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           Library/Physics/Data/Providers/Nadir.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Data/Providers/Nadir.hpp>
#include <Library/Physics/Coordinate/Spherical/LLA.hpp>

#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{
namespace data
{
namespace providers
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Direction                       Nadir                                       (   const   Position&                   aPosition,
                                                                                const   Celestial&                  aCelestialObject,
                                                                                const   Environment&                anEnvironment                               )
{

    using library::physics::coord::spherical::LLA ;

    if (!aPosition.isDefined())
    {
        throw library::core::error::runtime::Undefined("Position") ;
    }

    if (!aCelestialObject.isDefined())
    {
        throw library::core::error::runtime::Undefined("Celestial object") ;
    }

    if (!anEnvironment.isDefined())
    {
        throw library::core::error::runtime::Undefined("Environment") ;
    }

    const LLA lla = LLA::Cartesian(aPosition.inFrame(aCelestialObject.accessFrame(), anEnvironment.getInstant()).getCoordinates(), aCelestialObject.getEquatorialRadius(), aCelestialObject.getFlattening()) ;

    const Shared<const Frame> nedFrameSPtr = aCelestialObject.getFrameAt(lla, Celestial::FrameType::NED) ;

    const Vector3d z_NED_FIXED = nedFrameSPtr->getAxesIn(aCelestialObject.accessFrame(), anEnvironment.getInstant()).z() ;

    return { z_NED_FIXED, aCelestialObject.accessFrame() } ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
