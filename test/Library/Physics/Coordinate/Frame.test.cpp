////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Coordinate/Frame.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Coordinate/Frame/Providers/Static.hpp>
#include <Library/Physics/Coordinate/Frame.hpp>
#include <Library/Mathematics/Geometry/3D/Transformations/Rotations/RotationMatrix.hpp>
#include <Library/Mathematics/Geometry/3D/Transformations/Rotations/RotationVector.hpp>
#include <Library/Physics/Units/Derived/Angle.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Physics_Coordinate_Frame, EqualToOperator)
{

    using library::core::types::Shared ;
    using library::core::types::Real ;
    using library::core::types::String ;

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::trf::rot::Quaternion ;
    using library::math::geom::d3::trf::rot::RotationVector ;
    using library::math::geom::d3::trf::rot::RotationMatrix ;
    
    using library::physics::units::Angle ;
    using library::physics::time::Scale ;
    using library::physics::time::Instant ;
    using library::physics::time::DateTime ;
    using library::physics::coord::Transform ;
    using library::physics::coord::Frame ;
    using library::physics::coord::frame::Provider ;
    using library::physics::coord::frame::provider::Static ;

    {

        const String name = "Custom" ;
        const bool isQuasiInertial = true ;
        const Shared<const Frame> parentFrameSPtr = Frame::GCRF() ;
        const Shared<const Provider> providerSPtr = std::make_shared<Static>(Static(Transform::Passive(Instant::J2000(), Vector3d(0.0, 0.0, 0.0), Vector3d::Zero(), Quaternion::RotationVector(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(-90.0))), Vector3d(0.0, 0.0, +2.0)))) ;
        
        const Shared<const Frame> customFrameSPtr = Frame::Construct(name, isQuasiInertial, parentFrameSPtr, providerSPtr) ;

        EXPECT_TRUE(customFrameSPtr == customFrameSPtr) ;

        Frame::Destruct("Custom") ;

    }

    {

        EXPECT_TRUE(Frame::GCRF() == Frame::GCRF()) ;
        EXPECT_TRUE(Frame::ITRF() == Frame::ITRF()) ;

        EXPECT_TRUE(Frame::TEMEOfEpoch(Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::UTC)) == Frame::TEMEOfEpoch(Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::UTC))) ;

    }

    {

        const bool isQuasiInertial = true ;
        const Shared<const Provider> providerSPtr = std::make_shared<Static>(Static(Transform::Passive(Instant::J2000(), Vector3d(0.0, 0.0, 0.0), Vector3d::Zero(), Quaternion::RotationVector(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(-90.0))), Vector3d(0.0, 0.0, +2.0)))) ;
        
        const Shared<const Frame> firstCustomFrameSPtr = Frame::Construct("Custom A", isQuasiInertial, Frame::GCRF(), providerSPtr) ;
        const Shared<const Frame> secondCustomFrameSPtr = Frame::Construct("Custom B", isQuasiInertial, Frame::GCRF(), providerSPtr) ;

        EXPECT_FALSE(firstCustomFrameSPtr == secondCustomFrameSPtr) ;

        Frame::Destruct("Custom A") ;
        Frame::Destruct("Custom B") ;

    }

    {

        const Shared<const Provider> providerSPtr = std::make_shared<Static>(Static(Transform::Passive(Instant::J2000(), Vector3d(0.0, 0.0, 0.0), Vector3d::Zero(), Quaternion::RotationVector(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(-90.0))), Vector3d(0.0, 0.0, +2.0)))) ;
        
        const Shared<const Frame> firstCustomFrameSPtr = Frame::Construct("Custom A", true, Frame::GCRF(), providerSPtr) ;
        const Shared<const Frame> secondCustomFrameSPtr = Frame::Construct("Custom B", false, Frame::GCRF(), providerSPtr) ;

        EXPECT_FALSE(firstCustomFrameSPtr == secondCustomFrameSPtr) ;

        Frame::Destruct("Custom A") ;
        Frame::Destruct("Custom B") ;

    }

    {

        const bool isQuasiInertial = true ;
        const Shared<const Provider> providerSPtr = std::make_shared<Static>(Static(Transform::Passive(Instant::J2000(), Vector3d(0.0, 0.0, 0.0), Vector3d::Zero(), Quaternion::RotationVector(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(-90.0))), Vector3d(0.0, 0.0, +2.0)))) ;
        
        const Shared<const Frame> firstCustomFrameSPtr = Frame::Construct("Custom A", isQuasiInertial, Frame::GCRF(), providerSPtr) ;
        const Shared<const Frame> secondCustomFrameSPtr = Frame::Construct("Custom B", isQuasiInertial, Frame::ITRF(), providerSPtr) ;

        EXPECT_FALSE(firstCustomFrameSPtr == secondCustomFrameSPtr) ;

        Frame::Destruct("Custom A") ;
        Frame::Destruct("Custom B") ;

    }

    {

        const bool isQuasiInertial = true ;
        const Shared<const Provider> firstProviderSPtr = std::make_shared<Static>(Static(Transform::Passive(Instant::J2000(), Vector3d(0.0, 0.0, 0.0), Vector3d::Zero(), Quaternion::RotationVector(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(-90.0))), Vector3d(0.0, 0.0, +2.0)))) ;
        const Shared<const Provider> secondProviderSPtr = std::make_shared<Static>(Static(Transform::Passive(Instant::J2000(), Vector3d(1.0, 0.0, 0.0), Vector3d::Zero(), Quaternion::RotationVector(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(-90.0))), Vector3d(0.0, 0.0, +2.0)))) ;
        
        const Shared<const Frame> firstCustomFrameSPtr = Frame::Construct("Custom A", isQuasiInertial, Frame::GCRF(), firstProviderSPtr) ;
        const Shared<const Frame> secondCustomFrameSPtr = Frame::Construct("Custom B", isQuasiInertial, Frame::GCRF(), secondProviderSPtr) ;

        EXPECT_FALSE(firstCustomFrameSPtr == secondCustomFrameSPtr) ;

        Frame::Destruct("Custom A") ;
        Frame::Destruct("Custom B") ;

    }

    {

        EXPECT_FALSE(Frame::GCRF() == Frame::ITRF()) ;
        EXPECT_FALSE(Frame::TEMEOfEpoch(Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::UTC)) == Frame::TEMEOfEpoch(Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 1), Scale::UTC))) ;

    }

    {

        EXPECT_FALSE(Frame::Undefined() == Frame::Undefined()) ;
        EXPECT_FALSE(Frame::GCRF() == Frame::Undefined()) ;
        EXPECT_FALSE(Frame::Undefined() == Frame::GCRF()) ;

    }

}

