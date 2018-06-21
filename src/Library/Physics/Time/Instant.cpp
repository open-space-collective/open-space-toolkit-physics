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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{
namespace time
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Instant::Instant                            (           Uint64                      aNanosecondCountFromEpoch,
                                                                                        bool                        isPostEpoch,
                                                                                const   Scale&                      aTimeScale                                  )
                                :   count_({aNanosecondCountFromEpoch, isPostEpoch}),
                                    scale_(aTimeScale)
{

}

bool                            Instant::operator ==                        (   const   Instant&                    anInstant                                   ) const
{
    return count_ == ((scale_ == anInstant.scale_) ? anInstant.count_ : anInstant.inScale(scale_).count_) ;
}

bool                            Instant::operator !=                        (   const   Instant&                    anInstant                                   ) const
{
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

    library::core::utils::Print::Line(anOutputStream) << (anInstant.isDefined() ? anInstant.getString() : "Undefined") ;

    library::core::utils::Print::Footer(anOutputStream) ;

    return anOutputStream ;

}

bool                            Instant::isDefined                          ( ) const
{
    return scale_ != Scale::Undefined ;
}

Scale                           Instant::getScale                           ( ) const
{
    return scale_ ;
}

String                          Instant::getString                          ( ) const
{

    throw library::core::error::runtime::ToBeImplemented("Instant::getString") ;

    return String::Empty() ;

}

Instant                         Instant::inScale                            (   const   Scale&                      aTimeScale                                  ) const
{
    
    return Instant(Instant::ConvertCountScale(count_, scale_, aTimeScale), aTimeScale) ;
    
}

Instant                         Instant::Undefined                          ( )
{
    return Instant(0, true, Scale::Undefined) ;
}

// Instant                         Instant::DateTime                           (   const   time::DateTime&             aDateTime                                   )
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
                                    postEpoch_(isPostEpoch)
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

    return (!postEpoch_) && aCount.postEpoch_ ;

}

bool                            Instant::Count::operator >=                 (   const   Instant::Count&             aCount                                      ) const
{

    if (postEpoch_ == aCount.postEpoch_) // On the same side of the epoch
    {
        return postEpoch_ ? (countFromEpoch_ >= aCount.countFromEpoch_) : (aCount.countFromEpoch_ >= countFromEpoch_) ;
    }

    return (!postEpoch_) && aCount.postEpoch_ ;

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////