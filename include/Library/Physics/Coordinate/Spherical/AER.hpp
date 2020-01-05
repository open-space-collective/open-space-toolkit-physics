////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           OpenSpaceToolkit/Physics/Coordinate/Spherical/AER.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OpenSpaceToolkit_Physics_Coordinate_Spherical_AER__
#define __OpenSpaceToolkit_Physics_Coordinate_Spherical_AER__

#include <OpenSpaceToolkit/Physics/Coordinate/Position.hpp>
#include <OpenSpaceToolkit/Physics/Units/Derived/Angle.hpp>
#include <OpenSpaceToolkit/Physics/Units/Length.hpp>

#include <Library/Core/Types/String.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ostk
{
namespace physics
{
namespace coord
{
namespace spherical
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using ostk::core::types::String ;

using ostk::math::obj::Vector3d ;

using ostk::physics::units::Angle ;
using ostk::physics::units::Length ;
using ostk::physics::coord::Position ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Azimuth - Elevation - Range (AER)

class AER
{

    public:

                                AER                                         (   const   Angle&                      anAzimuth,
                                                                                const   Angle&                      anElevation,
                                                                                const   Length&                     aRange                                      ) ;

        bool                    operator ==                                 (   const   AER&                        anAER                                       ) const ;

        bool                    operator !=                                 (   const   AER&                        anAER                                       ) const ;

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   AER&                        anAER                                       ) ;

        bool                    isDefined                                   ( ) const ;

        Angle                   getAzimuth                                  ( ) const ;

        Angle                   getElevation                                ( ) const ;

        Length                  getRange                                    ( ) const ;

        Vector3d                toVector                                    ( ) const ;

        Vector3d                toCartesian                                 ( ) const ; // [TBI]

        String                  toString                                    ( ) const ;

        static AER              Undefined                                   ( ) ;

        static AER              Vector                                      (   const   Vector3d&                   aVector                                     ) ;

        /// @brief              AER from the relative position between two positions
        ///
        /// @param              [in] aFromPosition A FROM position
        /// @param              [in] aToPosition A TO position
        /// @param              [in] (optional) isZNegative If true, elevation is measured positive toward the -Z axis

        static AER              FromPositionToPosition                      (   const   Position&                   aFromPosition,
                                                                                const   Position&                   aToPosition,
                                                                                const   bool                        isZNegative                                 =   true ) ;

    private:

        Angle                   azimuth_ ;
        Angle                   elevation_ ;
        Length                  range_ ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
