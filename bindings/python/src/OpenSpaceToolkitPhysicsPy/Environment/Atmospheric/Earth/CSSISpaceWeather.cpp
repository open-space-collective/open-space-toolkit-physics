/// Apache License 2.0

#include <pybind11/functional.h>

#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/CSSISpaceWeather.hpp>

inline void OpenSpaceToolkitPhysicsPy_Environment_Atmospheric_Earth_CSSISpaceWeather(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Shared;

    using ostk::physics::environment::atmospheric::earth::CSSISpaceWeather;

    class_<CSSISpaceWeather> CSSISpaceWeatherClass(
        aModule,
        "CSSISpaceWeather",
        R"doc(
            Center for Space Weather and Innovation (CSSI) Space Weather data file.

            Consolidated data set which contains solar radiation and geomagnetic indices.
            Particularly contains the F10.7 solar flux index and Ap/Kp geomagnetic indices,
            which are commonly used to model atmospheric density.

        )doc"
    );

    CSSISpaceWeatherClass

        .def("__str__", &(shiftToString<CSSISpaceWeather>))
        .def("__repr__", &(shiftToString<CSSISpaceWeather>))

        .def(
            "is_defined",
            &CSSISpaceWeather::isDefined,
            R"doc(
                Check if the CSSI Space Weather data is defined.

                Returns:
                    bool: True if defined.
            )doc"
        )

        .def(
            "access_last_observation_date",
            &CSSISpaceWeather::accessLastObservationDate,
            R"doc(
                Access last observation Date. File publication date is the day following the last observation.

                Returns:
                    Date: Last observation Date.
            )doc"
        )
        .def(
            "access_observation_interval",
            &CSSISpaceWeather::accessObservationInterval,
            R"doc(
                Access observation interval.

                Returns:
                    Interval: Observation interval.
            )doc"
        )
        .def(
            "access_observation_at",
            &CSSISpaceWeather::accessObservationAt,
            arg("instant"),
            R"doc(
                Access observation at instant.

                Args:
                    instant (Instant): An instant.

                Returns:
                    Reading: Observation at instant.
            )doc"
        )
        .def(
            "access_daily_prediction_interval",
            &CSSISpaceWeather::accessDailyPredictionInterval,
            R"doc(
                Access daily prediction interval.

                Returns:
                    Interval: Daily prediction interval.
            )doc"
        )
        .def(
            "access_daily_prediction_at",
            &CSSISpaceWeather::accessDailyPredictionAt,
            arg("instant"),
            R"doc(
                Access daily prediction at instant.

                Args:
                    instant (Instant): An instant.

                Returns:
                    Reading: Daily prediction at instant.
            )doc"
        )
        .def(
            "access_monthly_prediction_interval",
            &CSSISpaceWeather::accessMonthlyPredictionInterval,
            R"doc(
                Access monthly prediction interval.

                Returns:
                    Interval: Monthly prediction interval.
            )doc"
        )
        .def(
            "access_monthly_prediction_at",
            &CSSISpaceWeather::accessMonthlyPredictionAt,
            arg("instant"),
            R"doc(
                Access monthly prediction at instant.

                Args:
                    instant (Instant): An instant.

                Returns:
                    Reading: Monthly prediction at instant.
            )doc"
        )
        .def(
            "access_reading_at",
            &CSSISpaceWeather::accessReadingAt,
            arg("instant"),
            R"doc(
                Access reading at Instant. Look first in observations, then in daily predictions, then monthly predictions.

                Args:
                    instant (Instant): An instant.

                Returns:
                    Reading: Reading at instant.
            )doc"
        )
        .def(
            "access_last_reading_where",
            &CSSISpaceWeather::accessLastReadingWhere,
            arg("predicate"),
            arg("instant"),
            R"doc(
                Access last reading before an Instant where a Predicate is true.

                Args:
                    predicate (Predicate): A predicate.
                    instant (Instant): An instant.

                Returns:
                    Reading: Last Reading satisfying predicate.
            )doc"
        )

        .def_static(
            "undefined",
            &CSSISpaceWeather::Undefined,
            R"doc(
                Create an undefined CSSI Space Weather object.

                Returns:
                    CSSISpaceWeather: Undefined CSSI Space Weather object.
            )doc"
        )
        .def_static(
            "load",
            &CSSISpaceWeather::Load,
            arg("file"),
            R"doc(
                Load CSSI Space Weather file in csv format.

                Args:
                    file (File): A csv file.

                Returns:
                    CSSISpaceWeather: CSSI Space Weather object.
            )doc"
        )
        .def_static(
            "load_legacy",
            &CSSISpaceWeather::LoadLegacy,
            arg("file"),
            R"doc(
                Load CSSI Space Weather file in legacy .txt format.

                Args:
                    file (File): A txt file.

                Returns:
                    CSSISpaceWeather: CSSI Space Weather object.
            )doc"
        )

        ;

    class_<CSSISpaceWeather::Reading>(
        CSSISpaceWeatherClass,
        "Reading",
        R"doc(
            CSSI Space Weather reading.

        )doc"
    )

        .def_readonly(
            "date",
            &CSSISpaceWeather::Reading::date,
            R"doc(
                UTC day of reading.

            )doc"
        )
        .def_readonly(
            "bsrn",
            &CSSISpaceWeather::Reading::BSRN,
            R"doc(
                Bartels Solar Rotation Number. A sequence of 27-day intervals counted continuously from 1832 Feb 8.

            )doc"
        )
        .def_readonly(
            "nd",
            &CSSISpaceWeather::Reading::ND,
            R"doc(
                Number of Day within the Bartels 27-day cycle (01-27).

            )doc"
        )
        .def_readonly(
            "kp_1",
            &CSSISpaceWeather::Reading::Kp1,
            R"doc(
                Planetary 3-hour Range Index (Kp) for 0000-0300 UT.
                
            )doc"
        )
        .def_readonly(
            "kp_2",
            &CSSISpaceWeather::Reading::Kp2,
            R"doc(
                Planetary 3-hour Range Index (Kp) for 0300-0600 UT.
            )doc"
        )
        .def_readonly(
            "kp_3",
            &CSSISpaceWeather::Reading::Kp3,
            R"doc(
                Planetary 3-hour Range Index (Kp) for 0600-0900 UT.

            )doc"
        )
        .def_readonly(
            "kp_4",
            &CSSISpaceWeather::Reading::Kp4,
            R"doc(
                Planetary 3-hour Range Index (Kp) for 0900-1200 UT.
            )doc"
        )
        .def_readonly(
            "kp_5",
            &CSSISpaceWeather::Reading::Kp5,
            R"doc(
                Planetary 3-hour Range Index (Kp) for 1200-1500 UT.
            )doc"
        )
        .def_readonly(
            "kp_6",
            &CSSISpaceWeather::Reading::Kp6,
            R"doc(
                Planetary 3-hour Range Index (Kp) for 1500-1800 UT.
            )doc"
        )
        .def_readonly(
            "kp_7",
            &CSSISpaceWeather::Reading::Kp7,
            R"doc(
                Planetary 3-hour Range Index (Kp) for 1800-2100 UT.
            )doc"
        )
        .def_readonly(
            "kp_8",
            &CSSISpaceWeather::Reading::Kp8,
            R"doc(
                Planetary 3-hour Range Index (Kp) for 2100-0000 UT.
            )doc"
        )
        .def_readonly(
            "kp_sum",
            &CSSISpaceWeather::Reading::KpSum,
            R"doc(
                Sum of the 8 Kp indices for the day.
            )doc"
        )
        .def_readonly(
            "ap_1",
            &CSSISpaceWeather::Reading::Ap1,
            R"doc(
                Planetary Equivalent Amplitude (Ap) for 0000-0300 UT.
            )doc"
        )
        .def_readonly(
            "ap_2",
            &CSSISpaceWeather::Reading::Ap2,
            R"doc(
                Planetary Equivalent Amplitude (Ap) for 0300-0600 UT.
            )doc"
        )
        .def_readonly(
            "ap_3",
            &CSSISpaceWeather::Reading::Ap3,
            R"doc(
                Planetary Equivalent Amplitude (Ap) for 0600-0900 UT.
            )doc"
        )
        .def_readonly(
            "ap_4",
            &CSSISpaceWeather::Reading::Ap4,
            R"doc(
                Planetary Equivalent Amplitude (Ap) for 0900-1200 UT.
            )doc"
        )
        .def_readonly(
            "ap_5",
            &CSSISpaceWeather::Reading::Ap5,
            R"doc(
                Planetary Equivalent Amplitude (Ap) for 1200-1500 UT.
            )doc"
        )
        .def_readonly(
            "ap_6",
            &CSSISpaceWeather::Reading::Ap6,
            R"doc(
                Planetary Equivalent Amplitude (Ap) for 1500-1800 UT.
            )doc"
        )
        .def_readonly(
            "ap_7",
            &CSSISpaceWeather::Reading::Ap7,
            R"doc(
                Planetary Equivalent Amplitude (Ap) for 1800-2100 UT.
            )doc"
        )
        .def_readonly(
            "ap_8",
            &CSSISpaceWeather::Reading::Ap8,
            R"doc(
                Planetary Equivalent Amplitude (Ap) for 2100-0000 UT.
            )doc"
        )
        .def_readonly(
            "ap_avg",
            &CSSISpaceWeather::Reading::ApAvg,
            R"doc(
                Arithmetic average of the 8 Ap indices for the day.
            )doc"
        )
        .def_readonly(
            "cp",
            &CSSISpaceWeather::Reading::Cp,
            R"doc(
                Cp or Planetary Daily Character Figure. A qualitative estimate of overall level of magnetic activity for the day determined from the sum of the 8 Ap indices. Cp ranges, in steps of one-tenth, from 0 (quiet) to 2.5 (highly disturbed).
            )doc"
        )
        .def_readonly("c9", &CSSISpaceWeather::Reading::C9,
            R"doc(
                C9. A conversion of the 0-to-2.5 range of the Cp index to one digit between 0 and 9.
            )doc"
        )
        .def_readonly("isn", &CSSISpaceWeather::Reading::ISN,
            R"doc(
                International Sunspot Number. Records contain the Zurich number through 1980 Dec 31 and the International Brussels number thereafter.
            )doc"
        )
        .def_readonly("f107_obs", &CSSISpaceWeather::Reading::F107Obs,
            R"doc(
                Observed 10.7-cm Solar Radio Flux (F10.7). Measured at Ottawa at 1700 UT daily from 1947 Feb 14 until 1991 May 31 and measured at Penticton at 2000 UT from 1991 Jun 01 on. Expressed in units of 10-22 W/m2/Hz.
            )doc"
        )
        .def_readonly("f107_adj", &CSSISpaceWeather::Reading::F107Adj,
            R"doc(
                10.7-cm Solar Radio Flux (F10.7) adjusted to 1 AU.
            )doc"
        )
        .def_readonly("f107_data_type", &CSSISpaceWeather::Reading::F107DataType,
            R"doc(
                Flux Qualifier.
                OBS: Observed flux measurement
                INT: CelesTrak linear interpolation of missing data
                PRD: 45-Day predicted flux
                PRM: Monthly predicted flux
            )doc"
        )
        .def_readonly("f107_obs_center_81", &CSSISpaceWeather::Reading::F107ObsCenter81,
            R"doc(
                Centered 81-day arithmetic average of F107 (observed).
            )doc"
        )
        .def_readonly("f107_obs_last_81", &CSSISpaceWeather::Reading::F107ObsLast81,
            R"doc(
                Last 81-day arithmetic average of F107 (observed).
            )doc"
        )
        .def_readonly("f107_adj_center_81", &CSSISpaceWeather::Reading::F107AdjCenter81,
            R"doc(
                Centered 81-day arithmetic average of F10.7 (adjusted).
            )doc"
        )
        .def_readonly("f107_adj_last_81", &CSSISpaceWeather::Reading::F107AdjLast81,
            R"doc(
                Last 81-day arithmetic average of F10.7 (adjusted).
            )doc"
        )

        ;
}
