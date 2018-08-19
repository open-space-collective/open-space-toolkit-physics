////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Coordinate/Frame.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Coordinate/Frame/Providers/Fixed.hpp>
#include <Library/Physics/Coordinate/Frame.hpp>
#include <Library/Mathematics/Geometry/Transformations/Rotations/RotationMatrix.hpp>
#include <Library/Mathematics/Geometry/Transformations/Rotations/RotationVector.hpp>
#include <Library/Physics/Units/Derived/Angle.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// TEST (Library_Physics_Coordinate_Frame, Constructor)
// {

//     using library::core::types::Shared ;
//     using library::core::types::Real ;
//     using library::core::types::String ;
//     using library::math::obj::Vector3d ;
//     using library::physics::units::Angle ;
//     using library::math::geom::trf::rot::Quaternion ;
//     using library::math::geom::trf::rot::RotationVector ;
//     using library::math::geom::trf::rot::RotationMatrix ;
//     using library::physics::time::Instant ;
//     using library::physics::coord::Transform ;
//     using library::physics::coord::Frame ;
//     using library::physics::coord::frame::Provider ;
//     using library::physics::coord::frame::provider::Fixed ;

//     {

//         RotationVector rv_A_B = RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(-90.0)) ;

//         std::cout << "rv_A_B = " << std::endl << rv_A_B << std::endl ;

//         RotationMatrix rm_A_B = RotationMatrix::RotationVector(rv_A_B) ;

//         std::cout << "rm_A_B = " << std::endl << rm_A_B << std::endl ;

//         Quaternion q_A_B = Quaternion::RotationVector(rv_A_B) ;

//         std::cout << "q_A_B = " << std::endl << q_A_B << std::endl ;

//         RotationVector rv_B_A = RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(+90.0)) ;

//         std::cout << "rv_B_A = " << std::endl << rv_B_A << std::endl ;

//         RotationMatrix rm_B_A = RotationMatrix::RotationVector(rv_B_A) ;

//         std::cout << "rm_B_A = " << std::endl << rm_B_A << std::endl ;

//         Quaternion q_B_A_rv = Quaternion::RotationVector(rv_B_A) ;

//         std::cout << "q_B_A_rv = " << std::endl << q_B_A_rv << std::endl ;

//         Quaternion q_B_A_rm = Quaternion::RotationMatrix(rm_B_A) ;

//         std::cout << "q_B_A_rm = " << std::endl << q_B_A_rm << std::endl ;

//         Vector3d x_A = { +0.0, +1.0, +0.0 } ;

//         std::cout << "x_A = " << x_A.toString() << std::endl ;

//         Vector3d x_B = q_B_A_rv * x_A ;

//         std::cout << "x_B = " << x_B.toString() << std::endl ;

//     }

//     // Pure static translation

//     {

//         const String name = "Custom" ;
//         const bool isQuasiInertial = true ;
//         const Shared<const Frame> parentFrame = std::make_shared<Frame>(Frame::GCRF()) ;
//         const Shared<Provider> provider = std::make_shared<Fixed>(Fixed(Transform::Passive(Instant::J2000(), Vector3d(-1.0, +0.0, +0.0), Vector3d::Zero(), Quaternion::Unit(), Vector3d::Zero()))) ;
        
//         EXPECT_NO_THROW(Frame(name, isQuasiInertial, parentFrame, provider)) ;

//         const Frame customFrame = { name, isQuasiInertial, parentFrame, provider } ;

//         EXPECT_TRUE(customFrame.isDefined()) ;

//         // Position

//         {

//             const Vector3d x_CUSTOM = {+1.0, +0.0, +0.0} ;
        
//             const Vector3d x_GCRF = customFrame.getTransformTo(Frame::GCRF(), Instant::J2000()).applyToPosition(x_CUSTOM) ;
            
//             EXPECT_TRUE(x_GCRF.isApprox(Vector3d(+2.0, +0.0, +0.0), Real::Epsilon())) ;

//         }

//         // Velocity

//         {

//             const Vector3d x_CUSTOM = {+1.0, +0.0, +0.0} ;
//             const Vector3d v_CUSTOM = {+1.0, +0.0, +0.0} ;

//             const Vector3d v_GCRF = customFrame.getTransformTo(Frame::GCRF(), Instant::J2000()).applyToVelocity(x_CUSTOM, v_CUSTOM) ;
            
