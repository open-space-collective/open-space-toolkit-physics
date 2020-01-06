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

        .def("is_defined", &Frame::isDefined)
        .def("is_quasi_inertial", &Frame::isQuasiInertial)
        .def("has_parent", &Frame::hasParent)

        .def("access_parent", &Frame::accessParent)
        .def("access_ancestor", &Frame::accessAncestor)
        .def("access_provider", &Frame::accessProvider)
        .def("get_name", &Frame::getName)
        .def("get_origin_in", &Frame::getOriginIn)
        .def("get_velocity_in", &Frame::getVelocityIn)
        .def("get_axes_in", &Frame::getAxesIn)
        .def("get_transform_to", &Frame::getTransformTo)

        .def("undefined", &Frame::Undefined).staticmethod("undefined")
        // .def("ICRF", &Frame::ICRF).staticmethod("ICRF")
        .def("GCRF", &Frame::GCRF).staticmethod("GCRF")
        // .def("EME2000", &Frame::EME2000).staticmethod("EME2000")
        .def("TEME", &Frame::TEME).staticmethod("TEME")
        .def("TEME_of_epoch", &Frame::TEMEOfEpoch).staticmethod("TEME_of_epoch")
        .def("CIRF", &Frame::CIRF).staticmethod("CIRF")
        .def("TIRF", &Frame::TIRF).staticmethod("TIRF")
        .def("ITRF", &Frame::ITRF).staticmethod("ITRF")
        .def("with_name", &Frame::WithName).staticmethod("with_name")
        .def("exists", &Frame::Exists).staticmethod("exists")
        .def("construct", &Frame::Construct).staticmethod("construct")
        .def("destruct", &Frame::Destruct).staticmethod("destruct")

    ;

    // register_ptr_to_python<Shared<Frame>>() ;
    register_ptr_to_python<Shared<const Frame>>() ;

    implicitly_convertible<Shared<Frame>, Shared<const Frame>>() ;

    boost::python::object module(boost::python::handle<>(boost::python::borrowed(PyImport_AddModule("ostk.physics.coordinate")))) ;

    boost::python::scope().attr("coordinate") = module ;

    boost::python::scope scope = module ;

    OpenSpaceToolkitPhysicsPy_Coordinate_Frame_Provider() ;
    OpenSpaceToolkitPhysicsPy_Coordinate_Frame_Providers() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
