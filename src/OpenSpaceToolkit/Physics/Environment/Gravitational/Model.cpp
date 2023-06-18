/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Model.hpp>

namespace ostk
{
namespace physics
{
namespace environment
{
namespace gravitational
{

Model::Parameters::Parameters(
    const Derived& aGravitationalParameter,
    const Length& anEquatorialRadius,
    const Real& aFlattening,
    const Real& aC20,
    const Real& aC40
)
    : gravitationalParameter_(aGravitationalParameter),
      equatorialRadius_(anEquatorialRadius),
      flattening_(aFlattening),
      C20_(aC20),
      C40_(aC40),
      J2_(aC20.isDefined() ? -aC20 * std::sqrt(5.0) : Real::Undefined()),
      J4_(aC40.isDefined() ? -aC40 * std::sqrt(9.0) : Real::Undefined())
{
}

Model::Parameters Model::Parameters::Undefined()
{
    return {
        Derived::Undefined(),
        Length::Undefined(),
        Real::Undefined(),
        Real::Undefined(),
        Real::Undefined(),
    };
}

bool Model::Parameters::isDefined() const
{
    return (
        gravitationalParameter_.isDefined() &&
        equatorialRadius_.isDefined() && flattening_.isDefined() &&
        J2_.isDefined() && J4_.isDefined() && C20_.isDefined() && C40_.isDefined()
    );
}

bool Model::Parameters::operator==(const Model::Parameters& aParameterSet) const
{
    if ((!this->isDefined()) || (!aParameterSet.isDefined()))
    {
        return false;
    }

    return (
        (gravitationalParameter_ == aParameterSet.gravitationalParameter_) &&
        (equatorialRadius_ == aParameterSet.equatorialRadius_) && (flattening_ == aParameterSet.flattening_) &&
        (J2_ == aParameterSet.J2_) && J4_ == (aParameterSet.J4_)
    );
}

bool Model::Parameters::operator!=(const Model::Parameters& aParameterSet) const
{
    return !((*this) == aParameterSet);
}

std::ostream& operator<<(std::ostream& anOutputStream, const Model::Parameters& aParameterSet)
{
    ostk::core::utils::Print::Header(anOutputStream, "Gravitational Model Parameters");

    ostk::core::utils::Print::Line(anOutputStream)
        << "Gravitational Parameter:" << (aParameterSet.gravitationalParameter_.isDefined() ? aParameterSet.gravitationalParameter_.toString() : "Undefined");
    ostk::core::utils::Print::Line(anOutputStream)
        << "Equatorial Radius:" << (aParameterSet.equatorialRadius_.isDefined() ? aParameterSet.equatorialRadius_.toString() : "Undefined");
    ostk::core::utils::Print::Line(anOutputStream) << "Flattening:" << (aParameterSet.flattening_.isDefined() ? aParameterSet.flattening_.toString() : "Undefined");
    ostk::core::utils::Print::Line(anOutputStream) << "C20:" << (aParameterSet.C20_.isDefined() ? aParameterSet.C20_.toString() : "Undefined");
    ostk::core::utils::Print::Line(anOutputStream) << "C40:" << (aParameterSet.C40_.isDefined() ? aParameterSet.C40_.toString() : "Undefined");
    ostk::core::utils::Print::Line(anOutputStream) << "J2:" << (aParameterSet.J2_.isDefined() ? aParameterSet.J2_.toString() : "Undefined");
    ostk::core::utils::Print::Line(anOutputStream) << "J4:" << (aParameterSet.J4_.isDefined() ? aParameterSet.J4_.toString() : "Undefined");

    ostk::core::utils::Print::Footer(anOutputStream);

    return anOutputStream;
}

Model::Model(const Parameters& aSetOfParameters)
    : parameters_(aSetOfParameters)
{
}

Model::Parameters Model::getParameters() const
{
    return parameters_;
}

Model::~Model() {}

}  // namespace gravitational
}  // namespace environment
}  // namespace physics
}  // namespace ostk
