#include"log.hpp"

#include<filesystem>

#include<fmt/core.h>
#include<fmt/base.h>
#include<fmt/color.h>
#include<fmt/chrono.h>

LogLevel      Logger::s_curLevel;
std::mutex    Logger::s_mutex;

// TODO: Log files
// TODO: Log level filter
// ? Swap out in favor off spdlog
// ? Make more customizable
// ? Add async queue for messages
// ? Remove fmt in favor of built-in print and format

void Logger::initilize(const std::string& logFilePath)
{
    #if __cplusplus == 202002L
        fmt::println("C++20");
    #elif __cplusplus == 202300L
        fmt::println("C++23");
    #elif __cplusplus > 202002L
        fmt::println("C++23 or newer (__cplusplus = {})", __cplusplus);
    #elif __cplusplus == 201703L
        fmt::println("C++17");
    #elif __cplusplus == 201402L
        fmt::println("C++14");
    #elif __cplusplus == 201103L
        fmt::println("C++11");
    #elif __cplusplus == 199711L
        fmt::println("C++98");
    #else
        fmt::println("pre-standard or unknown (__cplusplus = {})", __cplusplus);
    #endif

    #ifdef _MSC_VER
        fmt::println("Compiled with MSVC");
    #elif defined(__clang__)
        fmt::println("Compiled with Clang");
    #elif defined(__GNUC__)
        fmt::println("Compiled with GCC");
    #else
        fmt::println("Compiler not detected");
    #endif

    #if RS_DEBUG
        fmt::println("Debug mode is active.");
    #elif RS_RELEASE
        fmt::println("Release mode is active.");
    #else
        fmt::println("No mode is active.");
    #endif

}

void Logger::log(LogLevel level, const std::string& msg, std::source_location locaction)
{
#ifdef RS_DEBUG
   
    std::lock_guard<std::mutex> lock(s_mutex);

    fmt::color color;
    std::string levelLabel;

    switch (level) 
    {
        case LogLevel::DEBUG: levelLabel = "DEBUG"; color = fmt::color::cyan; break;
        case LogLevel::INFO:  levelLabel = "INFO";  color = fmt::color::green; break;
        case LogLevel::WARN:  levelLabel = "WARN";  color = fmt::color::yellow; break;
        case LogLevel::ERROR: levelLabel = "ERROR"; color = fmt::color::red; break;
        case LogLevel::FATAL: levelLabel = "FATAL"; color = fmt::color::magenta; break;
    }

    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);

    // TODO: Add "./"
    std::filesystem::path relativePath = std::filesystem::relative(locaction.file_name(), SOURCE_DIR);

    // fmt::print("\n[{:%Y-%m-%d %H:%M:%S}] {}: {}\n{}:{}({})\n\n",
    //     *std::localtime(&time),
    //     fmt::format(fg(color) | fmt::emphasis::bold, "[{}]", levelLabel),
    //     fmt::format(fmt::emphasis::bold, "{}", msg),
    //     relativePath.c_str(), locaction.line(), locaction.function_name()
    // );

    
    fmt::print("\n{}: {} \n {}:  {:%Y-%m-%d %H:%M:%S} \n {}: {} \n {}: ./{}:{}\n\n",
        fmt::format(fg(color) | fmt::emphasis::bold, "[{}]", levelLabel),
        fmt::format(fmt::emphasis::italic | fmt::emphasis::underline, "{}", msg),
        fmt::format(fmt::emphasis::bold, "Time"), *std::localtime(&time),
        fmt::format(fmt::emphasis::bold, "Function"), locaction.function_name(),
        fmt::format(fmt::emphasis::bold, "Location"), relativePath.c_str(), locaction.line()
    );

    if (level == LogLevel::FATAL) 
        exit(1);
#endif 
}






