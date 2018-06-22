////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Time/Instant.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Time/Instant.hpp>

#include <Library/Core/Containers/Array.hpp>
#include <Library/Core/Containers/Triple.hpp>
#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

#include <chrono>
#include <iomanip>
#include <iostream>
#include <stdlib.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{
namespace time
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//                                 Instant::Instant                            (           Uint64                      aNanosecondCountFromEpoch,
//                                                                                         bool                        isPostEpoch,
//                                                                                 const   Scale&                      aTimeScale                                  )
//                                 :   count_({aNanosecondCountFromEpoch, isPostEpoch}),
//                                     scale_(aTimeScale)
// {

// }

bool                            Instant::operator ==                        (   const   Instant&                    anInstant                                   ) const
{

    if ((!this->isDefined()) || (!anInstant.isDefined()))
    {
        return false ;
    }
    
    return count_ == ((scale_ == anInstant.scale_) ? anInstant.count_ : anInstant.inScale(scale_).count_) ;

}

bool                            Instant::operator !=                        (   const   Instant&                    anInstant                                   ) const
{

    if ((!this->isDefined()) || (!anInstant.isDefined()))
    {
        return true ;
    }
    
    return count_ != ((scale_ == anInstant.scale_) ? anInstant.count_ : anInstant.inScale(scale_).count_) ;

}

bool                            Instant::operator <                         (   const   Instant&                    anInstant                                   ) const
{

    if ((!this->isDefined()) || (!anInstant.isDefined()))
    {
        throw library::core::error::runtime::Undefined("Instant") ;
    }
    
    return count_ < ((scale_ == anInstant.scale_) ? anInstant.count_ : anInstant.inScale(scale_).count_) ;

}

bool                            Instant::operator <=                        (   const   Instant&                    anInstant                                   ) const
{

    if ((!this->isDefined()) || (!anInstant.isDefined()))
    {
        throw library::core::error::runtime::Undefined("Instant") ;
    }
    
    return count_ <= ((scale_ == anInstant.scale_) ? anInstant.count_ : anInstant.inScale(scale_).count_) ;

}

bool                            Instant::operator >                         (   const   Instant&                    anInstant                                   ) const
{

    if ((!this->isDefined()) || (!anInstant.isDefined()))
    {
        throw library::core::error::runtime::Undefined("Instant") ;
    }
    
    return count_ > ((scale_ == anInstant.scale_) ? anInstant.count_ : anInstant.inScale(scale_).count_) ;

}

bool                            Instant::operator >=                        (   const   Instant&                    anInstant                                   ) const
{

    if ((!this->isDefined()) || (!anInstant.isDefined()))
    {
        throw library::core::error::runtime::Undefined("Instant") ;
    }
    
    return count_ >= ((scale_ == anInstant.scale_) ? anInstant.count_ : anInstant.inScale(scale_).count_) ;

}

Instant                         Instant::operator +                         (   const   Duration&                   aDuration                                   ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Instant") ;
    }

    if (!aDuration.isDefined())
    {
        throw library::core::error::runtime::Undefined("Duration") ;
    }

    return Instant(count_ + aDuration.count_, scale_) ;

}

Instant                         Instant::operator -                         (   const   Duration&                   aDuration                                   ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Instant") ;
    }

    if (!aDuration.isDefined())
    {
        throw library::core::error::runtime::Undefined("Duration") ;
    }

    return Instant(count_ - aDuration.count_, scale_) ;

}

Duration                        Instant::operator -                         (   const   Instant&                    anInstant                                   ) const
{

    if ((!this->isDefined()) || (!anInstant.isDefined()))
    {
        throw library::core::error::runtime::Undefined("Instant") ;
    }

    const Instant::Count startCount = ((scale_ == anInstant.scale_) ? anInstant.count_ : anInstant.inScale(scale_).count_) ;
    const Instant::Count endCount = count_ ;

    if (startCount.postEpoch_ && endCount.postEpoch_) // Start and end instants are after epoch
    {
        return Duration(endCount.countFromEpoch_ - startCount.countFromEpoch_) ;
    }
    else if ((!startCount.postEpoch_) && (!endCount.postEpoch_)) // Start and end instants are before epoch
    {
        return Duration(startCount.countFromEpoch_ - endCount.countFromEpoch_) ;
    }
    else if ((!startCount.postEpoch_) && endCount.postEpoch_) // Start instant is before epoch and end instant is after epoch
    {
        return Duration(startCount.countFromEpoch_ + endCount.countFromEpoch_) ;
    }
    else // Start instant is after epoch and end instant is before epoch
    {
        return Duration(- endCount.countFromEpoch_ - startCount.countFromEpoch_) ;
    }

}

