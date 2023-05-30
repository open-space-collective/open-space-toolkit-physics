/// Apache License 2.0

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

#include <OpenSpaceToolkit/Physics/Time/Date.hpp>

namespace ostk
{
namespace physics
{
namespace time
{

Date::Date(Uint16 aYear, Uint8 aMonth, Uint8 aDay)
    : defined_(true),
      year_(aYear),
      month_(aMonth),
      day_(aDay)
{
    Date::ValidateDate(year_, month_, day_);
}

bool Date::operator==(const Date& aDate) const
{
    if ((!this->isDefined()) || (!aDate.isDefined()))
    {
        return false;
    }

    return (year_ == aDate.year_) && (month_ == aDate.month_) && (day_ == aDate.day_);
}

bool Date::operator!=(const Date& aDate) const
{
    if ((!this->isDefined()) || (!aDate.isDefined()))
    {
        return true;
    }

    return (year_ != aDate.year_) || (month_ != aDate.month_) || (day_ != aDate.day_);
}

std::ostream& operator<<(std::ostream& anOutputStream, const Date& aDate)
{
    ostk::core::utils::Print::Header(anOutputStream, "Date");

    ostk::core::utils::Print::Line(anOutputStream)
        << "Year:" << (aDate.isDefined() ? String::Format("{:d}", aDate.year_) : "Undefined");
    ostk::core::utils::Print::Line(anOutputStream)
        << "Month:" << (aDate.isDefined() ? String::Format("{:d}", aDate.month_) : "Undefined");
    ostk::core::utils::Print::Line(anOutputStream)
        << "Day:" << (aDate.isDefined() ? String::Format("{:d}", aDate.day_) : "Undefined");

    ostk::core::utils::Print::Footer(anOutputStream);

    return anOutputStream;
}

bool Date::isDefined() const
{
    return defined_;
}

Uint16 Date::getYear() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Date");
    }

    return year_;
}

Uint8 Date::getMonth() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Date");
    }

    return month_;
}

Uint8 Date::getDay() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Date");
    }

    return day_;
}

String Date::toString(const Date::Format& aFormat) const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Date");
    }

    switch (aFormat)
    {
        case Date::Format::Standard:
        {
            if (std::abs(year_) < 1000)
            {
                return String::Format("{0:04d}-{1:02d}-{2:02d}", year_, month_, day_);
            }

            return String::Format("{0:d}-{1:02d}-{2:02d}", year_, month_, day_);
        }

        case Date::Format::STK:
        {
            auto formatMonth = [](Uint8 aMonth) -> String
            {
                switch (aMonth)
                {
                    case 1:
                        return "Jan";

                    case 2:
                        return "Feb";

                    case 3:
                        return "Mar";

                    case 4:
                        return "Apr";

                    case 5:
                        return "May";

                    case 6:
                        return "Jun";

                    case 7:
                        return "Jul";

                    case 8:
                        return "Aug";

                    case 9:
                        return "Sep";

                    case 10:
                        return "Oct";

                    case 11:
                        return "Nov";

                    case 12:
                        return "Dec";

                    default:
                        throw ostk::core::error::runtime::Wrong("Month", aMonth);
                        break;
                }
            };

            return String::Format("{0:d} {1:s} {2:d}", day_, formatMonth(month_), year_);
        }

        default:
            throw ostk::core::error::runtime::Wrong("Format");
            break;
    }

    return String::Empty();
}

void Date::setYear(Uint16 aYear)
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Date");
    }

    Date::ValidateDate(aYear, month_, day_);

    year_ = aYear;
}

void Date::setMonth(Uint8 aMonth)
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Date");
    }

    Date::ValidateDate(year_, aMonth, day_);

    month_ = aMonth;
}

void Date::setDay(Uint8 aDay)
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Date");
    }

    Date::ValidateDate(year_, month_, aDay);

    day_ = aDay;
}

Date Date::Undefined()
{
    return Date();
}

Date Date::J2000()
{
    return Date(2000, 1, 1);
}

Date Date::GPSEpoch()
{
    return Date(1980, 1, 6);
}

Date Date::UnixEpoch()
{
    return Date(1970, 1, 1);
}

Date Date::ModifiedJulianDateEpoch()
{
    return Date(1858, 11, 17);
}

