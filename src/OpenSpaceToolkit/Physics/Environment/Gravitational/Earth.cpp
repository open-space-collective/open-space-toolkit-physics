////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           OpenSpaceToolkit/Physics/Environment/Gravitational/Earth.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Earth/Manager.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Spherical.hpp>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

#include <GeographicLib/GravityModel.hpp>
#include <GeographicLib/Constants.hpp>
#include <GeographicLib/Utility.hpp>

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

using GeographicLib::GravityModel ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static Real gravitationalParameter_SI = 398600441500000.0 ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Earth::Impl
{

    public:

                                Impl                                        (   const   Earth::Type&                aType,
                                                                                const   Directory&                  aDataDirectory,
                                                                                const   Integer&                    aGravityModelDegree,
                                                                                const   Integer&                    aGravityModelOrder                          ) ;

                                ~Impl                                       ( ) ;

        Earth::Type             getType                                     ( ) const ;

        Vector3d                getFieldValueAt                             (   const   Vector3d&                   aPosition,
                                                                                const   Instant&                    anInstant                                   ) const ;

    private:

        Earth::Type             type_ ;

        GravityModel*           gravityModelPtr_ ;

        static GravityModel*    GravityModelFromType                        (   const   Earth::Type&                aType,
                                                                                const   Directory&                  aDataDirectory,
                                                                                const   Integer&                    aGravityModelDegree,
                                                                                const   Integer&                    aGravityModelOrder                          ) ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Earth::Impl::Impl                           (   const   Earth::Type&                aType,
                                                                                const   Directory&                  aDataDirectory,
                                                                                const   Integer&                    aGravityModelDegree,
                                                                                const   Integer&                    aGravityModelOrder                          )

                                :   type_(aType),
                                    gravityModelPtr_(Earth::Impl::GravityModelFromType(aType, aDataDirectory, aGravityModelDegree, aGravityModelOrder))

{

}

                                Earth::Impl::~Impl                          ( )
{
    delete gravityModelPtr_ ;
}

Earth::Type                     Earth::Impl::getType                        ( ) const
{
    return type_ ;
}

Vector3d                        Earth::Impl::getFieldValueAt                (   const   Vector3d&                   aPosition,
                                                                                const   Instant&                    anInstant                                   ) const
{

    (void) anInstant ; // Temporal invariance

    if (type_ == Earth::Type::Spherical)
    {

        const Real r = aPosition.norm() ;
        const Vector3d fieldDirection = aPosition.normalized() ;

        const Vector3d field = (- gravitationalParameter_SI) / (r * r) * fieldDirection ;

        return field ;

    }

    double g_x ;
    double g_y ;
    double g_z ;

    gravityModelPtr_->V(aPosition.x(), aPosition.y(), aPosition.z(), g_x, g_y, g_z) ;

    return { g_x, g_y, g_z } ;

}

GravityModel*                   Earth::Impl::GravityModelFromType           (   const   Earth::Type&                aType,
                                                                                const   Directory&                  aDataDirectory,
                                                                                const   Integer&                    aGravityModelDegree,
                                                                                const   Integer&                    aGravityModelOrder                          )
{

    using ostk::core::types::String ;

    using ostk::physics::environment::gravitational::earth::Manager ;

    if (aType == Earth::Type::Spherical)
    {
        return nullptr ;
    }

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

        case Earth::Type::WGS84:
            if ((aGravityModelDegree > 20) || (aGravityModelOrder > 0)) {throw ostk::core::error::runtime::Wrong("Model Degree/Order") ; }
            return new GeographicLib::GravityModel("wgs84", dataPath, aGravityModelDegree, aGravityModelOrder) ;

        case Earth::Type::EGM84:
            if ((aGravityModelDegree > 180) || (aGravityModelOrder > 180)) {throw ostk::core::error::runtime::Wrong("Model Degree/Order") ; }
            return new GeographicLib::GravityModel("egm84", dataPath, aGravityModelDegree, aGravityModelOrder) ;

        case Earth::Type::EGM96:
            if ((aGravityModelDegree > 360) || (aGravityModelOrder > 360)) {throw ostk::core::error::runtime::Wrong("Model Degree/Order") ; }
            return new GeographicLib::GravityModel("egm96", dataPath, aGravityModelDegree, aGravityModelOrder) ;

        case Earth::Type::EGM2008:
            if((aGravityModelDegree > 2190) || (aGravityModelOrder > 2160)) {throw ostk::core::error::runtime::Wrong("Model Degree/Order") ; }
            return new GeographicLib::GravityModel("egm2008", dataPath, aGravityModelDegree, aGravityModelOrder) ;

        default:
            throw ostk::core::error::runtime::Wrong("Type") ;

    }

    return nullptr ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Earth::Earth                                (   const   Earth::Type&                aType,
                                                                                const   Directory&                  aDataDirectory,
                                                                                const   Integer&                    aGravityModelDegree,
                                                                                const   Integer&                    aGravityModelOrder                          )
                                :   Model(),
                                    implUPtr_(std::make_unique<Earth::Impl>(aType, aDataDirectory, aGravityModelDegree, aGravityModelOrder))
{

}


                                Earth::Earth                                (   const   Earth&                      anEarthGravitationalModel                   )
                                :   Model(anEarthGravitationalModel),
                                    implUPtr_((anEarthGravitationalModel.implUPtr_ != nullptr) ? std::make_unique<Earth::Impl>(*anEarthGravitationalModel.implUPtr_) : nullptr)
{

}

Earth&                          Earth::operator =                           (   const   Earth&                      anEarthGravitationalModel                   )
{

    if (this != &anEarthGravitationalModel)
    {

        Model::operator = (anEarthGravitationalModel) ;

        implUPtr_.reset((anEarthGravitationalModel.implUPtr_ != nullptr) ? new Earth::Impl(*anEarthGravitationalModel.implUPtr_) : nullptr) ;

    }

    return *this ;

}

                                Earth::~Earth                               ( )
{

}

Earth*                          Earth::clone                                ( ) const
{
    return new Earth(*this) ;
}

Earth::Type                     Earth::getType                              ( ) const
{
    return implUPtr_->getType() ;
}

Vector3d                        Earth::getFieldValueAt                      (   const   Vector3d&                   aPosition,
                                                                                const   Instant&                    anInstant                                   ) const
{
    return implUPtr_->getFieldValueAt(aPosition, anInstant) ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