TEST (Library_Physics_Coordinate_Frame, NotEqualToOperator)
{

    using library::core::types::Shared ;
    using library::core::types::Real ;
    using library::core::types::String ;

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::trf::rot::Quaternion ;
    using library::math::geom::d3::trf::rot::RotationVector ;
    using library::math::geom::d3::trf::rot::RotationMatrix ;
    
    using library::physics::units::Angle ;
    using library::physics::time::Scale ;
    using library::physics::time::Instant ;
    using library::physics::time::DateTime ;
    using library::physics::coord::Transform ;
    using library::physics::coord::Frame ;
    using library::physics::coord::frame::Provider ;
    using library::physics::coord::frame::provider::Static ;

    {

        const String name = "Custom" ;
        const bool isQuasiInertial = true ;
        const Shared<const Frame> parentFrameSPtr = Frame::GCRF() ;
        const Shared<const Provider> providerSPtr = std::make_shared<Static>(Static(Transform::Passive(Instant::J2000(), Vector3d(0.0, 0.0, 0.0), Vector3d::Zero(), Quaternion::RotationVector(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(-90.0))), Vector3d(0.0, 0.0, +2.0)))) ;
        
        const Shared<const Frame> customFrameSPtr = Frame::Construct(name, isQuasiInertial, parentFrameSPtr, providerSPtr) ;

        EXPECT_FALSE(customFrameSPtr != customFrameSPtr) ;

        Frame::Destruct("Custom") ;

    }

    {

        EXPECT_FALSE(Frame::GCRF() != Frame::GCRF()) ;
        EXPECT_FALSE(Frame::ITRF() != Frame::ITRF()) ;

        EXPECT_FALSE(Frame::TEMEOfEpoch(Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::UTC)) != Frame::TEMEOfEpoch(Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::UTC))) ;

    }

    {

        const bool isQuasiInertial = true ;
        const Shared<const Provider> providerSPtr = std::make_shared<Static>(Static(Transform::Passive(Instant::J2000(), Vector3d(0.0, 0.0, 0.0), Vector3d::Zero(), Quaternion::RotationVector(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(-90.0))), Vector3d(0.0, 0.0, +2.0)))) ;
        
        const Shared<const Frame> firstCustomFrameSPtr = Frame::Construct("Custom A", isQuasiInertial, Frame::GCRF(), providerSPtr) ;
        const Shared<const Frame> secondCustomFrameSPtr = Frame::Construct("Custom B", isQuasiInertial, Frame::GCRF(), providerSPtr) ;

        EXPECT_TRUE(firstCustomFrameSPtr != secondCustomFrameSPtr) ;

        Frame::Destruct("Custom A") ;
        Frame::Destruct("Custom B") ;

    }

    {

        const Shared<const Provider> providerSPtr = std::make_shared<Static>(Static(Transform::Passive(Instant::J2000(), Vector3d(0.0, 0.0, 0.0), Vector3d::Zero(), Quaternion::RotationVector(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(-90.0))), Vector3d(0.0, 0.0, +2.0)))) ;
        
        const Shared<const Frame> firstCustomFrameSPtr = Frame::Construct("Custom A", true, Frame::GCRF(), providerSPtr) ;
        const Shared<const Frame> secondCustomFrameSPtr = Frame::Construct("Custom B", false, Frame::GCRF(), providerSPtr) ;

        EXPECT_TRUE(firstCustomFrameSPtr != secondCustomFrameSPtr) ;

        Frame::Destruct("Custom A") ;
        Frame::Destruct("Custom B") ;

    }

    {

        const bool isQuasiInertial = true ;
        const Shared<const Provider> providerSPtr = std::make_shared<Static>(Static(Transform::Passive(Instant::J2000(), Vector3d(0.0, 0.0, 0.0), Vector3d::Zero(), Quaternion::RotationVector(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(-90.0))), Vector3d(0.0, 0.0, +2.0)))) ;
        
        const Shared<const Frame> firstCustomFrameSPtr = Frame::Construct("Custom A", isQuasiInertial, Frame::GCRF(), providerSPtr) ;
        const Shared<const Frame> secondCustomFrameSPtr = Frame::Construct("Custom B", isQuasiInertial, Frame::ITRF(), providerSPtr) ;

        EXPECT_TRUE(firstCustomFrameSPtr != secondCustomFrameSPtr) ;

        Frame::Destruct("Custom A") ;
        Frame::Destruct("Custom B") ;

    }

    {

        const bool isQuasiInertial = true ;
        const Shared<const Provider> firstProviderSPtr = std::make_shared<Static>(Static(Transform::Passive(Instant::J2000(), Vector3d(0.0, 0.0, 0.0), Vector3d::Zero(), Quaternion::RotationVector(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(-90.0))), Vector3d(0.0, 0.0, +2.0)))) ;
        const Shared<const Provider> secondProviderSPtr = std::make_shared<Static>(Static(Transform::Passive(Instant::J2000(), Vector3d(1.0, 0.0, 0.0), Vector3d::Zero(), Quaternion::RotationVector(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(-90.0))), Vector3d(0.0, 0.0, +2.0)))) ;
        
        const Shared<const Frame> firstCustomFrameSPtr = Frame::Construct("Custom A", isQuasiInertial, Frame::GCRF(), firstProviderSPtr) ;
        const Shared<const Frame> secondCustomFrameSPtr = Frame::Construct("Custom B", isQuasiInertial, Frame::GCRF(), secondProviderSPtr) ;

        EXPECT_TRUE(firstCustomFrameSPtr != secondCustomFrameSPtr) ;

        Frame::Destruct("Custom A") ;
        Frame::Destruct("Custom B") ;

    }

    {

        EXPECT_TRUE(Frame::GCRF() != Frame::ITRF()) ;
        EXPECT_TRUE(Frame::TEMEOfEpoch(Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::UTC)) != Frame::TEMEOfEpoch(Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 1), Scale::UTC))) ;

    }

    {

        EXPECT_TRUE(Frame::Undefined() != Frame::Undefined()) ;
        EXPECT_TRUE(Frame::GCRF() != Frame::Undefined()) ;
        EXPECT_TRUE(Frame::Undefined() != Frame::GCRF()) ;

    }

}

TEST (Library_Physics_Coordinate_Frame, StreamOperator)
{

    using library::core::types::Shared ;
    using library::core::types::Real ;
    using library::core::types::String ;

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::trf::rot::Quaternion ;
    using library::math::geom::d3::trf::rot::RotationVector ;
    using library::math::geom::d3::trf::rot::RotationMatrix ;
    
    using library::physics::units::Angle ;
    using library::physics::time::Scale ;
    using library::physics::time::Instant ;
    using library::physics::time::DateTime ;
    using library::physics::coord::Transform ;
    using library::physics::coord::Frame ;
    using library::physics::coord::frame::Provider ;
    using library::physics::coord::frame::provider::Static ;

    {

        const String name = "Custom" ;
        const bool isQuasiInertial = true ;
        const Shared<const Frame> parentFrameSPtr = Frame::GCRF() ;
        const Shared<const Provider> providerSPtr = std::make_shared<Static>(Static(Transform::Passive(Instant::J2000(), Vector3d(0.0, 0.0, 0.0), Vector3d::Zero(), Quaternion::RotationVector(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(-90.0))), Vector3d(0.0, 0.0, +2.0)))) ;
        
        const Shared<const Frame> customFrameSPtr = Frame::Construct(name, isQuasiInertial, parentFrameSPtr, providerSPtr) ;

        testing::internal::CaptureStdout() ;

        EXPECT_NO_THROW(std::cout << (*customFrameSPtr) << std::endl) ;

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty()) ;

        Frame::Destruct("Custom") ;

    }

}

