/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/Exponential.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Objects/CelestialBodies/Earth.hpp>

namespace ostk
{
namespace physics
{
namespace environment
{
namespace atmospheric
{
namespace earth
{

using ostk::physics::coord::Frame;
using EarthCelestialBody = ostk::physics::env::obj::celest::Earth;
using EarthGravitational = ostk::physics::environment::gravitational::Earth;

Exponential::Exponential()
    : Model()
{
}

Exponential* Exponential::clone() const
{
    return new Exponential(*this);
}

bool Exponential::isDefined() const
{
    return true;
}

Real Exponential::getDensityAt(const Position& aPosition, const Instant& anInstant) const
{
    return this->getDensityAt(
        LLA::Cartesian(
            aPosition.inFrame(Frame::ITRF(), anInstant).accessCoordinates(),
            EarthGravitational::EGM2008Parameters.equatorialRadius_,
            EarthGravitational::EGM2008Parameters.flattening_
        ),
        anInstant
    );
}

Real Exponential::getDensityAt(const LLA& aLLA, const Instant& anInstant) const
{
    (void)anInstant;  // temporal invariance

    const Length h = aLLA.getAltitude();

    const Tuple<Real, Real, Real> densityBand = Exponential::DensityBandValues(h);

    const Real h_0 = std::get<0>(densityBand);
    const Real rho_0 = std::get<1>(densityBand);
    const Real H_0 = std::get<2>(densityBand);

    const Real rho = rho_0 * std::exp(-(h.inKilometers() - h_0) / H_0);

    return rho;
}

Tuple<Real, Real, Real> Exponential::DensityBandValues(const Length& anAltitude)
{
    // Reference values defined in Fundamentals of Astrodynamics and Applications by Vallado p. 534
    static const Array<Real> refHeights = {0.0,   25.0,  30.0,  40.0,  50.0,  60.0,  70.0,  80.0,  90.0,  100.0,
                                           110.0, 120.0, 130.0, 140.0, 150.0, 180.0, 200.0, 250.0, 300.0, 350.0,
                                           400.0, 450.0, 500.0, 600.0, 700.0, 800.0, 900.0, 1000.0};

    static const Array<Tuple<Real, Real>> densityBands = {
        // ref density [kg/m^3], scale height [km], ref height [km]
        {1.225, 7.249},       // 0.0
        {3.899e-2, 6.349},    // 25.0
        {1.774e-2, 6.682},    // 30.0
        {3.972e-3, 7.554},    // 40.0
        {1.057e-3, 8.382},    // 50.0
        {3.206e-4, 7.714},    // 60.0
        {8.770e-5, 6.549},    // 70.0
        {1.905e-5, 5.799},    // 80.0
        {3.396e-6, 5.382},    // 90.0
        {5.297e-7, 5.877},    // 100.0
        {9.661e-8, 7.263},    // 110.0
        {2.438e-8, 9.473},    // 120.0
        {8.484e-9, 12.636},   // 130.0
        {3.845e-9, 16.149},   // 140.0
        {2.070e-9, 22.523},   // 150.0
        {5.464e-10, 29.740},  // 180.0
        {2.789e-10, 37.105},  // 200.0
        {7.248e-11, 45.546},  // 250.0
        {2.418e-11, 53.628},  // 300.0
        {9.518e-12, 53.298},  // 350.0
        {3.725e-12, 58.515},  // 400.0
        {1.585e-12, 60.828},  // 450.0
        {6.967e-13, 63.822},  // 500.0
        {1.454e-13, 71.835},  // 600.0
        {3.614e-14, 88.667},  // 700.0
        {1.170e-14, 124.64},  // 800.0
        {5.245e-15, 181.05},  // 900.0
        {3.019e-15, 268.00}   // 1000.0
    };

    const Real altitude_km = anAltitude.inKilometers();

    Integer bandIndex = Integer::Undefined();

    for (uint i = 0; i < refHeights.getSize() - 1; ++i)
    {
        if (altitude_km < refHeights[i + 1])
        {
            bandIndex = i;
            break;
        }
    }

    if (!bandIndex.isDefined())
    {
        throw ostk::core::error::RuntimeError(String::Format(
            "Exponential density model is not valid for altitudes above 1000 km. Altitude = {}", anAltitude.toString()
        ));
    }

    // TBI: can cache the index bandIndex to avoid searching from the top of the list every time.

    return {refHeights[bandIndex], std::get<0>(densityBands[bandIndex]), std::get<1>(densityBands[bandIndex])};
}

}  // namespace earth
}  // namespace atmospheric
}  // namespace environment
}  // namespace physics
}  // namespace ostk
