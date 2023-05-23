/// Apache License 2.0

#include <boost/algorithm/string/predicate.hpp>

#include <OpenSpaceToolkit/Core/Containers/Map.hpp>
#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Ephemerides/SPICE/Kernel.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ostk
{
namespace physics
{
namespace env
{
namespace ephem
{
namespace spice
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Kernel::Kernel(const Kernel::Type& aType, const fs::File& aFile)
    : type_(aType),
      file_(aFile)
{
}

bool Kernel::operator==(const Kernel& aKernel) const
{
    if ((!this->isDefined()) || (!aKernel.isDefined()))
    {
        return false;
    }

    return (type_ == aKernel.type_) && (file_ == aKernel.file_);
}

bool Kernel::operator!=(const Kernel& aKernel) const
{
    return !((*this) == aKernel);
}

bool Kernel::isDefined() const
{
    return (type_ != Kernel::Type::Undefined) && file_.isDefined();
}

Kernel::Type Kernel::getType() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Kernel");
    }

    return type_;
}

String Kernel::getName() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Kernel");
    }

    return file_.getName();
}

fs::File Kernel::getFile() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Kernel");
    }

    return file_;
}

Kernel Kernel::Undefined()
{
    return {Kernel::Type::Undefined, fs::File::Undefined()};
}

Kernel Kernel::File(const fs::File& aFile)
{
    if (!aFile.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("File");
    }

    return {Kernel::TypeFromFileExtension(aFile.getExtension()), aFile};
}

Kernel::Type Kernel::TypeFromString(const String& aString)
{
    using ostk::core::ctnr::Map;

    static const Map<String, Kernel::Type> stringTypeMap = {
        {"Undefined", Kernel::Type::Undefined},
        {"SCLK", Kernel::Type::SCLK},
        {"LSK", Kernel::Type::LSK},
        {"PCK", Kernel::Type::PCK},
        {"IK", Kernel::Type::IK},
        {"FK", Kernel::Type::FK},
        {"EK", Kernel::Type::EK},
        {"MK", Kernel::Type::MK},
        {"SPK", Kernel::Type::SPK},
        {"BPCK", Kernel::Type::BPCK},
        {"CK", Kernel::Type::CK},
        {"BEK", Kernel::Type::BEK}};

    return stringTypeMap.at(aString);
}

String Kernel::StringFromType(const Kernel::Type& aType)
{
    using ostk::core::ctnr::Map;

    static const Map<Kernel::Type, String> typeStringMap = {
        {Kernel::Type::Undefined, "Undefined"},
        {Kernel::Type::SCLK, "SCLK"},
        {Kernel::Type::LSK, "LSK"},
        {Kernel::Type::PCK, "PCK"},
        {Kernel::Type::IK, "IK"},
        {Kernel::Type::FK, "FK"},
        {Kernel::Type::EK, "EK"},
        {Kernel::Type::MK, "MK"},
        {Kernel::Type::SPK, "SPK"},
        {Kernel::Type::BPCK, "BPCK"},
        {Kernel::Type::CK, "CK"},
        {Kernel::Type::BEK, "BEK"}};

    return typeStringMap.at(aType);
}

Kernel::Type Kernel::TypeFromFileExtension(const String& aFileExtension)
{
    // https://naif.jpl.nasa.gov/pub/naif/self_training/individual_docs/03_conventions.pdf

    if (aFileExtension.isEmpty())
    {
        throw ostk::core::error::runtime::Undefined("File extension");
    }

    if (boost::iequals(aFileExtension, "tsc"))
    {
        return Kernel::Type::SCLK;
    }

    if (boost::iequals(aFileExtension, "tls"))
    {
        return Kernel::Type::LSK;
    }

    if (boost::iequals(aFileExtension, "tpc"))
    {
        return Kernel::Type::PCK;
    }

    if (boost::iequals(aFileExtension, "ti"))
    {
        return Kernel::Type::IK;
    }

    if (boost::iequals(aFileExtension, "tf"))
    {
        return Kernel::Type::FK;
    }

    // [TBI]

    // if (boost::iequals(aFileExtension, "???"))
    // {
    //     return Kernel::Type::EK ;
    // }

    if (boost::iequals(aFileExtension, "tm"))
    {
        return Kernel::Type::MK;
    }

    if (boost::iequals(aFileExtension, "bsp"))
    {
        return Kernel::Type::SPK;
    }

    if (boost::iequals(aFileExtension, "bpc"))
    {
        return Kernel::Type::BPCK;
    }

    if (boost::iequals(aFileExtension, "bc"))
    {
        return Kernel::Type::CK;
    }

    if (boost::iequals(aFileExtension, "bes"))
    {
        return Kernel::Type::BEK;
    }

    return Kernel::Type::Undefined;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}  // namespace spice
}  // namespace ephem
}  // namespace env
}  // namespace physics
}  // namespace ostk

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
