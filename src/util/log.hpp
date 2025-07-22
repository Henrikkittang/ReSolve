#pragma once
#include<string>


enum class LogLevel { TRACE=0, DEBUG, INFO, WARN, ERROR, FATAL };

// NB! These should be changed to 'using' or idealy fmt
#define TERMINAL_BLACK   "\033[30m"      
#define TERMINAL_RED     "\033[31m"      
#define TERMINAL_GREEN   "\033[32m"      
#define TERMINAL_YELLOW  "\033[33m"      
#define TERMINAL_BLUE    "\033[34m"      
#define TERMINAL_MAGENTA "\033[35m"      
#define TERMINAL_CYAN    "\033[36m"      
#define TERMINAL_WHITE   "\033[37m"      
#define TERMINAL_RESET   "\033[0m"

class Logger {
public:
    static void init(const std::string& logFilePath);
    static void log(LogLevel level, const char* file, int line, const char* func, const std::string& msg);

    

private:
    static LogLevel currentLevel;
};


#define LOG_TRACE(msg) Logger::log(LogLevel::TRACE, __FILE__, __LINE__, __func__, msg)
#define LOG_DEBUG(msg) Logger::log(LogLevel::DEBUG, __FILE__, __LINE__, __func__, msg)
#define LOG_INFO(msg)  Logger::log(LogLevel::INFO,  __FILE__, __LINE__, __func__, msg)
#define LOG_WARN(msg)  Logger::log(LogLevel::WARN,  __FILE__, __LINE__, __func__, msg)
#define LOG_ERROR(msg) Logger::log(LogLevel::ERROR, __FILE__, __LINE__, __func__, msg)
#define LOG_FATAL(msg) Logger::log(LogLevel::FATAL, __FILE__, __LINE__, __func__, msg)
