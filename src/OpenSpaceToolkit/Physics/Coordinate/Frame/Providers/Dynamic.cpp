////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/Dynamic.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/Dynamic.hpp>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ostk
{
namespace physics
{
namespace coord
{
namespace frame
{
namespace provider
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Dynamic::Dynamic                            (   const   Dynamic::Generator&         aGenerator                                  )
                                :   generator_(aGenerator)
{

}

                                Dynamic::~Dynamic                           ( )
{

}

Dynamic*                        Dynamic::clone                              ( ) const
{
    return new Dynamic(*this) ;
}

bool                            Dynamic::isDefined                          ( ) const
{
    return !!generator_ ;
}

Transform                       Dynamic::getTransformAt                     (   const   Instant&                    anInstant                                   ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Dynamic provider") ;
    }

    return generator_(anInstant) ;

}

Dynamic                         Dynamic::Undefined                          ( )
{
    return { {} } ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
