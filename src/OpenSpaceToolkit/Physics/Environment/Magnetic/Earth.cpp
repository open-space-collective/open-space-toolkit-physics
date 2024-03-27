/// Apache License 2.0

#include <GeographicLib/Constants.hpp>
#include <GeographicLib/Geocentric.hpp>
#include <GeographicLib/MagneticModel.hpp>
#include <GeographicLib/Utility.hpp>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/RotationMatrix.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Magnetic/Dipole.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Magnetic/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Magnetic/Earth/Manager.hpp>

namespace ostk
{
namespace physics
{
namespace environment
{
namespace magnetic
{

using GeographicLib::MagneticModel;

/// @brief                      Coefficients from the 2005 DGRF
///
/// @ref                        Markley F. L., Fundamentals of Spacecraft Attitude Determination and Control, p. 404

static const Real a = 6371.2 * 1e3;        // [m]
static const Real g_01 = -29554.63 / 1e9;  // [T]
static const Real g_11 = -1669.05 / 1e9;   // [T]
static const Real h_11 = 5077.99 / 1e9;    // [T]

static const Vector3d EarthMagneticMoment = Vector3d {g_11, h_11, g_01} * (a * a * a) * 1e7;  // [A⋅m2]

static const Dipole EarthDipole = {EarthMagneticMoment};

class Earth::Impl
{
   public:
    Impl(const Earth::Type& aType, const Directory& aDataDirectory);

    Impl(const Impl& anImpl);

    ~Impl();

    Earth::Type getType() const;
    Directory getDataDirectory() const;

    bool isDefined() const;

    Vector3d getFieldValueAt(const Vector3d& aPosition, const Instant& anInstant) const;

   private:
    Earth::Type type_;
    Directory dataDirectory_;

    Unique<MagneticModel> magneticModelUPtr_;

