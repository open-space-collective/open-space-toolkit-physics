////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/TOD.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/IERS/Manager.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/TOD.hpp>
#include <OpenSpaceToolkit/Physics/Time/DateTime.hpp>
#include <OpenSpaceToolkit/Physics/Time/Scale.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/RotationMatrix.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/RotationVector.hpp>

#include <OpenSpaceToolkit/Core/Containers/Triple.hpp>
#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

#include <Eigen/Dense>

#include <math.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using ostk::core::ctnr::Triple ;

using ostk::math::geom::d3::trf::rot::RotationVector ;

using ostk::physics::time::Scale ;
using IersManager = ostk::physics::coord::frame::provider::iers::Manager ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// an1  an2  an3  an4  an5        Ai            Bi         Ci            Di
//                  Units:  [0.0001"]  [0.0001"/JC]  [0.0001"]  [0.0001"/JC]

const std::array<std::array<double, 9>, 106> nut_coefs_1980 =
{{
    {  0.0,    0.0,    0.0,    0.0,    1.0,  -171996.0,       -174.2,    92025.0,           8.9 },
    {  0.0,    0.0,    2.0,   -2.0,    2.0,   -13187.0,         -1.6,     5736.0,          -3.1 },
    {  0.0,    0.0,    2.0,    0.0,    2.0,    -2274.0,         -0.2,      977.0,          -0.5 },
    {  0.0,    0.0,    0.0,    0.0,    2.0,     2062.0,          0.2,     -895.0,           0.5 },
    {  0.0,   -1.0,    0.0,    0.0,    0.0,    -1426.0,          3.4,       54.0,          -0.1 },
    {  1.0,    0.0,    0.0,    0.0,    0.0,      712.0,          0.1,       -7.0,           0.0 },
    {  0.0,    1.0,    2.0,   -2.0,    2.0,     -517.0,          1.2,      224.0,          -0.6 },
    {  0.0,    0.0,    2.0,    0.0,    1.0,     -386.0,         -0.4,      200.0,           0.0 },
    {  1.0,    0.0,    2.0,    0.0,    2.0,     -301.0,          0.0,      129.0,          -0.1 },
    {  0.0,   -1.0,    2.0,   -2.0,    2.0,      217.0,         -0.5,      -95.0,           0.3 },
    { -1.0,    0.0,    0.0,    2.0,    0.0,      158.0,          0.0,       -1.0,           0.0 },
    {  0.0,    0.0,    2.0,   -2.0,    1.0,      129.0,          0.1,      -70.0,           0.0 },
    { -1.0,    0.0,    2.0,    0.0,    2.0,      123.0,          0.0,      -53.0,           0.0 },
    {  1.0,    0.0,    0.0,    0.0,    1.0,       63.0,          0.1,      -33.0,           0.0 },
    {  0.0,    0.0,    0.0,    2.0,    0.0,       63.0,          0.0,       -2.0,           0.0 },
    { -1.0,    0.0,    2.0,    2.0,    2.0,      -59.0,          0.0,       26.0,           0.0 },
    { -1.0,    0.0,    0.0,    0.0,    1.0,      -58.0,         -0.1,       32.0,           0.0 },
    {  1.0,    0.0,    2.0,    0.0,    1.0,      -51.0,          0.0,       27.0,           0.0 },
    { -2.0,    0.0,    0.0,    2.0,    0.0,      -48.0,          0.0,        1.0,           0.0 },
    { -2.0,    0.0,    2.0,    0.0,    1.0,       46.0,          0.0,      -24.0,           0.0 },
    {  0.0,    0.0,    2.0,    2.0,    2.0,      -38.0,          0.0,       16.0,           0.0 },
    {  2.0,    0.0,    2.0,    0.0,    2.0,      -31.0,          0.0,       13.0,           0.0 },
    {  2.0,    0.0,    0.0,    0.0,    0.0,       29.0,          0.0,       -1.0,           0.0 },
    {  1.0,    0.0,    2.0,   -2.0,    2.0,       29.0,          0.0,      -12.0,           0.0 },
    {  0.0,    0.0,    2.0,    0.0,    0.0,       26.0,          0.0,       -1.0,           0.0 },
    {  0.0,    0.0,    2.0,   -2.0,    0.0,      -22.0,          0.0,        0.0,           0.0 },
    { -1.0,    0.0,    2.0,    0.0,    1.0,       21.0,          0.0,      -10.0,           0.0 },
    {  0.0,    2.0,    0.0,    0.0,    0.0,       17.0,         -0.1,        0.0,           0.0 },
    {  0.0,    2.0,    2.0,   -2.0,    2.0,      -16.0,          0.1,        7.0,           0.0 },
    { -1.0,    0.0,    0.0,    2.0,    1.0,       16.0,          0.0,       -8.0,           0.0 },
    {  0.0,    1.0,    0.0,    0.0,    1.0,      -15.0,          0.0,        9.0,           0.0 },
    {  1.0,    0.0,    0.0,   -2.0,    1.0,      -13.0,          0.0,        7.0,           0.0 },
    {  0.0,   -1.0,    0.0,    0.0,    1.0,      -12.0,          0.0,        6.0,           0.0 },
    {  2.0,    0.0,   -2.0,    0.0,    0.0,       11.0,          0.0,        0.0,           0.0 },
    { -1.0,    0.0,    2.0,    2.0,    1.0,      -10.0,          0.0,        5.0,           0.0 },
    {  1.0,    0.0,    2.0,    2.0,    2.0,       -8.0,          0.0,        3.0,           0.0 },
    {  0.0,   -1.0,    2.0,    0.0,    2.0,       -7.0,          0.0,        3.0,           0.0 },
    {  0.0,    0.0,    2.0,    2.0,    1.0,       -7.0,          0.0,        3.0,           0.0 },
    {  1.0,    1.0,    0.0,   -2.0,    0.0,       -7.0,          0.0,        0.0,           0.0 },
    {  0.0,    1.0,    2.0,    0.0,    2.0,        7.0,          0.0,       -3.0,           0.0 },
    { -2.0,    0.0,    0.0,    2.0,    1.0,       -6.0,          0.0,        3.0,           0.0 },
    {  0.0,    0.0,    0.0,    2.0,    1.0,       -6.0,          0.0,        3.0,           0.0 },
    {  2.0,    0.0,    2.0,   -2.0,    2.0,        6.0,          0.0,       -3.0,           0.0 },
    {  1.0,    0.0,    0.0,    2.0,    0.0,        6.0,          0.0,        0.0,           0.0 },
    {  1.0,    0.0,    2.0,   -2.0,    1.0,        6.0,          0.0,       -3.0,           0.0 },
    {  0.0,    0.0,    0.0,   -2.0,    1.0,       -5.0,          0.0,        3.0,           0.0 },
    {  0.0,   -1.0,    2.0,   -2.0,    1.0,       -5.0,          0.0,        3.0,           0.0 },
    {  2.0,    0.0,    2.0,    0.0,    1.0,       -5.0,          0.0,        3.0,           0.0 },
    {  1.0,   -1.0,    0.0,    0.0,    0.0,        5.0,          0.0,        0.0,           0.0 },
    {  1.0,    0.0,    0.0,   -1.0,    0.0,       -4.0,          0.0,        0.0,           0.0 },
    {  0.0,    0.0,    0.0,    1.0,    0.0,       -4.0,          0.0,        0.0,           0.0 },
    {  0.0,    1.0,    0.0,   -2.0,    0.0,       -4.0,          0.0,        0.0,           0.0 },
    {  1.0,    0.0,   -2.0,    0.0,    0.0,        4.0,          0.0,        0.0,           0.0 },
    {  2.0,    0.0,    0.0,   -2.0,    1.0,        4.0,          0.0,       -2.0,           0.0 },
    {  0.0,    1.0,    2.0,   -2.0,    1.0,        4.0,          0.0,       -2.0,           0.0 },
    {  1.0,    1.0,    0.0,    0.0,    0.0,       -3.0,          0.0,        0.0,           0.0 },
    {  1.0,   -1.0,    0.0,   -1.0,    0.0,       -3.0,          0.0,        0.0,           0.0 },
    { -1.0,   -1.0,    2.0,    2.0,    2.0,       -3.0,          0.0,        1.0,           0.0 },
    {  0.0,   -1.0,    2.0,    2.0,    2.0,       -3.0,          0.0,        1.0,           0.0 },
    {  1.0,   -1.0,    2.0,    0.0,    2.0,       -3.0,          0.0,        1.0,           0.0 },
    {  3.0,    0.0,    2.0,    0.0,    2.0,       -3.0,          0.0,        1.0,           0.0 },
    { -2.0,    0.0,    2.0,    0.0,    2.0,       -3.0,          0.0,        1.0,           0.0 },
    {  1.0,    0.0,    2.0,    0.0,    0.0,        3.0,          0.0,        0.0,           0.0 },
    { -1.0,    0.0,    2.0,    4.0,    2.0,       -2.0,          0.0,        1.0,           0.0 },
    {  1.0,    0.0,    0.0,    0.0,    2.0,       -2.0,          0.0,        1.0,           0.0 },
    { -1.0,    0.0,    2.0,   -2.0,    1.0,       -2.0,          0.0,        1.0,           0.0 },
    {  0.0,   -2.0,    2.0,   -2.0,    1.0,       -2.0,          0.0,        1.0,           0.0 },
    { -2.0,    0.0,    0.0,    0.0,    1.0,       -2.0,          0.0,        1.0,           0.0 },
    {  2.0,    0.0,    0.0,    0.0,    1.0,        2.0,          0.0,       -1.0,           0.0 },
    {  3.0,    0.0,    0.0,    0.0,    0.0,        2.0,          0.0,        0.0,           0.0 },
    {  1.0,    1.0,    2.0,    0.0,    2.0,        2.0,          0.0,       -1.0,           0.0 },
    {  0.0,    0.0,    2.0,    1.0,    2.0,        2.0,          0.0,       -1.0,           0.0 },
    {  1.0,    0.0,    0.0,    2.0,    1.0,       -1.0,          0.0,        0.0,           0.0 },
    {  1.0,    0.0,    2.0,    2.0,    1.0,       -1.0,          0.0,        1.0,           0.0 },
    {  1.0,    1.0,    0.0,   -2.0,    1.0,       -1.0,          0.0,        0.0,           0.0 },
    {  0.0,    1.0,    0.0,    2.0,    0.0,       -1.0,          0.0,        0.0,           0.0 },
    {  0.0,    1.0,    2.0,   -2.0,    0.0,       -1.0,          0.0,        0.0,           0.0 },
    {  0.0,    1.0,   -2.0,    2.0,    0.0,       -1.0,          0.0,        0.0,           0.0 },
    {  1.0,    0.0,   -2.0,    2.0,    0.0,       -1.0,          0.0,        0.0,           0.0 },
    {  1.0,    0.0,   -2.0,   -2.0,    0.0,       -1.0,          0.0,        0.0,           0.0 },
    {  1.0,    0.0,    2.0,   -2.0,    0.0,       -1.0,          0.0,        0.0,           0.0 },
    {  1.0,    0.0,    0.0,   -4.0,    0.0,       -1.0,          0.0,        0.0,           0.0 },
    {  2.0,    0.0,    0.0,   -4.0,    0.0,       -1.0,          0.0,        0.0,           0.0 },
    {  0.0,    0.0,    2.0,    4.0,    2.0,       -1.0,          0.0,        0.0,           0.0 },
    {  0.0,    0.0,    2.0,   -1.0,    2.0,       -1.0,          0.0,        0.0,           0.0 },
    { -2.0,    0.0,    2.0,    4.0,    2.0,       -1.0,          0.0,        1.0,           0.0 },
    {  2.0,    0.0,    2.0,    2.0,    2.0,       -1.0,          0.0,        0.0,           0.0 },
    {  0.0,   -1.0,    2.0,    0.0,    1.0,       -1.0,          0.0,        0.0,           0.0 },
    {  0.0,    0.0,   -2.0,    0.0,    1.0,       -1.0,          0.0,        0.0,           0.0 },
    {  0.0,    0.0,    4.0,   -2.0,    2.0,        1.0,          0.0,        0.0,           0.0 },
    {  0.0,    1.0,    0.0,    0.0,    2.0,        1.0,          0.0,        0.0,           0.0 },
    {  1.0,    1.0,    2.0,   -2.0,    2.0,        1.0,          0.0,       -1.0,           0.0 },
    {  3.0,    0.0,    2.0,   -2.0,    2.0,        1.0,          0.0,        0.0,           0.0 },
    { -2.0,    0.0,    2.0,    2.0,    2.0,        1.0,          0.0,       -1.0,           0.0 },
    { -1.0,    0.0,    0.0,    0.0,    2.0,        1.0,          0.0,       -1.0,           0.0 },
    {  0.0,    0.0,   -2.0,    2.0,    1.0,        1.0,          0.0,        0.0,           0.0 },
    {  0.0,    1.0,    2.0,    0.0,    1.0,        1.0,          0.0,        0.0,           0.0 },
    { -1.0,    0.0,    4.0,    0.0,    2.0,        1.0,          0.0,        0.0,           0.0 },
    {  2.0,    1.0,    0.0,   -2.0,    0.0,        1.0,          0.0,        0.0,           0.0 },
    {  2.0,    0.0,    0.0,    2.0,    0.0,        1.0,          0.0,        0.0,           0.0 },
    {  2.0,    0.0,    2.0,   -2.0,    1.0,        1.0,          0.0,       -1.0,           0.0 },
    {  2.0,    0.0,   -2.0,    0.0,    1.0,        1.0,          0.0,        0.0,           0.0 },
    {  1.0,   -1.0,    0.0,   -2.0,    0.0,        1.0,          0.0,        0.0,           0.0 },
    { -1.0,    0.0,    0.0,    1.0,    1.0,        1.0,          0.0,        0.0,           0.0 },
    { -1.0,   -1.0,    0.0,    2.0,    1.0,        1.0,          0.0,        0.0,           0.0 },
    {  0.0,    1.0,    0.0,    1.0,    0.0,        1.0,          0.0,        0.0,           0.0 }
}} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Triple<Angle, Angle, Angle>     computeFK5Nutation                          (   const   Instant&                    anInstant                                   )
{

    // Mean obliquity of the ecliptic.
    // Nutation in obliquity of the ecliptic.
    // Nutation in longitude.

    // Compute the Julian Centuries.

    const double JD_TT = anInstant.getJulianDate(Scale::TT) ;
    const double JD_J2000 = 2451545.0 ;
    const double T_TT = (JD_TT - JD_J2000) / 36525.0 ;

    // Auxiliary variables

    const double d2r = M_PI / 180.0 ;

    // Mean obliquity of the ecliptic

    // Compute the mean obliquity of the ecliptic [°].
    double me_1980 = 23.439291 + (-0.0130042 * T_TT) + (-1.64e-7 * T_TT * T_TT) + (5.04e-7 * T_TT * T_TT * T_TT) ;
    me_1980 = fmod(me_1980, 360.0) * d2r ; // Reduce to the interval [0, 2π]°.

    // Delaunay parameters of the Sun and Moon

    // Evaluate the Delaunay parameters associated with the Moon and the Sun in the interval [0,2π]°.

    // The parameters here were updated as stated in the errata [2].
    const double r = 360.0 ;

    double M_m = +134.96298139 + (+(1325.0 * r + 198.8673981) * T_TT) + (+0.0086972 * T_TT * T_TT) + (+1.78e-5 * T_TT * T_TT * T_TT) ;
    M_m = fmod(M_m, 360.0) * d2r ;

    double M_s = +357.52772333 + (+(99.0 * r + 359.0503400) * T_TT) + (-0.0001603 * T_TT * T_TT) + (-3.3e-6 * T_TT * T_TT * T_TT) ;
    M_s = fmod(M_s, 360.0) * d2r ;

    double u_Mm = +93.27191028 + (+(1342.0 * r + 82.0175381) * T_TT) + (-0.0036825 * T_TT * T_TT) + (+3.1e-6 * T_TT * T_TT * T_TT) ;
    u_Mm = fmod(u_Mm, 360.0) * d2r ;

    double D_s = +297.85036306 + (+(1236.0 * r + 307.1114800) * T_TT) + (-0.0019142 * T_TT * T_TT) + (+5.3e-6 * T_TT * T_TT * T_TT) ;
    D_s = fmod(D_s, 360.0) * d2r ;

    double O_m = +125.04452222 + (-(5.0 * r + 134.1362608) * T_TT) + (+0.0020708 * T_TT * T_TT) + (+2.2e-6 * T_TT * T_TT * T_TT) ;
    O_m = fmod(O_m, 360.0) * d2r ;

    // Nutation in longitude and obliquity

    // Compute the nutation in the longitude and in obliquity.

    double dpsi_1980 = 0.0 ;
    double de_1980 = 0.0 ;

    const size_t n_max = 106 ;

    for (size_t i = 0; i < n_max; i++)
    {

        const double an1 = nut_coefs_1980[i][0] ;
        const double an2 = nut_coefs_1980[i][1] ;
        const double an3 = nut_coefs_1980[i][2] ;
        const double an4 = nut_coefs_1980[i][3] ;
        const double an5 = nut_coefs_1980[i][4] ;
        const double Ai  = nut_coefs_1980[i][5] ;
        const double Bi  = nut_coefs_1980[i][6] ;
        const double Ci  = nut_coefs_1980[i][7] ;
        const double Di  = nut_coefs_1980[i][8] ;

        const double a_pi = an1 * M_m + an2 * M_s + an3 * u_Mm + an4 * D_s + an5 * O_m ;

        const double sin_a_pi = std::sin(a_pi) ;
        const double cos_a_pi = std::cos(a_pi) ;

        dpsi_1980 += (Ai + Bi * T_TT) * sin_a_pi ;
        de_1980 += (Ci + Di * T_TT) * cos_a_pi ;

    }

    // The nutation coefficients in `nut_coefs_1980` lead to angles with unit 0.0001". Hence, we must convert to [rad].

    dpsi_1980 *= (0.0001 / 3600.0 * d2r) ;
    de_1980 *= (0.0001 / 3600.0 * d2r) ;

    return { Angle::Radians(me_1980), Angle::Radians(de_1980), Angle::Radians(dpsi_1980) } ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                TOD::TOD                                    (   const   Instant&                    anEpoch,
                                                                                const   Angle&                      anObliquityCorrection,
                                                                                const   Angle&                      aLongitudeCorrection                        )
                                :   epoch_(anEpoch),
                                    obliquityCorrection_(anObliquityCorrection),
                                    longitudeCorrection_(aLongitudeCorrection)
{

}

                                TOD::~TOD                                   ( )
{

}

TOD*                            TOD::clone                                  ( ) const
{
    return new TOD(*this) ;
}

bool                            TOD::isDefined                              ( ) const
{
    return true ;
}

Instant                         TOD::getEpoch                               ( ) const
{
    return epoch_ ;
}

Transform                       TOD::getTransformAt                         (   const   Instant&                    anInstant                                   ) const
{

    using ostk::math::obj::Vector2d ;
    using ostk::math::geom::d3::trf::rot::RotationMatrix ;

    using ostk::physics::time::Scale ;
    using ostk::physics::time::DateTime ;
    using ostk::physics::units::Angle ;

    if (!anInstant.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant") ;
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("TOD") ;
    }

    // In a future release, use `IersManager` Bulletin A or Finals 2000 instead to obtain deps and dpsi corrections.
    // e.g.: const auto finals = IersManager::Get().getFinals2000AAt(epoch_).getDataAt(epoch_) ;

    const Angle& dde_1980 = obliquityCorrection_ ;
    const Angle& ddpsi_1980 = longitudeCorrection_ ;

    // Compute nutation angles

    auto [me_1980, de_1980, dpsi_1980] = computeFK5Nutation(epoch_) ;

    // Add the corrections to the nutation in obliquity and longitude.

    de_1980 += dde_1980 ;
    dpsi_1980 += ddpsi_1980 ;

    // Compute the obliquity.

    const Angle e_1980 = me_1980 + de_1980 ;

    const RotationMatrix dcm_MOD_TOD = RotationMatrix::RX(-me_1980) * RotationMatrix::RZ(dpsi_1980) * RotationMatrix::RX(e_1980) ;

    const Vector3d x_TOD_MOD = { 0.0, 0.0, 0.0 } ;
    const Vector3d v_TOD_MOD = { 0.0, 0.0, 0.0 } ;

    const Quaternion q_TOD_MOD = Quaternion::RotationMatrix(dcm_MOD_TOD).conjugate().normalize().rectify() ;
    const Vector3d w_TOD_MOD_in_TOD = { 0.0, 0.0, 0.0 } ;

    return Transform::Passive(anInstant, x_TOD_MOD, v_TOD_MOD, q_TOD_MOD, w_TOD_MOD_in_TOD) ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