//             EXPECT_TRUE(v_GCRF.isApprox(Vector3d(+1.0, +0.0, +0.0), Real::Epsilon())) ;

//         }

//         // Vector

//         {

//             const Vector3d u_CUSTOM = {+1.0, +0.0, +0.0} ;

//             const Vector3d u_GCRF = customFrame.getTransformTo(Frame::GCRF(), Instant::J2000()).applyToVector(u_CUSTOM) ;

//             EXPECT_TRUE(u_GCRF.isApprox(Vector3d(+1.0, +0.0, +0.0), Real::Epsilon())) ;

//         }

//     }

//     // Pure dynamic translation

//     {

//         const String name = "Custom" ;
//         const bool isQuasiInertial = true ;
//         const Shared<const Frame> parentFrame = std::make_shared<Frame>(Frame::GCRF()) ;
//         const Shared<Provider> provider = std::make_shared<Fixed>(Fixed(Transform::Passive(Instant::J2000(), Vector3d(-1.0, +0.0, +0.0), Vector3d(-2.0, +0.0, +0.0), Quaternion::Unit(), Vector3d::Zero()))) ;
        
//         EXPECT_NO_THROW(Frame(name, isQuasiInertial, parentFrame, provider)) ;

//         const Frame customFrame = { name, isQuasiInertial, parentFrame, provider } ;

//         EXPECT_TRUE(customFrame.isDefined()) ;

//         // Position

//         {

//             const Vector3d x_CUSTOM = {+1.0, +0.0, +0.0} ;
        
//             const Vector3d x_GCRF = customFrame.getTransformTo(Frame::GCRF(), Instant::J2000()).applyToPosition(x_CUSTOM) ;
            
//             EXPECT_TRUE(x_GCRF.isApprox(Vector3d(+2.0, +0.0, +0.0), Real::Epsilon())) ;

//         }

//         // Velocity

//         {

//             const Vector3d x_CUSTOM = {+1.0, +0.0, +0.0} ;
//             const Vector3d v_CUSTOM = {+0.0, +1.0, +0.0} ;

//             const Vector3d v_GCRF = customFrame.getTransformTo(Frame::GCRF(), Instant::J2000()).applyToVelocity(x_CUSTOM, v_CUSTOM) ;
            
//             EXPECT_TRUE(v_GCRF.isApprox(Vector3d(+2.0, +1.0, +0.0), Real::Epsilon())) ;

//         }

//         // Vector

//         {

//             const Vector3d u_CUSTOM = {+1.0, +0.0, +0.0} ;

//             const Vector3d u_GCRF = customFrame.getTransformTo(Frame::GCRF(), Instant::J2000()).applyToVector(u_CUSTOM) ;

//             EXPECT_TRUE(u_GCRF.isApprox(Vector3d(+1.0, +0.0, +0.0), Real::Epsilon())) ;

//         }

//     }

//     // Pure static rotation

//     {

//         const String name = "Custom" ;
//         const bool isQuasiInertial = true ;
//         const Shared<const Frame> parentFrame = std::make_shared<Frame>(Frame::GCRF()) ;
//         const Shared<Provider> provider = std::make_shared<Fixed>(Fixed(Transform::Passive(Instant::J2000(), Vector3d::Zero(), Vector3d::Zero(), Quaternion::RotationVector(RotationVector({ +0.0, +0.0, +1.0 }, Angle::Degrees(90.0))), Vector3d::Zero()))) ;
        
//         EXPECT_NO_THROW(Frame(name, isQuasiInertial, parentFrame, provider)) ;

//         const Frame customFrame = { name, isQuasiInertial, parentFrame, provider } ;

//         EXPECT_TRUE(customFrame.isDefined()) ;

//         // Position
        
//         {

//             const Vector3d x_CUSTOM = {+1.0, +0.0, +0.0} ;
        
//             const Vector3d x_GCRF = customFrame.getTransformTo(Frame::GCRF(), Instant::J2000()).applyToPosition(x_CUSTOM) ;
            
//             EXPECT_TRUE(x_GCRF.isApprox(Vector3d(+0.0, +1.0, +0.0), Real::Epsilon())) ;

//         }

//         // Velocity

//         {

//             const Vector3d x_CUSTOM = {+1.0, +0.0, +0.0} ;
//             const Vector3d v_CUSTOM = {+1.0, +0.0, +0.0} ;

//             const Vector3d v_GCRF = customFrame.getTransformTo(Frame::GCRF(), Instant::J2000()).applyToVelocity(x_CUSTOM, v_CUSTOM) ;
            