Instant&                        Instant::operator +=                        (   const   Duration&                   aDuration                                   )
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Instant") ;
    }

    if (!aDuration.isDefined())
    {
        throw library::core::error::runtime::Undefined("Duration") ;
    }

    count_ = count_ + aDuration.count_ ;

    return (*this) ;

}

Instant&                        Instant::operator -=                        (   const   Duration&                   aDuration                                   )
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Instant") ;
    }

    if (!aDuration.isDefined())
    {
        throw library::core::error::runtime::Undefined("Duration") ;
    }

    count_ = count_ - aDuration.count_ ;

    return (*this) ;

}

std::ostream&                   operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Instant&                    anInstant                                   )
{

    library::core::utils::Print::Header(anOutputStream, "Instant") ;

    library::core::utils::Print::Line(anOutputStream) << "Count:" << (anInstant.isDefined() ? anInstant.count_.getString() : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Scale:" << StringFromScale(anInstant.scale_) ;

    library::core::utils::Print::Footer(anOutputStream) ;

    return anOutputStream ;

}

bool                            Instant::isDefined                          ( ) const
{
    return scale_ != Scale::Undefined ;
}

bool                            Instant::isPostEpoch                        ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Instant") ;
    }
    
    return (*this) >= Instant::J2000() ;

}

Scale                           Instant::getScale                           ( ) const
{
    return scale_ ;
}

// Real                            Instant::getJulianDate                      ( ) const
// {

// }

// Real                            Instant::getModifiedJulianDate              ( ) const
// {

// }

