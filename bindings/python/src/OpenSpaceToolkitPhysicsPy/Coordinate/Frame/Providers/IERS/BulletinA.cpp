/// Apache License 2.0 

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/IERS/BulletinA.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitPhysicsPy_Coordinate_Frame_Providers_IERS_BulletinA ( pybind11::module& aModule                                 )
{

    using namespace pybind11 ;

    using ostk::core::types::Shared ;

    using ostk::physics::coord::frame::provider::iers::BulletinA ;

    class_<BulletinA> bulletinA(aModule, "BulletinA") ;

    bulletinA

        .def("__str__", &(shiftToString<BulletinA>))
        .def("__repr__", &(shiftToString<BulletinA>))

        .def("is_defined", &BulletinA::isDefined)

        .def("access_release_date", &BulletinA::accessReleaseDate)
        .def("access_tai_minus_utc", &BulletinA::accessTAIMinusUTC)
        .def("access_tai_minus_utc_epoch", &BulletinA::accessTAIMinusUTCEpoch)
        .def("access_observation_interval", &BulletinA::accessObservationInterval)
        .def("access_prediction_interval", &BulletinA::accessPredictionInterval)

        .def("get_release_date", &BulletinA::getReleaseDate)
        .def("get_tai_minus_utc", &BulletinA::getTAIMinusUTC)
        .def("get_tai_minus_utc_epoch", &BulletinA::getTAIMinusUTCEpoch)
        .def("get_observation_interval", &BulletinA::getObservationInterval)
        .def("get_observation_at", &BulletinA::getObservationAt, arg("instant"))
        .def("get_prediction_interval", &BulletinA::getPredictionInterval)
        .def("get_prediction_at", &BulletinA::getPredictionAt, arg("instant"))

        .def_static("undefined", &BulletinA::Undefined)
        .def_static("load", &BulletinA::Load, arg("file"))

    ;

    class_<BulletinA::Observation>(bulletinA, "Observation")

        .def_readonly("year", &BulletinA::Observation::year)
        .def_readonly("month", &BulletinA::Observation::month)
        .def_readonly("day", &BulletinA::Observation::day)
        .def_readonly("mjd", &BulletinA::Observation::mjd)
        .def_readonly("x", &BulletinA::Observation::x)
        .def_readonly("x_error", &BulletinA::Observation::xError)
        .def_readonly("y", &BulletinA::Observation::y)
        .def_readonly("y_error", &BulletinA::Observation::yError)
        .def_readonly("ut1_minus_utc", &BulletinA::Observation::ut1MinusUtc)
        .def_readonly("ut1_minus_utc_error", &BulletinA::Observation::ut1MinusUtcError)

    ;

    class_<BulletinA::Prediction>(bulletinA, "Prediction")

        .def_readonly("year", &BulletinA::Prediction::year)
        .def_readonly("month", &BulletinA::Prediction::month)
        .def_readonly("day", &BulletinA::Prediction::day)
        .def_readonly("mjd", &BulletinA::Prediction::mjd)
        .def_readonly("x", &BulletinA::Prediction::x)
        .def_readonly("y", &BulletinA::Prediction::y)
        .def_readonly("ut1_minus_utc", &BulletinA::Prediction::ut1MinusUtc)

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
