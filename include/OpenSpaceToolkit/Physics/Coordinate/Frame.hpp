/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Coordinate_Frame__
#define __OpenSpaceToolkit_Physics_Coordinate_Frame__

#include <memory>

#include <OpenSpaceToolkit/Core/Type/Integer.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>
#include <OpenSpaceToolkit/Core/Type/Shared.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Axes.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/IAU/Theory.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Position.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Transform.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Velocity.hpp>

namespace ostk
{
namespace physics
{
namespace coordinate
{

namespace iau = ostk::physics::coordinate::frame::provider::iau;

using ostk::core::type::Real;
using ostk::core::type::Shared;
using ostk::core::type::String;
using ostk::core::type::Uint8;

using ostk::mathematics::object::Vector3d;

using ostk::physics::coordinate::Axes;
using ostk::physics::coordinate::frame::Provider;
using ostk::physics::coordinate::Position;
using ostk::physics::coordinate::Transform;
using ostk::physics::coordinate::Velocity;

/// @brief Reference frame
///
/// @ref https://en.wikipedia.org/wiki/Frame_of_reference
/// @note Implementation heavily inspired by (the great!) https://www.orekit.org/static/architecture/frames.html

class Frame : public std::enable_shared_from_this<Frame>
{
   public:
    /// @brief Destructor

    ~Frame();

    /// @brief Equality operator
    ///
    /// @code
    ///     Frame::GCRF() == Frame::GCRF() ; // True
    /// @endcode
    ///
    /// @param [in] aFrame A frame to compare with
    /// @return True if frames are equal
    bool operator==(const Frame& aFrame) const;

    /// @brief Inequality operator
    ///
    /// @code
    ///     Frame::GCRF() != Frame::ITRF() ; // True
    /// @endcode
    ///
    /// @param [in] aFrame A frame to compare with
    /// @return True if frames are not equal
    bool operator!=(const Frame& aFrame) const;

    /// @brief Output stream operator
    ///
    /// @code
    ///     std::cout << *Frame::GCRF() ;
    /// @endcode
    ///
    /// @param [in] anOutputStream An output stream
    /// @param [in] aFrame A frame
    /// @return A reference to the output stream
    friend std::ostream& operator<<(std::ostream& anOutputStream, const Frame& aFrame);

    /// @brief Check if the frame is defined
    ///
    /// @code
    ///     Frame::GCRF()->isDefined() ; // True
    /// @endcode
    ///
    /// @return True if the frame is defined
    bool isDefined() const;

    /// @brief Check if the frame is quasi-inertial
    ///
    /// @code
    ///     Frame::GCRF()->isQuasiInertial() ; // True
    /// @endcode
    ///
    /// @return True if the frame is quasi-inertial
    bool isQuasiInertial() const;

    /// @brief Check if the frame has a parent frame
    ///
    /// @code
    ///     Frame::ITRF()->hasParent() ; // True
    /// @endcode
    ///
    /// @return True if the frame has a parent
    bool hasParent() const;

    /// @brief Access the parent frame
    ///
    /// @code
    ///     Frame::ITRF()->accessParent() ;
    /// @endcode
    ///
    /// @return Shared pointer to the parent frame
    Shared<const Frame> accessParent() const;

    /// @brief Access an ancestor frame at a given degree
    ///
    /// @code
    ///     Frame::ITRF()->accessAncestor(2) ;
    /// @endcode
    ///
    /// @param [in] anAncestorDegree The ancestor degree (1 = parent, 2 = grandparent, etc.)
    /// @return Shared pointer to the ancestor frame
    Shared<const Frame> accessAncestor(const Uint8 anAncestorDegree) const;

    /// @brief Access the transform provider
    ///
    /// @code
    ///     Frame::GCRF()->accessProvider() ;
    /// @endcode
    ///
    /// @return Shared pointer to the transform provider
    Shared<const Provider> accessProvider() const;

    /// @brief Get the name of the frame
    ///
    /// @code
    ///     Frame::GCRF()->getName() ; // "GCRF"
    /// @endcode
    ///
    /// @return Frame name
    String getName() const;