time::DateTime                  Instant::getDateTime                        ( ) const
{

    using library::core::types::Uint8 ;

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Instant") ;
    }

    auto parseDateTimeString =
    [ ] (const String& aDateTimeString) -> std::chrono::time_point<std::chrono::system_clock>
    {

        std::istringstream stringStream(aDateTimeString) ;

        std::tm dateTime = {} ;
        
        stringStream >> std::get_time(&dateTime, "%Y-%m-%d %H:%M:%S") ;

        if (stringStream.fail())
        {
            throw library::core::error::RuntimeError("Cannot parse date time string [" + aDateTimeString + "].") ;
        }

        return std::chrono::system_clock::from_time_t(std::mktime(&dateTime)) ;

    } ;

    auto getTimePointString =
    [ ] (const std::chrono::time_point<std::chrono::system_clock>& aTimePoint) -> String
    {

        std::time_t time = std::chrono::system_clock::to_time_t(aTimePoint) ;

        std::stringstream stringStream ;

        stringStream << std::put_time(std::gmtime(&time), "%F %T %z") ;

        return stringStream.str() ;

    } ;

    // Epoch

    std::chrono::time_point<std::chrono::system_clock> epochTimePoint = parseDateTimeString("2000-01-01 12:00:00") ; // J2000 [TT]

    std::chrono::time_point<std::chrono::system_clock> timePoint = epochTimePoint + std::chrono::nanoseconds(this->inScale(Scale::TT).count_.countFromEpoch_) ; // [TBM] + or -

    std::cout << "AAA = " << getTimePointString(timePoint) << std::endl ;

    std::time_t time = std::chrono::system_clock::to_time_t(timePoint) ;

    std::tm tm = *std::gmtime(&time) ;

    int year = 1900 + tm.tm_year ;
    Uint8 month = tm.tm_mon + 1 ;
    Uint8 day = tm.tm_mday ;

    Uint8 hours = tm.tm_hour ;
    Uint8 minutes = tm.tm_min ;
    Uint8 seconds = tm.tm_sec ;

    auto fraction = timePoint - std::chrono::time_point_cast<std::chrono::seconds>(timePoint) ;

    Uint8 milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(fraction).count() ;
    Uint8 microseconds = std::chrono::duration_cast<std::chrono::microseconds>(fraction).count() ;
    Uint8 nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(fraction).count() ;

    std::cout << "year: " << year << std::endl ;
    std::cout << "month: " << month << std::endl ;
    std::cout << "day: " << day << std::endl ;
    std::cout << "hours: " << hours << std::endl ;
    std::cout << "minutes: " << minutes << std::endl ;
    std::cout << "seconds: " << seconds << std::endl ;
    std::cout << "milliseconds: " << milliseconds << std::endl ;
    std::cout << "microseconds: " << microseconds << std::endl ;
    std::cout << "nanoseconds: " << nanoseconds << std::endl ;

    // return DateTime::Undefined() ;

    // using boost::posix_time::ptime ;
	// using boost::posix_time::microsec_clock ;
	// using boost::gregorian::day_clock ;
	// using boost::gregorian::date ;
	// using boost::posix_time::time_duration ;
	// using boost::posix_time::time_period ;

	// using namespace boost::posix_time ;

	// CountFromEpoch 				nanosecondsSinceJ2000_timeScale 				=		convertTimeScale(nanosecondsCountSinceJ2000_TT_, Time::Scale::TT, aTimeScale) ;
	
	// date 						tmp_dateJ2000(2000, 1, 1) ;
	// time_duration 				tmp_durationJ2000 								=		hours(12) ;
	// ptime 						tmp_timeJ2000(tmp_dateJ2000, tmp_durationJ2000) ;
	// ptime 						tmp_timeJ2000Day(tmp_dateJ2000, hours(0)) ;
	
	// time_duration 				tmp_durationSinceJ2000 							=		microseconds(signOfCount(nanosecondsSinceJ2000_timeScale) * std::floor(nanosecondsSinceJ2000_timeScale.count_ / 1000.0)) ;

	// ptime 						tmp_time 										=		tmp_timeJ2000 + tmp_durationSinceJ2000 ;

	// uint 						tmp_year 										=		uint(tmp_time.date().year()) ;
	// uint 						tmp_month 										=		uint(tmp_time.date().month()) ;
	// uint 						tmp_day 										=		uint(tmp_time.date().day()) ;

	// date 						tmp_dayDate(tmp_year, tmp_month, tmp_day) ;
	// ptime 						tmp_timeDay(tmp_dayDate, seconds(0)) ;
	
	// int64_t 					tmp_daysCountFromJ2000Day 						=		std::floor(time_period(tmp_timeJ2000Day, tmp_timeDay).length().hours() / 24.0) ;
	
	// uint64_t 					tmp_nanosecondsCountOfDay 						=		0 ;
	
	// if (nanosecondsSinceJ2000_timeScale.positiveCount_)
	// {
	// 	tmp_nanosecondsCountOfDay 												=		uint64_t(nanosecondsSinceJ2000_timeScale.count_) - uint64_t(std::abs(tmp_daysCountFromJ2000Day) * 24.0 * 3600.0 * 1e9) + uint64_t(12.0 * 3600.0 * 1e9) ;
	// }
	// else
	// {
	// 	tmp_nanosecondsCountOfDay 												=		uint64_t(std::abs(tmp_daysCountFromJ2000Day) * 24.0 * 3600.0 * 1e9) - uint64_t(nanosecondsSinceJ2000_timeScale.count_) + uint64_t(12.0 * 3600.0 * 1e9) ;
	// }

	// uint 						tmp_hours 										=		std::floor(tmp_nanosecondsCountOfDay / (3600.0 * 1e9)) ;
	// uint 						tmp_minutes										=		std::floor((tmp_nanosecondsCountOfDay - tmp_hours * 3600.0 * 1e9) / (60.0 * 1e9)) ;
	// uint 						tmp_seconds 									=		std::floor((tmp_nanosecondsCountOfDay - tmp_hours * 3600.0 * 1e9 - tmp_minutes * 60.0 * 1e9) / (1e9)) ;
	// uint 						tmp_milliseconds 								=		std::floor((tmp_nanosecondsCountOfDay - tmp_hours * 3600.0 * 1e9 - tmp_minutes * 60.0 * 1e9 - tmp_seconds * 1e9) / (1e6)) ;
	// uint 						tmp_microseconds 								=		std::floor((tmp_nanosecondsCountOfDay - tmp_hours * 3600.0 * 1e9 - tmp_minutes * 60.0 * 1e9 - tmp_seconds * 1e9 - tmp_milliseconds * 1e6) / (1e3)) ;
	// uint 						tmp_nanoseconds 								=		std::floor(tmp_nanosecondsCountOfDay - tmp_hours * 3600.0 * 1e9 - tmp_minutes * 60.0 * 1e9 - tmp_seconds * 1e9 - tmp_milliseconds * 1e6  - tmp_microseconds * 1e3) ;

	// return AxelTools::time::CalendarDate(aTimeScale, tmp_year, tmp_month, tmp_day, tmp_hours, tmp_minutes, tmp_seconds, tmp_milliseconds, tmp_microseconds, tmp_nanoseconds) ;

}

// Uint64                          Instant::getCountSinceEpoch                 (   const   units::Time&                aTimeUnit,
//                                                                                 const   Instant&                    anEpoch                                     )
// {

// }

String                          Instant::getString                          ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Instant") ;
    }

    return this->getDateTime().getString() ;

}

Instant                         Instant::inScale                            (   const   Scale&                      aTimeScale                                  ) const
{
    return Instant(Instant::ConvertCountScale(count_, scale_, aTimeScale), aTimeScale) ;
}

Instant                         Instant::Undefined                          ( )
{
    return Instant({ 0, true }, Scale::Undefined) ;
}

