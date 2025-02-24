/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Unit_Derived_Angle__
#define __OpenSpaceToolkit_Physics_Unit_Derived_Angle__

#include <OpenSpaceToolkit/Core/Type/Integer.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/Angle.hpp>
#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

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

using ostk::mathematics::object::Vector2d;
using ostk::mathematics::object::Vector3d;

/// @brief                      Angle
///
///                             In plane geometry, an angle is the figure formed by two rays, called the sides of the
///                             angle, sharing a common endpoint, called the vertex of the angle.
///
/// @ref                        https://en.wikipedia.org/wiki/Angle

class Angle : public Unit
{
   public:
    enum class Unit
    {

        Undefined,  ///< Undefined
        Radian,     ///< Radian
        Degree,     ///< Degree
        Arcminute,  ///< Arcminute
        Arcsecond,  ///< Arcsecond
        Revolution  ///< Revolution

    };

    /// @brief              Constructor
    ///
    /// @code
    ///                     Angle angle(90.0, Angle::Unit::Degree) ;
    /// @endcode
    ///
    /// @param              [in] aValue A value
    /// @param              [in] aUnit An angle unit

    Angle(const Real& aValue, const Angle::Unit& aUnit);

    Angle(const ostk::mathematics::geometry::Angle& anAngle);

    virtual Angle* clone() const override;

    bool operator==(const Angle& anAngle) const;

    bool operator!=(const Angle& anAngle) const;

    Angle operator+(const Angle& anAngle) const;

    Angle operator-(const Angle& anAngle) const;

    Angle operator*(const Real& aReal) const;

    Angle operator/(const Real& aReal) const;

    Angle& operator+=(const Angle& anAngle);

    Angle& operator-=(const Angle& anAngle);

    Angle& operator*=(const Real& aReal);

    Angle& operator/=(const Real& aReal);

    friend Angle operator*(const Real& aReal, const Angle& anAngle);

    Angle operator+() const;

    Angle operator-() const;

    operator ostk::mathematics::geometry::Angle() const;

    friend std::ostream& operator<<(std::ostream& anOutputStream, const Angle& anAngle);

    virtual bool isDefined() const override;

    bool isZero() const;

    Angle::Unit getUnit() const;

    Real in(const Angle::Unit& aUnit) const;

    Real inRadians() const;

    Real inRadians(const Real& aLowerBound, const Real& anUpperBound) const;

    Real inDegrees() const;

    Real inDegrees(const Real& aLowerBound, const Real& anUpperBound) const;

    Real inArcminutes() const;

    Real inArcminutes(const Real& aLowerBound, const Real& anUpperBound) const;

    Real inArcseconds() const;

    Real inArcseconds(const Real& aLowerBound, const Real& anUpperBound) const;

    Real inRevolutions() const;

    virtual String toString(const Integer& aPrecision = Integer::Undefined()) const override;

    static Angle Undefined();

    static Angle Zero();

    static Angle HalfPi();

    static Angle Pi();

    static Angle TwoPi();

    static Angle Radians(const Real& aValue);

    static Angle Degrees(const Real& aValue);

    static Angle Arcminutes(const Real& aValue);

    static Angle Arcseconds(const Real& aValue);

    static Angle Revolutions(const Real& aValue);

    static Angle Between(const Vector2d& aFirstVector, const Vector2d& aSecondVector);

    static Angle Between(const Vector3d& aFirstVector, const Vector3d& aSecondVector);

    static Angle Parse(const String& aString);

    static String StringFromUnit(const Angle::Unit& aUnit);

    static String SymbolFromUnit(const Angle::Unit& aUnit);

    static Angle::Unit UnitFromSymbol(const String& aSymbol);

   private:
    Angle::Unit unit_;

    static Real SIRatio(const Angle::Unit& aUnit);

    static Real ReduceRange(const Real& aValue, const Real& aRangeLowerBound, const Real& aRangeUpperBound);
};

}  // namespace unit
}  // namespace physics
}  // namespace ostk

#endif
