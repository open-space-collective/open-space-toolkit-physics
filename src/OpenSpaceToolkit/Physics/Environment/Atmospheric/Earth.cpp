////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/Manager.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth.hpp>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

#include <nrlmsise-00.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ostk
{
namespace physics
{
namespace environment
{
namespace atmospheric
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Earth::Impl
{

    public:

                                Impl                                        (   const   Earth::Type&                aType,
                                                                                const   Directory&                  aDataDirectory                              ) ;

                                ~Impl                                       ( ) ;

        Earth::Type             getType                                     ( ) const ;

        Real                    getDensityAt                                (   const   Vector3d&                   aPosition,
                                                                                const   Instant&                    anInstant                                   ) const ;

    private:

        Earth::Type             type_ ;

        //AtmosphericModel*          atmosphericModelPtr_ ;

        //static AtmosphericModel*   AtmosphericModelFromType                       (   const   Earth::Type&                aType,
        //                                                                        const   Directory&                  aDataDirectory                              ) ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Earth::Impl::Impl                           (   const   Earth::Type&                aType,
                                                                                const   Directory&                  aDataDirectory                              )
                                :   type_(aType)
                                    //atmosphericModelPtr_(Earth::Impl::AtmosphericModelFromType(aType, aDataDirectory))
{

}

                                Earth::Impl::~Impl                          ( )
{
    //delete atmosphericModelPtr_ ;
}

Earth::Type                     Earth::Impl::getType                        ( ) const
{
    return type_ ;
}

extern "C" void 

Real                        Earth::Impl::getDensityAt                (   const   Vector3d&                   aPosition,
                                                                                const   Instant&                    anInstant                                   ) const
{
    
    return 0.0 ;
}
/*
    using GeographicLib::Geocentric ;

    using ostk::core::types::Integer ;

    using ostk::math::geom::d3::trf::rot::RotationMatrix ;

    using ostk::physics::time::Scale ;

    if (type_ == Earth::Type::Dipole)
    {
        return EarthDipole.getFieldValueAt(aPosition, anInstant) ;
    }

    const Integer year = anInstant.getDateTime(Scale::UTC).accessDate().getYear() ;

    if (((year < static_cast<int>(atmosphericModelPtr_->MinTime())) || (year > static_cast<int>(atmosphericModelPtr_->MaxTime()))))
    {
        throw ostk::core::error::RuntimeError("Year [{}] is out of [{}, {}] bounds.", year, atmosphericModelPtr_->MinTime(), atmosphericModelPtr_->MaxTime()) ;
    }

    static const Geocentric earthGeocentric = Geocentric::WGS84() ;

    double latitude_deg ; // [deg]
    double longitude_deg ; // [deg]
    double altitude_m ; // [m]

    earthGeocentric.Reverse(aPosition.x(), aPosition.y(), aPosition.z(), latitude_deg, longitude_deg, altitude_m) ;

    double Bx_nT ; // [nT] Easterly component of the atmospheric field
    double By_nT ; // [nT] Northerly component of the atmospheric field
    double Bz_nT ; // [nT] Vertical component of the atmospheric field

    (*atmosphericModelPtr_)(year, latitude_deg, longitude_deg, altitude_m, Bx_nT, By_nT, Bz_nT) ;

    const Vector3d atmosphericField_NED = Vector3d { By_nT, Bx_nT, -Bz_nT } / 1e9 ; // [T]

    const double latitude_rad = latitude_deg * M_PI / 180.0 ; // [rad]
    const double longitude_rad = longitude_deg * M_PI / 180.0 ; // [rad]

    const Real cos_lat = std::cos(latitude_rad) ;
    const Real sin_lat = std::sin(latitude_rad) ;

    const Real cos_lon = std::cos(longitude_rad) ;
    const Real sin_lon = std::sin(longitude_rad) ;

    const RotationMatrix dcm_ECEF_NED = {   -sin_lat * cos_lon, -sin_lon, -cos_lat * cos_lon,
                                            -sin_lat * sin_lon, +cos_lon, -cos_lat * sin_lon,
                                            +cos_lat,           0.0,      -sin_lat } ;

    const Vector3d atmosphericField = dcm_ECEF_NED * atmosphericField_NED ; // [T]

    return atmosphericField ;

}
*/
/*
AtmosphericModel*                  Earth::Impl::AtmosphericModelFromType          (   const   Earth::Type&                aType,
                                                                                const   Directory&                  aDataDirectory                              )
{

    using ostk::core::types::String ;

    using ostk::physics::environment::atmospheric::earth::Manager ;

    String dataPath = "" ;

    if (aDataDirectory.isDefined())
    {

        if (!aDataDirectory.exists())
        {
            throw ostk::core::error::RuntimeError("Data directory [{}] does not exist.", aDataDirectory.toString()) ;
        }

        dataPath = aDataDirectory.getPath().toString() ;

    }
    else
    {

        if (Manager::Get().isEnabled())
        {

            if (!Manager::Get().hasDataFileForType(aType))
            {
                Manager::Get().fetchDataFileForType(aType) ;
            }

            dataPath = Manager::Get().getLocalRepository().getPath().toString() ;

        }

    }

    switch (aType)
    {

        case Earth::Type::NRLMISE00:
            return new GeographicLib::AtmosphericModel("nrlmsise00", dataPath) ;

        default:
            throw ostk::core::error::runtime::Wrong("Type") ;

    }

    return nullptr ;

}
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Earth::Earth                                (   const   Earth::Type&                aType,
                                                                                const   Directory&                  aDataDirectory                              )
                                :   Model(),
                                    implUPtr_(std::make_unique<Earth::Impl>(aType, aDataDirectory))
{

}

                                Earth::Earth                                (   const   Earth&                      anEarthAtmosphericModel                        )
                                :   Model(anEarthAtmosphericModel),
                                    implUPtr_((anEarthAtmosphericModel.implUPtr_ != nullptr) ? std::make_unique<Earth::Impl>(*anEarthAtmosphericModel.implUPtr_) : nullptr)
{

}

Earth&                          Earth::operator =                           (   const   Earth&                      anEarthAtmosphericModel                        )
{

    if (this != &anEarthAtmosphericModel)
    {

        Model::operator = (anEarthAtmosphericModel) ;

        implUPtr_.reset((anEarthAtmosphericModel.implUPtr_ != nullptr) ? new Earth::Impl(*anEarthAtmosphericModel.implUPtr_) : nullptr) ;

    }

    return *this ;

}

                                Earth::~Earth                               ( )
{

}

// Might want to look into using a Shared Pointer for Earth::Impl
Earth*                          Earth::clone                                ( ) const
{
    return new Earth(*this) ;
}

Earth::Type                     Earth::getType                              ( ) const
{
    return implUPtr_->getType() ;
}

Real                        Earth::getDensityAt                      (   const   Vector3d&                   aPosition,
                                                                                const   Instant&                    anInstant                                   ) const
{
    return implUPtr_->getDensityAt(aPosition, anInstant) ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
