/// Apache License 2.0

#include <chrono>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <numeric>
#include <thread>

#include <OpenSpaceToolkit/Core/Container/Map.hpp>
#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Path.hpp>
#include <OpenSpaceToolkit/Core/Type/Integer.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Physics/Manager.hpp>
#include <OpenSpaceToolkit/Physics/Time/Date.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Time/Scale.hpp>
#include <OpenSpaceToolkit/Physics/Time/Time.hpp>

namespace ostk
{
namespace physics
{

using ostk::core::filesystem::Path;
using ostk::core::type::String;

Manager::Mode Manager::getMode() const
{
    std::lock_guard<std::mutex> lock {mutex_};

    return mode_;
}

Directory Manager::getLocalRepository() const
{
    std::lock_guard<std::mutex> lock {mutex_};

    return localRepository_;
}

Duration Manager::getLocalRepositoryLockTimeout() const
{
    return localRepositoryLockTimeout_;
}

void Manager::setMode(const Manager::Mode& aMode)
{
    std::lock_guard<std::mutex> lock {mutex_};

    mode_ = aMode;
}

void Manager::setLocalRepository(const Directory& aDirectory)
{
    if (!aDirectory.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Directory");
    }

    const std::lock_guard<std::mutex> lock {mutex_};

    localRepository_ = aDirectory;

    setup_();
}

void Manager::reset()
{
    const std::lock_guard<std::mutex> lock {mutex_};

    mode_ = Manager::DefaultMode_(managerModeEnvironmentVariableName_);
    localRepository_ = Manager::DefaultLocalRepository_(
        defaultLocalRepositoryDirectory_, localRepositoryEnvironmentVariableName_, localRepositoryPath_
    );
    localRepositoryLockTimeout_ =
        Manager::DefaultLocalRepositoryLockTimeout_(localRepositoryLockTimeoutEnvironmentVariableName_);
}

void Manager::clearLocalRepository()
{
    localRepository_.remove();

    setup_();
}

Manager::Manager(
    const String& aManagerModeEnvironmentVariableName,
    const Directory& aDefaultLocalRepositoryDirectory,
    const String& aLocalRepositoryEnvironmentVariableName,
    const Path& aLocalRepositoryPath,
    const String& aLocalRepositoryLockTimeoutEnvironmentVariableName
)
    : managerModeEnvironmentVariableName_(aManagerModeEnvironmentVariableName),
      defaultLocalRepositoryDirectory_(aDefaultLocalRepositoryDirectory),
      localRepositoryEnvironmentVariableName_(aLocalRepositoryEnvironmentVariableName),
      localRepositoryPath_(aLocalRepositoryPath),
      localRepositoryLockTimeoutEnvironmentVariableName_(aLocalRepositoryLockTimeoutEnvironmentVariableName),
      mode_(Manager::Mode::Automatic),
      localRepository_(Directory::Undefined()),
      localRepositoryLockTimeout_(Duration::Undefined())
{
    reset();
    setup_();
}

void Manager::setup_()
{
    if (!localRepository_.exists())
    {
        localRepository_.create();
    }
}

bool Manager::isLocalRepositoryLocked_() const
{
    return getLocalRepositoryLockFile_().exists();
}

File Manager::getLocalRepositoryLockFile_() const
{
    return File::Path(localRepository_.getPath() + Path::Parse(".lock"));
}

void Manager::lockLocalRepository_(const Duration& aTimeout) const
{
    std::cout << String::Format("Locking local repository [{}]...", localRepository_.toString()) << std::endl;

    const auto tryLock = [](File& aLockFile) -> bool
    {
        if (!aLockFile.exists())  // [TBM] Should use system-wide semaphore instead (race condition can still occur)
        {
            try
            {
                aLockFile.create();

                return true;
            }
            catch (...)
            {
                // Do nothing
            }

            return false;
        }

        return false;
    };

    const Instant timeoutInstant = Instant::Now() + aTimeout;

    File lockFile = getLocalRepositoryLockFile_();

    while (!tryLock(lockFile))
    {
        if (Instant::Now() >= timeoutInstant)
        {
            throw ostk::core::error::RuntimeError("Cannot lock local repository: timeout reached.");
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void Manager::unlockLocalRepository_() const
{
    std::cout << String::Format("Unlocking local repository [{}]...", localRepository_.toString()) << std::endl;

    if (!isLocalRepositoryLocked_())
    {
        throw ostk::core::error::RuntimeError("Cannot unlock local repository: lock file does not exist.");
    }

    getLocalRepositoryLockFile_().remove();
}

Directory Manager::DefaultLocalRepository_(
    const Directory& aDefaultLocalRepositoryDirectory,
    const String& aLocalRepositoryEnvironmentVariableName,
    const Path& aLocalRepositoryPath
)
{
    if (const char* localRepositoryPath = std::getenv(aLocalRepositoryEnvironmentVariableName.c_str()))
    {
        return Directory::Path(Path::Parse(localRepositoryPath));
    }
    else if (const char* dataPath = std::getenv("OSTK_PHYSICS_DATA_LOCAL_REPOSITORY"))
    {
        return Directory::Path(Path::Parse(dataPath) + aLocalRepositoryPath);
    }

    return aDefaultLocalRepositoryDirectory;
}

Manager::Mode Manager::DefaultMode_(const String& aManagerModeEnvironmentVariableName)
{
    static const Manager::Mode defaultMode = Mode::Automatic;

    if (const char* modeString = std::getenv(aManagerModeEnvironmentVariableName.c_str()))
    {
        if (strcmp(modeString, "Manual") == 0)
        {
            return Manager::Mode::Manual;
        }
        else if (strcmp(modeString, "Automatic") == 0)
        {
            return Manager::Mode::Automatic;
        }
        else
        {
            throw ostk::core::error::runtime::Wrong("Mode", modeString);
        }
    }

    return defaultMode;
}

Duration Manager::DefaultLocalRepositoryLockTimeout_(const String& aLocalRepositoryLockTimeoutEnvironmentVariableName)
{
    static const Duration defaultLocalRepositoryLockTimeout = Duration::Seconds(60.0);

    if (const char* localRepositoryLockTimeoutString =
            std::getenv(aLocalRepositoryLockTimeoutEnvironmentVariableName.c_str()))
    {
        return Duration::Parse(localRepositoryLockTimeoutString);
    }

    return defaultLocalRepositoryLockTimeout;
}

}  // namespace physics
}  // namespace ostk
