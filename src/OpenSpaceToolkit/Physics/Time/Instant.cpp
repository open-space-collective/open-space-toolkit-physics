/// Apache License 2.0

#include <chrono>
#include <iomanip>
#include <stdlib.h>

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Container/Triple.hpp>
#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

namespace ostk
{
namespace physics
{
namespace time
{

bool Instant::operator==(const Instant& anInstant) const
{
    if ((!this->isDefined()) || (!anInstant.isDefined()))
    {
        return false;
    }

    return count_ == ((scale_ == anInstant.scale_) ? anInstant.count_ : anInstant.inScale(scale_).count_);
}

bool Instant::operator!=(const Instant& anInstant) const
{
    if ((!this->isDefined()) || (!anInstant.isDefined()))
    {
        return true;
    }

    return count_ != ((scale_ == anInstant.scale_) ? anInstant.count_ : anInstant.inScale(scale_).count_);
}

bool Instant::operator<(const Instant& anInstant) const
{
    if ((!this->isDefined()) || (!anInstant.isDefined()))
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

    return count_ < ((scale_ == anInstant.scale_) ? anInstant.count_ : anInstant.inScale(scale_).count_);
}

bool Instant::operator<=(const Instant& anInstant) const
{
    if ((!this->isDefined()) || (!anInstant.isDefined()))
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

    return count_ <= ((scale_ == anInstant.scale_) ? anInstant.count_ : anInstant.inScale(scale_).count_);
}

bool Instant::operator>(const Instant& anInstant) const
{
    if ((!this->isDefined()) || (!anInstant.isDefined()))
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

    return count_ > ((scale_ == anInstant.scale_) ? anInstant.count_ : anInstant.inScale(scale_).count_);
}

bool Instant::operator>=(const Instant& anInstant) const
{
    if ((!this->isDefined()) || (!anInstant.isDefined()))
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

    return count_ >= ((scale_ == anInstant.scale_) ? anInstant.count_ : anInstant.inScale(scale_).count_);
}

Instant Instant::operator+(const Duration& aDuration) const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

    if (!aDuration.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Duration");
    }

    return Instant(count_ + aDuration.count_, scale_);
}

Instant Instant::operator-(const Duration& aDuration) const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

    if (!aDuration.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Duration");
    }

    return Instant(count_ - aDuration.count_, scale_);
}

Duration Instant::operator-(const Instant& anInstant) const
{
    if ((!this->isDefined()) || (!anInstant.isDefined()))
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

    const Instant::Count startCount =
        ((scale_ == anInstant.scale_) ? anInstant.count_ : anInstant.inScale(scale_).count_);
    const Instant::Count endCount = count_;

    if (startCount.postEpoch_ && endCount.postEpoch_)  // Start and end instants are after epoch
    {
        return Duration(endCount.countFromEpoch_ - startCount.countFromEpoch_);
    }
    else if ((!startCount.postEpoch_) && (!endCount.postEpoch_))  // Start and end instants are before epoch
    {
        return Duration(startCount.countFromEpoch_ - endCount.countFromEpoch_);
    }
    else if ((!startCount.postEpoch_) && endCount.postEpoch_)  // Start instant is before epoch and end instant is after
                                                               // epoch
    {
        return Duration(startCount.countFromEpoch_ + endCount.countFromEpoch_);
    }
    else  // Start instant is after epoch and end instant is before epoch
    {
        return Duration(-endCount.countFromEpoch_ - startCount.countFromEpoch_);
    }
}

Instant& Instant::operator+=(const Duration& aDuration)
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

    if (!aDuration.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Duration");
    }

    count_ = count_ + aDuration.count_;

    return *this;
}

Instant& Instant::operator-=(const Duration& aDuration)
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

    if (!aDuration.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Duration");
    }

    count_ = count_ - aDuration.count_;

    return *this;
}

std::ostream& operator<<(std::ostream& anOutputStream, const Instant& anInstant)
{
    ostk::core::utils::Print::Header(anOutputStream, "Instant");

    ostk::core::utils::Print::Line(anOutputStream)
        << "Date-Time:" << (anInstant.isDefined() ? anInstant.getDateTime(anInstant.scale_).toString() : "Undefined");
    ostk::core::utils::Print::Line(anOutputStream) << "Scale:" << StringFromScale(anInstant.scale_);

    ostk::core::utils::Print::Footer(anOutputStream);

    return anOutputStream;
}

bool Instant::isDefined() const
{
    return scale_ != Scale::Undefined;
}

bool Instant::isPostEpoch() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

    return (*this) >= Instant::J2000();
}

