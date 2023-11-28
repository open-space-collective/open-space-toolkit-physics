/// Apache License 2.0

#include <GeographicLib/Constants.hpp>
#include <GeographicLib/GravityModel.hpp>
#include <GeographicLib/Utility.hpp>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Earth/Manager.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Spherical.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Objects/CelestialBodies/Earth.hpp>

namespace ostk
{
namespace physics
{
namespace environment
{
namespace gravitational
{

using GeographicLib::GravityModel;

using ostk::physics::units::Derived;
using ostk::physics::units::Length;
using ostk::physics::units::Time;
using SphericalGravitationalModel = ostk::physics::environment::gravitational::Spherical;

// EGM2008

const Model::Parameters Earth::EGM2008 = {
    {398600441500000.0, GravitationalParameterSIUnit},
    Length::Meters(6378137.0),
    1.0 / 298.257223563,
    -4.84169317366974e-04,
    5.39965866638991e-07,
};

// EGM96 + WGS84

const Model::Parameters Earth::WGS84_EGM96 = {
    {398600441800000.0, GravitationalParameterSIUnit},
    Length::Meters(6378137.0),
    1.0 / 298.257223563,
    -4.841653717360e-04,
    5.398738637890e-07,
};

// EGM96

const Model::Parameters Earth::EGM96 = {
    {398600441500000.0, GravitationalParameterSIUnit},
    Length::Meters(6378136.3),
    1.0 / 298.257223563,
    -4.841653717360e-04,
    5.398738637890e-07,
};

// EGM84

const Model::Parameters Earth::EGM84 = {
    {398600441800000.0, GravitationalParameterSIUnit},
    Length::Meters(6378137.0),
    1.0 / 298.257223563,
    -4.841668500000e-04,
    5.369958670000e-07,
};

// WGS84

const Model::Parameters Earth::WGS84 = {
    {398600441800000.0, GravitationalParameterSIUnit},
    Length::Meters(6378137.0),
    1.0 / 298.257223563,
    -4.841668500000e-04,
    5.369958670000e-07,
};

// Spherical

const Model::Parameters Earth::Spherical = {
    {398600441500000.0, GravitationalParameterSIUnit},
    Length::Meters(6378137.0),
    0.0,
    0.0,
    0.0,
};

class Earth::Impl
{
   public:
    Impl(const Earth::Type& aType);

    virtual ~Impl() = 0;

    virtual Impl* clone() const = 0;

    Earth::Type getType() const;

    virtual Integer getDegree() const = 0;

    virtual Integer getOrder() const = 0;

    virtual Vector3d getFieldValueAt(const Vector3d& aPosition, const Instant& anInstant) const = 0;

   private:
    Earth::Type type_;
};

Earth::Impl::Impl(const Earth::Type& aType)

    : type_(aType)

{
}

Earth::Impl::~Impl() {}

Earth::Type Earth::Impl::getType() const
{
    return type_;
}

class Earth::SphericalImpl : public Earth::Impl
{
   public:
    SphericalImpl(const Earth::Type& aType);

    ~SphericalImpl();

    virtual SphericalImpl* clone() const override;

    virtual Integer getDegree() const override;

    virtual Integer getOrder() const override;

    virtual Vector3d getFieldValueAt(const Vector3d& aPosition, const Instant& anInstant) const override;

   private:
    SphericalGravitationalModel sphericalModel_;
};

Earth::SphericalImpl::SphericalImpl(const Earth::Type& aType)

    : Earth::Impl(aType),
      sphericalModel_(Earth::Spherical)

{
}

Earth::SphericalImpl::~SphericalImpl() {}

Earth::SphericalImpl* Earth::SphericalImpl::clone() const
{
    return new Earth::SphericalImpl(*this);
}

Integer Earth::SphericalImpl::getDegree() const
{
    return Integer::Undefined();
}

Integer Earth::SphericalImpl::getOrder() const
{
    return Integer::Undefined();
}

Vector3d Earth::SphericalImpl::getFieldValueAt(const Vector3d& aPosition, const Instant& anInstant) const
{
    return sphericalModel_.getFieldValueAt(aPosition, anInstant);
}

class Earth::ExternalImpl : public Earth::Impl
{
   public:
    ExternalImpl(
        const Earth::Type& aType,
        const Directory& aDataDirectory,
        const Integer& aGravityModelDegree,
        const Integer& aGravityModelOrder
    );

