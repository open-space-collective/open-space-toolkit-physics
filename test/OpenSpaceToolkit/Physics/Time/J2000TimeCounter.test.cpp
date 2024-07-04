/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Type/Integer.hpp>

#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

#include <Global.test.hpp>

/**
 * @brief Return the current sec/microsec pair elapsed since J2000 for a given point in time
 */
std::pair<uint32_t, uint32_t> get_hub_nav_time_at(
    const std::chrono::time_point<std::chrono::high_resolution_clock>& desired_time_point_utc
)
{
    // Double check that the epoch is 1970-01-01T00:00:00, since this can be dependent on the platform
    const std::chrono::time_point<std::chrono::high_resolution_clock> epoch;
    const std::time_t epoch_time = std::chrono::high_resolution_clock::to_time_t(epoch);
    if (std::string(std::ctime(&epoch_time)) != "Thu Jan  1 00:00:00 1970\n")
    {
        throw std::runtime_error("The epoch is not 1970-01-01T00:00:00");
    }

    // Convert the desired time point to a duration of continuous seconds since the Unix epoch
    const std::chrono::duration duration_since_unix_epoch = desired_time_point_utc.time_since_epoch();

    // Check that the desired time is not before the last leap second addition, and not too far in the future
    if (duration_since_unix_epoch < std::chrono::seconds(1483228827))
    {
        throw std::runtime_error(
            "This function cannot be used with epoch before the last leap second was added on 2016-12-31T23:59:60"
        );
    }

    // Difference between the Unix epoch and the J2000 epoch
    const std::chrono::duration duration_from_unix_to_j2000_epoch =
        std::chrono::nanoseconds(946727930815999980);

    // Obtain the duration_since_j2000_epoch
    const std::chrono::duration duration_since_j2000_epoch =
        duration_since_unix_epoch - duration_from_unix_to_j2000_epoch;

    // Extract seconds and microseconds from the duration
    auto seconds_since_j2000_epoch = std::chrono::duration_cast<std::chrono::seconds>(duration_since_j2000_epoch);
    auto micros_since_j2000_epoch =
        std::chrono::duration_cast<std::chrono::microseconds>(duration_since_j2000_epoch - seconds_since_j2000_epoch);

    return {
        static_cast<uint32_t>(seconds_since_j2000_epoch.count()),
        static_cast<uint32_t>(micros_since_j2000_epoch.count())
    };
}

/**
 * @brief Return the current sec/microsec pair elapsed since J2000 for the current point in time
 */
std::pair<uint32_t, uint32_t> get_hub_nav_time()
{
    // Get the current time point
    return get_hub_nav_time_at(std::chrono::high_resolution_clock::now());
}