    /// @brief Get the origin of this frame expressed in another frame at a given instant
    ///
    /// @code
    ///     Frame::ITRF()->getOriginIn(Frame::GCRF(), Instant::J2000()) ;
    /// @endcode
    ///
    /// @param [in] aFrame A shared pointer to the target frame
    /// @param [in] anInstant An instant
    /// @return Position of the origin in the target frame
    Position getOriginIn(const Shared<const Frame>& aFrame, const Instant& anInstant) const;

    /// @brief Get the velocity of this frame's origin expressed in another frame at a given instant
    ///
    /// @code
    ///     Frame::ITRF()->getVelocityIn(Frame::GCRF(), Instant::J2000()) ;
    /// @endcode
    ///
    /// @param [in] aFrame A shared pointer to the target frame
    /// @param [in] anInstant An instant
    /// @return Velocity of the origin in the target frame
    Velocity getVelocityIn(const Shared<const Frame>& aFrame, const Instant& anInstant) const;

    /// @brief Get the axes of this frame expressed in another frame at a given instant
    ///
    /// @code
    ///     Frame::ITRF()->getAxesIn(Frame::GCRF(), Instant::J2000()) ;
    /// @endcode
    ///
    /// @param [in] aFrame A shared pointer to the target frame
    /// @param [in] anInstant An instant
    /// @return Axes expressed in the target frame
    Axes getAxesIn(const Shared<const Frame>& aFrame, const Instant& anInstant) const;

    /// @brief Get the transform from this frame to another frame at a given instant
    ///
    /// @code
    ///     Frame::ITRF()->getTransformTo(Frame::GCRF(), Instant::J2000()) ;
    /// @endcode
    ///
    /// @param [in] aFrame A shared pointer to the target frame
    /// @param [in] anInstant An instant
    /// @return Transform from this frame to the target frame
    Transform getTransformTo(const Shared<const Frame>& aFrame, const Instant& anInstant) const;

    /// @brief Construct an undefined frame
    ///
    /// @code
    ///     Shared<const Frame> frame = Frame::Undefined() ;
    /// @endcode
    ///
    /// @return Shared pointer to an undefined frame
    static Shared<const Frame> Undefined();

    /// @brief Get the Geocentric Celestial Reference Frame (GCRF)
    ///
    /// @code
    ///     Shared<const Frame> frame = Frame::GCRF() ;
    /// @endcode
    ///
    /// @return Shared pointer to the GCRF frame
    static Shared<const Frame> GCRF();

    /// @brief Get the J2000 frame for a given IAU theory
    ///
    /// @code
    ///     Shared<const Frame> frame = Frame::J2000(iau::Theory::IAU_2006) ;
    /// @endcode
    ///
    /// @param [in] aTheory An IAU precession-nutation theory
    /// @return Shared pointer to the J2000 frame
    static Shared<const Frame> J2000(const iau::Theory& aTheory);

    /// @brief Get the Mean of Date (MOD) frame for a given epoch
    ///
    /// @code
    ///     Shared<const Frame> frame = Frame::MOD(Instant::J2000()) ;
    /// @endcode
    ///
    /// @param [in] anEpoch An epoch instant
    /// @return Shared pointer to the MOD frame
    static Shared<const Frame> MOD(const Instant& anEpoch);

    /// @brief Get the True of Date (TOD) frame for a given epoch and IAU theory
    ///
    /// @code
    ///     Shared<const Frame> frame = Frame::TOD(Instant::J2000(), iau::Theory::IAU_2006) ;
    /// @endcode
    ///
    /// @param [in] anEpoch An epoch instant
    /// @param [in] aTheory An IAU precession-nutation theory
    /// @return Shared pointer to the TOD frame
    static Shared<const Frame> TOD(const Instant& anEpoch, const iau::Theory& aTheory);

    /// @brief Get the True Equator Mean Equinox (TEME) frame
    ///
    /// @code
    ///     Shared<const Frame> frame = Frame::TEME() ;
    /// @endcode
    ///
    /// @return Shared pointer to the TEME frame
    static Shared<const Frame> TEME();

