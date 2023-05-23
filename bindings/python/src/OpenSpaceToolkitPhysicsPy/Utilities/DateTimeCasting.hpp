/// Apache License 2.0

#include <pybind11/pybind11.h>
#include <datetime.h>

#include <OpenSpaceToolkit/Physics/Time/DateTime.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// https://github.com/pybind/pybind11/issues/1176 (MAIN)
// https://pybind11.readthedocs.io/en/stable/advanced/cast/custom.html
// https://github.com/pybind/pybind11/blob/master/include/pybind11/chrono.h
// https://docs.python.org/3/c-api/datetime.html
// https://en.cppreference.com/w/cpp/chrono/system_clock/to_time_t
// https://github.com/pybind/pybind11/issues/2417

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using ostk::physics::time::DateTime ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace pybind11
{
namespace detail
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <>
class type_caster<DateTime> : public type_caster_base<DateTime>
{

    using type = DateTime ;
    using base = type_caster_base<DateTime> ;

    public:

        // datetime.datetime (Python) -> DateTime (C++)
        bool load (handle src, bool convert)
        {

            // Lazy initialise the PyDateTime import
            if (!PyDateTimeAPI) { PyDateTime_IMPORT ; }

            if (!src) return false ;

            if (base::load(src, convert))
            {
                return true ;
            }
            else if (PyDateTime_Check(src.ptr()))
            {

                const int year = PyDateTime_GET_YEAR(src.ptr()) ;
                const int month = PyDateTime_GET_MONTH(src.ptr()) ;
                const int day = PyDateTime_GET_DAY(src.ptr()) ;

                const int hour = PyDateTime_DATE_GET_HOUR(src.ptr()) ;
                const int minute = PyDateTime_DATE_GET_MINUTE(src.ptr()) ;
                const int second = PyDateTime_DATE_GET_SECOND(src.ptr()) ;

                int microseconds = PyDateTime_DATE_GET_MICROSECOND(src.ptr()) ;

                const int millisecond = microseconds / 1000 ;
                const int microsecond = microseconds - millisecond * 1000 ;

                value = new DateTime(year, month, day, hour, minute, second, millisecond, microsecond) ;

                return true ;

            }

            // Possibility to add conditions to convert datetime.date and datetime.time

            return false ;

        }

        // DateTime (C++) -> datetime.datetime (Python)
        static handle cast (const DateTime& aDateTime, return_value_policy /* policy */, handle /* parent */)
        {

            // Lazy initialise the PyDateTime import
            if (!PyDateTimeAPI) { PyDateTime_IMPORT ; }

            if (!aDateTime.isDefined())
            {
                return pybind11::none() ;
            }

            const int year = static_cast<int>(aDateTime.accessDate().getYear()) ;
            const int month = static_cast<int>(aDateTime.accessDate().getMonth()) ;
            const int day = static_cast<int>(aDateTime.accessDate().getDay()) ;
            const int hour = static_cast<int>(aDateTime.accessTime().getHour()) ;
            const int minute = static_cast<int>(aDateTime.accessTime().getMinute()) ;
            const int second = static_cast<int>(aDateTime.accessTime().getSecond()) ;
            const int microseconds = (aDateTime.accessTime().getMillisecond() * 1000) + aDateTime.accessTime().getMicrosecond() ;

            return PyDateTime_FromDateAndTime(year, month, day, hour, minute, second, microseconds) ;

        }

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
