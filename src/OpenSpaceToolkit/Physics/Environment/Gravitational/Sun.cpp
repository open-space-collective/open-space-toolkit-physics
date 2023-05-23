/// Apache License 2.0 

#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Sun.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Spherical.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Objects/CelestialBodies/Sun.hpp>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

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

class Sun::Impl
{

    public:

                                Impl                                        (   const   Sun::Type&                  aType                                       ) ;

        virtual                 ~Impl                                       ( ) = 0 ;

        virtual Impl*           clone                                       ( ) const = 0 ;

        Sun::Type               getType                                     ( ) const ;

        virtual Vector3d        getFieldValueAt                             (   const   Vector3d&                   aPosition,
                                                                                const   Instant&                    anInstant                                   ) const = 0 ;

    private:

        Sun::Type               type_ ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Sun::Impl::Impl                             (   const   Sun::Type&                aType                                       )

                                :   type_(aType)
{

}

                                Sun::Impl::~Impl                            ( )
{

}

Sun::Type                       Sun::Impl::getType                          ( ) const
{
    return type_ ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Sun::SphericalImpl : public Sun::Impl
{

    public:

                                SphericalImpl                               (   const   Sun::Type&                  aType                                       ) ;

                                ~SphericalImpl                              ( ) ;

        virtual SphericalImpl*  clone                                       ( ) const override ;

        virtual Vector3d        getFieldValueAt                             (   const   Vector3d&                   aPosition,
                                                                                const   Instant&                    anInstant                                   ) const override ;

    private:

        Spherical               sphericalModel_ ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Sun::SphericalImpl::SphericalImpl           (   const   Sun::Type&                  aType                                       )

                                :   Sun::Impl(aType),
                                    sphericalModel_(ostk::physics::env::obj::celest::Sun::GravitationalParameter)
{

}

                                Sun::SphericalImpl::~SphericalImpl          ( )
{

}

Sun::SphericalImpl*             Sun::SphericalImpl::clone                   ( ) const
{
    return new Sun::SphericalImpl(*this) ;
}

Vector3d                        Sun::SphericalImpl::getFieldValueAt         (   const   Vector3d&                   aPosition,
                                                                                const   Instant&                    anInstant                                   ) const
{
    return sphericalModel_.getFieldValueAt(aPosition, anInstant) ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Sun::Sun                                    (   const   Sun::Type&                  aType,
                                                                                const   Directory&                  aDataDirectory                              )
                                :   Model(),
                                    implUPtr_(Sun::ImplFromType(aType, aDataDirectory))
{

}

                                Sun::Sun                                    (   const   Sun&                        aSunGravitationalModel                      )
                                :   Model(aSunGravitationalModel),
                                    implUPtr_((aSunGravitationalModel.implUPtr_ != nullptr) ? aSunGravitationalModel.implUPtr_->clone() : nullptr)
{

}

Sun&                            Sun::operator =                             (   const   Sun&                        aSunGravitationalModel                      )
{

    if (this != &aSunGravitationalModel)
    {

        Model::operator = (aSunGravitationalModel) ;

        implUPtr_.reset((aSunGravitationalModel.implUPtr_ != nullptr) ? aSunGravitationalModel.implUPtr_->clone() : nullptr) ;

    }

    return *this ;

}

                                Sun::~Sun                                   ( )
{

}

Sun*                            Sun::clone                                  ( ) const
{
    return new Sun(*this) ;
}

Sun::Type                       Sun::getType                                ( ) const
{
    return implUPtr_->getType() ;
}

Vector3d                        Sun::getFieldValueAt                        (   const   Vector3d&                   aPosition,
                                                                                const   Instant&                    anInstant                                   ) const
{
    return implUPtr_->getFieldValueAt(aPosition, anInstant) ;
}

Unique<Sun::Impl>               Sun::ImplFromType                           (   const   Sun::Type&                  aType,
                                                                                const   Directory&                  aDataDirectory                              )
{

    (void) aDataDirectory ;  // Temporary

    if (aType == Sun::Type::Spherical)
    {
        return std::make_unique<Sun::SphericalImpl>(aType) ;
    }

    throw ostk::core::error::runtime::ToBeImplemented("Non spherical Sun gravity field type") ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