Instant                         Instant::Now                                ( )
{

    auto parseDateTimeString =
    [ ] (const String& aDateTimeString) -> std::chrono::time_point<std::chrono::system_clock>
    {

        std::istringstream stringStream(aDateTimeString) ;

        std::tm dateTime = {} ;
        
        stringStream >> std::get_time(&dateTime, "%Y-%m-%d %H:%M:%S") ;

        if (stringStream.fail())
        {
            throw library::core::error::RuntimeError("Cannot parse date time string [" + aDateTimeString + "].") ;
        }

        return std::chrono::system_clock::from_time_t(std::mktime(&dateTime)) ;

    } ;

    auto getTimePointString =
    [ ] (const std::chrono::time_point<std::chrono::system_clock>& aTimePoint) -> String
    {

        std::time_t time = std::chrono::system_clock::to_time_t(aTimePoint) ;

        std::stringstream stringStream ;

        stringStream << std::put_time(std::gmtime(&time), "%F %T %z") ;

        return stringStream.str() ;

    } ;

    // Epoch

    std::chrono::time_point<std::chrono::system_clock> epochTimePoint = parseDateTimeString("2000-01-01 12:00:00") ; // J2000
    // std::chrono::time_point<std::chrono::system_clock> epochTimePoint = parseDateTimeString("2005-12-31 23:59:59") ;

    // std::cout << "Epoch: " << getTimePointString(epochTimePoint) << std::endl ;

    // Now

    std::chrono::time_point<std::chrono::system_clock> nowTimePoint = std::chrono::system_clock::now() ;
    // std::chrono::time_point<std::chrono::system_clock> nowTimePoint = parseDateTimeString("2006-01-01 00:00:01") ;

    // std::cout << "Now: " << getTimePointString(nowTimePoint) << std::endl ;

    // Difference

    auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(nowTimePoint - epochTimePoint) ;

    // std::cout << "Delta: " << nanoseconds.count() << " [ns]" << std::endl ;

    // Output

    Instant::Count count_UTC = {nanoseconds.count(), (nanoseconds.count() >= 0)} ;

    // std::cout << "count_UTC = " << count_UTC.countFromEpoch_ << std::endl ;

    // return Instant(count_UTC, Scale::UTC) ;

    Instant::Count count_TT = Instant::TT_TAI(Instant::TAI_UTC(count_UTC)) ;

    // std::cout << "count_TT   = " << count_TT.countFromEpoch_ << std::endl ;

    return Instant(count_TT, Scale::TT) ;

}

Instant                         Instant::J2000                              ( )
{
    return Instant({ 0, true }, Scale::TT) ;
}

// Instant                         Instant::DateTime                           (   const   time::DateTime&             aDateTime                                   )
// {

// }

// Instant                         Instant::JulianDate                         (   const   Real&                       aJulianDate,
//                                                                                 const   Scale&                      aTimeScale                                  )
// {

// }

// Instant                         Instant::ModifiedJulianDate                 (   const   Real&                       aModifiedJulianDate,
//                                                                                 const   Scale&                      aTimeScale                                  )
// {

// }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Instant::Instant                            (   const   Instant::Count&             aCount,
                                                                                const   Scale&                      aTimeScale                                  )
                                :   count_(aCount),
                                    scale_(aTimeScale)    
{

}

