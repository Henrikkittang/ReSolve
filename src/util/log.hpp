#pragma once
#include<string>
#include<chrono>
#include<ctime>
#include<sstream>
#include<iomanip>
#include<cstdlib>
#include<mutex>
#include<string>
#include<sstream>

#include<glad/glad.h>

// | Level   | Meaning                                                     | Typical Use Cases                           |
// | ------- | ----------------------------------------------------------- | ------------------------------------------- |
// | `DEBUG` | Very detailed, noisy logs, mostly useful during development | Variable values, function entry/exit        |
// | `INFO`  | General information about app progress                      | "Scene loaded", "Renderer initialized"      |
// | `WARN`  | Something unexpected, but non-breaking                      | "Fallback to default shader", missing asset |
// | `ERROR` | A serious problem occurred, but app can continue            | Failed file load, OpenGL error              |
// | `FATAL` | Critical problem that forces app termination                | GL context failure, missing dependencies    |


enum class LogLevel { TRACE=0, DEBUG, INFO, WARN, ERROR, FATAL };

class Logger {
public:
    static void initilize(const std::string& logFilePath);
    static void log(LogLevel level, const char* file, int line, const char* func, const std::string& msg);

private:
    static std::string getTimestampStr();


private:
    static LogLevel      s_curLevel;
    static std::ofstream s_file;
    static std::mutex    s_mutex;

};


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
#define TERMINAL_BOLDWHITE   "\033[1m\033[37m"      /* Bold White */


#define LOG_TRACE(msg) Logger::log(LogLevel::TRACE, __FILE__, __LINE__, __func__, msg)
#define LOG_DEBUG(msg) Logger::log(LogLevel::DEBUG, __FILE__, __LINE__, __func__, msg)
#define LOG_INFO(msg)  Logger::log(LogLevel::INFO,  __FILE__, __LINE__, __func__, msg)
#define LOG_WARN(msg)  Logger::log(LogLevel::WARN,  __FILE__, __LINE__, __func__, msg)
#define LOG_ERROR(msg) Logger::log(LogLevel::ERROR, __FILE__, __LINE__, __func__, msg)
#define LOG_FATAL(msg) Logger::log(LogLevel::FATAL, __FILE__, __LINE__, __func__, msg)

#define CHECK_DEBUG(cond, msg) do { if (cond) LOG_DEBUG(msg); } while (0)
#define CHECK_INFO(cond, msg)  do { if (cond) LOG_INFO(msg); } while (0)
#define CHECK_WARN(cond, msg)  do { if (cond) LOG_WARN(msg); } while (0)
#define CHECK_ERROR(cond, msg) do { if (cond) LOG_ERROR(msg); } while (0)
#define CHECK_FATAL(cond, msg) do { if (cond) LOG_FATAL(msg); } while (0)



// ─── Platform-Specific Debug Break ─────────────────────────────────────────────
#if defined(_MSC_VER)
    #define DEBUG_BREAK() __debugbreak()
#else
    #define DEBUG_BREAK() __builtin_trap()
#endif

const char* getGLErrorString(GLenum error);
const char* getGLErrorHint(GLenum error);

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line, const char* context = nullptr);

const char* getDebugSource(GLenum source);
const char* getDebugType(GLenum type);
const char* getDebugSeverity(GLenum severity); 
void APIENTRY GLDebugCallback(GLenum source, GLenum type, GLuint id,
                                     GLenum severity, GLsizei length,
                                     const GLchar* message, const void* userParam); 
void enableOpenGLDebugOutput();


#define GLCall(x) GLClearError();\
    x;\
    if (!GLLogCall(#x, __FILE__, __LINE__)) DEBUG_BREAK()

#define GLCheck(x, context) GLClearError();\
    x;\
    if (!GLLogCall(#x, __FILE__, __LINE__, context)) DEBUG_BREAK()


