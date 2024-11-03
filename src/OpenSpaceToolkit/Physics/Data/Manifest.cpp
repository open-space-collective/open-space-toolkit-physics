/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Container/Dictionary.hpp>
#include <OpenSpaceToolkit/Core/Container/Object.hpp>
#include <OpenSpaceToolkit/Core/Error.hpp>

#include <OpenSpaceToolkit/Physics/Data/Manifest.hpp>
#include <OpenSpaceToolkit/Physics/Data/Utility.hpp>
#include <OpenSpaceToolkit/Physics/Time/DateTime.hpp>
#include <OpenSpaceToolkit/Physics/Time/Scale.hpp>

namespace ostk
{
namespace physics
{
namespace data
{
using ostk::core::container::Dictionary;
using ostk::core::container::Object;

using ostk::physics::data::utilities::getFileModifiedInstant;
using ostk::physics::time::DateTime;
using ostk::physics::time::Instant;
using ostk::physics::time::Scale;

std::ostream& operator<<(std::ostream& anOutputStream, const Manifest& aManifest)
{
    ostk::core::utils::Print::Header(anOutputStream, "Manifest");

    ostk::core::utils::Print::Line(anOutputStream) << "Last Modified Timestamp: " << aManifest.lastModifiedTimestamp_;
    ostk::core::utils::Print::Line(anOutputStream) << aManifest.dictionary_;

    ostk::core::utils::Print::Footer(anOutputStream);

    return anOutputStream;
}

bool Manifest::isDefined() const
{
    return !dictionary_.isEmpty();
}

Instant Manifest::getLastModifiedTimestamp() const
{
    return this->lastModifiedTimestamp_;
}

Instant Manifest::getLastUpdateTimestampFor(const String& aDataName) const
{
    return Instant::DateTime(
        DateTime::Parse(dictionary_[aDataName]["last_update"].accessString(), DateTime::Format::ISO8601), Scale::UTC
    );
}

Instant Manifest::getNextUpdateCheckTimestampFor(const String& aDataName) const
{
    return Instant::DateTime(
        DateTime::Parse(dictionary_[aDataName]["next_update_check"].accessString(), DateTime::Format::ISO8601),
        Scale::UTC
    );
}

Array<URL> Manifest::getRemoteDataUrls(const URL& aBaseUrl, const String& aDataName) const
{
    Array<URL> urls = Array<URL>::Empty();

    for (const auto& dictionaryIt : dictionary_)
    {
        if (dictionaryIt.accessKey() == aDataName)
        {
            Object filenamesDictValue = dictionaryIt.accessValue()["filenames"];

            const Array<Object> filenames =
                filenamesDictValue.isString() ? Array<Object>({filenamesDictValue}) : filenamesDictValue.accessArray();

            for (const auto& filename : filenames)
            {
                const URL url =
                    aBaseUrl + "/" + dictionaryIt.accessValue()["path"].accessString() + "/" + filename.accessString();
                urls.add(url);
            }
        }
    }

    return urls;
}

Array<URL> Manifest::findRemoteDataUrls(const URL& aBaseUrl, const String& aDataNameRegexString) const
{
    Array<URL> urls = Array<URL>::Empty();

    const std::regex aDataNameRegex(aDataNameRegexString);

    for (const auto& dictionaryIt : dictionary_)
    {
        if (dictionaryIt.accessKey().match(aDataNameRegex))
        {
            Object filenamesDictValue = dictionaryIt.accessValue()["filenames"];

            const Array<Object> filenames =
                filenamesDictValue.isString() ? Array<Object>({filenamesDictValue}) : filenamesDictValue.accessArray();

            for (const auto& filename : filenames)
            {
                const URL url =
                    aBaseUrl + "/" + dictionaryIt.accessValue()["path"].accessString() + "/" + filename.accessString();
                urls.add(url);
            }
        }
    }

    if (urls.isEmpty())
    {
        throw ostk::core::error::RuntimeError("No Manifest data entry found matching [{}].", aDataNameRegexString);
    }

    return urls;
}

Manifest Manifest::Undefined()
{
    return {};
}

Manifest Manifest::Load(const File& aFile)
{
    if (!aFile.exists())
    {
        throw ostk::core::error::RuntimeError("Manifest file [{}] does not exist.", aFile.toString());
    }

    Manifest manifest;

    manifest.dictionary_ = Object::Load(aFile, Object::Format::JSON).getDictionary();
    manifest.lastModifiedTimestamp_ = getFileModifiedInstant(aFile);

    return manifest;
}

Manifest::Manifest()
    : dictionary_(Dictionary::Empty()),
      lastModifiedTimestamp_(Instant::Undefined())
{
}

}  // namespace data
}  // namespace physics
}  // namespace ostk
