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
using ostk::physics::environment::object::Celestial;
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
        NRLMSISE00,   ///< Navy Research Lab Mass Spectrometer and Incoherent Scatter Radar Exosphere 2000
    };

    enum class InputDataType
    {
        Undefined,              ///< Undefined
        ConstantFluxAndGeoMag,  ///< Use constant values for F10.7, F10.7a and Kp NRLMSISE00 input parameters
        CSSISpaceWeatherFile,   ///< Use historical and predicted values for F10.7, F10.7a and Kp NRLMSISE00 input
                                ///< parameters from CSSI
    };

    /// @brief              Constructor
    ///
    /// @param              [in] aType An atmospheric model type
    /// @param              [in] anInputDataType An input data source type
    /// @param              [in] aF107ConstantValue A constant value for F10.7 input parameter
    /// @param              [in] aF107AConstantValue A constant value for F10.7a input parameter
    /// @param              [in] aKpConstantValue A constant value for Kp input parameter
    /// @param              [in] anEarthFrameSPtr A shared pointer to the Earth frame
    /// @param              [in] anEarthRadius An Earth radius
    /// @param              [in] anEarthFlattening An Earth flattening
    /// @param              [in] aSunCelestialSPtr A shared pointer to the Sun celestial body

    Earth(
        const Earth::Type& aType,
        const Earth::InputDataType& anInputDataType = Earth::InputDataType::CSSISpaceWeatherFile,
        const Real& aF107ConstantValue = defaultF107ConstantValue,
        const Real& aF107AConstantValue = defaultF107AConstantValue,
        const Real& aKpConstantValue = defaultKpConstantValue,
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

    /// @brief              Get input data source type
    ///
    /// @return             Input data source type

    Earth::InputDataType getInputDataType() const;

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

    static constexpr double defaultF107ConstantValue = 150.0;   // 10⁻²² W⋅m⁻²⋅Hz⁻¹
    static constexpr double defaultF107AConstantValue = 150.0;  // 10⁻²² W⋅m⁻²⋅Hz⁻¹
    static constexpr double defaultKpConstantValue = 3.0;       // dimensionless

   private:
    Earth();

    class Impl;
    class ExponentialImpl;
    class NRLMSISE00Impl;

    Unique<Impl> implUPtr_;

    static Unique<Impl> ImplFromType(
        const Type& aType,
        const InputDataType& anInputDataType,
        const Real& aF107ConstantValue,
        const Real& aF107AConstantValue,
        const Real& aKpConstantValue,
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
