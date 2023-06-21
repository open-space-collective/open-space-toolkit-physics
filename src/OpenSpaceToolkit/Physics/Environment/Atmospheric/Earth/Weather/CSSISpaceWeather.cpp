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
/*
std::ostream& operator<<(std::ostream& anOutputStream, const CSSISpaceWeather& aCSSISpaceWeather)
{
    using ostk::core::types::String;

    using ostk::physics::time::Scale;

    ostk::core::utils::Print::Header(anOutputStream, "CSSI Space Weather");

    ostk::core::utils::Print::Line(anOutputStream)
        << "LastObservation date:" << (aCSSISpaceWeather.lastObservationInstant_.isDefined() ? aCSSISpaceWeather.lastObservationInstant_.toString() : "Undefined");
    
    ostk::core::utils::Print::Line(anOutputStream)
        << "Observation interval:"
        << (aCSSISpaceWeather.observationInterval_.isDefined() ? aCSSISpaceWeather.observationInterval_.toString(Scale::UTC)
                                                        : "Undefined");
    ostk::core::utils::Print::Line(anOutputStream)
        << "Predictiom interval:"
        << (aCSSISpaceWeather.predictionInterval_.isDefined() ? aCSSISpaceWeather.predictionInterval_.toString(Scale::UTC)
                                                       : "Undefined");
    
    ostk::core::utils::Print::Separator(anOutputStream, "Observation");

    for (const auto& observationIt : aCSSISpaceWeather.observations_)
    {
        const CSSISpaceWeather::Observation& observation = observationIt.second;

        ostk::core::utils::Print::Line(anOutputStream) << String::Format(
            "{:>4d}  {:>2d}  {:>2d}  {:>5d}  {:f}  {:f}  {:f}  {:f}  {:f}  {:f}",
            static_cast<int>(observation.year),
            static_cast<int>(observation.month),
            static_cast<int>(observation.day),
            static_cast<int>(observation.mjd),
            static_cast<double>(observation.x),
            static_cast<double>(observation.xError),
            static_cast<double>(observation.y),
            static_cast<double>(observation.yError),
            static_cast<double>(observation.ut1MinusUtc),
            static_cast<double>(observation.ut1MinusUtcError)
        );
    }

    ostk::core::utils::Print::Separator(anOutputStream, "Prediction");

    for (const auto& predictionIt : aCSSISpaceWeather.predictions_)
    {
        const CSSISpaceWeather::Prediction& prediction = predictionIt.second;

        ostk::core::utils::Print::Line(anOutputStream) << String::Format(
            "{:>4d}  {:>2d}  {:>2d}  {:>5d}  {:f}  {:f}  {:f}",
            static_cast<int>(prediction.year),
            static_cast<int>(prediction.month),
            static_cast<int>(prediction.day),
            static_cast<int>(prediction.mjd),
            static_cast<double>(prediction.x),
            static_cast<double>(prediction.y),
            static_cast<double>(prediction.ut1MinusUtc)
        );
    }

    ostk::core::utils::Print::Footer(anOutputStream);

    return anOutputStream;
}
*/
bool CSSISpaceWeather::isDefined() const
{
    return observationInterval_.isDefined() && (!observations_.empty()) && dailyPredictionInterval_.isDefined() &&
          (!dailyPredictions_.empty()) && monthlyPredictionInterval_.isDefined() && (!monthlyPredictions_.empty());

}

const Interval& CSSISpaceWeather::accessObservationInterval() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("CSSI Space Weather");
    }

    return observationInterval_;
}

const Interval& CSSISpaceWeather::accessDailyPredictionInterval() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("CSSI Space Weather");
    }

    return dailyPredictionInterval_;
}

const Interval& CSSISpaceWeather::accessMonthlyPredictionInterval() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("CSSI Space Weather");
    }

    return monthlyPredictionInterval_;
}

Interval CSSISpaceWeather::getObservationInterval() const
{
    return this->accessObservationInterval();
}

