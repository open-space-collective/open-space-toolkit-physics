////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Coordinate/Transform.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Coordinate/Transform.hpp>
#include <Library/Physics/Time/DateTime.hpp>
#include <Library/Physics/Time/Instant.hpp>
#include <Library/Physics/Units/Derived/Angle.hpp>

#include <Library/Mathematics/Geometry/Transformations/Rotations/RotationMatrix.hpp>
#include <Library/Mathematics/Geometry/Transformations/Rotations/RotationVector.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Physics_Coordinate_Transform, Constructor)
{

    using library::math::obj::Vector3d ;
    using library::math::geom::trf::rot::Quaternion ;
    
    using library::physics::time::Instant ;
    using library::physics::coord::Transform ;

    {

        const Instant instant = Instant::J2000() ;

        const Vector3d t_B_A = { +0.0, +0.0, +0.0 } ;
        const Vector3d v_B_A = { +0.0, +0.0, +0.0 } ;
        
        const Quaternion q_B_A = Quaternion::Unit() ;
        const Vector3d w_B_A_in_B = { +0.0, +0.0, +0.0 } ;

        EXPECT_NO_THROW(Transform(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B, Transform::Type::Active)) ;

    }

    {

        const Instant instant = Instant::J2000() ;

        const Vector3d t_B_A = { +0.0, +0.0, +0.0 } ;
        const Vector3d v_B_A = { +0.0, +0.0, +0.0 } ;
        
        const Quaternion q_B_A = Quaternion::Unit() ;
        const Vector3d w_B_A_in_B = { +0.0, +0.0, +0.0 } ;

        EXPECT_NO_THROW(Transform(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B, Transform::Type::Passive)) ;

    }

    {

        const Instant instant = Instant::J2000() ;

        const Vector3d t_B_A = { +0.0, +0.0, +0.0 } ;
        const Vector3d v_B_A = { +0.0, +0.0, +0.0 } ;
        
        const Quaternion q_B_A = Quaternion::Unit() ;
        const Vector3d w_B_A_in_B = { +0.0, +0.0, +0.0 } ;

        EXPECT_NO_THROW(Transform(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B, Transform::Type::Undefined)) ;

    }

}

TEST (Library_Physics_Coordinate_Transform, EqualToOperator)
{

    using library::math::obj::Vector3d ;
    using library::math::geom::trf::rot::Quaternion ;
    using library::math::geom::trf::rot::RotationVector ;
    
    using library::physics::units::Angle ;
    using library::physics::time::Scale ;
    using library::physics::time::Instant ;
    using library::physics::time::DateTime ;
    using library::physics::coord::Transform ;

    {

        const Instant instant = Instant::J2000() ;

        const Vector3d t_B_A = { +0.0, +0.0, +0.0 } ;
        const Vector3d v_B_A = { +0.0, +0.0, +0.0 } ;
        
        const Quaternion q_B_A = Quaternion::Unit() ;
        const Vector3d w_B_A_in_B = { +0.0, +0.0, +0.0 } ;

        EXPECT_TRUE(Transform(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B, Transform::Type::Active) == Transform(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B, Transform::Type::Active)) ;

        EXPECT_FALSE(Transform(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B, Transform::Type::Active) == Transform(Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::UTC), t_B_A, v_B_A, q_B_A, w_B_A_in_B, Transform::Type::Active)) ;
        EXPECT_FALSE(Transform(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B, Transform::Type::Active) == Transform(instant, { +0.0, +0.0, +1.0 }, v_B_A, q_B_A, w_B_A_in_B, Transform::Type::Active)) ;
        EXPECT_FALSE(Transform(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B, Transform::Type::Active) == Transform(instant, t_B_A, { +0.0, +0.0, +1.0 }, q_B_A, w_B_A_in_B, Transform::Type::Active)) ;
        EXPECT_FALSE(Transform(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B, Transform::Type::Active) == Transform(instant, t_B_A, v_B_A, Quaternion::RotationVector(RotationVector({ +0.0, +0.0, +1.0 }, Angle::Degrees(+1.0))), w_B_A_in_B, Transform::Type::Active)) ;
        EXPECT_FALSE(Transform(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B, Transform::Type::Active) == Transform(instant, t_B_A, v_B_A, q_B_A, { +0.0, +0.0, +1.0 }, Transform::Type::Active)) ;
        EXPECT_FALSE(Transform(instant, { +0.0, +0.0, +1.0 }, { +0.0, +0.0, +1.0 }, Quaternion::RotationVector(RotationVector({ +0.0, +0.0, +1.0 }, Angle::Degrees(+1.0))), { +0.0, +0.0, +1.0 }, Transform::Type::Active) == Transform(instant, { +0.0, +0.0, +1.0 }, { +0.0, +0.0, +1.0 }, Quaternion::RotationVector(RotationVector({ +0.0, +0.0, +1.0 }, Angle::Degrees(+1.0))), { +0.0, +0.0, +1.0 }, Transform::Type::Passive)) ;
        
        EXPECT_FALSE(Transform(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B, Transform::Type::Active) == Transform::Undefined()) ;
        EXPECT_FALSE(Transform::Undefined() == Transform(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B, Transform::Type::Active)) ;

    }

    {

        EXPECT_FALSE(Transform::Undefined() == Transform::Undefined()) ;

    }

}

