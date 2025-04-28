# Apache License 2.0

from datetime import timedelta

from ostk.core.type import String

from ostk.physics.unit import Time
from ostk.physics.time import Instant
from ostk.physics.time import Duration


class TestDuration:
    def test_constructor_success_duration(self):
        duration: Duration = Duration.seconds(123.0)
        assert Duration(duration) == duration

    def test_constructor_success_timedelta(self):
        assert Duration(timedelta(days=123)).in_days() == 123.0
        assert Duration(timedelta(hours=123)).in_hours() == 123.0
        assert Duration(timedelta(minutes=123)).in_minutes() == 123.0
        assert Duration(timedelta(seconds=123)).in_seconds() == 123.0
        assert (
            Duration(timedelta(seconds=123, microseconds=456000)).in_seconds() == 123.456
        )
        assert (
            Duration(timedelta(seconds=123, microseconds=456)).in_seconds() == 123.000456
        )
        assert Duration(timedelta(microseconds=456000)).in_seconds() == 0.456
        assert Duration(timedelta(microseconds=456)).in_seconds() == 0.000456

    def test_operators_success(self):
        duration_A = Duration.seconds(123.0)
        duration_B = Duration.seconds(456.0)

        assert (duration_A == duration_B) is not None
        assert (duration_A != duration_B) is not None

        assert (duration_A < duration_B) is not None
        assert (duration_A <= duration_B) is not None
        assert (duration_A > duration_B) is not None
        assert (duration_A >= duration_B) is not None

        assert (duration_A + duration_B) is not None
        assert (duration_A - duration_B) is not None

        assert (2.0 * duration_A) is not None
        assert (duration_A * 2.0) is not None
        assert (duration_A / 2.0) is not None

        duration_A += duration_B
        duration_A -= duration_B

        duration_A *= 2.0
        duration_A /= 2.0

    def test_is_defined_success(self):
        assert Duration.seconds(123.0).is_defined() is not None

    def test_is_zero_success(self):
        assert Duration.seconds(123.0).is_zero() is not None

    def test_is_positive_success(self):
        assert Duration.seconds(123.0).is_positive() is not None

    def test_is_strictly_positive_success(self):
        assert Duration.seconds(123.0).is_strictly_positive() is not None

    def test_is_near_success(self):
        assert (
            Duration.seconds(123.0).is_near(Duration.seconds(123.0), Duration.zero())
            is not None
        )

    def test_get_nanoseconds_success(self):
        assert Duration.seconds(123.0).get_nanoseconds() is not None

    def test_get_microseconds_success(self):
        assert Duration.seconds(123.0).get_microseconds() is not None

    def test_get_milliseconds_success(self):
        assert Duration.seconds(123.0).get_milliseconds() is not None

    def test_get_seconds_success(self):
        assert Duration.seconds(123.0).get_seconds() is not None

    def test_get_minutes_success(self):
        assert Duration.seconds(123.0).get_minutes() is not None

    def test_get_hours_success(self):
        assert Duration.seconds(123.0).get_hours() is not None

    def test_get_days_success(self):
        assert Duration.seconds(123.0).get_days() is not None

    def test_get_weeks_success(self):
        assert Duration.seconds(123.0).get_weeks() is not None

    def test_in_nanoseconds_success(self):
        assert Duration.seconds(123.0).in_nanoseconds() is not None

    def test_in_microseconds_success(self):
        assert Duration.seconds(123.0).in_microseconds() is not None

    def test_in_milliseconds_success(self):
        assert Duration.seconds(123.0).in_milliseconds() is not None

    def test_in_seconds_success(self):
        assert Duration.seconds(123.0).in_seconds() is not None

    def test_in_minutes_success(self):
        assert Duration.seconds(123.0).in_minutes() is not None

    def test_in_hours_success(self):
        assert Duration.seconds(123.0).in_hours() is not None

    def test_in_days_success(self):
        assert Duration.seconds(123.0).in_days() is not None

    def test_in_weeks_success(self):
        assert Duration.seconds(123.0).in_weeks() is not None

    def test_in_unit_success(self):
        assert Duration.seconds(123.0).in_unit(Time.Unit.Second) is not None

    def test_get_absolute_success(self):
        assert Duration.seconds(123.0).get_absolute() is not None

    def test_to_string_success(self):
        assert Duration.seconds(123.0).to_string() is not None
        assert Duration.seconds(123.0).to_string(Duration.Format.Standard)
        assert Duration.seconds(123.0).to_string(Duration.Format.ISO8601)

    def test_to_timedelta_success(self):
        assert isinstance(Duration.hours(1.0).to_timedelta(), timedelta)

        assert Duration.seconds(0.0).to_timedelta() == timedelta(seconds=0.0)

        assert Duration.nanoseconds(1.0).to_timedelta() == timedelta(microseconds=0.001)
        assert Duration.microseconds(1.0).to_timedelta() == timedelta(microseconds=1.0)
        assert Duration.seconds(1.0).to_timedelta() == timedelta(seconds=1.0)
        assert Duration.minutes(1.0).to_timedelta() == timedelta(minutes=1.0)
        assert Duration.hours(1.0).to_timedelta() == timedelta(hours=1.0)
        assert Duration.days(1.0).to_timedelta() == timedelta(days=1.0)

    def test_undefined_success(self):
        assert Duration.undefined() is not None

    def test_zero_success(self):
        assert Duration.zero() is not None

    def test_nanoseconds_success(self):
        assert Duration.nanoseconds(123.456) is not None

    def test_microseconds_success(self):
        assert Duration.microseconds(123.456) is not None

    def test_milliseconds_success(self):
        assert Duration.milliseconds(123.456) is not None

    def test_seconds_success(self):
        assert Duration.seconds(123.456) is not None

    def test_minutes_success(self):
        assert Duration.minutes(123.456) is not None

    def test_hours_success(self):
        assert Duration.hours(123.456) is not None

    def test_days_success(self):
        assert Duration.days(123.456) is not None

    def test_weeks_success(self):
        assert Duration.weeks(123.456) is not None

    def test_between_success(self):
        assert Duration.between(Instant.now(), Instant.now()) is not None

    def test_parse_success_python_str(self):
        # Testing with default format argument (Duration::Format::Undefined)
        duration = Duration.parse("02:03.456.000.000")

        assert duration is not None
        assert isinstance(duration, Duration)
        assert duration.is_defined() is True

        # Testing with Duration.Format.Standard
        duration = Duration.parse("02:03.456.000.000", Duration.Format.Standard)

        assert duration is not None
        assert isinstance(duration, Duration)
        assert duration.is_defined() is True

        # Testing with Duration.Format.ISO8601
        duration = Duration.parse("PT2M3.456S", Duration.Format.ISO8601)

        assert duration is not None
        assert isinstance(duration, Duration)
        assert duration.is_defined() is True

    def test_parse_success_string(self):
        # Testing with default format argument (Duration::Format::Undefined)
        duration = Duration.parse(String("02:03.456.000.000"))

        assert duration is not None
        assert isinstance(duration, Duration)
        assert duration.is_defined() is True

        # Testing with Duration.Format.Standard
        duration = Duration.parse(String("02:03.456.000.000"), Duration.Format.Standard)

        assert duration is not None
        assert isinstance(duration, Duration)
        assert duration.is_defined() is True

        # Testing with Duration.Format.ISO8601
        duration = Duration.parse(String("PT2M3.456S"), Duration.Format.ISO8601)

        assert duration is not None
        assert isinstance(duration, Duration)
        assert duration.is_defined() is True