// ─── OpenGL Error Name & Hint ──────────────────────────────────────────────────
const char* getGLErrorString(GLenum error) 
{
    switch (error) 
    {
        case GL_NO_ERROR:                      return "GL_NO_ERROR";
        case GL_INVALID_ENUM:                  return "GL_INVALID_ENUM";
        case GL_INVALID_VALUE:                 return "GL_INVALID_VALUE";
        case GL_INVALID_OPERATION:             return "GL_INVALID_OPERATION";
        case GL_STACK_OVERFLOW:                return "GL_STACK_OVERFLOW";
        case GL_STACK_UNDERFLOW:               return "GL_STACK_UNDERFLOW";
        case GL_OUT_OF_MEMORY:                 return "GL_OUT_OF_MEMORY";
        case GL_INVALID_FRAMEBUFFER_OPERATION: return "GL_INVALID_FRAMEBUFFER_OPERATION";
        default:                               return "UNKNOWN_GL_ERROR";
    }
}

const char* getGLErrorHint(GLenum error) 
{
    switch (error) 
    {
        case GL_INVALID_ENUM: return "Likely caused by an invalid enum value.";
        case GL_INVALID_VALUE: return "Numeric argument is out of range.";
        case GL_INVALID_OPERATION: return "Operation is not allowed in the current state.";
        case GL_OUT_OF_MEMORY: return "System ran out of memory.";
        default: return "No hint";
    }
}

// ─── Error Clearing & Logging ──────────────────────────────────────────────────
void GLClearError() 
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* context, std::source_location locaction) 
{
    bool success = true;
    while (GLenum error = glGetError()) 
    {
        const char* hint = getGLErrorHint(error);
        fmt::print("[OpenGL ERROR]: {} ({}) \n  Function: \n Location: {}:{} \n Hint: {}",
            getGLErrorString(error), error,
            function,
            locaction.file_name(), locaction.line(),
            hint 
        );

        success = false;
    }
    return success;
}

// ─── Optional: OpenGL Debug Output (GL 4.3+) ───────────────────────────────────
// #ifdef GL_ARB_debug_output
const char* getDebugSource(GLenum source) 
{
    switch (source) 
    {
        case GL_DEBUG_SOURCE_API: return "API";
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM: return "Window System";
        case GL_DEBUG_SOURCE_SHADER_COMPILER: return "Shader Compiler";
        case GL_DEBUG_SOURCE_THIRD_PARTY: return "Third Party";
        case GL_DEBUG_SOURCE_APPLICATION: return "Application";
        case GL_DEBUG_SOURCE_OTHER: return "Other";
        default: return "Unknown";
    }
}

const char* getDebugType(GLenum type) 
{
    switch (type) 
    {
        case GL_DEBUG_TYPE_ERROR: return "Error";
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "Deprecated Behavior";
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: return "Undefined Behavior";
        case GL_DEBUG_TYPE_PORTABILITY: return "Portability";
        case GL_DEBUG_TYPE_PERFORMANCE: return "Performance";
        case GL_DEBUG_TYPE_MARKER: return "Marker";
        case GL_DEBUG_TYPE_OTHER: return "Other";
        default: return "Unknown";
    }
}

const char* getDebugSeverity(GLenum severity) 
{
    switch (severity) 
    {
        case GL_DEBUG_SEVERITY_HIGH: return "High";
        case GL_DEBUG_SEVERITY_MEDIUM: return "Medium";
        case GL_DEBUG_SEVERITY_LOW: return "Low";
        case GL_DEBUG_SEVERITY_NOTIFICATION: return "Notification";
        default: return "Unknown";
    }
}

void APIENTRY GLDebugCallback(GLenum source, GLenum type, GLuint id,
                                     GLenum severity, GLsizei length,
                                     const GLchar* message, const void* userParam) 
{

    fmt::print( "[GL DEBUG] Type: {} | Severity: {} | Source: {} \n Message: {}", 
        getDebugType(type),
        getDebugSeverity(severity),
        getDebugSource(source),
        message
    );

    // GL_DEBUG_SEVERITY_HIGH ? LOG_ERROR(ss.str()) : LOG_WARN(ss.str());    
}

void enableOpenGLDebugOutput() 
{
    GLCall( glEnable(GL_DEBUG_OUTPUT) );
    GLCall( glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS) );
    GLCall( glDebugMessageCallback(GLDebugCallback, nullptr) );
    GLCall( glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE) );
}
// #endif




