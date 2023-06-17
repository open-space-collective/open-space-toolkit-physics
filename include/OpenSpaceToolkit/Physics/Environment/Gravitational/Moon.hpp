/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Environment_Gravitational_Moon__
#define __OpenSpaceToolkit_Physics_Environment_Gravitational_Moon__

#include <OpenSpaceToolkit/Core/FileSystem/Directory.hpp>
#include <OpenSpaceToolkit/Core/Types/Real.hpp>
#include <OpenSpaceToolkit/Core/Types/Unique.hpp>

#include <OpenSpaceToolkit/IO/URL.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Model.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Units/Derived.hpp>

namespace ostk
{
namespace physics
{
namespace environment
{
namespace gravitational
{

using ostk::core::types::Unique;
using ostk::core::types::Integer;
using ostk::core::types::Real;
using ostk::core::fs::Directory;

using ostk::io::URL;

using ostk::physics::units::Derived;
using ostk::physics::time::Instant;
using ostk::physics::environment::gravitational::Model;

/// @brief                      Moon gravitational model
///
///                             The gravitational potential of the Moon for now is kept as a simple spherical model.

class Moon : public Model
{
   public:
    // Declare static gravitational model parameters
    static const Parameters Spherical;

    enum class Type
    {
        Undefined,  /// Undefined
        Spherical   /// The spherical gravity originating from a point source at the center of the Moon
    };

    /// @brief              Constructor
    ///
    /// @param              [in] aType A gravitational model type
    /// @param              [in] (optional) aDataDirectory A gravitational model data directory

    Moon(const Moon::Type& aType, const Directory& aDataDirectory = Directory::Undefined());

    /// @brief              Copy constructor
    ///
    /// @param              [in] aMoonGravitationalModel A Moon model

    Moon(const Moon& aMoonGravitationalModel);

    /// @brief              Copy assignment operator
    ///
    /// @param              [in] aMoonGravitationalModel A Moon model
    /// @return             Reference to Moon model

    Moon& operator=(const Moon& aMoonGravitationalModel);

    /// @brief              Destructor

    ~Moon();

    /// @brief              Clone the Moon gravitational model
    ///
    /// @return             Pointer to Moon gravitational model

    virtual Moon* clone() const override;

    /// @brief              Check if the Moon gravitational model is defined
    ///
    /// @return             True if the Moon gravitational model is defined

    virtual bool isDefined() const override;

    /// @brief              Get gravitational model type
    ///
    /// @return             Gravitational model type

    Moon::Type getType() const;

    /// @brief              Get the gravitational field value at a given position and instant
    ///
    /// @param              [in] aPosition A position, expressed in the gravitational object frame [m]
    /// @param              [in] anInstant An instant
    /// @return             Gravitational field value, expressed in the gravitational object frame [m.s-2]

    virtual Vector3d getFieldValueAt(const Vector3d& aPosition, const Instant& anInstant) const override;

    static Model::Parameters ParametersFromType(const Moon::Type& aType);

   private:
    class Impl;
    class SphericalImpl;

    Unique<Impl> implUPtr_;

    static Unique<Impl> ImplFromType(const Moon::Type& aType, const Directory& aDataDirectory);
};

}  // namespace gravitational
}  // namespace environment
}  // namespace physics
}  // namespace ostk

#endif
