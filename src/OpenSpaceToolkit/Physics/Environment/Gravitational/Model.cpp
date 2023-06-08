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
