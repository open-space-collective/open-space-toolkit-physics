/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Containers/Array.hpp>
#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Types/Integer.hpp>
#include <OpenSpaceToolkit/Core/Types/Real.hpp>
#include <OpenSpaceToolkit/Core/Types/Size.hpp>
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

void NRLMSISE00::computeAPArray(double* outputArray, const Instant& anInstant) const
{
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
    const Real apAvg3657 = Real(Array<Integer>(startIterator, startIterator + 8).reduce(std::plus<Integer>())) / 8.0;

    // Average of 8 AP values from 36 hours ago to 12 hours ago
    const Real apAvg1236 =
        Real(Array<Integer>(startIterator + 8, startIterator + 16).reduce(std::plus<Integer>())) / 8.0;

    outputArray[0] = spaceWeatherManager.getApDailyIndexAt(anInstant);
    outputArray[1] = apMultiDayArray[startIndex + 19];  // now
    outputArray[2] = apMultiDayArray[startIndex + 18];  // now - 3 hours
    outputArray[3] = apMultiDayArray[startIndex + 17];  // now - 6 hours
    outputArray[4] = apMultiDayArray[startIndex + 16];  // now - 9 hours
    outputArray[5] = apAvg1236;
    outputArray[6] = apAvg3657;
}

void NRLMSISE00::computeNRLMSISE00Input(
    nrlmsise_input& input, ap_array& aph, const LLA& aLLA, const Instant& anInstant, const Position& sunPosition
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

    // Ap solar indices array
    this->computeAPArray(aph.a, anInstant);

    const Position positionITRF = {
        aLLA.toCartesian(EarthGravitationalModel::WGS84.equatorialRadius_, EarthGravitationalModel::WGS84.flattening_),
        Position::Unit::Meter,
        Frame::ITRF()};

    Real lst = Real::Undefined();

    // Use actual sun position to compute local solar time if provided
    if (sunPosition.isDefined())
    {
        const Position sunPositionITRF = sunPosition.inFrame(Frame::ITRF(), anInstant);

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
        // https://github.com/magnific0/nrlmsise-00/blob/master/nrlmsise-00.h#L103
        lst = Real::Integer(secondsInDay) / 3600.0 + aLLA.getLongitude().inDegrees() / 15.0;
    }

    input.doy = dayOfYear;
    input.year = year;
    input.sec = secondsInDay;
    input.alt = aLLA.getAltitude().inKilometers();
    input.g_lat = aLLA.getLatitude().inDegrees();
    input.g_long = aLLA.getLongitude().inDegrees();
    input.lst = lst;
    input.f107A = f107Average;
    input.f107 = f107Previous;
    input.ap = aph.a[0];
    input.ap_a = &aph;
}

Real NRLMSISE00::getDensityAt(const LLA& aLLA, const Instant& anInstant, const Position& sunPosition) const
{
    // Included from NRLMSISE-00.h
    NRLMSISE00_c::ap_array ap_values_c;
    NRLMSISE00_c::nrlmsise_input input_c;

    NRLMSISE00_c::nrlmsise_output output;
    NRLMSISE00_c::nrlmsise_flags flags;

    // Redefined from NRLMSISE00.hpp
    NRLMSISE00::nrlmsise_input input;
    NRLMSISE00::ap_array ap_values;

    // Set model behavior flags. Their meaning is defined in the NRLMSISE-00 header file.
    // https://github.com/magnific0/nrlmsise-00/blob/master/nrlmsise-00.h
    for (int i = 0; i < 24; i++)
    {
        flags.switches[i] = 1;
    }

    this->computeNRLMSISE00Input(input, ap_values, aLLA, anInstant, sunPosition);

    std::copy(std::begin(ap_values.a), std::end(ap_values.a), std::begin(ap_values_c.a));

    input_c.doy = input.doy;
    input_c.year = input.year;
    input_c.sec = input.sec;
    input_c.alt = input.alt;
    input_c.g_lat = input.g_lat;
    input_c.g_long = input.g_long;
    input_c.lst = input.lst;
    input_c.f107A = input.f107A;
    input_c.f107 = input.f107;
    input_c.ap = input.ap;
    input_c.ap_a = &ap_values_c;

    NRLMSISE00_c::gtd7d(&input_c, &flags, &output);

    return output.d[5];
}

Real NRLMSISE00::getDensityAt(const Position& aPosition, const Instant& anInstant, const Position& sunPosition) const
{
    return this->getDensityAt(
        LLA::Cartesian(
            aPosition.inFrame(Frame::ITRF(), anInstant).accessCoordinates(),
            // [TBI] inherit this from correct gravitational model, if present
            EarthGravitationalModel::EGM2008.equatorialRadius_,
            EarthGravitationalModel::EGM2008.flattening_
        ),
        anInstant,
        sunPosition
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