TEST (Library_Physics_Coordinate_Transform, NotEqualToOperator)
{

    using library::math::obj::Vector3d ;
    using library::math::geom::trf::rot::Quaternion ;
    using library::math::geom::trf::rot::RotationVector ;
    
    using library::physics::units::Angle ;
    using library::physics::time::Scale ;
    using library::physics::time::Instant ;
    using library::physics::time::DateTime ;
    using library::physics::coord::Transform ;

    {

        const Instant instant = Instant::J2000() ;

        const Vector3d t_B_A = { +0.0, +0.0, +0.0 } ;
        const Vector3d v_B_A = { +0.0, +0.0, +0.0 } ;
        
        const Quaternion q_B_A = Quaternion::Unit() ;
        const Vector3d w_B_A_in_B = { +0.0, +0.0, +0.0 } ;

        EXPECT_FALSE(Transform(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B, Transform::Type::Active) != Transform(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B, Transform::Type::Active)) ;

        EXPECT_TRUE(Transform(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B, Transform::Type::Active) != Transform(Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::UTC), t_B_A, v_B_A, q_B_A, w_B_A_in_B, Transform::Type::Active)) ;
        EXPECT_TRUE(Transform(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B, Transform::Type::Active) != Transform(instant, { +0.0, +0.0, +1.0 }, v_B_A, q_B_A, w_B_A_in_B, Transform::Type::Active)) ;
        EXPECT_TRUE(Transform(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B, Transform::Type::Active) != Transform(instant, t_B_A, { +0.0, +0.0, +1.0 }, q_B_A, w_B_A_in_B, Transform::Type::Active)) ;
        EXPECT_TRUE(Transform(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B, Transform::Type::Active) != Transform(instant, t_B_A, v_B_A, Quaternion::RotationVector(RotationVector({ +0.0, +0.0, +1.0 }, Angle::Degrees(+1.0))), w_B_A_in_B, Transform::Type::Active)) ;
        EXPECT_TRUE(Transform(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B, Transform::Type::Active) != Transform(instant, t_B_A, v_B_A, q_B_A, { +0.0, +0.0, +1.0 }, Transform::Type::Active)) ;
        EXPECT_TRUE(Transform(instant, { +0.0, +0.0, +1.0 }, { +0.0, +0.0, +1.0 }, Quaternion::RotationVector(RotationVector({ +0.0, +0.0, +1.0 }, Angle::Degrees(+1.0))), { +0.0, +0.0, +1.0 }, Transform::Type::Active) != Transform(instant, { +0.0, +0.0, +1.0 }, { +0.0, +0.0, +1.0 }, Quaternion::RotationVector(RotationVector({ +0.0, +0.0, +1.0 }, Angle::Degrees(+1.0))), { +0.0, +0.0, +1.0 }, Transform::Type::Passive)) ;
        
        EXPECT_TRUE(Transform(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B, Transform::Type::Active) != Transform::Undefined()) ;
        EXPECT_TRUE(Transform::Undefined() != Transform(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B, Transform::Type::Active)) ;

    }

    {

        EXPECT_TRUE(Transform::Undefined() != Transform::Undefined()) ;

    }

}

TEST (Library_Physics_Coordinate_Transform, MultiplicationOperator)
{

    using library::core::types::Real ;
    
    using library::math::obj::Vector3d ;
    using library::math::geom::trf::rot::Quaternion ;
    using library::math::geom::trf::rot::RotationVector ;
    
    using library::physics::units::Angle ;
    using library::physics::time::Instant ;
    using library::physics::coord::Transform ;

    // Translation + Velocity + Rotation

    {

        const Instant instant = Instant::J2000() ;

        // A to B

        const Vector3d t_B_A = { +0.0, -1.0, +0.0 } ;
        const Vector3d v_B_A = { +0.0, -1.0, +0.0 } ;
        
        const Quaternion q_B_A = Quaternion::RotationVector(RotationVector({ +0.0, +0.0, +1.0 }, Angle::Degrees(+90.0))) ;
        const Vector3d w_B_A_in_B = Vector3d::Zero() ;

        const Transform transform_B_A = Transform::Passive(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B) ;

        // B to C

        const Vector3d t_C_B = { +0.0, -1.0, +0.0 } ;
        const Vector3d v_C_B = { +1.0, +0.0, +0.0 } ;
        
        const Quaternion q_C_B = Quaternion::RotationVector(RotationVector({ +0.0, +1.0, +0.0 }, Angle::Degrees(-90.0))) ;
        const Vector3d w_C_B_in_C = Vector3d::Zero() ;

        const Transform transform_C_B = Transform::Passive(instant, t_C_B, v_C_B, q_C_B, w_C_B_in_C) ;

        // A to C

        const Vector3d t_C_A = { +1.0, -1.0, +0.0 } ;
        const Vector3d v_C_A = { +0.0, +0.0, +0.0 } ;
        
        const Quaternion q_C_A = q_C_B * q_B_A ;
        const Vector3d w_C_A_in_C = Vector3d::Zero() ;

        const Transform transform_C_A = Transform::Passive(instant, t_C_A, v_C_A, q_C_A, w_C_A_in_C) ;

        // Comparison
        
        EXPECT_GT(1e-14, ((transform_C_B * transform_B_A).accessTranslation() - transform_C_A.accessTranslation()).norm()) ;
        EXPECT_GT(1e-14, ((transform_C_B * transform_B_A).getVelocity() - transform_C_A.getVelocity()).norm()) ;
        EXPECT_TRUE((transform_C_B * transform_B_A).accessOrientation().isNear(transform_C_A.accessOrientation(), Angle::Degrees(1e-7))) ;
        EXPECT_GT(1e-14, ((transform_C_B * transform_B_A).accessAngularVelocity() - transform_C_A.accessAngularVelocity()).norm()) ;

    }

}

TEST (Library_Physics_Coordinate_Transform, StreamOperator)
{

    using library::math::obj::Vector3d ;
    using library::math::geom::trf::rot::Quaternion ;
    using library::math::geom::trf::rot::RotationVector ;
    
    using library::physics::units::Angle ;
    using library::physics::time::Instant ;
    using library::physics::coord::Transform ;

    {

        const Instant instant = Instant::J2000() ;

        const Vector3d t_B_A = { +0.0, +0.0, +0.0 } ;
        const Vector3d v_B_A = { +0.0, +0.0, +0.0 } ;
        
        const Quaternion q_B_A = Quaternion::Unit() ;
        const Vector3d w_B_A_in_B = { +0.0, +0.0, +0.0 } ;

        testing::internal::CaptureStdout() ;

        EXPECT_NO_THROW(std::cout << Transform(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B, Transform::Type::Active) << std::endl) ;

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty()) ;

    }

}

