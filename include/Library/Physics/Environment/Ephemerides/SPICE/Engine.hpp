////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           OpenSpaceToolkit/Physics/Environment/Ephemerides/SPICE/Engine.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OpenSpaceToolkit_Physics_Environment_Ephemerides_SPICE_Engine__
#define __OpenSpaceToolkit_Physics_Environment_Ephemerides_SPICE_Engine__

#include <OpenSpaceToolkit/Physics/Environment/Ephemerides/SPICE/Kernel.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Ephemerides/SPICE.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Transform.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Time/Interval.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

#include <Library/Core/FileSystem/Directory.hpp>
#include <Library/Core/FileSystem/File.hpp>
#include <Library/Core/FileSystem/Path.hpp>
#include <Library/Core/Containers/Array.hpp>
#include <Library/Core/Containers/Pair.hpp>
#include <Library/Core/Types/String.hpp>
#include <Library/Core/Types/Index.hpp>
#include <Library/Core/Types/Shared.hpp>

#include <mutex>
#include <unordered_set>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define LIBRARY_PHYSICS_ENVIRONMENT_EPHEMERIDES_SPICE_ENGINE_MODE Engine::Mode::Automatic

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ostk
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

using ostk::core::types::Shared ;
using ostk::core::types::Index ;
using ostk::core::types::String ;
using ostk::core::ctnr::Pair ;
using ostk::core::ctnr::Array ;
using ostk::core::fs::Path ;
using ostk::core::fs::File ;
using ostk::core::fs::Directory ;

using ostk::physics::time::Instant ;
using ostk::physics::time::Interval ;
using ostk::physics::coord::Frame ;
using ostk::physics::coord::Transform ;
using ostk::physics::env::ephem::SPICE ;
using ostk::physics::env::ephem::spice::Kernel ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      SPICE Toolkit engine
///
///                             The following environment variables can be defined:
///
///                             - "LIBRARY_PHYSICS_ENVIRONMENT_EPHEMERIDES_SPICE_ENGINE_MODE" will override "DefaultMode"

class Engine
{

    public:

        /// @brief              Engine mode

        enum class Mode
        {

            Manual,             ///< Manually load and unload kernels
            Automatic           ///< Automatically fetch, load and unload kernels (from remote repositories)

        } ;

        /// @brief              Copy constructor (deleted)

                                Engine                                      (   const   Engine&                     aSpiceEngine                                ) = delete ;

        /// @brief              Copy assignment operator (deleted)

        Engine&                 operator =                                  (   const   Engine&                     aSpiceEngine                                ) = delete ;

        /// @brief              Output stream operator
        ///
        /// @param              [in] anOutputStream An output stream
        /// @param              [in] anEngine A SPICE engine
        /// @return             A reference to output stream

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Engine&                     anEngine                                    ) ;

        /// @brief              Returns true if kernel is loaded
        ///
        /// @param              [in] aKernel A kernel
        /// @return             True if kernel is loaded

        bool                    isKernelLoaded                              (   const   Kernel&                     aKernel                                     ) const ;

        /// @brief              Get engine mode
        ///
        /// @return             Engine mode

        Engine::Mode            getMode                                     ( ) const ;

        /// @brief              Get frame of SPICE object
        ///
        /// @param              [in] A SPICE object
        /// @return             Frame of SPICE object

        Shared<const Frame>     getFrameOf                                  (   const   SPICE::Object&              aSpiceObject                                ) const ;

        /// @brief              Set engine mode
        ///
        /// @param              [in] aMode An engine mode
        /// @return             Engine mode

        void                    setMode                                     (   const   Engine::Mode&               aMode                                       ) ;

        /// @brief              Load kernel
        ///
        /// @param              [in] aKernel A kernel

        void                    loadKernel                                  (   const   Kernel&                     aKernel                                     ) ;

        /// @brief              Unload kernel
        ///
        /// @param              [in] aKernel

        void                    unloadKernel                                (   const   Kernel&                     aKernel                                     ) ;

        /// @brief              Reset engine
        ///
        ///                     Unload all kernels and clear cache.

        void                    reset                                       ( ) ;

        /// @brief              Get engine singleton
        ///
        /// @return             Reference to engine

        static Engine&          Get                                         ( ) ;

        /// @brief              Get default engine mode
        ///
        ///                     Overriden by: LIBRARY_PHYSICS_ENVIRONMENT_EPHEMERIDES_SPICE_ENGINE_MODE
        ///
        /// @return             Default engine mode

        static Engine::Mode     DefaultMode                                 ( ) ;

        /// @brief              Get default kernels
        ///
        /// @param              [in] aLocalRepository A local repository
        /// @return             Default kernels

        static Array<Kernel>    DefaultKernels                              (   const   Directory&                  aLocalRepository                            ) ;

    private:

        Engine::Mode            mode_ ;

        std::unordered_set<Kernel> kernelSet_ ;

        Array<Pair<Interval, const Kernel*>> earthKernelCache_ ;
        mutable Index           earthKernelCacheIndex_ ;

        mutable std::mutex      mutex_ ;

                                Engine                                      (   const   Engine::Mode&               aMode                                       =   Engine::DefaultMode() ) ;

        bool                    isKernelLoaded_                             (   const   Kernel&                     aKernel                                     ) const ;

        Transform               getTransformAt                              (   const   String&                     aSpiceIdentifier,
                                                                                const   String&                     aFrameName,
                                                                                const   Instant&                    anInstant                                   ) const ;

        void                    setup                                       ( ) ;

        void                    manageKernels                               (   const   String&                     aSpiceIdentifier,
                                                                                const   Instant&                    anInstant                                   ) const ;

        void                    loadKernel_                                 (   const   Kernel&                     aKernel                                     ) ;

        void                    unloadKernel_                               (   const   Kernel&                     aKernel                                     ) ;

        void                    updateEarthKernelCache                      ( ) ;

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