    /// @brief Get the True Equator Mean Equinox (TEME) frame of a given epoch
    ///
    /// @code
    ///     Shared<const Frame> frame = Frame::TEMEOfEpoch(Instant::J2000()) ;
    /// @endcode
    ///
    /// @param [in] anEpoch An epoch instant
    /// @return Shared pointer to the TEME of epoch frame
    static Shared<const Frame> TEMEOfEpoch(const Instant& anEpoch);

    /// @brief Get the Celestial Intermediate Reference Frame (CIRF)
    ///
    /// @code
    ///     Shared<const Frame> frame = Frame::CIRF() ;
    /// @endcode
    ///
    /// @return Shared pointer to the CIRF frame
    static Shared<const Frame> CIRF();

    /// @brief Get the Terrestrial Intermediate Reference Frame (TIRF)
    ///
    /// @code
    ///     Shared<const Frame> frame = Frame::TIRF() ;
    /// @endcode
    ///
    /// @return Shared pointer to the TIRF frame
    static Shared<const Frame> TIRF();

    /// @brief Get the International Terrestrial Reference Frame (ITRF)
    ///
    /// @code
    ///     Shared<const Frame> frame = Frame::ITRF() ;
    /// @endcode
    ///
    /// @return Shared pointer to the ITRF frame
    static Shared<const Frame> ITRF();

    /// @brief Get a frame by name
    ///
    /// @code
    ///     Shared<const Frame> frame = Frame::WithName("GCRF") ;
    /// @endcode
    ///
    /// @param [in] aName A frame name
    /// @return Shared pointer to the frame
    static Shared<const Frame> WithName(const String& aName);

    /// @brief Check if a frame with the given name exists
    ///
    /// @code
    ///     Frame::Exists("GCRF") ; // True
    /// @endcode
    ///
    /// @param [in] aName A frame name
    /// @return True if the frame exists
    static bool Exists(const String& aName);

    /// @brief Constructor
    ///
    /// @code
    ///     Shared<const Frame> frame = Frame::Construct("MyFrame", true, Frame::GCRF(), aProvider) ;
    /// @endcode
    ///
    /// @param [in] aName A frame name
    /// @param [in] isQuasiInertialT True is frame is quasi-inertial
    /// @param [in] aParentFrame A shared pointer to the parent frame
    /// @param [in] aProvider A shared pointer to the transform provider

    static Shared<const Frame> Construct(
        const String& aName,
        bool isQuasiInertial,
        const Shared<const Frame>& aParentFrame,
        const Shared<const Provider>& aProvider
    );

    /// @brief Destruct and remove a frame by name
    ///
    /// @code
    ///     Frame::Destruct("MyFrame") ;
    /// @endcode
    ///
    /// @param [in] aName A frame name
    static void Destruct(const String& aName);

   protected:
    /// @brief Constructor
    ///
    /// @param [in] aName A frame name
    /// @param [in] isQuasiInertial True if the frame is quasi-inertial
    /// @param [in] aParentFrame A shared pointer to the parent frame
    /// @param [in] aProvider A shared pointer to the transform provider
    Frame(
        const String& aName,
        bool isQuasiInertial,
        const Shared<const Frame>& aParentFrame,
        const Shared<const Provider>& aProvider
    );

    /// @brief Copy constructor (defaulted)
    Frame(const Frame& aFrame) = default;

    /// @brief Copy assignment operator (defaulted)
    Frame& operator=(const Frame& aFrame) = default;

   private:
    String name_;
    bool quasiInertial_;
    Shared<const Frame> parentFrameSPtr_;
    Shared<const Provider> providerSPtr_;  // Provides transform from parent to instance -> Unique<> instead?

    Uint8 getDepth() const;

    static Shared<const Frame> Emplace(
        const String& aName,
        bool isQuasiInertial,
        const Shared<const Frame>& aParentFrame,
        const Shared<const Provider>& aProvider
    );

    static Shared<const Frame> FindCommonAncestor(
        const Shared<const Frame>& aFirstFrameSPtr, const Shared<const Frame>& aSecondFrameSPtr
    );
};

}  // namespace coordinate
}  // namespace physics
}  // namespace ostk

#endif
