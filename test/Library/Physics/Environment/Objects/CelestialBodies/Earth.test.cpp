////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Environment/Objects/CelestialBodies/Earth.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Environment/Objects/CelestialBodies/Earth.hpp>
#include <Library/Physics/Environment.hpp>
#include <Library/Physics/Coordinate/Spherical/LLA.hpp>
#include <Library/Physics/Time/Interval.hpp>
#include <Library/Physics/Time/Duration.hpp>
#include <Library/Physics/Time/Instant.hpp>
#include <Library/Physics/Time/DateTime.hpp>
#include <Library/Physics/Time/Scale.hpp>
#include <Library/Physics/Units/Length.hpp>

#include <Library/Mathematics/Geometry/Transformations/Rotations/RotationVector.hpp>
#include <Library/Mathematics/Geometry/Transformations/Rotations/Quaternion.hpp>
#include <Library/Mathematics/Geometry/3D/Intersection.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Pyramid.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Ellipsoid.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Polygon.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Segment.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/LineString.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Point.hpp>
#include <Library/Mathematics/Geometry/2D/Objects/Polygon.hpp>
#include <Library/Mathematics/Geometry/2D/Objects/Point.hpp>

#include <Library/Core/Containers/Map.hpp>
#include <Library/Core/Types/String.hpp>
#include <Library/Core/Types/Weak.hpp>
#include <Library/Core/Types/Shared.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Physics_Environment_Objects_CelestialBodies_Earth, Constructor)
{

    using library::physics::env::obj::celest::Earth ;

    {

        FAIL() ;

    }

}

TEST (Library_Physics_Environment_Objects_CelestialBodies_Earth, GetNEDFrameAt)
{

    using library::core::types::Shared ;

    using library::physics::units::Length ;
    using library::physics::units::Angle ;
    using library::physics::time::Instant ;
    using library::physics::time::Duration ;
    using library::physics::coord::spherical::LLA ;
    using library::physics::coord::Frame ;
    using library::physics::env::obj::celest::Earth ;

    {

        const Instant epoch = Instant::J2000() ;

        const Earth earth = Earth::Analytical(epoch) ;

        const LLA lla = { Angle::Degrees(0.0), Angle::Degrees(0.0), Length::Meters(0.0) } ;
        
        const Shared<const Frame> nedSPtr = earth.getNEDFrameAt(lla) ;

        std::cout << (*nedSPtr) << std::endl ;

        // std::cout << nedSPtr->getTransformTo(Frame::ITRF(), epoch) << std::endl ;
        // std::cout << nedSPtr->getTransformTo(Frame::ITRF(), epoch + Duration::Hours(12.0)) << std::endl ;

        // std::cout << nedSPtr->getTransformTo(earth.accessFrame(), epoch) << std::endl ;
        // std::cout << nedSPtr->getTransformTo(earth.accessFrame(), epoch + Duration::Hours(12.0)) << std::endl ;

        // std::cout << nedSPtr->getTransformTo(Frame::GCRF(), epoch) << std::endl ;
        // std::cout << nedSPtr->getTransformTo(Frame::GCRF(), epoch + Duration::Hours(12.0)) << std::endl ;

        std::cout << nedSPtr->getAxesIn(Frame::ITRF(), epoch) << std::endl ;
        std::cout << nedSPtr->getAxesIn(Frame::ITRF(), epoch + Duration::Hours(12.0)) << std::endl ;

        std::cout << nedSPtr->getAxesIn(earth.accessFrame(), epoch) << std::endl ;
        std::cout << nedSPtr->getAxesIn(earth.accessFrame(), epoch + Duration::Hours(12.0)) << std::endl ;

        std::cout << nedSPtr->getAxesIn(Frame::GCRF(), epoch) << std::endl ;
        std::cout << nedSPtr->getAxesIn(Frame::GCRF(), epoch + Duration::Hours(12.0)) << std::endl ;

    }

}

TEST (Library_Physics_Environment_Objects_CelestialBodies_Earth, Analytical)
{

    using library::physics::time::Instant ;
    using library::physics::env::obj::celest::Earth ;

    {

        const Instant epoch = Instant::J2000() ;

        EXPECT_NO_THROW(Earth::Analytical(epoch)) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////