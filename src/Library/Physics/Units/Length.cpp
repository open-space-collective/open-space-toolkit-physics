////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Units/Length.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Units/Length.hpp>
#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

#include <iostream>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{
namespace units
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Length::Length                              (   const   Real&                       aValue,
                                                                                const   Length::Unit&               aUnit                                       )
                                :   units::Unit(units::Unit::Type::Length, aValue),
                                    unit_(aUnit)
{

}

bool                            Length::operator ==                         (   const   Length&                     aLength                                     ) const
{

    if ((unit_ == Length::Unit::Undefined) || (aLength.unit_ == Length::Unit::Undefined))
    {
        return false ;
    }

    return this->accessValue() == ((unit_ == aLength.unit_) ? aLength.accessValue() : aLength.in(unit_)) ;

}

bool                            Length::operator !=                         (   const   Length&                     aLength                                     ) const
{
    return !((*this) == aLength) ;
}

bool                            Length::operator <                          (   const   Length&                     aLength                                     ) const
{

    if ((unit_ == Length::Unit::Undefined) || (aLength.unit_ == Length::Unit::Undefined))
    {
        throw library::core::error::runtime::Undefined("Length") ;
    }

    return this->accessValue() < ((unit_ == aLength.unit_) ? aLength.accessValue() : aLength.in(unit_)) ;

}

bool                            Length::operator <=                         (   const   Length&                     aLength                                     ) const
{

    if ((unit_ == Length::Unit::Undefined) || (aLength.unit_ == Length::Unit::Undefined))
    {
        throw library::core::error::runtime::Undefined("Length") ;
    }

    return this->accessValue() <= ((unit_ == aLength.unit_) ? aLength.accessValue() : aLength.in(unit_)) ;

}

bool                            Length::operator >                          (   const   Length&                     aLength                                     ) const
{

    if ((unit_ == Length::Unit::Undefined) || (aLength.unit_ == Length::Unit::Undefined))
    {
        throw library::core::error::runtime::Undefined("Length") ;
    }

    return this->accessValue() > ((unit_ == aLength.unit_) ? aLength.accessValue() : aLength.in(unit_)) ;

}

bool                            Length::operator >=                         (   const   Length&                     aLength                                     ) const
{

    if ((unit_ == Length::Unit::Undefined) || (aLength.unit_ == Length::Unit::Undefined))
    {
        throw library::core::error::runtime::Undefined("Length") ;
    }

    return this->accessValue() >= ((unit_ == aLength.unit_) ? aLength.accessValue() : aLength.in(unit_)) ;

}

Length                          Length::operator +                          (   const   Length&                     aLength                                     ) const
{

    if ((unit_ == Length::Unit::Undefined) || (aLength.unit_ == Length::Unit::Undefined))
    {
        throw library::core::error::runtime::Undefined("Length") ;
    }

    return Length((this->accessValue() + ((unit_ == aLength.unit_) ? aLength.accessValue() : aLength.in(unit_))), unit_) ;

}

Length                          Length::operator -                          (   const   Length&                     aLength                                     ) const
{

    if ((unit_ == Length::Unit::Undefined) || (aLength.unit_ == Length::Unit::Undefined))
    {
        throw library::core::error::runtime::Undefined("Length") ;
    }

    return Length((this->accessValue() - ((unit_ == aLength.unit_) ? aLength.accessValue() : aLength.in(unit_))), unit_) ;

}

Length                          Length::operator *                          (   const   Real&                       aReal                                       ) const
{

    if (unit_ == Length::Unit::Undefined)
    {
        throw library::core::error::runtime::Undefined("Length") ;
    }

    if (!aReal.isDefined())
    {
        throw library::core::error::runtime::Undefined("Real") ;
    }

    return Length((this->accessValue() * aReal), unit_) ;

}

Length                          Length::operator /                          (   const   Real&                       aReal                                       ) const
{

    if (unit_ == Length::Unit::Undefined)
    {
        throw library::core::error::runtime::Undefined("Length") ;
    }

    if (!aReal.isDefined())
    {
        throw library::core::error::runtime::Undefined("Real") ;
    }

    if (aReal.isZero())
    {
        throw library::core::error::RuntimeError("Cannot divide by zero.") ;
    }

    return Length((this->accessValue() / aReal), unit_) ;

}

Length&                         Length::operator +=                         (   const   Length&                     aLength                                     )
{

    if ((unit_ == Length::Unit::Undefined) || (aLength.unit_ == Length::Unit::Undefined))
    {
        throw library::core::error::runtime::Undefined("Length") ;
    }

    this->accessValue() += ((unit_ == aLength.unit_) ? aLength.accessValue() : aLength.in(unit_)) ;

    return (*this) ;

}

Length&                         Length::operator -=                         (   const   Length&                     aLength                                     )
{

    if ((unit_ == Length::Unit::Undefined) || (aLength.unit_ == Length::Unit::Undefined))
    {
        throw library::core::error::runtime::Undefined("Length") ;
    }

    this->accessValue() -= ((unit_ == aLength.unit_) ? aLength.accessValue() : aLength.in(unit_)) ;

    return (*this) ;

}

