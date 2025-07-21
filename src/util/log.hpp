#include<string>


enum class LogLevel { TRACE=0, DEBUG, INFO, WARN, ERROR, FATAL };



class Logger {
public:
    static void Init(const std::string& logFilePath);
    static void Log(LogLevel level, const char* file, int line, const char* func, const std::string& msg);

    // Optional: set log level filter
    static void SetLogLevel(LogLevel level);

private:
    static LogLevel currentLevel;
};


#define LOG_TRACE(msg) Logger::Log(LogLevel::TRACE, __FILE__, __LINE__, __func__, msg)
#define LOG_DEBUG(msg) Logger::Log(LogLevel::DEBUG, __FILE__, __LINE__, __func__, msg)
#define LOG_INFO(msg)  Logger::Log(LogLevel::INFO,  __FILE__, __LINE__, __func__, msg)
#define LOG_WARN(msg)  Logger::Log(LogLevel::WARN,  __FILE__, __LINE__, __func__, msg)
#define LOG_ERROR(msg) Logger::Log(LogLevel::ERROR, __FILE__, __LINE__, __func__, msg)
#define LOG_FATAL(msg) Logger::Log(LogLevel::FATAL, __FILE__, __LINE__, __func__, msg)
