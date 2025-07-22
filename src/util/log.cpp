#include"log.hpp"
#include<iostream>

void Logger::init(const std::string& logFilePath)
{

}

void Logger::log(LogLevel level, const char* file, int line, const char* func, const std::string& msg)
{
    // This distinction might become kinda weird
#ifdef RS_DEBUG
   
    std::cout << "\n";

    switch (level) 
    {
        case LogLevel::DEBUG: std::cout << TERMINAL_CYAN    << "[DEBUG]" << TERMINAL_RESET; break;
        case LogLevel::INFO:  std::cout << TERMINAL_GREEN   << "[INFO]" << TERMINAL_RESET; break;
        case LogLevel::WARN:  std::cout << TERMINAL_YELLOW  << "[WARN]" << TERMINAL_RESET; break;
        case LogLevel::ERROR: std::cout << TERMINAL_RED     << "[ERROR]" << TERMINAL_RESET; break;
        case LogLevel::FATAL: std::cout << TERMINAL_MAGENTA << "[FATAL]" << TERMINAL_RESET; break;
    }

    std::cout << ": " << msg << "\n";
    std::cout <<  file << ":" << line << "(" << func << ")\n\n";


    // if (level == LogLevel::FATAL) 
    //     exit(1);
#endif 
}



