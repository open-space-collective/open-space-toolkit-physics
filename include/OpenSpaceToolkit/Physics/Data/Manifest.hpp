/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Environment_Data_Manifest__
#define __OpenSpaceToolkit_Physics_Environment_Data_Manifest__

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Container/Dictionary.hpp>
#include <OpenSpaceToolkit/Core/Container/Map.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include <OpenSpaceToolkit/IO/URL.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Ephemeris/SPICE/Kernel.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

namespace ostk
{
namespace physics
{
namespace data
{

using ostk::core::container::Array;
using ostk::core::container::Dictionary;
using ostk::core::container::Map;
using ostk::core::filesystem::File;
using ostk::core::type::String;

using ostk::io::URL;

using ostk::physics::time::Instant;

/// @brief Data class for the OSTk Data Manifest
class Manifest
{
   public:
    /// @brief Output stream operator
    ///
    /// @code
    ///     std::cout << manifest;
    /// @endcode
    ///
    /// @param [in] anOutputStream An output stream
    /// @param [in] aManifest A manifest
    /// @return A reference to output stream
    friend std::ostream& operator<<(std::ostream& anOutputStream, const Manifest& aManifest);

    /// @brief Return true if manifest is defined.
    ///
    /// @code
    ///     Boolean isDefined = manifest.isDefined();
    /// @endcode
    ///
    /// @return True if manifest is defined.
    bool isDefined() const;

    /// @brief Get last update timestamp
    ///
    /// @code
    ///     Instant timestamp = manifest.getLastModifiedTimestamp();
    /// @endcode
    ///
    /// @return Instant indicating when the manifest was last updated based on file modification time
    Instant getLastModifiedTimestamp() const;

    /// @brief Get last update timestamp for data
    ///
    /// @code
    ///     Instant timestamp = manifest.getLastUpdateTimestampFor("earth-gravity-egm96");
    /// @endcode
    ///
    /// @param [in] dataName A data name
    /// @return Last update instant for data
    Instant getLastUpdateTimestampFor(const String& aDataName) const;

    /// @brief Get the next update check timestamp for data
    ///
    /// @code
    ///     Instant timestamp = manifest.getNextUpdateCheckTimestampFor("earth-gravity-egm96");
    /// @endcode
    ///
    /// @param [in] dataName A data name
    /// @return Next update check instant for data
    Instant getNextUpdateCheckTimestampFor(const String& aDataName) const;

    /// @brief Get the remote data URL for a given data name.
    ///
    /// @code
    ///     Array<URL> urls = manifest.getRemoteDataUrls(baseUrl, "earth-gravity-egm96");
    /// @endcode
    ///
    /// @param [in] aBaseUrl A base URL for remote data
    /// @param [in] aDataName name of the data. i.e. the key for the data entry in the manifest
    /// @return Array of remote data URLs
    Array<URL> getRemoteDataUrls(const URL& aBaseUrl, const String& aDataName) const;

    /// @brief Return remote data URLs the for data items matching the given name regex string
    ///
    /// @code
    ///     Array<URL> urls = manifest.findRemoteDataUrls(baseUrl, "earth-gravity-.*");
    /// @endcode
    ///
    /// @param [in] aBaseUrl A base URL for remote data
    /// @param [in] aDataNameRegexString A data name regex string
    /// @return Array of remote data URLs
    Array<URL> findRemoteDataUrls(const URL& aBaseUrl, const String& aDataNameRegexString) const;

    /// @brief Construct an undefined manifest
    ///
    /// @code
    ///     Manifest manifest = Manifest::Undefined();
    /// @endcode
    ///
    /// @return Undefined manifest
    static Manifest Undefined();

    /// @brief Load manifest from file
    ///
    /// @code
    ///     Manifest manifest = Manifest::Load(file);
    /// @endcode
    ///
    /// @param [in] aFile A manifest file
    /// @return Manifest
    static Manifest Load(const File& aFile);

   private:
    Dictionary dictionary_;
    Instant lastModifiedTimestamp_;

    Manifest();
};

}  // namespace data
}  // namespace physics
}  // namespace ostk

#endif
