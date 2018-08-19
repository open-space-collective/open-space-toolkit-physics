////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Coordinate/Frame/Providers/IERS/Finals2000A.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Coordinate/Frame/Providers/IERS/Finals2000A.hpp>

#include <Library/Core/Types/String.hpp>
#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

#include <boost/lexical_cast.hpp>

#include <sstream>
#include <fstream>
#include <iostream>
#include <iterator>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
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
                                                                                const   Finals2000A&                aFinals2000A                                )
{

    using library::core::types::String ;

    using library::physics::time::Scale ;

    library::core::utils::Print::Header(anOutputStream, "Finals 2000A") ;

    library::core::utils::Print::Line(anOutputStream) << "Interval:" << (aFinals2000A.getInterval().isDefined() ? aFinals2000A.getInterval().toString(Scale::UTC) : "Undefined") ;

    library::core::utils::Print::Footer(anOutputStream) ;

    return anOutputStream ;

}

bool                            Finals2000A::isDefined                      ( ) const
{
    return !data_.empty() ;
}

Interval                        Finals2000A::getInterval                    ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Finals 2000A") ;
    }

    return span_ ;

}

Vector2d                        Finals2000A::getPolarMotionAt               (   const   Instant&                    anInstant                                   ) const
{

    using library::physics::time::Scale ;

    if (!anInstant.isDefined())
    {
        throw library::core::error::runtime::Undefined("Instant") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Finals 2000A") ;
    }

    const Pair<const Finals2000A::Data*, const Finals2000A::Data*> dataRange = this->accessDataRange(anInstant) ;

    if ((dataRange.first != nullptr) && (dataRange.second != nullptr))
    {

        const Finals2000A::Data& previousData = *(dataRange.first) ;
        const Finals2000A::Data& nextData = *(dataRange.second) ;

        const Real instantMjd = anInstant.getModifiedJulianDate(Scale::UTC) ;

        const Real ratio = (instantMjd - previousData.mjd) / (nextData.mjd - previousData.mjd) ;
        
        const Real x_A = previousData.x_A + ratio * (nextData.x_A - previousData.x_A) ;
        const Real y_A = previousData.y_A + ratio * (nextData.y_A - previousData.y_A) ;

        return { x_A, y_A } ;

    }

    throw library::core::error::RuntimeError("Cannot get polar motion at [{}].", anInstant.toString(Scale::UTC)) ;

}

Real                            Finals2000A::getUt1MinusUtcAt               (   const   Instant&                    anInstant                                   ) const
{

    using library::physics::time::Scale ;

    if (!anInstant.isDefined())
    {
        throw library::core::error::runtime::Undefined("Instant") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Finals 2000A") ;
    }

    const Pair<const Finals2000A::Data*, const Finals2000A::Data*> dataRange = this->accessDataRange(anInstant) ;

    if ((dataRange.first != nullptr) && (dataRange.second != nullptr))
    {

        const Finals2000A::Data& previousData = *(dataRange.first) ;
        const Finals2000A::Data& nextData = *(dataRange.second) ;

        const Real instantMjd = anInstant.getModifiedJulianDate(Scale::UTC) ;

        const Real ratio = (instantMjd - previousData.mjd) / (nextData.mjd - previousData.mjd) ;
        
        const Real ut1MinusUtc_A = previousData.ut1MinusUtc_A + ratio * (nextData.ut1MinusUtc_A - previousData.ut1MinusUtc_A) ;
        // const Real ut1MinusUtc_B = previousData.ut1MinusUtc_B + ratio * (nextData.ut1MinusUtc_B - previousData.ut1MinusUtc_B) ;

        return ut1MinusUtc_A ;

    }

    throw library::core::error::RuntimeError("Cannot get UT1 - UTC at [{}].", anInstant.toString(Scale::UTC)) ;

}

Real                            Finals2000A::getLodAt                       (   const   Instant&                    anInstant                                   ) const
{

    using library::physics::time::Scale ;

    if (!anInstant.isDefined())
    {
        throw library::core::error::runtime::Undefined("Instant") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Finals 2000A") ;
    }

    const Pair<const Finals2000A::Data*, const Finals2000A::Data*> dataRange = this->accessDataRange(anInstant) ;

    if ((dataRange.first != nullptr) && (dataRange.second != nullptr))
    {

        const Finals2000A::Data& previousData = *(dataRange.first) ;
        const Finals2000A::Data& nextData = *(dataRange.second) ;

        const Real instantMjd = anInstant.getModifiedJulianDate(Scale::UTC) ;

        const Real ratio = (instantMjd - previousData.mjd) / (nextData.mjd - previousData.mjd) ;
        
        const Real lod_A = previousData.lod_A + ratio * (nextData.lod_A - previousData.lod_A) ;

        return lod_A ;

    }

    throw library::core::error::RuntimeError("Cannot get length of day at [{}].", anInstant.toString(Scale::UTC)) ;

}

