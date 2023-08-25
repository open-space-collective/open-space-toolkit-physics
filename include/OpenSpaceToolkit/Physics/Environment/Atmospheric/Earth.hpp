/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth__
#define __OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth__

#include <OpenSpaceToolkit/Core/FileSystem/Directory.hpp>
#include <OpenSpaceToolkit/Core/Types/Real.hpp>
#include <OpenSpaceToolkit/Core/Types/Shared.hpp>
#include <OpenSpaceToolkit/Core/Types/Unique.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Position.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Spherical/LLA.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Model.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Objects/Celestial.hpp>
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

using ostk::core::types::Unique;
using ostk::core::types::Real;
using ostk::core::types::Shared;
using ostk::core::fs::Directory;

using ostk::physics::time::Instant;
using ostk::physics::units::Length;
using ostk::physics::coord::Position;
using ostk::physics::coord::spherical::LLA;
using ostk::physics::units::Length;
using ostk::physics::coord::Frame;
using ostk::physics::env::obj::Celestial;
using ostk::physics::environment::atmospheric::Model;
using EarthGravitationalModel = ostk::physics::environment::gravitational::Earth;

/// @brief                      Earth atmospheric model

class Earth : public Model
{
   public:
    enum class Type
    {
        Undefined,    ///< Undefined
        Exponential,  ///< Exponential atmospheric density model, valid up to 1000 km
        NRLMSISE00    ///< Navy Research Lab Mass Spectrometer and Incoherent Scatter Radar Exosphere 2000
    };

    /// @brief              Constructor
    ///
    /// @param              [in] aType An atmospheric model type
    /// @param              [in] (optional) aDataDirectory An atmospheric model data directory

    Earth(
        const Earth::Type& aType,
        const Shared<const Frame>& anEarthFrameSPtr = Frame::ITRF(),
        const Length& anEarthRadius = EarthGravitationalModel::WGS84.equatorialRadius_,
        const Real& anEarthFlattening = EarthGravitationalModel::WGS84.flattening_,
        const Shared<Celestial>& aSunCelestialSPtr = nullptr
    );

    /// @brief              Copy constructor
    ///
    /// @param              [in] anEarthAtmosphericModel An Earth atmospheric model

    Earth(const Earth& anEarthAtmosphericModel);

    /// @brief              Copy assignment operator
    ///
    /// @param              [in] anEarthAtmosphericModel An Earth atmospheric model
    /// @return             Reference to Earth atmospheric model

    Earth& operator=(const Earth& anEarthAtmosphericModel);

    /// @brief              Destructor

    ~Earth();

    /// @brief              Clone the Earth atmospheric model
    ///
    /// @return             Pointer to Earth atmospheric model

    virtual Earth* clone() const override;

    /// @brief              Check if the Earth atmospheric model is defined
    ///
    /// @return             True if the Earth atmospheric model is defined

    bool isDefined() const;

    /// @brief              Get atmospheric model type
    ///
    /// @return             Atmospheric model type

    Earth::Type getType() const;

    /// @brief              Get the atmospheric density value at a given position and instant
    ///
    /// @param              [in] aPosition A Position
    /// @param              [in] anInstant An Instant
    /// @return             Atmospheric density value [kg.m^-3]

    Real getDensityAt(const Position& aPosition, const Instant& anInstant) const override;

    /// @brief              Get the atmospheric density value at a given position and instant
    ///
    /// @param              [in] aLLA A LLA
    /// @param              [in] anInstant An Instant
    /// @return             Atmospheric density value [kg.m^-3]
    Real getDensityAt(const LLA& aLLA, const Instant& anInstant) const;

   private:
    class Impl;
    class ExponentialImpl;
    class NRLMSISE00Impl;

    Unique<Impl> implUPtr_;

    static Unique<Impl> ImplFromType(
        const Type& aType,
        const Shared<const Frame>& anEarthFrameSPtr,
        const Length& anEarthRadius,
        const Real& anEarthFlattening,
        const Shared<Celestial>& aSunCelestialSPtr
    );
};

}  // namespace atmospheric
}  // namespace environment
}  // namespace physics
}  // namespace ostk

#endif
