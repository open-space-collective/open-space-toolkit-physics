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
    const Derived& gravitationalParameter,
    const Length& equatorialRadius,
    const Real& flattening,
    const Real& J2,
    const Real& J4
)
    : gravitationalParameter_(gravitationalParameter),
      equatorialRadius_(equatorialRadius),
      flattening_(flattening),
      J2_(J2),
      J4_(J4),
      C20_(J2.isDefined() ? J2 * std::sqrt(5.0) : Real::Undefined()),
      C40_(J4.isDefined() ? J4 * std::sqrt(9.0) : Real::Undefined())
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
