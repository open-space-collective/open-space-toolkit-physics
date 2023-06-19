/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/IAU/Theory.hpp>

namespace ostk
{
namespace physics
{
namespace coord
{
namespace frame
{
namespace providers
{
namespace iau
{

String StringFromTheory(const Theory& aTheory)
{
    switch (aTheory)
    {
        case Theory::IAU_2000A:
            return "IAU 2000A";

        case Theory::IAU_2000B:
            return "IAU 2000B";

        case Theory::IAU_2006:
            return "IAU 2006";

        default:
            throw ostk::core::error::runtime::Wrong("Theory");
            break;
    }

    return String::Empty();
}

Theory TheoryFromString(const String& aString)
{
    if (aString == "IAU 2000A")
    {
        return Theory::IAU_2000A;
    }
    else if (aString == "IAU 2000B")
    {
        return Theory::IAU_2000B;
    }
    else if (aString == "IAU 2006")
    {
        return Theory::IAU_2006;
    }

    throw ostk::core::error::runtime::Wrong("String");
}

}  // namespace iau
}  // namespace providers
}  // namespace frame
}  // namespace coord
}  // namespace physics
}  // namespace ostk
