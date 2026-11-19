/// Apache License 2.0

#include <datetime.h>
#include <optional>
#include <type_traits>

#include <nanobind/nanobind.h>

#include <OpenSpaceToolkit/Physics/Time/DateTime.hpp>

// https://nanobind.readthedocs.io/en/latest/porting.html#type-casters
// https://docs.python.org/3/c-api/datetime.html

using ostk::physics::time::DateTime;

namespace nanobind
{
namespace detail
{

/// @brief                      Type caster for DateTime
///
///                             DateTime is a bound class, and this caster keeps accepting its instances (by
///                             reference, like nanobind's own class caster). It also accepts a Python
///                             `datetime.datetime`, and it returns every C++ DateTime to Python as a
///                             `datetime.datetime`.
///
///                             It derives from `type_caster_base_tag`, so that nanobind still treats DateTime as a
///                             bound class (`class_<DateTime>` requires it), like `type_caster_base<DateTime>`.

template <>
struct type_caster<DateTime> : type_caster_base_tag
{
    using Value = DateTime;

    static constexpr auto Name = const_name<DateTime>();

    template <typename T_>
    using Cast = precise_cast_t<T_>;

    template <typename T_>
    bool can_cast() const noexcept
    {
        return std::is_pointer_v<T_> || (valuePtr_ != nullptr);
    }

    // datetime.datetime (Python) -> DateTime (C++)
    bool from_python(handle src, uint32_t flags, cleanup_list* cleanup) noexcept
    {
        if (src.is_none())
        {
            return false;
        }

        type_caster_base<DateTime> baseCaster;

        if (baseCaster.from_python(src, flags, cleanup))
        {
            valuePtr_ = baseCaster.operator DateTime*();
            return valuePtr_ != nullptr;
        }

        // Lazy initialise the PyDateTime import
        if (!PyDateTimeAPI)
        {
            PyDateTime_IMPORT;

            if (!PyDateTimeAPI)
            {
                PyErr_Clear();
                return false;
            }
        }

        if (!PyDateTime_Check(src.ptr()))
        {
            return false;
        }

        const int year = PyDateTime_GET_YEAR(src.ptr());
        const int month = PyDateTime_GET_MONTH(src.ptr());
        const int day = PyDateTime_GET_DAY(src.ptr());

        const int hour = PyDateTime_DATE_GET_HOUR(src.ptr());
        const int minute = PyDateTime_DATE_GET_MINUTE(src.ptr());
        const int second = PyDateTime_DATE_GET_SECOND(src.ptr());

        const int microseconds = PyDateTime_DATE_GET_MICROSECOND(src.ptr());

        const int millisecond = microseconds / 1000;
        const int microsecond = microseconds - millisecond * 1000;

        try
        {
            value_.emplace(year, month, day, hour, minute, second, millisecond, microsecond);
        }
        catch (...)
        {
            return false;
        }

        valuePtr_ = &(*value_);

        // Possibility to add conditions to convert datetime.date and datetime.time

        return true;
    }

    // DateTime (C++) -> datetime.datetime (Python)
    static handle from_cpp(const DateTime& aDateTime, rv_policy /* policy */, cleanup_list* /* cleanup */) noexcept
    {
        // Lazy initialise the PyDateTime import
        if (!PyDateTimeAPI)
        {
            PyDateTime_IMPORT;

            if (!PyDateTimeAPI)
            {
                return handle();
            }
        }

        const int year = static_cast<int>(aDateTime.getDate().getYear());
        const int month = static_cast<int>(aDateTime.getDate().getMonth());
        const int day = static_cast<int>(aDateTime.getDate().getDay());
        const int hour = static_cast<int>(aDateTime.getTime().getHour());
        const int minute = static_cast<int>(aDateTime.getTime().getMinute());
        const int second = static_cast<int>(aDateTime.getTime().getSecond());
        const int microseconds = (aDateTime.getTime().getMillisecond() * 1000) + aDateTime.getTime().getMicrosecond();

        return PyDateTime_FromDateAndTime(year, month, day, hour, minute, second, microseconds);
    }

    static handle from_cpp(const DateTime* aDateTimePtr, rv_policy aPolicy, cleanup_list* aCleanup) noexcept
    {
        if (aDateTimePtr == nullptr)
        {
            return none().release();
        }

        return from_cpp(*aDateTimePtr, aPolicy, aCleanup);
    }

    explicit operator DateTime*()
    {
        return valuePtr_;
    }

    explicit operator DateTime&()
    {
        return *valuePtr_;
    }

    explicit operator DateTime&&()
    {
        return (DateTime&&)*valuePtr_;
    }

   private:
    DateTime* valuePtr_ = nullptr;
    std::optional<DateTime> value_;
};

}  // namespace detail
}  // namespace nanobind
