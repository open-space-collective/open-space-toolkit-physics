/// Apache License 2.0

#include <fstream>
#include <iostream>
#include <sstream>

#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/trim.hpp>

#include <OpenSpaceToolkit/Core/Containers/Table.hpp>
#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Types/Size.hpp>
#include <OpenSpaceToolkit/Core/Types/String.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/CSSISpaceWeather.hpp>

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

using ostk::core::types::Index;
using ostk::core::types::Uint8;
using ostk::core::types::Uint16;
using ostk::core::types::Size;
using ostk::core::types::Real;
using ostk::core::types::String;
using ostk::core::utils::Print;
using ostk::core::ctnr::Table;

using ostk::physics::time::Scale;
using ostk::physics::time::Time;
using ostk::physics::time::DateTime;

std::ostream& operator<<(std::ostream& anOutputStream, const CSSISpaceWeather& aCSSISpaceWeather)
{
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
            "{:04}-{:02}-{:02}  {:>4d}  {:>2d}  {:>2d}  {:>2d}  {:>2d}  {:>2d}  {:>2d}  {:>2d}  {:>2d}  {:>2d}  {:>4d} "
            " {:>2d}  {:>2d}  {:>2d}  {:>2d}  {:>2d}  {:>2d}  {:>2d}  {:>2d}  {:>2d}  {:.2f}  {:>2d}  {:>4d}  {:6.2f}  "
            "{:6.2f}  {:s}  {:6.2f}  {:6.2f}  {:6.2f}  {:6.2f}",
            observation.date.getYear(),
            observation.date.getMonth(),
            observation.date.getDay(),
            observation.BSRN,
            observation.ND,
            observation.Kp1,
            observation.Kp2,
            observation.Kp3,
            observation.Kp4,
            observation.Kp5,
            observation.Kp6,
            observation.Kp7,
            observation.Kp8,
            observation.KpSum,
            observation.Ap1,
            observation.Ap2,
            observation.Ap3,
            observation.Ap4,
            observation.Ap5,
            observation.Ap6,
            observation.Ap7,
            observation.Ap8,
            observation.ApAvg,
            observation.Cp,
            observation.C9,
            observation.ISN,
            observation.F107Obs,
            observation.F107Adj,
            observation.F107DataType,
            observation.F107ObsCenter81,
            observation.F107ObsLast81,
            observation.F107AdjCenter81,
            observation.F107AdjLast81
        );
    }

    Print::Separator(anOutputStream, "Daily Predictions");
    Print::Line(anOutputStream) << dataHeader;

    for (const auto& dailyPredictionIt : aCSSISpaceWeather.dailyPredictions_)
    {
        const CSSISpaceWeather::Reading& dailyPrediction = dailyPredictionIt.second;

        Print::Line(anOutputStream) << String::Format(
            "{:04}-{:02}-{:02}  {:>4d}  {:>2d}  {:>2d}  {:>2d}  {:>2d}  {:>2d}  {:>2d}  {:>2d}  {:>2d}  {:>2d}  {:>4d} "
            " {:>2d}  {:>2d}  {:>2d}  {:>2d}  {:>2d}  {:>2d}  {:>2d}  {:>2d}  {:>2d}  {:.2f}  {:>2d}  {:>4d}  {:6.2f}  "
            "{:6.2f}  {:s}  {:6.2f}  {:6.2f}  {:6.2f}  {:6.2f}",
            dailyPrediction.date.getYear(),
            dailyPrediction.date.getMonth(),
            dailyPrediction.date.getDay(),
            dailyPrediction.BSRN,
            dailyPrediction.ND,
            dailyPrediction.Kp1,
            dailyPrediction.Kp2,
            dailyPrediction.Kp3,
            dailyPrediction.Kp4,
            dailyPrediction.Kp5,
            dailyPrediction.Kp6,
            dailyPrediction.Kp7,
            dailyPrediction.Kp8,
            dailyPrediction.KpSum,
            dailyPrediction.Ap1,
            dailyPrediction.Ap2,
            dailyPrediction.Ap3,
            dailyPrediction.Ap4,
            dailyPrediction.Ap5,
            dailyPrediction.Ap6,
            dailyPrediction.Ap7,
            dailyPrediction.Ap8,
            dailyPrediction.ApAvg,
            dailyPrediction.Cp,
            dailyPrediction.C9,
            dailyPrediction.ISN,
            dailyPrediction.F107Obs,
            dailyPrediction.F107Adj,
            dailyPrediction.F107DataType,
            dailyPrediction.F107ObsCenter81,
            dailyPrediction.F107ObsLast81,
            dailyPrediction.F107AdjCenter81,
            dailyPrediction.F107AdjLast81
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
            "{:04}-{:02}-{:02}  {:>4d}  {:>2d}  {:>4d}  {:6.2f}  {:6.2f}  {:s}  {:6.2f}  {:6.2f}  {:6.2f}  {:6.2f}",
            monthlyPrediction.date.getYear(),
            monthlyPrediction.date.getMonth(),
            monthlyPrediction.date.getDay(),
            monthlyPrediction.BSRN,
            monthlyPrediction.ND,
            monthlyPrediction.ISN,
            monthlyPrediction.F107Obs,
            monthlyPrediction.F107Adj,
            monthlyPrediction.F107DataType,
            monthlyPrediction.F107ObsCenter81,
            monthlyPrediction.F107ObsLast81,
            monthlyPrediction.F107AdjCenter81,
            monthlyPrediction.F107AdjLast81
        );
    }

    Print::Footer(anOutputStream);

    return anOutputStream;
}