    static MagneticModel* MagneticModelFromType(const Earth::Type& aType, const Directory& aDataDirectory);
};

Earth::Impl::Impl(const Earth::Type& aType, const Directory& aDataDirectory)
    : type_(aType),
      dataDirectory_(aDataDirectory),
      magneticModelUPtr_(Earth::Impl::MagneticModelFromType(aType, aDataDirectory))
{
}

Earth::Impl::Impl(const Earth::Impl& anImpl)
    : type_(anImpl.getType()),
      dataDirectory_(anImpl.getDataDirectory()),
      magneticModelUPtr_(Earth::Impl::MagneticModelFromType(anImpl.getType(), anImpl.getDataDirectory()))
{
}

Earth::Impl::~Impl() {}

Earth::Type Earth::Impl::getType() const
{
    return type_;
}

Directory Earth::Impl::getDataDirectory() const
{
    return dataDirectory_;
}

bool Earth::Impl::isDefined() const
{
    return magneticModelUPtr_ != nullptr;
}

Vector3d Earth::Impl::getFieldValueAt(const Vector3d& aPosition, const Instant& anInstant) const
{
    using GeographicLib::Geocentric;

    using ostk::core::type::Integer;

    using ostk::mathematics::geometry::d3::transformation::rotation::RotationMatrix;

    using ostk::physics::time::Scale;

    if (type_ == Earth::Type::Dipole)
    {
        return EarthDipole.getFieldValueAt(aPosition, anInstant);
    }

    const Integer year = anInstant.getDateTime(Scale::UTC).accessDate().getYear();

    if (((year < static_cast<int>(magneticModelUPtr_->MinTime())) ||
         (year > static_cast<int>(magneticModelUPtr_->MaxTime()))))
    {
        throw ostk::core::error::RuntimeError(
            "Year [{}] is out of [{}, {}] bounds.", year, magneticModelUPtr_->MinTime(), magneticModelUPtr_->MaxTime()
        );
    }

    static const Geocentric earthGeocentric = Geocentric::WGS84();

    double latitude_deg;   // [deg]
    double longitude_deg;  // [deg]
    double altitude_m;     // [m]

    earthGeocentric.Reverse(aPosition.x(), aPosition.y(), aPosition.z(), latitude_deg, longitude_deg, altitude_m);

    double Bx_nT;  // [nT] Easterly component of the magnetic field
    double By_nT;  // [nT] Northerly component of the magnetic field
    double Bz_nT;  // [nT] Vertical component of the magnetic field

    (*magneticModelUPtr_)(year, latitude_deg, longitude_deg, altitude_m, Bx_nT, By_nT, Bz_nT);

    const Vector3d magneticField_NED = Vector3d {By_nT, Bx_nT, -Bz_nT} / 1e9;  // [T]

    const double latitude_rad = latitude_deg * M_PI / 180.0;    // [rad]
    const double longitude_rad = longitude_deg * M_PI / 180.0;  // [rad]

    const Real cos_lat = std::cos(latitude_rad);
    const Real sin_lat = std::sin(latitude_rad);

    const Real cos_lon = std::cos(longitude_rad);
    const Real sin_lon = std::sin(longitude_rad);

    const RotationMatrix dcm_ECEF_NED = {
        -sin_lat * cos_lon,
        -sin_lon,
        -cos_lat * cos_lon,
        -sin_lat * sin_lon,
        +cos_lon,
        -cos_lat * sin_lon,
        +cos_lat,
        0.0,
        -sin_lat
    };

    const Vector3d magneticField = dcm_ECEF_NED * magneticField_NED;  // [T]

    return magneticField;
}

MagneticModel* Earth::Impl::MagneticModelFromType(const Earth::Type& aType, const Directory& aDataDirectory)
{
    using ostk::core::type::String;

    using ostk::physics::environment::magnetic::earth::Manager;

    // TBI: move dipole to an implementation class to align with other models
    if (aType == Earth::Type::Undefined || aType == Earth::Type::Dipole)
    {
        return nullptr;
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

    switch (aType)
    {
        case Earth::Type::EMM2010:
            return new GeographicLib::MagneticModel("emm2010", dataPath);

        case Earth::Type::EMM2015:
            return new GeographicLib::MagneticModel("emm2015", dataPath);

        case Earth::Type::EMM2017:
            return new GeographicLib::MagneticModel("emm2017", dataPath);

        case Earth::Type::IGRF11:
            return new GeographicLib::MagneticModel("igrf11", dataPath);

        case Earth::Type::IGRF12:
            return new GeographicLib::MagneticModel("igrf12", dataPath);

        case Earth::Type::WMM2010:
            return new GeographicLib::MagneticModel("wmm2010", dataPath);

        case Earth::Type::WMM2015:
            return new GeographicLib::MagneticModel("wmm2015", dataPath);

        default:
            throw ostk::core::error::runtime::Wrong("Type");
    }

    return nullptr;
}

Earth::Earth(const Earth::Type& aType, const Directory& aDataDirectory)
    : Model(),
      implUPtr_(std::make_unique<Earth::Impl>(aType, aDataDirectory))
{
}

Earth::Earth(const Earth& anEarthMagneticModel)
    : Model(anEarthMagneticModel),
      implUPtr_(
          (anEarthMagneticModel.implUPtr_ != nullptr) ? std::make_unique<Earth::Impl>(*anEarthMagneticModel.implUPtr_)
                                                      : nullptr
      )
{
}

Earth& Earth::operator=(const Earth& anEarthMagneticModel)
{
    if (this != &anEarthMagneticModel)
    {
        Model::operator=(anEarthMagneticModel);

        implUPtr_.reset(
            (anEarthMagneticModel.implUPtr_ != nullptr) ? new Earth::Impl(*anEarthMagneticModel.implUPtr_) : nullptr
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
    if (implUPtr_ == nullptr)
    {
        return false;
    }

    return implUPtr_->isDefined();
}

Earth::Type Earth::getType() const
{
    return implUPtr_->getType();
}

Vector3d Earth::getFieldValueAt(const Vector3d& aPosition, const Instant& anInstant) const
{
    return implUPtr_->getFieldValueAt(aPosition, anInstant);
}

}  // namespace magnetic
}  // namespace environment
}  // namespace physics
}  // namespace ostk
