#pragma once
#include<string>
#include<chrono>
#include<mutex>
#include<source_location>


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
    static void log(LogLevel level, const std::string& msg, std::source_location locaction = std::source_location::current());


private:
    static LogLevel      s_curLevel;
    static std::ofstream s_file;
    static std::mutex    s_mutex;

};


#define LOG_TRACE(msg) Logger::log(LogLevel::TRACE, msg)
#define LOG_DEBUG(msg) Logger::log(LogLevel::DEBUG, msg)
#define LOG_INFO(msg)  Logger::log(LogLevel::INFO,  msg)
#define LOG_WARN(msg)  Logger::log(LogLevel::WARN,  msg)
#define LOG_ERROR(msg) Logger::log(LogLevel::ERROR, msg)
#define LOG_FATAL(msg) Logger::log(LogLevel::FATAL, msg)

#define CHECK_DEBUG(cond, msg) do { if (cond) LOG_DEBUG(msg); } while (0)
#define CHECK_INFO(cond, msg)  do { if (cond) LOG_INFO(msg); } while (0)
#define CHECK_WARN(cond, msg)  do { if (cond) LOG_WARN(msg); } while (0)
#define CHECK_ERROR(cond, msg) do { if (cond) LOG_ERROR(msg); } while (0)
#define CHECK_FATAL(cond, msg) do { if (cond) LOG_FATAL(msg); } while (0)



// ─── Platform-Specific Debug Break ─────────────────────────────────────────────
#if defined(_MSC_VER)
    #define DEBUG_BREAK() __debugbreak()
#elif __clang__ || __GNUC__
    #define DEBUG_BREAK() __builtin_trap()
#else
    #error "Debug break not defined" 
#endif

const char* getGLErrorString(GLenum error);
const char* getGLErrorHint(GLenum error);

void GLClearError();
bool GLLogCall(const char* function, const char* context = nullptr, std::source_location locaction = std::source_location::current());

const char* getDebugSource(GLenum source);
const char* getDebugType(GLenum type);
const char* getDebugSeverity(GLenum severity); 
void APIENTRY GLDebugCallback(GLenum source, GLenum type, GLuint id,
                                     GLenum severity, GLsizei length,
                                     const GLchar* message, const void* userParam); 
void enableOpenGLDebugOutput();


#define GLCall(x) GLClearError();\
    x;\
    if (!GLLogCall(#x)) DEBUG_BREAK()

#define GLCheck(x, context) GLClearError();\
    x;\
    if (!GLLogCall(#x, context)) DEBUG_BREAK()


