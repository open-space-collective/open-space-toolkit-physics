/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Exponential__
#define __OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Exponential__

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Container/Tuple.hpp>
#include <OpenSpaceToolkit/Core/Type/Integer.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

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

using ostk::core::type::Integer;
using ostk::core::type::Real;
using ostk::core::type::String;
using ostk::core::container::Tuple;
using ostk::core::container::Array;

using ostk::physics::time::Instant;
using ostk::physics::units::Length;
using ostk::physics::coord::spherical::LLA;
using ostk::physics::environment::atmospheric::Model;

/// @brief                      Exponential atmospheric model

class Exponential
{
   public:
    /// @brief              Constructor

    Exponential();

    /// @brief              Clone the exponential atmospheric model
    ///
    /// @return             Pointer to exponential atmospheric model

    virtual Exponential* clone() const;

    /// @brief              Check if the exponential atmospheric model is defined
    ///
    /// @return             True if the exponential atmospheric model is defined

    bool isDefined() const;

    /// @brief              Get the atmospheric density value at a given position and instant
    ///
    /// @param              [in] aLLA A position, expressed as latitude, longitude, altitude [deg, deg, m]
    /// @param              [in] anInstant An instant
    /// @return             Atmospheric density value [kg.m^-3]

    Real getDensityAt(const LLA& aLLA, const Instant& anInstant) const;

   private:
    static Tuple<Real, Real, Real> DensityBandValues(const Length& anAltitude);
};

}  // namespace earth
}  // namespace atmospheric
}  // namespace environment
}  // namespace physics
}  // namespace ostk

#endif
