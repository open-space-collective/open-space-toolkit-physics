////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Units/Derived/Angle.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Units/Derived/Angle.hpp>
#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{
namespace units
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Angle::Angle                                (   const   Real&                       aValue,
                                                                                const   Angle::Unit&                aUnit                                       )
                                :   units::Unit(units::Unit::Type::Derived, aValue),
                                    unit_(aUnit)
{

}

bool                            Angle::operator ==                          (   const   Angle&                      anAngle                                     ) const
{

    if ((unit_ == Angle::Unit::Undefined) || (anAngle.unit_ == Angle::Unit::Undefined))
    {
        return false ;
    }

    switch (unit_)
    {

        case Angle::Unit::Radian:
            return this->accessValue() == Angle::ReduceRange(((anAngle.unit_ == Angle::Unit::Radian) ? anAngle.accessValue() : anAngle.in(Angle::Unit::Radian)), this->accessValue(), this->accessValue() + Real::TwoPi()) ;

        case Angle::Unit::Degree:
            return this->accessValue() == Angle::ReduceRange(((anAngle.unit_ == Angle::Unit::Degree) ? anAngle.accessValue() : anAngle.in(Angle::Unit::Degree)), this->accessValue(), this->accessValue() + 360.0) ;

        case Angle::Unit::Arcminute:
            return this->accessValue() == Angle::ReduceRange(((anAngle.unit_ == Angle::Unit::Arcminute) ? anAngle.accessValue() : anAngle.in(Angle::Unit::Arcminute)), this->accessValue(), this->accessValue() + 21600.0) ;

        case Angle::Unit::Arcsecond:
            return this->accessValue() == Angle::ReduceRange(((anAngle.unit_ == Angle::Unit::Arcsecond) ? anAngle.accessValue() : anAngle.in(Angle::Unit::Arcsecond)), this->accessValue(), this->accessValue() + 1296000.0) ;

        case Angle::Unit::Revolution:
            return this->accessValue() == Angle::ReduceRange(((anAngle.unit_ == Angle::Unit::Revolution) ? anAngle.accessValue() : anAngle.in(Angle::Unit::Revolution)), this->accessValue(), this->accessValue() + 1.0) ;

        default:
            throw library::core::error::runtime::Wrong("Unit") ;
            break ;

    }

    return false ;

}

bool                            Angle::operator !=                          (   const   Angle&                      anAngle                                     ) const
{
    return !((*this) == anAngle) ;
}

Angle                           Angle::operator +                           (   const   Angle&                      anAngle                                     ) const
{

    if ((unit_ == Angle::Unit::Undefined) || (anAngle.unit_ == Angle::Unit::Undefined))
    {
        throw library::core::error::runtime::Undefined("Angle") ;
    }

    return Angle((this->accessValue() + ((unit_ == anAngle.unit_) ? anAngle.accessValue() : anAngle.in(unit_))), unit_) ;

}

Angle                           Angle::operator -                           (   const   Angle&                      anAngle                                     ) const
{

    if ((unit_ == Angle::Unit::Undefined) || (anAngle.unit_ == Angle::Unit::Undefined))
    {
        throw library::core::error::runtime::Undefined("Angle") ;
    }

    return Angle((this->accessValue() - ((unit_ == anAngle.unit_) ? anAngle.accessValue() : anAngle.in(unit_))), unit_) ;

}

Angle                           Angle::operator *                           (   const   Real&                       aReal                                       ) const
{

    if (unit_ == Angle::Unit::Undefined)
    {
        throw library::core::error::runtime::Undefined("Angle") ;
    }

    if (!aReal.isDefined())
    {
        throw library::core::error::runtime::Undefined("Real") ;
    }

    return Angle((this->accessValue() * aReal), unit_) ;

}

Angle                           Angle::operator /                           (   const   Real&                       aReal                                       ) const
{

    if (unit_ == Angle::Unit::Undefined)
    {
        throw library::core::error::runtime::Undefined("Angle") ;
    }

    if (!aReal.isDefined())
    {
        throw library::core::error::runtime::Undefined("Real") ;
    }

    if (aReal.isZero())
    {
        throw library::core::error::RuntimeError("Cannot divide by zero.") ;
    }

    return Angle((this->accessValue() / aReal), unit_) ;

}

Angle&                          Angle::operator +=                          (   const   Angle&                      anAngle                                     )
{

    if ((unit_ == Angle::Unit::Undefined) || (anAngle.unit_ == Angle::Unit::Undefined))
    {
        throw library::core::error::runtime::Undefined("Angle") ;
    }

    this->accessValue() += ((unit_ == anAngle.unit_) ? anAngle.accessValue() : anAngle.in(unit_)) ;

    return (*this) ;

}

