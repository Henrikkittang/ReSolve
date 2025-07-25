#pragma once

#include<chrono>
#include<functional>

using Clock = std::chrono::high_resolution_clock;

using Second = std::chrono::seconds;
using Milli  = std::chrono::milliseconds;
using Micro  = std::chrono::microseconds;
using Nano   = std::chrono::nanoseconds;


template<typename T>
using Ref = std::shared_ptr<T>;

template<typename T>
using FuncRef = std::function<Ref<T>()>;

// ─── Platform-Specific Debug Break ─────────────────────────────────────────────
#if defined(_MSC_VER)
    #define DEBUG_BREAK() __debugbreak()
#elif __clang__ || __GNUC__
    #define DEBUG_BREAK() __builtin_trap()
#else
    #error "Debug break not defined" 
#endif