////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           OpenSpaceToolkit/Physics/Environment/Gravitational/Spherical.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Spherical.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Time/DateTime.hpp>
#include <OpenSpaceToolkit/Physics/Time/Scale.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (OpenSpaceToolkit_Physics_Environment_Gravitational_Spherical, Constructor)
{

    using ostk::physics::units::Length ;
    using ostk::physics::units::Time ;
    using ostk::physics::units::Derived ;
    using ostk::physics::environment::gravitational::Spherical ;

    {

        const Derived gravitationalParameter = { 1.0, Derived::Unit::GravitationalParameter(Length::Unit::Meter, Time::Unit::Second) } ;

        EXPECT_NO_THROW(Spherical spherical(gravitationalParameter)) ;

    }

    {

        EXPECT_ANY_THROW(Spherical(Derived::Undefined())) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Environment_Gravitational_Spherical, Clone)
{

    using ostk::physics::units::Length ;
    using ostk::physics::units::Time ;
    using ostk::physics::units::Derived ;
    using ostk::physics::environment::gravitational::Spherical ;

    {

        const Derived gravitationalParameter = { 1.0, Derived::Unit::GravitationalParameter(Length::Unit::Meter, Time::Unit::Second) } ;

        const Spherical spherical = { gravitationalParameter } ;

        EXPECT_NO_THROW(const Spherical* sphericalPtr = spherical.clone() ; delete sphericalPtr ;) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Environment_Gravitational_Spherical, GetFieldValueAt)
{

    using ostk::math::obj::Vector3d ;

    using ostk::physics::units::Length ;
    using ostk::physics::units::Time ;
    using ostk::physics::units::Derived ;
    using ostk::physics::time::Instant ;
    using ostk::physics::environment::gravitational::Spherical ;

    {

        const Derived gravitationalParameter = { 1.0, Derived::Unit::GravitationalParameter(Length::Unit::Meter, Time::Unit::Second) } ;

        const Spherical spherical = { gravitationalParameter } ;

        const Vector3d fieldValue = spherical.getFieldValueAt({ 1.0, 0.0, 0.0 }, Instant::J2000()) ;

        EXPECT_EQ(Vector3d(-1.0, 0.0, 0.0), fieldValue) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
