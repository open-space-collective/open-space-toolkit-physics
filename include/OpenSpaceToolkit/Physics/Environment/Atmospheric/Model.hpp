/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Environment_Atmospheric_Model__
#define __OpenSpaceToolkit_Physics_Environment_Atmospheric_Model__

#include <OpenSpaceToolkit/Core/Type/Real.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Position.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

namespace ostk
{
namespace physics
{
namespace environment
{
namespace atmospheric
{

using ostk::core::type::Real;

using ostk::physics::coordinate::Position;
using ostk::physics::time::Instant;

/// @brief                      Atmospheric model (interface)

class Model
{
   public:
    /// @brief              Constructor (default)

    Model();

    /// @brief              Destructor (pure virtual)

    virtual ~Model() = 0;

    /// @brief              Clone the atmospheric model (pure virtual)
    ///
    /// @return             Pointer to atmospheric model

    virtual Model* clone() const = 0;

    /// @brief              Check if the atmospheric model is defined (pure virtual)
    ///
    /// @return             True if the atmospheric model is defined

    virtual bool isDefined() const = 0;

    /// @brief              Get the atmospheric density value at a given position and instant
    ///
    /// @param              [in] aPosition A Position
    /// @param              [in] anInstant An Instant
    /// @return             Atmospheric density value [kg.m^-3]

    virtual Real getDensityAt(const Position& aPosition, const Instant& anInstant) const = 0;
};

}  // namespace atmospheric
}  // namespace environment
}  // namespace physics
}  // namespace ostk

#endif
