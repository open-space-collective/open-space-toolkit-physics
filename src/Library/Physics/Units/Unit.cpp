////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library ▸ Physics
/// @file           Library/Physics/Units/Unit.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Units/Unit.hpp>

#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>

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

Pair<Real, String>              Unit::ParseString                           (   const   String&                     aString                                     )
{

    if (aString.isEmpty())
    {
        throw library::core::error::runtime::Undefined("String") ;
    }

    boost::smatch match ;

    if (boost::regex_match(aString, match, boost::regex("^([-+\\de.]+) \\[([\\w\\/^\\.]+)\\]$")))
    {

        const Real value = boost::lexical_cast<double>(match[1]) ;
        const String unit = String(match[2]) ;

        return { value, unit } ;

    }
    else
    {
        throw library::core::error::RuntimeError("Cannot parse unit string [{}].", aString) ;
    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
