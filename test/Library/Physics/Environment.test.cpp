////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Environment.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Environment.hpp>
#include <Library/Physics/Time/Interval.hpp>
#include <Library/Physics/Time/Duration.hpp>
#include <Library/Physics/Time/Instant.hpp>
#include <Library/Physics/Time/DateTime.hpp>
#include <Library/Physics/Time/Scale.hpp>

#include <Library/Core/Types/Weak.hpp>
#include <Library/Core/Types/Shared.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Physics_Environment, Default)
{

    using library::core::types::Shared ;
    using library::core::types::Weak ;
    using library::physics::time::Scale ;
    using library::physics::time::DateTime ;
    using library::physics::time::Instant ;
    using library::physics::time::Duration ;
    using library::physics::time::Interval ;
    using library::physics::coord::Frame ;
    using library::physics::Environment ;
    using library::physics::env::Object ;

    {

        Environment environment = Environment::Default() ;

        EXPECT_TRUE(environment.isDefined()) ;

        const Instant startInstant = Instant::DateTime(DateTime::Parse("2018-01-01 00:00:00"), Scale::UTC) ;
        const Instant endInstant = Instant::DateTime(DateTime::Parse("2018-01-02 00:00:00"), Scale::UTC) ;
        const Duration stepDuration = Duration::Hours(1.0) ;

        Weak<const Object> earthWPtr = environment.accessObjectWithName("Earth") ;

        EXPECT_FALSE(earthWPtr.expired()) ;

        if (auto earthSPtr = earthWPtr.lock())
        {

            for (const auto& instant : Interval::Closed(startInstant, endInstant).generateGrid(stepDuration))
            {

                environment.setInstant(instant) ;

                std::cout << "axes B = " << std::endl << earthSPtr->getAxesIn(Frame::GCRF()) << std::endl ;

                // FAIL() ;

            }

        }

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////