TEST (Library_Physics_Coordinate_Transform, IsDefined)
{

    using library::math::obj::Vector3d ;
    using library::math::geom::trf::rot::Quaternion ;
    using library::math::geom::trf::rot::RotationVector ;
    
    using library::physics::units::Angle ;
    using library::physics::time::Instant ;
    using library::physics::coord::Transform ;

    {

        const Instant instant = Instant::J2000() ;

        const Vector3d t_B_A = { +0.0, +0.0, +0.0 } ;
        const Vector3d v_B_A = { +0.0, +0.0, +0.0 } ;
        
        const Quaternion q_B_A = Quaternion::Unit() ;
        const Vector3d w_B_A_in_B = { +0.0, +0.0, +0.0 } ;

        EXPECT_TRUE(Transform(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B, Transform::Type::Active).isDefined()) ;

    }

    {

        EXPECT_FALSE(Transform::Undefined().isDefined()) ;

    }
    
}

TEST (Library_Physics_Coordinate_Transform, IsIdentity)
{

    using library::math::obj::Vector3d ;
    using library::math::geom::trf::rot::Quaternion ;
    using library::math::geom::trf::rot::RotationVector ;
    
    using library::physics::units::Angle ;
    using library::physics::time::Instant ;
    using library::physics::coord::Transform ;

    {

        const Instant instant = Instant::J2000() ;

        const Vector3d t_B_A = Vector3d::Zero() ;
        const Vector3d v_B_A = Vector3d::Zero() ;
        
        const Quaternion q_B_A = Quaternion::Unit() ;
        const Vector3d w_B_A_in_B = Vector3d::Zero() ;

        EXPECT_TRUE(Transform(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B, Transform::Type::Active).isIdentity()) ;
        EXPECT_TRUE(Transform(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B, Transform::Type::Passive).isIdentity()) ;

    }

    {

        const Instant instant = Instant::J2000() ;

        const Vector3d t_B_A = { 0.0, 0.0, 1.0 } ;
        const Vector3d v_B_A = Vector3d::Zero() ;
        
        const Quaternion q_B_A = Quaternion::Unit() ;
        const Vector3d w_B_A_in_B = Vector3d::Zero() ;

        EXPECT_FALSE(Transform(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B, Transform::Type::Active).isIdentity()) ;
        EXPECT_FALSE(Transform(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B, Transform::Type::Passive).isIdentity()) ;

    }

    {

        EXPECT_ANY_THROW(Transform::Undefined().isIdentity()) ;

    }
    
}

TEST (Library_Physics_Coordinate_Transform, AccessInstant)
{

    using library::math::obj::Vector3d ;
    using library::math::geom::trf::rot::Quaternion ;
    using library::math::geom::trf::rot::RotationVector ;
    
    using library::physics::units::Angle ;
    using library::physics::time::Instant ;
    using library::physics::coord::Transform ;

    {

        const Instant instant = Instant::J2000() ;

        const Vector3d t_B_A = { +1.0, +2.0, +3.0 } ;
        const Vector3d v_B_A = { +4.0, +5.0, +6.0 } ;
        
        const Quaternion q_B_A = Quaternion::Unit() ;
        const Vector3d w_B_A_in_B = { +7.0, +8.0, +9.0 } ;

        EXPECT_EQ(instant, Transform(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B, Transform::Type::Passive).accessInstant()) ;

    }

    {

        EXPECT_ANY_THROW(Transform::Undefined().accessInstant()) ;

    }
    
}

TEST (Library_Physics_Coordinate_Transform, AccessTranslation)
{

    using library::math::obj::Vector3d ;
    using library::math::geom::trf::rot::Quaternion ;
    using library::math::geom::trf::rot::RotationVector ;
    
    using library::physics::units::Angle ;
    using library::physics::time::Instant ;
    using library::physics::coord::Transform ;

    {

        const Instant instant = Instant::J2000() ;

        const Vector3d t_B_A = { +1.0, +2.0, +3.0 } ;
        const Vector3d v_B_A = { +4.0, +5.0, +6.0 } ;
        
        const Quaternion q_B_A = Quaternion::Unit() ;
        const Vector3d w_B_A_in_B = { +7.0, +8.0, +9.0 } ;

        EXPECT_EQ(t_B_A, Transform(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B, Transform::Type::Passive).accessTranslation()) ;

    }

    {

        EXPECT_ANY_THROW(Transform::Undefined().accessTranslation()) ;

    }
    
}

TEST (Library_Physics_Coordinate_Transform, AccessVelocity)
{

    using library::math::obj::Vector3d ;
    using library::math::geom::trf::rot::Quaternion ;
    using library::math::geom::trf::rot::RotationVector ;
    
    using library::physics::units::Angle ;
    using library::physics::time::Instant ;
    using library::physics::coord::Transform ;

    {

        const Instant instant = Instant::J2000() ;

        const Vector3d t_B_A = { +1.0, +2.0, +3.0 } ;
        const Vector3d v_B_A = { +4.0, +5.0, +6.0 } ;
        
        const Quaternion q_B_A = Quaternion::Unit() ;
        const Vector3d w_B_A_in_B = { +7.0, +8.0, +9.0 } ;

        EXPECT_EQ(v_B_A, Transform(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B, Transform::Type::Passive).accessVelocity()) ;

    }

    {

        EXPECT_ANY_THROW(Transform::Undefined().accessVelocity()) ;

    }
    
}

TEST (Library_Physics_Coordinate_Transform, AccessOrientation)
{

    using library::math::obj::Vector3d ;
    using library::math::geom::trf::rot::Quaternion ;
    using library::math::geom::trf::rot::RotationVector ;
    
    using library::physics::units::Angle ;
    using library::physics::time::Instant ;
    using library::physics::coord::Transform ;

    {

        const Instant instant = Instant::J2000() ;

        const Vector3d t_B_A = { +1.0, +2.0, +3.0 } ;
        const Vector3d v_B_A = { +4.0, +5.0, +6.0 } ;
        
        const Quaternion q_B_A = Quaternion::Unit() ;
        const Vector3d w_B_A_in_B = { +7.0, +8.0, +9.0 } ;

        EXPECT_EQ(q_B_A, Transform(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B, Transform::Type::Passive).accessOrientation()) ;

    }

    {

        EXPECT_ANY_THROW(Transform::Undefined().accessOrientation()) ;

    }
    
}

