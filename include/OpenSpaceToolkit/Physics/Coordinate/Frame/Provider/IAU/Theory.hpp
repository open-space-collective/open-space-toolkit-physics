/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IAU_Theory__
#define __OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IAU_Theory__

#include <OpenSpaceToolkit/Core/Type/String.hpp>

namespace ostk
{
namespace physics
{
namespace coord
{
namespace frame
{
namespace provider
{
namespace iau
{

using ostk::core::type::String;

/// @brief                      IAU theory.
///
///                             The IAU 2000A precession-nutation theory relates the International Celestial Reference
///                             Frame to the International Terrestrial Reference Frame and has been effective since
///                             January 2003. In 2006, the IAU moved to adopt a more dynamically consistent precession
///                             model to complement the IAU 2000A nutation theory.
///
/// @ref
/// https://www.researchgate.net/publication/289753602_The_IAU_2000A_and_IAU_2006_precession-nutation_theories_and_their_implementation

enum class Theory
{

    IAU_2000A,  ///< IAU 2000A theory
    IAU_2000B,  ///< IAU 2000B theory
    IAU_2006    ///< IAU 2006 theory

};

/// @brief                      Parse a theory representation to its corresponding string
///
/// @code
///                             String string = StringFromTheory(Theory::IAU_2000A) ; // "IAU 2000A"
/// @endcode
///
/// @param                      [in] aTheory A string
/// @return                     String

String StringFromTheory(const Theory& aTheory);

/// @brief                      Parse a string representation to its corresponding theory
///
/// @code
///                             Theory theory = TheoryFromString("IAU 2000A") ; // Theory::IAU_2000A
/// @endcode
///
/// @param                      [in] aString A string
/// @return                     Theory

Theory TheoryFromString(const String& aString);

}  // namespace iau
}  // namespace provider
}  // namespace frame
}  // namespace coord
}  // namespace physics
}  // namespace ostk

#endif
