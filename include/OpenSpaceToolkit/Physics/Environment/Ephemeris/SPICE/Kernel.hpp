/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Environment_Ephemeris_SPICE_Kernel__
#define __OpenSpaceToolkit_Physics_Environment_Ephemeris_SPICE_Kernel__

#include <optional>

#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

namespace ostk
{
namespace physics
{
namespace environment
{
namespace ephemeris
{
namespace spice
{

namespace filesystem = ostk::core::filesystem;

using ostk::core::type::String;

using ostk::physics::time::Instant;

/// @brief SPICE Toolkit kernel. Generalized data class for every type of kernel.
///
/// @ref https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/info/intrdctn.html

class Kernel
{
   public:
    enum class Type
    {

        SCLK,  ///< Spacecraft clock kernels (text)
        LSK,   ///< Leapseconds kernels (text)
        PCK,   ///< Physical constants kernels (text)
        IK,    ///< Instrument parameter kernels (text)
        FK,    ///< Frame definition kernels (text)
        EK,    ///< E-kernels (text)
        MK,    ///< Meta-kernels (text)
        SPK,   ///< SP-kernels (binary)
        BPCK,  ///< Physical constants kernels (binary)
        CK,    ///< C-kernels (binary)
        BEK    ///< Events kernels (binary)

    };

    /// @brief Constructor
    ///
    /// @code
    ///     Kernel kernel = Kernel(Kernel::Type::SPK, File::Path(Path::Parse("/path/to/kernel.bsp")));
    /// @endcode
    ///
    /// @param [in] aType A kernel type
    /// @param [in] aFile A kernel file

    Kernel(const Kernel::Type& aType, const filesystem::File& aFile);

    /// @brief Equal to operator
    ///
    /// @code
    ///     Kernel kernelA = Kernel::File(file);
    ///     Kernel kernelB = Kernel::File(file);
    ///     kernelA == kernelB;
    /// @endcode
    ///
    /// @param [in] aKernel A kernel
    /// @return True if kernels are equal

    bool operator==(const Kernel& aKernel) const;

    /// @brief Not equal to operator
    ///
    /// @code
    ///     Kernel kernelA = Kernel::File(fileA);
    ///     Kernel kernelB = Kernel::File(fileB);
    ///     kernelA != kernelB;
    /// @endcode
    ///
    /// @param [in] aKernel A kernel
    /// @return True if kernels are not equal

    bool operator!=(const Kernel& aKernel) const;

    /// @brief Get kernel type
    ///
    /// @code
    ///     Kernel kernel = Kernel::File(aFile);
    ///     Kernel::Type type = kernel.getType();
    /// @endcode
    ///
    /// @return Kernel type

    Kernel::Type getType() const;

    /// @brief Get kernel name
    ///
    /// @code
    ///     Kernel kernel = Kernel::File(aFile);
    ///     String name = kernel.getName();
    /// @endcode
    ///
    /// @return Kernel name

    String getName() const;

    /// @brief Get kernel file
    ///
    /// @code
    ///     Kernel kernel = Kernel::File(aFile);
    ///     const filesystem::File& file = kernel.getFile();
    /// @endcode
    ///
    /// @return Const reference to kernel file

    const filesystem::File& getFile() const;

    /// @brief Constructs a kernel from a file
    ///
    /// @code
    ///     Kernel kernel = Kernel::File(filesystem::File::Path(Path::Parse("/path/to/de430.bsp")));
    /// @endcode
    ///
    /// @param [in] aFile A kernel file
    /// @return Kernel

    static Kernel File(const filesystem::File& aFile);

    /// @brief Converts kernel type string to type
    ///
    /// @code
    ///     Kernel::Type type = Kernel::TypeFromString("SPK");
    /// @endcode
    ///
    /// @param [in] aType A kernel type string
    /// @return A kernel type

    static Kernel::Type TypeFromString(const String& aString);

    /// @brief Converts kernel type to string
    ///
    /// @code
    ///     String str = Kernel::StringFromType(Kernel::Type::SPK); // "SPK"
    /// @endcode
    ///
    /// @param [in] aType A kernel type
    /// @return A string

    static String StringFromType(const Kernel::Type& aType);

    /// @brief Converts file extension to kernel type
    ///
    /// @code
    ///     std::optional<Kernel::Type> type = Kernel::TypeFromFileExtension("bsp"); // Kernel::Type::SPK
    /// @endcode
    ///
    /// @param [in] aFileExtension A file extension
    /// @return Kernel type, or std::nullopt if the extension is not a known kernel extension

    static std::optional<Kernel::Type> TypeFromFileExtension(const String& aFileExtension);

   private:
    Kernel::Type type_;
    filesystem::File file_;
};

}  // namespace spice
}  // namespace ephemeris
}  // namespace environment
}  // namespace physics
}  // namespace ostk

namespace std
{

using ostk::physics::environment::ephemeris::spice::Kernel;

template <>
struct hash<Kernel>
{
    size_t operator()(const Kernel& aKernel) const
    {
        return hash<std::string>()(aKernel.getFile().getName());
    }
};

}  // namespace std

#endif
