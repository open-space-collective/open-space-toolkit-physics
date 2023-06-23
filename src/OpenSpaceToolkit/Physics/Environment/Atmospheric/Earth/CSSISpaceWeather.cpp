/// Apache License 2.0

#include <fstream>
#include <iostream>
#include <sstream>

#include <boost/lexical_cast.hpp>

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
        const CSSISpaceWeather::Observation& observation = observationIt.second;

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
        const CSSISpaceWeather::DailyPrediction& dailyPrediction = dailyPredictionIt.second;

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
        const CSSISpaceWeather::MonthlyPrediction& monthlyPrediction = monthlyPredictionIt.second;

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

const CSSISpaceWeather::Observation& CSSISpaceWeather::accessObservationAt(const Instant& anInstant) const
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

const CSSISpaceWeather::DailyPrediction& CSSISpaceWeather::accessDailyPredictionAt(const Instant& anInstant) const
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

    throw ostk::core::error::RuntimeError("Cannot find prediction at [{}].", anInstant.toString(Scale::UTC));
}

const Interval& CSSISpaceWeather::accessMonthlyPredictionInterval() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("CSSI Space Weather");
    }

    return monthlyPredictionInterval_;
}

const CSSISpaceWeather::MonthlyPrediction& CSSISpaceWeather::accessMonthlyPredictionAt(const Instant& anInstant) const
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

    throw ostk::core::error::RuntimeError("Cannot find prediction at [{}].", anInstant.toString(Scale::UTC));
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
    std::ifstream fileStream {aFile.getPath().toString()};

    String line;

    // TBI: Use split from string type once new OSTk Core released
    auto split = [](String s, const String delimiter) -> Array<String>
    {
        Array<String> results;

        if (s.empty())
        {
            return results;
        }

        Size last = 0;
        Size next = 0;
        while ((next = s.find(delimiter, last)) != std::string::npos)
        {
            results.add(s.substr(last, next - last));
            last = next + 1;
        }

        results.add(s.substr(last));
        return results;
    };

    while (std::getline(fileStream, line))
    {
        Array<String> lineParts = split(String(line).trim(), ",");

        if (lineParts.empty() || lineParts[0] == "DATE")
        {
            continue;
        }

        // Data points that exist for every reading
        const Date date = Date::Parse(lineParts[0], Date::Format::Standard);

        // [TBR] Toss data past 2030 due to this restriction in the Instant class
        if (date.getYear() > 2030)
        {
            continue;
        }

        const Integer BSRN = boost::lexical_cast<int>(lineParts[1]);
        const Integer ND = boost::lexical_cast<int>(lineParts[2]);
        const Integer ISN = boost::lexical_cast<int>(lineParts[23]);
        const Real F107Obs = boost::lexical_cast<double>(lineParts[24]);
        const Real F107Adj = boost::lexical_cast<double>(lineParts[25]);
        const String F107DataType = lineParts[26];
        const Real F107ObsCenter81 = boost::lexical_cast<double>(lineParts[27]);
        const Real F107ObsLast81 = boost::lexical_cast<double>(lineParts[28]);
        const Real F107AdjCenter81 = boost::lexical_cast<double>(lineParts[29]);
        const Real F107AdjLast81 = boost::lexical_cast<double>(String(lineParts[30]));

        const Integer mjd = DateTime(date, Time(0, 0, 0)).getModifiedJulianDate().floor();

        // observed and daily predicted readings
        if (F107DataType == "OBS" || F107DataType == "INT" || F107DataType == "PRD")
        {
            // Data points that exist for observed and daily predicted readings
            const Integer Kp1 = boost::lexical_cast<int>(lineParts[3]);
            const Integer Kp2 = boost::lexical_cast<int>(lineParts[4]);
            const Integer Kp3 = boost::lexical_cast<int>(lineParts[5]);
            const Integer Kp4 = boost::lexical_cast<int>(lineParts[6]);
            const Integer Kp5 = boost::lexical_cast<int>(lineParts[7]);
            const Integer Kp6 = boost::lexical_cast<int>(lineParts[8]);
            const Integer Kp7 = boost::lexical_cast<int>(lineParts[9]);
            const Integer Kp8 = boost::lexical_cast<int>(lineParts[10]);
            const Integer KpSum = boost::lexical_cast<int>(lineParts[11]);
            const Integer Ap1 = boost::lexical_cast<int>(lineParts[12]);
            const Integer Ap2 = boost::lexical_cast<int>(lineParts[13]);
            const Integer Ap3 = boost::lexical_cast<int>(lineParts[14]);
            const Integer Ap4 = boost::lexical_cast<int>(lineParts[15]);
            const Integer Ap5 = boost::lexical_cast<int>(lineParts[16]);
            const Integer Ap6 = boost::lexical_cast<int>(lineParts[17]);
            const Integer Ap7 = boost::lexical_cast<int>(lineParts[18]);
            const Integer Ap8 = boost::lexical_cast<int>(lineParts[19]);
            const Integer ApAvg = boost::lexical_cast<int>(lineParts[20]);
            const Real Cp = boost::lexical_cast<double>(lineParts[21]);
            const Integer C9 = boost::lexical_cast<int>(lineParts[22]);

            const CSSISpaceWeather::Observation reading = {
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
            else
            {
                spaceWeather.dailyPredictions_.insert({mjd, reading});
            }
        }

        // monthly predicted readings
        if (F107DataType == "PRM")
        {
            const CSSISpaceWeather::MonthlyPrediction reading = {
                date,
                BSRN,
                ND,
                ISN,
                F107Obs,
                F107Adj,
                F107DataType,
                F107ObsCenter81,
                F107ObsLast81,
                F107AdjCenter81,
                F107AdjLast81,
            };

            spaceWeather.monthlyPredictions_.insert({mjd, reading});
        }
    }

    if (!spaceWeather.observations_.empty())
    {
        spaceWeather.lastObservationDate_ = spaceWeather.observations_.rbegin()->second.date;

        const Instant observationStartInstant =
            Instant::ModifiedJulianDate(Real::Integer(spaceWeather.observations_.begin()->first), Scale::UTC);
        const Instant observationEndInstant =
            Instant::ModifiedJulianDate(Real::Integer(spaceWeather.observations_.rbegin()->first), Scale::UTC);

        spaceWeather.observationInterval_ = Interval::Closed(observationStartInstant, observationEndInstant);
    }

    if (!spaceWeather.dailyPredictions_.empty())
    {
        const Instant dailyPredictionStartInstant =
            Instant::ModifiedJulianDate(Real::Integer(spaceWeather.dailyPredictions_.begin()->first), Scale::UTC);
        const Instant dailyPredictionEndInstant =
            Instant::ModifiedJulianDate(Real::Integer(spaceWeather.dailyPredictions_.rbegin()->first), Scale::UTC);

        spaceWeather.dailyPredictionInterval_ =
            Interval::Closed(dailyPredictionStartInstant, dailyPredictionEndInstant);

        // Use the last daily prediction to make an artificial first monthly prediction
        // so that the data overlaps
        const CSSISpaceWeather::DailyPrediction& lastDailyPrediction = spaceWeather.dailyPredictions_.rbegin()->second;

        Date monthBeginningDate = lastDailyPrediction.date;
        monthBeginningDate.setDay(1);

        const CSSISpaceWeather::MonthlyPrediction overlapMonthlyReading = {
            monthBeginningDate,
            lastDailyPrediction.BSRN,
            lastDailyPrediction.ND,
            lastDailyPrediction.ISN,
            lastDailyPrediction.F107Obs,
            lastDailyPrediction.F107Adj,
            lastDailyPrediction.F107DataType,
            lastDailyPrediction.F107ObsCenter81,
            lastDailyPrediction.F107ObsLast81,
            lastDailyPrediction.F107AdjCenter81,
            lastDailyPrediction.F107AdjLast81,
        };
        const Integer monthMjd = DateTime(monthBeginningDate, Time::Midnight()).getModifiedJulianDate().floor();
        spaceWeather.monthlyPredictions_.insert({monthMjd, overlapMonthlyReading});
    }

    if (!spaceWeather.monthlyPredictions_.empty())
    {
        const Instant monthlyPredictionStartInstant =
            Instant::ModifiedJulianDate(Real::Integer(spaceWeather.monthlyPredictions_.begin()->first), Scale::UTC);
        const Instant monthlyPredictionEndInstant =
            Instant::ModifiedJulianDate(Real::Integer(spaceWeather.monthlyPredictions_.rbegin()->first), Scale::UTC);

        spaceWeather.monthlyPredictionInterval_ =
            Interval::Closed(monthlyPredictionStartInstant, monthlyPredictionEndInstant);
    }

    return spaceWeather;
}

}  // namespace earth
}  // namespace atmospheric
}  // namespace environment
}  // namespace physics
}  // namespace ostk
