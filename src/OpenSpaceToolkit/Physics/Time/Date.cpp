/// Apache License 2.0

#include <cmath>

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Physics/Time/Date.hpp>

namespace ostk
{
namespace physics
{
namespace time
{

Date::Date(Uint16 aYear, Uint8 aMonth, Uint8 aDay)
    : year_(aYear),
      month_(aMonth),
      day_(aDay)
{
    Date::ValidateDate(year_, month_, day_);
}

bool Date::operator==(const Date& aDate) const
{
    return (year_ == aDate.year_) && (month_ == aDate.month_) && (day_ == aDate.day_);
}

bool Date::operator!=(const Date& aDate) const
{
    return (year_ != aDate.year_) || (month_ != aDate.month_) || (day_ != aDate.day_);
}

std::ostream& operator<<(std::ostream& anOutputStream, const Date& aDate)
{
    ostk::core::utils::Print::Header(anOutputStream, "Date");

    ostk::core::utils::Print::Line(anOutputStream) << "Year:" << String::Format("{:d}", aDate.year_);
    ostk::core::utils::Print::Line(anOutputStream) << "Month:" << String::Format("{:d}", aDate.month_);
    ostk::core::utils::Print::Line(anOutputStream) << "Day:" << String::Format("{:d}", aDate.day_);

    ostk::core::utils::Print::Footer(anOutputStream);

    return anOutputStream;
}

Uint16 Date::getYear() const
{
    return year_;
}

Uint8 Date::getMonth() const
{
    return month_;
}

Uint8 Date::getDay() const
{
    return day_;
}

String Date::toString(const Date::Format& aFormat) const
{
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

Date Date::replace(const std::optional<int>& aYear, const std::optional<int>& aMonth, const std::optional<int>& aDay)
    const
{
    const int year = aYear.value_or(static_cast<int>(year_));
    const int month = aMonth.value_or(static_cast<int>(month_));
    const int day = aDay.value_or(static_cast<int>(day_));

    Date::ValidateDate(year, month, day);

    return Date(static_cast<Uint16>(year), static_cast<Uint8>(month), static_cast<Uint8>(day));
}

void Date::setYear(Uint16 aYear)
{
    Date::ValidateDate(aYear, month_, day_);

    year_ = aYear;
}

void Date::setMonth(Uint8 aMonth)
{
    Date::ValidateDate(year_, aMonth, day_);

    month_ = aMonth;
}

void Date::setDay(Uint8 aDay)
{
    Date::ValidateDate(year_, month_, aDay);

    day_ = aDay;
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

Date Date::Parse(const String& aString, const std::optional<Date::Format>& aFormat)
{
    if (aString.isEmpty())
    {
        throw ostk::core::error::runtime::Undefined("String");
    }

    if (!aFormat.has_value())
    {
        // Automatic format detection

        if (aString.match(boost::regex("^([\\d]{1,2}) ([\\w]{3}) ([\\d]{4})$")))
        {
            return Date::Parse(aString, Date::Format::STK);
        }

        return Date::Parse(aString, Date::Format::Standard);
    }

    switch (aFormat.value())
    {
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

    throw ostk::core::error::runtime::Wrong("Format");
}

void Date::ValidateDate(int aYear, int aMonth, int aDay)
{
    if ((aYear < 1400) || (aYear > 9999))
    {
        throw ostk::core::error::RuntimeError(String::Format("Year [{}] out of range [1400 - 9999].", aYear));
    }

    if ((aMonth < 1) || (aMonth > 12))
    {
        throw ostk::core::error::RuntimeError(String::Format("Month [{}] out of range [1 - 12].", aMonth));
    }

    if ((aDay < 1) || (aDay > 31))
    {
        throw ostk::core::error::RuntimeError(String::Format("Day [{}] out of range [1 - 31].", aDay));
    }

    // [TBM] This is a quick and dirty implementation using boost::gregorian::date, it should be replaced by something
    // more efficient

    const Uint16 year = static_cast<Uint16>(aYear);
    const Uint8 month = static_cast<Uint8>(aMonth);
    const Uint8 day = static_cast<Uint8>(aDay);

    try
    {
        boost::gregorian::date date(year, month, day);
    }
    catch (const std::out_of_range& e)
    {
        throw ostk::core::error::RuntimeError(
            String::Format("Date [{:d}-{:02d}-{:02d}] out of range.", year, month, day)
        );
    }
}

}  // namespace time
}  // namespace physics
}  // namespace ostk
