/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_Dynamic__
#define __OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_Dynamic__

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Transform.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

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

using ostk::physics::coordinate::frame::Provider;
using ostk::physics::coordinate::Transform;
using ostk::physics::time::Instant;

/// @brief Dynamic provider

class Dynamic : public Provider
{
   public:
    /// @brief Transform generator function type.
    typedef std::function<Transform(const Instant&)> Generator;

    /// @brief Constructor.
    ///
    /// @code
    ///     Dynamic provider(generator) ;
    /// @endcode
    ///
    /// @param [in] aGenerator A transform generator function
    Dynamic(const Dynamic::Generator& aGenerator);

    /// @brief Destructor.
    virtual ~Dynamic() override;

    /// @brief Clone the Dynamic provider.
    ///
    /// @code
    ///     Dynamic* clonePtr = provider.clone() ;
    /// @endcode
    ///
    /// @return A pointer to the cloned Dynamic provider
    virtual Dynamic* clone() const override;

    /// @brief Check if the Dynamic provider is defined.
    ///
    /// @code
    ///     provider.isDefined() ; // True
    /// @endcode
    ///
    /// @return True if the Dynamic provider is defined
    virtual bool isDefined() const override;

    /// @brief Get the transform at a given instant.
    ///
    /// @code
    ///     Transform transform = provider.getTransformAt(Instant::J2000()) ;
    /// @endcode
    ///
    /// @param [in] anInstant An instant
    /// @return The transform at the given instant
    virtual Transform getTransformAt(const Instant& anInstant) const override;

    /// @brief Create an undefined Dynamic provider.
    ///
    /// @code
    ///     Dynamic provider = Dynamic::Undefined() ;
    /// @endcode
    ///
    /// @return An undefined Dynamic provider
    static Dynamic Undefined();

   private:
    Dynamic::Generator generator_;
};

}  // namespace provider
}  // namespace frame
}  // namespace coordinate
}  // namespace physics
}  // namespace ostk

#endif
