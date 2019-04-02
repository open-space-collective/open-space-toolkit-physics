////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Environment/Magnetic/Dipole.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Environment/Magnetic/Dipole.hpp>
#include <Library/Physics/Time/Instant.hpp>
#include <Library/Physics/Time/DateTime.hpp>
#include <Library/Physics/Time/Scale.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Physics_Environment_Magnetic_Dipole, Constructor)
{

    using library::math::obj::Vector3d ;

    using library::physics::environment::magnetic::Dipole ;

    {

        const Vector3d magneticMoment = { 0.0, 0.0, 1.0 } ;

        EXPECT_NO_THROW(Dipole dipole(magneticMoment)) ;

    }

    {

        EXPECT_ANY_THROW(Dipole(Vector3d::Undefined())) ;

    }

}

TEST (Library_Physics_Environment_Magnetic_Dipole, Clone)
{

    using library::math::obj::Vector3d ;

    using library::physics::environment::magnetic::Dipole ;

    {

        const Vector3d magneticMoment = { 0.0, 0.0, 1.0 } ;

        const Dipole dipole = { magneticMoment } ;

        EXPECT_NO_THROW(const Dipole* dipolePtr = dipole.clone() ; delete dipolePtr ;) ;

    }

}

TEST (Library_Physics_Environment_Magnetic_Dipole, GetFieldValueAt)
{

    using library::math::obj::Vector3d ;

    using library::physics::time::Instant ;
    using library::math::obj::Vector3d ;

    using library::physics::environment::magnetic::Dipole ;

    {

        const Vector3d magneticMoment = { 0.0, 0.0, 1.0 } ;

        const Dipole dipole = { magneticMoment } ;

        const Vector3d fieldValue = dipole.getFieldValueAt({ 1.0, 0.0, 0.0 }, Instant::J2000()) ;

        EXPECT_EQ(Vector3d(0.0, 0.0, 0.0), fieldValue) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////