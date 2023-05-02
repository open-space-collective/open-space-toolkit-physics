////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth.cpp
/// @author         Kyle Cochran <kyle.cochran@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <math.h>

#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Exponential.hpp>
#include <OpenSpaceToolkit/Physics/Units/Length.hpp>

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

using ostk::physics::units::Length ;
using ostk::physics::environment::atmospheric::Exponential ;

using ostk::core::ctnr::Array ;
using ostk::core::ctnr::Tuple ;
using ostk::core::types::String ;
using ostk::core::types::Integer ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Earth::Impl
{

    public:

                                Impl                                        (   const   Earth::Type&                aType,
                                                                                const   Directory&                  aDataDirectory                              ) ;

                                Impl                                        (   const   Earth::Type&                aType                                       ) ;

        virtual                 ~Impl                                       ( ) ;

        virtual Impl*           clone                                       ( ) const = 0 ;

        Earth::Type             getType                                     ( ) const ;

        virtual Real            getDensityAt                                (   const   LLA&                        aLLA,
                                                                                const   Instant&                    anInstant                                   ) const = 0 ;

    private:

        Earth::Type             type_ ;

        static Tuple<Real, Real, Real> getDensityBandValues                 (   const   Length&                     anAltitude                                  ) ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Earth::Impl::Impl                           (   const   Earth::Type&                aType,
                                                                                const   Directory&                  aDataDirectory                              )
                                :   type_(aType)
{

}

                                Earth::Impl::Impl                           (   const   Earth::Type&                aType                                       )
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Earth::ExponentialImpl : public Earth::Impl
{

    public:

                                ExponentialImpl                             (   const   Earth::Type&                aType                                       ) ;

                                ~ExponentialImpl                            ( ) ;

        virtual ExponentialImpl*  clone                                     ( ) const override ;

        virtual Real            getDensityAt                                (   const   LLA&                        aLLA,
                                                                                const   Instant&                    anInstant                                   ) const override ;

    private:

        Exponential               ExponentialModel_ ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Earth::ExponentialImpl::ExponentialImpl     (   const   Earth::Type&                aType                                       )

                                :   Earth::Impl(aType)
{

}

                                Earth::ExponentialImpl::~ExponentialImpl    ( )
{

}

Earth::ExponentialImpl*           Earth::ExponentialImpl::clone             ( ) const
{
    return new Earth::ExponentialImpl(*this) ;
}

Real                            Earth::ExponentialImpl::getDensityAt        (   const   LLA&                        aLLA,
                                                                                const   Instant&                    anInstant                                   ) const
{
    return ExponentialModel_.getDensityAt(aLLA, anInstant) ;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Earth::Earth                                (   const   Earth::Type&                aType,
                                                                                const   Directory&                  aDataDirectory                              )
                                :   Model(),
                                    implUPtr_(Earth::ImplFromType(aType))
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

Real                            Earth::getDensityAt                         (   const   LLA&                        aLLA,
                                                                                const   Instant&                    anInstant                                   ) const
{
    return implUPtr_->getDensityAt(aLLA, anInstant) ;
}

Unique<Earth::Impl>             Earth::ImplFromType                         (   const   Earth::Type&                aType                                      )
{

    if (aType == Earth::Type::Exponential)
    {
        return std::make_unique<Earth::ExponentialImpl>(aType) ;
    }

    throw ostk::core::error::runtime::Undefined("Type") ;
    
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
