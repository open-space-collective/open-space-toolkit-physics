////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Environment/Ephemerides/SPICE.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Environment/Ephemerides/SPICE/Engine.hpp>
#include <Library/Physics/Environment/Ephemerides/SPICE.hpp>

#include <Library/Core/Containers/Map.hpp>
#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{
namespace env
{
namespace ephem
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                SPICE::SPICE                                (   const   SPICE::Object&              anObject                                    )
                                :   object_(anObject)
{

}

                                SPICE::~SPICE                               ( )
{

}

SPICE*                          SPICE::clone                                ( ) const
{
    return new SPICE(*this) ;
}

bool                            SPICE::isDefined                            ( ) const
{
    return object_ != SPICE::Object::Undefined ;
}

Shared<const Frame>             SPICE::accessFrame                          ( ) const
{

    using library::physics::env::ephem::spice::Engine ;
    
    return Engine::Get().getFrameOf(object_) ;

}

String                          SPICE::StringFromObject                     (   const   SPICE::Object&              anObject                                    )
{

    using library::core::ctnr::Map ;

    static const Map<SPICE::Object, String> objectStringMap =
    {
        { SPICE::Object::Undefined, "Undefined" },
        { SPICE::Object::Sun,       "Sun" },
        { SPICE::Object::Mercury,   "Mercury" },
        { SPICE::Object::Venus,     "Venus" },
        { SPICE::Object::Earth,     "Earth" },
        { SPICE::Object::Moon,      "Moon" },
        { SPICE::Object::Mars,      "Mars" },
        { SPICE::Object::Jupiter,   "Jupiter" },
        { SPICE::Object::Saturn,    "Saturn" },
        { SPICE::Object::Uranus,    "Uranus" },
        { SPICE::Object::Neptune,   "Neptune" }
    } ;

    return objectStringMap.at(anObject) ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////