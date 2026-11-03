/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Utility_String__
#define __OpenSpaceToolkit_Physics_Utility_String__

#include <cmath>
#include <ios>
#include <limits>
#include <sstream>
#include <string>

#include <boost/lexical_cast.hpp>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

namespace ostk
{
namespace physics
{
namespace utility
{

using ostk::core::type::String;

/// @brief Convert a double to a string
///
/// Internal helper. The output matches the former ostk::core::type::Real::toString(precision) output: NaN prints as
/// "Undefined", infinities print as "+Inf" / "-Inf". With a negative precision, integral values keep a trailing ".0",
/// and other values use the round-trip representation without trailing zeros. With a non-negative precision, fixed
/// notation with that many decimals is used.
///
/// @code{.cpp}
///     DoubleToString(1.0) ; // "1.0"
///     DoubleToString(0.5) ; // "0.5"
///     DoubleToString(0.5, 3) ; // "0.500"
/// @endcode
///
/// @param [in] aValue A value
/// @param [in] aPrecision A precision (number of decimal places, or -1 for automatic)
/// @return String representation
inline String DoubleToString(double aValue, int aPrecision = -1)
{
    if (std::isnan(aValue))
    {
        return "Undefined";
    }

    if (std::isinf(aValue))
    {
        return (aValue > 0.0) ? "+Inf" : "-Inf";
    }

    if (aPrecision < 0)
    {
        std::string string = boost::lexical_cast<std::string>(aValue);

        if (string.find('e') == std::string::npos)
        {
            double integralPart;

            if (std::modf(aValue, &integralPart) == 0.0)
            {
                string += ".0";
            }
            else
            {
                string.erase(string.find_last_not_of('0') + 1, std::string::npos);  // Remove trailing zeros if any
            }
        }

        return string;
    }

    std::ostringstream stringStream;

    stringStream.precision(aPrecision);

    stringStream << std::fixed << aValue;

    return stringStream.str();
}

/// @brief Parse a string into a double
///
/// Internal helper. Accepts the same inputs as the former ostk::core::type::Real::Parse: "Undefined" / "NaN" give NaN,
/// "Inf" / "+Inf" / "-Inf" give infinities, and other strings are parsed as numbers.
///
/// @param [in] aString A string
/// @return Parsed value
inline double ParseDouble(const String& aString)
{
    if (aString.isEmpty())
    {
        throw ostk::core::error::runtime::Undefined("String");
    }

    if ((aString == "Undefined") || (aString == "NaN"))
    {
        return std::numeric_limits<double>::quiet_NaN();
    }

    if ((aString == "Inf") || (aString == "+Inf"))
    {
        return std::numeric_limits<double>::infinity();
    }

    if (aString == "-Inf")
    {
        return -std::numeric_limits<double>::infinity();
    }

    double value = 0.0;

    if ((!boost::conversion::try_lexical_convert<double>(aString, value)) || std::isnan(value))
    {
        throw ostk::core::error::RuntimeError("Cannot cast string [" + aString + "] to Real.");
    }

    return value;
}

/// @brief Parse a string into an int
///
/// Internal helper. Accepts the same numeric inputs as the former ostk::core::type::Integer::Parse.
///
/// @param [in] aString A string
/// @return Parsed value
inline int ParseInt(const String& aString)
{
    if (aString.isEmpty())
    {
        throw ostk::core::error::runtime::Undefined("String");
    }

    int value = 0;

    if (!boost::conversion::try_lexical_convert<int>(aString, value))
    {
        throw ostk::core::error::RuntimeError("Cannot cast string [" + aString + "] to Integer.");
    }

    return value;
}

}  // namespace utility
}  // namespace physics
}  // namespace ostk

#endif
