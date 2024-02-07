/// Apache License 2.0

#include <array>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

#include <OpenSpaceToolkit/Physics/Data/Utility.hpp>

#include <Global.test.hpp>

using ostk::core::filesystem::File;
using ostk::core::filesystem::Path;
using ostk::core::type::String;

using ostk::physics::time::Scale;
using ostk::physics::time::Instant;
using ostk::physics::time::DateTime;
using ostk::physics::time::Duration;

String runCommand(String commandString)
{
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(commandString.c_str(), "r"), pclose);
    if (!pipe)
    {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
    {
        result += buffer.data();
    }

    return String(result).trim();
}

TEST(OpenSpaceToolkit_Physics_Data_Utilities, GetFileModifiedInstant)
{
    const String repoToplevelPath = runCommand("git rev-parse --show-toplevel");

    // File choice is arbitrary
    const File manifestFile = File::Path(
        Path::Parse(repoToplevelPath) + Path::Parse("test/OpenSpaceToolkit/Physics/Data/Manifest/manifest.json")
    );

    // Run the GNU "stat" command to compare. Not portable, so not appropriate for implementation, but useful for
    // testing.
    std::string commandString =
        String::Format("stat --format=%.19y {}", manifestFile.getPath().getAbsolutePath().toString());

    const String resultString = runCommand(commandString);

    Instant expectedInstant = Instant::DateTime(DateTime::Parse(resultString, DateTime::Format::Standard), Scale::UTC);

    const Instant actualInstant = ostk::physics::data::utilities::getFileModifiedInstant(manifestFile);

    EXPECT_TRUE(actualInstant - expectedInstant < Duration::Milliseconds(1.0));
}
