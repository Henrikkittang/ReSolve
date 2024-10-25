#pragma once

#include<chrono>

class Timer
{
public:
    Timer();

    double milliseconds() const;
    double seconds() const;
    void reset();

private:

    std::chrono::time_point<std::chrono::high_resolution_clock> m_time;

};
