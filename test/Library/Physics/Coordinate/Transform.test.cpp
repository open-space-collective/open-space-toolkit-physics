////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Coordinate/Transform.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Coordinate/Transform.hpp>
#include <Library/Mathematics/Geometry/Transformations/Rotations/RotationMatrix.hpp>
#include <Library/Mathematics/Geometry/Transformations/Rotations/RotationVector.hpp>
#include <Library/Physics/Units/Derived/Angle.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Physics_Coordinate_Transform, Constructor)
{

    using library::core::types::Real ;
    using library::math::obj::Vector3d ;
    using library::physics::units::Angle ;
    using library::math::geom::trf::rot::Quaternion ;
    using library::math::geom::trf::rot::RotationVector ;
    using library::math::geom::trf::rot::RotationMatrix ;
    using library::physics::time::Instant ;
    using library::physics::coord::Transform ;

    {

        const Instant instant = Instant::J2000() ;

        const Vector3d t_B_A = { +0.0, +0.0, +0.0 } ;
        const Vector3d v_B_A = { +0.0, +0.0, +0.0 } ;
        
        const Quaternion q_B_A = Quaternion::RotationVector(RotationVector({ +0.0, +0.0, +1.0 }, Angle::Degrees(+0.0))) ;
        const Vector3d w_B_A_in_B = { +0.0, +0.0, +0.0 } ;

        EXPECT_NO_THROW(Transform(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B, Transform::Type::Active)) ;

    }

    {

        const Instant instant = Instant::J2000() ;

        const Vector3d t_B_A = { +0.0, +0.0, +0.0 } ;
        const Vector3d v_B_A = { +0.0, +0.0, +0.0 } ;
        
        const Quaternion q_B_A = Quaternion::RotationVector(RotationVector({ +0.0, +0.0, +1.0 }, Angle::Degrees(+0.0))) ;
        const Vector3d w_B_A_in_B = { +0.0, +0.0, +0.0 } ;

        EXPECT_NO_THROW(Transform(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B, Transform::Type::Passive)) ;

    }

    {

        const Instant instant = Instant::J2000() ;

        const Vector3d t_B_A = { +0.0, +0.0, +0.0 } ;
        const Vector3d v_B_A = { +0.0, +0.0, +0.0 } ;
        
        const Quaternion q_B_A = Quaternion::RotationVector(RotationVector({ +0.0, +0.0, +1.0 }, Angle::Degrees(+0.0))) ;
        const Vector3d w_B_A_in_B = { +0.0, +0.0, +0.0 } ;

        EXPECT_ANY_THROW(Transform(instant, t_B_A, v_B_A, q_B_A, w_B_A_in_B, Transform::Type::Undefined)) ;

    }

}

TEST (Library_Physics_Coordinate_Transform, EqualToOperator)
{

    using library::physics::coord::Transform ;

    {

        FAIL() ;

    }

}

TEST (Library_Physics_Coordinate_Transform, NotEqualToOperator)
{

    using library::physics::coord::Transform ;

    {

        FAIL() ;

    }

}

TEST (Library_Physics_Coordinate_Transform, MultiplicationOperator)
{

    using library::core::types::Real ;
    using library::math::obj::Vector3d ;
    using library::physics::units::Angle ;
    using library::math::geom::trf::rot::Quaternion ;
    using library::math::geom::trf::rot::RotationVector ;
    using library::math::geom::trf::rot::RotationMatrix ;
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

    using library::physics::coord::Transform ;

    {

        FAIL() ;

    }

}

TEST (Library_Physics_Coordinate_Transform, IsDefined)
{

    using library::physics::coord::Transform ;

    {

        FAIL() ;

    }
    
}

TEST (Library_Physics_Coordinate_Transform, AccessInstant)
{

    using library::physics::coord::Transform ;

    {

        FAIL() ;

    }
    
}

TEST (Library_Physics_Coordinate_Transform, AccessTranslation)
{

    using library::physics::coord::Transform ;

    {

        FAIL() ;

    }
    
}

TEST (Library_Physics_Coordinate_Transform, AccessVelocity)
{

    using library::physics::coord::Transform ;

    {

        FAIL() ;

    }
    
}

TEST (Library_Physics_Coordinate_Transform, AccessOrientation)
{

    using library::physics::coord::Transform ;

    {

        FAIL() ;

    }
    
}

TEST (Library_Physics_Coordinate_Transform, AccessAngularVelocity)
{

    using library::physics::coord::Transform ;

    {

        FAIL() ;

    }
    
}

TEST (Library_Physics_Coordinate_Transform, GetInstant)
{

    using library::physics::coord::Transform ;

    {

        FAIL() ;

    }
    
}

TEST (Library_Physics_Coordinate_Transform, GetTranslation)
{

    using library::physics::coord::Transform ;

    {

        FAIL() ;

    }
    
}

TEST (Library_Physics_Coordinate_Transform, GetVelocity)
{

    using library::physics::coord::Transform ;

    {

        FAIL() ;

    }
    
}

TEST (Library_Physics_Coordinate_Transform, GetOrientation)
{

    using library::physics::coord::Transform ;

    {

        FAIL() ;

    }
    
}

TEST (Library_Physics_Coordinate_Transform, GetAngularVelocity)
{

    using library::physics::coord::Transform ;

    {

        FAIL() ;

    }
    
}

