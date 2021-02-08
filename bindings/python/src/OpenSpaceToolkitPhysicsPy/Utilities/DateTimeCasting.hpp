////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           bindings/python/src/OpenSpaceToolkitPhysicsPy/Utilities/DateTimeCasting.cpp
/// @author         Remy Derollez <remy@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <pybind11/pybind11.h>
#include <datetime.h>
#include <iostream>

#include <OpenSpaceToolkit/Physics/Time/DateTime.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// https://github.com/pybind/pybind11/issues/1176
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

// WARNING: Requires DateTime to have a Default Constructor to be used by load function. To be added if the following piece of code is to be used

template <>
// Alternative would not extend the type_caster_base
class type_caster<DateTime> : public type_caster_base<DateTime>
{

public:

    using base = type_caster_base<DateTime>;
    using type = DateTime ;

    bool load(handle src, bool convert)
    {

        // Lazy initialise the PyDateTime import
        if (!PyDateTimeAPI) { PyDateTime_IMPORT; }

        if (!src) return false ;

        int year, month, day, hour, minute, second, microsecond, millisecond ;

        // if (base::load(src, convert)) {
        //     return true;
        // }

        else if (PyDateTime_Check(src.ptr()))
        {

            year = PyDateTime_GET_YEAR(src.ptr()) ;
            month = PyDateTime_GET_MONTH(src.ptr()) ;
            day = PyDateTime_GET_DAY(src.ptr()) ;

            hour = PyDateTime_DATE_GET_HOUR(src.ptr()) ;
            minute = PyDateTime_DATE_GET_MINUTE(src.ptr()) ;
            second = PyDateTime_DATE_GET_SECOND(src.ptr()) ;

            const int microseconds = PyDateTime_DATE_GET_MICROSECOND(src.ptr()) ;

            millisecond = microseconds / 1000 ;
            microsecond = microseconds - millisecond * 1000 ;

        }

        // ...
        // Possibility to add loops to convert datetime.date and datetime.time
        // and convert them directly to DateTime as well if wanted

        else return false;

        value = DateTime(year, month, day, hour, minute, second, millisecond, microsecond) ;

        return true;
    }

    // From C++ DateTime to python datetime.datetime
    static handle cast(const DateTime &aDateTime, return_value_policy /* policy */, handle /* parent */)
    {

        // Lazy initialise the PyDateTime import
        if (!PyDateTimeAPI) { PyDateTime_IMPORT; }

        const int year = static_cast<int>(aDateTime.accessDate().getYear()) ;
        const int month = static_cast<int>(aDateTime.accessDate().getMonth()) ;
        const int day = static_cast<int>(aDateTime.accessDate().getDay()) ;

        const int hour = static_cast<int>(aDateTime.accessTime().getHour()) ;
        const int minute = static_cast<int>(aDateTime.accessTime().getMinute()) ;
        const int second = static_cast<int>(aDateTime.accessTime().getSecond()) ;

        const int microseconds = (aDateTime.accessTime().getMillisecond() * 1000) + aDateTime.accessTime().getMicrosecond() ;

        return PyDateTime_FromDateAndTime(year, month, day, hour, minute, second, microseconds) ;

    }

    PYBIND11_TYPE_CASTER(type, _("datetime.datetime"));

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