TEST (Library_Physics_Coordinate_Frame, IsDefined)
{

    using library::core::types::Shared ;
    using library::core::types::Real ;
    using library::core::types::String ;

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::trf::rot::Quaternion ;
    using library::math::geom::d3::trf::rot::RotationVector ;
    using library::math::geom::d3::trf::rot::RotationMatrix ;
    
    using library::physics::units::Angle ;
    using library::physics::time::Scale ;
    using library::physics::time::Instant ;
    using library::physics::time::DateTime ;
    using library::physics::coord::Transform ;
    using library::physics::coord::Frame ;
    using library::physics::coord::frame::Provider ;
    using library::physics::coord::frame::provider::Static ;

    {

        const String name = "Custom" ;
        const bool isQuasiInertial = true ;
        const Shared<const Frame> parentFrameSPtr = Frame::GCRF() ;
        const Shared<const Provider> providerSPtr = std::make_shared<Static>(Static(Transform::Passive(Instant::J2000(), Vector3d(0.0, 0.0, 0.0), Vector3d::Zero(), Quaternion::RotationVector(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(-90.0))), Vector3d(0.0, 0.0, +2.0)))) ;
        
        const Shared<const Frame> customFrameSPtr = Frame::Construct(name, isQuasiInertial, parentFrameSPtr, providerSPtr) ;

        EXPECT_TRUE(customFrameSPtr->isDefined()) ;

        Frame::Destruct("Custom") ;

    }

    {

        // EXPECT_TRUE(Frame::ICRF()->isDefined()) ;
        EXPECT_TRUE(Frame::GCRF()->isDefined()) ;
        // EXPECT_TRUE(Frame::EME2000()->isDefined()) ;
        EXPECT_TRUE(Frame::TEME()->isDefined()) ;
        EXPECT_TRUE(Frame::TEMEOfEpoch(Instant::J2000())->isDefined()) ;
        EXPECT_TRUE(Frame::CIRF()->isDefined()) ;
        EXPECT_TRUE(Frame::TIRF()->isDefined()) ;
        EXPECT_TRUE(Frame::ITRF()->isDefined()) ;

    }

    {
        
        EXPECT_FALSE(Frame::Undefined()->isDefined()) ;

    }

}

TEST (Library_Physics_Coordinate_Frame, IsQuasiInertial)
{

    using library::core::types::Shared ;
    using library::core::types::Real ;
    using library::core::types::String ;

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::trf::rot::Quaternion ;
    using library::math::geom::d3::trf::rot::RotationVector ;
    using library::math::geom::d3::trf::rot::RotationMatrix ;
    
    using library::physics::units::Angle ;
    using library::physics::time::Scale ;
    using library::physics::time::Instant ;
    using library::physics::time::DateTime ;
    using library::physics::coord::Transform ;
    using library::physics::coord::Frame ;
    using library::physics::coord::frame::Provider ;
    using library::physics::coord::frame::provider::Static ;

    {

        const String name = "Custom" ;
        const bool isQuasiInertial = true ;
        const Shared<const Frame> parentFrameSPtr = Frame::GCRF() ;
        const Shared<const Provider> providerSPtr = std::make_shared<Static>(Static(Transform::Passive(Instant::J2000(), Vector3d(0.0, 0.0, 0.0), Vector3d::Zero(), Quaternion::RotationVector(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(-90.0))), Vector3d(0.0, 0.0, +2.0)))) ;
        
        const Shared<const Frame> customFrameSPtr = Frame::Construct(name, isQuasiInertial, parentFrameSPtr, providerSPtr) ;

        EXPECT_TRUE(customFrameSPtr->isQuasiInertial()) ;

        Frame::Destruct("Custom") ;

    }

    {

        // EXPECT_TRUE(Frame::ICRF()->isQuasiInertial()) ;
        EXPECT_TRUE(Frame::GCRF()->isQuasiInertial()) ;
        // EXPECT_TRUE(Frame::EME2000()->isQuasiInertial()) ;
        EXPECT_TRUE(Frame::TEME()->isQuasiInertial()) ;
        EXPECT_TRUE(Frame::TEMEOfEpoch(Instant::J2000())->isQuasiInertial()) ;
        EXPECT_FALSE(Frame::CIRF()->isQuasiInertial()) ;
        EXPECT_FALSE(Frame::TIRF()->isQuasiInertial()) ;
        EXPECT_FALSE(Frame::ITRF()->isQuasiInertial()) ;

    }

    {
        
        EXPECT_ANY_THROW(Frame::Undefined()->isQuasiInertial()) ;

    }

}

TEST (Library_Physics_Coordinate_Frame, HasParent)
{

    using library::core::types::Shared ;
    using library::core::types::Real ;
    using library::core::types::String ;

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::trf::rot::Quaternion ;
    using library::math::geom::d3::trf::rot::RotationVector ;
    using library::math::geom::d3::trf::rot::RotationMatrix ;
    
    using library::physics::units::Angle ;
    using library::physics::time::Scale ;
    using library::physics::time::Instant ;
    using library::physics::time::DateTime ;
    using library::physics::coord::Transform ;
    using library::physics::coord::Frame ;
    using library::physics::coord::frame::Provider ;
    using library::physics::coord::frame::provider::Static ;

    {

        const String name = "Custom" ;
        const bool isQuasiInertial = true ;
        const Shared<const Frame> parentFrameSPtr = Frame::GCRF() ;
        const Shared<const Provider> providerSPtr = std::make_shared<Static>(Static(Transform::Passive(Instant::J2000(), Vector3d(0.0, 0.0, 0.0), Vector3d::Zero(), Quaternion::RotationVector(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(-90.0))), Vector3d(0.0, 0.0, +2.0)))) ;
        
        const Shared<const Frame> customFrameSPtr = Frame::Construct(name, isQuasiInertial, parentFrameSPtr, providerSPtr) ;

        EXPECT_TRUE(customFrameSPtr->hasParent()) ;

        Frame::Destruct("Custom") ;

    }

    {

        // EXPECT_FALSE(Frame::ICRF()->hasParent()) ;
        EXPECT_FALSE(Frame::GCRF()->hasParent()) ;
        // EXPECT_TRUE(Frame::EME2000()->hasParent()) ;
        EXPECT_TRUE(Frame::TEME()->hasParent()) ;
        EXPECT_TRUE(Frame::TEMEOfEpoch(Instant::J2000())->hasParent()) ;
        EXPECT_TRUE(Frame::CIRF()->hasParent()) ;
        EXPECT_TRUE(Frame::TIRF()->hasParent()) ;
        EXPECT_TRUE(Frame::ITRF()->hasParent()) ;

    }

    {
        
        EXPECT_ANY_THROW(Frame::Undefined()->hasParent()) ;

    }

}

TEST (Library_Physics_Coordinate_Frame, AccessParent)
{

    using library::core::types::Shared ;
    using library::core::types::Real ;
    using library::core::types::String ;

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::trf::rot::Quaternion ;
    using library::math::geom::d3::trf::rot::RotationVector ;
    using library::math::geom::d3::trf::rot::RotationMatrix ;
    
    using library::physics::units::Angle ;
    using library::physics::time::Scale ;
    using library::physics::time::Instant ;
    using library::physics::time::DateTime ;
    using library::physics::coord::Transform ;
    using library::physics::coord::Frame ;
    using library::physics::coord::frame::Provider ;
    using library::physics::coord::frame::provider::Static ;

    {

        const String name = "Custom" ;
        const bool isQuasiInertial = true ;
        const Shared<const Frame> parentFrameSPtr = Frame::GCRF() ;
        const Shared<const Provider> providerSPtr = std::make_shared<Static>(Static(Transform::Passive(Instant::J2000(), Vector3d(0.0, 0.0, 0.0), Vector3d::Zero(), Quaternion::RotationVector(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(-90.0))), Vector3d(0.0, 0.0, +2.0)))) ;
        
        const Shared<const Frame> customFrameSPtr = Frame::Construct(name, isQuasiInertial, parentFrameSPtr, providerSPtr) ;

        EXPECT_EQ(parentFrameSPtr, customFrameSPtr->accessParent()) ;

        Frame::Destruct("Custom") ;

    }

    {

        // EXPECT_EQ(..., Frame::ICRF()->accessParent()) ;
        EXPECT_ANY_THROW(Frame::GCRF()->accessParent()) ;
        // EXPECT_EQ(..., Frame::EME2000()->accessParent()) ;
        EXPECT_EQ(Frame::ITRF(), Frame::TEME()->accessParent()) ;
        EXPECT_EQ(Frame::GCRF(), Frame::TEMEOfEpoch(Instant::J2000())->accessParent()) ;
        EXPECT_EQ(Frame::GCRF(), Frame::CIRF()->accessParent()) ;
        EXPECT_EQ(Frame::CIRF(), Frame::TIRF()->accessParent()) ;
        EXPECT_EQ(Frame::TIRF(), Frame::ITRF()->accessParent()) ;

    }

    {
        
        EXPECT_ANY_THROW(Frame::Undefined()->accessParent()) ;

    }

}

