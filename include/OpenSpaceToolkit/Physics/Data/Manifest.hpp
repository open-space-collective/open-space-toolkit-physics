/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Environment_Data_Manifest__
#define __OpenSpaceToolkit_Physics_Environment_Data_Manifest__

#include <OpenSpaceToolkit/Core/Containers/Array.hpp>
#include <OpenSpaceToolkit/Core/Containers/Dictionary.hpp>
#include <OpenSpaceToolkit/Core/Containers/Map.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>
#include <OpenSpaceToolkit/Core/Types/String.hpp>

#include <OpenSpaceToolkit/IO/URL.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Ephemerides/SPICE/Kernel.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

namespace ostk
{
namespace physics
{
namespace data
{

using ostk::core::types::String;
using ostk::core::ctnr::Array;
using ostk::core::ctnr::Map;
using ostk::core::fs::File;
using ostk::core::ctnr::Dictionary;

using ostk::io::URL;

using ostk::physics::time::Instant;

/// @brief                      Data class for the OSTk Data Manifest

class Manifest
{
   public:
    /// @brief                  Output stream operator
    ///
    /// @param                  [in] anOutputStream An output stream
    /// @param                  [in] aManifest A manifest
    /// @return                 A reference to output stream

    friend std::ostream& operator<<(std::ostream& anOutputStream, const Manifest& aManifest);

    /// @brief                  Return true if manifest is defined.
    ///
    /// @return                 True if manifest is defined.

    bool isDefined() const;

    /// @brief                  Get last update timestamp for data
    ///
    /// @param                  [in] dataName A data name
    /// @return                 Last update instant for data

    Instant getLastUpdateTimestampFor(const String& aDataName) const;

    /// @brief                  Get the remote data URL for a given data name.
    ///
    /// @param                  [in] aBaseUrl A base URL for remote data
    /// @param                  [in] aDataName name of the data. i.e. the key for the data entry in the manifest
    /// @return                 Array of remote data URLs

    Array<URL> getRemoteDataUrls(const URL& aBaseUrl, const String& aDataName) const;

    /// @brief                  Return remote data URLs the for data items matching the given name regex string
    ///
    /// @param                  [in] aBaseUrl A base URL for remote data
    /// @param                  [in] aDataNameRegexString A data name regex string
    /// @return                 Array of remote data URLs

    Array<URL> findRemoteDataUrls(const URL& aBaseUrl, const String& aDataNameRegexString) const;

    /// @brief                  Construct an undefined manifest
    ///
    /// @return                 Undefined manifest

    static Manifest Undefined();

    /// @brief                  Load manifest from file
    ///
    /// @param                  [in] aFile A manifest file
    /// @return                 Manifest

    static Manifest Load(const File& aFile);

   private:
    Dictionary dictionary_;

    Manifest();
};

}  // namespace data
}  // namespace physics
}  // namespace ostk

#endif
