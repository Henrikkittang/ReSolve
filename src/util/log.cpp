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

    oss << ": " << TERMINAL_BOLDWHITE << msg << TERMINAL_RESET << "\n";
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
        default: return "";
    }
}

// ─── Error Clearing & Logging ──────────────────────────────────────────────────
void GLClearError() 
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line, const char* context) 
{
    bool success = true;
    while (GLenum error = glGetError()) 
    {
        std::stringstream ss;
        ss << "OpenGL Error: " << getGLErrorString(error)
           << " (" << error << ")";
        if (context) ss << " in " << context;
        ss << "\n  Function: " << function
           << "\n  Location: " << file << ":" << line;
        const char* hint = getGLErrorHint(error);
        if (*hint) ss << "\n  Hint:     " << hint;

        LOG_ERROR( ss.str() );
        success = false;
    }
    return success;
}

#define GLCall(x) GLClearError();\
    x;\
    if (!GLLogCall(#x, __FILE__, __LINE__)) DEBUG_BREAK()

#define GLCheck(x, context) GLClearError();\
    x;\
    if (!GLLogCall(#x, __FILE__, __LINE__, context)) DEBUG_BREAK()

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
                                     GLenum severity, GLsizei /*length*/,
                                     const GLchar* message, const void* /*userParam*/) 
                                     {
    std::stringstream ss;
    ss << "[GL DEBUG] Type: " << getDebugType(type)
       << " | Severity: " << getDebugSeverity(severity)
       << " | Source: " << getDebugSource(source)
       << "\n  Message: " << message;
    
    GL_DEBUG_SEVERITY_HIGH ? LOG_ERROR(ss.str()) : LOG_WARN(ss.str());    
}

void enableOpenGLDebugOutput() 
{
    GLCall( glEnable(GL_DEBUG_OUTPUT) );
    GLCall( glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS) );
    GLCall( glDebugMessageCallback(GLDebugCallback, nullptr) );
    GLCall( glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE) );
}
// #endif




