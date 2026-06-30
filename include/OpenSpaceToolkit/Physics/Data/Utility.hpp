/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Data_Utility__
#define __OpenSpaceToolkit_Physics_Data_Utility__

#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>

#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

namespace ostk
{
namespace physics
{
namespace data
{
namespace utilities
{

using ostk::core::filesystem::File;

using ostk::physics::time::Instant;

/// @brief Get the instant at which a file was last modified.
///
/// @code
///     Instant instant = utilities::getFileModifiedInstant(file);
/// @endcode
///
/// @param [in] aFile A file
/// @return The instant at which the file was last modified
Instant getFileModifiedInstant(const File& aFile);

}  // namespace utilities
}  // namespace data
}  // namespace physics
}  // namespace ostk

#endif
