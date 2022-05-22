////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/IERS/BulletinA.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/IERS/BulletinA.hpp>

#include <OpenSpaceToolkit/Core/Types/String.hpp>
#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

#include <boost/lexical_cast.hpp>

#include <sstream>
#include <fstream>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ostk
{
namespace physics
{
namespace coord
{
namespace frame
{
namespace provider
{
namespace iers
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::ostream&                   operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   BulletinA&                  aBulletinA                                  )
{

    using ostk::core::types::String ;

    using ostk::physics::time::Scale ;

    ostk::core::utils::Print::Header(anOutputStream, "Bulletin A") ;

    ostk::core::utils::Print::Line(anOutputStream) << "Release date:" << (aBulletinA.releaseDate_.isDefined() ? aBulletinA.releaseDate_.toString() : "Undefined") ;
    ostk::core::utils::Print::Line(anOutputStream) << "TAI - UTC:" << (aBulletinA.taiMinusUtc_.isDefined() ? String::Format("{} @ {}", aBulletinA.taiMinusUtc_.toString(), aBulletinA.taiMinusUtcEpoch_.toString(Scale::UTC)) : "Undefined") ;
    ostk::core::utils::Print::Line(anOutputStream) << "Observation interval:" << (aBulletinA.observationInterval_.isDefined() ? aBulletinA.observationInterval_.toString(Scale::UTC) : "Undefined") ;
    ostk::core::utils::Print::Line(anOutputStream) << "Predictiom interval:" << (aBulletinA.predictionInterval_.isDefined() ? aBulletinA.predictionInterval_.toString(Scale::UTC) : "Undefined") ;

    ostk::core::utils::Print::Separator(anOutputStream, "Observation") ;

    for (const auto& observationIt : aBulletinA.observations_)
    {

        const BulletinA::Observation& observation = observationIt.second ;

        ostk::core::utils::Print::Line(anOutputStream) << String::Format("{:>4d}  {:>2d}  {:>2d}  {:>5d}  {:f}  {:f}  {:f}  {:f}  {:f}  {:f}",
                                                                            static_cast<int>(observation.year),
                                                                            static_cast<int>(observation.month),
                                                                            static_cast<int>(observation.day),
                                                                            static_cast<int>(observation.mjd),
                                                                            static_cast<double>(observation.x),
                                                                            static_cast<double>(observation.xError),
                                                                            static_cast<double>(observation.y),
                                                                            static_cast<double>(observation.yError),
                                                                            static_cast<double>(observation.ut1MinusUtc),
                                                                            static_cast<double>(observation.ut1MinusUtcError)) ;

    }

    ostk::core::utils::Print::Separator(anOutputStream, "Prediction") ;

    for (const auto& predictionIt : aBulletinA.predictions_)
    {

        const BulletinA::Prediction& prediction = predictionIt.second ;

        ostk::core::utils::Print::Line(anOutputStream) << String::Format("{:>4d}  {:>2d}  {:>2d}  {:>5d}  {:f}  {:f}  {:f}",
                                                                            static_cast<int>(prediction.year),
                                                                            static_cast<int>(prediction.month),
                                                                            static_cast<int>(prediction.day),
                                                                            static_cast<int>(prediction.mjd),
                                                                            static_cast<double>(prediction.x),
                                                                            static_cast<double>(prediction.y),
                                                                            static_cast<double>(prediction.ut1MinusUtc)) ;

    }

    ostk::core::utils::Print::Footer(anOutputStream) ;

    return anOutputStream ;

}

bool                            BulletinA::isDefined                        ( ) const
{

    return releaseDate_.isDefined()
        && taiMinusUtc_.isDefined()
        && taiMinusUtcEpoch_.isDefined()
        && observationInterval_.isDefined()
        && (!observations_.empty())
        && predictionInterval_.isDefined()
        && (!predictions_.empty()) ;

}

const Date&                     BulletinA::accessReleaseDate                ( ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Bulletin A") ;
    }

    return releaseDate_ ;

}

const Duration&                 BulletinA::accessTAIMinusUTC                ( ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Bulletin A") ;
    }

    return taiMinusUtc_ ;

}

const Instant&                  BulletinA::accessTAIMinusUTCEpoch           ( ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Bulletin A") ;
    }

    return taiMinusUtcEpoch_ ;

}

const Interval&                 BulletinA::accessObservationInterval        ( ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Bulletin A") ;
    }

    return observationInterval_ ;

}

const Interval&                 BulletinA::accessPredictionInterval         ( ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Bulletin A") ;
    }

    return predictionInterval_ ;

}

Date                            BulletinA::getReleaseDate                   ( ) const
{
    return this->accessReleaseDate() ;
}

Duration                        BulletinA::getTAIMinusUTC                   ( ) const
{
    return this->accessTAIMinusUTC() ;
}