Instant::Count                  Instant::ConvertCountScale                  (   const   Instant::Count&             aCount,
                                                                                const   Scale&                      anInputTimeScale,
                                                                                const   Scale&                      anOutputTimeScale                           )
{

    Instant::Count count_TT = {0, true} ;

    switch (anInputTimeScale)
    {

        case Scale::UTC:
            count_TT = Instant::TT_TAI(Instant::TAI_UTC(aCount)) ;
            break ;

        case Scale::TT:
            count_TT = aCount ;
            break ;

        case Scale::TAI:
            count_TT = Instant::TT_TAI(aCount) ;
            break ;

        case Scale::UT1:
            count_TT = Instant::TT_TAI(Instant::TAI_UTC(Instant::UTC_UT1(aCount))) ;
            break ;

        case Scale::TCG:
            throw library::core::error::runtime::ToBeImplemented("TCG") ;
            break ;

        case Scale::TCB:
            throw library::core::error::runtime::ToBeImplemented("TCB") ;
            break ;

        case Scale::TDB:
            throw library::core::error::runtime::ToBeImplemented("TDB") ;
            break ;

        case Scale::GMST:
            throw library::core::error::runtime::ToBeImplemented("GMST") ;
            break ;

        case Scale::GPST:
            count_TT = Instant::TT_TAI(Instant::TAI_GPST(aCount)) ;
            break ;

        case Scale::GST:
            throw library::core::error::runtime::ToBeImplemented("GST") ;
            break ;

        case Scale::GLST:
            throw library::core::error::runtime::ToBeImplemented("GLST") ;
            break ;

        case Scale::BDT:
            throw library::core::error::runtime::ToBeImplemented("BDT") ;
            break ;

        case Scale::QZSST:
            throw library::core::error::runtime::ToBeImplemented("QZSST") ;
            break ;

        case Scale::IRNSST:
            throw library::core::error::runtime::ToBeImplemented("IRNSST") ;
            break ;

        default:
            throw library::core::error::runtime::Wrong("Time scale") ;
            break ;

    }
    
    switch (anOutputTimeScale)
    {

        case Scale::UTC:
            return Instant::UTC_TAI(Instant::TAI_TT(count_TT)) ;

        case Scale::TT:
            return count_TT ;

        case Scale::TAI:
            return Instant::TAI_TT(count_TT) ;

        case Scale::UT1:
            return Instant::UT1_UTC(Instant::UTC_TAI(Instant::TAI_TT(count_TT))) ;

        case Scale::TCG:
            throw library::core::error::runtime::ToBeImplemented("TCG") ;
            break ;

        case Scale::TCB:
            throw library::core::error::runtime::ToBeImplemented("TCB") ;
            break ;

        case Scale::TDB:
            throw library::core::error::runtime::ToBeImplemented("TDB") ;
            break ;

        case Scale::GMST:
            throw library::core::error::runtime::ToBeImplemented("GMST") ;
            break ;

        case Scale::GPST:
            return Instant::GPST_TAI(Instant::TAI_TT(count_TT)) ;

        case Scale::GST:
            throw library::core::error::runtime::ToBeImplemented("GST") ;
            break ;

        case Scale::GLST:
            throw library::core::error::runtime::ToBeImplemented("GLST") ;
            break ;

        case Scale::BDT:
            throw library::core::error::runtime::ToBeImplemented("BDT") ;
            break ;

        case Scale::QZSST:
            throw library::core::error::runtime::ToBeImplemented("QZSST") ;
            break ;

        case Scale::IRNSST:
            throw library::core::error::runtime::ToBeImplemented("IRNSST") ;
            break ;

        default:
            throw library::core::error::runtime::Wrong("Time scale") ;
            break ;

    }

    return Instant::Count(0, true) ;

}

Real                            Instant::ModifiedJulianDateFromJulianDate   (   const   Real&                       aJulianDate                                 )
{
    return aJulianDate - 2400000.5 ; // MJD = JD - 2400000.5 [day]
}

Real                            Instant::JulianDateFromModifiedJulianDate   (   const   Real&                       aModifiedJulianDate                         )
{
    return aModifiedJulianDate + 2400000.5 ; // JD = MJD + 2400000.5 [day]
}

Instant::Count                  Instant::UTC_TAI                            (   const   Instant::Count&             aCount_TAI                                  )
{
    return aCount_TAI - Instant::dAT_TAI(aCount_TAI) ; // UTC = TAI - dAT
}

Instant::Count                  Instant::TAI_UTC                            (   const   Instant::Count&             aCount_UTC                                  )
{
    return aCount_UTC + Instant::dAT_UTC(aCount_UTC) ; // TAI = UTC + dAT
}

Instant::Count                  Instant::TAI_TT                             (   const   Instant::Count&             aCount_TT                                   )
{
    return aCount_TT - Int64(32184000000) ; // TAI = TT - 32.184 [s]
}

Instant::Count                  Instant::TT_TAI                             (   const   Instant::Count&             aCount_TAI                                  )
{
    return aCount_TAI + Int64(32184000000) ; // TT = TAI + 32.184 [s]
}

Instant::Count                  Instant::UT1_UTC                            (   const   Instant::Count&             aCount_UTC                                  )
{
    return aCount_UTC + Instant::DUT1_UTC(aCount_UTC) ; // UT1 = UTC + DUT1
}

Instant::Count                  Instant::UTC_UT1                            (   const   Instant::Count&             aCount_UT1                                  )
{
    return aCount_UT1 - Instant::DUT1_UT1(aCount_UT1) ; // UTC = UT1 - DUT1
}

Instant::Count                  Instant::GPST_TAI                           (   const   Instant::Count&             aCount_TAI                                  )
{
    return aCount_TAI - Int64(19000000000) ; // TAI = GPST - 19 [s]
}

Instant::Count                  Instant::TAI_GPST                           (   const   Instant::Count&             aCount_GPST                                 )
{
    return aCount_GPST + Int64(19000000000) ; // GPST = TAI + 19 [s]
}

