////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Environment/Objects/CelestialBodies/Earth.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Environment/Ephemerides/Analytical.hpp>
#include <Library/Physics/Environment/Objects/CelestialBodies/Earth.hpp>
#include <Library/Physics/Coordinate/Frame.hpp>

#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
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

using library::physics::units::Mass ;
using library::physics::units::Time ;
using library::physics::units::Angle ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static const Derived::Unit      GravitationalParameterSIUnit                    =   Derived::Unit::GravitationalParameter(Length::Unit::Meter, Time::Unit::Second) ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// http://jules.unavco.org/Voyager/Anc/Earth/egm96_geoid_diff
// https://science.gsfc.nasa.gov/sed/content/uploadFiles/publication_files/EGM96_NASA-TP-1998-206861.pdf
// https://geographiclib.sourceforge.io/html/gravity.html
// http://help.agi.com/stk/Content/gator/ab-cb.htm
// https://www.iers.org/SharedDocs/Publikationen/EN/IERS/Publications/tn/TechnNote36/tn36_079.pdf?__blob=publicationFile&v=1

// EGM2008

const Derived                   Earth::Models::EGM2008::GravitationalParameter  =       { 398600441500000.0, GravitationalParameterSIUnit } ;
const Length                    Earth::Models::EGM2008::EquatorialRadius        =       Length::Meters(6378137.0) ;
const Real                      Earth::Models::EGM2008::Flattening              =       1.0 / 298.257223563 ;
const Real                      Earth::Models::EGM2008::C20                     =       -4.84169317366974e-4 ;
const Real                      Earth::Models::EGM2008::J2                      =       -Earth::Models::EGM2008::C20 * std::sqrt(5.0) ;

// EGM96 + WGS84

const Derived                   Earth::Models::WGS84_EGM96::GravitationalParameter =      { 398600441800000.0, GravitationalParameterSIUnit } ;
const Length                    Earth::Models::WGS84_EGM96::EquatorialRadius    =       Length::Meters(6378137.0) ;
const Real                      Earth::Models::WGS84_EGM96::Flattening          =       1.0 / 298.257223563 ;
const Real                      Earth::Models::WGS84_EGM96::C20                 =       -4.841653717360e-04 ;
const Real                      Earth::Models::WGS84_EGM96::J2                  =       -Earth::Models::WGS84_EGM96::C20 * std::sqrt(5.0) ; // 0.0010826266835531513

// EGM96

const Derived                   Earth::Models::EGM96::GravitationalParameter    =       { 398600441500000.0, GravitationalParameterSIUnit } ;
const Length                    Earth::Models::EGM96::EquatorialRadius          =       Length::Meters(6378136.3) ;
const Real                      Earth::Models::EGM96::Flattening                =       1.0 / 298.257223563 ;
const Real                      Earth::Models::EGM96::C20                       =       -4.841653717360e-04 ;
const Real                      Earth::Models::EGM96::J2                        =       -Earth::Models::EGM96::C20 * std::sqrt(5.0) ;

// WGS84

const Derived                   Earth::Models::WGS84::GravitationalParameter    =       { 398600441800000.0, GravitationalParameterSIUnit } ;
const Length                    Earth::Models::WGS84::EquatorialRadius          =       Length::Meters(6378137.0) ;
const Real                      Earth::Models::WGS84::Flattening                =       1.0 / 298.257223563 ;
const Real                      Earth::Models::WGS84::C20                       =       -4.841668500000e-04 ;
const Real                      Earth::Models::WGS84::J2                        =       -Earth::Models::WGS84::C20 * std::sqrt(5.0) ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const Derived                   Earth::GravitationalParameter                   =       Earth::Models::EGM2008::GravitationalParameter ; // [TBR]
const Length                    Earth::EquatorialRadius                         =       Earth::Models::EGM2008::EquatorialRadius ; // [TBR]
const Real                      Earth::Flattening                               =       Earth::Models::EGM2008::Flattening ; // [TBR]
const Real                      Earth::C20                                      =       Earth::Models::EGM2008::C20 ; // [TBR]
const Real                      Earth::J2                                       =       Earth::Models::EGM2008::J2 ; // [TBR]

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Earth::Earth                                (   const   Derived&                    aGravitationalParameter,
                                                                                const   Length&                     anEquatorialRadius,
                                                                                const   Real&                       aFlattening,
                                                                                const   Real&                       aJ2,
                                                                                const   Shared<Ephemeris>&          anEphemeris,
                                                                                const   EarthGravitationalModel::Type& aGravitationalModelType,
                                                                                const   EarthMagneticModel::Type&   aMagneticModelType,
                                                                                const   Instant&                    anInstant                                   )
                                :   Celestial
                                    (
                                        "Earth",
                                        Celestial::Type::Earth,
                                        aGravitationalParameter,
                                        anEquatorialRadius,
                                        aFlattening,
                                        aJ2,
                                        anEphemeris,
                                        std::make_shared<EarthGravitationalModel>(aGravitationalModelType),
                                        std::make_shared<EarthMagneticModel>(aMagneticModelType),
                                        anInstant,
                                        Earth::Geometry(anEquatorialRadius, aFlattening, anEphemeris->accessFrame())
                                    )
{

}

                                Earth::~Earth                               ( )
{

}

