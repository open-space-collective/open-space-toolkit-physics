/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Container/Map.hpp>
#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Physics/Unit.hpp>

namespace ostk
{
namespace physics
{

Unit::Unit(const Unit& aUnit)
    : type_(aUnit.type_),
      unitUPtr_((aUnit.unitUPtr_ != nullptr) ? aUnit.unitUPtr_->clone() : nullptr)
{
}

Unit& Unit::operator=(const Unit& aUnit)
{
    if (this != &aUnit)
    {
        type_ = aUnit.type_;
        unitUPtr_.reset((aUnit.unitUPtr_ != nullptr) ? aUnit.unitUPtr_->clone() : nullptr);
    }

    return *this;
}

bool Unit::operator==(const Unit& aUnit) const
{
    if ((!this->isDefined()) || (!aUnit.isDefined()))
    {
        return false;
    }

    if (type_ == aUnit.type_)
    {
        switch (type_)
        {
            case Unit::Type::None:
                return true;

            case Unit::Type::Length:
                return static_cast<const units::Length&>(*unitUPtr_.get()) ==
                       static_cast<const units::Length&>(*aUnit.unitUPtr_.get());

            case Unit::Type::Mass:
                return static_cast<const units::Mass&>(*unitUPtr_.get()) ==
                       static_cast<const units::Mass&>(*aUnit.unitUPtr_.get());

            case Unit::Type::Time:
                return static_cast<const units::Time&>(*unitUPtr_.get()) ==
                       static_cast<const units::Time&>(*aUnit.unitUPtr_.get());

            case Unit::Type::Temperature:
            case Unit::Type::ElectricCurrent:
            case Unit::Type::LuminousIntensity:
                throw ostk::core::error::runtime::ToBeImplemented(Unit::StringFromType(type_));

            case Unit::Type::Derived:
                return static_cast<const units::Derived&>(*unitUPtr_.get()) ==
                       static_cast<const units::Derived&>(*aUnit.unitUPtr_.get());

            default:
                throw ostk::core::error::runtime::Wrong("Type");
                break;
        }
    }

    return false;
}

bool Unit::operator!=(const Unit& aUnit) const
{
    return !((*this) == aUnit);
}

std::ostream& operator<<(std::ostream& anOutputStream, const Unit& aUnit)
{
    ostk::core::utils::Print::Header(anOutputStream, "Unit");

    ostk::core::utils::Print::Line(anOutputStream) << "Type:" << Unit::StringFromType(aUnit.type_);
    ostk::core::utils::Print::Line(anOutputStream)
        << "Value:"
        << (((aUnit.unitUPtr_ != nullptr) && aUnit.unitUPtr_->isDefined()) ? aUnit.unitUPtr_->toString() : "Undefined");

    ostk::core::utils::Print::Footer(anOutputStream);

    return anOutputStream;
}

bool Unit::isDefined() const
{
    return type_ != Unit::Type::Undefined;
}

bool Unit::isNone() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Unit");
    }

    return type_ == Unit::Type::None;
}

Unit::Type Unit::getType() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Unit");
    }

    return type_;
}

Real Unit::ratioTo(const Unit& aUnit) const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Unit");
    }

    if (!aUnit.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Unit");
    }

    if (type_ != aUnit.type_)
    {
        throw ostk::core::error::RuntimeError(
            "Types [{}] and [{}] are incompatibles.", Unit::StringFromType(type_), Unit::StringFromType(aUnit.type_)
        );
    }

    switch (type_)
    {
        case Unit::Type::None:
            return 1.0;

        case Unit::Type::Length:
            return static_cast<const units::Length&>(*unitUPtr_.get())
                .in(static_cast<const units::Length&>(*aUnit.unitUPtr_.get()).getUnit());

        case Unit::Type::Mass:
        case Unit::Type::Time:
        case Unit::Type::Temperature:
        case Unit::Type::ElectricCurrent:
        case Unit::Type::LuminousIntensity:
            throw ostk::core::error::runtime::ToBeImplemented(Unit::StringFromType(type_));

        case Unit::Type::Derived:
            return static_cast<const units::Derived&>(*unitUPtr_.get())
                .in(static_cast<const units::Derived&>(*aUnit.unitUPtr_.get()).getUnit());

        default:
            throw ostk::core::error::runtime::Wrong("Type");
            break;
    }

    return Real::Undefined();
}

String Unit::toString() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Unit");
    }

    switch (type_)
    {
        case Unit::Type::None:
            return "-";

        case Unit::Type::Length:
            return units::Length::SymbolFromUnit(static_cast<const units::Length&>(*unitUPtr_.get()).getUnit());

            // case Unit::Type::Mass:
            // return units::Mass::SymbolFromUnit(static_cast<const units::Mass&>(*unitUPtr_.get()).getUnit()) ;

            // case Unit::Type::Time:
            // return units::Time::SymbolFromUnit(static_cast<const units::Time&>(*unitUPtr_.get()).getUnit()) ;

        case Unit::Type::Derived:
            return units::Derived::SymbolFromUnit(static_cast<const units::Derived&>(*unitUPtr_.get()).getUnit());

        case Unit::Type::Mass:
        case Unit::Type::Time:
        case Unit::Type::Temperature:
        case Unit::Type::ElectricCurrent:
        case Unit::Type::LuminousIntensity:
            throw ostk::core::error::runtime::ToBeImplemented(Unit::StringFromType(type_));

        default:
            throw ostk::core::error::runtime::Wrong("Type");
            break;
    }

    return String::Empty();
}

Unit Unit::Undefined()
{
    return {Unit::Type::Undefined, nullptr};
}

Unit Unit::None()
{
    return {Unit::Type::None, nullptr};
}

Unit Unit::Length(const units::Length::Unit& aLengthUnit)
{
    return {Unit::Type::Length, std::make_unique<units::Length>(1.0, aLengthUnit)};
}

Unit Unit::Derived(const units::Derived::Unit& aDerivedUnit)
{
    return {Unit::Type::Derived, std::make_unique<units::Derived>(1.0, aDerivedUnit)};
}

String Unit::StringFromType(const Unit::Type& aType)
{
    using ostk::core::container::Map;

    static const Map<Unit::Type, String> typeStringMap = {
        {Unit::Type::Undefined, "Undefined"},
        {Unit::Type::None, "None"},
        {Unit::Type::Length, "Length"},
        {Unit::Type::Mass, "Mass"},
        {Unit::Type::Time, "Time"},
        {Unit::Type::Temperature, "Temperature"},
        {Unit::Type::ElectricCurrent, "ElectricCurrent"},
        {Unit::Type::LuminousIntensity, "LuminousIntensity"},
        {Unit::Type::Derived, "Derived"}
    };

    return typeStringMap.at(aType);
}

Unit::Unit(const Unit::Type& aType, const Unique<units::Unit>& aUnitUPtr)
    : type_(aType),
      unitUPtr_((aUnitUPtr != nullptr) ? aUnitUPtr->clone() : nullptr)
{
}

}  // namespace physics
}  // namespace ostk