TEST (Library_Physics_Coordinate_Frame, GetName)
{

    using library::core::types::Shared ;
    using library::core::types::Real ;
    using library::core::types::String ;

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::trf::rot::Quaternion ;
    using library::math::geom::d3::trf::rot::RotationVector ;
    using library::math::geom::d3::trf::rot::RotationMatrix ;
    
    using library::physics::units::Angle ;
    using library::physics::time::Scale ;
    using library::physics::time::Instant ;
    using library::physics::time::DateTime ;
    using library::physics::coord::Transform ;
    using library::physics::coord::Frame ;
    using library::physics::coord::frame::Provider ;
    using library::physics::coord::frame::provider::Static ;

    {

        const String name = "Custom" ;
        const bool isQuasiInertial = true ;
        const Shared<const Frame> parentFrameSPtr = Frame::GCRF() ;
        const Shared<const Provider> providerSPtr = std::make_shared<Static>(Static(Transform::Passive(Instant::J2000(), Vector3d(0.0, 0.0, 0.0), Vector3d::Zero(), Quaternion::RotationVector(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(-90.0))), Vector3d(0.0, 0.0, +2.0)))) ;
        
        const Shared<const Frame> customFrameSPtr = Frame::Construct(name, isQuasiInertial, parentFrameSPtr, providerSPtr) ;

        EXPECT_EQ(name, customFrameSPtr->getName()) ;

        Frame::Destruct("Custom") ;

    }

    {

        // EXPECT_EQ("ICRF", Frame::ICRF()->getName()) ;
        EXPECT_EQ("GCRF", Frame::GCRF()->getName()) ;
        // EXPECT_EQ("EME2000", Frame::EME2000()->getName()) ;
        EXPECT_EQ("TEME", Frame::TEME()->getName()) ;
        EXPECT_EQ("TEMEOfEpoch @ 2000-01-01 12:00:00 [TT]", Frame::TEMEOfEpoch(Instant::J2000())->getName()) ;
        EXPECT_EQ("CIRF", Frame::CIRF()->getName()) ;
        EXPECT_EQ("TIRF", Frame::TIRF()->getName()) ;
        EXPECT_EQ("ITRF", Frame::ITRF()->getName()) ;

    }

    {
        
        EXPECT_ANY_THROW(Frame::Undefined()->getName()) ;

    }

}

TEST (Library_Physics_Coordinate_Frame, GetOriginIn)
{

    using library::core::types::Shared ;
    using library::core::types::Real ;
    using library::core::types::String ;

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::trf::rot::Quaternion ;
    using library::math::geom::d3::trf::rot::RotationVector ;
    using library::math::geom::d3::trf::rot::RotationMatrix ;
    
    using library::physics::units::Length ;
    using library::physics::units::Angle ;
    using library::physics::time::Scale ;
    using library::physics::time::Instant ;
    using library::physics::time::DateTime ;
    using library::physics::coord::Transform ;
    using library::physics::coord::Position ;
    using library::physics::coord::Axes ;
    using library::physics::coord::Frame ;
    using library::physics::coord::frame::Provider ;
    using library::physics::coord::frame::provider::Static ;

    {

        const Position referenceOrigin = Position::Meters({ 0.0, 0.0, 0.0 }, Frame::GCRF()) ;

        EXPECT_EQ(referenceOrigin, Frame::ITRF()->getOriginIn(Frame::GCRF(), Instant::J2000())) ;

    }

    {

        const Position referenceOrigin = Position::Meters({ 0.0, 0.0, 0.0 }, Frame::ITRF()) ;

        EXPECT_EQ(referenceOrigin, Frame::GCRF()->getOriginIn(Frame::ITRF(), Instant::J2000())) ;

    }

    {

        const Instant epoch = Instant::J2000() ;

        {

            const String name = "Custom A" ;
            const bool isQuasiInertial = true ;
            const Shared<const Frame> parentFrameSPtr = Frame::GCRF() ;
            const Shared<const Provider> providerSPtr = std::make_shared<Static>(Static(Transform::Passive(epoch, Vector3d(0.0, -1.0, 0.0), Vector3d::Zero(), Quaternion::RotationVector(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(+90.0))), Vector3d::Zero()))) ;
            
            Frame::Construct(name, isQuasiInertial, parentFrameSPtr, providerSPtr) ;

            const Position origin = Frame::WithName("Custom A")->getOriginIn(Frame::GCRF(), epoch) ;

            const Position referenceOrigin = Position::Meters({ 0.0, +1.0, 0.0 }, Frame::GCRF()) ;

            EXPECT_TRUE(origin.isNear(referenceOrigin, Length::Meters(Real::Epsilon()))) << origin ;

        }

        {

            const String name = "Custom B" ;
            const bool isQuasiInertial = true ;
            const Shared<const Frame> parentFrameSPtr = Frame::GCRF() ;
            const Shared<const Provider> providerSPtr = std::make_shared<Static>(Static(Transform::Passive(epoch, Vector3d(-1.0, 0.0, 0.0), Vector3d::Zero(), Quaternion::RotationVector(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(-90.0))), Vector3d::Zero()))) ;
            
            Frame::Construct(name, isQuasiInertial, parentFrameSPtr, providerSPtr) ;

            const Position origin = Frame::WithName("Custom B")->getOriginIn(Frame::GCRF(), epoch) ;

            const Position referenceOrigin = Position::Meters({ +1.0, 0.0, 0.0 }, Frame::GCRF()) ;

            EXPECT_TRUE(origin.isNear(referenceOrigin, Length::Meters(Real::Epsilon()))) << origin ;

        }

        const Position origin = Frame::WithName("Custom B")->getOriginIn(Frame::WithName("Custom A"), epoch) ;

        const Position referenceOrigin = Position::Meters({ -1.0, -1.0, 0.0 }, Frame::WithName("Custom A")) ;

        EXPECT_TRUE(origin.isNear(referenceOrigin, Length::Meters(Real::Epsilon()))) << origin ;

        Frame::Destruct("Custom A") ;
        Frame::Destruct("Custom B") ;

    }

    {

        EXPECT_ANY_THROW(Frame::Undefined()->getOriginIn(Frame::Undefined(), Instant::J2000())) ;

    }

}

