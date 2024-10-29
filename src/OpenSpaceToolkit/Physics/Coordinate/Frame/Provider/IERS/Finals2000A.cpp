/// Apache License 2.0

#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>

#include <boost/lexical_cast.hpp>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/IERS/Finals2000A.hpp>
#include <OpenSpaceToolkit/Physics/Data/Utility.hpp>

namespace ostk
{
namespace physics
{
namespace coordinate
{
namespace frame
{
namespace provider
{
namespace iers
{

using ostk::physics::data::utilities::getFileModifiedInstant;

std::ostream& operator<<(std::ostream& anOutputStream, const Finals2000A& aFinals2000A)
{
    using ostk::core::type::String;

    using ostk::physics::time::Scale;

    ostk::core::utils::Print::Header(anOutputStream, "Finals 2000A");

    ostk::core::utils::Print::Line(anOutputStream)
        << "Interval:"
        << (aFinals2000A.getInterval().isDefined() ? aFinals2000A.getInterval().toString(Scale::UTC) : "Undefined");

    ostk::core::utils::Print::Footer(anOutputStream);

    return anOutputStream;
}

bool Finals2000A::isDefined() const
{
    return !data_.empty();
}

const Instant& Finals2000A::accessLastModifiedTimestamp() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Finals 2000A");
    }

    return lastModifiedTimestamp_;
}

Interval Finals2000A::getInterval() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Finals 2000A");
    }

