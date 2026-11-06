/// Apache License 2.0

#include <cmath>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>

#include <boost/lexical_cast.hpp>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/IERS/Finals2000A.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/IERS/Utility.hpp>
#include <OpenSpaceToolkit/Physics/Data/Utility.hpp>
#include <OpenSpaceToolkit/Physics/Utility/String.hpp>

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

using ostk::physics::coordinate::frame::provider::iers::utilities::interpolateUt1MinusUtc;
using ostk::physics::data::utilities::getFileModifiedInstant;
using ostk::physics::utility::ParseDouble;
using ostk::physics::utility::ParseInt;

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

const Instant& Finals2000A::accessLastModifiedTimestamp() const
{
    return lastModifiedTimestamp_;
}

Interval Finals2000A::getInterval() const
{
    return span_;
}

Vector2d Finals2000A::getPolarMotionAt(const Instant& anInstant) const
{
    using ostk::physics::time::Scale;

    if (!anInstant.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

    const Pair<const Finals2000A::Data*, const Finals2000A::Data*> dataRange = this->accessDataRange(anInstant);

    if ((dataRange.first != nullptr) && (dataRange.second != nullptr))
    {
        const Finals2000A::Data& previousData = *(dataRange.first);
        const Finals2000A::Data& nextData = *(dataRange.second);

        if (previousData.x_A.has_value() && previousData.y_A.has_value() && nextData.x_A.has_value() &&
            nextData.y_A.has_value())
        {
            const double instantMjd_UTC = anInstant.getModifiedJulianDate(Scale::UTC);

            const double ratio = (instantMjd_UTC - previousData.mjd) / (nextData.mjd - previousData.mjd);

            const double x_A = *previousData.x_A + ratio * (*nextData.x_A - *previousData.x_A);
            const double y_A = *previousData.y_A + ratio * (*nextData.y_A - *previousData.y_A);

            return {x_A, y_A};
        }
        else
        {
            return Vector2d::Undefined();
        }
    }

    throw ostk::core::error::RuntimeError("Cannot get polar motion at [{}].", anInstant.toString(Scale::UTC));
}

std::optional<double> Finals2000A::getUt1MinusUtcAt(const Instant& anInstant) const
{
    using ostk::physics::time::Scale;

    if (!anInstant.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

    const Pair<const Finals2000A::Data*, const Finals2000A::Data*> dataRange = this->accessDataRange(anInstant);

    if ((dataRange.first != nullptr) && (dataRange.second != nullptr))
    {
        const Finals2000A::Data& previousData = *(dataRange.first);
        const Finals2000A::Data& nextData = *(dataRange.second);

        if (previousData.ut1MinusUtc_A.has_value() && nextData.ut1MinusUtc_A.has_value())
        {
            const double instantMjd_UTC = anInstant.getModifiedJulianDate(Scale::UTC);

            const double ratio = (instantMjd_UTC - previousData.mjd) / (nextData.mjd - previousData.mjd);

            const double ut1MinusUtc_A = interpolateUt1MinusUtc(
                *previousData.ut1MinusUtc_A, previousData.mjd, *nextData.ut1MinusUtc_A, nextData.mjd, ratio, anInstant
            );

            return ut1MinusUtc_A;
        }
        else
        {
            return std::nullopt;
        }
    }

    throw ostk::core::error::RuntimeError("Cannot get UT1 - UTC at [{}].", anInstant.toString(Scale::UTC));
}

std::optional<double> Finals2000A::getLodAt(const Instant& anInstant) const
{
    using ostk::physics::time::Scale;

    if (!anInstant.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

    const Pair<const Finals2000A::Data*, const Finals2000A::Data*> dataRange = this->accessDataRange(anInstant);

    if ((dataRange.first != nullptr) && (dataRange.second != nullptr))
    {
        const Finals2000A::Data& previousData = *(dataRange.first);
        const Finals2000A::Data& nextData = *(dataRange.second);

        if (previousData.lod_A.has_value() && nextData.lod_A.has_value())
        {
            const double instantMjd_UTC = anInstant.getModifiedJulianDate(Scale::UTC);

            const double ratio = (instantMjd_UTC - previousData.mjd) / (nextData.mjd - previousData.mjd);

            const double lod_A = *previousData.lod_A + ratio * (*nextData.lod_A - *previousData.lod_A);

            return lod_A;
        }
        else
        {
            return std::nullopt;
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

    const Pair<const Finals2000A::Data*, const Finals2000A::Data*> dataRange = this->accessDataRange(anInstant);

    if ((dataRange.first != nullptr) && (dataRange.second != nullptr))
    {
        auto interpolate = [](const std::optional<double>& aPreviousValue,
                              const std::optional<double>& aNextValue,
                              double aRatio) -> std::optional<double>
        {
            if (std::isnan(aRatio))
            {
                throw ostk::core::error::runtime::Undefined("Ratio");
            }

            if (aPreviousValue.has_value() && aNextValue.has_value())
            {
                return *aPreviousValue + aRatio * (*aNextValue - *aPreviousValue);
            }

            return std::nullopt;
        };

        auto interpolateUt1MinusUtc_ = [&anInstant](
                                           const std::optional<double>& aPreviousValue,
                                           double aPreviousMjd,
                                           const std::optional<double>& aNextValue,
                                           double aNextMjd,
                                           double aRatio
                                       ) -> std::optional<double>
        {
            if (aPreviousValue.has_value() && aNextValue.has_value())
            {
                return interpolateUt1MinusUtc(*aPreviousValue, aPreviousMjd, *aNextValue, aNextMjd, aRatio, anInstant);
            }

            return std::nullopt;
        };

        const Finals2000A::Data& previousData = *(dataRange.first);
        const Finals2000A::Data& nextData = *(dataRange.second);

        const double instantMjd_UTC = anInstant.getModifiedJulianDate(Scale::UTC);

        const double ratio = (instantMjd_UTC - previousData.mjd) / (nextData.mjd - previousData.mjd);

        const int year = previousData.year;
        const int month = previousData.month;
        const int day = previousData.day;

        const double mjd = previousData.mjd + ratio * (nextData.mjd - previousData.mjd);

        const char polarMotionflag =
            (previousData.polarMotionflag == nextData.polarMotionflag) ? previousData.polarMotionflag : '?';

        const std::optional<double> x_A = interpolate(previousData.x_A, nextData.x_A, ratio);
        const std::optional<double> xError_A = interpolate(previousData.xError_A, nextData.xError_A, ratio);
        const std::optional<double> y_A = interpolate(previousData.y_A, nextData.y_A, ratio);
        const std::optional<double> yError_A = interpolate(previousData.yError_A, nextData.yError_A, ratio);

        const char ut1MinusUtcFlag =
            (previousData.ut1MinusUtcFlag == nextData.ut1MinusUtcFlag) ? previousData.ut1MinusUtcFlag : '?';

        const std::optional<double> ut1MinusUtc_A = interpolateUt1MinusUtc_(
            previousData.ut1MinusUtc_A, previousData.mjd, nextData.ut1MinusUtc_A, nextData.mjd, ratio
        );
        const std::optional<double> ut1MinusUtcError_A =
            interpolate(previousData.ut1MinusUtcError_A, nextData.ut1MinusUtcError_A, ratio);
        const std::optional<double> lod_A = interpolate(previousData.lod_A, nextData.lod_A, ratio);
        const std::optional<double> lodError_A = interpolate(previousData.lodError_A, nextData.lodError_A, ratio);

        const char nutationFlag =
            (previousData.nutationFlag == nextData.nutationFlag) ? previousData.nutationFlag : '?';

        const std::optional<double> dx_A = interpolate(previousData.dx_A, nextData.dx_A, ratio);
        const std::optional<double> dxError_A = interpolate(previousData.dxError_A, nextData.dxError_A, ratio);
        const std::optional<double> dy_A = interpolate(previousData.dy_A, nextData.dy_A, ratio);
        const std::optional<double> dyError_A = interpolate(previousData.dyError_A, nextData.dyError_A, ratio);
        const std::optional<double> x_B = interpolate(previousData.x_B, nextData.x_B, ratio);
        const std::optional<double> y_B = interpolate(previousData.y_B, nextData.y_B, ratio);
        const std::optional<double> ut1MinusUtc_B = interpolateUt1MinusUtc_(
            previousData.ut1MinusUtc_B, previousData.mjd, nextData.ut1MinusUtc_B, nextData.mjd, ratio
        );
        const std::optional<double> dx_B = interpolate(previousData.dx_B, nextData.dx_B, ratio);
        const std::optional<double> dy_B = interpolate(previousData.dy_B, nextData.dy_B, ratio);

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

Finals2000A Finals2000A::Load(const filesystem::File& aFile)
{
    using ostk::core::container::Array;
    using ostk::core::type::Index;
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

    auto parseReal = [](const String& aLine, const Index& aStartColumnNumber, const Index& anEndColumnNumber
                     ) -> std::optional<double>
    {
        String string = aLine.getSubstring(aStartColumnNumber - 1, anEndColumnNumber - aStartColumnNumber + 1).trim();

        if (string.isEmpty())
        {
            return std::nullopt;
        }

        if ((string.getLength() > 2) && (string.getHead(1) == "."))
        {
            string = "0." + string.getTail(string.getLength() - 1);
        }

        if ((string.getLength() > 2) && (string.getHead(2) == "-."))
        {
            string = "-0." + string.getTail(string.getLength() - 2);
        }

        return ParseDouble(string);
    };

    while (std::getline(fileStream, line))
    {
        const int year = ParseInt(line.getSubstring(0, 2).trim());
        const int month = ParseInt(line.getSubstring(2, 2).trim());
        const int day = ParseInt(line.getSubstring(4, 2).trim());

        const double mjd = parseReal(line, 8, 15).value();

        const char polarMotionflag = line.at(16);

        const std::optional<double> x_A = parseReal(line, 19, 27);
        const std::optional<double> xError_A = parseReal(line, 28, 36);
        const std::optional<double> y_A = parseReal(line, 38, 46);
        const std::optional<double> yError_A = parseReal(line, 47, 55);

        const char ut1MinusUtcFlag = line.at(57);

        const std::optional<double> ut1MinusUtc_A = parseReal(line, 59, 68);
        const std::optional<double> ut1MinusUtcError_A = parseReal(line, 69, 78);
        const std::optional<double> lod_A = parseReal(line, 80, 86);
        const std::optional<double> lodError_A = parseReal(line, 87, 93);

        const char nutationFlag = line.at(95);

        const std::optional<double> dx_A = parseReal(line, 98, 106);
        const std::optional<double> dxError_A = parseReal(line, 107, 115);
        const std::optional<double> dy_A = parseReal(line, 117, 125);
        const std::optional<double> dyError_A = parseReal(line, 126, 134);
        const std::optional<double> x_B = parseReal(line, 135, 144);
        const std::optional<double> y_B = parseReal(line, 145, 154);
        const std::optional<double> ut1MinusUtc_B = parseReal(line, 155, 165);
        const std::optional<double> dx_B = parseReal(line, 166, 175);
        const std::optional<double> dy_B = parseReal(line, 176, 185);

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
      data_(Map<double, Finals2000A::Data>())
{
}

Pair<const Finals2000A::Data*, const Finals2000A::Data*> Finals2000A::accessDataRange(const Instant& anInstant) const
{
    using ostk::physics::time::Scale;

    const double instantMjd_UTC = anInstant.getModifiedJulianDate(Scale::UTC);

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
