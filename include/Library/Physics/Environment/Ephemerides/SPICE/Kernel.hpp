////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           Library/Physics/Environment/Ephemerides/SPICE/Kernel.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Physics_Environment_Ephemerides_SPICE_Kernel__
#define __Library_Physics_Environment_Ephemerides_SPICE_Kernel__

#include <Library/Physics/Time/Instant.hpp>

#include <Library/Core/FileSystem/File.hpp>
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

namespace fs = library::core::fs ;

using library::core::types::String ;

using library::physics::time::Instant ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      SPICE Toolkit kernel
///
/// @ref                        https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/info/intrdctn.html

class Kernel
{

    public:

        enum class Type
        {

            Undefined,          ///< Undefined kernel
            SCLK,               ///< Spacecraft clock kernels (text)
            LSK,                ///< Leapseconds kernels (text)
            PCK,                ///< Physical constants kernels (text)
            IK,                 ///< Instrument parameter kernels (text)
            FK,                 ///< Frame definition kernels (text)
            EK,                 ///< E-kernels (text)
            MK,                 ///< Meta-kernels (text)
            SPK,                ///< SP-kernels (binary)
            BPCK,               ///< Physical constants kernels (binary)
            CK,                 ///< C-kernels (binary)
            BEK                 ///< Events kernels (binary)

        } ;

        /// @brief              Constructor
        ///
        /// @param              [in] aType A kernel type
        /// @param              [in] aFile A kernel file

                                Kernel                                      (   const   Kernel::Type&               aType,
                                                                                const   fs::File&                   aFile                                       ) ;

        /// @brief              Equal to operator
        ///
        /// @param              [in] aKernel A kernel
        /// @return             True if kernels are equal

        bool                    operator ==                                 (   const   Kernel&                     aKernel                                     ) const ;

        /// @brief              Not equal to operator
        ///
        /// @param              [in] aKernel A kernel
        /// @return             True if kernels are not equal

        bool                    operator !=                                 (   const   Kernel&                     aKernel                                     ) const ;

        /// @brief              Returns true if kernel is defined
        ///
        /// @return             True if kernel is defined

        bool                    isDefined                                   ( ) const ;

        /// @brief              Get kernel type
        ///
        /// @return             Kernel type

        Kernel::Type            getType                                     ( ) const ;

        /// @brief              Get kernel name
        ///
        /// @return             Kernel name

        String                  getName                                     ( ) const ;

        /// @brief              Get kernel file
        ///
        /// @return             Kernel file

        fs::File                getFile                                     ( ) const ;

        /// @brief              Constructs an undefined kernel
        ///
        /// @return             Undefined kernel

        static Kernel           Undefined                                   ( ) ;

        /// @brief              Constructs a kernel from a file
        ///
        /// @param              [in] aFile A kernel file
        /// @return             Kernel

        static Kernel           File                                        (   const   fs::File&                   aFile                                       ) ;

        /// @brief              Converts kernel type string to type
        ///
        /// @param              [in] aType A kernel type string
        /// @return             A kernel type

        static Kernel::Type     TypeFromString                              (   const   String&                     aString                                     ) ;

        /// @brief              Converts kernel type to string
        ///
        /// @param              [in] aType A kernel type
        /// @return             A string

        static String           StringFromType                              (   const   Kernel::Type&               aType                                       ) ;

        /// @brief              Converts file extension to kernel type
        ///
        /// @param              [in] aFileExtension A file extension
        /// @return             Kernel type

        static Kernel::Type     TypeFromFileExtension                       (   const   String&                     aFileExtension                              ) ;

    private:

        Kernel::Type            type_ ;
        fs::File                file_ ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace std
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using library::physics::env::ephem::spice::Kernel ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <>
struct hash<Kernel>
{

    size_t                      operator ()                                 (   const   Kernel&                     aKernel                                     ) const
    {
        return hash<std::string>()(aKernel.getFile().getName()) ;
    }

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