TEST(OpenSpaceToolkit_Physics_Time_J2000TimeCounter, Validate)
{
    using ostk::physics::time::Scale;
    using ostk::physics::time::DateTime;
    using ostk::physics::time::Duration;
    using ostk::physics::time::Instant;

    // Test case for customer
    {
        // UTC time point
        int year = 2024;
        int month = 2;
        int day = 25;
        int hour = 11;
        int minute = 25;
        int second = 50;
        int microsecond = 200000;

        std::tm tm = {};           // Initialize to zero
        tm.tm_year = year - 1900;  // Year since 1900
        tm.tm_mon = month - 1;     // Month since January [0-11]
        tm.tm_mday = day;          // Day of the month [1-31]
        tm.tm_hour = hour;         // Hours since midnight [0-23]
        tm.tm_min = minute;        // Minutes after the hour [0-59]
        tm.tm_sec = second;        // Seconds after the minute [0-59]

        std::chrono::time_point<std::chrono::high_resolution_clock> time_point_utc =
            std::chrono::high_resolution_clock::from_time_t(std::mktime(&tm));
        time_point_utc += std::chrono::microseconds(microsecond);

        const std::pair<uint32_t, uint32_t> test_duration = get_hub_nav_time_at(time_point_utc);

        // std::cout << "Current time: " << test_duration.first << "s " << test_duration.second << "us" << std::endl;

        // Validate against the expected values
        EXPECT_EQ(test_duration.first, 762132419);
        EXPECT_EQ(test_duration.second, 384000);

        // Validate against ostk
        const Duration test_duration_ostk =
            (Instant::DateTime(DateTime(year, month, day, hour, minute, second, 0, 0, 0), Scale::UTC) +=
             Duration::Microseconds(microsecond)) -
            Instant::J2000();

        double ostk_whole_seconds = std::floor(test_duration_ostk.inSeconds());
        double ostk_whole_microseconds =
            std::round((test_duration_ostk.inSeconds() - ostk_whole_seconds) * std::pow(10.0, 6));

        EXPECT_EQ(test_duration.first, static_cast<uint32_t>(ostk_whole_seconds));
        EXPECT_EQ(test_duration.second, static_cast<uint32_t>(ostk_whole_microseconds));
    }

    // Test throw for epoch before the last leap second
    {
        // UTC time point
        int year = 2016;
        int month = 12;
        int day = 31;
        int hour = 23;
        int minute = 59;
        int second = 59;
        int microsecond = 999999;

        std::tm tm = {};           // Initialize to zero
        tm.tm_year = year - 1900;  // Year since 1900
        tm.tm_mon = month - 1;     // Month since January [0-11]
        tm.tm_mday = day;          // Day of the month [1-31]
        tm.tm_hour = hour;         // Hours since midnight [0-23]
        tm.tm_min = minute;        // Minutes after the hour [0-59]
        tm.tm_sec = second;        // Seconds after the minute [0-59]

        std::chrono::time_point<std::chrono::high_resolution_clock> time_point_utc =
            std::chrono::high_resolution_clock::from_time_t(std::mktime(&tm));
        time_point_utc += std::chrono::microseconds(microsecond);

        EXPECT_THROW(get_hub_nav_time_at(time_point_utc), std::runtime_error);
    }

    // Test a bunch of different cases equally spaced once per month until 2030 against ostk
    {
        for (int year = 2017; year <= 2030; year++)
        {
            for (int month = 1; month <= 12; month++)
            {
                // UTC time point
                int day = 1;
                int hour = 18;
                int minute = 32;
                int second = 15;
                int microsecond = 34859;

                std::tm tm = {};           // Initialize to zero
                tm.tm_year = year - 1900;  // Year since 1900
                tm.tm_mon = month - 1;     // Month since January [0-11]
                tm.tm_mday = day;          // Day of the month [1-31]
                tm.tm_hour = hour;         // Hours since midnight [0-23]
                tm.tm_min = minute;        // Minutes after the hour [0-59]
                tm.tm_sec = second;        // Seconds after the minute [0-59]

                std::chrono::time_point<std::chrono::high_resolution_clock> time_point_utc =
                    std::chrono::high_resolution_clock::from_time_t(std::mktime(&tm));
                time_point_utc += std::chrono::microseconds(microsecond);

                const std::pair<uint32_t, uint32_t> test_duration = get_hub_nav_time_at(time_point_utc);

                // Validate against ostk
                const Duration test_duration_ostk =
                    (Instant::DateTime(DateTime(year, month, day, hour, minute, second, 0, 0, 0), Scale::UTC) +=
                     Duration::Microseconds(microsecond)) -
                    Instant::J2000();

                double ostk_whole_seconds = std::floor(test_duration_ostk.inSeconds());
                double ostk_whole_microseconds =
                    std::round((test_duration_ostk.inSeconds() - ostk_whole_seconds) * std::pow(10.0, 6));

                EXPECT_EQ(test_duration.first, static_cast<uint32_t>(ostk_whole_seconds));
                EXPECT_EQ(test_duration.second, static_cast<uint32_t>(ostk_whole_microseconds));
            }
        }
    }

    // Test current time
    {
        const std::pair<uint32_t, uint32_t> test_duration = get_hub_nav_time();
        const Duration test_duration_ostk = Instant::Now() - Instant::J2000();

        // std::cout << "Current time: " << test_duration.first << "s " << test_duration.second << "us" << std::endl;

        // Validate against ostk

        double ostk_whole_seconds = std::floor(test_duration_ostk.inSeconds());
        double ostk_whole_microseconds =
            std::round((test_duration_ostk.inSeconds() - ostk_whole_seconds) * std::pow(10.0, 6));

        EXPECT_EQ(test_duration.first, static_cast<uint32_t>(ostk_whole_seconds));
        // EXPECT_EQ(test_duration.second, static_cast<uint32_t>(ostk_whole_microseconds)); // This will fail because
        // the std::chrono is called at a different time than the ostk::Instant::Now()
    }
}
