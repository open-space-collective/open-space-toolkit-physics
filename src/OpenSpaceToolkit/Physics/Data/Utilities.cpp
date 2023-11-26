#include <ctime>
#include <filesystem>

#include <OpenSpaceToolkit/Physics/Data/Utilities.hpp>
#include <OpenSpaceToolkit/Physics/Time/DateTime.hpp>

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
using ostk::physics::time::Scale;
using ostk::physics::time::DateTime;

Instant getFileModifiedInstant(const File& aFile)
{
    if (!aFile.exists())
    {
        throw ostk::core::error::RuntimeError(
            "Cannot get file modification time. File [{}] does not exist.", aFile.toString()
        );
    }

    std::filesystem::path filePath = std::filesystem::path(std::string(aFile.getPath().getAbsolutePath().toString()));

    const std::filesystem::file_time_type lastWriteTime = std::filesystem::last_write_time(filePath);

    // TBI: this is an approximation. In c++ 20, there is a better way
    // https://stackoverflow.com/questions/61030383/how-to-convert-stdfilesystemfile-time-type-to-time-t
    auto cftime = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
        lastWriteTime - std::filesystem::file_time_type::clock::now() + std::chrono::system_clock::now()
    );

    // Convert to time_t
    std::time_t timeT = std::chrono::system_clock::to_time_t(cftime);

    // Convert to struct tm in UTC
    std::tm* utcTime = std::gmtime(&timeT);

    DateTime lastWriteTimeDT = DateTime(
        utcTime->tm_year + 1900,
        utcTime->tm_mon + 1,
        utcTime->tm_mday,
        utcTime->tm_hour,
        utcTime->tm_min,
        utcTime->tm_sec
    );

    return Instant::DateTime(lastWriteTimeDT, Scale::UTC);
}

}  // namespace utilities
}  // namespace data
}  // namespace physics
}  // namespace ostk