bool CSSISpaceWeather::isDefined() const
{
    return observationInterval_.isDefined() && (!observations_.empty()) && dailyPredictionInterval_.isDefined() &&
           (!dailyPredictions_.empty()) && monthlyPredictionInterval_.isDefined() && (!monthlyPredictions_.empty());
}

const Date& CSSISpaceWeather::accessLastObservationDate() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("CSSI Space Weather");
    }

    return lastObservationDate_;
}

const Interval& CSSISpaceWeather::accessObservationInterval() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("CSSI Space Weather");
    }

    return observationInterval_;
}

const CSSISpaceWeather::Reading& CSSISpaceWeather::accessObservationAt(const Instant& anInstant) const
{
    if (!anInstant.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("CSSI Space Weather");
    }

    if (!observationInterval_.contains(anInstant))
    {
        throw ostk::core::error::RuntimeError(
            "Instant [{}] out of observation range [{} - {}].",
            anInstant.toString(Scale::UTC),
            observationInterval_.accessStart().toString(Scale::UTC),
            observationInterval_.accessEnd().toString(Scale::UTC)
        );
    }

    const Real instantMjd = anInstant.getModifiedJulianDate(Scale::UTC);

    const auto observationIt = observations_.find(instantMjd.floor());

    if (observationIt != observations_.end())
    {
        return observationIt->second;
    }

    throw ostk::core::error::RuntimeError("Cannot find observation at [{}].", anInstant.toString(Scale::UTC));
}

const Interval& CSSISpaceWeather::accessDailyPredictionInterval() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("CSSI Space Weather");
    }

    return dailyPredictionInterval_;
}

const CSSISpaceWeather::Reading& CSSISpaceWeather::accessDailyPredictionAt(const Instant& anInstant) const
{
    if (!anInstant.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("CSSI Space Weather");
    }

    if (!dailyPredictionInterval_.contains(anInstant))
    {
        throw ostk::core::error::RuntimeError(
            "Instant [{}] out of prediction range [{} - {}].",
            anInstant.toString(Scale::UTC),
            dailyPredictionInterval_.accessStart().toString(Scale::UTC),
            dailyPredictionInterval_.accessEnd().toString(Scale::UTC)
        );
    }

    const Real instantMjd = anInstant.getModifiedJulianDate(Scale::UTC);

    const auto predictionIt = dailyPredictions_.find(instantMjd.floor());

    if (predictionIt != dailyPredictions_.end())
    {
        return predictionIt->second;
    }

    throw ostk::core::error::RuntimeError("Cannot find daily prediction at [{}].", anInstant.toString(Scale::UTC));
}

const Interval& CSSISpaceWeather::accessMonthlyPredictionInterval() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("CSSI Space Weather");
    }

    return monthlyPredictionInterval_;
}