Finals2000A::Data               Finals2000A::getDataAt                      (   const   Instant&                    anInstant                                   ) const
{
    
    using library::physics::time::Scale ;

    if (!anInstant.isDefined())
    {
        throw library::core::error::runtime::Undefined("Instant") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Finals 2000A") ;
    }

    const Pair<const Finals2000A::Data*, const Finals2000A::Data*> dataRange = this->accessDataRange(anInstant) ;

    if ((dataRange.first != nullptr) && (dataRange.second != nullptr))
    {

        const Finals2000A::Data& previousData = *(dataRange.first) ;
        const Finals2000A::Data& nextData = *(dataRange.second) ;

        const Real instantMjd = anInstant.getModifiedJulianDate(Scale::UTC) ;

        const Real ratio = (instantMjd - previousData.mjd) / (nextData.mjd - previousData.mjd) ;

        const Integer year = previousData.year ;
        const Integer month = previousData.month ;
        const Integer day = previousData.day ;
        
        const Real mjd = previousData.mjd + ratio * (nextData.mjd - previousData.mjd) ;
        
        const char polarMotionflag = (previousData.polarMotionflag == nextData.polarMotionflag) ? previousData.polarMotionflag : '?' ;
        
        const Real x_A = previousData.x_A + ratio * (nextData.x_A - previousData.x_A) ;
        const Real xError_A = previousData.xError_A + ratio * (nextData.xError_A - previousData.xError_A) ;
        const Real y_A = previousData.y_A + ratio * (nextData.y_A - previousData.y_A) ;
        const Real yError_A = previousData.yError_A + ratio * (nextData.yError_A - previousData.yError_A) ;
        
        const char ut1MinusUtcFlag = (previousData.ut1MinusUtcFlag == nextData.ut1MinusUtcFlag) ? previousData.ut1MinusUtcFlag : '?' ;
        
        const Real ut1MinusUtc_A = previousData.ut1MinusUtc_A + ratio * (nextData.ut1MinusUtc_A - previousData.ut1MinusUtc_A) ;
        const Real ut1MinusUtcError_A = previousData.ut1MinusUtcError_A + ratio * (nextData.ut1MinusUtcError_A - previousData.ut1MinusUtcError_A) ;
        const Real lod_A = previousData.lod_A + ratio * (nextData.lod_A - previousData.lod_A) ;
        const Real lodError_A = previousData.lodError_A + ratio * (nextData.lodError_A - previousData.lodError_A) ;
        
        const char nutationFlag = (previousData.nutationFlag == nextData.nutationFlag) ? previousData.nutationFlag : '?' ;
        
        const Real dx_A = previousData.dx_A + ratio * (nextData.dx_A - previousData.dx_A) ;
        const Real dxError_A = previousData.dxError_A + ratio * (nextData.dxError_A - previousData.dxError_A) ;
        const Real dy_A = previousData.dy_A + ratio * (nextData.dy_A - previousData.dy_A) ;
        const Real dyError_A = previousData.dyError_A + ratio * (nextData.dyError_A - previousData.dyError_A) ;
        const Real x_B = previousData.x_B + ratio * (nextData.x_B - previousData.x_B) ;
        const Real y_B = previousData.y_B + ratio * (nextData.y_B - previousData.y_B) ;
        const Real ut1MinusUtc_B = previousData.ut1MinusUtc_B + ratio * (nextData.ut1MinusUtc_B - previousData.ut1MinusUtc_B) ;
        const Real dx_B = previousData.dx_B + ratio * (nextData.dx_B - previousData.dx_B) ;
        const Real dy_B = previousData.dy_B + ratio * (nextData.dy_B - previousData.dy_B) ;

        const Finals2000A::Data data =
        {
            year,
            month,
            day,
            mjd,
            polarMotionflag,
            x_A,
            xError_A,
            y_A,
            yError_A,
            ut1MinusUtcFlag,
            ut1MinusUtc_A,
            ut1MinusUtcError_A,
            lod_A,
            lodError_A,
            nutationFlag,
            dx_A,
            dxError_A,
            dy_A,
            dyError_A,
            x_B,
            y_B,
            ut1MinusUtc_B,
            dx_B,
            dy_B
        } ;

        return data ;

    }

    throw library::core::error::RuntimeError("Cannot get data at [{}].", anInstant.toString(Scale::UTC)) ;

}

Finals2000A                     Finals2000A::Undefined                      ( )
{
    return Finals2000A() ;
}