/*
CSSISpaceWeather::Observation CSSISpaceWeather::getObservationAt(const Instant& anInstant) const
{
    using ostk::physics::time::Scale;

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
        if (instantMjd.isInteger())
        {
            return observationIt->second;
        }
        else
        {
            const auto nextObservationIt = std::next(observationIt);

            if (nextObservationIt != observations_.end())
            {
                // [TBI] IERS gazette #13 for more precise interpolation and correction for tidal effects

                const CSSISpaceWeather::Observation& previousObservation = observationIt->second;
                const CSSISpaceWeather::Observation& nextObservation = nextObservationIt->second;

                const Real ratio =
                    (instantMjd - previousObservation.mjd) / (nextObservation.mjd - previousObservation.mjd);

                const Integer year = previousObservation.year;
                const Integer month = previousObservation.month;
                const Integer day = previousObservation.day;

                const Real mjd = previousObservation.mjd + ratio * (nextObservation.mjd - previousObservation.mjd);

                const Real x = previousObservation.x + ratio * (nextObservation.x - previousObservation.x);
                const Real xError =
                    previousObservation.xError + ratio * (nextObservation.xError - previousObservation.xError);
                const Real y = previousObservation.y + ratio * (nextObservation.y - previousObservation.y);
                const Real yError =
                    previousObservation.yError + ratio * (nextObservation.yError - previousObservation.yError);
                const Real ut1MinusUtc = previousObservation.ut1MinusUtc +
                                         ratio * (nextObservation.ut1MinusUtc - previousObservation.ut1MinusUtc);
                const Real ut1MinusUtcError =
                    previousObservation.ut1MinusUtcError +
                    ratio * (nextObservation.ut1MinusUtcError - previousObservation.ut1MinusUtcError);

                const CSSISpaceWeather::Observation observation = {
                    year, month, day, mjd, x, xError, y, yError, ut1MinusUtc, ut1MinusUtcError};

                return observation;
            }
            else
            {
                throw ostk::core::error::RuntimeError(
                    "Cannot find observation at [{}].", anInstant.toString(Scale::UTC)
                );
            }
        }
    }
    else
    {
        throw ostk::core::error::RuntimeError("Cannot find observation at [{}].", anInstant.toString(Scale::UTC));
    }
}
*/

Interval CSSISpaceWeather::getDailyPredictionInterval() const
{
    return this->accessDailyPredictionInterval();
}
/*
CSSISpaceWeather::Prediction CSSISpaceWeather::getDailyPredictionAt(const Instant& anInstant) const
{
    using ostk::core::types::Real;

    using ostk::physics::time::Scale;

    if (!anInstant.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("spaceWeather A");
    }

    if (!predictionInterval_.contains(anInstant))
    {
        throw ostk::core::error::RuntimeError(
            "Instant [{}] out of prediction range [{} - {}].",
            anInstant.toString(Scale::UTC),
            predictionInterval_.accessStart().toString(Scale::UTC),
            predictionInterval_.accessEnd().toString(Scale::UTC)
        );
    }

    const Real instantMjd = anInstant.getModifiedJulianDate(Scale::UTC);

    const auto predictionIt = predictions_.find(instantMjd.floor());

    if (predictionIt != predictions_.end())
    {
        if (instantMjd.isInteger())
        {
            return predictionIt->second;
        }
        else
        {
            const auto nextPredictionIt = std::next(predictionIt);

            if (nextPredictionIt != predictions_.end())
            {
                // [TBI] IERS gazette #13 for more precise interpolation and correction for tidal effects

                const CSSISpaceWeather::Prediction& previousPrediction = predictionIt->second;
                const CSSISpaceWeather::Prediction& nextPrediction = nextPredictionIt->second;

                const Real ratio =
                    (instantMjd - previousPrediction.mjd) / (nextPrediction.mjd - previousPrediction.mjd);

                const Integer year = previousPrediction.year;
                const Integer month = previousPrediction.month;
                const Integer day = previousPrediction.day;

                const Real mjd = previousPrediction.mjd + ratio * (nextPrediction.mjd - previousPrediction.mjd);

                const Real x = previousPrediction.x + ratio * (nextPrediction.x - previousPrediction.x);
                const Real y = previousPrediction.y + ratio * (nextPrediction.y - previousPrediction.y);
                const Real ut1MinusUtc = previousPrediction.ut1MinusUtc +
                                         ratio * (nextPrediction.ut1MinusUtc - previousPrediction.ut1MinusUtc);

                const CSSISpaceWeather::Prediction prediction = {year, month, day, mjd, x, y, ut1MinusUtc};

                return prediction;
            }
            else
            {
                throw ostk::core::error::RuntimeError(
                    "Cannot find prediction at [{}].", anInstant.toString(Scale::UTC)
                );
            }
        }
    }
    else
    {
        throw ostk::core::error::RuntimeError("Cannot find prediction at [{}].", anInstant.toString(Scale::UTC));
    }
}
*/