Instant                         BulletinA::getTAIMinusUTCEpoch              ( ) const
{
    return this->accessTAIMinusUTCEpoch() ;
}

Interval                        BulletinA::getObservationInterval           ( ) const
{
    return this->accessObservationInterval() ;
}

BulletinA::Observation          BulletinA::getObservationAt                 (   const   Instant&                    anInstant                                   ) const
{

    using ostk::physics::time::Scale ;

    if (!anInstant.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant") ;
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Bulletin A") ;
    }

    if (!observationInterval_.contains(anInstant))
    {
        throw ostk::core::error::RuntimeError("Instant [{}] out of observation range [{} - {}].", anInstant.toString(Scale::UTC), observationInterval_.accessStart().toString(Scale::UTC), observationInterval_.accessEnd().toString(Scale::UTC)) ;
    }

    const Real instantMjd = anInstant.getModifiedJulianDate(Scale::UTC) ;

    const auto observationIt = observations_.find(instantMjd.floor()) ;

    if (observationIt != observations_.end())
    {

        if (instantMjd.isInteger())
        {
            return observationIt->second ;
        }
        else
        {

            const auto nextObservationIt = std::next(observationIt) ;

            if (nextObservationIt != observations_.end())
            {

                // [TBI] IERS gazette #13 for more precise interpolation and correction for tidal effects

                const BulletinA::Observation& previousObservation = observationIt->second ;
                const BulletinA::Observation& nextObservation = nextObservationIt->second ;

                const Real ratio = (instantMjd - previousObservation.mjd) / (nextObservation.mjd - previousObservation.mjd) ;

                const Integer year = previousObservation.year ;
                const Integer month = previousObservation.month ;
                const Integer day = previousObservation.day ;

                const Real mjd = previousObservation.mjd + ratio * (nextObservation.mjd - previousObservation.mjd) ;

                const Real x = previousObservation.x + ratio * (nextObservation.x - previousObservation.x) ;
                const Real xError = previousObservation.xError + ratio * (nextObservation.xError - previousObservation.xError) ;
                const Real y = previousObservation.y + ratio * (nextObservation.y - previousObservation.y) ;
                const Real yError = previousObservation.yError + ratio * (nextObservation.yError - previousObservation.yError) ;
                const Real ut1MinusUtc = previousObservation.ut1MinusUtc + ratio * (nextObservation.ut1MinusUtc - previousObservation.ut1MinusUtc) ;
                const Real ut1MinusUtcError = previousObservation.ut1MinusUtcError + ratio * (nextObservation.ut1MinusUtcError - previousObservation.ut1MinusUtcError) ;

                const BulletinA::Observation observation =
                {
                    year,
                    month,
                    day,
                    mjd,
                    x,
                    xError,
                    y,
                    yError,
                    ut1MinusUtc,
                    ut1MinusUtcError
                } ;

                return observation ;

            }
            else
            {
                throw ostk::core::error::RuntimeError("Cannot find observation at [{}].", anInstant.toString(Scale::UTC)) ;
            }

        }

    }
    else
    {
        throw ostk::core::error::RuntimeError("Cannot find observation at [{}].", anInstant.toString(Scale::UTC)) ;
    }

}

Interval                        BulletinA::getPredictionInterval            ( ) const
{
    return this->accessPredictionInterval() ;
}

BulletinA::Prediction           BulletinA::getPredictionAt                  (   const   Instant&                    anInstant                                   ) const
{

    using ostk::core::types::Real ;

    using ostk::physics::time::Scale ;

    if (!anInstant.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant") ;
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Bulletin A") ;
    }

    if (!predictionInterval_.contains(anInstant))
    {
        throw ostk::core::error::RuntimeError("Instant [{}] out of prediction range [{} - {}].", anInstant.toString(Scale::UTC), predictionInterval_.accessStart().toString(Scale::UTC), predictionInterval_.accessEnd().toString(Scale::UTC)) ;
    }

    const Real instantMjd = anInstant.getModifiedJulianDate(Scale::UTC) ;

    const auto predictionIt = predictions_.find(instantMjd.floor()) ;

    if (predictionIt != predictions_.end())
    {

        if (instantMjd.isInteger())
        {
            return predictionIt->second ;
        }
        else
        {

            const auto nextPredictionIt = std::next(predictionIt) ;

            if (nextPredictionIt != predictions_.end())
            {

                // [TBI] IERS gazette #13 for more precise interpolation and correction for tidal effects

                const BulletinA::Prediction& previousPrediction = predictionIt->second ;
                const BulletinA::Prediction& nextPrediction = nextPredictionIt->second ;

                const Real ratio = (instantMjd - previousPrediction.mjd) / (nextPrediction.mjd - previousPrediction.mjd) ;

                const Integer year = previousPrediction.year ;
                const Integer month = previousPrediction.month ;
                const Integer day = previousPrediction.day ;

                const Real mjd = previousPrediction.mjd + ratio * (nextPrediction.mjd - previousPrediction.mjd) ;

                const Real x = previousPrediction.x + ratio * (nextPrediction.x - previousPrediction.x) ;
                const Real y = previousPrediction.y + ratio * (nextPrediction.y - previousPrediction.y) ;
                const Real ut1MinusUtc = previousPrediction.ut1MinusUtc + ratio * (nextPrediction.ut1MinusUtc - previousPrediction.ut1MinusUtc) ;

                const BulletinA::Prediction prediction =
                {
                    year,
                    month,
                    day,
                    mjd,
                    x,
                    y,
                    ut1MinusUtc
                } ;

                return prediction ;

            }
            else
            {
                throw ostk::core::error::RuntimeError("Cannot find prediction at [{}].", anInstant.toString(Scale::UTC)) ;
            }

        }

    }
    else
    {
        throw ostk::core::error::RuntimeError("Cannot find prediction at [{}].", anInstant.toString(Scale::UTC)) ;
    }

}