Date Date::Parse(const String& aString, const Date::Format& aFormat)
{
    if (aString.isEmpty())
    {
        throw ostk::core::error::runtime::Undefined("String");
    }

    switch (aFormat)
    {
        case Date::Format::Undefined:  // Automatic format detection
        {
            if (aString.match(std::regex("^([\\d]{1,2}) ([\\w]{3}) ([\\d]{4})$")))
            {
                return Date::Parse(aString, Date::Format::STK);
            }

            return Date::Parse(aString, Date::Format::Standard);
        }

        case Date::Format::Standard:
        {
            boost::smatch match;

            if (boost::regex_match(aString, match, boost::regex("^([-]?[0-9]+)-([0-9]{2})-([0-9]{2})$")))
            {
                try
                {
                    const Uint16 year = boost::lexical_cast<Uint16>(match[1]);
                    const Uint8 month = static_cast<Uint8>(boost::lexical_cast<Uint16>(match[2]));
                    const Uint8 day = static_cast<Uint8>(boost::lexical_cast<Uint16>(match[3]));

                    return Date(year, month, day);
                }
                catch (const boost::bad_lexical_cast& e)
                {
                    throw ostk::core::error::RuntimeError("Cannot parse date string [{}] ({}).", aString, e.what());
                }
            }
            else
            {
                throw ostk::core::error::RuntimeError("Cannot parse date string [{}].", aString);
            }
        }

        case Date::Format::STK:
        {
            boost::smatch match;

            if (boost::regex_match(aString, match, boost::regex("^([\\d]{1,2}) ([\\w]{3}) ([\\d]{4})$")))
            {
                try
                {
                    auto parseMonth = [](const String& aMonthString) -> Uint8
                    {
                        if (aMonthString == "Jan")
                        {
                            return 1;
                        }

                        if (aMonthString == "Feb")
                        {
                            return 2;
                        }

                        if (aMonthString == "Mar")
                        {
                            return 3;
                        }

                        if (aMonthString == "Apr")
                        {
                            return 4;
                        }

                        if (aMonthString == "May")
                        {
                            return 5;
                        }

                        if (aMonthString == "Jun")
                        {
                            return 6;
                        }

                        if (aMonthString == "Jul")
                        {
                            return 7;
                        }

                        if (aMonthString == "Aug")
                        {
                            return 8;
                        }

                        if (aMonthString == "Sep")
                        {
                            return 9;
                        }

                        if (aMonthString == "Oct")
                        {
                            return 10;
                        }

                        if (aMonthString == "Nov")
                        {
                            return 11;
                        }

                        if (aMonthString == "Dec")
                        {
                            return 12;
                        }

                        return 0;
                    };

                    const Uint8 day = static_cast<Uint8>(boost::lexical_cast<Uint16>(match[1]));
                    const Uint8 month = parseMonth(std::string(match[2]));
                    const Uint16 year = boost::lexical_cast<Uint16>(match[3]);

                    return Date(year, month, day);
                }
                catch (const boost::bad_lexical_cast& e)
                {
                    throw ostk::core::error::RuntimeError("Cannot parse date string [{}] ({}).", aString, e.what());
                }
            }
            else
            {
                throw ostk::core::error::RuntimeError("Cannot parse date string [{}].", aString);
            }
        }

        default:
            throw ostk::core::error::runtime::Wrong("Format");
            break;
    }

    return Date::Undefined();
}

Date::Date()
    : defined_(false),
      year_(0),
      month_(0),
      day_(0)
{
}

void Date::ValidateDate(Uint16 aYear, Uint8 aMonth, Uint8 aDay)
{
    if ((aYear < 1400) || (aYear > 9999))
    {
        throw ostk::core::error::RuntimeError(String::Format("Year [{}] out of range [1400 - 9999].", aYear));
    }

    if ((aMonth == 0) || (aMonth > 12))
    {
        throw ostk::core::error::RuntimeError(String::Format("Month [{}] out of range [1 - 12].", aMonth));
    }

    if ((aDay == 0) || (aDay > 31))
    {
        throw ostk::core::error::RuntimeError(String::Format("Day [{}] out of range [1 - 31].", aDay));
    }

    // [TBM] This is a quick and dirty implementation using boost::gregorian::date, it should be replaced by something
    // more efficient

    try
    {
        boost::gregorian::date date(aYear, aMonth, aDay);
    }
    catch (const std::out_of_range& e)
    {
        throw ostk::core::error::RuntimeError(
            String::Format("Date [{:d}-{:02d}-{:02d}] out of range.", aYear, aMonth, aDay)
        );
    }
}

}  // namespace time
}  // namespace physics
}  // namespace ostk

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
