/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Environment/Ephemeris/SPICE/Kernel.hpp>

inline void OpenSpaceToolkitPhysicsPy_Environment_Ephemeris_SPICE_Kernel(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::filesystem::File;

    using ostk::physics::environment::ephemeris::spice::Kernel;

    class_<Kernel> kernel_class(
        aModule,
        "Kernel",
        R"doc(
            SPICE Toolkit kernel.

            A generalized data class for SPICE kernel files. SPICE kernels contain
            various types of data including spacecraft clock data, leap seconds,
            physical constants, instrument parameters, frame definitions, events,
            and ephemeris data.

            See Also:
                https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/info/intrdctn.html
        )doc"
    );

    enum_<Kernel::Type>(kernel_class, "Type")

        .value(
            "Undefined",
            Kernel::Type::Undefined,
            R"doc(
                Undefined kernel type.
            )doc"
        )
        .value(
            "SCLK",
            Kernel::Type::SCLK,
            R"doc(
                Spacecraft clock kernels (text).
            )doc"
        )
        .value(
            "LSK",
            Kernel::Type::LSK,
            R"doc(
                Leapseconds kernels (text).
            )doc"
        )
        .value(
            "PCK",
            Kernel::Type::PCK,
            R"doc(
                Physical constants kernels (text).
            )doc"
        )
        .value(
            "IK",
            Kernel::Type::IK,
            R"doc(
                Instrument parameter kernels (text).
            )doc"
        )
        .value(
            "FK",
            Kernel::Type::FK,
            R"doc(
                Frame definition kernels (text).
            )doc"
        )
        .value(
            "EK",
            Kernel::Type::EK,
            R"doc(
                E-kernels (text).
            )doc"
        )
        .value(
            "MK",
            Kernel::Type::MK,
            R"doc(
                Meta-kernels (text).
            )doc"
        )
        .value(
            "SPK",
            Kernel::Type::SPK,
            R"doc(
                SP-kernels (binary) - Spacecraft and Planet ephemeris.
            )doc"
        )
        .value(
            "BPCK",
            Kernel::Type::BPCK,
            R"doc(
                Physical constants kernels (binary).
            )doc"
        )
        .value(
            "CK",
            Kernel::Type::CK,
            R"doc(
                C-kernels (binary) - Spacecraft orientation.
            )doc"
        )
        .value(
            "BEK",
            Kernel::Type::BEK,
            R"doc(
                Events kernels (binary).
            )doc"
        )

        ;

    kernel_class

        .def(
            init<const Kernel::Type&, const File&>(),
            arg("type"),
            arg("file"),
            R"doc(
                Constructor.

                Args:
                    type (Kernel.Type): The kernel type.
                    file (File): The kernel file.
            )doc"
        )

        .def(
            "__eq__",
            [](const Kernel& self, const Kernel& other)
            {
                return self == other;
            }
        )
        .def(
            "__ne__",
            [](const Kernel& self, const Kernel& other)
            {
                return self != other;
            }
        )

        .def(
            "is_defined",
            &Kernel::isDefined,
            R"doc(
                Check if the kernel is defined.

                Returns:
                    bool: True if the kernel is defined, False otherwise.
            )doc"
        )
        .def(
            "get_type",
            &Kernel::getType,
            R"doc(
                Get the kernel type.

                Returns:
                    Kernel.Type: The kernel type.
            )doc"
        )
        .def(
            "get_name",
            &Kernel::getName,
            R"doc(
                Get the kernel name.

                Returns:
                    str: The kernel name.
            )doc"
        )
        .def(
            "get_file",
            &Kernel::getFile,
            R"doc(
                Get the kernel file.

                Returns:
                    File: The kernel file.
            )doc"
        )

        .def_static(
            "undefined",
            &Kernel::Undefined,
            R"doc(
                Create an undefined kernel.

                Returns:
                    Kernel: An undefined kernel.
            )doc"
        )
        .def_static(
            "file",
            &Kernel::File,
            arg("file"),
            R"doc(
                Create a kernel from a file.

                The kernel type is automatically determined from the file extension.

                Args:
                    file (File): The kernel file.

                Returns:
                    Kernel: A kernel object.
            )doc"
        )
        .def_static(
            "type_from_string",
            &Kernel::TypeFromString,
            arg("string"),
            R"doc(
                Convert a string to a kernel type.

                Args:
                    string (str): The kernel type string.

                Returns:
                    Kernel.Type: The kernel type.
            )doc"
        )
        .def_static(
            "string_from_type",
            &Kernel::StringFromType,
            arg("type"),
            R"doc(
                Convert a kernel type to string.

                Args:
                    type (Kernel.Type): The kernel type.

                Returns:
                    str: The string representation of the kernel type.
            )doc"
        )
        .def_static(
            "type_from_file_extension",
            &Kernel::TypeFromFileExtension,
            arg("file_extension"),
            R"doc(
                Convert a file extension to a kernel type.

                Args:
                    file_extension (str): The file extension.

                Returns:
                    Kernel.Type: The kernel type.
            )doc"
        )

        ;
}