//             EXPECT_TRUE(v_GCRF.isApprox(Vector3d(+0.0, +1.0, +0.0), Real::Epsilon())) ;

//         }

//         // Vector

//         {

//             const Vector3d u_CUSTOM = {+1.0, +0.0, +0.0} ;

//             const Vector3d u_GCRF = customFrame.getTransformTo(Frame::GCRF(), Instant::J2000()).applyToVector(u_CUSTOM) ;

//             EXPECT_TRUE(u_GCRF.isApprox(Vector3d(+0.0, +1.0, +0.0), Real::Epsilon())) ;

//         }

//     }

//     // Pure dynamic rotation

//     {

//         const String name = "Custom" ;
//         const bool isQuasiInertial = true ;
//         const Shared<const Frame> parentFrame = std::make_shared<Frame>(Frame::GCRF()) ;
//         const Shared<Provider> provider = std::make_shared<Fixed>(Fixed(Transform::Passive(Instant::J2000(), Vector3d::Zero(), Vector3d::Zero(), Quaternion::Unit(), Vector3d(+0.0, +0.0, -1.0)))) ;
        
//         EXPECT_NO_THROW(Frame(name, isQuasiInertial, parentFrame, provider)) ;

//         const Frame customFrame = { name, isQuasiInertial, parentFrame, provider } ;

//         EXPECT_TRUE(customFrame.isDefined()) ;

//         // Position
        
//         {

//             const Vector3d x_CUSTOM = {+1.0, +0.0, +0.0} ;
        
//             const Vector3d x_GCRF = customFrame.getTransformTo(Frame::GCRF(), Instant::J2000()).applyToPosition(x_CUSTOM) ;
            
//             EXPECT_TRUE(x_GCRF.isApprox(Vector3d(+1.0, +0.0, +0.0), Real::Epsilon())) ;

//         }

//         // Velocity

//         {

//             const Vector3d x_CUSTOM = {+1.0, +0.0, +0.0} ;
//             const Vector3d v_CUSTOM = {+1.0, +0.0, +0.0} ;

//             const Vector3d v_GCRF = customFrame.getTransformTo(Frame::GCRF(), Instant::J2000()).applyToVelocity(x_CUSTOM, v_CUSTOM) ;
            
//             EXPECT_TRUE(v_GCRF.isApprox(Vector3d(+1.0, +1.0, +0.0), Real::Epsilon())) ;

//         }

//         // Vector

//         {

//             const Vector3d u_CUSTOM = {+1.0, +0.0, +0.0} ;

//             const Vector3d u_GCRF = customFrame.getTransformTo(Frame::GCRF(), Instant::J2000()).applyToVector(u_CUSTOM) ;

//             EXPECT_TRUE(u_GCRF.isApprox(Vector3d(+1.0, +0.0, +0.0), Real::Epsilon())) ;

//         }

//     }

//     // {

//     //     const String name = "Custom" ;
//     //     const bool isQuasiInertial = true ;
//     //     const Shared<const Frame> parentFrame = std::make_shared<Frame>(Frame::GCRF()) ;
//     //     const Shared<Provider> provider = std::make_shared<Fixed>(Fixed(Transform::Passive(Instant::J2000(), Vector3d(0.0, 0.0, 0.0), Vector3d::Zero(), Quaternion::Unit(), Vector3d(0.0, 0.0, +2.0)))) ;
        
//     //     EXPECT_NO_THROW(Frame(name, isQuasiInertial, parentFrame, provider)) ;

//     //     const Frame customFrame = { name, isQuasiInertial, parentFrame, provider } ;

//     //     EXPECT_TRUE(customFrame.isDefined()) ;

//     //     // Position
        
//     //     {

//     //         const Vector3d x_CUSTOM = {0.0, +1.0, 0.0} ;
        
//     //         const Vector3d x_GCRF = customFrame.getTransformTo(Frame::GCRF(), Instant::J2000()).applyToPosition(x_CUSTOM) ;
            
//     //         EXPECT_TRUE(x_GCRF.isApprox(Vector3d(+1.0, 0.0, 0.0), Real::Epsilon())) ;

//     //     }

//     //     // Velocity

//     //     {

//     //         const Vector3d x_CUSTOM = {+0.0, +1.0, +0.0} ;
//     //         const Vector3d v_CUSTOM = {-2.0, +1.0, +0.0} ;

