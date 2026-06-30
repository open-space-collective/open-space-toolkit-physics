/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Unit_Derived__
#define __OpenSpaceToolkit_Physics_Unit_Derived__

#include <OpenSpaceToolkit/Core/Type/Integer.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include <OpenSpaceToolkit/Physics/Unit/Derived/Angle.hpp>
#include <OpenSpaceToolkit/Physics/Unit/ElectricCurrent.hpp>
#include <OpenSpaceToolkit/Physics/Unit/Length.hpp>
#include <OpenSpaceToolkit/Physics/Unit/Mass.hpp>
#include <OpenSpaceToolkit/Physics/Unit/Time.hpp>
#include <OpenSpaceToolkit/Physics/Unit/Unit.hpp>

namespace ostk
{
namespace physics
{
namespace unit
{

using ostk::core::type::Int16;
using ostk::core::type::Integer;
using ostk::core::type::Real;
using ostk::core::type::String;

/// @brief Derived unit
///
/// @ref https://en.wikipedia.org/wiki/SI_derived_unit

class Derived : public Unit
{
   public:
    /// @brief SI unit order

    class Order
    {
       public:
        /// @brief Constructor from integer order.
        ///
        /// @code
        ///     Derived::Order order(1);
        /// @endcode
        ///
        /// @param [in] aNumerator A numerator value (denominator defaults to 1)

        Order(Int16 aNumerator);

        /// @brief Constructor from fractional order.
        ///
        /// @code
        ///     Derived::Order order(1, 2);
        /// @endcode
        ///
        /// @param [in] aNumerator A numerator value
        /// @param [in] aDenominator A denominator value

        Order(Int16 aNumerator, Int16 aDenominator);

        /// @brief Equal to operator.
        ///
        /// @code
        ///     Derived::Order(1) == Derived::Order(1); // True
        /// @endcode
        ///
        /// @param [in] anOrder An order to compare with
        /// @return True if orders are equal

        bool operator==(const Order& anOrder) const;

        /// @brief Not equal to operator.
        ///
        /// @code
        ///     Derived::Order(1) != Derived::Order(2); // True
        /// @endcode
        ///
        /// @param [in] anOrder An order to compare with
        /// @return True if orders are not equal

        bool operator!=(const Order& anOrder) const;

        /// @brief Check if the order is zero.
        ///
        /// @code
        ///     Derived::Order(0).isZero(); // True
        /// @endcode
        ///
        /// @return True if zero

        bool isZero() const;

        /// @brief Check if the order is unity (1).
        ///
        /// @code
        ///     Derived::Order(1).isUnity(); // True
        /// @endcode
        ///
        /// @return True if unity

        bool isUnity() const;

        /// @brief Get the numerator.
        ///
        /// @code
        ///     Derived::Order(1, 2).getNumerator(); // 1
        /// @endcode
        ///
        /// @return The numerator

        Int16 getNumerator() const;

        /// @brief Get the denominator.
        ///
        /// @code
        ///     Derived::Order(1, 2).getDenominator(); // 2
        /// @endcode
        ///
        /// @return The denominator

        Int16 getDenominator() const;

        /// @brief Get the value as a real number (numerator / denominator).
        ///
        /// @code
        ///     Derived::Order(1, 2).getValue(); // 0.5
        /// @endcode
        ///
        /// @return The value

        Real getValue() const;

        /// @brief Convert to string representation.
        ///
        /// @code
        ///     Derived::Order(1, 2).toString();
        /// @endcode
        ///
        /// @return A string representation

        String toString() const;

        /// @brief Construct a zero order.
        ///
        /// @code
        ///     Derived::Order order = Derived::Order::Zero();
        /// @endcode
        ///
        /// @return A zero order

        static Order Zero();

        /// @brief Construct a first order (1).
        ///
        /// @code
        ///     Derived::Order order = Derived::Order::One();
        /// @endcode
        ///
        /// @return A first order

        static Order One();

        /// @brief Construct a second order (2).
        ///
        /// @code
        ///     Derived::Order order = Derived::Order::Two();
        /// @endcode
        ///
        /// @return A second order

        static Order Two();

       private:
        Int16 numerator_;
        Int16 denominator_;
    };

    /// @brief Unit

