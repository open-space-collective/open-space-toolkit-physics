/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/IERS/Finals2000A.hpp>

inline void OpenSpaceToolkitPhysicsPy_Coordinate_Frame_Provider_IERS_Finals2000A(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Shared;

    using ostk::physics::coordinate::frame::provider::iers::Finals2000A;

    class_<Finals2000A> finals2000A(aModule, "Finals2000A",
        R"doc(
            Standard Rapid EOP Data since 01. January 1992 (IAU2000)

            This file (updated weekly) is the complete Earth orientation data set, since 1 January
            1992 with 1 year of predictions. The nutation series in dX and dY uses the IAU 2000A
            Nutation Theory.


        )doc"
    );

    finals2000A

        .def("__str__", &(shiftToString<Finals2000A>))
        .def("__repr__", &(shiftToString<Finals2000A>))

        .def("is_defined", &Finals2000A::isDefined,
            R"doc(
            Returns true if defined.

            Returns:
                bool: True if defined.

            )doc"
        )

        .def("get_interval", &Finals2000A::getInterval,
            R"doc(
            Get data interval.

            Returns:
                Interval: Data Interval of Instants.

            )doc"
        )
        .def("get_polar_motion_at", &Finals2000A::getPolarMotionAt, arg("instant"),
            R"doc(
            Get polar motion at instant.

            Args:
                instant (Instant): Instant.

            Returns:
                Vector2d: Polar motion.

            )doc"
        )
        .def("get_ut1_minus_utc_at", &Finals2000A::getUt1MinusUtcAt, arg("instant"),
            R"doc(
            Get UT1-UTC at instant.

            Args:
                instant (Instant): Instant.

            Returns:
                Real: UT1-UTC.

            )doc"
        )
        .def("get_lod_at", &Finals2000A::getLodAt, arg("instant"),
            R"doc(
            Get LOD at instant.

            Args:
                instant (Instant): Instant.

            Returns:
                Real: LOD.

            )doc"
        )
        .def("get_data_at", &Finals2000A::getDataAt, arg("instant"),
            R"doc(
            Get data at instant.

            Args:
                instant (Instant): Instant.

            Returns:
                Finals2000.Data: Data.

            )doc"
        )

        .def_static("undefined", &Finals2000A::Undefined,
            R"doc(
            Undefined factory function.

            Returns:
                Finals2000A: Undefined Finals2000A object.

            )doc"
        )
        .def_static("load", &Finals2000A::Load, arg("file"),
            R"doc(
            Load data from file.

            Args:
                file (str): File.

            Returns:
                Finals2000A: Finals2000A object.

            )doc"
        )

        ;

    class_<Finals2000A::Data>(finals2000A, "Data")

        .def_readonly("year", &Finals2000A::Data::year,
            R"doc(
            Year (to get true calendar year, add 1900 for MJD <= 51543 or add 2000 for MJD >= 51544).

            )doc"
        )
        .def_readonly("month", &Finals2000A::Data::month,
            R"doc(
            Month number.

            )doc"
        )
        .def_readonly("day", &Finals2000A::Data::day,
            R"doc(
            Day of month.

            )doc"
        )
        .def_readonly("mjd", &Finals2000A::Data::mjd,
            R"doc(
            Modified Julian Date.

            )doc"
        )
        .def_readonly("polar_motionflag", &Finals2000A::Data::polarMotionflag,
            R"doc(
            IERS (I) or Prediction (P) flag for Bulletin A polar motion values.

            )doc"
        )
        .def_readonly("x_a", &Finals2000A::Data::x_A,
            R"doc(
            [asec] Bulletin A PM-x.

            )doc"
        )
        .def_readonly("x_error_a", &Finals2000A::Data::xError_A,
            R"doc(
            [asec] Error in PM-x.

            )doc"
        )
        .def_readonly("y_a", &Finals2000A::Data::y_A,
            R"doc(
            [asec] Bulletin A PM-y.

            )doc"
        )
        .def_readonly("y_error_a", &Finals2000A::Data::yError_A,
            R"doc(
            [asec] Error in PM-y.

            )doc"
        )
        .def_readonly("ut1_minus_utc_flag", &Finals2000A::Data::ut1MinusUtcFlag,
            R"doc(
            IERS (I) or Prediction (P) flag for Bulletin A UT1-UTC values.

            )doc"
        )
        .def_readonly("ut1_minus_utc_a", &Finals2000A::Data::ut1MinusUtc_A,
            R"doc(
            [s] Bulletin A UT1-UTC.

            )doc"
        )
        .def_readonly("ut1_minus_utc_error_a", &Finals2000A::Data::ut1MinusUtcError_A,
            R"doc(
            [s] Error in UT1-UTC.

            )doc"
        )
        .def_readonly("lod_a", &Finals2000A::Data::lod_A,
            R"doc(
            [ms] Bulletin A LOD (not always filled).

            )doc"
        )
        .def_readonly("lod_error_a", &Finals2000A::Data::lodError_A,
            R"doc(
            [ms] Error in LOD (not always filled).

            )doc"
        )
        .def_readonly("nutation_flag", &Finals2000A::Data::nutationFlag,
            R"doc(
            IERS (I) or Prediction (P) flag for Bulletin A nutation values.

            )doc"
        )
        .def_readonly("dx_a", &Finals2000A::Data::dx_A,
            R"doc(
            [amsec] Bulletin A dX wrt IAU2000A Nutation, Free Core Nutation NOT Removed.

            )doc"
        )
        .def_readonly("dx_error_a", &Finals2000A::Data::dxError_A,
            R"doc(
            [amsec] Error in dX.

            )doc"
        )
        .def_readonly("dy_a", &Finals2000A::Data::dy_A,
            R"doc(
            [amsec] Bulletin A dY wrt IAU2000A Nutation, Free Core Nutation NOT Removed.

            )doc"
        )
        .def_readonly("dy_error_a", &Finals2000A::Data::dyError_A,
            R"doc(
            [amsec] Error in dY.

            )doc"
        )
        .def_readonly("x_b", &Finals2000A::Data::x_B,
            R"doc(
            [asec] Bulletin B PM-x.

            )doc"
        )
        .def_readonly("y_b", &Finals2000A::Data::y_B,
            R"doc(
            [asec] Bulletin B PM-y.

            )doc"
        )
        .def_readonly("ut1_minus_utc_b", &Finals2000A::Data::ut1MinusUtc_B,
            R"doc(
            [s] Bulletin B UT1-UTC.

            )doc"
        )
        .def_readonly("dx_b", &Finals2000A::Data::dx_B,
            R"doc(
            [amsec] Bulletin B dX wrt IAU2000A Nutation.

            )doc"
        )
        .def_readonly("dy_b", &Finals2000A::Data::dy_B,
            R"doc(
            [amsec] Bulletin B dY wrt IAU2000A Nutation.

            )doc"
        )

        ;
}
