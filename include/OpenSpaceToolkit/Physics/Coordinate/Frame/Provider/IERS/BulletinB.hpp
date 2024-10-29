/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_BulletinB__
#define __OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_BulletinB__

#include <OpenSpaceToolkit/Core/Container/Map.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>
#include <OpenSpaceToolkit/Core/Type/Integer.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>

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
using ostk::core::filesystem::File;
using ostk::core::type::Integer;
using ostk::core::type::Real;

using ostk::physics::time::Date;
using ostk::physics::time::Duration;
using ostk::physics::time::Instant;
using ostk::physics::time::Interval;

/// @brief                      IERS Bulletin B
///
///                             IERS Bulletin B provides current information on the Earth’s orientation in the IERS
///                             Reference System. This includes Universal Time, coordinates of the terrestrial pole, and
///                             celestial pole offsets. IERS Bulletin B consists of 5 sections:
///
///                             Section 1:
///                             Daily final values at 0:00 UT of x, y, UT1-UTC, dX, dY, and their uncertainties. Time
///                             span: one month with final values, one month with preliminary values.
///
///                             Section 2:
///                             Daily final values at 0:00 UT of celestial pole offsets dPsi and dEps in the IAU 1980
///                             system and their uncertainties.
///
///                             Section 3:
///                             Earth angular velocity (daily estimates of LOD and OMEGA with their uncertainties).
///
///                             Section 4:
///                             Information on the time scales and announcement of occurring leap seconds.
///
///                             Section 5:
///                             Average formal precision of the individual and combined series contributing or not to
///                             the combination and their agreement with the combination.
///
/// @ref                        https://www.iers.org/IERS/EN/Publications/Bulletins/bulletins.html

class BulletinB
{
   public:
    friend std::ostream& operator<<(std::ostream& anOutputStream, const BulletinB& aBulletinB);

    /// @brief              true if defined
    ///
    /// @return             True if defined.

    bool isDefined() const;

    /// @brief              Undefined factory function
    ///
    /// @return             Undefined Bulletin B object.

    static BulletinB Undefined();

    /// @brief              Load Bulletin B from file
    ///
    /// @param              [in] aFile A file.
    /// @return             Bulletin B object.

    static BulletinB Load(const filesystem::File& aFile);

   private:
    Date releaseDate_;

    BulletinB();
};

}  // namespace iers
}  // namespace provider
}  // namespace frame
}  // namespace coordinate
}  // namespace physics
}  // namespace ostk

#endif
