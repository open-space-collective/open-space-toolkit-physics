/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Type/Integer.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>
#include <OpenSpaceToolkit/Core/Type/Size.hpp>
#include <OpenSpaceToolkit/Core/Type/Unique.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/Manager.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/NRLMSISE00.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Object/Celestial/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Time/Scale.hpp>

namespace NRLMSISE00_c
{
extern "C"
{
#include <NRLMSISE-00/nrlmsise-00.h>
}
}  // namespace NRLMSISE00_c

#include <cmath>

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

using ostk::core::container::Array;
using ostk::core::type::Integer;
using ostk::core::type::Real;
using ostk::core::type::Size;
using ostk::core::type::Unique;

using ostk::physics::coordinate::Frame;
using ostk::physics::time::Date;
using ostk::physics::time::DateTime;
using ostk::physics::time::Instant;
using ostk::physics::time::Scale;
using ostk::physics::time::Time;

using EarthCelestial = ostk::physics::environment::object::celestial::Earth;
using EarthGravitationalModel = ostk::physics::environment::gravitational::Earth;
using ostk::physics::environment::atmospheric::earth::Manager;

NRLMSISE00::NRLMSISE00(
    const InputDataType& anInputDataType,
    const Real& aF107ConstantValue,
    const Real& aF107AConstantValue,
    const Real& aKpConstantValue,
    const Shared<const Frame>& anEarthFrameSPtr,
    const Length& anEarthRadius,
    const Real& anEarthFlattening,
    const Shared<Celestial>& aSunCelestialSPtr
)
    : inputDataType_(anInputDataType),
      f107ConstantValue_(aF107ConstantValue),
      f107AConstantValue_(aF107AConstantValue),
      kpConstantValue_(aKpConstantValue),
      earthFrameSPtr_(anEarthFrameSPtr),
      earthRadius_(anEarthRadius),
      earthFlattening_(anEarthFlattening),
      sunCelestialSPtr_(aSunCelestialSPtr)
{
}

NRLMSISE00::NRLMSISE00(const NRLMSISE00& aNRLMSISE00Model)
    : inputDataType_(aNRLMSISE00Model.inputDataType_),
      f107ConstantValue_(aNRLMSISE00Model.f107ConstantValue_),
      f107AConstantValue_(aNRLMSISE00Model.f107AConstantValue_),
      kpConstantValue_(aNRLMSISE00Model.kpConstantValue_),
      earthFrameSPtr_(aNRLMSISE00Model.earthFrameSPtr_),
      earthRadius_(aNRLMSISE00Model.earthRadius_),
      earthFlattening_(aNRLMSISE00Model.earthFlattening_),
      sunCelestialSPtr_(aNRLMSISE00Model.sunCelestialSPtr_),
      spaceWeatherMemo_(SpaceWeatherMemo())
{
    // The memo is deliberately left empty rather than copied: it is a per-instance cache, and
    // copying it would mean reading the source's memo under this instance's mutex.
}

NRLMSISE00& NRLMSISE00::operator=(const NRLMSISE00& aNRLMSISE00Model)
{
    if (this != &aNRLMSISE00Model)
    {
        inputDataType_ = aNRLMSISE00Model.inputDataType_;
        f107ConstantValue_ = aNRLMSISE00Model.f107ConstantValue_;
        f107AConstantValue_ = aNRLMSISE00Model.f107AConstantValue_;
        kpConstantValue_ = aNRLMSISE00Model.kpConstantValue_;
        earthFrameSPtr_ = aNRLMSISE00Model.earthFrameSPtr_;
        earthRadius_ = aNRLMSISE00Model.earthRadius_;
        earthFlattening_ = aNRLMSISE00Model.earthFlattening_;
        sunCelestialSPtr_ = aNRLMSISE00Model.sunCelestialSPtr_;

        const std::lock_guard<std::mutex> lock {spaceWeatherMemoMutex_};

        spaceWeatherMemo_ = SpaceWeatherMemo();
    }

    return *this;
}

NRLMSISE00* NRLMSISE00::clone() const
{
    return new NRLMSISE00(*this);
}

bool NRLMSISE00::isDefined() const
{
    return true;
}

