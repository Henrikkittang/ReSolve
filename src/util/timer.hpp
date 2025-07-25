#pragma once

#include<chrono>
#include<fmt/core.h>

#include"core/base.hpp"

template<typename Duration = std::chrono::seconds>
class ScopedTimer
{
public:
    ScopedTimer()
        : m_time(Clock::now())
    {}

    ~ScopedTimer()
    {

        auto now = Clock::now();

        // Convert to duration<double, Ratio> to get fractional count
        std::chrono::duration<double, typename Duration::period> elapsed = now - m_time;
        double elapsed_time = elapsed.count();

        if constexpr (std::is_same_v<Duration, std::chrono::seconds>)
            fmt::println("Time elapsed: {} [s]", elapsed_time);
        else if constexpr (std::is_same_v<Duration, std::chrono::milliseconds>)
            fmt::println("Time elapsed: {} [ms]", elapsed_time);
        else if constexpr (std::is_same_v<Duration, std::chrono::microseconds>)
            fmt::println("Time elapsed: {} [us]", elapsed_time);
        else if constexpr (std::is_same_v<Duration, std::chrono::nanoseconds>)
            fmt::println("Time elapsed: {} [ns]", elapsed_time);
        else
            fmt::println("Time elapsed: {} (custom duration units)", elapsed_time);

    }

private:
    Clock::time_point m_time;
};
