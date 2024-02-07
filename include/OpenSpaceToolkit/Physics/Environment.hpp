/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Environment__
#define __OpenSpaceToolkit_Physics_Environment__

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Type/Shared.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>
#include <OpenSpaceToolkit/Core/Type/Unique.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Object.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Objects/Celestial.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

namespace ostk
{
namespace physics
{

using ostk::core::type::Unique;
using ostk::core::type::Shared;
using ostk::core::type::String;
using ostk::core::container::Array;

using ostk::physics::time::Instant;
using ostk::physics::coord::Position;
using ostk::physics::environment::Object;
using ostk::physics::environment::object::Celestial;

/// @brief                      Environment modeling

class Environment
{
   public:
    /// @brief              Constructor
    ///
    /// @param              [in] anInstant An instant
    /// @param              [in] An array of shared pointers to objects

    Environment(const Instant& anInstant, const Array<Shared<Object>>& anObjectArray);

    /// @brief              Copy constructor
    ///
    /// @param              [in] anEnvironment An environment

    Environment(const Environment& anEnvironment);

    /// @brief              Copy assignment operator
    ///
    /// @param              [in] anEnvironment An environment
    /// @return             Reference to environment

    Environment& operator=(const Environment& anEnvironment);

    /// @brief              Output stream operator
    ///
    /// @param              [in] anOutputStream An output stream
    /// @param              [in] anEnvironment An environment
    /// @return             A reference to output stream

    friend std::ostream& operator<<(std::ostream& anOutputStream, const Environment& anEnvironment);

    /// @brief              Check if environment is defined
    ///
    /// @return             True if environment is defined

    bool isDefined() const;

    /// @brief              Returns true if environment contains objects with a given name
    ///
    /// @param              [in] aName An object name
    /// @return             True if environment contains objects with a given name

    bool hasObjectWithName(const String& aName) const;

    /// @brief              Returns true if a given geometry intersects any of the environment objects
    ///
    /// @param              [in] aGeometry A geometry
    /// @param              [in] (optional) anObjectToIgnoreArray An array of objects to ignore
    /// @return             True if a given geometry intersects any of the environment objects

    bool intersects(
        const Object::Geometry& aGeometry,
        const Array<Shared<const Object>>& anObjectToIgnoreArray = Array<Shared<const Object>>::Empty()
    ) const;

    /// @brief              Access objects
    ///
    /// @return             Reference to array of shared pointers to objects

    Array<Shared<const Object>> accessObjects() const;

    /// @brief              Access object with a given name
    ///
    /// @param              [in] aName An object name
    /// @return             Reference to shared pointer to object

    Shared<const Object> accessObjectWithName(const String& aName) const;

    /// @brief              Access celestial object with a given name
    ///
    /// @param              [in] aName A celestial object name
    /// @return             Reference to shared pointer to celestial object

    Shared<const Celestial> accessCelestialObjectWithName(const String& aName) const;

    /// @brief              Get instant
    ///
    /// @return             Instant

    Instant getInstant() const;

    /// @brief              Get names of objects
    ///
    /// @return             Array of objects names

    Array<String> getObjectNames() const;

    /// @brief              Set instant
    ///
    /// @param              [in] anInstant An instant

    void setInstant(const Instant& anInstant);

    /// @brief              Is position in eclipse
    ///
    /// @param              [in] aPosition A position
    /// @return             True if the position is in eclipse

    bool isPositionInEclipse(const Position& aPosition) const;

    /// @brief              Get gravitational field at position
    ///
    /// @param              [in] aPosition A position
    /// @return             Gravitational field vector

    // Vector                  getGravitationalFieldAt                     (   const   Position& aPosition ) const ;
    // [TBI]

    /// @brief              Get magnetic field at position
    ///
    /// @param              [in] aPosition A position
    /// @return             Magnetic field vector

    // Vector                  getMagneticFieldAt                          (   const   Position& aPosition ) const ;
    // [TBI]

    /// @brief              Constructs an undefined environment
    ///
    /// @code
    ///                     Environment environment = Environment::Undefined() ;
    ///                     environment.isDefined() ; // False
    /// @endcode
    ///
    /// @return             Undefined environment

    static Environment Undefined();

    /// @brief              Constructs a default environment
    ///
    ///                     Contains Earth, Sun and Moon, with SPICE-based ephemeris.
    ///
    /// @code
    ///                     Environment environment = Environment::Default() ;
    /// @endcode
    ///
    /// @return             Undefined environment

    static Environment Default();

   private:
    Instant instant_;
    Array<Shared<const Object>> objects_;
};

}  // namespace physics
}  // namespace ostk

#endif