Finals2000A                     Finals2000A::Load                           (   const   fs::File&                   aFile                                       )
{

    using library::core::types::Index ;
    using library::core::types::Uint8 ;
    using library::core::types::Uint16 ;
    using library::core::types::Real ;
    using library::core::types::String ;
    using library::core::ctnr::Array ;

    using library::physics::time::Scale ;
    using library::physics::time::Time ;
    using library::physics::time::DateTime ;

    if (!aFile.isDefined())
    {
        throw library::core::error::runtime::Undefined("File") ;
    }

    if (!aFile.exists())
    {
        throw library::core::error::RuntimeError("File [{}] does not exist.", aFile.toString()) ;
    }

    Finals2000A finals2000a ;

    std::ifstream fileStream(aFile.getPath().toString()) ;
    
    Index lineIndex = 0 ;
    String line ;

    // auto splitString = [] (const String& aString, char aDelimiter) -> Array<String>
    // {

    //     Array<String> aStringArray = Array<String>::Empty() ;
        
    //     std::stringstream stringStream(aString) ;
        
    //     String item ;

    //     while (std::getline(stringStream, item, aDelimiter))
    //     {

    //         if (!item.empty())
    //         {
    //             aStringArray.add(item) ;
    //         }

    //     }
        
    //     return aStringArray ;

    // } ;

    auto parseReal = [] (const String& aLine, const Index& aStartColumnNumber, const Index& anEndColumnNumber) -> Real
    {

        String string = aLine.getSubstring(aStartColumnNumber - 1, anEndColumnNumber - aStartColumnNumber + 1).trim() ;

        if (string.isEmpty())
        {
            return Real::Undefined() ;
        }

        if ((string.getLength() > 2) && (string.getHead(1) == "."))
        {
            string = "0." + string.getTail(string.getLength() - 1) ;
        }

        if ((string.getLength() > 2) && (string.getHead(2) == "-."))
        {
            string = "-0." + string.getTail(string.getLength() - 2) ;
        }

        return Real::Parse(string) ;

    } ;

    while (std::getline(fileStream, line))
    {

        const Integer year = Integer::Parse(line.getSubstring(0, 2).trim()) ;
        const Integer month = Integer::Parse(line.getSubstring(2, 2).trim()) ;
        const Integer day = Integer::Parse(line.getSubstring(4, 2).trim()) ;
        
        const Real mjd = parseReal(line, 8, 15) ;
        
        const char polarMotionflag = line.at(16) ;
        
        const Real x_A = parseReal(line, 19, 27) ;
        const Real xError_A = parseReal(line, 28, 36) ;
        const Real y_A = parseReal(line, 38, 46) ;
        const Real yError_A = parseReal(line, 47, 55) ;
        
        const char ut1MinusUtcFlag = line.at(57) ;
        
        const Real ut1MinusUtc_A = parseReal(line, 59, 68) ;
        const Real ut1MinusUtcError_A = parseReal(line, 69, 78) ;
        const Real lod_A = parseReal(line, 80, 86) ;
        const Real lodError_A = parseReal(line, 87, 93) ;
        
        const char nutationFlag = line.at(95) ;
        
        const Real dx_A = parseReal(line, 98, 106) ;
        const Real dxError_A = parseReal(line, 107, 115) ;
        const Real dy_A = parseReal(line, 117, 125) ;
        const Real dyError_A = parseReal(line, 126, 134) ;
        const Real x_B = parseReal(line, 135, 144) ;
        const Real y_B = parseReal(line, 145, 154) ;
        const Real ut1MinusUtc_B = parseReal(line, 155, 165) ;
        const Real dx_B = parseReal(line, 166, 175) ;
        const Real dy_B = parseReal(line, 176, 185) ;

        const Finals2000A::Data data =
        {
            year,
            month,
            day,
            mjd,
            polarMotionflag,
            x_A,
            xError_A,
            y_A,
            yError_A,
            ut1MinusUtcFlag,
            ut1MinusUtc_A,
            ut1MinusUtcError_A,
            lod_A,
            lodError_A,
            nutationFlag,
            dx_A,
            dxError_A,
            dy_A,
            dyError_A,
            x_B,
            y_B,
            ut1MinusUtc_B,
            dx_B,
            dy_B
        } ;

        finals2000a.data_.insert({ mjd, data }) ;

        lineIndex++ ;

    }

    if (!finals2000a.data_.empty())
    {
        
        const Instant startInstant = Instant::ModifiedJulianDate(finals2000a.data_.begin()->first, Scale::UTC) ;
        const Instant endInstant = Instant::ModifiedJulianDate(finals2000a.data_.rbegin()->first, Scale::UTC) ;
        
        finals2000a.span_ = Interval::Closed(startInstant, endInstant) ;

    }

    return finals2000a ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Finals2000A::Finals2000A                    ( )
                                :   span_(Interval::Undefined()),
                                    data_(Map<Real, Finals2000A::Data>())
{

}

Pair<const Finals2000A::Data*, const Finals2000A::Data*> Finals2000A::accessDataRange ( const Instant&              anInstant                                   ) const
{

    using library::physics::time::Scale ;

    const Real instantMjd = anInstant.getModifiedJulianDate(Scale::UTC) ;
    
    const auto nextDataIt = data_.lower_bound(instantMjd) ;

    if (nextDataIt == data_.end())
    {
        return { &(data_.rbegin()->second), nullptr } ;
    }
    else if (nextDataIt == data_.begin())
    {
        return { nullptr, &(nextDataIt->second) } ;
    }
    else
    {

        const auto previousDataIt = std::prev(nextDataIt) ;

        return { &(previousDataIt->second), &(nextDataIt->second) } ;

    }

    return { nullptr, nullptr } ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////