Earth*                          Earth::clone                                ( ) const
{
    return new Earth(*this) ;
}

Earth                           Earth::Default                              ( )
{
    return Earth::EGM2008() ;
}

Earth                           Earth::EGM2008                              ( )
{

    using library::physics::coord::Frame ;
    using library::physics::env::ephem::Analytical ;

    const Shared<const Frame> earthFrameSPtr = Frame::ITRF() ;

    return
    {
        Earth::Models::EGM2008::GravitationalParameter,
        Earth::Models::EGM2008::EquatorialRadius,
        Earth::Models::EGM2008::Flattening,
        Earth::Models::EGM2008::J2,
        std::make_shared<Analytical>(earthFrameSPtr),
        EarthGravitationalModel::Type::EGM2008,
        EarthMagneticModel::Type::Dipole,
        Instant::J2000()
    } ;

}

Earth                           Earth::WGS84_EGM96                          ( )
{

    using library::physics::coord::Frame ;
    using library::physics::env::ephem::Analytical ;

    const Shared<const Frame> earthFrameSPtr = Frame::ITRF() ;

    return
    {
        Earth::Models::WGS84_EGM96::GravitationalParameter,
        Earth::Models::WGS84_EGM96::EquatorialRadius,
        Earth::Models::WGS84_EGM96::Flattening,
        Earth::Models::WGS84_EGM96::J2,
        std::make_shared<Analytical>(earthFrameSPtr),
        EarthGravitationalModel::Type::EGM96,
        EarthMagneticModel::Type::Dipole,
        Instant::J2000()
    } ;

}

Earth                           Earth::EGM96                                ( )
{

    using library::physics::coord::Frame ;
    using library::physics::env::ephem::Analytical ;

    const Shared<const Frame> earthFrameSPtr = Frame::ITRF() ;

    return
    {
        Earth::Models::EGM96::GravitationalParameter,
        Earth::Models::EGM96::EquatorialRadius,
        Earth::Models::EGM96::Flattening,
        Earth::Models::EGM96::J2,
        std::make_shared<Analytical>(earthFrameSPtr),
        EarthGravitationalModel::Type::EGM96,
        EarthMagneticModel::Type::Dipole,
        Instant::J2000()
    } ;

}

Earth                           Earth::WGS84                                ( )
{

    using library::physics::coord::Frame ;
    using library::physics::env::ephem::Analytical ;

    const Shared<const Frame> earthFrameSPtr = Frame::ITRF() ;

    return
    {
        Earth::Models::WGS84::GravitationalParameter,
        Earth::Models::WGS84::EquatorialRadius,
        Earth::Models::WGS84::Flattening,
        Earth::Models::WGS84::J2,
        std::make_shared<Analytical>(earthFrameSPtr),
        EarthGravitationalModel::Type::WGS84,
        EarthMagneticModel::Type::Dipole,
        Instant::J2000()
    } ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Object::Geometry                Earth::Geometry                             (   const   Length&                     anEquatorialRadius,
                                                                                const   Real&                       aFlattening,
                                                                                const   Shared<const Frame>&        aFrameSPtr                                  )
{

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::trf::rot::Quaternion ;

    const Real equatorialRadius_m = anEquatorialRadius.inMeters() ;
    const Real polarRadius_m = equatorialRadius_m * (1.0 - aFlattening) ;

    const Ellipsoid ellipsoid = { Point::Origin(), equatorialRadius_m, equatorialRadius_m, polarRadius_m, Quaternion::Unit() } ;

    return { ellipsoid, aFrameSPtr } ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////