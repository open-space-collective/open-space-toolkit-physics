/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/IERS/BulletinA.hpp>

inline void OpenSpaceToolkitPhysicsPy_Coordinate_Frame_Provider_IERS_BulletinA(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Shared;

    using ostk::physics::coordinate::frame::provider::iers::BulletinA;

    class_<BulletinA> bulletinA(
        aModule,
        "BulletinA",
        R"doc(
            Contains rapid determinations for Earth orientation parameters:
            x/y pole, UT1-UTC and their errors at daily intervals and predictions for 1 year into
            the future.

            The contents of IERS Bulletin A are divided into four sections:

            1. General information including key definitions and the most recently adopted values of
            DUT1 and TAI-UTC.

            2. Quick-look daily estimates of the EOPs determined by smoothing the observed data.
            This involves the application of systematic corrections and statistical weighting.
            The results are published with a delay of about one to three days between the date of
            publication and the last available date with estimated EOP.

            3. Predictions of x, y, and UT1-UTC, up to 365 days following the last day of data.
            The predictions use similar algorithms based on seasonal filtering and autoregressive
            processing for x, y, and UT1.

            4. The combination series for the celestial pole offsets.
            Bulletin A contains celestial pole offsets with respect to the IAU1980 Nutation theory
            (dpsi and deps) and the IAU 2000 Resolutions (dX and dY), beginning on 1 January 2003.

            :reference: https://datacenter.iers.org/productMetadata.php?id=6
        
        )doc"
    );

    bulletinA

        .def("__str__", &(shiftToString<BulletinA>))
        .def("__repr__", &(shiftToString<BulletinA>))

        .def(
            "is_defined",
            &BulletinA::isDefined,
            R"doc(
                Returns true if the bulletin is defined.

                Returns:
                    bool: True if the bulletin is defined.
            )doc"
        )
        .def(
            "access_release_date",
            &BulletinA::accessReleaseDate,
            R"doc(
                Access the release date.

                Returns:
                    Date: The release date.
            )doc"
        )
        .def(
            "access_tai_minus_utc",
            &BulletinA::accessTAIMinusUTC,
            R"doc(
                Access the TAI-UTC.

                Returns:
                    Duration: The TAI-UTC.
            )doc"
        )
        .def(
            "access_tai_minus_utc_epoch",
            &BulletinA::accessTAIMinusUTCEpoch,
            R"doc(
                Access the TAI-UTC epoch.

                Returns:
                    Instant: The TAI-UTC epoch.
            )doc"
        )
        .def(
            "access_observation_interval",
            &BulletinA::accessObservationInterval,
            R"doc(
                Access the observation interval.

                Returns:
                    Interval: The observation Interval of Instants.
            )doc"
        )
        .def(
            "access_prediction_interval",
            &BulletinA::accessPredictionInterval,
            R"doc(
                Access the prediction interval.

                Returns:
                    Interval: The prediction Interval of Instants.
            )doc"
        )

        .def(
            "get_release_date",
            &BulletinA::getReleaseDate,
            R"doc(
                Get release Date of Bulletin A.

                Returns:
                    Date: Release Date of Bulletin A.
            )doc"
        )
        .def(
            "get_tai_minus_utc",
            &BulletinA::getTAIMinusUTC,
            R"doc(
                Get TAI-UTC.

                Returns:
                    Duration: TAI-UTC.
            )doc"
        )
        .def(
            "get_tai_minus_utc_epoch",
            &BulletinA::getTAIMinusUTCEpoch,
            R"doc(
                Get TAI-UTC epoch.

                Returns:
                    Instant: TAI-UTC epoch.
            )doc"
        )
        .def(
            "get_observation_interval",
            &BulletinA::getObservationInterval,
            R"doc(
                Get observation interval.

                Returns:
                    Interval: Observation Interval of Instants.
            )doc"
        )
        .def(
            "get_observation_at",
            &BulletinA::getObservationAt,
            arg("instant"),
            R"doc(
                Get observation at a given instant.

                Parameters:
                    instant (Instant): The instant.

                Returns:
                    Observation: The observation.
            )doc"
        )
        .def(
            "get_prediction_interval",
            &BulletinA::getPredictionInterval,
            R"doc(
                Get prediction interval.

                Returns:
                    Interval: Prediction Interval of Instants.
            )doc"
        )
        .def(
            "get_prediction_at",
            &BulletinA::getPredictionAt,
            arg("instant"),
            R"doc(
                Get prediction at a given instant.

                Parameters:
                    instant (Instant): The instant.

                Returns:
                    Prediction: The prediction.
            )doc"
        )

        .def_static(
            "undefined",
            &BulletinA::Undefined,
            R"doc(
                Undefined factory function.

                Returns:
                    BulletinA: An undefined Bulletin A object.
            )doc"
        )
        .def_static(
            "load",
            &BulletinA::Load,
            arg("file"),
            R"doc(
                Load Bulletin A from a file.

                Parameters:
                    file (File): The file.

                Returns:
                    BulletinA: The Bulletin A object.
            )doc"
        )

        ;

    class_<BulletinA::Observation>(bulletinA, "Observation")

        .def_readonly(
            "year",
            &BulletinA::Observation::year,
            R"doc(
                Year (to get true calendar year, add 1900 for MJD <= 51543 or add 2000 for MJD >= 51544).
            )doc"
        )
        .def_readonly(
            "month",
            &BulletinA::Observation::month,
            R"doc(
                Month number.
            )doc"
        )
        .def_readonly(
            "day",
            &BulletinA::Observation::day,
            R"doc(
                Day of month.
            )doc"
        )
        .def_readonly(
            "mjd",
            &BulletinA::Observation::mjd,
            R"doc(
                Modified Julian Day.
            )doc"
        )
        .def_readonly(
            "x",
            &BulletinA::Observation::x,
            R"doc(
                PM-x [asec].
            )doc"
        )
        .def_readonly(
            "x_error",
            &BulletinA::Observation::xError,
            R"doc(
                PM-x error [asec].
            )doc"
        )
        .def_readonly(
            "y",
            &BulletinA::Observation::y,
            R"doc(
                PM-y [asec].
            )doc"
        )
        .def_readonly(
            "y_error",
            &BulletinA::Observation::yError,
            R"doc(
                PM-y error [asec].
            )doc"
        )
        .def_readonly(
            "ut1_minus_utc",
            &BulletinA::Observation::ut1MinusUtc,
            R"doc(
                UT1-UTC [s].
            )doc"
        )
        .def_readonly(
            "ut1_minus_utc_error",
            &BulletinA::Observation::ut1MinusUtcError,
            R"doc(
                UT1-UTC error [s].
            )doc"
        )

        ;

    class_<BulletinA::Prediction>(bulletinA, "Prediction")

        .def_readonly(
            "year",
            &BulletinA::Prediction::year,
            R"doc(
                Year (to get true calendar year, add 1900 for MJD <= 51543 or add 2000 for MJD >= 51544).
            )doc"
        )
        .def_readonly(
            "month",
            &BulletinA::Prediction::month,
            R"doc(
                Month number.
            )doc"
        )
        .def_readonly(
            "day",
            &BulletinA::Prediction::day,
            R"doc(
                Day of month.
            )doc"
        )
        .def_readonly(
            "mjd",
            &BulletinA::Prediction::mjd,
            R"doc(
                Modified Julian Day.
            )doc"
        )
        .def_readonly(
            "x",
            &BulletinA::Prediction::x,
            R"doc(
                PM-x [asec].
            )doc"
        )
        .def_readonly(
            "y",
            &BulletinA::Prediction::y,
            R"doc(
                PM-y [asec].
            )doc"
        )
        .def_readonly(
            "ut1_minus_utc",
            &BulletinA::Prediction::ut1MinusUtc,
            R"doc(
                UT1-UTC [s].
            )doc"
        )

        ;
}