//     //         const Vector3d v_GCRF = customFrame.getTransformTo(Frame::GCRF(), Instant::J2000()).applyToVelocity(x_CUSTOM, v_CUSTOM) ;
            
//     //         EXPECT_TRUE(v_GCRF.isApprox(Vector3d(+1.0, 0.0, 0.0), Real::Epsilon())) ;

//     //     }

//     //     // Vector

//     //     {

//     //         const Vector3d v_CUSTOM = {0.0, +1.0, 0.0} ;

//     //         const Vector3d v_GCRF = customFrame.getTransformTo(Frame::GCRF(), Instant::J2000()).applyToVector(v_CUSTOM) ;

//     //         EXPECT_TRUE(v_GCRF.isApprox(Vector3d(+1.0, 0.0, 0.0), Real::Epsilon())) ;

//     //     }

//     // }

//     // {

//     //     const String name = "Custom" ;
//     //     const bool isQuasiInertial = true ;
//     //     const Shared<const Frame> parentFrame = std::make_shared<Frame>(Frame::GCRF()) ;
//     //     const Shared<Provider> provider = std::make_shared<Fixed>(Fixed(Transform::Passive(Instant::J2000(), Vector3d(0.0, 0.0, 0.0), Vector3d::Zero(), Quaternion::RotationVector(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(-90.0))), Vector3d(0.0, 0.0, +2.0)))) ;
        
//     //     EXPECT_NO_THROW(Frame(name, isQuasiInertial, parentFrame, provider)) ;

//     //     const Frame customFrame = { name, isQuasiInertial, parentFrame, provider } ;

//     //     EXPECT_TRUE(customFrame.isDefined()) ;

//     //     // Position
        
//     //     {

//     //         const Vector3d x_CUSTOM = {0.0, +1.0, 0.0} ;
        
//     //         const Vector3d x_GCRF = customFrame.getTransformTo(Frame::GCRF(), Instant::J2000()).applyToPosition(x_CUSTOM) ;
            
//     //         EXPECT_TRUE(x_GCRF.isApprox(Vector3d(+1.0, 0.0, 0.0), Real::Epsilon())) ;

//     //     }

//     //     // Velocity

//     //     {

//     //         const Vector3d x_CUSTOM = {+0.0, +1.0, +0.0} ;
//     //         const Vector3d v_CUSTOM = {-2.0, +1.0, +0.0} ;

//     //         const Vector3d v_GCRF = customFrame.getTransformTo(Frame::GCRF(), Instant::J2000()).applyToVelocity(x_CUSTOM, v_CUSTOM) ;
            
//     //         EXPECT_TRUE(v_GCRF.isApprox(Vector3d(+1.0, 0.0, 0.0), Real::Epsilon())) ;

//     //     }

//     //     // Vector

//     //     {

//     //         const Vector3d v_CUSTOM = {0.0, +1.0, 0.0} ;

//     //         const Vector3d v_GCRF = customFrame.getTransformTo(Frame::GCRF(), Instant::J2000()).applyToVector(v_CUSTOM) ;

//     //         EXPECT_TRUE(v_GCRF.isApprox(Vector3d(+1.0, 0.0, 0.0), Real::Epsilon())) ;

//     //     }

//     // }

// }

// // TEST (Library_Physics_Coordinate_Frame, EqualToOperator)
// // {

// //     using library::physics::coord::Frame ;

// //     {

// //         FAIL() ;

// //     }

// //     {

// //         EXPECT_FALSE(Frame::Undefined() == Frame::Undefined()) ;

// //     }

// // }

// // TEST (Library_Physics_Coordinate_Frame, NotEqualToOperator)
// // {

// //     using library::physics::coord::Frame ;

// //     {

// //         FAIL() ;

// //     }

// //     {

// //         EXPECT_TRUE(Frame::Undefined() != Frame::Undefined()) ;

// //     }

// // }

// // TEST (Library_Physics_Coordinate_Frame, StreamOperator)
// // {

// //     using library::physics::coord::Frame ;

// //     {

// //         testing::internal::CaptureStdout() ;

// //         // EXPECT_NO_THROW(std::cout << Frame(23, 59, 60, 999, 999, 999) << std::endl) ;

// //         EXPECT_FALSE(testing::internal::GetCapturedStdout().empty()) ;

// //     }

// // }

// // TEST (Library_Physics_Coordinate_Frame, IsDefined)
// // {

