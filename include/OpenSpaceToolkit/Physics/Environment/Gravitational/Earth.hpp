/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Environment_Gravitational_Earth__
#define __OpenSpaceToolkit_Physics_Environment_Gravitational_Earth__

#include <OpenSpaceToolkit/Core/FileSystem/Directory.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>
#include <OpenSpaceToolkit/Core/Type/Unique.hpp>

#include <OpenSpaceToolkit/IO/URL.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Model.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

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

using ostk::physics::time::Instant;
using ostk::physics::environment::gravitational::Model;

/// @brief                      Earth gravitational model
///
///                             The gravitational potential is expanded as sum of spherical harmonics.
///
/// @ref                        https://en.wikipedia.org/wiki/Spherical_harmonics
/// @ref                        https://geographiclib.sourceforge.io/html/gravity.html

class Earth : public Model
{
   public:
    // Declare static gravitational model parameters
    static const Parameters EGM2008;
    static const Parameters WGS84_EGM96;
    static const Parameters EGM96;
    static const Parameters EGM84;
    static const Parameters WGS84;
    static const Parameters Spherical;

    enum class Type
    {
        Undefined,  ///< Undefined
        Spherical,  ///< The spherical gravity originating from a point source at the center of the Earth
        WGS84,  ///< The normal gravitational field for the reference ellipsoid. This includes the zonal coefficients up
                ///< to order 20.
        EGM84,  ///< The Earth Gravity Model 1984, which includes terms up to degree 180.
        WGS84_EGM96,  ///< The normal gravitational field for the reference ellipsoid plus the Earth Gravity Model 1996,
                      ///< which includes terms up to degree 360.
        EGM96,        ///< The Earth Gravity Model 1996, which includes terms up to degree 360.
        EGM2008       ///< The Earth Gravity Model 2008, which includes terms up to degree 2190.
    };

    /// @brief              Constructor with directory specification and max degree and order variables
    ///
    /// @param              [in] aType A gravitational model type
    /// @param              [in] (optional) aDataDirectory A gravitational model data directory
    /// @param              [in] (optional) aGravityModelDegree A gravitational model degree
    /// @param              [in] (optional) aGravityModelOrder A gravitational model order

    Earth(
        const Earth::Type& aType,
        const Directory& aDataDirectory = Directory::Undefined(),
        const Integer& aGravityModelDegree = Integer::Undefined(),
        const Integer& aGravityModelOrder = Integer::Undefined()
    );

    /// @brief              Constructor with max degree and order variables
    ///
    /// @param              [in] aType A gravitational model type
    /// @param              [in] aGravityModelDegree A gravitational model degree
    /// @param              [in] aGravityModelOrder A gravitational model order

    Earth(const Earth::Type& aType, const Integer& aGravityModelDegree, const Integer& aGravityModelOrder);

    /// @brief              Copy constructor
    ///
    /// @param              [in] anEarthGravitationalModel An Earth model

    Earth(const Earth& anEarthGravitationalModel);

    /// @brief              Copy assignment operator
    ///
    /// @param              [in] anEarthGravitationalModel An Earth model
    /// @return             Reference to Earth model

    Earth& operator=(const Earth& anEarthGravitationalModel);

    /// @brief              Destructor

    ~Earth();

    /// @brief              Clone the Earth gravitational model
    ///
    /// @return             Pointer to Earth gravitational model

    virtual Earth* clone() const override;

    /// @brief              Check if the Earth gravitational model is defined
    ///
    /// @return             True if the Earth gravitational model is defined

    virtual bool isDefined() const override;

    /// @brief              Get gravitational model type
    ///
    /// @return             Gravitational model type

    Earth::Type getType() const;

    /// @brief              Get gravitational model degree
    ///
    /// @return             Gravitational model degree

    virtual Integer getDegree() const;

    /// @brief              Get gravitational model order
    ///
    /// @return             Gravitational model order

    virtual Integer getOrder() const;

    /// @brief              Get the gravitational field value at a given position and instant
    ///
    /// @param              [in] aPosition A position, expressed in the gravitational object frame [m]
    /// @param              [in] anInstant An instant
    /// @return             Gravitational field value, expressed in the gravitational object frame [m.s-2]

    virtual Vector3d getFieldValueAt(const Vector3d& aPosition, const Instant& anInstant) const override;

    static Model::Parameters ParametersFromType(const Earth::Type& aType);

    static constexpr double gravityConstant = 9.80665;  /// Standard gravity [m.s-2]

   private:
    class Impl;
    class SphericalImpl;
    class ExternalImpl;

    Unique<Impl> implUPtr_;

    static Unique<Impl> ImplFromType(
        const Earth::Type& aType,
        const Directory& aDataDirectory,
        const Integer& aGravityModelDegree,
        const Integer& aGravityModelOrder
    );
};

}  // namespace gravitational
}  // namespace environment
}  // namespace physics
}  // namespace ostk

#endif
