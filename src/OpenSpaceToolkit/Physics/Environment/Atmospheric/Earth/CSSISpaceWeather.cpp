/// Apache License 2.0

#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
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
using ostk::core::type::Real;
using ostk::core::type::Size;
using ostk::core::type::String;
using ostk::core::type::Uint16;
using ostk::core::type::Uint8;
using ostk::core::utils::Print;

using ostk::physics::time::DateTime;
using ostk::physics::time::Scale;
using ostk::physics::time::Time;

using ostk::physics::data::utilities::getFileModifiedInstant;

namespace
{

/// Number of entries in CSSISpaceWeather::Quantity.
const Size QuantityCount = 5;

/// Derive the MJD day containing an Instant.
///
/// Instant::getModifiedJulianDate splits the count into whole days and a remainder, so the
/// result is exact to double precision and flooring it recovers the day without going through
/// Real/Integer temporaries.
int DayIndexOf(const Instant& anInstant)
{
    return static_cast<int>(std::floor(static_cast<double>(anInstant.getModifiedJulianDate(Scale::UTC))));
}

bool IsQuantityDefined(const CSSISpaceWeather::Quantity& aQuantity, const CSSISpaceWeather::Reading& aReading)
{
    switch (aQuantity)
    {
        case CSSISpaceWeather::Quantity::Kp:
            return aReading.Kp1.isDefined() && aReading.Kp2.isDefined() && aReading.Kp3.isDefined() &&
                   aReading.Kp4.isDefined() && aReading.Kp5.isDefined() && aReading.Kp6.isDefined() &&
                   aReading.Kp7.isDefined() && aReading.Kp8.isDefined();

        case CSSISpaceWeather::Quantity::Ap:
            return aReading.Ap1.isDefined() && aReading.Ap2.isDefined() && aReading.Ap3.isDefined() &&
                   aReading.Ap4.isDefined() && aReading.Ap5.isDefined() && aReading.Ap6.isDefined() &&
                   aReading.Ap7.isDefined() && aReading.Ap8.isDefined();

        case CSSISpaceWeather::Quantity::ApDaily:
            return aReading.ApAvg.isDefined();

        case CSSISpaceWeather::Quantity::F107Obs:
            return aReading.F107Obs.isDefined();

        case CSSISpaceWeather::Quantity::F107ObsCenter81:
            return aReading.F107ObsCenter81.isDefined();
    }

    return false;
}

int DayCountInMonth(const int aYear, const int aMonth)
{
    static const int dayCounts[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (aMonth == 2)
    {
        const bool isLeapYear = ((aYear % 4) == 0) && (((aYear % 100) != 0) || ((aYear % 400) == 0));

        return isLeapYear ? 29 : 28;
    }

    return dayCounts[aMonth - 1];
}

}  // namespace

CSSISpaceWeather::CSSISpaceWeather(const CSSISpaceWeather& aCSSISpaceWeather)
    : lastObservationDate_(aCSSISpaceWeather.lastObservationDate_),
      lastModifiedTimestamp_(aCSSISpaceWeather.lastModifiedTimestamp_),
      observationInterval_(aCSSISpaceWeather.observationInterval_),
      observations_(aCSSISpaceWeather.observations_),
      dailyPredictionInterval_(aCSSISpaceWeather.dailyPredictionInterval_),
      dailyPredictions_(aCSSISpaceWeather.dailyPredictions_),
      monthlyPredictionInterval_(aCSSISpaceWeather.monthlyPredictionInterval_),
      monthlyPredictions_(aCSSISpaceWeather.monthlyPredictions_),
      isDefined_(false),
      indexedFirstDay_(Integer::Undefined()),
      readingIndex_(Array<const Reading*>::Empty()),
      definedIndex_(Array<Array<const Reading*>>::Empty())
{
    // The indices point into our own map nodes, so they cannot be copied over from the source.

    this->buildIndex_();
}

CSSISpaceWeather& CSSISpaceWeather::operator=(const CSSISpaceWeather& aCSSISpaceWeather)
{
    if (this != &aCSSISpaceWeather)
    {
        lastObservationDate_ = aCSSISpaceWeather.lastObservationDate_;
        lastModifiedTimestamp_ = aCSSISpaceWeather.lastModifiedTimestamp_;

        observationInterval_ = aCSSISpaceWeather.observationInterval_;
        observations_ = aCSSISpaceWeather.observations_;

        dailyPredictionInterval_ = aCSSISpaceWeather.dailyPredictionInterval_;
        dailyPredictions_ = aCSSISpaceWeather.dailyPredictions_;

        monthlyPredictionInterval_ = aCSSISpaceWeather.monthlyPredictionInterval_;
        monthlyPredictions_ = aCSSISpaceWeather.monthlyPredictions_;

        this->buildIndex_();
    }

    return *this;
}

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
    // Established when the indices are built: the readings never change afterwards, and this is
    // re-checked by every accessor.

