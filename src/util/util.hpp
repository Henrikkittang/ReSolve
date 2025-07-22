#pragma once

#include<iostream>
#include<string>
#include<sstream>
#include<glad/glad.h>

#include"log.hpp"

// ─── Platform-Specific Debug Break ─────────────────────────────────────────────
#if defined(_MSC_VER)
    #define DEBUG_BREAK() __debugbreak()
#else
    #define DEBUG_BREAK() __builtin_trap()
#endif

// ─── OpenGL Error Name & Hint ──────────────────────────────────────────────────
inline const char* GetGLErrorString(GLenum error) 
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

inline const char* GetGLErrorHint(GLenum error) 
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
inline void GLClearError() 
{
    while (glGetError() != GL_NO_ERROR);
}

inline bool GLLogCall(const char* function, const char* file, int line, const char* context = nullptr) 
{
    bool success = true;
    while (GLenum error = glGetError()) 
    {
        std::stringstream ss;
        ss << "OpenGL Error: " << GetGLErrorString(error)
           << " (" << error << ")";
        if (context) ss << " in " << context;
        ss << "\n  Function: " << function
           << "\n  Location: " << file << ":" << line;
        const char* hint = GetGLErrorHint(error);
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
inline const char* GetDebugSource(GLenum source) 
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

inline const char* GetDebugType(GLenum type) 
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

inline const char* GetDebugSeverity(GLenum severity) 
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

inline void APIENTRY GLDebugCallback(GLenum source, GLenum type, GLuint id,
                                     GLenum severity, GLsizei /*length*/,
                                     const GLchar* message, const void* /*userParam*/) 
                                     {
    std::stringstream ss;
    ss << "[GL DEBUG] Type: " << GetDebugType(type)
       << " | Severity: " << GetDebugSeverity(severity)
       << " | Source: " << GetDebugSource(source)
       << "\n  Message: " << message;
    
    GL_DEBUG_SEVERITY_HIGH ? LOG_ERROR(ss.str()) : LOG_WARN(ss.str());    
}

inline void EnableOpenGLDebugOutput() 
{
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(GLDebugCallback, nullptr);
}
// #endif



inline void DEBUG_LOG(const std::string& msg)
{
#ifdef RS_DEBUG
    std::cout << msg << "\n";
#endif
}

inline void DEBUG_CHECK(bool cond, const std::string& msg)
{
#ifdef RS_DEBUG
    if(cond)
        std::cout << msg << "\n";
#endif
}