/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_NRLMSISE00__
#define __OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_NRLMSISE00__

#include <OpenSpaceToolkit/Core/Containers/Array.hpp>
#include <OpenSpaceToolkit/Core/Containers/Tuple.hpp>
#include <OpenSpaceToolkit/Core/Types/Integer.hpp>
#include <OpenSpaceToolkit/Core/Types/Real.hpp>
#include <OpenSpaceToolkit/Core/Types/Shared.hpp>
#include <OpenSpaceToolkit/Core/Types/String.hpp>
#include <OpenSpaceToolkit/Core/Types/Unique.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Spherical/LLA.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Model.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Objects/Celestial.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Units/Length.hpp>

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

using ostk::core::types::Integer;
using ostk::core::types::Real;
using ostk::core::types::String;
using ostk::core::types::Unique;
using ostk::core::types::Shared;
using ostk::core::ctnr::Tuple;
using ostk::core::ctnr::Array;

using ostk::physics::time::Instant;
using ostk::physics::units::Length;
using ostk::physics::coord::spherical::LLA;
using ostk::physics::coord::Frame;
using ostk::physics::env::obj::Celestial;
using ostk::physics::environment::atmospheric::Model;
using EarthGravitationalModel = ostk::physics::environment::gravitational::Earth;

/// @brief                      NRLMSISE00 atmospheric model

class NRLMSISE00
{
   public:
    /// @brief              Constructor

    NRLMSISE00(
        const Shared<const Frame>& anEarthFrameSPtr = Frame::ITRF(),
        const Length& anEarthRadius = EarthGravitationalModel::WGS84.equatorialRadius_,
        const Real& anEarthFlattening = EarthGravitationalModel::WGS84.flattening_,
        const Shared<Celestial>& aSunCelestialSPtr = nullptr
    );

    /// @brief              Clone the NRLMSISE00 atmospheric model
    ///
    /// @return             Pointer to NRLMSISE00 atmospheric model

    virtual NRLMSISE00* clone() const;

    /// @brief              Check if the NRLMSISE00 atmospheric model is defined
    ///
    /// @return             True if the NRLMSISE00 atmospheric model is defined

    bool isDefined() const;

    /// @brief              Get the atmospheric density value at a given position and instant.
    ///
    /// @param              [in] aLLA A position, expressed as latitude, longitude, altitude [deg, deg, m]
    /// @param              [in] anInstant An instant

    /// @return             Atmospheric density value [kg.m^-3]

    Real getDensityAt(const LLA& aLLA, const Instant& anInstant) const;



    // redefine input structs from NRLMSISE-00.h to avoid including it in this header

    struct ap_array
    {
        double a[7];
    };

    struct nrlmsise_input
    {
        int year;               // unused, according to the documentation
        int doy;                // day of year [1-365] (except leap years)
        double sec;             // seconds in day [0-86400]
        double alt;             // altitude [km]
        double g_lat;           // geodetic latitude [deg]
        double g_long;          // geodetic longitude [deg]
        double lst;             // local apparent solar time [hours]
        double f107A;           // 81 day average of F10.7 flux (centered on doy)
        double f107;            // daily F10.7 flux for previous day
        double ap;              // AP magnetic index(daily)
        struct ap_array* ap_a;  // array of 7 values of AP. [see computeApArray below]
    };

    static Real GetDensityAt(nrlmsise_input input);


protected:
    /// @brief              Fill the provided array with AP values needed for the NRLMSISE model.
    ///                     The output array is filled like so:
    ///
    ///                     0 : daily AP [average of current day AP values]
    ///                     1 : 3 hr AP index for instant
    ///                     2 : 3 hr AP index for 3 hrs before instant
    ///                     3 : 3 hr AP index for 6 hrs before instant
    ///                     4 : 3 hr AP index for 9 hrs before instant
    ///                     5 : Average of eight 3 hr AP indices from 12 to 33 hrs
    ///                             prior to instant
    ///                     6 : Average of eight 3 hr AP indices from 36 to 57 hrs
    ///                             prior to instant
    ///
    /// @param              [in] anInstant An Instant
    /// @return             Pointer to AP array struct

    Unique<NRLMSISE00::ap_array> computeApArray(const Instant& anInstant) const;

    /// @brief              Compute the NRLMSISE00 input and populate into the given struct
    ///                     Optionally use provided sun position to calculate local solar time.
    ///
    /// @param              [in] apValues Pointer to AP values struct
    /// @param              [in] aLLA A position, expressed as latitude, longitude, altitude [deg, deg, m]
    /// @param              [in] anInstant An instant

    Unique<NRLMSISE00::nrlmsise_input> computeNRLMSISE00Input(
        const Unique<NRLMSISE00::ap_array>& apValues, const LLA& aLLA, const Instant& anInstant
    ) const;

   private:
    Shared<const Frame> earthFrameSPtr_;
    Length earthRadius_;
    Real earthFlattening_;
    Shared<Celestial> sunCelestialSPtr_;
};

}  // namespace earth
}  // namespace atmospheric
}  // namespace environment
}  // namespace physics
}  // namespace ostk

#endif
