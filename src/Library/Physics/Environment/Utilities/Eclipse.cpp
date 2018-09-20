////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Environment/Utilities/Eclipse.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Environment/Utilities/Eclipse.hpp>
#include <Library/Physics/Environment/Object.hpp>

#include <Library/Mathematics/Geometry/3D/Objects/Segment.hpp>

#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{
namespace env
{
namespace utilities
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool                            isPositionInEclipse                         (   const   Position&                   aPosition,
                                                                                const   Environment&                anEnvironment                               )
{

    using library::core::types::Shared ;

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Segment ;

    using library::physics::env::Object ;

    if (!aPosition.isDefined())
    {
        throw library::core::error::runtime::Undefined("Position") ;
    }

    if (aPosition.accessFrame() != Frame::GCRF())
    {
        throw library::core::error::RuntimeError("Position has to be expressed in GCRF.") ;
    }

    if (!anEnvironment.isDefined())
    {
        throw library::core::error::runtime::Undefined("Environment") ;
    }

    const Shared<const Object> sunSPtr = anEnvironment.accessObjectWithName("Sun") ;

    const Segment sunToObjectSegment_GCRF = { Point::Vector(aPosition.getCoordinates()), Point::Vector(sunSPtr->getPositionIn(Frame::GCRF()).getCoordinates()) } ;

    const Object::Geometry sunToObjectGeometry = { sunToObjectSegment_GCRF, Frame::GCRF() } ;

    return anEnvironment.intersects(sunToObjectGeometry, { sunSPtr }) ;

}

Array<Interval>                 eclipseIntervalsAtPosition                  (   const   Interval&                   anAnalysisInterval,
                                                                                const   Position&                   aPosition,
                                                                                const   Environment&                anEnvironment                               )
{

    using library::core::types::Shared ;

    using library::math::geom::d3::objects::Segment ;

    using library::physics::time::Instant ;
    using library::physics::time::Duration ;
    using library::physics::env::Object ;

    if (!anAnalysisInterval.isDefined())
    {
        throw library::core::error::runtime::Undefined("Analysis interval") ;
    }
    
    if (!aPosition.isDefined())
    {
        throw library::core::error::runtime::Undefined("Position") ;
    }

    if (!anEnvironment.isDefined())
    {
        throw library::core::error::runtime::Undefined("Environment") ;
    }

    Environment environment = anEnvironment ;

    const Duration timeStep = Duration::Minutes(1.0) ; // [TBM] Param

    Array<Interval> eclipseIntervals = Array<Interval>::Empty() ;

    Instant eclipseStartInstant = Instant::Undefined() ;
    Instant eclipseEndInstant = Instant::Undefined() ;

    for (const auto& instant : anAnalysisInterval.generateGrid(timeStep))
    {

        environment.setInstant(instant) ;

        const Position position_GCRF = aPosition.inFrame(Frame::GCRF(), instant) ;

        const bool inEclipse = isPositionInEclipse(position_GCRF, environment) ;

        if (inEclipse && (!eclipseStartInstant.isDefined()))
        {
            eclipseStartInstant = instant ;
        }
        else if ((!inEclipse) && eclipseStartInstant.isDefined())
        {
            
            eclipseIntervals.add(Interval::Closed(eclipseStartInstant, eclipseEndInstant)) ;

            eclipseStartInstant = Instant::Undefined() ;
            eclipseEndInstant = Instant::Undefined() ;
            
        }

        eclipseEndInstant = instant ;

    }

    if (eclipseStartInstant.isDefined())
    {
        eclipseIntervals.add(Interval::Closed(eclipseStartInstant, eclipseEndInstant)) ;
    }

    return eclipseIntervals ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////