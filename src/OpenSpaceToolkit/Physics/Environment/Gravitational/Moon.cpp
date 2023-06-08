/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Moon.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Spherical.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Objects/CelestialBodies/Moon.hpp>

namespace ostk
{
namespace physics
{
namespace environment
{
namespace gravitational
{

const Model::Parameters Moon::SphericalParameters = {
    {4902.8000e9, GravitationalParameterSIUnit}, Length::Meters(1738.14e3), 0.00125, 0.0, 0.0};

class Moon::Impl
{
   public:
    Impl(const Moon::Type& aType);

    virtual ~Impl() = 0;

    virtual Impl* clone() const = 0;

    Moon::Type getType() const;

    virtual Vector3d getFieldValueAt(const Vector3d& aPosition, const Instant& anInstant) const = 0;

   private:
    Moon::Type type_;
};

Moon::Impl::Impl(const Moon::Type& aType)

    : type_(aType)
{
}

Moon::Impl::~Impl() {}

Moon::Type Moon::Impl::getType() const
{
    return type_;
}

class Moon::SphericalImpl : public Moon::Impl
{
   public:
    SphericalImpl(const Moon::Type& aType);

    ~SphericalImpl();

    virtual SphericalImpl* clone() const override;

    virtual Vector3d getFieldValueAt(const Vector3d& aPosition, const Instant& anInstant) const override;

   private:
    Spherical sphericalModel_;
};

Moon::SphericalImpl::SphericalImpl(const Moon::Type& aType)

    : Moon::Impl(aType),
      sphericalModel_(Moon::SphericalParameters)
{
}

Moon::SphericalImpl::~SphericalImpl() {}

Moon::SphericalImpl* Moon::SphericalImpl::clone() const
{
    return new Moon::SphericalImpl(*this);
}

Vector3d Moon::SphericalImpl::getFieldValueAt(const Vector3d& aPosition, const Instant& anInstant) const
{
    return sphericalModel_.getFieldValueAt(aPosition, anInstant);
}

Moon::Moon(const Moon::Type& aType, const Directory& aDataDirectory)
    : Model(Moon::ParametersFromType(aType)),
      implUPtr_(Moon::ImplFromType(aType, aDataDirectory))
{
}

Moon::Moon(const Moon& aMoonGravitationalModel)
    : Model(aMoonGravitationalModel),
      implUPtr_((aMoonGravitationalModel.implUPtr_ != nullptr) ? aMoonGravitationalModel.implUPtr_->clone() : nullptr)
{
}

Moon& Moon::operator=(const Moon& aMoonGravitationalModel)
{
    if (this != &aMoonGravitationalModel)
    {
        Model::operator=(aMoonGravitationalModel);

        implUPtr_.reset(
            (aMoonGravitationalModel.implUPtr_ != nullptr) ? aMoonGravitationalModel.implUPtr_->clone() : nullptr
        );
    }

    return *this;
}

Moon::~Moon() {}

Moon* Moon::clone() const
{
    return new Moon(*this);
}

bool Moon::isDefined() const
{
    return implUPtr_ != nullptr;
}

Moon::Type Moon::getType() const
{
    return implUPtr_->getType();
}

Vector3d Moon::getFieldValueAt(const Vector3d& aPosition, const Instant& anInstant) const
{
    return implUPtr_->getFieldValueAt(aPosition, anInstant);
}

Model::Parameters Moon::ParametersFromType(const Moon::Type& aType)
{
    switch (aType)
    {
        case (Moon::Type::Spherical):
            return Moon::SphericalParameters;

        case (Moon::Type::Undefined):
            return Moon::Parameters::Undefined();

        default:
            throw ostk::core::error::runtime::Wrong("Type");
    }
}

Unique<Moon::Impl> Moon::ImplFromType(const Moon::Type& aType, const Directory& aDataDirectory)
{
    (void)aDataDirectory;  // Temporary

    if (aType == Moon::Type::Undefined)
    {
        return nullptr;
    }
    if (aType == Moon::Type::Spherical)
    {
        return std::make_unique<Moon::SphericalImpl>(aType);
    }

    throw ostk::core::error::runtime::ToBeImplemented("Non spherical Moon gravity field type");
}

}  // namespace gravitational
}  // namespace environment
}  // namespace physics
}  // namespace ostk
