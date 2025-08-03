#pragma once
#include<string>
#include<chrono>
#include<mutex>
#include<source_location>


#include<glad/glad.h>
#include<spdlog/spdlog.h>

#include"core/base.hpp"

// | Level   | Meaning                                                     | Typical Use Cases                           |
// | ------- | ----------------------------------------------------------- | ------------------------------------------- |
// | `DEBUG` | Very detailed, noisy logs, mostly useful during development | Variable values, function entry/exit        |
// | `INFO`  | General information about app progress                      | "Scene loaded", "Renderer initialized"      |
// | `WARN`  | Something unexpected, but non-breaking                      | "Fallback to default shader", missing asset |
// | `ERROR` | A serious problem occurred, but app can continue            | Failed file load, OpenGL error              |
// | `FATAL` | Critical problem that forces app termination                | GL context failure, missing dependencies    |


class Logger {
public:
    static void initialize();
    static Ref<spdlog::logger> getLogger() { return s_logger; }

private:
    static Ref<spdlog::logger> s_logger;

};


#define LOG_TRACE(...) Logger::getLogger()->trace(__VA_ARGS__)
#define LOG_DEBUG(...) Logger::getLogger()->debug(__VA_ARGS__)
#define LOG_INFO(...)  Logger::getLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)  Logger::getLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...) Logger::getLogger()->error(__VA_ARGS__)
#define LOG_FATAL(...) Logger::getLogger()->critical(__VA_ARGS__)

#define CHECK_DEBUG(cond, ...) do { if (cond) LOG_DEBUG(__VA_ARGS__); } while (0)
#define CHECK_INFO(cond, ...)  do { if (cond) LOG_INFO(__VA_ARGS__); } while (0)
#define CHECK_WARN(cond, ...)  do { if (cond) LOG_WARN(__VA_ARGS__); } while (0)
#define CHECK_ERROR(cond, ...) do { if (cond) LOG_ERROR(__VA_ARGS__); } while (0)
#define CHECK_FATAL(cond, ...) do { if (cond) LOG_FATAL(__VA_ARGS__); } while (0)





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


