////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth.cpp
/// @author         Kyle Cochran <kyle.cochran@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth.hpp>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

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

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Earth::Impl::Impl                           (   const   Earth::Type&                aType,
                                                                                const   Directory&                  aDataDirectory                              )
                                :   type_(aType)
{

}

                                Earth::Impl::~Impl                          ( )
{

}

Earth::Type                     Earth::Impl::getType                        ( ) const
{
    return type_ ;
}

Real                            Earth::Impl::getDensityAt                   (   const   Vector3d&                   aPosition,
                                                                                const   Instant&                    anInstant                                   ) const
{
    
    return  0.0;
}
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

Real                            Earth::getDensityAt                         (   const   Vector3d&                   aPosition,
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
