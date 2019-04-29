////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Environment/Magnetic/Dipole.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Environment/Magnetic/Dipole.hpp>

#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{
namespace environment
{
namespace magnetic
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using library::physics::units::Length ;
using library::physics::units::Mass ;
using library::physics::units::Time ;
using library::physics::units::Angle ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Dipole::Dipole                              (   const   Vector3d&                   aMagneticMoment                             )
                                :   Model(),
                                    magneticMoment_SI_(aMagneticMoment)
{

    if (!magneticMoment_SI_.isDefined())
    {
        throw library::core::error::runtime::Undefined("Magnetic moment") ;
    }

}

Dipole*                         Dipole::clone                               ( ) const
{
    return new Dipole(*this) ;
}

Vector3d                        Dipole::getFieldValueAt                     (   const   Vector3d&                   aPosition,
                                                                                const   Instant&                    anInstant                                   ) const
{

    (void) anInstant ; // Temporal invariance

    const Real r = aPosition.norm() ; // [m]

	const Vector3d magneticField = 1e-7 * (3.0 * (magneticMoment_SI_.dot(aPosition)) * aPosition - std::pow(r, 2.0) * magneticMoment_SI_) / std::pow(r, 5.0) ; // [T]
	// const Vector3d magneticField = (3.0 * (magneticMoment_SI_.dot(aPosition)) * aPosition - std::pow(r, 2.0) * magneticMoment_SI_) / std::pow(r, 5.0) ; // [T]

	return magneticField ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////