////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library ▸ Physics
/// @file           Library/Physics/Environment/Ephemerides/SPICE/Index.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Physics_Environment_Ephemerides_SPICE_Index__
#define __Library_Physics_Environment_Ephemerides_SPICE_Index__

#include <Library/Physics/Environment/Ephemerides/SPICE/Kernel.hpp>
#include <Library/Physics/Time/Instant.hpp>

#include <Library/IO/URL.hpp>

#include <Library/Core/FileSystem/File.hpp>
#include <Library/Core/Containers/Map.hpp>
#include <Library/Core/Containers/Array.hpp>
#include <Library/Core/Types/String.hpp>

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

using library::core::types::String ;
using library::core::ctnr::Array ;
using library::core::ctnr::Map ;
using library::core::fs::File ;

using library::io::URL ;

using library::physics::time::Instant ;
using library::physics::env::ephem::spice::Kernel ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      SPICE Toolkit kernel index

class Index
{

    public:

        /// @brief              Output stream operator
        ///
        /// @param              [in] anOutputStream An output stream
        /// @param              [in] anIndex An index
        /// @return             A reference to output stream

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Index&                      anIndex                                     ) ;

        /// @brief              Returns true if index is empty
        ///
        /// @return             True if index is empty

        bool                    isEmpty                                     ( ) const ;

        /// @brief              Get index timestamp
        ///
        /// @return             Index timestamp

        Instant                 getTimestamp                                ( ) const ;

        /// @brief              Get remote URL of kernel
        ///
        /// @param              [in] aKernel A kernel
        /// @return             Remote URL of kernel

        URL                     getRemoteUrlOfKernel                        (   const   Kernel&                     aKernel                                     ) const ;

        /// @brief              Find remote URLs of kernels matching regular expression
        ///
        /// @param              [in] aKernelNameRegex A regular expression
        /// @return             Array of URLs

        Array<URL>              findRemoteUrls                              (   const   std::regex&                 aKernelNameRegex                            ) const ;

        /// @brief              Constructs an empty index
        ///
        /// @return             Empty index

        static Index            Empty                                       ( ) ;

        /// @brief              Load index from file
        ///
        /// @param              [in] aFile An index file
        /// @return             Index

        static Index            Load                                        (   const   File&                       aFile                                       ) ;

    private:

        Instant                 timestamp_ ;

        Map<Kernel::Type, Map<String, URL>> itemMap_ ;

                                Index                                       ( ) ;

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
