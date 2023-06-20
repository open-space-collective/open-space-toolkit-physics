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
        << "Release date:" << (aCSSISpaceWeather.releaseDate_.isDefined() ? aCSSISpaceWeather.releaseDate_.toString() : "Undefined");
    
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
    //return releaseDate_.isDefined() && 
    //       observationInterval_.isDefined() && (!observations_.empty()) && dailyPredictionInterval_.isDefined() &&
    //       (!dailyPredictions_.empty()) && monthlyPredictionInterval_.isDefined() && (!monthlyPredictions_.empty());
    return releaseDate_.isDefined();
}

const Date& CSSISpaceWeather::accessReleaseDate() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("CSSI Space Weather");
    }

    return releaseDate_;
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

Date CSSISpaceWeather::getReleaseDate() const
{
    return this->accessReleaseDate();
}

Interval CSSISpaceWeather::getObservationInterval() const
{
    return this->accessObservationInterval();
}

Interval CSSISpaceWeather::getDailyPredictionInterval() const
{
    return this->accessDailyPredictionInterval();
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

/*
Interval CSSISpaceWeather::getPredictionInterval() const
{
    return this->accessPredictionInterval();
}

CSSISpaceWeather::Prediction CSSISpaceWeather::getPredictionAt(const Instant& anInstant) const
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

    const auto monthFromString = [](const String& aMonthString) -> Uint8
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

        throw ostk::core::error::runtime::Wrong("Month string", aMonthString);

        return 0;
    };

    CSSISpaceWeather spaceWeather;

    std::ifstream fileStream {aFile.getPath().toString()};

    bool readingObserved = false;
    bool readingDailyPredicted = false;
    //bool readingMonthlyPredicted = false;

    String line;

    auto split = [] ( std::string s, std::string delimiter ) -> Array<String>
    {
        Array<String> results;

        size_t last = 0; 
        size_t next = 0; 
        while ((next = s.find(delimiter, last)) != std::string::npos) 
        {   
            if (next-last > 0)
            {
                const String token = String(s.substr(last, next-last));
                results.add(token);
            }
            last = next + 1; 
        }

        // Trim to eliminate trailing newline
        const String lastToken = String(s.substr(last)).trim();
        results.add(lastToken);
        return results;
    };
    
    while (std::getline(fileStream, line))
    {

        Array<String> lineParts = split(line, ",");

        if (lineParts.empty())
        {
            continue;
        }
        
        if (lineParts[0] == "UPDATED") 
        {
            std::cout << "UPDATED" << std::endl;
            const Uint16 year = boost::lexical_cast<Uint16>(lineParts[1]);
            const Uint8 month = monthFromString(lineParts[2]);
            const Uint8 day = static_cast<Uint8>(boost::lexical_cast<Uint16>(lineParts[3]));

            spaceWeather.releaseDate_ = Date(year, month, day);
            continue;
        }

        if ( lineParts.getSize() >= 2 && (std::string(lineParts[0]) == "BEGIN") && (std::string(lineParts[1]) == "OBSERVED")) 
        {
            std::cout << "BEGIN OBSERVED" << std::endl;
            readingObserved = true;
            continue;
        }

        if ( lineParts.getSize() >= 2 && lineParts[0] == "END" && lineParts[1] == "OBSERVED")
        {
            readingObserved = false;
            std::cout << "END OBSERVED" << std::endl;
            // save observation interval
            const Instant observationStartInstant =
                Instant::ModifiedJulianDate(Real::Integer(spaceWeather.observations_.begin()->first), Scale::UTC);
            const Instant observationEndInstant =
                Instant::ModifiedJulianDate(Real::Integer(spaceWeather.observations_.rbegin()->first), Scale::UTC);

            spaceWeather.observationInterval_ = Interval::Closed(observationStartInstant, observationEndInstant);

            continue;
        }

        if ( readingObserved )
        {
            std::cout << "readingObserved" << std::endl;
            const Integer DATE_YEAR = boost::lexical_cast<int>(lineParts[0]);
            const Integer DATE_MONTH = boost::lexical_cast<int>(lineParts[1]);
            const Integer DATE_DAY = boost::lexical_cast<int>(lineParts[2]);
            const Integer BSRN = boost::lexical_cast<int>(lineParts[3]);
            const Integer ND = boost::lexical_cast<int>(lineParts[4]);
            const Integer KP1 = boost::lexical_cast<int>(lineParts[5]);
            const Integer KP2 = boost::lexical_cast<int>(lineParts[6]);
            const Integer KP3 = boost::lexical_cast<int>(lineParts[7]);
            const Integer KP4 = boost::lexical_cast<int>(lineParts[8]);
            const Integer KP5 = boost::lexical_cast<int>(lineParts[9]);
            const Integer KP6 = boost::lexical_cast<int>(lineParts[10]);
            const Integer KP7 = boost::lexical_cast<int>(lineParts[11]);
            const Integer KP8 = boost::lexical_cast<int>(lineParts[12]);
            const Integer KP_SUM = boost::lexical_cast<int>(lineParts[13]);
            const Integer AP1 = boost::lexical_cast<int>(lineParts[14]);
            const Integer AP2 = boost::lexical_cast<int>(lineParts[15]);
            const Integer AP3 = boost::lexical_cast<int>(lineParts[16]);
            const Integer AP4 = boost::lexical_cast<int>(lineParts[17]);
            const Integer AP5 = boost::lexical_cast<int>(lineParts[18]);
            const Integer AP6 = boost::lexical_cast<int>(lineParts[19]);
            const Integer AP7 = boost::lexical_cast<int>(lineParts[20]);
            const Integer AP8 = boost::lexical_cast<int>(lineParts[21]);
            const Integer AP_AVG = boost::lexical_cast<int>(lineParts[22]);
            const Real CP = boost::lexical_cast<double>(lineParts[23]);
            const Integer C9 = boost::lexical_cast<int>(lineParts[24]);
            const Integer ISN = boost::lexical_cast<int>(lineParts[25]);
            const Real F107_OBS = boost::lexical_cast<double>(lineParts[26]);
            const Real F107_ADJ = boost::lexical_cast<double>(lineParts[27]);
            const Real F107_DATA_TYPE = boost::lexical_cast<double>(lineParts[28]);
            const Real F107_OBS_CENTER81 = boost::lexical_cast<double>(lineParts[29]);
            const Real F107_OBS_LAST81 = boost::lexical_cast<double>(lineParts[30]);
            const Real F107_ADJ_CENTER81 = boost::lexical_cast<double>(lineParts[31]);
            const Real F107_ADJ_LAST81 = boost::lexical_cast<double>(String(lineParts[32]).trim());

            const CSSISpaceWeather::Observation observation = {
                DATE_YEAR,
                DATE_MONTH,
                DATE_DAY,
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

            const Integer mjd = DateTime(DATE_YEAR, DATE_MONTH, DATE_DAY).getModifiedJulianDate().floor();

            spaceWeather.observations_.insert({mjd, observation});
            continue;
        }

        // DAILY PREDICTED
        if ( lineParts.getSize() >= 2 && (std::string(lineParts[0]) == "BEGIN") && (std::string(lineParts[1]) == "DAILY_PREDICTED")) 
        {
            std::cout << "BEGIN DAILY_PREDICTED" << std::endl;
            readingDailyPredicted = true;
            continue;
        }

        if ( lineParts.getSize() >= 2 && lineParts[0] == "END" && lineParts[1] == "DAILY_PREDICTED")
        {
            readingDailyPredicted = false;
            std::cout << "END DAILY_PREDICTED" << std::endl;
            // save dailyPrediction interval
            const Instant dailyPredictionStartInstant =
                Instant::ModifiedJulianDate(Real::Integer(spaceWeather.dailyPredictions_.begin()->first), Scale::UTC);
            const Instant dailyPredictionEndInstant =
                Instant::ModifiedJulianDate(Real::Integer(spaceWeather.dailyPredictions_.rbegin()->first), Scale::UTC);

            spaceWeather.dailyPredictionInterval_ = Interval::Closed(dailyPredictionStartInstant, dailyPredictionEndInstant);

            continue;
        }

        if ( readingDailyPredicted )
        {
            std::cout << "readingDailyPredicted" << std::endl;
            const Integer DATE_YEAR = boost::lexical_cast<int>(lineParts[0]);
            const Integer DATE_MONTH = boost::lexical_cast<int>(lineParts[1]);
            const Integer DATE_DAY = boost::lexical_cast<int>(lineParts[2]);
            const Integer BSRN = boost::lexical_cast<int>(lineParts[3]);
            const Integer ND = boost::lexical_cast<int>(lineParts[4]);
            const Integer KP1 = boost::lexical_cast<int>(lineParts[5]);
            const Integer KP2 = boost::lexical_cast<int>(lineParts[6]);
            const Integer KP3 = boost::lexical_cast<int>(lineParts[7]);
            const Integer KP4 = boost::lexical_cast<int>(lineParts[8]);
            const Integer KP5 = boost::lexical_cast<int>(lineParts[9]);
            const Integer KP6 = boost::lexical_cast<int>(lineParts[10]);
            const Integer KP7 = boost::lexical_cast<int>(lineParts[11]);
            const Integer KP8 = boost::lexical_cast<int>(lineParts[12]);
            const Integer KP_SUM = boost::lexical_cast<int>(lineParts[13]);
            const Integer AP1 = boost::lexical_cast<int>(lineParts[14]);
            const Integer AP2 = boost::lexical_cast<int>(lineParts[15]);
            const Integer AP3 = boost::lexical_cast<int>(lineParts[16]);
            const Integer AP4 = boost::lexical_cast<int>(lineParts[17]);
            const Integer AP5 = boost::lexical_cast<int>(lineParts[18]);
            const Integer AP6 = boost::lexical_cast<int>(lineParts[19]);
            const Integer AP7 = boost::lexical_cast<int>(lineParts[20]);
            const Integer AP8 = boost::lexical_cast<int>(lineParts[21]);
            const Integer AP_AVG = boost::lexical_cast<int>(lineParts[22]);
            const Real CP = boost::lexical_cast<double>(lineParts[23]);
            const Integer C9 = boost::lexical_cast<int>(lineParts[24]);
            const Integer ISN = boost::lexical_cast<int>(lineParts[25]);
            const Real F107_OBS = boost::lexical_cast<double>(lineParts[26]);
            const Real F107_ADJ = boost::lexical_cast<double>(lineParts[27]);
            const Real F107_DATA_TYPE = boost::lexical_cast<double>(lineParts[28]);
            const Real F107_OBS_CENTER81 = boost::lexical_cast<double>(lineParts[29]);
            const Real F107_OBS_LAST81 = boost::lexical_cast<double>(lineParts[30]);
            const Real F107_ADJ_CENTER81 = boost::lexical_cast<double>(lineParts[31]);
            const Real F107_ADJ_LAST81 = boost::lexical_cast<double>(String(lineParts[32]).trim());

            const CSSISpaceWeather::Observation dailyPrediction = {
                DATE_YEAR,
                DATE_MONTH,
                DATE_DAY,
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

            const Integer mjd = DateTime(DATE_YEAR, DATE_MONTH, DATE_DAY).getModifiedJulianDate().floor();

            spaceWeather.dailyPredictions_.insert({mjd, dailyPrediction});
            continue;
        }

        /*
        if ((lineIndex < 30) && (!spaceWeather.taiMinusUtc_.isDefined()) && std::regex_match(line, match, taiMinusUtcRegex))
        {
            const Real seconds = boost::lexical_cast<double>(match[1]) + boost::lexical_cast<double>(match[2]) / 1e6;

            spaceWeather.taiMinusUtc_ = Duration::Seconds(seconds);
        }

        if (std::regex_match(line, match, observationRegex))
        {
            const Integer year = 2000 + boost::lexical_cast<int>(match[1]);
            const Integer month = boost::lexical_cast<int>(match[2]);
            const Integer day = boost::lexical_cast<int>(match[3]);

            const Integer mjd = boost::lexical_cast<int>(match[4]);

            const Real x = boost::lexical_cast<double>(match[5]);
            const Real xError = boost::lexical_cast<double>(match[6]);
            const Real y = boost::lexical_cast<double>(match[7]);
            const Real yError = boost::lexical_cast<double>(match[8]);
            const Real ut1MinusUtc = boost::lexical_cast<double>(match[9]);
            const Real ut1MinusUtcError = boost::lexical_cast<double>(match[10]);

            const CSSISpaceWeather::Observation observation = {
                year, month, day, Real::Integer(mjd), x, xError, y, yError, ut1MinusUtc, ut1MinusUtcError};

            spaceWeather.observations_.insert({mjd, observation});
        }

        if (std::regex_match(line, match, predictionRegex))
        {
            const Integer year = boost::lexical_cast<int>(match[1]);
            const Integer month = boost::lexical_cast<int>(match[2]);
            const Integer day = boost::lexical_cast<int>(match[3]);

            const Integer mjd = boost::lexical_cast<int>(match[4]);

            const Real x = boost::lexical_cast<double>(match[5]);
            const Real y = boost::lexical_cast<double>(match[6]);
            const Real ut1MinusUtc = boost::lexical_cast<double>(match[7]);

            const CSSISpaceWeather::Prediction prediction = {
                year,
                month,
                day,
                Real::Integer(mjd),
                x,
                y,
                ut1MinusUtc,
            };

            spaceWeather.predictions_.insert({mjd, prediction});
        }

        lineIndex++;
        */
    }

    /*


    if (!spaceWeather.predictions_.empty())
    {
        const Instant predictionStartInstant =
            Instant::ModifiedJulianDate(Real::Integer(spaceWeather.predictions_.begin()->first), Scale::UTC);
        const Instant predictionEndInstant =
            Instant::ModifiedJulianDate(Real::Integer(spaceWeather.predictions_.rbegin()->first), Scale::UTC);

        spaceWeather.predictionInterval_ = Interval::Closed(predictionStartInstant, predictionEndInstant);
    }
    */

    return spaceWeather;
}

CSSISpaceWeather::CSSISpaceWeather()
    : releaseDate_(Date::Undefined()),

      //numObservedData_(Integer::Undefined()),
      observationInterval_(Interval::Undefined()),
      observations_(Map<Integer, CSSISpaceWeather::Observation>()),

      //numDailyPredictionData_(Integer::Undefined()),
      dailyPredictionInterval_(Interval::Undefined()),
      dailyPredictions_(Map<Integer, CSSISpaceWeather::DailyPrediction>()),

      //numMonthlyPredictionData_(Integer::Undefined()),
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
