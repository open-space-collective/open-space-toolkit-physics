/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Time/Scale.hpp>

inline void OpenSpaceToolkitPhysicsPy_Time_Scale(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::physics::time::Scale;

    enum_<Scale>(aModule, "Scale",
        R"doc(
            Time scale.

            See also:
                - [SOFA](http://www.iausofa.org/sofa_ts_c.pdf)
                - [Times](https://www.cv.nrao.edu/~rfisher/Ephemerides/times.html)
                - [Time](http://stjarnhimlen.se/comp/time.html)
                - [GNSS](http://www.navipedia.net/index.php/Time_References_in_GNSS)
                - [GNSS](Springer Handbook of Global Navigation Satellite Systems)
        )doc"
    )

        .value("Undefined", Scale::Undefined,
            R"doc(
                Undefined time.
            )doc"
        )
        .value("UTC", Scale::UTC,
            R"doc(
                Coordinated Universal Time.
            )doc"
        )
        .value("TT", Scale::TT,
            R"doc(
                Terrestial Time (a.k.a. TDT).
            )doc"
        )
        .value("TAI", Scale::TAI,
            R"doc(
                International Atomic Time.
            )doc"
        )
        .value("UT1", Scale::UT1,
            R"doc(
                Universal Time.
            )doc"
        )
        .value("TCG", Scale::TCG,
            R"doc(
                Geocentric Coordinate Time.
            )doc"
        )
        .value("TCB", Scale::TCB,
            R"doc(
                Barycentric Coordinate Time.
            )doc"
        )
        .value("TDB", Scale::TDB,
            R"doc(
                Barycentric Dynamic Time.
            )doc"
        )
        .value("GMST", Scale::GMST,
            R"doc(
                Greenwich Mean Sidereal Time.
            )doc"
        )
        .value("GPST", Scale::GPST,
            R"doc(
                Global Positioning System (GPS) Time.
            )doc"
        )
        .value("GST", Scale::GST,
            R"doc(
                Galileo System Time.
            )doc"
        )
        .value("GLST", Scale::GLST,
            R"doc(
                GLONASS Time.
            )doc"
        )
        .value("BDT", Scale::BDT,
            R"doc(
                BeiDou Time.
            )doc"
        )
        .value("QZSST", Scale::QZSST,
            R"doc(
                Quasi-Zenith Satellite System (QZSS) Time.
            )doc"
        )
        .value("IRNSST", Scale::IRNSST,
            R"doc(
                Indian Regional Navigation Satellite System (IRNSS) Time.
            )doc"
        )

        ;
}
