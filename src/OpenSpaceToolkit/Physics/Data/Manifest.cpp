/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Containers/Dictionary.hpp>
#include <OpenSpaceToolkit/Core/Containers/Object.hpp>
#include <OpenSpaceToolkit/Core/Error.hpp>

#include <OpenSpaceToolkit/Physics/Data/Manifest.hpp>
#include <OpenSpaceToolkit/Physics/Time/DateTime.hpp>
#include <OpenSpaceToolkit/Physics/Time/Scale.hpp>

namespace ostk
{
namespace physics
{
namespace data
{

std::ostream& operator<<(std::ostream& anOutputStream, const Manifest& aManifest)
{
    ostk::core::utils::Print::Header(anOutputStream, "Manifest");

    ostk::core::utils::Print::Line(anOutputStream) << aManifest.dictionary_;

    ostk::core::utils::Print::Footer(anOutputStream);

    return anOutputStream;
}

bool Manifest::isEmpty() const
{
    return dictionary_.isEmpty();
}

Instant Manifest::getLastUpdateTimestampFor(const String& dataName) const
{
    using ostk::physics::time::Instant;
    using ostk::physics::time::DateTime;
    using ostk::physics::time::Scale;

    return Instant::DateTime(
        DateTime::Parse(dictionary_[dataName]["last_update"].accessString(), DateTime::Format::ISO8601), Scale::UTC
    );
}

Manifest Manifest::Empty()
{
    return {};
}

Manifest Manifest::Load(const File& aFile)
{
    using ostk::core::ctnr::Object;
    using ostk::core::ctnr::Dictionary;

    if (!aFile.exists())
    {
        throw ostk::core::error::RuntimeError("Manifest file [{}] does not exist.", aFile.toString());
    }

    Manifest manifest;

    manifest.dictionary_ = Object::Load(aFile, Object::Format::JSON).getDictionary();

    return manifest;
}

Manifest::Manifest()
    : dictionary_(Dictionary::Empty())
{
}

}  // namespace data
}  // namespace physics
}  // namespace ostk
