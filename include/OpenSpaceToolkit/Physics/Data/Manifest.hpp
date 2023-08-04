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

using ostk::physics::time::Instant;

/// @brief                      Data class for the OSTk Data Manifest

class Manifest
{
   public:
    /// @brief              Output stream operator
    ///
    /// @param              [in] anOutputStream An output stream
    /// @param              [in] aManifest A manifest
    /// @return             A reference to output stream

    friend std::ostream& operator<<(std::ostream& anOutputStream, const Manifest& aManifest);

    /// @brief              Return true if manifest is empty
    ///
    /// @return             True if manifest is empty

    bool isDefined() const;

    /// @brief              Get last update timestamp for data
    ///
    /// @param              [in] dataName A data name
    /// @return             Last update instant for data

    Instant getLastUpdateTimestampFor(const String& aDataName) const;

    /// @brief              Construct an empty manifest
    ///
    /// @return             Empty manifest

    static Manifest Undefined();

    /// @brief              Load manifest from file
    ///
    /// @param              [in] aFile A manifest file
    /// @return             Manifest

    static Manifest Load(const File& aFile);

   private:
    Dictionary dictionary_;

    Manifest();
};

}  // namespace data
}  // namespace physics
}  // namespace ostk

#endif
