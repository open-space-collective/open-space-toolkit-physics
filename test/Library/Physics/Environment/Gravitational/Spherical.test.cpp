////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library ▸ Physics
/// @file           Library/Physics/Environment/Gravitational/Spherical.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Environment/Gravitational/Spherical.hpp>
#include <Library/Physics/Time/Instant.hpp>
#include <Library/Physics/Time/DateTime.hpp>
#include <Library/Physics/Time/Scale.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Physics_Environment_Gravitational_Spherical, Constructor)
{

    using library::physics::units::Length ;
    using library::physics::units::Time ;
    using library::physics::units::Derived ;
    using library::physics::environment::gravitational::Spherical ;

    {

        const Derived gravitationalParameter = { 1.0, Derived::Unit::GravitationalParameter(Length::Unit::Meter, Time::Unit::Second) } ;

        EXPECT_NO_THROW(Spherical spherical(gravitationalParameter)) ;

    }

    {

        EXPECT_ANY_THROW(Spherical(Derived::Undefined())) ;

    }

}

TEST (Library_Physics_Environment_Gravitational_Spherical, Clone)
{

    using library::physics::units::Length ;
    using library::physics::units::Time ;
    using library::physics::units::Derived ;
    using library::physics::environment::gravitational::Spherical ;

    {

        const Derived gravitationalParameter = { 1.0, Derived::Unit::GravitationalParameter(Length::Unit::Meter, Time::Unit::Second) } ;

        const Spherical spherical = { gravitationalParameter } ;

        EXPECT_NO_THROW(const Spherical* sphericalPtr = spherical.clone() ; delete sphericalPtr ;) ;

    }

}

TEST (Library_Physics_Environment_Gravitational_Spherical, GetFieldValueAt)
{

    using library::math::obj::Vector3d ;

    using library::physics::units::Length ;
    using library::physics::units::Time ;
    using library::physics::units::Derived ;
    using library::physics::time::Instant ;
    using library::physics::environment::gravitational::Spherical ;

    {

        const Derived gravitationalParameter = { 1.0, Derived::Unit::GravitationalParameter(Length::Unit::Meter, Time::Unit::Second) } ;

        const Spherical spherical = { gravitationalParameter } ;

        const Vector3d fieldValue = spherical.getFieldValueAt({ 1.0, 0.0, 0.0 }, Instant::J2000()) ;

        EXPECT_EQ(Vector3d(-1.0, 0.0, 0.0), fieldValue) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
