////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           LibraryPhysicsPy/Time/DateTime.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <datetime.h>

#include <OpenSpaceToolkit/Physics/Time/DateTime.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using ostk::physics::time::DateTime ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// http://code.activestate.com/recipes/576395/

struct DateTimeFromPythonDateTime
{
                                DateTimeFromPythonDateTime                  ( )
    {

        boost::python::converter::registry::push_back
        (
            &convertible,
            &construct,
            boost::python::type_id<DateTime>()
        ) ;

    }

    static void*                convertible                                 (           PyObject*                   anObject                                    )
    {

        if (!PyDateTime_Check(anObject))
        {
            return 0 ;
        }

        return anObject ;

    }

     static void                construct                                   (           PyObject*                   anObject,
                                                                                        boost::python::converter::rvalue_from_python_stage1_data* data          )
    {

        const PyDateTime_DateTime* pydate = reinterpret_cast<PyDateTime_DateTime*>(anObject) ;

        const int year = PyDateTime_GET_YEAR(pydate) ;
        const int month = PyDateTime_GET_MONTH(pydate) ;
        const int day = PyDateTime_GET_DAY(pydate) ;

        const int hour = PyDateTime_DATE_GET_HOUR(pydate) ;
        const int minute = PyDateTime_DATE_GET_MINUTE(pydate) ;
        const int second = PyDateTime_DATE_GET_SECOND(pydate) ;

        const int microseconds = PyDateTime_DATE_GET_MICROSECOND(pydate) ;

        const int millisecond = microseconds / 1000 ;
        const int microsecond = microseconds - millisecond * 1000 ;

        // Create DateTime object

        void* storage = ((boost::python::converter::rvalue_from_python_storage<DateTime>*) data)->storage.bytes ;

        new (storage) DateTime (year, month, day, hour, minute, second, millisecond, microsecond) ;

        data->convertible = storage ;

    }

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct PythonDatetimeFromDateTime
{

    static PyObject*            convert                                     (   const   DateTime&                   aDateTime                                   )
    {

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

inline void                     LibraryPhysicsPy_Time_DateTime              ( )
{

    using namespace boost::python ;

    using ostk::core::types::String ;

    using ostk::physics::time::DateTime ;
    using ostk::physics::time::Date ;
    using ostk::physics::time::Time ;

    scope in_DateTime = class_<DateTime>("DateTime", init<Date, Time>())

        .def(init<int, int, int, int, int, int, int, int, int>())
        .def(init<int, int, int, int, int, int>())

        .def(self == self)
        .def(self != self)

        .def(self_ns::str(self_ns::self))

        .def("__repr__", +[] (const DateTime& aDateTime) -> std::string { return aDateTime.toString() ; })

        .def("isDefined", &DateTime::isDefined)

        .def("getDate", &DateTime::getDate)
        .def("getTime", &DateTime::getTime)
        .def("getJulianDate", &DateTime::getJulianDate)
        .def("getModifiedJulianDate", &DateTime::getModifiedJulianDate)
        .def("toString", +[] (const DateTime& aDateTime) -> String { return aDateTime.toString() ; })
        .def("toString", +[] (const DateTime& aDateTime, const DateTime::Format& aFormat) -> String { return aDateTime.toString(aFormat) ; })

        .def("Undefined", &DateTime::Undefined).staticmethod("Undefined")
        .def("J2000", &DateTime::J2000).staticmethod("J2000")
        .def("GPSEpoch", &DateTime::GPSEpoch).staticmethod("GPSEpoch")
        .def("UnixEpoch", &DateTime::UnixEpoch).staticmethod("UnixEpoch")
        .def("ModifiedJulianDateEpoch", &DateTime::ModifiedJulianDateEpoch).staticmethod("ModifiedJulianDateEpoch")
        .def("JulianDate", &DateTime::JulianDate).staticmethod("JulianDate")
        .def("ModifiedJulianDate", &DateTime::ModifiedJulianDate).staticmethod("ModifiedJulianDate")
        .def("Parse", +[] (const String& aString) -> DateTime { return DateTime::Parse(aString) ; })
        .def("Parse", +[] (const String& aString, const DateTime::Format& aFormat) -> DateTime { return DateTime::Parse(aString, aFormat) ; })

    ;

    enum_<DateTime::Format>("Format")

        .value("Undefined", DateTime::Format::Undefined)
        .value("Standard", DateTime::Format::Standard)
        .value("ISO8601", DateTime::Format::ISO8601)
        .value("STK", DateTime::Format::STK)

    ;

    PyDateTime_IMPORT ;

    DateTimeFromPythonDateTime() ;

    to_python_converter<DateTime, PythonDatetimeFromDateTime>() ;

    // tduration_from_python_delta();

    // to_python_converter<
    // const boost::posix_time::time_duration
    // , tduration_to_python_delta
    // >();

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