bool Instant::isNear(const Instant& anInstant, const Duration& aTolerance) const
{
    if (!anInstant.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

    if (!aTolerance.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Tolerance");
    }

    if (!aTolerance.isPositive())
    {
        throw ostk::core::error::RuntimeError("Tolerance is not positive.");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

    return Duration::Between(*this, anInstant).getAbsolute() <= aTolerance;
}

time::DateTime Instant::getDateTime(const Scale& aTimeScale) const
{
    using ostk::core::type::Uint8;

    if (aTimeScale == Scale::Undefined)
    {
        throw ostk::core::error::runtime::Undefined("Scale");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

    // auto getTimePointString =
    // [ ] (const std::chrono::time_point<std::chrono::system_clock>& aTimePoint) -> String
    // {

    //     std::time_t time = std::chrono::system_clock::to_time_t(aTimePoint) ;

    //     std::stringstream stringStream ;

    //     stringStream << std::put_time(std::gmtime(&time), "%F %T %z") ;

    //     return stringStream.str() ;

    // } ;

    // Epoch

    std::tm epochTime = {};  // J2000

    epochTime.tm_sec = 0;
    epochTime.tm_min = 0;
    epochTime.tm_hour = 12;
    epochTime.tm_mday = 1;
    epochTime.tm_mon = 0;
    epochTime.tm_year = 100;

    const std::chrono::time_point<std::chrono::system_clock> epochTimePoint =
        std::chrono::system_clock::from_time_t(std::mktime(&epochTime));

    // const Instant::Count dateCount_TT = this->inScale(Scale::TT).count_ ; // [TBM] remove inScale ?
    const Instant::Count dateCount_TT = this->inScale(aTimeScale).count_;  // [TBM] remove inScale ?

    const std::chrono::time_point<std::chrono::system_clock> dateTimePoint =
        dateCount_TT.postEpoch_ ? (epochTimePoint + std::chrono::nanoseconds(dateCount_TT.countFromEpoch_))
                                : (epochTimePoint - std::chrono::nanoseconds(dateCount_TT.countFromEpoch_));

    std::time_t time = std::chrono::system_clock::to_time_t(dateTimePoint);

    const std::tm tm = *std::gmtime(&time);

    const Uint16 year = 1900 + tm.tm_year;
    const Uint8 month = tm.tm_mon + 1;
    const Uint8 day = tm.tm_mday;

    const Uint8 hours = tm.tm_hour;
    const Uint8 minutes = tm.tm_min;
    const Uint8 seconds = tm.tm_sec;

    const auto fraction = dateTimePoint - std::chrono::time_point_cast<std::chrono::seconds>(dateTimePoint);

    const Uint16 milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(fraction).count();
    const Uint16 microseconds =
        std::chrono::duration_cast<std::chrono::microseconds>(fraction).count() - milliseconds * 1000;
    const Uint16 nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(fraction).count() -
                               milliseconds * 1000000 - microseconds * 1000;

    // [TBI] Time scale conversion

    return time::DateTime(year, month, day, hours, minutes, seconds, milliseconds, microseconds, nanoseconds);
}

Real Instant::getJulianDate(const Scale& aTimeScale) const
{
    if (aTimeScale == Scale::Undefined)
    {
        throw ostk::core::error::runtime::Undefined("Scale");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

    return this->getDateTime(aTimeScale).getJulianDate();
}

Real Instant::getModifiedJulianDate(const Scale& aTimeScale) const
{
    if (aTimeScale == Scale::Undefined)
    {
        throw ostk::core::error::runtime::Undefined("Scale");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

    return this->getDateTime(aTimeScale).getModifiedJulianDate();
}

Int64 Instant::getLeapSecondCount() const
{
    return Instant::dAT_UTC(this->inScale(Scale::UTC).count_) / 1000000000;
}

String Instant::toString(const Scale& aTimeScale, const DateTime::Format& aDateTimeFormat) const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

    if ((aDateTimeFormat == DateTime::Format::ISO8601) && (aTimeScale == Scale::UTC))
    {
        return this->getDateTime(aTimeScale).toString(aDateTimeFormat) + "Z";
    }

    return this->getDateTime(aTimeScale).toString(aDateTimeFormat) + " [" + StringFromScale(aTimeScale) + "]";
}

Instant Instant::Undefined()
{
    return Instant({0, true}, Scale::Undefined);
}

Instant Instant::Now()
{
    // auto getTimePointString =
    // [ ] (const std::chrono::time_point<std::chrono::system_clock>& aTimePoint) -> String
    // {

    //     const std::time_t time = std::chrono::system_clock::to_time_t(aTimePoint) ;

    //     std::stringstream stringStream ;

    //     stringStream << std::put_time(std::gmtime(&time), "%F %T %z") ;

    //     return stringStream.str() ;

    // } ;

    // Epoch

    std::tm epochTime = {};  // J2000

    epochTime.tm_sec = 0;
    epochTime.tm_min = 0;
    epochTime.tm_hour = 12;
    epochTime.tm_mday = 1;
    epochTime.tm_mon = 0;
    epochTime.tm_year = 100;

    const std::chrono::time_point<std::chrono::system_clock> epochTimePoint =
        std::chrono::system_clock::from_time_t(std::mktime(&epochTime));

    // Now

    const std::chrono::time_point<std::chrono::system_clock> nowTimePoint = std::chrono::system_clock::now();

    // Difference

    const auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(nowTimePoint - epochTimePoint);

    if (nanoseconds.count() < 0)
    {
        throw ostk::core::error::RuntimeError("Current time is before J2000 epoch.");  // [TBI] Implement this case
    }

    // Output

    const Instant::Count count_UTC = {Uint64(nanoseconds.count()), (nanoseconds.count() >= 0)};

    // return Instant(count_UTC, Scale::UTC) ;

    const Instant::Count count_TT = Instant::TT_TAI(Instant::TAI_UTC(count_UTC));

    return Instant(count_TT, Scale::TT);
}

Instant Instant::J2000()
{
    return Instant({0, true}, Scale::TT);
}

Instant Instant::DateTime(const time::DateTime& aDateTime, const Scale& aTimeScale)
{
    using ostk::core::type::Int32;

    if (!aDateTime.isDefined())
    {
        throw ostk::core::error::runtime::Wrong("DateTime");
    }

    if (aTimeScale == Scale::Undefined)
    {
        throw ostk::core::error::runtime::Wrong("Scale");
    }

    if ((aDateTime.accessDate().getYear() < 1970) || (aDateTime.accessDate().getYear() > 2030))
    {
        throw ostk::core::error::RuntimeError(
            "DateTime year {} out of supported range [{} - {}]", aDateTime.accessDate().getYear(), 1970, 2030
        );
    }

    // auto getTimePointString =
    // [ ] (const std::chrono::time_point<std::chrono::system_clock>& aTimePoint) -> String
    // {

    //     const std::time_t time = std::chrono::system_clock::to_time_t(aTimePoint) ;

    //     std::stringstream stringStream ;

    //     stringStream << std::put_time(std::gmtime(&time), "%F %T %z") ;

    //     return stringStream.str() ;

    // } ;

    // Epoch

    std::tm epochTime = {};  // J2000

    epochTime.tm_sec = 0;
    epochTime.tm_min = 0;
    epochTime.tm_hour = 12;
    epochTime.tm_mday = 1;
    epochTime.tm_mon = 0;
    epochTime.tm_year = 100;

    const std::chrono::time_point<std::chrono::system_clock> epochTimePoint =
        std::chrono::system_clock::from_time_t(std::mktime(&epochTime));

    // Date

    std::tm dateTime = {};

    dateTime.tm_sec = aDateTime.accessTime().getSecond();
    dateTime.tm_min = aDateTime.accessTime().getMinute();
    dateTime.tm_hour = aDateTime.accessTime().getHour();
    dateTime.tm_mday = aDateTime.accessDate().getDay();
    dateTime.tm_mon = aDateTime.accessDate().getMonth() - 1;
    dateTime.tm_year = static_cast<Int32>(aDateTime.accessDate().getYear()) - 1900;

    const std::chrono::time_point<std::chrono::system_clock> dateTimePoint =
        std::chrono::system_clock::from_time_t(std::mktime(&dateTime));

    // Difference

    const auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(dateTimePoint - epochTimePoint);

    Uint64 nanosecondCount = 0;
    bool postEpoch = true;

    if (nanoseconds.count() >= 0)
    {
        const Uint64 ns = nanoseconds.count();

        nanosecondCount = ns + aDateTime.accessTime().getMillisecond() * 1000000 +
                          aDateTime.accessTime().getMicrosecond() * 1000 + aDateTime.accessTime().getNanosecond();
        postEpoch = true;
    }
    else
    {
        const Uint64 ns = std::abs(nanoseconds.count());

        nanosecondCount = ns - aDateTime.accessTime().getMillisecond() * 1000000 -
                          aDateTime.accessTime().getMicrosecond() * 1000 - aDateTime.accessTime().getNanosecond();
        postEpoch = false;
    }

    // const Int64 nanosecondCount = nanoseconds.count() + aDateTime.accessTime().getMillisecond() * 1000000 +
    // aDateTime.accessTime().getMicrosecond() * 1000 + aDateTime.accessTime().getNanosecond() ;

    // Output

    const Instant::Count count = {nanosecondCount, postEpoch};  // [TBM] This cast in incorrect !!

    const Instant::Count count_TT = Instant::ConvertCountScale(count, aTimeScale, Scale::TT);

    return Instant(count_TT, Scale::TT);
}

Instant Instant::JulianDate(const Real& aJulianDate, const Scale& aTimeScale)
{
    if (!aJulianDate.isDefined())
    {
        throw ostk::core::error::runtime::Wrong("Julian Date");
    }

    if (aTimeScale == Scale::Undefined)
    {
        throw ostk::core::error::runtime::Wrong("Scale");
    }

    return Instant::DateTime(DateTime::JulianDate(aJulianDate), aTimeScale);
}

Instant Instant::ModifiedJulianDate(const Real& aModifiedJulianDate, const Scale& aTimeScale)
{
    if (!aModifiedJulianDate.isDefined())
    {
        throw ostk::core::error::runtime::Wrong("Modified Julian Date");
    }

    if (aTimeScale == Scale::Undefined)
    {
        throw ostk::core::error::runtime::Wrong("Scale");
    }

    return Instant::DateTime(DateTime::ModifiedJulianDate(aModifiedJulianDate), aTimeScale);
}

Instant::Instant(const Instant::Count& aCount, const Scale& aTimeScale)
    : count_(aCount),
      scale_(aTimeScale)
{
}

Instant Instant::inScale(const Scale& aTimeScale) const
{
    return Instant(Instant::ConvertCountScale(count_, scale_, aTimeScale), aTimeScale);
}

Instant::Count Instant::ConvertCountScale(
    const Instant::Count& aCount, const Scale& anInputTimeScale, const Scale& anOutputTimeScale
)
{
    Instant::Count count_TT = {0, true};

    switch (anInputTimeScale)
    {
        case Scale::UTC:
            count_TT = Instant::TT_TAI(Instant::TAI_UTC(aCount));
            break;

        case Scale::TT:
            count_TT = aCount;
            break;

        case Scale::TAI:
            count_TT = Instant::TT_TAI(aCount);
            break;

        case Scale::UT1:
            count_TT = Instant::TT_TAI(Instant::TAI_UTC(Instant::UTC_UT1(aCount)));
            break;

        case Scale::TCG:
            throw ostk::core::error::runtime::ToBeImplemented("TCG");
            break;

        case Scale::TCB:
            throw ostk::core::error::runtime::ToBeImplemented("TCB");
            break;

        case Scale::TDB:
            throw ostk::core::error::runtime::ToBeImplemented("TDB");
            break;

        case Scale::GMST:
            throw ostk::core::error::runtime::ToBeImplemented("GMST");
            break;

        case Scale::GPST:
            count_TT = Instant::TT_TAI(Instant::TAI_GPST(aCount));
            break;

        case Scale::GST:
            throw ostk::core::error::runtime::ToBeImplemented("GST");
            break;

        case Scale::GLST:
            throw ostk::core::error::runtime::ToBeImplemented("GLST");
            break;

        case Scale::BDT:
            throw ostk::core::error::runtime::ToBeImplemented("BDT");
            break;

        case Scale::QZSST:
            throw ostk::core::error::runtime::ToBeImplemented("QZSST");
            break;

        case Scale::IRNSST:
            throw ostk::core::error::runtime::ToBeImplemented("IRNSST");
            break;

        default:
            throw ostk::core::error::runtime::Wrong("Time scale");
            break;
    }

    switch (anOutputTimeScale)
    {
        case Scale::UTC:
            return Instant::UTC_TAI(Instant::TAI_TT(count_TT));

        case Scale::TT:
            return count_TT;

        case Scale::TAI:
            return Instant::TAI_TT(count_TT);

        case Scale::UT1:
            return Instant::UT1_UTC(Instant::UTC_TAI(Instant::TAI_TT(count_TT)));

        case Scale::TCG:
            throw ostk::core::error::runtime::ToBeImplemented("TCG");
            break;

        case Scale::TCB:
            throw ostk::core::error::runtime::ToBeImplemented("TCB");
            break;

        case Scale::TDB:
            throw ostk::core::error::runtime::ToBeImplemented("TDB");
            break;

        case Scale::GMST:
            throw ostk::core::error::runtime::ToBeImplemented("GMST");
            break;

        case Scale::GPST:
            return Instant::GPST_TAI(Instant::TAI_TT(count_TT));

        case Scale::GST:
            throw ostk::core::error::runtime::ToBeImplemented("GST");
            break;

        case Scale::GLST:
            throw ostk::core::error::runtime::ToBeImplemented("GLST");
            break;

        case Scale::BDT:
            throw ostk::core::error::runtime::ToBeImplemented("BDT");
            break;

        case Scale::QZSST:
            throw ostk::core::error::runtime::ToBeImplemented("QZSST");
            break;

        case Scale::IRNSST:
            throw ostk::core::error::runtime::ToBeImplemented("IRNSST");
            break;

        default:
            throw ostk::core::error::runtime::Wrong("Time scale");
            break;
    }

    return Instant::Count(0, true);
}

Instant::Count Instant::UTC_TAI(const Instant::Count& aCount_TAI)
{
    return aCount_TAI - Instant::dAT_TAI(aCount_TAI);  // UTC = TAI - dAT
}

Instant::Count Instant::TAI_UTC(const Instant::Count& aCount_UTC)
{
    return aCount_UTC + Instant::dAT_UTC(aCount_UTC);  // TAI = UTC + dAT
}

Instant::Count Instant::TAI_TT(const Instant::Count& aCount_TT)
{
    return aCount_TT - Int64(32184000000);  // TAI = TT - 32.184 [s]
}

Instant::Count Instant::TT_TAI(const Instant::Count& aCount_TAI)
{
    return aCount_TAI + Int64(32184000000);  // TT = TAI + 32.184 [s]
}

Instant::Count Instant::UT1_UTC(const Instant::Count& aCount_UTC)
{
    return aCount_UTC + Instant::DUT1_UTC(aCount_UTC);  // UT1 = UTC + DUT1
}

Instant::Count Instant::UTC_UT1(const Instant::Count& aCount_UT1)
{
    return aCount_UT1 - Instant::DUT1_UT1(aCount_UT1);  // UTC = UT1 - DUT1
}

Instant::Count Instant::GPST_TAI(const Instant::Count& aCount_TAI)
{
    return aCount_TAI - Int64(19000000000);  // TAI = GPST - 19 [s]
}

Instant::Count Instant::TAI_GPST(const Instant::Count& aCount_GPST)
{
    return aCount_GPST + Int64(19000000000);  // GPST = TAI + 19 [s]
}

Int64 Instant::dAT_UTC(const Instant::Count& aCount_UTC)
{
    // [TBI] Implement dAT automatic manager

    using ostk::core::container::Array;
    using ostk::core::container::Triple;

    if (aCount_UTC.postEpoch_)
    {
        static const Array<Triple<Uint64, Uint64, Int64>> dATMap = {
            {536500800000000000, 999999999999999999, 37000000000
            },  // December 2016    >   +Inf            : dAT =   37 [s]
            {488980800000000000, 536500800000000000, 36000000000
            },  // June 2015        >   December 2016   : dAT =   36 [s]
            {394372800000000000, 488980800000000000, 35000000000
            },  // June 2012        >   June 2015       : dAT =   35 [s]
            {284040000000000000, 394372800000000000, 34000000000
            },  // December 2008    >   June 2012       : dAT =   34 [s]
            {189345600000000000, 284040000000000000, 33000000000
            },  // December 2005    >   December 2008   : dAT =   33 [s]
            {000000000000000000, 189345600000000000, 32000000000
            }  // Epoch            >   December 2005   : dAT =   32 [s]
        };

        if (dATMap.accessFirst().first <= aCount_UTC.countFromEpoch_)
        {
            return dATMap.accessFirst().third;
        }

        for (const auto& dATIt : dATMap)
        {
            if ((dATIt.first <= aCount_UTC.countFromEpoch_) && (aCount_UTC.countFromEpoch_ < dATIt.second))
            {
                return dATIt.third;
            }
        }
    }
    else
    {
        static const Array<Triple<Uint64, Uint64, Int64>> dATMap = {
            {000000000000000000, 31579200000000000, 32000000000
            },  // Epoch            <   December 1998   : dAT =   32 [s]
            {31579200000000000, 79012800000000000, 31000000000
            },  // December 1998    <   June 1997       : dAT =   31 [s]
            {79012800000000000, 126273600000000000, 30000000000
            },  // June 1997        <   December 1995   : dAT =   30 [s]
            {126273600000000000, 173707200000000000, 29000000000
            },  // December 1995    <   June 1994       : dAT =   29 [s]
            {173707200000000000, 205243200000000000, 28000000000
            },  // June 1994        <   June 1993       : dAT =   28 [s]
            {205243200000000000, 236779200000000000, 27000000000
            },  // June 1993        <   June 1992       : dAT =   27 [s]
            {236779200000000000, 284040000000000000, 26000000000
            },  // June 1992        <   December 1990   : dAT =   26 [s]
            {284040000000000000, 315576000000000000, 25000000000
            },  // December 1990    <   December 1989   : dAT =   25 [s]
            {315576000000000000, 378734400000000000, 24000000000
            },  // December 1989    <   December 1987   : dAT =   24 [s]
            {378734400000000000, 457704000000000000, 23000000000
            },  // December 1987    <   June 1985       : dAT =   23 [s]
            {457704000000000000, 520862400000000000, 22000000000
            },  // June 1985        <   June 1983       : dAT =   22 [s]
            {520862400000000000, 552398400000000000, 21000000000
            },  // June 1983        <   June 1982       : dAT =   21 [s]
            {552398400000000000, 583934400000000000, 20000000000
            },  // June 1982        <   June 1981       : dAT =   20 [s]
            {583934400000000000, 631195200000000000, 19000000000
            },  // June 1981        <   December 1979   : dAT =   19 [s]
            {631195200000000000, 662731200000000000, 18000000000
            },  // December 1979    <   December 1978   : dAT =   18 [s]
            {662731200000000000, 694267200000000000, 17000000000
            },  // December 1978    <   December 1977   : dAT =   17 [s]
            {694267200000000000, 725803200000000000, 16000000000
            },  // December 1977    <   December 1976   : dAT =   16 [s]
            {725803200000000000, 757425600000000000, 15000000000
            },  // December 1976    <   December 1975   : dAT =   15 [s]
            {757425600000000000, 788961600000000000, 14000000000
            },  // December 1975    <   December 1974   : dAT =   14 [s]
            {788961600000000000, 820497600000000000, 13000000000
            },  // December 1974    <   December 1973   : dAT =   13 [s]
            {820497600000000000, 852033600000000000, 12000000000
            },  // December 1973    <   December 1972   : dAT =   12 [s]
            {852033600000000000, 867931200000000000, 11000000000
            },  // December 1972    <   June 1972       : dAT =   11 [s]
            {867931200000000000, 999999999999999999, 10000000000
            }  // June 1972        <   Start           : dAT =   10 [s]
        };

        for (const auto& dATIt : dATMap)
        {
            if ((dATIt.first < aCount_UTC.countFromEpoch_) && (aCount_UTC.countFromEpoch_ <= dATIt.second))
            {
                return dATIt.third;
            }
        }

        throw ostk::core::error::RuntimeError("dAT out of bounds.");
    }

    return 0;
}

Int64 Instant::dAT_TAI(const Instant::Count& aCount_TAI)
{
    // [TBI] Implement dAT automatic manager

    using ostk::core::container::Array;
    using ostk::core::container::Triple;

    if (aCount_TAI.postEpoch_)
    {
        static const Array<Triple<Uint64, Uint64, Int64>> dATMap = {
            {536500800000000000 + 36000000000, 999999999999999999 + 00000000000, 37000000000
            },  // December 2016    >   +Inf            : dAT =   37 [s]
            {488980800000000000 + 35000000000, 536500800000000000 + 36000000000, 36000000000
            },  // June 2015        >   December 2016   : dAT =   36 [s]
            {394372800000000000 + 34000000000, 488980800000000000 + 35000000000, 35000000000
            },  // June 2012        >   June 2015       : dAT =   35 [s]
            {284040000000000000 + 33000000000, 394372800000000000 + 34000000000, 34000000000
            },  // December 2008    >   June 2012       : dAT =   34 [s]
            {189345600000000000 + 32000000000, 284040000000000000 + 33000000000, 33000000000
            },  // December 2005    >   December 2008   : dAT =   33 [s]
            {000000000000000000 + 31000000000, 189345600000000000 + 32000000000, 32000000000
            },  // Epoch - 31 [s]   >   December 2005   : dAT =   32 [s]
            {000000000000000000 + 00000000000, 000000000000000000 + 31000000000, 32000000000
            }  // Epoch            >   Epoch - 31 [s]  : dAT =   32 [s]
        };

        if (dATMap.accessFirst().first <= aCount_TAI.countFromEpoch_)
        {
            return dATMap.accessFirst().third;
        }

        for (const auto& dATIt : dATMap)
        {
            if ((dATIt.first <= aCount_TAI.countFromEpoch_) && (aCount_TAI.countFromEpoch_ < dATIt.second))
            {
                return dATIt.third;
            }
        }
    }
    else
    {
        static const Array<Triple<Uint64, Uint64, Int64>> dATMap = {
            {000000000000000000 - 00000000000, 31579200000000000 - 31000000000, 32000000000
            },  // Epoch            <   December 1998   : dAT =   32 [s]
            {31579200000000000 - 31000000000, 79012800000000000 - 30000000000, 31000000000
            },  // December 1998    <   June 1997       : dAT =   31 [s]
            {79012800000000000 - 30000000000, 126273600000000000 - 29000000000, 30000000000
            },  // June 1997        <   December 1995   : dAT =   30 [s]
            {126273600000000000 - 29000000000, 173707200000000000 - 28000000000, 29000000000
            },  // December 1995    <   June 1994       : dAT =   29 [s]
            {173707200000000000 - 28000000000, 205243200000000000 - 27000000000, 28000000000
            },  // June 1994        <   June 1993       : dAT =   28 [s]
            {205243200000000000 - 27000000000, 236779200000000000 - 26000000000, 27000000000
            },  // June 1993        <   June 1992       : dAT =   27 [s]
            {236779200000000000 - 26000000000, 284040000000000000 - 25000000000, 26000000000
            },  // June 1992        <   December 1990   : dAT =   26 [s]
            {284040000000000000 - 25000000000, 315576000000000000 - 24000000000, 25000000000
            },  // December 1990    <   December 1989   : dAT =   25 [s]
            {315576000000000000 - 24000000000, 378734400000000000 - 23000000000, 24000000000
            },  // December 1989    <   December 1987   : dAT =   24 [s]
            {378734400000000000 - 23000000000, 457704000000000000 - 22000000000, 23000000000
            },  // December 1987    <   June 1985       : dAT =   23 [s]
            {457704000000000000 - 22000000000, 520862400000000000 - 21000000000, 22000000000
            },  // June 1985        <   June 1983       : dAT =   22 [s]
            {520862400000000000 - 21000000000, 552398400000000000 - 20000000000, 21000000000
            },  // June 1983        <   June 1982       : dAT =   21 [s]
            {552398400000000000 - 20000000000, 583934400000000000 - 19000000000, 20000000000
            },  // June 1982        <   June 1981       : dAT =   20 [s]
            {583934400000000000 - 19000000000, 631195200000000000 - 18000000000, 19000000000
            },  // June 1981        <   December 1979   : dAT =   19 [s]
            {631195200000000000 - 18000000000, 662731200000000000 - 17000000000, 18000000000
            },  // December 1979    <   December 1978   : dAT =   18 [s]
            {662731200000000000 - 17000000000, 694267200000000000 - 16000000000, 17000000000
            },  // December 1978    <   December 1977   : dAT =   17 [s]
            {694267200000000000 - 16000000000, 725803200000000000 - 15000000000, 16000000000
            },  // December 1977    <   December 1976   : dAT =   16 [s]
            {725803200000000000 - 15000000000, 757425600000000000 - 14000000000, 15000000000
            },  // December 1976    <   December 1975   : dAT =   15 [s]
            {757425600000000000 - 14000000000, 788961600000000000 - 13000000000, 14000000000
            },  // December 1975    <   December 1974   : dAT =   14 [s]
            {788961600000000000 - 13000000000, 820497600000000000 - 12000000000, 13000000000
            },  // December 1974    <   December 1973   : dAT =   13 [s]
            {820497600000000000 - 12000000000, 852033600000000000 - 11000000000, 12000000000
            },  // December 1973    <   December 1972   : dAT =   12 [s]
            {852033600000000000 - 11000000000, 867931200000000000 - 10000000000, 11000000000
            },  // December 1972    <   June 1972       : dAT =   11 [s]
            {867931200000000000 - 10000000000, 999999999999999999, 10000000000
            }  // June 1972        <   Start           : dAT =   10 [s]
        };

        for (const auto& dATIt : dATMap)
        {
            if ((dATIt.first < aCount_TAI.countFromEpoch_) && (aCount_TAI.countFromEpoch_ <= dATIt.second))
            {
                return dATIt.third;
            }
        }

        throw ostk::core::error::RuntimeError("dAT out of bounds.");
    }

    return 0;
}

Int64 Instant::DUT1_UTC(const Instant::Count& aCount_UTC)
{
    (void)aCount_UTC;

    throw ostk::core::error::runtime::ToBeImplemented("DUT1_UTC");

    return 0;
}

Int64 Instant::DUT1_UT1(const Instant::Count& aCount_UT1)
{
    (void)aCount_UT1;

    throw ostk::core::error::runtime::ToBeImplemented("DUT1_UT1");

    return 0;
}

Instant::Count::Count(Uint64 aNanosecondCountFromEpoch, bool isPostEpoch)
    : countFromEpoch_(aNanosecondCountFromEpoch),
      postEpoch_((aNanosecondCountFromEpoch != 0) ? isPostEpoch : true)
{
}

bool Instant::Count::operator==(const Instant::Count& aCount) const
{
    return (countFromEpoch_ == aCount.countFromEpoch_) && (postEpoch_ == aCount.postEpoch_);
}

bool Instant::Count::operator!=(const Instant::Count& aCount) const
{
    return (countFromEpoch_ != aCount.countFromEpoch_) || (postEpoch_ != aCount.postEpoch_);
}

bool Instant::Count::operator<(const Instant::Count& aCount) const
{
    if (postEpoch_ == aCount.postEpoch_)  // On the same side of the epoch
    {
        return postEpoch_ ? (countFromEpoch_ < aCount.countFromEpoch_) : (aCount.countFromEpoch_ < countFromEpoch_);
    }

    return (!postEpoch_) && aCount.postEpoch_;
}

bool Instant::Count::operator<=(const Instant::Count& aCount) const
{
    if (postEpoch_ == aCount.postEpoch_)  // On the same side of the epoch
    {
        return postEpoch_ ? (countFromEpoch_ <= aCount.countFromEpoch_) : (aCount.countFromEpoch_ <= countFromEpoch_);
    }

    return (!postEpoch_) && aCount.postEpoch_;
}

bool Instant::Count::operator>(const Instant::Count& aCount) const
{
    if (postEpoch_ == aCount.postEpoch_)  // On the same side of the epoch
    {
        return postEpoch_ ? (countFromEpoch_ > aCount.countFromEpoch_) : (aCount.countFromEpoch_ > countFromEpoch_);
    }

    return postEpoch_ && (!aCount.postEpoch_);
}

bool Instant::Count::operator>=(const Instant::Count& aCount) const
{
    if (postEpoch_ == aCount.postEpoch_)  // On the same side of the epoch
    {
        return postEpoch_ ? (countFromEpoch_ >= aCount.countFromEpoch_) : (aCount.countFromEpoch_ >= countFromEpoch_);
    }

    return postEpoch_ && (!aCount.postEpoch_);
}

Instant::Count Instant::Count::operator+(const Instant::Count& aCount) const
{
    // [TBI] Check count overflow

    if (aCount.countFromEpoch_ <=
        countFromEpoch_)  // Displacement lower than count from epoch: we remain on the same epoch side
    {
        return postEpoch_ ? Count((countFromEpoch_ + aCount.countFromEpoch_), true)
                          : Count((countFromEpoch_ - aCount.countFromEpoch_), false);
    }
    else  // Displacement greater than count from epoch: we switch epoch side
    {
        if ((postEpoch_) && (aCount.postEpoch_))  // Count is after epoch and displacement is positive
        {
            return Count((countFromEpoch_ + aCount.countFromEpoch_), true);
        }
        else if ((!postEpoch_) && (!aCount.postEpoch_))  // Count is before epoch and displacement is negative
        {
            return Count((countFromEpoch_ - aCount.countFromEpoch_), false);
        }
        else  // Count and displacement of opposite directions
        {
            return Count((aCount.countFromEpoch_ - countFromEpoch_), (!postEpoch_));
        }
    }
}

Instant::Count Instant::Count::operator+(Int64 aNanosecondDisplacement) const
{
    // [TBI] Check count overflow

    if (static_cast<Uint64>(std::abs(aNanosecondDisplacement)) <=
        countFromEpoch_)  // Displacement lower than count from epoch: we remain on the same epoch side
    {
        return postEpoch_ ? Count((countFromEpoch_ + aNanosecondDisplacement), true)
                          : Count((countFromEpoch_ - aNanosecondDisplacement), false);
    }
    else  // Displacement greater than count from epoch: we switch epoch side
    {
        if ((postEpoch_) && (aNanosecondDisplacement >= 0))  // Count is after epoch and displacement is positive
        {
            return Count((countFromEpoch_ + aNanosecondDisplacement), true);
        }
        else if ((!postEpoch_) && (aNanosecondDisplacement < 0))  // Count is before epoch and displacement is negative
        {
            return Count((countFromEpoch_ - aNanosecondDisplacement), false);
        }
        else  // Count and displacement of opposite directions
        {
            return Count((std::abs(aNanosecondDisplacement) - countFromEpoch_), (!postEpoch_));
        }
    }
}

Instant::Count Instant::Count::operator-(Int64 aNanosecondDisplacement) const
{
    return (*this) + (-aNanosecondDisplacement);
}

String Instant::Count::toString() const
{
    using ostk::core::type::Integer;

    return postEpoch_ ? ("+" + std::to_string(countFromEpoch_)) : ("-" + std::to_string(countFromEpoch_));
}

// auto parseDateTimeString =
// [ ] (const String& aDateTimeString) -> std::chrono::time_point<std::chrono::system_clock>
// {

//     std::istringstream stringStream(aDateTimeString) ;

//     std::tm dateTime = {} ;

//     stringStream >> std::get_time(&dateTime, "%Y-%m-%d %H:%M:%S") ;

//     if (stringStream.fail())
//     {
//         throw ostk::core::error::RuntimeError("Cannot parse date time string [" + aDateTimeString + "].") ;
//     }

//     return std::chrono::system_clock::from_time_t(std::mktime(&dateTime)) ;

// } ;

}  // namespace time
}  // namespace physics
}  // namespace ostk
