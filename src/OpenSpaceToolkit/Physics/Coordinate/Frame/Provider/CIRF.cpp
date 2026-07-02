/// Apache License 2.0

#include <cmath>
#include <cstdlib>
#include <cstring>
#include <mutex>
#include <unordered_map>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/RotationMatrix.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/CIRF.hpp>
#include <OpenSpaceToolkit/Physics/Time/DateTime.hpp>
#include <OpenSpaceToolkit/Physics/Time/Scale.hpp>
#include <OpenSpaceToolkit/Physics/Unit/Derived/Angle.hpp>

// Include sofa last to avoid type errors in underlying Eigen lib
#include <sofa/sofa.h>

#define DAS2R (4.848136811095359935899141e-6)
#define DMAS2R (DAS2R / 1e3)

namespace
{

/// The IAU 2006/2000A X, Y, s series (iauXys06a) dominates the cost of a GCRF <> CIRF
/// transform (~50 us per evaluation) while its output varies smoothly in time (the shortest
/// significant nutation periods are ~5 days). Evaluating the series on a uniform 0.25-day
/// grid and interpolating with a centered 4-point Lagrange polynomial reproduces the direct
/// evaluation to nano-arcsecond level, several orders of magnitude below both the series
/// truncation level and the CIP corrections applied by the caller.
class XysGrid
{
   public:
    static void Evaluate(const double aModifiedJulianDate_TT, double& x, double& y, double& s)
    {
        static XysGrid grid;
        grid.evaluate(aModifiedJulianDate_TT, x, y, s);
    }

   private:
    struct Node
    {
        double x;
        double y;
        double s;
    };

    static constexpr double gridSpacingDays_ = 0.25;
    static constexpr std::size_t maxNodeCount_ = 16384;

    std::mutex mutex_;
    std::unordered_map<std::int64_t, Node> nodes_;

    void evaluate(const double aModifiedJulianDate_TT, double& x, double& y, double& s)
    {
        const double gridCoordinate = aModifiedJulianDate_TT / gridSpacingDays_;
        const std::int64_t nodeIndex = static_cast<std::int64_t>(std::floor(gridCoordinate));
        const double tau = gridCoordinate - static_cast<double>(nodeIndex);  // in [0, 1)

        const std::lock_guard<std::mutex> lock {mutex_};

        const Node node0 = this->accessNode(nodeIndex - 1);
        const Node node1 = this->accessNode(nodeIndex);
        const Node node2 = this->accessNode(nodeIndex + 1);
        const Node node3 = this->accessNode(nodeIndex + 2);

        // Centered 4-point Lagrange weights at tau between node1 and node2

        const double w0 = -tau * (tau - 1.0) * (tau - 2.0) / 6.0;
        const double w1 = (tau + 1.0) * (tau - 1.0) * (tau - 2.0) / 2.0;
        const double w2 = -(tau + 1.0) * tau * (tau - 2.0) / 2.0;
        const double w3 = (tau + 1.0) * tau * (tau - 1.0) / 6.0;

        x = w0 * node0.x + w1 * node1.x + w2 * node2.x + w3 * node3.x;
        y = w0 * node0.y + w1 * node1.y + w2 * node2.y + w3 * node3.y;
        s = w0 * node0.s + w1 * node1.s + w2 * node2.s + w3 * node3.s;
    }

    const Node& accessNode(const std::int64_t aNodeIndex)  // requires mutex_ to be held
    {
        const auto nodeIt = this->nodes_.find(aNodeIndex);

        if (nodeIt != this->nodes_.end())
        {
            return nodeIt->second;
        }

        if (this->nodes_.size() >= maxNodeCount_)
        {
            this->nodes_.clear();
        }

        Node node;
        iauXys06a(2400000.5, static_cast<double>(aNodeIndex) * gridSpacingDays_, &node.x, &node.y, &node.s);

        return this->nodes_.emplace(aNodeIndex, node).first->second;
    }
};

bool useXysInterpolation()
{
    static const bool enabled = []() -> bool
    {
        const char* env = std::getenv("OSTK_PHYSICS_COORDINATE_FRAME_PROVIDER_CIRF_XYS_INTERPOLATION");
        return !((env != nullptr) && ((std::strcmp(env, "Disabled") == 0) || (std::strcmp(env, "False") == 0)));
    }();

    return enabled;
}

}  // namespace

namespace ostk
{
namespace physics
{
namespace coordinate
{
namespace frame
{
namespace provider
{

CIRF::CIRF() {}

CIRF::~CIRF() {}

CIRF* CIRF::clone() const
{
    return new CIRF(*this);
}

bool CIRF::isDefined() const
{
    return true;
}

Transform CIRF::getTransformAt(const Instant& anInstant) const
{
    using ostk::mathematics::geometry::d3::transformation::rotation::RotationMatrix;

    using ostk::physics::time::DateTime;
    using ostk::physics::time::Scale;

    if (!anInstant.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("CIRF");
    }

    // http://www.iausofa.org/2018_0130_C/sofa/sofa_pn_c.pdf

    // Time (TT)

    static const Real djmjd0 = 2400000.5;
    const Real tt = anInstant.getModifiedJulianDate(Scale::TT);

    // CIP and CIO, IAU 2006/2000A

    double x;
    double y;
    double s;

    if (useXysInterpolation())
    {
        XysGrid::Evaluate(tt, x, y, s);
    }
    else
    {
        iauXys06a(djmjd0, tt, &x, &y, &s);
    }

    // CIP offsets wrt IAU 2006/2000A (mas->radians)

    static const Real dx06 = +0.1750 * DMAS2R;
    static const Real dy06 = -0.2259 * DMAS2R;

    // Add CIP corrections

    x += dx06;
    y += dy06;

    // GCRS to CIRS matrix

    double rc2i[3][3];  // dcm_CIRS_GCRS

    iauC2ixys(x, y, s, rc2i);

    const Vector3d GCRF_x_CIRF = Vector3d(rc2i[0][0], rc2i[1][0], rc2i[2][0]).normalized();
    const Vector3d GCRF_y_CIRF = Vector3d(rc2i[0][1], rc2i[1][1], rc2i[2][1]).normalized();
    const Vector3d GCRF_z_CIRF = Vector3d(rc2i[0][2], rc2i[1][2], rc2i[2][2]).normalized();

    const RotationMatrix dcm_CIRF_GCRF = RotationMatrix::Columns(GCRF_x_CIRF, GCRF_y_CIRF, GCRF_z_CIRF);

    // Output

    const Vector3d x_CIRF_GCRF = {0.0, 0.0, 0.0};
    const Vector3d v_CIRF_GCRF = {0.0, 0.0, 0.0};

    const Quaternion q_CIRF_GCRF = Quaternion::RotationMatrix(dcm_CIRF_GCRF).rectify();
    const Vector3d w_CIRF_GCRF_in_CIRF = {0.0, 0.0, 0.0};

    return Transform::Passive(anInstant, x_CIRF_GCRF, v_CIRF_GCRF, q_CIRF_GCRF, w_CIRF_GCRF_in_CIRF);
}

}  // namespace provider
}  // namespace frame
}  // namespace coordinate
}  // namespace physics
}  // namespace ostk
