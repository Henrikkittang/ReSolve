#pragma once

#include<iostream>
#include<type_traits>
#include<chrono>

using Clock = std::chrono::high_resolution_clock;

using Second = std::chrono::seconds;
using Milli  = std::chrono::milliseconds;
using Micro  = std::chrono::microseconds;
using Nano   = std::chrono::nanoseconds;


template<typename Duration = std::chrono::seconds>
class ScopedTimer
{
public:
    ScopedTimer()
        : m_time(std::chrono::high_resolution_clock::now())
    {}

    ~ScopedTimer()
    {
        auto now = std::chrono::high_resolution_clock::now();

        // Convert to duration<double, Ratio> to get fractional count
        std::chrono::duration<double, typename Duration::period> elapsed = now - m_time;
        double elapsed_time = elapsed.count();

        std::cout << "Time elapsed: " << elapsed_time;

        if constexpr (std::is_same_v<Duration, std::chrono::seconds>)
            std::cout << " [s]\n";
        else if constexpr (std::is_same_v<Duration, std::chrono::milliseconds>)
            std::cout << " [ms]\n";
        else if constexpr (std::is_same_v<Duration, std::chrono::microseconds>)
            std::cout << " [us]\n";
        else if constexpr (std::is_same_v<Duration, std::chrono::nanoseconds>)
            std::cout << " [ns]\n";
        else
            std::cout << " (custom duration units)\n";
    }

private:
    std::chrono::high_resolution_clock::time_point m_time;
};
