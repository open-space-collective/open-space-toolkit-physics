////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           Library/Physics/Environment/Objects/Celestial.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OpenSpaceToolkit_Physics_Environment_Objects_Celestial__
#define __OpenSpaceToolkit_Physics_Environment_Objects_Celestial__

#include <Library/Physics/Environment/Magnetic/Model.hpp>
#include <Library/Physics/Environment/Gravitational/Model.hpp>
#include <Library/Physics/Environment/Ephemeris.hpp>
#include <Library/Physics/Environment/Object.hpp>
#include <Library/Physics/Coordinate/Transform.hpp>
#include <Library/Physics/Coordinate/Frame.hpp>
#include <Library/Physics/Coordinate/Axes.hpp>
#include <Library/Physics/Coordinate/Spherical/LLA.hpp>
#include <Library/Physics/Coordinate/Position.hpp>
#include <Library/Physics/Data/Vector.hpp>
#include <Library/Physics/Units/Derived.hpp>
#include <Library/Physics/Units/Length.hpp>
#include <Library/Physics/Time/Instant.hpp>

#include <Library/Mathematics/Objects/Vector.hpp>

#include <Library/Core/Types/String.hpp>
#include <Library/Core/Types/Real.hpp>
#include <Library/Core/Types/Shared.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{
namespace env
{
namespace obj
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using library::core::types::Shared ;
using library::core::types::Real ;
using library::core::types::String ;

using library::math::obj::Vector3d ;

using library::physics::time::Instant ;
using library::physics::units::Length ;
using library::physics::units::Derived ;
using library::physics::data::Vector ;
using library::physics::coord::Position ;
using library::physics::coord::spherical::LLA ;
using library::physics::coord::Axes ;
using library::physics::coord::Frame ;
using library::physics::coord::Transform ;
using library::physics::env::Object ;
using library::physics::env::Ephemeris ;
using GravitationalModel = library::physics::environment::gravitational::Model ;
using MagneticModel = library::physics::environment::magnetic::Model ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Celestial : public Object
{

    public:

        enum class Type
        {

            Undefined,
            Sun,
            Mercury,
            Venus,
            Earth,
            Moon,
            Mars

        } ;

        enum class FrameType
        {

            Undefined,          ///< Undefined frame
            NED,                ///< North-East-Down (NED) frame

        } ;

        struct ModelBase
        {

            static Derived      GravitationalParameter ;
            static Length       EquatorialRadius ;
            static Real         Flattening ;
            static Real         C20 ;
            static Real         J2 ;

        } ;

                                Celestial                                   (   const   String&                     aName,
                                                                                const   Celestial::Type&            aType,
                                                                                const   Derived&                    aGravitationalParameter,
                                                                                const   Length&                     anEquatorialRadius,
                                                                                const   Real&                       aFlattening,
                                                                                const   Real&                       aJ2,
                                                                                const   Shared<Ephemeris>&          anEphemeris,
                                                                                const   Shared<GravitationalModel>& aGravitationalModel,
                                                                                const   Shared<MagneticModel>&      aMagneticModel,
                                                                                const   Instant&                    anInstant                                   ) ;

                                Celestial                                   (   const   String&                     aName,
                                                                                const   Celestial::Type&            aType,
                                                                                const   Derived&                    aGravitationalParameter,
                                                                                const   Length&                     anEquatorialRadius,
                                                                                const   Real&                       aFlattening,
                                                                                const   Real&                       aJ2,
                                                                                const   Shared<Ephemeris>&          anEphemeris,
                                                                                const   Shared<GravitationalModel>& aGravitationalModel,
                                                                                const   Shared<MagneticModel>&      aMagneticModel,
                                                                                const   Instant&                    anInstant,
                                                                                const   Object::Geometry&           aGeometry                                   ) ;

        virtual                 ~Celestial                                  ( ) override ;

        virtual Celestial*      clone                                       ( ) const override ;

        virtual bool            isDefined                                   ( ) const override ;

        Shared<const Ephemeris> accessEphemeris                             ( ) const ;

        Shared<const GravitationalModel> accessGravitationalModel           ( ) const ;

        Shared<const MagneticModel> accessMagneticModel                     ( ) const ;

        Celestial::Type         getType                                     ( ) const ;

        Derived                 getGravitationalParameter                    ( ) const ;

        Length                  getEquatorialRadius                         ( ) const ;

        Real                    getFlattening                               ( ) const ;

        Real                    getJ2                                       ( ) const ;

        virtual Shared<const Frame> accessFrame                             ( ) const override ;

        virtual Position        getPositionIn                               (   const   Shared<const Frame>&        aFrameSPtr                                  ) const override ;

        virtual Velocity        getVelocityIn                               (   const   Shared<const Frame>&        aFrameSPtr                                  ) const override ;

        virtual Transform       getTransformTo                              (   const   Shared<const Frame>&        aFrameSPtr                                  ) const override ;

        virtual Axes            getAxesIn                                   (   const   Shared<const Frame>&        aFrameSPtr                                  ) const override ;

        Vector                  getGravitationalFieldAt                     (   const   Position&                   aPosition                                   ) const ;

        Vector                  getMagneticFieldAt                          (   const   Position&                   aPosition                                   ) const ;

        Shared<const Frame>     getFrameAt                                  (   const   LLA&                        aLla,
                                                                                const   Celestial::FrameType&       aFrameType                                  ) const ;

        Object::Geometry        getTerminatorGeometry                       ( ) const ;

        static Celestial        Undefined                                   ( ) ;

        static String           StringFromFrameType                         (   const   Celestial::FrameType&       aFrameType                                  ) ;

    private:

        Celestial::Type         type_ ;
        Derived                 gravitationalParameter_ ;
        Length                  equatorialRadius_ ;
        Real                    flattening_ ;
        Real                    j2_ ;
        Shared<Ephemeris>       ephemeris_ ;
        Shared<GravitationalModel> gravitationalModelSPtr_ ;
        Shared<MagneticModel>   magneticModelSPtr_ ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
