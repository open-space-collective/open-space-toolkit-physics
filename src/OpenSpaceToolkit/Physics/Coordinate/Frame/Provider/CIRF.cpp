/// Apache License 2.0

#include <array>
#include <atomic>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <limits>
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
///
/// Thread safety: the shared node map is guarded by a mutex, but the hot path does not take it.
/// Each thread keeps the stencil of its most recent grid interval in a thread_local window, so
/// consecutive evaluations within the same 0.25-day interval (the common case when stepping
/// through time) are lock-free. The mutex is only taken when a thread moves to another interval,
/// and the series itself is evaluated outside the lock, so a cache miss on one thread never
/// blocks the others. Nodes are deterministic functions of their index, hence the result never
/// depends on which thread populated the cache or on the evaluation order.
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

    /// Stencil nodes of one grid interval, kept per thread (see class comment).
    struct Window
    {
        std::int64_t intervalIndex = std::numeric_limits<std::int64_t>::min();
        std::array<Node, stencilSize_> nodes {};
    };

    std::mutex mutex_;
    std::unordered_map<std::int64_t, Node> nodes_;

    void evaluate(const double aModifiedJulianDate_TT, double& x, double& y, double& s)
    {
        static thread_local Window window;

        const double gridCoordinate = aModifiedJulianDate_TT / gridSpacingDays_;
        const std::int64_t intervalIndex = static_cast<std::int64_t>(std::floor(gridCoordinate));
        const double tau = gridCoordinate - static_cast<double>(intervalIndex);  // in [0, 1)

        if (window.intervalIndex != intervalIndex)
        {
            this->loadWindow(intervalIndex, window);
        }

        const std::array<double, stencilSize_> weights = XysGrid::LagrangeWeights(tau);

        x = 0.0;
        y = 0.0;
        s = 0.0;

        for (std::size_t j = 0; j < stencilSize_; ++j)
        {
            x += weights[j] * window.nodes[j].x;
            y += weights[j] * window.nodes[j].y;
            s += weights[j] * window.nodes[j].s;
        }
    }

    void loadWindow(const std::int64_t anIntervalIndex, Window& aWindow)
    {
        for (std::size_t j = 0; j < stencilSize_; ++j)
        {
            aWindow.nodes[j] = this->getNode(anIntervalIndex + stencilFirstOffset_ + static_cast<std::int64_t>(j));
        }

        aWindow.intervalIndex = anIntervalIndex;
    }

    Node getNode(const std::int64_t aNodeIndex)
    {
        {
            const std::lock_guard<std::mutex> lock {mutex_};

            const auto nodeIt = this->nodes_.find(aNodeIndex);

            if (nodeIt != this->nodes_.end())
            {
                return nodeIt->second;
            }
        }

        // Cache miss: evaluate the series outside the lock so that other threads are not blocked meanwhile. Threads
        // missing on the same node compute identical values, and emplace keeps whichever was inserted first.

        Node node;
        iauXys06a(2400000.5, static_cast<double>(aNodeIndex) * gridSpacingDays_, &node.x, &node.y, &node.s);

        const std::lock_guard<std::mutex> lock {mutex_};

        if (this->nodes_.size() >= maxNodeCount_)
        {
            this->nodes_.clear();
        }

        return this->nodes_.emplace(aNodeIndex, node).first->second;
    }

    void clear()
    {
        // Only the shared map is released. Per-thread windows hold a fixed 8 nodes each and remain valid, since
        // nodes are deterministic functions of their index.

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

}  // namespace provider
}  // namespace frame
}  // namespace coordinate
}  // namespace physics
}  // namespace ostk