BulletinA                       BulletinA::Undefined                        ( )
{
    return BulletinA() ;
}

BulletinA                       BulletinA::Load                             (   const   fs::File&                   aFile                                       )
{

    using ostk::core::types::Index ;
    using ostk::core::types::Uint8 ;
    using ostk::core::types::Uint16 ;
    using ostk::core::types::Real ;
    using ostk::core::types::String ;

    using ostk::physics::time::Scale ;
    using ostk::physics::time::Time ;
    using ostk::physics::time::DateTime ;

    if (!aFile.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("File") ;
    }

    if (!aFile.exists())
    {
        throw ostk::core::error::RuntimeError("File [{}] does not exist.", aFile.toString()) ;
    }

    const auto monthFromString = [ ] (const String& aMonthString) -> Uint8
    {

        if (aMonthString == "January")
        {
            return 1 ;
        }

        if (aMonthString == "February")
        {
            return 2 ;
        }

        if (aMonthString == "March")
        {
            return 3 ;
        }

        if (aMonthString == "April")
        {
            return 4 ;
        }

        if (aMonthString == "May")
        {
            return 5 ;
        }

        if (aMonthString == "June")
        {
            return 6 ;
        }

        if (aMonthString == "July")
        {
            return 7 ;
        }

        if (aMonthString == "August")
        {
            return 8 ;
        }

        if (aMonthString == "September")
        {
            return 9 ;
        }

        if (aMonthString == "October")
        {
            return 10 ;
        }

        if (aMonthString == "November")
        {
            return 11 ;
        }

        if (aMonthString == "December")
        {
            return 12 ;
        }

        throw ostk::core::error::runtime::Wrong("Month string", aMonthString) ;

        return 0 ;

    } ;

    BulletinA bulletin ;

    std::ifstream fileStream { aFile.getPath().toString() } ;

    Index lineIndex = 0 ;
    String line ;

    static const std::regex releaseDateRegex = std::regex("^[ ]+([\\d]+) ([\\w]+) ([\\d]+)[ ]+Vol\\.[\\d\\w\\. ]+$") ;
    static const std::regex taiMinusUtcEpochRegex = std::regex("^[ ]+Beginning ([\\d]+) ([\\w]+) ([\\d]+):[ ]+$") ;
    static const std::regex taiMinusUtcRegex = std::regex("^[ ]+TAI-UTC = ([-]?[\\d.]+) ([\\d]+) seconds[ ]+$") ;
    static const std::regex observationRegex = std::regex("^[ ]+([\\d]+)[ ]+([\\d]+)[ ]+([\\d]+)[ ]+([\\d]+)[ ]+([-]?[\\d.]+)[ ]+([\\d.]+)[ ]+([-]?[\\d.]+)[ ]+([\\d.]+)[ ]+([-]?[\\d.]+)[ ]+([\\d.]+)[ ]+$") ;
    static const std::regex predictionRegex = std::regex("^[ ]+([\\d]+)[ ]+([\\d]+)[ ]+([\\d]+)[ ]+([\\d]+)[ ]+([-]?[\\d.]+)[ ]+([-]?[\\d.]+)[ ]+([-]?[\\d.]+)[ ]+$") ;

    // Quick and dirty implementation.
    // The part below can be greatly improved:
    // - If Bulletin A has constant line count, using line index based parsing will be much faster
    // - Use flags to identify sections, to avoid regex'ing each line

    std::smatch match ;

    while (std::getline(fileStream, line))
    {

        if ((lineIndex < 10) && (!bulletin.releaseDate_.isDefined()) && std::regex_match(line, match, releaseDateRegex))
        {

            const Uint8 day = static_cast<Uint8>(boost::lexical_cast<Uint16>(match[1])) ;
            const Uint8 month = monthFromString(String(match[2])) ;
            const Uint16 year = boost::lexical_cast<Uint16>(match[3]) ;

            bulletin.releaseDate_ = Date(year, month, day) ;

        }

        if ((lineIndex < 30) && (!bulletin.taiMinusUtcEpoch_.isDefined()) && std::regex_match(line, match, taiMinusUtcEpochRegex))
        {

            const Uint8 day = static_cast<Uint8>(boost::lexical_cast<Uint16>(match[1])) ;
            const Uint8 month = monthFromString(String(match[2])) ;
            const Uint16 year = boost::lexical_cast<Uint16>(match[3]) ;

            bulletin.taiMinusUtcEpoch_ = Instant::DateTime(DateTime(Date(year, month, day), Time::Midnight()), Scale::UTC) ; // [TBC] UTC?

        }

        if ((lineIndex < 30) && (!bulletin.taiMinusUtc_.isDefined()) && std::regex_match(line, match, taiMinusUtcRegex))
        {

            const Real seconds = boost::lexical_cast<double>(match[1]) + boost::lexical_cast<double>(match[2]) / 1e6 ;

            bulletin.taiMinusUtc_ = Duration::Seconds(seconds) ;

        }

        if (std::regex_match(line, match, observationRegex))
        {

            const Integer year = 2000 + boost::lexical_cast<int>(match[1]) ;
            const Integer month = boost::lexical_cast<int>(match[2]) ;
            const Integer day = boost::lexical_cast<int>(match[3]) ;

            const Integer mjd = boost::lexical_cast<int>(match[4]) ;

            const Real x = boost::lexical_cast<double>(match[5]) ;
            const Real xError = boost::lexical_cast<double>(match[6]) ;
            const Real y = boost::lexical_cast<double>(match[7]) ;
            const Real yError = boost::lexical_cast<double>(match[8]) ;
            const Real ut1MinusUtc = boost::lexical_cast<double>(match[9]) ;
            const Real ut1MinusUtcError = boost::lexical_cast<double>(match[10]) ;

            const BulletinA::Observation observation =
            {
                year,
                month,
                day,
                Real::Integer(mjd),
                x,
                xError,
                y,
                yError,
                ut1MinusUtc,
                ut1MinusUtcError
            } ;

            bulletin.observations_.insert({ mjd, observation }) ;

        }

        if (std::regex_match(line, match, predictionRegex))
        {

            const Integer year = boost::lexical_cast<int>(match[1]) ;
            const Integer month = boost::lexical_cast<int>(match[2]) ;
            const Integer day = boost::lexical_cast<int>(match[3]) ;

            const Integer mjd = boost::lexical_cast<int>(match[4]) ;

            const Real x = boost::lexical_cast<double>(match[5]) ;
            const Real y = boost::lexical_cast<double>(match[6]) ;
            const Real ut1MinusUtc = boost::lexical_cast<double>(match[7]) ;

            const BulletinA::Prediction prediction =
            {
                year,
                month,
                day,
                Real::Integer(mjd),
                x,
                y,
                ut1MinusUtc,
            } ;

            bulletin.predictions_.insert({ mjd, prediction }) ;

        }

        lineIndex++ ;

    }

    if (!bulletin.observations_.empty())
    {

        const Instant observationStartInstant = Instant::ModifiedJulianDate(Real::Integer(bulletin.observations_.begin()->first), Scale::UTC) ;
        const Instant observationEndInstant = Instant::ModifiedJulianDate(Real::Integer(bulletin.observations_.rbegin()->first), Scale::UTC) ;

        bulletin.observationInterval_ = Interval::Closed(observationStartInstant, observationEndInstant) ;

    }

    if (!bulletin.predictions_.empty())
    {

        const Instant predictionStartInstant = Instant::ModifiedJulianDate(Real::Integer(bulletin.predictions_.begin()->first), Scale::UTC) ;
        const Instant predictionEndInstant = Instant::ModifiedJulianDate(Real::Integer(bulletin.predictions_.rbegin()->first), Scale::UTC) ;

        bulletin.predictionInterval_ = Interval::Closed(predictionStartInstant, predictionEndInstant) ;

    }

    return bulletin ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                BulletinA::BulletinA                        ( )
                                :   releaseDate_(Date::Undefined()),
                                    taiMinusUtc_(Duration::Undefined()),
                                    taiMinusUtcEpoch_(Instant::Undefined()),
                                    observationInterval_(Interval::Undefined()),
                                    observations_(Map<Integer, BulletinA::Observation>()),
                                    predictionInterval_(Interval::Undefined()),
                                    predictions_(Map<Integer, BulletinA::Prediction>())
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
