/// Apache License 2.0

#include <cmath>

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
using ostk::physics::environment::atmospheric::earth::Exponential;
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
        double anEarthFlattening
    );

    virtual ~Impl() = 0;

    virtual Impl* clone() const = 0;

    Earth::Type getType() const;

    Earth::InputDataType getInputDataType() const;

    virtual double getDensityAt(const LLA& aLLA, const Instant& anInstant) const = 0;

    virtual double getDensityAt(const Position& aPosition, const Instant& anInstant) const = 0;

   protected:
    Shared<const Frame> earthFrameSPtr_;
    Length earthRadius_;
    double earthFlattening_;

   private:
    Earth::Type type_;
    Earth::InputDataType inputDataType_;
};

Earth::Impl::Impl(
    const Earth::Type& aType,
    const Earth::InputDataType& anInputDataType,
    const Shared<const Frame>& anEarthFrameSPtr,
    const Length& anEarthRadius,
    double anEarthFlattening
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

class Earth::ExponentialImpl : public Earth::Impl
{
   public:
    ExponentialImpl(
        const Earth::Type& aType,
        const Earth::InputDataType& anInputDataType,
        const Shared<const Frame>& anEarthFrameSPtr,
        const Length& anEarthRadius,
        double anEarthFlattening
    );

    ~ExponentialImpl();

    virtual ExponentialImpl* clone() const override;

    virtual double getDensityAt(const LLA& aLLA, const Instant& anInstant) const override;

    virtual double getDensityAt(const Position& aPosition, const Instant& anInstant) const override;

   private:
    Exponential exponentialModel_;
};

Earth::ExponentialImpl::ExponentialImpl(
    const Earth::Type& aType,
    const Earth::InputDataType& anInputDataType,
    const Shared<const Frame>& anEarthFrameSPtr,
    const Length& anEarthRadius,
    double anEarthFlattening
)
    : Earth::Impl(aType, anInputDataType, anEarthFrameSPtr, anEarthRadius, anEarthFlattening)
{
}

Earth::ExponentialImpl::~ExponentialImpl() {}

Earth::ExponentialImpl* Earth::ExponentialImpl::clone() const
{
    return new Earth::ExponentialImpl(*this);
}

double Earth::ExponentialImpl::getDensityAt(const LLA& aLLA, const Instant& anInstant) const
{
    return this->exponentialModel_.getDensityAt(aLLA, anInstant);
}

double Earth::ExponentialImpl::getDensityAt(const Position& aPosition, const Instant& anInstant) const
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
        const Earth::InputDataType& anEarthInputDataType,
        const NRLMSISE00::InputDataType& anInputDataType,
        double aF107ConstantValue,
        double aF107AConstantValue,
        double aKpConstantValue,
        const Shared<const Frame>& anEarthFrameSPtr,
        const Length& anEarthRadius,
        double anEarthFlattening,
        const Shared<Celestial>& aSunCelestialSPtr
    );

    ~NRLMSISE00Impl();

    virtual NRLMSISE00Impl* clone() const override;

    virtual double getDensityAt(const LLA& aLLA, const Instant& anInstant) const override;

    virtual double getDensityAt(const Position& aPosition, const Instant& anInstant) const override;

   private:
    NRLMSISE00 NRLMSISE00Model_;
};

Earth::NRLMSISE00Impl::NRLMSISE00Impl(
    const Earth::Type& aType,
    const Earth::InputDataType& anEarthInputDataType,
    const NRLMSISE00::InputDataType& anInputDataType,
    double aF107ConstantValue,
    double aF107AConstantValue,
    double aKpConstantValue,
    const Shared<const Frame>& anEarthFrameSPtr,
    const Length& anEarthRadius,
    double anEarthFlattening,
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

double Earth::NRLMSISE00Impl::getDensityAt(const LLA& aLLA, const Instant& anInstant) const
{
    return this->NRLMSISE00Model_.getDensityAt(aLLA, anInstant);
}

double Earth::NRLMSISE00Impl::getDensityAt(const Position& aPosition, const Instant& anInstant) const
{
    return this->NRLMSISE00Model_.getDensityAt(
        LLA::Cartesian(aPosition.inFrame(earthFrameSPtr_, anInstant).getCoordinates(), earthRadius_, earthFlattening_),
        anInstant
    );
}

Earth::Earth(
    const Earth::Type& aType,
    const Earth::InputDataType& anInputDataType,
    double aF107ConstantValue,
    double aF107AConstantValue,
    double aKpConstantValue,
    const Shared<const Frame>& anEarthFrameSPtr,
    const Length& anEarthRadius,
    double anEarthFlattening,
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
}

Earth::Earth(
    const Earth::Type& aType,
    const Shared<const Frame>& anEarthFrameSPtr,
    const Earth::InputDataType& anInputDataType,
    double aF107ConstantValue,
    double aF107AConstantValue,
    double aKpConstantValue,
    const Length& anEarthRadius,
    double anEarthFlattening,
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

Earth::Type Earth::getType() const
{
    return implUPtr_->getType();
}

Earth::InputDataType Earth::getInputDataType() const
{
    return implUPtr_->getInputDataType();
}

double Earth::getDensityAt(const Position& aPosition, const Instant& anInstant) const
{
    return implUPtr_->getDensityAt(aPosition, anInstant);
}

double Earth::getDensityAt(const LLA& aLLA, const Instant& anInstant) const
{
    return implUPtr_->getDensityAt(aLLA, anInstant);
}

Unique<Earth::Impl> Earth::ImplFromType(
    const Earth::Type& aType,
    const Earth::InputDataType& anInputDataType,
    double aF107ConstantValue,
    double aF107AConstantValue,
    double aKpConstantValue,
    const Shared<const Frame>& anEarthFrameSPtr,
    const Length& anEarthRadius,
    double anEarthFlattening,
    const Shared<Celestial>& aSunCelestialSPtr
)
{
    if (aType == Earth::Type::Exponential)
    {
        return std::make_unique<ExponentialImpl>(
            aType, anInputDataType, anEarthFrameSPtr, anEarthRadius, anEarthFlattening
        );
    }
    else if (aType == Earth::Type::NRLMSISE00)
    {
        if (anInputDataType == Earth::InputDataType::CSSISpaceWeatherFile)
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
            if (std::isnan(aF107ConstantValue))
            {
                throw ostk::core::error::runtime::Undefined("F10.7 constant value");
            }
            else if (std::isnan(aF107AConstantValue))
            {
                throw ostk::core::error::runtime::Undefined("F10.7a constant value");
            }
            else if (std::isnan(aKpConstantValue))
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
