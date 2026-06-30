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

/// @brief Angle
///
/// In plane geometry, an angle is the figure formed by two rays, called the sides of the
/// angle, sharing a common endpoint, called the vertex of the angle.
///
/// @ref https://en.wikipedia.org/wiki/Angle

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

    /// @brief Constructor
    ///
    /// @code
    ///     Angle angle(90.0, Angle::Unit::Degree);
    /// @endcode
    ///
    /// @param [in] aValue A value
    /// @param [in] aUnit An angle unit
    Angle(const Real& aValue, const Angle::Unit& aUnit);

    /// @brief Constructor from a mathematics geometry angle.
    ///
    /// @code
    ///     Angle angle(ostk::mathematics::geometry::Angle::Degrees(90.0));
    /// @endcode
    ///
    /// @param [in] anAngle A mathematics geometry angle
    Angle(const ostk::mathematics::geometry::Angle& anAngle);

    /// @brief Clone the angle.
    ///
    /// @code
    ///     Angle angle = Angle::Degrees(90.0);
    ///     Angle* clonePtr = angle.clone();
    /// @endcode
    ///
    /// @return A pointer to a dynamically allocated clone of this angle
    virtual Angle* clone() const override;

    /// @brief Equal to operator.
    ///
    /// @code
    ///     Angle::Degrees(90.0) == Angle::Degrees(90.0); // True
    /// @endcode
    ///
    /// @param [in] anAngle An angle to compare with
    /// @return True if angles are equal
    bool operator==(const Angle& anAngle) const;

    /// @brief Not equal to operator.
    ///
    /// @code
    ///     Angle::Degrees(90.0) != Angle::Degrees(180.0); // True
    /// @endcode
    ///
    /// @param [in] anAngle An angle to compare with
    /// @return True if angles are not equal
    bool operator!=(const Angle& anAngle) const;

    /// @brief Addition operator.
    ///
    /// @code
    ///     Angle::Degrees(90.0) + Angle::Degrees(90.0); // 180.0 [deg]
    /// @endcode
    ///
    /// @param [in] anAngle An angle to add
    /// @return The sum of the two angles
    Angle operator+(const Angle& anAngle) const;

    /// @brief Subtraction operator.
    ///
    /// @code
    ///     Angle::Degrees(180.0) - Angle::Degrees(90.0); // 90.0 [deg]
    /// @endcode
    ///
    /// @param [in] anAngle An angle to subtract
    /// @return The difference of the two angles
    Angle operator-(const Angle& anAngle) const;

    /// @brief Multiplication by scalar operator.
    ///
    /// @code
    ///     Angle::Degrees(90.0) * 2.0; // 180.0 [deg]
    /// @endcode
    ///
    /// @param [in] aReal A scalar multiplier
    /// @return The scaled angle
    Angle operator*(const Real& aReal) const;

    /// @brief Division by scalar operator.
    ///
    /// @code
    ///     Angle::Degrees(180.0) / 2.0; // 90.0 [deg]
    /// @endcode
    ///
    /// @param [in] aReal A scalar divisor
    /// @return The scaled angle
    Angle operator/(const Real& aReal) const;

    /// @brief Addition assignment operator.
    ///
    /// @code
    ///     Angle angle = Angle::Degrees(90.0);
    ///     angle += Angle::Degrees(90.0); // 180.0 [deg]
    /// @endcode
    ///
    /// @param [in] anAngle An angle to add
    /// @return A reference to this angle after addition
    Angle& operator+=(const Angle& anAngle);

    /// @brief Subtraction assignment operator.
    ///
    /// @code
    ///     Angle angle = Angle::Degrees(180.0);
    ///     angle -= Angle::Degrees(90.0); // 90.0 [deg]
    /// @endcode
    ///
    /// @param [in] anAngle An angle to subtract
    /// @return A reference to this angle after subtraction
    Angle& operator-=(const Angle& anAngle);

    /// @brief Multiplication assignment operator.
    ///
    /// @code
    ///     Angle angle = Angle::Degrees(90.0);
    ///     angle *= 2.0; // 180.0 [deg]
    /// @endcode
    ///
    /// @param [in] aReal A scalar multiplier
    /// @return A reference to this angle after multiplication
    Angle& operator*=(const Real& aReal);

    /// @brief Division assignment operator.
    ///
    /// @code
    ///     Angle angle = Angle::Degrees(180.0);
    ///     angle /= 2.0; // 90.0 [deg]
    /// @endcode
    ///
    /// @param [in] aReal A scalar divisor
    /// @return A reference to this angle after division
    Angle& operator/=(const Real& aReal);

    /// @brief Scalar multiplication operator (scalar * angle).
    ///
    /// @code
    ///     2.0 * Angle::Degrees(90.0); // 180.0 [deg]
    /// @endcode
    ///
    /// @param [in] aReal A scalar multiplier
    /// @param [in] anAngle An angle
    /// @return The scaled angle
    friend Angle operator*(const Real& aReal, const Angle& anAngle);

    /// @brief Unary plus operator.
    ///
    /// @code
    ///     +Angle::Degrees(90.0); // 90.0 [deg]
    /// @endcode
    ///
    /// @return A copy of this angle
    Angle operator+() const;

    /// @brief Unary minus operator.
    ///
    /// @code
    ///     -Angle::Degrees(90.0); // -90.0 [deg]
    /// @endcode
    ///
    /// @return The negated angle
    Angle operator-() const;

    /// @brief Conversion operator to mathematics geometry angle.
    ///
    /// @code
    ///     ostk::mathematics::geometry::Angle mathAngle = Angle::Degrees(90.0);
    /// @endcode
    ///
    /// @return A mathematics geometry angle
    operator ostk::mathematics::geometry::Angle() const;

    /// @brief Output stream operator.
    ///
    /// @code
    ///     std::cout << Angle::Degrees(90.0);
    /// @endcode
    ///
    /// @param [in] anOutputStream An output stream
    /// @param [in] anAngle An angle
    /// @return A reference to the output stream
    friend std::ostream& operator<<(std::ostream& anOutputStream, const Angle& anAngle);

    /// @brief Check if the angle is defined.
    ///
    /// @code
    ///     Angle::Degrees(90.0).isDefined(); // True
    /// @endcode
    ///
    /// @return True if defined
    virtual bool isDefined() const override;

    /// @brief Check if the angle value is zero.
    ///
    /// @code
    ///     Angle::Degrees(0.0).isZero(); // True
    /// @endcode
    ///
    /// @return True if zero
    bool isZero() const;

    /// @brief Get the angle unit.
    ///
    /// @code
    ///     Angle::Degrees(90.0).getUnit(); // Angle::Unit::Degree
    /// @endcode
    ///
    /// @return The angle unit
    Angle::Unit getUnit() const;

    /// @brief Get the value in the specified unit.
    ///
    /// @code
    ///     Angle::Degrees(90.0).in(Angle::Unit::Radian);
    /// @endcode
    ///
    /// @param [in] aUnit An angle unit
    /// @return The value in the specified unit
    Real in(const Angle::Unit& aUnit) const;

    /// @brief Get the value in radians.
    ///
    /// @code
    ///     Angle::Degrees(180.0).inRadians();
    /// @endcode
    ///
    /// @return The value in radians
    Real inRadians() const;

    /// @brief Get the value in radians within the specified range.
    ///
    /// @code
    ///     Angle::Degrees(270.0).inRadians(0.0, Real::TwoPi());
    /// @endcode
    ///
    /// @param [in] aLowerBound A lower bound (in radians)
    /// @param [in] anUpperBound An upper bound (in radians)
    /// @return The value in radians within the range
    Real inRadians(const Real& aLowerBound, const Real& anUpperBound) const;

    /// @brief Get the value in degrees.
    ///
    /// @code
    ///     Angle::Radians(Real::Pi()).inDegrees(); // 180.0
    /// @endcode
    ///
    /// @return The value in degrees
    Real inDegrees() const;

    /// @brief Get the value in degrees within the specified range.
    ///
    /// @code
    ///     Angle::Degrees(400.0).inDegrees(0.0, 360.0); // 40.0
    /// @endcode
    ///
    /// @param [in] aLowerBound A lower bound (in degrees)
    /// @param [in] anUpperBound An upper bound (in degrees)
    /// @return The value in degrees within the range
    Real inDegrees(const Real& aLowerBound, const Real& anUpperBound) const;

    /// @brief Get the value in arcminutes.
    ///
    /// @code
    ///     Angle::Degrees(1.0).inArcminutes(); // 60.0
    /// @endcode
    ///
    /// @return The value in arcminutes
    Real inArcminutes() const;

    /// @brief Get the value in arcminutes within the specified range.
    ///
    /// @code
    ///     Angle::Arcminutes(100.0).inArcminutes(0.0, 60.0);
    /// @endcode
    ///
    /// @param [in] aLowerBound A lower bound (in arcminutes)
    /// @param [in] anUpperBound An upper bound (in arcminutes)
    /// @return The value in arcminutes within the range
    Real inArcminutes(const Real& aLowerBound, const Real& anUpperBound) const;

    /// @brief Get the value in arcseconds.
    ///
    /// @code
    ///     Angle::Degrees(1.0).inArcseconds(); // 3600.0
    /// @endcode
    ///
    /// @return The value in arcseconds
    Real inArcseconds() const;

    /// @brief Get the value in arcseconds within the specified range.
    ///
    /// @code
    ///     Angle::Arcseconds(5000.0).inArcseconds(0.0, 3600.0);
    /// @endcode
    ///
    /// @param [in] aLowerBound A lower bound (in arcseconds)
    /// @param [in] anUpperBound An upper bound (in arcseconds)
    /// @return The value in arcseconds within the range
    Real inArcseconds(const Real& aLowerBound, const Real& anUpperBound) const;

    /// @brief Get the value in revolutions.
    ///
    /// @code
    ///     Angle::Degrees(360.0).inRevolutions(); // 1.0
    /// @endcode
    ///
    /// @return The value in revolutions
    Real inRevolutions() const;

    /// @brief Convert to string representation.
    ///
    /// @code
    ///     Angle::Degrees(90.0).toString();
    /// @endcode
    ///
    /// @param [in] aPrecision A precision (number of decimal places)
    /// @return A string representation
    virtual String toString(const Integer& aPrecision = Integer::Undefined()) const override;

    /// @brief Construct an undefined angle.
    ///
    /// @code
    ///     Angle angle = Angle::Undefined();
    /// @endcode
    ///
    /// @return An undefined angle
    static Angle Undefined();

    /// @brief Construct a zero angle.
    ///
    /// @code
    ///     Angle angle = Angle::Zero();
    /// @endcode
    ///
    /// @return A zero angle
    static Angle Zero();

    /// @brief Construct an angle of pi/2 radians (90 degrees).
    ///
    /// @code
    ///     Angle angle = Angle::HalfPi();
    /// @endcode
    ///
    /// @return A half-pi angle
    static Angle HalfPi();

    /// @brief Construct an angle of pi radians (180 degrees).
    ///
    /// @code
    ///     Angle angle = Angle::Pi();
    /// @endcode
    ///
    /// @return A pi angle
    static Angle Pi();

    /// @brief Construct an angle of 2*pi radians (360 degrees).
    ///
    /// @code
    ///     Angle angle = Angle::TwoPi();
    /// @endcode
    ///
    /// @return A two-pi angle
    static Angle TwoPi();

    /// @brief Construct an angle from a value in radians.
    ///
    /// @code
    ///     Angle angle = Angle::Radians(3.14159);
    /// @endcode
    ///
    /// @param [in] aValue A value in radians
    /// @return An angle
    static Angle Radians(const Real& aValue);

    /// @brief Construct an angle from a value in degrees.
    ///
    /// @code
    ///     Angle angle = Angle::Degrees(90.0);
    /// @endcode
    ///
    /// @param [in] aValue A value in degrees
    /// @return An angle
    static Angle Degrees(const Real& aValue);

    /// @brief Construct an angle from a value in arcminutes.
    ///
    /// @code
    ///     Angle angle = Angle::Arcminutes(60.0);
    /// @endcode
    ///
    /// @param [in] aValue A value in arcminutes
    /// @return An angle
    static Angle Arcminutes(const Real& aValue);

    /// @brief Construct an angle from a value in arcseconds.
    ///
    /// @code
    ///     Angle angle = Angle::Arcseconds(3600.0);
    /// @endcode
    ///
    /// @param [in] aValue A value in arcseconds
    /// @return An angle
    static Angle Arcseconds(const Real& aValue);

    /// @brief Construct an angle from a value in revolutions.
    ///
    /// @code
    ///     Angle angle = Angle::Revolutions(1.0);
    /// @endcode
    ///
    /// @param [in] aValue A value in revolutions
    /// @return An angle
    static Angle Revolutions(const Real& aValue);

    /// @brief Compute the shortest signed angle from the first angle to the second.
    /// Positive if the shortest path from `aFirstAngle` to `aSecondAngle` is clockwise, otherwise negative.
    /// The result is in the range (-180, +180] degrees and is returned in the unit of the first angle.
    ///
    /// @code
    ///     Angle angle = Angle::Between(Angle::Degrees(0.0), Angle::Degrees(90.0));
    /// @endcode
    ///
    /// @param [in] aFirstAngle A first angle
    /// @param [in] aSecondAngle A second angle
    /// @return The shortest signed angle from the first angle to the second
    static Angle Between(const Angle& aFirstAngle, const Angle& aSecondAngle);

    /// @brief Compute the angle between two 2D vectors.
    ///
    /// @code
    ///     Angle angle = Angle::Between(Vector2d(1.0, 0.0), Vector2d(0.0, 1.0));
    /// @endcode
    ///
    /// @param [in] aFirstVector A first 2D vector
    /// @param [in] aSecondVector A second 2D vector
    /// @return The angle between the two vectors
    static Angle Between(const Vector2d& aFirstVector, const Vector2d& aSecondVector);

    /// @brief Compute the angle between two 3D vectors.
    ///
    /// @code
    ///     Angle angle = Angle::Between(Vector3d(1.0, 0.0, 0.0), Vector3d(0.0, 1.0, 0.0));
    /// @endcode
    ///
    /// @param [in] aFirstVector A first 3D vector
    /// @param [in] aSecondVector A second 3D vector
    /// @return The angle between the two vectors
    static Angle Between(const Vector3d& aFirstVector, const Vector3d& aSecondVector);

    /// @brief Parse an angle from a string.
    ///
    /// @code
    ///     Angle angle = Angle::Parse("90.0 [deg]");
    /// @endcode
    ///
    /// @param [in] aString A string to parse
    /// @return An angle
    static Angle Parse(const String& aString);

    /// @brief Get the string representation of an angle unit.
    ///
    /// @code
    ///     Angle::StringFromUnit(Angle::Unit::Degree); // "Degree"
    /// @endcode
    ///
    /// @param [in] aUnit An angle unit
    /// @return The string representation
    static String StringFromUnit(const Angle::Unit& aUnit);

    /// @brief Get the symbol of an angle unit.
    ///
    /// @code
    ///     Angle::SymbolFromUnit(Angle::Unit::Degree); // "deg"
    /// @endcode
    ///
    /// @param [in] aUnit An angle unit
    /// @return The unit symbol
    static String SymbolFromUnit(const Angle::Unit& aUnit);

    /// @brief Get the angle unit from a symbol string.
    ///
    /// @code
    ///     Angle::UnitFromSymbol("deg"); // Angle::Unit::Degree
    /// @endcode
    ///
    /// @param [in] aSymbol A unit symbol
    /// @return The angle unit
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