Unique<NRLMSISE00::ap_array> NRLMSISE00::computeApArray(const Instant& anInstant) const
{
    Unique<NRLMSISE00::ap_array> outputStruct = std::make_unique<NRLMSISE00::ap_array>();

    switch (this->inputDataType_)
    {
        case InputDataType::ConstantFluxAndGeoMag:
        {
            // Use constant values for F10.7, F10.7a and Kp NRLMSISE00 input parameters

            const Real constantApValue = this->convertKpToAp(this->kpConstantValue_);

            std::fill(std::begin(outputStruct->a), std::end(outputStruct->a), constantApValue);

            break;
        }

        case InputDataType::CSSISpaceWeatherFile:
        {
            // Use historical and predicted values for F10.7, F10.7a and Kp NRLMSISE00 input parameters
            //
            // Algorithm:
            //
            // Ap readings are given on a daily basis.
            // We first create a timestamp in each day for which we will need data.
            // Sometimes "now" and "now-9hr" land on the same day.
            //
            //  now-57hr                 now
            //     v                      v
            //     *        *        *    *
            //     |--------|--------|----|
            //        24hr     24hr   9hr
            //
            // Then, we fetch the Ap data for each of those days
            // For each day, we get 8 3-hourly readings, starting at 00:00 UTC.
            // They usually do not line up with the 24-hour periods.
            //
            //     *        *        *    *
            //     |--------|--------|----|
            //|........|........|........|........|
            //   day1     day2     day3     day4
            //
            // We stack the data into a single array then find which data point
            // on day 1 lines up with the "now-57hr" timestamp
            //
            //     *        *        *    *
            //     |--------|--------|----|
            //|........|........|........|........|
            //     ^
            //  this one
            //
            // Then use that as a starting index to find the correct data points and averages.

            // Every input above is a step function of time that only changes on a 3-hour UTC
            // boundary: the fetched days, the start index derived from the time of day of the
            // 57-hour look-back, and the daily Ap. Serve the memo while the Instant stays inside
            // the 3-hour range the memo was resolved for.

            const Manager& spaceWeatherManager = Manager::Get();

            const Index dataVersion = spaceWeatherManager.getDataVersion();

            {
                const std::lock_guard<std::mutex> lock {spaceWeatherMemoMutex_};

                if (spaceWeatherMemo_.apIsValid && (spaceWeatherMemo_.apDataVersion == dataVersion) &&
                    (!(anInstant < spaceWeatherMemo_.apRangeStart)) && (anInstant < spaceWeatherMemo_.apRangeEnd))
                {
                    *outputStruct = spaceWeatherMemo_.apValues;

                    return outputStruct;
                }
            }

            // Fetch AP parameters for each day up to 57 hours ago
            const Instant instant57HrPrevious = anInstant - Duration::Hours(57);
            const Instant instant33HrPrevious = anInstant - Duration::Hours(33);
            const Instant instant9HrPrevious = anInstant - Duration::Hours(9);

            // Fetch daily AP array for each day and stack end-to-end
            Array<Instant> fetchDays = {instant57HrPrevious, instant33HrPrevious, instant9HrPrevious};

            // add today if not already covered by instant9HrPrevious
            if (instant9HrPrevious.getDateTime(Scale::UTC).getDate().getDay() !=
                anInstant.getDateTime(Scale::UTC).getDate().getDay())
            {
                fetchDays.add(anInstant);
            }

            // Fetch AP indices for all days. Stack them into one continuous array.
            // Each day contributes eight 3-hourly indices.
            Array<Integer> apMultiDayArray = Array<Integer>::Empty();
            apMultiDayArray.reserve(fetchDays.getSize() * 8);

            for (const Instant& fetchDay : fetchDays)
            {
                apMultiDayArray.add(spaceWeatherManager.getAp3HourSolarIndicesAt(fetchDay));
            }

            // Find correct index to start at based on time of day of the first day
            // [00:00 - 03:00) == 0, [03:00 - 06:00) == 1, etc.
            const Time startTime = instant57HrPrevious.getDateTime(Scale::UTC).getTime();
            const Size startIndex = (startTime.getHour() / 3);

            const Array<Integer>::ConstIterator startIterator = apMultiDayArray.begin() + startIndex;

            // Average of 8 AP values from 57 hours ago to 36 hours ago
            const Real apAvg36HrTo57Hr =
                Real(Array<Integer>(startIterator, startIterator + 8).reduce(std::plus<Integer>())) / 8.0;

            // Average of 8 AP values from 36 hours ago to 12 hours ago
            const Real apAvg12HrTo36Hr =
                Real(Array<Integer>(startIterator + 8, startIterator + 16).reduce(std::plus<Integer>())) / 8.0;

            outputStruct->a[0] = spaceWeatherManager.getApDailyIndexAt(anInstant);
            outputStruct->a[1] = apMultiDayArray[startIndex + 19];  // now
            outputStruct->a[2] = apMultiDayArray[startIndex + 18];  // now - 3 hours
            outputStruct->a[3] = apMultiDayArray[startIndex + 17];  // now - 6 hours
            outputStruct->a[4] = apMultiDayArray[startIndex + 16];  // now - 9 hours
            outputStruct->a[5] = apAvg12HrTo36Hr;
            outputStruct->a[6] = apAvg36HrTo57Hr;

            // Record the 3-hour range this result holds for. The version read before the manager
            // was queried is the one stored: if a new file was loaded while we were reading, the
            // manager is now ahead of it and the memo is discarded on the next call.

            {
                const double threeHourIndex =
                    std::floor(static_cast<double>(anInstant.getModifiedJulianDate(Scale::UTC)) * 8.0);

                const std::lock_guard<std::mutex> lock {spaceWeatherMemoMutex_};

                spaceWeatherMemo_.apRangeStart = Instant::ModifiedJulianDate(Real(threeHourIndex / 8.0), Scale::UTC);
                spaceWeatherMemo_.apRangeEnd = spaceWeatherMemo_.apRangeStart + Duration::Hours(3);
                spaceWeatherMemo_.apValues = *outputStruct;
                spaceWeatherMemo_.apDataVersion = dataVersion;
                spaceWeatherMemo_.apIsValid = true;
            }

            break;
        }
    }

    return outputStruct;
}