TEST (Library_Physics_Coordinate_Transform, AccessAngularVelocity)
{

    using library::math::obj::Vector3d ;
    using library::math::geom::trf::rot::Quaternion ;
    using library::math::geom::trf::rot::RotationVector ;
    
    using library::physics::units::Angle ;
    using library::physics::time::Instant ;
    using library::physics::coord::Transform ;

    {

        const Instant instant = Instant::J2000() ;

        const Vector3d t_B_A = { +1.0, +2.0, +3.0 } ;
        const Vector3d v_B_A = { +4.0, +5.0, +6.0 } ;
        
        const Quaternion q_B_A = Quaternion::Unit() ;
        const Vector3d w_B_A_in_B = { +7.0, +8.0, +9.0 } ;

        EXPECT_EQ(w_B_A_in_B, Transform(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B, Transform::Type::Passive).accessAngularVelocity()) ;

    }

    {

        EXPECT_ANY_THROW(Transform::Undefined().accessAngularVelocity()) ;

    }
    
}

TEST (Library_Physics_Coordinate_Transform, GetInstant)
{

    using library::math::obj::Vector3d ;
    using library::math::geom::trf::rot::Quaternion ;
    using library::math::geom::trf::rot::RotationVector ;
    
    using library::physics::units::Angle ;
    using library::physics::time::Instant ;
    using library::physics::coord::Transform ;

    {

        const Instant instant = Instant::J2000() ;

        const Vector3d t_B_A = { +1.0, +2.0, +3.0 } ;
        const Vector3d v_B_A = { +4.0, +5.0, +6.0 } ;
        
        const Quaternion q_B_A = Quaternion::Unit() ;
        const Vector3d w_B_A_in_B = { +7.0, +8.0, +9.0 } ;

        EXPECT_EQ(instant, Transform(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B, Transform::Type::Passive).getInstant()) ;

    }

    {

        EXPECT_ANY_THROW(Transform::Undefined().getInstant()) ;

    }
    
}

TEST (Library_Physics_Coordinate_Transform, GetTranslation)
{

    using library::math::obj::Vector3d ;
    using library::math::geom::trf::rot::Quaternion ;
    using library::math::geom::trf::rot::RotationVector ;
    
    using library::physics::units::Angle ;
    using library::physics::time::Instant ;
    using library::physics::coord::Transform ;

    {

        const Instant instant = Instant::J2000() ;

        const Vector3d t_B_A = { +1.0, +2.0, +3.0 } ;
        const Vector3d v_B_A = { +4.0, +5.0, +6.0 } ;
        
        const Quaternion q_B_A = Quaternion::Unit() ;
        const Vector3d w_B_A_in_B = { +7.0, +8.0, +9.0 } ;

        EXPECT_EQ(t_B_A, Transform(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B, Transform::Type::Passive).getTranslation()) ;

    }

    {

        EXPECT_ANY_THROW(Transform::Undefined().getTranslation()) ;

    }
    
}

TEST (Library_Physics_Coordinate_Transform, GetVelocity)
{

    using library::math::obj::Vector3d ;
    using library::math::geom::trf::rot::Quaternion ;
    using library::math::geom::trf::rot::RotationVector ;
    
    using library::physics::units::Angle ;
    using library::physics::time::Instant ;
    using library::physics::coord::Transform ;

    {

        const Instant instant = Instant::J2000() ;

        const Vector3d t_B_A = { +1.0, +2.0, +3.0 } ;
        const Vector3d v_B_A = { +4.0, +5.0, +6.0 } ;
        
        const Quaternion q_B_A = Quaternion::Unit() ;
        const Vector3d w_B_A_in_B = { +7.0, +8.0, +9.0 } ;

        EXPECT_EQ(v_B_A, Transform(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B, Transform::Type::Passive).getVelocity()) ;

    }

    {

        EXPECT_ANY_THROW(Transform::Undefined().getVelocity()) ;

    }
    
}

TEST (Library_Physics_Coordinate_Transform, GetOrientation)
{

    using library::math::obj::Vector3d ;
    using library::math::geom::trf::rot::Quaternion ;
    using library::math::geom::trf::rot::RotationVector ;
    
    using library::physics::units::Angle ;
    using library::physics::time::Instant ;
    using library::physics::coord::Transform ;

    {

        const Instant instant = Instant::J2000() ;

        const Vector3d t_B_A = { +1.0, +2.0, +3.0 } ;
        const Vector3d v_B_A = { +4.0, +5.0, +6.0 } ;
        
        const Quaternion q_B_A = Quaternion::Unit() ;
        const Vector3d w_B_A_in_B = { +7.0, +8.0, +9.0 } ;

        EXPECT_EQ(q_B_A, Transform(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B, Transform::Type::Passive).getOrientation()) ;

    }

    {

        EXPECT_ANY_THROW(Transform::Undefined().getOrientation()) ;

    }
    
}

TEST (Library_Physics_Coordinate_Transform, GetAngularVelocity)
{

    using library::math::obj::Vector3d ;
    using library::math::geom::trf::rot::Quaternion ;
    using library::math::geom::trf::rot::RotationVector ;
    
    using library::physics::units::Angle ;
    using library::physics::time::Instant ;
    using library::physics::coord::Transform ;

    {

        const Instant instant = Instant::J2000() ;

        const Vector3d t_B_A = { +1.0, +2.0, +3.0 } ;
        const Vector3d v_B_A = { +4.0, +5.0, +6.0 } ;
        
        const Quaternion q_B_A = Quaternion::Unit() ;
        const Vector3d w_B_A_in_B = { +7.0, +8.0, +9.0 } ;

        EXPECT_EQ(w_B_A_in_B, Transform(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B, Transform::Type::Passive).getAngularVelocity()) ;

    }

    {

        EXPECT_ANY_THROW(Transform::Undefined().getAngularVelocity()) ;

    }
    
}

