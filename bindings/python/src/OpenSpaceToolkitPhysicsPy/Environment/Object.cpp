/// Apache License 2.0 

#include <OpenSpaceToolkitPhysicsPy/Environment/Object/Geometry.cpp>

#include <OpenSpaceToolkit/Physics/Environment/Object.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitPhysicsPy_Environment_Object (           pybind11::module&          aModule                                     )
{

    using namespace pybind11 ;

    using ostk::core::types::Shared ;
    using ostk::core::types::String ;

    using ostk::physics::time::Instant ;
    using ostk::physics::env::Object ;

    // Binding class "Object"
    class_<Object, Shared<Object>>(aModule, "Object")

        // no init

        .def("__str__", &(shiftToString<Object>))
        .def("__repr__", &(shiftToString<Object>))

        .def("is_defined", &Object::isDefined)

        // .def("access_name", &Object::accessName, return_value_policy<reference_existing_object>())
        // .def("access_instant", &Object::accessInstant, return_value_policy<reference_existing_object>())
        .def("access_name", &Object::accessName, return_value_policy::reference)
        .def("access_instant", &Object::accessInstant, return_value_policy::reference)
        .def("access_frame", &Object::accessFrame)
        .def("get_name", &Object::getName)
        .def("get_instant", &Object::getInstant)
        .def("get_geometry", &Object::getGeometry)
        .def("get_position_in", &Object::getPositionIn)
        .def("get_transform_to", &Object::getTransformTo)
        .def("get_axes_in", &Object::getAxesIn)
        .def("get_geometry_in", &Object::getGeometryIn)
        .def("set_instant", &Object::setInstant)

    ;

    // register_ptr_to_python<Shared<const Object>>() ;

    // implicitly_convertible<Shared<Object>, Shared<const Object>>() ;

    // Adding python submodule "object"

    // Create "object" python submodule
    auto object = aModule.def_submodule("object") ;

    // Add __path__ attribute for "object" submodule
    object.attr("__path__") = "ostk.physics.environment.object" ;

    // Add elements to object
    OpenSpaceToolkitPhysicsPy_Environment_Object_Geometry(object) ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
