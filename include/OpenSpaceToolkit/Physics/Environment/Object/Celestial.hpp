/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Environment_Object_Celestial__
#define __OpenSpaceToolkit_Physics_Environment_Object_Celestial__

#include <OpenSpaceToolkit/Core/Type/Real.hpp>
#include <OpenSpaceToolkit/Core/Type/Shared.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Axes.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Position.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Spherical/LLA.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Transform.hpp>
#include <OpenSpaceToolkit/Physics/Data/Scalar.hpp>
#include <OpenSpaceToolkit/Physics/Data/Vector.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Model.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Ephemeris.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Model.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Magnetic/Model.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Object.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Unit/Derived.hpp>
#include <OpenSpaceToolkit/Physics/Unit/Length.hpp>
#include <OpenSpaceToolkit/Physics/Unit/Mass.hpp>

namespace ostk
{
namespace physics
{
namespace environment
{
namespace object
{

using ostk::core::type::Shared;
using ostk::core::type::Real;
using ostk::core::type::String;

using ostk::mathematics::object::Vector3d;

using ostk::physics::time::Instant;
using ostk::physics::unit::Length;
using ostk::physics::unit::Mass;
using ostk::physics::unit::Derived;
using ostk::physics::data::Scalar;
using ostk::physics::data::Vector;
using ostk::physics::coordinate::Position;
using ostk::physics::coordinate::spherical::LLA;
using ostk::physics::coordinate::Axes;
using ostk::physics::coordinate::Frame;
using ostk::physics::coordinate::Transform;
using ostk::physics::environment::Object;
using ostk::physics::environment::Ephemeris;
using GravitationalModel = ostk::physics::environment::gravitational::Model;
using MagneticModel = ostk::physics::environment::magnetic::Model;
using AtmosphericModel = ostk::physics::environment::atmospheric::Model;

class Celestial : public Object
{
   public:
    enum class Type
    {

        Undefined,
        Sun,
        Mercury,
        Venus,
        Earth,
        Moon,
        Mars

    };

    enum class FrameType
    {

        Undefined,  ///< Undefined frame
        NED,        ///< North-East-Down (NED) frame

    };

    struct ModelBase
    {
        static Derived GravitationalParameter;
        static Length EquatorialRadius;
        static Real Flattening;
        static Real C20;
        static Real C40;
        static Real J2;
        static Real J4;
    };

    Celestial(
        const String& aName,
        const Celestial::Type& aType,
        const Derived& aGravitationalParameter,
        const Length& anEquatorialRadius,
        const Real& aFlattening,
        const Real& aJ2,
        const Real& aJ4,
        const Shared<Ephemeris>& anEphemeris,
        const Shared<GravitationalModel>& aGravitationalModel,
        const Shared<MagneticModel>& aMagneticModel,
        const Shared<AtmosphericModel>& anAtmosphericModel
    );

    Celestial(
        const String& aName,
        const Celestial::Type& aType,
        const Derived& aGravitationalParameter,
        const Length& anEquatorialRadius,
        const Real& aFlattening,
        const Real& aJ2,
        const Real& aJ4,
        const Shared<Ephemeris>& anEphemeris,
        const Shared<GravitationalModel>& aGravitationalModel,
        const Shared<MagneticModel>& aMagneticModel,
        const Shared<AtmosphericModel>& anAtmosphericModel,
        const Object::Geometry& aGeometry
    );

    virtual ~Celestial() override;

    virtual Celestial* clone() const override;

    virtual bool isDefined() const override;

    Shared<const Ephemeris> accessEphemeris() const;

    Shared<const GravitationalModel> accessGravitationalModel() const;

    Shared<const MagneticModel> accessMagneticModel() const;

    Shared<const AtmosphericModel> accessAtmosphericModel() const;

    bool gravitationalModelIsDefined() const;

    bool magneticModelIsDefined() const;

    bool atmosphericModelIsDefined() const;

    Celestial::Type getType() const;

    Derived getGravitationalParameter() const;

    Length getEquatorialRadius() const;

    Real getFlattening() const;

    Real getJ2() const;

    Real getJ4() const;

    virtual Shared<const Frame> accessFrame() const override;

    virtual Position getPositionIn(const Shared<const Frame>& aFrameSPtr, const Instant& anInstant) const override;

    virtual Velocity getVelocityIn(const Shared<const Frame>& aFrameSPtr, const Instant& anInstant) const override;

    virtual Transform getTransformTo(const Shared<const Frame>& aFrameSPtr, const Instant& anInstant) const override;

    virtual Axes getAxesIn(const Shared<const Frame>& aFrameSPtr, const Instant& anInstant) const override;

    Vector getGravitationalFieldAt(const Position& aPosition, const Instant& anInstant) const;

    Vector getMagneticFieldAt(const Position& aPosition, const Instant& anInstant) const;

    Scalar getAtmosphericDensityAt(const Position& aPosition, const Instant& anInstant) const;

    Shared<const Frame> getFrameAt(const LLA& aLla, const Celestial::FrameType& aFrameType) const;

    Object::Geometry getTerminatorGeometry() const;

    static Celestial Undefined();

    static String StringFromFrameType(const Celestial::FrameType& aFrameType);

   private:
    Celestial::Type type_;
    Derived gravitationalParameter_;
    Length equatorialRadius_;
    Real flattening_;
    Real j2_;
    Real j4_;
    Shared<Ephemeris> ephemeris_;
    Shared<GravitationalModel> gravitationalModelSPtr_;
    Shared<MagneticModel> magneticModelSPtr_;
    Shared<AtmosphericModel> atmosphericModelSPtr_;
};

}  // namespace object
}  // namespace environment
}  // namespace physics
}  // namespace ostk

#endif