Length&                         Length::operator *=                         (   const   Real&                       aReal                                       )
{

    if (unit_ == Length::Unit::Undefined)
    {
        throw library::core::error::runtime::Undefined("Length") ;
    }

    if (!aReal.isDefined())
    {
        throw library::core::error::runtime::Undefined("Real") ;
    }

    this->accessValue() *= aReal ;

    return (*this) ;

}

Length&                         Length::operator /=                         (   const   Real&                       aReal                                       )
{

    if (unit_ == Length::Unit::Undefined)
    {
        throw library::core::error::runtime::Undefined("Length") ;
    }

    if (!aReal.isDefined())
    {
        throw library::core::error::runtime::Undefined("Real") ;
    }

    if (aReal.isZero())
    {
        throw library::core::error::RuntimeError("Cannot divide by zero.") ;
    }

    this->accessValue() /= aReal ;

    return (*this) ;

}

Length                          operator *                                  (   const   Real&                       aReal,
                                                                                const   Length&                     aLength                                     )
{

    if (!aReal.isDefined())
    {
        throw library::core::error::runtime::Undefined("Real") ;
    }

    if (aLength.unit_ == Length::Unit::Undefined)
    {
        throw library::core::error::runtime::Undefined("Length") ;
    }
    
    return Length((aLength.accessValue() * aReal), aLength.unit_) ;

}

std::ostream&                   operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Length&                     aLength                                     )
{

    library::core::utils::Print::Header(anOutputStream, "Length") ;

    library::core::utils::Print::Line(anOutputStream) << "Value:" << aLength.accessValue() ;
    library::core::utils::Print::Line(anOutputStream) << "Unit:" << Length::StringFromUnit(aLength.unit_) ;

    library::core::utils::Print::Footer(anOutputStream) ;

    return anOutputStream ;

}

bool                            Length::isDefined                           ( ) const
{
    return units::Unit::isDefined() && (unit_ != Length::Unit::Undefined) ;
}

Length::Unit                    Length::getUnit                             ( ) const
{
    return unit_ ;
}

Real                            Length::in                                  (   const   Length::Unit&               aUnit                                       ) const
{

    if (!this->isDefined())
    {
        return Real::Undefined() ;
    }

    if (unit_ == aUnit)
    {
        return this->accessValue() ;
    }

    return this->accessValue() * Length::SIRatio(unit_) / Length::SIRatio(aUnit) ;

}

Real                            Length::inMeters                            ( ) const
{
    return this->in(Length::Unit::Meter) ;
}

Real                            Length::inKilometers                        ( ) const
{
    return this->in(Length::Unit::Meter) / 1e3 ;
}

String                          Length::toString                            (   const   Integer&                    aPrecision                                  ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Length") ;
    }

    return this->accessValue().toString(aPrecision) + " [" + Length::SymbolFromUnit(unit_) + "]" ;

}

Length                          Length::Undefined                           ( )
{
    return Length(Real::Undefined(), Length::Unit::Undefined) ;
}

Length                          Length::Millimeters                         (   const   Real&                       aValue                                      )
{
    return Length(aValue / 1e3, Length::Unit::Meter) ;
}

Length                          Length::Meters                              (   const   Real&                       aValue                                      )
{
    return Length(aValue, Length::Unit::Meter) ;
}

Length                          Length::Kilometers                          (   const   Real&                       aValue                                      )
{
    return Length(aValue * 1e3, Length::Unit::Meter) ;
}

// Length                          Length::Parse                               (   const   String&                     aString                                     )
// {

// }

String                          Length::StringFromUnit                      (   const   Length::Unit&               aUnit                                       )
{

    switch (aUnit)
    {

        case Length::Unit::Undefined:
            return "Undefined" ;
            
        case Length::Unit::Meter:
            return "Meter" ;
            
        case Length::Unit::Foot:
            return "Foot" ;
            
        case Length::Unit::TerrestrialMile:
            return "Terrestrial Mile" ;
            
        case Length::Unit::NauticalMile:
            return "Nautical Mile" ;
            
        case Length::Unit::AstronomicalUnit:
            return "Astronomical Unit" ;
            
        default:
            break ;

    }

    throw library::core::error::runtime::Wrong("Unit") ;

    return String::Empty() ;

}

String                          Length::SymbolFromUnit                      (   const   Length::Unit&               aUnit                                       )
{

    switch (aUnit)
    {

        case Length::Unit::Meter:
            return "m" ;
            
        case Length::Unit::Foot:
            return "ft" ;
            
        case Length::Unit::TerrestrialMile:
            return "mi" ;
            
        case Length::Unit::NauticalMile:
            return "nmi" ;
            
        case Length::Unit::AstronomicalUnit:
            return "AU" ;
            
        default:
            break ;

    }

    throw library::core::error::runtime::Wrong("Unit") ;

    return String::Empty() ;

}

Real                            Length::SIRatio                             (   const   Length::Unit&               aUnit                                       )
{

    switch (aUnit)
    {

        case Length::Unit::Meter:
            return 1.0 ;

        case Length::Unit::Foot:
            return 0.3048 ;

        case Length::Unit::TerrestrialMile:
            return 1609.344 ;

        case Length::Unit::NauticalMile:
            return 1852.0 ;

        case Length::Unit::AstronomicalUnit:
            return 149597870700.0 ;

        default:
            break ;

    }

    throw library::core::error::runtime::Wrong("Unit") ;

    return Real::Undefined() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////