    return isDefined_;
}

const Date& CSSISpaceWeather::accessLastObservationDate() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("CSSI Space Weather");
    }

    return lastObservationDate_;
}

const Instant& CSSISpaceWeather::accessLastModifiedTimestamp() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("CSSI Space Weather");
    }

    return lastModifiedTimestamp_;
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

    const auto observationIt = observations_.find(Integer::Int32(DayIndexOf(anInstant)));

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

    const auto predictionIt = dailyPredictions_.find(Integer::Int32(DayIndexOf(anInstant)));

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

    const Date date = anInstant.getDateTime(Scale::UTC).getDate();

    const Integer year = date.getYear();
    const Integer month = date.getMonth();

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
    if (const Reading* readingPtr = this->accessReadingPtrAt_(anInstant))
    {
        return *readingPtr;
    }

    // The day index does not cover this Instant, either because it falls outside the file or
    // because it lands on a day the file does not fully cover. Fall back to the interval
    // dispatch, which resolves the remaining cases and reports the appropriate error.

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

        // Go back in time by approximately 1 month at a time, but not past the last daily prediction.
        // The daily prediction Interval is half-open, so its end Instant is not itself a valid search
        // point: a stride landing on it exactly would exit this loop with nothing left to search.

        const Instant nextSearchInstant = searchInstant - Duration::Days(30);

        searchInstant = (nextSearchInstant > dailyPredictionInterval_.accessEnd())
                          ? nextSearchInstant
                          : dailyPredictionInterval_.accessEnd() - Duration::Days(1);
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

