/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Environment_Gravitational_Model__
#define __OpenSpaceToolkit_Physics_Environment_Gravitational_Model__

#include <OpenSpaceToolkit/Core/Types/Real.hpp>

#include <OpenSpaceToolkit/Mathematics/Objects/Vector.hpp>

#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Units/Derived.hpp>
#include <OpenSpaceToolkit/Physics/Units/Length.hpp>

namespace ostk
{
namespace physics
{
namespace environment
{
namespace gravitational
{

using ostk::core::types::Real;

using ostk::math::obj::Vector3d;

using ostk::physics::time::Instant;
using ostk::physics::units::Derived;
using ostk::physics::units::Length;
using ostk::physics::units::Time;

/// @brief                      Gravitational model (interface)

static const Derived::Unit GravitationalParameterSIUnit =
    Derived::Unit::GravitationalParameter(Length::Unit::Meter, Time::Unit::Second);

class Model
{
   public:

    // @brief                  Gravitational model parameters
    struct Parameters
    {

        // @brief              Constructor

        // @param              [in] aGravitationalParameter A gravitational parameter [m^3/s^2]
        // @param              [in] anEquatorialRadius An equatorial radius [m]
        // @param              [in] aFlattening A flattening
        // @param              [in] aC20 C20
        // @param              [in] aC40 C40

        Parameters(
            const Derived& aGravitationalParameter,
            const Length& anEquatorialRadius,
            const Real& aFlattening,
            const Real& aC20,
            const Real& aC40
        );

        // @brief              Equal to operator
        //
        // @param              [in] aParameterSet A parameter set
        // @return             True if the parameter set are equal

        bool operator==(const Parameters& aParameterSet) const;

        // @brief              Not equal to operator
        //
        // @param              [in] aParameterSet A parameter set
        // @return             True if the parameter set are not equal

        bool operator!=(const Parameters& aParameterSet) const;

        // @brief              Output stream operator
        //
        // @param              [in] anOutputStream An output stream
        // @param              [in] aParameterSet A parameter set
        // @return             A reference to output stream

        friend std::ostream& operator<<(std::ostream& anOutputStream, const Parameters& aParameterSet);

        // @brief              Check if the parameter set is defined
        //
        // @return             True if the parameter set is defined

        bool isDefined() const;

        // @brief              Undefined parameter set
        //
        // @return             An undefined parameter set

        static Parameters Undefined();

        Derived gravitationalParameter_;
        Length equatorialRadius_;
        Real flattening_;
        Real C20_;
        Real C40_;
        Real J2_;
        Real J4_;
    };

    /// @brief              Constructor (default)

    Model(const Parameters& aSetOfParameters);

    /// @brief              Destructor (pure virtual)

    virtual ~Model() = 0;

    /// @brief              Clone the gravitational model (pure virtual)
    ///
    /// @return             Pointer to gravitational model

    virtual Model* clone() const = 0;

    /// @brief              Check if the gravitational model is defined (pure virtual)
    ///
    /// @return             True if the gravitational model is defined

    virtual bool isDefined() const = 0;

    /// @brief              Get the gravitational field value at a given position and instant (pure virtual)
    ///
    /// @param              [in] aPosition A position, expressed in the gravitational object frame [m]
    /// @param              [in] anInstant An instant
    /// @return             Gravitational field value, expressed in the gravitational object frame [m.s-2]

    virtual Vector3d getFieldValueAt(const Vector3d& aPosition, const Instant& anInstant) const = 0;

    Parameters getParameters() const;

   private:
    Model::Parameters parameters_;
};

}  // namespace gravitational
}  // namespace environment
}  // namespace physics
}  // namespace ostk

#endif
