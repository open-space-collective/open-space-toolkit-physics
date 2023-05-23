/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/IERS/Finals2000A.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void OpenSpaceToolkitPhysicsPy_Coordinate_Frame_Providers_IERS_Finals2000A(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::types::Shared;

    using ostk::physics::coord::frame::provider::iers::Finals2000A;

    class_<Finals2000A> finals2000A(aModule, "Finals2000A");

    finals2000A

        .def("__str__", &(shiftToString<Finals2000A>))
        .def("__repr__", &(shiftToString<Finals2000A>))

        .def("is_defined", &Finals2000A::isDefined)

        .def("get_interval", &Finals2000A::getInterval)
        .def("get_polar_motion_at", &Finals2000A::getPolarMotionAt, arg("instant"))
        .def("get_ut1_minus_utc_at", &Finals2000A::getUt1MinusUtcAt, arg("instant"))
        .def("get_lod_at", &Finals2000A::getLodAt, arg("instant"))
        .def("get_data_at", &Finals2000A::getDataAt, arg("instant"))

        .def_static("undefined", &Finals2000A::Undefined)
        .def_static("load", &Finals2000A::Load, arg("file"))

        ;

    class_<Finals2000A::Data>(finals2000A, "Data")

        .def_readonly("year", &Finals2000A::Data::year)
        .def_readonly("month", &Finals2000A::Data::month)
        .def_readonly("day", &Finals2000A::Data::day)
        .def_readonly("mjd", &Finals2000A::Data::mjd)
        .def_readonly("polar_motionflag", &Finals2000A::Data::polarMotionflag)
        .def_readonly("x_a", &Finals2000A::Data::x_A)
        .def_readonly("x_error_a", &Finals2000A::Data::xError_A)
        .def_readonly("y_a", &Finals2000A::Data::y_A)
        .def_readonly("y_error_a", &Finals2000A::Data::yError_A)
        .def_readonly("ut1_minus_utc_flag", &Finals2000A::Data::ut1MinusUtcFlag)
        .def_readonly("ut1_minus_utc_a", &Finals2000A::Data::ut1MinusUtc_A)
        .def_readonly("ut1_minus_utc_error_a", &Finals2000A::Data::ut1MinusUtcError_A)
        .def_readonly("lod_a", &Finals2000A::Data::lod_A)
        .def_readonly("lod_error_a", &Finals2000A::Data::lodError_A)
        .def_readonly("nutation_flag", &Finals2000A::Data::nutationFlag)
        .def_readonly("dx_a", &Finals2000A::Data::dx_A)
        .def_readonly("dx_error_a", &Finals2000A::Data::dxError_A)
        .def_readonly("dy_a", &Finals2000A::Data::dy_A)
        .def_readonly("dy_error_a", &Finals2000A::Data::dyError_A)
        .def_readonly("x_b", &Finals2000A::Data::x_B)
        .def_readonly("y_b", &Finals2000A::Data::y_B)
        .def_readonly("ut1_minus_utc_b", &Finals2000A::Data::ut1MinusUtc_B)
        .def_readonly("dx_b", &Finals2000A::Data::dx_B)
        .def_readonly("dy_b", &Finals2000A::Data::dy_B)

        ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
