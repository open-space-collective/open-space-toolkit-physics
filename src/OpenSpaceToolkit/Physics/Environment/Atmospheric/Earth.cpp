/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/Exponential.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/NRLMSISE00.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Objects/CelestialBodies/Earth.hpp>

namespace ostk
{
namespace physics
{
namespace environment
{
namespace atmospheric
{

using ostk::physics::coord::Frame;
using ostk::physics::environment::atmospheric::earth::Exponential;
using ostk::physics::environment::atmospheric::earth::NRLMSISE00;
using EarthCelestialBody = ostk::physics::env::obj::celest::Earth;
using EarthGravitationalModel = ostk::physics::environment::gravitational::Earth;

class Earth::Impl
{
   public:
    Impl(
        const Earth::Type& aType,
        const Earth::InputDataSourceType& anInputDataSourceType,
        const Shared<const Frame>& anEarthFrameSPtr,
        const Length& anEarthRadius,
        const Real& anEarthFlattening
    );

    virtual ~Impl() = 0;

    virtual Impl* clone() const = 0;

    Earth::Type getType() const;

    Earth::InputDataSourceType getInputDataSourceType() const;

    virtual Real getDensityAt(const LLA& aLLA, const Instant& anInstant) const = 0;

    virtual Real getDensityAt(const Position& aPosition, const Instant& anInstant) const = 0;

   protected:
    Shared<const Frame> earthFrameSPtr_;
    Length earthRadius_;
    Real earthFlattening_;

   private:
    Earth::Type type_;
    Earth::InputDataSourceType inputDataSourceType_;
};

Earth::Impl::Impl(
    const Earth::Type& aType,
    const Earth::InputDataSourceType& anInputDataSourceType,
    const Shared<const Frame>& anEarthFrameSPtr,
    const Length& anEarthRadius,
    const Real& anEarthFlattening
)
    : earthFrameSPtr_(anEarthFrameSPtr),
      earthRadius_(anEarthRadius),
      earthFlattening_(anEarthFlattening),
      type_(aType),
      inputDataSourceType_(anInputDataSourceType)
{
}

Earth::Impl::~Impl() {}

Earth::Type Earth::Impl::getType() const
{
    return type_;
}

Earth::InputDataSourceType Earth::Impl::getInputDataSourceType() const
{
    return inputDataSourceType_;
}

class Earth::ExponentialImpl : public Earth::Impl
{
   public:
    ExponentialImpl(
        const Earth::Type& aType,
        const Earth::InputDataSourceType& anInputDataSourceType,
        const Shared<const Frame>& anEarthFrameSPtr,
        const Length& anEarthRadius,
        const Real& anEarthFlattening
    );

    ~ExponentialImpl();

    virtual ExponentialImpl* clone() const override;

    virtual Real getDensityAt(const LLA& aLLA, const Instant& anInstant) const override;

    virtual Real getDensityAt(const Position& aPosition, const Instant& anInstant) const override;

   private:
    Exponential exponentialModel_;
};

Earth::ExponentialImpl::ExponentialImpl(
    const Earth::Type& aType,
    const Earth::InputDataSourceType& anInputDataSourceType,
    const Shared<const Frame>& anEarthFrameSPtr,
    const Length& anEarthRadius,
    const Real& anEarthFlattening
)
    : Earth::Impl(aType, anInputDataSourceType, anEarthFrameSPtr, anEarthRadius, anEarthFlattening)
{
}

Earth::ExponentialImpl::~ExponentialImpl() {}

Earth::ExponentialImpl* Earth::ExponentialImpl::clone() const
{
    return new Earth::ExponentialImpl(*this);
}

Real Earth::ExponentialImpl::getDensityAt(const LLA& aLLA, const Instant& anInstant) const
{
    return this->exponentialModel_.getDensityAt(aLLA, anInstant);
}

Real Earth::ExponentialImpl::getDensityAt(const Position& aPosition, const Instant& anInstant) const
{
    return this->exponentialModel_.getDensityAt(
        LLA::Cartesian(aPosition.inFrame(earthFrameSPtr_, anInstant).getCoordinates(), earthRadius_, earthFlattening_),
        anInstant
    );
}

class Earth::NRLMSISE00Impl : public Earth::Impl
{
   public:
    NRLMSISE00Impl(
        const Earth::Type& aType,
        const Earth::InputDataSourceType& anEarthInputDataSourceType,
        const NRLMSISE00::InputDataSourceType& anInputDataSourceType,
        const Real& aF107ConstantValue,
        const Real& aF107AConstantValue,
        const Real& aKpConstantValue,
        const Shared<const Frame>& anEarthFrameSPtr,
        const Length& anEarthRadius,
        const Real& anEarthFlattening,
        const Shared<Celestial>& aSunCelestialSPtr
    );

