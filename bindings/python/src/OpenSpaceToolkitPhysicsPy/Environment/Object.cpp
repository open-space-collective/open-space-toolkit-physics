////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           bindings/python/src/OpenSpaceToolkitPhysicsPy/Environment/Object.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkitPhysicsPy/Environment/Object/Geometry.cpp>

#include <OpenSpaceToolkit/Physics/Environment/Object.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitPhysicsPy_Environment_Object         ( )
{

    using namespace boost::python ;

    using ostk::core::types::Shared ;
    using ostk::core::types::String ;

    using ostk::physics::time::Instant ;
    using ostk::physics::env::Object ;

    class_<Object, boost::noncopyable>("Object", no_init)

        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))

        .def("is_defined", &Object::isDefined)

        .def("access_name", &Object::accessName, return_value_policy<reference_existing_object>())
        .def("access_instant", &Object::accessInstant, return_value_policy<reference_existing_object>())
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

    register_ptr_to_python<Shared<const Object>>() ;

    implicitly_convertible<Shared<Object>, Shared<const Object>>() ;

    boost::python::object module(boost::python::handle<>(boost::python::borrowed(PyImport_AddModule("ostk.physics.environment.object")))) ;

    boost::python::scope().attr("object") = module ;

    boost::python::scope scope = module ;

    OpenSpaceToolkitPhysicsPy_Environment_Object_Geometry() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
