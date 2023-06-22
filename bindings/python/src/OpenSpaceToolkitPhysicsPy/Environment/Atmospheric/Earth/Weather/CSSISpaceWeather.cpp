/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/Weather/CSSISpaceWeather.hpp>

inline void OpenSpaceToolkitPhysicsPy_Environment_Atmospheric_Earth_Weather_CSSISpaceWeather(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::types::Shared;

    using ostk::physics::environment::atmospheric::earth::weather::CSSISpaceWeather;

    class_<CSSISpaceWeather> CSSISpaceWeatherClass(aModule, "CSSISpaceWeather");

    CSSISpaceWeatherClass

        .def("__str__", &(shiftToString<CSSISpaceWeather>))
        .def("__repr__", &(shiftToString<CSSISpaceWeather>))

        .def("is_defined", &CSSISpaceWeather::isDefined)

        .def("access_last_observation_date", &CSSISpaceWeather::accessLastObservationDate)
        .def("access_observation_interval", &CSSISpaceWeather::accessObservationInterval)
        .def("access_observation_at", &CSSISpaceWeather::accessObservationAt, arg("instant"))
        .def("access_daily_prediction_interval", &CSSISpaceWeather::accessDailyPredictionInterval)
        .def("access_daily_prediction_at", &CSSISpaceWeather::accessDailyPredictionAt, arg("instant"))
        .def("access_monthly_prediction_interval", &CSSISpaceWeather::accessMonthlyPredictionInterval)
        .def("access_monthly_prediction_at", &CSSISpaceWeather::accessMonthlyPredictionAt, arg("instant"))

        .def_static("undefined", &CSSISpaceWeather::Undefined)
        .def_static("load", &CSSISpaceWeather::Load, arg("file"))

        ;

    class_<CSSISpaceWeather::Observation>(CSSISpaceWeatherClass, "Observation")

        .def_readonly("date", &CSSISpaceWeather::Observation::date)
        .def_readonly("bsrn", &CSSISpaceWeather::Observation::BSRN)
        .def_readonly("nd", &CSSISpaceWeather::Observation::ND)
        .def_readonly("kp_1", &CSSISpaceWeather::Observation::KP1)
        .def_readonly("kp_2", &CSSISpaceWeather::Observation::KP2)
        .def_readonly("kp_3", &CSSISpaceWeather::Observation::KP3)
        .def_readonly("kp_4", &CSSISpaceWeather::Observation::KP4)
        .def_readonly("kp_5", &CSSISpaceWeather::Observation::KP5)
        .def_readonly("kp_6", &CSSISpaceWeather::Observation::KP6)
        .def_readonly("kp_7", &CSSISpaceWeather::Observation::KP7)
        .def_readonly("kp_8", &CSSISpaceWeather::Observation::KP8)
        .def_readonly("kp_sum", &CSSISpaceWeather::Observation::KP_SUM)
        .def_readonly("ap_1", &CSSISpaceWeather::Observation::AP1)
        .def_readonly("ap_2", &CSSISpaceWeather::Observation::AP2)
        .def_readonly("ap_3", &CSSISpaceWeather::Observation::AP3)
        .def_readonly("ap_4", &CSSISpaceWeather::Observation::AP4)
        .def_readonly("ap_5", &CSSISpaceWeather::Observation::AP5)
        .def_readonly("ap_6", &CSSISpaceWeather::Observation::AP6)
        .def_readonly("ap_7", &CSSISpaceWeather::Observation::AP7)
        .def_readonly("ap_8", &CSSISpaceWeather::Observation::AP8)
        .def_readonly("ap_avg", &CSSISpaceWeather::Observation::AP_AVG)
        .def_readonly("cp", &CSSISpaceWeather::Observation::CP)

        .def_readonly("c9", &CSSISpaceWeather::Observation::C9)
        .def_readonly("isn", &CSSISpaceWeather::Observation::ISN)
        .def_readonly("f107_obs", &CSSISpaceWeather::Observation::F107_OBS)
        .def_readonly("f107_adj", &CSSISpaceWeather::Observation::F107_ADJ)
        .def_readonly("f107_data_type", &CSSISpaceWeather::Observation::F107_DATA_TYPE)
        .def_readonly("f107_obs_center_81", &CSSISpaceWeather::Observation::F107_OBS_CENTER81)
        .def_readonly("f107_obs_last_81", &CSSISpaceWeather::Observation::F107_OBS_LAST81)
        .def_readonly("f107_adj_center_81", &CSSISpaceWeather::Observation::F107_ADJ_CENTER81)
        .def_readonly("f107_adj_last_81", &CSSISpaceWeather::Observation::F107_ADJ_LAST81)

        ;

    class_<CSSISpaceWeather::DailyPrediction>(CSSISpaceWeatherClass, "DailyPrediction"); // TBI: Add attributes

    class_<CSSISpaceWeather::MonthlyPrediction>(CSSISpaceWeatherClass, "MonthlyPrediction")

        .def_readonly("date", &CSSISpaceWeather::MonthlyPrediction::date)
        .def_readonly("bsrn", &CSSISpaceWeather::MonthlyPrediction::BSRN)
        .def_readonly("nd", &CSSISpaceWeather::MonthlyPrediction::ND)
        .def_readonly("isn", &CSSISpaceWeather::MonthlyPrediction::ISN)
        .def_readonly("f107_obs", &CSSISpaceWeather::MonthlyPrediction::F107_OBS)
        .def_readonly("f107_adj", &CSSISpaceWeather::MonthlyPrediction::F107_ADJ)
        .def_readonly("f107_data_type", &CSSISpaceWeather::MonthlyPrediction::F107_DATA_TYPE)
        .def_readonly("f107_obs_center_81", &CSSISpaceWeather::MonthlyPrediction::F107_OBS_CENTER81)
        .def_readonly("f107_obs_last_81", &CSSISpaceWeather::MonthlyPrediction::F107_OBS_LAST81)
        .def_readonly("f107_adj_center_81", &CSSISpaceWeather::MonthlyPrediction::F107_ADJ_CENTER81)
        .def_readonly("f107_adj_last_81", &CSSISpaceWeather::MonthlyPrediction::F107_ADJ_LAST81)

        ;
}