Int64                           Instant::dAT_UTC                            (   const   Instant::Count&             aCount_UTC                                  )
{

    // [TBI] Implement dAT automatic manager

    using library::core::ctnr::Array ;
    using library::core::ctnr::Triple ;

    if (aCount_UTC.postEpoch_)
    {

        static const Array<Triple<Uint64, Uint64, Int64>> dATMap =
        {
            { 536500800000000000, 999999999999999999, 37000000000 },            // December 2016    >   +Inf            : dAT =   37 [s]
            { 488980800000000000, 536500800000000000, 36000000000 },            // June 2015        >   December 2016   : dAT =   36 [s]
            { 394372800000000000, 488980800000000000, 35000000000 },            // June 2012        >   June 2015       : dAT =   35 [s]
            { 284040000000000000, 394372800000000000, 34000000000 },            // December 2008    >   June 2012       : dAT =   34 [s]
            { 189345600000000000, 284040000000000000, 33000000000 },            // December 2005    >   December 2008   : dAT =   33 [s]
            { 000000000000000000, 189345600000000000, 32000000000 }             // Epoch            >   December 2005   : dAT =   32 [s]
        } ;

        if (dATMap.accessFirst().first <= aCount_UTC.countFromEpoch_)
        {
            return dATMap.accessFirst().third ;
        }

        for (const auto& dATIt: dATMap)
        {

            if ((dATIt.first <= aCount_UTC.countFromEpoch_) && (aCount_UTC.countFromEpoch_ < dATIt.second))
            {
                return dATIt.third ;
            }

        }

    }
    else
    {

        static const Array<Triple<Uint64, Uint64, Int64>> dATMap =
        {
            { 000000000000000000,  31579200000000000, 32000000000 },            // Epoch            <   December 1998   : dAT =   32 [s]
            {  31579200000000000,  79012800000000000, 31000000000 },            // December 1998    <   June 1997       : dAT =   31 [s]
            {  79012800000000000, 126273600000000000, 30000000000 },            // June 1997        <   December 1995   : dAT =   30 [s]
            { 126273600000000000, 173707200000000000, 29000000000 },            // December 1995    <   June 1994       : dAT =   29 [s]
            { 173707200000000000, 205243200000000000, 28000000000 },            // June 1994        <   June 1993       : dAT =   28 [s]
            { 205243200000000000, 236779200000000000, 27000000000 },            // June 1993        <   June 1992       : dAT =   27 [s]
            { 236779200000000000, 284040000000000000, 26000000000 },            // June 1992        <   December 1990   : dAT =   26 [s]
            { 284040000000000000, 315576000000000000, 25000000000 },            // December 1990    <   December 1989   : dAT =   25 [s]
            { 315576000000000000, 378734400000000000, 24000000000 },            // December 1989    <   December 1987   : dAT =   24 [s]
            { 378734400000000000, 457704000000000000, 23000000000 },            // December 1987    <   June 1985       : dAT =   23 [s]
            { 457704000000000000, 520862400000000000, 22000000000 },            // June 1985        <   June 1983       : dAT =   22 [s]
            { 520862400000000000, 552398400000000000, 21000000000 },            // June 1983        <   June 1982       : dAT =   21 [s]
            { 552398400000000000, 583934400000000000, 20000000000 },            // June 1982        <   June 1981       : dAT =   20 [s]
            { 583934400000000000, 631195200000000000, 19000000000 }             // June 1981        <   December 1979   : dAT =   19 [s]
        } ;
        
        for (const auto& dATIt: dATMap)
        {

            if ((dATIt.first < aCount_UTC.countFromEpoch_) && (aCount_UTC.countFromEpoch_ <= dATIt.second))
            {
                return dATIt.third ;
            }

        }

        throw library::core::error::RuntimeError("dAT out of bounds.") ;

    }

    return 0 ;

}