Unique<NRLMSISE00::nrlmsise_input> NRLMSISE00::computeNRLMSISE00Input(
    const Unique<NRLMSISE00::ap_array>& apValues, const LLA& aLLA, const Instant& anInstant
) const
{
    Real f107Previous = Real::Undefined();
    Real f107Average = Real::Undefined();

    switch (this->inputDataType_)
    {
        case InputDataType::ConstantFluxAndGeoMag:
        {
            // Use constant values for F10.7, F10.7a and Kp NRLMSISE00 input parameters

            f107Previous = this->f107ConstantValue_;
            f107Average = this->f107AConstantValue_;

            break;
        }

        case InputDataType::CSSISpaceWeatherFile:
        {
            // Use historical and predicted values for F10.7, F10.7a and Kp NRLMSISE00 input parameters

            // Input reference is in the NRLMSISE header file
            // https://github.com/magnific0/nrlmsise-00/blob/master/nrlmsise-00.h

            // Both values resolve to a per-day reading, so both are step functions of the UTC day.
            // Serve the memo while the Instant stays inside the day it was resolved for.

            const Manager& spaceWeatherManager = Manager::Get();

            const Index dataVersion = spaceWeatherManager.getDataVersion();

            {
                const std::lock_guard<std::mutex> lock {spaceWeatherMemoMutex_};

                if (spaceWeatherMemo_.f107IsValid && (spaceWeatherMemo_.f107DataVersion == dataVersion) &&
                    (!(anInstant < spaceWeatherMemo_.f107RangeStart)) && (anInstant < spaceWeatherMemo_.f107RangeEnd))
                {
                    f107Previous = spaceWeatherMemo_.f107Previous;
                    f107Average = spaceWeatherMemo_.f107Average;

                    break;
                }
            }

            // Solar flux values
            f107Previous = spaceWeatherManager.getF107SolarFluxAt(anInstant - Duration::Days(1));
            f107Average = spaceWeatherManager.getF107SolarFlux81DayAvgAt(anInstant);

            {
                const Instant dayStart = Instant::ModifiedJulianDate(
                    Real(std::floor(static_cast<double>(anInstant.getModifiedJulianDate(Scale::UTC)))), Scale::UTC
                );

                const std::lock_guard<std::mutex> lock {spaceWeatherMemoMutex_};

                spaceWeatherMemo_.f107RangeStart = dayStart;
                spaceWeatherMemo_.f107RangeEnd = dayStart + Duration::Days(1);
                spaceWeatherMemo_.f107Previous = f107Previous;
                spaceWeatherMemo_.f107Average = f107Average;
                spaceWeatherMemo_.f107DataVersion = dataVersion;
                spaceWeatherMemo_.f107IsValid = true;
            }

            break;
        }
    }

    const DateTime currentDateTime = anInstant.getDateTime(Scale::UTC);

    // current year/doy/sec
    const Integer year = currentDateTime.getDate().getYear();

    const Instant startOfYear = Instant::DateTime(DateTime(Date(year, 1, 1), Time::Midnight()), Scale::UTC);
    const Integer dayOfYear = (anInstant - startOfYear).getDays() + 1;

    const Time timeOfDay = currentDateTime.getTime();
    const Integer secondsInDay = timeOfDay.getHour() * 3600 + timeOfDay.getMinute() * 60 + timeOfDay.getSecond();

    Real lst = Real::Undefined();

    // Use actual sun position to compute local solar time if provided
    if (sunCelestialSPtr_)
    {
        const Position position = {
            aLLA.toCartesian(earthRadius_, earthFlattening_), Position::Unit::Meter, earthFrameSPtr_
        };

        const Position sunPositionInFrame = sunCelestialSPtr_->getPositionIn(earthFrameSPtr_, anInstant);

        lst = (Real::Pi() + std::atan2(
                                sunPositionInFrame.accessCoordinates()[0] * position.accessCoordinates()[1] -
                                    sunPositionInFrame.accessCoordinates()[1] * position.accessCoordinates()[0],
                                sunPositionInFrame.accessCoordinates()[0] * position.accessCoordinates()[0] +
                                    sunPositionInFrame.accessCoordinates()[1] * position.accessCoordinates()[1]
                            )) *
              12.0 / Real::Pi();
    }
    else
    {
        // This is the preferred method per the NRLMSISE documentation
        // https://github.com/magnific0/nrlmsise-00/blob/master/nrlmsise-00.h#L103
        lst = Real::Integer(secondsInDay) / 3600.0 + aLLA.getLongitude().inDegrees() / 15.0;
    }

    Unique<NRLMSISE00::nrlmsise_input> input = std::make_unique<NRLMSISE00::nrlmsise_input>();

    input->doy = dayOfYear;
    input->year = year;
    input->sec = secondsInDay;
    input->alt = aLLA.getAltitude().inKilometers();
    input->g_lat = aLLA.getLatitude().inDegrees();
    input->g_long = aLLA.getLongitude().inDegrees();
    input->lst = lst;
    input->f107A = f107Average;
    input->f107 = f107Previous;

    if (apValues != nullptr)
    {
        input->ap = apValues->a[0];
        input->ap_a = apValues.get();
    }
    else
    {
        const Real ap = this->convertKpToAp(this->kpConstantValue_);

        input->ap = ap;
        input->ap_a = nullptr;
    }

    return input;
}

