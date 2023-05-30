/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Time_Scale__
#define __OpenSpaceToolkit_Physics_Time_Scale__

#include <OpenSpaceToolkit/Core/Types/String.hpp>

namespace ostk
{
namespace physics
{
namespace time
{

using ostk::core::types::String;

/// @brief                      Time scale
///
/// @ref                        http://www.iausofa.org/sofa_ts_c.pdf
/// @ref                        https://www.cv.nrao.edu/~rfisher/Ephemerides/times.html
/// @ref                        http://stjarnhimlen.se/comp/time.html
/// @ref                        http://www.navipedia.net/index.php/Time_References_in_GNSS
/// @ref                        Springer Handbook of Global Navigation Satellite Systems

enum class Scale
{

    Undefined,  ///< Undefined time

    UTC,  ///< Coordinated Universal Time
    TT,   ///< Terrestial Time (a.k.a. TDT)
    TAI,  ///< International Atomic Time

    UT1,   ///< Universal Time
    TCG,   ///< Geocentric Coordinate Time
    TCB,   ///< Barycentric Coordinate Time
    TDB,   ///< Barycentric Dynamic Time
    GMST,  ///< Greenwich Mean Sidereal Time

    GPST,   ///< Global Positioning System (GPS) Time
    GST,    ///< Galileo System Time
    GLST,   ///< GLONASS Time
    BDT,    ///< BeiDou Time
    QZSST,  ///< Quasi-Zenith Satellite System (QZSS) Time
    IRNSST  ///< Indian Regional Navigation Satellite System (IRNSS) Time

};

/// @brief                      Convert a time scale to its string representation
///
/// @code
///                             String scaleString = StringFromScale(time::Scale::UTC) ; // "UTC"
/// @endcode
///
/// @param                      [in] aScale A time scale
/// @return                     String representation of time scale

String StringFromScale(const Scale& aScale);

/// @brief                      Parse a string representation to its corresponding time scale
///
/// @code
///                             time::Scale timeScale = ScaleFromString("UTC") ; // time::Scale::UTC
/// @endcode
///
/// @param                      [in] aString A string
/// @return                     Time scale

Scale ScaleFromString(const String& aString);

}  // namespace time
}  // namespace physics
}  // namespace ostk

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
