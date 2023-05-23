/// Apache License 2.0 

#include <OpenSpaceToolkit/Physics/Environment/Ephemerides/SPICE.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Objects/CelestialBodies/Moon.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/Static.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ostk
{
namespace physics
{
namespace env
{
namespace obj
{
namespace celest
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using ostk::physics::units::Mass ;
using ostk::physics::units::Time ;
using ostk::physics::units::Angle ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Derived                         Moon::GravitationalParameter                    =       { 4902.8000e9, Derived::Unit::GravitationalParameter(Length::Unit::Meter, Time::Unit::Second) } ;
Length                          Moon::EquatorialRadius                          =       Length::Meters(1738.14e3) ;
Real                            Moon::Flattening                                =       0.00125 ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Moon::Moon                                  (   const   Shared<Ephemeris>&          anEphemeris,
                                                                                const   MoonGravitationalModel::Type& aGravitationalModelType,
                                                                                const   Instant&                    anInstant                                   )
                                :   Celestial
                                    (
                                        "Moon",
                                        Celestial::Type::Moon,
                                        Moon::GravitationalParameter,
                                        Moon::EquatorialRadius,
                                        Moon::Flattening,
                                        0.0,
                                        0.0,
                                        anEphemeris,
                                        std::make_shared<MoonGravitationalModel>(aGravitationalModelType),
                                        nullptr,
                                        nullptr,
                                        anInstant,
                                        Moon::Geometry(anEphemeris->accessFrame())
                                    )
{

}

                                Moon::~Moon                                 ( )
{

}

Moon*                           Moon::clone                                 ( ) const
{
    return new Moon(*this) ;
}

Moon                            Moon::Default                               ( )
{
    return Moon::Spherical() ;
}

Moon                            Moon::Spherical                             ( )
{

    using ostk::physics::env::ephem::SPICE ;

    return
    {
        std::make_shared<SPICE>(SPICE::Object::Moon),
        MoonGravitationalModel::Type::Spherical,
        Instant::J2000()
    } ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Object::Geometry                Moon::Geometry                              (   const   Shared<const Frame>&        aFrame                                      )
{

    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::trf::rot::Quaternion ;

    const Real equatorialRadius_m = Moon::EquatorialRadius.inMeters() ;
    const Real polarRadius_m = equatorialRadius_m * (1.0 - Moon::Flattening) ;

    const Ellipsoid ellipsoid = { Point::Origin(), equatorialRadius_m, equatorialRadius_m, polarRadius_m, Quaternion::Unit() } ;

    return { ellipsoid, aFrame } ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
