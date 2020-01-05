////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           Library/Physics/Data/Direction.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Data/Direction.hpp>
#include <Library/Physics/Unit.hpp>

#include <Library/Core/Types/Real.hpp>
#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{
namespace data
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using library::core::types::Real ;

using library::physics::Unit ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Direction::Direction                        (   const   Vector3d&                   aValue,
                                                                                const   Shared<const Frame>&        aFrameSPtr                                  )
                                :   Vector(aValue.normalized(), Unit::None(), aFrameSPtr)
{

    if (std::abs(aValue.norm() - 1.0) > Real::Epsilon())
    {
        throw library::core::error::RuntimeError("Direction vector is not unitary [{}].", aValue.norm()) ;
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

    library::core::utils::Print::Header(anOutputStream, "Direction") ;

    library::core::utils::Print::Line(anOutputStream) << "Value:"               << (aDirection.getValue().isDefined() ? aDirection.getValue().toString() : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Frame:"                << (((aDirection.getFrame() != nullptr) && (aDirection.getFrame()->isDefined())) ? aDirection.getFrame()->getName() : "Undefined") ;

    library::core::utils::Print::Footer(anOutputStream) ;

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
