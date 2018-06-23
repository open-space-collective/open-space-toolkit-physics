////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Time/Date.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Time/Date.hpp>

#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{
namespace time
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Date::Date                                  (           Int16                       aYear,
                                                                                        Uint8                       aMonth,
                                                                                        Uint8                       aDay                                        )
                                :   defined_(true),
                                    year_(aYear),
                                    month_(aMonth),
                                    day_(aDay)
{

    Date::ValidateDate(year_, month_, day_) ;

}

bool                            Date::operator ==                           (   const   Date&                       aDate                                       ) const
{

    if ((!this->isDefined()) || (!aDate.isDefined()))
    {
        return false ;
    }

    return (year_ == aDate.year_) && (month_ == aDate.month_) && (day_ == aDate.day_) ;

}

bool                            Date::operator !=                           (   const   Date&                       aDate                                       ) const
{

    if ((!this->isDefined()) || (!aDate.isDefined()))
    {
        return true ;
    }

    return (year_ != aDate.year_) || (month_ != aDate.month_) || (day_ != aDate.day_) ;

}

std::ostream&                   operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Date&                       aDate                                       )
{

    library::core::utils::Print::Header(anOutputStream, "Date") ;

    library::core::utils::Print::Line(anOutputStream) << "Year:" << (aDate.isDefined() ? String::Format("{:d}", aDate.year_) : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Month:" << (aDate.isDefined() ? String::Format("{:d}", aDate.month_) : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Day:" << (aDate.isDefined() ? String::Format("{:d}", aDate.day_) : "Undefined") ;

    library::core::utils::Print::Footer(anOutputStream) ;

    return anOutputStream ;

}

bool                            Date::isDefined                             ( ) const
{
    return defined_ ;
}

Int16                           Date::getYear                               ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Date") ;
    }
    
    return year_ ;

}

Uint8                           Date::getMonth                              ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Date") ;
    }
    
    return month_ ;

}

Uint8                           Date::getDay                                ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Date") ;
    }
    
    return day_ ;

}

String                          Date::getString                             ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Date") ;
    }
    
    return String::Format("{0:d}-{1:02d}-{2:02d}", year_, month_, day_) ;

}

void                            Date::setYear                               (           Int16                       aYear                                       )
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Date") ;
    }

    Date::ValidateDate(aYear, month_, day_) ;
    
    year_ = aYear ;

}

void                            Date::setMonth                              (           Uint8                       aMonth                                      )
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Date") ;
    }

    Date::ValidateDate(year_, aMonth, day_) ;
    
    month_ = aMonth ;

}

void                            Date::setDay                                (           Uint8                       aDay                                        )
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Date") ;
    }

    Date::ValidateDate(year_, month_, aDay) ;
    
    day_ = aDay ;

}

Date                            Date::Undefined                             ( )
{
    return Date() ;
}

Date                            Date::J2000                                 ( )
{
    return Date(2000, 1, 1) ;
}

Date                            Date::GPS                                   ( )
{
    return Date(1980, 1, 6) ;
}

Date                            Date::Unix                                  ( )
{
    return Date(1970, 1, 1) ;
}

Date                            Date::JulianDate                            ( )
{
    return Date(-4712, 1, 1) ;
}

Date                            Date::ModifiedJulianDate                    ( )
{
    return Date(1858, 11, 17) ;
}

Date                            Date::Parse                                 (   const   String&                     aString                                     )
{

    if (aString.isEmpty())
    {
        throw library::core::error::runtime::Undefined("String") ;
    }

    boost::smatch match ;

    if (boost::regex_match(aString, match, boost::regex("^([-]?[0-9]+)-([0-9]{2})-([0-9]{2})$")))
    {

        try
        {

            const Int16 year = boost::lexical_cast<Int16>(match[1]) ;
            const Uint8 month = boost::lexical_cast<Int16>(match[2]) ;
            const Uint8 day = boost::lexical_cast<Int16>(match[3]) ;

            return Date(year, month, day) ;

        }
        catch (const boost::bad_lexical_cast& e)
        {
            throw library::core::error::RuntimeError("Cannot parse date string [" + aString + "] (parsing error).") ;
        }

    }
    else
    {
        throw library::core::error::RuntimeError("Cannot parse date string [" + aString + "].") ;
    }

    return Date::Undefined() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Date::Date                                  ( )
                                :   defined_(false),
                                    year_(0),
                                    month_(0),
                                    day_(0)
{

}

void                            Date::ValidateDate                          (           Int16                       aYear,
                                                                                        Uint8                       aMonth,
                                                                                        Uint8                       aDay                                        )
{

    (void) aYear ; // No validation required

    if ((aMonth == 0) || (aMonth > 12))
    {
        throw library::core::error::RuntimeError(String::Format("Month {} out of range [1 - 12].", aMonth)) ;
    }

    if ((aDay == 0) || (aDay > 31))
    {
        throw library::core::error::RuntimeError(String::Format("Day {} out of range [1 - 31].", aDay)) ;
    }

    // [TBI] Validate date

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////