TEST (Library_Physics_Coordinate_Transform, GetInverse)
{

    using library::core::types::Real ;

    using library::math::obj::Vector3d ;
    using library::math::geom::trf::rot::Quaternion ;
    using library::math::geom::trf::rot::RotationVector ;
    
    using library::physics::units::Angle ;
    using library::physics::time::Instant ;
    using library::physics::coord::Transform ;

    {

        for (auto idx = 1; idx < 10000; ++idx)
        {

            const Vector3d t_A_B = { std::cos(+1.0 * idx), std::cos(+2.0 * idx), std::cos(+3.0 * idx) } ;
            const Vector3d v_A_B = { std::cos(+4.0 * idx), std::cos(+5.0 * idx), std::cos(+6.0 * idx) } ;
            
            const Quaternion q_B_A = Quaternion::RotationVector(RotationVector(Vector3d(std::cos(+0.1 * idx) * std::sin(+0.3 * idx), std::cos(+0.2 * idx) * std::sin(+0.2 * idx), std::cos(+0.3 * idx) * std::sin(+0.1 * idx)).normalized(), Angle::Degrees(0.1 * idx))) ;
            const Vector3d w_B_A_in_B = { std::cos(+7.0 * idx), std::cos(+8.0 * idx), std::cos(+9.0 * idx) } ;

            const Transform transform = Transform::Passive(Instant::J2000(), t_A_B, v_A_B, q_B_A, w_B_A_in_B) ;

            EXPECT_TRUE(transform.getInverse().getInverse().accessTranslation().isNear(transform.accessTranslation(), 1e-14)) ;
            EXPECT_TRUE(transform.getInverse().getInverse().accessVelocity().isNear(transform.accessVelocity(), 1e-14)) ;
            EXPECT_TRUE(transform.getInverse().getInverse().accessOrientation().isNear(transform.accessOrientation(), Angle::Radians(1e-7))) ;
            EXPECT_TRUE(transform.getInverse().getInverse().accessAngularVelocity().isNear(transform.accessAngularVelocity(), 1e-14)) ;

        }

    }

    {

        EXPECT_ANY_THROW(Transform::Undefined().getInverse()) ;

    }

}

TEST (Library_Physics_Coordinate_Transform, ApplyToPosition)
{

    using library::core::types::Real ;

    using library::math::obj::Vector3d ;
    using library::math::geom::trf::rot::Quaternion ;
    using library::math::geom::trf::rot::RotationVector ;
    
    using library::physics::units::Angle ;
    using library::physics::time::Instant ;
    using library::physics::coord::Transform ;

    // Identity

    {

        const Instant instant = Instant::J2000() ;

        const Transform transform_B_A = Transform::Identity(instant) ;

        const Vector3d x_A = { +0.0, +0.0, +0.0 } ;

        const Vector3d x_B = transform_B_A.applyToPosition(x_A) ;

        EXPECT_TRUE(x_B.isNear(x_A, 1e-14)) ;

    }

    // Translation

    {

        const Instant instant = Instant::J2000() ;

        const Vector3d t_B_A = { +0.0, -1.0, +0.0 } ;
        const Vector3d v_B_A = Vector3d::Zero() ;
        
        const Quaternion q_B_A = Quaternion::Unit() ;
        const Vector3d w_B_A_in_B = Vector3d::Zero() ;

        const Transform transform_B_A = Transform::Passive(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B) ;

        const Vector3d x_A = { +0.0, +1.0, +0.0 } ;

        const Vector3d x_B = transform_B_A.applyToPosition(x_A) ;

        EXPECT_TRUE(x_B.isNear(Vector3d(+0.0, +0.0, +0.0), 1e-14)) ;

    }

    // Rotation

    {

        const Instant instant = Instant::J2000() ;

        const Vector3d t_B_A = Vector3d::Zero() ;
        const Vector3d v_B_A = Vector3d::Zero() ;
        
        const Quaternion q_B_A = Quaternion::RotationVector(RotationVector({ +0.0, +0.0, +1.0 }, Angle::Degrees(+90.0))) ;
        const Vector3d w_B_A_in_B = Vector3d::Zero() ;

        const Transform transform_B_A = Transform::Passive(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B) ;

        const Vector3d x_A = { +0.0, +1.0, +0.0 } ;

        const Vector3d x_B = transform_B_A.applyToPosition(x_A) ;

        EXPECT_TRUE(x_B.isNear(Vector3d(+1.0, +0.0, +0.0), 1e-14)) ;

    }

    // Translation + Rotation

    {

        const Instant instant = Instant::J2000() ;

        const Vector3d t_B_A = { +0.0, -1.0, +0.0 } ;
        const Vector3d v_B_A = Vector3d::Zero() ;
        
        const Quaternion q_B_A = Quaternion::RotationVector(RotationVector({ +0.0, +0.0, +1.0 }, Angle::Degrees(+90.0))) ;
        const Vector3d w_B_A_in_B = Vector3d::Zero() ;

        const Transform transform_B_A = Transform::Passive(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B) ;

        const Vector3d x_A = { +0.0, +2.0, +0.0 } ;

        const Vector3d x_B = transform_B_A.applyToPosition(x_A) ;

        EXPECT_TRUE(x_B.isNear(Vector3d(+1.0, +0.0, +0.0), 1e-14)) ;

    }

    // Translation + Velocity

    {

        const Instant instant = Instant::J2000() ;

        const Vector3d t_B_A = { +0.0, -1.0, +0.0 } ;
        const Vector3d v_B_A = { +0.0, -1.0, +0.0 } ;
        
        const Quaternion q_B_A = Quaternion::Unit() ;
        const Vector3d w_B_A_in_B = Vector3d::Zero() ;

        const Transform transform_B_A = Transform::Passive(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B) ;

        const Vector3d x_A = { +0.0, +1.0, +0.0 } ;

        const Vector3d x_B = transform_B_A.applyToPosition(x_A) ;

        EXPECT_TRUE(x_B.isNear(Vector3d(+0.0, +0.0, +0.0), 1e-14)) ;

    }

    // Translation + Velocity + Rotation

    {

        const Instant instant = Instant::J2000() ;

        const Vector3d t_B_A = { +0.0, -1.0, +0.0 } ;
        const Vector3d v_B_A = { +0.0, -1.0, +0.0 } ;
        
        const Quaternion q_B_A = Quaternion::RotationVector(RotationVector({ +0.0, +0.0, +1.0 }, Angle::Degrees(+90.0))) ;
        const Vector3d w_B_A_in_B = Vector3d::Zero() ;

        const Transform transform_B_A = Transform::Passive(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B) ;

        const Vector3d x_A = { +0.0, +2.0, +0.0 } ;

        const Vector3d x_B = transform_B_A.applyToPosition(x_A) ;

        EXPECT_TRUE(x_B.isNear(Vector3d(+1.0, +0.0, +0.0), 1e-14)) ;

    }

    // Translation + Velocity + Rotation + Angular Velocity

    {

        const Instant instant = Instant::J2000() ;

        const Vector3d t_B_A = { +0.0, -1.0, +0.0 } ;
        const Vector3d v_B_A = { +0.0, -1.0, +0.0 } ;
        
        const Quaternion q_B_A = Quaternion::RotationVector(RotationVector({ +0.0, +0.0, +1.0 }, Angle::Degrees(+90.0))) ;
        const Vector3d w_B_A_in_B = { +0.0, +0.0, +1.0 } ;

        const Transform transform_B_A = Transform::Passive(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B) ;

        const Vector3d x_A = { +0.0, +2.0, +0.0 } ;

        const Vector3d x_B = transform_B_A.applyToPosition(x_A) ;

        EXPECT_TRUE(x_B.isNear(Vector3d(+1.0, +0.0, +0.0), 1e-14)) ;

    }

}

