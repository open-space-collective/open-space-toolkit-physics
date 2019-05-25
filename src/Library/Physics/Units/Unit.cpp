////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library ▸ Physics
/// @file           Library/Physics/Units/Unit.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Units/Unit.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{
namespace units
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Unit::Unit                                  (   const   Unit::Type&                 aType,
                                                                                const   Real&                       aValue                                      )
                                :   type_(aType),
                                    value_(aValue)
{

}

                                Unit::~Unit                                 ( )
{

}

bool                            Unit::operator ==                           (   const   Unit&                       aUnit                                       ) const
{

    if ((!this->isDefined()) || (!aUnit.isDefined()))
    {
        return false ;
    }

    return (type_ == aUnit.type_) && (value_ == aUnit.value_) ;

}

bool                            Unit::operator !=                           (   const   Unit&                       aUnit                                       ) const
{

    if ((!this->isDefined()) || (!aUnit.isDefined()))
    {
        return true ;
    }

    return (type_ != aUnit.type_) || (value_ != aUnit.value_) ;

}

bool                            Unit::isDefined                             ( ) const
{
    return (type_ != Unit::Type::Undefined) && value_.isDefined() ;
}

bool                            Unit::isZero                                ( ) const
{
    return (type_ != Unit::Type::Undefined) && value_.isZero() ;
}

const Real&                     Unit::accessValue                           ( ) const
{
    return value_ ;
}

Unit::Type                      Unit::getType                               ( ) const
{
    return type_ ;
}

Real                            Unit::getValue                              ( ) const
{
    return value_ ;
}

Real&                           Unit::accessValue                           ( )
{
    return value_ ;
}

void                            Unit::setValue                              (   const   Real&                       aValue                                      )
{
    value_ = aValue ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
