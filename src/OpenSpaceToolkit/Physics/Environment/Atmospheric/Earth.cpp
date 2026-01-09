/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/Exponential.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/NRLMSISE00.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Object/Celestial/Earth.hpp>

namespace ostk
{
namespace physics
{
namespace environment
{
namespace atmospheric
{

using ostk::physics::coordinate::Frame;
using ExponentialModel = ostk::physics::environment::atmospheric::earth::Exponential;
using ostk::physics::environment::atmospheric::earth::NRLMSISE00;
using EarthCelestial = ostk::physics::environment::object::celestial::Earth;
using EarthGravitationalModel = ostk::physics::environment::gravitational::Earth;

class Earth::Impl
{
   public:
    Impl(
        const Earth::Type& aType,
        const Earth::InputDataType& anInputDataType,
        const Shared<const Frame>& anEarthFrameSPtr,
        const Length& anEarthRadius,
        const Real& anEarthFlattening
    );

    virtual ~Impl() = 0;

    virtual Impl* clone() const = 0;

    Earth::Type getType() const;

    Earth::InputDataType getInputDataType() const;

    virtual Real getDensityAt(const LLA& aLLA, const Instant& anInstant) const = 0;

    Real getDensityAt(const Position& aPosition, const Instant& anInstant) const;

    protected:
     Shared<const Frame> earthFrameSPtr_;
     Length earthRadius_;
     Real earthFlattening_;

   private:
    Earth::Type type_;
    Earth::InputDataType inputDataType_;
};

Earth::Impl::Impl(
    const Earth::Type& aType,
    const Earth::InputDataType& anInputDataType,
    const Shared<const Frame>& anEarthFrameSPtr,
    const Length& anEarthRadius,
    const Real& anEarthFlattening
)
    : earthFrameSPtr_(anEarthFrameSPtr),
      earthRadius_(anEarthRadius),
      earthFlattening_(anEarthFlattening),
      type_(aType),
      inputDataType_(anInputDataType)
{
}

Earth::Impl::~Impl() {}

Earth::Type Earth::Impl::getType() const
{
    return type_;
}

Earth::InputDataType Earth::Impl::getInputDataType() const
{
    return inputDataType_;
}

Real Earth::Impl::getDensityAt(const Position& aPosition, const Instant& anInstant) const
{
    const LLA lla = LLA::Cartesian(aPosition.getCoordinates(), earthRadius_, earthFlattening_);
    return this->getDensityAt(lla, anInstant);
}

class Earth::ExponentialImpl : public Earth::Impl
{
   public:
    ExponentialImpl(
        const Earth::Type& aType,
        const Earth::InputDataType& anInputDataType,
        const Shared<const Frame>& anEarthFrameSPtr,
        const Length& anEarthRadius,
        const Real& anEarthFlattening
    );

    ~ExponentialImpl();

    virtual ExponentialImpl* clone() const override;

    virtual Real getDensityAt(const LLA& aLLA, const Instant& anInstant) const override;