const CSSISpaceWeather::Reading& CSSISpaceWeather::accessMonthlyPredictionAt(const Instant& anInstant) const
{
    if (!anInstant.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("CSSI Space Weather");
    }

    if (!monthlyPredictionInterval_.contains(anInstant))
    {
        throw ostk::core::error::RuntimeError(
            "Instant [{}] out of prediction range [{} - {}].",
            anInstant.toString(Scale::UTC),
            monthlyPredictionInterval_.accessStart().toString(Scale::UTC),
            monthlyPredictionInterval_.accessEnd().toString(Scale::UTC)
        );
    }

    const Integer year = anInstant.getDateTime(Scale::UTC).getDate().getYear();
    const Integer month = anInstant.getDateTime(Scale::UTC).getDate().getMonth();

    const Real monthMjd = DateTime(year, month, 1).getModifiedJulianDate();

    const auto predictionIt = monthlyPredictions_.find(monthMjd.floor());

    if (predictionIt != monthlyPredictions_.end())
    {
        return predictionIt->second;
    }

    throw ostk::core::error::RuntimeError("Cannot find monthly prediction at [{}].", anInstant.toString(Scale::UTC));
}

const CSSISpaceWeather::Reading& CSSISpaceWeather::accessReadingAt(const Instant& anInstant) const
{
    if (observationInterval_.contains(anInstant))
    {
        return this->accessObservationAt(anInstant);
    }
    if (dailyPredictionInterval_.contains(anInstant))
    {
        return this->accessDailyPredictionAt(anInstant);
    }
    if (monthlyPredictionInterval_.contains(anInstant))
    {
        return this->accessMonthlyPredictionAt(anInstant);
    }

    throw ostk::core::error::RuntimeError(
        "Instant [{}] out of range [{} - {}].",
        anInstant.toString(Scale::UTC),
        observationInterval_.accessStart().toString(Scale::UTC),
        monthlyPredictionInterval_.accessEnd().toString(Scale::UTC)
    );
}