TEST (Library_Physics_Coordinate_Frame, GetVelocityIn)
{

    using library::core::types::Shared ;
    using library::core::types::Real ;
    using library::core::types::String ;

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::trf::rot::Quaternion ;
    using library::math::geom::d3::trf::rot::RotationVector ;
    using library::math::geom::d3::trf::rot::RotationMatrix ;
    
    using library::physics::units::Length ;
    using library::physics::units::Angle ;
    using library::physics::time::Scale ;
    using library::physics::time::Instant ;
    using library::physics::time::DateTime ;
    using library::physics::coord::Transform ;
    using library::physics::coord::Velocity ;
    using library::physics::coord::Axes ;
    using library::physics::coord::Frame ;
    using library::physics::coord::frame::Provider ;
    using library::physics::coord::frame::provider::Static ;

    {

        const Velocity referenceVelocity = Velocity::MetersPerSecond({ 0.0, 0.0, 0.0 }, Frame::GCRF()) ;

        EXPECT_EQ(referenceVelocity, Frame::ITRF()->getVelocityIn(Frame::GCRF(), Instant::J2000())) ;

    }

    {

        const Velocity referenceVelocity = Velocity::MetersPerSecond({ 0.0, 0.0, 0.0 }, Frame::ITRF()) ;

        EXPECT_EQ(referenceVelocity, Frame::GCRF()->getVelocityIn(Frame::ITRF(), Instant::J2000())) ;

    }

    {

        const Instant epoch = Instant::J2000() ;

        {

            const String name = "Custom A" ;
            const bool isQuasiInertial = true ;
            const Shared<const Frame> parentFrameSPtr = Frame::GCRF() ;
            const Shared<const Provider> providerSPtr = std::make_shared<Static>(Static(Transform::Passive(epoch, Vector3d(0.0, -1.0, 0.0), Vector3d(-1.0, 0.0, 0.0), Quaternion::RotationVector(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(+90.0))), Vector3d::Zero()))) ;
            
            Frame::Construct(name, isQuasiInertial, parentFrameSPtr, providerSPtr) ;

            const Velocity velocity = Frame::WithName("Custom A")->getVelocityIn(Frame::GCRF(), epoch) ;

            const Velocity referenceVelocity = Velocity::MetersPerSecond({ +1.0, 0.0, 0.0 }, Frame::GCRF()) ;

            EXPECT_TRUE(velocity.getCoordinates().isNear(referenceVelocity.getCoordinates(), Real::Epsilon())) << velocity ;

        }

        {

            const String name = "Custom B" ;
            const bool isQuasiInertial = true ;
            const Shared<const Frame> parentFrameSPtr = Frame::GCRF() ;
            const Shared<const Provider> providerSPtr = std::make_shared<Static>(Static(Transform::Passive(epoch, Vector3d(-1.0, 0.0, 0.0), Vector3d(0.0, -1.0, 0.0), Quaternion::RotationVector(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(-90.0))), Vector3d::Zero()))) ;
            
            Frame::Construct(name, isQuasiInertial, parentFrameSPtr, providerSPtr) ;

            const Velocity velocity = Frame::WithName("Custom B")->getVelocityIn(Frame::GCRF(), epoch) ;

            const Velocity referenceVelocity = Velocity::MetersPerSecond({ 0.0, +1.0, 0.0 }, Frame::GCRF()) ;

            EXPECT_TRUE(velocity.getCoordinates().isNear(referenceVelocity.getCoordinates(), Real::Epsilon())) << velocity ;

        }

        const Velocity velocity = Frame::WithName("Custom B")->getVelocityIn(Frame::WithName("Custom A"), epoch) ;

        const Velocity referenceVelocity = Velocity::MetersPerSecond({ +1.0, +1.0, 0.0 }, Frame::WithName("Custom A")) ;

        EXPECT_TRUE(velocity.getCoordinates().isNear(referenceVelocity.getCoordinates(), Real::Epsilon())) << velocity ;

        Frame::Destruct("Custom A") ;
        Frame::Destruct("Custom B") ;

    }

    {

        EXPECT_ANY_THROW(Frame::Undefined()->getVelocityIn(Frame::Undefined(), Instant::J2000())) ;

    }

}

TEST (Library_Physics_Coordinate_Frame, GetAxesIn)
{

    using library::core::types::Shared ;
    using library::core::types::Real ;
    using library::core::types::String ;

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::trf::rot::Quaternion ;
    using library::math::geom::d3::trf::rot::RotationVector ;
    using library::math::geom::d3::trf::rot::RotationMatrix ;
    
    using library::physics::units::Length ;
    using library::physics::units::Angle ;
    using library::physics::time::Scale ;
    using library::physics::time::Instant ;
    using library::physics::time::DateTime ;
    using library::physics::coord::Transform ;
    using library::physics::coord::Position ;
    using library::physics::coord::Axes ;
    using library::physics::coord::Frame ;
    using library::physics::coord::frame::Provider ;
    using library::physics::coord::frame::provider::Static ;

    {

        const Instant epoch = Instant::J2000() ;

        {

            const String name = "Custom A" ;
            const bool isQuasiInertial = true ;
            const Shared<const Frame> parentFrameSPtr = Frame::GCRF() ;
            const Shared<const Provider> providerSPtr = std::make_shared<Static>(Static(Transform::Passive(epoch, Vector3d(0.0, -1.0, 0.0), Vector3d::Zero(), Quaternion::RotationVector(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(+90.0))), Vector3d::Zero()))) ;
            
            Frame::Construct(name, isQuasiInertial, parentFrameSPtr, providerSPtr) ;

            const Axes axes = Frame::WithName("Custom A")->getAxesIn(Frame::GCRF(), epoch) ;

            const Axes referenceAxes = Axes({ 0.0, +1.0, 0.0 }, { -1.0, 0.0, 0.0 }, { 0.0, 0.0, +1.0 }, Frame::GCRF()) ;

            EXPECT_TRUE(axes.x().isNear(referenceAxes.x(), Real::Epsilon())) << axes ;
            EXPECT_TRUE(axes.y().isNear(referenceAxes.y(), Real::Epsilon())) << axes ;
            EXPECT_TRUE(axes.z().isNear(referenceAxes.z(), Real::Epsilon())) << axes ;

        }

        {

            const String name = "Custom B" ;
            const bool isQuasiInertial = true ;
            const Shared<const Frame> parentFrameSPtr = Frame::GCRF() ;
            const Shared<const Provider> providerSPtr = std::make_shared<Static>(Static(Transform::Passive(epoch, Vector3d(-1.0, 0.0, 0.0), Vector3d::Zero(), Quaternion::RotationVector(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(-90.0))), Vector3d::Zero()))) ;
            
            Frame::Construct(name, isQuasiInertial, parentFrameSPtr, providerSPtr) ;

            const Axes axes = Frame::WithName("Custom B")->getAxesIn(Frame::GCRF(), epoch) ;

            const Axes referenceAxes = Axes({ 0.0, -1.0, 0.0 }, { +1.0, 0.0, 0.0 }, { 0.0, 0.0, +1.0 }, Frame::GCRF()) ;

            EXPECT_TRUE(axes.x().isNear(referenceAxes.x(), Real::Epsilon())) << axes ;
            EXPECT_TRUE(axes.y().isNear(referenceAxes.y(), Real::Epsilon())) << axes ;
            EXPECT_TRUE(axes.z().isNear(referenceAxes.z(), Real::Epsilon())) << axes ;

        }

        const Axes axes = Frame::WithName("Custom B")->getAxesIn(Frame::WithName("Custom A"), epoch) ;

        const Axes referenceAxes = Axes({ -1.0, 0.0, 0.0 }, { 0.0, -1.0, 0.0 }, { 0.0, 0.0, +1.0 }, Frame::GCRF()) ;

        EXPECT_TRUE(axes.x().isNear(referenceAxes.x(), Real::Epsilon())) << axes ;
        EXPECT_TRUE(axes.y().isNear(referenceAxes.y(), Real::Epsilon())) << axes ;
        EXPECT_TRUE(axes.z().isNear(referenceAxes.z(), Real::Epsilon())) << axes ;

        Frame::Destruct("Custom A") ;
        Frame::Destruct("Custom B") ;

    }

    {

        EXPECT_ANY_THROW(Frame::Undefined()->getAxesIn(Frame::Undefined(), Instant::J2000())) ;

    }

}

