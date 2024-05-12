/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Environment/Object.hpp>

#include <OpenSpaceToolkitPhysicsPy/Environment/Object/Celestial.cpp>
#include <OpenSpaceToolkitPhysicsPy/Environment/Object/Geometry.cpp>

inline void OpenSpaceToolkitPhysicsPy_Environment_Object(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Shared;
    using ostk::core::type::String;

    using ostk::physics::time::Instant;
    using ostk::physics::environment::Object;

    // Binding class "Object"
    class_<Object, Shared<Object>>(
        aModule,
        "Object",
        R"doc(
            This class represents a physical object in the environment.
            It can be subclassed to represent specific types of objects, like celestial bodies.
        )doc"
    )

        // no init

        .def("__str__", &(shiftToString<Object>), R"doc(
            Returns:
                str: a string representation of the Object.
        )doc")

        .def("__repr__", &(shiftToString<Object>), R"doc(
            Returns:
                str: a string representation of the Object. Similar to __str__.
        )doc")

        .def("is_defined", &Object::isDefined, R"doc(
            Checks if the Object is defined.

            Returns:
                bool: True if the Object is defined, False otherwise.
        )doc")

        // .def("access_name", &Object::accessName, return_value_policy<reference_existing_object>())
        .def("access_name", &Object::accessName, return_value_policy::reference, R"doc(
            Accesses the name of the Object.

            Returns:
                str: The name of the Object.
        )doc")

        .def("access_frame", &Object::accessFrame, R"doc(
            Accesses the frame of the Object.

            Returns:
                Frame: The frame of the Object.
        )doc")

        .def("get_name", &Object::getName, R"doc(
            Gets the name of the Object.

            Returns:
                str: The name of the Object.
        )doc")

        .def("get_geometry", &Object::getGeometry, R"doc(
            Gets the geometry of the Object.

            Returns:
                Geometry: The geometry of the Object.
        )doc")

        .def("get_position_in", &Object::getPositionIn, R"doc(
            Gets the position of the Object in a given frame.

            Args:
                frame (Frame): The frame in which the position is expressed.

            Returns:
                Position: The position of the Object.
        )doc")

        .def("get_transform_to", &Object::getTransformTo, R"doc(
            Gets the transformation from the Object to a given frame.

            Args:
                frame (Frame): The frame to which the transformation is expressed.

            Returns:
                Transformation: the transformation.
        )doc")

        .def("get_axes_in", &Object::getAxesIn, R"doc(
            Gets the axes of the Object in a given frame.

            Args:
                frame (Frame): The frame in which the axes are expressed.

            Returns:
                Axes: the axes of the Object.
        )doc")

        .def("get_geometry_in", &Object::getGeometryIn, R"doc(
            Gets the geometry of the Object in a given frame.

            Args:
                frame (Frame): The frame in which the geometry is expressed.

            Returns:
                Geometry: the geometry of the Object.
        )doc");

    // register_ptr_to_python<Shared<const Object>>() ;

    // implicitly_convertible<Shared<Object>, Shared<const Object>>() ;

    // Adding python submodule "object"

    // Create "object" python submodule
    auto object = aModule.def_submodule("object");

    // Add elements to object
    OpenSpaceToolkitPhysicsPy_Environment_Object_Geometry(object);
    OpenSpaceToolkitPhysicsPy_Environment_Object_Celestial(object);
}
