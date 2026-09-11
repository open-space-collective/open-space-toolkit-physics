/// Apache License 2.0

#include <array>
#include <atomic>
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
/// grid and interpolating with a centered 8-point Lagrange polynomial reproduces the direct
/// evaluation to the double-precision floor (observed max ~1e-4 uas on X, Y, s and ~6e-16 rad
/// on the resulting rotation, sampled over 1980-2060), so the interpolated and direct paths
/// are indistinguishable. Same grid spacing, 4-point polynomial: ~1 uas; 8-point at 12 h: ~0.02 uas.
class XysGrid
{
   public:
    static void Evaluate(const double aModifiedJulianDate_TT, double& x, double& y, double& s)
    {
        XysGrid::Get().evaluate(aModifiedJulianDate_TT, x, y, s);
    }

    static void Clear()
    {
        XysGrid::Get().clear();
    }

   private:
    struct Node
    {
        double x;
        double y;
        double s;
    };

    // 0.25 days (4 series evaluations per simulated day), with maximum 16384 size gives ~11 years of storage.
    static constexpr double gridSpacingDays_ = 0.25;
    static constexpr std::size_t maxNodeCount_ = 16384;  // maximum ~1 MB of memory

    // Centered 8-point stencil: a date in grid interval [k, k + 1) is interpolated from nodes k - 3 ... k + 4.
    static constexpr std::size_t stencilSize_ = 8;
    static constexpr std::int64_t stencilFirstOffset_ = -3;

    std::mutex mutex_;
    std::unordered_map<std::int64_t, Node> nodes_;

    void evaluate(const double aModifiedJulianDate_TT, double& x, double& y, double& s)
    {
        const double gridCoordinate = aModifiedJulianDate_TT / gridSpacingDays_;
        const std::int64_t intervalIndex = static_cast<std::int64_t>(std::floor(gridCoordinate));
        const double tau = gridCoordinate - static_cast<double>(intervalIndex);  // in [0, 1)

        const std::array<double, stencilSize_> weights = XysGrid::LagrangeWeights(tau);

        const std::lock_guard<std::mutex> lock {mutex_};

        x = 0.0;
        y = 0.0;
        s = 0.0;

        for (std::size_t j = 0; j < stencilSize_; ++j)
        {
            const Node& node = this->accessNode(intervalIndex + stencilFirstOffset_ + static_cast<std::int64_t>(j));

            x += weights[j] * node.x;
            y += weights[j] * node.y;
            s += weights[j] * node.s;
        }
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

    void clear()
    {
        const std::lock_guard<std::mutex> lock {mutex_};

        this->nodes_.clear();
    }

    static XysGrid& Get()
    {
        static XysGrid grid;

        return grid;
    }

    /// Weights of the Lagrange polynomial through the stencil nodes, evaluated at tau in [0, 1), where tau is measured
    /// from the node at offset 0 in units of the grid spacing. At tau == 0 the weight of that node is exactly 1.
    static std::array<double, stencilSize_> LagrangeWeights(const double tau)
    {
        std::array<double, stencilSize_> weights;

        for (std::size_t j = 0; j < stencilSize_; ++j)
        {
            const double p = static_cast<double>(stencilFirstOffset_ + static_cast<std::int64_t>(j));

            double weight = 1.0;

            for (std::size_t m = 0; m < stencilSize_; ++m)
            {
                if (m != j)
                {
                    const double q = static_cast<double>(stencilFirstOffset_ + static_cast<std::int64_t>(m));

                    weight *= (tau - q) / (p - q);
                }
            }

            weights[j] = weight;
        }

        return weights;
    }
};

bool xysInterpolationEnabledFromEnv()
{
    const char* env = std::getenv("OSTK_PHYSICS_COORDINATE_FRAME_PROVIDER_CIRF_XYS_INTERPOLATION");
    if (env == nullptr)
    {
        return false;
    }

    if ((std::strcmp(env, "Enabled") == 0) || (std::strcmp(env, "enabled") == 0) || (std::strcmp(env, "True") == 0) ||
        (std::strcmp(env, "true") == 0))
    {
        return true;
    }

    return false;
}

// Effective interpolation flag: initialized from the environment, overridable at runtime.
std::atomic<bool>& xysInterpolationEnabledFlag()
{
    static std::atomic<bool> enabled {xysInterpolationEnabledFromEnv()};
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

    const Real tt = anInstant.getModifiedJulianDate(Scale::TT);

    // CIP and CIO, IAU 2006/2000A

    double x;
    double y;
    double s;

    CIRF::ComputeCIPCoordinates(tt, x, y, s, CIRF::IsXysInterpolationEnabled());

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

void CIRF::ComputeCIPCoordinates(
    const Real& aModifiedJulianDate_TT, double& x, double& y, double& s, const bool interpolate
)
{
    static const double djmjd0 = 2400000.5;

    if (interpolate)
    {
        XysGrid::Evaluate(aModifiedJulianDate_TT, x, y, s);
    }
    else
    {
        iauXys06a(djmjd0, aModifiedJulianDate_TT, &x, &y, &s);
    }
}

bool CIRF::IsXysInterpolationEnabled()
{
    return xysInterpolationEnabledFlag().load();
}

void CIRF::SetXysInterpolationEnabled(const bool anInterpolationEnabledFlag)
{
    xysInterpolationEnabledFlag().store(anInterpolationEnabledFlag);
}

void CIRF::ClearXysCache()
{
    XysGrid::Clear();
}

}  // namespace provider
}  // namespace frame
}  // namespace coordinate
}  // namespace physics
}  // namespace ostk