    class Unit
    {
       public:
        /// @brief Constructor.
        ///
        /// @code
        ///     Derived::Unit unit = Derived::Unit::MeterPerSecond();
        /// @endcode
        ///
        /// @param [in] aLengthUnit A length unit
        /// @param [in] aLengthOrder The order of the length unit
        /// @param [in] aMassUnit A mass unit
        /// @param [in] aMassOrder The order of the mass unit
        /// @param [in] aTimeUnit A time unit
        /// @param [in] aTimeOrder The order of the time unit
        /// @param [in] anElectricCurrentUnit An electric current unit
        /// @param [in] anElectricCurrentOrder The order of the electric current unit
        /// @param [in] anAngleUnit An angle unit
        /// @param [in] anAngleOrder The order of the angle unit

        Unit(
            const Length::Unit& aLengthUnit,
            const Order& aLengthOrder,
            const Mass::Unit& aMassUnit,
            const Order& aMassOrder,
            const Time::Unit& aTimeUnit,
            const Order& aTimeOrder,
            const ElectricCurrent::Unit& anElectricCurrentUnit,
            const Order& anElectricCurrentOrder,
            const Angle::Unit& anAngleUnit,
            const Order& anAngleOrder
        );

        /// @brief Equal to operator.
        ///
        /// @code
        ///     Derived::Unit::MeterPerSecond() == Derived::Unit::MeterPerSecond(); // True
        /// @endcode
        ///
        /// @param [in] aUnit A derived unit to compare with
        /// @return True if units are equal

        bool operator==(const Unit& aUnit) const;

        /// @brief Not equal to operator.
        ///
        /// @code
        ///     Derived::Unit::MeterPerSecond() != Derived::Unit::Newton(); // True
        /// @endcode
        ///
        /// @param [in] aUnit A derived unit to compare with
        /// @return True if units are not equal

        bool operator!=(const Unit& aUnit) const;

        /// @brief Check if the unit is defined.
        ///
        /// @code
        ///     Derived::Unit::MeterPerSecond().isDefined(); // True
        /// @endcode
        ///
        /// @return True if defined

        bool isDefined() const;

        /// @brief Check if this unit is compatible with another unit (same dimension orders).
        ///
        /// @code
        ///     Derived::Unit::MeterPerSecond().isCompatibleWith(Derived::Unit::MeterPerSecond()); // True
        /// @endcode
        ///
        /// @param [in] aUnit A derived unit
        /// @return True if compatible

        bool isCompatibleWith(const Unit& aUnit) const;

        /// @brief Access the length unit.
        ///
        /// @code
        ///     Derived::Unit::MeterPerSecond().accessLengthUnit(); // Length::Unit::Meter
        /// @endcode
        ///
        /// @return A const reference to the length unit

        const Length::Unit& accessLengthUnit() const;

        /// @brief Access the length order.
        ///
        /// @code
        ///     Derived::Unit::MeterPerSecond().accessLengthOrder();
        /// @endcode
        ///
        /// @return A const reference to the length order

        const Order& accessLengthOrder() const;

        /// @brief Access the mass unit.
        ///
        /// @code
        ///     Derived::Unit::Newton().accessMassUnit(); // Mass::Unit::Kilogram
        /// @endcode
        ///
        /// @return A const reference to the mass unit

        const Mass::Unit& accessMassUnit() const;

        /// @brief Access the mass order.
        ///
        /// @code
        ///     Derived::Unit::Newton().accessMassOrder();
        /// @endcode
        ///
        /// @return A const reference to the mass order

        const Derived::Order& accessMassOrder() const;

        /// @brief Access the time unit.
        ///
        /// @code
        ///     Derived::Unit::MeterPerSecond().accessTimeUnit(); // Time::Unit::Second
        /// @endcode
        ///
        /// @return A const reference to the time unit

        const Time::Unit& accessTimeUnit() const;

        /// @brief Access the time order.
        ///
        /// @code
        ///     Derived::Unit::MeterPerSecond().accessTimeOrder();
        /// @endcode
        ///
        /// @return A const reference to the time order

        const Derived::Order& accessTimeOrder() const;

        /// @brief Access the electric current unit.
        ///
        /// @code
        ///     Derived::Unit::Tesla().accessElectricCurrentUnit();
        /// @endcode
        ///
        /// @return A const reference to the electric current unit

        const ElectricCurrent::Unit& accessElectricCurrentUnit() const;

        /// @brief Access the electric current order.
        ///
        /// @code
        ///     Derived::Unit::Tesla().accessElectricCurrentOrder();
        /// @endcode
        ///
        /// @return A const reference to the electric current order