    ~NRLMSISE00Impl();

    virtual NRLMSISE00Impl* clone() const override;

    virtual Real getDensityAt(const LLA& aLLA, const Instant& anInstant) const override;

    virtual Real getDensityAt(const Position& aPosition, const Instant& anInstant) const override;

   private:
    NRLMSISE00 NRLMSISE00Model_;
};

Earth::NRLMSISE00Impl::NRLMSISE00Impl(
    const Earth::Type& aType,
    const Earth::InputDataSourceType& anEarthInputDataSourceType,
    const NRLMSISE00::InputDataSourceType& anInputDataSourceType,
    const Real& aF107ConstantValue,
    const Real& aF107AConstantValue,
    const Real& aKpConstantValue,
    const Shared<const Frame>& anEarthFrameSPtr,
    const Length& anEarthRadius,
    const Real& anEarthFlattening,
    const Shared<Celestial>& aSunCelestialSPtr
)
    : Earth::Impl(aType, anEarthInputDataSourceType, anEarthFrameSPtr, anEarthRadius, anEarthFlattening),
      NRLMSISE00Model_(
          anInputDataSourceType,
          aF107ConstantValue,
          aF107AConstantValue,
          aKpConstantValue,
          anEarthFrameSPtr,
          anEarthRadius,
          anEarthFlattening,
          aSunCelestialSPtr
      )
{
}

Earth::NRLMSISE00Impl::~NRLMSISE00Impl() {}

Earth::NRLMSISE00Impl* Earth::NRLMSISE00Impl::clone() const
{
    return new Earth::NRLMSISE00Impl(*this);
}

Real Earth::NRLMSISE00Impl::getDensityAt(const LLA& aLLA, const Instant& anInstant) const
{
    return this->NRLMSISE00Model_.getDensityAt(aLLA, anInstant);
}

Real Earth::NRLMSISE00Impl::getDensityAt(const Position& aPosition, const Instant& anInstant) const
{
    return this->NRLMSISE00Model_.getDensityAt(
        LLA::Cartesian(aPosition.inFrame(earthFrameSPtr_, anInstant).getCoordinates(), earthRadius_, earthFlattening_),
        anInstant
    );
}

Earth::Earth(
    const Earth::Type& aType,
    const Earth::InputDataSourceType& anInputDataSourceType,
    const Real& aF107ConstantValue,
    const Real& aF107AConstantValue,
    const Real& aKpConstantValue,
    const Shared<const Frame>& anEarthFrameSPtr,
    const Length& anEarthRadius,
    const Real& anEarthFlattening,
    const Shared<Celestial>& aSunCelestialSPtr
)
    : Model(),
      implUPtr_(Earth::ImplFromType(
          aType,
          anInputDataSourceType,
          aF107ConstantValue,
          aF107AConstantValue,
          aKpConstantValue,
          anEarthFrameSPtr,
          anEarthRadius,
          anEarthFlattening,
          aSunCelestialSPtr
      ))
{
}

Earth::Earth(const Earth& anEarthAtmosphericModel)
    : Model(anEarthAtmosphericModel),
      implUPtr_((anEarthAtmosphericModel.implUPtr_ != nullptr) ? anEarthAtmosphericModel.implUPtr_->clone() : nullptr)
{
}

Earth& Earth::operator=(const Earth& anEarthAtmosphericModel)
{
    if (this != &anEarthAtmosphericModel)
    {
        Model::operator=(anEarthAtmosphericModel);

        implUPtr_.reset(
            (anEarthAtmosphericModel.implUPtr_ != nullptr) ? anEarthAtmosphericModel.implUPtr_->clone() : nullptr
        );
    }

    return *this;
}

Earth::~Earth() {}

Earth* Earth::clone() const
{
    return new Earth(*this);
}

bool Earth::isDefined() const
{
    return implUPtr_ != nullptr;
}

Earth::Type Earth::getType() const
{
    return implUPtr_->getType();
}

Earth::InputDataSourceType Earth::getInputDataSourceType() const
{
    return implUPtr_->getInputDataSourceType();
}

Real Earth::getDensityAt(const Position& aPosition, const Instant& anInstant) const
{
    return implUPtr_->getDensityAt(aPosition, anInstant);
}

Real Earth::getDensityAt(const LLA& aLLA, const Instant& anInstant) const
{
    return implUPtr_->getDensityAt(aLLA, anInstant);
}

Unique<Earth::Impl> Earth::ImplFromType(
    const Earth::Type& aType,
    const Earth::InputDataSourceType& anInputDataSourceType,
    const Real& aF107ConstantValue,
    const Real& aF107AConstantValue,
    const Real& aKpConstantValue,
    const Shared<const Frame>& anEarthFrameSPtr,
    const Length& anEarthRadius,
    const Real& anEarthFlattening,
    const Shared<Celestial>& aSunCelestialSPtr
)
{
    if (aType == Earth::Type::Undefined)
    {
        return nullptr;
    }
    else if (aType == Earth::Type::Exponential)
    {
        return std::make_unique<ExponentialImpl>(
            aType, anInputDataSourceType, anEarthFrameSPtr, anEarthRadius, anEarthFlattening
        );
    }
    else if (aType == Earth::Type::NRLMSISE00)
    {
        if (anInputDataSourceType == Earth::InputDataSourceType::Undefined)
        {
            throw ostk::core::error::runtime::Undefined("Input data source type");
        }
        else if (anInputDataSourceType == Earth::InputDataSourceType::ConstantFluxAndGeoMag)
        {
            if (!aF107ConstantValue.isDefined())
            {
                throw ostk::core::error::runtime::Undefined("F10.7 constant value");
            }
            else if (!aF107AConstantValue.isDefined())
            {
                throw ostk::core::error::runtime::Undefined("F10.7a constant value");
            }
            else if (!aKpConstantValue.isDefined())
            {
                throw ostk::core::error::runtime::Undefined("Kp constant value");
            }

            return std::make_unique<NRLMSISE00Impl>(
                aType,
                anInputDataSourceType,
                NRLMSISE00::InputDataSourceType::ConstantFluxAndGeoMag,
                aF107ConstantValue,
                aF107AConstantValue,
                aKpConstantValue,
                anEarthFrameSPtr,
                anEarthRadius,
                anEarthFlattening,
                aSunCelestialSPtr
            );
        }
        else if (anInputDataSourceType == Earth::InputDataSourceType::SpaceWeatherFile)
        {
            return std::make_unique<NRLMSISE00Impl>(
                aType,
                anInputDataSourceType,
                NRLMSISE00::InputDataSourceType::SpaceWeatherFile,
                aF107ConstantValue,
                aF107AConstantValue,
                aKpConstantValue,
                anEarthFrameSPtr,
                anEarthRadius,
                anEarthFlattening,
                aSunCelestialSPtr
            );
        }
    }

    throw ostk::core::error::runtime::Wrong("Type");
}

}  // namespace atmospheric
}  // namespace environment
}  // namespace physics
}  // namespace ostk
