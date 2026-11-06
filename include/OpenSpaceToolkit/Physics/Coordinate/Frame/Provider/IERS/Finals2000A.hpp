/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_Finals2000A__
#define __OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_Finals2000A__

#include <optional>

#include <OpenSpaceToolkit/Core/Container/Map.hpp>
#include <OpenSpaceToolkit/Core/Container/Pair.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>

#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

#include <OpenSpaceToolkit/Physics/Time/Date.hpp>
#include <OpenSpaceToolkit/Physics/Time/Duration.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Time/Interval.hpp>

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

namespace filesystem = ostk::core::filesystem;

using ostk::core::container::Map;
using ostk::core::container::Pair;
using ostk::core::filesystem::File;

using ostk::mathematics::object::Vector2d;

using ostk::physics::time::Date;
using ostk::physics::time::Duration;
using ostk::physics::time::Instant;
using ostk::physics::time::Interval;

/// @brief Standard Rapid EOP Data since 01. January 1992 (IAU2000)
///
/// This file (updated weekly) is the complete Earth orientation data set, since 1 January
/// 1992 with 1 year of predictions. The nutation series in dX and dY uses the IAU 2000A Nutation Theory.
///
/// @ref https://www.iers.org/IERS/EN/DataProducts/EarthOrientationData/eop.html -> finals.data (IAU2000)
class Finals2000A
{
   public:
    /// @brief One line of the file. Real-valued fields that are empty in the file are std::nullopt.
    struct Data
    {
        int year;   ///< Year (to get true calendar year, add 1900 for MJD <= 51543 or add 2000 for MJD >= 51544)
        int month;  ///< Month number
        int day;    ///< Day of month

        double mjd;  ///< Fractional Modified Julian Date (MJD UTC)

        char polarMotionflag;  ///< IERS (I) or Prediction (P) flag for Bulletin A polar motion values

        std::optional<double> x_A;       ///< [asec] Bulletin A PM-x
        std::optional<double> xError_A;  ///< [asec] Error in PM-x
        std::optional<double> y_A;       ///< [asec] Bulletin A PM-y
        std::optional<double> yError_A;  ///< [asec] Error in PM-y

        char ut1MinusUtcFlag;  ///< IERS (I) or Prediction (P) flag for Bulletin A UT1-UTC values

        std::optional<double> ut1MinusUtc_A;       ///< [s] Bulletin A UT1-UTC
        std::optional<double> ut1MinusUtcError_A;  ///< [s] Error in UT1-UTC
        std::optional<double> lod_A;               ///< [ms] Bulletin A LOD (not always filled)
        std::optional<double> lodError_A;          ///< [ms] Error in LOD (not always filled)

        char nutationFlag;  ///< IERS (I) or Prediction (P) flag for Bulletin A nutation values

        std::optional<double> dx_A;  ///< [amsec] Bulletin A dX wrt IAU2000A Nutation, Free Core Nutation NOT Removed
        std::optional<double> dxError_A;  ///< [amsec] Error in dX
        std::optional<double> dy_A;  ///< [amsec] Bulletin A dY wrt IAU2000A Nutation, Free Core Nutation NOT Removed
        std::optional<double> dyError_A;      ///< [amsec] Error in dY
        std::optional<double> x_B;            ///< [asec] Bulletin B PM-x
        std::optional<double> y_B;            ///< [asec] Bulletin B PM-y
        std::optional<double> ut1MinusUtc_B;  ///< [s] Bulletin B UT1-UTC
        std::optional<double> dx_B;           ///< [amsec] Bulletin B dX wrt IAU2000A Nutation
        std::optional<double> dy_B;           ///< [amsec] Bulletin B dY wrt IAU2000A Nutation
    };

    /// @brief Output stream operator.
    ///
    /// @code
    ///     std::cout << finals2000A;
    /// @endcode
    ///
    /// @param [in] anOutputStream An output stream
    /// @param [in] aFinals2000A A Finals2000A
    /// @return A reference to the output stream
    friend std::ostream& operator<<(std::ostream& anOutputStream, const Finals2000A& aFinals2000A);

    /// @brief Get timestamp at which the BulletinA file was last modified
    ///
    /// @code
    ///     const Instant& timestamp = finals2000A.getLastModifiedTimestamp();
    /// @endcode
    ///
    /// @return Instant indicating when the file was last updated based on file modification time
    const Instant& getLastModifiedTimestamp() const;

    /// @brief Get data interval
    ///
    /// @code
    ///     const Interval& interval = finals2000A.getInterval();
    /// @endcode
    ///
    /// @return Const reference to data Interval of Instants
    const Interval& getInterval() const;

    /// @brief Get polar motion at Instant
    ///
    /// @code
    ///     Vector2d polarMotion = finals2000A.getPolarMotionAt(anInstant);
    /// @endcode
    ///
    /// @param [in] anInstant An Instant
    /// @return Polar motion
    Vector2d getPolarMotionAt(const Instant& anInstant) const;

    /// @brief Get UT1-UTC at Instant
    ///
    /// @code
    ///     std::optional<double> ut1MinusUtc = finals2000A.getUt1MinusUtcAt(anInstant);
    /// @endcode
    ///
    /// @param [in] anInstant An Instant
    /// @return UT1-UTC [s], or std::nullopt if it is not tabulated at the Instant
    std::optional<double> getUt1MinusUtcAt(const Instant& anInstant) const;

    /// @brief Get LOD (Length Of Day) at Instant
    ///
    /// @code
    ///     std::optional<double> lod = finals2000A.getLodAt(anInstant);
    /// @endcode
    ///
    /// @param [in] anInstant An Instant
    /// @return LOD [ms], or std::nullopt if it is not tabulated at the Instant
    std::optional<double> getLodAt(const Instant& anInstant) const;

    /// @brief Get Data reading at instant
    ///
    /// @code
    ///     Finals2000A::Data data = finals2000A.getDataAt(anInstant);
    /// @endcode
    ///
    /// @param [in] anInstant An Instant
    /// @return Data reading
    Finals2000A::Data getDataAt(const Instant& anInstant) const;

    /// @brief Load Finals2000A from file
    ///
    /// @code
    ///     Finals2000A finals2000A = Finals2000A::Load(file);
    /// @endcode
    ///
    /// @param [in] aFile A file
    /// @return Finals2000A object
    static Finals2000A Load(const filesystem::File& aFile);

   private:
    Instant lastModifiedTimestamp_;
    Interval span_;
    Map<double, Finals2000A::Data> data_;

    Finals2000A();

    Pair<const Finals2000A::Data*, const Finals2000A::Data*> accessDataRange(const Instant& anInstant) const;
};

}  // namespace iers
}  // namespace provider
}  // namespace frame
}  // namespace coordinate
}  // namespace physics
}  // namespace ostk

#endif
