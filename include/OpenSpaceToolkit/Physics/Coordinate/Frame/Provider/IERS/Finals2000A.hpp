/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_Finals2000A__
#define __OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_Finals2000A__

#include <OpenSpaceToolkit/Core/Container/Map.hpp>
#include <OpenSpaceToolkit/Core/Container/Pair.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>
#include <OpenSpaceToolkit/Core/Type/Integer.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>

#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

#include <OpenSpaceToolkit/Physics/Time/Date.hpp>
#include <OpenSpaceToolkit/Physics/Time/Duration.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Time/Interval.hpp>

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

namespace filesystem = ostk::core::filesystem;

using ostk::core::type::Integer;
using ostk::core::type::Real;
using ostk::core::container::Pair;
using ostk::core::container::Map;
using ostk::core::filesystem::File;

using ostk::mathematics::object::Vector2d;

using ostk::physics::time::Date;
using ostk::physics::time::Instant;
using ostk::physics::time::Duration;
using ostk::physics::time::Interval;

/// @brief                      Standard Rapid EOP Data since 01. January 1992 (IAU2000)
///
///                             This file (updated weekly) is the complete Earth orientation data set, since 1 January
///                             1992 with 1 year of predictions. The nutation series in dX and dY uses the IAU 2000A
///                             Nutation Theory.
///
/// @ref                        https://www.iers.org/IERS/EN/DataProducts/EarthOrientationData/eop.html -> finals.data
/// (IAU2000)

class Finals2000A
{
   public:
    struct Data
    {
        Integer year;   ///< Year (to get true calendar year, add 1900 for MJD <= 51543 or add 2000 for MJD >= 51544)
        Integer month;  ///< Month number
        Integer day;    ///< Day of month

        Real mjd;  ///< Fractional Modified Julian Date (MJD UTC)

        char polarMotionflag;  ///< IERS (I) or Prediction (P) flag for Bulletin A polar motion values

        Real x_A;       ///< [asec] Bulletin A PM-x
        Real xError_A;  ///< [asec] Error in PM-x
        Real y_A;       ///< [asec] Bulletin A PM-y
        Real yError_A;  ///< [asec] Error in PM-y

        char ut1MinusUtcFlag;  ///< IERS (I) or Prediction (P) flag for Bulletin A UT1-UTC values

        Real ut1MinusUtc_A;       ///< [s] Bulletin A UT1-UTC
        Real ut1MinusUtcError_A;  ///< [s] Error in UT1-UTC
        Real lod_A;               ///< [ms] Bulletin A LOD (not always filled)
        Real lodError_A;          ///< [ms] Error in LOD (not always filled)

        char nutationFlag;  ///< IERS (I) or Prediction (P) flag for Bulletin A nutation values

        Real dx_A;           ///< [amsec] Bulletin A dX wrt IAU2000A Nutation, Free Core Nutation NOT Removed
        Real dxError_A;      ///< [amsec] Error in dX
        Real dy_A;           ///< [amsec] Bulletin A dY wrt IAU2000A Nutation, Free Core Nutation NOT Removed
        Real dyError_A;      ///< [amsec] Error in dY
        Real x_B;            ///< [asec] Bulletin B PM-x
        Real y_B;            ///< [asec] Bulletin B PM-y
        Real ut1MinusUtc_B;  ///< [s] Bulletin B UT1-UTC
        Real dx_B;           ///< [amsec] Bulletin B dX wrt IAU2000A Nutation
        Real dy_B;           ///< [amsec] Bulletin B dY wrt IAU2000A Nutation
    };

    friend std::ostream& operator<<(std::ostream& anOutputStream, const Finals2000A& aFinals2000A);

    /// @brief                  true if defined
    ///
    /// @return                 True if defined

    bool isDefined() const;

    /// @brief                  Access timestamp at which the BulletinA file was last modified
    ///
    /// @return                 Instant indicating when the file was last updated based on file modification time

    const Instant& accessLastModifiedTimestamp() const;

    /// @brief                  Get data interval
    ///
    /// @return                 Data Intervalt of Instants

    Interval getInterval() const;

    /// @brief                  Get polar motion at Instant
    ///
    /// @param                  [in] anInstant An Instant
    /// @return                 Polar motion

    Vector2d getPolarMotionAt(const Instant& anInstant) const;

    /// @brief                  Get UT1-UTC at Instant
    ///
    /// @param                  [in] anInstant An Instant
    /// @return                 UT1-UTC

    Real getUt1MinusUtcAt(const Instant& anInstant) const;

    /// @brief                  Get LOD (Length Of Day) at Instant
    ///
    /// @param                  [in] anInstant An Instant
    /// @return                 LOD

    Real getLodAt(const Instant& anInstant) const;

    /// @brief                  Get Data reading at instant
    ///
    /// @param                  [in] anInstant An Instant
    /// @return                 Data reading

    Finals2000A::Data getDataAt(const Instant& anInstant) const;

    /// @brief                  Undefined factory function
    ///
    /// @return                 Undefined Finals2000A object

    static Finals2000A Undefined();

    /// @brief                  Load Finals2000A from file
    ///
    /// @param                  [in] aFile A file
    /// @return                 Finals2000A object

    static Finals2000A Load(const filesystem::File& aFile);

   private:
    Instant lastModifiedTimestamp_;
    Interval span_;
    Map<Real, Finals2000A::Data> data_;

    Finals2000A();

    Pair<const Finals2000A::Data*, const Finals2000A::Data*> accessDataRange(const Instant& anInstant) const;
};

}  // namespace iers
}  // namespace provider
}  // namespace frame
}  // namespace coord
}  // namespace physics
}  // namespace ostk

#endif
