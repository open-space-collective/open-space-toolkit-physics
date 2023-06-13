/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Environment_Atmospheric_Undefined__
#define __OpenSpaceToolkit_Physics_Environment_Atmospheric_Undefined__

#include <OpenSpaceToolkit/Core/Types/Real.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Model.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Units/Derived.hpp>

namespace ostk
{
namespace physics
{
namespace environment
{
namespace atmospheric
{

using ostk::core::types::Real;

using ostk::physics::units::Derived;
using ostk::physics::time::Instant;
using ostk::physics::environment::atmospheric::Model;

/// @brief						Atmospheric Undefined model

class Undefined : public Model
{
   public:
    /// @brief              Constructor

    Undefined();

    /// @brief              Clone the undefined atmospheric model
    ///
    /// @return             Pointer to undefined atmospheric model

    virtual Undefined* clone() const override;

    /// @brief              Check if the undefined atmospheric model is defined
    ///
    /// @return             True if the undefined atmospheric model is defined

    bool isDefined() const;

    /// @brief              Get the atmospheric density at a given position and instant
    ///
    /// @param              [in] aPosition A position, expressed in the atmospheric object frame [m]
    /// @param              [in] anInstant An instant
    /// @return             Atmospheric density

    virtual Real getDensityAt(const Position& aPosition, const Instant& anInstant) const override;

};

}  // namespace atmospheric
}  // namespace environment
}  // namespace physics
}  // namespace ostk

#endif
