////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Environment/Ephemerides/SPICE/Engine.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Physics_Environment_Ephemerides_SPICE_Engine__
#define __Library_Physics_Environment_Ephemerides_SPICE_Engine__

#include <Library/Physics/Environment/Ephemerides/SPICE.hpp>
#include <Library/Physics/Coordinate/Transform.hpp>
#include <Library/Physics/Coordinate/Frame.hpp>
#include <Library/Physics/Time/Instant.hpp>

#include <Library/Core/FileSystem/File.hpp>
#include <Library/Core/FileSystem/Path.hpp>
#include <Library/Core/Types/String.hpp>
#include <Library/Core/Types/Shared.hpp>

#include <mutex>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{
namespace env
{
namespace ephem
{
namespace spice
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using library::core::types::Shared ;
using library::core::types::String ;
using library::core::fs::Path ;
using library::core::fs::File ;

using library::physics::time::Instant ;
using library::physics::coord::Frame ;
using library::physics::coord::Transform ;
using library::physics::env::ephem::SPICE ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      SPICE Toolkit engine

class Engine
{

    public:

                                Engine                                      (   const   Engine&                     aSpiceEngine                                ) = delete ;

        Engine&                 operator =                                  (   const   Engine&                     aSpiceEngine                                ) = delete ;

        Shared<const Frame>     getFrameOf                                  (   const   SPICE::Object&              aSpiceObject                                ) const ;

        void                    loadKernel                                  (   const   File&                       aKernelFile                                 ) ;

        static Engine&          Get                                         ( ) ;

    private:

        mutable std::mutex      mutex_ ;

                                Engine                                      ( ) ;

        Transform               getTransformAt                              (   const   String&                     aSpiceIdentifier,
                                                                                const   String&                     aFrameName,
                                                                                const   Instant&                    anInstant                                   ) const ;

        void                    setup                                       ( ) ;

        static String           SpiceIdentifierFromSpiceObject              (   const   SPICE::Object&              aSpiceObject                                ) ;

        static String           FrameNameFromSpiceObject                    (   const   SPICE::Object&              aSpiceObject                                ) ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////