TEST (Library_Physics_Coordinate_Transform, ApplyToVelocity)
{

    using library::core::types::Real ;
    
    using library::math::obj::Vector3d ;
    using library::math::geom::trf::rot::Quaternion ;
    using library::math::geom::trf::rot::RotationVector ;
    
    using library::physics::units::Angle ;
    using library::physics::time::Instant ;
    using library::physics::coord::Transform ;

    // Identity

    {

        const Instant instant = Instant::J2000() ;

        const Transform transform_B_A = Transform::Identity(instant) ;

        const Vector3d x_A = { +0.0, +0.0, +0.0 } ;
        const Vector3d v_A = { +0.0, +0.0, +0.0 } ;

        const Vector3d v_B = transform_B_A.applyToVelocity(x_A, v_A) ;

        EXPECT_TRUE(v_B.isNear(v_A, 1e-14)) ;

    }

    // Translation

    {

        const Instant instant = Instant::J2000() ;

        const Vector3d t_B_A = { +0.0, -1.0, +0.0 } ;
        const Vector3d v_B_A = Vector3d::Zero() ;
        
        const Quaternion q_B_A = Quaternion::Unit() ;
        const Vector3d w_B_A_in_B = Vector3d::Zero() ;

        const Transform transform_B_A = Transform::Passive(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B) ;

        const Vector3d x_A = { +0.0, +0.0, +0.0 } ;
        const Vector3d v_A = { +0.0, +1.0, +0.0 } ;

        const Vector3d v_B = transform_B_A.applyToVelocity(x_A, v_A) ;

        EXPECT_TRUE(v_B.isNear(Vector3d(+0.0, +1.0, +0.0), 1e-14)) ;

    }

    // Rotation

    {

        const Instant instant = Instant::J2000() ;

        const Vector3d t_B_A = Vector3d::Zero() ;
        const Vector3d v_B_A = Vector3d::Zero() ;
        
        const Quaternion q_B_A = Quaternion::RotationVector(RotationVector({ +0.0, +0.0, +1.0 }, Angle::Degrees(+90.0))) ;
        const Vector3d w_B_A_in_B = Vector3d::Zero() ;

        const Transform transform_B_A = Transform::Passive(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B) ;

        const Vector3d x_A = { +0.0, +0.0, +0.0 } ;
        const Vector3d v_A = { +0.0, +1.0, +0.0 } ;

        const Vector3d v_B = transform_B_A.applyToVelocity(x_A, v_A) ;

        EXPECT_TRUE(v_B.isNear(Vector3d(+1.0, +0.0, +0.0), 1e-14)) ;

    }

    // Translation + Rotation

    {

        const Instant instant = Instant::J2000() ;

        const Vector3d t_B_A = { +0.0, -1.0, +0.0 } ;
        const Vector3d v_B_A = Vector3d::Zero() ;
        
        const Quaternion q_B_A = Quaternion::RotationVector(RotationVector({ +0.0, +0.0, +1.0 }, Angle::Degrees(+90.0))) ;
        const Vector3d w_B_A_in_B = Vector3d::Zero() ;

        const Transform transform_B_A = Transform::Passive(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B) ;

        const Vector3d x_A = { +0.0, +2.0, +0.0 } ;
        const Vector3d v_A = { +0.0, +1.0, +0.0 } ;

        const Vector3d v_B = transform_B_A.applyToVelocity(x_A, v_A) ;

        EXPECT_TRUE(v_B.isNear(Vector3d(+1.0, +0.0, +0.0), 1e-14)) ;

    }

    // Translation + Velocity

    {

        const Instant instant = Instant::J2000() ;

        const Vector3d t_B_A = { +0.0, -1.0, +0.0 } ;
        const Vector3d v_B_A = { +0.0, -1.0, +0.0 } ;
        
        const Quaternion q_B_A = Quaternion::Unit() ;
        const Vector3d w_B_A_in_B = Vector3d::Zero() ;

        const Transform transform_B_A = Transform::Passive(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B) ;

        const Vector3d x_A = { +0.0, +2.0, +0.0 } ;
        const Vector3d v_A = { +0.0, +2.0, +0.0 } ;

        const Vector3d v_B = transform_B_A.applyToVelocity(x_A, v_A) ;

        EXPECT_TRUE(v_B.isNear(Vector3d(+0.0, +1.0, +0.0), 1e-14)) ;

    }

    // Translation + Velocity + Rotation

    {

        const Instant instant = Instant::J2000() ;

        const Vector3d t_B_A = { +0.0, -1.0, +0.0 } ;
        const Vector3d v_B_A = { +0.0, -1.0, +0.0 } ;
        
        const Quaternion q_B_A = Quaternion::RotationVector(RotationVector({ +0.0, +0.0, +1.0 }, Angle::Degrees(+90.0))) ;
        const Vector3d w_B_A_in_B = Vector3d::Zero() ;

        const Transform transform_B_A = Transform::Passive(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B) ;

        const Vector3d x_A = { +0.0, +2.0, +0.0 } ;
        const Vector3d v_A = { +0.0, +2.0, +0.0 } ;

        const Vector3d v_B = transform_B_A.applyToVelocity(x_A, v_A) ;

        EXPECT_TRUE(v_B.isNear(Vector3d(+1.0, +0.0, +0.0), 1e-14)) ;

    }

    // Translation + Velocity + Rotation + Angular Velocity

    {

        const Instant instant = Instant::J2000() ;

        const Vector3d t_B_A = { +0.0, -1.0, +0.0 } ;
        const Vector3d v_B_A = { +0.0, -1.0, +0.0 } ;
        
        const Quaternion q_B_A = Quaternion::RotationVector(RotationVector({ +0.0, +0.0, +1.0 }, Angle::Degrees(+90.0))) ;
        const Vector3d w_B_A_in_B = { +0.0, +0.0, +1.0 } ;

        const Transform transform_B_A = Transform::Passive(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B) ;

        const Vector3d x_A = { +0.0, +2.0, +0.0 } ;
        const Vector3d v_A = { +0.0, +2.0, +0.0 } ;

        const Vector3d v_B = transform_B_A.applyToVelocity(x_A, v_A) ;

        EXPECT_TRUE(v_B.isNear(Vector3d(+1.0, -1.0, +0.0), 1e-14)) ;

    }

}

