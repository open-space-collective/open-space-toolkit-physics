/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_NRLMSISE00__
#define __OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_NRLMSISE00__

#include <OpenSpaceToolkit/Core/Containers/Array.hpp>
#include <OpenSpaceToolkit/Core/Containers/Tuple.hpp>
#include <OpenSpaceToolkit/Core/Types/Integer.hpp>
#include <OpenSpaceToolkit/Core/Types/Real.hpp>
#include <OpenSpaceToolkit/Core/Types/String.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Spherical/LLA.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Model.hpp>
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
using ostk::core::ctnr::Tuple;
using ostk::core::ctnr::Array;

using ostk::physics::time::Instant;
using ostk::physics::units::Length;
using ostk::physics::coord::spherical::LLA;
using ostk::physics::environment::atmospheric::Model;

/// @brief                      NRLMSISE00 atmospheric model

class NRLMSISE00 : public Model
{
   public:
    // redefine input structs from NRLMSISE-00.h to avoid including it in this header
    struct ap_array
    {
        double a[7];
    };

    struct nrlmsise_input
    {
        int year;
        int doy;
        double sec;
        double alt;
        double g_lat;
        double g_long;
        double lst;
        double f107A;
        double f107;
        double ap;
        struct ap_array* ap_a;
    };

    /// @brief              Constructor

    NRLMSISE00();

    /// @brief              Clone the exponential atmospheric model
    ///
    /// @return             Pointer to exponential atmospheric model

    virtual NRLMSISE00* clone() const override;

    /// @brief              Check if the exponential atmospheric model is defined
    ///
    /// @return             True if the exponential atmospheric model is defined

    bool isDefined() const;

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
    /// @param              [in] outputArray C-style array to be filled with AP values.
    /// @param              [in] anInstant An Instant
    /// @return             Atmospheric density value [kg.m^-3]

    void computeAPArray(double* outputArray, const Instant& anInstant) const;

    /// @brief              Compute the NRLMSISE00 input and populate into the given struct
    ///                     Optionally use provided sun position to calculate local solar time.
    ///
    /// @param              [out] input NRLMSISE00 input struct to be populated
    /// @param              [in] aph Struct to holp AP values
    /// @param              [in] aLLA A position, expressed as latitude, longitude, altitude [deg, deg, m]
    /// @param              [in] anInstant An instant

    void computeNRLMSISE00Input(
        nrlmsise_input& input,
        ap_array& aph,
        const LLA& aLLA,
        const Instant& anInstant,
        const Position& aSunPosition = Position::Undefined()
    ) const;

    /// @brief              Get the atmospheric density value at a given position and instant.
    ///                     Optionally use provided sun position to calculate local solar time.
    ///
    /// @param              [in] aLLA A position, expressed as latitude, longitude, altitude [deg, deg, m]
    /// @param              [in] anInstant An instant
    /// @param              [in] aSunPosition Position of the sun
    /// @return             Atmospheric density value [kg.m^-3]

    Real getDensityAt(const LLA& aLLA, const Instant& anInstant, const Position& aSunPosition = Position::Undefined())
        const;

    /// @brief              Get the atmospheric density value at a given position and instant
    ///                     Use provided sun position to calculate local solar time.
    ///
    /// @param              [in] aPosition A Position
    /// @param              [in] anInstant An Instant
    /// @param              [in] aSunPosition Position of the sun
    /// @return             Atmospheric density value [kg.m^-3]

    Real getDensityAt(const Position& aPosition, const Instant& anInstant, const Position& aSunPosition) const;

    /// @brief              Get the atmospheric density value at a given position and instant.
    ///                     Use lst = secondsInDay/3600.0 + aLLA.getLongitude().inDegrees()/15.0 to calculate local
    ///                     solar time.
    ///
    /// @param              [in] aLLA A position, expressed as latitude, longitude, altitude [deg, deg, m]
    /// @param              [in] anInstant An instant
    /// @return             Atmospheric density value [kg.m^-3]

    virtual Real getDensityAt(const Position& aPosition, const Instant& anInstant) const override;
};

}  // namespace earth
}  // namespace atmospheric
}  // namespace environment
}  // namespace physics
}  // namespace ostk

#endif