/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Coordinate_Axes__
#define __OpenSpaceToolkit_Physics_Coordinate_Axes__

#include <OpenSpaceToolkit/Core/Type/Shared.hpp>

#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

namespace ostk
{
namespace physics
{
namespace coordinate
{

using ostk::core::type::Shared;

using ostk::mathematics::object::Vector3d;

using ostk::physics::time::Instant;

class Frame;

/// @brief Axes

class Axes
{
   public:
    /// @brief Constructor
    ///
    /// @code
    ///     Axes axes({1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}, Frame::GCRF());
    /// @endcode
    ///
    /// @param [in] aXAxis An X-axis vector
    /// @param [in] aYAxis A Y-axis vector
    /// @param [in] aZAxis A Z-axis vector
    /// @param [in] aFrameSPtr A shared pointer to the reference frame
    Axes(const Vector3d& aXAxis, const Vector3d& aYAxis, const Vector3d& aZAxis, const Shared<const Frame>& aFrameSPtr);

    /// @brief Equality operator
    ///
    /// @code
    ///     axes == otherAxes; // True
    /// @endcode
    ///
    /// @param [in] anAxes An axes object to compare with
    /// @return True if axes are equal
    bool operator==(const Axes& anAxes) const;

    /// @brief Inequality operator
    ///
    /// @code
    ///     axes != otherAxes; // False
    /// @endcode
    ///
    /// @param [in] anAxes An axes object to compare with
    /// @return True if axes are not equal
    bool operator!=(const Axes& anAxes) const;

    /// @brief Output stream operator
    ///
    /// @code
    ///     std::cout << axes;
    /// @endcode
    ///
    /// @param [in] anOutputStream An output stream
    /// @param [in] anAxes An axes object
    /// @return A reference to the output stream
    friend std::ostream& operator<<(std::ostream& anOutputStream, const Axes& anAxes);

    /// @brief Check if the axes are defined
    ///
    /// @code
    ///     Axes::Undefined().isDefined(); // False
    /// @endcode
    ///
    /// @return True if the axes are defined
    bool isDefined() const;

    /// @brief Get the X-axis vector
    ///
    /// @code
    ///     axes.x();
    /// @endcode
    ///
    /// @return Reference to the X-axis vector
    const Vector3d& x() const;

    /// @brief Get the Y-axis vector
    ///
    /// @code
    ///     axes.y();
    /// @endcode
    ///
    /// @return Reference to the Y-axis vector
    const Vector3d& y() const;

    /// @brief Get the Z-axis vector
    ///
    /// @code
    ///     axes.z();
    /// @endcode
    ///
    /// @return Reference to the Z-axis vector
    const Vector3d& z() const;

    /// @brief Get the reference frame
    ///
    /// @code
    ///     axes.getFrame();
    /// @endcode
    ///
    /// @return Shared pointer to the reference frame
    Shared<const Frame> getFrame() const;

    /// @brief Convert axes to a different reference frame at a given instant
    ///
    /// @code
    ///     axes.inFrame(Frame::ITRF(), Instant::J2000());
    /// @endcode
    ///
    /// @param [in] aFrameSPtr A shared pointer to the target frame
    /// @param [in] anInstant An instant
    /// @return Axes expressed in the specified frame
    Axes inFrame(const Shared<const Frame>& aFrameSPtr, const Instant& anInstant) const;

    /// @brief Construct an undefined axes object
    ///
    /// @code
    ///     Axes axes = Axes::Undefined();
    /// @endcode
    ///
    /// @return Undefined axes
    static Axes Undefined();

   private:
    Vector3d x_;
    Vector3d y_;
    Vector3d z_;

    Shared<const Frame> frameSPtr_;
};

}  // namespace coordinate
}  // namespace physics
}  // namespace ostk

#endif
