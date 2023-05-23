/// Apache License 2.0 

#ifndef __OpenSpaceToolkit_Physics_Environment_Ephemerides_SPICE_Index__
#define __OpenSpaceToolkit_Physics_Environment_Ephemerides_SPICE_Index__

#include <OpenSpaceToolkit/Physics/Environment/Ephemerides/SPICE/Kernel.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

#include <OpenSpaceToolkit/IO/URL.hpp>

#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>
#include <OpenSpaceToolkit/Core/Containers/Map.hpp>
#include <OpenSpaceToolkit/Core/Containers/Array.hpp>
#include <OpenSpaceToolkit/Core/Types/String.hpp>

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

using ostk::core::types::String ;
using ostk::core::ctnr::Array ;
using ostk::core::ctnr::Map ;
using ostk::core::fs::File ;

using ostk::io::URL ;

using ostk::physics::time::Instant ;
using ostk::physics::env::ephem::spice::Kernel ;

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