TEST (Library_Physics_Coordinate_Transform, ApplyToVector)
{

    using library::core::types::Real ;
    
    using library::math::obj::Vector3d ;
    using library::math::geom::trf::rot::Quaternion ;
    using library::math::geom::trf::rot::RotationVector ;
    
    using library::physics::units::Angle ;
    using library::physics::time::Instant ;
    using library::physics::coord::Transform ;

    // Identity

    {

        const Instant instant = Instant::J2000() ;

        const Transform transform_B_A = Transform::Identity(instant) ;

        const Vector3d v_A = { +0.0, +0.0, +0.0 } ;

        const Vector3d v_B = transform_B_A.applyToVector(v_A) ;

        EXPECT_TRUE(v_B.isNear(v_A, 1e-14)) ;

    }

    // Translation

    {

        const Instant instant = Instant::J2000() ;

        const Vector3d t_B_A = { +0.0, -1.0, +0.0 } ;
        const Vector3d v_B_A = Vector3d::Zero() ;
        
        const Quaternion q_B_A = Quaternion::Unit() ;
        const Vector3d w_B_A_in_B = Vector3d::Zero() ;

        const Transform transform_B_A = Transform::Passive(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B) ;

        const Vector3d v_A = { +0.0, +1.0, +0.0 } ;

        const Vector3d v_B = transform_B_A.applyToVector(v_A) ;

        EXPECT_TRUE(v_B.isNear(v_A, 1e-14)) ;

    }

    // Rotation

    {

        const Instant instant = Instant::J2000() ;

        const Vector3d t_B_A = Vector3d::Zero() ;
        const Vector3d v_B_A = Vector3d::Zero() ;
        
        const Quaternion q_B_A = Quaternion::RotationVector(RotationVector({ +0.0, +0.0, +1.0 }, Angle::Degrees(+90.0))) ;
        const Vector3d w_B_A_in_B = Vector3d::Zero() ;

        const Transform transform_B_A = Transform::Passive(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B) ;

        const Vector3d v_A = { +0.0, +1.0, +0.0 } ;

        const Vector3d v_B = transform_B_A.applyToVector(v_A) ;

        EXPECT_TRUE(v_B.isNear(Vector3d(+1.0, +0.0, +0.0), 1e-14)) ;

    }

    // Translation + Rotation

    {

        const Instant instant = Instant::J2000() ;

        const Vector3d t_B_A = { +0.0, -1.0, +0.0 } ;
        const Vector3d v_B_A = Vector3d::Zero() ;
        
        const Quaternion q_B_A = Quaternion::RotationVector(RotationVector({ +0.0, +0.0, +1.0 }, Angle::Degrees(+90.0))) ;
        const Vector3d w_B_A_in_B = Vector3d::Zero() ;

        const Transform transform_B_A = Transform::Passive(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B) ;

        const Vector3d v_A = { +0.0, +1.0, +0.0 } ;

        const Vector3d v_B = transform_B_A.applyToVector(v_A) ;

        EXPECT_TRUE(v_B.isNear(Vector3d(+1.0, +0.0, +0.0), 1e-14)) ;

    }

    // Translation + Velocity

    {

        const Instant instant = Instant::J2000() ;

        const Vector3d t_B_A = { +0.0, -1.0, +0.0 } ;
        const Vector3d v_B_A = { +0.0, -1.0, +0.0 } ;
        
        const Quaternion q_B_A = Quaternion::Unit() ;
        const Vector3d w_B_A_in_B = Vector3d::Zero() ;

        const Transform transform_B_A = Transform::Passive(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B) ;

        const Vector3d v_A = { +0.0, +2.0, +0.0 } ;

        const Vector3d v_B = transform_B_A.applyToVector(v_A) ;

        EXPECT_TRUE(v_B.isNear(Vector3d(+0.0, +2.0, +0.0), 1e-14)) ;

    }

    // Translation + Velocity + Rotation

    {

        const Instant instant = Instant::J2000() ;

        const Vector3d t_B_A = { +0.0, -1.0, +0.0 } ;
        const Vector3d v_B_A = { +0.0, -1.0, +0.0 } ;
        
        const Quaternion q_B_A = Quaternion::RotationVector(RotationVector({ +0.0, +0.0, +1.0 }, Angle::Degrees(+90.0))) ;
        const Vector3d w_B_A_in_B = Vector3d::Zero() ;

        const Transform transform_B_A = Transform::Passive(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B) ;

        const Vector3d v_A = { +0.0, +2.0, +0.0 } ;

        const Vector3d v_B = transform_B_A.applyToVector(v_A) ;

        EXPECT_TRUE(v_B.isNear(Vector3d(+2.0, +0.0, +0.0), 1e-14)) ;

    }

    // Translation + Velocity + Rotation + Angular Velocity

    {

        const Instant instant = Instant::J2000() ;

        const Vector3d t_B_A = { +0.0, -1.0, +0.0 } ;
        const Vector3d v_B_A = { +0.0, -1.0, +0.0 } ;
        
        const Quaternion q_B_A = Quaternion::RotationVector(RotationVector({ +0.0, +0.0, +1.0 }, Angle::Degrees(+90.0))) ;
        const Vector3d w_B_A_in_B = { +0.0, +0.0, +1.0 } ;

        const Transform transform_B_A = Transform::Passive(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B) ;

        const Vector3d v_A = { +0.0, +2.0, +0.0 } ;

        const Vector3d v_B = transform_B_A.applyToVector(v_A) ;

        EXPECT_TRUE(v_B.isNear(Vector3d(+2.0, +0.0, +0.0), 1e-14)) ;

    }
    
}

