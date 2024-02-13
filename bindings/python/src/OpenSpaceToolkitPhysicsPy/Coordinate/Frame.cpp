/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>

#include <OpenSpaceToolkitPhysicsPy/Coordinate/Frame/Provider.cpp>

inline void OpenSpaceToolkitPhysicsPy_Coordinate_Frame(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Shared;
    using ostk::core::type::String;

    using ostk::physics::coordinate::Frame;
    using ostk::physics::coordinate::frame::Provider;

    class_<Frame, Shared<Frame>>(aModule, "Frame")

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Frame>))
        .def("__repr__", &(shiftToString<Frame>))

        .def("is_defined", &Frame::isDefined)
        .def("is_quasi_inertial", &Frame::isQuasiInertial)
        .def("has_parent", &Frame::hasParent)

        .def("access_parent", &Frame::accessParent)
        .def("access_ancestor", &Frame::accessAncestor, arg("ancestor_degree"))
        .def("access_provider", &Frame::accessProvider)
        .def("get_name", &Frame::getName)
        .def("get_origin_in", &Frame::getOriginIn, arg("frame"), arg("instant"))
        .def("get_velocity_in", &Frame::getVelocityIn, arg("frame"), arg("instant"))
        .def("get_axes_in", &Frame::getAxesIn, arg("frame"), arg("instant"))
        .def("get_transform_to", &Frame::getTransformTo, arg("frame"), arg("instant"))

        .def_static("undefined", &Frame::Undefined)
        .def_static("GCRF", &Frame::GCRF)
        .def_static("J2000", &Frame::J2000, arg("theory"))
        .def_static("MOD", &Frame::MOD, arg("epoch"))
        .def_static("TOD", &Frame::TOD, arg("epoch"), arg("theory"))
        .def_static("TEME", &Frame::TEME)
        .def_static("TEME_of_epoch", &Frame::TEMEOfEpoch, arg("epoch"))
        .def_static("CIRF", &Frame::CIRF)
        .def_static("TIRF", &Frame::TIRF)
        .def_static("ITRF", &Frame::ITRF)
        .def_static("with_name", &Frame::WithName, arg("name"))
        .def_static("exists", &Frame::Exists, arg("name"))
        .def_static(
            "construct", &Frame::Construct, arg("name"), arg("is_quasi_inertial"), arg("parent_frame"), arg("provider")
        )
        .def_static("destruct", &Frame::Destruct, arg("name"))

        ;

    // register_ptr_to_python<Shared<Frame>>() ;
    // register_ptr_to_python<Shared<const Frame>>() ;

    // implicitly_convertible<Shared<Frame>, Shared<const Frame>>() ;

    // Create "frame" python submodule
    auto frame = aModule.def_submodule("frame");


    OpenSpaceToolkitPhysicsPy_Coordinate_Frame_Provider(frame);
}