    ~ExternalImpl();

    virtual ExternalImpl* clone() const override;

    virtual Integer getDegree() const override;

    virtual Integer getOrder() const override;

    virtual Vector3d getFieldValueAt(const Vector3d& aPosition, const Instant& anInstant) const override;

   private:
    Integer gravityModelDegree_;
    Integer gravityModelOrder_;
    GravityModel* gravityModelPtr_;

    static GravityModel* GravityModelFromType(
        const Earth::Type& aType,
        const Directory& aDataDirectory,
        const Integer& aGravityModelDegree,
        const Integer& aGravityModelOrder
    );
};

Earth::ExternalImpl::ExternalImpl(
    const Earth::Type& aType,
    const Directory& aDataDirectory,
    const Integer& aGravityModelDegree,
    const Integer& aGravityModelOrder
)

    : Earth::Impl(aType),
      gravityModelDegree_(aGravityModelDegree),
      gravityModelOrder_(aGravityModelOrder),
      gravityModelPtr_(
          Earth::ExternalImpl::GravityModelFromType(aType, aDataDirectory, aGravityModelDegree, aGravityModelOrder)
      )

{
}

Earth::ExternalImpl::~ExternalImpl()
{
    delete gravityModelPtr_;
}

Earth::ExternalImpl* Earth::ExternalImpl::clone() const
{
    return new Earth::ExternalImpl(*this);
}

Integer Earth::ExternalImpl::getDegree() const
{
    return gravityModelDegree_;
}

Integer Earth::ExternalImpl::getOrder() const
{
    return gravityModelOrder_;
}

Vector3d Earth::ExternalImpl::getFieldValueAt(const Vector3d& aPosition, const Instant& anInstant) const
{
    (void)anInstant;  // Temporal invariance

    double g_x;
    double g_y;
    double g_z;

    gravityModelPtr_->V(aPosition.x(), aPosition.y(), aPosition.z(), g_x, g_y, g_z);

    return {g_x, g_y, g_z};
}

GravityModel* Earth::ExternalImpl::GravityModelFromType(
    const Earth::Type& aType,
    const Directory& aDataDirectory,
    const Integer& aGravityModelDegree,
    const Integer& aGravityModelOrder
)
{
    using ostk::core::types::String;

    using ostk::physics::environment::gravitational::earth::Manager;

    if (aType == Earth::Type::Spherical)
    {
        throw ostk::core::error::runtime::Wrong("Type");
    }

    String dataPath = "";

    if (aDataDirectory.isDefined())
    {
        if (!aDataDirectory.exists())
        {
            throw ostk::core::error::RuntimeError("Data directory [{}] does not exist.", aDataDirectory.toString());
        }

        dataPath = aDataDirectory.getPath().toString();
    }
    else
    {
        if (Manager::Get().getMode() == Manager::Mode::Automatic)
        {
            if (!Manager::Get().hasDataFilesForType(aType))
            {
                Manager::Get().fetchDataFilesForType(aType);
            }

            dataPath = Manager::Get().getLocalRepository().getPath().toString();
        }
    }

    const Integer gravityModelDegree = aGravityModelDegree.isDefined() ? aGravityModelDegree : Integer(-1);
    const Integer gravityModelOrder = aGravityModelOrder.isDefined() ? aGravityModelOrder : Integer(-1);

    switch (aType)
    {
        case Earth::Type::WGS84:
        {
            if (gravityModelDegree > 20)
            {
                throw ostk::core::error::runtime::Wrong("Gravity Model Degree", gravityModelDegree);
            }

            if (gravityModelOrder > 0)
            {
                throw ostk::core::error::runtime::Wrong("Gravity Model Order", gravityModelOrder);
            }

            return new GeographicLib::GravityModel("wgs84", dataPath, gravityModelDegree, gravityModelOrder);
        }

        case Earth::Type::EGM84:
        {
            if (gravityModelDegree > 180)
            {
                throw ostk::core::error::runtime::Wrong("Gravity Model Degree", gravityModelDegree);
            }

            if (gravityModelOrder > 180)
            {
                throw ostk::core::error::runtime::Wrong("Gravity Model Order", gravityModelOrder);
            }

            return new GeographicLib::GravityModel("egm84", dataPath, gravityModelDegree, gravityModelOrder);
        }

        case Earth::Type::WGS84_EGM96:
        case Earth::Type::EGM96:
        {
            if (gravityModelDegree > 360)
            {
                throw ostk::core::error::runtime::Wrong("Gravity Model Degree", gravityModelDegree);
            }

            if (gravityModelOrder > 360)
            {
                throw ostk::core::error::runtime::Wrong("Gravity Model Order", gravityModelOrder);
            }

            return new GeographicLib::GravityModel("egm96", dataPath, gravityModelDegree, gravityModelOrder);
        }

        case Earth::Type::EGM2008:
        {
            if (gravityModelDegree > 2190)
            {
                throw ostk::core::error::runtime::Wrong("Gravity Model Degree", gravityModelDegree);
            }

            if (gravityModelOrder > 2160)
            {
                throw ostk::core::error::runtime::Wrong("Gravity Model Order", gravityModelOrder);
            }

            return new GeographicLib::GravityModel("egm2008", dataPath, gravityModelDegree, gravityModelOrder);
        }

        default:
            throw ostk::core::error::runtime::Wrong("Type");
    }

    return nullptr;
}

Earth::Earth(
    const Earth::Type& aType,
    const Directory& aDataDirectory,
    const Integer& aGravityModelDegree,
    const Integer& aGravityModelOrder
)
    : Model(Earth::ParametersFromType(aType)),
      implUPtr_(Earth::ImplFromType(aType, aDataDirectory, aGravityModelDegree, aGravityModelOrder))
{
}

Earth::Earth(const Earth& anEarthGravitationalModel)
    : Model(anEarthGravitationalModel),
      implUPtr_(
          (anEarthGravitationalModel.implUPtr_ != nullptr) ? anEarthGravitationalModel.implUPtr_->clone() : nullptr
      )
{
}

Earth& Earth::operator=(const Earth& anEarthGravitationalModel)
{
    if (this != &anEarthGravitationalModel)
    {
        Model::operator=(anEarthGravitationalModel);

        implUPtr_.reset(
            (anEarthGravitationalModel.implUPtr_ != nullptr) ? anEarthGravitationalModel.implUPtr_->clone() : nullptr
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

Integer Earth::getDegree() const
{
    return implUPtr_->getDegree();
}

Integer Earth::getOrder() const
{
    return implUPtr_->getOrder();
}

Vector3d Earth::getFieldValueAt(const Vector3d& aPosition, const Instant& anInstant) const
{
    return implUPtr_->getFieldValueAt(aPosition, anInstant);
}

Unique<Earth::Impl> Earth::ImplFromType(
    const Earth::Type& aType,
    const Directory& aDataDirectory,
    const Integer& aGravityModelDegree,
    const Integer& aGravityModelOrder
)
{
    if (aType == Earth::Type::Undefined)
    {
        return nullptr;
    }
    if (aType == Earth::Type::Spherical)
    {
        return std::make_unique<Earth::SphericalImpl>(aType);
    }

    return std::make_unique<Earth::ExternalImpl>(aType, aDataDirectory, aGravityModelDegree, aGravityModelOrder);
}

Model::Parameters Earth::ParametersFromType(const Earth::Type& aType)
{
    switch (aType)
    {
        case Earth::Type::Spherical:
            return Earth::Spherical;

        case Earth::Type::WGS84:
            return Earth::WGS84;

        case Earth::Type::EGM84:
            return Earth::EGM84;

        case Earth::Type::EGM96:
            return Earth::EGM96;

        case Earth::Type::WGS84_EGM96:
            return Earth::WGS84_EGM96;

        case Earth::Type::EGM2008:
            return Earth::EGM2008;

        case Earth::Type::Undefined:
            return Earth::Parameters::Undefined();

        default:
            throw ostk::core::error::runtime::Wrong("Type");
    }
}

}  // namespace gravitational
}  // namespace environment
}  // namespace physics
}  // namespace ostk