TEST (Library_Physics_Coordinate_Frame, GetTransformTo)
{

    using library::core::types::Shared ;
    using library::core::types::Real ;

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::trf::rot::Quaternion ;

    using library::physics::units::Angle ;
    using library::physics::time::Instant ;
    using library::physics::coord::Transform ;
    using library::physics::coord::Frame ;

    {

        const Transform transform = Frame::GCRF()->getTransformTo(Frame::GCRF(), Instant::J2000()) ;

        EXPECT_TRUE(transform.isIdentity()) ;

    }

    {

        const Instant instant = Instant::J2000() ;

        const Shared<const Frame> gcrfSPtr = Frame::GCRF() ;
        const Shared<const Frame> itrfSPtr = Frame::ITRF() ;
        
        const Transform transform = itrfSPtr->getTransformTo(gcrfSPtr, instant) ;

        EXPECT_EQ(instant, transform.getInstant()) ;

        EXPECT_TRUE(transform.getTranslation().isNear(Vector3d(+0.0, +0.0, +0.0), Real::Epsilon())) ;
        EXPECT_TRUE(transform.getVelocity().isNear(Vector3d(+0.0, +0.0, +0.0), Real::Epsilon())) ;
        EXPECT_TRUE(transform.getOrientation().isNear(Quaternion::XYZS(-1.86147346436534e-05, 8.45983422546411e-07, 0.641490222201766, 0.767131210727542), Angle::Degrees(Real::Epsilon()))) ;
        EXPECT_TRUE(transform.getAngularVelocity().isNear(Vector3d(1.96489918038813e-09, 2.04221635598212e-09, -7.29211506735101e-05), Real::Epsilon())) ;

    }

    {

        EXPECT_ANY_THROW(Frame::Undefined()->getTransformTo(Frame::GCRF(), Instant::J2000())) ;
        EXPECT_ANY_THROW(Frame::GCRF()->getTransformTo(Frame::Undefined(), Instant::J2000())) ;
        EXPECT_ANY_THROW(Frame::GCRF()->getTransformTo(Frame::GCRF(), Instant::Undefined())) ;

    }

}

TEST (Library_Physics_Coordinate_Frame, Undefined)
{

    using library::physics::coord::Frame ;

    {

        EXPECT_FALSE(Frame::Undefined()->isDefined()) ;

    }

}

// TEST (Library_Physics_Coordinate_Frame, ICRF)
// {

//     using library::physics::coord::Frame ;

//     {

//         EXPECT_TRUE(Frame::ICRF()->isDefined()) ;

//     }

// }

TEST (Library_Physics_Coordinate_Frame, GCRF)
{

    using library::physics::coord::Frame ;

    {

        EXPECT_TRUE(Frame::GCRF()->isDefined()) ;

    }

}

// TEST (Library_Physics_Coordinate_Frame, EME2000)
// {

//     using library::physics::coord::Frame ;

//     {

//         EXPECT_TRUE(Frame::EME2000()->isDefined()) ;

//     }

// }

TEST (Library_Physics_Coordinate_Frame, TEME)
{

    using library::physics::coord::Frame ;

    {

        EXPECT_TRUE(Frame::TEME()->isDefined()) ;

    }

}

TEST (Library_Physics_Coordinate_Frame, TEMEOfEpoch)
{

    using library::physics::time::Instant ;
    using library::physics::coord::Frame ;

    {

        EXPECT_TRUE(Frame::TEMEOfEpoch(Instant::J2000())->isDefined()) ;

    }

}

TEST (Library_Physics_Coordinate_Frame, CIRF)
{

    using library::physics::coord::Frame ;

    {

        EXPECT_TRUE(Frame::CIRF()->isDefined()) ;

    }

}

TEST (Library_Physics_Coordinate_Frame, TIRF)
{

    using library::physics::coord::Frame ;

    {

        EXPECT_TRUE(Frame::TIRF()->isDefined()) ;

    }

}

TEST (Library_Physics_Coordinate_Frame, ITRF)
{

    using library::physics::coord::Frame ;

    {

        EXPECT_TRUE(Frame::ITRF()->isDefined()) ;

    }

}

TEST (Library_Physics_Coordinate_Frame, WithName)
{

    using library::physics::coord::Frame ;

    {

        EXPECT_TRUE(Frame::WithName("ITRF")->isDefined()) ;

    }

}

TEST (Library_Physics_Coordinate_Frame, Exists)
{

    using library::core::types::Shared ;
    using library::core::types::Real ;
    using library::core::types::String ;

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::trf::rot::Quaternion ;
    using library::math::geom::d3::trf::rot::RotationVector ;
    using library::math::geom::d3::trf::rot::RotationMatrix ;
    
    using library::physics::units::Angle ;
    using library::physics::time::Scale ;
    using library::physics::time::Instant ;
    using library::physics::time::DateTime ;
    using library::physics::coord::Transform ;
    using library::physics::coord::Frame ;
    using library::physics::coord::frame::Provider ;
    using library::physics::coord::frame::provider::Static ;

    {

        const String name = "Custom" ;
        const bool isQuasiInertial = true ;
        const Shared<const Frame> parentFrameSPtr = Frame::GCRF() ;
        const Shared<const Provider> providerSPtr = std::make_shared<Static>(Static(Transform::Passive(Instant::J2000(), Vector3d(0.0, 0.0, 0.0), Vector3d::Zero(), Quaternion::RotationVector(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(-90.0))), Vector3d(0.0, 0.0, +2.0)))) ;
        
        EXPECT_FALSE(Frame::Exists("Custom")) ;

        Frame::Construct(name, isQuasiInertial, parentFrameSPtr, providerSPtr) ;

        EXPECT_TRUE(Frame::Exists("Custom")) ;

        Frame::Destruct("Custom") ;

        EXPECT_FALSE(Frame::Exists("Custom")) ;

    }

    {

        EXPECT_ANY_THROW(Frame::Exists("")) ;
        
    }

}

TEST (Library_Physics_Coordinate_Frame, Construct)
{

    using library::core::types::Shared ;
    using library::core::types::Real ;
    using library::core::types::String ;

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::trf::rot::Quaternion ;
    using library::math::geom::d3::trf::rot::RotationVector ;
    using library::math::geom::d3::trf::rot::RotationMatrix ;
    
    using library::physics::units::Angle ;
    using library::physics::time::Scale ;
    using library::physics::time::Instant ;
    using library::physics::time::DateTime ;
    using library::physics::coord::Transform ;
    using library::physics::coord::Frame ;
    using library::physics::coord::frame::Provider ;
    using library::physics::coord::frame::provider::Static ;

    {

        const String name = "Custom" ;
        const bool isQuasiInertial = true ;
        const Shared<const Frame> parentFrameSPtr = Frame::GCRF() ;
        const Shared<const Provider> providerSPtr = std::make_shared<Static>(Static(Transform::Passive(Instant::J2000(), Vector3d(0.0, 0.0, 0.0), Vector3d::Zero(), Quaternion::RotationVector(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(-90.0))), Vector3d(0.0, 0.0, +2.0)))) ;
        
        EXPECT_NO_THROW(Frame::Construct(name, isQuasiInertial, parentFrameSPtr, providerSPtr)) ;
        EXPECT_ANY_THROW(Frame::Construct(name, isQuasiInertial, parentFrameSPtr, providerSPtr)) ;

        Frame::Destruct("Custom") ;

    }

    {

        const String name = "" ;
        const bool isQuasiInertial = true ;
        const Shared<const Frame> parentFrameSPtr = Frame::GCRF() ;
        const Shared<const Provider> providerSPtr = std::make_shared<Static>(Static(Transform::Passive(Instant::J2000(), Vector3d(0.0, 0.0, 0.0), Vector3d::Zero(), Quaternion::RotationVector(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(-90.0))), Vector3d(0.0, 0.0, +2.0)))) ;
        
        EXPECT_ANY_THROW(Frame::Construct(name, isQuasiInertial, parentFrameSPtr, providerSPtr)) ;

    }

}

