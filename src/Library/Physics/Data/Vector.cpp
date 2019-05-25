////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library ▸ Physics
/// @file           Library/Physics/Data/Vector.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Data/Vector.hpp>

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

                                Vector::Vector                              (   const   Vector3d&                   aValue,
                                                                                const   Unit&                       aUnit,
                                                                                const   Shared<const Frame>&        aFrameSPtr                                  )
                                :   value_(aValue),
                                    unit_(aUnit),
                                    frameSPtr_(aFrameSPtr)
{

}

bool                            Vector::operator ==                         (   const   Vector&                     aVector                                     ) const
{

    if ((!this->isDefined()) || (!aVector.isDefined()))
    {
        return false ;
    }

    return (value_ == aVector.value_) && (unit_ == aVector.unit_) && (frameSPtr_ == aVector.frameSPtr_) ;

}

bool                            Vector::operator !=                         (   const   Vector&                     aVector                                     ) const
{
    return !((*this) == aVector) ;
}

std::ostream&                   operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Vector&                     aVector                                     )
{

    library::core::utils::Print::Header(anOutputStream, "Vector") ;

    library::core::utils::Print::Line(anOutputStream) << "Value:"               << (aVector.value_.isDefined() ? aVector.value_.toString() : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Unit:"                << (aVector.unit_.isDefined() ? aVector.unit_.toString() : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Frame:"                << (((aVector.frameSPtr_ != nullptr) && (aVector.frameSPtr_->isDefined())) ? aVector.frameSPtr_->getName() : "Undefined") ;

    library::core::utils::Print::Footer(anOutputStream) ;

    return anOutputStream ;

}

bool                            Vector::isDefined                           ( ) const
{
    return value_.isDefined() && unit_.isDefined() && (frameSPtr_ != nullptr) && frameSPtr_->isDefined() ;
}

Vector3d                        Vector::getValue                            ( ) const
{
    return value_ ;
}

Unit                            Vector::getUnit                             ( ) const
{
    return unit_ ;
}

Shared<const Frame>             Vector::getFrame                            ( ) const
{
    return frameSPtr_ ;
}

Vector                          Vector::inUnit                              (   const   Unit&                       aUnit                                       ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Scalar") ;
    }

    return { value_ * unit_.ratioTo(aUnit), aUnit, frameSPtr_ } ;

}

Vector                          Vector::inFrame                             (   const   Shared<const Frame>&        aFrameSPtr,
                                                                                const   Instant&                    anInstant                                   ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Scalar") ;
    }

    return { frameSPtr_->getTransformTo(aFrameSPtr, anInstant).applyToVector(value_), unit_, aFrameSPtr } ;

}

String                          Vector::toString                            (   const   Integer&                    aPrecision                                  ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Scalar") ;
    }

    return String::Format("{} [{}] @ {}", value_.toString(aPrecision), unit_.toString(), frameSPtr_->getName()) ;

}

Vector                          Vector::Undefined                           ( )
{
    return { Vector3d::Undefined(), Unit::Undefined(), Frame::Undefined() } ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
