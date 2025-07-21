#include"log.hpp"
#include<iostream>

void Logger::Init(const std::string& logFilePath)
{

}

void Logger::Log(LogLevel level, const char* file, int line, const char* func, const std::string& msg)
{
#ifdef DEBUG
    switch (level) {
        case LogLevel::DEBUG: return;
        case LogLevel::INFO:  return;
        case LogLevel::WARN:  return;
    }
#endif 

    switch (level) {
        case LogLevel::DEBUG: std::cout << "[DEBUG] "; break;
        case LogLevel::INFO:  std::cout << "[INFO]  "; break;
        case LogLevel::WARN:  std::cout << "[WARN]  "; break;

        case LogLevel::ERROR: std::cout << "[ERROR] "; break;
        case LogLevel::FATAL: std::cout << "[FATAL] "; break;
    }



    std::cout << msg << "\n";
    
    if (level == LogLevel::FATAL) {
        exit(1); // or exit(1)
    }
}

void Logger::SetLogLevel(LogLevel level) {}


