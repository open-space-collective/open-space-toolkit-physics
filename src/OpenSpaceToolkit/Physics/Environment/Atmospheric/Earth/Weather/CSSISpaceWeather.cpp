/// Apache License 2.0

#include <fstream>
#include <iostream>
#include <sstream>

#include <boost/lexical_cast.hpp>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Types/String.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/Weather/CSSISpaceWeather.hpp>

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
namespace weather
{

std::ostream& operator<<(std::ostream& anOutputStream, const CSSISpaceWeather& aCSSISpaceWeather)
{

    ostk::core::utils::Print::Header(anOutputStream, "CSSI Space Weather");

    ostk::core::utils::Print::Line(anOutputStream)
        << "Observation interval:"
        << (aCSSISpaceWeather.observationInterval_.isDefined() ? aCSSISpaceWeather.observationInterval_.toString(Scale::UTC)
                                                        : "Undefined");
    ostk::core::utils::Print::Line(anOutputStream)
        << "Daily prediction interval:"
        << (aCSSISpaceWeather.dailyPredictionInterval_.isDefined() ? aCSSISpaceWeather.dailyPredictionInterval_.toString(Scale::UTC)
                                                       : "Undefined");

    ostk::core::utils::Print::Line(anOutputStream)
        << "Monthly prediction interval:"
        << (aCSSISpaceWeather.monthlyPredictionInterval_.isDefined() ? aCSSISpaceWeather.monthlyPredictionInterval_.toString(Scale::UTC)
                                                       : "Undefined");
    
    const String dataHeader = String("DATE,BSRN,ND,KP1,KP2,KP3,KP4,KP5,KP6,KP7,KP8,KP_SUM,AP1,AP2,AP3,AP4,AP5,AP6,AP7,AP8,AP_AVG,CP,C9,ISN,F10.7_OBS,F10.7_ADJ,F10.7_DATA_TYPE,F10.7_OBS_CENTER81,F10.7_OBS_LAST81,F10.7_ADJ_CENTER81,F10.7_ADJ_LAST81");

    ostk::core::utils::Print::Separator(anOutputStream, "Observations");
    ostk::core::utils::Print::Line(anOutputStream) << dataHeader;
    for (const auto& observationIt : aCSSISpaceWeather.observations_)
    {
        const CSSISpaceWeather::Observation& observation = observationIt.second;

        ostk::core::utils::Print::Line(anOutputStream) << String::Format(
            "{:04}-{:02}-{:02}  {:>4d}  {:>2d}  {:>2d}  {:>2d}  {:>2d}  {:>2d}  {:>2d}  {:>2d}  {:>2d}  {:>2d}  {:>4d}  {:>2d}  {:>2d}  {:>2d}  {:>2d}  {:>2d}  {:>2d}  {:>2d}  {:>2d}  {:>2d}  {:.2f}  {:>2d}  {:>4d}  {:6.2f}  {:6.2f}  {:s}  {:6.2f}  {:6.2f}  {:6.2f}  {:6.2f}",
            observation.date.getYear(),
            observation.date.getMonth(),
            observation.date.getDay(),
            observation.BSRN,
            observation.ND,
            observation.KP1,
            observation.KP2,
            observation.KP3,
            observation.KP4,
            observation.KP5,
            observation.KP6,
            observation.KP7,
            observation.KP8,
            observation.KP_SUM,
            observation.AP1,
            observation.AP2,
            observation.AP3,
            observation.AP4,
            observation.AP5,
            observation.AP6,
            observation.AP7,
            observation.AP8,
            observation.AP_AVG,
            observation.CP,
            observation.C9,
            observation.ISN,
            observation.F107_OBS,
            observation.F107_ADJ,
            observation.F107_DATA_TYPE,
            observation.F107_OBS_CENTER81,
            observation.F107_OBS_LAST81,
            observation.F107_ADJ_CENTER81,
            observation.F107_ADJ_LAST81
        );
    }

    ostk::core::utils::Print::Separator(anOutputStream, "Daily Predictions");
    ostk::core::utils::Print::Line(anOutputStream) << dataHeader;

    for (const auto& dailyPredictionIt : aCSSISpaceWeather.dailyPredictions_)
    {
        const CSSISpaceWeather::DailyPrediction& dailyPrediction = dailyPredictionIt.second;

        ostk::core::utils::Print::Line(anOutputStream) << String::Format(
            "{:04}-{:02}-{:02}  {:>4d}  {:>2d}  {:>2d}  {:>2d}  {:>2d}  {:>2d}  {:>2d}  {:>2d}  {:>2d}  {:>2d}  {:>4d}  {:>2d}  {:>2d}  {:>2d}  {:>2d}  {:>2d}  {:>2d}  {:>2d}  {:>2d}  {:>2d}  {:.2f}  {:>2d}  {:>4d}  {:6.2f}  {:6.2f}  {:s}  {:6.2f}  {:6.2f}  {:6.2f}  {:6.2f}",
            dailyPrediction.date.getYear(),
            dailyPrediction.date.getMonth(),
            dailyPrediction.date.getDay(),
            dailyPrediction.BSRN,
            dailyPrediction.ND,
            dailyPrediction.KP1,
            dailyPrediction.KP2,
            dailyPrediction.KP3,
            dailyPrediction.KP4,
            dailyPrediction.KP5,
            dailyPrediction.KP6,
            dailyPrediction.KP7,
            dailyPrediction.KP8,
            dailyPrediction.KP_SUM,
            dailyPrediction.AP1,
            dailyPrediction.AP2,
            dailyPrediction.AP3,
            dailyPrediction.AP4,
            dailyPrediction.AP5,
            dailyPrediction.AP6,
            dailyPrediction.AP7,
            dailyPrediction.AP8,
            dailyPrediction.AP_AVG,
            dailyPrediction.CP,
            dailyPrediction.C9,
            dailyPrediction.ISN,
            dailyPrediction.F107_OBS,
            dailyPrediction.F107_ADJ,
            dailyPrediction.F107_DATA_TYPE,
            dailyPrediction.F107_OBS_CENTER81,
            dailyPrediction.F107_OBS_LAST81,
            dailyPrediction.F107_ADJ_CENTER81,
            dailyPrediction.F107_ADJ_LAST81
        );
    }
    
    ostk::core::utils::Print::Separator(anOutputStream, "Monthly Predictions");
    ostk::core::utils::Print::Line(anOutputStream) << 
        String("DATE,BSRN,ND,ISN,F10.7_OBS,F10.7_ADJ,F10.7_DATA_TYPE,F10.7_OBS_CENTER81,F10.7_OBS_LAST81,F10.7_ADJ_CENTER81,F10.7_ADJ_LAST81");

    for (const auto& monthlyPredictionIt : aCSSISpaceWeather.monthlyPredictions_)
    {
        const CSSISpaceWeather::MonthlyPrediction& monthlyPrediction = monthlyPredictionIt.second;

        ostk::core::utils::Print::Line(anOutputStream) << String::Format(
            "{:04}-{:02}-{:02}  {:>4d}  {:>2d}  {:>4d}  {:6.2f}  {:6.2f}  {:s}  {:6.2f}  {:6.2f}  {:6.2f}  {:6.2f}",
            monthlyPrediction.date.getYear(),
            monthlyPrediction.date.getMonth(),
            monthlyPrediction.date.getDay(),
            monthlyPrediction.BSRN,
            monthlyPrediction.ND,
            monthlyPrediction.ISN,
            monthlyPrediction.F107_OBS,
            monthlyPrediction.F107_ADJ,
            monthlyPrediction.F107_DATA_TYPE,
            monthlyPrediction.F107_OBS_CENTER81,
            monthlyPrediction.F107_OBS_LAST81,
            monthlyPrediction.F107_ADJ_CENTER81,
            monthlyPrediction.F107_ADJ_LAST81
        );
    }

    ostk::core::utils::Print::Footer(anOutputStream);
    
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
    else
    {
        throw ostk::core::error::RuntimeError("Cannot find observation at [{}].", anInstant.toString(Scale::UTC));
    }
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
    else
    {
        throw ostk::core::error::RuntimeError("Cannot find prediction at [{}].", anInstant.toString(Scale::UTC));
    }
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
    else
    {
        throw ostk::core::error::RuntimeError("Cannot find prediction at [{}].", anInstant.toString(Scale::UTC));
    }
}

Date CSSISpaceWeather::getLastObservationDate() const
{
    return this->accessLastObservationDate();
}

Interval CSSISpaceWeather::getObservationInterval() const
{
    return this->accessObservationInterval();
}

CSSISpaceWeather::Observation CSSISpaceWeather::getObservationAt(const Instant& anInstant) const
{
    return this->accessObservationAt(anInstant);
}

Interval CSSISpaceWeather::getDailyPredictionInterval() const
{
    return this->accessDailyPredictionInterval();
}

CSSISpaceWeather::DailyPrediction CSSISpaceWeather::getDailyPredictionAt(const Instant& anInstant) const
{
    return this->accessDailyPredictionAt(anInstant);
}

Interval CSSISpaceWeather::getMonthlyPredictionInterval() const
{
    return this->accessMonthlyPredictionInterval();
}

CSSISpaceWeather::MonthlyPrediction CSSISpaceWeather::getMonthlyPredictionAt(const Instant& anInstant) const
{
    return this->accessMonthlyPredictionAt(anInstant);
}

CSSISpaceWeather CSSISpaceWeather::Undefined()
{
    return CSSISpaceWeather();
}

CSSISpaceWeather CSSISpaceWeather::Load(const fs::File& aFile)
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

