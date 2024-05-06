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

    class_<Frame, Shared<Frame>>(aModule, "Frame",
        R"doc(
            Reference frame.

            )doc"
        )

        .def(self == self,
            R"doc(
            Equality operator.

            Args:
                other (Frame): Other frame.

            Returns:
                bool: True if equal.
            )doc"
        )
        .def(self != self,
            R"doc(
            Inequality operator.

            Args:
                other (Frame): Other frame.

            Returns:
                bool: True if not equal.
            )doc"
        )

        .def("__str__", &(shiftToString<Frame>))
        .def("__repr__", &(shiftToString<Frame>))

        .def("is_defined", &Frame::isDefined,
            R"doc(
            Check if the instance is defined.

            Returns:
                bool: True if the instance is defined.
            )doc"
        )
        .def("is_quasi_inertial", &Frame::isQuasiInertial,
            R"doc(
            Check if the frame is quasi-inertial.

            Returns:
                bool: True if the frame is quasi-inertial.
            )doc"
        )
        .def("has_parent", &Frame::hasParent,
            R"doc(
            Check if the frame has a parent.

            Returns:
                bool: True if the frame has a parent.
            )doc"
        )

        .def("access_parent", &Frame::accessParent,
            R"doc(
            Access the parent frame.

            Returns:
                Frame: Parent frame.
            )doc"
        )
        .def("access_ancestor", &Frame::accessAncestor, arg("ancestor_degree"),
            R"doc(
            Access the ancestor frame.

            Args:
                ancestor_degree (int): Ancestor degree.

            Returns:
                Frame: Ancestor frame.
            )doc"
        )
        .def("access_provider", &Frame::accessProvider,
            R"doc(
            Access the provider.

            Returns:
                Provider: Provider.
            )doc"
        )
        .def("get_name", &Frame::getName,
            R"doc(
            Get the name.

            Returns:
                String: Name.
            )doc"
        )
        .def("get_origin_in", &Frame::getOriginIn, arg("frame"), arg("instant"),
            R"doc(
            Get the origin in another frame.

            Args:
                frame (Frame): Frame.
                instant (Instant): Instant.

            Returns:
                Position: Origin.
            )doc"
        )
        .def("get_velocity_in", &Frame::getVelocityIn, arg("frame"), arg("instant"),
            R"doc(
            Get the velocity in another frame.

            Args:
                frame (Frame): Frame.
                instant (Instant): Instant.

            Returns:
                Velocity: Velocity.
            )doc"
        )
        .def("get_axes_in", &Frame::getAxesIn, arg("frame"), arg("instant"),
            R"doc(
            Get the axes in another frame.

            Args:
                frame (Frame): Frame.
                instant (Instant): Instant.

            Returns:
                Axes: Axes.
            )doc"
        )
        .def("get_transform_to", &Frame::getTransformTo, arg("frame"), arg("instant"),
            R"doc(
            Get the transformation to another frame.

            Args:
                frame (Frame): Frame.
                instant (Instant): Instant.

            Returns:
                Transform: Transformation.
            )doc"
        )

        .def_static("undefined", &Frame::Undefined,
            R"doc(
            Get undefined frame.

            Returns:
                Frame: Undefined frame.
            )doc"
        )
        .def_static("GCRF", &Frame::GCRF,
            R"doc(
            Get the Geocentric Celestial Reference Frame (GCRF).

            Returns:
                Frame: GCRF.
            )doc"
        )
        .def_static("J2000", &Frame::J2000, arg("theory"),
            R"doc(
            Get the J2000 frame.

            Args:
                theory (Theory): Theory.

            Returns:
                Frame: J2000.
            )doc"
        )
        .def_static("MOD", &Frame::MOD, arg("epoch"),
            R"doc(
            Get the MOD frame.

            Args:
                epoch (Instant): Epoch.

            Returns:
                Frame: MOD.
            )doc"
        )
        .def_static("TOD", &Frame::TOD, arg("epoch"), arg("theory"),
            R"doc(
            Get the TOD frame.

            Args:
                epoch (Instant): Epoch.
                theory (Theory): Theory.

            Returns:
                Frame: TOD.
            )doc"
        )
        .def_static("TEME", &Frame::TEME,
            R"doc(
            Get the True Equator Mean Equinox (TEME) frame.

            Returns:
                Frame: TEME.
            )doc"
        )
        .def_static("TEME_of_epoch", &Frame::TEMEOfEpoch, arg("epoch"),
            R"doc(
            Get the True Equator Mean Equinox (TEME) frame of epoch.

            Args:
                epoch (Instant): Epoch.

            Returns:
                Frame: TEME of epoch.
            )doc"
        )
        .def_static("CIRF", &Frame::CIRF,
            R"doc(
            Get the Celestial Intermediate Reference Frame (CIRF).

            Returns:
                Frame: CIRF.
            )doc"
        )
        .def_static("TIRF", &Frame::TIRF,
            R"doc(
            Get the Terrestrial Intermediate Reference Frame (TIRF).

            Returns:
                Frame: TIRF.
            )doc"
        )
        .def_static("ITRF", &Frame::ITRF,
            R"doc(
            Get the International Terrestrial Reference Frame (ITRF).

            Returns:
                Frame: ITRF.
            )doc"
        )
        .def_static("with_name", &Frame::WithName, arg("name"),
            R"doc(
            Get the frame with a given name.

            Args:
                name (String): Name.

            Returns:
                Frame: Frame.
            )doc"
        )
        .def_static("exists", &Frame::Exists, arg("name"),
            R"doc(
            Check if a frame exists.

            Args:
                name (String): Name.

            Returns:
                bool: True if exists.
            )doc"
        )
        .def_static(
            "construct", &Frame::Construct, arg("name"), arg("is_quasi_inertial"), arg("parent_frame"), arg("provider"),
            R"doc(
            Construct a frame.

            Args:
                name (String): Name.
                is_quasi_inertial (bool): True if quasi-inertial.
                parent_frame (Frame): Parent frame.
                provider (Provider): Provider.

            Returns:
                Frame: Frame.
            )doc"
        )
        .def_static("destruct", &Frame::Destruct, arg("name"),
            R"doc(
            Destruct a frame.

            Args:
                name (String): Name.
            )doc"
        )

        ;

    // register_ptr_to_python<Shared<Frame>>() ;
    // register_ptr_to_python<Shared<const Frame>>() ;

    // implicitly_convertible<Shared<Frame>, Shared<const Frame>>() ;

    // Create "frame" python submodule
    auto frame = aModule.def_submodule("frame");


    OpenSpaceToolkitPhysicsPy_Coordinate_Frame_Provider(frame);
}