    return span_;
}

Vector2d Finals2000A::getPolarMotionAt(const Instant& anInstant) const
{
    using ostk::physics::time::Scale;

    if (!anInstant.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Finals 2000A");
    }

    const Pair<const Finals2000A::Data*, const Finals2000A::Data*> dataRange = this->accessDataRange(anInstant);

    if ((dataRange.first != nullptr) && (dataRange.second != nullptr))
    {
        const Finals2000A::Data& previousData = *(dataRange.first);
        const Finals2000A::Data& nextData = *(dataRange.second);

        if (previousData.x_A.isDefined() && previousData.y_A.isDefined() && nextData.x_A.isDefined() &&
            nextData.y_A.isDefined())
        {
            const Real instantMjd_UTC = anInstant.getModifiedJulianDate(Scale::UTC);

            const Real ratio = (instantMjd_UTC - previousData.mjd) / (nextData.mjd - previousData.mjd);

            const Real x_A = previousData.x_A + ratio * (nextData.x_A - previousData.x_A);
            const Real y_A = previousData.y_A + ratio * (nextData.y_A - previousData.y_A);

            return {x_A, y_A};
        }
        else
        {
            return Vector2d::Undefined();
        }
    }

    throw ostk::core::error::RuntimeError("Cannot get polar motion at [{}].", anInstant.toString(Scale::UTC));
}

Real Finals2000A::getUt1MinusUtcAt(const Instant& anInstant) const
{
    using ostk::physics::time::Scale;

    if (!anInstant.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Finals 2000A");
    }

    const Pair<const Finals2000A::Data*, const Finals2000A::Data*> dataRange = this->accessDataRange(anInstant);

    if ((dataRange.first != nullptr) && (dataRange.second != nullptr))
    {
        const Finals2000A::Data& previousData = *(dataRange.first);
        const Finals2000A::Data& nextData = *(dataRange.second);

        if (previousData.ut1MinusUtc_A.isDefined() && nextData.ut1MinusUtc_A.isDefined())
        {
            const Real instantMjd_UTC = anInstant.getModifiedJulianDate(Scale::UTC);

            const Real ratio = (instantMjd_UTC - previousData.mjd) / (nextData.mjd - previousData.mjd);

            const Real ut1MinusUtc_A =
                previousData.ut1MinusUtc_A + ratio * (nextData.ut1MinusUtc_A - previousData.ut1MinusUtc_A);
            // const Real ut1MinusUtc_B = previousData.ut1MinusUtc_B + ratio * (nextData.ut1MinusUtc_B -
            // previousData.ut1MinusUtc_B) ;

            return ut1MinusUtc_A;
        }
        else
        {
            return Real::Undefined();
        }
    }

    throw ostk::core::error::RuntimeError("Cannot get UT1 - UTC at [{}].", anInstant.toString(Scale::UTC));
}

Real Finals2000A::getLodAt(const Instant& anInstant) const
{
    using ostk::physics::time::Scale;

    if (!anInstant.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Finals 2000A");
    }

    const Pair<const Finals2000A::Data*, const Finals2000A::Data*> dataRange = this->accessDataRange(anInstant);

    if ((dataRange.first != nullptr) && (dataRange.second != nullptr))
    {
        const Finals2000A::Data& previousData = *(dataRange.first);
        const Finals2000A::Data& nextData = *(dataRange.second);

        if (previousData.lod_A.isDefined() && nextData.lod_A.isDefined())
        {
            const Real instantMjd_UTC = anInstant.getModifiedJulianDate(Scale::UTC);

            const Real ratio = (instantMjd_UTC - previousData.mjd) / (nextData.mjd - previousData.mjd);

            const Real lod_A = previousData.lod_A + ratio * (nextData.lod_A - previousData.lod_A);

            return lod_A;
        }
        else
        {
            return Real::Undefined();
        }
    }

    throw ostk::core::error::RuntimeError("Cannot get length of day at [{}].", anInstant.toString(Scale::UTC));
}

Finals2000A::Data Finals2000A::getDataAt(const Instant& anInstant) const
{
    using ostk::physics::time::Scale;

    if (!anInstant.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Finals 2000A");
    }

    const Pair<const Finals2000A::Data*, const Finals2000A::Data*> dataRange = this->accessDataRange(anInstant);

    if ((dataRange.first != nullptr) && (dataRange.second != nullptr))
    {
        auto interpolate = [](const Real& aPreviousValue, const Real& aNextValue, const Real& aRatio) -> Real
        {
            if (!aRatio.isDefined())
            {
                throw ostk::core::error::runtime::Undefined("Ratio");
            }

            if (aPreviousValue.isDefined() && aNextValue.isDefined())
            {
                return aPreviousValue + aRatio * (aNextValue - aPreviousValue);
            }

            return Real::Undefined();
        };

        const Finals2000A::Data& previousData = *(dataRange.first);
        const Finals2000A::Data& nextData = *(dataRange.second);

        const Real instantMjd_UTC = anInstant.getModifiedJulianDate(Scale::UTC);

        const Real ratio = (instantMjd_UTC - previousData.mjd) / (nextData.mjd - previousData.mjd);

        const Integer year = previousData.year;
        const Integer month = previousData.month;
        const Integer day = previousData.day;

        const Real mjd = interpolate(previousData.mjd, nextData.mjd, ratio);

        const char polarMotionflag =
            (previousData.polarMotionflag == nextData.polarMotionflag) ? previousData.polarMotionflag : '?';

        const Real x_A = interpolate(previousData.x_A, nextData.x_A, ratio);
        const Real xError_A = interpolate(previousData.xError_A, nextData.xError_A, ratio);
        const Real y_A = interpolate(previousData.y_A, nextData.y_A, ratio);
        const Real yError_A = interpolate(previousData.yError_A, nextData.yError_A, ratio);

        const char ut1MinusUtcFlag =
            (previousData.ut1MinusUtcFlag == nextData.ut1MinusUtcFlag) ? previousData.ut1MinusUtcFlag : '?';

        const Real ut1MinusUtc_A = interpolate(previousData.ut1MinusUtc_A, nextData.ut1MinusUtc_A, ratio);
        const Real ut1MinusUtcError_A =
            interpolate(previousData.ut1MinusUtcError_A, nextData.ut1MinusUtcError_A, ratio);
        const Real lod_A = interpolate(previousData.lod_A, nextData.lod_A, ratio);
        const Real lodError_A = interpolate(previousData.lodError_A, nextData.lodError_A, ratio);

        const char nutationFlag =
            (previousData.nutationFlag == nextData.nutationFlag) ? previousData.nutationFlag : '?';

        const Real dx_A = interpolate(previousData.dx_A, nextData.dx_A, ratio);
        const Real dxError_A = interpolate(previousData.dxError_A, nextData.dxError_A, ratio);
        const Real dy_A = interpolate(previousData.dy_A, nextData.dy_A, ratio);
        const Real dyError_A = interpolate(previousData.dyError_A, nextData.dyError_A, ratio);
        const Real x_B = interpolate(previousData.x_B, nextData.x_B, ratio);
        const Real y_B = interpolate(previousData.y_B, nextData.y_B, ratio);
        const Real ut1MinusUtc_B = interpolate(previousData.ut1MinusUtc_B, nextData.ut1MinusUtc_B, ratio);
        const Real dx_B = interpolate(previousData.dx_B, nextData.dx_B, ratio);
        const Real dy_B = interpolate(previousData.dy_B, nextData.dy_B, ratio);

        const Finals2000A::Data data = {
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
        };

        return data;
    }

    throw ostk::core::error::RuntimeError("Cannot get data at [{}].", anInstant.toString(Scale::UTC));
}

Finals2000A Finals2000A::Undefined()
{
    return Finals2000A();
}

Finals2000A Finals2000A::Load(const filesystem::File& aFile)
{
    using ostk::core::container::Array;
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

    Finals2000A finals2000a;

    finals2000a.lastModifiedTimestamp_ = getFileModifiedInstant(aFile);

    std::ifstream fileStream(aFile.getPath().toString());

    Index lineIndex = 0;
    String line;

    auto parseReal = [](const String& aLine, const Index& aStartColumnNumber, const Index& anEndColumnNumber) -> Real
    {
        String string = aLine.getSubstring(aStartColumnNumber - 1, anEndColumnNumber - aStartColumnNumber + 1).trim();

        if (string.isEmpty())
        {
            return Real::Undefined();
        }

        if ((string.getLength() > 2) && (string.getHead(1) == "."))
        {
            string = "0." + string.getTail(string.getLength() - 1);
        }

        if ((string.getLength() > 2) && (string.getHead(2) == "-."))
        {
            string = "-0." + string.getTail(string.getLength() - 2);
        }

        return Real::Parse(string);
    };

    while (std::getline(fileStream, line))
    {
        const Integer year = Integer::Parse(line.getSubstring(0, 2).trim());
        const Integer month = Integer::Parse(line.getSubstring(2, 2).trim());
        const Integer day = Integer::Parse(line.getSubstring(4, 2).trim());

        const Real mjd = parseReal(line, 8, 15);

        const char polarMotionflag = line.at(16);

        const Real x_A = parseReal(line, 19, 27);
        const Real xError_A = parseReal(line, 28, 36);
        const Real y_A = parseReal(line, 38, 46);
        const Real yError_A = parseReal(line, 47, 55);

        const char ut1MinusUtcFlag = line.at(57);

        const Real ut1MinusUtc_A = parseReal(line, 59, 68);
        const Real ut1MinusUtcError_A = parseReal(line, 69, 78);
        const Real lod_A = parseReal(line, 80, 86);
        const Real lodError_A = parseReal(line, 87, 93);

        const char nutationFlag = line.at(95);

        const Real dx_A = parseReal(line, 98, 106);
        const Real dxError_A = parseReal(line, 107, 115);
        const Real dy_A = parseReal(line, 117, 125);
        const Real dyError_A = parseReal(line, 126, 134);
        const Real x_B = parseReal(line, 135, 144);
        const Real y_B = parseReal(line, 145, 154);
        const Real ut1MinusUtc_B = parseReal(line, 155, 165);
        const Real dx_B = parseReal(line, 166, 175);
        const Real dy_B = parseReal(line, 176, 185);

        const Finals2000A::Data data = {
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
        };

        finals2000a.data_.insert({mjd, data});

        lineIndex++;
    }

    if (!finals2000a.data_.empty())
    {
        const Instant startInstant = Instant::ModifiedJulianDate(finals2000a.data_.begin()->first, Scale::UTC);
        const Instant endInstant = Instant::ModifiedJulianDate(finals2000a.data_.rbegin()->first, Scale::UTC);

        finals2000a.span_ = Interval::Closed(startInstant, endInstant);
    }

    return finals2000a;
}

Finals2000A::Finals2000A()
    : lastModifiedTimestamp_(Instant::Undefined()),
      span_(Interval::Undefined()),
      data_(Map<Real, Finals2000A::Data>())
{
}

Pair<const Finals2000A::Data*, const Finals2000A::Data*> Finals2000A::accessDataRange(const Instant& anInstant) const
{
    using ostk::physics::time::Scale;

    const Real instantMjd_UTC = anInstant.getModifiedJulianDate(Scale::UTC);

    const auto nextDataIt = data_.lower_bound(instantMjd_UTC);

    if (nextDataIt == data_.end())
    {
        return {&(data_.rbegin()->second), nullptr};
    }
    else if (nextDataIt == data_.begin())
    {
        return {nullptr, &(nextDataIt->second)};
    }
    else
    {
        const auto previousDataIt = std::prev(nextDataIt);

        return {&(previousDataIt->second), &(nextDataIt->second)};
    }

    return {nullptr, nullptr};
}

}  // namespace iers
}  // namespace provider
}  // namespace frame
}  // namespace coordinate
}  // namespace physics
}  // namespace ostk