const CSSISpaceWeather::Reading& CSSISpaceWeather::accessLastReadingWhere(
    const std::function<bool(const Reading&)>& aPredicate, const Instant& anInstant
) const
{
    if (!anInstant.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("CSSI Space Weather");
    }

    Instant searchInstant = anInstant - Duration::Days(1);

    // Search monthly data backwards, skips if not relevant
    while (monthlyPredictionInterval_.contains(searchInstant) && searchInstant > dailyPredictionInterval_.accessEnd())
    {
        const CSSISpaceWeather::Reading& reading = this->accessMonthlyPredictionAt(searchInstant);

        if (aPredicate(reading))
        {
            return reading;
        }

        // Go back in time by approximately 1 month at a time, but not past the last daily prediction
        searchInstant = std::max(searchInstant - Duration::Days(30), dailyPredictionInterval_.accessEnd() - Duration::Days(1));
    }

    // Search daily predicton data backwards, skips if not relevant
    while (dailyPredictionInterval_.contains(searchInstant))
    {
        const CSSISpaceWeather::Reading& reading = this->accessDailyPredictionAt(searchInstant);

        if (aPredicate(reading))
        {
            return reading;
        }

        searchInstant -= Duration::Days(1);
    }

    // Search observation data backwards, skips if not relevant
    while (observationInterval_.contains(searchInstant))
    {
        const CSSISpaceWeather::Reading& reading = this->accessObservationAt(searchInstant);

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

CSSISpaceWeather CSSISpaceWeather::Undefined()
{
    return CSSISpaceWeather();
}

CSSISpaceWeather CSSISpaceWeather::Load(const File& aFile)
{
    if (!aFile.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("File");
    }

    if (!aFile.exists())
    {
        throw ostk::core::error::RuntimeError("File [{}] does not exist.", aFile.toString());
    }

    CSSISpaceWeather spaceWeather;

    Table spaceWeatherTable = Table::Load(aFile, Table::Format::CSV, true);

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

        const Integer mjd = DateTime(date, Time(0, 0, 0)).getModifiedJulianDate().floor();

        const Integer BSRN = row[1].isDefined() ? row[1].getInteger() : Integer::Undefined();
        const Integer ND = row[2].isDefined() ? row[2].getInteger() : Integer::Undefined();
        const Integer Kp1 = row[3].isDefined() ? row[3].getInteger() : Integer::Undefined();
        const Integer Kp2 = row[4].isDefined() ? row[4].getInteger() : Integer::Undefined();
        const Integer Kp3 = row[5].isDefined() ? row[5].getInteger() : Integer::Undefined();
        const Integer Kp4 = row[6].isDefined() ? row[6].getInteger() : Integer::Undefined();
        const Integer Kp5 = row[7].isDefined() ? row[7].getInteger() : Integer::Undefined();
        const Integer Kp6 = row[8].isDefined() ? row[8].getInteger() : Integer::Undefined();
        const Integer Kp7 = row[9].isDefined() ? row[9].getInteger() : Integer::Undefined();
        const Integer Kp8 = row[10].isDefined() ? row[10].getInteger() : Integer::Undefined();
        const Integer KpSum = row[11].isDefined() ? row[11].getInteger() : Integer::Undefined();
        const Integer Ap1 = row[12].isDefined() ? row[12].getInteger() : Integer::Undefined();
        const Integer Ap2 = row[13].isDefined() ? row[13].getInteger() : Integer::Undefined();
        const Integer Ap3 = row[14].isDefined() ? row[14].getInteger() : Integer::Undefined();
        const Integer Ap4 = row[15].isDefined() ? row[15].getInteger() : Integer::Undefined();
        const Integer Ap5 = row[16].isDefined() ? row[16].getInteger() : Integer::Undefined();
        const Integer Ap6 = row[17].isDefined() ? row[17].getInteger() : Integer::Undefined();
        const Integer Ap7 = row[18].isDefined() ? row[18].getInteger() : Integer::Undefined();
        const Integer Ap8 = row[19].isDefined() ? row[19].getInteger() : Integer::Undefined();
        const Integer ApAvg = row[20].isDefined() ? row[20].getInteger() : Integer::Undefined();
        const Real Cp = row[21].isDefined() ? row[21].getReal() : Real::Undefined();
        const Integer C9 = row[22].isDefined() ? row[22].getInteger() : Integer::Undefined();
        const Integer ISN = row[23].isDefined() ? row[23].getInteger() : Integer::Undefined();
        const Real F107Obs = row[24].isDefined() ? row[24].getReal() : Real::Undefined();
        const Real F107Adj = row[25].isDefined() ? row[25].getReal() : Real::Undefined();
        const String F107DataType = row[26].getString();
        const Real F107ObsCenter81 = row[27].isDefined() ? row[27].getReal() : Real::Undefined();
        const Real F107ObsLast81 = row[28].isDefined() ? row[28].getReal() : Real::Undefined();
        const Real F107AdjCenter81 = row[29].isDefined() ? row[29].getReal() : Real::Undefined();
        const Real F107AdjLast81 = row[30].isDefined() ? row[30].getReal() : Real::Undefined();

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
        else if (F107DataType == "PRD")
        {
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
            Instant::ModifiedJulianDate(Real::Integer(spaceWeather.observations_.begin()->first), Scale::UTC);

        // End at the end of the day
        const Instant observationEndInstant =
            Instant::ModifiedJulianDate(Real::Integer(spaceWeather.observations_.rbegin()->first), Scale::UTC) +
            Duration::Days(1);

        spaceWeather.observationInterval_ = Interval(observationStartInstant, observationEndInstant, Interval::Type::HalfOpenRight);
    }

    if (!spaceWeather.dailyPredictions_.empty())
    {
        const Instant dailyPredictionStartInstant =
            Instant::ModifiedJulianDate(Real::Integer(spaceWeather.dailyPredictions_.begin()->first), Scale::UTC);

        // End at the end of the day
        const Instant dailyPredictionEndInstant =
            Instant::ModifiedJulianDate(Real::Integer(spaceWeather.dailyPredictions_.rbegin()->first), Scale::UTC) +
            Duration::Days(1);

        spaceWeather.dailyPredictionInterval_ =
            Interval(dailyPredictionStartInstant, dailyPredictionEndInstant, Interval::Type::HalfOpenRight);

        // Use the last daily prediction to make an artificial first monthly prediction
        // so that the data Intervals overlap
        const CSSISpaceWeather::Reading& lastDailyPrediction = spaceWeather.dailyPredictions_.rbegin()->second;

        Date monthBeginningDate = lastDailyPrediction.date;
        monthBeginningDate.setDay(1);

        CSSISpaceWeather::Reading overlapMonthlyReading = lastDailyPrediction;
        overlapMonthlyReading.date = monthBeginningDate;
        overlapMonthlyReading.F107DataType = "PRM";

        const Integer monthMjd = DateTime(monthBeginningDate, Time::Midnight()).getModifiedJulianDate().floor();
        spaceWeather.monthlyPredictions_.insert({monthMjd, overlapMonthlyReading});
    }

    if (!spaceWeather.monthlyPredictions_.empty())
    {
        const Instant monthlyPredictionStartInstant =
            Instant::ModifiedJulianDate(Real::Integer(spaceWeather.monthlyPredictions_.begin()->first), Scale::UTC);

        // End at the end of the day
        const Instant monthlyPredictionEndInstant =
            Instant::ModifiedJulianDate(Real::Integer(spaceWeather.monthlyPredictions_.rbegin()->first), Scale::UTC);

        spaceWeather.monthlyPredictionInterval_ =
            Interval::Closed(monthlyPredictionStartInstant, monthlyPredictionEndInstant);
    }

    return spaceWeather;
}

CSSISpaceWeather CSSISpaceWeather::LoadLegacy(const File& aFile)
{
    using ostk::core::types::Index;
    using ostk::core::types::Uint8;
    using ostk::core::types::Uint16;
    using ostk::core::types::Real;
    using ostk::core::types::String;

    using ostk::physics::time::Scale;
    using ostk::physics::time::Time;
    using ostk::physics::time::DateTime;

    if (!aFile.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("File");
    }

    if (!aFile.exists())
    {
        throw ostk::core::error::RuntimeError("File [{}] does not exist.", aFile.toString());
    }

    CSSISpaceWeather spaceWeather;

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
                Instant::ModifiedJulianDate(Real::Integer(spaceWeather.observations_.begin()->first), Scale::UTC);

            // End at the end of the day
            const Instant observationEndInstant =
                Instant::ModifiedJulianDate(Real::Integer(spaceWeather.observations_.rbegin()->first), Scale::UTC) +
                Duration::Days(1);

            spaceWeather.observationInterval_ = Interval(observationStartInstant, observationEndInstant, Interval::Type::HalfOpenRight);

            continue;
        }

        if (lineParts.getSize() >= 2 && lineParts[0] == "END" && lineParts[1] == "DAILY_PREDICTED")
        {

            readingDailyPredicted = false;

            const Instant dailyPredictionStartInstant =
                Instant::ModifiedJulianDate(Real::Integer(spaceWeather.dailyPredictions_.begin()->first), Scale::UTC);

            // End at the end of the day
            const Instant dailyPredictionEndInstant =
                Instant::ModifiedJulianDate(Real::Integer(spaceWeather.dailyPredictions_.rbegin()->first), Scale::UTC) +
                Duration::Days(1);

            spaceWeather.dailyPredictionInterval_ =
                Interval(dailyPredictionStartInstant, dailyPredictionEndInstant, Interval::Type::HalfOpenRight);

            // Use the last daily prediction to make an artificial first monthly prediction
            // so that the data Intervals overlap
            const CSSISpaceWeather::Reading& lastDailyPrediction = spaceWeather.dailyPredictions_.rbegin()->second;

            Date monthBeginningDate = lastDailyPrediction.date;
            monthBeginningDate.setDay(1);

            CSSISpaceWeather::Reading overlapMonthlyReading = lastDailyPrediction;
            overlapMonthlyReading.date = monthBeginningDate;
            overlapMonthlyReading.F107DataType = "PRM";

            const Integer monthMjd = DateTime(monthBeginningDate, Time::Midnight()).getModifiedJulianDate().floor();
            spaceWeather.monthlyPredictions_.insert({monthMjd, overlapMonthlyReading});

            continue;
        }

        if (lineParts.getSize() >= 2 && lineParts[0] == "END" && lineParts[1] == "MONTHLY_PREDICTED")
        {
            readingMonthlyPredicted = false;
            
            const Instant monthlyPredictionStartInstant =
                Instant::ModifiedJulianDate(Real::Integer(spaceWeather.monthlyPredictions_.begin()->first), Scale::UTC);

            const Instant monthlyPredictionEndInstant =
                Instant::ModifiedJulianDate(Real::Integer(spaceWeather.monthlyPredictions_.rbegin()->first), Scale::UTC);

            spaceWeather.monthlyPredictionInterval_ =
                Interval::Closed(monthlyPredictionStartInstant, monthlyPredictionEndInstant);
        }

        if (readingObserved || readingDailyPredicted || readingMonthlyPredicted)
        {   
            // From docs:
            // FORMAT(I4,I3,I3,I5,I3,8I3,I4,8I4,I4,F4.1,I2,I4,F6.1,I2,5F6.1)
            try{
            Integer DATE_YEAR = boost::lexical_cast<int>(lineParts[0]);
            Integer DATE_MONT = boost::lexical_cast<int>(lineParts[1]);
            Integer DATE_DAY = boost::lexical_cast<int>(lineParts[2]);
            Integer BSRN = boost::lexical_cast<int>(lineParts[3]);
            Integer ND = boost::lexical_cast<int>(lineParts[4]);
            Integer Kp1 = boost::lexical_cast<int>(lineParts[5]);
            Integer Kp2 = boost::lexical_cast<int>(lineParts[6]);
            Integer Kp3 = boost::lexical_cast<int>(lineParts[7]);
            Integer Kp4 = boost::lexical_cast<int>(lineParts[8]);
            Integer Kp5 = boost::lexical_cast<int>(lineParts[9]);
            Integer Kp6 = boost::lexical_cast<int>(lineParts[10]);
            Integer Kp7 = boost::lexical_cast<int>(lineParts[11]);
            Integer Kp8 = boost::lexical_cast<int>(lineParts[12]);
            Integer KpSum = boost::lexical_cast<int>(lineParts[13]);
            Integer Ap1 = boost::lexical_cast<int>(lineParts[14]);
            Integer Ap2 = boost::lexical_cast<int>(lineParts[15]);
            Integer Ap3 = boost::lexical_cast<int>(lineParts[16]);
            Integer Ap4 = boost::lexical_cast<int>(lineParts[17]);
            Integer Ap5 = boost::lexical_cast<int>(lineParts[18]);
            Integer Ap6 = boost::lexical_cast<int>(lineParts[19]);
            Integer Ap7 = boost::lexical_cast<int>(lineParts[20]);
            Integer Ap8 = boost::lexical_cast<int>(lineParts[21]);
            Integer ApAvg = boost::lexical_cast<int>(lineParts[22]);
            Real Cp = boost::lexical_cast<double>(lineParts[23]);
            Integer C9 = boost::lexical_cast<int>(lineParts[24]);
            Integer ISN = boost::lexical_cast<int>(lineParts[25]);
            Real F107Adj = boost::lexical_cast<double>(lineParts[26]);
            // Real Q = boost::lexical_cast<double>(lineParts[27]); // This isn't in the CSV format, so let's ignore it
            Real F107AdjCenter81 = boost::lexical_cast<double>(lineParts[28]);
            Real F107AdjLast81 = boost::lexical_cast<double>(lineParts[29]);
            Real F107Obs = boost::lexical_cast<double>(lineParts[30]);
            Real F107ObsCenter81 = boost::lexical_cast<double>(lineParts[31]);
            Real F107ObsLast81 = boost::lexical_cast<double>(lineParts[32]);

            Date date = Date(DATE_YEAR, DATE_MONT, DATE_DAY);
            
            // [TBR] Toss data before 1970 and past 2030 due to this restriction in the Instant class
            if (date.getYear() < 1970 || date.getYear() > 2030)
            {
                continue;
            }

            const Integer mjd = DateTime(date, Time(0, 0, 0)).getModifiedJulianDate().floor();

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
                "OBS",
                F107ObsCenter81,
                F107ObsLast81,
                F107AdjCenter81,
                F107AdjLast81,
            };

            if (readingObserved){
                spaceWeather.observations_.insert({mjd, reading});
            } else if (readingDailyPredicted){
                spaceWeather.dailyPredictions_.insert({mjd, reading});
            } else if (readingMonthlyPredicted){
                spaceWeather.monthlyPredictions_.insert({mjd, reading});
            }

            continue;

            }catch (...){
                std::cout << "Error parsing line: " << line << std::endl;
                std::cout << lineParts << std::endl;
            }
        }
    }

    return spaceWeather;
}

CSSISpaceWeather::CSSISpaceWeather()
    : lastObservationDate_(Date::Undefined()),
      observationInterval_(Interval::Undefined()),
      observations_(Map<Integer, CSSISpaceWeather::Reading>()),

      dailyPredictionInterval_(Interval::Undefined()),
      dailyPredictions_(Map<Integer, CSSISpaceWeather::Reading>()),

      monthlyPredictionInterval_(Interval::Undefined()),
      monthlyPredictions_(Map<Integer, CSSISpaceWeather::Reading>())
{
}

}  // namespace earth
}  // namespace atmospheric
}  // namespace environment
}  // namespace physics
}  // namespace ostk
