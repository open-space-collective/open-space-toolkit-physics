////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth.cpp
/// @author         Kyle Cochran <kyle.cochran@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Physics/Environment/Objects/CelestialBodies/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/Exponential.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>

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

using ostk::physics::coord::Frame ;
using ostk::physics::environment::atmospheric::earth::Exponential ;
using EarthCelestialBody = ostk::physics::env::obj::celest::Earth ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Earth::Impl
{

    public:

                                Impl                                        (   const   Earth::Type&                aType,
                                                                                const   Directory&                  aDataDirectory                              =   Directory::Undefined() ) ;

        virtual                 ~Impl                                       ( ) = 0 ;

        virtual Impl*           clone                                       ( ) const = 0 ;

        Earth::Type             getType                                     ( ) const ;

        virtual Real            getDensityAt                                (   const   LLA&                        aLLA,
                                                                                const   Instant&                    anInstant                                   ) const = 0 ;

    private:

        Earth::Type             type_ ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Earth::Impl::Impl                           (   const   Earth::Type&                aType,
                                                                                const   Directory&                  aDataDirectory                              )
                                :   type_(aType)
{
    (void) aDataDirectory ; // Not yet used
}

                                Earth::Impl::~Impl                          ( )
{

}

Earth::Type                     Earth::Impl::getType                        ( ) const
{
    return type_ ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Earth::ExponentialImpl : public Earth::Impl
{

    public:

                                ExponentialImpl                             (   const   Earth::Type&                aType                                       ) ;

                                ~ExponentialImpl                            ( ) ;

        virtual ExponentialImpl* clone                                      ( ) const override ;

        virtual Real            getDensityAt                                (   const   LLA&                        aLLA,
                                                                                const   Instant&                    anInstant                                   ) const override ;

    private:

        Exponential             exponentialModel_ ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Earth::ExponentialImpl::ExponentialImpl            (   const   Earth::Type&                aType                                       )
                                :   Earth::Impl(aType)
{

}

                                Earth::ExponentialImpl::~ExponentialImpl           ( )
{

}

Earth::ExponentialImpl*                Earth::ExponentialImpl::clone                      ( ) const
{
    return new Earth::ExponentialImpl(*this) ;
}

Real                            Earth::ExponentialImpl::getDensityAt               (   const   LLA&                        aLLA,
                                                                                const   Instant&                    anInstant                                   ) const
{
    return this->exponentialModel_.getDensityAt(aLLA, anInstant) ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Earth::Earth                                (   const   Earth::Type&                aType,
                                                                                const   Directory&                  aDataDirectory                              )
                                :   Model(),
                                    implUPtr_(Earth::ImplFromType(aType, aDataDirectory))
{

}

                                Earth::Earth                                (   const   Earth&                      anEarthAtmosphericModel                     )
                                :   Model(anEarthAtmosphericModel),
                                    implUPtr_((anEarthAtmosphericModel.implUPtr_ != nullptr) ? anEarthAtmosphericModel.implUPtr_->clone() : nullptr)
{

}

Earth&                          Earth::operator =                           (   const   Earth&                      anEarthAtmosphericModel                     )
{

    if (this != &anEarthAtmosphericModel)
    {

        Model::operator = (anEarthAtmosphericModel) ;

        implUPtr_.reset((anEarthAtmosphericModel.implUPtr_ != nullptr) ? anEarthAtmosphericModel.implUPtr_->clone() : nullptr) ;

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

Real                            Earth::getDensityAt                         (   const   Position&                   aPosition,
                                                                                const   Instant&                    anInstant                                   ) const
{
    return this->getDensityAt
    (
        LLA::Cartesian(aPosition.inFrame(Frame::ITRF(), anInstant).accessCoordinates(), EarthCelestialBody::EquatorialRadius, EarthCelestialBody::Flattening),
        anInstant
    ) ;
}

Real                            Earth::getDensityAt                         (   const   LLA&                        aLLA,
                                                                                const   Instant&                    anInstant                                   ) const
{
    return implUPtr_->getDensityAt(aLLA, anInstant) ;
}

Unique<Earth::Impl>             Earth::ImplFromType                         (   const   Earth::Type&                aType,
                                                                                const   Directory&                  aDataDirectory                              )
{

    (void) aDataDirectory ; // Not yet used

    if (aType == Earth::Type::Exponential)
    {
        return std::make_unique<ExponentialImpl>(aType) ;
    }

    throw ostk::core::error::runtime::Wrong("Type") ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
