////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           Library/Physics/Data/Scalar.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Data/Scalar.hpp>

#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ostk
{
namespace physics
{
namespace data
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Scalar::Scalar                              (   const   Real&                       aValue,
                                                                                const   Unit&                       aUnit                                       )
                                :   value_(aValue),
                                    unit_(aUnit)
{

}

bool                            Scalar::operator ==                         (   const   Scalar&                     aScalar                                     ) const
{

    if ((!this->isDefined()) || (!aScalar.isDefined()))
    {
        return false ;
    }

    return (value_ == aScalar.value_) && (unit_ == aScalar.unit_) ;

}

bool                            Scalar::operator !=                         (   const   Scalar&                     aScalar                                     ) const
{
    return !((*this) == aScalar) ;
}

std::ostream&                   operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Scalar&                     aScalar                                     )
{

    ostk::core::utils::Print::Header(anOutputStream, "Scalar") ;

    ostk::core::utils::Print::Line(anOutputStream) << "Value:"               << (aScalar.value_.isDefined() ? aScalar.value_.toString() : "Undefined") ;
    ostk::core::utils::Print::Line(anOutputStream) << "Unit:"                << (aScalar.unit_.isDefined() ? aScalar.unit_.toString() : "Undefined") ;

    ostk::core::utils::Print::Footer(anOutputStream) ;

    return anOutputStream ;

}

bool                            Scalar::isDefined                           ( ) const
{
    return value_.isDefined() && unit_.isDefined() ;
}

Real                            Scalar::getValue                            ( ) const
{
    return value_ ;
}

Unit                            Scalar::getUnit                             ( ) const
{
    return unit_ ;
}

Scalar                          Scalar::inUnit                              (   const   Unit&                       aUnit                                       ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Scalar") ;
    }

    return { value_ * unit_.ratioTo(aUnit), aUnit } ;

}

String                          Scalar::toString                            (   const   Integer&                    aPrecision                                  ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Scalar") ;
    }

    return String::Format("{} [{}]", value_.toString(aPrecision), unit_.toString()) ;

}

Scalar                          Scalar::Undefined                           ( )
{
    return { Real::Undefined(), Unit::Undefined() } ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
