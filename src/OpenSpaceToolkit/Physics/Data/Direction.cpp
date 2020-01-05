////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           OpenSpaceToolkit/Physics/Data/Direction.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Physics/Data/Direction.hpp>
#include <OpenSpaceToolkit/Physics/Unit.hpp>

#include <OpenSpaceToolkit/Core/Types/Real.hpp>
#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ostk
{
namespace physics
{
namespace data
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using ostk::core::types::Real ;

using ostk::physics::Unit ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Direction::Direction                        (   const   Vector3d&                   aValue,
                                                                                const   Shared<const Frame>&        aFrameSPtr                                  )
                                :   Vector(aValue.normalized(), Unit::None(), aFrameSPtr)
{

    if (std::abs(aValue.norm() - 1.0) > Real::Epsilon())
    {
        throw ostk::core::error::RuntimeError("Direction vector is not unitary [{}].", aValue.norm()) ;
    }

}

bool                            Direction::operator ==                      (   const   Direction&                  aDirection                                  ) const
{

    if ((!this->isDefined()) || (!aDirection.isDefined()))
    {
        return false ;
    }

    return Vector::operator == (aDirection) ;

}

bool                            Direction::operator !=                      (   const   Direction&                  aDirection                                  ) const
{
    return !((*this) == aDirection) ;
}

std::ostream&                   operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Direction&                  aDirection                                  )
{

    ostk::core::utils::Print::Header(anOutputStream, "Direction") ;

    ostk::core::utils::Print::Line(anOutputStream) << "Value:"               << (aDirection.getValue().isDefined() ? aDirection.getValue().toString() : "Undefined") ;
    ostk::core::utils::Print::Line(anOutputStream) << "Frame:"                << (((aDirection.getFrame() != nullptr) && (aDirection.getFrame()->isDefined())) ? aDirection.getFrame()->getName() : "Undefined") ;

    ostk::core::utils::Print::Footer(anOutputStream) ;

    return anOutputStream ;

}

Direction                       Direction::Undefined                        ( )
{
    return { Vector3d::Undefined(), Frame::Undefined() } ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
