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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ostk
{
namespace physics
{
namespace environment
{
namespace gravitational
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using GeographicLib::GravityModel;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Earth::Impl
{
   public:
    Impl(const Earth::Type& aType);

    virtual ~Impl() = 0;

    virtual Impl* clone() const = 0;

    Earth::Type getType() const;

    virtual Vector3d getFieldValueAt(const Vector3d& aPosition, const Instant& anInstant) const = 0;

   private:
    Earth::Type type_;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Earth::Impl::Impl(const Earth::Type& aType)

    : type_(aType)

{
}

Earth::Impl::~Impl() {}

Earth::Type Earth::Impl::getType() const
{
    return type_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Earth::SphericalImpl : public Earth::Impl
{
   public:
    SphericalImpl(const Earth::Type& aType);

    ~SphericalImpl();

    virtual SphericalImpl* clone() const override;

    virtual Vector3d getFieldValueAt(const Vector3d& aPosition, const Instant& anInstant) const override;

   private:
    Spherical sphericalModel_;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Earth::SphericalImpl::SphericalImpl(const Earth::Type& aType)

    : Earth::Impl(aType),
      sphericalModel_(ostk::physics::env::obj::celest::Earth::Models::Spherical::GravitationalParameter)

{
}

Earth::SphericalImpl::~SphericalImpl() {}

Earth::SphericalImpl* Earth::SphericalImpl::clone() const
{
    return new Earth::SphericalImpl(*this);
}

Vector3d Earth::SphericalImpl::getFieldValueAt(const Vector3d& aPosition, const Instant& anInstant) const
{
    return sphericalModel_.getFieldValueAt(aPosition, anInstant);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

    virtual Vector3d getFieldValueAt(const Vector3d& aPosition, const Instant& anInstant) const override;

   private:
    GravityModel* gravityModelPtr_;

    static GravityModel* GravityModelFromType(
        const Earth::Type& aType,
        const Directory& aDataDirectory,
        const Integer& aGravityModelDegree,
        const Integer& aGravityModelOrder
    );
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Earth::ExternalImpl::ExternalImpl(
    const Earth::Type& aType,
    const Directory& aDataDirectory,
    const Integer& aGravityModelDegree,
    const Integer& aGravityModelOrder
)

    : Earth::Impl(aType),
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
        if (Manager::Get().isEnabled())
        {
            if (!Manager::Get().hasDataFileForType(aType))
            {
                Manager::Get().fetchDataFileForType(aType);
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Earth::Earth(
    const Earth::Type& aType,
    const Directory& aDataDirectory,
    const Integer& aGravityModelDegree,
    const Integer& aGravityModelOrder
)
    : Model(),
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

Earth::Type Earth::getType() const
{
    return implUPtr_->getType();
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
    if (aType == Earth::Type::Spherical)
    {
        return std::make_unique<Earth::SphericalImpl>(aType);
    }

    return std::make_unique<Earth::ExternalImpl>(aType, aDataDirectory, aGravityModelDegree, aGravityModelOrder);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}  // namespace gravitational
}  // namespace environment
}  // namespace physics
}  // namespace ostk

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