Real NRLMSISE00::convertKpToAp(const Real& aKp)
{
    if (!aKp.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Kp");
    }

    return exp((aKp + 1.6) / 1.75);  // Exponential approximation, Vallado, 2nd edition (eq 8-31).
}

NRLMSISE00::InputDataType NRLMSISE00::getInputDataType() const
{
    return this->inputDataType_;
}

Real NRLMSISE00::getF107ConstantValue() const
{
    return this->f107ConstantValue_;
}

Real NRLMSISE00::getF107AConstantValue() const
{
    return this->f107AConstantValue_;
}

Real NRLMSISE00::getKpConstantValue() const
{
    return this->kpConstantValue_;
}

Real NRLMSISE00::getDensityAt(const LLA& aLLA, const Instant& anInstant) const
{
    Unique<NRLMSISE00::ap_array> apValues = nullptr;

    if (this->inputDataType_ == InputDataType::CSSISpaceWeatherFile)
    {
        apValues = this->computeApArray(anInstant);
    }

    const Unique<NRLMSISE00::nrlmsise_input> input = this->computeNRLMSISE00Input(apValues, aLLA, anInstant);

    return NRLMSISE00::GetDensityAt(*input);
}

Real NRLMSISE00::GetDensityAt(NRLMSISE00::nrlmsise_input& input)
{
    // Included from https://github.com/magnific0/nrlmsise-00/blob/master/nrlmsise-00.h
    NRLMSISE00_c::nrlmsise_output output;
    NRLMSISE00_c::nrlmsise_flags flags;

    // Set model behavior flags. Their meaning is defined in the NRLMSISE-00 header file.
    for (int i = 0; i < 24; i++)
    {
        flags.switches[i] = 1;
    }

    NRLMSISE00_c::nrlmsise_input* input_c = reinterpret_cast<NRLMSISE00_c::nrlmsise_input*>(&input);
    NRLMSISE00_c::gtd7d(input_c, &flags, &output);

    return output.d[5];
}

}  // namespace earth
}  // namespace atmospheric
}  // namespace environment
}  // namespace physics
}  // namespace ostk
