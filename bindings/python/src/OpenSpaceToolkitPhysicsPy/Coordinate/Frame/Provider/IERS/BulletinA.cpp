/// Apache License 2.0

#include <pybind11/stl.h>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/IERS/BulletinA.hpp>

inline void OpenSpaceToolkitPhysicsPy_Coordinate_Frame_Provider_IERS_BulletinA(nanobind::module_& aModule)
{
    using namespace nanobind;

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
                    Duration | None: TAI-UTC, or None if the bulletin does not hold it.
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

        .def_ro(
            "year",
            &BulletinA::Observation::year,
            R"doc(
                Year (to get true calendar year, add 1900 for MJD <= 51543 or add 2000 for MJD >= 51544).
            )doc"
        )
        .def_ro(
            "month",
            &BulletinA::Observation::month,
            R"doc(
                Month number.
            )doc"
        )
        .def_ro(
            "day",
            &BulletinA::Observation::day,
            R"doc(
                Day of month.
            )doc"
        )
        .def_ro(
            "mjd",
            &BulletinA::Observation::mjd,
            R"doc(
                Modified Julian Day.
            )doc"
        )
        .def_ro(
            "x",
            &BulletinA::Observation::x,
            R"doc(
                PM-x [asec].
            )doc"
        )
        .def_ro(
            "x_error",
            &BulletinA::Observation::xError,
            R"doc(
                PM-x error [asec].
            )doc"
        )
        .def_ro(
            "y",
            &BulletinA::Observation::y,
            R"doc(
                PM-y [asec].
            )doc"
        )
        .def_ro(
            "y_error",
            &BulletinA::Observation::yError,
            R"doc(
                PM-y error [asec].
            )doc"
        )
        .def_ro(
            "ut1_minus_utc",
            &BulletinA::Observation::ut1MinusUtc,
            R"doc(
                UT1-UTC [s].
            )doc"
        )
        .def_ro(
            "ut1_minus_utc_error",
            &BulletinA::Observation::ut1MinusUtcError,
            R"doc(
                UT1-UTC error [s].
            )doc"
        )

        ;

    class_<BulletinA::Prediction>(bulletinA, "Prediction")

        .def_ro(
            "year",
            &BulletinA::Prediction::year,
            R"doc(
                Year (to get true calendar year, add 1900 for MJD <= 51543 or add 2000 for MJD >= 51544).
            )doc"
        )
        .def_ro(
            "month",
            &BulletinA::Prediction::month,
            R"doc(
                Month number.
            )doc"
        )
        .def_ro(
            "day",
            &BulletinA::Prediction::day,
            R"doc(
                Day of month.
            )doc"
        )
        .def_ro(
            "mjd",
            &BulletinA::Prediction::mjd,
            R"doc(
                Modified Julian Day.
            )doc"
        )
        .def_ro(
            "x",
            &BulletinA::Prediction::x,
            R"doc(
                PM-x [asec].
            )doc"
        )
        .def_ro(
            "y",
            &BulletinA::Prediction::y,
            R"doc(
                PM-y [asec].
            )doc"
        )
        .def_ro(
            "ut1_minus_utc",
            &BulletinA::Prediction::ut1MinusUtc,
            R"doc(
                UT1-UTC [s].
            )doc"
        )

        ;
}