Int64                           Instant::dAT_TAI                            (   const   Instant::Count&             aCount_TAI                                  )
{
    
    // [TBI] Implement dAT automatic manager

    using library::core::ctnr::Array ;
    using library::core::ctnr::Triple ;

    if (aCount_TAI.postEpoch_)
    {

        static const Array<Triple<Uint64, Uint64, Int64>> dATMap =
        {
            { 536500800000000000 + 36000000000, 999999999999999999 + 00000000000, 37000000000 },            // December 2016    >   +Inf            : dAT =   37 [s]
            { 488980800000000000 + 35000000000, 536500800000000000 + 36000000000, 36000000000 },            // June 2015        >   December 2016   : dAT =   36 [s]
            { 394372800000000000 + 34000000000, 488980800000000000 + 35000000000, 35000000000 },            // June 2012        >   June 2015       : dAT =   35 [s]
            { 284040000000000000 + 33000000000, 394372800000000000 + 34000000000, 34000000000 },            // December 2008    >   June 2012       : dAT =   34 [s]
            { 189345600000000000 + 32000000000, 284040000000000000 + 33000000000, 33000000000 },            // December 2005    >   December 2008   : dAT =   33 [s]
            { 000000000000000000 + 31000000000, 189345600000000000 + 32000000000, 32000000000 },            // Epoch - 31 [s]   >   December 2005   : dAT =   32 [s]
            { 000000000000000000 + 00000000000, 000000000000000000 + 31000000000, 32000000000 }             // Epoch            >   Epoch - 31 [s]  : dAT =   32 [s]
        } ;

        if (dATMap.accessFirst().first <= aCount_TAI.countFromEpoch_)
        {
            return dATMap.accessFirst().third ;
        }

        for (const auto& dATIt: dATMap)
        {

            if ((dATIt.first <= aCount_TAI.countFromEpoch_) && (aCount_TAI.countFromEpoch_ < dATIt.second))
            {
                return dATIt.third ;
            }

        }

    }
    else
    {

        static const Array<Triple<Uint64, Uint64, Int64>> dATMap =
        {
            { 000000000000000000 - 00000000000,  31579200000000000 - 31000000000, 32000000000 },            // Epoch            <   December 1998   : dAT =   32 [s]
            {  31579200000000000 - 31000000000,  79012800000000000 - 30000000000, 31000000000 },            // December 1998    <   June 1997       : dAT =   31 [s]
            {  79012800000000000 - 30000000000, 126273600000000000 - 29000000000, 30000000000 },            // June 1997        <   December 1995   : dAT =   30 [s]
            { 126273600000000000 - 29000000000, 173707200000000000 - 28000000000, 29000000000 },            // December 1995    <   June 1994       : dAT =   29 [s]
            { 173707200000000000 - 28000000000, 205243200000000000 - 27000000000, 28000000000 },            // June 1994        <   June 1993       : dAT =   28 [s]
            { 205243200000000000 - 27000000000, 236779200000000000 - 26000000000, 27000000000 },            // June 1993        <   June 1992       : dAT =   27 [s]
            { 236779200000000000 - 26000000000, 284040000000000000 - 25000000000, 26000000000 },            // June 1992        <   December 1990   : dAT =   26 [s]
            { 284040000000000000 - 25000000000, 315576000000000000 - 24000000000, 25000000000 },            // December 1990    <   December 1989   : dAT =   25 [s]
            { 315576000000000000 - 24000000000, 378734400000000000 - 23000000000, 24000000000 },            // December 1989    <   December 1987   : dAT =   24 [s]
            { 378734400000000000 - 23000000000, 457704000000000000 - 22000000000, 23000000000 },            // December 1987    <   June 1985       : dAT =   23 [s]
            { 457704000000000000 - 22000000000, 520862400000000000 - 21000000000, 22000000000 },            // June 1985        <   June 1983       : dAT =   22 [s]
            { 520862400000000000 - 21000000000, 552398400000000000 - 20000000000, 21000000000 },            // June 1983        <   June 1982       : dAT =   21 [s]
            { 552398400000000000 - 20000000000, 583934400000000000 - 19000000000, 20000000000 },            // June 1982        <   June 1981       : dAT =   20 [s]
            { 583934400000000000 - 19000000000, 631195200000000000 - 18000000000, 19000000000 }             // June 1981        <   December 1979   : dAT =   19 [s]
        } ;
        
        for (const auto& dATIt: dATMap)
        {

            if ((dATIt.first < aCount_TAI.countFromEpoch_) && (aCount_TAI.countFromEpoch_ <= dATIt.second))
            {
                return dATIt.third ;
            }

        }

        throw library::core::error::RuntimeError("dAT out of bounds.") ;

    }

    return 0 ;

}

Int64                           Instant::DUT1_UTC                           (   const   Instant::Count&             aCount_UTC                                  )
{

    (void) aCount_UTC ;
    
    throw library::core::error::runtime::ToBeImplemented("DUT1_UTC") ;

    return 0 ;

}

