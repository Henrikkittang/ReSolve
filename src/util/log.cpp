#include"log.hpp"

#include<filesystem>


#include<spdlog/sinks/stdout_color_sinks.h>
#include<spdlog/sinks/basic_file_sink.h>


Ref<spdlog::logger> Logger::s_logger;


void Logger::initialize()
{
    std::vector<spdlog::sink_ptr> logSinks;
    logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
    logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("ReSolve.log", true));

    logSinks[0]->set_pattern("[%T] [%^%l%$] %n: %v \n");
    logSinks[1]->set_pattern("[%T] [%^%l%$] [%s:%# - %!] %v");

    s_logger = std::make_shared<spdlog::logger>("RESOLVE", begin(logSinks), end(logSinks));
    spdlog::register_logger(s_logger);
    s_logger->set_level(spdlog::level::trace);
    s_logger->flush_on(spdlog::level::trace);

    // ? Kinda shakey code, maybe better to just print out the macro value
    constexpr auto cpp_version = __cplusplus;
    if( cpp_version > 202002L)        LOG_INFO("Version C++23 or newer (__cplusplus = {})", __cplusplus);
    else if( cpp_version ==  202300L) LOG_INFO("Version C++23");
    else if( cpp_version ==  202002L) LOG_INFO("Version C++20");
    else if( cpp_version ==  201703L) LOG_INFO("Version C++17");
    else if( cpp_version ==  201402L) LOG_INFO("Version C++14");
    else if( cpp_version ==  201103L) LOG_INFO("Version C++11");
    else if( cpp_version ==  199711L) LOG_INFO("Version C++98");
    else LOG_INFO("pre-standard or unknown (__cplusplus = {})", __cplusplus);


    #ifdef _MSC_VER
        LOG_INFO("Compiled with MSVC");
    #elif defined(__clang__)
        LOG_INFO("Compiled with Clang");
    #elif defined(__GNUC__)
        LOG_INFO("Compiled with GCC");
    #else
        LOG_INFO("Compiler not detected");
    #endif

    #if RS_DEBUG
        LOG_INFO("Debug mode is active.");
    #elif RS_RELEASE
        LOG_INFO("Release mode is active.");
    #else
        LOG_INFO("No mode is active.");
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

bool GLLogCall(const char* function, const char* context, std::source_location location) 
{
    bool success = true;
    while (GLenum error = glGetError()) 
    {
        const char* hint = getGLErrorHint(error);
        LOG_ERROR("[OpenGL ERROR]: {} ({}) \n  Function: \n Location: {}:{} \n Hint: {}",
            getGLErrorString(error), error,
            function,
            location.file_name(), location.line(),
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

    LOG_ERROR( "[GL DEBUG] Type: {} | Severity: {} | Source: {} \n Message: {}", 
        getDebugType(type),
        getDebugSeverity(severity),
        getDebugSource(source),
        message
    );

}

void enableOpenGLDebugOutput() 
{
    GLCall( glEnable(GL_DEBUG_OUTPUT) );
    GLCall( glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS) );
    GLCall( glDebugMessageCallback(GLDebugCallback, nullptr) );
    GLCall( glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE) );
}
// #endif




