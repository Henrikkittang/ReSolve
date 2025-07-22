#include"log.hpp"
#include<iostream>


LogLevel      Logger::s_curLevel;
std::mutex    Logger::s_mutex;

void Logger::initilize(const std::string& logFilePath)
{
    
}



void Logger::log(LogLevel level, const char* file, int line, const char* func, const std::string& msg)
{
#ifdef RS_DEBUG
   
    std::lock_guard<std::mutex> lock(s_mutex);

    std::ostringstream oss;
    oss << "\n";
    oss << "[" << getTimestampStr() << "] ";

    switch (level) 
    {
        case LogLevel::DEBUG: oss << TERMINAL_CYAN    << "[DEBUG]" << TERMINAL_RESET; break;
        case LogLevel::INFO:  oss << TERMINAL_GREEN   << "[INFO]"  << TERMINAL_RESET; break;
        case LogLevel::WARN:  oss << TERMINAL_YELLOW  << "[WARN]"  << TERMINAL_RESET; break;
        case LogLevel::ERROR: oss << TERMINAL_RED     << "[ERROR]" << TERMINAL_RESET; break;
        case LogLevel::FATAL: oss << TERMINAL_MAGENTA << "[FATAL]" << TERMINAL_RESET; break;
    }

    oss << ": " << msg << "\n";
    oss <<  file << ":" << line << "(" << func << ")\n\n";

    std::cout << oss.str();

    if (level == LogLevel::FATAL) 
        exit(1);
#endif 
}




std::string Logger::getTimestampStr() 
{
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::tm tm;
#if defined(_WIN32)
    localtime_s(&tm, &time);
#else
    localtime_r(&time, &tm);
#endif
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}



