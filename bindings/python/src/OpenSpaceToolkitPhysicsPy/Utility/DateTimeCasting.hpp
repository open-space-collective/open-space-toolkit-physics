/// Apache License 2.0

#include <datetime.h>

#include <nanobind/nanobind.h>

#include <OpenSpaceToolkit/Physics/Time/DateTime.hpp>

// https://nanobind.readthedocs.io/en/latest/porting.html
// https://nanobind.readthedocs.io/en/latest/lowlevel.html
// https://docs.python.org/3/c-api/datetime.html

using ostk::physics::time::DateTime;

namespace nanobind
{
namespace detail
{

/// @brief                      Accept a python datetime wherever a DateTime is expected, and return
///                             DateTime as a python datetime.
///
///                             The base caster handles an actual bound DateTime; everything below it
///                             is the datetime.datetime interoperability.

template <>
struct type_caster<DateTime> : type_caster_base<DateTime>
{
    using Base = type_caster_base<DateTime>;

    /// @brief                  Keeps a DateTime built from a python datetime alive for the call.

    object convertedObject_;

    bool from_python(handle aSource, uint8_t someFlags, cleanup_list* aCleanupList) noexcept
    {
        if (!aSource.is_valid())
        {
            return false;
        }

        if (Base::from_python(aSource, someFlags, aCleanupList))
        {
            return true;
        }

        if (!importDateTimeApi())
        {
            return false;
        }

        if (!PyDateTime_Check(aSource.ptr()))
        {
            return false;
        }

        const int microseconds = PyDateTime_DATE_GET_MICROSECOND(aSource.ptr());
        const int millisecond = microseconds / 1000;

        const DateTime dateTime = {
            PyDateTime_GET_YEAR(aSource.ptr()),
            PyDateTime_GET_MONTH(aSource.ptr()),
            PyDateTime_GET_DAY(aSource.ptr()),
            PyDateTime_DATE_GET_HOUR(aSource.ptr()),
            PyDateTime_DATE_GET_MINUTE(aSource.ptr()),
            PyDateTime_DATE_GET_SECOND(aSource.ptr()),
            millisecond,
            microseconds - millisecond * 1000,
        };

        // Round-trip through a bound DateTime so the base caster owns the storage.

        convertedObject_ = steal(Base::from_cpp(dateTime, rv_policy::copy, nullptr));

        if (!convertedObject_.is_valid())
        {
            PyErr_Clear();

            return false;
        }

        return Base::from_python(convertedObject_, someFlags, aCleanupList);
    }

    // Declared here so that the base class template of the same name is hidden.

    static handle from_cpp(const DateTime& aDateTime, rv_policy, cleanup_list*) noexcept
    {
        if (!importDateTimeApi())
        {
            return handle();
        }

        if (!aDateTime.isDefined())
        {
            return none().release();
        }

        const int microseconds =
            (aDateTime.accessTime().getMillisecond() * 1000) + aDateTime.accessTime().getMicrosecond();

        return PyDateTime_FromDateAndTime(
            static_cast<int>(aDateTime.accessDate().getYear()),
            static_cast<int>(aDateTime.accessDate().getMonth()),
            static_cast<int>(aDateTime.accessDate().getDay()),
            static_cast<int>(aDateTime.accessTime().getHour()),
            static_cast<int>(aDateTime.accessTime().getMinute()),
            static_cast<int>(aDateTime.accessTime().getSecond()),
            microseconds
        );
    }

    static handle from_cpp(const DateTime* aDateTimePtr, rv_policy aPolicy, cleanup_list* aCleanupList) noexcept
    {
        return (aDateTimePtr != nullptr) ? from_cpp(*aDateTimePtr, aPolicy, aCleanupList) : none().release();
    }

   private:
    static bool importDateTimeApi() noexcept
    {
        if (PyDateTimeAPI == nullptr)
        {
            PyDateTime_IMPORT;

            if (PyDateTimeAPI == nullptr)
            {
                PyErr_Clear();

                return false;
            }
        }

        return true;
    }
};

}  // namespace detail
}  // namespace nanobind
