/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>
#include <OpenSpaceToolkit/Core/Types/Integer.hpp>
#include <OpenSpaceToolkit/Core/Types/Real.hpp>
#include <OpenSpaceToolkit/Core/Types/Size.hpp>
#include <OpenSpaceToolkit/Core/Containers/Array.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Time/Scale.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/NRLMSISE00.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/Manager.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Objects/CelestialBodies/Earth.hpp>

extern "C"{
    #include <NRLMSISE-00/nrlmsise-00.h>
}

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

Real NRLMSISE00::getDensityAt(const LLA& aLLA, const Instant& anInstant) const
{
    // Input reference in the NRLMSISE header file
    // https://github.com/magnific0/nrlmsise-00/blob/master/nrlmsise-00.h
    
    struct nrlmsise_output output;
	struct nrlmsise_input input;
  	struct nrlmsise_flags flags;
	struct ap_array aph;

    // tbi make this an object variable so you can change it in a script i guess
    //flags.switches[0]=0;
  	for (int i=0;i<24;i++){
  		flags.switches[i]=1;
    }

    const Manager& spaceWeatherManager = Manager::Get();

    // Normal non-annoying parameters
    const DateTime currentDateTime = anInstant.getDateTime(Scale::UTC);
    const Date currentDate = anInstant.getDateTime(Scale::UTC).getDate();

    const Integer year = currentDate.getYear();

    const Instant startOfYear = Instant::DateTime(DateTime(Date(year, 1, 1), Time::Midnight()), Scale::UTC);
    const Integer dayOfYear = (anInstant - startOfYear).getDays();

    const Integer secondsInDay = currentDateTime.getTime().getSecond();

    const Real f107 = spaceWeatherManager.getF107SolarFluxAt(anInstant);
    const Real f107Average = spaceWeatherManager.getF107SolarFlux81DayAvgAt(anInstant);

    // Annoying AP parameters -------------------------------------------------
    const Array<Integer> apArray = spaceWeatherManager.getAp3HourSolarIndicesAt(anInstant);

    // 58 hours to catch edge cases
    const Instant instant58HrPrevious = anInstant - Duration::Hours(58);

    // Get all days between now and 58 hours ago
    Array<Instant> fetchDays = {instant58HrPrevious};

    while (fetchDays.accessLast() < anInstant)
    {
        fetchDays.add(fetchDays.accessLast() + Duration::Days(1));
    }

    // Fetch AP array for each day
    Array<Integer> apMultiDayArray = Array<Integer>::Empty();

    for (const Instant& fetchDay : fetchDays)
    {
        const Array<Integer> apMultiDayArrayFetch = spaceWeatherManager.getAp3HourSolarIndicesAt(fetchDay);

        apMultiDayArray.add(apMultiDayArrayFetch);
    }

    // Find correct index to start at based on time of day
    const Time startTime = instant58HrPrevious.getDateTime(Scale::UTC).getTime();

    const Size startIndex = (startTime.getHour() / 3);
    const Array<Integer>::ConstIterator startIterator = apMultiDayArray.begin() + startIndex;

    // Average of 8 AP values from 57 hours ago to 36 hours ago
    Real apAvg3657 = Real(Array<Integer>(startIterator, startIterator+8).reduce(std::plus<Integer>())) / 8.0;

    // Average of 8 AP values from 36 hours ago to 12 hours ago
    Real apAvg1236 = Real(Array<Integer>(startIterator+8, startIterator+16).reduce(std::plus<Integer>())) / 8.0;

    aph.a[0] = 4;
    aph.a[1] = apMultiDayArray[startIndex+20];
    aph.a[2] = apMultiDayArray[startIndex+19];
    aph.a[3] = apMultiDayArray[startIndex+18];
    aph.a[4] = apMultiDayArray[startIndex+17];
    aph.a[5] = apAvg1236;
    aph.a[6] = apAvg3657;

    std::cout << "ap array" << aph.a << std::endl;
    std::cout << "start time: " << startTime << std::endl;
    std::cout << Array<Integer>(startIterator, startIterator+8) << std::endl;
    std::cout << Array<Integer>(startIterator, startIterator+8).reduce(std::plus<Integer>()) << std::endl;
    std::cout << "apAvg3657: " << apAvg3657 << std::endl;


    /* Array containing the following magnetic values:
    *   0 : daily AP
    *   1 : 3 hr AP index for current time
    *   2 : 3 hr AP index for 3 hrs before current time
    *   3 : 3 hr AP index for 6 hrs before current time
    *   4 : 3 hr AP index for 9 hrs before current time
    *   5 : Average of eight 3 hr AP indices from 12 to 33 hrs 
    *           prior to current time
    *   6 : Average of eight 3 hr AP indices from 36 to 57 hrs 
    *           prior to current time 
    */

    input.doy=dayOfYear;
    input.year=year;
    input.sec=secondsInDay;
    input.alt=aLLA.getAltitude().inKilometers();
    input.g_lat=aLLA.getLatitude().inDegrees();
    input.g_long=aLLA.getLongitude().inDegrees();
    input.lst=input.sec/3600 + input.g_long/15;
    input.f107A=f107Average;
    input.f107=f107;
    input.ap=4; // <- ap avg I think
    input.ap_a = &aph;

    gtd7d(&input, &flags, &output) ;
    
    
    return  output.d[5];
}

}  // namespace earth
}  // namespace atmospheric
}  // namespace environment
}  // namespace physics
}  // namespace ostk
