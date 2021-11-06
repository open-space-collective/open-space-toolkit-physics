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

inline void                     OpenSpaceToolkitPhysicsPy_Coordinate_Frame  (           pybind11::module&           aModule                                     )
{

    using namespace pybind11 ;

    using ostk::core::types::Shared ;
    using ostk::core::types::String ;

    using ostk::physics::coord::Frame ;
    using ostk::physics::coord::frame::Provider ;

    // scope in_Frame = class_<Frame, Shared<Frame>>("Frame", init<String&, bool, Shared<const Frame>&, Shared<Provider>&>())
    // scope in_Frame = class_<Frame, Shared<Frame>, boost::noncopyable>("Frame", init<String&, bool, Shared<const Frame>&, Shared<Provider>&>())
    // scope in_Frame = class_<Frame>("Frame", init<String&, bool, Shared<const Frame>&, Shared<const Provider>&>())
    class_<Frame, Shared<Frame>>(aModule, "Frame")  // Added Shared<Frame> as Parent

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Frame>))
        .def("__repr__", &(shiftToString<Frame>))

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

        .def_static("undefined", &Frame::Undefined)
        // .def_static("ICRF", &Frame::ICRF)
        .def_static("GCRF", &Frame::GCRF)
        .def_static("MOD", &Frame::MOD)
        .def_static("TOD", &Frame::TOD)
        // .def_static("EME2000", &Frame::EME2000)
        .def_static("TEME", &Frame::TEME)
        .def_static("TEME_of_epoch", &Frame::TEMEOfEpoch)
        .def_static("CIRF", &Frame::CIRF)
        .def_static("TIRF", &Frame::TIRF)
        .def_static("ITRF", &Frame::ITRF)
        .def_static("with_name", &Frame::WithName)
        .def_static("exists", &Frame::Exists)
        .def_static("construct", &Frame::Construct)
        .def_static("destruct", &Frame::Destruct)

    ;

    // register_ptr_to_python<Shared<Frame>>() ;
    // register_ptr_to_python<Shared<const Frame>>() ;

    // implicitly_convertible<Shared<Frame>, Shared<const Frame>>() ;

    // Create "frame" python submodule
    auto frame = aModule.def_submodule("frame") ;

    // Add __path__ attribute for "frame" submodule
    frame.attr("__path__") = "ostk.physics.coordinate.frame" ;

    OpenSpaceToolkitPhysicsPy_Coordinate_Frame_Provider(frame) ;
    OpenSpaceToolkitPhysicsPy_Coordinate_Frame_Providers(frame) ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
