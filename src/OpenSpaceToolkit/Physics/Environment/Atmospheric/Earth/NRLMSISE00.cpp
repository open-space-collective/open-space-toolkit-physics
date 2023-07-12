/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Containers/Array.hpp>
#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Types/Integer.hpp>
#include <OpenSpaceToolkit/Core/Types/Real.hpp>
#include <OpenSpaceToolkit/Core/Types/Size.hpp>
#include <OpenSpaceToolkit/Core/Types/Unique.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/Manager.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/NRLMSISE00.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Objects/CelestialBodies/Earth.hpp>
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

using ostk::core::types::Integer;
using ostk::core::types::Real;
using ostk::core::types::Size;
using ostk::core::types::Unique;
using ostk::core::ctnr::Array;

using ostk::physics::coord::Frame;
using ostk::physics::time::Scale;
using ostk::physics::time::Instant;
using ostk::physics::time::DateTime;
using ostk::physics::time::Date;
using ostk::physics::time::Time;

using EarthCelestialBody = ostk::physics::env::obj::celest::Earth;
using EarthGravitationalModel = ostk::physics::environment::gravitational::Earth;
using ostk::physics::environment::atmospheric::earth::Manager;

NRLMSISE00::NRLMSISE00()
    : Model()
{
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

    const Manager& spaceWeatherManager = Manager::Get();

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
    Array<Integer> apMultiDayArray = Array<Integer>::Empty();
    apMultiDayArray.reserve(fetchDays.getSize());

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

    Unique<NRLMSISE00::ap_array> outputStruct = std::make_unique<NRLMSISE00::ap_array>();

    outputStruct->a[0] = spaceWeatherManager.getApDailyIndexAt(anInstant);
    outputStruct->a[1] = apMultiDayArray[startIndex + 19];  // now
    outputStruct->a[2] = apMultiDayArray[startIndex + 18];  // now - 3 hours
    outputStruct->a[3] = apMultiDayArray[startIndex + 17];  // now - 6 hours
    outputStruct->a[4] = apMultiDayArray[startIndex + 16];  // now - 9 hours
    outputStruct->a[5] = apAvg12HrTo36Hr;
    outputStruct->a[6] = apAvg36HrTo57Hr;

    return outputStruct;
}

Unique<NRLMSISE00::nrlmsise_input> NRLMSISE00::computeNRLMSISE00Input(
    const Unique<NRLMSISE00::ap_array>& apValues,
    const LLA& aLLA,
    const Instant& anInstant,
    const Position& aSunPosition
) const
{
    // Input reference is in the NRLMSISE header file
    // https://github.com/magnific0/nrlmsise-00/blob/master/nrlmsise-00.h

    const Manager& spaceWeatherManager = Manager::Get();

    const DateTime currentDateTime = anInstant.getDateTime(Scale::UTC);

    // current year/doy/sec
    const Integer year = currentDateTime.getDate().getYear();

    const Instant startOfYear = Instant::DateTime(DateTime(Date(year, 1, 1), Time::Midnight()), Scale::UTC);
    const Integer dayOfYear = (anInstant - startOfYear).getDays();

    const Time timeOfDay = currentDateTime.getTime();
    const Integer secondsInDay = timeOfDay.getHour() * 3600 + timeOfDay.getMinute() * 60 + timeOfDay.getSecond();

    // Solar flux values
    const Real f107Previous = spaceWeatherManager.getF107SolarFluxAt(anInstant - Duration::Days(1));
    const Real f107Average = spaceWeatherManager.getF107SolarFlux81DayAvgAt(anInstant);

    Real lst = Real::Undefined();

    // Use actual sun position to compute local solar time if provided
    if (aSunPosition.isDefined())
    {
        const Position positionITRF = {
            aLLA.toCartesian(
                EarthGravitationalModel::WGS84.equatorialRadius_, EarthGravitationalModel::WGS84.flattening_
            ),
            Position::Unit::Meter,
            Frame::ITRF()};

        const Position sunPositionITRF = aSunPosition.inFrame(Frame::ITRF(), anInstant);

        lst = (Real::Pi() + std::atan2(
                                sunPositionITRF.accessCoordinates()[0] * positionITRF.accessCoordinates()[1] -
                                    sunPositionITRF.accessCoordinates()[1] * positionITRF.accessCoordinates()[0],
                                sunPositionITRF.accessCoordinates()[0] * positionITRF.accessCoordinates()[0] +
                                    sunPositionITRF.accessCoordinates()[1] * positionITRF.accessCoordinates()[1]
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
    input->ap = apValues->a[0];
    input->ap_a = apValues.get();

    return input;
}

Real NRLMSISE00::getDensityAt(const LLA& aLLA, const Instant& anInstant, const Position& aSunPosition) const
{
    // Included from https://github.com/magnific0/nrlmsise-00/blob/master/nrlmsise-00.h
    NRLMSISE00_c::nrlmsise_output output;
    NRLMSISE00_c::nrlmsise_flags flags;

    // Set model behavior flags. Their meaning is defined in the NRLMSISE-00 header file.
    for (int i = 0; i < 24; i++)
    {
        flags.switches[i] = 1;
    }

    const Unique<NRLMSISE00::ap_array> apValues = this->computeApArray(anInstant);
    const Unique<NRLMSISE00::nrlmsise_input> input =
        this->computeNRLMSISE00Input(apValues, aLLA, anInstant, aSunPosition);

    NRLMSISE00_c::nrlmsise_input* input_c = reinterpret_cast<NRLMSISE00_c::nrlmsise_input*>(input.get());
    NRLMSISE00_c::gtd7d(input_c, &flags, &output);

    return output.d[5];
}

Real NRLMSISE00::getDensityAt(const Position& aPosition, const Instant& anInstant, const Position& aSunPosition) const
{
    return this->getDensityAt(
        LLA::Cartesian(
            aPosition.inFrame(Frame::ITRF(), anInstant).accessCoordinates(),
            // [TBI] inherit this from correct gravitational model, if present
            EarthGravitationalModel::EGM2008.equatorialRadius_,
            EarthGravitationalModel::EGM2008.flattening_
        ),
        anInstant,
        aSunPosition
    );
}

Real NRLMSISE00::getDensityAt(const Position& aPosition, const Instant& anInstant) const
{
    return this->getDensityAt(
        LLA::Cartesian(
            aPosition.inFrame(Frame::ITRF(), anInstant).accessCoordinates(),
            // [TBI] inherit this from correct gravitational model, if present
            EarthGravitationalModel::EGM2008.equatorialRadius_,
            EarthGravitationalModel::EGM2008.flattening_
        ),
        anInstant
    );
}

}  // namespace earth
}  // namespace atmospheric
}  // namespace environment
}  // namespace physics
}  // namespace ostk