    String line;

    auto split = [] ( String s, const String delimiter ) -> Array<String>
    {
        Array<String> results;

        if (s.empty()) { return results; }

        size_t last = 0; 
        size_t next = 0; 
        while ((next = s.find(delimiter, last)) != std::string::npos) 
        {   
            results.add(s.substr(last, next-last));
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
        const Real F107_OBS = boost::lexical_cast<double>(lineParts[24]);
        const Real F107_ADJ = boost::lexical_cast<double>(lineParts[25]);
        const String F107_DATA_TYPE = lineParts[26] ;
        const Real F107_OBS_CENTER81 = boost::lexical_cast<double>(lineParts[27]);
        const Real F107_OBS_LAST81 = boost::lexical_cast<double>(lineParts[28]);
        const Real F107_ADJ_CENTER81 = boost::lexical_cast<double>(lineParts[29]);
        const Real F107_ADJ_LAST81 = boost::lexical_cast<double>(String(lineParts[30]));

    
        const Integer mjd = DateTime(date, Time(0,0,0)).getModifiedJulianDate().floor();

        // observed and daily predicted readings
        if (F107_DATA_TYPE == "OBS" || F107_DATA_TYPE == "INT" || F107_DATA_TYPE == "PRD")
        {
            // Data points that exist for observed and daily predicted readings
            const Integer KP1 = boost::lexical_cast<int>(lineParts[3]);
            const Integer KP2 = boost::lexical_cast<int>(lineParts[4]);
            const Integer KP3 = boost::lexical_cast<int>(lineParts[5]);
            const Integer KP4 = boost::lexical_cast<int>(lineParts[6]);
            const Integer KP5 = boost::lexical_cast<int>(lineParts[7]);
            const Integer KP6 = boost::lexical_cast<int>(lineParts[8]);
            const Integer KP7 = boost::lexical_cast<int>(lineParts[9]);
            const Integer KP8 = boost::lexical_cast<int>(lineParts[10]);
            const Integer KP_SUM = boost::lexical_cast<int>(lineParts[11]);
            const Integer AP1 = boost::lexical_cast<int>(lineParts[12]);
            const Integer AP2 = boost::lexical_cast<int>(lineParts[13]);
            const Integer AP3 = boost::lexical_cast<int>(lineParts[14]);
            const Integer AP4 = boost::lexical_cast<int>(lineParts[15]);
            const Integer AP5 = boost::lexical_cast<int>(lineParts[16]);
            const Integer AP6 = boost::lexical_cast<int>(lineParts[17]);
            const Integer AP7 = boost::lexical_cast<int>(lineParts[18]);
            const Integer AP8 = boost::lexical_cast<int>(lineParts[19]);
            const Integer AP_AVG = boost::lexical_cast<int>(lineParts[20]);
            const Real CP = boost::lexical_cast<double>(lineParts[21]);
            const Integer C9 = boost::lexical_cast<int>(lineParts[22]);

            const CSSISpaceWeather::Observation reading = {
                date,
                BSRN,
                ND,
                KP1,
                KP2,
                KP3,
                KP4,
                KP5,
                KP6,
                KP7,
                KP8,
                KP_SUM,
                AP1,
                AP2,
                AP3,
                AP4,
                AP5,
                AP6,
                AP7,
                AP8,
                AP_AVG,
                CP,
                C9,
                ISN,
                F107_OBS,
                F107_ADJ,
                F107_DATA_TYPE,
                F107_OBS_CENTER81,
                F107_OBS_LAST81,
                F107_ADJ_CENTER81,
                F107_ADJ_LAST81,
            };

            if (F107_DATA_TYPE == "OBS" || F107_DATA_TYPE == "INT")
            {
                spaceWeather.observations_.insert({mjd, reading});
            } else {
                spaceWeather.dailyPredictions_.insert({mjd, reading});
            }
        }

        // monthly predicted readings
        if (F107_DATA_TYPE == "PRM")
        {

            const CSSISpaceWeather::MonthlyPrediction reading = {
                date,
                BSRN,
                ND,
                ISN,
                F107_OBS,
                F107_ADJ,
                F107_DATA_TYPE,
                F107_OBS_CENTER81,
                F107_OBS_LAST81,
                F107_ADJ_CENTER81,
                F107_ADJ_LAST81,
            };

            spaceWeather.monthlyPredictions_.insert({mjd, reading});
        }
    }

    if ( !spaceWeather.observations_.empty() )
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

        spaceWeather.dailyPredictionInterval_ = Interval::Closed(dailyPredictionStartInstant, dailyPredictionEndInstant);
    }

