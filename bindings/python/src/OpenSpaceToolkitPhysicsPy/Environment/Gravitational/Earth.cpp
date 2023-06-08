/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Earth/Manager.hpp>

inline void OpenSpaceToolkitPhysicsPy_Environment_Gravitational_Earth(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::types::Integer;
    using ostk::core::fs::Directory;

    using ostk::physics::environment::gravitational::Earth;
    using ostk::physics::environment::gravitational::earth::Manager;

    {
        class_<Earth> earth_class(aModule, "Earth");

        earth_class

            .def(init<const Earth::Type&, const Directory&>(), arg("type"), arg("directory"))

            .def(init<const Earth::Type&>(), arg("type"))

            .def(
                init<const Earth::Type&, const Directory&, const Integer&, const Integer&>(),
                arg("type"),
                arg("directory"),
                arg("gravitational_model_degree"),
                arg("gravitational_model_order")
            )

            .def("is_defined", &Earth::isDefined)

            .def("get_parameters", &Earth::getParameters)

            .def("get_type", &Earth::getType)

            .def("get_field_value_at", &Earth::getFieldValueAt, arg("position"), arg("instant"))

            .def_readonly_static("EGM2008", &Earth::EGM2008Parameters)
            .def_readonly_static("EGM96", &Earth::EGM96Parameters)
            .def_readonly_static("EGM84", &Earth::EGM84Parameters)
            .def_readonly_static("WGS84_EGM96", &Earth::WGS84_EGM96Parameters)
            .def_readonly_static("WGS84", &Earth::WGS84Parameters)
            .def_readonly_static("spherical", &Earth::SphericalParameters)

            ;

        enum_<Earth::Type>(earth_class, "EarthType")

            .value("Undefined", Earth::Type::Undefined)
            .value("Spherical", Earth::Type::Spherical)
            .value("WGS84", Earth::Type::WGS84)
            .value("EGM84", Earth::Type::EGM84)
            .value("EGM96", Earth::Type::EGM96)
            .value("EGM2008", Earth::Type::EGM2008)

            ;
    }

    // Create "earth" python submodule
    auto earth = aModule.def_submodule("earth");

    // Add __path__ attribute for "earth" submodule
    earth.attr("__path__") = "ostk.physics.environment.gravitational.earth";

    class_<Manager>(earth, "Manager")

        .def("is_enabled", &Manager::isEnabled)

        .def("has_data_file_for_type", &Manager::hasDataFileForType, arg("model_type"))

        .def("get_local_repository", &Manager::getLocalRepository)
        .def("get_remote_url", &Manager::getRemoteUrl)

        .def("fetch_data_file_for_type", &Manager::fetchDataFileForType, arg("model_type"))

        .def("set_local_repository", &Manager::setLocalRepository, arg("directory"))

        .def("set_remote_url", &Manager::setRemoteUrl, arg("remote_url"))

        .def("enable", &Manager::enable)
        .def("disable", &Manager::disable)

        .def_static("get", &Manager::Get, return_value_policy::reference)
        .def_static("default_local_repository", &Manager::DefaultLocalRepository)
        .def_static("default_remote_url", &Manager::DefaultRemoteUrl)

        ;

    // Create "models" python submodule
    // auto models = earth.def_submodule("models");

    // // Add __path__ attribute for "models" submodule
    // models.attr("__path__") = "ostk.physics.environment.gravitational.earth.models.models";

    // class_<Earth::EGM2008Parameters>(models, "EGM2008")

    //     .def_readonly_static("gravitational_parameter", &Earth::EGM2008Parameters.gravitationalParameter_)
    //     .def_readonly_static("equatorial_radius", &Earth::EGM2008Parameters.equatorialRadius_)
    //     .def_readonly_static("flattening", &Earth::EGM2008Parameters.flattening_)
    //     .def_readonly_static("C20", &Earth::EGM2008Parameters.C20_)
    //     .def_readonly_static("C40", &Earth::EGM2008Parameters.C40_)
    //     .def_readonly_static("J2", &Earth::EGM2008Parameters.J2_)
    //     .def_readonly_static("J4", &Earth::EGM2008Parameters.J4_)

    //     ;

    // class_<Earth::Models::WGS84_EGM96>(models, "WGS84_EGM96")

    //     .def_readonly_static("gravitational_parameter", &Earth::WGS84_EGM96Parameters.gravitationalParameter_)
    //     .def_readonly_static("equatorial_radius", &Earth::WGS84_EGM96Parameters.equatorialRadius_)
    //     .def_readonly_static("flattening", &Earth::WGS84_EGM96Parameters.flattening_)
    //     .def_readonly_static("C20", &Earth::WGS84_EGM96Parameters.C20_)
    //     .def_readonly_static("C40", &Earth::WGS84_EGM96Parameters.C40_)
    //     .def_readonly_static("J2", &Earth::WGS84_EGM96Parameters.J2_)
    //     .def_readonly_static("J4", &Earth::WGS84_EGM96Parameters.J4_)

    //     ;

    // class_<Earth::Models::EGM96>(models, "EGM96")

    //     .def_readonly_static("gravitational_parameter", &Earth::EGM96Parameters.gravitationalParameter_)
    //     .def_readonly_static("equatorial_radius", &Earth::EGM96Parameters.equatorialRadius_)
    //     .def_readonly_static("flattening", &Earth::EGM96Parameters.flattening_)
    //     .def_readonly_static("C20", &Earth::EGM96Parameters.C20_)
    //     .def_readonly_static("C40", &Earth::EGM96Parameters.C40_)
    //     .def_readonly_static("J2", &Earth::EGM96Parameters.J2_)
    //     .def_readonly_static("J4", &Earth::EGM96Parameters.J4_)

    //     ;

    // class_<Earth::Models::EGM84>(models, "EGM84")

    //     .def_readonly_static("gravitational_parameter", &Earth::EGM84Parameters.gravitationalParameter_)
    //     .def_readonly_static("equatorial_radius", &Earth::EGM84Parameters.equatorialRadius_)
    //     .def_readonly_static("flattening", &Earth::EGM84Parameters.flattening_)
    //     .def_readonly_static("C20", &Earth::EGM84Parameters.C20_)
    //     .def_readonly_static("C40", &Earth::EGM84Parameters.C40_)
    //     .def_readonly_static("J2", &Earth::EGM84Parameters.J2_)
    //     .def_readonly_static("J4", &Earth::EGM84Parameters.J4_)

    //     ;

    // class_<Earth::Models::WGS84>(models, "WGS84")

    //     .def_readonly_static("gravitational_parameter", &Earth::Models::WGS84::gravitationalParameter_)
    //     .def_readonly_static("equatorial_radius", &Earth::Models::WGS84::equatorialRadius_)
    //     .def_readonly_static("flattening", &Earth::Models::WGS84::flattening_)
    //     .def_readonly_static("C20", &Earth::Models::WGS84::C20_)
    //     .def_readonly_static("C40", &Earth::Models::WGS84::C40_)
    //     .def_readonly_static("J2", &Earth::Models::WGS84::J2_)
    //     .def_readonly_static("J4", &Earth::Models::WGS84::J4_)

    //     ;

    // class_<Earth::Models::Spherical>(models, "Spherical")

    //     .def_readonly_static("gravitational_parameter", &Earth::Models::Spherical::gravitationalParameter_)
    //     .def_readonly_static("equatorial_radius", &Earth::Models::Spherical::equatorialRadius_)
    //     .def_readonly_static("flattening", &Earth::Models::Spherical::flattening_)
    //     .def_readonly_static("C20", &Earth::Models::Spherical::C20_)
    //     .def_readonly_static("C40", &Earth::Models::Spherical::C40_)
    //     .def_readonly_static("J2", &Earth::Models::Spherical::J2_)
    //     .def_readonly_static("J4", &Earth::Models::Spherical::J4_)

    //     ;
}