const CSSISpaceWeather::Reading& CSSISpaceWeather::accessLastReadingWhereDefined(
    const Quantity& aQuantity, const Instant& anInstant
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

    // The day is established once here and reused for both lookups below.

    const int dayOffset = DayIndexOf(anInstant) - static_cast<int>(indexedFirstDay_);

    const bool isIndexed = (dayOffset >= 0) && (static_cast<Size>(dayOffset) < readingIndex_.getSize());

    if ((!isIndexed) || (readingIndex_[static_cast<Size>(dayOffset)] == nullptr))
    {
        // The day index does not resolve this Instant. Defer to accessReadingAt, which either
        // resolves it through the Interval dispatch or reports why it cannot.

        static_cast<void>(this->accessReadingAt(anInstant));
    }

    if (isIndexed)
    {
        if (const Reading* readingPtr = definedIndex_[static_cast<Size>(aQuantity)][static_cast<Size>(dayOffset)])
        {
            return *readingPtr;
        }
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
    spaceWeather.lastModifiedTimestamp_ = getFileModifiedInstant(aFile);

    Table spaceWeatherTable = Table::Load(aFile, Table::Format::CSV, true);

    // Helper functions to parse optional Integer/Real cells
    const auto parseOptionalIntegerCell = [](const Object& obj) -> Integer
    {
        if (!obj.isDefined())
            return Integer::Undefined();

        if (obj.isInteger())
            return obj.getInteger();

        if (!obj.isString())
            return Integer::Undefined();

        if (obj.getString().trim().empty())
            return Integer::Undefined();

        return Integer::Parse(obj.getString().trim());
    };

    const auto parseOptionalRealCell = [](const Object& obj) -> Real
    {
        if (!obj.isDefined())
            return Real::Undefined();

        if (obj.isReal())
            return obj.getReal();

        if (obj.isInteger())
            return Real::Integer(obj.getInteger());

        if (!obj.isString())
            return Real::Undefined();

        if (obj.getString().trim().empty())
            return Real::Undefined();

        return Real::Parse(obj.getString().trim());
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

        const Integer mjd = DateTime(date, Time(0, 0, 0)).getModifiedJulianDate().floor();

        const Integer BSRN = parseOptionalIntegerCell(row[1]);
        const Integer ND = parseOptionalIntegerCell(row[2]);
        const Integer Kp1 = parseOptionalIntegerCell(row[3]);
        const Integer Kp2 = parseOptionalIntegerCell(row[4]);
        const Integer Kp3 = parseOptionalIntegerCell(row[5]);
        const Integer Kp4 = parseOptionalIntegerCell(row[6]);
        const Integer Kp5 = parseOptionalIntegerCell(row[7]);
        const Integer Kp6 = parseOptionalIntegerCell(row[8]);
        const Integer Kp7 = parseOptionalIntegerCell(row[9]);
        const Integer Kp8 = parseOptionalIntegerCell(row[10]);
        const Integer KpSum = parseOptionalIntegerCell(row[11]);
        const Integer Ap1 = parseOptionalIntegerCell(row[12]);
        const Integer Ap2 = parseOptionalIntegerCell(row[13]);
        const Integer Ap3 = parseOptionalIntegerCell(row[14]);
        const Integer Ap4 = parseOptionalIntegerCell(row[15]);
        const Integer Ap5 = parseOptionalIntegerCell(row[16]);
        const Integer Ap6 = parseOptionalIntegerCell(row[17]);
        const Integer Ap7 = parseOptionalIntegerCell(row[18]);
        const Integer Ap8 = parseOptionalIntegerCell(row[19]);
        const Integer ApAvg = parseOptionalIntegerCell(row[20]);
        const Real Cp = parseOptionalRealCell(row[21]);
        const Integer C9 = parseOptionalIntegerCell(row[22]);
        const Integer ISN = parseOptionalIntegerCell(row[23]);
        const Real F107Obs = parseOptionalRealCell(row[24]);
        const Real F107Adj = parseOptionalRealCell(row[25]);
        const String F107DataType = row[26].getString();
        const Real F107ObsCenter81 = parseOptionalRealCell(row[27]);
        const Real F107ObsLast81 = parseOptionalRealCell(row[28]);
        const Real F107AdjCenter81 = parseOptionalRealCell(row[29]);
        const Real F107AdjLast81 = parseOptionalRealCell(row[30]);

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
            Instant::ModifiedJulianDate(Real::Integer(spaceWeather.observations_.begin()->first), Scale::UTC);

        // End at the end of the day
        const Instant observationEndInstant =
            Instant::ModifiedJulianDate(Real::Integer(spaceWeather.observations_.rbegin()->first), Scale::UTC) +
            Duration::Days(1);

        spaceWeather.observationInterval_ =
            Interval(observationStartInstant, observationEndInstant, Interval::Type::HalfOpenRight);
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

    spaceWeather.buildIndex_();

    return spaceWeather;
}

CSSISpaceWeather CSSISpaceWeather::LoadLegacy(const File& aFile)
{
    using ostk::core::type::Index;
    using ostk::core::type::Real;
    using ostk::core::type::String;
    using ostk::core::type::Uint16;
    using ostk::core::type::Uint8;

    using ostk::physics::time::DateTime;
    using ostk::physics::time::Scale;
    using ostk::physics::time::Time;

    if (!aFile.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("File");
    }

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
                Instant::ModifiedJulianDate(Real::Integer(spaceWeather.observations_.begin()->first), Scale::UTC);

            // End at the end of the day
            const Instant observationEndInstant =
                Instant::ModifiedJulianDate(Real::Integer(spaceWeather.observations_.rbegin()->first), Scale::UTC) +
                Duration::Days(1);

            spaceWeather.observationInterval_ =
                Interval(observationStartInstant, observationEndInstant, Interval::Type::HalfOpenRight);

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

            const Instant monthlyPredictionEndInstant = Instant::ModifiedJulianDate(
                Real::Integer(spaceWeather.monthlyPredictions_.rbegin()->first), Scale::UTC
            );

            spaceWeather.monthlyPredictionInterval_ =
                Interval::Closed(monthlyPredictionStartInstant, monthlyPredictionEndInstant);
        }

        if (readingObserved || readingDailyPredicted || readingMonthlyPredicted)
        {
            try
            {
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
                // Real Q = boost::lexical_cast<double>(lineParts[27]); // This isn't in the CSV format, so let's ignore
                // it
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

    spaceWeather.buildIndex_();

    return spaceWeather;
}

CSSISpaceWeather::CSSISpaceWeather()
    : lastObservationDate_(Date::Undefined()),
      lastModifiedTimestamp_(Instant::Undefined()),
      observationInterval_(Interval::Undefined()),
      observations_(Map<Integer, CSSISpaceWeather::Reading>()),

      dailyPredictionInterval_(Interval::Undefined()),
      dailyPredictions_(Map<Integer, CSSISpaceWeather::Reading>()),

      monthlyPredictionInterval_(Interval::Undefined()),
      monthlyPredictions_(Map<Integer, CSSISpaceWeather::Reading>()),

      isDefined_(false),
      indexedFirstDay_(Integer::Undefined()),
      readingIndex_(Array<const Reading*>::Empty()),
      definedIndex_(Array<Array<const Reading*>>(QuantityCount, Array<const Reading*>::Empty()))
{
}

const CSSISpaceWeather::Reading* CSSISpaceWeather::accessReadingPtrAt_(const Instant& anInstant) const
{
    if (readingIndex_.isEmpty() || (!anInstant.isDefined()))
    {
        return nullptr;
    }

    const int dayOffset = DayIndexOf(anInstant) - static_cast<int>(indexedFirstDay_);

    if ((dayOffset < 0) || (static_cast<Size>(dayOffset) >= readingIndex_.getSize()))
    {
        return nullptr;
    }

    return readingIndex_[static_cast<Size>(dayOffset)];
}

void CSSISpaceWeather::buildIndex_()
{
    isDefined_ = observationInterval_.isDefined() && (!observations_.empty()) && dailyPredictionInterval_.isDefined() &&
                 (!dailyPredictions_.empty()) && monthlyPredictionInterval_.isDefined() &&
                 (!monthlyPredictions_.empty());

    indexedFirstDay_ = Integer::Undefined();
    readingIndex_ = Array<const Reading*>::Empty();
    definedIndex_ = Array<Array<const Reading*>>(QuantityCount, Array<const Reading*>::Empty());

    if (observations_.empty() && dailyPredictions_.empty() && monthlyPredictions_.empty())
    {
        return;
    }

    // The index spans every day the file touches. Each map is keyed by MJD day, so the day
    // bounds come straight off the maps without going through the Intervals.

    int firstDay = std::numeric_limits<int>::max();
    int lastDay = std::numeric_limits<int>::min();

    for (const auto* readingMapPtr : {&observations_, &dailyPredictions_, &monthlyPredictions_})
    {
        if (!readingMapPtr->empty())
        {
            firstDay = std::min(firstDay, static_cast<int>(readingMapPtr->begin()->first));
            lastDay = std::max(lastDay, static_cast<int>(readingMapPtr->rbegin()->first));
        }
    }

    const Size dayCount = static_cast<Size>(lastDay - firstDay) + 1;

    indexedFirstDay_ = Integer::Int32(firstDay);

    // Resolve the reading of each day, lowest precedence first, mirroring accessReadingAt's
    // dispatch. Monthly predictions are keyed on the first of the month and stand for the whole
    // month; daily predictions and observations are keyed on the day itself.

    Array<const Reading*> dayReadings = Array<const Reading*>(dayCount, nullptr);

    for (const auto& monthlyPredictionIt : monthlyPredictions_)
    {
        const Date& monthDate = monthlyPredictionIt.second.date;

        if (monthDate.getDay() != 1)
        {
            // accessMonthlyPredictionAt keys on the first of the month, so a reading dated
            // anywhere else is unreachable through it and must stay unreachable here too.

            continue;
        }

        const int monthFirstDay = static_cast<int>(monthlyPredictionIt.first);

        const int monthLastDay = monthFirstDay + DayCountInMonth(monthDate.getYear(), monthDate.getMonth()) - 1;

        for (int day = std::max(monthFirstDay, firstDay); day <= std::min(monthLastDay, lastDay); ++day)
        {
            dayReadings[static_cast<Size>(day - firstDay)] = &monthlyPredictionIt.second;
        }
    }

    for (const auto& dailyPredictionIt : dailyPredictions_)
    {
        dayReadings[static_cast<Size>(static_cast<int>(dailyPredictionIt.first) - firstDay)] =
            &dailyPredictionIt.second;
    }

    for (const auto& observationIt : observations_)
    {
        dayReadings[static_cast<Size>(static_cast<int>(observationIt.first) - firstDay)] = &observationIt.second;
    }

    // Walk the days forward once, carrying the last reading seen to carry each quantity, so that
    // reading a quantity the reading of the day does not carry costs a single lookup rather than
    // a backward scan.

    Array<const Reading*> lastDefinedReadings = Array<const Reading*>(QuantityCount, nullptr);

    for (Size quantityIndex = 0; quantityIndex < QuantityCount; ++quantityIndex)
    {
        definedIndex_[quantityIndex] = Array<const Reading*>(dayCount, nullptr);
    }

    for (Size dayIndex = 0; dayIndex < dayCount; ++dayIndex)
    {
        const Reading* readingPtr = dayReadings[dayIndex];

        for (Size quantityIndex = 0; quantityIndex < QuantityCount; ++quantityIndex)
        {
            if ((readingPtr != nullptr) && IsQuantityDefined(static_cast<Quantity>(quantityIndex), *readingPtr))
            {
                lastDefinedReadings[quantityIndex] = readingPtr;
            }

            definedIndex_[quantityIndex][dayIndex] = lastDefinedReadings[quantityIndex];
        }
    }

    readingIndex_ = std::move(dayReadings);

    // The monthly prediction Interval is closed on the first of its last month, so only midnight
    // of that day is covered. Drop it from the reading index — where a day either resolves whole
    // or not at all — and let the Interval dispatch handle it.

    if (!monthlyPredictions_.empty())
    {
        const Size lastMonthlyOffset =
            static_cast<Size>(static_cast<int>(monthlyPredictions_.rbegin()->first) - firstDay);

        if (readingIndex_[lastMonthlyOffset] == &monthlyPredictions_.rbegin()->second)
        {
            readingIndex_[lastMonthlyOffset] = nullptr;
        }
    }
}

}  // namespace earth
}  // namespace atmospheric
}  // namespace environment
}  // namespace physics
}  // namespace ostk
