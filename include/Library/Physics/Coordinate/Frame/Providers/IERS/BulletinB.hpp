////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Coordinate/Frame/Providers/IERS/BulletinB.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Physics_Coordinate_Frame_Providers_IERS_BulletinB__
#define __Library_Physics_Coordinate_Frame_Providers_IERS_BulletinB__

#include <Library/Physics/Time/Interval.hpp>
#include <Library/Physics/Time/Duration.hpp>
#include <Library/Physics/Time/Instant.hpp>
#include <Library/Physics/Time/Date.hpp>

#include <Library/Core/FileSystem/File.hpp>
#include <Library/Core/Containers/Map.hpp>
#include <Library/Core/Types/Real.hpp>
#include <Library/Core/Types/Integer.hpp>

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

namespace fs = library::core::fs ;

using library::core::types::Integer ;
using library::core::types::Real ;
using library::core::ctnr::Map ;
using library::core::fs::File ;

using library::physics::time::Date ;
using library::physics::time::Instant ;
using library::physics::time::Duration ;
using library::physics::time::Interval ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      IERS Bulletin B
///
///                             IERS Bulletin B provides current information on the Earth’s orientation in the IERS Reference System.
///                             This includes Universal Time, coordinates of the terrestrial pole, and celestial pole offsets. 
///                             IERS Bulletin B consists of 5 sections:
///                             
///                             Section 1: 
///                             Daily final values at 0:00 UT of x, y, UT1-UTC, dX, dY, and their uncertainties. Time span: one month with final values, one month with preliminary values.
///                             
///                             Section 2: 
///                             Daily final values at 0:00 UT of celestial pole offsets dPsi and dEps in the IAU 1980 system and their uncertainties.
///                             
///                             Section 3: 
///                             Earth angular velocity (daily estimates of LOD and OMEGA with their uncertainties).
///                             
///                             Section 4: 
///                             Information on the time scales and announcement of occurring leap seconds.
///                             
///                             Section 5: 
///                             Average formal precision of the individual and combined series contributing or not to the combination and their agreement with the combination.
///
/// @ref                        https://www.iers.org/IERS/EN/Publications/Bulletins/bulletins.html

class BulletinB
{

    public:

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   BulletinB&                  aBulletinB                                  ) ;

        bool                    isDefined                                   ( ) const ;

        static BulletinB        Undefined                                   ( ) ;

        static BulletinB        Load                                        (   const   fs::File&                   aFile                                       ) ;

    private:

        Date                    releaseDate_ ;

                                BulletinB                                   ( ) ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////