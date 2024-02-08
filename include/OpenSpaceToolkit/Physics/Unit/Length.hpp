/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Unit_Length__
#define __OpenSpaceToolkit_Physics_Unit_Length__

#include <OpenSpaceToolkit/Core/Type/Integer.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include <OpenSpaceToolkit/Physics/Unit/Unit.hpp>

namespace ostk
{
namespace physics
{
namespace unit
{

using ostk::core::type::Integer;
using ostk::core::type::Real;
using ostk::core::type::String;

/// @brief                      Length
///
/// @ref                        https://en.wikipedia.org/wiki/Length

class Length : public Unit
{
   public:
    enum class Unit
    {

        Undefined,        ///< Undefined
        Meter,            ///< Meter (SI)
        Foot,             ///< Foot
        TerrestrialMile,  ///< Terrestrial mile
        NauticalMile,     ///< Nautical mile
        AstronomicalUnit  ///< Astronomical Unit

    };

    /// @brief              Constructor
    ///
    /// @code
    ///                     Length length(1.0, Length::Unit::Meter) ;
    /// @endcode
    ///
    /// @param              [in] aValue A value
    /// @param              [in] aUnit A length unit

    Length(const Real& aValue, const Length::Unit& aUnit);

    virtual Length* clone() const override;

    bool operator==(const Length& aLength) const;

    bool operator!=(const Length& aLength) const;

    bool operator<(const Length& aLength) const;

    bool operator<=(const Length& aLength) const;

    bool operator>(const Length& aLength) const;

    bool operator>=(const Length& aLength) const;

    Length operator+(const Length& aLength) const;

    Length operator-(const Length& aLength) const;

    Length operator*(const Real& aReal) const;

    Length operator/(const Real& aReal) const;

    Length& operator+=(const Length& aLength);

    Length& operator-=(const Length& aLength);

    Length& operator*=(const Real& aReal);

    Length& operator/=(const Real& aReal);

    friend Length operator*(const Real& aReal, const Length& aLength);

    Length operator+() const;

    Length operator-() const;

    friend std::ostream& operator<<(std::ostream& anOutputStream, const Length& aLength);

    virtual bool isDefined() const override;

    bool isZero() const;

    Length::Unit getUnit() const;

    Real in(const Length::Unit& aUnit) const;

    Real inMeters() const;

    Real inKilometers() const;

    virtual String toString(const Integer& aPrecision = Integer::Undefined()) const override;

    static Length Undefined();

    static Length Millimeters(const Real& aValue);

    static Length Meters(const Real& aValue);

    static Length Kilometers(const Real& aValue);

    static Length Parse(const String& aString);

    static String StringFromUnit(const Length::Unit& aUnit);

    static String SymbolFromUnit(const Length::Unit& aUnit);

    static Length::Unit UnitFromSymbol(const String& aSymbol);

   private:
    Length::Unit unit_;

    static Real SIRatio(const Length::Unit& aUnit);
};

}  // namespace unit
}  // namespace physics
}  // namespace ostk

#endif