TEST (Library_Physics_Coordinate_Transform, Undefined)
{

    using library::physics::coord::Transform ;

    {

        EXPECT_NO_THROW(Transform::Undefined()) ;
        
        EXPECT_FALSE(Transform::Undefined().isDefined()) ;

    }
    
}

TEST (Library_Physics_Coordinate_Transform, Identity)
{

    using library::physics::time::Instant ;
    using library::physics::coord::Transform ;

    {

        const Instant instant = Instant::J2000() ;

        EXPECT_NO_THROW(Transform::Identity(instant)) ;

        EXPECT_EQ(Transform::Identity(instant), Transform::Identity(instant).getInverse()) ;

    }
    
}

TEST (Library_Physics_Coordinate_Transform, Active)
{

    using library::math::obj::Vector3d ;
    using library::math::geom::trf::rot::Quaternion ;
    
    using library::physics::time::Instant ;
    using library::physics::coord::Transform ;

    {

        const Instant instant = Instant::J2000() ;

        const Vector3d t_B_A = { +0.0, +0.0, +0.0 } ;
        const Vector3d v_B_A = { +0.0, +0.0, +0.0 } ;
        
        const Quaternion q_B_A = Quaternion::Unit() ;
        const Vector3d w_B_A_in_B = { +0.0, +0.0, +0.0 } ;

        EXPECT_EQ(Transform(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B, Transform::Type::Active), Transform::Active(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B)) ;

    }
    
}

TEST (Library_Physics_Coordinate_Transform, Passive)
{

    using library::math::obj::Vector3d ;
    using library::math::geom::trf::rot::Quaternion ;
    
    using library::physics::time::Instant ;
    using library::physics::coord::Transform ;

    {

        const Instant instant = Instant::J2000() ;

        const Vector3d t_B_A = { +0.0, +0.0, +0.0 } ;
        const Vector3d v_B_A = { +0.0, +0.0, +0.0 } ;
        
        const Quaternion q_B_A = Quaternion::Unit() ;
        const Vector3d w_B_A_in_B = { +0.0, +0.0, +0.0 } ;

        EXPECT_EQ(Transform(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B, Transform::Type::Passive), Transform::Passive(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B)) ;

    }
    
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Physics_Coordinate_Transform, Test_1)
{

    using library::core::types::Real ;

    using library::math::obj::Vector3d ;
    using library::math::geom::trf::rot::Quaternion ;
    
    using library::physics::time::Instant ;
    using library::physics::coord::Transform ;

    {

        const Instant instant = Instant::J2000() ;

        const Vector3d t_A_G = { +0.0, -1.0, +0.0 } ;
        const Vector3d v_A_G = { +0.0, +0.0, +0.0 } ;
        
        const Quaternion q_A_G = Quaternion::XYZS(0.0, 0.0, 0.707106781186547, 0.707106781186548).toNormalized() ;
        const Vector3d w_A_G_in_A = { +0.0, +0.0, +0.0 } ;

        const Transform transform_A_G = { instant, t_A_G, v_A_G, q_A_G, w_A_G_in_A, Transform::Type::Passive } ;

        {

            const Vector3d x_G = { +0.0, +1.0, +0.0 } ;
            const Vector3d x_A = transform_A_G.applyToPosition(x_G) ;

            EXPECT_TRUE(x_A.isNear(Vector3d(+0.0, +0.0, +0.0), 1e-5)) << x_A.toString() ;

        }

        {

            const Vector3d x_G = { +0.0, +2.0, +0.0 } ;
            const Vector3d x_A = transform_A_G.applyToPosition(x_G) ;

            EXPECT_TRUE(x_A.isNear(Vector3d(+1.0, +0.0, +0.0), 1e-5)) << x_A.toString() ;

        }
        
        const Vector3d t_B_G = { -1.0, +0.0, +0.0 } ;
        const Vector3d v_B_G = { +0.0, +0.0, +0.0 } ;
        
        const Quaternion q_B_G = Quaternion::XYZS(0.0, 0.0, -0.707106781186547, 0.707106781186548).toNormalized() ;
        const Vector3d w_B_G_in_B = { +0.0, +0.0, +0.0 } ;

        const Transform transform_B_G = { instant, t_B_G, v_B_G, q_B_G, w_B_G_in_B, Transform::Type::Passive } ;

        {

            const Vector3d x_G = { +1.0, +0.0, +0.0 } ;
            const Vector3d x_B = transform_B_G.applyToPosition(x_G) ;

            EXPECT_TRUE(x_B.isNear(Vector3d(+0.0, +0.0, +0.0), 1e-5)) << x_B.toString() ;

        }

        {

            const Vector3d x_G = { +2.0, +0.0, +0.0 } ;
            const Vector3d x_B = transform_B_G.applyToPosition(x_G) ;

            EXPECT_TRUE(x_B.isNear(Vector3d(+0.0, +1.0, +0.0), 1e-5)) << x_B.toString() ;

        }

        const Transform transform_A_B = transform_A_G * transform_B_G.getInverse() ;

        {

            const Vector3d x_B = { +0.0, +0.0, +0.0 } ;
            const Vector3d x_A = transform_A_B.applyToPosition(x_B) ;

            EXPECT_TRUE(x_A.isNear(Vector3d(-1.0, -1.0, +0.0), 1e-5)) << x_A.toString() ;

        }

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////