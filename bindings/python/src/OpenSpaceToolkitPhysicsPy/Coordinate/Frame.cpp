////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           bindings/python/src/OpenSpaceToolkitPhysicsPy/Coordinate/Frame.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkitPhysicsPy/Coordinate/Frame/Providers.cpp>
#include <OpenSpaceToolkitPhysicsPy/Coordinate/Frame/Provider.cpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitPhysicsPy_Coordinate_Frame           ( )
{

    using namespace boost::python ;

    using ostk::core::types::Shared ;
    using ostk::core::types::String ;

    using ostk::physics::coord::Frame ;
    using ostk::physics::coord::frame::Provider ;

    // scope in_Frame = class_<Frame, Shared<Frame>>("Frame", init<String&, bool, Shared<const Frame>&, Shared<Provider>&>())
    // scope in_Frame = class_<Frame, Shared<Frame>, boost::noncopyable>("Frame", init<String&, bool, Shared<const Frame>&, Shared<Provider>&>())
    // scope in_Frame = class_<Frame>("Frame", init<String&, bool, Shared<const Frame>&, Shared<const Provider>&>())
    scope in_Frame = class_<Frame, boost::noncopyable>("Frame", no_init)

        .def(self == self)
        .def(self != self)

        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))

        .def("isDefined", &Frame::isDefined)
        .def("isQuasiInertial", &Frame::isQuasiInertial)
        .def("hasParent", &Frame::hasParent)

        .def("accessParent", &Frame::accessParent)
        .def("accessAncestor", &Frame::accessAncestor)
        .def("accessProvider", &Frame::accessProvider)
        .def("getName", &Frame::getName)
        .def("getOriginIn", &Frame::getOriginIn)
        .def("getVelocityIn", &Frame::getVelocityIn)
        .def("getAxesIn", &Frame::getAxesIn)
        .def("getTransformTo", &Frame::getTransformTo)

        .def("Undefined", &Frame::Undefined).staticmethod("Undefined")
        // .def("ICRF", &Frame::ICRF).staticmethod("ICRF")
        .def("GCRF", &Frame::GCRF).staticmethod("GCRF")
        // .def("EME2000", &Frame::EME2000).staticmethod("EME2000")
        .def("TEME", &Frame::TEME).staticmethod("TEME")
        .def("TEMEOfEpoch", &Frame::TEMEOfEpoch).staticmethod("TEMEOfEpoch")
        .def("CIRF", &Frame::CIRF).staticmethod("CIRF")
        .def("TIRF", &Frame::TIRF).staticmethod("TIRF")
        .def("ITRF", &Frame::ITRF).staticmethod("ITRF")
        .def("WithName", &Frame::WithName).staticmethod("WithName")
        .def("Exists", &Frame::Exists).staticmethod("Exists")
        .def("Construct", &Frame::Construct).staticmethod("Construct")
        .def("Destruct", &Frame::Destruct).staticmethod("Destruct")

    ;

    // register_ptr_to_python<Shared<Frame>>() ;
    register_ptr_to_python<Shared<const Frame>>() ;

    implicitly_convertible<Shared<Frame>, Shared<const Frame>>() ;

    OpenSpaceToolkitPhysicsPy_Coordinate_Frame_Provider() ;
    OpenSpaceToolkitPhysicsPy_Coordinate_Frame_Providers() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////