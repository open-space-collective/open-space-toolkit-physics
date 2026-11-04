/// Apache License 2.0

#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <optional>
#include <sstream>

#include <boost/algorithm/string/trim.hpp>
#include <boost/lexical_cast.hpp>

#include <OpenSpaceToolkit/Core/Container/Object.hpp>
#include <OpenSpaceToolkit/Core/Container/Table.hpp>
#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Type/Size.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Physics/Data/Utility.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/CSSISpaceWeather.hpp>
#include <OpenSpaceToolkit/Physics/Utility/String.hpp>

namespace ostk
{
namespace physics
{
namespace environment
{
namespace atmospheric
{
namespace earth
{

using ostk::core::container::Object;
using ostk::core::container::Table;
using ostk::core::type::Index;
using ostk::core::type::Size;
using ostk::core::type::String;
using ostk::core::type::Uint16;
using ostk::core::type::Uint8;
using ostk::core::utils::Print;

using ostk::physics::time::DateTime;
using ostk::physics::time::Scale;
using ostk::physics::time::Time;

using ostk::physics::data::utilities::getFileModifiedInstant;
using ostk::physics::utility::ParseDouble;
using ostk::physics::utility::ParseInt;

std::ostream& operator<<(std::ostream& anOutputStream, const CSSISpaceWeather& aCSSISpaceWeather)
{
    // Empty integer cells are printed as "-"
    const auto integerValue = [](const std::optional<int>& anInteger) -> std::string
    {
        return anInteger.has_value() ? std::to_string(anInteger.value()) : std::string("-");
    };

    // Empty cells are printed as NaN
    const auto realValue = [](const std::optional<double>& aReal) -> double
    {
        return aReal.value_or(std::numeric_limits<double>::quiet_NaN());
    };

    Print::Header(anOutputStream, "CSSI Space Weather");

    Print::Line(anOutputStream) << "Observation interval:"
                                << (aCSSISpaceWeather.observationInterval_.isDefined()
                                        ? aCSSISpaceWeather.observationInterval_.toString(Scale::UTC)
                                        : "Undefined");
    Print::Line(anOutputStream) << "Daily prediction interval:"
                                << (aCSSISpaceWeather.dailyPredictionInterval_.isDefined()
                                        ? aCSSISpaceWeather.dailyPredictionInterval_.toString(Scale::UTC)
                                        : "Undefined");

    Print::Line(anOutputStream) << "Monthly prediction interval:"
                                << (aCSSISpaceWeather.monthlyPredictionInterval_.isDefined()
                                        ? aCSSISpaceWeather.monthlyPredictionInterval_.toString(Scale::UTC)
                                        : "Undefined");

    const String dataHeader = String(
        "DATE,BSRN,ND,Kp1,Kp2,Kp3,Kp4,Kp5,Kp6,Kp7,Kp8,KpSum,Ap1,Ap2,Ap3,Ap4,Ap5,Ap6,Ap7,Ap8,ApAvg,Cp,C9,ISN,F10.7_"
        "OBS,F10.7Adj,F10.7DataType,F10.7ObsCenter81,F10.7ObsLast81,F10.7AdjCenter81,F10.7AdjLast81"
    );

    Print::Separator(anOutputStream, "Observations");
    Print::Line(anOutputStream) << dataHeader;
    for (const auto& observationIt : aCSSISpaceWeather.observations_)
    {
        const CSSISpaceWeather::Reading& observation = observationIt.second;

        Print::Line(anOutputStream) << String::Format(
            "{:04}-{:02}-{:02}  {:>4}  {:>2}  {:>2}  {:>2}  {:>2}  {:>2}  {:>2}  {:>2}  {:>2}  {:>2}  {:>4} "
            " {:>2}  {:>2}  {:>2}  {:>2}  {:>2}  {:>2}  {:>2}  {:>2}  {:>2}  {:.2f}  {:>2}  {:>4}  {:6.2f}  "
            "{:6.2f}  {:s}  {:6.2f}  {:6.2f}  {:6.2f}  {:6.2f}",
            observation.date.getYear(),
            observation.date.getMonth(),
            observation.date.getDay(),
            integerValue(observation.BSRN),
            integerValue(observation.ND),
            integerValue(observation.Kp1),
            integerValue(observation.Kp2),
            integerValue(observation.Kp3),
            integerValue(observation.Kp4),
            integerValue(observation.Kp5),
            integerValue(observation.Kp6),
            integerValue(observation.Kp7),
            integerValue(observation.Kp8),
            integerValue(observation.KpSum),
            integerValue(observation.Ap1),
            integerValue(observation.Ap2),
            integerValue(observation.Ap3),
            integerValue(observation.Ap4),
            integerValue(observation.Ap5),
            integerValue(observation.Ap6),
            integerValue(observation.Ap7),
            integerValue(observation.Ap8),
            integerValue(observation.ApAvg),
            realValue(observation.Cp),
            integerValue(observation.C9),
            integerValue(observation.ISN),
            realValue(observation.F107Obs),
            realValue(observation.F107Adj),
            observation.F107DataType,
            realValue(observation.F107ObsCenter81),
            realValue(observation.F107ObsLast81),
            realValue(observation.F107AdjCenter81),
            realValue(observation.F107AdjLast81)
        );
    }

    Print::Separator(anOutputStream, "Daily Predictions");
    Print::Line(anOutputStream) << dataHeader;

    for (const auto& dailyPredictionIt : aCSSISpaceWeather.dailyPredictions_)
    {
        const CSSISpaceWeather::Reading& dailyPrediction = dailyPredictionIt.second;

        Print::Line(anOutputStream) << String::Format(
            "{:04}-{:02}-{:02}  {:>4}  {:>2}  {:>2}  {:>2}  {:>2}  {:>2}  {:>2}  {:>2}  {:>2}  {:>2}  {:>4} "
            " {:>2}  {:>2}  {:>2}  {:>2}  {:>2}  {:>2}  {:>2}  {:>2}  {:>2}  {:.2f}  {:>2}  {:>4}  {:6.2f}  "
            "{:6.2f}  {:s}  {:6.2f}  {:6.2f}  {:6.2f}  {:6.2f}",
            dailyPrediction.date.getYear(),
            dailyPrediction.date.getMonth(),
            dailyPrediction.date.getDay(),
            integerValue(dailyPrediction.BSRN),
            integerValue(dailyPrediction.ND),
            integerValue(dailyPrediction.Kp1),
            integerValue(dailyPrediction.Kp2),
            integerValue(dailyPrediction.Kp3),
            integerValue(dailyPrediction.Kp4),
            integerValue(dailyPrediction.Kp5),
            integerValue(dailyPrediction.Kp6),
            integerValue(dailyPrediction.Kp7),
            integerValue(dailyPrediction.Kp8),
            integerValue(dailyPrediction.KpSum),
            integerValue(dailyPrediction.Ap1),
            integerValue(dailyPrediction.Ap2),
            integerValue(dailyPrediction.Ap3),
            integerValue(dailyPrediction.Ap4),
            integerValue(dailyPrediction.Ap5),
            integerValue(dailyPrediction.Ap6),
            integerValue(dailyPrediction.Ap7),
            integerValue(dailyPrediction.Ap8),
            integerValue(dailyPrediction.ApAvg),
            realValue(dailyPrediction.Cp),
            integerValue(dailyPrediction.C9),
            integerValue(dailyPrediction.ISN),
            realValue(dailyPrediction.F107Obs),
            realValue(dailyPrediction.F107Adj),
            dailyPrediction.F107DataType,
            realValue(dailyPrediction.F107ObsCenter81),
            realValue(dailyPrediction.F107ObsLast81),
            realValue(dailyPrediction.F107AdjCenter81),
            realValue(dailyPrediction.F107AdjLast81)
        );
    }

    Print::Separator(anOutputStream, "Monthly Predictions");
    Print::Line(anOutputStream) << String(
        "DATE,BSRN,ND,ISN,F10.7Obs,F10.7Adj,F10.7DataType,F10.7ObsCenter81,F10.7ObsLast81,F10.7AdjCenter81,"
        "F10.7AdjLast81"
    );

    for (const auto& monthlyPredictionIt : aCSSISpaceWeather.monthlyPredictions_)
    {
        const CSSISpaceWeather::Reading& monthlyPrediction = monthlyPredictionIt.second;

        Print::Line(anOutputStream) << String::Format(
            "{:04}-{:02}-{:02}  {:>4}  {:>2}  {:>4}  {:6.2f}  {:6.2f}  {:s}  {:6.2f}  {:6.2f}  {:6.2f}  {:6.2f}",
            monthlyPrediction.date.getYear(),
            monthlyPrediction.date.getMonth(),
            monthlyPrediction.date.getDay(),
            integerValue(monthlyPrediction.BSRN),
            integerValue(monthlyPrediction.ND),
            integerValue(monthlyPrediction.ISN),
            realValue(monthlyPrediction.F107Obs),
            realValue(monthlyPrediction.F107Adj),
            monthlyPrediction.F107DataType,
            realValue(monthlyPrediction.F107ObsCenter81),
            realValue(monthlyPrediction.F107ObsLast81),
            realValue(monthlyPrediction.F107AdjCenter81),
            realValue(monthlyPrediction.F107AdjLast81)
        );
    }

    Print::Footer(anOutputStream);

    return anOutputStream;
}

const Date& CSSISpaceWeather::getLastObservationDate() const
{
    if (!lastObservationDate_.has_value())
    {
        throw ostk::core::error::runtime::Undefined("Last observation date");
    }

    return lastObservationDate_.value();
}

const Instant& CSSISpaceWeather::getLastModifiedTimestamp() const
{
    return lastModifiedTimestamp_;
}

const Interval& CSSISpaceWeather::getObservationInterval() const
{
    return observationInterval_;
}

const CSSISpaceWeather::Reading& CSSISpaceWeather::getObservationAt(const Instant& anInstant) const
{
    if (!anInstant.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

    if (!observationInterval_.contains(anInstant))
    {
        throw ostk::core::error::RuntimeError(
            "Instant [{}] out of observation range [{} - {}].",
            anInstant.toString(Scale::UTC),
            observationInterval_.getStart().toString(Scale::UTC),
            observationInterval_.getEnd().toString(Scale::UTC)
        );
    }

    // Construct the MJD by only using the date component of the Instant, because an Instant just before
    // the end of the observationInterval (within some nanoseconds) can have an MJD in the next day
    // due to floating-point rounding error.
    const Date date = anInstant.getDateTime(Scale::UTC).getDate();
    const int mjd = static_cast<int>(std::floor(DateTime(date, Time::Midnight()).getModifiedJulianDate()));

    const auto observationIt = observations_.find(mjd);

    if (observationIt != observations_.end())
    {
        return observationIt->second;
    }

    throw ostk::core::error::RuntimeError("Cannot find observation at [{}].", anInstant.toString(Scale::UTC));
}

const Interval& CSSISpaceWeather::getDailyPredictionInterval() const
{
    return dailyPredictionInterval_;
}

const CSSISpaceWeather::Reading& CSSISpaceWeather::getDailyPredictionAt(const Instant& anInstant) const
{
    if (!anInstant.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

    if (!dailyPredictionInterval_.contains(anInstant))
    {
        throw ostk::core::error::RuntimeError(
            "Instant [{}] out of prediction range [{} - {}].",
            anInstant.toString(Scale::UTC),
            dailyPredictionInterval_.getStart().toString(Scale::UTC),
            dailyPredictionInterval_.getEnd().toString(Scale::UTC)
        );
    }

    // Construct the MJD by only using the date component of the Instant, because an Instant just before
    // the end of the dailyPredictionInterval (within some nanoseconds) can have an MJD in the next day
    // due to floating-point rounding error.
    const Date date = anInstant.getDateTime(Scale::UTC).getDate();
    const int mjd = static_cast<int>(std::floor(DateTime(date, Time::Midnight()).getModifiedJulianDate()));

    const auto predictionIt = dailyPredictions_.find(mjd);

    if (predictionIt != dailyPredictions_.end())
    {
        return predictionIt->second;
    }

    throw ostk::core::error::RuntimeError("Cannot find daily prediction at [{}].", anInstant.toString(Scale::UTC));
}

const Interval& CSSISpaceWeather::getMonthlyPredictionInterval() const
{
    return monthlyPredictionInterval_;
}

const CSSISpaceWeather::Reading& CSSISpaceWeather::getMonthlyPredictionAt(const Instant& anInstant) const
{
    if (!anInstant.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

    if (!monthlyPredictionInterval_.contains(anInstant))
    {
        throw ostk::core::error::RuntimeError(
            "Instant [{}] out of prediction range [{} - {}].",
            anInstant.toString(Scale::UTC),
            monthlyPredictionInterval_.getStart().toString(Scale::UTC),
            monthlyPredictionInterval_.getEnd().toString(Scale::UTC)
        );
    }

    const Date date = anInstant.getDateTime(Scale::UTC).getDate();

    const int year = date.getYear();
    const int month = date.getMonth();

    const double monthMjd = DateTime(year, month, 1).getModifiedJulianDate();

    const auto predictionIt = monthlyPredictions_.find(static_cast<int>(std::floor(monthMjd)));

    if (predictionIt != monthlyPredictions_.end())
    {
        return predictionIt->second;
    }

    throw ostk::core::error::RuntimeError("Cannot find monthly prediction at [{}].", anInstant.toString(Scale::UTC));
}

const CSSISpaceWeather::Reading& CSSISpaceWeather::getReadingAt(const Instant& anInstant) const
{
    if (observationInterval_.contains(anInstant))
    {
        return this->getObservationAt(anInstant);
    }
    if (dailyPredictionInterval_.contains(anInstant))
    {
        return this->getDailyPredictionAt(anInstant);
    }
    if (monthlyPredictionInterval_.contains(anInstant))
    {
        return this->getMonthlyPredictionAt(anInstant);
    }

    throw ostk::core::error::RuntimeError(
        "Instant [{}] out of range [{} - {}].",
        anInstant.toString(Scale::UTC),
        observationInterval_.getStart().toString(Scale::UTC),
        monthlyPredictionInterval_.getEnd().toString(Scale::UTC)
    );
}

const CSSISpaceWeather::Reading& CSSISpaceWeather::getLastReadingWhere(
    const std::function<bool(const Reading&)>& aPredicate, const Instant& anInstant
) const
{
    if (!anInstant.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

    Instant searchInstant = anInstant - Duration::Days(1);

    // Search monthly data backwards, skips if not relevant
    while (monthlyPredictionInterval_.contains(searchInstant) && searchInstant > dailyPredictionInterval_.getEnd())
    {
        const CSSISpaceWeather::Reading& reading = this->getMonthlyPredictionAt(searchInstant);

        if (aPredicate(reading))
        {
            return reading;
        }

        // Go back in time by approximately 1 month at a time, but not past the last daily prediction
        searchInstant =
            std::max(searchInstant - Duration::Days(30), dailyPredictionInterval_.getEnd() - Duration::Days(1));
    }

    // Search daily predicton data backwards, skips if not relevant
    while (dailyPredictionInterval_.contains(searchInstant))
    {
        const CSSISpaceWeather::Reading& reading = this->getDailyPredictionAt(searchInstant);

        if (aPredicate(reading))
        {
            return reading;
        }

        searchInstant -= Duration::Days(1);
    }

    // Search observation data backwards, skips if not relevant
    while (observationInterval_.contains(searchInstant))
    {
        const CSSISpaceWeather::Reading& reading = this->getObservationAt(searchInstant);

        if (aPredicate(reading))
        {
            return reading;
        }

        searchInstant -= Duration::Days(1);
    }

    throw ostk::core::error::RuntimeError(
        "Failed to extrapolate CSSI Space Weather Data to [{}].", anInstant.toString(Scale::UTC)
    );
}

CSSISpaceWeather CSSISpaceWeather::Load(const File& aFile)
{
    if (!aFile.exists())
    {
        throw ostk::core::error::RuntimeError("File [{}] does not exist.", aFile.toString());
    }

    CSSISpaceWeather spaceWeather;
    spaceWeather.lastModifiedTimestamp_ = getFileModifiedInstant(aFile);

    Table spaceWeatherTable = Table::Load(aFile, Table::Format::CSV, true);

    // Helper functions to parse optional integer/double cells
    const auto parseOptionalIntegerCell = [](const Object& obj) -> std::optional<int>
    {
        if (!obj.isDefined())
            return std::nullopt;

        if (obj.isInteger())
            return static_cast<int>(obj.getInteger());

        if (!obj.isString())
            return std::nullopt;

        if (String(obj.getString()).trim().empty())
            return std::nullopt;

        return ParseInt(String(obj.getString()).trim());
    };

    const auto parseOptionalRealCell = [](const Object& obj) -> std::optional<double>
    {
        if (!obj.isDefined())
            return std::nullopt;

        if (obj.isReal())
            return obj.getReal();

        if (obj.isInteger())
            return static_cast<double>(obj.getInteger());

        if (!obj.isString())
            return std::nullopt;

        if (String(obj.getString()).trim().empty())
            return std::nullopt;

        return ParseDouble(String(obj.getString()).trim());
    };

    for (const auto& row : spaceWeatherTable)
    {
        if (row.isEmpty() || !row[0].isDefined())
        {
            continue;
        }

        const Date date = Date::Parse(row[0].getString(), Date::Format::Standard);

        // [TBR] Toss data past 2030 due to this restriction in the Instant class
        if (date.getYear() > 2030)
        {
            continue;
        }

        const int mjd = static_cast<int>(std::floor(DateTime(date, Time(0, 0, 0)).getModifiedJulianDate()));

        const std::optional<int> BSRN = parseOptionalIntegerCell(row[1]);
        const std::optional<int> ND = parseOptionalIntegerCell(row[2]);
        const std::optional<int> Kp1 = parseOptionalIntegerCell(row[3]);
        const std::optional<int> Kp2 = parseOptionalIntegerCell(row[4]);
        const std::optional<int> Kp3 = parseOptionalIntegerCell(row[5]);
        const std::optional<int> Kp4 = parseOptionalIntegerCell(row[6]);
        const std::optional<int> Kp5 = parseOptionalIntegerCell(row[7]);
        const std::optional<int> Kp6 = parseOptionalIntegerCell(row[8]);
        const std::optional<int> Kp7 = parseOptionalIntegerCell(row[9]);
        const std::optional<int> Kp8 = parseOptionalIntegerCell(row[10]);
        const std::optional<int> KpSum = parseOptionalIntegerCell(row[11]);
        const std::optional<int> Ap1 = parseOptionalIntegerCell(row[12]);
        const std::optional<int> Ap2 = parseOptionalIntegerCell(row[13]);
        const std::optional<int> Ap3 = parseOptionalIntegerCell(row[14]);
        const std::optional<int> Ap4 = parseOptionalIntegerCell(row[15]);
        const std::optional<int> Ap5 = parseOptionalIntegerCell(row[16]);
        const std::optional<int> Ap6 = parseOptionalIntegerCell(row[17]);
        const std::optional<int> Ap7 = parseOptionalIntegerCell(row[18]);
        const std::optional<int> Ap8 = parseOptionalIntegerCell(row[19]);
        const std::optional<int> ApAvg = parseOptionalIntegerCell(row[20]);
        const std::optional<double> Cp = parseOptionalRealCell(row[21]);
        const std::optional<int> C9 = parseOptionalIntegerCell(row[22]);
        const std::optional<int> ISN = parseOptionalIntegerCell(row[23]);
        const std::optional<double> F107Obs = parseOptionalRealCell(row[24]);
        const std::optional<double> F107Adj = parseOptionalRealCell(row[25]);
        const String F107DataType = row[26].getString();
        const std::optional<double> F107ObsCenter81 = parseOptionalRealCell(row[27]);
        const std::optional<double> F107ObsLast81 = parseOptionalRealCell(row[28]);
        const std::optional<double> F107AdjCenter81 = parseOptionalRealCell(row[29]);
        const std::optional<double> F107AdjLast81 = parseOptionalRealCell(row[30]);

        const CSSISpaceWeather::Reading reading = {
            date,
            BSRN,
            ND,
            Kp1,
            Kp2,
            Kp3,
            Kp4,
            Kp5,
            Kp6,
            Kp7,
            Kp8,
            KpSum,
            Ap1,
            Ap2,
            Ap3,
            Ap4,
            Ap5,
            Ap6,
            Ap7,
            Ap8,
            ApAvg,
            Cp,
            C9,
            ISN,
            F107Obs,
            F107Adj,
            F107DataType,
            F107ObsCenter81,
            F107ObsLast81,
            F107AdjCenter81,
            F107AdjLast81,
        };

        if (F107DataType == "OBS" || F107DataType == "INT")
        {
            spaceWeather.observations_.insert({mjd, reading});
        }
        else if (F107DataType == "PRD" || (F107DataType == "PRM" && date.getDay() != 1))
        {
            // PRM rows are only valid as monthly predictions when dated on the 1st of the month.
            // Upstream feeds occasionally emit a PRM row on a non-1st date to fill the gap between
            // the last observation and the first daily prediction; treat those as daily predictions
            // so the monthly-lookup invariant (keyed by 1st-of-month) holds.
            spaceWeather.dailyPredictions_.insert({mjd, reading});
        }
        else
        {
            spaceWeather.monthlyPredictions_.insert({mjd, reading});
        }
    }

    if (!spaceWeather.observations_.empty())
    {
        spaceWeather.lastObservationDate_ = spaceWeather.observations_.rbegin()->second.date;

        const Instant observationStartInstant =
            Instant::ModifiedJulianDate(static_cast<double>(spaceWeather.observations_.begin()->first), Scale::UTC);

        // End at the end of the day
        const Instant observationEndInstant =
            Instant::ModifiedJulianDate(static_cast<double>(spaceWeather.observations_.rbegin()->first), Scale::UTC) +
            Duration::Days(1);

        spaceWeather.observationInterval_ =
            Interval(observationStartInstant, observationEndInstant, Interval::Type::HalfOpenRight);
    }

    if (!spaceWeather.dailyPredictions_.empty())
    {
        const Instant dailyPredictionStartInstant =
            Instant::ModifiedJulianDate(static_cast<double>(spaceWeather.dailyPredictions_.begin()->first), Scale::UTC);

        // End at the end of the day
        const Instant dailyPredictionEndInstant =
            Instant::ModifiedJulianDate(
                static_cast<double>(spaceWeather.dailyPredictions_.rbegin()->first), Scale::UTC
            ) +
            Duration::Days(1);

        spaceWeather.dailyPredictionInterval_ =
            Interval(dailyPredictionStartInstant, dailyPredictionEndInstant, Interval::Type::HalfOpenRight);

        // Use the last daily prediction to make an artificial first monthly prediction
        // so that the data Intervals overlap
        const CSSISpaceWeather::Reading& lastDailyPrediction = spaceWeather.dailyPredictions_.rbegin()->second;

        const Date monthBeginningDate = lastDailyPrediction.date.replace(std::nullopt, std::nullopt, 1);

        CSSISpaceWeather::Reading overlapMonthlyReading = lastDailyPrediction;
        overlapMonthlyReading.date = monthBeginningDate;
        overlapMonthlyReading.F107DataType = "PRM";

        const int monthMjd =
            static_cast<int>(std::floor(DateTime(monthBeginningDate, Time::Midnight()).getModifiedJulianDate()));
        spaceWeather.monthlyPredictions_.insert({monthMjd, overlapMonthlyReading});
    }

    if (!spaceWeather.monthlyPredictions_.empty())
    {
        const Instant monthlyPredictionStartInstant = Instant::ModifiedJulianDate(
            static_cast<double>(spaceWeather.monthlyPredictions_.begin()->first), Scale::UTC
        );

        // End at the end of the day
        const Instant monthlyPredictionEndInstant = Instant::ModifiedJulianDate(
            static_cast<double>(spaceWeather.monthlyPredictions_.rbegin()->first), Scale::UTC
        );

        spaceWeather.monthlyPredictionInterval_ =
            Interval::Closed(monthlyPredictionStartInstant, monthlyPredictionEndInstant);
    }

    return spaceWeather;
}

CSSISpaceWeather CSSISpaceWeather::LoadLegacy(const File& aFile)
{
    using ostk::core::type::Index;
    using ostk::core::type::String;
    using ostk::core::type::Uint16;
    using ostk::core::type::Uint8;

    using ostk::physics::time::DateTime;
    using ostk::physics::time::Scale;
    using ostk::physics::time::Time;

    if (!aFile.exists())
    {
        throw ostk::core::error::RuntimeError("File [{}] does not exist.", aFile.toString());
    }

    CSSISpaceWeather spaceWeather;

    spaceWeather.lastModifiedTimestamp_ = getFileModifiedInstant(aFile);

    std::ifstream fileStream {aFile.getPath().toString()};

    bool readingObserved = false;
    bool readingDailyPredicted = false;
    bool readingMonthlyPredicted = false;

    String line;

    auto split_spaces = [](std::string s) -> Array<String>
    {
        Array<String> results;
        const String delimiter = " ";

        size_t last = 0;
        size_t next = 0;
        while ((next = s.find(delimiter, last)) != std::string::npos)
        {
            // account for multiple consecutive delimiters
            String token = s.substr(last, next - last);
            if (token != delimiter)
            {
                results.add(token);
            }
            last = next + 1;
        }
        results.add(s.substr(last));
        return results;
    };

    while (std::getline(fileStream, line))
    {
        Array<String> lineParts = split_spaces(line);

        // TBI: this is hacky, removes any whitespace strings
        lineParts.remove({"", " ", "  ", "   "});

        if (lineParts.empty())
        {
            continue;
        }

        // Intepret BEGIN tags
        if (lineParts.getSize() >= 2 && lineParts[0] == "BEGIN" && lineParts[1] == "OBSERVED")
        {
            readingObserved = true;
            continue;
        }

        if (lineParts.getSize() >= 2 && lineParts[0] == "BEGIN" && lineParts[1] == "DAILY_PREDICTED")
        {
            readingDailyPredicted = true;
            continue;
        }

        if (lineParts.getSize() >= 2 && lineParts[0] == "BEGIN" && lineParts[1] == "MONTHLY_PREDICTED")
        {
            readingMonthlyPredicted = true;
            continue;
        }

        // Intepret END tags
        if (lineParts.getSize() >= 2 && lineParts[0] == "END" && lineParts[1] == "OBSERVED")
        {
            readingObserved = false;

            spaceWeather.lastObservationDate_ = spaceWeather.observations_.rbegin()->second.date;

            const Instant observationStartInstant =
                Instant::ModifiedJulianDate(static_cast<double>(spaceWeather.observations_.begin()->first), Scale::UTC);

            // End at the end of the day
            const Instant observationEndInstant =
                Instant::ModifiedJulianDate(
                    static_cast<double>(spaceWeather.observations_.rbegin()->first), Scale::UTC
                ) +
                Duration::Days(1);

            spaceWeather.observationInterval_ =
                Interval(observationStartInstant, observationEndInstant, Interval::Type::HalfOpenRight);

            continue;
        }

        if (lineParts.getSize() >= 2 && lineParts[0] == "END" && lineParts[1] == "DAILY_PREDICTED")
        {
            readingDailyPredicted = false;

            const Instant dailyPredictionStartInstant = Instant::ModifiedJulianDate(
                static_cast<double>(spaceWeather.dailyPredictions_.begin()->first), Scale::UTC
            );

            // End at the end of the day
            const Instant dailyPredictionEndInstant =
                Instant::ModifiedJulianDate(
                    static_cast<double>(spaceWeather.dailyPredictions_.rbegin()->first), Scale::UTC
                ) +
                Duration::Days(1);

            spaceWeather.dailyPredictionInterval_ =
                Interval(dailyPredictionStartInstant, dailyPredictionEndInstant, Interval::Type::HalfOpenRight);

            // Use the last daily prediction to make an artificial first monthly prediction
            // so that the data Intervals overlap
            const CSSISpaceWeather::Reading& lastDailyPrediction = spaceWeather.dailyPredictions_.rbegin()->second;

            const Date monthBeginningDate = lastDailyPrediction.date.replace(std::nullopt, std::nullopt, 1);

            CSSISpaceWeather::Reading overlapMonthlyReading = lastDailyPrediction;
            overlapMonthlyReading.date = monthBeginningDate;
            overlapMonthlyReading.F107DataType = "PRM";

            const int monthMjd =
                static_cast<int>(std::floor(DateTime(monthBeginningDate, Time::Midnight()).getModifiedJulianDate()));
            spaceWeather.monthlyPredictions_.insert({monthMjd, overlapMonthlyReading});

            continue;
        }

        if (lineParts.getSize() >= 2 && lineParts[0] == "END" && lineParts[1] == "MONTHLY_PREDICTED")
        {
            readingMonthlyPredicted = false;

            const Instant monthlyPredictionStartInstant = Instant::ModifiedJulianDate(
                static_cast<double>(spaceWeather.monthlyPredictions_.begin()->first), Scale::UTC
            );

            const Instant monthlyPredictionEndInstant = Instant::ModifiedJulianDate(
                static_cast<double>(spaceWeather.monthlyPredictions_.rbegin()->first), Scale::UTC
            );

            spaceWeather.monthlyPredictionInterval_ =
                Interval::Closed(monthlyPredictionStartInstant, monthlyPredictionEndInstant);
        }

        if (readingObserved || readingDailyPredicted || readingMonthlyPredicted)
        {
            try
            {
                int DATE_YEAR = boost::lexical_cast<int>(lineParts[0]);
                int DATE_MONT = boost::lexical_cast<int>(lineParts[1]);
                int DATE_DAY = boost::lexical_cast<int>(lineParts[2]);
                int BSRN = boost::lexical_cast<int>(lineParts[3]);
                int ND = boost::lexical_cast<int>(lineParts[4]);
                int Kp1 = boost::lexical_cast<int>(lineParts[5]);
                int Kp2 = boost::lexical_cast<int>(lineParts[6]);
                int Kp3 = boost::lexical_cast<int>(lineParts[7]);
                int Kp4 = boost::lexical_cast<int>(lineParts[8]);
                int Kp5 = boost::lexical_cast<int>(lineParts[9]);
                int Kp6 = boost::lexical_cast<int>(lineParts[10]);
                int Kp7 = boost::lexical_cast<int>(lineParts[11]);
                int Kp8 = boost::lexical_cast<int>(lineParts[12]);
                int KpSum = boost::lexical_cast<int>(lineParts[13]);
                int Ap1 = boost::lexical_cast<int>(lineParts[14]);
                int Ap2 = boost::lexical_cast<int>(lineParts[15]);
                int Ap3 = boost::lexical_cast<int>(lineParts[16]);
                int Ap4 = boost::lexical_cast<int>(lineParts[17]);
                int Ap5 = boost::lexical_cast<int>(lineParts[18]);
                int Ap6 = boost::lexical_cast<int>(lineParts[19]);
                int Ap7 = boost::lexical_cast<int>(lineParts[20]);
                int Ap8 = boost::lexical_cast<int>(lineParts[21]);
                int ApAvg = boost::lexical_cast<int>(lineParts[22]);
                double Cp = boost::lexical_cast<double>(lineParts[23]);
                int C9 = boost::lexical_cast<int>(lineParts[24]);
                int ISN = boost::lexical_cast<int>(lineParts[25]);
                double F107Adj = boost::lexical_cast<double>(lineParts[26]);
                // double Q = boost::lexical_cast<double>(lineParts[27]); // This isn't in the CSV format, so let's
                // ignore it
                double F107AdjCenter81 = boost::lexical_cast<double>(lineParts[28]);
                double F107AdjLast81 = boost::lexical_cast<double>(lineParts[29]);
                double F107Obs = boost::lexical_cast<double>(lineParts[30]);
                double F107ObsCenter81 = boost::lexical_cast<double>(lineParts[31]);
                double F107ObsLast81 = boost::lexical_cast<double>(lineParts[32]);

                Date date = Date(DATE_YEAR, DATE_MONT, DATE_DAY);

                // [TBR] Toss data before 1970 and past 2030 due to this restriction in the Instant class
                if (date.getYear() < 1970 || date.getYear() > 2030)
                {
                    continue;
                }

                const int mjd = static_cast<int>(std::floor(DateTime(date, Time(0, 0, 0)).getModifiedJulianDate()));

                String F107DataType;

                if (readingObserved)
                {
                    F107DataType = "OBS";
                }
                else if (readingDailyPredicted)
                {
                    F107DataType = "PRD";
                }
                else if (readingMonthlyPredicted)
                {
                    F107DataType = "PRM";
                }

                const CSSISpaceWeather::Reading reading = {
                    date,
                    BSRN,
                    ND,
                    Kp1,
                    Kp2,
                    Kp3,
                    Kp4,
                    Kp5,
                    Kp6,
                    Kp7,
                    Kp8,
                    KpSum,
                    Ap1,
                    Ap2,
                    Ap3,
                    Ap4,
                    Ap5,
                    Ap6,
                    Ap7,
                    Ap8,
                    ApAvg,
                    Cp,
                    C9,
                    ISN,
                    F107Obs,
                    F107Adj,
                    F107DataType,
                    F107ObsCenter81,
                    F107ObsLast81,
                    F107AdjCenter81,
                    F107AdjLast81,
                };

                if (readingObserved)
                {
                    spaceWeather.observations_.insert({mjd, reading});
                }
                else if (readingDailyPredicted)
                {
                    spaceWeather.dailyPredictions_.insert({mjd, reading});
                }
                else if (readingMonthlyPredicted)
                {
                    spaceWeather.monthlyPredictions_.insert({mjd, reading});
                }

                continue;
            }
            catch (...)
            {
                throw ostk::core::error::RuntimeError("CSSISpaceWeather failed to parse line: {}", line);
            }
        }
    }

    return spaceWeather;
}

CSSISpaceWeather::CSSISpaceWeather()
    : lastObservationDate_(std::nullopt),
      lastModifiedTimestamp_(Instant::Undefined()),
      observationInterval_(Interval::Undefined()),
      observations_(Map<int, CSSISpaceWeather::Reading>()),

      dailyPredictionInterval_(Interval::Undefined()),
      dailyPredictions_(Map<int, CSSISpaceWeather::Reading>()),

      monthlyPredictionInterval_(Interval::Undefined()),
      monthlyPredictions_(Map<int, CSSISpaceWeather::Reading>())
{
}

}  // namespace earth
}  // namespace atmospheric
}  // namespace environment
}  // namespace physics
}  // namespace ostk
