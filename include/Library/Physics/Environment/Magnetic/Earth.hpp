////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Environment/Magnetic/Earth.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Physics_Environment_Magnetic_Earth__
#define __Library_Physics_Environment_Magnetic_Earth__

#include <Library/Physics/Environment/Magnetic/Model.hpp>
#include <Library/Physics/Time/Instant.hpp>
#include <Library/Physics/Units/Derived.hpp>

#include <Library/IO/URL.hpp>

#include <Library/Core/FileSystem/Directory.hpp>
#include <Library/Core/Types/Real.hpp>
#include <Library/Core/Types/Unique.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{
namespace environment
{
namespace magnetic
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using library::core::types::Unique ;
using library::core::types::Real ;
using library::core::fs::Directory ;

using library::io::URL ;

using library::physics::units::Derived ;
using library::physics::time::Instant ;
using library::physics::environment::magnetic::Model ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Earth magnetic model
///
/// @ref                        https://geographiclib.sourceforge.io/html/magnetic.html

class Earth : public Model
{

    public:

        enum class Type
        {

            Dipole,             ///< Dipole Model
            EMM2010,            ///< Enhanced Magnetic Model 2010: approximates the main and crustal magnetic fields for the period 2010–2015.
            EMM2015,            ///< Enhanced Magnetic Model 2015: approximates the main and crustal magnetic fields for the period 2000–2020.
            EMM2017,            ///< Enhanced Magnetic Model 2017: approximates the main and crustal magnetic fields for the period 2000–2022.
            IGRF11,             ///< International Geomagnetic Reference Field (11th generation): approximates the main magnetic field for the period 1900–2015.
            IGRF12,             ///< International Geomagnetic Reference Field (12th generation): approximates the main magnetic field for the period 1900–2020.
            WMM2010,            ///< World Magnetic Model 2010: approximates the main magnetic field for the period 2010–2015.
            WMM2015             ///< World Magnetic Model 2015: approximates the main magnetic field for the period 2015–2020.

        } ;

        /// @brief              Constructor
        ///
        /// @param              [in] aType A magnetic model type
        /// @param              [in] (optional) aDataDirectory A magnetic model data directory

                                Earth                                       (   const   Earth::Type&                aType,
                                                                                const   Directory&                  aDataDirectory                              =   Directory::Undefined() ) ;

        /// @brief              Copy constructor
        ///
        /// @param              [in] anEarthMagneticModel An Earth model

                                Earth                                       (   const   Earth&                      anEarthMagneticModel                        ) ;

        /// @brief              Copy assignment operator
        ///
        /// @param              [in] anEarthMagneticModel An Earth model
        /// @return             Reference to Earth model

        Earth&                  operator =                                  (   const   Earth&                      anEarthMagneticModel                        ) ;

        /// @brief              Destructor

                                ~Earth                                      ( ) ;

        /// @brief              Clone the Earth magnetic model
        ///
        /// @return             Pointer to Earth magnetic model

        virtual Earth*          clone                                       ( ) const override ;

        /// @brief              Get magnetic model type
        ///
        /// @return             Magnetic model type

        Earth::Type             getType                                     ( ) const ;

        /// @brief              Get the magnetic field value at a given position and instant
        ///
        /// @param              [in] aPosition A position, expressed in the magnetic object frame [m]
        /// @param              [in] anInstant An instant
        /// @return             Magnetic field value, expressed in the magnetic object frame [T]

        virtual Vector3d        getFieldValueAt                             (   const   Vector3d&                   aPosition,
                                                                                const   Instant&                    anInstant                                   ) const override ;

    private:

        class Impl ;

        Unique<Impl>            implUPtr_ ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////