Angle&                          Angle::operator -=                          (   const   Angle&                      anAngle                                     )
{

    if ((unit_ == Angle::Unit::Undefined) || (anAngle.unit_ == Angle::Unit::Undefined))
    {
        throw library::core::error::runtime::Undefined("Angle") ;
    }

    this->accessValue() -= ((unit_ == anAngle.unit_) ? anAngle.accessValue() : anAngle.in(unit_)) ;

    return (*this) ;

}

Angle&                          Angle::operator *=                          (   const   Real&                       aReal                                       )
{

    if (unit_ == Angle::Unit::Undefined)
    {
        throw library::core::error::runtime::Undefined("Angle") ;
    }

    if (!aReal.isDefined())
    {
        throw library::core::error::runtime::Undefined("Real") ;
    }

    this->accessValue() *= aReal ;

    return (*this) ;

}

Angle&                          Angle::operator /=                          (   const   Real&                       aReal                                       )
{

    if (unit_ == Angle::Unit::Undefined)
    {
        throw library::core::error::runtime::Undefined("Angle") ;
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

Angle                           operator *                                  (   const   Real&                       aReal,
                                                                                const   Angle&                      anAngle                                     )
{

    if (!aReal.isDefined())
    {
        throw library::core::error::runtime::Undefined("Real") ;
    }

    if (anAngle.unit_ == Angle::Unit::Undefined)
    {
        throw library::core::error::runtime::Undefined("Angle") ;
    }
    
    return Angle((anAngle.accessValue() * aReal), anAngle.unit_) ;

}

                                Angle::operator library::math::geom::Angle  ( ) const
{
    
    if (!this->isDefined())
    {
        return library::math::geom::Angle::Undefined() ;
    }

    switch (unit_)
    {

        case Angle::Unit::Radian:
            return library::math::geom::Angle(this->accessValue(), library::math::geom::Angle::Unit::Radian) ;
        
        case Angle::Unit::Degree:
            return library::math::geom::Angle(this->accessValue(), library::math::geom::Angle::Unit::Degree) ;
        
        case Angle::Unit::Arcminute:
            return library::math::geom::Angle(this->accessValue(), library::math::geom::Angle::Unit::Arcminute) ;
        
        case Angle::Unit::Arcsecond:
            return library::math::geom::Angle(this->accessValue(), library::math::geom::Angle::Unit::Arcsecond) ;
        
        case Angle::Unit::Revolution:
            return library::math::geom::Angle(this->accessValue(), library::math::geom::Angle::Unit::Revolution) ;

        default:
            throw library::core::error::runtime::Wrong("Unit") ;
            break ;

    }

    return library::math::geom::Angle::Undefined() ;

}

std::ostream&                   operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Angle&                      anAngle                                     )
{

    library::core::utils::Print::Header(anOutputStream, "Angle") ;

    library::core::utils::Print::Line(anOutputStream) << "Value:" << anAngle.accessValue() ;
    library::core::utils::Print::Line(anOutputStream) << "Unit:" << Angle::StringFromUnit(anAngle.unit_) ;

    library::core::utils::Print::Footer(anOutputStream) ;

    return anOutputStream ;

}

bool                            Angle::isDefined                            ( ) const
{
    return units::Unit::isDefined() && (unit_ != Angle::Unit::Undefined) ;
}

Angle::Unit                     Angle::getUnit                              ( ) const
{
    return unit_ ;
}

Real                            Angle::in                                   (   const   Angle::Unit&                aUnit                                       ) const
{

    if (!this->isDefined())
    {
        return Real::Undefined() ;
    }

    if (unit_ == aUnit)
    {
        return this->accessValue() ;
    }

    return this->accessValue() * Angle::SIRatio(unit_) / Angle::SIRatio(aUnit) ;

}

Real                            Angle::inRadians                            ( ) const
{
    return this->in(Angle::Unit::Radian) ;
}

// Real                            Angle::inRadians                            (   const    Real&                      aLowerBound,
//                                                                                 const    Real&                      anUpperBound                                ) const
// {

// }

Real                            Angle::inDegrees                            ( ) const
{
    return this->in(Angle::Unit::Degree) ;
}

// Real                            Angle::inDegrees                            (   const    Real&                      aLowerBound,
//                                                                                 const    Real&                      anUpperBound                                ) const
// {

// }

Real                            Angle::inArcminutes                         ( ) const
{
    return this->in(Angle::Unit::Arcminute) ;
}

// Real                            Angle::inArcminutes                         (   const    Real&                      aLowerBound,
//                                                                                 const    Real&                      anUpperBound                                ) const
// {

// }

Real                            Angle::inArcseconds                         ( ) const
{
    return this->in(Angle::Unit::Arcsecond) ;
}

// Real                            Angle::inArcseconds                         (   const    Real&                      aLowerBound,
//                                                                                 const    Real&                      anUpperBound                                ) const
// {

// }

Real                            Angle::inRevolutions                        ( ) const
{
    return this->in(Angle::Unit::Revolution) ;
}

String                          Angle::toString                            ( ) const
{

    if (!this->isDefined())
    {
        return "Undef" ;
    }

    return this->accessValue().toString() + " [" + Angle::SymbolFromUnit(unit_) + "]" ;

}

Angle                           Angle::Undefined                            ( )
{
    return Angle(Real::Undefined(), Angle::Unit::Undefined) ;
}

Angle                           Angle::Radians                              (   const   Real&                       aValue                                      )
{
    return Angle(aValue, Angle::Unit::Radian) ;
}

Angle                           Angle::Degrees                              (   const   Real&                       aValue                                      )
{
    return Angle(aValue, Angle::Unit::Degree) ;
}

Angle                           Angle::Arcminutes                           (   const   Real&                       aValue                                      )
{
    return Angle(aValue, Angle::Unit::Arcminute) ;
}

Angle                           Angle::Arcseconds                           (   const   Real&                       aValue                                      )
{
    return Angle(aValue, Angle::Unit::Arcsecond) ;
}

Angle                           Angle::Revolutions                          (   const   Real&                       aValue                                      )
{
    return Angle(aValue, Angle::Unit::Revolution) ;
}

// Angle                            Angle::Parse                               (   const   String&                     aString                                     )
// {

// }

String                          Angle::StringFromUnit                       (   const   Angle::Unit&                aUnit                                       )
{

    switch (aUnit)
    {

        case Angle::Unit::Undefined:
            return "Undefined" ;
            
        case Angle::Unit::Radian:
            return "Radian" ;
            
        case Angle::Unit::Degree:
            return "Degree" ;
            
        case Angle::Unit::Arcminute:
            return "Arcminute" ;
            
        case Angle::Unit::Arcsecond:
            return "Arcsecond" ;

        case Angle::Unit::Revolution:
            return "Revolution" ;
            
        default:
            break ;

    }

    throw library::core::error::runtime::Wrong("Unit") ;

    return String::Empty() ;

}

String                          Angle::SymbolFromUnit                       (   const   Angle::Unit&               aUnit                                       )
{

    switch (aUnit)
    {

        case Angle::Unit::Radian:
            return "rad" ;
            
        case Angle::Unit::Degree:
            return "deg" ;
            
        case Angle::Unit::Arcminute:
            return "amin" ;
            
        case Angle::Unit::Arcsecond:
            return "asec" ;
            
        case Angle::Unit::Revolution:
            return "rev" ;
            
        default:
            break ;

    }

    throw library::core::error::runtime::Wrong("Unit") ;

    return String::Empty() ;

}

Real                            Angle::SIRatio                              (   const   Angle::Unit&                aUnit                                       )
{

    switch (aUnit)
    {

        case Angle::Unit::Radian:
            return 1.0 ;

        case Angle::Unit::Degree:
            return Real::Pi() / 180.0 ;

        case Angle::Unit::Arcminute:
            return Real::Pi() / 10800.0 ;

        case Angle::Unit::Arcsecond:
            return Real::Pi() / 648000.0 ;

        case Angle::Unit::Revolution:
            return Real::TwoPi() ;

        default:
            break ;

    }

    throw library::core::error::runtime::Wrong("Unit") ;

    return Real::Undefined() ;

}

Real                            Angle::ReduceRange                          (   const    Real&                      aValue,
                                                                                const    Real&                      aRangeLowerBound,
                                                                                const    Real&                      aRangeUpperBound                            )
{

    if ((aValue >= aRangeLowerBound) && (aValue < aRangeUpperBound)) // Value already in range
    {
        return aValue ;
    }

    Real value = aValue ;

    const Real range = aRangeUpperBound - aRangeLowerBound ;

    while (value < aRangeLowerBound) // [TBM] This is a STUPID implementation: just used as a logic placeholder... should be improved ASAP
    {
        value += range ;
    }
    
    while (value >= aRangeUpperBound) // [TBM] This is a STUPID implementation: just used as a logic placeholder... should be improved ASAP
    {
        value -= range ;
    }

    return value ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////