        const Derived::Order& accessElectricCurrentOrder() const;

        /// @brief Access the angle unit.
        ///
        /// @code
        ///     Derived::Unit::RadianPerSecond().accessAngleUnit(); // Angle::Unit::Radian
        /// @endcode
        ///
        /// @return A const reference to the angle unit

        const Angle::Unit& accessAngleUnit() const;

        /// @brief Access the angle order.
        ///
        /// @code
        ///     Derived::Unit::RadianPerSecond().accessAngleOrder();
        /// @endcode
        ///
        /// @return A const reference to the angle order

        const Derived::Order& accessAngleOrder() const;

        /// @brief Convert to string representation.
        ///
        /// @code
        ///     Derived::Unit::MeterPerSecond().toString();
        /// @endcode
        ///
        /// @return A string representation

        String toString() const;

        /// @brief Get the unit symbol.
        ///
        /// @code
        ///     Derived::Unit::MeterPerSecond().getSymbol();
        /// @endcode
        ///
        /// @return The unit symbol

        String getSymbol() const;

        // Static constructors for specifying actual named units

        /// @brief Construct a square meter unit (m^2).
        ///
        /// @code
        ///     Derived::Unit unit = Derived::Unit::SquareMeter();
        /// @endcode
        ///
        /// @return A square meter unit

        static Unit SquareMeter();

        /// @brief Construct a cubic meter unit (m^3).
        ///
        /// @code
        ///     Derived::Unit unit = Derived::Unit::CubicMeter();
        /// @endcode
        ///
        /// @return A cubic meter unit

        static Unit CubicMeter();

        /// @brief Construct a hertz unit (s^-1).
        ///
        /// @code
        ///     Derived::Unit unit = Derived::Unit::Hertz();
        /// @endcode
        ///
        /// @return A hertz unit

        static Unit Hertz();

        /// @brief Construct a watt unit (kg.m^2.s^-3).
        ///
        /// @code
        ///     Derived::Unit unit = Derived::Unit::Watt();
        /// @endcode
        ///
        /// @return A watt unit

        static Unit Watt();

        /// @brief Construct a tesla unit (kg.s^-2.A^-1).
        ///
        /// @code
        ///     Derived::Unit unit = Derived::Unit::Tesla();
        /// @endcode
        ///
        /// @return A tesla unit

        static Unit Tesla();

        /// @brief Construct a newton unit (kg.m.s^-2).
        ///
        /// @code
        ///     Derived::Unit unit = Derived::Unit::Newton();
        /// @endcode
        ///
        /// @return A newton unit

        static Unit Newton();

        /// @brief Construct a kilogram per second unit (kg.s^-1).
        ///
        /// @code
        ///     Derived::Unit unit = Derived::Unit::KilogramPerSecond();
        /// @endcode
        ///
        /// @return A kilogram per second unit

        static Unit KilogramPerSecond();

        /// @brief Construct a meter per second unit (m.s^-1).
        ///
        /// @code
        ///     Derived::Unit unit = Derived::Unit::MeterPerSecond();
        /// @endcode
        ///
        /// @return A meter per second unit

        static Unit MeterPerSecond();

        /// @brief Construct a meter per second squared unit (m.s^-2).
        ///
        /// @code
        ///     Derived::Unit unit = Derived::Unit::MeterPerSecondSquared();
        /// @endcode
        ///
        /// @return A meter per second squared unit

        static Unit MeterPerSecondSquared();

        /// @brief Construct a meter cubed per second squared unit (m^3.s^-2).
        ///
        /// @code
        ///     Derived::Unit unit = Derived::Unit::MeterCubedPerSecondSquared();
        /// @endcode
        ///
        /// @return A meter cubed per second squared unit

        static Unit MeterCubedPerSecondSquared();

        /// @brief Construct a radian per second unit (rad.s^-1).
        ///
        /// @code
        ///     Derived::Unit unit = Derived::Unit::RadianPerSecond();
        /// @endcode
        ///
        /// @return A radian per second unit

        static Unit RadianPerSecond();

        /// @brief Construct a revolution per day unit (rev.day^-1).
        ///
        /// @code
        ///     Derived::Unit unit = Derived::Unit::RevolutionPerDay();
        /// @endcode
        ///
        /// @return A revolution per day unit

        static Unit RevolutionPerDay();

        // Static constructors for specifying derived (non-base) quantities

