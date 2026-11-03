/// Apache License 2.0

#include <cmath>
#include <limits>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Model.hpp>
#include <OpenSpaceToolkit/Physics/Utility/String.hpp>

namespace ostk
{
namespace physics
{
namespace environment
{
namespace gravitational
{

using ostk::physics::utility::DoubleToString;

// TBM: make C30 term mandatory
Model::Parameters::Parameters(
    const Derived& aGravitationalParameter,
    const Length& anEquatorialRadius,
    double aFlattening,
    double aC20,
    double aC40
)
    : gravitationalParameter_(aGravitationalParameter),
      equatorialRadius_(anEquatorialRadius),
      flattening_(aFlattening),
      C20_(aC20),
      C30_(0.0),
      C40_(aC40),
      J2_(!std::isnan(aC20) ? -aC20 * std::sqrt(5.0) : std::numeric_limits<double>::quiet_NaN()),
      J3_(0.0),
      J4_(!std::isnan(aC40) ? -aC40 * std::sqrt(9.0) : std::numeric_limits<double>::quiet_NaN())
{
}

Model::Parameters::Parameters(
    const Derived& aGravitationalParameter,
    const Length& anEquatorialRadius,
    double aFlattening,
    double aC20,
    double aC30,
    double aC40
)
    : gravitationalParameter_(aGravitationalParameter),
      equatorialRadius_(anEquatorialRadius),
      flattening_(aFlattening),
      C20_(aC20),
      C30_(aC30),
      C40_(aC40),
      J2_(!std::isnan(aC20) ? -aC20 * std::sqrt(5.0) : std::numeric_limits<double>::quiet_NaN()),
      J3_(!std::isnan(aC30) ? -aC30 * std::sqrt(7.0) : std::numeric_limits<double>::quiet_NaN()),
      J4_(!std::isnan(aC40) ? -aC40 * std::sqrt(9.0) : std::numeric_limits<double>::quiet_NaN())
{
}

Model::Parameters Model::Parameters::Undefined()
{
    return {
        Derived::Undefined(),
        Length::Undefined(),
        std::numeric_limits<double>::quiet_NaN(),
        std::numeric_limits<double>::quiet_NaN(),
        std::numeric_limits<double>::quiet_NaN(),
        std::numeric_limits<double>::quiet_NaN(),
    };
}

bool Model::Parameters::isDefined() const
{
    return (
        gravitationalParameter_.isDefined() && equatorialRadius_.isDefined() && !std::isnan(flattening_) &&
        !std::isnan(J2_) && !std::isnan(J3_) && !std::isnan(J4_) && !std::isnan(C20_) && !std::isnan(C30_) &&
        !std::isnan(C40_)
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
        (J2_ == aParameterSet.J2_) && (J3_ == aParameterSet.J3_) && (J4_ == aParameterSet.J4_) &&
        (C20_ == aParameterSet.C20_) && (C30_ == aParameterSet.C30_) && (C40_ == aParameterSet.C40_)
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
        << "Gravitational Parameter:"
        << (aParameterSet.gravitationalParameter_.isDefined() ? aParameterSet.gravitationalParameter_.toString()
                                                              : "Undefined");
    ostk::core::utils::Print::Line(anOutputStream)
        << "Equatorial Radius:"
        << (aParameterSet.equatorialRadius_.isDefined() ? aParameterSet.equatorialRadius_.toString() : "Undefined");
    ostk::core::utils::Print::Line(anOutputStream) << "Flattening:" << DoubleToString(aParameterSet.flattening_);
    ostk::core::utils::Print::Line(anOutputStream) << "C20:" << DoubleToString(aParameterSet.C20_);
    ostk::core::utils::Print::Line(anOutputStream) << "C30:" << DoubleToString(aParameterSet.C30_);
    ostk::core::utils::Print::Line(anOutputStream) << "C40:" << DoubleToString(aParameterSet.C40_);
    ostk::core::utils::Print::Line(anOutputStream) << "J2:" << DoubleToString(aParameterSet.J2_);
    ostk::core::utils::Print::Line(anOutputStream) << "J3:" << DoubleToString(aParameterSet.J3_);
    ostk::core::utils::Print::Line(anOutputStream) << "J4:" << DoubleToString(aParameterSet.J4_);

    ostk::core::utils::Print::Footer(anOutputStream);

    return anOutputStream;
}

Length Model::Parameters::computeGeocentricRadiusAt(const Angle& aLatitude) const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Parameters");
    }

    const double equatorialRadius_Meters = equatorialRadius_.inMeters();
    const double polarRadius_Meters = equatorialRadius_Meters * (1.0 - flattening_);

    const double latitude_Radians = aLatitude.inRadians();
    const double cosLatitude = std::cos(latitude_Radians);
    const double sinLatitude = std::sin(latitude_Radians);

    const double polarRadiusSquared = polarRadius_Meters * polarRadius_Meters;
    const double equatorialRadiusSquared = equatorialRadius_Meters * equatorialRadius_Meters;

    const double numerator =
        std::pow((equatorialRadiusSquared * cosLatitude), 2) + std::pow((polarRadiusSquared * sinLatitude), 2);
    const double denominator =
        std::pow((equatorialRadius_Meters * cosLatitude), 2) + std::pow((polarRadius_Meters * sinLatitude), 2);

    return Length::Meters(std::sqrt(numerator / denominator));
}

Model::Model(const Parameters& aSetOfParameters)
    : parameters_(aSetOfParameters)
{
}

Model::~Model() {}

bool Model::isPointMass() const
{
    return false;
}

Model::Parameters Model::getParameters() const
{
    return parameters_;
}

}  // namespace gravitational
}  // namespace environment
}  // namespace physics
}  // namespace ostk