Int64                           Instant::DUT1_UT1                           (   const   Instant::Count&             aCount_UT1                                  )
{

    (void) aCount_UT1 ;
    
    throw library::core::error::runtime::ToBeImplemented("DUT1_UT1") ;

    return 0 ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Instant::Count::Count                       (           Uint64                      aNanosecondCountFromEpoch,
                                                                                        bool                        isPostEpoch                                 )
                                :   countFromEpoch_(aNanosecondCountFromEpoch),
                                    postEpoch_((aNanosecondCountFromEpoch != 0) ? isPostEpoch : true)
{

}

bool                            Instant::Count::operator ==                 (   const   Instant::Count&             aCount                                      ) const
{
    return (countFromEpoch_ == aCount.countFromEpoch_) && (postEpoch_ == aCount.postEpoch_) ;
}

bool                            Instant::Count::operator !=                 (   const   Instant::Count&             aCount                                      ) const
{
    return (countFromEpoch_ != aCount.countFromEpoch_) || (postEpoch_ != aCount.postEpoch_) ;
}

bool                            Instant::Count::operator <                  (   const   Instant::Count&             aCount                                      ) const
{

    if (postEpoch_ == aCount.postEpoch_) // On the same side of the epoch
    {
        return postEpoch_ ? (countFromEpoch_ < aCount.countFromEpoch_) : (aCount.countFromEpoch_ < countFromEpoch_) ;
    }

    return (!postEpoch_) && aCount.postEpoch_ ;

}

bool                            Instant::Count::operator <=                 (   const   Instant::Count&             aCount                                      ) const
{

    if (postEpoch_ == aCount.postEpoch_) // On the same side of the epoch
    {
        return postEpoch_ ? (countFromEpoch_ <= aCount.countFromEpoch_) : (aCount.countFromEpoch_ <= countFromEpoch_) ;
    }

    return (!postEpoch_) && aCount.postEpoch_ ;

}

bool                            Instant::Count::operator >                  (   const   Instant::Count&             aCount                                      ) const
{

    if (postEpoch_ == aCount.postEpoch_) // On the same side of the epoch
    {
        return postEpoch_ ? (countFromEpoch_ > aCount.countFromEpoch_) : (aCount.countFromEpoch_ > countFromEpoch_) ;
    }

    return postEpoch_ && (!aCount.postEpoch_) ;

}

bool                            Instant::Count::operator >=                 (   const   Instant::Count&             aCount                                      ) const
{

    if (postEpoch_ == aCount.postEpoch_) // On the same side of the epoch
    {
        return postEpoch_ ? (countFromEpoch_ >= aCount.countFromEpoch_) : (aCount.countFromEpoch_ >= countFromEpoch_) ;
    }

    return postEpoch_ && (!aCount.postEpoch_) ;

}

Instant::Count                  Instant::Count::operator +                  (   const   Instant::Count&             aCount                                      ) const
{

    // [TBI] Check count overflow

    if (aCount.countFromEpoch_ <= countFromEpoch_) // Displacement lower than count from epoch: we remain on the same epoch side
    {
        return postEpoch_ ? Count((countFromEpoch_ + aCount.countFromEpoch_), true) : Count((countFromEpoch_ - aCount.countFromEpoch_), false) ;
    }
    else // Displacement greater than count from epoch: we switch epoch side
    {

        if ((postEpoch_) && (aCount.postEpoch_)) // Count is after epoch and displacement is positive
        {
            return Count((countFromEpoch_ + aCount.countFromEpoch_), true) ;
        }
        else if ((!postEpoch_) && (!aCount.postEpoch_)) // Count is before epoch and displacement is negative
        {
            return Count((countFromEpoch_ - aCount.countFromEpoch_), false) ;
        }
        else // Count and displacement of opposite directions
        {
            return Count((aCount.countFromEpoch_ - countFromEpoch_), (!postEpoch_)) ;
        }

    }

}

Instant::Count                  Instant::Count::operator +                  (           Int64                       aNanosecondDisplacement                     ) const
{

    // [TBI] Check count overflow

    if (static_cast<Uint64>(std::abs(aNanosecondDisplacement)) <= countFromEpoch_) // Displacement lower than count from epoch: we remain on the same epoch side
    {
        return postEpoch_ ? Count((countFromEpoch_ + aNanosecondDisplacement), true) : Count((countFromEpoch_ - aNanosecondDisplacement), false) ;
    }
    else // Displacement greater than count from epoch: we switch epoch side
    {

        if ((postEpoch_) && (aNanosecondDisplacement >= 0)) // Count is after epoch and displacement is positive
        {
            return Count((countFromEpoch_ + aNanosecondDisplacement), true) ;
        }
        else if ((!postEpoch_) && (aNanosecondDisplacement < 0)) // Count is before epoch and displacement is negative
        {
            return Count((countFromEpoch_ - aNanosecondDisplacement), false) ;
        }
        else // Count and displacement of opposite directions
        {
            return Count((std::abs(aNanosecondDisplacement) - countFromEpoch_), (!postEpoch_)) ;
        }

    }

}

Instant::Count                  Instant::Count::operator -                  (           Int64                       aNanosecondDisplacement                     ) const
{
    return (*this) + (-aNanosecondDisplacement) ;
}

String                          Instant::Count::getString                   ( ) const
{

    using library::core::types::Integer ;
    
    return postEpoch_ ? ("+" + std::to_string(countFromEpoch_)) : ("-" + std::to_string(countFromEpoch_)) ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////