Interval CSSISpaceWeather::getMonthlyPredictionInterval() const
{
    return this->accessMonthlyPredictionInterval();
}
/*
CSSISpaceWeather::Prediction CSSISpaceWeather::getMonthlyPredictionAt(const Instant& anInstant) const
{
    using ostk::core::types::Real;

    using ostk::physics::time::Scale;

    if (!anInstant.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("spaceWeather A");
    }

    if (!predictionInterval_.contains(anInstant))
    {
        throw ostk::core::error::RuntimeError(
            "Instant [{}] out of prediction range [{} - {}].",
            anInstant.toString(Scale::UTC),
            predictionInterval_.accessStart().toString(Scale::UTC),
            predictionInterval_.accessEnd().toString(Scale::UTC)
        );
    }

    const Real instantMjd = anInstant.getModifiedJulianDate(Scale::UTC);

    const auto predictionIt = predictions_.find(instantMjd.floor());

    if (predictionIt != predictions_.end())
    {
        if (instantMjd.isInteger())
        {
            return predictionIt->second;
        }
        else
        {
            const auto nextPredictionIt = std::next(predictionIt);

            if (nextPredictionIt != predictions_.end())
            {
                // [TBI] IERS gazette #13 for more precise interpolation and correction for tidal effects

                const CSSISpaceWeather::Prediction& previousPrediction = predictionIt->second;
                const CSSISpaceWeather::Prediction& nextPrediction = nextPredictionIt->second;

                const Real ratio =
                    (instantMjd - previousPrediction.mjd) / (nextPrediction.mjd - previousPrediction.mjd);

                const Integer year = previousPrediction.year;
                const Integer month = previousPrediction.month;
                const Integer day = previousPrediction.day;

                const Real mjd = previousPrediction.mjd + ratio * (nextPrediction.mjd - previousPrediction.mjd);

                const Real x = previousPrediction.x + ratio * (nextPrediction.x - previousPrediction.x);
                const Real y = previousPrediction.y + ratio * (nextPrediction.y - previousPrediction.y);
                const Real ut1MinusUtc = previousPrediction.ut1MinusUtc +
                                         ratio * (nextPrediction.ut1MinusUtc - previousPrediction.ut1MinusUtc);

                const CSSISpaceWeather::Prediction prediction = {year, month, day, mjd, x, y, ut1MinusUtc};

                return prediction;
            }
            else
            {
                throw ostk::core::error::RuntimeError(
                    "Cannot find prediction at [{}].", anInstant.toString(Scale::UTC)
                );
            }
        }
    }
    else
    {
        throw ostk::core::error::RuntimeError("Cannot find prediction at [{}].", anInstant.toString(Scale::UTC));
    }
}
*/


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
        if (F107_DATA_TYPE == "OBS" || F107_DATA_TYPE == "PRD")
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

            
            if (F107_DATA_TYPE == "OBS")
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

        if (F107_DATA_TYPE == "INT"){
            throw ostk::core::error::RuntimeError("Parse interpolated data");
        }
    }

    if ( !spaceWeather.observations_.empty() )
    {
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
    : observationInterval_(Interval::Undefined()),
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