        /// @brief Construct a velocity unit.
        ///
        /// @code
        ///     Derived::Unit unit = Derived::Unit::Velocity(Length::Unit::Meter, Time::Unit::Second);
        /// @endcode
        ///
        /// @param [in] aLengthUnit A length unit
        /// @param [in] aTimeUnit A time unit
        /// @return A velocity unit

        static Unit Velocity(const Length::Unit& aLengthUnit, const Time::Unit& aTimeUnit);

        /// @brief Construct an acceleration unit.
        ///
        /// @code
        ///     Derived::Unit unit = Derived::Unit::Acceleration(Length::Unit::Meter, Time::Unit::Second);
        /// @endcode
        ///
        /// @param [in] aLengthUnit A length unit
        /// @param [in] aTimeUnit A time unit
        /// @return An acceleration unit

        static Unit Acceleration(const Length::Unit& aLengthUnit, const Time::Unit& aTimeUnit);

        /// @brief Construct an angular velocity unit.
        ///
        /// @code
        ///     Derived::Unit unit = Derived::Unit::AngularVelocity(Angle::Unit::Radian, Time::Unit::Second);
        /// @endcode
        ///
        /// @param [in] anAngleUnit An angle unit
        /// @param [in] aTimeUnit A time unit
        /// @return An angular velocity unit

        static Unit AngularVelocity(const Angle::Unit& anAngleUnit, const Time::Unit& aTimeUnit);

        /// @brief Construct a gravitational parameter unit (length^3 / time^2).
        ///
        /// @code
        ///     Derived::Unit unit = Derived::Unit::GravitationalParameter(Length::Unit::Meter, Time::Unit::Second);
        /// @endcode
        ///
        /// @param [in] aLengthUnit A length unit
        /// @param [in] aTimeUnit A time unit
        /// @return A gravitational parameter unit

        static Unit GravitationalParameter(const Length::Unit& aLengthUnit, const Time::Unit& aTimeUnit);

        /// @brief Construct a force unit (mass * length / time^2).
        ///
        /// @code
        ///     Derived::Unit unit = Derived::Unit::Force(Mass::Unit::Kilogram, Length::Unit::Meter, Time::Unit::Second)
        ///    ;
        /// @endcode
        ///
        /// @param [in] aMassUnit A mass unit
        /// @param [in] aLengthUnit A length unit
        /// @param [in] aTimeUnit A time unit
        /// @return A force unit

        static Unit Force(const Mass::Unit& aMassUnit, const Length::Unit& aLengthUnit, const Time::Unit& aTimeUnit);

        /// @brief Construct a mass flow rate unit (mass / time).
        ///
        /// @code
        ///     Derived::Unit unit = Derived::Unit::MassFlowRate(Mass::Unit::Kilogram, Time::Unit::Second);
        /// @endcode
        ///
        /// @param [in] aMassUnit A mass unit
        /// @param [in] aTimeUnit A time unit
        /// @return A mass flow rate unit

        static Unit MassFlowRate(const Mass::Unit& aMassUnit, const Time::Unit& aTimeUnit);

        /// @brief Construct a mass density unit (mass / length^3).
        ///
        /// @code
        ///     Derived::Unit unit = Derived::Unit::MassDensity(Mass::Unit::Kilogram, Length::Unit::Meter);
        /// @endcode
        ///
        /// @param [in] aMassUnit A mass unit
        /// @param [in] aLengthUnit A length unit
        /// @return A mass density unit

        static Unit MassDensity(const Mass::Unit& aMassUnit, const Length::Unit& aLengthUnit);

        /// @brief Construct an undefined derived unit.
        ///
        /// @code
        ///     Derived::Unit unit = Derived::Unit::Undefined();
        /// @endcode
        ///
        /// @return An undefined derived unit

        static Unit Undefined();

        // static Unit Parse(const String& aString);

       private:
        // S.I.

        Length::Unit lengthUnit_;
        Order lengthOrder_;

        Mass::Unit massUnit_;
        Order massOrder_;

        Time::Unit timeUnit_;
        Order timeOrder_;

        // Temperature::Unit temperatureUnit_;
        // Order           temperatureOrder_;

        ElectricCurrent::Unit electricCurrentUnit_;
        Order electricCurrentOrder_;

        // LuminousIntensity::Unit luminousIntensityUnit_;
        // Order           luminousIntensityOrder_;

        // Derived

        Angle::Unit angleUnit_;
        Order angleOrder_;
    };