// //     using library::physics::coord::Frame ;

// //     {

// //         FAIL() ;

// //     }

// //     {
        
// //         EXPECT_FALSE(Frame::Undefined().isDefined()) ;

// //     }

// // }

// // TEST (Library_Physics_Coordinate_Frame, IsQuasiInertial)
// // {

// //     using library::physics::coord::Frame ;

// //     {

// //         FAIL() ;

// //     }

// // }

// // TEST (Library_Physics_Coordinate_Frame, HasParent)
// // {

// //     using library::physics::coord::Frame ;

// //     {

// //         FAIL() ;

// //     }

// // }

// // TEST (Library_Physics_Coordinate_Frame, AccessParent)
// // {

// //     using library::physics::coord::Frame ;

// //     {

// //         FAIL() ;

// //     }

// // }

// // TEST (Library_Physics_Coordinate_Frame, GetName)
// // {

// //     using library::physics::coord::Frame ;

// //     {

// //         FAIL() ;

// //     }

// // }

// // TEST (Library_Physics_Coordinate_Frame, GetOriginIn)
// // {

// //     using library::physics::coord::Frame ;
    
// //     {

// //         FAIL() ;

// //     }

// // }

// // TEST (Library_Physics_Coordinate_Frame, GetAxesIn)
// // {

// //     using library::physics::coord::Frame ;
    
// //     {

// //         FAIL() ;

// //     }

// // }

// TEST (Library_Physics_Coordinate_Frame, GetTransformTo)
// {

//     using library::physics::time::Instant ;
//     using library::physics::coord::Transform ;
//     using library::physics::coord::Frame ;

//     {

//         const Instant instant = Instant::J2000() ;

//         const Frame gcrf = Frame::GCRF() ;
//         std::cout << "gcrf = " << std::endl << gcrf << std::endl ;
//         const Frame itrf = Frame::ITRF() ;
//         std::cout << "itrf = " << std::endl << itrf << std::endl ;
        
//         const Transform transform = itrf.getTransformTo(gcrf, instant) ;

//         std::cout << "transform = " << std::endl ;
//         std::cout << transform << std::endl ;

//     }

//     {

//         EXPECT_ANY_THROW(Frame::Undefined().getTransformTo(Frame::GCRF(), Instant::J2000())) ;
//         EXPECT_ANY_THROW(Frame::GCRF().getTransformTo(Frame::Undefined(), Instant::J2000())) ;
//         EXPECT_ANY_THROW(Frame::GCRF().getTransformTo(Frame::GCRF(), Instant::Undefined())) ;

//     }

// }

// TEST (Library_Physics_Coordinate_Frame, Undefined)
// {

//     using library::physics::coord::Frame ;

//     {

//         EXPECT_NO_THROW(Frame::Undefined()) ;

//         EXPECT_FALSE(Frame::Undefined().isDefined()) ;

//     }

// }

// // TEST (Library_Physics_Coordinate_Frame, ICRF)
// // {

// //     using library::physics::coord::Frame ;

// //     {

// //         EXPECT_NO_THROW(Frame::ICRF()) ;

// //         EXPECT_TRUE(Frame::ICRF().isDefined()) ;

// //     }

// // }

// TEST (Library_Physics_Coordinate_Frame, GCRF)
// {

//     using library::physics::coord::Frame ;

//     {

//         EXPECT_NO_THROW(Frame::GCRF()) ;

//         EXPECT_TRUE(Frame::GCRF().isDefined()) ;

//     }

// }

// // TEST (Library_Physics_Coordinate_Frame, EME2000)
// // {

// //     using library::physics::coord::Frame ;

// //     {

// //         EXPECT_NO_THROW(Frame::EME2000()) ;

// //         EXPECT_TRUE(Frame::EME2000().isDefined()) ;

// //     }

// // }

// TEST (Library_Physics_Coordinate_Frame, TIRF)
// {

//     using library::physics::coord::Frame ;

//     {

//         EXPECT_NO_THROW(Frame::TIRF()) ;

//         EXPECT_TRUE(Frame::TIRF().isDefined()) ;

//     }

// }

// TEST (Library_Physics_Coordinate_Frame, ITRF)
// {

//     using library::physics::coord::Frame ;

//     {

//         EXPECT_NO_THROW(Frame::ITRF()) ;

//         EXPECT_TRUE(Frame::ITRF().isDefined()) ;

//     }

// }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////