   private:
   ExponentialModel exponentialModel_;
};

Earth::ExponentialImpl::ExponentialImpl(
    const Earth::Type& aType,
    const Earth::InputDataType& anInputDataType,
    const Shared<const Frame>& anEarthFrameSPtr,
    const Length& anEarthRadius,
    const Real& anEarthFlattening
)
    : Earth::Impl(aType, anInputDataType, anEarthFrameSPtr, anEarthRadius, anEarthFlattening)
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

class Earth::NRLMSISE00Impl : public Earth::Impl
{
   public:
    NRLMSISE00Impl(
        const Earth::Type& aType,
        const Earth::InputDataType& anEarthInputDataType,
        const NRLMSISE00::InputDataType& anInputDataType,
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

   private:
    NRLMSISE00 NRLMSISE00Model_;
};

Earth::NRLMSISE00Impl::NRLMSISE00Impl(
    const Earth::Type& aType,
    const Earth::InputDataType& anEarthInputDataType,
    const NRLMSISE00::InputDataType& anInputDataType,
    const Real& aF107ConstantValue,
    const Real& aF107AConstantValue,
    const Real& aKpConstantValue,
    const Shared<const Frame>& anEarthFrameSPtr,
    const Length& anEarthRadius,
    const Real& anEarthFlattening,
    const Shared<Celestial>& aSunCelestialSPtr
)
    : Earth::Impl(aType, anEarthInputDataType, anEarthFrameSPtr, anEarthRadius, anEarthFlattening),
      NRLMSISE00Model_(
          anInputDataType,
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

Earth::Earth(
    const Earth::Type& aType,
    const Earth::InputDataType& anInputDataType,
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
          anInputDataType,
          aF107ConstantValue,
          aF107AConstantValue,
          aKpConstantValue,
          anEarthFrameSPtr,
          anEarthRadius,
          anEarthFlattening,
          aSunCelestialSPtr
      ))
{
    if (anEarthRadius.isDefined())
    {
        std::cout << "Warning: Earth radius will be removed in a future release as it is no longer needed. Please use the appropriate named static constructors." << std::endl;
    }
    if (anEarthFlattening.isDefined())
    {
        std::cout << "Warning: Earth flattening will be removed in a future release as it is no longer needed. Please use the appropriate named static constructors." << std::endl;
    }
    if (anEarthFrameSPtr != nullptr)
    {
        std::cout << "Warning: Earth frame will be removed in a future release as it is no longer needed. Please use the appropriate named static constructors." << std::endl;
    }
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

Earth::InputDataType Earth::getInputDataType() const
{
    return implUPtr_->getInputDataType();
}

Real Earth::getDensityAt(const Position& aPosition, const Instant& anInstant) const
{
    return implUPtr_->getDensityAt(aPosition, anInstant);
}

Real Earth::getDensityAt(const LLA& aLLA, const Instant& anInstant) const
{
    return implUPtr_->getDensityAt(aLLA, anInstant);
}

Real Earth::getDensityAt(const Position& aPosition, const Instant& anInstant, const Length& anEquatorialRadius, const Real& aFlattening) const
{
    const LLA lla = LLA::Cartesian(aPosition.getCoordinates(), anEquatorialRadius, aFlattening);
    return this->getDensityAt(lla, anInstant);
}

Earth Earth::Exponential()
{
    return Earth(Earth::Type::Exponential, Earth::InputDataType::Undefined, Real::Undefined(), Real::Undefined(), Real::Undefined(), nullptr, Length::Undefined(), Real::Undefined(), nullptr);
}

Earth Earth::NRLMSISE00WithCSSI(const Shared<Celestial>& aSunCelestialSPtr)
{
    return Earth(Earth::Type::NRLMSISE00, Earth::InputDataType::CSSISpaceWeatherFile, Real::Undefined(), Real::Undefined(), Real::Undefined(), nullptr, Length::Undefined(), Real::Undefined(), aSunCelestialSPtr);
}

Earth Earth::NRLMSISE00WithConstantFlux(const Real& aF107ConstantValue, const Real& aF107AConstantValue, const Real& aKpConstantValue)
{
    return Earth(Earth::Type::NRLMSISE00, Earth::InputDataType::ConstantFluxAndGeoMag, aF107ConstantValue, aF107AConstantValue, aKpConstantValue, nullptr, Length::Undefined(), Real::Undefined(), nullptr);
}


Unique<Earth::Impl> Earth::ImplFromType(
    const Earth::Type& aType,
    const Earth::InputDataType& anInputDataType,
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
            aType, anInputDataType, anEarthFrameSPtr, anEarthRadius, anEarthFlattening
        );
    }
    else if (aType == Earth::Type::NRLMSISE00)
    {
        if (anInputDataType == Earth::InputDataType::Undefined ||
            anInputDataType == Earth::InputDataType::CSSISpaceWeatherFile)
        {
            return std::make_unique<NRLMSISE00Impl>(
                aType,
                anInputDataType,
                NRLMSISE00::InputDataType::CSSISpaceWeatherFile,
                aF107ConstantValue,
                aF107AConstantValue,
                aKpConstantValue,
                anEarthFrameSPtr,
                anEarthRadius,
                anEarthFlattening,
                aSunCelestialSPtr
            );
        }
        else if (anInputDataType == Earth::InputDataType::ConstantFluxAndGeoMag)
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
                anInputDataType,
                NRLMSISE00::InputDataType::ConstantFluxAndGeoMag,
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