    /// @brief Constructor.
    ///
    /// @code
    ///     Derived derived(1.0, Derived::Unit::MeterPerSecond());
    /// @endcode
    ///
    /// @param [in] aValue A value
    /// @param [in] aUnit A derived unit

    Derived(const Real& aValue, const Derived::Unit& aUnit);

    /// @brief Clone the derived unit.
    ///
    /// @code
    ///     Derived derived(1.0, Derived::Unit::MeterPerSecond());
    ///     Derived* clonePtr = derived.clone();
    /// @endcode
    ///
    /// @return A pointer to a dynamically allocated clone of this derived unit

    virtual Derived* clone() const override;

    /// @brief Equal to operator.
    ///
    /// @code
    ///     Derived(1.0, Derived::Unit::MeterPerSecond()) == Derived(1.0, Derived::Unit::MeterPerSecond()); // True
    /// @endcode
    ///
    /// @param [in] aDerivedUnit A derived unit to compare with
    /// @return True if derived units are equal

    bool operator==(const Derived& aDerivedUnit) const;

    /// @brief Not equal to operator.
    ///
    /// @code
    ///     Derived(1.0, Derived::Unit::MeterPerSecond()) != Derived(2.0, Derived::Unit::MeterPerSecond()); // True
    /// @endcode
    ///
    /// @param [in] aDerivedUnit A derived unit to compare with
    /// @return True if derived units are not equal

    bool operator!=(const Derived& aDerivedUnit) const;

    /// @brief Output stream operator.
    ///
    /// @code
    ///     std::cout << Derived(1.0, Derived::Unit::MeterPerSecond());
    /// @endcode
    ///
    /// @param [in] anOutputStream An output stream
    /// @param [in] aDerivedUnit A derived unit
    /// @return A reference to the output stream

    friend std::ostream& operator<<(std::ostream& anOutputStream, const Derived& aDerivedUnit);

    /// @brief Check if the derived unit is defined.
    ///
    /// @code
    ///     Derived(1.0, Derived::Unit::MeterPerSecond()).isDefined(); // True
    /// @endcode
    ///
    /// @return True if defined

    virtual bool isDefined() const override;

    /// @brief Get the derived unit.
    ///
    /// @code
    ///     Derived(1.0, Derived::Unit::MeterPerSecond()).getUnit();
    /// @endcode
    ///
    /// @return The derived unit

    Derived::Unit getUnit() const;

    /// @brief Get the value in the specified unit.
    ///
    /// @code
    ///     Derived(1.0, Derived::Unit::MeterPerSecond()).in(Derived::Unit::MeterPerSecond()); // 1.0
    /// @endcode
    ///
    /// @param [in] aUnit A derived unit
    /// @return The value in the specified unit

    Real in(const Derived::Unit& aUnit) const;

    /// @brief Convert to string representation.
    ///
    /// @code
    ///     Derived(1.0, Derived::Unit::MeterPerSecond()).toString();
    /// @endcode
    ///
    /// @param [in] aPrecision A precision (number of decimal places)
    /// @return A string representation

    virtual String toString(const Integer& aPrecision = Integer::Undefined()) const override;

    /// @brief Construct an undefined derived unit.
    ///
    /// @code
    ///     Derived derived = Derived::Undefined();
    /// @endcode
    ///
    /// @return An undefined derived unit

    static Derived Undefined();

    /// @brief Parse a derived unit from a string.
    ///
    /// @code
    ///     Derived derived = Derived::Parse("1.0 [m/s]");
    /// @endcode
    ///
    /// @param [in] aString A string to parse
    /// @return A derived unit

    static Derived Parse(const String& aString);

    /// @brief Get the string representation of a derived unit.
    ///
    /// @code
    ///     Derived::StringFromUnit(Derived::Unit::MeterPerSecond());
    /// @endcode
    ///
    /// @param [in] aUnit A derived unit
    /// @return The string representation

    static String StringFromUnit(const Derived::Unit& aUnit);

    /// @brief Get the symbol of a derived unit.
    ///
    /// @code
    ///     Derived::SymbolFromUnit(Derived::Unit::MeterPerSecond());
    /// @endcode
    ///
    /// @param [in] aUnit A derived unit
    /// @return The unit symbol

    static String SymbolFromUnit(const Derived::Unit& aUnit);

   private:
    Derived::Unit unit_;

    static Real SIRatio(const Derived::Unit& aUnit);
};

}  // namespace unit
}  // namespace physics
}  // namespace ostk

#endif
