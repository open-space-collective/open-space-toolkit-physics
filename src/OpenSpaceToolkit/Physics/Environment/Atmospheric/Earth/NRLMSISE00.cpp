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

void NRLMSISE00::computeAPArray(double* outputArray, const Instant& anInstant) const
{
    const Manager& spaceWeatherManager = Manager::Get();
    
    // Fetch AP parameters for each day up to 57 hours ago
    const Instant instant57HrPrevious = anInstant - Duration::Hours(57);
    const Instant instant33HrPrevious = anInstant - Duration::Hours(33);
    const Instant instant9HrPrevious = anInstant - Duration::Hours(9);
    //std::cout << "instant57HrPrevious: " << instant57HrPrevious.toString(Scale::UTC) << std::endl;
    // Fetch daily AP array for each day and stack end-to-end
    Array<Instant> fetchDays = {instant57HrPrevious, instant33HrPrevious, instant9HrPrevious};

    // add today if not already covered by instant9HrPrevious
    // std::cout << "fetching days" << std::endl;
    // std::cout << instant57HrPrevious.toString(Scale::UTC) << std::endl;
    // std::cout << instant33HrPrevious.toString(Scale::UTC) << std::endl;
    // std::cout << instant9HrPrevious.toString(Scale::UTC) << std::endl;

    if (instant9HrPrevious.getDateTime(Scale::UTC).getDate().getDay() != anInstant.getDateTime(Scale::UTC).getDate().getDay())
    {
        fetchDays.add(anInstant);
        // std::cout << anInstant.toString(Scale::UTC) << std::endl;
    }

    // Fetch AP indices for all days. Stack them into one continuous array.
    Array<Integer> apMultiDayArray = Array<Integer>::Empty();

    for (const Instant& fetchDay : fetchDays)
    {
        apMultiDayArray.add(spaceWeatherManager.getAp3HourSolarIndicesAt(fetchDay));
        //std::cout << "0   3   6   9   12  15  18  21  ";
    }
    //std::cout << std::endl;
    // Find correct index to start at based on time of day of the first day
    // [00:00 - 03:00) == 0, [03:00 - 06:00) == 1, etc.
    // const DateTime startDatetime = instant57HrPrevious.getDateTime(Scale::UTC);
    // std::cout << "start datetime: " << startDatetime << std::endl;
    const Time startTime = instant57HrPrevious.getDateTime(Scale::UTC).getTime();
    // std::cout << "start time: " << startTime << std::endl;
    const Size startIndex = (startTime.getHour() / 3);

    for (Size j = 0; j < startIndex; ++j)
    {
        //std::cout << apMultiDayArray[j] << "_ ";
        //if (apMultiDayArray[j]<10) std::cout << " ";
    }
    for (Size i = startIndex; i < apMultiDayArray.getSize(); ++i)
    {
        //std::cout << apMultiDayArray[i] << "  ";

       // if (apMultiDayArray[i]<10) std::cout << " ";
    }
    //std::cout << std::endl;
    // std::cout << "ap array size: " << apMultiDayArray.getSize() << std::endl;
    // std::cout << "which is: " << apMultiDayArray.getSize() / 8 << " days" << std::endl;

    // std::cout << "start index is: " << startIndex << std::endl;

    const Array<Integer>::ConstIterator startIterator = apMultiDayArray.begin() + startIndex;

    // Average of 8 AP values from 57 hours ago to 36 hours ago
    const Real apAvg3657 = Real(Array<Integer>(startIterator, startIterator+8).reduce(std::plus<Integer>())) / 8.0;

    // Average of 8 AP values from 36 hours ago to 12 hours ago
    const Real apAvg1236 = Real(Array<Integer>(startIterator+8, startIterator+16).reduce(std::plus<Integer>())) / 8.0;

    // Get daily average AP for current day
    //const Real apAvgCurrentDay = Real(Array<Integer>(apMultiDayArray.end()-8, apMultiDayArray.end()).reduce(std::plus<Integer>())) / 8.0;

    outputArray[0] = spaceWeatherManager.getApDailyIndexAt(anInstant);
    outputArray[1] = apMultiDayArray[startIndex+19]; // now
    outputArray[2] = apMultiDayArray[startIndex+18]; // now - 3 hours
    outputArray[3] = apMultiDayArray[startIndex+17]; // now - 6 hours
    outputArray[4] = apMultiDayArray[startIndex+16]; // now - 9 hours
    outputArray[5] = apAvg1236;
    outputArray[6] = apAvg3657;

    //std::cout << "ap multi day: " << apMultiDayArray << std::endl;
    Array<Real> apArrayReal = Array<Real>(outputArray, outputArray+7);
    //std::cout << "ap multi day: " << apMultiDayArray << std::endl;

    // std::cout << "ap daily" << apAvgCurrentDay << std::endl;
    // std::cout << "start time: " << startTime << std::endl;

     //
     // 0_  2_  5_  6_  15_ 18  12  22  39  27  27  18  32  39  32  15  15  15  12  6   15  12  18  27  9   15  7   12  6   12  22  27


     // 15  15  12   6  15  12  18  27   9  15   7  12   6  12  22  27  7   7   4   6   5   5   7   15  5   2   3   2   4   7   9   12 
     // 15_ 15_ 12_  6_ 15_ 12  18  27   9   15  7  12   6  12  22  27  7   7   4   6   5   5   7   15  5   2   3   2   4   7   9   12 
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

    const DateTime currentDateTime = anInstant.getDateTime(Scale::UTC);
    const Date currentDate = anInstant.getDateTime(Scale::UTC).getDate();

    // current year/day of year/sec
    const Integer year = currentDate.getYear();

    const Instant startOfYear = Instant::DateTime(DateTime(Date(year, 1, 1), Time::Midnight()), Scale::UTC);
    const Integer dayOfYear = (anInstant - startOfYear).getDays();

    const Time timeOfDay = currentDateTime.getTime();
    const Integer secondsInDay = timeOfDay.getHour() * 3600 + timeOfDay.getMinute() * 60 + timeOfDay.getSecond();

    // Solar flux values
    const Real f107 = spaceWeatherManager.getF107SolarFluxAt(anInstant);
    const Real f107Average = spaceWeatherManager.getF107SolarFlux81DayAvgAt(anInstant);

    // Ap solar indices array
    this->computeAPArray(aph.a, anInstant);
    
    input.doy=dayOfYear;
    input.year=year;
    input.sec=secondsInDay;
    input.alt=aLLA.getAltitude().inKilometers();
    input.g_lat=aLLA.getLatitude().inDegrees();
    input.g_long=aLLA.getLongitude().inDegrees();
    input.lst=input.sec/3600 + input.g_long/15; // https://github.com/magnific0/nrlmsise-00/blob/master/nrlmsise-00.h#L103
    input.f107A=f107Average;
    input.f107=f107;
    input.ap=aph.a[0];
    input.ap_a = &aph;

    gtd7d(&input, &flags, &output) ;
    
    
    return  output.d[5];
}

}  // namespace earth
}  // namespace atmospheric
}  // namespace environment
}  // namespace physics
}  // namespace ostk
