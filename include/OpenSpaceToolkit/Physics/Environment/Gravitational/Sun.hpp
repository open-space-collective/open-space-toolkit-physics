/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Environment_Gravitational_Sun__
#define __OpenSpaceToolkit_Physics_Environment_Gravitational_Sun__

#include <OpenSpaceToolkit/Core/FileSystem/Directory.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>
#include <OpenSpaceToolkit/Core/Type/Unique.hpp>

#include <OpenSpaceToolkit/IO/URL.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Model.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Unit/Derived.hpp>

namespace ostk
{
namespace physics
{
namespace environment
{
namespace gravitational
{

using ostk::core::type::Unique;
using ostk::core::type::Integer;
using ostk::core::type::Real;
using ostk::core::filesystem::Directory;

using ostk::io::URL;

using ostk::physics::unit::Derived;
using ostk::physics::time::Instant;
using ostk::physics::environment::gravitational::Model;

/// @brief                      Sun gravitational model
///
///                             The gravitational potential of the Sun for now is kept as a simple spherical model.

class Sun : public Model
{
   public:
    static const Parameters Spherical;

    enum class Type
    {
        Undefined,  /// Undefined
        Spherical   /// The spherical gravity originating from a point source at the center of the Sun
    };

    /// @brief              Constructor
    ///
    /// @param              [in] aType A gravitational model type
    /// @param              [in] (optional) aDataDirectory A gravitational model data directory

    Sun(const Sun::Type& aType, const Directory& aDataDirectory = Directory::Undefined());

    /// @brief              Copy constructor
    ///
    /// @param              [in] aSunGravitationalModel A Sun model

    Sun(const Sun& aSunGravitationalModel);

    /// @brief              Copy assignment operator
    ///
    /// @param              [in] aSunGravitationalModel A Sun model
    /// @return             Reference to Sun model

    Sun& operator=(const Sun& aSunGravitationalModel);

    /// @brief              Destructor

    ~Sun();

    /// @brief              Clone the Sun gravitational model
    ///
    /// @return             Pointer to Sun gravitational model

    virtual Sun* clone() const override;

    /// @brief              Check if the Sun gravitational model is defined
    ///
    /// @return             True if the Sun gravitational model is defined

    virtual bool isDefined() const override;

    /// @brief              Get gravitational model type
    ///
    /// @return             Gravitational model type

    Sun::Type getType() const;

    /// @brief              Get the gravitational field value at a given position and instant
    ///
    /// @param              [in] aPosition A position, expressed in the gravitational object frame [m]
    /// @param              [in] anInstant An instant
    /// @return             Gravitational field value, expressed in the gravitational object frame [m.s-2]

    virtual Vector3d getFieldValueAt(const Vector3d& aPosition, const Instant& anInstant) const override;

    Model::Parameters ParametersFromType(const Sun::Type& aType);

   private:
    class Impl;
    class SphericalImpl;

    Unique<Impl> implUPtr_;

    static Unique<Impl> ImplFromType(const Sun::Type& aType, const Directory& aDataDirectory);
};

}  // namespace gravitational
}  // namespace environment
}  // namespace physics
}  // namespace ostk

#endif
