/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/CSSISpaceWeather.hpp>

inline void OpenSpaceToolkitPhysicsPy_Environment_Atmospheric_Earth_CSSISpaceWeather(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::types::Shared;

    using ostk::physics::environment::atmospheric::earth::CSSISpaceWeather;

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

    class_<CSSISpaceWeather::Reading>(CSSISpaceWeatherClass, "Reading")

        .def_readonly("date", &CSSISpaceWeather::Reading::date)
        .def_readonly("bsrn", &CSSISpaceWeather::Reading::BSRN)
        .def_readonly("nd", &CSSISpaceWeather::Reading::ND)
        .def_readonly("kp_1", &CSSISpaceWeather::Reading::Kp1)
        .def_readonly("kp_2", &CSSISpaceWeather::Reading::Kp2)
        .def_readonly("kp_3", &CSSISpaceWeather::Reading::Kp3)
        .def_readonly("kp_4", &CSSISpaceWeather::Reading::Kp4)
        .def_readonly("kp_5", &CSSISpaceWeather::Reading::Kp5)
        .def_readonly("kp_6", &CSSISpaceWeather::Reading::Kp6)
        .def_readonly("kp_7", &CSSISpaceWeather::Reading::Kp7)
        .def_readonly("kp_8", &CSSISpaceWeather::Reading::Kp8)
        .def_readonly("kp_sum", &CSSISpaceWeather::Reading::KpSum)
        .def_readonly("ap_1", &CSSISpaceWeather::Reading::Ap1)
        .def_readonly("ap_2", &CSSISpaceWeather::Reading::Ap2)
        .def_readonly("ap_3", &CSSISpaceWeather::Reading::Ap3)
        .def_readonly("ap_4", &CSSISpaceWeather::Reading::Ap4)
        .def_readonly("ap_5", &CSSISpaceWeather::Reading::Ap5)
        .def_readonly("ap_6", &CSSISpaceWeather::Reading::Ap6)
        .def_readonly("ap_7", &CSSISpaceWeather::Reading::Ap7)
        .def_readonly("ap_8", &CSSISpaceWeather::Reading::Ap8)
        .def_readonly("ap_avg", &CSSISpaceWeather::Reading::ApAvg)
        .def_readonly("cp", &CSSISpaceWeather::Reading::Cp)

        .def_readonly("c9", &CSSISpaceWeather::Reading::C9)
        .def_readonly("isn", &CSSISpaceWeather::Reading::ISN)
        .def_readonly("f107_obs", &CSSISpaceWeather::Reading::F107Obs)
        .def_readonly("f107_adj", &CSSISpaceWeather::Reading::F107Adj)
        .def_readonly("f107_data_type", &CSSISpaceWeather::Reading::F107DataType)
        .def_readonly("f107_obs_center_81", &CSSISpaceWeather::Reading::F107ObsCenter81)
        .def_readonly("f107_obs_last_81", &CSSISpaceWeather::Reading::F107ObsLast81)
        .def_readonly("f107_adj_center_81", &CSSISpaceWeather::Reading::F107AdjCenter81)
        .def_readonly("f107_adj_last_81", &CSSISpaceWeather::Reading::F107AdjLast81)

        ;

    class_<CSSISpaceWeather::Reading>(CSSISpaceWeatherClass, "MonthlyPrediction")

        .def_readonly("date", &CSSISpaceWeather::Reading::date)
        .def_readonly("bsrn", &CSSISpaceWeather::Reading::BSRN)
        .def_readonly("nd", &CSSISpaceWeather::Reading::ND)
        .def_readonly("isn", &CSSISpaceWeather::Reading::ISN)
        .def_readonly("f107_obs", &CSSISpaceWeather::Reading::F107Obs)
        .def_readonly("f107_adj", &CSSISpaceWeather::Reading::F107Adj)
        .def_readonly("f107_data_type", &CSSISpaceWeather::Reading::F107DataType)
        .def_readonly("f107_obs_center_81", &CSSISpaceWeather::Reading::F107ObsCenter81)
        .def_readonly("f107_obs_last_81", &CSSISpaceWeather::Reading::F107ObsLast81)
        .def_readonly("f107_adj_center_81", &CSSISpaceWeather::Reading::F107AdjCenter81)
        .def_readonly("f107_adj_last_81", &CSSISpaceWeather::Reading::F107AdjLast81)

        ;
}