TEST (Library_Physics_Coordinate_Frame, Destruct)
{
    
    using library::core::types::Shared ;
    using library::core::types::Real ;
    using library::core::types::String ;

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::trf::rot::Quaternion ;
    using library::math::geom::d3::trf::rot::RotationVector ;
    using library::math::geom::d3::trf::rot::RotationMatrix ;
    
    using library::physics::units::Angle ;
    using library::physics::time::Scale ;
    using library::physics::time::Instant ;
    using library::physics::time::DateTime ;
    using library::physics::coord::Transform ;
    using library::physics::coord::Frame ;
    using library::physics::coord::frame::Provider ;
    using library::physics::coord::frame::provider::Static ;

    {

        const String name = "Custom" ;
        const bool isQuasiInertial = true ;
        const Shared<const Frame> parentFrameSPtr = Frame::GCRF() ;
        const Shared<const Provider> providerSPtr = std::make_shared<Static>(Static(Transform::Passive(Instant::J2000(), Vector3d(0.0, 0.0, 0.0), Vector3d::Zero(), Quaternion::RotationVector(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(-90.0))), Vector3d(0.0, 0.0, +2.0)))) ;
        
        const Shared<const Frame> customFrameSPtr = Frame::Construct(name, isQuasiInertial, parentFrameSPtr, providerSPtr) ;

        EXPECT_NO_THROW(Frame::Destruct("Custom")) ;
        EXPECT_ANY_THROW(Frame::Destruct("Custom")) ;

    }

    {

        EXPECT_ANY_THROW(Frame::Destruct("")) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Physics_Coordinate_Frame, Test_1)
{

    using library::core::types::Shared ;
    using library::core::types::Real ;
    using library::core::types::String ;

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::trf::rot::Quaternion ;
    using library::math::geom::d3::trf::rot::RotationVector ;
    using library::math::geom::d3::trf::rot::RotationMatrix ;
    
    using library::physics::units::Angle ;
    using library::physics::time::Instant ;
    using library::physics::coord::Transform ;
    using library::physics::coord::Frame ;
    using library::physics::coord::frame::Provider ;
    using library::physics::coord::frame::provider::Static ;

    // Pure static translation

    {

        const String name = "Custom" ;
        const bool isQuasiInertial = true ;
        const Shared<const Frame> parentFrameSPtr = Frame::GCRF() ;
        const Shared<const Provider> providerSPtr = std::make_shared<Static>(Static(Transform::Passive(Instant::J2000(), Vector3d(-1.0, +0.0, +0.0), Vector3d::Zero(), Quaternion::Unit(), Vector3d::Zero()))) ;
        
        const Shared<const Frame> customFrameSPtr = Frame::Construct(name, isQuasiInertial, parentFrameSPtr, providerSPtr) ;

        EXPECT_TRUE(customFrameSPtr->isDefined()) ;

        // Position

        {

            const Vector3d x_CUSTOM = { +1.0, +0.0, +0.0 } ;
        
            const Vector3d x_GCRF = customFrameSPtr->getTransformTo(Frame::GCRF(), Instant::J2000()).applyToPosition(x_CUSTOM) ;
            
            EXPECT_TRUE(x_GCRF.isNear(Vector3d(+2.0, +0.0, +0.0), Real::Epsilon())) << x_GCRF.toString() ;

        }

        // Velocity

        {

            const Vector3d x_CUSTOM = { +1.0, +0.0, +0.0 } ;
            const Vector3d v_CUSTOM = { +1.0, +0.0, +0.0 } ;

            const Vector3d v_GCRF = customFrameSPtr->getTransformTo(Frame::GCRF(), Instant::J2000()).applyToVelocity(x_CUSTOM, v_CUSTOM) ;
            
            EXPECT_TRUE(v_GCRF.isNear(Vector3d(+1.0, +0.0, +0.0), Real::Epsilon())) << v_GCRF.toString() ;

        }

        // Vector

        {

            const Vector3d u_CUSTOM = { +1.0, +0.0, +0.0 } ;

            const Vector3d u_GCRF = customFrameSPtr->getTransformTo(Frame::GCRF(), Instant::J2000()).applyToVector(u_CUSTOM) ;

            EXPECT_TRUE(u_GCRF.isNear(Vector3d(+1.0, +0.0, +0.0), Real::Epsilon())) << u_GCRF.toString() ;

        }

        Frame::Destruct("Custom") ;

    }

    // Pure dynamic translation

    {

        const String name = "Custom" ;
        const bool isQuasiInertial = true ;
        const Shared<const Frame> parentFrameSPtr = Frame::GCRF() ;
        const Shared<const Provider> providerSPtr = std::make_shared<Static>(Static(Transform::Passive(Instant::J2000(), Vector3d(-1.0, +0.0, +0.0), Vector3d(-2.0, +0.0, +0.0), Quaternion::Unit(), Vector3d::Zero()))) ;
        
        const Shared<const Frame> customFrameSPtr = Frame::Construct(name, isQuasiInertial, parentFrameSPtr, providerSPtr) ;

        EXPECT_TRUE(customFrameSPtr->isDefined()) ;

        // Position

        {

            const Vector3d x_CUSTOM = { +1.0, +0.0, +0.0 } ;
        
            const Vector3d x_GCRF = customFrameSPtr->getTransformTo(Frame::GCRF(), Instant::J2000()).applyToPosition(x_CUSTOM) ;
            
            EXPECT_TRUE(x_GCRF.isNear(Vector3d(+2.0, +0.0, +0.0), Real::Epsilon())) << x_GCRF.toString() ;

        }

        // Velocity

        {

            const Vector3d x_CUSTOM = { +1.0, +0.0, +0.0 } ;
            const Vector3d v_CUSTOM = { +0.0, +1.0, +0.0 } ;

            const Vector3d v_GCRF = customFrameSPtr->getTransformTo(Frame::GCRF(), Instant::J2000()).applyToVelocity(x_CUSTOM, v_CUSTOM) ;
            
            EXPECT_TRUE(v_GCRF.isNear(Vector3d(+2.0, +1.0, +0.0), Real::Epsilon())) << v_GCRF.toString() ;

        }

        // Vector

        {

            const Vector3d u_CUSTOM = { +1.0, +0.0, +0.0 } ;

            const Vector3d u_GCRF = customFrameSPtr->getTransformTo(Frame::GCRF(), Instant::J2000()).applyToVector(u_CUSTOM) ;

            EXPECT_TRUE(u_GCRF.isNear(Vector3d(+1.0, +0.0, +0.0), Real::Epsilon())) << u_GCRF.toString() ;

        }

        Frame::Destruct("Custom") ;

    }

    // Pure static rotation

    {

        const String name = "Custom" ;
        const bool isQuasiInertial = true ;
        const Shared<const Frame> parentFrameSPtr = Frame::GCRF() ;
        const Shared<const Provider> providerSPtr = std::make_shared<Static>(Static(Transform::Passive(Instant::J2000(), Vector3d::Zero(), Vector3d::Zero(), Quaternion::RotationVector(RotationVector({ +0.0, +0.0, +1.0 }, Angle::Degrees(90.0))), Vector3d::Zero()))) ;
        
        const Shared<const Frame> customFrameSPtr = Frame::Construct(name, isQuasiInertial, parentFrameSPtr, providerSPtr) ;

        EXPECT_TRUE(customFrameSPtr->isDefined()) ;

        // Position
        
        {

            const Vector3d x_CUSTOM = { +1.0, +0.0, +0.0 } ;
        
            const Vector3d x_GCRF = customFrameSPtr->getTransformTo(Frame::GCRF(), Instant::J2000()).applyToPosition(x_CUSTOM) ;
            
            EXPECT_TRUE(x_GCRF.isNear(Vector3d(+0.0, +1.0, +0.0), Real::Epsilon())) << x_GCRF.toString() ;

        }

        // Velocity

        {

            const Vector3d x_CUSTOM = { +1.0, +0.0, +0.0 } ;
            const Vector3d v_CUSTOM = { +1.0, +0.0, +0.0 } ;

            const Vector3d v_GCRF = customFrameSPtr->getTransformTo(Frame::GCRF(), Instant::J2000()).applyToVelocity(x_CUSTOM, v_CUSTOM) ;
            
            EXPECT_TRUE(v_GCRF.isNear(Vector3d(+0.0, +1.0, +0.0), Real::Epsilon())) << v_GCRF.toString() ;

        }

        // Vector

        {

            const Vector3d u_CUSTOM = { +1.0, +0.0, +0.0 } ;

            const Vector3d u_GCRF = customFrameSPtr->getTransformTo(Frame::GCRF(), Instant::J2000()).applyToVector(u_CUSTOM) ;

            EXPECT_TRUE(u_GCRF.isNear(Vector3d(+0.0, +1.0, +0.0), Real::Epsilon())) << u_GCRF.toString() ;

        }

        Frame::Destruct("Custom") ;

    }

    // Pure dynamic rotation

    {

        const String name = "Custom" ;
        const bool isQuasiInertial = true ;
        const Shared<const Frame> parentFrameSPtr = Frame::GCRF() ;
        const Shared<const Provider> providerSPtr = std::make_shared<Static>(Static(Transform::Passive(Instant::J2000(), Vector3d::Zero(), Vector3d::Zero(), Quaternion::Unit(), Vector3d(+0.0, +0.0, -1.0)))) ;
        
        const Shared<const Frame> customFrameSPtr = Frame::Construct(name, isQuasiInertial, parentFrameSPtr, providerSPtr) ;

        EXPECT_TRUE(customFrameSPtr->isDefined()) ;

        // Position
        
        {

            const Vector3d x_CUSTOM = { +1.0, +0.0, +0.0 } ;
        
            const Vector3d x_GCRF = customFrameSPtr->getTransformTo(Frame::GCRF(), Instant::J2000()).applyToPosition(x_CUSTOM) ;
            
            EXPECT_TRUE(x_GCRF.isNear(Vector3d(+1.0, +0.0, +0.0), Real::Epsilon())) << x_GCRF.toString() ;

        }

        // Velocity

        {

            const Vector3d x_CUSTOM = { +1.0, +0.0, +0.0 } ;
            const Vector3d v_CUSTOM = { +1.0, +0.0, +0.0 } ;

            const Vector3d v_GCRF = customFrameSPtr->getTransformTo(Frame::GCRF(), Instant::J2000()).applyToVelocity(x_CUSTOM, v_CUSTOM) ;
            
            EXPECT_TRUE(v_GCRF.isNear(Vector3d(+1.0, -1.0, +0.0), Real::Epsilon())) << v_GCRF.toString() ;

        }

        // Vector

        {

            const Vector3d u_CUSTOM = { +1.0, +0.0, +0.0 } ;

            const Vector3d u_GCRF = customFrameSPtr->getTransformTo(Frame::GCRF(), Instant::J2000()).applyToVector(u_CUSTOM) ;

            EXPECT_TRUE(u_GCRF.isNear(Vector3d(+1.0, +0.0, +0.0), Real::Epsilon())) << u_GCRF.toString() ;

        }

        Frame::Destruct("Custom") ;

    }

    {

        const String name = "Custom" ;
        const bool isQuasiInertial = true ;
        const Shared<const Frame> parentFrameSPtr = Frame::GCRF() ;
        const Shared<const Provider> providerSPtr = std::make_shared<Static>(Static(Transform::Passive(Instant::J2000(), Vector3d(0.0, 0.0, 0.0), Vector3d::Zero(), Quaternion::Unit(), Vector3d(0.0, 0.0, +2.0)))) ;
        
        const Shared<const Frame> customFrameSPtr = Frame::Construct(name, isQuasiInertial, parentFrameSPtr, providerSPtr) ;

        EXPECT_TRUE(customFrameSPtr->isDefined()) ;

        // Position
        
        {

            const Vector3d x_CUSTOM = { 0.0, +1.0, 0.0 } ;
        
            const Vector3d x_GCRF = customFrameSPtr->getTransformTo(Frame::GCRF(), Instant::J2000()).applyToPosition(x_CUSTOM) ;
            
            EXPECT_TRUE(x_GCRF.isNear(Vector3d(0.0, +1.0, 0.0), Real::Epsilon())) << x_GCRF.toString() ;

        }

        // Velocity

        {

            const Vector3d x_CUSTOM = { +0.0, +1.0, +0.0 } ;
            const Vector3d v_CUSTOM = { -2.0, +1.0, +0.0 } ;

            const Vector3d v_GCRF = customFrameSPtr->getTransformTo(Frame::GCRF(), Instant::J2000()).applyToVelocity(x_CUSTOM, v_CUSTOM) ;
            
            EXPECT_TRUE(v_GCRF.isNear(Vector3d(-4.0, +1.0, 0.0), Real::Epsilon())) << v_GCRF.toString() ;

        }

        // Vector

        {

            const Vector3d v_CUSTOM = { 0.0, +1.0, 0.0 } ;

            const Vector3d v_GCRF = customFrameSPtr->getTransformTo(Frame::GCRF(), Instant::J2000()).applyToVector(v_CUSTOM) ;

            EXPECT_TRUE(v_GCRF.isNear(Vector3d(0.0, +1.0, 0.0), Real::Epsilon())) << v_GCRF.toString() ;

        }

        Frame::Destruct("Custom") ;

    }

    {

        const String name = "Custom" ;
        const bool isQuasiInertial = true ;
        const Shared<const Frame> parentFrameSPtr = Frame::GCRF() ;
        const Shared<const Provider> providerSPtr = std::make_shared<Static>(Static(Transform::Passive(Instant::J2000(), Vector3d(0.0, 0.0, 0.0), Vector3d::Zero(), Quaternion::RotationVector(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(-90.0))), Vector3d(0.0, 0.0, +2.0)))) ;
        
        const Shared<const Frame> customFrameSPtr = Frame::Construct(name, isQuasiInertial, parentFrameSPtr, providerSPtr) ;

        EXPECT_TRUE(customFrameSPtr->isDefined()) ;

        // Position
        
        {

            const Vector3d x_CUSTOM = { 0.0, +1.0, 0.0 } ;
        
            const Vector3d x_GCRF = customFrameSPtr->getTransformTo(Frame::GCRF(), Instant::J2000()).applyToPosition(x_CUSTOM) ;
            
            EXPECT_TRUE(x_GCRF.isNear(Vector3d(+1.0, 0.0, 0.0), Real::Epsilon())) << x_GCRF.toString() ;

        }

        // Velocity

        {

            const Vector3d x_CUSTOM = { +0.0, +1.0, +0.0 } ;
            const Vector3d v_CUSTOM = { -2.0, +1.0, +0.0 } ;

            const Vector3d v_GCRF = customFrameSPtr->getTransformTo(Frame::GCRF(), Instant::J2000()).applyToVelocity(x_CUSTOM, v_CUSTOM) ;
            
            EXPECT_TRUE(v_GCRF.isNear(Vector3d(+1.0, +4.0, 0.0), Real::Epsilon())) << v_GCRF.toString() ;

        }

        // Vector

        {

            const Vector3d v_CUSTOM = { 0.0, +1.0, 0.0 } ;

            const Vector3d v_GCRF = customFrameSPtr->getTransformTo(Frame::GCRF(), Instant::J2000()).applyToVector(v_CUSTOM) ;

            EXPECT_TRUE(v_GCRF.isNear(Vector3d(+1.0, 0.0, 0.0), Real::Epsilon())) << v_GCRF.toString() ;

        }

        Frame::Destruct("Custom") ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////