    if (!spaceWeather.monthlyPredictions_.empty())
    {
        const Instant monthlyPredictionStartInstant =
            Instant::ModifiedJulianDate(Real::Integer(spaceWeather.monthlyPredictions_.begin()->first), Scale::UTC);
        const Instant monthlyPredictionEndInstant =
            Instant::ModifiedJulianDate(Real::Integer(spaceWeather.monthlyPredictions_.rbegin()->first), Scale::UTC);

        spaceWeather.monthlyPredictionInterval_ = Interval::Closed(monthlyPredictionStartInstant, monthlyPredictionEndInstant);
    }

    return spaceWeather;
}

CSSISpaceWeather::CSSISpaceWeather()
    : lastObservationDate_(Date::Undefined()),
      observationInterval_(Interval::Undefined()),
      observations_(Map<Integer, CSSISpaceWeather::Observation>()),

      dailyPredictionInterval_(Interval::Undefined()),
      dailyPredictions_(Map<Integer, CSSISpaceWeather::DailyPrediction>()),

      monthlyPredictionInterval_(Interval::Undefined()),
      monthlyPredictions_(Map<Integer, CSSISpaceWeather::MonthlyPrediction>())
{
}

}  // namespace iers
}  // namespace provider
}  // namespace frame
}  // namespace coord
}  // namespace physics
}  // namespace ostk