TEST (Library_Physics_Coordinate_Transform, GetInverse)
{

    using library::core::types::Real ;
    using library::math::obj::Vector3d ;
    using library::physics::units::Angle ;
    using library::math::geom::trf::rot::Quaternion ;
    using library::math::geom::trf::rot::RotationVector ;
    using library::math::geom::trf::rot::RotationMatrix ;
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

            EXPECT_TRUE(transform.getInverse().getInverse().accessTranslation().isApprox(transform.accessTranslation(), 1e-14)) ;
            EXPECT_TRUE(transform.getInverse().getInverse().accessVelocity().isApprox(transform.accessVelocity(), 1e-14)) ;
            EXPECT_TRUE(transform.getInverse().getInverse().accessOrientation().isNear(transform.accessOrientation(), Angle::Radians(1e-7))) ;
            EXPECT_TRUE(transform.getInverse().getInverse().accessAngularVelocity().isApprox(transform.accessAngularVelocity(), 1e-14)) ;

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
    using library::physics::units::Angle ;
    using library::math::geom::trf::rot::Quaternion ;
    using library::math::geom::trf::rot::RotationVector ;
    using library::math::geom::trf::rot::RotationMatrix ;
    using library::physics::time::Instant ;
    using library::physics::coord::Transform ;

    // Identity

    {

        const Instant instant = Instant::J2000() ;

        const Transform transform_B_A = Transform::Identity(instant) ;

        const Vector3d x_A = { +0.0, +0.0, +0.0 } ;

        const Vector3d x_B = transform_B_A.applyToPosition(x_A) ;

        EXPECT_TRUE(x_B.isApprox(x_A, 1e-14)) ;

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

        EXPECT_TRUE(x_B.isApprox(Vector3d(+0.0, +0.0, +0.0), 1e-14)) ;

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

        EXPECT_TRUE(x_B.isApprox(Vector3d(+1.0, +0.0, +0.0), 1e-14)) ;

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

        EXPECT_TRUE(x_B.isApprox(Vector3d(+1.0, +0.0, +0.0), 1e-14)) ;

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

        EXPECT_TRUE(x_B.isApprox(Vector3d(+0.0, +0.0, +0.0), 1e-14)) ;

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

        EXPECT_TRUE(x_B.isApprox(Vector3d(+1.0, +0.0, +0.0), 1e-14)) ;

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

        EXPECT_TRUE(x_B.isApprox(Vector3d(+1.0, +0.0, +0.0), 1e-14)) ;

    }

}

TEST (Library_Physics_Coordinate_Transform, ApplyToVelocity)
{

    using library::core::types::Real ;
    using library::math::obj::Vector3d ;
    using library::physics::units::Angle ;
    using library::math::geom::trf::rot::Quaternion ;
    using library::math::geom::trf::rot::RotationVector ;
    using library::math::geom::trf::rot::RotationMatrix ;
    using library::physics::time::Instant ;
    using library::physics::coord::Transform ;

    // Identity

    {

        const Instant instant = Instant::J2000() ;

        const Transform transform_B_A = Transform::Identity(instant) ;

        const Vector3d x_A = { +0.0, +0.0, +0.0 } ;
        const Vector3d v_A = { +0.0, +0.0, +0.0 } ;

        const Vector3d v_B = transform_B_A.applyToVelocity(x_A, v_A) ;

        EXPECT_TRUE(v_B.isApprox(v_A, 1e-14)) ;

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

        EXPECT_TRUE(v_B.isApprox(Vector3d(+0.0, +1.0, +0.0), 1e-14)) ;

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

        EXPECT_TRUE(v_B.isApprox(Vector3d(+1.0, +0.0, +0.0), 1e-14)) ;

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

        EXPECT_TRUE(v_B.isApprox(Vector3d(+1.0, +0.0, +0.0), 1e-14)) ;

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

        EXPECT_TRUE(v_B.isApprox(Vector3d(+0.0, +1.0, +0.0), 1e-14)) ;

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

        EXPECT_TRUE(v_B.isApprox(Vector3d(+1.0, +0.0, +0.0), 1e-14)) ;

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

        EXPECT_TRUE(v_B.isApprox(Vector3d(+1.0, -1.0, +0.0), 1e-14)) ;

    }

}

TEST (Library_Physics_Coordinate_Transform, ApplyToVector)
{

    using library::physics::coord::Transform ;

    {

        FAIL() ;

    }
    
}

TEST (Library_Physics_Coordinate_Transform, Undefined)
{

    using library::physics::coord::Transform ;

    {

        FAIL() ;

    }
    
}

TEST (Library_Physics_Coordinate_Transform, Identity)
{

    using library::physics::coord::Transform ;

    {

        FAIL() ;

    }
    
}

TEST (Library_Physics_Coordinate_Transform, Translation)
{

    using library::physics::coord::Transform ;

    {

        FAIL() ;

    }
    
}

TEST (Library_Physics_Coordinate_Transform, Active)
{

    using library::physics::coord::Transform ;

    {

        FAIL() ;

    }
    
}

TEST (Library_Physics_Coordinate_Transform, Passive)
{

    using library::physics::coord::Transform ;

    {

        FAIL() ;

    }
    
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////